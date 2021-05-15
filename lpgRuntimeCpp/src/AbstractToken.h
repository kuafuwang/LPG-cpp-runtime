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
      AbstractToken(IPrsStream* iPrsStream, int startOffset, int endOffset, int kind);

      int getKind();
      void setKind(int kind);

      int getStartOffset();
      void setStartOffset(int start_offset);

      int getEndOffset();
      void setEndOffset(int endOffset);

      int getTokenIndex();
      void setTokenIndex(int tokenIndex);

      void setAdjunctIndex(int adjunctIndex);
      int getAdjunctIndex();

      IPrsStream* getIPrsStream();
      ILexStream* getILexStream();
      int getLine();
      int getColumn();
      int getEndLine();
      int getEndColumn();

      std::wstring toString();
};

