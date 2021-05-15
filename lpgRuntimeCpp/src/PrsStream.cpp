#include "PrsStream.h"

#include <iostream>

#include "ILexStream.h"
#include "Exception.h"
#include <unordered_map>

#include "Adjunct.h"
#include "ErrorToken.h"
#include "LexStream.h"
#include "Token.h"

PrsStream::PrsStream(ILexStream* iLexStream)
{
	this->iLexStream = iLexStream;
	if (iLexStream != nullptr) iLexStream->setPrsStream(this);
	resetTokenStream();
}

void PrsStream::remapTerminalSymbols(const std::vector<std::wstring>& ordered_parser_symbols, int eof_symbol)
{
	// SMS 12 Feb 2008
	// lexStream might be nullptr, maybe only erroneously, but it has happened
	if (iLexStream == nullptr)
		throw std::exception("lpg.runtime.PrsStream.remapTerminalSymbols(..):  lexStream is nullptr");

	const auto& ordered_lexer_symbols = iLexStream->orderedExportedSymbols();
	if (ordered_lexer_symbols.empty())
		throw NullExportedSymbolsException();

	if (ordered_parser_symbols.empty())
		throw NullTerminalSymbolsException();
	
	std::vector<int> unimplemented_symbols;
	if (ordered_lexer_symbols != ordered_parser_symbols)
	{
		kindMap = shared_ptr_array<int>(ordered_lexer_symbols.size());

		std::unordered_map<std::wstring, int> terminal_map;
		for (int i = 0; i < ordered_lexer_symbols.size(); i++)
			terminal_map[ordered_lexer_symbols[i]] = i;
		
		for (int i = 0; i < ordered_parser_symbols.size(); i++)
		{
			auto findIt =terminal_map.find(ordered_parser_symbols[i]);
			if (findIt != terminal_map.end())
				kindMap[findIt->second] = i;
			else
			{
				if (i == eof_symbol)
					throw UndefinedEofSymbolException();
				unimplemented_symbols.push_back(i);
			}
		}
	}

	if (unimplemented_symbols.size() > 0)
		throw UnimplementedTerminalsException(unimplemented_symbols);
}

void PrsStream::resetTokenStream()
{
	tokens.reset();
	index = 0;

	adjuncts.reset();
}

void PrsStream::setLexStream(ILexStream* lexStream)
{
	this->iLexStream = lexStream;
	resetTokenStream();
}

void PrsStream::resetLexStream(LexStream* lexStream)
{
	this->iLexStream = lexStream;
	if (lexStream != nullptr) lexStream->setPrsStream(this);
}

void PrsStream::makeToken(int startLoc, int endLoc, int kind)
{
	Token* token = new Token(this, startLoc, endLoc, mapKind(kind));
	token->setTokenIndex(tokens.size());
	tokens.add(token);
	token->setAdjunctIndex(adjuncts.size());
	
}

void PrsStream::makeToken(IToken* token, int offset_adjustment)
{
	token->setStartOffset(token->getStartOffset() + offset_adjustment);
	token->setEndOffset(token->getEndOffset() + offset_adjustment);

	token->setTokenIndex(tokens.size());

	tokens.add(token);
	token->setAdjunctIndex(adjuncts.size());

}

void PrsStream::removeLastToken()
{
	/**
	 * ArrayList implementation
	int last_index = tokens.size() - 1;
	Token* token = (Token*) tokens.get(last_index);
	int adjuncts_size = adjuncts.size();
	while(adjuncts_size > token->getAdjunctIndex())
	    adjuncts.remove(--adjuncts_size);
	tokens.remove(last_index);
	 */

	/**
	 * SegmentedTuple implementation
	 */
	int last_index = tokens.size() - 1;
	Token* token = (Token*)tokens.get(last_index);
	adjuncts.reset(token->getAdjunctIndex());
	tokens.reset(last_index);
}

