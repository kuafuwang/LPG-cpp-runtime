#include "BacktrackingParser.h"

#include "ConfigurationElement.h"
#include "ConfigurationStack.h"
#include "ErrorToken.h"
#include "Exception.h"
#include "IPrsStream.h"
#include "IToken.h"
#include "Monitor.h"
#include "ParseErrorCodes.h"
#include "ParseTable.h"
#include "RecoveryParser.h"
#include "RuleAction.h"

int BacktrackingParser::getMarkerToken(int marker_kind, int start_token_index)
{
	if (marker_kind == 0)
		return 0;
	else
	{
		if (markerTokenIndex == 0)
		{
			if (!(dynamic_cast<IPrsStream*>(tokStream) ))
			{
				throw TokenStreamNotIPrsStreamException();
			}	
			markerTokenIndex = ((IPrsStream*)tokStream)->makeErrorToken(tokStream->getPrevious(start_token_index),
			                                                           tokStream->getPrevious(start_token_index),
			                                                           tokStream->getPrevious(start_token_index),
			                                                           marker_kind);
		}
		else ((IPrsStream*)tokStream)->getIToken(markerTokenIndex)->setKind(marker_kind);
	}

	return markerTokenIndex;
}

int BacktrackingParser::getFirstToken()
{
	return tokStream->getFirstRealToken(getToken(1));
}

int BacktrackingParser::getFirstToken(int i)
{
	return tokStream->getFirstRealToken(getToken(i));
}

int BacktrackingParser::getLastToken()
{
	return tokStream->getLastRealToken(lastToken);
}

int BacktrackingParser::getLastToken(int i)
{
	int l = (i >= prs->rhs(currentAction)
		         ? lastToken
		         : tokens->get(locationStack[stateStackTop + i] - 1));
	return tokStream->getLastRealToken(l);
}

void BacktrackingParser::reset()
{
	action->reset();
	skipTokens = false;
	markerTokenIndex = 0;
}

void BacktrackingParser::reset(Monitor* monitor, TokenStream* tokStream)
{
	this->monitor = monitor;
	this->tokStream = (TokenStream*)tokStream;
	reset();
}

void BacktrackingParser::reset(Monitor* monitor, TokenStream* tokStream, ParseTable* prs, RuleAction* ra)
{
	reset(monitor, tokStream);

	this->prs = prs;
	this->ra = ra;

	START_STATE = prs->getStartState();
	NUM_RULES = prs->getNumRules();
	NT_OFFSET = prs->getNtOffset();
	LA_STATE_OFFSET = prs->getLaStateOffset();
	EOFT_SYMBOL = prs->getEoftSymbol();
	ERROR_SYMBOL = prs->getErrorSymbol();
	ACCEPT_ACTION = prs->getAcceptAction();
	ERROR_ACTION = prs->getErrorAction();

	if (!prs->isValidForParser()) throw BadParseSymFileException();
	if (!prs->getBacktrack()) throw NotBacktrackParseTableException();
}

void BacktrackingParser::reallocateOtherStacks(int start_token_index)
{
	// assert(Stacks::stateStack != nullptr);
	if (!this->actionStack.Size())
	{
		this->actionStack.Resize(Stacks::stateStack.Size());
		Stacks::locationStack.Resize(Stacks::stateStack.Size());
		Stacks::parseStack.Resize(Stacks::stateStack.Size());

		actionStack[0] = 0;
		locationStack[0] = start_token_index;
	}
	else if (this->actionStack.Size() < Stacks::stateStack.Size())
	{
		this->actionStack.Resize(Stacks::stateStack.Size());
		Stacks::locationStack.Resize(Stacks::stateStack.Size());
		Stacks::parseStack.Resize(Stacks::stateStack.Size());
	}
	return;
}

Object* BacktrackingParser::fuzzyParse()
{
	return fuzzyParseEntry(0, std::numeric_limits<int>::max());
}

