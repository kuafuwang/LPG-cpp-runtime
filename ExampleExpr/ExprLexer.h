
    //#line 122 "LexerTemplateD.g



    //#line 128 "LexerTemplateD.g


#pragma once  
#include <string>
#include <iostream>
#include "IPrsStream.h"
#include "Object.h"
#include "ParseTable.h"
#include "RuleAction.h"
#include "stringex.h"
#include "Token.h"
#include "ExprLexersym.h"
#include "ExprLexerprs.h"
#include "ExprParsersym.h"
#include "LexParser.h"
#include "LpgLexStream.h"

 struct ExprLexer :public LpgLexStream ,public ExprParsersym, public ExprLexersym,public RuleAction
{
    inline  static ParseTable* prs = new ExprLexerprs();

    ~ExprLexer(){
        delete lexParser;
    }
     ParseTable* getParseTable() { return prs; }

     LexParser* lexParser = new LexParser(this, prs, this);
     LexParser* getParser() { return lexParser; }

     int getToken(int i) { return lexParser->getToken(i); }
     int getRhsFirstTokenIndex(int i) { return lexParser->getFirstToken(i); }
     int getRhsLastTokenIndex(int i) { return lexParser->getLastToken(i); }

     int getLeftSpan() { return lexParser->getToken(1); }
     int getRightSpan() { return lexParser->getLastToken(); }

     ExprLexer(const std::wstring& filename, int tab) : LpgLexStream (filename, tab)
    {
       
    }

     ExprLexer(shared_ptr_wstring& input_chars, const std::wstring& filename, int tab=1)
     : LpgLexStream (input_chars, filename, tab)
    {
       
    }


     ExprLexer() {}

     std::vector<std::wstring> orderedExportedSymbols() { return ExprParsersym::orderedTerminalSymbols; }
     LexStream* getLexStream() { return (LexStream*) this; }

     void initializeLexer(IPrsStream * prsStream, int start_offset, int end_offset)
    {
        if (getInputChars().size() == 0)
            throw  std::exception("LexStream was not initialized");
        setPrsStream(prsStream);
        prsStream->makeToken(start_offset, end_offset, 0); // Token list must start with a bad token
    }

     void addEOF(IPrsStream * prsStream, int end_offset)
    {
        prsStream->makeToken(end_offset, end_offset, ExprParsersym::TK_EOF_TOKEN); // and end with the end of file token
        prsStream->setStreamLength(prsStream->getSize());
    }

     void lexer(IPrsStream *prsStream)
    {
        lexer(nullptr, prsStream);
    }
    
     void lexer(Monitor* monitor, IPrsStream * prsStream)
    {
        initializeLexer(prsStream, 0, -1);
        lexParser->parseCharacters(monitor);  // Lex the input characters
        addEOF(prsStream, getStreamIndex());
    }

     void lexer(IPrsStream *prsStream, int start_offset, int end_offset)
    {
        lexer(nullptr, prsStream, start_offset, end_offset);
    }
    
     void lexer(Monitor* monitor, IPrsStream *prsStream, int start_offset, int end_offset)
    {
        if (start_offset <= 1)
             initializeLexer(prsStream, 0, -1);
        else initializeLexer(prsStream, start_offset - 1, start_offset - 1);

        lexParser->parseCharacters(monitor, start_offset, end_offset);

        addEOF(prsStream, (end_offset >= getStreamIndex() ? getStreamIndex() : end_offset + 1));
    }

    /**
     * If a parse stream was not passed to this Lexical analyser then we
     * simply report a lexical error. Otherwise, we produce a bad token.
     */
     void reportLexicalError(int startLoc, int endLoc) {
        IPrsStream *prs_stream = getPrsStream();
        if (prs_stream == nullptr)
            LpgLexStream ::reportLexicalError(startLoc, endLoc);
        else {
            //
            // Remove any token that may have been processed that fall in the
            // range of the lexical error... then add one error token that spans
            // the error range.
            //
            for (int i = prs_stream->getSize() - 1; i > 0; i--) {
                if (prs_stream->getStartOffset(i) >= startLoc)
                     prs_stream->removeLastToken();
                else break;
            }
            prs_stream->makeToken(startLoc, endLoc, 0); // add an error token to the prsStream
        }        
    }

    //#line 11 "ExprLexer.g

     void makeToken(int kind)
    {
        int startOffset = getLeftSpan(), endOffset = getRightSpan();
        LpgLexStream ::makeToken(startOffset, endOffset, kind);
    }
  
    int getKind(int i)  // Classify character at ith location
    {
        int c = (i >= getStreamLength() ? 0xffff : getCharValue(i));
        return (c <  33		? Char_WSChar : 
        		c>= '0' && c <= '9' ? Char_Digit :
        		c == '+' 		? Char_Plus :
        		c == '*' 		? Char_Star :
        		c == '(' 		? Char_LeftParen :
        		c == ')' 		? Char_RightParen :
        		c == 0xffff 	? Char_EOF : 
        					  Char_Unused);
    }

    //#line 248 "LexerTemplateD.g

     void ruleAction(int ruleNumber)
    {
        switch(ruleNumber)
        {
 
            //
            // Rule 1:  Token ::= IntegerLiteral
            //
            case 1: { 
                makeToken(ExprParsersym::TK_IntegerLiteral);
                break;
            }
     
            //
            // Rule 2:  Token ::= +
            //
            case 2: { 
                makeToken(ExprParsersym::TK_PLUS);
                break;
            }
     
            //
            // Rule 3:  Token ::= *
            //
            case 3: { 
                makeToken(ExprParsersym::TK_MULTIPLY);
                break;
            }
     
            //
            // Rule 4:  Token ::= (
            //
            case 4: { 
                makeToken(ExprParsersym::TK_LPAREN);
                break;
            }
     
            //
            // Rule 5:  Token ::= )
            //
            case 5: { 
                makeToken(ExprParsersym::TK_RPAREN);
                break;
            }
    
    //#line 252 "LexerTemplateD.g

    
            default:
                break;
        }
        return;
    }
};