int PrsStream::makeErrorToken(int firsttok, int lasttok, int errortok, int kind)
{
	int index = tokens.size(); // the next index

	//
	// Note that when creating an error token, we do not remap its kind.
	// Since this is not a lexical operation, it is the responsibility of
	// the calling program (a parser driver) to pass to us the proper kind
	// that it wants for an error token->
	//
	Token* token = new ErrorToken(getIToken(firsttok),
	                               getIToken(lasttok),
	                               getIToken(errortok),
	                               getStartOffset(firsttok),
	                               getEndOffset(lasttok),
	                               kind);
	token->setTokenIndex(tokens.size());
	tokens.add(token);
	token->setAdjunctIndex(adjuncts.size());
	
	return index;
}

void PrsStream::addToken(IToken* token)
{
	token->setTokenIndex(tokens.size());
	tokens.add(token);
	token->setAdjunctIndex(adjuncts.size());
	
}

void PrsStream::makeAdjunct(int startLoc, int endLoc, int kind)
{
	int token_index = tokens.size() - 1; // index of last token processed
	auto adjunct = new Adjunct(this, startLoc, endLoc, mapKind(kind));
	adjunct->setAdjunctIndex(adjuncts.size());
	adjunct->setTokenIndex(token_index);
	adjuncts.add(adjunct);
}

void PrsStream::makeAdjunct(IToken* adjunct, int offset_adjustment)
{
	int token_index = tokens.size() - 1; // index of last token processed
	adjunct->setStartOffset(adjunct->getStartOffset() + offset_adjustment);
	adjunct->setEndOffset(adjunct->getEndOffset() + offset_adjustment);

	adjunct->setAdjunctIndex(adjuncts.size());
	adjunct->setAdjunctIndex(token_index);
	adjuncts.add(adjunct);
}

void PrsStream::addAdjunct(IToken* adjunct)
{
	int token_index = tokens.size() - 1; // index of last token processed
	adjunct->setTokenIndex(token_index);
	adjunct->setAdjunctIndex(adjuncts.size());
	adjuncts.add(adjunct);
}

std::wstring PrsStream::getTokenText(int i)
{
	IToken* t = (IToken*)tokens.get(i);
	return t->toString();
}

int PrsStream::getStartOffset(int i)
{
	IToken* t = (IToken*)tokens.get(i);
	return t->getStartOffset();
}

int PrsStream::getEndOffset(int i)
{
	IToken* t = (IToken*)tokens.get(i);
	return t->getEndOffset();
}

int PrsStream::getTokenLength(int i)
{
	IToken* t = (IToken*)tokens.get(i);
	return t->getEndOffset() - t->getStartOffset() + 1;
}

int PrsStream::getLineNumberOfTokenAt(int i)
{
	IToken* t = (IToken*)tokens.get(i);
	return iLexStream->getLineNumberOfCharAt(t->getStartOffset());
}

int PrsStream::getEndLineNumberOfTokenAt(int i)
{
	IToken* t = (IToken*)tokens.get(i);
	return iLexStream->getLineNumberOfCharAt(t->getEndOffset());
}

int PrsStream::getColumnOfTokenAt(int i)
{
	IToken* t = (IToken*)tokens.get(i);
	return iLexStream->getColumnOfCharAt(t->getStartOffset());
}

int PrsStream::getEndColumnOfTokenAt(int i)
{
	IToken* t = (IToken*)tokens.get(i);
	return iLexStream->getColumnOfCharAt(t->getEndOffset());
}

int PrsStream::getLineOffset(int i)
{
	return iLexStream->getLineOffset(i);
}

int PrsStream::getLineOffsetOfLine(int i)
{
	return iLexStream->getLineOffsetOfLine(i);
}

int PrsStream::getLineCount()
{
	return iLexStream->getLineCount();
}

int PrsStream::getLineNumberOfCharAt(int i)
{
	return iLexStream->getLineNumberOfCharAt(i);
}

int PrsStream::getFirstRealToken(int i)
{
	while (i >= len)
		i = ((ErrorToken*)tokens.get(i))->getFirstRealToken()->getTokenIndex();
	return i;
}

int PrsStream::getLastRealToken(int i)
{
	while (i >= len)
		i = ((ErrorToken*)tokens.get(i))->getLastRealToken()->getTokenIndex();
	return i;
}

