#pragma once
#include <exception>
#include <string>

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
    UnsupportedOperationException(const std::string& str)
    {
        this->str = str;
    }
    std::string toString() { return str; }
};
struct NullTerminalSymbolsException :public std::exception
{
    /**
     *
     */

    std::string str;

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

    int error_token = 0;
    BadParseException(int _error_token)
    {
        error_token = _error_token;
    }
};
