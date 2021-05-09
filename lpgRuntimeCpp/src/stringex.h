#ifndef _EXT_STRING_H
#define _EXT_STRING_H
#pragma once
#include <string>
#include <vector>
#include <stdarg.h>

namespace std
{

	/**
	 * An extension of STL's string providing additional functionality that is often availiable in
	 * higher-level languages such as Python.
	 */
	class stringex : public string
	{
	public:
		/**`
		 * Default constructor
		 *
		 * Constructs an empty stringex ("")
		 */
		stringex() : string() { }

		/**
		 * Duplicate the STL string copy constructor
		 *
		 * @param[in] s   The string to copy
		 * @param[in] pos The starting position in the string to copy from
		 * @param[in] n   The number of characters to copy
		 */
		stringex(const string &s, size_type pos = 0, size_type n = npos) : string(s, pos, npos) { }

		/**
		 * Construct an stringex from a null-terminated character array
		 *
		 * @param[in] s The character array to copy into the new string
		 */
		stringex(const value_type *s) : string(s) { }

		/**
		 * Construct an stringex from a character array and a length
		 *
		 * @param[in] s The character array to copy into the new string
		 * @param[in] n The number of characters to copy
		 */
		stringex(const value_type *s, size_type n) : string(s, n) { }

		/**
		 * Create an stringex with @p n copies of @p c
		 *
		 * @param[in] n The number of copies
		 * @param[in] c The character to copy @p n times
		 */
		stringex(size_type n, value_type c) : string(n, c) { }

		/**
		 * Create a string from a range
		 *
		 * @param[in] first The first element to copy in
		 * @param[in] last  The last element to copy in
		 */
		template <class InputIterator>
			stringex(InputIterator first, InputIterator last) : string(first, last) { }

		/**
		 * The destructor
		 */
		~stringex() { }

		/**
		 * Split a string by whitespace
		 *
		 * @return A vector of strings, each of which is a substring of the string
		 */
		vector<stringex> split(size_type limit = npos) const
		{
			vector<stringex> v;

			const_iterator 
				i = begin(),
				  last = i;
			for (; i != end(); i++)
			{
				if (*i == ' ' || *i == '\n' || *i == '\t' || *i == '\r')
				{
					if (i + 1 != end() && (i[1] == ' ' || i[1] == '\n' || i[1] == '\t' || i[1] == '\r'))
						continue;
					v.push_back(stringex(last, i));
					last = i + 1;
					if (v.size() >= limit - 1)
					{
						v.push_back(stringex(last, end()));
						return v;
					}
				}
			}

			if (last != i)
				v.push_back(stringex(last, i));

			return v;
		}

		/**
		 * Split a string by a character
		 *
		 * Returns a vector of ext_strings, each of which is a substring of the string formed by splitting
		 * it on boundaries formed by the character @p separator.  If @p limit is set, the returned vector
		 * will contain a maximum of @p limit elements with the last element containing the rest of
		 * the string.
		 *
		 * If @p separator is not found in the string, a single element will be returned in the vector
		 * containing the entire string.
		 *
		 * The separators are removed from the output
		 *
		 * @param[in] separator The character separator to split the string on
		 * @param[in] limit     The maximum number of output elements
		 * @return A vector of strings, each of which is a substring of the string
		 *
		 * @section split_ex Example
		 * @code
		 * std::stringex s("This|is|a|test.");
		 * std::vector<std::stringex> v = s.split('|');
		 * std::copy(v.begin(), v.end(), std::ostream_iterator<std::stringex>(std::cout, "\n"));
		 *
		 * This
		 * is
		 * a
		 * test.
		 * @endcode
		 */
		vector<stringex> split(value_type separator, size_type limit = npos) const
		{
			vector<stringex> v;

			const_iterator 
				i = begin(),
				last = i;
			for (; i != end(); i++)
			{
				if (*i == separator)
				{
					v.push_back(stringex(last, i));
					last = i + 1;
					if (v.size() >= limit - 1)
					{
						v.push_back(stringex(last, end()));
						return v;
					}
				}
			}

			if (last != i)
				v.push_back(stringex(last, i));

			return v;
		}

		/**
		 * Split a string by another string
		 *
		 * Returns a vector of ext_strings, each of which is a substring of the string formed by
		 * splitting it on boundaries formed by the string @p separator.  If @p limit is set, the
		 * returned vector will contain a maximum of @p limit elements with the last element
		 * containing the rest of the string.
		 *
		 * If @p separator is not found in the string, a single element will be returned in the
		 * vector containing the entire string.
		 *
		 * The separators are removed from the output
		 *
		 * @param[in] separator The string separator to split the string on
		 * @param[in] limit     The maximum number of output elements
		 * @return A vector of strings, each of which is a substring of the string
		 *
		 * @ref split_ex
		 */
		vector<stringex> split(const string &separator, size_type limit = npos) const
		{
			vector<stringex> v;

			const_iterator
				i = begin(),
				last = i;
			for (; i != end(); i++)
			{
				if (string(i, i + separator.length()) == separator)
				{
					v.push_back(stringex(last, i));
					last = i + separator.length();

					if (v.size() >= limit - 1)
					{
						v.push_back(stringex(last, end()));
						return v;
					}
				}
			}

			if (last != i)
				v.push_back(stringex(last, i));

			return v;
		}

