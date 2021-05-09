#pragma once
#include <vector>
struct IToken;
struct IAstVisitor;

struct IAst
{
	virtual ~IAst() = default;
	virtual IAst * getNextAst() = 0;
    virtual IAst* getParent() = 0;
    virtual IToken* getLeftIToken() = 0;
    virtual IToken* getRightIToken() = 0;
    virtual std::vector<IToken*> getPrecedingAdjuncts() = 0;
    virtual  std::vector<IToken*> getFollowingAdjuncts() = 0;
    virtual  std::vector<IAst*> getChildren() = 0;
    virtual std::vector<IAst*> getAllChildren() = 0;
    virtual void accept(IAstVisitor* v) = 0;
};


