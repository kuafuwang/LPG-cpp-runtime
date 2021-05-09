#pragma once
#include "IToken.h"
struct AbstractToken :
  public   IToken
{
      int kind = 0,
        startOffset = 0,
        endOffset = 0,
        tokenIndex = 0,
        adjunctIndex = 0;
     IPrsStream* iPrsStream = nullptr;

     AbstractToken() {}
     AbstractToken(IPrsStream* iPrsStream, int startOffset, int endOffset, int kind)
    {
       this->iPrsStream = iPrsStream;
       this->startOffset = startOffset;
       this->endOffset = endOffset;
       this->kind = kind;
    }

     int getKind() { return kind; }
     void setKind(int kind) {this->kind = kind; }

     int getStartOffset() { return startOffset; }
     void setStartOffset(int start_offset)
    {
       this->startOffset = start_offset;
    }

     int getEndOffset() { return endOffset; }
     void setEndOffset(int endOffset)
    {
       this->endOffset = endOffset;
    }

     int getTokenIndex() { return tokenIndex; }
     void setTokenIndex(int tokenIndex) {this->tokenIndex = tokenIndex; }

     void setAdjunctIndex(int adjunctIndex) {this->adjunctIndex = adjunctIndex; }
     int getAdjunctIndex() { return adjunctIndex; }

     IPrsStream* getIPrsStream() { return iPrsStream; }
      ILexStream* getILexStream();
      int getLine();
      int getColumn();
      int getEndLine();
      int getEndColumn();

    /**
     * @deprecated replaced by {@link #getIPrsStream()}
     */
     IPrsStream* getPrsStream() { return iPrsStream; }


    /**
     * @deprecated replaced by {@link #getILexStream()}
     */
      ILexStream* getLexStream();

    /**
     * @deprecated replaced by {@link #toString()}
     */
      std::wstring getValue(std::vector<wchar_t>& inputChars);

      std::wstring toString();
};

