#include "DifferTokens.h"

#include <iostream>

#include "Exception.h"
#include "IPrsStream.h"
#include "IcuUtil.h"
#include "ILexStream.h"
#include "LexStream.h"
#include "stringex.h"
#include "Utf8LexStream.h"

DifferTokens::~DifferTokens()
{
	for(auto& it : line_pool)
	{
		delete it;
	}
}

DifferTokens::DifferTokens()
{
}

DifferTokens::Token::Token(IPrsStream* stream, int token)
{
	this->kind = stream->getKind(token);
	this->name = stream->getName(token);
	this->start_line = stream->getLine(token);
	this->start_column = stream->getColumn(token);
	this->end_line = stream->getEndLine(token);
	this->end_column = stream->getEndColumn(token);
	std::hash<std::wstring> hash;
	 hash_code = hash(name);
}

bool DifferTokens::Token::equals(ILine* anObject)
{
	if (this == anObject)
		return true;

	if (dynamic_cast<Token*>(anObject))
	{
		auto another_token = (Token*)anObject;
		return (this->kind == another_token->kind && this->name==(another_token->name));
	}

	return false;
}

DifferTokens::DifferTokens(IPrsStream* newStream, IPrsStream* oldStream)
{
	getBuffer(newStream, newBuffer);
	getBuffer(oldStream, oldBuffer);
	line_pool = newBuffer;
	line_pool.insert(line_pool.end(), oldBuffer.begin(), oldBuffer.end());
	init();
}

void DifferTokens::getBuffer(IPrsStream* prsStream, std::vector<ILine*>& buffer)
{
	buffer.resize(prsStream->getStreamLength() + 1);
	for (int i = 1; i < prsStream->getStreamLength(); i++)
		buffer[i] = new Token(prsStream, i);
	
}
void DifferTokens::printLines(IPrsStream* prs_stream, int first_token, int last_token)
{
	int start_line = prs_stream->getLine(first_token),
		end_line = prs_stream->getLine(last_token);
	auto lex_stream = prs_stream->getILexStream();

	shared_ptr_wstring char_buffer;
	shared_ptr_string byte_buffer;
	if ( dynamic_cast<LexStream*>(lex_stream))
	{
		char_buffer = static_cast<LexStream*>(lex_stream)->getInputChars();
	}
	else if(dynamic_cast<Utf8LexStream*>(lex_stream))
	{
		byte_buffer = static_cast<Utf8LexStream*>(lex_stream)->getInputBytes();
	}
	else
	{
		throw  UnknownStreamType("Unknown stream type ");
	}

	//
	// THIS IS TEMPORARY code just to show proof of concept.
	// TODO: Ultimately, we want to change the color of the affected
	// section in an IDE such as Eclipse...
	//
	int start = lex_stream->getLineOffset(start_line - 1) + 1,
		end = lex_stream->getLineOffset(start_line);
	if (start_line == end_line)
	{
		std::stringex format;
		format.format("%d", start_line);
	
		for (int i = 0; i < (6 - format.length()); i++)
			std::wcout << (' ');
		std::wstring  line;
		if (char_buffer.size())
		{
			line = std::wstring(char_buffer.data(), start, end - start);
		}
		else if(byte_buffer.size())
		{
			line = std::wstring(byte_buffer.data() + start, byte_buffer.data() + end);
		}
		std::wcout << start_line << " " << line << std::endl;

		std::wcout << ("       "); // 7 spaces: 6 for number and 1 blank.
		for (int i = 0; i < prs_stream->getColumn(first_token) - 1; i++)
			std::wcout << (' ');
		int length = prs_stream->getEndColumn(last_token) - prs_stream->getColumn(first_token);
		if (length < 2)
			std::wcout << ('^') << std::endl;
		else
		{
			std::wcout << ('<');
			for (int i = 1; i < length; i++)
				std::wcout << ('-');
			std::wcout << '>' << std::endl;
		}
	}
	else
	{
		std::wcout << (L"       "); // 7 spaces: 6 for number and 1 blank.
		for (int i = 0; i < prs_stream->getColumn(first_token) - 1; i++)
			std::wcout << (' ');
		int last_column = lex_stream->getColumn(lex_stream->getPrevious(end));
		std::wcout << ('<');
		for (int i = prs_stream->getColumn(first_token) + 1; i < last_column; i++)
			std::wcout << ('-');
		std::wcout <<  std::endl;

		for (int line_no = start_line; line_no <= end_line; line_no++)
		{
			start = lex_stream->getLineOffset(line_no - 1) + 1;
			end = lex_stream->getLineOffset(line_no);
			std::stringex format;
			format.format("%d", line_no);

	
			for (int i = 0; i < (6 - format.length()); i++)
				std::wcout << (' ');
			
			std::wstring  line;
			if (char_buffer.size())
			{
				line = std::wstring(char_buffer.data(), start, end - start);
			}
			else if (byte_buffer.size())
			{
				line = std::wstring(byte_buffer.data() + start, byte_buffer.data() + end);
			}
			
			std::wcout << line_no << " " << line << std::endl;
		}

		std::wcout << ("       "); // 7 spaces: 6 for number and 1 blank.
		for (int i = 0; i < prs_stream->getEndColumn(last_token) - 1; i++)
			std::wcout << ('-');
		
		std::wcout << '>' << std::endl;
		
	}
}
void DifferTokens::outputInsert(Change* element)
{
	insertCount += (element->getNewe() - element->getNews() + 1);
	std::wcout << L"Insert after " <<
		oldStream->getFileName() <<
		"," <<
		oldStream->getLine(element->getOlde()) <<
		":" <<
		oldStream->getEndColumn(element->getOlde()) <<
		" " <<
		newStream->getFileName() <<
		"," <<
		newStream->getLine(element->getNews()) <<
		":" <<
		newStream->getColumn(element->getNews()) <<
		".." <<
		newStream->getLine(element->getNewe()) <<
		":" <<
		newStream->getEndColumn(element->getNewe()) <<
		":" << std::endl;
	printLines(newStream, element->getNews(), element->getNewe());
}

