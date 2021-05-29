#pragma once
#include <exception>
#include <string>

#include "stringex.h"

struct UnsupportedOperationException :public std::exception
{
    /**
     *
     */

    std::string str;

    UnsupportedOperationException()
    {
        str = "UnsupportedOperationException";
    }
    UnsupportedOperationException(const std::string& str):std::exception(str.c_str())
    {
        this->str = str;
    }
    std::string toString() { return str; }
    char const* what() const override
    {
        return  str.c_str();
    }
};
struct NullTerminalSymbolsException :public std::exception
{
    /**
     *
     */

    std::string str;
    char const* what() const override
    {
        return  str.c_str();
    }
    NullTerminalSymbolsException()
    {
        str = "NullTerminalSymbolsException";
    }
    NullTerminalSymbolsException(const std::string& str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
struct NullExportedSymbolsException :public std::exception
{
    /**
     *
     */

    std::string str;
    char const* what() const override
    {
        return  str.c_str();
    }
    NullExportedSymbolsException()
    {
        str = "NullExportedSymbolsException";
    }
    NullExportedSymbolsException(const std::string& str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
struct NotDeterministicParseTableException :public std::exception
{
    /**
     *
     */
    char const* what() const override
    {
        return  str.c_str();
    }
    std::string str;

    NotDeterministicParseTableException()
    {
        str = "NotDeterministicParseTableException";
    }
    NotDeterministicParseTableException(const std::string& str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
struct NotBacktrackParseTableException :public std::exception
{
    /**
     *
     */
    char const* what() const override
    {
        return  str.c_str();
    }
    std::string str;

    NotBacktrackParseTableException()
    {
        str = "NotBacktrackParseTableException";
    }
    NotBacktrackParseTableException(const std::string& str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
struct MismatchedInputCharsException :public std::exception
{
    /**
     *
     */
    char const* what() const override
    {
        return  str.c_str();
    }
    std::string str;

    MismatchedInputCharsException()
    {
        str = "MismatchedInputCharsException";
    }
    MismatchedInputCharsException(const std::string& str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
struct BadParseSymFileException :public std::exception
{
    /**
     *
     */
    char const* what() const override
    {
        return  str.c_str();
    }
    std::string str;

    BadParseSymFileException()
    {
        str = "BadParseSymFileException";
    }
    BadParseSymFileException(const std::string& str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
struct TokenStreamNotIPrsStreamException :public std::exception
{
    /**
     *
     */
    char const* what() const override
    {
        return  str.c_str();
    }
    std::string str;

    TokenStreamNotIPrsStreamException()
    {
        str = "TokenStreamNotIPrsStreamException";
    }
    TokenStreamNotIPrsStreamException(const std::string& str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
struct UnavailableParserInformationException :public std::exception
{
    /**
     *
     */
    char const* what() const override
    {
        return  str.c_str();
    }
    std::string str;

    UnavailableParserInformationException()
    {
        str = "Unavailable parser Information Exception";
    }
    UnavailableParserInformationException(std::string str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
struct UndefinedEofSymbolException :public std::exception
{
    /**
     *
     */
    char const* what() const override
    {
        return  str.c_str();
    }
    std::string str;

    UndefinedEofSymbolException()
    {
        str = "UndefinedEofSymbolException";
    }
    UndefinedEofSymbolException(std::string str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
#include <vector>

struct UnimplementedTerminalsException :public std::exception
{
    /**
     *
     */

    std::vector<int> symbols;


    UnimplementedTerminalsException(const  std::vector<int>& _symbols)
    {
        symbols = _symbols;
    }
    std::vector<int>& getSymbols() { return symbols; }
};

struct UnknownStreamType :public std::exception
{
    /**
     *
     */

    std::string str;
    char const* what() const override
    {
        return  str.c_str();
    }
    UnknownStreamType()
    {
        str = "UnknownStreamType";
    }
    UnknownStreamType(const std::string& str)
    {
        this->str = str;
    }
	
    std::string toString() { return str; }
};
struct BadParseException :public std::exception
{
    /**
     *
     */
    std::string  str = "error_token index is: ";
    int error_token = 0;
    BadParseException(int _error_token)
    {
        error_token = _error_token;
        std::stringex format;
        format.format("%d", error_token);
        str += format;
    }
    char const* what() const override
    {

        return  str.c_str();
    }
};

struct StringIndexOutOfBoundsException: public std::exception
{
    std::string str;
    StringIndexOutOfBoundsException(int index):exception("String index out of range: " + index)
    {
        str = "String index out of range: ";
        std::stringex format;
        format.format("%d", index);
        str += format;
    }

    char const* what() const override
    {
        return  str.c_str();
    }
};