Object* BacktrackingParser::fuzzyParse(int max_error_count)
{
	return fuzzyParseEntry(0, max_error_count);
}

Object* BacktrackingParser::fuzzyParseEntry(int marker_kind)
{
	return fuzzyParseEntry(marker_kind, std::numeric_limits<int>::max());
}

BacktrackingParser::ErrorPair::ErrorPair(int scope_index, int error_token)
{
	scopeIndex = scope_index;
	errorToken = error_token;
}

void BacktrackingParser::reportErrors()
{
	if (errors == nullptr) return;
	
	for (int k = 0; k < errors->size(); k++)
	{
		ErrorPair error = (ErrorPair)errors->at(k);
		int scope_index = error.scopeIndex,
		    error_token = error.errorToken;

		std::wstring text = L"\"";
		for (int i = prs->scopeSuffix(scope_index); prs->scopeRhs(i) != 0; i++)
		{
			if (!prs->isNullable(prs->scopeRhs(i)))
			{
				int symbol_index = (prs->scopeRhs(i) > NT_OFFSET
					                    ? prs->nonterminalIndex(prs->scopeRhs(i) - NT_OFFSET)
					                    : prs->terminalIndex(prs->scopeRhs(i)));
				if (prs->name(symbol_index).length() > 0)
				{
					if (text.length() > 1) // Not just starting quote?
						text += L" "; // add a space separator
					text += prs->name(symbol_index);
				}
			}
		}
		text += L"\"";

		tokStream->reportError(ParseErrorCodes::SCOPE_CODE,
		                       error_token,
		                       error_token,
		                       text);
	}


	return;
}

void BacktrackingParser::addRecoveryError(int scope_index, int error_index)
{
	if (errors == nullptr)
		errors = new std::vector<ErrorPair>();
	errors->push_back(ErrorPair(scope_index, error_index));
}

Object* BacktrackingParser::fuzzyParseEntry(int marker_kind, int max_error_count)
{
	errors = nullptr; // recovery errors list
	action->reset();
	tokStream->reset(); // Position at first token.
	reallocateStateStack();
	stateStackTop = 0;
	stateStack[0] = START_STATE;

	//
	// The tuple tokens will eventually contain the sequence 
	// of tokens that resulted in a successful parse. We leave
	// it up to the "Stream" implementer to define the predecessor
	// of the first token as he sees fit.
	//
	int first_token = tokStream->peek(),
	    start_token = first_token,
	    marker_token = getMarkerToken(marker_kind, first_token);
	tokens = new IntTuple(tokStream->getStreamLength());
	tokens->add(tokStream->getPrevious(first_token));

	int error_token = backtrackParse(action, marker_token);
	if (error_token != 0) // an error was detected?
	{
		if (!(dynamic_cast<IPrsStream*>(tokStream)))
		{
			throw TokenStreamNotIPrsStreamException();
		}
		std::unique_ptr<RecoveryParser> recovery_parser = std::make_unique<RecoveryParser>(this,  *action, *tokens, (IPrsStream*)tokStream, prs,
			monitor, max_error_count, 0);
		start_token = recovery_parser->recover(marker_token, error_token);
	}

	if (marker_token != 0 && start_token == first_token)
		tokens->add(marker_token);
	int t;
	for (t = start_token; tokStream->getKind(t) != EOFT_SYMBOL; t = tokStream->getNext(t))
		tokens->add(t);
	tokens->add(t);

	Object* parsing_result = parseActions(marker_kind);

	//
	// If the parsing was successful (no BadParseException was thrown) but it required the assistance of      
	// the recovery parser, issue the diagnostics of the repairs that were applied. Otherwise, the
	// BadParseException will cause us to bypass this code and leve it up to the DiagnosticParser to
	// issue the error messages.
	//      
	reportErrors();

	return parsing_result;
}

Object* BacktrackingParser::parse()
{
	// without an argument parse() will ignore error productions
	return parseEntry(0, 0);
}

