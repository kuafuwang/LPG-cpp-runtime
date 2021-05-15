#pragma once
 #include <string>
  #include "ExprParsersym.h"

 struct ExprParserprs :public ParseTable,public ExprParsersym {
             typedef  unsigned char byte;
     constexpr   static int ERROR_SYMBOL = 7;
     int getErrorSymbol() { return ERROR_SYMBOL; }

     constexpr   static int SCOPE_UBOUND = 0;
     int getScopeUbound() { return SCOPE_UBOUND; }

     constexpr   static int SCOPE_SIZE = 1;
     int getScopeSize() { return SCOPE_SIZE; }

     constexpr   static int MAX_NAME_LENGTH = 14;
     int getMaxNameLength() { return MAX_NAME_LENGTH; }

     constexpr   static int NUM_STATES = 8;
     int getNumStates() { return NUM_STATES; }

     constexpr   static int NT_OFFSET = 7;
     int getNtOffset() { return NT_OFFSET; }

     constexpr   static int LA_STATE_OFFSET = 32;
     int getLaStateOffset() { return LA_STATE_OFFSET; }

     constexpr   static int MAX_LA = 1;
     int getMaxLa() { return MAX_LA; }

     constexpr   static int NUM_RULES = 6;
     int getNumRules() { return NUM_RULES; }

     constexpr   static int NUM_NONTERMINALS = 4;
     int getNumNonterminals() { return NUM_NONTERMINALS; }

     constexpr   static int NUM_SYMBOLS = 11;
     int getNumSymbols() { return NUM_SYMBOLS; }

     constexpr   static int START_STATE = 7;
     int getStartState() { return START_STATE; }

     constexpr   static int IDENTIFIER_SYMBOL = 0;
     int getIdentifier_SYMBOL() { return IDENTIFIER_SYMBOL; }

     constexpr   static int EOFT_SYMBOL = 6;
     int getEoftSymbol() { return EOFT_SYMBOL; }

     constexpr   static int EOLT_SYMBOL = 6;
     int getEoltSymbol() { return EOLT_SYMBOL; }

     constexpr   static int ACCEPT_ACTION = 25;
     int getAcceptAction() { return ACCEPT_ACTION; }

     constexpr   static int ERROR_ACTION = 26;
     int getErrorAction() { return ERROR_ACTION; }

   constexpr   static bool BACKTRACK = false;
      bool getBacktrack() { return BACKTRACK; }

     int getStartSymbol() { return lhs(0); }
      bool isValidForParser() { return ExprParsersym::isValidForParser; }

inline static char _isNullable[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0
        };
      bool isNullable(int index) { return _isNullable[index] != 0; }
inline static signed char _prosthesesIndex[] = {0,
            4,3,2,1
        };
      int prosthesesIndex(int index) { return _prosthesesIndex[index]; }
inline static char _isKeyword[] = {0,
            0,0,0,0,0,0,0
        };
      bool isKeyword(int index) { return _isKeyword[index] != 0; }
inline static signed char _baseCheck[] = {0,
            3,1,3,1,1,3,-1,0,0,0,
            -3,0,0,0,-5,0,0,-7,0,-2,
            -4,-6,-8,0
        };
      int baseCheck(int index) { return _baseCheck[index]; }
inline      static signed char*  _rhs = _baseCheck;
     int rhs(int index) { return _rhs[index]; };
inline static signed char _baseAction[] = {
            3,3,3,2,2,1,1,1,4,21,
            20,1,4,21,22,1,4,23,1,3,
            2,10,6,13,26,26
        };
      int baseAction(int index) { return _baseAction[index]; }
 inline     static signed char * _lhs = _baseAction;
     int lhs(int index) { return _lhs[index]; };
inline static signed char _termCheck[] = {0,
            0,0,1,3,4,0,1,6,0,0,
            5,2,0,0,2,0,0,0,0,0
        };
      int termCheck(int index) { return _termCheck[index]; }
inline static signed char _termAction[] = {0,
            26,26,15,31,11,26,15,25,26,2,
            32,18,1,26,18
        };
      int termAction(int index) { return _termAction[index]; }
inline static signed char _asb[] = {0,
            1,4,1,7,1,9,1,7
        };
      int asb(int index) { return _asb[index]; }
inline static signed char _asr[] = {0,
            3,4,0,6,1,0,6,2,1,5,
            0
        };
      int asr(int index) { return _asr[index]; }
inline static signed char _nasb[] = {0,
            1,4,1,4,1,4,3,4
        };
      int nasb(int index) { return _nasb[index]; }
inline static signed char _nasr[] = {0,
            2,0,1,0
        };
      int nasr(int index) { return _nasr[index]; }
inline static signed char _terminalIndex[] = {0,
            1,2,6,3,4,7,8
        };
      int terminalIndex(int index) { return _terminalIndex[index]; }
inline static signed char _nonterminalIndex[] = {0,
            11,10,9,0
        };
      int nonterminalIndex(int index) { return _nonterminalIndex[index]; }
inline static signed char _scopePrefix[] = {
            1
        };
      int scopePrefix(int index) { return _scopePrefix[index]; }
inline static signed char _scopeSuffix[] = {
            4
        };
      int scopeSuffix(int index) { return _scopeSuffix[index]; }
inline static signed char _scopeLhs[] = {
            1
        };
      int scopeLhs(int index) { return _scopeLhs[index]; }
inline static signed char _scopeLa[] = {
            5
        };
      int scopeLa(int index) { return _scopeLa[index]; }
inline static signed char _scopeStateSet[] = {
            1
        };
      int scopeStateSet(int index) { return _scopeStateSet[index]; }
inline static signed char _scopeRhs[] = {0,
            10,4,0,5,0
        };
      int scopeRhs(int index) { return _scopeRhs[index]; }
inline static signed char _scopeState[] = {0,
            18,15,11,7,0
        };
      int scopeState(int index) { return _scopeState[index]; }
inline static signed char _inSymb[] = {0,
            0,10,4,9,1,10,2,9
        };
      int inSymb(int index) { return _inSymb[index]; }
inline static std::wstring _name[] = {
            L"",
            L"+",
            L"*",
            L"(",
            L")",
            L"$empty",
            L"IntegerLiteral",
            L"EOF_TOKEN",
            L"ERROR_TOKEN",
            L"E",
            L"T",
            L"F"
        };
      std::wstring name(int index) { return _name[index]; }

     int originalState(int state) {
        return - _baseCheck[state];
    }
     int asi(int state) {
        return _asb[originalState(state)];
    }
     int nasi(int state) {
        return _nasb[originalState(state)];
    }
     int inSymbol(int state) {
        return _inSymb[originalState(state)];
    }

    /**
     * assert(! goto_default);
     */
     int ntAction(int state, int sym) {
        return _baseAction[state + sym];
    }

    /**
     * assert(! shift_default);
     */
     int tAction(int state, int sym) {
        int i = _baseAction[state],
            k = i + sym;
        return _termAction[_termCheck[k] == sym ? k : i];
    }
     int lookAhead(int la_state, int sym) {
        int k = la_state + sym;
        return _termAction[_termCheck[k] == sym ? k : la_state];
    }
};
