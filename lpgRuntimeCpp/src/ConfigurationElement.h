#pragma once
#include <vector>

#include "tuple.h"
struct StateElement;

struct ConfigurationElement
{
    ConfigurationElement* next=nullptr;

    StateElement* last_element = nullptr;
     int stack_top = 0,
               action_length=0,
               conflict_index=0,
               curtok=0,
               act=0;

    void retrieveStack(Array<int>& stack);
};

