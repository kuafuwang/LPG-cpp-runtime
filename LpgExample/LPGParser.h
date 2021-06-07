
    //#line 163 "btParserTemplateF.gi

#pragma once

#include <iostream>
#include "AstPoolHolder.h"
#include "BacktrackingParser.h"
#include "DeterministicParser.h"
#include "diagnose.h"
#include "ErrorToken.h"
#include "Exception.h"
#include "IAbstractArrayList.h"
#include "IAst.h"
#include "IAstVisitor.h"
#include "ILexStream.h"
#include "LPGParsersym.h"
#include "LPGParserprs.h"
#include "Object.h"
#include "ParseTable.h"
#include "PrsStream.h"
#include "RuleAction.h"
#include "IcuUtil.h"
#include "stringex.h"
#include "Any.h"
#include<sstream>
    //#line 7 "LPGParser.g

    #include <unordered_map>
 
    //#line 190 "btParserTemplateF.gi

    namespace LPGParser_top_level_ast {
	    struct ASTNodeToken;
	    struct terminal;
	    struct nonTerm;
    }

 struct LPGParser :public Object ,public RuleAction
{
   
    PrsStream* prsStream = nullptr;
    ~LPGParser (){
        delete prsStream;
        delete btParser;
    }
     bool unimplementedSymbolsWarning = false;

     inline static ParseTable* prsTable = new LPGParserprs();
     ParseTable* getParseTable() { return prsTable; }

     BacktrackingParser* btParser = nullptr;
     BacktrackingParser* getParser() { return btParser; }

     void setResult(Object* object) { btParser->setSym1(object); }
     Object* getRhsSym(int i) { return btParser->getSym(i); }

     int getRhsTokenIndex(int i) { return btParser->getToken(i); }
     IToken* getRhsIToken(int i) { return prsStream->getIToken(getRhsTokenIndex(i)); }
    
     int getRhsFirstTokenIndex(int i) { return btParser->getFirstToken(i); }
     IToken* getRhsFirstIToken(int i) { return prsStream->getIToken(getRhsFirstTokenIndex(i)); }

     int getRhsLastTokenIndex(int i) { return btParser->getLastToken(i); }
     IToken* getRhsLastIToken(int i) { return prsStream->getIToken(getRhsLastTokenIndex(i)); }

     int getLeftSpan() { return btParser->getFirstToken(); }
     IToken* getLeftIToken()  { return prsStream->getIToken(getLeftSpan()); }

     int getRightSpan() { return btParser->getLastToken(); }
     IToken* getRightIToken() { return prsStream->getIToken(getRightSpan()); }

     int getRhsErrorTokenIndex(int i)
    {
        int index = btParser->getToken(i);
        IToken* err = prsStream->getIToken(index);
        return ( dynamic_cast<ErrorToken*>(err) ? index : 0);
    }
     ErrorToken * getRhsErrorIToken(int i)
    {
        int index = btParser->getToken(i);
        IToken* err = prsStream->getIToken(index);
        return (ErrorToken*) ( dynamic_cast<ErrorToken*>(err) ? err : nullptr);
    }

     void reset(ILexStream* lexStream)
    {
        delete prsStream;
        prsStream = new PrsStream(lexStream);
        btParser->reset(prsStream);

        try
        {
            prsStream->remapTerminalSymbols(orderedTerminalSymbols(), prsTable->getEoftSymbol());
        }
        catch (NullExportedSymbolsException& e) {
        }
        catch (NullTerminalSymbolsException& e) {
        }
        catch (UnimplementedTerminalsException& e)
        {
            if (unimplementedSymbolsWarning) {
               auto unimplemented_symbols = e.getSymbols();
               std::wstringstream  stream;
               stream << "The Lexer will not scan the following token(s):" << std::endl;
                for (int i = 0; i < unimplemented_symbols.size(); i++)
                {
                    auto id = unimplemented_symbols.at(i);
                    stream <<L"    " << LPGParsersym::orderedTerminalSymbols[id] << std::endl;
                }
                stream <<std::endl;
                throw  UndefinedEofSymbolException(IcuUtil::ws2s(stream.str()));
            }
        }
        catch (UndefinedEofSymbolException& e)
        {
            std::stringex str= "The Lexer does not implement the Eof symbol ";
            str += IcuUtil::ws2s(LPGParsersym::orderedTerminalSymbols[prsTable->getEoftSymbol()]);
            throw  UndefinedEofSymbolException(str);
        } 
    }
    
     LPGParser(ILexStream* lexStream = nullptr)
    {
        try
        {
            btParser = new BacktrackingParser(prsStream, prsTable,  this);
        }
        catch (NotBacktrackParseTableException& e)
        {
            throw ( NotBacktrackParseTableException
                                ("Regenerate LPGParserprs.java with -BACKTRACK option"));
        }
        catch (BadParseSymFileException& e)
        {
            throw ( BadParseSymFileException("Bad Parser Symbol File -- LPGParsersym::java"));
        }

        if(lexStream)
        {
            reset(lexStream);
        }
    }
    

    
     int numTokenKinds() { return LPGParsersym::numTokenKinds; }
     std::vector<std::wstring> orderedTerminalSymbols() { 
         return LPGParsersym::orderedTerminalSymbols; 
    }
     std::wstring getTokenKindName(int kind) { return LPGParsersym::orderedTerminalSymbols[kind]; }
     int getEOFTokenKind() { return prsTable->getEoftSymbol(); }
     IPrsStream* getIPrsStream() { return prsStream; }

    /**
     * @deprecated replaced by {@link #getIPrsStream()}
     *
     */
     PrsStream* getPrsStream() { return prsStream; }

    /**
     * @deprecated replaced by {@link #getIPrsStream()}
     *
     */
     PrsStream* getParseStream() { return prsStream; }

     Object* parser()
    {
        return parser(nullptr, 0);
    }
    
     Object* parser(Monitor* monitor)
    {
        return parser(monitor, 0);
    }
    
     Object * parser(int error_repair_count)
    {
        return parser(nullptr, error_repair_count);
    }

     Object * parser(Monitor* monitor, int error_repair_count)
    {
        btParser->setMonitor(monitor);
        
        try
        {
            return (Object *) btParser->fuzzyParse(error_repair_count);
        }
        catch (BadParseException& e)
        {
            prsStream->reset(e.error_token); // point to error token

            std::shared_ptr< DiagnoseParser> diagnoseParser = std::make_shared<DiagnoseParser>(prsStream, prsTable);
            diagnoseParser->diagnose(e.error_token);
        }

        return nullptr;
    }
     void ruleAction(int ruleNumber);
    //
    // Additional entry points, if any
    //
    

    //#line 37 "LPGParser.g

 std::unordered_multimap<std::wstring, IAst*> symtab;
 std::vector<LPGParser_top_level_ast::nonTerm*>  _non_terms;
 std::vector<LPGParser_top_level_ast::terminal*>  _terms;
 std::vector<LPGParser_top_level_ast::ASTNodeToken*>  _macro_name_symbo;
 
    //#line 364 "btParserTemplateF.gi

};

