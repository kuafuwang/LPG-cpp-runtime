#pragma once
#include <vector>

#include "ObjectTuple.h"
struct ParseTable;
struct StateElement;
struct ConfigurationElement;

struct ConfigurationStack
{
     constexpr  static int TABLE_SIZE = 1021; // 1021 is a prime
     Array<ConfigurationElement*>  table;
     Tuple<ConfigurationElement*> configuration_stack;
     StateElement* state_root;
     int max_configuration_size,
        stacks_size,
        state_element_size;

    ParseTable* prs;

     ConfigurationStack(ParseTable* prs);

     StateElement* makeStateList(StateElement* parent, Array<int>& stack, int index, int stack_top);

     StateElement* findOrInsertStack(StateElement* root, Array<int>& stack, int index, int stack_top);

     bool findConfiguration(Array<int>& stack, int stack_top, int curtok);

    //
    //
    //
     void push(Array<int>& stack, int stack_top, int conflict_index, int curtok, int action_length);

    //
    //
    //
     ConfigurationElement* pop();

    //
    //
    //
     ConfigurationElement* top();

     int size();

     int maxConfigurationSize() { return max_configuration_size; }

    int numStateElements() { return state_element_size; }

    int stacksSize()
    {
        return stacks_size;
    }
};

