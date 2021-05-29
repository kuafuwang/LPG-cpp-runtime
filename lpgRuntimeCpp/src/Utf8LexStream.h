#pragma once
#include "ILexStream.h"
#include "ObjectTuple.h"
#include "ParseErrorCodes.h"


//
// LexStreamBase contains an array of characters as the input stream to be parsed.
// There are methods to retrieve and classify characters.
// The lexparser "token" is implemented simply as the index of the next character in the array.
// The user must subclass LexStreamBase and implement the abstract methods: getKind.
//
 struct Utf8LexStream :public ILexStream,public ParseErrorCodes
{
      static  constexpr  int DEFAULT_TAB = 1;

    //
    // For each byte i in the range 0..FF, compute the number of bytes
    // required to store a UTF8 character sequence that starts with i.
    // If i is not a valid starting character for UTF8 then we compute
    // 0. The array charSize is used to store the values.
    //
     static std::vector<int8_t>  charSize;
 	
    

    //
    // Compute the number of bytes required to store a UTF8 character
    // sequence that starts with the character c. The size of a character
    // is always 1 when we are using the Exctended Ascii encoding.
    //
     int getCharSize(int8_t c) { return isUTF8 ? charSize[c & 0x000000FF] : 1; }

    //
    // Compute the code value of a Unicode character encoded in UTF8
    // format in the array inputBytes starting at index i.
    //
      static int getUnicodeValue(shared_ptr_string& bytes, int i);

    //
    // Construct a unicode string from the specified Utf8 substring of bytes.
    //
      std::wstring getString(int offset, int count);
      void this_init();
      void this_tab(int tab);

      int startIndex = -1;
     int index = -1;
     int lastIndex = -1;
     shared_ptr_string inputBytes;
     bool isUTF8= false;
     std::wstring fileName;
     std::shared_ptr<IntSegmentedTuple>  lineOffsets = std::make_shared<IntSegmentedTuple>();

     int tab = DEFAULT_TAB;
     IPrsStream* iPrsStream= nullptr;

 
      // can be used with explicit initialize call

     Utf8LexStream()
     {
         this_init();
     }
     Utf8LexStream(int tab)
     {
         this_tab(tab);
     }
      Utf8LexStream(const std::wstring& fileName, int tab = DEFAULT_TAB);

      Utf8LexStream(shared_ptr_string inputBytes, const std::wstring& fileName);

      Utf8LexStream(std::shared_ptr<IntSegmentedTuple> lineOffsets, shared_ptr_string inputBytes,
                    const std::wstring& fileName);

      Utf8LexStream(shared_ptr_string inputBytes, const std::wstring& fileName, int tab);

     Utf8LexStream(std::shared_ptr< IntSegmentedTuple> lineOffsets, shared_ptr_string inputBytes, const  std::wstring& fileName, int tab)
    {
        this->tab = tab;
        initialize(lineOffsets, inputBytes, fileName);
    }

     bool isUtf8() { return isUTF8; }

     bool isExtendedAscii() { return !isUTF8; }

     void initialize(shared_ptr_string inputBytes,const  std::wstring& fileName)
    {
        setInputBytes(inputBytes);
        setFileName(fileName);
        computeLineOffsets();
    }

      void initialize(std::shared_ptr<IntSegmentedTuple>& lineOffsets, shared_ptr_string inputBytes, const std::wstring& fileName);

      void computeLineOffsets();

      void setInputBytes(shared_ptr_string buffer);

      shared_ptr_string getInputBytes() { return inputBytes; }

     void setFileName(const std::wstring& fileName) { this->fileName = fileName; }

      std::wstring getFileName() { return fileName; }

      void setLineOffsets(std::shared_ptr< IntSegmentedTuple>& lineOffsets)
      {
          this->lineOffsets = lineOffsets;
      }
     std::shared_ptr<IntSegmentedTuple> getLineOffsets() { return lineOffsets; }

     void setTab(int tab) { this->tab = tab; }

     int getTab() { return tab; }

     void setStreamIndex(int index) { this->index = index; }

     int getStreamIndex() { return index; }

     int getStartIndex() { return startIndex; }

     int getLastIndex() { return lastIndex; }

     int getStreamLength() { return inputBytes.size(); }

     void setLineOffset(int i) { lineOffsets->add(i); }

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
     *  it should replaced by:
     *
     *     ... getLineOffsetofLine(line_number) ...
     *
     */
     int getLineOffset(int i) { return lineOffsets->get(i); }

