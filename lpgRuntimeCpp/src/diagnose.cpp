#include "diagnose.h"

#include <chrono>
#include <iostream>
#include <sstream>

#include "ConfigurationElement.h"
#include "ConfigurationStack.h"
#include "Monitor.h"
#include "ParseTable.h"
#include "stringex.h"
#include "TokenStream.h"

DiagnoseParser::PrimaryRepairInfo::PrimaryRepairInfo(PrimaryRepairInfo& clone)
{
	copy(clone);
}

DiagnoseParser::SecondaryRepairInfo::SecondaryRepairInfo(): code(0), distance(0), bufferPosition(0), stackPosition(0),
                                                            numDeletions(0),
                                                            symbol(0),
                                                            recoveryOnNextStack(false
                                                            )
{
}

DiagnoseParser::StateInfo::StateInfo()
{
}

DiagnoseParser::DiagnoseParser(TokenStream* tokStream, ParseTable* prs, Monitor* monitor, int maxErrors, long maxTime):ParseTableProxy(prs),
	stateStackTop(0),
	tempStackTop(0),
	prevStackTop(0),
	nextStackTop(0),
	scopeStackTop(0),
	statePool(256, 4)
{
	main_configuration_stack = std::make_shared<ConfigurationStack>(this);
		this->monitor = monitor;
	this->maxErrors = maxErrors;
	this->maxTime = maxTime;
	this->tokStream = tokStream;
	

	//ERROR_SYMBOL = prs->getErrorSymbol();
	//SCOPE_SIZE = prs->getScopeSize();
	//MAX_NAME_LENGTH = prs->getMaxNameLength();
	//NT_OFFSET = prs->getNtOffset();
	//LA_STATE_OFFSET = prs->getLaStateOffset();
	//NUM_RULES = prs->getNumRules();
	//NUM_SYMBOLS = prs->getNumSymbols();
	//START_STATE = prs->getStartState();
	//EOFT_SYMBOL = prs->getEoftSymbol();
	//EOLT_SYMBOL = prs->getEoltSymbol();
	//ACCEPT_ACTION = prs->getAcceptAction();
	//ERROR_ACTION = prs->getErrorAction();

	buffer.Resize(BUFF_SIZE);
	list.Resize(NUM_SYMBOLS + 1);
	list.MemReset();
}

void DiagnoseParser::reallocateStacks()
{
	int new_size = stateStack.Size() + STACK_INCREMENT;

	assert(new_size <= SHRT_MAX);

	stateStack.Resize(new_size);
	locationStack.Resize(new_size);
	tempStack.Resize(new_size);
	nextStack.Resize(new_size);
	prevStack.Resize(new_size);
	scopeIndex.Resize(new_size);
	scopePosition.Resize(new_size);
	
}

void DiagnoseParser::diagnoseEntry(int marker_kind, int error_token)
{
	IntTuple action(1 << 18);
	std::chrono::milliseconds startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);
	//long startTime = System.currentTimeMillis();
	int errorCount = 0;

	//
	// Compute sequence of actions that leads us to the
	// error_token.
	//
	if (!stateStack.Size())
		reallocateStacks();
	
	tempStackTop = 0;
	tempStack[tempStackTop] = START_STATE;
	tokStream->reset();
	int current_token,
	    current_kind;
	if (marker_kind == 0)
	{
		current_token = tokStream->getToken();
		current_kind = tokStream->getKind(current_token);
	}
	else
	{
		current_token = tokStream->peek();
		current_kind = marker_kind;
	}

	parseUpToError(action, current_kind, error_token);

	//
	// Start parsing
	//
	stateStackTop = 0;
	stateStack[stateStackTop] = START_STATE;

	tempStackTop = stateStackTop;
	
	//System.arraycopy(tempStack, 0, stateStack, 0, tempStackTop + 1);
	System::arraycopy(tempStack, 0, stateStack, 0, tempStackTop + 1);

	
	tokStream->reset();
	if (marker_kind == 0)
	{
		current_token = tokStream->getToken();
		current_kind = tokStream->getKind(current_token);
	}
	else
	{
		current_token = tokStream->peek();
		current_kind = marker_kind;
	}
	locationStack[stateStackTop] = current_token;

	//
	// Process a terminal
	//
	int act;
	do
	{
		//
		// Synchronize state stacks and update the location stack
		//
		int prev_pos = -1;
		prevStackTop = -1;

		int next_pos = -1;
		nextStackTop = -1;

		int pos = stateStackTop;
		tempStackTop = stateStackTop - 1;
		// System.arraycopy(stateStack, 0, tempStack, 0, stateStackTop + 1);
		System::arraycopy(stateStack, 0, tempStack, 0, stateStackTop + 1);

		int action_index = 0;
		act = action.get(action_index++); // tAction(act, current_kind);

		//
		// When a reduce action is encountered, we compute all REDUCE
		// and associated goto actions induced by the current token.
		// Eventually, a SHIFT, SHIFT-REDUCE, ACCEPT or ERROR action is
		// computed...
		//
		while (act <= NUM_RULES)
		{
			do
			{
				tempStackTop -= (rhs(act) - 1);
				act = ntAction(tempStack[tempStackTop], lhs(act));
			}
			while (act <= NUM_RULES);
			//
			// ... Update the maximum useful position of the
			// (STATE_)STACK, push goto state into stack, and
			// compute next action on current symbol ...
			//
			if (tempStackTop + 1 >= stateStack.Size())
				reallocateStacks();
			pos = pos < tempStackTop ? pos : tempStackTop;
			tempStack[tempStackTop + 1] = act;
			act = action.get(action_index++); // tAction(act, current_kind);
		}

		//
		// At this point, we have a shift, shift-reduce, accept or error
		// action.  STACK contains the configuration of the state stack
		// prior to executing any action on current_token. next_stack contains
		// the configuration of the state stack after executing all
		// reduce actions induced by current_token.  The variable pos indicates
		// the highest position in STACK that is still useful after the
		// reductions are executed.
		//
		while (act > ERROR_ACTION || act < ACCEPT_ACTION) // SHIFT-REDUCE action or SHIFT action ?
		{
			//
			// if the parser needs to stop processing,
			// it may do so here.
			//
			if (monitor != nullptr && monitor->isCancelled())
				return;

			nextStackTop = tempStackTop + 1;
			for (int i = next_pos + 1; i <= nextStackTop; i++)
				nextStack[i] = tempStack[i];

			for (int k = pos + 1; k <= nextStackTop; k++)
				locationStack[k] = locationStack[stateStackTop];

			//
			// If we have a shift-reduce, process it as well as
			// the goto-reduce actions that follow it.
			//
			if (act > ERROR_ACTION)
			{
				act -= ERROR_ACTION;
				do
				{
					nextStackTop -= (rhs(act) - 1);
					act = ntAction(nextStack[nextStackTop], lhs(act));
				}
				while (act <= NUM_RULES);
				pos = pos < nextStackTop ? pos : nextStackTop;
			}

			if (nextStackTop + 1 >= stateStack.Size())
				reallocateStacks();

			tempStackTop = nextStackTop;
			nextStack[++nextStackTop] = act;
			next_pos = nextStackTop;

			//
			// Simulate the parser through the next token without
			// destroying STACK or next_stack.
			//
			current_token = tokStream->getToken();
			current_kind = tokStream->getKind(current_token);
			act = action.get(action_index++); // tAction(act, current_kind);
			while (act <= NUM_RULES)
			{
				//
				// ... Process all goto-reduce actions following
				// reduction, until a goto action is computed ...
				//
				do
				{
					int lhs_symbol = lhs(act);
					tempStackTop -= (rhs(act) - 1);
					act = (tempStackTop > next_pos
						       ? tempStack[tempStackTop]
						       : nextStack[tempStackTop]);
					act = ntAction(act, lhs_symbol);
				}
				while (act <= NUM_RULES);

				//
				// ... Update the maximum useful position of the
				// (STATE_)STACK, push GOTO state into stack, and
				// compute next action on current symbol ...
				//
				if (tempStackTop + 1 >= stateStack.Size())
					reallocateStacks();

				next_pos = next_pos < tempStackTop ? next_pos : tempStackTop;
				tempStack[tempStackTop + 1] = act;
				act = action.get(action_index++); // tAction(act, current_kind);
			}

			//
			// No error was detected, Read next token into
			// PREVTOK element, advance CURRENT_TOKEN pointer and
			// update stacks.
			//
			if (act != ERROR_ACTION)
			{
				prevStackTop = stateStackTop;
				for (int i = prev_pos + 1; i <= prevStackTop; i++)
					prevStack[i] = stateStack[i];
				prev_pos = pos;

				stateStackTop = nextStackTop;
				for (int k = pos + 1; k <= stateStackTop; k++)
					stateStack[k] = nextStack[k];
				locationStack[stateStackTop] = current_token;
				pos = next_pos;
			}
		}

		//
		// At this stage, either we have an ACCEPT or an ERROR
		// action.
		//
		if (act == ERROR_ACTION)
		{
			//
			// An error was detected.
			//
			errorCount += 1;

			//
			// Check time and error limits after the first error encountered
			// Exit if number of errors exceeds maxError or if maxTime reached
			//
			if (errorCount > 1)
			{
				if (maxErrors > 0 && errorCount > maxErrors) 
					break;
				std::chrono::milliseconds endTime = std::chrono::duration_cast<std::chrono::milliseconds>(
					std::chrono::system_clock::now().time_since_epoch()
					);
				
				if (maxTime > 0 && (endTime - startTime).count() > maxTime)
					break;
			}

			RepairCandidate candidate = errorRecovery(current_token);

			//
			// if the parser needs to stop processing,
			// it may do so here.
			//
			if (monitor != nullptr && monitor->isCancelled())
				return;

			act = stateStack[stateStackTop];

			//
			// If the recovery was successful on a nonterminal candidate,
			// parse through that candidate and "read" the next token.
			//
			if (candidate.symbol == 0)
				break;
			else if (candidate.symbol > NT_OFFSET)
			{
				int lhs_symbol = candidate.symbol - NT_OFFSET;
				act = ntAction(act, lhs_symbol);
				while (act <= NUM_RULES)
				{
					stateStackTop -= (rhs(act) - 1);
					act = ntAction(stateStack[stateStackTop], lhs(act));
				}
				stateStack[++stateStackTop] = act;
				current_token = tokStream->getToken();
				current_kind = tokStream->getKind(current_token);
				locationStack[stateStackTop] = current_token;
			}
			else
			{
				current_kind = candidate.symbol;
				locationStack[stateStackTop] = candidate.location;
			}

			//
			// At this stage, we have a recovery configuration-> See how
			// far we can go with it.
			//
			int next_token = tokStream->peek();
			
			tempStackTop = stateStackTop;
			//System.arraycopy(stateStack, 0, tempStack, 0, stateStackTop + 1);
			System::arraycopy(stateStack, 0, tempStack, 0, stateStackTop + 1);
			error_token = parseForError(current_kind);

			//
			// If an error was found, compute the sequence of actions that reaches
			// the error token. Otherwise, claim victory...
			//
			if (error_token != 0)
			{
				tokStream->reset(next_token);
				tempStackTop = stateStackTop;
				System::arraycopy(stateStack, 0, tempStack, 0, stateStackTop + 1);

				parseUpToError(action, current_kind, error_token);
				tokStream->reset(next_token);
			}
			else act = ACCEPT_ACTION;
		}
	}
	while (act != ACCEPT_ACTION);

	return;
}

