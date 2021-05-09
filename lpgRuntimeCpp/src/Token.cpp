#include "Token.h"

#include "IPrsStream.h"

Token::Token(int startOffset, int endOffset, int kind):AbstractToken(nullptr, startOffset, endOffset, kind)
{

}

Token::Token(IPrsStream* iPrsStream, int startOffset, int endOffset, int kind) : AbstractToken(iPrsStream, startOffset, endOffset, kind)
{
	
}

std::vector<IToken*> Token::getFollowingAdjuncts()
{
	return getIPrsStream()->getFollowingAdjuncts(getTokenIndex());
}

std::vector<IToken*> Token::getPrecedingAdjuncts()
{
	return getIPrsStream()->getPrecedingAdjuncts(getTokenIndex());
}
