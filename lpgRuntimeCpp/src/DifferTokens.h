#pragma once
#include "Differ.h"

struct DifferTokens:  public Differ
{
    std::vector<ILine*> line_pool;
    //
    // Class that encodes the meaningful content of a line.
    //
    struct Token : ILine
    {
        int kind,
            start_line,
            start_column,
            end_line,
            end_column;
        std::wstring name;

        int hash_code;

        Token(IPrsStream* stream, int token);

        int size() { return name.length(); }

        int hashCode() { return hash_code; }

        bool equals(ILine* anObject);

        int getStartLine() { return start_line; }
        int getStartColumn() { return start_column; }
        int getEndLine() { return end_line; }
        int getEndColumn() { return end_column; }
        std::wstring toString() { return this->name; }
    };
    ~DifferTokens();
    DifferTokens();

    DifferTokens(IPrsStream* newStream, IPrsStream* oldStream);

    static void getBuffer(IPrsStream* prsStream, std::vector<ILine*>& line_pool);

    //
    //
    //
    void printLines(IPrsStream* prs_stream, int first_token, int last_token);

    //
    //
    //
    void outputInsert(Change* element);

    //
    //
    //
    void outputDelete(Change* element);

    //
    //
    //
    void outputReplace(Change* element);

    //
    //
    //
    void outputMove(Change* element);

    //
    //
    //
    void outputMoveDelete(Change* element);

    //
    //
    //
    void outputMoveInsert(Change* element);
};


