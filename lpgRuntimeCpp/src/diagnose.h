#ifndef diagnose_INCLUDED
#define diagnose_INCLUDED


#include "ParseErrorCodes.h"
#include "ParseTable.h"
#include "tuple.h"
#include <limits>

#include "ConfigurationStack.h"
#include "TokenStream.h"
#include "TokenStream.h"
struct ParseTable;

struct Monitor;


struct DiagnoseParser :public ParseErrorCodes
{
    //
   //
   //
    struct RepairCandidate
    {
        int symbol=0,
            location=0;
    };

    struct PrimaryRepairInfo
    {
        int distance,
            misspellIndex,
            code,
            bufferPosition,
            symbol;

        PrimaryRepairInfo() : distance(0), misspellIndex(0), code(0), bufferPosition(0), symbol(0)
        {
        }

        PrimaryRepairInfo(PrimaryRepairInfo& clone)
        {
            copy(clone);
        }

        void copy(PrimaryRepairInfo& clone)
        {
            this->distance = clone.distance;
            this->misspellIndex = clone.misspellIndex;
            this->code = clone.code;
            this->bufferPosition = clone.bufferPosition;
            this->symbol = clone.symbol;

            return;
        }
    };

    struct SecondaryRepairInfo
    {
        int code,
            distance,
            bufferPosition,
            stackPosition,
            numDeletions,
            symbol;

        bool recoveryOnNextStack;
    };

    struct StateInfo
    {
        int state = 0,
            next = 0;
        StateInfo();
        StateInfo(int state, int next)
        {
            this->state = state;
            this->next = next;
        }
    };

	
    Monitor* monitor = nullptr;
    TokenStream* tokStream = nullptr;
    ParseTable* prs = nullptr;
    int ERROR_SYMBOL,
        SCOPE_SIZE,
        MAX_NAME_LENGTH,
        NT_OFFSET,
        LA_STATE_OFFSET,
        NUM_RULES,
        NUM_SYMBOLS,
        START_STATE,
        EOFT_SYMBOL,
        EOLT_SYMBOL,
        ACCEPT_ACTION,
        ERROR_ACTION;

   

    int maxErrors;

    long maxTime;

    void setMonitor(Monitor* monitor) { this->monitor = monitor; }

    //
    // maxErrors is the maximum number of errors to be repaired
    // maxTime is the maximum amount of time allowed for diagnosing
    // but at least one error must be diagnosed 
    //
    DiagnoseParser(TokenStream* tokStream, ParseTable* prs, Monitor* monitor=nullptr, int maxErrors=0, long maxTime=0);

    static constexpr  int STACK_INCREMENT = 256;

    static constexpr int BUFF_UBOUND = 31,
        BUFF_SIZE = 32,
        MAX_DISTANCE = 30,
        MIN_DISTANCE = 3;
        static constexpr int  INFINITY_ = std::numeric_limits<int>::max(); // should be much bigger than MAX_DISTANCE !!!


    int rhs(int index) { return prs->rhs(index); }

    int baseAction(int index) { return prs->baseAction(index); }

    int baseCheck(int index) { return prs->baseCheck(index); }

    int lhs(int index) { return prs->lhs(index); }

    int termCheck(int index) { return prs->termCheck(index); }

    int termAction(int index) { return prs->termAction(index); }

    int asb(int index) { return prs->asb(index); }

    int asr(int index) { return prs->asr(index); }

    int nasb(int index) { return prs->nasb(index); }

    int nasr(int index) { return prs->nasr(index); }

    int terminalIndex(int index) { return prs->terminalIndex(index); }

    int nonterminalIndex(int index) { return prs->nonterminalIndex(index); }

    int symbolIndex(int index)
    {
        return index > NT_OFFSET
            ? nonterminalIndex(index - NT_OFFSET)
            : terminalIndex(index);
    }

    int scopePrefix(int index) { return prs->scopePrefix(index); }

    int scopeSuffix(int index) { return prs->scopeSuffix(index); }

    int scopeLhs(int index) { return prs->scopeLhs(index); }

    int scopeLa(int index) { return prs->scopeLa(index); }

    int scopeStateSet(int index) { return prs->scopeStateSet(index); }

    int scopeRhs(int index) { return prs->scopeRhs(index); }

    int scopeState(int index) { return prs->scopeState(index); }

    int inSymb(int index) { return prs->inSymb(index); }

    std::wstring name(int index) { return prs->name(index); }

    int originalState(int state) { return prs->originalState(state); }

    int asi(int state) { return prs->asi(state); }

    int nasi(int state) { return prs->nasi(state); }

    int inSymbol(int state) { return prs->inSymbol(state); }

