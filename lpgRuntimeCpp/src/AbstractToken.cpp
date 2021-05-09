#include "AbstractToken.h"

#include "Exception.h"
#include "ILexStream.h"
#include "IPrsStream.h"
#include <typeinfo>

#include "LexStream.h"

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

ILexStream* AbstractToken::getLexStream()
{
	return iPrsStream == nullptr ? nullptr : iPrsStream->getILexStream();
}

std::wstring AbstractToken::getValue(std::vector<wchar_t>& inputChars)
{
	if (iPrsStream != nullptr)
		return toString();
	if (
		 dynamic_cast<LexStream*> ( iPrsStream->getLexStream() ))
	{
		auto lex_stream = (LexStream*)iPrsStream->getLexStream();
		//if (inputChars != lex_stream->getInputChars().data())
		//	throw  MismatchedInputCharsException();
		return toString();
	}
	const type_info& nInfo = typeid(iPrsStream->getLexStream());
	std::string temp = "Unknown stream type ";
	temp =+nInfo.name();
	throw  UnknownStreamType(temp);
}

std::wstring AbstractToken::toString()
{
	return (iPrsStream == nullptr
		        ? L"<toString>"
		        : iPrsStream->toString(this, this));
}

