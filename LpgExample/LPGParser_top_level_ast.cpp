#include "LPGParser_top_level_ast.h"

void LPGParser_top_level_ast::option_specList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			option_spec* element = (option_spec*)getoption_specAt(i);
			if (! v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}

void LPGParser_top_level_ast::optionList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			option* element = (option*)getoptionAt(i);
			if (! v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}

void LPGParser_top_level_ast::defineSpecList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			defineSpec* element = (defineSpec*)getdefineSpecAt(i);
			if (! v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}

void LPGParser_top_level_ast::action_segmentList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			action_segment* element = (action_segment*)getaction_segmentAt(i);
			if (! v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}

void LPGParser_top_level_ast::drop_ruleList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			drop_rule* element = (drop_rule*)getdrop_ruleAt(i);
			if (! v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}

void LPGParser_top_level_ast::nameSpecList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			nameSpec* element = (nameSpec*)getnameSpecAt(i);
			if (! v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}

void LPGParser_top_level_ast::nonTermList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			nonTerm* element = (nonTerm*)getnonTermAt(i);
			if (! v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}
 void LPGParser_top_level_ast::ruleList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			rule* element = (rule*)getruleAt(i);
			if (!v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}
  void LPGParser_top_level_ast::terminalList::enter(Visitor* v)
 {
	 bool checkChildren = v->visit(this);
	 if (checkChildren)
	 {
		 for (int i = 0; i < size(); i++)
		 {
			 terminal* element = (terminal*)getterminalAt(i);
			 if (!v->preVisit(element)) continue;
			 element->enter(v);
			 v->postVisit(element);
		 }
	 }
	 v->endVisit(this);
 }

void LPGParser_top_level_ast::symbol_pairList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			symbol_pair* element = (symbol_pair*)getsymbol_pairAt(i);
			if (! v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}
 void LPGParser_top_level_ast::type_declarationsList::enter(Visitor* v)
{
	bool checkChildren = v->visit(this);
	if (checkChildren)
	{
		for (int i = 0; i < size(); i++)
		{
			type_declarations* element = (type_declarations*)gettype_declarationsAt(i);
			if (!v->preVisit(element)) continue;
			element->enter(v);
			v->postVisit(element);
		}
	}
	v->endVisit(this);
}