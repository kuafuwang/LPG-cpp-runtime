#include "CharOperation.h"

#include <cassert>
#include <locale>
#include <string>
#include "U_chars.h"
using namespace std;
namespace Jikes { // Open namespace Jikes block

//#defind toLowerCase() 

	 	wstring CharOperation::ConvertUtf8ToUnicode(const string& strUtf8)
	{
		wchar_t* target = new wchar_t[strUtf8.length() + 1];
		int len = ConvertUtf8ToUnicode(target, strUtf8.c_str(), strUtf8.length());
		wstring ret(target, target + len);
		delete[] target;
		return ret;

	}

	string CharOperation::ConvertUnicodeToUtf8(const wchar_t* strUnicode)
	{
		if (strUnicode)
		{
			wstring temp = strUnicode;
			return ConvertUnicodeToUtf8(temp);
		}
		return "";
	}

	  string CharOperation::ConvertUnicodeToUtf8(const wstring& strUnicode)
	{
		char* input_name_with_char = new char[strUnicode.length() * 3 + 1];
		int len = CharOperation::ConvertUnicodeToUtf8(strUnicode.c_str(), input_name_with_char);
		string ret(input_name_with_char, input_name_with_char + len);
		delete[] input_name_with_char;
		return ret;
	}

	 int CharOperation::ConvertUnicodeToUtf8(const wchar_t* source, char* target)
	{
		int length = 0;

		if (!source || !target)
			return 0;

		for (; *source; source++)
		{
			int ch = *source;

			if (ch == 0)
			{
				target[length++] = (char)0xC0;
				target[length++] = (char)0x80;
			}
			else if (ch <= 0x007F)
				target[length++] = (char)ch;
			else if (ch <= 0x07FF)
			{

				target[length++] = (char)(0xC0 | ((ch >> 6) & 0x1F));
				target[length++] = (char)(0x80 | (ch & 0x3F));
			}
			else
			{
				target[length++] = (char)(0xE0 | ((ch >> 12) & 0x0F));
				target[length++] = (char)(0x80 | ((ch >> 6) & 0x3F));
				target[length++] = (char)(0x80 | (ch & 0x3F));
			}
		}
		target[length] = U_NULL;
		return length;
	}



	//
	// Convert the Utf8 string of length len pointed to by source into its unicode
	// representation pointed to by target. The wchar_t string target is presumed
	// to have been allocated and to be large enough (at least len + 1) to
	// accomodate the conversion.
	//
	  int CharOperation::ConvertUtf8ToUnicode(wchar_t* target, const char* source, int len)
	{
	  if (!source || !target)
		  return 0;
		wchar_t* ptr = target;
		for (int i = 0; i < len; i++, ptr++)
		{
			uint8_t ch = source[i];

			if ((ch & 0x80) == 0)
				*ptr = ch;
			else if ((ch & 0xE0) == 0xC0)
			{
				*ptr = ch & 0x1F;
				*ptr <<= 6;
				i++;
				ch = source[i] & 0x3F;
				*ptr += ch;
			}
			else if ((ch & 0xF0) == 0xE0)
			{
				*ptr = ch & 0x0F;
				*ptr <<= 6;
				i++;
				ch = source[i] & 0x3F;
				*ptr += ch;

				*ptr <<= 6;
				i++;
				ch = source[i] & 0x3F;
				*ptr += ch;
			}
			else assert(false && "invalid character encoding");
		}
		*ptr = U_NULL;
		return ptr - target;
	}



bool CharOperation::endsWith(const wstring& array, const wstring& toBeFound) {
		  int i = toBeFound.length();
		  int j = array.length() - i;

		  if (j < 0)
			  return false;
		  auto data_toBeFound = toBeFound.data();
		  auto data_array = array.data();
		  while (--i >= 0)
			  if (data_toBeFound[i] != data_array[i + j])
				  return false;
		  return true;
	  }



	    bool CharOperation::equals(const wstring* first, int firstLen, const wstring* second, int secondLen, bool isCaseSensitive)
	  {
			if (!first || !second)
				return false;
		  if (firstLen != secondLen)
			  return false;
		  if (isCaseSensitive)
		  {
			  for (auto i = 0; i < firstLen; ++i)
			  {
				  if (first[i] != second[i])
					  return false;
			  }
			  return true;
		  }
		  for (auto i = 0; i < firstLen; ++i)
		  {
			  if (!equals(first[i], second[i], isCaseSensitive))
				  return false;
		  }
		  return  true;
	  }

