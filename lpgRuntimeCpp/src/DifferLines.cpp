#include "DifferLines.h"

#include <iostream>

#include "Exception.h"
#include "ILexStream.h"
#include "IPrsStream.h"
#include "LexStream.h"

std::wstring DifferLines::Line::toString()
{
	std::wstring buffer;
	if (name.size() > 0)
	{
		buffer.append(name[0]);
		for (int i = 1; i < name.size(); i++)
		{
			buffer.append(L" ");
			buffer.append(name[i]);
		}
	}

	return buffer;
}

DifferLines::DifferLines(IPrsStream* newStream, IPrsStream* oldStream): Differ(newStream, oldStream)
{
	 getBuffer(newStream, newBuffer);
	 getBuffer(oldStream, oldBuffer);
	 line_pool = newBuffer;
	 line_pool.insert(line_pool.end(), oldBuffer.begin(), oldBuffer.end());
	 init();
}

DifferLines::~DifferLines()
{
	for(auto& it : line_pool)
	{
		delete it;
	}
}

DifferLines::Line::Line(IPrsStream* stream, int start_token, int gate_token):buffer_length(0)
{
	int size = (gate_token > start_token ? gate_token - start_token : 0),
	    end_token = gate_token - 1;

	this->start_line = stream->getLine(start_token);
	this->start_column = stream->getColumn(start_token);
	if (size > 0)
	{
		this->end_line = stream->getEndLine(end_token);
		this->end_column = stream->getEndColumn(end_token);
	}
	else
	{
		this->end_line = stream->getLine(start_token);
		this->end_column = stream->getColumn(start_token);
	}
	this->kind.clear();
	this->kind.resize(size);
	this->name.clear();
	this->name.resize(size);

	hash_code = size;
	for (int i = 0; i < size; i++)
	{
		this->kind[i] = stream->getKind(start_token + i);
		this->name[i] = stream->getName(start_token + i);
		buffer_length += (this->name[i].size() + 1);
		hash_code += this->kind[i];
	}

	hash_code += buffer_length;
}

bool DifferLines::Line::equals(ILine* anObject)
{
	if (this == anObject)
		return true;

	if (dynamic_cast<Line*>(anObject))
	{
		Line* another_line = (Line*)anObject;

		if (this->kind.size() == another_line->kind.size())
		{
			int i;
			for (i = 0; i < kind.size(); i++)
			{
				if (!(this->kind[i] == another_line->kind[i] && this->name[i]==(another_line->name[i])))
					break;
			}
			return i == this->kind.size();
		}
	}

	return false;
}

void DifferLines::getBuffer(IPrsStream* prsStream, std::vector<ILine*>& buffer)
{
	ILexStream *lex_stream = prsStream->getILexStream();
	buffer.resize(lex_stream->getLineCount() + 1);

	int token = 1;
	buffer[0] = new Line(prsStream, 0, 0);
	for (int line_no = 1; line_no < buffer.size(); line_no++)
	{
		int first_token = token;
		while (token < prsStream->getSize() && prsStream->getLine(token) == line_no)
			token++;
		buffer[line_no] = new Line(prsStream, first_token, token);
	}
}
#include <sstream>
void DifferLines::printLines(IPrsStream* prs_stream, int first_line, int last_line)
{
	if ( dynamic_cast<LexStream*>(prs_stream->getILexStream()))
	{
		LexStream* lex_stream = (LexStream*)prs_stream->getILexStream();
		auto buffer = lex_stream->getInputChars();

		for (int line_no = first_line; line_no <= last_line; line_no++)
		{
			int start = lex_stream->getLineOffset(line_no - 1) + 1,
			    end = lex_stream->getLineOffset(line_no);
			std::wostringstream str_stream;
			str_stream << line_no << L" ";
			str_stream.clear();
			std::wstring num = str_stream.str();
			for (int i = 0; i < (7 - num.size()); i++)
				num.push_back (' ');
			
			
			std::wstring  line = num + std::wstring(buffer.data(), start, end - start);
			std::wcout << (line);
		}
	}

	else
	throw  UnknownStreamType("Unknown stream type ");
}

