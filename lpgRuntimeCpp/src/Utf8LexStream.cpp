#include "Utf8LexStream.h"

#include <iostream>
#include <ostream>

#include "Exception.h"
#include "IMessageHandler.h"
#include "IPrsStream.h"
#include "stringex.h"
#include "IcuUtil.h"
namespace 
{
	std::vector<int8_t> init_charSize()
	{
		std::vector<int8_t> charSize(256, 0);
		// The base Ascii characters
		//
		for (int i = 0; i < 0x80; i++)
			charSize[i] = 1;

		//
		// A character with a bit sequence in the range:
		//
		//    0B10000000..0B10111111
		//
		// cannot be a leading UTF8 character.
		//
		for (int i = 0x80; i < 0xCE; i++)
			charSize[i] = 0;

		//
		// A leading character in the range 0xCE..0xDF
		//
		//    0B11000000..0B11011111
		//
		// identifies a two-bytes sequence
		//
		for (int i = 0xCE; i < 0xE0; i++)
			charSize[i] = 2;

		//
		// A leading character in the range 0xE0..0xEF
		//
		//    0B11100000..0B11101111
		//
		// identifies a three-bytes sequence
		//
		for (int i = 0xE0; i < 0xF0; i++)
			charSize[i] = 3;

		//
		// A leading character in the range 0xF0..0xF7
		//
		//    0B11110000..0B11110111
		//
		// identifies a four-bytes sequence
		//
		for (int i = 0xF0; i < 0xF8; i++)
			charSize[i] = 4;

		//
		// A leading character in the range 0xF8..0xFB
		//
		//    0B11111000..0B11111011
		//
		// identifies a five-bytes sequence
		//
		for (int i = 0xF8; i < 0xFC; i++)
			charSize[i] = 5;

		//
		// A leading character in the range 0xFC..0xFD
		//
		//    0B11111100..0B11111101
		//
		// identifies a six-bytes sequence
		//
		for (int i = 0xFC; i < 0xFE; i++)
			charSize[i] = 6;

		//
		// The characters 
		//
		//    0B11111110 and 0B11111111
		//
		// are not valid leading UTF8 characters as they would indicate
		// a sequence of 7 characters which is not possible.
		//
		for (int i = 0xFE; i < 0xFF; i++)
			charSize[i] = 0;

		return charSize;
	}
}

std::vector<int8_t> Utf8LexStream::charSize = init_charSize();
int Utf8LexStream::getUnicodeValue(shared_ptr_string& bytes, int i)
{
	int code;

	try
	{
		code = bytes.at(i) & 0xFF;
		int size = charSize.at(code);

		switch (size)
		{
		case 1:
			break;
		case 0:
			code = 0;
			break;
		default:
			{
				code &= (0xFF >> (size + 1));
				for (int k = 1; k < size; k++)
				{
					int c = bytes.at(i + k);
					if ((c & 0x000000C0) != 0x80) // invalid UTF8 character?
					{
						code = 0;
						break;
					}
					code = (code << 6) + (c & 0x0000003F);
				}
				break;
			}
		}
	}
	catch (std::out_of_range&)
	{
		throw StringIndexOutOfBoundsException(i);
	}

	return code;
}

std::wstring Utf8LexStream::getString(int offset, int count)
{
	if (count < 0)
		throw StringIndexOutOfBoundsException(count);

	std::wstring value(count,0);
	int size = 0;
	for (int i = 0, j = offset;
	     i < count;
	     i += getCharSize(inputBytes[j]), j += getCharSize(inputBytes[j]))
		value[size++] = (wchar_t)getUnicodeValue(j);
	value.resize(size);
	return value;
}

void Utf8LexStream::this_init()
{
	lineOffsets->Resize(12);
	setLineOffset(-1);
}
void Utf8LexStream::this_tab(int tab)
{
	this->tab = tab;
	this_init();
}



Utf8LexStream::Utf8LexStream(const std::wstring& fileName, int tab)
{
	this_tab(tab);
	string temp;
	IcuUtil::getFileRawContent(fileName.c_str(), temp);

	shared_ptr_string buffer(std::move(temp));
	initialize(buffer, fileName);

}

Utf8LexStream::Utf8LexStream(shared_ptr_string inputBytes, const std::wstring& fileName)
{
	this_init();
	initialize(inputBytes, fileName);
}