	    bool CharOperation::equals(const wstring& first,
		  const wstring& second, bool isCaseSensitive)
	  {

		  auto first_length = first.length();
		  auto second_length = second.length();
		  if (first_length != second_length)
			  return false;

		  auto data_first = first.data();
		  auto data_second = second.data();

		  if (isCaseSensitive)
		  {
			  for (int i = first_length; --i >= 0;)
				  if (data_first[i] != data_second[i])
					  return false;
			  return true;
		  }
		  for (int i = first_length; --i >= 0;)
		  {

			  if (data_first[i] == data_second[i])
				  continue;


			  if (tolower(data_first[i]) != tolower(data_second[i]))
				  return false;
		  }
			 
		  return true;
	  }
	    bool CharOperation::prefixEquals(const wstring& prefix, const wstring& name) {

		  int max = prefix.length();
		  if (name.length() < max) return false;
		  auto prefix_data = prefix.data();
		  auto name_data = name.data();
		  for (int i = max; --i >= 0;) // assumes the prefix is not larger than the name
			  if (prefix_data[i] != name_data[i])
				  return false;
		  return true;
	  }
	    bool CharOperation::prefixEquals(const wstring& prefix, const wstring& name, bool isCaseSensitive) {

		  int max = prefix.length();
		  if (name.length() < max) return false;

		  auto prefix_data = prefix.data();
		  auto name_data = name.data();
		  if (isCaseSensitive) {
			  for (int i = max; --i >= 0;) // assumes the prefix is not larger than the name
				  if (prefix_data[i] != name_data[i])
					  return false;
			  return true;
		  }

		  for (int i = max; --i >= 0;) // assumes the prefix is not larger than the name
		  {

			  if (prefix_data[i] == name_data[i])
				  continue;

			  if (tolower(prefix_data[i]) != tolower(name_data[i]))
				  return false;
		  }
			
		  return true;
	  }

	    bool CharOperation::suffixEquals(const vector<wstring>& suffix, const vector<wstring>& name, bool isCaseSensitive)
	  {
		  auto max = suffix.size();
		  auto size_name = name.size();
		  auto suffix_data = suffix.data();
		  auto name_data = name.data();
		  return suffixEquals(suffix_data, max, name_data, size_name, isCaseSensitive);
	  }
	    bool CharOperation::equals(const vector<wstring>& first, const vector<wstring>& second, bool isCaseSensitive)
	  {
		  return  equals(first.data(), first.size(), second.data(), second.size(), isCaseSensitive);
	  }

	    bool CharOperation::suffixEquals(const wstring* suffix_data, int suffixLen, const wstring* name_data, int nameLen, bool isCaseSensitive)
	  {
		  auto max = suffixLen;

		  if (max > nameLen) {
			  return  false;
		  }
		  if(!suffix_data || !name_data)
		  {
			  return false;
		  }

		  auto offset = nameLen - max;
		  if (isCaseSensitive)
		  {
			  for (int i = max; --i >= 0;)
			  {
				  if (suffix_data[i] != name_data[offset + i])
					  return false;
			  }
			  return true;
		  }


		  for (int i = max; --i >= 0;)
		  {
			  if (!equals(suffix_data[i], name_data[offset + i], isCaseSensitive))
				  return false;
		  }
		  return true;
	  }

	bool CharOperation::suffixEquals(const wstring& suffix, const wstring& name, bool isCaseSensitive)
	{
		auto max = suffix.size();
		auto nameLen = name.size();
		if (max > nameLen) {
			return  false;
		}
		auto suffix_data = suffix.data();
		auto name_data = name.data();
		auto offset = nameLen - max;
		if (isCaseSensitive){
			for (int i = max; --i >= 0;){
				if (suffix_data[i] != name_data[offset + i])
					return false;
			}
			return true;
		}
	
		for (int i = max; --i >= 0;){
			if (suffix_data[i] == name_data[offset + i]){
				continue;
			}
			if (tolower(suffix_data[i]) != tolower(name_data[offset + i])){
				return  false;
			}
		}
		return true;
	}

	bool CharOperation::match(const wstring& pattern, const wstring& name, bool isCaseSensitive)
	{
		return match(pattern.data(), pattern.length(), name.data(), name.length(), isCaseSensitive);
	}