    int ntAction(int state, int sym) { return prs->ntAction(state, sym); }

    bool isNullable(int symbol) { return prs->isNullable(symbol); }

    Array<int> locationStack;


    //
//
//
    int stateStackTop,
        tempStackTop,
        prevStackTop,
        nextStackTop,
        scopeStackTop;

    Array<int> stateStack,
        tempStack,
        nextStack,
        prevStack,
        scopeIndex,
        scopePosition;
	

    Array<int> buffer;
    std::shared_ptr<ConfigurationStack>  main_configuration_stack;

    static constexpr  int NIL = -1;
	
    Array<int> list,
        stateSeen; // this variable is managed entirely by the function "scope_trial"  stateSeen;

    int statePoolTop;
    Tuple < StateInfo> statePool;

   


    void reallocateStacks();


    //
    //
    //
    void diagnose()
    {
        diagnoseEntry(0, 0);
    }

    void diagnose(int error_token)
    {
        diagnoseEntry(0, error_token);
    }

    //
    //
    //
    void diagnoseEntry(int marker_kind)
    {
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

        int error_token = parseForError(current_kind);

        //
        // If an error was found, start the diagnosis and recovery.
        //
        if (error_token != 0)
            diagnoseEntry(marker_kind, error_token);

        return;
    }

    void diagnoseEntry(int marker_kind, int error_token);


    //
    // Given the configuration consisting of the states in tempStack
    // and the sequence of tokens (current_kind, followed by the tokens
    // in tokStream), keep parsing until either the parse completes
    // successfully or it encounters an error. If the parse is not
    // succesful, we return the farthest token on which an error was
    // encountered. Otherwise, we return 0.
    //
    int parseForError(int current_kind);

    //
    // Given the configuration consisting of the states in tempStack
    // and the sequence of tokens (current_kind, followed by the tokens
    // in tokStream), parse up to error_token in the tokStream and store
    // all the parsing actions executed in the "action" tuple.
    //
    void parseUpToError(IntTuple& action, int current_kind, int error_token);

    //
    // Try to parse until first_symbol and all tokens in BUFFER have
    // been consumed, or an error is encountered. Return the number
    // of tokens that were expended before the parse blocked.
    //
    int parseCheck(Array<int>& stack, int stack_top, int first_symbol, int buffer_position);


    //
    //  This routine is invoked when an error is encountered.  It
    // tries to diagnose the error and recover from it.  If it is
    // successful, the state stack, the current token and the buffer
    // are readjusted; i.e., after a successful recovery,
    // state_stack_top points to the location in the state stack
    // that contains the state on which to recover; current_token
    // identifies the symbol on which to recover.
    //
    // Up to three configurations may be available when this routine
    // is invoked. PREV_STACK may contain the sequence of states
    // preceding any action on prevtok, STACK always contains the
    // sequence of states preceding any action on current_token, and
    // NEXT_STACK may contain the sequence of states preceding any
    // action on the successor of current_token.
    //
    RepairCandidate errorRecovery(int error_token);

    //
    // This function tries primary and scope recovery on each
    // available configuration.  If a successful recovery is found
    // and no secondary phase recovery can do better, a diagnosis is
    // issued, the configuration is updated and the function returns
    // "true".  Otherwise, it returns "false".
    //
    RepairCandidate primaryPhase(int error_token);


    //
    //  This function checks whether or not a given state has a
    // candidate, whose string representaion is a merging of the two
    // tokens at positions buffer_position and buffer_position+1 in
    // the buffer.  If so, it returns the candidate in question;
    // otherwise it returns 0.
    //
    int mergeCandidate(int state, int buffer_position);


    //
    // This procedure takes as arguments a parsing configuration
    // consisting of a state stack (stack and stack_top) and a fixed
    // number of input tokens (starting at buffer_position) in the
    // input BUFFER; and some reference arguments: repair_code,
    // distance, misspell_index, candidate, and stack_position
    // which it sets based on the best possible recovery that it
    // finds in the given configuration.  The effectiveness of a
    // a repair is judged based on two criteria:
    //
    //       1) the number of tokens that can be parsed after the repair
    //              is applied: distance.
    //       2) how close to perfection is the candidate that is chosen:
    //              misspell_index.
    //
    // When this procedure is entered, distance, misspell_index and
    // repair_code are assumed to be initialized.
    //
    void checkPrimaryDistance(PrimaryRepairInfo& repair, Array<int>& stck, int stack_top);


    //
    // This procedure is invoked to issue a diagnostic message and
    // adjust the input buffer.  The recovery in question is either
    // the insertion of one or more scopes, the merging of the error
    // token with its successor, the deletion of the error token,
    // the insertion of a single token in front of the error token
    // or the substitution of another token for the error token.
    //
    RepairCandidate primaryDiagnosis(PrimaryRepairInfo& repair);


