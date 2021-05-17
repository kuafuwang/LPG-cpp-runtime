#pragma once
#include "Differ.h"

struct DifferLines :  Differ
{
    std::vector<ILine*> line_pool;
    //
    // Class that encodes the meaningful content of a line.
    //
    struct Line : ILine
    {
        std::vector<int>   kind;
        std::vector<std::wstring>  name;

        int hash_code;
        int start_line;
        int start_column;
        int end_line;
        int end_column;
        int buffer_length;

        Line(IPrsStream* stream, int start_token, int gate_token);

        int size() { return kind.size(); }

        int hashCode() { return hash_code; }

        bool equals(ILine* anObject);

        int getStartLine() { return start_line; }
        int getStartColumn() { return start_column; }
        int getEndLine() { return end_line; }
        int getEndColumn() { return end_column; }

        std::wstring toString();
    };

    DifferLines(IPrsStream* newStream, IPrsStream* oldStream);
    ~DifferLines();
     DifferLines() {}

    static void getBuffer(IPrsStream* prsStream, std::vector<ILine*>& line_pool);

    //
    //
    //
    void printLines(IPrsStream* prs_stream, int first_line, int last_line);

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