Object* BacktrackingParser::parse(int max_error_count)
{
	return parseEntry(0, max_error_count);
}

Object* BacktrackingParser::parseEntry(int marker_kind)
{
	// without an argument parse() will ignore error productions
	return parseEntry(marker_kind, 0);
}

Object* BacktrackingParser::parseEntry(int marker_kind, int max_error_count)
{
	action->reset();
	tokStream->reset(); // Position at first token.
	reallocateStateStack();
	stateStackTop = 0;
	stateStack[0] = START_STATE;

	skipTokens = max_error_count < 0;

	if (max_error_count > 0 &&  dynamic_cast<IPrsStream*>( tokStream))
	{
		max_error_count = 0;
	}

	//
	// The tuple tokens will eventually contain the sequence 
	// of tokens that resulted in a successful parse. We leave
	// it up to the "Stream" implementer to define the predecessor
	// of the first token as he sees fit.
	//
	tokens = new IntTuple(tokStream->getStreamLength());
	tokens->add(tokStream->getPrevious(tokStream->peek()));

	int start_token_index = tokStream->peek(),
		repair_token = getMarkerToken(marker_kind, start_token_index),
		start_action_index = action->size(); // obviously 0
	
	Array<int>  temp_stack(stateStackTop + 1);
	for (int i = 0; i <= stateStackTop; ++i)
	{
		temp_stack[i] = stateStack[i];
	}
	//System.arraycopy(stateStack, 0, temp_stack, 0, temp_stack.length);

	int initial_error_token = backtrackParse(action, repair_token);
	for (int error_token = initial_error_token, count = 0;
	     error_token != 0;
	     error_token = backtrackParse(action, repair_token), count++)
	{
		if (count == max_error_count)
			throw BadParseException(initial_error_token);
		
		action->reset(start_action_index);
		tokStream->reset(start_token_index);
		stateStackTop = temp_stack.Size() - 1;
		for (int i = 0; i <= stateStackTop; ++i)
		{
			stateStack[i] = temp_stack[i];
		}
		//System.arraycopy(temp_stack, 0, stateStack, 0, temp_stack.length);
		reallocateOtherStacks(start_token_index);

		backtrackParseUpToError(repair_token, error_token);

		for (stateStackTop = findRecoveryStateIndex(stateStackTop);
		     stateStackTop >= 0;
		     stateStackTop = findRecoveryStateIndex(stateStackTop - 1))
		{
			int recovery_token = tokens->get(locationStack[stateStackTop] - 1);
			repair_token = errorRepair((IPrsStream*)tokStream,
			                           (recovery_token >= start_token_index ? recovery_token : error_token),
			                           error_token);
			if (repair_token != 0)
				break;
		}

		if (stateStackTop < 0)
			throw BadParseException(initial_error_token);

		temp_stack.Resize(stateStackTop + 1);
		for (int i = 0; i <= stateStackTop; ++i)
		{
			temp_stack[i] = stateStack[i];
		}
		//System.arraycopy(stateStack, 0, temp_stack, 0, temp_stack.length);

		start_action_index = action->size();
		start_token_index = tokStream->peek();
	}

	if (repair_token != 0)
		tokens->add(repair_token);
	int t;
	for (t = start_token_index; tokStream->getKind(t) != EOFT_SYMBOL; t = tokStream->getNext(t))
		tokens->add(t);
	tokens->add(t);

	return parseActions(marker_kind);
}

void BacktrackingParser::process_reductions()
{
	do
	{
		stateStackTop -= (prs->rhs(currentAction) - 1);
		ra->ruleAction(currentAction);
		currentAction = prs->ntAction(stateStack[stateStackTop], prs->lhs(currentAction));
		//if(currentAction <= NUM_RULES)
		//System.err.println("Goto-reducing by rule " + currentAction);              
	}
	while (currentAction <= NUM_RULES);
	//System.err.println("Goto state " + prs->originalState(currentAction));
	return;
}

