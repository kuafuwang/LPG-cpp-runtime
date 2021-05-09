#pragma once
#include "Token.h"
struct ErrorToken :
    public Token
{

    IToken* firstToken = nullptr;
    IToken* lastToken = nullptr;
    IToken* errorToken = nullptr;

    ErrorToken(IToken* firstToken, IToken* lastToken, IToken* errorToken, int startOffset, int endOffset, int kind);

    /**
     * @deprecated replaced by {@link #getFirstRealToken()}
     *
     */
    IToken* getFirstToken();

    IToken* getFirstRealToken()
    {
        return firstToken;
    }

    /**
     * @deprecated replaced by {@link #getLastRealToken()}
     *
     */
    IToken* getLastToken() { return getLastRealToken(); }
    IToken* getLastRealToken()
    {
        return lastToken;
    }

    IToken* getErrorToken()
    {
        return errorToken;
    }

    std::vector<IToken*> getPrecedingAdjuncts();
    std::vector<IToken*> getFollowingAdjuncts();
};

