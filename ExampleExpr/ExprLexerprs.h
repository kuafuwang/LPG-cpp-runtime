#pragma once
 #include <string>
  #include "ExprLexersym.h"
#include "ParseTable.h"



struct ExprLexerprs :public ParseTable,public ExprLexersym {
             typedef  unsigned char byte;
     constexpr   static int ERROR_SYMBOL = 0;
     int getErrorSymbol() { return ERROR_SYMBOL; }

     constexpr   static int SCOPE_UBOUND = 0;
     int getScopeUbound() { return SCOPE_UBOUND; }

     constexpr   static int SCOPE_SIZE = 0;
     int getScopeSize() { return SCOPE_SIZE; }

     constexpr   static int MAX_NAME_LENGTH = 0;
     int getMaxNameLength() { return MAX_NAME_LENGTH; }

     constexpr   static int NUM_STATES = 4;
     int getNumStates() { return NUM_STATES; }

     constexpr   static int NT_OFFSET = 8;
     int getNtOffset() { return NT_OFFSET; }

     constexpr   static int LA_STATE_OFFSET = 30;
     int getLaStateOffset() { return LA_STATE_OFFSET; }

     constexpr   static int MAX_LA = 1;
     int getMaxLa() { return MAX_LA; }

     constexpr   static int NUM_RULES = 10;
     int getNumRules() { return NUM_RULES; }

     constexpr   static int NUM_NONTERMINALS = 4;
     int getNumNonterminals() { return NUM_NONTERMINALS; }

     constexpr   static int NUM_SYMBOLS = 12;
     int getNumSymbols() { return NUM_SYMBOLS; }

     constexpr   static int START_STATE = 11;
     int getStartState() { return START_STATE; }

     constexpr   static int IDENTIFIER_SYMBOL = 0;
     int getIdentifier_SYMBOL() { return IDENTIFIER_SYMBOL; }

     constexpr   static int EOFT_SYMBOL = 3;
     int getEoftSymbol() { return EOFT_SYMBOL; }

     constexpr   static int EOLT_SYMBOL = 5;
     int getEoltSymbol() { return EOLT_SYMBOL; }

     constexpr   static int ACCEPT_ACTION = 19;
     int getAcceptAction() { return ACCEPT_ACTION; }

     constexpr   static int ERROR_ACTION = 20;
     int getErrorAction() { return ERROR_ACTION; }

   constexpr   static bool BACKTRACK = false;
      bool getBacktrack() { return BACKTRACK; }

     int getStartSymbol() { return lhs(0); }
      bool isValidForParser() { return ExprLexersym::isValidForParser; }

inline static char _isNullable[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0,0
        };
      bool isNullable(int index) { return _isNullable[index] != 0; }
inline static signed char _prosthesesIndex[] = {0,
            2,3,4,1
        };
      int prosthesesIndex(int index) { return _prosthesesIndex[index]; }
inline static char _isKeyword[] = {0,
            0,0,0,0,0,0,0,0
        };
      bool isKeyword(int index) { return _isKeyword[index] != 0; }
inline static signed char _baseCheck[] = {0,
            1,1,1,1,1,1,1,2,1,2
        };
      int baseCheck(int index) { return _baseCheck[index]; }
inline      static signed char*  _rhs = _baseCheck;
     int rhs(int index) { return _rhs[index]; };
inline static signed char _baseAction[] = {
            1,1,1,1,1,1,1,2,2,3,
            3,1,15,17,16,9,10,13,20,20
        };
      int baseAction(int index) { return _baseAction[index]; }
 inline     static signed char * _lhs = _baseAction;
     int lhs(int index) { return _lhs[index]; };
inline static signed char _termCheck[] = {0,
            0,1,2,0,4,5,6,7,0,0,
            1,3,0,0,2,0,0,0,0,0,
            0
        };
      int termCheck(int index) { return _termCheck[index]; }
inline static signed char _termAction[] = {0,
            20,29,27,20,22,23,24,25,20,6,
            30,19,1,20,28
        };
      int termAction(int index) { return _termAction[index]; }
     int asb(int index) { return 0; }
     int asr(int index) { return 0; }
     int nasb(int index) { return 0; }
     int nasr(int index) { return 0; }
     int terminalIndex(int index) { return 0; }
     int nonterminalIndex(int index) { return 0; }
     int scopePrefix(int index) { return 0;}
     int scopeSuffix(int index) { return 0;}
     int scopeLhs(int index) { return 0;}
     int scopeLa(int index) { return 0;}
     int scopeStateSet(int index) { return 0;}
     int scopeRhs(int index) { return 0;}
     int scopeState(int index) { return 0;}
     int inSymb(int index) { return 0;}
      std::wstring name(int index) { return {}; }
     int originalState(int state) { return 0; }
     int asi(int state) { return 0; }
     int nasi(int state) { return 0; }
     int inSymbol(int state) { return 0; }

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