int DiagnoseParser::parseForError(int current_kind)
{
	int error_token = 0;

	//
	// Get next token in stream and compute initial action
	//
	int curtok = tokStream->getPrevious(tokStream->peek()),
	    act = tAction(tempStack[tempStackTop], current_kind);

	//
	// Allocate configuration stack.
	//
	ConfigurationStack configuration_stack(this);

	//
	// Keep parsing until we reach the end of file and succeed or
	// an error is encountered. The list of actions executed will
	// be store in the "action" tuple.
	//
	for (;;)
	{
		if (act <= NUM_RULES)
		{
			tempStackTop--;

			do
			{
				tempStackTop -= (rhs(act) - 1);
				act = ntAction(tempStack[tempStackTop], lhs(act));
			}
			while (act <= NUM_RULES);
		}
		else if (act > ERROR_ACTION)
		{
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
			act -= ERROR_ACTION;

			do
			{
				tempStackTop -= (rhs(act) - 1);
				act = ntAction(tempStack[tempStackTop], lhs(act));
			}
			while (act <= NUM_RULES);
		}
		else if (act < ACCEPT_ACTION)
		{
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
		}
		else if (act == ERROR_ACTION)
		{
			error_token = (error_token > curtok ? error_token : curtok);

			auto configuration = configuration_stack.pop();
			if (configuration == nullptr)
				act = ERROR_ACTION;
			else
			{
				tempStackTop = configuration->stack_top;
				configuration->retrieveStack(tempStack);
				act = configuration->act;
				curtok = configuration->curtok;
				// no need to execute: action.reset(configuration->action_length);
				current_kind = tokStream->getKind(curtok);
				tokStream->reset(tokStream->getNext(curtok));
				continue;
			}
			break;
		}
		else if (act > ACCEPT_ACTION)
		{
			if (configuration_stack.findConfiguration(tempStack, tempStackTop, curtok))
				act = ERROR_ACTION;
			else
			{
				configuration_stack.push(tempStack, tempStackTop, act + 1, curtok, 0);
				act = baseAction(act);
			}
			continue;
		}
		else break; // assert(act == ACCEPT_ACTION);


		if (++tempStackTop >= tempStack.Size())
		{
			reallocateStacks();
		}
		tempStack[tempStackTop] = act;
		act = tAction(act, current_kind);
	}

	return (act == ERROR_ACTION ? error_token : 0);
}

void DiagnoseParser::parseUpToError(IntTuple& action, int current_kind, int error_token)
{
	//
	// Assume predecessor of next token and compute initial action
	//
	int curtok = tokStream->getPrevious(tokStream->peek());
	int act = tAction(tempStack[tempStackTop], current_kind);

	//
	// Allocate configuration stack.
	//
	ConfigurationStack configuration_stack(this);

	//
	// Keep parsing until we reach the end of file and succeed or
	// an error is encountered. The list of actions executed will
	// be store in the "action" tuple.
	//
	action.reset();
	for (;;)
	{
		if (act <= NUM_RULES)
		{
			action.add(act); // save this reduce action
			tempStackTop--;

			do
			{
				tempStackTop -= (rhs(act) - 1);
				act = ntAction(tempStack[tempStackTop], lhs(act));
			}
			while (act <= NUM_RULES);
		}
		else if (act > ERROR_ACTION)
		{
			action.add(act); // save this shift-reduce action
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
			act -= ERROR_ACTION;

			do
			{
				tempStackTop -= (rhs(act) - 1);
				act = ntAction(tempStack[tempStackTop], lhs(act));
			}
			while (act <= NUM_RULES);
		}
		else if (act < ACCEPT_ACTION)
		{
			action.add(act); // save this shift action
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
		}
		else if (act == ERROR_ACTION)
		{
			if (curtok != error_token)
			{
				auto configuration = configuration_stack.pop();
				if (configuration == nullptr)
					act = ERROR_ACTION;
				else
				{
					tempStackTop = configuration->stack_top;
					configuration->retrieveStack(tempStack);
					act = configuration->act;
					curtok = configuration->curtok;
					action.reset(configuration->action_length);
					current_kind = tokStream->getKind(curtok);
					tokStream->reset(tokStream->getNext(curtok));
					continue;
				}
			}
			break;
		}
		else if (act > ACCEPT_ACTION)
		{
			if (configuration_stack.findConfiguration(tempStack, tempStackTop, curtok))
				act = ERROR_ACTION;
			else
			{
				configuration_stack.push(tempStack, tempStackTop, act + 1, curtok, action.size());
				act = baseAction(act);
			}
			continue;
		}
		else break; // assert(act == ACCEPT_ACTION);

		if(++tempStackTop >= tempStack.Size())
		{
			reallocateStacks();
		}
		tempStack[tempStackTop] = act;
		act = tAction(act, current_kind);
	}

	action.add(ERROR_ACTION);

	return;
}

int DiagnoseParser::parseCheck(Array<int>& stack, int stack_top, int first_symbol, int buffer_position)
{
	int buffer_index,
	    current_kind;

	Array<int> local_stack(stack.Size(),0);
	int local_stack_top = stack_top;
	for (int i = 0; i <= stack_top; i++)
		local_stack[i] = stack[i];

	ConfigurationStack configuration_stack(this);

	//
	// If the first symbol is a nonterminal, process it here.
	//
	int act = local_stack[local_stack_top];
	if (first_symbol > NT_OFFSET)
	{
		int lhs_symbol = first_symbol - NT_OFFSET;
		buffer_index = buffer_position;
		current_kind = tokStream->getKind(buffer[buffer_index]);
		tokStream->reset(tokStream->getNext(buffer[buffer_index]));
		act = ntAction(act, lhs_symbol);
		while (act <= NUM_RULES)
		{
			local_stack_top -= (rhs(act) - 1);
			act = ntAction(local_stack[local_stack_top], lhs(act));
		}
	}
	else
	{
		local_stack_top--;
		buffer_index = buffer_position - 1;
		current_kind = first_symbol;
		tokStream->reset(buffer[buffer_position]);
	}

	//
	// Start parsing the remaining symbols in the buffer
	//
	if (++local_stack_top >= local_stack.Size()) // Stack overflow!!!
		return buffer_index;
	local_stack[local_stack_top] = act;

	act = tAction(act, current_kind);

	for (;;)
	{
		if (act <= NUM_RULES) // reduce action
		{
			local_stack_top -= rhs(act);
			act = ntAction(local_stack[local_stack_top], lhs(act));

			while (act <= NUM_RULES)
			{
				local_stack_top -= (rhs(act) - 1);
				act = ntAction(local_stack[local_stack_top], lhs(act));
			}
		}
		else if (act > ERROR_ACTION) // shift-reduce action
		{
			if (buffer_index++ == MAX_DISTANCE)
				break;
			current_kind = tokStream->getKind(buffer[buffer_index]);
			tokStream->reset(tokStream->getNext(buffer[buffer_index]));
			act -= ERROR_ACTION;

			do
			{
				local_stack_top -= (rhs(act) - 1);
				act = ntAction(local_stack[local_stack_top], lhs(act));
			}
			while (act <= NUM_RULES);
		}
		else if (act < ACCEPT_ACTION) // shift action
		{
			if (buffer_index++ == MAX_DISTANCE)
				break;
			current_kind = tokStream->getKind(buffer[buffer_index]);
			tokStream->reset(tokStream->getNext(buffer[buffer_index]));
		}
		else if (act == ERROR_ACTION)
		{
			auto configuration = configuration_stack.pop();
			if (configuration == nullptr)
				act = ERROR_ACTION;
			else
			{
				local_stack_top = configuration->stack_top;
				configuration->retrieveStack(local_stack);
				act = configuration->act;
				buffer_index = configuration->curtok;
				// no need to execute: action.reset(configuration->action_length);
				current_kind = tokStream->getKind(buffer[buffer_index]);
				tokStream->reset(tokStream->getNext(buffer[buffer_index]));
				continue;
			}
			break;
		}
		else if (act > ACCEPT_ACTION)
		{
			if (configuration_stack.findConfiguration(local_stack, local_stack_top, buffer_index))
				act = ERROR_ACTION;
			else
			{
				configuration_stack.push(local_stack, local_stack_top, act + 1, buffer_index, 0);
				act = baseAction(act);
			}
			continue;
		}
		else break;

		if (++local_stack_top >= local_stack.Size()) // Stack overflow!!!
			break;
		local_stack[local_stack_top] = act;

		act = tAction(act, current_kind);
	}

	return (act == ACCEPT_ACTION ? INFINITY_ : buffer_index);
}

