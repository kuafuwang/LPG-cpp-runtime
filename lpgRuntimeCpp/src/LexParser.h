#pragma once
#include <vector>

#include "tuple.h"


struct Monitor;
struct RuleAction;
struct ParseTable;
struct ILexStream;

struct LexParser
{
    bool taking_actions = false;

    int START_STATE{},
        LA_STATE_OFFSET{},
        EOFT_SYMBOL{},
        ACCEPT_ACTION{},
        ERROR_ACTION{},
        START_SYMBOL{},
        NUM_RULES{};

    ILexStream* tokStream=nullptr;
    ParseTable* prs = nullptr;
    RuleAction* ra = nullptr;
    IntTuple* action= nullptr;
    

    void reset(ILexStream* tokStream);

    void reset(ILexStream* tokStream, ParseTable* prs, RuleAction* ra);

    LexParser() {}

    LexParser(ILexStream* tokStream, ParseTable* prs, RuleAction* ra);

    //
    // Stacks portion
    //
    int STACK_INCREMENT = 1024,
        stateStackTop{},
        stackLength = 0;
	
    std::vector<int>  stack;
    std::vector<int>  locationStack;
    std::vector<int>  tempStack;
	
    void reallocateStacks();

    int lastToken{},
        currentAction{},
        curtok{},
        starttok{},
        current_kind{};

    //
    // The following functions can be invoked only when the parser is
    // processing actions. Thus, they can be invoked when the parser
    // was entered via the main entry point (parseCharacters()). When using
    // the incremental parser (via the entry point scanNextToken(int [], int)),
    // they always return 0 when invoked. // TODO: Should we throw an Exception instead?
    // However, note that when parseActions() is invoked after successfully
    // parsing an input with the incremental parser, then they can be invoked.
    //
    int getFirstToken(int i);

    int getLastToken(int i);

    int getCurrentRule();

    //
    // Given a rule of the form     A ::= x1 x2 ... xn     n > 0
    //
    // the function getToken(i) yields the symbol xi, if xi is a terminal
    // or ti, if xi is a nonterminal that produced a string of the form
    // xi => ti w. If xi is a nullable nonterminal, then ti is the first
    //  symbol that immediately follows xi in the input (the lookahead).
    //
    int getToken(int i);
     void setSym1(int i) {}
     int getSym(int i) { return getLastToken(i); }

     int getFirstToken() { return starttok; }
     int getLastToken() { return lastToken; }

    void resetTokenStream(int i);

    //
    // Parse the input and create a stream of tokens.
    //
    void parseCharacters(int start_offset, int end_offset);

    void parseCharacters(Monitor* monitor, int start_offset, int end_offset);

    //
    //
    //
    int incrementalParseCharacters()
    {
        scanNextToken();

        return curtok;
    }

    //
    // Parse the input and create a stream of tokens.
    //
    void parseCharacters();

    void parseCharacters(Monitor* monitor);

    //
    // This function takes as argument a configuration ([stack, stackTop], [tokStream, curtok])
    // and determines whether or not curtok can be validly parsed in this configuration. If so,
    // it parses curtok and returns the  shift or shift-reduce action on it. Otherwise, it
    // leaves the configuration unchanged and returns ERROR_ACTION.
    //
    void parseNextCharacter(int token, int kind);

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

    bool scanNextToken();

    bool scanNextToken(int start_offset);

    bool lexNextToken(int end_offset);

    //
    // This function takes as argument a configuration ([stack, stackTop], [tokStream, curtok])
    // and determines whether or not the reduce action the curtok can be validly parsed in this
    // configuration.
    //
    int lexNextCharacter(int act, int kind);

    //
    // Now do the  parse of the input based on the actions in
    // the list "action" and the sequence of tokens in the token stream.
    //
    void parseActions();
};