void DifferLines::outputInsert(Change* element)
{
	insertCount += (element->getNewe() - element->getNews() + 1);
	std::wcout << L"Insert after " <<
		oldStream->getFileName() <<
		L"," <<
		oldBuffer[element->getOlde()]->getStartLine() <<
		L" " <<
		newStream->getFileName() <<
		L"," <<
		newBuffer[element->getNews()]->getStartLine();
	
		if(newBuffer[element->getNewe()]->getEndLine() > newBuffer[element->getNews()]->getStartLine())
		{
			std::wcout << L".." << newBuffer[element->getNewe()]->getEndLine();
		}
		else
		{
			std::wcout << L"";
		}
		std::wcout << std::endl;
	printLines(newStream, newBuffer[element->getNews()]->getStartLine(), newBuffer[element->getNewe()]->getEndLine());
}

void DifferLines::outputDelete(Change* element)
{
	deleteCount += (element->getOlde() - element->getOlds() + 1);
	std::wcout << L"Delete after " <<
		newStream->getFileName() <<
		L"," <<
		newBuffer[element->getNewe()]->getStartLine() <<
		L" " <<
		oldStream->getFileName() <<
		L"," <<
		oldBuffer[element->getOlds()]->getStartLine();
		if(oldBuffer[element->getOlde()]->getEndLine() > oldBuffer[element->getOlds()]->getStartLine())
		{
			std::wcout << L".." << oldBuffer[element->getOlde()]->getEndLine();
				
		}
		std::wcout << L":" << std::endl;
	
	printLines(oldStream, oldBuffer[element->getOlds()]->getStartLine(), oldBuffer[element->getOlde()]->getEndLine());
}

void DifferLines::outputReplace(Change* element)
{
	replaceDeleteCount += (element->getOlde() - element->getOlds() + 1);
	replaceInsertCount += (element->getNewe() - element->getNews() + 1);
	std::wcout << L"Replace " <<
		oldStream->getFileName() <<
		"," <<
		oldBuffer[element->getOlds()]->getStartLine();
	
		if(oldBuffer[element->getOlde()]->getEndLine() > oldBuffer[element->getOlds()]->getStartLine()
			)
		{
			std::wcout << L".." << oldBuffer[element->getOlde()]->getEndLine();
				
		}
		else
		{
			std::wcout <<  "";
		}
		std::wcout << ":" << std::endl;
	
	printLines(oldStream, oldBuffer[element->getOlds()]->getStartLine(), oldBuffer[element->getOlde()]->getEndLine());

	std::wcout << L"With " <<
		newStream->getFileName() <<
		"," <<
		newBuffer[element->getNews()]->getStartLine();
		if(newBuffer[element->getNewe()]->getEndLine() > newBuffer[element->getNews()]->getStartLine())
		{
			std::wcout << ".." << newBuffer[element->getNewe()]->getEndLine();
			
		}
		else
		{
			std::wcout << "";
		}
			std::wcout << ":" << std::endl;
	printLines(newStream, newBuffer[element->getNews()]->getStartLine(), newBuffer[element->getNewe()]->getEndLine());
}

void DifferLines::outputMove(Change* element)
{
	moveCount += (element->getNewe() - element->getNews() + 1);
	std::wcout << L"Move " <<
	oldStream->getFileName() <<
	"," <<
	oldBuffer[element->getOlds()]->getStartLine();
	if(oldBuffer[element->getOlde()]->getEndLine() > oldBuffer[element->getOlds()]->getStartLine())
	{
		std::wcout << L".." << oldBuffer[element->getOlde()]->getEndLine();		
	}
	std::wcout << " to " <<
	newStream->getFileName() <<
	"," <<
	newBuffer[element->getNews()]->getStartLine();

	if(newBuffer[element->getNewe()]->getEndLine() > newBuffer[element->getNews()]->getStartLine())
	{
		std::wcout << L".." << newBuffer[element->getNewe()]->getEndLine();
	}
	std::wcout << ":" << std::endl;

	printLines(newStream, newBuffer[element->getNews()]->getStartLine(), newBuffer[element->getNewe()]->getEndLine());
}

