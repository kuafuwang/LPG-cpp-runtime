#pragma once


#include "IPrsStream.h"
#include "ParseErrorCodes.h"
#include "tuple.h"
struct LexStream;
//
// PrsStream holds an arraylist of tokens "lexed" from the input stream.
//
struct PrsStream :public IPrsStream, public ParseErrorCodes
{

    ILexStream* iLexStream;
    shared_ptr_array<int> kindMap;
    Tuple<IToken*> tokens;
    Tuple<IToken*> rangeTokens;
    Tuple<IToken*> adjuncts;
    int index = 0;
    int len = 0;
    ~PrsStream();
    PrsStream();

    PrsStream(ILexStream* iLexStream);

    std::vector<std::wstring> orderedExportedSymbols() { return {}; }

    void remapTerminalSymbols(const std::vector<std::wstring>& ordered_parser_symbols, int eof_symbol);

    int mapKind(int kind) { return (kindMap.size() == 0 ? kind : kindMap[kind]); }

    void resetTokenStream();

    void setLexStream(ILexStream* lexStream);

    /**
     * @deprecated function
     */
    void resetLexStream(LexStream* lexStream);

    void makeToken(int startLoc, int endLoc, int kind);

    /**
     *
     * @param token
     * @param offset_adjustment
     */
    void makeToken(IToken* token, int offset_adjustment);

    void removeLastToken();

    int makeErrorToken(int firsttok, int lasttok, int errortok, int kind);

    void addToken(IToken* token);

    void makeAdjunct(int startLoc, int endLoc, int kind);

    /**
     *
     * @param adjunct
     * @param offset_adjustment
     */
    void makeAdjunct(IToken* adjunct, int offset_adjustment);

    void addAdjunct(IToken* adjunct);

    std::wstring getTokenText(int i);

    int getStartOffset(int i);

    int getEndOffset(int i);

    int getTokenLength(int i);

    int getLineNumberOfTokenAt(int i);

    int getEndLineNumberOfTokenAt(int i);

    int getColumnOfTokenAt(int i);

    int getEndColumnOfTokenAt(int i);

    std::vector< std::wstring > orderedTerminalSymbols() { return {}; }

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
    int getLineOffset(int i);

    int getLineOffsetOfLine(int i);

    int getLineCount();

    int getLineNumberOfCharAt(int i);

    int getColumnOfCharAt(int i) { return getColumnOfCharAt(i); }

    /**
     * @deprecated replaced by {@link #getFirstRealToken(int i)}
     *
     */
    int getFirstErrorToken(int i) { return getFirstRealToken(i); }
    int getFirstRealToken(int i);

    /**
     * @deprecated replaced by {@link #getLastRealToken(int i)}
     *
     */
    int getLastErrorToken(int i) { return getLastRealToken(i); }
    int getLastRealToken(int i);

    void addTokensInRangeToList(std::vector<IToken*>& list, IToken* start_token, IToken* end_token) ;

    // TODO: should this function throw an exception instead of returning nullptr?
    shared_ptr_wstring getInputChars();

    // TODO: should this function throw an exception instead of returning nullptr?
    shared_ptr_string getInputBytes();

    std::wstring toString(int first_token, int last_token);

    std::wstring toString(IToken* t1, IToken* t2);

    int getSize() { return tokens.size(); }

    /**
     * @deprecated replaced by {@link #setStreamLength()}
     *
     */
    void setSize() { len = tokens.size(); }

    //
    // This function returns the index of the token element
    // containing the offset specified. If such a token does
    // not exist, it returns the negation of the index of the 
    // element immediately preceding the offset.
    //
    int getTokenIndexAtCharacter(int offset);

    IToken* getTokenAtCharacter(int offset)
    {
        int tokenIndex = getTokenIndexAtCharacter(offset);
        return (tokenIndex < 0) ? nullptr : getTokenAt(tokenIndex);
    }

