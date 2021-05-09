#include "LexStream.h"

#include <iostream>

#include "IMessageHandler.h"
#include "IPrsStream.h"
#include "IcuUtil.h"
void LexStream::this_init()
{
	lineOffsets.Resize(12);
	setLineOffset(-1);
}

void LexStream::this_tab(int tab)
{
	this->tab_ = tab;
	this_init();
}

LexStream::LexStream(IntSegmentedTuple lineOffsets, shared_ptr_array<wchar_t> inputChars, const std::wstring& file_name)
{
	this_init();
	initialize(lineOffsets, inputChars, inputChars.size(), file_name);
}

LexStream::LexStream(IntSegmentedTuple lineOffsets, shared_ptr_array<wchar_t> inputChars, int inputLength,
                     const std::wstring& file_name)
{
	this_init();
	initialize(lineOffsets, inputChars, inputLength, file_name);
}

LexStream::LexStream(shared_ptr_array<wchar_t> inputChars, const std::wstring& file_name, int tab)
{
	this_tab(tab);
	initialize(inputChars, inputChars.size(), file_name);
}

void LexStream::initialize(const std::wstring& file_name)
{
	std::vector<wchar_t> buffer;
	IcuUtil::getFileUnicodeContent(fileName_.c_str(), buffer);
	initialize(buffer, buffer.size(), file_name);
	
}

void LexStream::computeLineOffsets(int offset)
{
	int line = getLineNumberOfCharAt(offset), // The line containing the offset character
	    line_offset = lineOffsets.get(line); // the beginnning character of the line containing the offset character
	lineOffsets.reset(line + 1);
	for (int i = line_offset + 1; i < inputChars_.size(); i++)
		if (inputChars_[i] == 0x0A) setLineOffset(i);
}
void LexStream::setPrsStream(IPrsStream* prsStream)
{
	prsStream->setLexStream(this);
	this->prsStream = prsStream;
}

IPrsStream* LexStream::getPrsStream()
{
	return prsStream;
}

int LexStream::getLineNumberOfCharAt(int i)
{
	int index = binarySearch(lineOffsets,i);
	return index < 0 ? -index : index == 0 ? 1 : index;
}

std::wstring LexStream::getName(int i)
{
	return i >= getStreamLength() ? L"" : L"" + getCharValue(i);
}

void LexStream::makeToken(int startLoc, int endLoc, int kind)
{
	if (prsStream != nullptr) // let the parser find the error
		prsStream->makeToken(startLoc, endLoc, kind);
	else this->reportLexicalError(startLoc, endLoc); // make it a lexical error
}

void LexStream::reportLexicalError(int left_loc, int right_loc)
{
	int errorCode = (right_loc >= streamLength_
		                 ? EOF_CODE
		                 : left_loc == right_loc
		                 ? LEX_ERROR_CODE
		                 : INVALID_TOKEN_CODE);
	
	std::wstring tokenText;
	if(errorCode == EOF_CODE)
	{
		tokenText = L"End-of-file ";
	}
	else if(errorCode == INVALID_TOKEN_CODE)
	{
		tokenText =L"\"" + std::wstring(inputChars_.data() + left_loc, inputChars_.data()
			+ left_loc + right_loc - left_loc + 1) + L"\" ";
	}

	else {
		tokenText = L"\"";
		tokenText.push_back( getCharValue(left_loc));
		tokenText +=L"\" ";
	}

	reportLexicalError(errorCode, left_loc, right_loc, 0, 0, {tokenText});
}

std::vector<int> LexStream::getLocation(int left_loc, int right_loc)
{
	int length = (right_loc < streamLength_
		              ? right_loc
		              : streamLength_ - 1) - left_loc + 1;
	return
	{
		left_loc,
		length,
		getLineNumberOfCharAt(left_loc),
		getColumnOfCharAt(left_loc),
		getLineNumberOfCharAt(right_loc),
		getColumnOfCharAt(right_loc)
	};
}

void LexStream::reportLexicalError(int errorCode, int left_loc, int right_loc, int error_left_loc, int error_right_loc,
                                   const std::vector<std::wstring>& errorInfo)
{
	if (errMsg == nullptr)
	{
		std::wstring locationInfo = getFileName() + L":";
	
		locationInfo.push_back(getLineNumberOfCharAt(left_loc));
		locationInfo += L":";
		
		locationInfo.push_back(getColumnOfCharAt(left_loc));
		locationInfo.push_back(':');
		
		locationInfo.push_back(getLineNumberOfCharAt(right_loc));
		locationInfo += L":";
		locationInfo.push_back(getColumnOfCharAt(right_loc));
		locationInfo.push_back(':');
		
		locationInfo.push_back(error_left_loc);
		locationInfo.push_back(':');
		
		locationInfo.push_back(error_right_loc);
		locationInfo.push_back(':');
		
		locationInfo.push_back(errorCode);
		locationInfo.push_back(':');

		std::wcout << (L"****Error: " + locationInfo);
		if (errorInfo.size())
		{
			for (int i = 0; i < errorInfo.size(); i++)
				std::wcout << (errorInfo[i] + L" ");
		}
		std::wcout<< (errorMsgText[errorCode]);
	}
	else
	{
		/**
		 * This is the only method in the IMessageHandler interface
		 * It is called with the following arguments:
		 */
		errMsg->handleMessage(errorCode,
		                     getLocation(left_loc, right_loc),
		                     getLocation(error_left_loc, error_right_loc),
		                     getFileName(),
		                     errorInfo);
	}
}

void LexStream::reportError(int errorCode, int leftToken, int rightToken, const std::wstring& errorInfo)
{
	reportError(errorCode,
	            leftToken,
	            0,
	            rightToken,
		errorInfo.empty() ? std::vector<std::wstring>{} : std::vector<std::wstring>{ errorInfo });
}

void LexStream::reportError(int errorCode, int leftToken, int rightToken, const std::vector<std::wstring>& errorInfo)
{
	reportError(errorCode,
	            leftToken,
	            0,
	            rightToken,
	            errorInfo);
}

void LexStream::reportError(int errorCode, int leftToken, int errorToken, int rightToken, const std::wstring& errorInfo)
{
	reportError(errorCode,
	            leftToken,
	            errorToken,
	            rightToken,
		errorInfo.empty() ? std::vector<std::wstring>{} : std::vector<std::wstring>{ errorInfo });
}

void LexStream::reportError(int errorCode, int leftToken, int errorToken, int rightToken,
	const  std::vector<std::wstring>& errorInfo)
{
	reportLexicalError(errorCode,
	                   leftToken,
	                   rightToken,
	                   errorToken,
	                   errorToken,
		errorInfo.empty()== true ? errorInfo : std::vector<std::wstring>{errorInfo});
}

std::wstring LexStream::toString(int startOffset, int endOffset)
{
	int length = endOffset - startOffset + 1;
	return (endOffset >= inputChars_.size()
		        ? L"$EOF"
		        : length <= 0
		        ? L""
		        : std::wstring(inputChars_.data()+startOffset, inputChars_.data() + startOffset+ length));
}