DiagnoseParser::RepairCandidate DiagnoseParser::errorRecovery(int error_token)
{
	if(error_token == 5410)
	{
		error_token = 5410;
	}
	int prevtok = tokStream->getPrevious(error_token);

	//
	// Try primary phase recoveries. If not successful, try secondary
	// phase recoveries.  If not successful and we are at end of the
	// file, we issue the end-of-file error and quit. Otherwise, ...
	//
	RepairCandidate candidate = primaryPhase(error_token);
	if (candidate.symbol != 0)
		return candidate;

	candidate = secondaryPhase(error_token);
	if (candidate.symbol != 0)
		return candidate;

	//
	// At this point, primary and (initial attempt at) secondary
	// recovery did not work.  We will now get into "panic mode" and
	// keep trying secondary phase recoveries until we either find
	// a successful recovery or have consumed the remaining input
	// tokens.
	//
	if (tokStream->getKind(error_token) != EOFT_SYMBOL)
	{
		while (tokStream->getKind(buffer[BUFF_UBOUND]) != EOFT_SYMBOL)
		{
			candidate = secondaryPhase(buffer[MAX_DISTANCE - MIN_DISTANCE + 2]);
			if (candidate.symbol != 0)
				return candidate;
		}
	}

	//
	// If no successful recovery is found and we have reached the
	// end of the file, check whether or not any scope recovery is
	// applicable at the end of the file after discarding some
	// states.
	//
	PrimaryRepairInfo scope_repair;
	scope_repair.bufferPosition = BUFF_UBOUND;
	for (int top = stateStackTop; top >= 0; top--)
	{
		scopeTrial(scope_repair, stateStack, top);

		if (scope_repair.distance > 0)
			break;
	}

	//
	// If any scope repair was successful, emit the message now
	//
	for (int i = 0; i < scopeStackTop; i++)
	{
		emitError(SCOPE_CODE,
		          -scopeIndex[i],
		          locationStack[scopePosition[i]],
		          buffer[1],
		          nonterminalIndex(scopeLhs(scopeIndex[i])));
	}

	//
	// If the original error_token was already pointing to the EOF, issue the EOF-reached message.
	//
	if (tokStream->getKind(error_token) == EOFT_SYMBOL)
	{
		emitError(EOF_CODE,
		          terminalIndex(EOFT_SYMBOL),
		          prevtok,
		          prevtok);
	}
	else
	{
		//
		// We reached the end of the file while panicking. Delete all
		// remaining tokens in the input.
		//
		int i;
		for (i = BUFF_UBOUND; tokStream->getKind(buffer[i]) == EOFT_SYMBOL; i--);

		emitError(DELETION_CODE,
		          terminalIndex(tokStream->getKind(error_token)),
		          error_token,
		          buffer[i]);
	}

	//
	// Create the "failed" candidate and return it.
	//
	candidate.symbol = 0;
	candidate.location = buffer[BUFF_UBOUND]; // point to EOF

	return candidate;
}
DiagnoseParser::RepairCandidate DiagnoseParser::primaryPhase(int error_token)
{
	//
	// Initialize the buffer.
	//
	int i = (nextStackTop >= 0 ? 3 : 2);
	buffer[i] = error_token;

	for (int j = i; j > 0; j--)
		buffer[j - 1] = tokStream->getPrevious(buffer[j]);

	for (int k = i + 1; k < BUFF_SIZE; k++)
		buffer[k] = tokStream->getNext(buffer[k - 1]);

	//
	// If NEXT_STACK_TOP > 0 then the parse was successful on CURRENT_TOKEN
	// and the error was detected on the successor of CURRENT_TOKEN. In
	// that case, first check whether or not primary recovery is
	// possible on next_stack ...
	//
	PrimaryRepairInfo repair;
	if (nextStackTop >= 0)
	{
		repair.bufferPosition = 3;
		checkPrimaryDistance(repair, nextStack, nextStackTop);
	}

	//
	// ... Try primary recovery on the current token and compare
	// the quality of this recovery to the one on the next token...
	//
	PrimaryRepairInfo base_repair(repair);
	base_repair.bufferPosition = 2;
	checkPrimaryDistance(base_repair, stateStack, stateStackTop);
	if (base_repair.distance > repair.distance || base_repair.misspellIndex > repair.misspellIndex)
		repair = base_repair;

	//
	// Finally, if prev_stack_top >= 0 try primary recovery on
	// the prev_stack configuration and compare it to the best
	// recovery computed thus far.
	//
	if (prevStackTop >= 0)
	{
		PrimaryRepairInfo prev_repair;
		prev_repair.bufferPosition = 1;
		checkPrimaryDistance(prev_repair, prevStack, prevStackTop);
		if (prev_repair.distance > repair.distance || prev_repair.misspellIndex > repair.misspellIndex)
			repair = prev_repair;
	}

	//
	// Before accepting the best primary phase recovery obtained,
	// ensure that we cannot do better with a similar secondary
	// phase recovery.
	//
	RepairCandidate candidate;
	if (nextStackTop >= 0) // next_stack available
	{
		if (secondaryCheck(nextStack, nextStackTop, 3, repair))
			return candidate;
	}
	else if (secondaryCheck(stateStack, stateStackTop, 2, repair))
		return candidate;

	//
	// First, adjust distance if the recovery is on the error token;
	// it is important that the adjustment be made here and not at
	// each primary trial to prevent the distance tests from being
	// biased in favor of deferred recoveries which have access to
	// more input tokens...
	//
	repair.distance = repair.distance - repair.bufferPosition + 1;

	//
	// ...Next, adjust the distance if the recovery is a deletion or
	// (some form of) substitution...
	//
	if (repair.code == INVALID_CODE ||
		repair.code == DELETION_CODE ||
		repair.code == SUBSTITUTION_CODE ||
		repair.code == MERGE_CODE)
		repair.distance--;

	//
	// ... After adjustment, check if the most successful primary
	// recovery can be applied.  If not, continue with more radical
	// recoveries...
	//
	if (repair.distance < MIN_DISTANCE)
		return candidate;

	//
	// When processing an insertion error, if the token preceeding
	// the error token is not available, we change the repair code
	// into a BEFORE_CODE to instruct the reporting routine that it
	// indicates that the repair symbol should be inserted before
	// the error token.
	//
	if (repair.code == INSERTION_CODE)
	{
		if (tokStream->getKind(buffer[repair.bufferPosition - 1]) == 0)
			repair.code = BEFORE_CODE;
	}

	//
	// Select the proper sequence of states on which to recover,
	// update stack accordingly and call diagnostic routine.
	//
	if (repair.bufferPosition == 1)
	{
		stateStackTop = prevStackTop;
		//System.arraycopy(prevStack, 0, stateStack, 0, stateStackTop + 1);
		System::arraycopy(prevStack, 0, stateStack, 0, stateStackTop + 1);
	}
	else if (nextStackTop >= 0 && repair.bufferPosition >= 3)
	{
		stateStackTop = nextStackTop;
		//System.arraycopy(nextStack, 0, stateStack, 0, stateStackTop + 1);
		System::arraycopy(nextStack, 0, stateStack, 0, stateStackTop + 1);

		locationStack[stateStackTop] = buffer[3];
	}

	return primaryDiagnosis(repair);
}


