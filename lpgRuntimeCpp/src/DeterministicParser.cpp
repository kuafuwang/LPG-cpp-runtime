#include "DeterministicParser.h"

#include "Exception.h"
#include "Monitor.h"
#include "ParseTable.h"
#include "RuleAction.h"
#include "TokenStream.h"

DeterministicParser::~DeterministicParser()
{
	delete action;
	action = nullptr;
}

int DeterministicParser::lookahead(int act, int token)
{
	act = prs->lookAhead(act - LA_STATE_OFFSET, tokStream->getKind(token));
	return (act > LA_STATE_OFFSET
		        ? lookahead(act, tokStream->getNext(token))
		        : act);
}

int DeterministicParser::tAction(int act, int sym)
{
	act = prs->tAction(act, sym);
	return (act > LA_STATE_OFFSET
		        ? lookahead(act, tokStream->peek())
		        : act);
}

int DeterministicParser::tAction(int act, std::vector<int>& sym, int index)
{
	act = prs->tAction(act, sym[index]);
	while (act > LA_STATE_OFFSET)
	{
		index = ((index + 1) % sym.size());
		act = prs->lookAhead(act - LA_STATE_OFFSET, sym[index]);
	}

	return act;
}

void DeterministicParser::processReductions()
{
	do
	{
		stateStackTop -= (prs->rhs(currentAction) - 1);
		ra->ruleAction(currentAction);
		currentAction = prs->ntAction(stateStack[stateStackTop],
		                              prs->lhs(currentAction));
	}
	while (currentAction <= NUM_RULES);

	return;
}

int DeterministicParser::getCurrentRule()
{
	if (taking_actions)
		return currentAction;
	throw  UnavailableParserInformationException();
}

int DeterministicParser::getFirstToken()
{
	if (taking_actions)
		return getToken(1);
	throw  UnavailableParserInformationException();
}

int DeterministicParser::getFirstToken(int i)
{
	if (taking_actions)
		return getToken(i);
	throw  UnavailableParserInformationException();
}

int DeterministicParser::getLastToken()
{
	if (taking_actions)
		return lastToken;
	throw  UnavailableParserInformationException();
}

int DeterministicParser::getLastToken(int i)
{
	if (taking_actions)
		return (i >= prs->rhs(currentAction)
			        ? lastToken
			        : tokStream->getPrevious(getToken(i + 1)));
	throw  UnavailableParserInformationException();
}

void DeterministicParser::reset()
{
	this->taking_actions = false;
	this->markerKind = 0;

	if (action != nullptr) action->reset();
}

void DeterministicParser::reset(Monitor* monitor, TokenStream* tokStream)
{
	this->monitor = monitor;
	this->tokStream = (TokenStream*)tokStream;

	reset();
}

void DeterministicParser::reset(Monitor* monitor, TokenStream* tokStream, ParseTable* prs, RuleAction* ra)
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

	if (!prs->isValidForParser()) throw  BadParseSymFileException();
	if (prs->getBacktrack()) throw  NotDeterministicParseTableException();
}

Object* DeterministicParser::parseEntry(int marker_kind)
{
	//
	// Indicate that we are running the regular parser and that it's
	// ok to use the utility functions to query the parser.
	//
	taking_actions = true;

	//
	// Reset the token stream and get the first token.
	//
	tokStream->reset();
	lastToken = tokStream->getPrevious(tokStream->peek());
	int curtok,
	    current_kind;
	if (marker_kind == 0)
	{
		curtok = tokStream->getToken();
		current_kind = tokStream->getKind(curtok);
	}
	else
	{
		curtok = lastToken;
		current_kind = marker_kind;
	}

	//
	// Start parsing.
	//
	reallocateStacks(); // make initial allocation
	stateStackTop = -1;
	currentAction = START_STATE;

ProcessTerminals:
	for (;;)
	{
		//
		// if the parser needs to stop processing,
		// it may do so here.
		//
		if (monitor != nullptr && monitor->isCancelled())
		{
			taking_actions = false; // indicate that we are done
			return nullptr;
		}

		try
		{
			stateStack.at(++stateStackTop) = currentAction;
		}
		catch (std::out_of_range&)
		{
			reallocateStacks();
			stateStack[stateStackTop] = currentAction;
		}

		locationStack[stateStackTop] = curtok;

		currentAction = tAction(currentAction, current_kind);

		if (currentAction <= NUM_RULES)
		{
			stateStackTop--; // make reduction look like a shift-reduce
			processReductions();
		}
		else if (currentAction > ERROR_ACTION)
		{
			lastToken = curtok;
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
			currentAction -= ERROR_ACTION;
			processReductions();
		}
		else if (currentAction < ACCEPT_ACTION)
		{
			lastToken = curtok;
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
		}
		else
		{
			break/* ProcessTerminals*/;
		}
	}

	taking_actions = false; // indicate that we are done

	if (currentAction == ERROR_ACTION)
		throw  BadParseException(curtok);

	return parseStack[marker_kind == 0 ? 0 : 1];
}

