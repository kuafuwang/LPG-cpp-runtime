#include "LexParser.h"

#include "Exception.h"
#include "ILexStream.h"
#include "Monitor.h"
#include "ParseTable.h"
#include "RuleAction.h"
#include "tuple.h"
void LexParser::reset(ILexStream* tokStream)
{
	this->tokStream = tokStream;
}

void LexParser::reset(ILexStream* tokStream, ParseTable* prs, RuleAction* ra)
{
	this->tokStream = tokStream;
	this->prs = prs;
	this->ra = ra;

	START_STATE = prs->getStartState();
	LA_STATE_OFFSET = prs->getLaStateOffset();
	EOFT_SYMBOL = prs->getEoftSymbol();
	ACCEPT_ACTION = prs->getAcceptAction();
	ERROR_ACTION = prs->getErrorAction();
	START_SYMBOL = prs->getStartSymbol();
	NUM_RULES = prs->getNumRules();
}

LexParser::LexParser(ILexStream* tokStream, ParseTable* prs, RuleAction* ra)
{
	reset(tokStream, prs, ra);
}

void LexParser::reallocateStacks()
{
	int old_stack_length = (stack.empty() ? 0 : stackLength);
	stackLength += STACK_INCREMENT;

	stack.resize(stackLength);
	locationStack.resize(stackLength);
	tempStack.resize(stackLength);
	
	return;
}

int LexParser::getFirstToken(int i)
{
	return getToken(i);
}

int LexParser::getLastToken(int i)
{
	if (taking_actions)
		return (i >= prs->rhs(currentAction)
			        ? lastToken
			        : tokStream->getPrevious(getToken(i + 1)));
	throw  UnavailableParserInformationException();
}

int LexParser::getCurrentRule()
{
	if (taking_actions)
		return currentAction;
	throw  UnavailableParserInformationException();
}

int LexParser::getToken(int i)
{
	if (taking_actions)
		return locationStack[stateStackTop + (i - 1)];
	throw  UnavailableParserInformationException();
}

void LexParser::resetTokenStream(int i)
{
	//
	// if i exceeds the upper bound, reset it to point to the last element.
	//
	tokStream->reset(i > tokStream->getStreamLength() ? tokStream->getStreamLength() : i);
	curtok = tokStream->getToken();
	current_kind = tokStream->getKind(curtok);
	if (stack.empty())
		reallocateStacks();
	if (action == nullptr)
		action = new IntTuple(1 << 10);
}

void LexParser::parseCharacters(int start_offset, int end_offset)
{
	parseCharacters(nullptr, start_offset, end_offset);
}

void LexParser::parseCharacters(Monitor* monitor, int start_offset, int end_offset)
{
	resetTokenStream(start_offset);
	while (curtok <= end_offset)
	{
		//
		// if the parser needs to stop processing,
		// it may do so here.
		//
		if (monitor != nullptr && monitor->isCancelled())
			return;
		lexNextToken(end_offset);
	}
}

void LexParser::parseCharacters()
{
	parseCharacters(nullptr);
}

