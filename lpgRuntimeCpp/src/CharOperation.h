
#ifndef CharOperation_INCLUDED
#define CharOperation_INCLUDED

#include <locale>
#include <string>
#include <vector>
using std::vector;
namespace Jikes { // Open namespace Jikes block

	class CharOperation
	{
	public:
		static bool  endsWith(const std::wstring& array, const std::wstring& toBeFound);

		static bool equals(const vector<std::wstring>& first, const vector<std::wstring>& second, bool isCaseSensitive);
		static bool equals(const std::wstring* first, int firstLen, const std::wstring*  name, int nameLen, bool isCaseSensitive);
		static bool equals(const std::wstring&first, const std::wstring&second, bool isCaseSensitive);
		static bool prefixEquals(const std::wstring& prefix, const std::wstring& name);
		static bool prefixEquals(const std::wstring& prefix, const std::wstring& name, bool isCaseSensitive);

		static bool suffixEquals(const vector<std::wstring>& suffix, const vector<std::wstring>& name, bool isCaseSensitive);
		static bool suffixEquals(const std::wstring* suffix, int suffixLen, const std::wstring*  name, int nameLen,bool isCaseSensitive);
		static bool suffixEquals(const std::wstring& suffix, const std::wstring&  name , bool isCaseSensitive);
		static bool match(const std::wstring& pattern, const std::wstring& name, bool isCaseSensitive);
		//
		// Convert the null terminated Unicode string source into its Utf8
		// representation pointed to by target. The char string target is presumed
		// to have been allocated and to be large enough to accomodate the conversion.
		//
		static bool equals(const wchar_t* data_first, size_t first_length, const wchar_t* data_second, size_t second_length,
			bool isCaseSensitive);

		static bool prefixEquals(const wchar_t* prefix_data, size_t prefix_length, const wchar_t* name_data, size_t name_length);
		
		static bool prefixEquals(const wchar_t* prefix_data, size_t prefix_length, const wchar_t* name_data, size_t name_length,
			bool isCaseSensitive);
		
		static bool match(const wchar_t* data_pattern, size_t patternLength, const wchar_t* data_name, size_t nameLength, bool isCaseSensitive);

		static std::wstring ConvertUtf8ToUnicode(const char* strUtf8);
		static std::wstring ConvertUtf8ToUnicode(const std::string& strUtf8);

		static std::string ConvertUnicodeToUtf8(const wchar_t* strUnicode);
		static std::string ConvertUnicodeToUtf8(const std::wstring& strUnicode);

		static	int ConvertUnicodeToUtf8(const wchar_t* source, char* target);
		
		static int  ConvertUtf8ToUnicode(wchar_t* target, const char* source, int len);

		static bool IsWhitespace(int c)
		{
			std::locale loc;
			return std::isspace(c, loc);
		}
	};



	


} // Close namespace Jikes block


#endif // _INCLUDED