Object* DeterministicParser::parseActions()
{
	//
	// Indicate that we are processing actions now (for the incremental
	// parser) and that it's ok to use the utility functions to query the
	// parser.
	//
	taking_actions = true;

	tokStream->reset();
	lastToken = tokStream->getPrevious(tokStream->peek());
	int curtok = (markerKind == 0 ? tokStream->getToken() : lastToken);

	try
	{
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
			{
				taking_actions = false; // indicate that we are done
				return nullptr;
			}

			stateStack[++stateStackTop] = currentAction;
			locationStack[stateStackTop] = curtok;

			currentAction = action->get(i);
			if (currentAction <= NUM_RULES) // a reduce action?
			{
				stateStackTop--; // turn reduction intoshift-reduction
				processReductions();
			}
			else // a shift or shift-reduce action
			{
				lastToken = curtok;
				curtok = tokStream->getToken();
				if (currentAction > ERROR_ACTION) // a shift-reduce action?
				{
					currentAction -= ERROR_ACTION;
					processReductions();
				}
			}
		}
	}
	catch (std::exception&) // if any exception is thrown, indicate BadParse
	{
		taking_actions = false; // indicate that we are done.
		throw  BadParseException(curtok);
	}

	taking_actions = false; // indicate that we are done.
	delete action;
	action = nullptr; // turn into garbage
	return parseStack[markerKind == 0 ? 0 : 1];
}

 void DeterministicParser::resetParserEntry(int marker_kind)
{
	this->markerKind = marker_kind;

	if (!stateStack.Size())
		reallocateStacks(); // make initial allocation
	
	stateStackTop = 0;
	stateStack[stateStackTop] = START_STATE;
	if (action == nullptr)
		action = new IntTuple(1 << 20);
	else action->reset();

	//
	// Indicate that we are going to run the incremental parser and that
	// it's forbidden to use the utility functions to query the parser.
	//
	taking_actions = false;

	if (marker_kind != 0)
	{
		std::vector<int> sym = { markerKind };
		parse(sym, 0);
	}
}

bool DeterministicParser::recoverableState(int state)
{
	for (int k = prs->asi(state); prs->asr(k) != 0; k++)
	{
		if (prs->asr(k) == ERROR_SYMBOL)
			return true;
	}
	return false;
}

void DeterministicParser::errorReset()
{
	int gate = (this->markerKind == 0 ? 0 : 1);
	for (; stateStackTop >= gate; stateStackTop--)
		if (recoverableState(stateStack[stateStackTop]))
			break;
	if (stateStackTop < gate)
		resetParserEntry(markerKind);
	return;
}

int DeterministicParser::parse(std::vector<int>& sym, int index)
{
	// assert(sym.length == prs->getMaxLa());

	//
	// First, we save the current length of the action tuple, in
	// case an error is encountered and we need to restore the
	// original configuration.
	//
	// Next, we declara and initialize the variable pos which will
	// be used to indicate the highest useful position in stateStack
	// as we are simulating the actions induced by the next k input
	// terminals in sym.
	//
	// The location stack will be used here as a temporary stack
	// to simulate these actions. We initialize its first useful
	// offset here.
	//
	int save_action_length = action->size(),
	    pos = stateStackTop,
	    location_top = stateStackTop - 1;

	//
	// When a reduce action is encountered, we compute all REDUCE
	// and associated goto actions induced by the current token.
	// Eventually, a SHIFT, SHIFT-REDUCE, ACCEPT or ERROR action is
	// computed...
	//
	for (currentAction = tAction(stateStack[stateStackTop], sym, index);
	     currentAction <= NUM_RULES;
	     currentAction = tAction(currentAction, sym, index))
	{
		action->add(currentAction);
		do
		{
			location_top -= (prs->rhs(currentAction) - 1);
			int state = (location_top > pos
				             ? locationStack[location_top]
				             : stateStack[location_top]);
			currentAction = prs->ntAction(state, prs->lhs(currentAction));
		}
		while (currentAction <= NUM_RULES);

		//
		// ... Update the maximum useful position of the
		// stateSTACK, push goto state into stack, and
		// continue by compute next action on current symbol
		// and reentering the loop...
		//
		pos = pos < location_top ? pos : location_top;
		try
		{
			locationStack.at(location_top + 1) = currentAction;
		}
		catch (std::out_of_range&)
		{
			reallocateStacks();
			locationStack[location_top + 1] = currentAction;
		}
	}

	//
	// At this point, we have a shift, shift-reduce, accept or error
	// action. stateSTACK contains the configuration of the state stack
	// prior to executing any action on the currenttoken. locationStack
	// contains the configuration of the state stack after executing all
	// reduce actions induced by the current token. The variable pos
	// indicates the highest position in the stateSTACK that is still
	// useful after the reductions are executed.
	//
	if (currentAction > ERROR_ACTION || // SHIFT-REDUCE action ?
		currentAction < ACCEPT_ACTION) // SHIFT action ?
	{
		action->add(currentAction);
		//
		// If no error was detected, update the state stack with 
		// the info that was temporarily computed in the locationStack.
		//
		stateStackTop = location_top + 1;
		for (int i = pos + 1; i <= stateStackTop; i++)
			stateStack[i] = locationStack[i];

		//
		// If we have a shift-reduce, process it as well as
		// the goto-reduce actions that follow it.
		//
		if (currentAction > ERROR_ACTION)
		{
			currentAction -= ERROR_ACTION;
			do
			{
				stateStackTop -= (prs->rhs(currentAction) - 1);
				currentAction = prs->ntAction(stateStack[stateStackTop],
				                              prs->lhs(currentAction));
			}
			while (currentAction <= NUM_RULES);
		}

		//
		// Process the  transition - either a shift action of
		// if we started out with a shift-reduce, the  GOTO
		// action that follows it.
		//
		try
		{
			stateStack.at(++stateStackTop) = currentAction;
		}
		catch (std::exception&)
		{
			reallocateStacks();
			stateStack[stateStackTop] = currentAction;
		}
	}
	else if (currentAction == ERROR_ACTION)
		action->reset(save_action_length); // restore original action state.
	return currentAction;
}