void LexParser::parseCharacters(Monitor* monitor)
{
	//
	// Indicate that we are running the regular parser and that it's
	// ok to use the utility functions to query the parser.
	//
	taking_actions = true;

	resetTokenStream(0);
	lastToken = tokStream->getPrevious(curtok);

	//
	// Until it reaches the end-of-file token, this outer loop
	// resets the parser and processes the next token.
	//

ProcessTokens:
	while (current_kind != EOFT_SYMBOL)
	{

		//
		// if the parser needs to stop processing,
		// it may do so here.
		//
		if (monitor != nullptr && monitor->isCancelled())
		{
			//break ProcessTokens;
			goto  break_ProcessTokens;
		}

		stateStackTop = -1;
		currentAction = START_STATE;
		starttok = curtok;


	ScanToken:
	for (;;)
		{
	
			try
			{
				stack.at(++stateStackTop) = currentAction;
			}
			catch (std::exception& e)
			{
				reallocateStacks();
				stack[stateStackTop] = currentAction;
			}

			locationStack[stateStackTop] = curtok;

			//
			// Compute the action on the next character. If it is a reduce action, we do not
			// want to accept it until we are sure that the character in question is can be parsed.
			// What we are trying to avoid is a situation where Curtok is not the EOF token
			// but it yields a default reduce action in the current configuration even though
			// it cannot ultimately be shifted; However, the state on top of the configuration also
			// contains a valid reduce action on EOF which, if taken, would lead to the successful
			// scanning of the token.
			// 
			// Thus, if the character can be parsed, we proceed normally. Otherwise, we proceed
			// as if we had reached the end of the file (end of the token, since we are really
			// scanning).
			// 
			parseNextCharacter(curtok, current_kind);
			if (currentAction == ERROR_ACTION && current_kind != EOFT_SYMBOL) // if not successful try EOF 
			{
				int save_next_token = tokStream->peek(); // save position after curtok
				tokStream->reset(tokStream->getStreamLength() - 1); // point to the end of the input
				parseNextCharacter(curtok, EOFT_SYMBOL);
				// assert (currentAction == ACCEPT_ACTION || currentAction == ERROR_ACTION);
				tokStream->reset(save_next_token); // reset the stream for the next token after curtok.
			}

			//
			// At this point, currentAction is either a Shift, Shift-Reduce, Accept or Error action->
			//
			if (currentAction > ERROR_ACTION) // Shift-reduce
			{
				lastToken = curtok;
				curtok = tokStream->getToken();
				current_kind = tokStream->getKind(curtok);
				currentAction -= ERROR_ACTION;
				do
				{
					stateStackTop -= (prs->rhs(currentAction) - 1);
					ra->ruleAction(currentAction);
					int lhs_symbol = prs->lhs(currentAction);
					if (lhs_symbol == START_SYMBOL)
					{
						//continue ProcessTokens;
						goto  ProcessTokens;
					}
					currentAction = prs->ntAction(stack[stateStackTop], lhs_symbol);
				}
				while (currentAction <= NUM_RULES);
			}
			else if (currentAction < ACCEPT_ACTION) // Shift
			{
				lastToken = curtok;
				curtok = tokStream->getToken();
				current_kind = tokStream->getKind(curtok);
			}
			else if (currentAction == ACCEPT_ACTION)
			{
				//continue ProcessTokens;
				goto  ProcessTokens;
			}
			else
			{
				//break ScanToken; // ERROR_ACTION
				goto break_ScanToken;
			}
		}
	break_ScanToken:
		
		//
		// Whenever we reach this point, an error has been detected.
		// Note that the parser loop above can never reach the ACCEPT
		// point as it is short-circuited each time it reduces a phrase
		// to the START_SYMBOL.
		//
		// If an error is detected on a single bad character,
		// we advance to the next character before resuming the
		// scan. However, if an error is detected after we start
		// scanning a construct, we form a bad token out of the
		// characters that have already been scanned and resume
		// scanning on the character on which the problem was
		// detected. In other words, in that case, we do not advance.
		//
		if (starttok == curtok)
		{
			if (current_kind == EOFT_SYMBOL)
			{
				goto break_ProcessTokens;
				//break ProcessTokens;
			}
			tokStream->reportLexicalError(starttok, curtok);
			lastToken = curtok;
			curtok = tokStream->getToken();
			current_kind = tokStream->getKind(curtok);
		}
		else tokStream->reportLexicalError(starttok, lastToken);
	}
break_ProcessTokens:
	taking_actions = false; // indicate that we are done

	return;
}

void LexParser::parseNextCharacter(int token, int kind)
{
	int start_action = stack[stateStackTop],
	    pos = stateStackTop,
	    tempStackTop = stateStackTop - 1;

Scan:
	for (currentAction = tAction(start_action, kind);
           currentAction <= NUM_RULES;
           currentAction = tAction(currentAction, kind))
	{
		bool break_Scan = false;
		do
		{
			int lhs_symbol = prs->lhs(currentAction);
			if (lhs_symbol == START_SYMBOL)
			{
				break_Scan = true;
				break ;
			}
			tempStackTop -= (prs->rhs(currentAction) - 1);
			int state = (tempStackTop > pos
				             ? tempStack[tempStackTop]
				             : stack[tempStackTop]);
			currentAction = prs->ntAction(state, lhs_symbol);
		}
		while (currentAction <= NUM_RULES);
		if (break_Scan)
			break;
		if (tempStackTop + 1 >= stack.size())
			reallocateStacks();
		//
		// ... Update the maximum useful position of the stack,
		// push goto state into (temporary) stack, and compute
		// the next action on the current symbol ...
		//
		pos = pos < tempStackTop ? pos : tempStackTop;
		tempStack[tempStackTop + 1] = currentAction;
	}

	//
	// If no error was detected, we update the configuration up to the point prior to the
	// shift or shift-reduce on the token by processing all reduce and goto actions associated
	// with the current token.
	//
	if (currentAction != ERROR_ACTION)
	{
		//
		// Note that it is important that the global variable currentAction be used here when
		// we are actually processing the rules. The reason being that the user-defined function
		// ra->ruleAction() may call  functions defined in this class (such as getLastToken())
		// which require that currentAction be properly initialized. 
		//
	Replay:
		for (currentAction = tAction(start_action, kind);
	             currentAction <= NUM_RULES;
	             currentAction = tAction(currentAction, kind))
		{
			stateStackTop--;
			bool break_Replay = false;
			do
			{
				stateStackTop -= (prs->rhs(currentAction) - 1);
				ra->ruleAction(currentAction);
				int lhs_symbol = prs->lhs(currentAction);
				if (lhs_symbol == START_SYMBOL)
				{
					currentAction = (starttok == token // nullptr string reduction to START_SYMBOL is illegal
						                 ? ERROR_ACTION
						                 : ACCEPT_ACTION);
					break_Replay = true;
					break /*Replay*/;
				}
				currentAction = prs->ntAction(stack[stateStackTop], lhs_symbol);
			}
			while (currentAction <= NUM_RULES);
		
		    if(break_Replay)
				break;
		
			stack[++stateStackTop] = currentAction;
			locationStack[stateStackTop] = token;
		}
	}

	return;
}