Object* BacktrackingParser::parseActions(int marker_kind)
{
	int ti = -1,
	    curtok;
	lastToken = tokens->get(++ti);
	curtok = tokens->get(++ti);
	allocateOtherStacks();

	//
	// Reparse the input...
	//
	stateStackTop = -1;
	currentAction = START_STATE;

	for (int i = 0; i < action->size(); i++)
	{
		//
		// if the parser needs to stop processing, it may do so here.
		//
		if (monitor != nullptr && monitor->isCancelled())
			return nullptr;

		stateStack[++stateStackTop] = currentAction;
		locationStack[stateStackTop] = ti;

		currentAction = action->get(i);
		if (currentAction <= NUM_RULES) // a reduce action?
		{
			//System.err.println("reducing by rule " + currentAction);              
			stateStackTop--; // make reduction look like shift-reduction
			process_reductions();
		}
		else // a shift or shift-reduce action
		{
			if (tokStream->getKind(curtok) > NT_OFFSET)
			{
				auto badtok = (ErrorToken*)((IPrsStream*)tokStream)->getIToken(curtok);
				throw BadParseException(badtok->getErrorToken()->getTokenIndex());
				// parseStack[stateStackTop] = ra->prostheticAst[prs->getProsthesisIndex(tokStream->getKind(curtok))].create(tokStream->getIToken(curtok));
			}
			lastToken = curtok;
			curtok = tokens->get(++ti);
			if (currentAction > ERROR_ACTION) // a shift-reduce action?
			{
				currentAction -= ERROR_ACTION;
				//System.err.println("Shift-reducing by rule " + currentAction + " on token " + tokStream->getName(lastToken));              
				process_reductions();
			}
			//else System.err.println("Shifting on token " + tokStream->getName(lastToken) + " to state " + prs->originalState(currentAction));              
		}
	}

	return parseStack[marker_kind == 0 ? 0 : 1];
}

int BacktrackingParser::process_backtrack_reductions(int act)
{
	do
	{
		stateStackTop -= (prs->rhs(act) - 1);
		act = prs->ntAction(stateStack[stateStackTop], prs->lhs(act));
		//if(act <= NUM_RULES)
		//System.err.println("*Goto-reducing by rule " + act);
	}
	while (act <= NUM_RULES);
	//System.err.println("*Goto state " + prs->originalState(act));
	return act;
}

int BacktrackingParser::backtrackParse(Array<int>& stack_arg, int stack_top, IntSegmentedTuple* action_arg, int initial_token)
{
	stateStackTop = stack_top;
	//System.arraycopy(stack_arg, 0, stateStack, 0, stateStackTop + 1);
	for(int i = 0 ; i <= stateStackTop; ++i)
	{
		stateStack[i] = stack_arg[i];
	}
	// assert(this->action == action);
	return backtrackParse(action_arg, initial_token);
}

