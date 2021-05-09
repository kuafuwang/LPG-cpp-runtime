#pragma once
#include <vector>

#include "tuple.h"

struct Object
{
	
};

struct Stacks
{
    int STACK_INCREMENT = 1024,
        stateStackTop = 0;

    Array< int> stateStack;
    Array< int>         locationStack;
    Array< Object* >  parseStack;

    //
    // Given a rule of the form     A ::= x1 x2 ... xn     n > 0
    //
    // the function GETTOKEN(i) yields the symbol xi, if xi is a terminal
    // or ti, if xi is a nonterminal that produced a string of the form
    // xi => ti w.
    //
    int getToken(int i)
    {
        return locationStack[stateStackTop + (i - 1)];
    }

    //
    // Given a rule of the form     A ::= x1 x2 ... xn     n > 0
    //
    // The function GETSYM(i) yields the AST subtree associated with symbol
    // xi. NOTE that if xi is a terminal, GETSYM(i) is undefined ! (However,
    // see token_action below.)
    //
    // setSYM1(Object ast) is a function that allows us to assign an AST
    // tree to GETSYM(1).
    //
    Object* getSym(int i) { return parseStack[stateStackTop + (i - 1)]; }
    void setSym1(Object* ast) { parseStack[stateStackTop] = ast; }

    //
    // Allocate or reallocate all the stacks. Their sizes should always be the same.
    //
    void reallocateStacks()
    {
        int old_stack_length = (stateStack.Size());
    	
        int   stack_length = old_stack_length + STACK_INCREMENT;
        stateStack.Resize(stack_length);
        locationStack.Resize(stack_length);
        parseStack.Resize(stack_length);
        return;
    }

    //
    // Allocate or reallocate the state stack only.
    //
    void reallocateStateStack()
    {
        int old_stack_length = (stateStack.Size());
        int   stack_length = old_stack_length + STACK_INCREMENT;
        stateStack.Resize(stack_length);
    
    }

    //
    // Allocate location and parse stacks using the size of the state stack.
    //
    void allocateOtherStacks()
    {
        locationStack.Memset(0);
        locationStack.Resize(stateStack.Size());
        parseStack.Memset(0);
        parseStack.Resize(stateStack.Size());
    }
};
