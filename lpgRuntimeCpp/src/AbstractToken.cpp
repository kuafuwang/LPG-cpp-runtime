#include "AbstractToken.h"

#include "Exception.h"
#include "ILexStream.h"
#include "IPrsStream.h"
#include <typeinfo>

#include "Adjunct.h"
#include "LexStream.h"

AbstractToken::AbstractToken(IPrsStream* iPrsStream, int startOffset, int endOffset, int kind)
{
	this->iPrsStream = iPrsStream;
	this->startOffset = startOffset;
	this->endOffset = endOffset;
	this->kind = kind;
}

int AbstractToken::getKind()
{
	return kind;
}

void AbstractToken::setKind(int kind)
{
	this->kind = kind;
}

int AbstractToken::getStartOffset()
{
	return startOffset;
}

void AbstractToken::setStartOffset(int start_offset)
{
	this->startOffset = start_offset;
}

int AbstractToken::getEndOffset()
{
	return endOffset;
}

void AbstractToken::setEndOffset(int endOffset)
{
	this->endOffset = endOffset;
}

int AbstractToken::getTokenIndex()
{
	return tokenIndex;
}

void AbstractToken::setTokenIndex(int tokenIndex)
{
	this->tokenIndex = tokenIndex;
}

void AbstractToken::setAdjunctIndex(int adjunctIndex)
{
	this->adjunctIndex = adjunctIndex;
}

int AbstractToken::getAdjunctIndex()
{
	return adjunctIndex;
}

IPrsStream* AbstractToken::getIPrsStream()
{
	return iPrsStream;
}

ILexStream* AbstractToken::getILexStream()
{
	return iPrsStream == nullptr ? nullptr : iPrsStream->getILexStream();
}

int AbstractToken::getLine()
{
	return (iPrsStream == nullptr ? 0 : iPrsStream->getILexStream()->getLineNumberOfCharAt(startOffset));
}

int AbstractToken::getColumn()
{
	return (iPrsStream == nullptr ? 0 : iPrsStream->getILexStream()->getColumnOfCharAt(startOffset));
}

int AbstractToken::getEndLine()
{
	return (iPrsStream == nullptr ? 0 : iPrsStream->getILexStream()->getLineNumberOfCharAt(endOffset));
}

int AbstractToken::getEndColumn()
{
	return (iPrsStream == nullptr ? 0 : iPrsStream->getILexStream()->getColumnOfCharAt(endOffset));
}

std::wstring AbstractToken::toString()
{
	return (iPrsStream == nullptr
		        ? L"<toString>"
		        : iPrsStream->toString(this, this));
}

 Adjunct::Adjunct(IPrsStream* prsStream, int startOffset, int endOffset, int kind) : AbstractToken(
	prsStream, startOffset, endOffset, kind)
{
}

std::vector<IToken*> Adjunct::getFollowingAdjuncts()
{
	return {};
}

std::vector<IToken*> Adjunct::getPrecedingAdjuncts()
{
	return {};
}
