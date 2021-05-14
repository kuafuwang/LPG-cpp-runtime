#pragma once
#include <vector>

#include "IToken.h"
#include "Object.h"
struct IToken;
struct IAstVisitor;

struct IAst:public   Object, virtual  IGetToken
{
	virtual ~IAst() = default;
	virtual IAst * getNextAst() = 0;
    virtual IAst* getParent() = 0;
   
    virtual std::vector<IToken*> getPrecedingAdjuncts() = 0;
    virtual  std::vector<IToken*> getFollowingAdjuncts() = 0;
    virtual  std::vector<IAst*> getChildren() = 0;
    virtual std::vector<IAst*> getAllChildren() = 0;
    virtual void accept(IAstVisitor* v) = 0;
	std::string to_utf8_string();
    virtual std::wstring toString() = 0;
    
};