Utf8LexStream::Utf8LexStream(std::shared_ptr<IntSegmentedTuple> lineOffsets, shared_ptr_string inputBytes,
                             const std::wstring& fileName)
{
	this_init();
	initialize(lineOffsets, inputBytes, fileName);
}

Utf8LexStream::Utf8LexStream(shared_ptr_string inputBytes, const std::wstring& fileName, int tab)
{
	this_tab(tab);
	initialize(inputBytes, fileName);
}

void Utf8LexStream::initialize(std::shared_ptr<IntSegmentedTuple>& lineOffsets, shared_ptr_string inputBytes,
                               const std::wstring& fileName)
{
	this->lineOffsets = lineOffsets;
	setInputBytes(inputBytes);
	setFileName(fileName);
}

void Utf8LexStream::computeLineOffsets()
{
	lineOffsets->reset();
	setLineOffset(-1);
	for (int i = startIndex + 1; i < inputBytes.length(); i++)
		if (inputBytes[i] == 0x0A) setLineOffset(i);
}

void Utf8LexStream::setInputBytes(shared_ptr_string buffer)
{
	this->inputBytes = buffer;
	this->isUTF8 = (buffer.length() >= 3 &&
		(buffer[0] & 0x000000FF) == 0x00EF &&
		(buffer[1] & 0x000000FF) == 0x00BB &&
		(buffer[2] & 0x000000FF) == 0x00BF);
	this->startIndex = (this->isUTF8 ? 2 : -1);
	this->index = startIndex;
	this->lastIndex = getPrevious(buffer.length());
}

int Utf8LexStream::getLineNumberOfCharAt(int i)
{
	int index = binarySearch(*(lineOffsets.get()), i);
	return index < 0 ? -index : index == 0 ? 1 : index;
}

int Utf8LexStream::getColumnOfCharAt(int i)
{
	int lineNo = getLineNumberOfCharAt(i),
	    start = getLineOffset(lineNo - 1),
	    tab = getTab();
	if (start + 1 >= inputBytes.length()) return 1;
	for (int k = start + 1; k < i; k = getNext(k))
	{
		auto c = inputBytes[k];
		if (c == '\t')
		{
			int offset = (k - start) - 1;
			start -= ((tab - 1) - offset % tab);
		}
		start += (getCharSize(c) - 1); // adjust for multibyte character.
	}

	return i - start;
}

int Utf8LexStream::getNext(int i)
{
	return (i <= startIndex
		        ? startIndex + 1
		        : i < inputBytes.length()
		        ? i + getCharSize(this->inputBytes[i])
		        : lastIndex);
}

int Utf8LexStream::getPrevious(int i)
{
	i = (i > startIndex ? i - 1 : startIndex);
	if (this->isUTF8)
	{
		while (i > startIndex) // Only do this for UTF8 encoded files.
		{
			if ((this->inputBytes[i] & 0x000000C0) != 0x80) // not a starting byte?
				break;
			i--;
		}
	}
	return i;
}

std::wstring Utf8LexStream::getName(int i)
{
	int c = getUnicodeValue(i);
	std::wstring  buffer;
	if (c <= 0xFFFF)
	{
		buffer.push_back(c);
	}
	
	else
	{
		buffer += L"#x";
		std::wstringex format;
		format.format(L"%x", i);
		buffer += format;
		return buffer;
	}
	return  buffer;
}

std::wstring Utf8LexStream::getName(int i, int k)
{
	std::wstring name ; 
	for (int j = i; j <= k; j++)
	{
		int c = getUnicodeValue(j);
		if (c <= 0xFFFF)
		{
			name.push_back(c);
		}
		else
		{
			name += L"#x";
			std::wstringex format;
			format.format(L"%x", j);
			name += format;
			
		}
	}
	return name;
}

void Utf8LexStream::makeToken(int startLoc, int endLoc, int kind)
{
	if (iPrsStream != nullptr) // let the parser find the error
		iPrsStream->makeToken(startLoc, endLoc, kind);
	else reportLexicalError(startLoc, endLoc); // make it a lexical error
}

