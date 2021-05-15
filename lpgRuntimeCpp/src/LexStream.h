#pragma once
#include "ILexStream.h"
#include "ObjectTuple.h"
#include "ParseErrorCodes.h"

//
// LexStream contains an array of characters as the input stream to be parsed.
// There are methods to retrieve and classify characters.
// The lexparser "token" is implemented simply as the index of the next character in the array.
// The user must subclass LexStreamBase and implement the abstract methods: getKind.
//
struct LexStream :
    public ILexStream,public ParseErrorCodes
{

    constexpr  static int DEFAULT_TAB = 1;

    int index = -1;
    int streamLength_ = 0;

    shared_ptr_array<wchar_t>  inputChars_;
    std::wstring fileName_;
	
    IntSegmentedTuple lineOffsets;
	
    int tab_ = DEFAULT_TAB;

    /**
     * @deprecated Use function getIPrsStream()
     */
     /*  ... when not deprecated! */ IPrsStream* prsStream;

     LexStream(int tab = DEFAULT_TAB)
     {
         this_tab(tab);
     }
    LexStream(const std::wstring& file_name, int tab= DEFAULT_TAB)
    {
        this_tab(tab);
        initialize(file_name);
    }

    LexStream(shared_ptr_array<wchar_t> inputChars, const std::wstring& file_name)
    {
        this_init();
        initialize(inputChars, inputChars.size(), file_name);
    }

    LexStream(shared_ptr_array<wchar_t>  inputChars, int inputLength, const std::wstring& file_name)
    {
        this_init();
        initialize(inputChars, inputLength, file_name);
    }

    LexStream(IntSegmentedTuple lineOffsets, shared_ptr_array<wchar_t> inputChars, const std::wstring& file_name);

    LexStream(IntSegmentedTuple lineOffsets, shared_ptr_array<wchar_t> inputChars, int inputLength,
              const std::wstring& file_name);

    LexStream(shared_ptr_array<wchar_t> inputChars, const std::wstring& file_name, int tab);

    LexStream(shared_ptr_array<wchar_t> inputChars, int inputLength,const std::wstring& fileName, int tab)
    {
        this_tab(tab);
        initialize(inputChars, inputLength, fileName);
    }

    LexStream(IntSegmentedTuple lineOffsets, shared_ptr_array<wchar_t> inputChars, const std::wstring& fileName, int tab)
    {
        this_tab(tab);
        initialize(lineOffsets, inputChars, inputChars.size(), fileName);
    }

    LexStream(IntSegmentedTuple lineOffsets, std::vector<wchar_t> inputChars, int inputLength, const std::wstring& fileName, int tab)
    {
        this_tab(tab);
        initialize(lineOffsets, inputChars, inputLength, fileName);
    }

    void initialize(const std::wstring& file_name);

    void initialize(shared_ptr_array<wchar_t> inputChars, const std::wstring& fileName)
    {
        initialize(inputChars, inputChars.size(), fileName);
    }

    void initialize(shared_ptr_array<wchar_t> inputChars, int inputLength, const std::wstring& fileName)
    {
        setInputChars(inputChars);
        setStreamLength(inputLength);
        setFileName(fileName);
        computeLineOffsets();
    }

    void initialize(IntSegmentedTuple lineOffsets_, shared_ptr_array<wchar_t> inputChars, const std::wstring& fileName)
    {
        initialize(lineOffsets_, inputChars, inputChars.size(), fileName);
    }

    void initialize(IntSegmentedTuple lineOffsets_, shared_ptr_array<wchar_t> inputChars, int inputLength, const std::wstring& fileName)
    {
        this->lineOffsets = lineOffsets_;
        setInputChars(inputChars);
        setStreamLength(inputLength);
        setFileName(fileName);
    }

    void computeLineOffsets()
    {
        lineOffsets.reset();
        setLineOffset(-1);
        for (int i = 0; i < inputChars_.size(); i++)
            if (inputChars_[i] == 0x0A) setLineOffset(i);
    }

    /**
     *
     * @param offset
     *
     *  update of lineOffsets starting at offset.
     *
     */
    void computeLineOffsets(int offset);

    void setInputChars(shared_ptr_array<wchar_t> inputChars)
    {
        this->inputChars_ = inputChars;
        index = -1; // reset the start index to the beginning of the input
    }

    shared_ptr_array<wchar_t> getInputChars() { return inputChars_; }

    void setFileName(std::wstring fileName) { this->fileName_ = fileName; }

    std::wstring getFileName() { return fileName_; }

    void setLineOffsets(IntSegmentedTuple lineOffsets)
    {
	    this->lineOffsets = lineOffsets;
    }

    IntSegmentedTuple& getLineOffsets() { return lineOffsets; }

    void setTab(int tab) { this->tab_ = tab; }

    int getTab() { return tab_; }

    void setStreamIndex(int index) { this->index = index; }

    int getStreamIndex() { return index; }

    void setStreamLength(int streamLength)
    {
	    this->streamLength_ = streamLength;
    }

    int getStreamLength() { return streamLength_; }

    void setLineOffset(int i)
    {
        lineOffsets.add(i);
    }

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
    int getLineOffset(int i) { return lineOffsets.get(i); }

    /**
     *
     * @param i
     * @return
     *
     * Note that 1 is subtracted from the line number before indexing the lineOffsets array.
     * That is because lines are numbered from 1..MAX_LINE_NUMBER, whereas the lineOffsets
     * table is indexed from 0..MAX_LINE_NUMBER-1.
     */
    int getLineOffsetOfLine(int line_number) { return lineOffsets.get(line_number - 1); }

    void setPrsStream(IPrsStream* prsStream);

    IPrsStream* getIPrsStream() { return prsStream; }

    /**
     * @deprecated replaced by {@link #getIPrsStream()}
     */
    IPrsStream* getPrsStream();

    std::vector< std::wstring> orderedExportedSymbols() { return {}; }

    wchar_t getCharValue(int i) { return inputChars_[i]; }

    int getIntValue(int i) { return inputChars_[i]; }

    /**
     * @deprecated replaced by {@link #getLineCount()}
     *
     */
    int getLine() { return getLineCount(); }
    int getLineCount() { return lineOffsets.size(); }

    int getLineNumberOfCharAt(int i);

    int getColumnOfCharAt(int i)
    {
        int lineNo = getLineNumberOfCharAt(i),
            start = lineOffsets.get(lineNo - 1);
        if (start + 1 >= streamLength_) return 1;
        for (int k = start + 1; k < i; k++)
        {
            if (inputChars_[k] == '\t')
            {
                int offset = (k - start) - 1;
                start -= ((tab_ - 1) - offset % tab_);
            }
        }
        return i - start;
    }

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
        return index = (index < end_token ? getNext(index) : streamLength_);
    }

    int getKind(int i) { return 0; }

    /**
     * @deprecated replaced by {@link #getNext()}
     *
     */
    int next(int i) { return getNext(i); }
    int getNext(int i) { return (++i < streamLength_ ? i : streamLength_); }

    /**
     * @deprecated replaced by {@link #getPrevious()}
     *
     */
    int previous(int i) { return getPrevious(i); }
    int getPrevious(int i) { return (i <= 0 ? 0 : i - 1); }

    std::wstring getName(int i);

    int peek() { return getNext(index); }

    void reset(int i) { index = i - 1; }

    void reset() { index = -1; }

    int badToken() { return 0; }

    /**
     * @deprecated replaced by {@link #getLineNumberOfCharAt()}
     */
    int getLine(int i) { return getLineNumberOfCharAt(i); }

    /**
     * @deprecated replaced by {@link #getColumnOfCharAt()}
     */
    int getColumn(int i) { return getColumnOfCharAt(i); }

    /**
     * @deprecated replaced by {@link #getLineNumberOfCharAt()}
     */
    int getEndLine(int i) { return getLineNumberOfCharAt(i); }

    /**
     * @deprecated replaced by {@link #getColumnOfCharAt()}
     */
    int getEndColumn(int i) { return getColumnOfCharAt(i); }

    bool afterEol(int i) { return (i < 1 ? true : getLineNumberOfCharAt(i - 1) < getLineNumberOfCharAt(i)); }

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
    // error message handler class implement the IMessageHandler* interface and provides an object of this type
    // to the runtime using the setMessageHandler(errorMsg) method. If the message handler object is set, 
    // the reportError methods will invoke its handleMessage() method.
    //
    IMessageHandler* errMsg = nullptr;// this is the error message handler object

    void setMessageHandler(IMessageHandler* errMsg) { this->errMsg = errMsg; }

    IMessageHandler* getMessageHandler() { return errMsg; }

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

private:
    void this_init(); // can be used with explicit initialize call

    void this_tab(int tab);
};

