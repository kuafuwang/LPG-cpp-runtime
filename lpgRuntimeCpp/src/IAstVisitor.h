#pragma once
//struct IAst;
#include "IAst.h"
struct IAstVisitor
{
	virtual ~IAstVisitor() = default;
	virtual  bool preVisit(IAst* element) = 0;
	virtual void postVisit(IAst* element) = 0;
};