void PrsStream::addTokensInRangeToList(std::vector<IToken*>& list, IToken* start_token, IToken* end_token)
{
	assert(list.size());

	if (start_token == nullptr || end_token == nullptr)
		return;

	//
	// If the list of tokens start with an adjunct, starting with the adjunct in question,
	// add it all subsequent adjuncts associated with the same token to the list and adjust
	// the token index.
	//
	int token_index = start_token->getTokenIndex();
	if (dynamic_cast<Adjunct*>(start_token))
	{
		for (int i = start_token->getAdjunctIndex(); i < adjuncts.size(); i++)
		{
			IToken* adjunct = adjuncts.get(i);
			if (adjunct->getTokenIndex() != token_index)
				break;
			list.push_back(adjunct);
			if (adjunct == end_token)
				return;
		}
		token_index++;
	}

	//
	// Starting with the token identified by token_index, add all tokens and their
	// associated adjuncts to the lis, until the end_token is reached or we reach 
	// the end of the token list.
	//
	for (; token_index < tokens.size(); token_index++)
	{
		IToken* token = tokens.get(token_index);
		list.push_back(token);
		if (token == end_token)
			return;

		for (int i = token->getAdjunctIndex(); i < adjuncts.size(); i++)
		{
			IToken* adjunct = adjuncts.get(i);
			if (adjunct->getTokenIndex() != token_index)
				break;
			list.push_back(adjunct);
			if (adjunct == end_token)
				return;
		}
	}

	return;
}

shared_ptr_array<wchar_t> PrsStream::getInputChars()
{
	if (dynamic_cast<LexStream*>(iLexStream))
		return  ((LexStream*)iLexStream)->getInputChars();
	return {};
}

shared_ptr_array<char> PrsStream::getInputBytes()
{
	//  return (iLexStream instanceof Utf8LexStream
	//        ? ((Utf8LexStream) iLexStream).getInputBytes()
	//        : nullptr);
	return {};
}

std::wstring PrsStream::toString(int first_token, int last_token)
{
	return toString((IToken*)tokens.get(first_token), (IToken*)tokens.get(last_token));
}

std::wstring PrsStream::toString(IToken* t1, IToken* t2)
{
	return iLexStream->toString(t1->getStartOffset(), t2->getEndOffset());
}

int PrsStream::getTokenIndexAtCharacter(int offset)
{
	int low = 0,
	    high = tokens.size();
	while (high > low)
	{
		int mid = (high + low) / 2;
		IToken* mid_element = (IToken*)tokens.get(mid);
		if (offset >= mid_element->getStartOffset() &&
			offset <= mid_element->getEndOffset())
			return mid;
		else if (offset < mid_element->getStartOffset())
			high = mid;
		else low = mid + 1;
	}

	return -(low - 1);
}

IToken* PrsStream::getIToken(int i)
{
	return (IToken*)tokens.get(i);
}

void PrsStream::dumpTokens()
{
	if (getSize() <= 2) return;
	std::cout << (" Kind \tOffset \tLen \tLine \tCol \tText\n");
	for (int i = 1; i < getSize() - 1; i++) dumpToken(i);
}

void PrsStream::dumpToken(int i)
{
	std::cout << " ("  << getKind(i)<< ")";
	std::cout << " \t" << getStartOffset(i);
	std::cout << " \t"<< getTokenLength(i);
	std::cout << " \t" << getLineNumberOfTokenAt(i);
	std::cout << " \t" << getColumnOfTokenAt(i);
	std::wcout << L" \t" << getTokenText(i);
	std::cout << std::endl;
}