		/**
		 * Convert a string into an integer
		 *
		 * Convert the initial portion of a string into a signed integer.  Once a non-numeric
		 * character is reached, the remainder of @p string is ignored and the integer that was
		 * read returned.
		 *
		 * @param s The string to convert
		 * @return The integer converted from @p string
		 */
		static long int integer(const string &s)
		{
			long int retval = 0;
			bool neg = false;

			for (const_iterator i = s.begin(); i != s.end(); i++)
			{
				if (i == s.begin())
				{
					if (*i == '-')
					{
						neg = true;
						continue;
					}
					else if (*i == '+')
						continue;
				}
				if (*i >= '0' && *i <= '9')
				{
					retval *= 10;
					retval += *i - '0';
				}
				else
					break;
			}

			if (neg)
				retval *= -1;

			return retval;
		}

		/**
		 * Convert the string to an integer
		 *
		 * Convert the initial portion of the string into a signed integer.  Once a non-numeric
		 * character is reached, the remainder of the string is ignored and the integer that had
		 * been read thus far is returned.
		 *
		 * @return The integer converted from the string
		 */
		long int integer() const
		{
			return integer(*this);
		}

		/**
		 * Split a string into chunks of size @p chunklen.  Returns a vector of strings.
		 *
		 * Splits a string into chunks of the given size.  The final chunk may not fill its
		 * entire allocated number of characters.
		 *
		 * @param[in] chunklen The number of characters per chunk
		 * @return A vector of strings, each of length <= chunklen
		 *
		 * @section chunk_split-ex Example
		 * @code
		 * std::stringex s("abcdefghijk");
		 * std::vector<std::stringex> v = s.chunk_split(3);
		 * std::copy(v.begin(), v.end(), ostream_iterator<std::stringex>(cout, " "));
		 *
		 * abc def ghi jk
		 * @endcode
		 */
		vector<stringex> chunk_split(size_type chunklen) const
		{
			vector<stringex> retval;
			retval.reserve(size() / chunklen + 1);

			size_type count = 0;
			const_iterator
				i = begin(),
				last = i;
			for (; i != end(); i++, count++)
			{
				if (count == chunklen)
				{
					count = 0;
					retval.push_back(stringex(last, i));
					last = i;
				}
			}
			
			if (last != i)
				retval.push_back(stringex(last, i));

			return retval;
		}

		/**
		 * Join a sequence of strings by some glue to create a new string
		 *
		 * Glue is not added to the end of the string.
		 *
		 * @pre [first, last) is a valid range
		 * @pre InputIterator is a model of STL's Input Iterator
		 * @pre InputIterator must point to a string type (std::string, std::stringex, char *)
		 *
		 * @param[in] glue  The glue to join strings with
		 * @param[in] first The beginning of the range to join
		 * @param[in] last  The end of the range to join
		 * @return A string constructed of each element of the range connected together with @p glue
		 *
		 * @section join_ex Example
		 * @code
		 * std::vector<std::stringex> v;
		 * v.push_back("This");
		 * v.push_back("is");
		 * v.push_back("a");
		 * v.push_back("test.");
		 * std::cout << std::stringex::join("|", v.begin(), v.end()) << std::endl;
		 *
		 * This|is|a|test.
		 * @endcode
		 */
		template <class InputIterator>
			static stringex join(const string &glue, InputIterator first, InputIterator last)
			{
				stringex retval;

				for (; first != last; ++first)
				{
					retval.append(*first);
					retval.append(glue);
				}
				retval.erase(retval.length() - glue.length());

				return retval;
			}

		/**
		 * Join a sequence of strings by some glue to create a new string
		 *
		 * @copydoc join
		 * @ref join_ex
		 */
		template <class InputIterator>
			static stringex join(value_type glue, InputIterator first, InputIterator last)
			{
				stringex retval;

				for (; first != last; ++first)
				{
					retval.append(*first);
					retval.append(1, glue);
				}
				retval.erase(retval.length() - 1);

				return retval;
			}