	/**
	* char[] pattern matching, accepting wild-cards '*'.
	*
	* When not case sensitive, the pattern is assumed to already be lowercased, the
	* name will be lowercased character per character as comparing.
	*/


	    bool CharOperation::equals(const wchar_t* data_first, size_t first_length, const wchar_t* data_second, size_t second_length,
		  bool isCaseSensitive)
	  {

		  if (first_length != second_length)
			  return false;

		  if (!data_first || !data_second)
			  return false;

		  if (isCaseSensitive)
		  {
			  for (int i = first_length; --i >= 0;)
				  if (data_first[i] != data_second[i])
					  return false;
			  return true;
		  }
		  for (int i = first_length; --i >= 0;)
		  {
			  if (data_first[i] != data_second[i])
				  continue;

			  if (tolower(data_first[i]) != tolower(data_second[i]))
				  return false;
		  }
			
		  return true;
	  }
	    bool CharOperation::prefixEquals(const wchar_t* prefix_data, size_t prefix_length, const wchar_t* name_data, size_t name_length) {
		
	 	if (!prefix_data || !name_data)
				return false;

		  int max = prefix_length;
		  if (name_length < max) return false;
		  for (int i = max; --i >= 0;) // assumes the prefix is not larger than the name
			  if (prefix_data[i] != name_data[i])
				  return false;
		  return true;
	  }
	    bool CharOperation::prefixEquals(const wchar_t* prefix_data, size_t prefix_length,
		  const wchar_t* name_data, size_t name_length, bool isCaseSensitive)
	{

		if (!prefix_data || !name_data)
			return false;
		  int max = prefix_length;
		  if (name_length < max) return false;


		  if (isCaseSensitive) {
			  for (int i = max; --i >= 0;) // assumes the prefix is not larger than the name
				  if (prefix_data[i] != name_data[i])
					  return false;
			  return true;
		  }

		  for (int i = max; --i >= 0;) // assumes the prefix is not larger than the name
		  {
			  if (prefix_data[i] != name_data[i])
				  continue;

			  if (tolower(prefix_data[i]) != tolower(name_data[i]))
				  return false;
		  }
			  
		  return true;
	  }
	  /**
	  * char[] pattern matching, accepting wild-cards '*'.
	  *
	  * When not case sensitive, the pattern is assumed to already be lowercased, the
	  * name will be lowercased character per character as comparing.
	  */
	    bool CharOperation::match(
		  const wchar_t* data_pattern,
		  size_t patternLength,
		  const wchar_t* data_name,
		  size_t nameLength,
		  bool isCaseSensitive) {

		  if (nameLength == 0) return false; // null name cannot match
		  if (patternLength == 0) return true; // null pattern is equivalent to '*'
		  int iPattern = 0;
		  int iName = 0;

		  /* check first segment */
		  char patternChar = 0;

		  while ((iPattern < patternLength) && (patternChar = data_pattern[iPattern]) != '*') {
			  if (iName == nameLength) return false;
			  if (patternChar != (isCaseSensitive
				  ? data_name[iName]
				  : tolower(data_name[iName]))) {
				  return false;
			  }
			  iName++;
			  iPattern++;
		  }
		  /* check sequence of star+segment */
		  int segmentStart;
		  if (patternChar == '*') {
			  segmentStart = ++iPattern; // skip star
		  }
		  else {
			  segmentStart = 0; // force iName check
		  }
		  int prefixStart = iName;


		  while (iName < nameLength && iPattern < patternLength) {
			  /* segment is ending */
			  if ((patternChar = data_pattern[iPattern]) == '*') {
				  segmentStart = ++iPattern; // skip start
				  prefixStart = iName;
				  continue;
			  }
			  /* chech current name character */
			  if ((isCaseSensitive
				  ? data_name[iName]
				  : tolower(data_name[iName])) != patternChar) {
				  iPattern = segmentStart; // mismatch - restart current segment
				  iName = ++prefixStart;
				  continue;
			  }
			  iName++;
			  iPattern++;
		  }

		  return (segmentStart == patternLength)
			  || (iName == nameLength && iPattern == patternLength)
			  || (iPattern == patternLength - 1 && data_pattern[iPattern] == '*');
	  }

	wstring CharOperation::ConvertUtf8ToUnicode(const char* strUtf8)
	{
		if (strUtf8)
		{
			string temp = strUtf8;
			return ConvertUtf8ToUnicode(temp);
		}
		return L"";
	}
} // Close namespace Jikes block