int DiagnoseParser::mergeCandidate(int state, int buffer_position)
{
	std::wstringex str = tokStream->getName(buffer[buffer_position]) + tokStream->getName(buffer[buffer_position + 1]);
	for (int k = asi(state); asr(k) != 0; k++)
	{
		int i = terminalIndex(asr(k));
		if (str.length() == name(i).length())
		{
			if (str.compare_nocase(name(i)))
				return asr(k);
		}
	}

	return 0;
}
void DiagnoseParser::checkPrimaryDistance(PrimaryRepairInfo& repair, Array<int>& stck, int stack_top)
{
	//
	//  First, try scope recovery.
	//
	PrimaryRepairInfo scope_repair(repair);
	scopeTrial(scope_repair, stck, stack_top);
	if (scope_repair.distance > repair.distance)
		repair.copy(scope_repair);

	//
	//  Next, try merging the error token with its successor.
	//
	int symbol = mergeCandidate(stck[stack_top], repair.bufferPosition);
	if (symbol != 0)
	{
		int j = parseCheck(stck, stack_top, symbol, repair.bufferPosition + 2);
		if ((j > repair.distance) || (j == repair.distance && repair.misspellIndex < 10))
		{
			repair.misspellIndex = 10;
			repair.symbol = symbol;
			repair.distance = j;
			repair.code = MERGE_CODE;
		}
	}

	//
	// Next, try deletion of the error token.
	//
	int j = parseCheck(stck,
		stack_top,
		tokStream->getKind(buffer[repair.bufferPosition + 1]),
		repair.bufferPosition + 2);
	int k = (tokStream->getKind(buffer[repair.bufferPosition]) == EOLT_SYMBOL &&
		tokStream->afterEol(buffer[repair.bufferPosition + 1])
		? 10
		: 0);
	if (j > repair.distance || (j == repair.distance && k > repair.misspellIndex))
	{
		repair.misspellIndex = k;
		repair.code = DELETION_CODE;
		repair.distance = j;
	}

	//
	// Update the error configuration by simulating all reduce and
	// goto actions induced by the error token. Then assign the top
	// most state of the new configuration to next_state.
	//
	int next_state = stck[stack_top],
		max_pos = stack_top;
	tempStackTop = stack_top - 1;

	tokStream->reset(buffer[repair.bufferPosition + 1]);
	int tok = tokStream->getKind(buffer[repair.bufferPosition]),
		act = tAction(next_state, tok);
	while (act <= NUM_RULES)
	{
		do
		{
			int lhs_symbol = lhs(act);
			tempStackTop -= (rhs(act) - 1);
			act = (tempStackTop > max_pos
				? tempStack[tempStackTop]
				: stck[tempStackTop]);
			act = ntAction(act, lhs_symbol);
		}while (act <= NUM_RULES);
		max_pos = max_pos < tempStackTop ? max_pos : tempStackTop;
		tempStack[tempStackTop + 1] = act;
		next_state = act;
		act = tAction(next_state, tok);
	}

	//
	//  Next, place the list of candidates in proper order.
	//
	int root = 0;
	for (int i = asi(next_state); asr(i) != 0; i++)
	{
		symbol = asr(i);
		if (symbol != EOFT_SYMBOL && symbol != ERROR_SYMBOL)
		{
			if (root == 0)
				list[symbol] = symbol;
			else
			{
				list[symbol] = list[root];
				list[root] = symbol;
			}
			root = symbol;
		}
	}

	if (stck[stack_top] != next_state)
	{
		for (int i = asi(stck[stack_top]); asr(i) != 0; i++)
		{
			symbol = asr(i);
			if (symbol != EOFT_SYMBOL && symbol != ERROR_SYMBOL && list[symbol] == 0)
			{
				if (root == 0)
					list[symbol] = symbol;
				else
				{
					list[symbol] = list[root];
					list[root] = symbol;
				}
				root = symbol;
			}
		}
	}

	int head = list[root];
	list[root] = 0;
	root = head;

	//
	//  Next, try insertion for each possible candidate available in
	// the current state, except EOFT and ERROR_SYMBOL.
	//
	symbol = root;
	while (symbol != 0)
	{
		int m = parseCheck(stck, stack_top, symbol, repair.bufferPosition),
			n = (symbol == EOLT_SYMBOL && tokStream->afterEol(buffer[repair.bufferPosition])
				? 10
				: 0);
		if (m > repair.distance ||
			(m == repair.distance && n > repair.misspellIndex))
		{
			repair.misspellIndex = n;
			repair.distance = m;
			repair.symbol = symbol;
			repair.code = INSERTION_CODE;
		}

		symbol = list[symbol];
	}

	//
	//  Next, Try substitution for each possible candidate available
	// in the current state, except EOFT and ERROR_SYMBOL.
	//
	symbol = root;
	while (symbol != 0)
	{
		int m = parseCheck(stck, stack_top, symbol, repair.bufferPosition + 1),
			n = (symbol == EOLT_SYMBOL && tokStream->afterEol(buffer[repair.bufferPosition + 1])
				? 10
				: misspell(symbol, buffer[repair.bufferPosition]));
		if (m > repair.distance ||
			(m == repair.distance && n > repair.misspellIndex))
		{
			repair.misspellIndex = n;
			repair.distance = m;
			repair.symbol = symbol;
			repair.code = SUBSTITUTION_CODE;
		}

		int s = symbol;
		symbol = list[symbol];
		list[s] = 0; // reset element
	}


	//
	// Next, we try to insert a nonterminal candidate in front of the
	// error token, or substituting a nonterminal candidate for the
	// error token. Precedence is given to insertion.
	//
	int nt_index = nasi(stck[stack_top]);
	for (; nasr(nt_index) != 0; nt_index++)
	{
		symbol = nasr(nt_index) + NT_OFFSET;
		int n = parseCheck(stck, stack_top, symbol, repair.bufferPosition + 1);
		if (n > repair.distance)
		{
			repair.misspellIndex = 0;
			repair.distance = n;
			repair.symbol = symbol;
			repair.code = INVALID_CODE;
		}

		n = parseCheck(stck, stack_top, symbol, repair.bufferPosition);
		if (n > repair.distance || (n == repair.distance && repair.code == INVALID_CODE))
		{
			repair.misspellIndex = 0;
			repair.distance = n;
			repair.symbol = symbol;
			repair.code = INSERTION_CODE;
		}
	}

	return;
}

DiagnoseParser::RepairCandidate DiagnoseParser::primaryDiagnosis(PrimaryRepairInfo& repair)
{
	//
	//  Issue diagnostic.
	//
	int prevtok = buffer[repair.bufferPosition - 1],
		current_token = buffer[repair.bufferPosition];

	switch (repair.code)
	{
	case INSERTION_CODE:
	case BEFORE_CODE:
	{
		int name_index = (repair.symbol > NT_OFFSET
			? getNtermIndex(stateStack[stateStackTop],
				repair.symbol,
				repair.bufferPosition)
			: getTermIndex(stateStack,
				stateStackTop,
				repair.symbol,
				repair.bufferPosition));
		int tok = (repair.code == INSERTION_CODE ? prevtok : current_token);
		emitError(repair.code, name_index, tok, tok);
		break;
	}
	case INVALID_CODE:
	{
		int name_index = getNtermIndex(stateStack[stateStackTop],
			repair.symbol,
			repair.bufferPosition + 1);
		emitError(repair.code, name_index, current_token, current_token);
		break;
	}
	case SUBSTITUTION_CODE:
	{
		int name_index;
		if (repair.misspellIndex >= 6)
			name_index = terminalIndex(repair.symbol);
		else
		{
			name_index = getTermIndex(stateStack, stateStackTop,
				repair.symbol,
				repair.bufferPosition + 1);
			if (name_index != terminalIndex(repair.symbol))
				repair.code = INVALID_CODE;
		}
		emitError(repair.code, name_index, current_token, current_token);
		break;
	}
	case MERGE_CODE:
		emitError(repair.code,
			terminalIndex(repair.symbol),
			current_token,
			tokStream->getNext(current_token));
		break;
	case SCOPE_CODE:
	{
		for (int i = 0; i < scopeStackTop; i++)
		{
			emitError(repair.code,
				-scopeIndex[i],
				locationStack[scopePosition[i]],
				prevtok,
				nonterminalIndex(scopeLhs(scopeIndex[i])));
		}

		repair.symbol = scopeLhs(scopeIndex[scopeStackTop]) + NT_OFFSET;
		stateStackTop = scopePosition[scopeStackTop];
		emitError(repair.code,
			-scopeIndex[scopeStackTop],
			locationStack[scopePosition[scopeStackTop]],
			prevtok,
			getNtermIndex(stateStack[stateStackTop],
				repair.symbol,
				repair.bufferPosition)
		);
		break;
	}
	default: // deletion
		emitError(repair.code, terminalIndex(ERROR_SYMBOL), current_token, current_token);
	}

	//
	//  Update buffer.
	//
	RepairCandidate candidate;
	switch (repair.code)
	{
	case SCOPE_CODE:
		//
		// If a scope repair is to be applied at the end of the input, accept it as valid
		// repair only if after applying it the parser will accept the input. 
		//
		candidate.symbol = (tokStream->getKind(buffer[repair.bufferPosition]) != EOFT_SYMBOL ||
			repair.distance >= MAX_DISTANCE)
			? repair.symbol
			: 0;
		candidate.location = buffer[repair.bufferPosition];
		tokStream->reset(buffer[repair.bufferPosition]);
		break;
	case INSERTION_CODE:
	case BEFORE_CODE:
		candidate.symbol = repair.symbol;
		candidate.location = buffer[repair.bufferPosition];
		tokStream->reset(buffer[repair.bufferPosition]);
		break;
	case INVALID_CODE:
	case SUBSTITUTION_CODE:
		candidate.symbol = repair.symbol;
		candidate.location = buffer[repair.bufferPosition];
		tokStream->reset(buffer[repair.bufferPosition + 1]);
		break;
	case MERGE_CODE:
		candidate.symbol = repair.symbol;
		candidate.location = buffer[repair.bufferPosition];
		tokStream->reset(buffer[repair.bufferPosition + 2]);
		break;
	default: // deletion
		candidate.location = buffer[repair.bufferPosition + 1];
		candidate.symbol = tokStream->getKind(buffer[repair.bufferPosition + 1]);
		tokStream->reset(buffer[repair.bufferPosition + 2]);
		break;
	}

	return candidate;
}






