#pragma once
#include "TokenStream.h"
#include "tuple.h"

struct ILexStream;
struct IMessageHandler;
struct IToken;

struct IPrsStream :public  TokenStream
{

    struct Range {

        Range(IPrsStream* iprs_stream, IToken* start_token, IToken* end_token) : list(nullptr)
        {
            this->iprsStream = iprs_stream;
            this->startToken = start_token;
            this->endToken = end_token;
        }
        ~Range()
        {
            delete list;
        }
        IPrsStream* iprsStream;
        IToken* startToken;
        IToken* endToken;
        std::vector<IToken*>* list;

        IToken* getStartToken() { return startToken; }
        IToken* getEndToken() { return endToken; }

        const std::vector<IToken*>& getTokenList() {
            if (list == nullptr) {
                list = new std::vector<IToken*>();
                iprsStream->addTokensInRangeToList(*list, startToken, endToken);
            }
            return *list;
        }
    };

    virtual   IMessageHandler* getMessageHandler()=0;
    virtual    void setMessageHandler(IMessageHandler* errMsg)=0;

    virtual    ILexStream* getILexStream()=0;

    /**
     * @deprecated replaced by {@link #getILexStream()}
     */
    virtual   ILexStream* getLexStream()=0;

    virtual    void setLexStream(ILexStream* lexStream)=0;

    /**
     * @deprecated replaced by {@link #getFirstRealToken()}
     *
     */
    virtual    int getFirstErrorToken(int i)=0;

    /**
     * @deprecated replaced by {@link #getLastRealToken()}
     *
     */
    virtual   int getLastErrorToken(int i)=0;

    virtual    void makeToken(int startLoc, int endLoc, int kind)=0;

    virtual    void makeToken(IToken* token, int offset_adjustment)=0;

    virtual    void makeAdjunct(int startLoc, int endLoc, int kind)=0;

    virtual   void makeAdjunct(IToken* token, int offset_adjustment)=0;

    virtual    void removeLastToken()=0;

    virtual   void addTokensInRangeToList(std::vector<IToken*>& list, IToken* start_token, IToken* end_token)=0;

    virtual    int getLineCount()=0;

    virtual    int getSize()=0;

    virtual    void remapTerminalSymbols(const std::vector<std::wstring>& ordered_parser_symbols, int eof_symbol)=0;
  
    virtual    std::vector<std::wstring> orderedTerminalSymbols()=0;

    virtual   int mapKind(int kind)=0;

    virtual   void resetTokenStream()=0;

    virtual    int getStreamIndex()=0;

    virtual   void setStreamIndex(int index)=0;

    virtual   void setStreamLength()=0;

    virtual   void setStreamLength(int len)=0;

    virtual   void addToken(IToken* token)=0;

    virtual   void addAdjunct(IToken* adjunct)=0;

    virtual    std::vector<std::wstring> orderedExportedSymbols()=0;

    virtual   Tuple <IToken*> getTokens()=0;

    virtual   Tuple<IToken*> getAdjuncts()=0;

    virtual std::vector<IToken*> getFollowingAdjuncts(int i) =0;

    virtual std::vector<IToken*> getPrecedingAdjuncts(int i) =0;

    virtual    IToken* getIToken(int i)=0;

    virtual    std::wstring getTokenText(int i)=0;

    virtual   int getStartOffset(int i)=0;

    virtual   int getEndOffset(int i)=0;

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
    virtual    int getLineOffset(int i)=0;

    /**
     *
     * @param i
     * @return
     *
     * Note that 1 is subtracted from the line number before indexing the lineOffsets array.
     * That is because lines are numbered from 1..MAX_LINE_NUMBER, whereas the lineOffsets
     * table is indexed from 0..MAX_LINE_NUMBER-1.
     */
    virtual    int getLineOffsetOfLine(int line_number)=0;

    virtual    int getLineNumberOfCharAt(int i)=0;

    virtual    int getColumnOfCharAt(int i)=0;

    virtual    int getTokenLength(int i)=0;

    virtual    int getLineNumberOfTokenAt(int i)=0;

    virtual   int getEndLineNumberOfTokenAt(int i)=0;

    virtual   int getColumnOfTokenAt(int i)=0;

    virtual   int getEndColumnOfTokenAt(int i)=0;

    virtual    Tuple<IToken*> incrementalResetAtCharacterOffset(int damage_offset)=0;

    virtual    shared_ptr_wstring getInputChars()=0;

    virtual   shared_ptr_string  getInputBytes()=0;

    virtual   std::wstring toString(int first_token, int last_token)=0;

    virtual   std::wstring toString(IToken* t1, IToken* t2)=0;

    virtual    int getTokenIndexAtCharacter(int offset)=0;

    virtual   IToken* getTokenAtCharacter(int offset)=0;

    virtual    IToken* getTokenAt(int i)=0;

    virtual    IToken* getAdjunctAt(int i)=0;

    virtual    void dumpTokens()=0;

    virtual    void dumpToken(int i)=0;

    virtual    int makeErrorToken(int first, int last, int error, int kind)=0;
};