int BacktrackingParser::backtrackParse(IntSegmentedTuple* action_arg, int initial_token)
{
	//
	// Allocate configuration stack.
	//
	ConfigurationStack configuration_stack(prs);

	//
	// Keep parsing until we successfully reach the end of file or
	// an error is encountered. The list of actions executed will
	// be stored in the "action" tuple.
	//
	int error_token = 0,
	    maxStackTop = stateStackTop,
	    start_token = tokStream->peek(),
	    curtok = (initial_token > 0 ? initial_token : tokStream->getToken()),
	    current_kind = tokStream->getKind(curtok),
	    act = tAction(stateStack[stateStackTop], current_kind);

	//
	// The main driver loop
	//
	for (;;)
	{
		//
		// if the parser needs to stop processing,
		// it may do so here.
		//
		if (monitor != nullptr && monitor->isCancelled())
			return 0;

		if (act <= NUM_RULES)
		{
			//System.err.println("*reducing by rule " + act);              
			action_arg->add(act); // save this reduce action
			stateStackTop--;
			act = process_backtrack_reductions(act);
		}
		else if (act > ERROR_ACTION)
		{
			//System.err.println("*Shift-reducing by rule " + (act - ERROR_ACTION) + " on token " + tokStream->getName(curtok));
			action_arg->add(act); // save this shift-reduce action
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
			act = process_backtrack_reductions(act - ERROR_ACTION);
		}
		else if (act < ACCEPT_ACTION)
		{
			//System.err.println("*Shifting on token " + tokStream->getName(curtok) + " to state " + prs->originalState(act));
			action_arg->add(act); // save this shift action
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
				action_arg->reset(configuration->action_length);
				act = configuration->act;
				curtok = configuration->curtok;
				current_kind = tokStream->getKind(curtok);
				tokStream->reset(curtok == initial_token
					                 ? start_token
					                 : tokStream->getNext(curtok));
				stateStackTop = configuration->stack_top;
				configuration->retrieveStack(stateStack);
				//System.err.println("*Backtracking to state " + prs->originalState(stateStack[stateStackTop]) + " back on token (" + curtok + ") " + tokStream->getName(curtok));
				continue;
			}
			break;
		}
		else if (act > ACCEPT_ACTION)
		{
			if (configuration_stack.findConfiguration(stateStack, stateStackTop, curtok))
				act = ERROR_ACTION;
			else
			{
				configuration_stack.push(stateStack, stateStackTop, act + 1, curtok, action_arg->size());
				act = prs->baseAction(act);
				maxStackTop = stateStackTop > maxStackTop ? stateStackTop : maxStackTop;
			}
			continue;
		}
		else break; // assert(act == ACCEPT_ACTION);
		try
		{
			stateStack.at(++stateStackTop) = act;
		}
		catch (std::out_of_range&)
		{
			reallocateStateStack();
			stateStack[stateStackTop] = act;
		}

		act = tAction(act, current_kind);
	}

	// System.out.println("****Max Number of configurations: " + configuration_stack.maxConfigurationSize());
	// for (ConfigurationElement configuration = configuration_stack.pop();
	//      configuration != nullptr;
	//      configuration = configuration_stack.pop())
	//        {
	//System.out.println("    restart at position " + configuration->action_length +
	//                   " on action " + configuration->act +
	//                   " and token " + configuration->curtok +
	//                   " with kind " + tokStream->getKind(configuration->curtok)
	//                  );   
	//        }
	//
	// System.out.println("****Number of elements in stack tree: " + configuration_stack.numStateElements());
	// System.out.println("****Number of elements in stacks: " + configuration_stack.stacksSize());
	// System.out.println("****Number of actions: " + action->size());
	// System.out.println("****Max Stack Size = " + maxStackTop);
	// System.out.flush();
	return (act == ERROR_ACTION ? error_token : 0);
}