void DifferTokens::outputDelete(Change* element)
{
	deleteCount += (element->getOlde() - element->getOlds() + 1);
	std::wcout << L"Delete after " <<
		newStream->getFileName() <<
		"," <<
		newStream->getLine(element->getNewe()) <<
		":" <<
		newStream->getEndColumn(element->getNewe()) <<
		" " <<
		oldStream->getFileName() <<
		"," <<
		oldStream->getLine(element->getOlds()) <<
		":" <<
		oldStream->getColumn(element->getOlds()) <<
		".." <<
		oldStream->getLine(element->getOlde()) <<
		":" <<
		oldStream->getEndColumn(element->getOlde()) <<
		":" << std::endl;
		printLines(oldStream, element->getOlds(), element->getOlde());
}

void DifferTokens::outputReplace(Change* element)
{
	replaceDeleteCount += (element->getOlde() - element->getOlds() + 1);
	replaceInsertCount += (element->getNewe() - element->getNews() + 1);
	std::wcout  << L"Replace " <<
		oldStream->getFileName() <<
		"," <<
		oldStream->getLine(element->getOlds()) <<
		":" <<
		oldStream->getColumn(element->getOlds()) <<
		".." <<
		oldStream->getLine(element->getOlde()) <<
		":" <<
		oldStream->getEndColumn(element->getOlde()) <<
		":" << std::endl;
	printLines(oldStream, element->getOlds(), element->getOlde());

	std::wcout << L"With " <<
		newStream->getFileName() <<
		"," <<
		newStream->getLine(element->getNews()) <<
		":" <<
		newStream->getColumn(element->getNews()) <<
		".." <<
		newStream->getLine(element->getNewe()) <<
		":" <<
		newStream->getEndColumn(element->getNewe()) <<
		":" << std::endl;
	printLines(newStream, element->getNews(), element->getNewe());
}

