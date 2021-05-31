
    //#line 162 "dtParserTemplateF.gi

#pragma once

#include <iostream>
#include "AstPoolHolder.h"
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

    //#line 7 "LPGParser.g


 
    //#line 186 "dtParserTemplateF.gi

 struct LPGParser :public Object ,public RuleAction
{
  
     PrsStream* prsStream = nullptr;
    ~LPGParser (){
        delete prsStream;
        delete dtParser;
    }
     bool unimplementedSymbolsWarning = false;

    inline static ParseTable* prsTable = new LPGParserprs();
     ParseTable* getParseTable() { return prsTable; }

     DeterministicParser* dtParser = nullptr;
     DeterministicParser* getParser() { return dtParser; }

     void setResult(Object* object) { dtParser->setSym1(object); }
     Object* getRhsSym(int i) { return dtParser->getSym(i); }

     int getRhsTokenIndex(int i) { return dtParser->getToken(i); }
     IToken* getRhsIToken(int i) { return prsStream->getIToken(getRhsTokenIndex(i)); }
    
     int getRhsFirstTokenIndex(int i) { return dtParser->getFirstToken(i); }
     IToken* getRhsFirstIToken(int i) { return prsStream->getIToken(getRhsFirstTokenIndex(i)); }

     int getRhsLastTokenIndex(int i) { return dtParser->getLastToken(i); }
     IToken* getRhsLastIToken(int i) { return prsStream->getIToken(getRhsLastTokenIndex(i)); }

     int getLeftSpan() { return dtParser->getFirstToken(); }
     IToken* getLeftIToken()  { return prsStream->getIToken(getLeftSpan()); }

     int getRightSpan() { return dtParser->getLastToken(); }
     IToken* getRightIToken() { return prsStream->getIToken(getRightSpan()); }

     int getRhsErrorTokenIndex(int i)
    {
        int index = dtParser->getToken(i);
        IToken* err = prsStream->getIToken(index);
        return (dynamic_cast<ErrorToken*>(err) ? index : 0);
    }
     ErrorToken* getRhsErrorIToken(int i)
    {
        int index = dtParser->getToken(i);
        IToken* err = prsStream->getIToken(index);
        return (ErrorToken*) (dynamic_cast<ErrorToken*>(err) ? err : nullptr);
    }

     void reset(ILexStream* lexStream)
    {
        delete prsStream;
        prsStream = new PrsStream(lexStream);
        dtParser->reset(prsStream);

        try
        {
            prsStream->remapTerminalSymbols(orderedTerminalSymbols(), prsTable->getEoftSymbol());
        }
        catch(NullExportedSymbolsException& e) {
        }
        catch(NullTerminalSymbolsException& e) {
        }
        catch(UnimplementedTerminalsException& e)
        {
            if (unimplementedSymbolsWarning) {
                auto unimplemented_symbols = e.getSymbols();
                std::cout <<"The Lexer will not scan the following token(s):";
                for (int i = 0; i < unimplemented_symbols.size(); i++)
                {
                    auto id =  unimplemented_symbols[i];
                    std::wcout << L"    " << LPGParsersym::orderedTerminalSymbols[id];               
                }
                std::cout << std::endl;
            }
        }
        catch(UndefinedEofSymbolException& e)
        {
            std::string str = "The Lexer does not implement the Eof symbol ";
            str += IcuUtil::ws2s(LPGParsersym::orderedTerminalSymbols[prsTable->getEoftSymbol()]);
            throw  UndefinedEofSymbolException(str);
        }
    }
    
     LPGParser(ILexStream* lexStream = nullptr)
    {
        try
        {
            dtParser = new DeterministicParser(prsStream, prsTable,  this);
        }
        catch (NotDeterministicParseTableException& e)
        {
            throw  ( NotDeterministicParseTableException
                                ("Regenerate LPGParserprs.java with -NOBACKTRACK option"));
        }
        catch (BadParseSymFileException& e)
        {
            throw  (BadParseSymFileException("Bad Parser Symbol File -- LPGParsersym.cpp. Regenerate LPGParserprs.cpp"));
        }
		if(lexStream){
			reset(lexStream);
		}
    }

    
     int numTokenKinds() { return LPGParsersym::numTokenKinds; }
     std::vector< std::wstring> orderedTerminalSymbols() { return LPGParsersym::orderedTerminalSymbols; }
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
     PrsStream * getParseStream() { return prsStream; }

     Object * parser()
    {
        return parser(nullptr, 0);
    }
        
     Object * parser(Monitor* monitor)
    {
        return parser(monitor, 0);
    }
        
     Object * parser(int error_repair_count)
    {
        return parser(nullptr, error_repair_count);
    }
        
     Object *parser(Monitor* monitor, int error_repair_count)
    {
        dtParser->setMonitor(monitor);

        try
        {
            return (Object *) dtParser->parse();
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

    
 
    //#line 355 "dtParserTemplateF.gi

};

