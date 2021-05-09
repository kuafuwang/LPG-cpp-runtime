#include "ConfigurationStack.h"

#include "ConfigurationElement.h"
#include "ParseTable.h"
#include "StateElement.h"

ConfigurationStack::ConfigurationStack(ParseTable* prs): configuration_stack(1 << 12), state_element_size(0), table(TABLE_SIZE)
{
	
	this->prs = prs;

	state_element_size++;

	state_root = new StateElement();
	state_root->parent = nullptr;
	state_root->siblings = nullptr;
	state_root->children = nullptr;
	state_root->number = prs->getStartState();
}

StateElement* ConfigurationStack::makeStateList(StateElement* parent, Array<int>& stack, int index, int stack_top)
{
	for (int i = index; i <= stack_top; i++)
	{
		state_element_size++;

		StateElement* state = new StateElement();
		state->number = stack[i];
		state->parent = parent;
		state->children = nullptr;
		state->siblings = nullptr;

		parent->children = state;
		parent = state;
	}

	return parent;
}

StateElement* ConfigurationStack::findOrInsertStack(StateElement* root, Array<int>& stack, int index,
                                                    int stack_top)
{
	int state_number = stack[index];
	for (StateElement* p = root; p != nullptr; p = p->siblings)
	{
		if (p->number == state_number)
			return (index == stack_top
				        ? p
				        : p->children == nullptr
				        ? makeStateList(p, stack, index + 1, stack_top)
				        : findOrInsertStack(p->children, stack, index + 1, stack_top));
	}

	state_element_size++;

	StateElement* node = new StateElement();
	node->number = state_number;
	node->parent = root->parent;
	node->children = nullptr;
	node->siblings = root->siblings;
	root->siblings = node;

	return (index == stack_top ? node : makeStateList(node, stack, index + 1, stack_top));
}

bool ConfigurationStack::findConfiguration(Array<int>& stack, int stack_top, int curtok)
{
	StateElement* last_element = findOrInsertStack(state_root, stack, 0, stack_top);
	int hash_address = curtok % TABLE_SIZE;
	for (ConfigurationElement* configuration = table[hash_address]; configuration != nullptr; configuration = configuration
	     ->next)
	{
		if (configuration->curtok == curtok && last_element == configuration->last_element)
			return true;
	}

	return false;
}

void ConfigurationStack::push(Array<int>& stack, int stack_top, int conflict_index, int curtok, int action_length)
{
	ConfigurationElement* configuration = new ConfigurationElement();
	int hash_address = curtok % TABLE_SIZE;
	configuration->next = table[hash_address];
	table[hash_address] = configuration;
	max_configuration_size++; // keep track of number of configurations

	configuration->stack_top = stack_top;
	stacks_size += (stack_top + 1); // keep track of number of stack elements processed
	configuration->last_element = findOrInsertStack(state_root, stack, 0, stack_top);
	configuration->conflict_index = conflict_index;
	configuration->curtok = curtok;
	configuration->action_length = action_length;

	configuration_stack.add(configuration);

	return;
}

ConfigurationElement* ConfigurationStack::pop()
{
	ConfigurationElement* configuration = nullptr;
	if (configuration_stack.size() > 0)
	{
		int index = configuration_stack.size() - 1;
		configuration = (ConfigurationElement*)configuration_stack.get(index);
		configuration->act = prs->baseAction(configuration->conflict_index++);
		if (prs->baseAction(configuration->conflict_index) == 0)
			configuration_stack.reset(index);
	}

	return configuration;
}

ConfigurationElement* ConfigurationStack::top()
{
	ConfigurationElement* configuration = nullptr;
	if (configuration_stack.size() > 0)
	{
		int index = configuration_stack.Length() - 1;
		configuration = (ConfigurationElement*)configuration_stack.get(index);
		configuration->act = prs->baseAction(configuration->conflict_index);
	}

	return configuration;
}

int ConfigurationStack::size()
{
	return configuration_stack.size();
}
