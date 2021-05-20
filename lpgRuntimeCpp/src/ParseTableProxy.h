#pragma once

#include "ParseTable.h"

class ParseTableProxy
{
public:
   
	ParseTableProxy(ParseTable*);
	
    ParseTable* _prs;
    const  int ERROR_SYMBOL;
 
    const int SCOPE_UBOUND;
  
    const   int SCOPE_SIZE ;
   
    const  int MAX_NAME_LENGTH ;
    
    const    int NUM_STATES ;
  

    const  int NT_OFFSET ;


    const  int LA_STATE_OFFSET ;
  
    const  int MAX_LA;
  
    const   int NUM_RULES;
 
    const   int NUM_NONTERMINALS;
   
    const  int NUM_SYMBOLS;
   
    const   int START_STATE;
   
    const  int IDENTIFIER_SYMBOL;
   
    const   int EOFT_SYMBOL;
 
    const  int EOLT_SYMBOL;
  
    const  int ACCEPT_ACTION;
   
    const   int ERROR_ACTION;
    const   bool BACKTRACK;
    const   bool isValidForParser;
	
	int getStartSymbol() { return lhs(0); }
 
    const   char* _isNullable;
    bool isNullable(int index) { return _isNullable[index] != 0; }
    const   signed int* _prosthesesIndex;
    int prosthesesIndex(int index) { return _prosthesesIndex[index]; }
    const   char* _isKeyword;
    bool isKeyword(int index) { return _isKeyword[index] != 0; }
	
    const  signed int* _baseCheck;
    int baseCheck(int index) { return _baseCheck[index]; }
    const   signed int* _rhs;
    int rhs(int index) { return _rhs[index]; }
    const   signed int* _baseAction;
    int baseAction(int index) { return _baseAction[index]; }
    const   signed int* _lhs;
    int lhs(int index) { return _lhs[index]; }
    const  signed int* _termCheck;
    int termCheck(int index) { return _termCheck[index]; }
    const   signed int* _termAction;
    int termAction(int index) { return _termAction[index]; }
 

    int asb(int index) { return _prs->asb(index); }
    int asr(int index) { return _prs->asr(index); }
    int nasb(int index) { return _prs->nasb(index); }
    int nasr(int index) { return _prs->nasr(index); }
    int terminalIndex(int index) { return _prs->terminalIndex(index); }
    int nonterminalIndex(int index) { return _prs->nonterminalIndex(index); }
    int scopePrefix(int index) { return _prs->scopePrefix(index); }
    int scopeSuffix(int index) {  return _prs->scopeSuffix(index);
    }
    int scopeLhs(int index) { return _prs->scopeLhs(index); }
    int scopeLa(int index) { return _prs->scopeLa(index); }
    int scopeStateSet(int index) { return _prs->scopeStateSet(index); }
    int scopeRhs(int index) { return _prs->scopeRhs(index); }
    int scopeState(int index) { return _prs->scopeState(index); }
    int inSymb(int index) { return _prs->inSymb(index); }
    std::wstring name(int index) { return _prs->name(index); }
    int originalState(int state) { return _prs->originalState(state); }
    int asi(int state) { return _prs->asi(state); }
    int nasi(int state) { return _prs->nasi(state); }
    int inSymbol(int state) { return _prs->inSymbol(state); }

	
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