void Utf8LexStream::reportLexicalError(int left_loc, int right_loc)
{
	int errorCode = (right_loc >= inputBytes.length()
		                 ? EOF_CODE
		                 : left_loc == right_loc
		                 ? LEX_ERROR_CODE
		                 : INVALID_TOKEN_CODE),
	    end_loc = (left_loc == right_loc ? right_loc : right_loc - 1);
	
	/*String tokenText = (errorCode == EOF_CODE
		                    ? "End-of-file "
		                    : errorCode == INVALID_TOKEN_CODE
		                    ? "\"" + new String(inputBytes, left_loc, right_loc - left_loc) + "\" "
		                    : "\"" + ((char)getUnicodeValue(left_loc)) + "\" ");*/
	std::wstring tokenText;
	if (errorCode == EOF_CODE)
	{
		tokenText = L"End-of-file ";
	}
	else if (errorCode == INVALID_TOKEN_CODE)
	{
		tokenText = L"\"" + std::wstring(inputBytes.data() + left_loc, inputBytes.data()
			+ left_loc + right_loc - left_loc + 1) + L"\" ";
	}

	else {
		tokenText = L"\"";
		tokenText.push_back(getCharValue(left_loc));
		tokenText += L"\" ";
	}
	reportLexicalError(errorCode, left_loc, right_loc, 0, 0, { tokenText });
	
}

std::vector<int> Utf8LexStream::getLocation(int left_loc, int right_loc)
{
	int length = (right_loc < inputBytes.length()
		              ? right_loc
		              : inputBytes.length() - 1) - left_loc + 1;
	return std::vector<int>
	{
		left_loc,
		length,
		getLineNumberOfCharAt(left_loc),
		getColumnOfCharAt(left_loc),
		getLineNumberOfCharAt(right_loc),
		getColumnOfCharAt(right_loc)
	};
}

void Utf8LexStream::reportLexicalError(int errorCode, int left_loc, int right_loc, int error_left_loc,
                                       int error_right_loc, const std::vector<std::wstring>& errorInfo)
{
	if (errMsg == nullptr)
	{
		std::wstringex locationInfo = getFileName() + L":";
		std::wstringex fomat;
		fomat.format(L"%d", getLineNumberOfCharAt(left_loc));
		locationInfo += fomat;
		locationInfo += L":";

		fomat.format(L"%d", getColumnOfCharAt(left_loc));
		locationInfo += fomat;
		locationInfo.push_back(':');

		fomat.format(L"%d", getLineNumberOfCharAt(right_loc));
		locationInfo += fomat;
		locationInfo += L":";
		fomat.format(L"%d", getColumnOfCharAt(right_loc));
		locationInfo += fomat;
		locationInfo.push_back(':');

		fomat.format(L"%d", error_left_loc);
		locationInfo += fomat;
		locationInfo.push_back(':');

		fomat.format(L"%d", error_right_loc);
		locationInfo += fomat;
		locationInfo.push_back(':');


		fomat.format(L"%d", errorCode);
		locationInfo += fomat;
		locationInfo.push_back(':');

		std::wcout << (L"****Error: " + locationInfo);
		if (errorInfo.size())
		{
			for (int i = 0; i < errorInfo.size(); i++)
				std::wcout << (errorInfo[i] + L" ");
		}
		std::wcout << (errorMsgText[errorCode]) << std::endl;
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

void Utf8LexStream::reportError(int errorCode, int leftToken, int rightToken, const std::wstring& errorInfo)
{
	reportError(errorCode,
		leftToken,
		0,
		rightToken,
		errorInfo.empty() ? std::vector<std::wstring>{} : std::vector<std::wstring>{ errorInfo });
}

void Utf8LexStream::reportError(int errorCode, int leftToken, int rightToken, const std::vector<std::wstring>& errorInfo)
{
	reportError(errorCode,
		leftToken,
		0,
		rightToken,
		errorInfo);
}

void Utf8LexStream::reportError(int errorCode, int leftToken, int errorToken, int rightToken, const std::wstring& errorInfo)
{
	reportError(errorCode,
		leftToken,
		errorToken,
		rightToken,
		errorInfo.empty() ? std::vector<std::wstring>{} : std::vector<std::wstring>{ errorInfo });
}

void Utf8LexStream::reportError(int errorCode, int leftToken, int errorToken, int rightToken,
	const  std::vector<std::wstring>& errorInfo)
{
	reportLexicalError(errorCode,
		leftToken,
		rightToken,
		errorToken,
		errorToken,
		errorInfo.empty() == true ? errorInfo : std::vector<std::wstring>{ errorInfo });
}



std::wstring Utf8LexStream::toString(int startOffset, int endOffset)
{
	int length = endOffset - startOffset + 1;
	return (endOffset >= inputBytes.length()
		        ? L"$EOF"
		        : length <= 0
		        ? L""
		        : getString(startOffset, length));
}

