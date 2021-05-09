#include "ErrorToken.h"


 ErrorToken::ErrorToken(IToken* firstToken, IToken* lastToken, IToken* errorToken, int startOffset, int endOffset,
	int kind):Token(firstToken->getIPrsStream(), startOffset, endOffset, kind)
{
	
	this->firstToken = firstToken;
	this->lastToken = lastToken;
	this->errorToken = errorToken;
}

IToken* ErrorToken::getFirstToken()
{
	return getFirstRealToken();
}

std::vector<IToken*> ErrorToken::getPrecedingAdjuncts()
{
	return firstToken->getPrecedingAdjuncts();
}

std::vector<IToken*> ErrorToken::getFollowingAdjuncts()
{
	return lastToken->getFollowingAdjuncts();
}