    //
    // This function takes as parameter an integer STACK_TOP that
    // points to a STACK element containing the state on which a
    // primary recovery will be made; the terminal candidate on which
    // to recover; and an integer: buffer_position, which points to
    // the position of the next input token in the BUFFER.  The
    // parser is simulated until a shift (or shift-reduce) action
    // is computed on the candidate.  Then we proceed to compute the
    // the name index of the highest level nonterminal that can
    // directly or indirectly produce the candidate.
    //
    int getTermIndex(Array<int>& stck, int stack_top, int tok, int buffer_position);

    //
    // This function takes as parameter a starting state number:
    // start, a nonterminal symbol, A (candidate), and an integer,std::vector<int>&
    // buffer_position,  which points to the position of the next
    // input token in the BUFFER.
    // It returns the highest level non-terminal B such that
    // B =>*rm A.  I.e., there does not exists a nonterminal C such
    // that C =>+rm B. (Recall that for an LALR(k) grammar if
    // C =>+rm B, it cannot be the case that B =>+rm C)
    //
    int getNtermIndex(int start, int sym, int buffer_position);

    //
    //  Check whether or not there is a high probability that a
    // given string is a misspelling of another.
    // Certain singleton symbols (such as ":" and ";") are also
    // considered to be misspellings of each other.
    //
    int misspell(int sym, int tok);

    void scopeTrial(PrimaryRepairInfo& repair, Array<int>& stack, int stack_top);

    void scopeTrialCheck(PrimaryRepairInfo& repair, Array<int>& stack, int stack_top, int indx);

    //
    // This function computes the ParseCheck distance for the best
    // possible secondary recovery for a given configuration that
    // either deletes none or only one symbol in the forward context.
    // If the recovery found is more effective than the best primary
    // recovery previously computed, then the function returns true.
    // Only misplacement, scope and manual recoveries are attempted;
    // simple insertion or substitution of a nonterminal are tried
    // in CHECK_PRIMARY_DISTANCE as part of primary recovery.
    //
    bool secondaryCheck(Array<int>& stack, int stack_top, int buffer_position, PrimaryRepairInfo& repair);


    //
    // Secondary_phase is a bool function that checks whether or
    // not some form of secondary recovery is applicable to one of
    // the error configurations. First, if "next_stack" is available,
    // misplacement and secondary recoveries are attempted on it.
    // Then, in any case, these recoveries are attempted on "stack".
    // If a successful recovery is found, a diagnosis is issued, the
    // configuration is updated and the function returns "true".
    // Otherwise, the function returns false.
    //
    RepairCandidate secondaryPhase(int error_token);


    //
    // This bool function checks whether or not a given
    // configuration yields a better misplacement recovery than
    // the best misplacement recovery computed previously.
    //
    void misplacementRecovery(SecondaryRepairInfo& repair, Array<int>& stack, int stack_top, int last_index,
                              bool stack_flag);


    //
    // This function checks whether or not a given
    // configuration yields a better secondary recovery than the
    // best misplacement recovery computed previously.
    //
    void secondaryRecovery(SecondaryRepairInfo& repair, Array<int>& stack, int stack_top, int last_index,
                           bool stack_flag);


    //
    // This procedure is invoked to issue a secondary diagnosis and
    // adjust the input buffer.  The recovery in question is either
    // an automatic scope recovery, a manual scope recovery, a
    // secondary substitution or a secondary deletion.
    //
    void secondaryDiagnosis(SecondaryRepairInfo& repair);


    //
    // This method is invoked by an LPG PARSER or a semantic
    // routine to process an error message.
    //
    void emitError(int msg_code,
                   int name_index,
                   int left_token,
                   int right_token,
                   int scope_name_index);


    void emitError(int msgCode, int nameIndex, int leftToken, int rightToken)
    {
        emitError(msgCode, nameIndex, leftToken, rightToken, 0);
    }

    //
    // keep looking ahead until we compute a valid action
    //
    int lookahead(int act, int token)
    {
        act = prs->lookAhead(act - LA_STATE_OFFSET, tokStream->getKind(token));
        return (act > LA_STATE_OFFSET
            ? lookahead(act, tokStream->getNext(token))
            : act);
    }

    //
    // Compute the next action defined on act and sym. If this
    // action requires more lookahead, these lookahead symbols
    // are in the token stream beginning at the next token that
    // is yielded by peek().
    //
    int tAction(int act, int sym)
    {
        act = prs->tAction(act, sym);
        return  (act > LA_STATE_OFFSET
            ? lookahead(act, tokStream->peek())
            : act);
    }
};

#endif