    IToken* getTokenAt(int i) { return (IToken*)tokens.get(i); }

    /**
     * @deprecated replaced by {@link #getTokenAt()}
     */
    IToken* getIToken(int i);

    Tuple<IToken*> getTokens() { return tokens; }

    int getStreamIndex() { return index; }

    int getStreamLength() { return len; }

    void setStreamIndex(int index) { this->index = index; }

    void setStreamLength() { this->len = tokens.size(); }

    void setStreamLength(int len) { this->len = len; }

    ILexStream* getILexStream() { return iLexStream; }

    /**
     * @deprecated replaced by {@link #getILexStream()}
     */
    ILexStream* getLexStream() { return iLexStream; }

    void dumpTokens();

    void dumpToken(int i);

    /**
     *
     * @param damage_offset
     * @return
     *
     * If an update occurred in the input stream, calculate the token (or adjunct)
     * where to start rescanning. Reset the stream accordingly and return the list
     * of starting offset of the tokens that were removed from the stream.
     */
    Tuple<IToken*> incrementalResetAtCharacterOffset(int damage_offset);

    std::vector<IToken*> getAdjuncts(int i);

    //
    // Return an iterator for the adjuncts that follow token i.
    //
    std::vector<IToken*> getFollowingAdjuncts(int i)
    {
        return getAdjuncts(i);
    }

    std::vector<IToken*> getPrecedingAdjuncts(int i)
    {
        return getAdjuncts(getPrevious(i));
    }

    IToken* getAdjunctAt(int i) { return (IToken*)adjuncts.get(i); }

    Tuple<IToken*> getAdjuncts() { return adjuncts; }

    //
    // Methods that implement the TokenStream Interface
    //
    int getToken()
    {
        index = getNext(index);
        return index;
    }

    int getToken(int end_token)
    {
        return index = (index < end_token ? getNext(index) : len - 1);
    }

    int getKind(int i);

    int getNext(int i) { return (++i < len ? i : len - 1); }

    int getPrevious(int i) { return (i <= 0 ? 0 : i - 1); }

    std::wstring getName(int i) { return getTokenText(i); }

    int peek() { return getNext(index); }

    void reset(int i) { index = getPrevious(i); }

    void reset() { index = 0; }

    int badToken() { return 0; }

    int getLine(int i) { return getLineNumberOfTokenAt(i); }

    int getColumn(int i) { return getColumnOfTokenAt(i); }

    int getEndLine(int i) { return getEndLineNumberOfTokenAt(i); }

    int getEndColumn(int i) { return getEndColumnOfTokenAt(i); }

    bool afterEol(int i) { return (i < 1 ? true : getEndLineNumberOfTokenAt(i - 1) < getLineNumberOfTokenAt(i)); }

    std::wstring getFileName();

    //
    // Here is where we report errors.  The default method is simply to print the error message to the console.
    // However, the user may supply an error message handler to process error messages.  To support that
    // a message handler interface is provided that has a single method handleMessage().  The user has his
    // error message handler class implement the IMessageHandler interface and provides an object of this type
    // to the runtime using the setMessageHandler(errorMsg) method. If the message handler object is set, 
    // the reportError methods will invoke its handleMessage() method.
    //
    // IMessageHandler errMsg = nullptr; // the error message handler object is declared in LexStream
    //
    void setMessageHandler(IMessageHandler* errMsg);

    IMessageHandler* getMessageHandler();

    void reportError(int errorCode, int leftToken, int rightToken, const std::wstring& errorInfo);

    void reportError(int errorCode, int leftToken, int rightToken,const std::vector<std::wstring>& errorInfo);

    void reportError(int errorCode, int leftToken, int errorToken, int rightToken, const std::wstring& errorInfo);

    void reportError(int errorCode, int leftToken, int errorToken, int rightToken,
        const  std::vector<std::wstring>& errorInfo);

private:
    void internalResetTokenStream();
};