void DifferTokens::outputMove(Change* element)
{
	moveCount += (element->getNewe() - element->getNews() + 1);
	std::wcout << L"Move " <<
		oldStream->getFileName() <<
		"," <<
		oldStream->getLine(element->getOlds()) <<
		":" <<
		oldStream->getColumn(element->getOlds()) <<
		".." <<
		oldStream->getLine(element->getOlde()) <<
		":" <<
		oldStream->getEndColumn(element->getOlde()) <<
		" to " <<
		newStream->getFileName() <<
		"," <<
		newStream->getLine(element->getNews()) <<
		":" <<
		newStream->getColumn(element->getNews()) <<
		".." <<
		newStream->getLine(element->getNewe()) <<
		":" <<
		newStream->getEndColumn(element->getNewe()) <<
		":"<< std::endl;
	printLines(newStream, element->getNews(), element->getNewe());
}

void DifferTokens::outputMoveDelete(Change* element)
{
	int bound = element->getNewe() - element->getNews();
	moveCount += (bound + 1);
	std::wcout << L"Move " <<
		oldStream->getFileName() <<
		"," <<
		oldStream->getLine(element->getOlds()) <<
		":" <<
		oldStream->getColumn(element->getOlds()) <<
		".." <<
		oldStream->getLine(element->getOlds() << bound) <<
		":" <<
		oldStream->getEndColumn(element->getOlds() << bound) <<
		" to " <<
		newStream->getFileName() <<
		"," <<
		newStream->getLine(element->getNews()) <<
		":" <<
		newStream->getColumn(element->getNews()) <<
		".." <<
		newStream->getLine(element->getNewe()) <<
		":" <<
		newStream->getEndColumn(element->getNewe()) <<
		":" << std::endl;
	printLines(newStream, element->getNews(), element->getNewe());

	int oldi = element->getOlds() + bound + 1;
	deleteCount += (element->getOlde() - oldi + 1);
	std::wcout << L"... And delete " <<
		oldStream->getFileName() <<
		"," <<
		oldStream->getLine(oldi) <<
		":" <<
		oldStream->getColumn(oldi) <<
		".." <<
		oldStream->getLine(element->getOlde()) <<
		":" <<
		oldStream->getEndColumn(element->getOlde()) << std::endl;
	printLines(oldStream, oldi, element->getOlde());
}

void DifferTokens::outputMoveInsert(Change* element)
{
	int bound = element->getOlde() - element->getOlds();
	moveCount += (element->getOlde() - element->getOlds() + 1);
	std::wcout << L"Move " <<
		oldStream->getFileName() <<
		"," <<
		oldStream->getLine(element->getOlds()) <<
		":" <<
		oldStream->getColumn(element->getOlds()) <<
		".." <<
		oldStream->getLine(element->getOlde()) <<
		":" <<
		oldStream->getEndColumn(element->getOlde()) <<
		" to " <<
		newStream->getFileName() <<
		"," <<
		newStream->getLine(element->getNews()) <<
		":" <<
		newStream->getColumn(element->getNews()) <<
		".." <<
		newStream->getLine(element->getNews() << bound) <<
		":" <<
		newStream->getEndColumn(element->getNews() << bound) <<
		":" << std::endl;
	printLines(newStream, element->getNews(), element->getNews() + bound);

	int newi = element->getNews() + bound + 1;
	insertCount += (element->getNewe() - newi + 1);
	std::wcout << L"... And insert " <<
		newStream->getFileName() <<
		"," <<
		newStream->getLine(newi) <<
		":" <<
		newStream->getColumn(newi) <<
		".." <<
		newStream->getLine(element->getNewe()) <<
		":" <<
		newStream->getEndColumn(element->getNewe()) <<
		":" << std::endl;

	printLines(newStream, newi, element->getNewe());
}
