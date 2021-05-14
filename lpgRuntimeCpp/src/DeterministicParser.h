#pragma once
#include "Stacks.h"
#include "tuple.h"



struct ParseTable;
struct RuleAction;
struct TokenStream;
struct Monitor;

struct DeterministicParser :
    public Stacks
{
	~DeterministicParser();
    bool taking_actions = false;
    int markerKind = 0;

    Monitor* monitor=nullptr;
	int START_STATE=0;
	int NUM_RULES = 0;
	int NT_OFFSET = 0;
	int LA_STATE_OFFSET = 0;
	int EOFT_SYMBOL = 0;
	int ACCEPT_ACTION = 0;
	int ERROR_ACTION = 0;
	int ERROR_SYMBOL = 0;

	int lastToken = 0;
    int  currentAction = 0;
   

	
    IntTuple* action = nullptr;

    TokenStream* tokStream=nullptr;
    ParseTable* prs = nullptr;
    RuleAction* ra = nullptr;;

    //
    // keep looking ahead until we compute a valid action
    //
    int lookahead(int act, int token);

    //
    // Compute the next action defined on act and sym. If this
    // action requires more lookahead, these lookahead symbols
    // are in the token stream beginning at the next token that
    // is yielded by peek().
    //
    int tAction(int act, int sym);

    //
    // Compute the next action defined on act and the next k tokens
    // whose types are stored in the array sym starting at location
    // index. The array sym is a circular buffer. If we reach the last
    // element of sym and we need more lookahead, we proceed to the
    // first element.
    // 
    // assert(sym.length == prs->getMaxLa());
    //
    int tAction(int act, std::vector<int>& sym, int index);

    //
    // Process reductions and continue...
    //
    void processReductions();

    //
    // The following functions can be invoked only when the parser is
    // processing actions. Thus, they can be invoked when the parser
    // was entered via the main entry point (parse()). When using
    // the incremental parser (via the entry point parse(int [], int)),
    // an Exception is thrown if any of these functions is invoked?
    // However, note that when parseActions() is invoked after successfully
    // parsing an input with the incremental parser, then they can be invoked.
    //
    int getCurrentRule();

    int getFirstToken();

    int getFirstToken(int i);

    int getLastToken();

    int getLastToken(int i);

    void setMonitor(Monitor* monitor) { this->monitor = monitor; }

    void reset();

	void reset(Monitor* monitor, TokenStream* tokStream);

    void reset(TokenStream* tokStream)
    {
        reset(nullptr, tokStream);
    }

    void reset(Monitor* monitor, TokenStream* tokStream, ParseTable* prs, RuleAction* ra);

        void reset(TokenStream* tokStream, ParseTable* prs, RuleAction* ra) 
    {
        reset(nullptr, tokStream, prs, ra);
    }

    DeterministicParser() = default;

    DeterministicParser(TokenStream* tokStream, ParseTable* prs, RuleAction* ra) 
    {
        reset(nullptr, tokStream, prs, ra);
    }

        DeterministicParser(Monitor* monitor, TokenStream* tokStream, ParseTable* prs, RuleAction* ra) 
    {
        reset(monitor, tokStream, prs, ra);
    }

        //
        //
        //
	Object* parse() 
    {
        return parseEntry(0);
    }

    //
    //
    //
    Object* parseEntry(int marker_kind);

    //
    // This method is invoked when using the parser in an incremental mode
    // using the entry point parse(int [], int).
    //
    void resetParser()
    {
        resetParserEntry(0);
    }

    //
    // This method is invoked when using the parser in an incremental mode
    // using the entry point parse(int [], int).
    //
    void resetParserEntry(int marker_kind);

    //
    // Find a state in the state stack that has a valid action on ERROR token
    //
    bool recoverableState(int state);

    //
    // Reset the parser at a point where it can legally process
    // the error token. If we can't do that, reset it to the beginning.
    //
    void errorReset();

    //
    // This is an incremental LALR(k) parser that takes as argument
    // the next k tokens in the input. If these k tokens are valid for
    // the current configuration, it advances past the first of the k
    // tokens and returns either:
    //
    //    . the last transition induced by that token 
    //    . the Accept action
    //
    // If the tokens are not valid, the initial configuration remains
    // unchanged and the Error action is returned.
    //
    // Note that it is the user's responsibility to start the parser in a
    // proper configuration by initially invoking the method resetParser
    // prior to invoking this function.
    //
    int parse(std::vector<int>& sym, int index);

    //
    // Now do the  parse of the input based on the actions in
    // the list "action" and the sequence of tokens in the token stream.
    //
    Object* parseActions();
};
