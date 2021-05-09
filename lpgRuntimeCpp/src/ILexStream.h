#pragma once
#include "TokenStream.h"

struct IPrsStream;

struct  IMessageHandler;

struct ILexStream : public TokenStream
{

	
   virtual   IPrsStream* getIPrsStream()=0;

    /**
     * @deprecated replaced by {@link #getIPrsStream()}
     */
   virtual  IPrsStream* getPrsStream()=0;

   virtual  void setPrsStream(IPrsStream* stream)=0;

   virtual  int getLineCount()=0;

   virtual  std::vector<std::wstring> orderedExportedSymbols()=0;

    /**
     * @deprecated Use function getLineOffsetOfLine()
     *
     * This function was deprecated because it exposes an implementation detail that
     * should be hidden. I.e., lines are numbered from 1..MAX_LINE_NUMBER, whereas
     * the line offset table is indexed from 0..MAX_LINE_NUMBER-1.
     *
     * Thus, if a user has a call that reads:
     *
     *     ... getLineOffset(line_number - 1) ...
     *
     *  it should be replaced by:
     *
     *     ... getLineOffsetofLine(line_number) ...
     *
     */
   virtual int getLineOffset(int i)=0;

    /**
     *
     * @param i
     * @return
     *
     * Note that 1 is subtracted from the line number before indexing the lineOffsets array.
     * That is because lines are numbered from 1..MAX_LINE_NUMBER, whereas the lineOffsets
     * table is indexed from 0..MAX_LINE_NUMBER-1.
     */
   virtual  int getLineOffsetOfLine(int line_number)=0;

   virtual int getLineNumberOfCharAt(int i)=0;

   virtual int getColumnOfCharAt(int i)=0;

   virtual wchar_t getCharValue(int i)=0;

   virtual int getIntValue(int i)=0;

   virtual void makeToken(int startLoc, int endLoc, int kind)=0;

   virtual void setMessageHandler(IMessageHandler* errMsg)=0;
   virtual  IMessageHandler* getMessageHandler()=0;

    /**
     * See IMessaageHandler for a description of the int[] return value.
     */
   virtual std::vector<int> getLocation(int left_loc, int right_loc)=0;

   virtual void reportLexicalError(int left, int right)=0;

   virtual void reportLexicalError(int errorCode, int left_loc, int right_loc, int error_left_loc, int error_right_loc, const std::vector<std::wstring>& errorInfo)=0;

   virtual std::wstring toString(int startOffset, int endOffset)=0;
};