    /**
     *
     * @param i
     * @return
     *
     * Note that 1 is subtracted from the line number before indexing the lineOffsets array.
     * That is because lines are numbered from 1..MAX_LINE_NUMBER, whereas the lineOffsets
     * table is indexed from 0..MAX_LINE_NUMBER-1.
     */
     int getLineOffsetOfLine(int line_number) { return lineOffsets->get(line_number - 1); }

     void setPrsStream(IPrsStream* iPrsStream) { this->iPrsStream = iPrsStream; }

     IPrsStream* getIPrsStream() { return iPrsStream; }

    /**
     * @deprecated replaced by {@link #getIPrsStream()}
     */
     IPrsStream* getPrsStream() { return iPrsStream; }

    std::vector<std::wstring> orderedExportedSymbols() { return {}; }

     wchar_t getCharValue(int i) { return (wchar_t)getUnicodeValue(i); }

     int getIntValue(int i) { return getUnicodeValue(i); }

     int getUnicodeValue(int i)
    {
        return (isUTF8
            ? getUnicodeValue(this->inputBytes, i) // either UTF8
            : inputBytes[i] & 0xFF);              // or Extended Ascii.
    }

     int getLineCount() { return lineOffsets->size(); }

      int getLineNumberOfCharAt(int i);

      int getColumnOfCharAt(int i);

    //
    // Methods that implement the TokenStream Interface.
    // Note that this function updates the lineOffsets table
    // as a side-effect when the next character is a line feed.
    // If this is not the expected behavior then this function should 
    // be overridden.
    //
     int getToken() { return index = getNext(index); }

     int getToken(int end_token)
    {
        return index = (index < end_token ? getNext(index) : lastIndex);
    }

     int getKind(int i) { return 0; }

      int getNext(int i);

      int getPrevious(int i);

      std::wstring getName(int i);

      std::wstring getName(int i, int k);

     int peek() { return getNext(index); }

     void reset(int i) { index = getPrevious(i); }

     void reset() { index = startIndex; }

     int badToken() { return 0; }

     int getLine(int i) { return getLineNumberOfCharAt(i); }

     int getColumn(int i) { return getColumnOfCharAt(i); }

     int getEndLine(int i) { return getLine(i); }

     int getEndColumn(int i) { return getColumnOfCharAt(i); }

     bool afterEol(int i) { return (i < 1 ? true : getLineNumberOfCharAt(getPrevious(i)) < getLineNumberOfCharAt(i)); }

    /**
     * @deprecated replaced by {@link #getFirstRealToken()}
     *
     */
     int getFirstErrorToken(int i) { return getFirstRealToken(i); }
     int getFirstRealToken(int i) { return i; }

    /**
     * @deprecated replaced by {@link #getLastRealToken()}
     *
     */
     int getLastErrorToken(int i) { return getLastRealToken(i); }
     int getLastRealToken(int i) { return i; }

    //
    // Here is where we report errors.  The default method is simply to print the error message to the console.
    // However, the user may supply an error message handler to process error messages.  To support that
    // a message handler interface is provided that has a single method handleMessage().  The user has his
    // error message handler class implement the IMessageHandler interface and provides an object of this type
    // to the runtime using the setMessageHandler(errorMsg) method. If the message handler object is set, 
    // the reportError methods will invoke its handleMessage() method.
    //
     IMessageHandler* errMsg = nullptr;// this is the error message handler object

     void setMessageHandler(IMessageHandler* errMsg) {
        this->errMsg = errMsg;
    }

     IMessageHandler* getMessageHandler() {
        return errMsg;
    }

      void makeToken(int startLoc, int endLoc, int kind);

      void reportLexicalError(int left_loc, int right_loc);

    /**
     * See IMessaageHandler for a description of the int[] return value.
     */
      std::vector<int> getLocation(int left_loc, int right_loc);

      void reportLexicalError(int errorCode, int left_loc, int right_loc, int error_left_loc, int error_right_loc,
                              const std::vector<std::wstring>& errorInfo);


      //
      // Note that when this function is invoked, the leftToken and rightToken are assumed
      // to be indexes into the input stream as the tokens for a lexer are the characters
      // in the input stream.
      //
      void reportError(int errorCode, int leftToken, int rightToken, const std::wstring& errorInfo);

      void reportError(int errorCode, int leftToken, int rightToken, const std::vector<std::wstring>& errorInfo);

      //
      // Note that when this function is invoked, the leftToken and rightToken are assumed
      // to be indexes into the input stream as the tokens for a lexer are the characters
      // in the input stream.
      //
      void reportError(int errorCode, int leftToken, int errorToken, int rightToken, const std::wstring& errorInfo);

      void reportError(int errorCode, int leftToken, int errorToken, int rightToken,
          const std::vector<std::wstring>& errorInfo);

      std::wstring toString(int startOffset, int endOffset);
};