int DiagnoseParser::getTermIndex(Array<int>& stck, int stack_top, int tok, int buffer_position)
{
	//
	// Initialize stack index of temp_stack and initialize maximum
	// position of state stack that is still useful.
	//
	int act = stck[stack_top],
	    max_pos = stack_top,
	    highest_symbol = tok;

	tempStackTop = stack_top - 1;

	//
	// Compute all reduce and associated actions induced by the
	// candidate until a SHIFT or SHIFT-REDUCE is computed. ERROR
	// and ACCEPT actions cannot be computed on the candidate in
	// this context, since we know that it is suitable for recovery.
	//
	tokStream->reset(buffer[buffer_position]);
	act = tAction(act, tok);
	while (act <= NUM_RULES)
	{
		//
		// Process all goto-reduce actions following reduction,
		// until a goto action is computed ...
		//
		do
		{
			int lhs_symbol = lhs(act);
			tempStackTop -= (rhs(act) - 1);
			act = (tempStackTop > max_pos
				       ? tempStack[tempStackTop]
				       : stck[tempStackTop]);
			act = ntAction(act, lhs_symbol);
		}
		while (act <= NUM_RULES);

		//
		// Compute new maximum useful position of (STATE_)stack,
		// push goto state into the stack, and compute next
		// action on candidate ...
		//
		max_pos = max_pos < tempStackTop ? max_pos : tempStackTop;
		tempStack[tempStackTop + 1] = act;
		act = tAction(act, tok);
	}

	//
	// At this stage, we have simulated all actions induced by the
	// candidate and we are ready to shift or shift-reduce it. First,
	// set tok and next_ptr appropriately and identify the candidate
	// as the initial highest_symbol. If a shift action was computed
	// on the candidate, update the stack and compute the next
	// action. Next, simulate all actions possible on the next input
	// token until we either have to shift it or are about to reduce
	// below the initial starting point in the stack (indicated by
	// max_pos as computed in the previous loop).  At that point,
	// return the highest_symbol computed.
	//
	tempStackTop++; // adjust top of stack to reflect last goto
	// next move is shift or shift-reduce.
	int threshold = tempStackTop;

	tok = tokStream->getKind(buffer[buffer_position]);
	tokStream->reset(buffer[buffer_position + 1]);

	if (act > ERROR_ACTION) // shift-reduce on candidate?
		act -= ERROR_ACTION;
	else if (act < ACCEPT_ACTION) // shift on candidate
	{
		tempStack[tempStackTop + 1] = act;
		act = tAction(act, tok);
	}

	while (act <= NUM_RULES)
	{
		//
		// Process all goto-reduce actions following reduction,
		// until a goto action is computed ...
		//
		do
		{
			int lhs_symbol = lhs(act);
			tempStackTop -= (rhs(act) - 1);

			if (tempStackTop < threshold)
				return (highest_symbol > NT_OFFSET
					        ? nonterminalIndex(highest_symbol - NT_OFFSET)
					        : terminalIndex(highest_symbol));

			if (tempStackTop == threshold)
				highest_symbol = lhs_symbol + NT_OFFSET;
			act = (tempStackTop > max_pos
				       ? tempStack[tempStackTop]
				       : stck[tempStackTop]);
			act = ntAction(act, lhs_symbol);
		}
		while (act <= NUM_RULES);

		tempStack[tempStackTop + 1] = act;
		act = tAction(act, tok);
	}

	return (highest_symbol > NT_OFFSET
		        ? nonterminalIndex(highest_symbol - NT_OFFSET)
		        : terminalIndex(highest_symbol));
}

int DiagnoseParser::getNtermIndex(int start, int sym, int buffer_position)
{
	//
	// This code was initially written to handle deterministic grammars. To extend it to handle
	// ambiguous grammars we need to keep track of rules that have been visited.
	//
	std::vector<bool>  rule_seen(NUM_RULES + 1,false);
	int highest_symbol = sym - NT_OFFSET,
	    tok = tokStream->getKind(buffer[buffer_position]);
	tokStream->reset(buffer[buffer_position + 1]);

	//
	// Initialize stack index of temp_stack and initialize maximum
	// position of state stack that is still useful.
	//
	tempStackTop = 0;
	tempStack[tempStackTop] = start;

	int act = ntAction(start, highest_symbol);
	if (act > NUM_RULES) // goto action?
	{
		tempStack[tempStackTop + 1] = act;
		act = tAction(act, tok);
	}

	while (act <= NUM_RULES)
	{
		if (rule_seen[act]) // if we've already seen this rule don't revisit it.
			break;

		rule_seen[act] = true; // indicate that we've seeen this rule already.

		//
		// Process all goto-reduce actions following reduction,
		// until a goto action is computed ...
		//
		do
		{
			tempStackTop -= (rhs(act) - 1);
			if (tempStackTop < 0)
				return nonterminalIndex(highest_symbol);
			if (tempStackTop == 0)
				highest_symbol = lhs(act);
			act = ntAction(tempStack[tempStackTop], lhs(act));
		}
		while (act <= NUM_RULES);
		tempStack[tempStackTop + 1] = act;
		act = tAction(act, tok);
	}

	return nonterminalIndex(highest_symbol);
}

int DiagnoseParser::misspell(int sym, int tok)
{
	//
	// Set up the two strings in question. Note that there is a "0"
	// gate added at the end of each string. This is important as
	// the algorithm assumes that it can "peek" at the symbol immediately
	// following the one that is being analysed.
	//
	std::wstringex s1 = (std::wstringex(name(terminalIndex(sym)))).tolower();
	int n = s1.length();
	s1.push_back(0);

	std::wstringex s2 = ( std::wstringex(tokStream->getName(tok))).tolower();
	int m = (s2.length() < MAX_NAME_LENGTH ? s2.length() : MAX_NAME_LENGTH);
	s2 = s2.substr(0, m);
	s2.push_back(0);

	//
	//  Singleton misspellings:
	//
	//  ;      <---->     ,
	//
	//  ;      <---->     :
	//
	//  .      <---->     ,
	//
	//  '      <---->     "
	//
	//
	if (n == 1 && m == 1)
	{
		if ((s1[0] == ';' && s2[0] == ',') ||
			(s1[0] == ',' && s2[0] == ';') ||
			(s1[0] == ';' && s2[0] == ':') ||
			(s1[0] == ':' && s2[0] == ';') ||
			(s1[0] == '.' && s2[0] == ',') ||
			(s1[0] == ',' && s2[0] == '.') ||
			(s1[0] == '\'' && s2[0] == '\"') ||
			(s1[0] == '\"' && s2[0] == '\''))
		{
			return 3;
		}
	}

	//
	// Scan the two strings. Increment "match" count for each match.
	// When a transposition is encountered, increase "match" count
	// by two but count it as one error. When a typo is found, skip
	// it and count it as one error. Otherwise we have a mismatch; if
	// one of the strings is longer, increment its index, otherwise,
	// increment both indices and continue.
	//
	// This algorithm is an adaptation of a bool misspelling
	// algorithm proposed by Juergen Uhl.
	//
	int count = 0,
	    prefix_length = 0,
	    num_errors = 0;

	int i = 0;
	int j = 0;
	while ((i < n) && (j < m))
	{
		if (s1[i] == s2[j])
		{
			count++;
			i++;
			j++;
			if (num_errors == 0)
				prefix_length++;
		}
		else if (s1[i + 1] == s2[j] && s1[i] == s2[j + 1])
		{
			count += 2;
			i += 2;
			j += 2;
			num_errors++;
		}
		else if (s1[i + 1] == s2[j + 1])// mismatch
		{
			i++;
			j++;
			num_errors++;
		}
		else
		{
			if ((n - i) > (m - j))
				i++;
			else if ((m - j) > (n - i))
				j++;
			else
			{
				i++;
				j++;
			}
			num_errors++;
		}
	}


	if (i < n || j < m)
		num_errors++;

	if (num_errors > ((n < m ? n : m) / 6 + 1))
		count = prefix_length;

	return (count * 10 / ((n < s1.length() ? s1.length() : n) + num_errors));
}

