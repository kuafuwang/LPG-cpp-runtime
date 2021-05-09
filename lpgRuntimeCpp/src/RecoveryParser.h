#pragma once
#include "diagnose.h"
struct IPrsStream;
struct BacktrackingParser;

struct RecoveryParser :
    public DiagnoseParser
{

    
        BacktrackingParser* parser;
        IntSegmentedTuple action;
        IntTuple tokens;
        Array<int> actionStack;
        PrimaryRepairInfo scope_repair;

        //
        //
        //
    

        //
        // maxErrors is the maximum number of errors to be repaired
        // maxTime is the maximum amount of time allowed for diagnosing
        // but at least one error must be diagnosed 
        //
        RecoveryParser(BacktrackingParser* parser, IntSegmentedTuple action, IntTuple tokens, IPrsStream* tokStream,
                       ParseTable* prs, Monitor* monitor = nullptr, int maxErrors = 0, long maxTime = 0);

        void reallocateStacks();

        int recover(int marker_token, int error_token);

        //void TemporaryErrorDump()
        //{
        //int prevStackTop = stateStackTop;
        //System.arraycopy(stateStack, 0, prevStack, 0, stateStackTop + 1); // save StateStack
        //RepairCandidate candidate = primaryDiagnosis(scope_repair);
        //stateStackTop = prevStackTop;
        //System.arraycopy(prevStack, 0, stateStack, 0, stateStackTop + 1); // restore StateStack
        //}

            //
            // Given the configuration consisting of the states in stateStack
            // and the sequence of tokens (current_kind, followed by the tokens
            // in tokStream), fixError parses up to error_token in the tokStream
            // recovers, if possible, from that error and returns the result.
            // While doing this, it also computes the location_stack information
            // and the sequence of actions that matches up with the result that
            // it returns.
            //
        bool fixError(int start_token, int error_token);

        //
        //
        //
        void acceptRecovery(int error_token);

        //
        //
        //
        bool completeScope(IntSegmentedTuple action, int scope_rhs_index);
};

