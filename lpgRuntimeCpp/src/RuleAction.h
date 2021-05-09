#pragma once
struct RuleAction
{
	virtual ~RuleAction() = default;
	virtual   void ruleAction(int ruleNumber) = 0;
};