void DifferLines::outputMoveDelete(Change* element)
{
	moveCount += (element->getNewe() - element->getNews() + 1);
	int bound = newBuffer[element->getNewe()]->getEndLine() - newBuffer[element->getNews()]->getStartLine();
	std::wcout << L"Move " <<
		oldStream->getFileName() <<
		"," <<
		oldBuffer[element->getOlds()]->getStartLine();
	
	if (bound > 0) {
		std::wcout << L".." << oldBuffer[element->getOlds()]->getStartLine() + bound;
	}
			
	std::wcout << L" to " <<
		newStream->getFileName() <<
		"," <<
		newBuffer[element->getNews()]->getStartLine();
	
	if(newBuffer[element->getNewe()]->getEndLine() > newBuffer[element->getNews()]->getStartLine())
	{
		std::wcout << L".." << newBuffer[element->getNewe()]->getEndLine();
	}

	std::wcout << ":" << std::endl;
	
	printLines(newStream, newBuffer[element->getNews()]->getStartLine(), newBuffer[element->getNewe()]->getEndLine());

	int oldi = oldBuffer[element->getOlds()]->getStartLine() + bound + 1;
	deleteCount += (element->getOlde() - element->getOlds() - element->getNewe() + element->getNews());
	std::wcout << L"... And delete " <<
		oldStream->getFileName() <<
		"," <<
		oldi;
	
	if(oldBuffer[element->getOlde()]->getEndLine() > oldi)
	{
		std::wcout << L".." << oldBuffer[element->getOlde()]->getEndLine();
	}
			
			
	printLines(oldStream, oldi, newBuffer[element->getOlde()]->getEndLine());
}

void DifferLines::outputMoveInsert(Change* element)
{
	moveCount += (element->getOlde() - element->getOlds() + 1);
	int bound = oldBuffer[element->getOlde()]->getStartLine() - oldBuffer[element->getOlds()]->getEndLine();
	std::wcout << L"Move " <<
		oldStream->getFileName() <<
		"," <<
		oldBuffer[element->getOlds()]->getStartLine();
	
	if (oldBuffer[element->getOlde()]->getEndLine() > oldBuffer[element->getOlds()]->getStartLine()
		)
	{
		std::wcout << L".." << oldBuffer[element->getOlde()]->getEndLine();
			
	}
		std::wcout << L" to " <<
		newStream->getFileName() <<
		"," <<
		newBuffer[element->getNews()]->getStartLine();
	if(bound > 0)
	{
		std::wcout << L".." << newBuffer[element->getNews()]->getStartLine() + bound;
	}
	std::wcout << ":" << std::endl;
	
	printLines(newStream, newBuffer[element->getNews()]->getStartLine(),
	           newBuffer[element->getNews()]->getStartLine() + bound);

	int newi = newBuffer[element->getNews()]->getStartLine() + bound + 1;
	insertCount += (element->getNewe() - element->getNews() - element->getOlde() + element->getOlds());
	std::wcout << L"... And insert " <<
		newStream->getFileName() <<
		L"," <<
		newi;
	
	if(newBuffer[element->getNewe()]->getEndLine() > newi)
	{
		std::wcout << L".." << newBuffer[element->getNewe()]->getEndLine();
	}

	std::wcout << ":" << std::endl;
	
	printLines(newStream, newi, newBuffer[element->getNewe()]->getEndLine());
}