void DiagnoseParser::scopeTrial(PrimaryRepairInfo& repair, Array<int>& stack, int stack_top)
{
	stateSeen.Resize(stateStack.Size());
	stateSeen.Initialize(NIL);
	statePool.reset();
	scopeTrialCheck(repair, stack, stack_top, 0);

	repair.code = SCOPE_CODE;
	repair.misspellIndex = 10;

	return;
}

void DiagnoseParser::scopeTrialCheck(PrimaryRepairInfo& repair, Array<int>& stack, int stack_top, int indx)
{
	for (int i = stateSeen[stack_top]; i != NIL; i = statePool[i].next)
	{
		if (statePool[i].state == stack[stack_top])
			return;
	}

	int old_state_pool_top = statePoolTop++;
	if (statePoolTop >= statePool.size())
	{
		statePool.Resize(statePoolTop * 2);
	}

	statePool[old_state_pool_top] =  StateInfo(stack[stack_top], stateSeen[stack_top]);
	stateSeen[stack_top] = old_state_pool_top;

	IntTuple action(1 << 3);
	for (int i = 0; i < SCOPE_SIZE; i++)
	{
		//
		// Compute the action (or set of actions in case of conflicts) that
		// can be executed on the scope lookahead symbol. Save the action(s)
		// in the action tuple.
		//
		action.reset();
		int act = tAction(stack[stack_top], scopeLa(i));
		if (act > ACCEPT_ACTION && act < ERROR_ACTION) // conflicting actions?
		{
			do
			{
				action.add(baseAction(act++));
			}
			while (baseAction(act) != 0);
		}
		else action.add(act);

		//
		// For each action defined on the scope lookahead symbol,
		// try scope recovery.
		//
		for (int action_index = 0; action_index < action.size(); action_index++)
		{
			tokStream->reset(buffer[repair.bufferPosition]);
			tempStackTop = stack_top - 1;
			int max_pos = stack_top;

			act = action.get(action_index);
			while (act <= NUM_RULES)
			{
				//
				// ... Process all goto-reduce actions following
				// reduction, until a goto action is computed ...
				//
				do
				{
					int lhs_symbol = lhs(act);
					tempStackTop -= (rhs(act) - 1);
					act = (tempStackTop > max_pos
						       ? tempStack[tempStackTop]
						       : stack[tempStackTop]);
					act = ntAction(act, lhs_symbol);
				}
				while (act <= NUM_RULES);
				if (tempStackTop + 1 >= stateStack.Size())
					return;
				max_pos = max_pos < tempStackTop ? max_pos : tempStackTop;
				tempStack[tempStackTop + 1] = act;
				act = tAction(act, scopeLa(i));
			}

			//
			// If the lookahead symbol is parsable, then we check
			// whether or not we have a match between the scope
			// prefix and the transition symbols corresponding to
			// the states on top of the stack.
			//
			if (act != ERROR_ACTION)
			{
				int j,
				    k = scopePrefix(i);
				for (j = tempStackTop + 1;
				     j >= (max_pos + 1) &&
				     inSymbol(tempStack[j]) == scopeRhs(k); j--)
					k++;

				if (j == max_pos)
				{
					for (j = max_pos;
					     j >= 1 && inSymbol(stack[j]) == scopeRhs(k);
					     j--)
						k++;
				}
				//
				// If the prefix matches, check whether the state
				// newly exposed on top of the stack, (after the
				// corresponding prefix states are popped from the
				// stack), is in the set of "source states" for the
				// scope in question and that it is at a position
				// below the threshold indicated by MARKED_POS.
				//
				int marked_pos = (max_pos < stack_top ? max_pos + 1 : stack_top);
				if (scopeRhs(k) == 0 && j < marked_pos) // match?
				{
					int stack_position = j;
					for (j = scopeStateSet(i);
					     stack[stack_position] != scopeState(j) &&
					     scopeState(j) != 0;
					     j++);
					//
					// If the top state is valid for scope recovery,
					// the left-hand side of the scope is used as
					// starting symbol and we calculate how far the
					// parser can advance within the forward context
					// after parsing the left-hand symbol.
					//
					if (scopeState(j) != 0) // state was found
					{
						int previous_distance = repair.distance,
						    distance = parseCheck(stack,
						                          stack_position,
						                          scopeLhs(i) + NT_OFFSET,
						                          repair.bufferPosition);
						//
						// if the recovery is not successful, we
						// update the stack with all actions induced
						// by the left-hand symbol, and recursively
						// call SCOPE_TRIAL_CHECK to try again.
						// Otherwise, the recovery is successful. If
						// the new distance is greater than the
						// initial SCOPE_DISTANCE, we update
						// SCOPE_DISTANCE and set scope_stack_top to INDX
						// to indicate the number of scopes that are
						// to be applied for a succesful  recovery.
						// NOTE that this procedure cannot get into
						// an infinite loop, since each prefix match
						// is guaranteed to take us to a lower point
						// within the stack.
						//
						if ((distance - repair.bufferPosition + 1) < MIN_DISTANCE)
						{
							int top = stack_position;
							act = ntAction(stack[top], scopeLhs(i));
							while (act <= NUM_RULES)
							{
								top -= (rhs(act) - 1);
								act = ntAction(stack[top], lhs(act));
							}
							top++;

							j = act;
							act = stack[top]; // save
							stack[top] = j; // swap
							scopeTrialCheck(repair, stack, top, indx + 1);
							stack[top] = act; // restore
						}
						else if (distance > repair.distance)
						{
							scopeStackTop = indx;
							repair.distance = distance;
						}

						//
						// If no other recovery possibility is left (due to
						// backtracking and we are at the end of the input,
						// then we favor a scope recovery over all other kinds
						// of recovery unless the other recovery led to an
						// acceptance of the input
						//
						if ( // TODO: main_configuration_stack.size() == 0 && // no other bactracking possibilities left
							tokStream->getKind(buffer[repair.bufferPosition]) == EOFT_SYMBOL &&
							repair.code != SCOPE_CODE && // previous recovery was not a scope recovery
							repair.distance < MAX_DISTANCE && // previous recovery was not perfect!
							repair.distance == previous_distance)
						{
							scopeStackTop = indx;
							repair.distance = MAX_DISTANCE;
						}

						//
						// If this scope recovery has beaten the
						// previous distance, then we have found a
						// better recovery (or this recovery is one
						// of a list of scope recoveries). Record
						// its information at the proper location
						// (INDX) in SCOPE_INDEX and SCOPE_STACK.
						//
						if (repair.distance > previous_distance)
						{
							scopeIndex[indx] = i;
							scopePosition[indx] = stack_position;
							return;
						}
					}
				}
			}
		}
	}
}

bool DiagnoseParser::secondaryCheck(Array<int>& stack, int stack_top, int buffer_position,
                                    PrimaryRepairInfo& repair)
{
	for (int top = stack_top - 1; top >= 0; top--)
	{
		int j = parseCheck(stack,
		                   top,
		                   tokStream->getKind(buffer[buffer_position]),
		                   buffer_position + 1);
		if (((j - buffer_position + 1) > MIN_DISTANCE) && (j > repair.distance))
			return true;
	}

	PrimaryRepairInfo scope_repair;
	scope_repair.bufferPosition = buffer_position + 1;
	scope_repair.code = repair.code;
	scope_repair.distance = repair.distance; // distance to beat
	scopeTrial(scope_repair, stack, stack_top);

	return ((scope_repair.distance - buffer_position) > MIN_DISTANCE && scope_repair.distance > repair.distance);
}