		/**
		 * Search for any instances of @p needle and replace them with @p s
		 *
		 * @param[in] needle The string to replace
		 * @param[in] s      The replacement string
		 * @return				*this
		 * @post					All instances of @p needle in the string are replaced with @p s
		 *
		 * @section replace-ex Example
		 * @code
		 * std::stringex s("This is a test.");
		 * s.replace("is", "ere");
		 * std::cout << s << std::endl;
		 *
		 * There ere a test.
		 * @endcode
		 */
		stringex &replace(const string &needle, const string &s)
		{
			size_type
				lastpos = 0,
				thispos;

			while ((thispos = find(needle, lastpos)) != npos)
			{
				string::replace(thispos, needle.length(), s);
				lastpos = thispos + 1;
			}
			return *this;
		}
		stringex &replace_first(const string &needle, const string &s)
		{
			size_type
				lastpos = 0,
				thispos;

			if ((thispos = find(needle, lastpos)) != npos)
			{
				string::replace(thispos, needle.length(), s);
				lastpos = thispos + 1;
			}
			return *this;
		}
		/**
		 * Search of any instances of @p needle and replace them with @p c
		 *
		 * @param[in] needle The character to replace
		 * @param[in] c      The replacement character
		 * @return           *this
		 * @post             All instances of @p needle in the string are replaced with @p c
		 *
		 * @ref replace-ex
		 */
		stringex &replace(value_type needle, value_type c)
		{
			for (iterator i = begin(); i != end(); i++)
				if (*i == needle)
					*i = c;

			return *this;
		}

		/**
		 * Repeat a string @p n times
		 *
		 * @param[in] n The number of times to repeat the string
		 * @return stringex containing @p n copies of the string
		 *
		 * @section repeat-ex Example
		 * @code
		 * std::stringex s("123");
		 * s = s * 3;
		 * std::cout << s << std::endl;
		 *
		 * 123123123
		 * @endcode
		 */
		stringex operator*(size_type n)
		{
			stringex retval;
			for (size_type i = 0; i < n; i++)
				retval.append(*this);

			return retval;
		}

		/**
		 * Convert the string to lowercase
		 *
		 * @return *this
		 * @post The string is converted to lowercase
		 */
		stringex &tolower()
		{
			for (iterator i = begin(); i != end(); i++)
				if (*i >= 'A' && *i <= 'Z')
					*i = (*i) + ('a' - 'A');
			return *this;
		}

		/**
		 * Convert the string to uppercase
		 *
		 * @return *this
		 * @post The string is converted to uppercase
		 */
		stringex &toupper()
		{
			for (iterator i = begin(); i != end(); i++)
				if (*i >= 'a' && *i <= 'z')
					*i = (*i) - ('a' - 'A');
			return *this;
		}

		/**
		 * Count the occurances of @p str in the string.
		 *
		 * @return The count of substrings @p str in the string
		 */
		size_type count(const string &str) const
		{
			size_type
				count = 0,
				last = 0,
				cur = 0;

			while ((cur = find(str, last + 1)) != npos)
			{
				count++;
				last = cur;
			}

			return count;
		}

		/**
		 * Determine if the string is alphanumeric
		 *
		 * @return true if the string contains only characters between a-z, A-Z and 0-9 and
		 * contains at least one character, else false
		 */
		bool is_alnum() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
			{
				if (*i < 'A' || *i > 'Z')
					if (*i < '0' || *i > '9')
						if (*i < 'a' || *i > 'z')
							return false;
			}

			return true;
		}

		/**
		 * Determine if the string is alphabetic only
		 *
		 * @return true of the string contains only characters between a-z and A-Z and contains at
		 * least one character, else false
		 */
		bool is_alpha() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
				if (*i < 'A' || (*i > 'Z' && (*i < 'a' || *i > 'z')))
					return false;