int LexParser::lookahead(int act, int token)
{
	act = prs->lookAhead(act - LA_STATE_OFFSET, tokStream->getKind(token));
	return (act > LA_STATE_OFFSET
		        ? lookahead(act, tokStream->getNext(token))
		        : act);
}

int LexParser::tAction(int act, int sym)
{
	act = prs->tAction(act, sym);
	return (act > LA_STATE_OFFSET
		        ? lookahead(act, tokStream->peek())
		        : act);
}

bool LexParser::scanNextToken()
{
	return lexNextToken(tokStream->getStreamLength());
}

bool LexParser::scanNextToken(int start_offset)
{
	resetTokenStream(start_offset);
	return lexNextToken(tokStream->getStreamLength());
}

bool LexParser::lexNextToken(int end_offset)
{
	//
	// Indicate that we are going to run the incremental parser and that
	// it's forbidden to use the utility functions to query the parser.
	//
	taking_actions = false;

	stateStackTop = -1;
	currentAction = START_STATE;
	starttok = curtok;
	action->reset();

ScanToken: for (;;)
	{
		try
		{
			stack.at(++stateStackTop) = currentAction;
		}
		catch (std::exception& e)
		{
			reallocateStacks();
			stack[stateStackTop] = currentAction;
		}

		//
		// Compute the action on the next character. If it is a reduce action, we do not
		// want to accept it until we are sure that the character in question is parsable.
		// What we are trying to avoid is a situation where curtok is not the EOF token
		// but it yields a default reduce action in the current configuration even though
		// it cannot ultimately be shifted; However, the state on top of the configuration also
		// contains a valid reduce action on EOF which, if taken, would lead to the succesful
		// scanning of the token.
		// 
		// Thus, if the character is parsable, we proceed normally. Otherwise, we proceed
		// as if we had reached the end of the file (end of the token, since we are really
		// scanning).
		// 
		currentAction = lexNextCharacter(currentAction, current_kind);
		if (currentAction == ERROR_ACTION && current_kind != EOFT_SYMBOL) // if not successful try EOF
		{
			int save_next_token = tokStream->peek(); // save position after curtok
			tokStream->reset(tokStream->getStreamLength() - 1); // point to the end of the input
			currentAction = lexNextCharacter(stack[stateStackTop], EOFT_SYMBOL);
			// assert (currentAction == ACCEPT_ACTION || currentAction == ERROR_ACTION);
			tokStream->reset(save_next_token); // reset the stream for the next token after curtok.
		}

		action->add(currentAction); // save the action

		//
		// At this point, currentAction is either a Shift, Shift-Reduce, Accept or Error action->
		//
		if (currentAction > ERROR_ACTION) //Shift-reduce
		{
			curtok = tokStream->getToken();
			if (curtok > end_offset)
				curtok = tokStream->getStreamLength();
			current_kind = tokStream->getKind(curtok);
			currentAction -= ERROR_ACTION;
			do
			{
				int lhs_symbol = prs->lhs(currentAction);
				if (lhs_symbol == START_SYMBOL)
				{
					parseActions();
					return true;
				}
				stateStackTop -= (prs->rhs(currentAction) - 1);
				currentAction = prs->ntAction(stack[stateStackTop], lhs_symbol);
			}
			while (currentAction <= NUM_RULES);
		}
		else if (currentAction < ACCEPT_ACTION) // Shift
		{
			curtok = tokStream->getToken();
			if (curtok > end_offset)
				curtok = tokStream->getStreamLength();
			current_kind = tokStream->getKind(curtok);
		}
		else if (currentAction == ACCEPT_ACTION)
			return true;
		else
			break /*ScanToken*/; // ERROR_ACTION
	}

	//
	// Whenever we reach this point, an error has been detected.
	// Note that the parser loop above can never reach the ACCEPT
	// point as it is short-circuited each time it reduces a phrase
	// to the START_SYMBOL.
	//
	// If an error is detected on a single bad character,
	// we advance to the next character before resuming the
	// scan. However, if an error is detected after we start
	// scanning a construct, we form a bad token out of the
	// characters that have already been scanned and resume
	// scanning on the character on which the problem was
	// detected. In other words, in that case, we do not advance.
	//
	if (starttok == curtok)
	{
		if (current_kind == EOFT_SYMBOL)
		{
			action = nullptr; // turn into garbage!
			return false;
		}
		lastToken = curtok;
		tokStream->reportLexicalError(starttok, curtok);
		curtok = tokStream->getToken();
		if (curtok > end_offset)
			curtok = tokStream->getStreamLength();
		current_kind = tokStream->getKind(curtok);
	}
	else
	{
		lastToken = tokStream->getPrevious(curtok);
		tokStream->reportLexicalError(starttok, lastToken);
	}

	return true;
}