DiagnoseParser::RepairCandidate DiagnoseParser::secondaryPhase(int error_token)
{
	SecondaryRepairInfo repair, misplaced_repair;


	//
	// If the next_stack is available, try misplaced and secondary
	// recovery on it first.
	//
	int next_last_index = 0;
	if (nextStackTop >= 0)
	{
		int save_location;

		buffer[2] = error_token;
		buffer[1] = tokStream->getPrevious(buffer[2]);
		buffer[0] = tokStream->getPrevious(buffer[1]);

		for (int k = 3; k < BUFF_UBOUND; k++)
			buffer[k] = tokStream->getNext(buffer[k - 1]);

		buffer[BUFF_UBOUND] = tokStream->badToken(); // elmt not available

		//
		// If we are at the end of the input stream, compute the
		// index position of the first EOFT symbol (last useful
		// index).
		//
		for (next_last_index = MAX_DISTANCE - 1;
			next_last_index >= 1 &&
			tokStream->getKind(buffer[next_last_index]) == EOFT_SYMBOL;
			next_last_index--);
		next_last_index = next_last_index + 1;

		save_location = locationStack[nextStackTop];
		locationStack[nextStackTop] = buffer[2];
		misplaced_repair.numDeletions = nextStackTop;
		misplacementRecovery(misplaced_repair, nextStack, nextStackTop, next_last_index, true);
		if (misplaced_repair.recoveryOnNextStack)
			misplaced_repair.distance++;

		repair.numDeletions = nextStackTop + BUFF_UBOUND;
		secondaryRecovery(repair,
			nextStack, nextStackTop,
			next_last_index, true);
		if (repair.recoveryOnNextStack)
			repair.distance++;

		locationStack[nextStackTop] = save_location;
	}
	else // next_stack not available, initialize ...
	{
		misplaced_repair.numDeletions = stateStackTop;
		repair.numDeletions = stateStackTop + BUFF_UBOUND;
	}

	//
	// Try secondary recovery on the "stack" configuration->
	//
	buffer[3] = error_token;

	buffer[2] = tokStream->getPrevious(buffer[3]);
	buffer[1] = tokStream->getPrevious(buffer[2]);
	buffer[0] = tokStream->getPrevious(buffer[1]);

	for (int k = 4; k < BUFF_SIZE; k++)
		buffer[k] = tokStream->getNext(buffer[k - 1]);

	int last_index;
	for (last_index = MAX_DISTANCE - 1;
		last_index >= 1 && tokStream->getKind(buffer[last_index]) == EOFT_SYMBOL;
		last_index--);
	last_index++;

	misplacementRecovery(misplaced_repair, stateStack, stateStackTop, last_index, false);

	secondaryRecovery(repair, stateStack, stateStackTop, last_index, false);

	//
	// If a successful misplaced recovery was found, compare it with
	// the most successful secondary recovery.  If the misplaced
	// recovery either deletes fewer symbols or parse-checks further
	// then it is chosen.
	//
	if (misplaced_repair.distance > MIN_DISTANCE)
	{
		if (misplaced_repair.numDeletions <= repair.numDeletions ||
			(misplaced_repair.distance - misplaced_repair.numDeletions) >=
			(repair.distance - repair.numDeletions))
		{
			repair.code = MISPLACED_CODE;
			repair.stackPosition = misplaced_repair.stackPosition;
			repair.bufferPosition = 2;
			repair.numDeletions = misplaced_repair.numDeletions;
			repair.distance = misplaced_repair.distance;
			repair.recoveryOnNextStack = misplaced_repair.recoveryOnNextStack;
		}
	}

	//
	// If the successful recovery was on next_stack, update: stack,
	// buffer, location_stack and last_index.
	//
	if (repair.recoveryOnNextStack)
	{
		stateStackTop = nextStackTop;
		//System.arraycopy(nextStack, 0, stateStack, 0, stateStackTop + 1);
		System::arraycopy(nextStack, 0, stateStack, 0, stateStackTop + 1);

		buffer[2] = error_token;
		buffer[1] = tokStream->getPrevious(buffer[2]);
		buffer[0] = tokStream->getPrevious(buffer[1]);

		for (int k = 3; k < BUFF_UBOUND; k++)
			buffer[k] = tokStream->getNext(buffer[k - 1]);

		buffer[BUFF_UBOUND] = tokStream->badToken(); // elmt not available

		locationStack[nextStackTop] = buffer[2];
		last_index = next_last_index;
	}

	//
	// Next, try scope recoveries after deletion of one, two, three,
	// four ... buffer_position tokens from the input stream.
	//
	if (repair.code == SECONDARY_CODE || repair.code == DELETION_CODE)
	{
		PrimaryRepairInfo scope_repair;
		for (scope_repair.bufferPosition = 2;
			scope_repair.bufferPosition <= repair.bufferPosition &&
			repair.code != SCOPE_CODE; scope_repair.bufferPosition++)
		{
			scopeTrial(scope_repair, stateStack, stateStackTop);
			int j = (scope_repair.distance >= MAX_DISTANCE
				? last_index
				: scope_repair.distance),
				k = scope_repair.bufferPosition - 1;
			if ((scope_repair.distance - k) > MIN_DISTANCE && (j - k) > (repair.distance - repair.numDeletions))
			{
				int i = scopeIndex[scopeStackTop]; // upper bound
				repair.code = SCOPE_CODE;
				repair.symbol = scopeLhs(i) + NT_OFFSET;
				repair.stackPosition = stateStackTop;
				repair.bufferPosition = scope_repair.bufferPosition;
			}
		}
	}

	//
	// If a successful repair was not found, quit!  Otherwise, issue
	// diagnosis and adjust configuration->..
	//
	RepairCandidate candidate;
	if (repair.code == 0)
		return candidate;

	secondaryDiagnosis(repair);

	//
	// Update buffer based on number of elements that are deleted.
	//
	switch (repair.code)
	{
	case MISPLACED_CODE:
		candidate.location = buffer[2];
		candidate.symbol = tokStream->getKind(buffer[2]);
		tokStream->reset(tokStream->getNext(buffer[2]));

		break;

	case DELETION_CODE:
		candidate.location = buffer[repair.bufferPosition];
		candidate.symbol = tokStream->getKind(buffer[repair.bufferPosition]);
		tokStream->reset(tokStream->getNext(buffer[repair.bufferPosition]));

		break;

	default: // SCOPE_CODE || SECONDARY_CODE
		candidate.symbol = repair.symbol;
		candidate.location = buffer[repair.bufferPosition];
		tokStream->reset(buffer[repair.bufferPosition]);

		break;
	}

	return candidate;
}

void DiagnoseParser::misplacementRecovery(SecondaryRepairInfo& repair, Array<int>& stack, int stack_top,
	int last_index, bool stack_flag)
{
	int previous_loc = buffer[2],
		stack_deletions = 0;

	for (int top = stack_top - 1; top >= 0; top--)
	{
		if (locationStack[top] < previous_loc)
			stack_deletions++;
		previous_loc = locationStack[top];

		int parse_distance = parseCheck(stack, top, tokStream->getKind(buffer[2]), 3),
			j = (parse_distance >= MAX_DISTANCE ? last_index : parse_distance);
		if ((parse_distance > MIN_DISTANCE) && (j - stack_deletions) > (repair.distance - repair.numDeletions))
		{
			repair.stackPosition = top;
			repair.distance = j;
			repair.numDeletions = stack_deletions;
			repair.recoveryOnNextStack = stack_flag;
		}
	}

	return;
}

void DiagnoseParser::secondaryRecovery(SecondaryRepairInfo& repair, Array<int>& stack, int stack_top,
	int last_index, bool stack_flag)
{
	int previous_loc = buffer[2],
		stack_deletions = 0;

	for (int top = stack_top; top >= 0 && repair.numDeletions >= stack_deletions; top--)
	{
		if (locationStack[top] < previous_loc)
			stack_deletions++;
		previous_loc = locationStack[top];

		for (int i = 2;
			i <= (last_index - MIN_DISTANCE + 1) &&
			(repair.numDeletions >= (stack_deletions + i - 1)); i++)
		{
			int parse_distance = parseCheck(stack, top, tokStream->getKind(buffer[i]), i + 1),
				j = (parse_distance >= MAX_DISTANCE ? last_index : parse_distance);

			if ((parse_distance - i + 1) > MIN_DISTANCE)
			{
				int k = stack_deletions + i - 1;
				if ((k < repair.numDeletions) ||
					(j - k) > (repair.distance - repair.numDeletions) ||
					((repair.code == SECONDARY_CODE) && (j - k) == (repair.distance - repair.numDeletions)))
				{
					repair.code = DELETION_CODE;
					repair.distance = j;
					repair.stackPosition = top;
					repair.bufferPosition = i;
					repair.numDeletions = k;
					repair.recoveryOnNextStack = stack_flag;
				}
			}

			for (int l = nasi(stack[top]); l >= 0 && nasr(l) != 0; l++)
			{
				int symbol = nasr(l) + NT_OFFSET;
				parse_distance = parseCheck(stack, top, symbol, i);
				j = (parse_distance >= MAX_DISTANCE ? last_index : parse_distance);

				if ((parse_distance - i + 1) > MIN_DISTANCE)
				{
					int k = stack_deletions + i - 1;
					if (k < repair.numDeletions || (j - k) >(repair.distance - repair.numDeletions))
					{
						repair.code = SECONDARY_CODE;
						repair.symbol = symbol;
						repair.distance = j;
						repair.stackPosition = top;
						repair.bufferPosition = i;
						repair.numDeletions = k;
						repair.recoveryOnNextStack = stack_flag;
					}
				}
			}
		}
	}

	return;
}

