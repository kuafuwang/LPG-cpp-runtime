#pragma once
#include "ObjectTuple.h"
#include "Stacks.h"

class ParseTableProxy;
struct IPrsStream;
struct RuleAction;
struct ParseTable;
struct TokenStream;
struct Monitor;

struct 
BacktrackingParser :
    public Stacks
{
     Monitor* monitor;
    int START_STATE;
    int NUM_RULES;
    int NT_OFFSET;
    int LA_STATE_OFFSET;
    int EOFT_SYMBOL;
    int ERROR_SYMBOL;
    int ACCEPT_ACTION;
    int ERROR_ACTION;

    int lastToken,
        currentAction;
    TokenStream* tokStream = nullptr;
    ParseTableProxy* prs = nullptr;
    RuleAction* ra = nullptr;
    IntSegmentedTuple* action = new IntSegmentedTuple(10, 1024); // IntTuple(1 << 20),
    std::shared_ptr< IntTuple>  tokens = nullptr;
    Array<int> actionStack;
    bool skipTokens = false; // true if error productions are used to skip tokens

   //
   // A starting marker indicates that we are dealing with an entry point
   // for a given nonterminal. We need to execute a shift action on the
   // marker in order to parse the entry point in question.
   //
    int markerTokenIndex = 0;
    int getMarkerToken(int marker_kind, int start_token_index);

    //
    // Override the getToken function in Stacks.
    //
    int getToken(int i);

    int getCurrentRule();
    int getFirstToken();
    int getFirstToken(int i);
    int getLastToken();

    int getLastToken(int i);

    void setMonitor(Monitor* monitor);

    void reset();

    void reset(Monitor* monitor, TokenStream* tokStream);


    void reset(TokenStream* tokStream);


    void reset(Monitor* monitor, TokenStream* tokStream, ParseTable* prs, RuleAction* ra);

     void reset(TokenStream* tokStream, ParseTable* prs, RuleAction* ra)
    {
        reset(nullptr, tokStream, prs, ra);
    }
    ~BacktrackingParser();
    BacktrackingParser();

    BacktrackingParser(TokenStream* tokStream, ParseTable* prs, RuleAction* ra);

    BacktrackingParser(Monitor* monitor, TokenStream* tokStream, ParseTable* prs, RuleAction* ra);

        //
        // Allocate or reallocate all the stacks. Their sizes should always be the same.
        //
    void reallocateOtherStacks(int start_token_index);

    //
    // Always attempt to recover
    //
    Object* fuzzyParse();

    //
    // Recover up to max_error_count times and then quit
    //
    Object* fuzzyParse(int max_error_count);

    //
    // Always attempt to recover
    //
    Object* fuzzyParseEntry(int marker_kind);

    //
    //
    //
     struct ErrorPair {
        ErrorPair(int scope_index, int error_token);
        int scopeIndex,
            errorToken;
    };
    std::shared_ptr<std::vector<ErrorPair>>  errors;
    void reportErrors();

    void addRecoveryError(int scope_index, int error_index);

    //
    //
    //
    Object* fuzzyParseEntry(int marker_kind, int max_error_count);

    //
    // Parse without attempting any Error token recovery
    //
    Object* parse();

    //
    // Parse input allowing up to max_error_count Error token recoveries.
    // When max_error_count is 0, no Error token recoveries occur.
    // When max_error is > 0, it limits the number of Error token recoveries.
    // When max_error is < 0, the number of error token recoveries is unlimited.
    // Also, such recoveries only require one token to be parsed beyond the recovery point.
    // (normally two tokens beyond the recovery point must be parsed)
    // Thus, a negative max_error_count should be used when error productions are used to 
    // skip tokens.
    //
    Object* parse(int max_error_count);

    //
    // Parse without attempting any Error token recovery
    //
    Object* parseEntry(int marker_kind);

    //
    // Parse input allowing up to max_error_count Error token recoveries.
    // When max_error_count is 0, no Error token recoveries occur.
    // When max_error is > 0, it limits the number of Error token recoveries.
    // When max_error is < 0, the number of error token recoveries is unlimited.
    // Also, such recoveries only require one token to be parsed beyond the recovery point.
    // (normally two tokens beyond the recovery point must be parsed)
    // Thus, a negative max_error_count should be used when error productions are used to 
    // skip tokens.
    //
    Object* parseEntry(int marker_kind, int max_error_count);

    //
    // Process reductions and continue...
    //
    void process_reductions();

    //
    // Now do the final parse of the input based on the actions in
    // the list "action" and the sequence of tokens in list "tokens".
    //
    Object* parseActions(int marker_kind);

    //
    // Process reductions and continue...
    //
    int process_backtrack_reductions(int act);

    //
    // This method is intended to be used by the type RecoveryParser.
    // Note that the action tuple passed here must be the same action
    // tuple that was passed down to RecoveryParser. It is passed back
    // to this method as documention.
    //
    int backtrackParse(Array<int>& stack_arg, int stack_top, IntSegmentedTuple* action_arg, int initial_token);

    //
    // Parse the input until either the parse completes successfully or
    // an error is encountered. This function returns an integer that
    // represents the last action that was executed by the parser. If
    // the parse was succesful, then the tuple "action" contains the
    // successful sequence of actions that was executed.
    //
    int backtrackParse(IntSegmentedTuple* action_arg, int initial_token);

    void backtrackParseUpToError(int initial_token, int error_token);

    bool repairable(int error_token);

    bool recoverableState(int state);

    int findRecoveryStateIndex(int start_index);

    int errorRepair(IPrsStream* stream, int recovery_token, int error_token);

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
};


