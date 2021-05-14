#pragma once
#include <string>

struct ParseTable
{
	virtual ~ParseTable() = default;
	virtual int baseCheck(int index) = 0;

    virtual int rhs(int index) = 0;

    virtual int baseAction(int index) = 0;

    virtual int lhs(int index) = 0;

    virtual int termCheck(int index) = 0;

    virtual int termAction(int index) = 0;

    virtual int asb(int index) = 0;

    virtual int asr(int index) = 0;

    virtual int nasb(int index) = 0;

    virtual int nasr(int index) = 0;

    virtual int terminalIndex(int index) = 0;

    virtual int nonterminalIndex(int index) = 0;

    virtual int scopePrefix(int index) = 0;

    virtual int scopeSuffix(int index) = 0;

    virtual int scopeLhs(int index) = 0;

    virtual int scopeLa(int index) = 0;

    virtual int scopeStateSet(int index) = 0;

    virtual int scopeRhs(int index) = 0;

    virtual int scopeState(int index) = 0;

    virtual int inSymb(int index) = 0;

    virtual std::wstring name(int index) = 0;

    virtual int originalState(int state) = 0;

    virtual int asi(int state) = 0;

    virtual int nasi(int state) = 0;

    virtual int inSymbol(int state) = 0;

    virtual int ntAction(int state, int sym) = 0;

    virtual int tAction(int act, int sym) = 0;

    virtual int lookAhead(int act, int sym) = 0;

    virtual int getErrorSymbol() = 0;

    virtual int getScopeUbound() = 0;

    virtual int getScopeSize() = 0;

    virtual int getMaxNameLength() = 0;

    virtual int getNumStates() = 0;

    virtual int getNtOffset() = 0;

    virtual int getLaStateOffset() = 0;

    virtual int getMaxLa() = 0;

    virtual int getNumRules() = 0;

    virtual int getNumNonterminals() = 0;

    virtual int getNumSymbols() = 0;



    virtual int getStartState() = 0;

    virtual int getStartSymbol() = 0;

    virtual int getEoftSymbol() = 0;

    virtual int getEoltSymbol() = 0;

    virtual int getAcceptAction() = 0;

    virtual int getErrorAction() = 0;

    virtual bool isNullable(int symbol) = 0;

    virtual bool isValidForParser() = 0;

    virtual bool getBacktrack() = 0;
};