			return true;
		}

		/**
		 * Determine if the string is numeric only
		 *
		 * @return true if the string contains only characters between 0-9 and contains at least
		 * one character, else false
		 */
		bool is_numeric() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
				if (*i < '0' || *i > '9')
					return false;

			return true;
		}

		/**
		 * Determine if a string is all lower case
		 *
		 * @return true if there is at least one character, and all characters are lowercase
		 * letters, else false
		 */
		bool is_lower() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
				if (*i < 'a' || *i < 'z')
					return false;

			return true;
		}

		/**
		 * Determine if a string is all upper case
		 *
		 * @return true if there is at least one character, and all characters are uppercase
		 * letters, else false
		 */
		bool is_upper() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
				if (*i < 'A' || *i > 'Z')
					return false;

			return true;
		}

		/**
		 * Swap the case of a string
		 *
		 * @post Converts all uppercase to lowercase, and all lowercase to uppercase in the string
		 * @return *this
		 */
		stringex &swapcase()
		{
			for (iterator i = begin(); i != end(); i++)
				if (*i >= 'A' && *i <= 'Z')
					*i += ('a' - 'A');
				else if (*i >= 'a' && *i <= 'z')
					*i -= ('a' - 'A');
			
			return *this;
		}

		/*******************************************************************************
			Function:	std::stringex::start_with
			Access:		public 
			Qualifier:	const
			Parameter:	const string & str			
			Returns:	bool		
		
			Purpose:	is the string start with str
		*******************************************************************************/
		bool start_with(const string& str) const
		{
			return ( this->find(str) == 0 );
		}

		/*******************************************************************************
			Function:	std::stringex::end_with
			Access:		public 
			Qualifier:	const
			Parameter:	const string & str			
			Returns:	bool		
		
			Purpose:	is the string end with str
		*******************************************************************************/
		bool end_with(const string& str) const
		{
			if (str.length() > this->length())
			{
				return false;
			}
			size_type off = this->length() - str.length();
			return ( find(str, off) == off);
		}

		/*******************************************************************************
			Function:	hl_lib::stringex::format
			Access:		public 
			Qualifier:	
			Parameter:	const char * format_string
			Parameter:	...
			Returns:	stringex&
			
			Purpose:	format the string
		*******************************************************************************/
		stringex& format(const char* format_string, ...)
		{
			if (format_string == 0)
			{
				return *this;
			}

			va_list argList;
			char* pbuf = 0;
			va_start( argList, format_string );
			int len = _vscprintf( format_string, argList );
			pbuf = new char[len + 1];
			if (pbuf != 0)
			{
				vsprintf_s( pbuf, len + 1, format_string, argList );
				*this = pbuf;
			}
			delete[] pbuf;
			va_end( argList );

			return *this;
		}

		/*******************************************************************************
			Function:	hl_lib::stringex::trim_left
			Access:		public 
			Qualifier:	
			Parameter:	value_type ch
			Returns:	stringex&
			
			Purpose:	delete all char which is ch at the left of the string
		*******************************************************************************/
		stringex& trim_left(value_type ch = ' ')
		{
			size_type off = this->find_first_not_of(ch);
			if (off != string::npos)
			{
				this->erase(0, off);
			}
			return *this;
		}

		/*******************************************************************************
			Function:	hl_lib::stringex::trim_right
			Access:		public 
			Qualifier:	
			Parameter:	value_type ch
			Returns:	stringex&
			
			Purpose:	delete all char which is ch at the right of the string
		*******************************************************************************/
		stringex& trim_right(value_type ch = ' ')
		{
			size_type off = this->find_last_not_of(ch);
			if (off == string::npos)
			{
				off = 0;
			}
			else
			{
				off++;
			}
			this->erase(off, length() - off);
			return *this;
		}

		/*******************************************************************************
			Function:	hl_lib::stringex::trim
			Access:		public 
			Qualifier:	
			Parameter:	value_type ch
			Returns:	stringex&
			
			Purpose:	delete all char which is ch at the left and right of the string
		*******************************************************************************/
		stringex& trim(value_type ch = ' ')
		{
			trim_left(ch);
			trim_right(ch);
			return *this;
		}

		/*******************************************************************************
			Function:	hl_lib::stringex::float_num
			Access:		public static 
			Qualifier:	
			Parameter:	const string & str
			Returns:	double
			
			Purpose:	parse str to a float number
		*******************************************************************************/
		static double float_num(const string& str)
		{
			return atof(str.c_str());
		}

		/*******************************************************************************
			Function:	hl_lib::stringex::float_num
			Access:		public static 
			Qualifier:	
			Returns:	double
			
			Purpose:	parse this to a float number
		*******************************************************************************/
		double float_num() const
		{
			return float_num(*this);
		}

		/*******************************************************************************
			Function:	hl_lib::stringex::compare_nocase
			Access:		public 
			Qualifier:	const
			Parameter:	const string & str
			Returns:	int
			
			Purpose:	compare string no case
		*******************************************************************************/
		int compare_nocase(const string& str) const
		{
			return _stricmp(this->c_str(), str.c_str());
		}

		/*******************************************************************************
			Function:	hl_lib::stringex::compare_nocase
			Access:		public 
			Qualifier:	const
			Parameter:	size_type index
			Parameter:	size_type length
			Parameter:	const string & str
			Returns:	int
			
			Purpose:	compare substring no case
		*******************************************************************************/
		int compare_nocase( size_type index, size_type length, const string &str ) const
		{
			stringex temp = this->substr(index, length);
			return temp.compare_nocase(str);
		}

		/*******************************************************************************
			Function:	hl_lib::stringex::compare_nocase
			Access:		public 
			Qualifier:	const
			Parameter:	size_type index
			Parameter:	size_type length
			Parameter:	const string & str
			Parameter:	size_type index2
			Parameter:	size_type length2
			Returns:	int
			
			Purpose:	compare two substring no case
		*******************************************************************************/
		int compare_nocase( size_type index, size_type length, const string &str, size_type index2,	size_type length2) const
		{
			stringex temp1 = this->substr(index, length);
			stringex temp2 = str.substr(index2, length2);
			return temp1.compare_nocase(temp2);
		}

	};

	/**
	* An extension of STL's wstring providing additional functionality that is often availiable in
	* higher-level languages such as Python.
	*/
	class wstringex : public wstring
	{
	public:
		/**
		* Default constructor
		*
		* Constructs an empty wstringex ("")
		*/
		wstringex() : wstring() { }

		/**
		* Duplicate the STL wstring copy constructor
		*
		* @param[in] s   The wstring to copy
		* @param[in] pos The starting position in the wstring to copy from
		* @param[in] n   The number of characters to copy
		*/
		wstringex(const wstring &s, size_type pos = 0, size_type n = npos) : wstring(s, pos, npos) { }

		/**
		* Construct an wstringex from a null-terminated character array
		*
		* @param[in] s The character array to copy into the new wstring
		*/
		wstringex(const value_type *s) : wstring(s) { }

		/**
		* Construct an wstringex from a character array and a length
		*
		* @param[in] s The character array to copy into the new wstring
		* @param[in] n The number of characters to copy
		*/
		wstringex(const value_type *s, size_type n) : wstring(s, n) { }

		/**
		* Create an wstringex with @p n copies of @p c
		*
		* @param[in] n The number of copies
		* @param[in] c The character to copy @p n times
		*/
		wstringex(size_type n, value_type c) : wstring(n, c) { }

		/**
		* Create a wstring from a range
		*
		* @param[in] first The first element to copy in
		* @param[in] last  The last element to copy in
		*/
		template <class InputIterator>
		wstringex(InputIterator first, InputIterator last) : wstring(first, last) { }

		/**
		* The destructor
		*/
		~wstringex() { }

		/**
		* Split a wstring by whitespace
		*
		* @return A vector of strings, each of which is a substring of the wstring
		*/
		vector<wstringex> split(size_type limit = npos) const
		{
			vector<wstringex> v;

			const_iterator 
				i = begin(),
				last = i;
			for (; i != end(); i++)
			{
				if (*i == ' ' || *i == '\n' || *i == '\t' || *i == '\r')
				{
					if (i + 1 != end() && (i[1] == ' ' || i[1] == '\n' || i[1] == '\t' || i[1] == '\r'))
						continue;
					v.push_back(wstringex(last, i));
					last = i + 1;
					if (v.size() >= limit - 1)
					{
						v.push_back(wstringex(last, end()));
						return v;
					}
				}
			}

			if (last != i)
				v.push_back(wstringex(last, i));

			return v;
		}

		/**
		* Split a wstring by a character
		*
		* Returns a vector of ext_strings, each of which is a substring of the wstring formed by splitting
		* it on boundaries formed by the character @p separator.  If @p limit is set, the returned vector
		* will contain a maximum of @p limit elements with the last element containing the rest of
		* the wstring.
		*
		* If @p separator is not found in the wstring, a single element will be returned in the vector
		* containing the entire wstring.
		*
		* The separators are removed from the output
		*
		* @param[in] separator The character separator to split the wstring on
		* @param[in] limit     The maximum number of output elements
		* @return A vector of strings, each of which is a substring of the wstring
		*
		* @section split_ex Example
		* @code
		* std::wstringex s("This|is|a|test.");
		* std::vector<std::wstringex> v = s.split('|');
		* std::copy(v.begin(), v.end(), std::ostream_iterator<std::wstringex>(std::cout, "\n"));
		*
		* This
		* is
		* a
		* test.
		* @endcode
		*/
		vector<wstringex> split(value_type separator, size_type limit = npos) const
		{
			vector<wstringex> v;

			const_iterator 
				i = begin(),
				last = i;
			for (; i != end(); i++)
			{
				if (*i == separator)
				{
					v.push_back(wstringex(last, i));
					last = i + 1;
					if (v.size() >= limit - 1)
					{
						v.push_back(wstringex(last, end()));
						return v;
					}
				}
			}

			if (last != i)
				v.push_back(wstringex(last, i));

			return v;
		}

		/**
		* Split a wstring by another wstring
		*
		* Returns a vector of ext_strings, each of which is a substring of the wstring formed by
		* splitting it on boundaries formed by the wstring @p separator.  If @p limit is set, the
		* returned vector will contain a maximum of @p limit elements with the last element
		* containing the rest of the wstring.
		*
		* If @p separator is not found in the wstring, a single element will be returned in the
		* vector containing the entire wstring.
		*
		* The separators are removed from the output
		*
		* @param[in] separator The wstring separator to split the wstring on
		* @param[in] limit     The maximum number of output elements
		* @return A vector of strings, each of which is a substring of the wstring
		*
		* @ref split_ex
		*/
		vector<wstringex> split(const wstring &separator, size_type limit = npos) const
		{
			vector<wstringex> v;

			const_iterator
				i = begin(),
				last = i;
			for (; i != end(); i++)
			{
				if (wstring(i, i + separator.length()) == separator)
				{
					v.push_back(wstringex(last, i));
					last = i + separator.length();

					if (v.size() >= limit - 1)
					{
						v.push_back(wstringex(last, end()));
						return v;
					}
				}
			}

			if (last != i)
				v.push_back(wstringex(last, i));

			return v;
		}

		/**
		* Convert a wstring into an integer
		*
		* Convert the initial portion of a wstring into a signed integer.  Once a non-numeric
		* character is reached, the remainder of @p wstring is ignored and the integer that was
		* read returned.
		*
		* @param s The wstring to convert
		* @return The integer converted from @p wstring
		*/
		static long int integer(const wstring &s)
		{
			long int retval = 0;
			bool neg = false;

			for (const_iterator i = s.begin(); i != s.end(); i++)
			{
				if (i == s.begin())
				{
					if (*i == '-')
					{
						neg = true;
						continue;
					}
					else if (*i == '+')
						continue;
				}
				if (*i >= '0' && *i <= '9')
				{
					retval *= 10;
					retval += *i - '0';
				}
				else
					break;
			}

			if (neg)
				retval *= -1;

			return retval;
		}

		/**
		* Convert the wstring to an integer
		*
		* Convert the initial portion of the wstring into a signed integer.  Once a non-numeric
		* character is reached, the remainder of the wstring is ignored and the integer that had
		* been read thus far is returned.
		*
		* @return The integer converted from the wstring
		*/
		long int integer() const
		{
			return integer(*this);
		}

		/**
		* Split a wstring into chunks of size @p chunklen.  Returns a vector of strings.
		*
		* Splits a wstring into chunks of the given size.  The final chunk may not fill its
		* entire allocated number of characters.
		*
		* @param[in] chunklen The number of characters per chunk
		* @return A vector of strings, each of length <= chunklen
		*
		* @section chunk_split-ex Example
		* @code
		* std::wstringex s("abcdefghijk");
		* std::vector<std::wstringex> v = s.chunk_split(3);
		* std::copy(v.begin(), v.end(), ostream_iterator<std::wstringex>(cout, " "));
		*
		* abc def ghi jk
		* @endcode
		*/
		vector<wstringex> chunk_split(size_type chunklen) const
		{
			vector<wstringex> retval;
			retval.reserve(size() / chunklen + 1);

			size_type count = 0;
			const_iterator
				i = begin(),
				last = i;
			for (; i != end(); i++, count++)
			{
				if (count == chunklen)
				{
					count = 0;
					retval.push_back(wstringex(last, i));
					last = i;
				}
			}

			if (last != i)
				retval.push_back(wstringex(last, i));

			return retval;
		}

		/**
		* Join a sequence of strings by some glue to create a new wstring
		*
		* Glue is not added to the end of the wstring.
		*
		* @pre [first, last) is a valid range
		* @pre InputIterator is a model of STL's Input Iterator
		* @pre InputIterator must point to a wstring type (std::wstring, std::wstringex, char *)
		*
		* @param[in] glue  The glue to join strings with
		* @param[in] first The beginning of the range to join
		* @param[in] last  The end of the range to join
		* @return A wstring constructed of each element of the range connected together with @p glue
		*
		* @section join_ex Example
		* @code
		* std::vector<std::wstringex> v;
		* v.push_back("This");
		* v.push_back("is");
		* v.push_back("a");
		* v.push_back("test.");
		* std::cout << std::wstringex::join("|", v.begin(), v.end()) << std::endl;
		*
		* This|is|a|test.
		* @endcode
		*/
		template <class InputIterator>
		static wstringex join(const wstring &glue, InputIterator first, InputIterator last)
		{
			wstringex retval;

			for (; first != last; ++first)
			{
				retval.append(*first);
				retval.append(glue);
			}
			retval.erase(retval.length() - glue.length());

			return retval;
		}

		/**
		* Join a sequence of strings by some glue to create a new wstring
		*
		* @copydoc join
		* @ref join_ex
		*/
		template <class InputIterator>
		static wstringex join(value_type glue, InputIterator first, InputIterator last)
		{
			wstringex retval;

			for (; first != last; ++first)
			{
				retval.append(*first);
				retval.append(1, glue);
			}
			retval.erase(retval.length() - 1);

			return retval;
		}

		/**
		* Search for any instances of @p needle and replace them with @p s
		*
		* @param[in] needle The wstring to replace
		* @param[in] s      The replacement wstring
		* @return				*this
		* @post					All instances of @p needle in the wstring are replaced with @p s
		*
		* @section replace-ex Example
		* @code
		* std::wstringex s("This is a test.");
		* s.replace("is", "ere");
		* std::cout << s << std::endl;
		*
		* There ere a test.
		* @endcode
		*/
		wstringex &replace(const wstring &needle, const wstring &s)
		{
			size_type
				lastpos = 0,
				thispos;

			while ((thispos = find(needle, lastpos)) != npos)
			{
				wstring::replace(thispos, needle.length(), s);
				lastpos = thispos + 1;
			}
			return *this;
		}
		wstringex &replace_first(const wstring &needle, const wstring &s)
		{
			size_type
				lastpos = 0,
				thispos;

			if ((thispos = find(needle, lastpos)) != npos)
			{
				wstring::replace(thispos, needle.length(), s);
				lastpos = thispos + 1;
			}
			return *this;
		}
		/**
		* Search of any instances of @p needle and replace them with @p c
		*
		* @param[in] needle The character to replace
		* @param[in] c      The replacement character
		* @return           *this
		* @post             All instances of @p needle in the wstring are replaced with @p c
		*
		* @ref replace-ex
		*/
		wstringex &replace(value_type needle, value_type c)
		{
			for (iterator i = begin(); i != end(); i++)
				if (*i == needle)
					*i = c;

			return *this;
		}

		/**
		* Repeat a wstring @p n times
		*
		* @param[in] n The number of times to repeat the wstring
		* @return wstringex containing @p n copies of the wstring
		*
		* @section repeat-ex Example
		* @code
		* std::wstringex s("123");
		* s = s * 3;
		* std::cout << s << std::endl;
		*
		* 123123123
		* @endcode
		*/
		wstringex operator*(size_type n)
		{
			wstringex retval;
			for (size_type i = 0; i < n; i++)
				retval.append(*this);

			return retval;
		}

		/**
		* Convert the wstring to lowercase
		*
		* @return *this
		* @post The wstring is converted to lowercase
		*/
		wstringex &tolower()
		{
			for (iterator i = begin(); i != end(); i++)
				if (*i >= 'A' && *i <= 'Z')
					*i = (*i) + ('a' - 'A');
			return *this;
		}

		/**
		* Convert the wstring to uppercase
		*
		* @return *this
		* @post The wstring is converted to uppercase
		*/
		wstringex &toupper()
		{
			for (iterator i = begin(); i != end(); i++)
				if (*i >= 'a' && *i <= 'z')
					*i = (*i) - ('a' - 'A');
			return *this;
		}

		/**
		* Count the occurances of @p str in the wstring.
		*
		* @return The count of substrings @p str in the wstring
		*/
		size_type count(const wstring &str) const
		{
			size_type
				count = 0,
				last = 0,
				cur = 0;

			while ((cur = find(str, last + 1)) != npos)
			{
				count++;
				last = cur;
			}

			return count;
		}

		/**
		* Determine if the wstring is alphanumeric
		*
		* @return true if the wstring contains only characters between a-z, A-Z and 0-9 and
		* contains at least one character, else false
		*/
		bool is_alnum() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
			{
				if (*i < 'A' || *i > 'Z')
					if (*i < '0' || *i > '9')
						if (*i < 'a' || *i > 'z')
							return false;
			}

			return true;
		}

		/**
		* Determine if the wstring is alphabetic only
		*
		* @return true of the wstring contains only characters between a-z and A-Z and contains at
		* least one character, else false
		*/
		bool is_alpha() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
				if (*i < 'A' || (*i > 'Z' && (*i < 'a' || *i > 'z')))
					return false;

			return true;
		}

		/**
		* Determine if the wstring is numeric only
		*
		* @return true if the wstring contains only characters between 0-9 and contains at least
		* one character, else false
		*/
		bool is_numeric() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
				if (*i < '0' || *i > '9')
					return false;

			return true;
		}

		/**
		* Determine if a wstring is all lower case
		*
		* @return true if there is at least one character, and all characters are lowercase
		* letters, else false
		*/
		bool is_lower() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
				if (*i < 'a' || *i < 'z')
					return false;

			return true;
		}

		/**
		* Determine if a wstring is all upper case
		*
		* @return true if there is at least one character, and all characters are uppercase
		* letters, else false
		*/
		bool is_upper() const
		{
			if (length() == 0)
				return false;

			for (const_iterator i = begin(); i != end(); i++)
				if (*i < 'A' || *i > 'Z')
					return false;

			return true;
		}

		/**
		* Swap the case of a wstring
		*
		* @post Converts all uppercase to lowercase, and all lowercase to uppercase in the wstring
		* @return *this
		*/
		wstringex &swapcase()
		{
			for (iterator i = begin(); i != end(); i++)
				if (*i >= 'A' && *i <= 'Z')
					*i += ('a' - 'A');
				else if (*i >= 'a' && *i <= 'z')
					*i -= ('a' - 'A');

			return *this;
		}

		/*******************************************************************************
			Function:	std::wstringex::start_with
			Access:		public 
			Qualifier:	const
			Parameter:	const wstring & str			
			Returns:	bool		

			Purpose:	is the wstring start with str
		*******************************************************************************/
		bool start_with(const wstring& str) const
		{
			return ( this->find(str) == 0 );
		}

		/*******************************************************************************
			Function:	std::wstringex::end_with
			Access:		public 
			Qualifier:	const
			Parameter:	const wstring & str			
			Returns:	bool		

			Purpose:	is the wstring end with str
		*******************************************************************************/
		bool end_with(const wstring& str) const
		{
			if (str.length() > this->length())
			{
				return false;
			}
			size_type off = this->length() - str.length();
			return ( find(str, off) == off);
		}

		/*******************************************************************************
			Function:	hl_lib::wstringex::format
			Access:		public 
			Qualifier:	
			Parameter:	const char * format_string
			Parameter:	...
			Returns:	wstringex&

			Purpose:	format the wstring
		*******************************************************************************/
		wstringex& format(const value_type* format_string, ...)
		{
			if (format_string == 0)
			{
				return *this;
			}

			va_list argList;
			value_type* pbuf = 0;
			va_start( argList, format_string );
			int len = _vscwprintf( format_string, argList );
			pbuf = new value_type[len + 1];
			if (pbuf != 0)
			{
				vswprintf_s( pbuf, len + 1, format_string, argList );
				*this = pbuf;
			}
			delete[] pbuf;
			va_end( argList );

			return *this;
		}

		/*******************************************************************************
			Function:	hl_lib::wstringex::trim_left
			Access:		public 
			Qualifier:	
			Parameter:	value_type ch
			Returns:	wstringex&
			
			Purpose:	delete all char which is ch at the left of the string
		*******************************************************************************/
		wstringex& trim_left(value_type ch = ' ')
		{
			size_type off = this->find_first_not_of(ch);
			if (off != string::npos)
			{
				this->erase(0, off);
			}
			return *this;
		}

		/*******************************************************************************
			Function:	hl_lib::wstringex::trim_right
			Access:		public 
			Qualifier:	
			Parameter:	value_type ch
			Returns:	wstringex&
			
			Purpose:	delete all char which is ch at the right of the string
		*******************************************************************************/
		wstringex& trim_right(value_type ch = ' ')
		{
			size_type off = this->find_last_not_of(ch);
			if (off == string::npos)
			{
				off = 0;
			}
			else
			{
				off++;
			}
			this->erase(off, length() - off);
			return *this;
		}

		/*******************************************************************************
			Function:	hl_lib::wstringex::trim
			Access:		public 
			Qualifier:	
			Parameter:	value_type ch
			Returns:	wstringex&
			
			Purpose:	delete all char which is ch at the left and right of the string
		*******************************************************************************/
		wstringex& trim(value_type ch = ' ')
		{
			trim_left(ch);
			trim_right(ch);
			return *this;
		}

		/*******************************************************************************
			Function:	hl_lib::wstringex::float_num
			Access:		public static 
			Qualifier:	
			Parameter:	const wstring & str
			Returns:	double

			Purpose:	parse str to a float number
		*******************************************************************************/
		static double float_num(const wstring& str)
		{
			return _wtof(str.c_str());
		}

		/*******************************************************************************
			Function:	hl_lib::wstringex::float_num
			Access:		public static 
			Qualifier:	
			Returns:	double

			Purpose:	parse this to a float number
		*******************************************************************************/
		double float_num() const
		{
			return float_num(*this);
		}

		/*******************************************************************************
			Function:	hl_lib::wstringex::compare_nocase
			Access:		public 
			Qualifier:	const
			Parameter:	const wstring & str
			Returns:	int

			Purpose:	compare string no case
		*******************************************************************************/
		int compare_nocase(const wstring& str) const
		{
			return _wcsicmp(this->c_str(), str.c_str());
		}

		/*******************************************************************************
			Function:	hl_lib::wstringex::compare_nocase
			Access:		public 
			Qualifier:	const
			Parameter:	size_type index
			Parameter:	size_type length
			Parameter:	const wstring & str
			Returns:	int

			Purpose:	compare substring no case
		*******************************************************************************/
		int compare_nocase( size_type index, size_type length, const wstring &str ) const
		{
			wstringex temp = this->substr(index, length);
			return temp.compare_nocase(str);
		}

		/*******************************************************************************
			Function:	hl_lib::wstringex::compare_nocase
			Access:		public 
			Qualifier:	const
			Parameter:	size_type index
			Parameter:	size_type length
			Parameter:	const wstring & str
			Parameter:	size_type index2
			Parameter:	size_type length2
			Returns:	int

			Purpose:	compare two substring no case
		*******************************************************************************/
		int compare_nocase( size_type index, size_type length, const wstring &str, size_type index2, size_type length2 ) const
		{
			wstringex temp1 = this->substr(index, length);
			wstringex temp2 = str.substr(index2, length2);
			return temp1.compare_nocase(temp2);
		}


	};

}
#endif