void DiagnoseParser::secondaryDiagnosis(SecondaryRepairInfo& repair)
{
	switch (repair.code)
	{
	case SCOPE_CODE:
	{
		if (repair.stackPosition < stateStackTop)
			emitError(DELETION_CODE,
				terminalIndex(ERROR_SYMBOL),
				locationStack[repair.stackPosition],
				buffer[1]);
		for (int i = 0; i < scopeStackTop; i++)
			emitError(SCOPE_CODE,
				-scopeIndex[i],
				locationStack[scopePosition[i]],
				buffer[1],
				nonterminalIndex(scopeLhs(scopeIndex[i])));

		repair.symbol = scopeLhs(scopeIndex[scopeStackTop]) + NT_OFFSET;
		stateStackTop = scopePosition[scopeStackTop];
		emitError(SCOPE_CODE,
			-scopeIndex[scopeStackTop],
			locationStack[scopePosition[scopeStackTop]],
			buffer[1],
			getNtermIndex(stateStack[stateStackTop],
				repair.symbol,
				repair.bufferPosition)
		);
		break;
	}
	default:
		emitError(repair.code,
			(repair.code == SECONDARY_CODE
				? getNtermIndex(stateStack[repair.stackPosition],
					repair.symbol,
					repair.bufferPosition)
				: terminalIndex(ERROR_SYMBOL)),
			locationStack[repair.stackPosition],
			buffer[repair.bufferPosition - 1]);
		stateStackTop = repair.stackPosition;
	}

	return;
}


//
// This procedure is invoked to form a secondary error message.
// The parameter k identifies the error to be processed.  The
// global variable: msg, is used to store the message.
//
std::wstring DiagnoseParser::PrintSecondaryMessage(int msg_code,
	int name_index,
	int left_token_loc,
	int right_token_loc,
	int scope_name_index)
{
	//using std::wcout;
	std::wstringstream wstringstream;
	std::wstring name_str;
	int i,
		len = 0;

	if (name_index >= 0)
	{
	
		name_str = name(name_index);
		len =name_str.size();
	}

	/*int left_line_no = tokStream->getLine(left_token_loc),
		left_column_no = tokStream->getColumn(left_token_loc),
		right_line_no = tokStream->getEndLine(right_token_loc),
		right_column_no = tokStream->getEndColumn(right_token_loc),
		left_location = left_token_loc,
		right_location = right_token_loc;

	wstringstream << tokStream->getFileName()
		<< ':' << left_line_no << ':' << left_column_no
		<< ':' << right_line_no << ':' << right_column_no
		<< ':' << left_location << ':' << right_location
		<< ": ";*/

	switch (msg_code)
	{
	case MISPLACED_CODE:
		wstringstream << "Misplaced construct(s)";
		break;
	case SCOPE_CODE:
		wstringstream << '\"';
		for (i = scopeSuffix(-(int)name_index);
			scopeRhs(i) != 0; i++)
		{
			len = name(scopeRhs(i)).size();
			name_str = name(scopeRhs(i)).c_str();
			for (int j = 0; j < len; j++)
				wstringstream << name_str[j];
			if (scopeRhs(i + 1)) // any more symbols to print?
				wstringstream << ' ';
		}
		wstringstream << '\"';
		wstringstream << " inserted to complete scope";
		//
		// TODO: This should not be an option
		//
		if (scope_name_index)
		{
			name_str = name(scope_name_index);
			len = name_str.size();
			for (int j = 0; j < len; j++) // any more symbols to print?
				wstringstream << name_str[j];
		}
		else wstringstream << "phrase";
		break;
	case  MANUAL_CODE:
		wstringstream << '\"';
		for (i = 0; i < len; i++)
			wstringstream << name_str[i];
		wstringstream << "\" inserted to complete structure";
		break;
	case MERGE_CODE:
		wstringstream << "Symbols merged to form ";
		for (i = 0; i < len; i++)
			wstringstream << name_str[i];
		break;
	default:
		if (msg_code == DELETION_CODE || len == 0)
			wstringstream << "Unexpected input discarded";
		else
		{
			for (i = 0; i < len; i++)
				wstringstream << name_str[i];
			wstringstream << " expected instead";
		}
	}

	return  wstringstream.str();


}



//
// This procedure is invoked to form a primary error message. The
// parameter k identifies the error to be processed.  The global
// variable: msg, is used to store the message.
//
std::wstring DiagnoseParser::PrintPrimaryMessage(int msg_code,
	int name_index,
	int left_token_loc,
	int right_token_loc,
	int scope_name_index)
{
	std::wstringstream wstringstream;
	std::wstring name_str ;
	
	int i,
		len = 0;
	/*int left_line_no = tokStream->getLine(left_token_loc),
	left_column_no = tokStream->getColumn(left_token_loc),
	right_line_no = tokStream->getEndLine(right_token_loc),
	right_column_no = tokStream->getEndColumn(right_token_loc),
	left_location = left_token_loc,
	right_location = right_token_loc;

wstringstream << tokStream->getFileName()
	<< ':' << left_line_no << ':' << left_column_no
	<< ':' << right_line_no << ':' << right_column_no
	<< ':' << left_location << ':' << right_location
	<< ": ";*/
	if (name_index >= 0)
	{
		name_str = name(name_index);
		len = name_str.size();
	
	}

	switch (msg_code)
	{
	case ERROR_CODE:
		wstringstream << "Parsing terminated at this token";
		break;
	case BEFORE_CODE:
		for (i = 0; i < len; i++)
			wstringstream << name_str[i];
		wstringstream << " inserted before this token";
		break;
	case INSERTION_CODE:
		for (i = 0; i < len; i++)
			wstringstream << name_str[i];
		wstringstream << " expected after this token";
		break;
	case DELETION_CODE:
		if (left_token_loc == right_token_loc)
			wstringstream << "Unexpected symbol ignored";
		else wstringstream << "Unexpected symbols ignored";
		break;
	case INVALID_CODE:
		if (len == 0)
			wstringstream << "Unexpected input discarded";
		else
		{
			wstringstream << "Invalid ";
			for (i = 0; i < len; i++)
				wstringstream << name_str[i];
		}
		break;
	case SUBSTITUTION_CODE:
		for (i = 0; i < len; i++)
			wstringstream << name_str[i];
		wstringstream << " expected instead of this token";
		break;
	case SCOPE_CODE:
		wstringstream << '\"';
		for (i = scopeSuffix(-(int)name_index);
			scopeRhs(i) != 0; i++)
		{
			len = name(scopeRhs(i)).size();
			name_str = name(scopeRhs(i)).c_str();
			for (int j = 0; j < len; j++)
				wstringstream << name_str[j];
			if (scopeRhs(i + 1)) // any more symbols to print?
				wstringstream << ' ';
		}
		wstringstream << '\"';
		wstringstream << " inserted to complete scope";
		//
		// TODO: This should not be an option
		//
		if (scope_name_index)
		{
			name_str = name(scope_name_index);
			len = name_str.size();
			for (int j = 0; j < len; j++) // any more symbols to print?
				wstringstream << name_str[j];
		}
		else wstringstream << "scope";
		break;
	case MANUAL_CODE:
		wstringstream << '\"';
		for (i = 0; i < len; i++)
			wstringstream << name_str[i];
		wstringstream << "\" inserted to complete structure";
		break;
	case MERGE_CODE:
		wstringstream << "symbols merged to form ";
		for (i = 0; i < len; i++)
			wstringstream << name_str[i];
		break;
	case EOF_CODE:
		for (i = 0; i < len; i++)
			wstringstream << name_str[i];
		wstringstream << " reached after this token";
		break;
	default:
		if (msg_code == MISPLACED_CODE)
			wstringstream << "misplaced construct(s)";
		else if (len == 0)
			wstringstream << "unexpected input discarded";
		else
		{
			for (i = 0; i < len; i++)
				wstringstream << name_str[i];
			wstringstream << " expected instead";
		}
		break;
	}

	wstringstream << '\n';
	return  wstringstream.str();
}
void DiagnoseParser::emitError(int msg_code, int name_index, int left_token, int right_token, int scope_name_index)
{
	int left_token_loc = (left_token > right_token ? right_token : left_token),
		right_token_loc = right_token;


	std::wstring token_name;
	if (left_token_loc < right_token_loc)
		token_name=PrintSecondaryMessage(msg_code,
			name_index,
			left_token_loc,
			right_token_loc,
			scope_name_index);
	else
		token_name =PrintPrimaryMessage(msg_code,
		name_index,
		left_token_loc,
		right_token_loc,
		scope_name_index);

	

	if(token_name.empty())
	{
		std::wstringex temp_name;
		if (name_index >= 0)
		{
			temp_name = name(name_index);
		}
		std::wstringex upper_name = temp_name;
		upper_name.toupper();
		token_name = (name_index >= 0 &&
			!(upper_name == (L"ERROR"))
			? L"\"" + temp_name + L"\""
			: L"");

		if (msg_code == INVALID_CODE)
			msg_code = token_name.length() == 0 ? INVALID_CODE : INVALID_TOKEN_CODE;

		if (msg_code == SCOPE_CODE)
		{
			token_name = L"\"";
			for (int i = scopeSuffix(-(int)name_index); scopeRhs(i) != 0; i++)
			{
				if (!isNullable(scopeRhs(i)))
				{
					int symbol_index = (scopeRhs(i) > NT_OFFSET
						? nonterminalIndex(scopeRhs(i) - NT_OFFSET)
						: terminalIndex(scopeRhs(i)));
					if (name(symbol_index).length() > 0)
					{
						if (token_name.length() > 1) // Not just starting quote?
							token_name += L" "; // add a space separator
						token_name += name(symbol_index);
					}
				}
			}
			token_name += L"\"";
		}
	}
	

	tokStream->reportError(msg_code, left_token, right_token, token_name);

	return;
}
