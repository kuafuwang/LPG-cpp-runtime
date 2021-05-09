#pragma once
#include "AbstractToken.h"
struct Token :
   public  AbstractToken
{
     Token() {}
     Token(int startOffset, int endOffset, int kind);

     Token(IPrsStream* iPrsStream, int startOffset, int endOffset, int kind);

    //
    // Return an iterator for the adjuncts that follow token i.
    //
     std::vector<IToken*> getFollowingAdjuncts();

     std::vector<IToken*> getPrecedingAdjuncts();
};

