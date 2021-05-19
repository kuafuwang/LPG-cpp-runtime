#pragma once
#include "AstPoolHolder.h"

struct RuleAction
{
	pool_holder _automatic_ast_pool;
	virtual ~RuleAction() = default;
	virtual   void ruleAction(int ruleNumber) = 0;
};
