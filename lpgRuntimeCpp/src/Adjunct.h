#pragma once
#include "AbstractToken.h"

struct
    Adjunct :public AbstractToken
{
    Adjunct() {}
    Adjunct(IPrsStream* prsStream, int startOffset, int endOffset, int kind):AbstractToken(prsStream, startOffset, endOffset, kind)
    {
      
    }
    std::vector<IToken*>  getFollowingAdjuncts() { return {}; }
    std::vector<IToken*> getPrecedingAdjuncts() { return {}; }
};
