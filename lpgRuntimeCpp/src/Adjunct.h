#pragma once
#include "AbstractToken.h"

struct
    Adjunct :public AbstractToken
{
    Adjunct() {}
    Adjunct(IPrsStream* prsStream, int startOffset, int endOffset, int kind);
    std::vector<IToken*> getFollowingAdjuncts();
    std::vector<IToken*> getPrecedingAdjuncts();
};