void BacktrackingParser::backtrackParseUpToError(int initial_token, int error_token)
{
	//
	// Allocate configuration stack.
	//
	ConfigurationStack configuration_stack(prs);

	//
	// Keep parsing until we successfully reach the end of file or
	// an error is encountered. The list of actions executed will
	// be stored in the "action" tuple.
	//
	int start_token = tokStream->peek(),
	    curtok = (initial_token > 0 ? initial_token : tokStream->getToken()),
	    current_kind = tokStream->getKind(curtok),
	    act = tAction(stateStack[stateStackTop], current_kind);

	tokens->add(curtok);
	locationStack[stateStackTop] = tokens->size();
	actionStack[stateStackTop] = action->size();

	for (;;)
	{
		//
		// if the parser needs to stop processing,
		// it may do so here.
		//
		if (monitor != nullptr && monitor->isCancelled())
			return;

		if (act <= NUM_RULES)
		{
			action->add(act); // save this reduce action
			stateStackTop--;
			act = process_backtrack_reductions(act);
		}
		else if (act > ERROR_ACTION)
		{
			action->add(act); // save this shift-reduce action
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
			tokens->add(curtok);
			act = process_backtrack_reductions(act - ERROR_ACTION);
		}
		else if (act < ACCEPT_ACTION)
		{
			action->add(act); // save this shift action
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
			tokens->add(curtok);
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
					action->reset(configuration->action_length);
					act = configuration->act;
					int next_token_index = configuration->curtok;
					tokens->reset(next_token_index);
					curtok = tokens->get(next_token_index - 1);
					current_kind = tokStream->getKind(curtok);
					tokStream->reset(curtok == initial_token
						                 ? start_token
						                 : tokStream->getNext(curtok));
					stateStackTop = configuration->stack_top;
					configuration->retrieveStack(stateStack);
					locationStack[stateStackTop] = tokens->size();
					actionStack[stateStackTop] = action->size();
					continue;
				}
			}
			break;
		}
		else if (act > ACCEPT_ACTION)
		{
			if (configuration_stack.findConfiguration(stateStack, stateStackTop, tokens->size()))
				act = ERROR_ACTION;
			else
			{
				configuration_stack.push(stateStack, stateStackTop, act + 1, tokens->size(), action->size());
				act = prs->baseAction(act);
			}
			continue;
		}
		else break; // assert(act == ACCEPT_ACTION);

		stateStack[++stateStackTop] = act; // no need to check if out of bounds
		locationStack[stateStackTop] = tokens->size();
		actionStack[stateStackTop] = action->size();
		act = tAction(act, current_kind);
	}

	// assert(curtok == error_token);

	return;
}

bool BacktrackingParser::repairable(int error_token)
{
	//
	// Allocate configuration stack.
	//
	ConfigurationStack configuration_stack(prs);

	//
	// Keep parsing until we successfully reach the end of file or
	// an error is encountered. The list of actions executed will
	// be stored in the "action" tuple.
	//
	int start_token = tokStream->peek(),
	    final_token = tokStream->getStreamLength(), // unreachable
	    curtok = 0,
	    current_kind = ERROR_SYMBOL,
	    act = tAction(stateStack[stateStackTop], current_kind);

	for (;;)
	{
		if (act <= NUM_RULES)
		{
			stateStackTop--;
			act = process_backtrack_reductions(act);
		}
		else if (act > ERROR_ACTION)
		{
			curtok = tokStream->getToken();
			if (curtok > final_token) return true;
			current_kind = tokStream->getKind(curtok);
			act = process_backtrack_reductions(act - ERROR_ACTION);
		}
		else if (act < ACCEPT_ACTION)
		{
			curtok = tokStream->getToken();
			if (curtok > final_token) return true;
			current_kind = tokStream->getKind(curtok);
		}
		else if (act == ERROR_ACTION)
		{
			auto configuration = configuration_stack.pop();
			if (configuration == nullptr)
				act = ERROR_ACTION;
			else
			{
				stateStackTop = configuration->stack_top;
				configuration->retrieveStack(stateStack);
				act = configuration->act;
				curtok = configuration->curtok;
				if (curtok == 0)
				{
					current_kind = ERROR_SYMBOL;
					tokStream->reset(start_token);
				}
				else
				{
					current_kind = tokStream->getKind(curtok);
					tokStream->reset(tokStream->getNext(curtok));
				}
				continue;
			}
			break;
		}
		else if (act > ACCEPT_ACTION)
		{
			if (configuration_stack.findConfiguration(stateStack, stateStackTop, curtok))
				act = ERROR_ACTION;
			else
			{
				configuration_stack.push(stateStack, stateStackTop, act + 1, curtok, 0);
				act = prs->baseAction(act);
			}
			continue;
		}
		else break; // assert(act == ACCEPT_ACTION);
		try
		{
			//
			// We consider a configuration to be acceptable for recovery
			// if we are able to consume enough symbols in the remainining
			// tokens to reach another potential recovery point past the
			// original error token.
			//
			if ((curtok > error_token) && (final_token == tokStream->getStreamLength()))
			{
				//
				// If the ERROR_SYMBOL is a valid Action Adjunct in the state
				// "act" then we set the terminating token as the successor of
				// the current token. I.e., we have to be able to parse at least
				// two tokens past the resynch point before we claim victory.
				//
				if (recoverableState(act))
					final_token = skipTokens ? curtok : tokStream->getNext(curtok);
			}

			stateStack.at(++stateStackTop) = act;
		}
		catch (std::out_of_range&)
		{
			reallocateStateStack();
			stateStack[stateStackTop] = act;
		}

		act = tAction(act, current_kind);
	}

	//
	// If we can reach the end of the input successfully, we claim victory.
	//
	return (act == ACCEPT_ACTION);
}