int LexParser::lexNextCharacter(int act, int kind)
{
	int action_save = action->size(),
	    pos = stateStackTop,
	    tempStackTop = stateStackTop - 1;
	act = tAction(act, kind);
Scan: while (act <= NUM_RULES)
	{
		action->add(act);
		bool break_Scan = false;
		do
		{
			int lhs_symbol = prs->lhs(act);
			if (lhs_symbol == START_SYMBOL)
			{
				if (starttok == curtok) // nullptr string reduction to START_SYMBOL is illegal
				{
					act = ERROR_ACTION;
					break_Scan = true;
					break/* Scan*/;
				}
				else
				{
					parseActions();
					return ACCEPT_ACTION;
				}
			}
			tempStackTop -= (prs->rhs(act) - 1);
			int state = (tempStackTop > pos
				             ? tempStack[tempStackTop]
				             : stack[tempStackTop]);
			act = prs->ntAction(state, lhs_symbol);
		}
		while (act <= NUM_RULES);
		if(break_Scan)
		{
			break;
		}
	
		if (tempStackTop + 1 >= stack.size())
			reallocateStacks();
		//
		// ... Update the maximum useful position of the stack,
		// push goto state into (temporary) stack, and compute
		// the next action on the current symbol ...
		//
		pos = pos < tempStackTop ? pos : tempStackTop;
		tempStack[tempStackTop + 1] = act;
		act = tAction(act, kind);
	}

	//
	// If an error was detected, we restore the original configuration.
	// Otherwise, we update configuration up to the point prior to the
	// shift or shift-reduce on the token.
	//
	if (act == ERROR_ACTION)
		action->reset(action_save);
	else
	{
		stateStackTop = tempStackTop + 1;
		for (int i = pos + 1; i <= stateStackTop; i++) // update stack
			stack[i] = tempStack[i];
	}

	return act;
}

void LexParser::parseActions()
{
	//
	// Indicate that we are running the regular parser and that it's
	// ok to use the utility functions to query the parser.
	//
	taking_actions = true;

	curtok = starttok;
	lastToken = tokStream->getPrevious(curtok);

	//
	// Reparse the input...
	//
	stateStackTop = -1;
	currentAction = START_STATE;
process_actions:
	for (int i = 0; i < action->size(); i++)
	{
		stack[++stateStackTop] = currentAction;
		locationStack[stateStackTop] = curtok;
		bool break_process_actions = false;
		currentAction = action->get(i);
		if (currentAction <= NUM_RULES) // a reduce action?
		{
			stateStackTop--; // turn reduction intoshift-reduction
			do
			{
				stateStackTop -= (prs->rhs(currentAction) - 1);
				ra->ruleAction(currentAction);
				int lhs_symbol = prs->lhs(currentAction);
				if (lhs_symbol == START_SYMBOL)
				{
					// assert(starttok != curtok);  // nullptr string reduction to START_SYMBOL is illegal
					break_process_actions = true;
					break
					/*process_actions*/;
				}
				currentAction = prs->ntAction(stack[stateStackTop], lhs_symbol);
			}
			while (currentAction <= NUM_RULES);

			if (break_process_actions)
				break;
		}
		else // a shift or shift-reduce action
		{
			lastToken = curtok;
			curtok = tokStream->getNext(curtok);
			if (currentAction > ERROR_ACTION) // a shift-reduce action?
			{
				// REMOVE ME: current_kind = tokStream->getKind(curtok);
				currentAction -= ERROR_ACTION;
				do
				{
					stateStackTop -= (prs->rhs(currentAction) - 1);
					ra->ruleAction(currentAction);
					int lhs_symbol = prs->lhs(currentAction);
					if (lhs_symbol == START_SYMBOL)
					{
						break_process_actions = true;
						break  /*process_actions*/;
					}
					currentAction = prs->ntAction(stack[stateStackTop], lhs_symbol);
				}
				while (currentAction <= NUM_RULES);
				if (break_process_actions)
					break;
			}
		}
	}

	taking_actions = false; // indicate that we are done

	return;
}