Tuple<IToken*> PrsStream::incrementalResetAtCharacterOffset(int damage_offset)
{
	int token_index = getTokenIndexAtCharacter(damage_offset),
	    adjunct_index = -1;
	//
	// A negative token_index indicates that the damage_offset did not fall directly on a token 
	// and -token_index is the index of the token preceding the damage offset.
	//
	token_index = (token_index < 0 ? -token_index : token_index);

	//
	// If the damage is away from token? look for an adjunct that is closer
	//
	if (getTokenAt(token_index)->getEndOffset() + 1 < damage_offset)
	{
		for (int i = tokens.get(token_index)->getAdjunctIndex();
		     i < adjuncts.size() && adjuncts.get(i)->getTokenIndex() == token_index;
		     i++)
		{
			if (adjuncts.get(i)->getStartOffset() < damage_offset) // damage on or after this adjunct?
				adjunct_index = i;
			else break;
		}
	}

	Tuple<IToken*> affected_tokens;

	//
	// Start rescanning on an adjunct (indicated by adjunct_index) following the token at token_index;
	//
	int count = (adjunct_index >= 0
		             ? (adjuncts.size() - adjunct_index)
		             : (adjuncts.size() - tokens.get(token_index)->getAdjunctIndex()))
		+
		(tokens.size() - token_index);

	if (adjunct_index >= 0)
	{
		assert(token_index < tokens.size());

		token_index++; // next token following adjunct->..
		for (int i = adjunct_index; i < tokens.get(token_index)->getAdjunctIndex(); i++)
			affected_tokens.add(adjuncts.get(i));
		adjuncts.reset(adjunct_index); // remove all adjuncts from adjunct_index on from the adjunct list
	}
	else adjuncts.reset(tokens.get(token_index)->getAdjunctIndex()); // remove all adjuncts associated with token index
	// and all adjuncts following those from the adjunct list.

	//
	// Add all remaining tokens and their adjuncts to the list of affected tokens.
	//
	for (int i = token_index; i < tokens.size() - 1; i++)
	{
		affected_tokens.add(tokens.get(i));
		for (int k = tokens.get(i)->getAdjunctIndex(); k < tokens.get(i + 1)->getAdjunctIndex(); k++)
		{
			affected_tokens.add(adjuncts.get(k));
		}
	}
	affected_tokens.add(tokens.get(tokens.size() - 1));

	tokens.reset(token_index); // remove all tokens from token_index on from the token list

	//^System.out.println("***The number of affected tokens is " + count +
	//*                   "; The size of the array list is " + affected_tokens.size());

	return affected_tokens;
}

std::vector<IToken*> PrsStream::getAdjuncts(int i)
{
	int start_index = ((IToken*)tokens.get(i))->getAdjunctIndex(),
	    end_index = (i + 1 == tokens.size()
		                 ? adjuncts.size()
		                 : ((IToken*)tokens.get(getNext(i)))->getAdjunctIndex()),
	    size = end_index - start_index;

	std::vector<IToken*> slice(size,nullptr);

	for (int j = start_index, k = 0; j < end_index; j++, k++)
		slice[k] = (IToken*)adjuncts.get(j);
	return slice;
}

int PrsStream::getKind(int i)
{
	IToken* t = (IToken*)tokens.get(i);
	return t->getKind();
}

std::wstring PrsStream::getFileName()
{
	return iLexStream->getFileName();
}

void PrsStream::setMessageHandler(IMessageHandler* errMsg)
{
	iLexStream->setMessageHandler(errMsg);
}

IMessageHandler* PrsStream::getMessageHandler()
{
	return iLexStream->getMessageHandler();
}

void PrsStream::reportError(int errorCode, int leftToken, int rightToken, const std::wstring& errorInfo)
{
	// if (errorCode == DELETION_CODE ||
	//    errorCode == MISPLACED_CODE) tokenText = "";
	reportError(errorCode,
	            leftToken,
	            0,
	            rightToken,
		errorInfo.empty() ? std::vector<std::wstring>{} : std::vector<std::wstring>{ errorInfo });
}

void PrsStream::reportError(int errorCode, int leftToken, int rightToken, const std::vector<std::wstring>& errorInfo)
{
	// if (errorCode == DELETION_CODE ||
	//    errorCode == MISPLACED_CODE) tokenText = "";
	reportError(errorCode,
	            leftToken,
	            0,
	            rightToken,
	            errorInfo);
}

void PrsStream::reportError(int errorCode, int leftToken, int errorToken, int rightToken, const std::wstring& errorInfo)
{
	reportError(errorCode,
	            leftToken,
	            errorToken,
	            rightToken,
	            errorInfo.empty() ? std::vector<std::wstring>{} : std::vector<std::wstring>{ errorInfo });
}

void PrsStream::reportError(int errorCode, int leftToken, int errorToken, int rightToken,
                          const   std::vector<std::wstring>& errorInfo)
{
	iLexStream->reportLexicalError(errorCode,
	                               getStartOffset(leftToken),
	                               getEndOffset(rightToken),
	                               getStartOffset(errorToken),
	                               getEndOffset(errorToken),errorInfo);
}