bool BacktrackingParser::recoverableState(int state)
{
	for (int k = prs->asi(state); prs->asr(k) != 0; k++)
	{
		if (prs->asr(k) == ERROR_SYMBOL)
			return true;
	}
	return false;
}

int BacktrackingParser::findRecoveryStateIndex(int start_index)
{
	int i;
	for (i = start_index; i >= 0; i--)
	{
		//
		// If the ERROR_SYMBOL is an Action Adjunct in state stateStack[i]
		// then chose i as the index of the state to recover on.
		//
		if (recoverableState(stateStack[i]))
			break;
	}

	if (i >= 0) // if a recoverable state, remove nullptr reductions, if any.
	{
		int k;
		for (k = i - 1; k >= 0; k--)
		{
			if (locationStack[k] != locationStack[i])
				break;
		}
		i = k + 1;
	}

	return i;
}

int BacktrackingParser::errorRepair(IPrsStream* stream, int recovery_token, int error_token)
{

	Array<int> temp_stack(stateStackTop + 1);
	for(int i = 0 ;  i <= stateStackTop; ++i)
	{
		temp_stack[i] = stateStack[i];
	}
	for (;
		stream->getKind(recovery_token) != EOFT_SYMBOL;
		recovery_token = stream->getNext(recovery_token))
	{
		stream->reset(recovery_token);
		if (repairable(error_token))
			break;
		
		stateStackTop = temp_stack.Size() - 1;
		for (int i = 0; i <= stateStackTop; ++i)
		{
			stateStack[i] = temp_stack[i];
		}
		//System.arraycopy(temp_stack, 0, stateStack, 0, temp_stack.length);
	}

	if (stream->getKind(recovery_token) == EOFT_SYMBOL)
	{
		stream->reset(recovery_token);
		if (!repairable(error_token))
		{
			stateStackTop = temp_stack.Size() - 1;
			for (int i = 0; i <= stateStackTop; ++i)
			{
				stateStack[i] = temp_stack[i];
			}
			//System.arraycopy(temp_stack, 0, stateStack, 0, temp_stack.length);
			return 0;
		}
	}

	//
	//
	//
	stateStackTop = temp_stack.Size() - 1;
	for (int i = 0; i <= stateStackTop; ++i)
	{
		stateStack[i] = temp_stack[i];
	}
	//System.arraycopy(temp_stack, 0, stateStack, 0, temp_stack.length);
	stream->reset(recovery_token);
	tokens->reset(locationStack[stateStackTop] - 1);
	action->reset(actionStack[stateStackTop]);

	return stream->makeErrorToken(tokens->get(locationStack[stateStackTop] - 1),
	                             stream->getPrevious(recovery_token),
	                             error_token,
	                             ERROR_SYMBOL);
}

int BacktrackingParser::lookahead(int act, int token)
{
	act = prs->lookAhead(act - LA_STATE_OFFSET, tokStream->getKind(token));
	return (act > LA_STATE_OFFSET
		        ? lookahead(act, tokStream->getNext(token))
		        : act);
}

int BacktrackingParser::tAction(int act, int sym)
{
	act = prs->tAction(act, sym);
	return (act > LA_STATE_OFFSET
		        ? lookahead(act, tokStream->peek())
		        : act);
}
