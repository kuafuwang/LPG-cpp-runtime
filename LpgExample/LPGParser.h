
    //#line 157 "dtParserTemplateF.gi



    //#line 7 "LPGParser.g

#pragma once

#include <iostream>

#include "DeterministicParser.h"
#include "diagnose.h"
#include "ErrorToken.h"
#include "Exception.h"
#include "IAbstractArrayList.h"
#include "IAst.h"
#include "IAstVisitor.h"
#include "ILexStream.h"
#include "LPGParserprs.h"
#include "LPGParsersym.h"
#include "Object.h"
#include "ParseTable.h"
#include "PrsStream.h"
#include "RuleAction.h"
#include "IcuUtil.h"
 
    //#line 163 "dtParserTemplateF.gi

 struct LPGParser :public Object ,public RuleAction
{
     PrsStream* prsStream = nullptr;
    
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

            auto diagnoseParser = new DiagnoseParser(prsStream, prsTable);
            diagnoseParser->diagnose(e.error_token);
        }

        return nullptr;
    }

    //
    // Additional entry points, if any
    //
    

    //#line 55 "LPGParser.g

    
   struct ASTNode;
  struct AbstractASTNodeList;
  struct ASTNodeToken;
  struct LPG;
  struct LPG_itemList;
  struct AliasSeg;
  struct AstSeg;
  struct DefineSeg;
  struct EofSeg;
  struct EolSeg;
  struct ErrorSeg;
  struct ExportSeg;
  struct GlobalsSeg;
  struct HeadersSeg;
  struct IdentifierSeg;
  struct ImportSeg;
  struct IncludeSeg;
  struct KeywordsSeg;
  struct NamesSeg;
  struct NoticeSeg;
  struct RulesSeg;
  struct SoftKeywordsSeg;
  struct StartSeg;
  struct TerminalsSeg;
  struct TrailersSeg;
  struct TypesSeg;
  struct RecoverSeg;
  struct PredecessorSeg;
  struct option_specList;
  struct option_spec;
  struct optionList;
  struct option;
  struct SYMBOLList;
  struct aliasSpecList;
  struct alias_lhs_macro_name;
  struct defineSpecList;
  struct defineSpec;
  struct macro_segment;
  struct terminal_symbolList;
  struct action_segmentList;
  struct import_segment;
  struct drop_commandList;
  struct drop_ruleList;
  struct drop_rule;
  struct optMacroName;
  struct include_segment;
  struct keywordSpecList;
  struct keywordSpec;
  struct nameSpecList;
  struct nameSpec;
  struct rules_segment;
  struct nonTermList;
  struct nonTerm;
  struct RuleName;
  struct ruleList;
  struct rule;
  struct symWithAttrsList;
  struct symAttrs;
  struct action_segment;
  struct start_symbolList;
  struct terminalList;
  struct terminal;
  struct optTerminalAlias;
  struct type_declarationsList;
  struct type_declarations;
  struct symbol_pairList;
  struct symbol_pair;
  struct recover_symbol;
  struct END_KEY_OPT;
  struct option_value0;
  struct option_value1;
  struct aliasSpec0;
  struct aliasSpec1;
  struct aliasSpec2;
  struct aliasSpec3;
  struct aliasSpec4;
  struct aliasSpec5;
  struct alias_rhs0;
  struct alias_rhs1;
  struct alias_rhs2;
  struct alias_rhs3;
  struct alias_rhs4;
  struct alias_rhs5;
  struct alias_rhs6;
  struct macro_name_symbol0;
  struct macro_name_symbol1;
  struct drop_command0;
  struct drop_command1;
  struct name0;
  struct name1;
  struct name2;
  struct name3;
  struct name4;
  struct name5;
  struct produces0;
  struct produces1;
  struct produces2;
  struct produces3;
  struct symWithAttrs0;
  struct symWithAttrs1;
  struct start_symbol0;
  struct start_symbol1;
  struct terminal_symbol0;
  struct terminal_symbol1;
  struct Visitor;
  struct AbstractVisitor;
 Tuple<IAst*> ast_pool;
    struct ASTNode :public IAst
    {
        IAst* getNextAst() { return nullptr; }
         IToken* leftIToken=nullptr;
            IToken*    rightIToken=nullptr;
         IAst* parent = nullptr;
         void setParent(IAst* parent) { this->parent = parent; }
        IAst* getParent() { return parent; }

        IToken* getLeftIToken() { return leftIToken; }
        IToken* getRightIToken() { return rightIToken; }
        std::vector<IToken*> getPrecedingAdjuncts() { return leftIToken->getPrecedingAdjuncts(); }
        std::vector<IToken*> getFollowingAdjuncts() { return rightIToken->getFollowingAdjuncts(); }

        std::wstring toString()
        {
            return leftIToken->getILexStream()->toString(leftIToken->getStartOffset(), rightIToken->getEndOffset());
        }

        ASTNode(IToken* token) { this->leftIToken = this->rightIToken = token; }
        ASTNode(IToken* leftIToken, IToken* rightIToken)
        {
            this->leftIToken = leftIToken;
            this->rightIToken = rightIToken;
        }

        void initialize() {}

        /**
         * A list of all children of this node, excluding the nullptr ones.
         */
        std::vector<IAst*> getChildren()
        {
            std::vector<IAst*> list = getAllChildren();
            int k = -1;
            for (int i = 0; i < list.size(); i++)
            {
                IAst* element = list[i];
                if (element != nullptr)
                {
                    if (++k != i)
                        list[k]=(element);
                }
            }
            for (int i = list.size() - 1; i > k; i--) // remove extraneous elements
               list.erase(list.begin()+i);
            return list;
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        virtual std::vector<IAst*> getAllChildren()=0;

         virtual void accept(IAstVisitor* v)=0;
    };

    struct AbstractASTNodeList :public ASTNode ,public IAbstractArrayList<ASTNode*>
    {
        bool leftRecursive;
        int size() { return list.size(); }
       std::vector<ASTNode       *> getList() { return list; }
        ASTNode *getElementAt(int i) { return (ASTNode*) list.at(leftRecursive ? i : list.size() - 1 - i); }
       std::vector<IAst        *> getArrayList()
        {
            if (! leftRecursive) // reverse the list 
            {
                for (int i = 0, n = list.size() - 1; i < n; i++, n--)
                {
                    auto ith = list[i];
                     auto nth = list[n];
                    list[i]=(nth);
                    list[n]=(ith);
                }
                leftRecursive = true;
            }
             return  std::vector<IAst*>(list.begin(), list.end());
        }
        /**
         * @deprecated replaced by {@link #addElement()}
         *
         */
        bool add(ASTNode *element)
        {
            addElement(element);
            return true;
        }

        void addElement(ASTNode *element)
        {
            list.push_back(element);
            if (leftRecursive)
                 rightIToken = element->getRightIToken();
            else leftIToken =  element->getLeftIToken();
        }

        AbstractASTNodeList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):ASTNode(leftIToken, rightIToken)
        {
            this->leftRecursive = leftRecursive;
        }

        AbstractASTNodeList(ASTNode *element, bool leftRecursive):ASTNode(element->getLeftIToken(), element->getRightIToken())
        {
             this->leftRecursive = leftRecursive;
            list.push_back(element);
        }

        /**
         * Make a copy of the list and return it. Note that we obtain the local list by
         * invoking getArrayList so as to make sure that the list we return is in proper order.
         */
       std::vector<IAst        *> getAllChildren()
        {
            auto list_= getArrayList();
 return   std::vector<IAst*>(list_.begin(),list_.end());
        }

    };

    struct ASTNodeToken :public  ASTNode
    {
        ASTNodeToken(IToken* token):ASTNode(token){ }
        IToken* getIToken() { return leftIToken; }
        std::wstring toString() { return leftIToken->toString(); }

        /**
         * A token class has no children. So, we return the empty list.
         */
       std::vector<IAst*> getAllChildren() { return {}; }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 1:  LPG ::= options_segment LPG_INPUT
     *</b>
     */
    struct LPG :public ASTNode
    {
        LPGParser* environment;
        LPGParser* getEnvironment() { return environment; }

        IAst *_options_segment;
        IAst *_LPG_INPUT;

        IAst *getoptions_segment() { return _options_segment; };
        void setoptions_segment(IAst *_options_segment) { this->_options_segment = _options_segment; }
        IAst *getLPG_INPUT() { return _LPG_INPUT; };
        void setLPG_INPUT(IAst *_LPG_INPUT) { this->_LPG_INPUT = _LPG_INPUT; }

        LPG(LPGParser *environment, IToken* leftIToken, IToken* rightIToken,
            IAst *_options_segment,
            IAst *_LPG_INPUT):ASTNode(leftIToken, rightIToken)    {
            this->environment = environment;
            this->_options_segment = _options_segment;
            ((ASTNode*) _options_segment)->setParent(this);
            this->_LPG_INPUT = _LPG_INPUT;
            ((ASTNode*) _LPG_INPUT)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_options_segment);
            list.push_back(_LPG_INPUT);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _options_segment->accept(v);
                _LPG_INPUT->accept(v);
            }
            v->endVisit(this);
        }

    //#line 62 "LPGParser.g

  
     };

    /**
     *<b>
     *<li>Rule 2:  LPG_INPUT ::= $Empty
     *<li>Rule 3:  LPG_INPUT ::= LPG_INPUT LPG_item
     *</b>
     */
    struct LPG_itemList :public AbstractASTNodeList    {
        IAst* getLPG_itemAt(int i) { return (IAst*) getElementAt(i); }

        LPG_itemList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        LPG_itemList(IAst* _LPG_item, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _LPG_item, leftRecursive)
        {
            ((ASTNode*) _LPG_item)->setParent(this);
        }

        void addElement(IAst *_LPG_item)
        {
            AbstractASTNodeList::addElement((ASTNode*) _LPG_item);
            ((ASTNode*) _LPG_item)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    IAst* element = (IAst*)getLPG_itemAt(i);
                    element->accept(v);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 4:  LPG_item ::= ALIAS_KEY$ alias_segment END_KEY_OPT$
     *</b>
     */
    struct AliasSeg :public ASTNode
    {
        IAst *_alias_segment;

        IAst *getalias_segment() { return _alias_segment; };
        void setalias_segment(IAst *_alias_segment) { this->_alias_segment = _alias_segment; }

        AliasSeg(IToken* leftIToken, IToken* rightIToken,
                 IAst *_alias_segment):ASTNode(leftIToken, rightIToken)    {
            this->_alias_segment = _alias_segment;
            ((ASTNode*) _alias_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_alias_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _alias_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 5:  LPG_item ::= AST_KEY$ ast_segment END_KEY_OPT$
     *</b>
     */
    struct AstSeg :public ASTNode
    {
        IAst *_ast_segment;

        IAst *getast_segment() { return _ast_segment; };
        void setast_segment(IAst *_ast_segment) { this->_ast_segment = _ast_segment; }

        AstSeg(IToken* leftIToken, IToken* rightIToken,
               IAst *_ast_segment):ASTNode(leftIToken, rightIToken)    {
            this->_ast_segment = _ast_segment;
            ((ASTNode*) _ast_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ast_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _ast_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 6:  LPG_item ::= DEFINE_KEY$ define_segment END_KEY_OPT$
     *</b>
     */
    struct DefineSeg :public ASTNode
    {
        IAst *_define_segment;

        IAst *getdefine_segment() { return _define_segment; };
        void setdefine_segment(IAst *_define_segment) { this->_define_segment = _define_segment; }

        DefineSeg(IToken* leftIToken, IToken* rightIToken,
                  IAst *_define_segment):ASTNode(leftIToken, rightIToken)    {
            this->_define_segment = _define_segment;
            ((ASTNode*) _define_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_define_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _define_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 7:  LPG_item ::= EOF_KEY$ eof_segment END_KEY_OPT$
     *</b>
     */
    struct EofSeg :public ASTNode
    {
        IAst *_eof_segment;

        IAst *geteof_segment() { return _eof_segment; };
        void seteof_segment(IAst *_eof_segment) { this->_eof_segment = _eof_segment; }

        EofSeg(IToken* leftIToken, IToken* rightIToken,
               IAst *_eof_segment):ASTNode(leftIToken, rightIToken)    {
            this->_eof_segment = _eof_segment;
            ((ASTNode*) _eof_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_eof_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _eof_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 8:  LPG_item ::= EOL_KEY$ eol_segment END_KEY_OPT$
     *</b>
     */
    struct EolSeg :public ASTNode
    {
        IAst *_eol_segment;

        IAst *geteol_segment() { return _eol_segment; };
        void seteol_segment(IAst *_eol_segment) { this->_eol_segment = _eol_segment; }

        EolSeg(IToken* leftIToken, IToken* rightIToken,
               IAst *_eol_segment):ASTNode(leftIToken, rightIToken)    {
            this->_eol_segment = _eol_segment;
            ((ASTNode*) _eol_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_eol_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _eol_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 9:  LPG_item ::= ERROR_KEY$ error_segment END_KEY_OPT$
     *</b>
     */
    struct ErrorSeg :public ASTNode
    {
        IAst *_error_segment;

        IAst *geterror_segment() { return _error_segment; };
        void seterror_segment(IAst *_error_segment) { this->_error_segment = _error_segment; }

        ErrorSeg(IToken* leftIToken, IToken* rightIToken,
                 IAst *_error_segment):ASTNode(leftIToken, rightIToken)    {
            this->_error_segment = _error_segment;
            ((ASTNode*) _error_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_error_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _error_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 10:  LPG_item ::= EXPORT_KEY$ export_segment END_KEY_OPT$
     *</b>
     */
    struct ExportSeg :public ASTNode
    {
        IAst *_export_segment;

        IAst *getexport_segment() { return _export_segment; };
        void setexport_segment(IAst *_export_segment) { this->_export_segment = _export_segment; }

        ExportSeg(IToken* leftIToken, IToken* rightIToken,
                  IAst *_export_segment):ASTNode(leftIToken, rightIToken)    {
            this->_export_segment = _export_segment;
            ((ASTNode*) _export_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_export_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _export_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 11:  LPG_item ::= GLOBALS_KEY$ globals_segment END_KEY_OPT$
     *</b>
     */
    struct GlobalsSeg :public ASTNode
    {
        IAst *_globals_segment;

        IAst *getglobals_segment() { return _globals_segment; };
        void setglobals_segment(IAst *_globals_segment) { this->_globals_segment = _globals_segment; }

        GlobalsSeg(IToken* leftIToken, IToken* rightIToken,
                   IAst *_globals_segment):ASTNode(leftIToken, rightIToken)    {
            this->_globals_segment = _globals_segment;
            ((ASTNode*) _globals_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_globals_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _globals_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 12:  LPG_item ::= HEADERS_KEY$ headers_segment END_KEY_OPT$
     *</b>
     */
    struct HeadersSeg :public ASTNode
    {
        IAst *_headers_segment;

        IAst *getheaders_segment() { return _headers_segment; };
        void setheaders_segment(IAst *_headers_segment) { this->_headers_segment = _headers_segment; }

        HeadersSeg(IToken* leftIToken, IToken* rightIToken,
                   IAst *_headers_segment):ASTNode(leftIToken, rightIToken)    {
            this->_headers_segment = _headers_segment;
            ((ASTNode*) _headers_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_headers_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _headers_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 13:  LPG_item ::= IDENTIFIER_KEY$ identifier_segment END_KEY_OPT$
     *</b>
     */
    struct IdentifierSeg :public ASTNode
    {
        IAst *_identifier_segment;

        IAst *getidentifier_segment() { return _identifier_segment; };
        void setidentifier_segment(IAst *_identifier_segment) { this->_identifier_segment = _identifier_segment; }

        IdentifierSeg(IToken* leftIToken, IToken* rightIToken,
                      IAst *_identifier_segment):ASTNode(leftIToken, rightIToken)    {
            this->_identifier_segment = _identifier_segment;
            ((ASTNode*) _identifier_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_identifier_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _identifier_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 14:  LPG_item ::= IMPORT_KEY$ import_segment END_KEY_OPT$
     *</b>
     */
    struct ImportSeg :public ASTNode
    {
        IAst *_import_segment;

        IAst *getimport_segment() { return _import_segment; };
        void setimport_segment(IAst *_import_segment) { this->_import_segment = _import_segment; }

        ImportSeg(IToken* leftIToken, IToken* rightIToken,
                  IAst *_import_segment):ASTNode(leftIToken, rightIToken)    {
            this->_import_segment = _import_segment;
            ((ASTNode*) _import_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_import_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _import_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 15:  LPG_item ::= INCLUDE_KEY$ include_segment END_KEY_OPT$
     *</b>
     */
    struct IncludeSeg :public ASTNode
    {
        IAst *_include_segment;

        IAst *getinclude_segment() { return _include_segment; };
        void setinclude_segment(IAst *_include_segment) { this->_include_segment = _include_segment; }

        IncludeSeg(IToken* leftIToken, IToken* rightIToken,
                   IAst *_include_segment):ASTNode(leftIToken, rightIToken)    {
            this->_include_segment = _include_segment;
            ((ASTNode*) _include_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_include_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _include_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 16:  LPG_item ::= KEYWORDS_KEY$ keywords_segment END_KEY_OPT$
     *</b>
     */
    struct KeywordsSeg :public ASTNode
    {
        IAst *_keywords_segment;

        IAst *getkeywords_segment() { return _keywords_segment; };
        void setkeywords_segment(IAst *_keywords_segment) { this->_keywords_segment = _keywords_segment; }

        KeywordsSeg(IToken* leftIToken, IToken* rightIToken,
                    IAst *_keywords_segment):ASTNode(leftIToken, rightIToken)    {
            this->_keywords_segment = _keywords_segment;
            ((ASTNode*) _keywords_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_keywords_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _keywords_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 17:  LPG_item ::= NAMES_KEY$ names_segment END_KEY_OPT$
     *</b>
     */
    struct NamesSeg :public ASTNode
    {
        IAst *_names_segment;

        IAst *getnames_segment() { return _names_segment; };
        void setnames_segment(IAst *_names_segment) { this->_names_segment = _names_segment; }

        NamesSeg(IToken* leftIToken, IToken* rightIToken,
                 IAst *_names_segment):ASTNode(leftIToken, rightIToken)    {
            this->_names_segment = _names_segment;
            ((ASTNode*) _names_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_names_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _names_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 18:  LPG_item ::= NOTICE_KEY$ notice_segment END_KEY_OPT$
     *</b>
     */
    struct NoticeSeg :public ASTNode
    {
        IAst *_notice_segment;

        IAst *getnotice_segment() { return _notice_segment; };
        void setnotice_segment(IAst *_notice_segment) { this->_notice_segment = _notice_segment; }

        NoticeSeg(IToken* leftIToken, IToken* rightIToken,
                  IAst *_notice_segment):ASTNode(leftIToken, rightIToken)    {
            this->_notice_segment = _notice_segment;
            ((ASTNode*) _notice_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_notice_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _notice_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 19:  LPG_item ::= RULES_KEY$ rules_segment END_KEY_OPT$
     *</b>
     */
    struct RulesSeg :public ASTNode
    {
        IAst *_rules_segment;

        IAst *getrules_segment() { return _rules_segment; };
        void setrules_segment(IAst *_rules_segment) { this->_rules_segment = _rules_segment; }

        RulesSeg(IToken* leftIToken, IToken* rightIToken,
                 IAst *_rules_segment):ASTNode(leftIToken, rightIToken)    {
            this->_rules_segment = _rules_segment;
            ((ASTNode*) _rules_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_rules_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _rules_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 20:  LPG_item ::= SOFT_KEYWORDS_KEY$ keywords_segment END_KEY_OPT$
     *</b>
     */
    struct SoftKeywordsSeg :public ASTNode
    {
        IAst *_keywords_segment;

        IAst *getkeywords_segment() { return _keywords_segment; };
        void setkeywords_segment(IAst *_keywords_segment) { this->_keywords_segment = _keywords_segment; }

        SoftKeywordsSeg(IToken* leftIToken, IToken* rightIToken,
                        IAst *_keywords_segment):ASTNode(leftIToken, rightIToken)    {
            this->_keywords_segment = _keywords_segment;
            ((ASTNode*) _keywords_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_keywords_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _keywords_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 21:  LPG_item ::= START_KEY$ start_segment END_KEY_OPT$
     *</b>
     */
    struct StartSeg :public ASTNode
    {
        IAst *_start_segment;

        IAst *getstart_segment() { return _start_segment; };
        void setstart_segment(IAst *_start_segment) { this->_start_segment = _start_segment; }

        StartSeg(IToken* leftIToken, IToken* rightIToken,
                 IAst *_start_segment):ASTNode(leftIToken, rightIToken)    {
            this->_start_segment = _start_segment;
            ((ASTNode*) _start_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_start_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _start_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 22:  LPG_item ::= TERMINALS_KEY$ terminals_segment END_KEY_OPT$
     *</b>
     */
    struct TerminalsSeg :public ASTNode
    {
        IAst *_terminals_segment;

        IAst *getterminals_segment() { return _terminals_segment; };
        void setterminals_segment(IAst *_terminals_segment) { this->_terminals_segment = _terminals_segment; }

        TerminalsSeg(IToken* leftIToken, IToken* rightIToken,
                     IAst *_terminals_segment):ASTNode(leftIToken, rightIToken)    {
            this->_terminals_segment = _terminals_segment;
            ((ASTNode*) _terminals_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_terminals_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _terminals_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 23:  LPG_item ::= TRAILERS_KEY$ trailers_segment END_KEY_OPT$
     *</b>
     */
    struct TrailersSeg :public ASTNode
    {
        IAst *_trailers_segment;

        IAst *gettrailers_segment() { return _trailers_segment; };
        void settrailers_segment(IAst *_trailers_segment) { this->_trailers_segment = _trailers_segment; }

        TrailersSeg(IToken* leftIToken, IToken* rightIToken,
                    IAst *_trailers_segment):ASTNode(leftIToken, rightIToken)    {
            this->_trailers_segment = _trailers_segment;
            ((ASTNode*) _trailers_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_trailers_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _trailers_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 24:  LPG_item ::= TYPES_KEY$ types_segment END_KEY_OPT$
     *</b>
     */
    struct TypesSeg :public ASTNode
    {
        IAst *_types_segment;

        IAst *gettypes_segment() { return _types_segment; };
        void settypes_segment(IAst *_types_segment) { this->_types_segment = _types_segment; }

        TypesSeg(IToken* leftIToken, IToken* rightIToken,
                 IAst *_types_segment):ASTNode(leftIToken, rightIToken)    {
            this->_types_segment = _types_segment;
            ((ASTNode*) _types_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_types_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _types_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 25:  LPG_item ::= RECOVER_KEY$ recover_segment END_KEY_OPT$
     *</b>
     */
    struct RecoverSeg :public ASTNode
    {
        IAst *_recover_segment;

        IAst *getrecover_segment() { return _recover_segment; };
        void setrecover_segment(IAst *_recover_segment) { this->_recover_segment = _recover_segment; }

        RecoverSeg(IToken* leftIToken, IToken* rightIToken,
                   IAst *_recover_segment):ASTNode(leftIToken, rightIToken)    {
            this->_recover_segment = _recover_segment;
            ((ASTNode*) _recover_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_recover_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _recover_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 26:  LPG_item ::= DISJOINTPREDECESSORSETS_KEY$ predecessor_segment END_KEY_OPT$
     *</b>
     */
    struct PredecessorSeg :public ASTNode
    {
        IAst *_predecessor_segment;

        IAst *getpredecessor_segment() { return _predecessor_segment; };
        void setpredecessor_segment(IAst *_predecessor_segment) { this->_predecessor_segment = _predecessor_segment; }

        PredecessorSeg(IToken* leftIToken, IToken* rightIToken,
                       IAst *_predecessor_segment):ASTNode(leftIToken, rightIToken)    {
            this->_predecessor_segment = _predecessor_segment;
            ((ASTNode*) _predecessor_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_predecessor_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _predecessor_segment->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 27:  options_segment ::= $Empty
     *<li>Rule 28:  options_segment ::= options_segment option_spec
     *</b>
     */
    struct option_specList :public AbstractASTNodeList    {
        IAst* getoption_specAt(int i) { return (IAst*) getElementAt(i); }

        option_specList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        option_specList(IAst* _option_spec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _option_spec, leftRecursive)
        {
            ((ASTNode*) _option_spec)->setParent(this);
        }

        void addElement(IAst *_option_spec)
        {
            AbstractASTNodeList::addElement((ASTNode*) _option_spec);
            ((ASTNode*) _option_spec)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    option_spec* element = (option_spec*)getoption_specAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 29:  option_spec ::= OPTIONS_KEY$ option_list
     *</b>
     */
    struct option_spec :public ASTNode
    {
        IAst *_option_list;

        IAst *getoption_list() { return _option_list; };
        void setoption_list(IAst *_option_list) { this->_option_list = _option_list; }

        option_spec(IToken* leftIToken, IToken* rightIToken,
                    IAst *_option_list):ASTNode(leftIToken, rightIToken)    {
            this->_option_list = _option_list;
            ((ASTNode*) _option_list)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_option_list);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _option_list->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 30:  option_list ::= option
     *<li>Rule 31:  option_list ::= option_list ,$ option
     *</b>
     */
    struct optionList :public AbstractASTNodeList    {
        IAst* getoptionAt(int i) { return (IAst*) getElementAt(i); }

        optionList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        optionList(IAst* _option, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _option, leftRecursive)
        {
            ((ASTNode*) _option)->setParent(this);
        }

        void addElement(IAst *_option)
        {
            AbstractASTNodeList::addElement((ASTNode*) _option);
            ((ASTNode*) _option)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    option* element = (option*)getoptionAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 32:  option ::= SYMBOL option_value
     *</b>
     */
    struct option :public ASTNode
    {
        IAst *_SYMBOL;
        IAst *_option_value;

        IAst *getSYMBOL() { return _SYMBOL; };
        void setSYMBOL(IAst *_SYMBOL) { this->_SYMBOL = _SYMBOL; }
        /**
         * The value returned by <b>getoption_value</b> may be <b>nullptr</b>
         */
        IAst *getoption_value() { return _option_value; };
        void setoption_value(IAst *_option_value) { this->_option_value = _option_value; }

        option(IToken* leftIToken, IToken* rightIToken,
               IAst *_SYMBOL,
               IAst *_option_value):ASTNode(leftIToken, rightIToken)    {
            this->_SYMBOL = _SYMBOL;
            ((ASTNode*) _SYMBOL)->setParent(this);
            this->_option_value = _option_value;
            if (_option_value != nullptr) ((ASTNode*) _option_value)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SYMBOL);
            list.push_back(_option_value);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _SYMBOL->accept(v);
                if (_option_value != nullptr) _option_value->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 36:  symbol_list ::= SYMBOL
     *<li>Rule 37:  symbol_list ::= symbol_list ,$ SYMBOL
     *<li>Rule 75:  drop_symbols ::= SYMBOL
     *<li>Rule 76:  drop_symbols ::= drop_symbols SYMBOL
     *<li>Rule 136:  barSymbolList ::= SYMBOL
     *<li>Rule 137:  barSymbolList ::= barSymbolList |$ SYMBOL
     *<li>Rule 141:  recover_segment ::= $Empty
     *<li>Rule 142:  recover_segment ::= recover_segment recover_symbol
     *</b>
     */
    struct SYMBOLList :public AbstractASTNodeList    {
        IAst* getSYMBOLAt(int i) { return (IAst*) getElementAt(i); }

        SYMBOLList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        SYMBOLList(IAst* _SYMBOL, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _SYMBOL, leftRecursive)
        {
            ((ASTNode*) _SYMBOL)->setParent(this);
        }

        void addElement(IAst *_SYMBOL)
        {
            AbstractASTNodeList::addElement((ASTNode*) _SYMBOL);
            ((ASTNode*) _SYMBOL)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    ASTNodeToken* element = (ASTNodeToken*)getSYMBOLAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 38:  alias_segment ::= aliasSpec
     *<li>Rule 39:  alias_segment ::= alias_segment aliasSpec
     *</b>
     */
    struct aliasSpecList :public AbstractASTNodeList    {
        IAst* getaliasSpecAt(int i) { return (IAst*) getElementAt(i); }

        aliasSpecList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        aliasSpecList(IAst* _aliasSpec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _aliasSpec, leftRecursive)
        {
            ((ASTNode*) _aliasSpec)->setParent(this);
        }

        void addElement(IAst *_aliasSpec)
        {
            AbstractASTNodeList::addElement((ASTNode*) _aliasSpec);
            ((ASTNode*) _aliasSpec)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    IAst* element = (IAst*)getaliasSpecAt(i);
                    element->accept(v);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 46:  alias_lhs_macro_name ::= MACRO_NAME
     *</b>
     */
    struct alias_lhs_macro_name :public ASTNodeToken
    {
        IToken* getMACRO_NAME() { return leftIToken; }

        alias_lhs_macro_name(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 55:  define_segment ::= defineSpec
     *<li>Rule 56:  define_segment ::= define_segment defineSpec
     *</b>
     */
    struct defineSpecList :public AbstractASTNodeList    {
        IAst* getdefineSpecAt(int i) { return (IAst*) getElementAt(i); }

        defineSpecList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        defineSpecList(IAst* _defineSpec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _defineSpec, leftRecursive)
        {
            ((ASTNode*) _defineSpec)->setParent(this);
        }

        void addElement(IAst *_defineSpec)
        {
            AbstractASTNodeList::addElement((ASTNode*) _defineSpec);
            ((ASTNode*) _defineSpec)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    defineSpec* element = (defineSpec*)getdefineSpecAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 57:  defineSpec ::= macro_name_symbol macro_segment
     *</b>
     */
    struct defineSpec :public ASTNode
    {
        LPGParser* environment;
        LPGParser* getEnvironment() { return environment; }

        IAst *_macro_name_symbol;
        IAst *_macro_segment;

        IAst *getmacro_name_symbol() { return _macro_name_symbol; };
        void setmacro_name_symbol(IAst *_macro_name_symbol) { this->_macro_name_symbol = _macro_name_symbol; }
        IAst *getmacro_segment() { return _macro_segment; };
        void setmacro_segment(IAst *_macro_segment) { this->_macro_segment = _macro_segment; }

        defineSpec(LPGParser *environment, IToken* leftIToken, IToken* rightIToken,
                   IAst *_macro_name_symbol,
                   IAst *_macro_segment):ASTNode(leftIToken, rightIToken)    {
            this->environment = environment;
            this->_macro_name_symbol = _macro_name_symbol;
            ((ASTNode*) _macro_name_symbol)->setParent(this);
            this->_macro_segment = _macro_segment;
            ((ASTNode*) _macro_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_macro_name_symbol);
            list.push_back(_macro_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _macro_name_symbol->accept(v);
                _macro_segment->accept(v);
            }
            v->endVisit(this);
        }

    //#line 130 "LPGParser.g

   
     };

    /**
     *<b>
     *<li>Rule 60:  macro_segment ::= BLOCK
     *</b>
     */
    struct macro_segment :public ASTNodeToken
    {
        IToken* getBLOCK() { return leftIToken; }

        macro_segment(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 64:  export_segment ::= terminal_symbol
     *<li>Rule 65:  export_segment ::= export_segment terminal_symbol
     *</b>
     */
    struct terminal_symbolList :public AbstractASTNodeList    {
        IAst* getterminal_symbolAt(int i) { return (IAst*) getElementAt(i); }

        terminal_symbolList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        terminal_symbolList(IAst* _terminal_symbol, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _terminal_symbol, leftRecursive)
        {
            ((ASTNode*) _terminal_symbol)->setParent(this);
        }

        void addElement(IAst *_terminal_symbol)
        {
            AbstractASTNodeList::addElement((ASTNode*) _terminal_symbol);
            ((ASTNode*) _terminal_symbol)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    IAst* element = (IAst*)getterminal_symbolAt(i);
                    element->accept(v);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 66:  globals_segment ::= action_segment
     *<li>Rule 67:  globals_segment ::= globals_segment action_segment
     *<li>Rule 96:  notice_segment ::= action_segment
     *<li>Rule 97:  notice_segment ::= notice_segment action_segment
     *<li>Rule 146:  action_segment_list ::= $Empty
     *<li>Rule 147:  action_segment_list ::= action_segment_list action_segment
     *</b>
     */
    struct action_segmentList :public AbstractASTNodeList    {
        IAst* getaction_segmentAt(int i) { return (IAst*) getElementAt(i); }

        action_segmentList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        action_segmentList(IAst* _action_segment, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _action_segment, leftRecursive)
        {
            ((ASTNode*) _action_segment)->setParent(this);
        }

        void addElement(IAst *_action_segment)
        {
            AbstractASTNodeList::addElement((ASTNode*) _action_segment);
            ((ASTNode*) _action_segment)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    action_segment* element = (action_segment*)getaction_segmentAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 70:  import_segment ::= SYMBOL drop_command_list
     *</b>
     */
    struct import_segment :public ASTNode
    {
        IAst *_SYMBOL;
        IAst *_drop_command_list;

        IAst *getSYMBOL() { return _SYMBOL; };
        void setSYMBOL(IAst *_SYMBOL) { this->_SYMBOL = _SYMBOL; }
        IAst *getdrop_command_list() { return _drop_command_list; };
        void setdrop_command_list(IAst *_drop_command_list) { this->_drop_command_list = _drop_command_list; }

        import_segment(IToken* leftIToken, IToken* rightIToken,
                       IAst *_SYMBOL,
                       IAst *_drop_command_list):ASTNode(leftIToken, rightIToken)    {
            this->_SYMBOL = _SYMBOL;
            ((ASTNode*) _SYMBOL)->setParent(this);
            this->_drop_command_list = _drop_command_list;
            ((ASTNode*) _drop_command_list)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SYMBOL);
            list.push_back(_drop_command_list);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _SYMBOL->accept(v);
                _drop_command_list->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 71:  drop_command_list ::= $Empty
     *<li>Rule 72:  drop_command_list ::= drop_command_list drop_command
     *</b>
     */
    struct drop_commandList :public AbstractASTNodeList    {
        IAst* getdrop_commandAt(int i) { return (IAst*) getElementAt(i); }

        drop_commandList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        drop_commandList(IAst* _drop_command, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _drop_command, leftRecursive)
        {
            ((ASTNode*) _drop_command)->setParent(this);
        }

        void addElement(IAst *_drop_command)
        {
            AbstractASTNodeList::addElement((ASTNode*) _drop_command);
            ((ASTNode*) _drop_command)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    IAst* element = (IAst*)getdrop_commandAt(i);
                    element->accept(v);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 77:  drop_rules ::= drop_rule
     *<li>Rule 78:  drop_rules ::= drop_rules drop_rule
     *</b>
     */
    struct drop_ruleList :public AbstractASTNodeList    {
        IAst* getdrop_ruleAt(int i) { return (IAst*) getElementAt(i); }

        drop_ruleList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        drop_ruleList(IAst* _drop_rule, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _drop_rule, leftRecursive)
        {
            ((ASTNode*) _drop_rule)->setParent(this);
        }

        void addElement(IAst *_drop_rule)
        {
            AbstractASTNodeList::addElement((ASTNode*) _drop_rule);
            ((ASTNode*) _drop_rule)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    drop_rule* element = (drop_rule*)getdrop_ruleAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 79:  drop_rule ::= SYMBOL optMacroName produces ruleList
     *</b>
     */
    struct drop_rule :public ASTNode
    {
        IAst *_SYMBOL;
        IAst *_optMacroName;
        IAst *_produces;
        IAst *_ruleList;

        IAst *getSYMBOL() { return _SYMBOL; };
        void setSYMBOL(IAst *_SYMBOL) { this->_SYMBOL = _SYMBOL; }
        /**
         * The value returned by <b>getoptMacroName</b> may be <b>nullptr</b>
         */
        IAst *getoptMacroName() { return _optMacroName; };
        void setoptMacroName(IAst *_optMacroName) { this->_optMacroName = _optMacroName; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getruleList() { return _ruleList; };
        void setruleList(IAst *_ruleList) { this->_ruleList = _ruleList; }

        drop_rule(IToken* leftIToken, IToken* rightIToken,
                  IAst *_SYMBOL,
                  IAst *_optMacroName,
                  IAst *_produces,
                  IAst *_ruleList):ASTNode(leftIToken, rightIToken)    {
            this->_SYMBOL = _SYMBOL;
            ((ASTNode*) _SYMBOL)->setParent(this);
            this->_optMacroName = _optMacroName;
            if (_optMacroName != nullptr) ((ASTNode*) _optMacroName)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_ruleList = _ruleList;
            ((ASTNode*) _ruleList)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SYMBOL);
            list.push_back(_optMacroName);
            list.push_back(_produces);
            list.push_back(_ruleList);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _SYMBOL->accept(v);
                if (_optMacroName != nullptr) _optMacroName->accept(v);
                _produces->accept(v);
                _ruleList->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 80:  optMacroName ::= $Empty
     *</em>
     *<p>
     *<b>
     *<li>Rule 81:  optMacroName ::= MACRO_NAME
     *</b>
     */
    struct optMacroName :public ASTNodeToken
    {
        IToken* getMACRO_NAME() { return leftIToken; }

        optMacroName(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 82:  include_segment ::= SYMBOL
     *</b>
     */
    struct include_segment :public ASTNodeToken
    {
        IToken* getSYMBOL() { return leftIToken; }

        include_segment(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 83:  keywords_segment ::= keywordSpec
     *<li>Rule 84:  keywords_segment ::= keywords_segment keywordSpec
     *</b>
     */
    struct keywordSpecList :public AbstractASTNodeList    {
        IAst* getkeywordSpecAt(int i) { return (IAst*) getElementAt(i); }

        keywordSpecList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        keywordSpecList(IAst* _keywordSpec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _keywordSpec, leftRecursive)
        {
            ((ASTNode*) _keywordSpec)->setParent(this);
        }

        void addElement(IAst *_keywordSpec)
        {
            AbstractASTNodeList::addElement((ASTNode*) _keywordSpec);
            ((ASTNode*) _keywordSpec)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    IAst* element = (IAst*)getkeywordSpecAt(i);
                    element->accept(v);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 85:  keywordSpec ::= terminal_symbol
     *</em>
     *<p>
     *<b>
     *<li>Rule 86:  keywordSpec ::= terminal_symbol produces name
     *</b>
     */
    struct keywordSpec :public ASTNode
    {
        IAst *_terminal_symbol;
        IAst *_produces;
        IAst *_name;

        IAst *getterminal_symbol() { return _terminal_symbol; };
        void setterminal_symbol(IAst *_terminal_symbol) { this->_terminal_symbol = _terminal_symbol; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getname() { return _name; };
        void setname(IAst *_name) { this->_name = _name; }

        keywordSpec(IToken* leftIToken, IToken* rightIToken,
                    IAst *_terminal_symbol,
                    IAst *_produces,
                    IAst *_name):ASTNode(leftIToken, rightIToken)    {
            this->_terminal_symbol = _terminal_symbol;
            ((ASTNode*) _terminal_symbol)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_name = _name;
            ((ASTNode*) _name)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_terminal_symbol);
            list.push_back(_produces);
            list.push_back(_name);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _terminal_symbol->accept(v);
                _produces->accept(v);
                _name->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 87:  names_segment ::= nameSpec
     *<li>Rule 88:  names_segment ::= names_segment nameSpec
     *</b>
     */
    struct nameSpecList :public AbstractASTNodeList    {
        IAst* getnameSpecAt(int i) { return (IAst*) getElementAt(i); }

        nameSpecList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        nameSpecList(IAst* _nameSpec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _nameSpec, leftRecursive)
        {
            ((ASTNode*) _nameSpec)->setParent(this);
        }

        void addElement(IAst *_nameSpec)
        {
            AbstractASTNodeList::addElement((ASTNode*) _nameSpec);
            ((ASTNode*) _nameSpec)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    nameSpec* element = (nameSpec*)getnameSpecAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 89:  nameSpec ::= name produces name
     *</b>
     */
    struct nameSpec :public ASTNode
    {
        IAst *_name;
        IAst *_produces;
        IAst *_name3;

        IAst *getname() { return _name; };
        void setname(IAst *_name) { this->_name = _name; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getname3() { return _name3; };
        void setname3(IAst *_name3) { this->_name3 = _name3; }

        nameSpec(IToken* leftIToken, IToken* rightIToken,
                 IAst *_name,
                 IAst *_produces,
                 IAst *_name3):ASTNode(leftIToken, rightIToken)    {
            this->_name = _name;
            ((ASTNode*) _name)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_name3 = _name3;
            ((ASTNode*) _name3)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_name);
            list.push_back(_produces);
            list.push_back(_name3);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _name->accept(v);
                _produces->accept(v);
                _name3->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 98:  rules_segment ::= action_segment_list nonTermList
     *</b>
     */
    struct rules_segment :public ASTNode
    {
        IAst *_action_segment_list;
        IAst *_nonTermList;

        IAst *getaction_segment_list() { return _action_segment_list; };
        void setaction_segment_list(IAst *_action_segment_list) { this->_action_segment_list = _action_segment_list; }
        IAst *getnonTermList() { return _nonTermList; };
        void setnonTermList(IAst *_nonTermList) { this->_nonTermList = _nonTermList; }

        rules_segment(IToken* leftIToken, IToken* rightIToken,
                      IAst *_action_segment_list,
                      IAst *_nonTermList):ASTNode(leftIToken, rightIToken)    {
            this->_action_segment_list = _action_segment_list;
            ((ASTNode*) _action_segment_list)->setParent(this);
            this->_nonTermList = _nonTermList;
            ((ASTNode*) _nonTermList)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_action_segment_list);
            list.push_back(_nonTermList);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _action_segment_list->accept(v);
                _nonTermList->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 99:  nonTermList ::= $Empty
     *<li>Rule 100:  nonTermList ::= nonTermList nonTerm
     *</b>
     */
    struct nonTermList :public AbstractASTNodeList    {
        IAst* getnonTermAt(int i) { return (IAst*) getElementAt(i); }

        nonTermList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        nonTermList(IAst* _nonTerm, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _nonTerm, leftRecursive)
        {
            ((ASTNode*) _nonTerm)->setParent(this);
        }

        void addElement(IAst *_nonTerm)
        {
            AbstractASTNodeList::addElement((ASTNode*) _nonTerm);
            ((ASTNode*) _nonTerm)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    nonTerm* element = (nonTerm*)getnonTermAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 101:  nonTerm ::= ruleNameWithAttributes produces ruleList
     *</b>
     */
    struct nonTerm :public ASTNode
    {
        LPGParser* environment;
        LPGParser* getEnvironment() { return environment; }

        IAst *_ruleNameWithAttributes;
        IAst *_produces;
        IAst *_ruleList;

        IAst *getruleNameWithAttributes() { return _ruleNameWithAttributes; };
        void setruleNameWithAttributes(IAst *_ruleNameWithAttributes) { this->_ruleNameWithAttributes = _ruleNameWithAttributes; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getruleList() { return _ruleList; };
        void setruleList(IAst *_ruleList) { this->_ruleList = _ruleList; }

        nonTerm(LPGParser *environment, IToken* leftIToken, IToken* rightIToken,
                IAst *_ruleNameWithAttributes,
                IAst *_produces,
                IAst *_ruleList):ASTNode(leftIToken, rightIToken)    {
            this->environment = environment;
            this->_ruleNameWithAttributes = _ruleNameWithAttributes;
            ((ASTNode*) _ruleNameWithAttributes)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_ruleList = _ruleList;
            ((ASTNode*) _ruleList)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ruleNameWithAttributes);
            list.push_back(_produces);
            list.push_back(_ruleList);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _ruleNameWithAttributes->accept(v);
                _produces->accept(v);
                _ruleList->accept(v);
            }
            v->endVisit(this);
        }

    //#line 202 "LPGParser.g

 
     };

    /**
     *<b>
     *<li>Rule 102:  ruleNameWithAttributes ::= SYMBOL
     *<li>Rule 103:  ruleNameWithAttributes ::= SYMBOL MACRO_NAME$className
     *<li>Rule 104:  ruleNameWithAttributes ::= SYMBOL MACRO_NAME$className MACRO_NAME$arrayElement
     *</b>
     */
    struct RuleName :public  ASTNode    {
        IAst *_SYMBOL;
        IAst *_className;
        IAst *_arrayElement;

        IAst *getSYMBOL() { return _SYMBOL; }
        /**
         * The value returned by <b>getclassName</b> may be <b>nullptr</b>
         */
        IAst *getclassName() { return _className; }
        /**
         * The value returned by <b>getarrayElement</b> may be <b>nullptr</b>
         */
        IAst *getarrayElement() { return _arrayElement; }

        RuleName(IToken *leftIToken, IToken *rightIToken,
                 IAst *_SYMBOL,
                 IAst *_className,
                 IAst *_arrayElement)
:ASTNode    (leftIToken, rightIToken)
        {
            this->_SYMBOL = _SYMBOL;
            ((ASTNode*) _SYMBOL)->setParent(this);
            this->_className = _className;
            if (_className != nullptr) ((ASTNode*) _className)->setParent(this);
            this->_arrayElement = _arrayElement;
            if (_arrayElement != nullptr) ((ASTNode*) _arrayElement)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SYMBOL);
            list.push_back(_className);
            list.push_back(_arrayElement);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _SYMBOL->accept(v);
                if (_className != nullptr) _className->accept(v);
                if (_arrayElement != nullptr) _arrayElement->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 105:  ruleList ::= rule
     *<li>Rule 106:  ruleList ::= ruleList |$ rule
     *</b>
     */
    struct ruleList :public AbstractASTNodeList    {
        IAst* getruleAt(int i) { return (IAst*) getElementAt(i); }

        ruleList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        ruleList(IAst* _rule, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _rule, leftRecursive)
        {
            ((ASTNode*) _rule)->setParent(this);
        }

        void addElement(IAst *_rule)
        {
            AbstractASTNodeList::addElement((ASTNode*) _rule);
            ((ASTNode*) _rule)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    rule* element = (rule*)getruleAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 111:  rule ::= symWithAttrsList opt_action_segment
     *</b>
     */
    struct rule :public ASTNode
    {
        IAst *_symWithAttrsList;
        IAst *_opt_action_segment;

        IAst *getsymWithAttrsList() { return _symWithAttrsList; };
        void setsymWithAttrsList(IAst *_symWithAttrsList) { this->_symWithAttrsList = _symWithAttrsList; }
        /**
         * The value returned by <b>getopt_action_segment</b> may be <b>nullptr</b>
         */
        IAst *getopt_action_segment() { return _opt_action_segment; };
        void setopt_action_segment(IAst *_opt_action_segment) { this->_opt_action_segment = _opt_action_segment; }

        rule(IToken* leftIToken, IToken* rightIToken,
             IAst *_symWithAttrsList,
             IAst *_opt_action_segment):ASTNode(leftIToken, rightIToken)    {
            this->_symWithAttrsList = _symWithAttrsList;
            ((ASTNode*) _symWithAttrsList)->setParent(this);
            this->_opt_action_segment = _opt_action_segment;
            if (_opt_action_segment != nullptr) ((ASTNode*) _opt_action_segment)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_symWithAttrsList);
            list.push_back(_opt_action_segment);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _symWithAttrsList->accept(v);
                if (_opt_action_segment != nullptr) _opt_action_segment->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 112:  symWithAttrsList ::= $Empty
     *<li>Rule 113:  symWithAttrsList ::= symWithAttrsList symWithAttrs
     *</b>
     */
    struct symWithAttrsList :public AbstractASTNodeList    {
        IAst* getsymWithAttrsAt(int i) { return (IAst*) getElementAt(i); }

        symWithAttrsList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        symWithAttrsList(IAst* _symWithAttrs, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _symWithAttrs, leftRecursive)
        {
            ((ASTNode*) _symWithAttrs)->setParent(this);
        }

        void addElement(IAst *_symWithAttrs)
        {
            AbstractASTNodeList::addElement((ASTNode*) _symWithAttrs);
            ((ASTNode*) _symWithAttrs)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    IAst* element = (IAst*)getsymWithAttrsAt(i);
                    element->accept(v);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 116:  optAttrList ::= $Empty
     *<li>Rule 117:  optAttrList ::= MACRO_NAME
     *</b>
     */
    struct symAttrs :public  ASTNode    {
        IAst *_MACRO_NAME;

        /**
         * The value returned by <b>getMACRO_NAME</b> may be <b>nullptr</b>
         */
        IAst *getMACRO_NAME() { return _MACRO_NAME; }

        symAttrs(IToken *leftIToken, IToken *rightIToken,
                 IAst *_MACRO_NAME)
:ASTNode    (leftIToken, rightIToken)
        {
            this->_MACRO_NAME = _MACRO_NAME;
            if (_MACRO_NAME != nullptr) ((ASTNode*) _MACRO_NAME)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MACRO_NAME);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                if (_MACRO_NAME != nullptr) _MACRO_NAME->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 120:  action_segment ::= BLOCK
     *</b>
     */
    struct action_segment :public ASTNodeToken
    {
        LPGParser* environment;
        LPGParser* getEnvironment() { return environment; }

        IToken* getBLOCK() { return leftIToken; }

        action_segment(LPGParser *environment, IToken* token):ASTNodeToken    (token)
        {
            this->environment = environment;
            initialize();
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }

    //#line 244 "LPGParser.g


    };

    /**
     *<b>
     *<li>Rule 121:  start_segment ::= start_symbol
     *<li>Rule 122:  start_segment ::= start_segment start_symbol
     *</b>
     */
    struct start_symbolList :public AbstractASTNodeList    {
        IAst* getstart_symbolAt(int i) { return (IAst*) getElementAt(i); }

        start_symbolList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        start_symbolList(IAst* _start_symbol, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _start_symbol, leftRecursive)
        {
            ((ASTNode*) _start_symbol)->setParent(this);
        }

        void addElement(IAst *_start_symbol)
        {
            AbstractASTNodeList::addElement((ASTNode*) _start_symbol);
            ((ASTNode*) _start_symbol)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    IAst* element = (IAst*)getstart_symbolAt(i);
                    element->accept(v);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 125:  terminals_segment ::= terminal
     *<li>Rule 126:  terminals_segment ::= terminals_segment terminal
     *</b>
     */
    struct terminalList :public AbstractASTNodeList    {
        IAst* getterminalAt(int i) { return (IAst*) getElementAt(i); }

        terminalList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        terminalList(IAst* _terminal, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _terminal, leftRecursive)
        {
            ((ASTNode*) _terminal)->setParent(this);
        }

        void addElement(IAst *_terminal)
        {
            AbstractASTNodeList::addElement((ASTNode*) _terminal);
            ((ASTNode*) _terminal)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    terminal* element = (terminal*)getterminalAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 127:  terminal ::= terminal_symbol optTerminalAlias
     *</b>
     */
    struct terminal :public ASTNode
    {
        LPGParser* environment;
        LPGParser* getEnvironment() { return environment; }

        IAst *_terminal_symbol;
        IAst *_optTerminalAlias;

        IAst *getterminal_symbol() { return _terminal_symbol; };
        void setterminal_symbol(IAst *_terminal_symbol) { this->_terminal_symbol = _terminal_symbol; }
        /**
         * The value returned by <b>getoptTerminalAlias</b> may be <b>nullptr</b>
         */
        IAst *getoptTerminalAlias() { return _optTerminalAlias; };
        void setoptTerminalAlias(IAst *_optTerminalAlias) { this->_optTerminalAlias = _optTerminalAlias; }

        terminal(LPGParser *environment, IToken* leftIToken, IToken* rightIToken,
                 IAst *_terminal_symbol,
                 IAst *_optTerminalAlias):ASTNode(leftIToken, rightIToken)    {
            this->environment = environment;
            this->_terminal_symbol = _terminal_symbol;
            ((ASTNode*) _terminal_symbol)->setParent(this);
            this->_optTerminalAlias = _optTerminalAlias;
            if (_optTerminalAlias != nullptr) ((ASTNode*) _optTerminalAlias)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_terminal_symbol);
            list.push_back(_optTerminalAlias);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _terminal_symbol->accept(v);
                if (_optTerminalAlias != nullptr) _optTerminalAlias->accept(v);
            }
            v->endVisit(this);
        }

    //#line 258 "LPGParser.g

 
     };

    /**
     *<em>
     *<li>Rule 128:  optTerminalAlias ::= $Empty
     *</em>
     *<p>
     *<b>
     *<li>Rule 129:  optTerminalAlias ::= produces name
     *</b>
     */
    struct optTerminalAlias :public ASTNode
    {
        IAst *_produces;
        IAst *_name;

        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getname() { return _name; };
        void setname(IAst *_name) { this->_name = _name; }

        optTerminalAlias(IToken* leftIToken, IToken* rightIToken,
                         IAst *_produces,
                         IAst *_name):ASTNode(leftIToken, rightIToken)    {
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_name = _name;
            ((ASTNode*) _name)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_produces);
            list.push_back(_name);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _produces->accept(v);
                _name->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 133:  types_segment ::= type_declarations
     *<li>Rule 134:  types_segment ::= types_segment type_declarations
     *</b>
     */
    struct type_declarationsList :public AbstractASTNodeList    {
        IAst* gettype_declarationsAt(int i) { return (IAst*) getElementAt(i); }

        type_declarationsList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        type_declarationsList(IAst* _type_declarations, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _type_declarations, leftRecursive)
        {
            ((ASTNode*) _type_declarations)->setParent(this);
        }

        void addElement(IAst *_type_declarations)
        {
            AbstractASTNodeList::addElement((ASTNode*) _type_declarations);
            ((ASTNode*) _type_declarations)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    type_declarations* element = (type_declarations*)gettype_declarationsAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 135:  type_declarations ::= SYMBOL produces barSymbolList
     *</b>
     */
    struct type_declarations :public ASTNode
    {
        IAst *_SYMBOL;
        IAst *_produces;
        IAst *_barSymbolList;

        IAst *getSYMBOL() { return _SYMBOL; };
        void setSYMBOL(IAst *_SYMBOL) { this->_SYMBOL = _SYMBOL; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getbarSymbolList() { return _barSymbolList; };
        void setbarSymbolList(IAst *_barSymbolList) { this->_barSymbolList = _barSymbolList; }

        type_declarations(IToken* leftIToken, IToken* rightIToken,
                          IAst *_SYMBOL,
                          IAst *_produces,
                          IAst *_barSymbolList):ASTNode(leftIToken, rightIToken)    {
            this->_SYMBOL = _SYMBOL;
            ((ASTNode*) _SYMBOL)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_barSymbolList = _barSymbolList;
            ((ASTNode*) _barSymbolList)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SYMBOL);
            list.push_back(_produces);
            list.push_back(_barSymbolList);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _SYMBOL->accept(v);
                _produces->accept(v);
                _barSymbolList->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 138:  predecessor_segment ::= $Empty
     *<li>Rule 139:  predecessor_segment ::= predecessor_segment symbol_pair
     *</b>
     */
    struct symbol_pairList :public AbstractASTNodeList    {
        IAst* getsymbol_pairAt(int i) { return (IAst*) getElementAt(i); }

        symbol_pairList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList    (leftIToken, rightIToken, leftRecursive)
{
        }

        symbol_pairList(IAst* _symbol_pair, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) _symbol_pair, leftRecursive)
        {
            ((ASTNode*) _symbol_pair)->setParent(this);
        }

        void addElement(IAst *_symbol_pair)
        {
            AbstractASTNodeList::addElement((ASTNode*) _symbol_pair);
            ((ASTNode*) _symbol_pair)->setParent(this);
        }


        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }
        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                for (int i = 0; i < size(); i++)
                {
                    symbol_pair* element = (symbol_pair*)getsymbol_pairAt(i);
                    if (! v->preVisit(element)) continue;
                    element->enter(v);
                    v->postVisit(element);
                }
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 140:  symbol_pair ::= SYMBOL SYMBOL
     *</b>
     */
    struct symbol_pair :public ASTNode
    {
        IAst *_SYMBOL;
        IAst *_SYMBOL2;

        IAst *getSYMBOL() { return _SYMBOL; };
        void setSYMBOL(IAst *_SYMBOL) { this->_SYMBOL = _SYMBOL; }
        IAst *getSYMBOL2() { return _SYMBOL2; };
        void setSYMBOL2(IAst *_SYMBOL2) { this->_SYMBOL2 = _SYMBOL2; }

        symbol_pair(IToken* leftIToken, IToken* rightIToken,
                    IAst *_SYMBOL,
                    IAst *_SYMBOL2):ASTNode(leftIToken, rightIToken)    {
            this->_SYMBOL = _SYMBOL;
            ((ASTNode*) _SYMBOL)->setParent(this);
            this->_SYMBOL2 = _SYMBOL2;
            ((ASTNode*) _SYMBOL2)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SYMBOL);
            list.push_back(_SYMBOL2);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _SYMBOL->accept(v);
                _SYMBOL2->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 143:  recover_symbol ::= SYMBOL
     *</b>
     */
    struct recover_symbol :public ASTNodeToken
    {
        LPGParser* environment;
        LPGParser* getEnvironment() { return environment; }

        IToken* getSYMBOL() { return leftIToken; }

        recover_symbol(LPGParser *environment, IToken* token):ASTNodeToken    (token)
        {
            this->environment = environment;
            initialize();
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }

    //#line 287 "LPGParser.g

   
     };

    /**
     *<em>
     *<li>Rule 144:  END_KEY_OPT ::= $Empty
     *</em>
     *<p>
     *<b>
     *<li>Rule 145:  END_KEY_OPT ::= END_KEY
     *</b>
     */
    struct END_KEY_OPT :public ASTNodeToken
    {
        IToken* getEND_KEY() { return leftIToken; }

        END_KEY_OPT(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 34:  option_value ::= =$ SYMBOL
     *</b>
     */
    struct option_value0 :public ASTNode
    {
        IAst *_SYMBOL;

        IAst *getSYMBOL() { return _SYMBOL; };
        void setSYMBOL(IAst *_SYMBOL) { this->_SYMBOL = _SYMBOL; }

        option_value0(IToken* leftIToken, IToken* rightIToken,
                      IAst *_SYMBOL):ASTNode(leftIToken, rightIToken)    {
            this->_SYMBOL = _SYMBOL;
            ((ASTNode*) _SYMBOL)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SYMBOL);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _SYMBOL->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 35:  option_value ::= =$ ($ symbol_list )$
     *</b>
     */
    struct option_value1 :public ASTNode
    {
        IAst *_symbol_list;

        IAst *getsymbol_list() { return _symbol_list; };
        void setsymbol_list(IAst *_symbol_list) { this->_symbol_list = _symbol_list; }

        option_value1(IToken* leftIToken, IToken* rightIToken,
                      IAst *_symbol_list):ASTNode(leftIToken, rightIToken)    {
            this->_symbol_list = _symbol_list;
            ((ASTNode*) _symbol_list)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_symbol_list);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
                _symbol_list->accept(v);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 40:  aliasSpec ::= ERROR_KEY produces alias_rhs
     *</b>
     */
    struct aliasSpec0 :public ASTNode
    {
        IAst *_ERROR_KEY;
        IAst *_produces;
        IAst *_alias_rhs;

        IAst *getERROR_KEY() { return _ERROR_KEY; };
        void setERROR_KEY(IAst *_ERROR_KEY) { this->_ERROR_KEY = _ERROR_KEY; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getalias_rhs() { return _alias_rhs; };
        void setalias_rhs(IAst *_alias_rhs) { this->_alias_rhs = _alias_rhs; }

        aliasSpec0(IToken* leftIToken, IToken* rightIToken,
                   IAst *_ERROR_KEY,
                   IAst *_produces,
                   IAst *_alias_rhs):ASTNode(leftIToken, rightIToken)    {
            this->_ERROR_KEY = _ERROR_KEY;
            ((ASTNode*) _ERROR_KEY)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_alias_rhs = _alias_rhs;
            ((ASTNode*) _alias_rhs)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ERROR_KEY);
            list.push_back(_produces);
            list.push_back(_alias_rhs);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _ERROR_KEY->accept(v);
                _produces->accept(v);
                _alias_rhs->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 41:  aliasSpec ::= EOL_KEY produces alias_rhs
     *</b>
     */
    struct aliasSpec1 :public ASTNode
    {
        IAst *_EOL_KEY;
        IAst *_produces;
        IAst *_alias_rhs;

        IAst *getEOL_KEY() { return _EOL_KEY; };
        void setEOL_KEY(IAst *_EOL_KEY) { this->_EOL_KEY = _EOL_KEY; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getalias_rhs() { return _alias_rhs; };
        void setalias_rhs(IAst *_alias_rhs) { this->_alias_rhs = _alias_rhs; }

        aliasSpec1(IToken* leftIToken, IToken* rightIToken,
                   IAst *_EOL_KEY,
                   IAst *_produces,
                   IAst *_alias_rhs):ASTNode(leftIToken, rightIToken)    {
            this->_EOL_KEY = _EOL_KEY;
            ((ASTNode*) _EOL_KEY)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_alias_rhs = _alias_rhs;
            ((ASTNode*) _alias_rhs)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_EOL_KEY);
            list.push_back(_produces);
            list.push_back(_alias_rhs);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _EOL_KEY->accept(v);
                _produces->accept(v);
                _alias_rhs->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 42:  aliasSpec ::= EOF_KEY produces alias_rhs
     *</b>
     */
    struct aliasSpec2 :public ASTNode
    {
        IAst *_EOF_KEY;
        IAst *_produces;
        IAst *_alias_rhs;

        IAst *getEOF_KEY() { return _EOF_KEY; };
        void setEOF_KEY(IAst *_EOF_KEY) { this->_EOF_KEY = _EOF_KEY; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getalias_rhs() { return _alias_rhs; };
        void setalias_rhs(IAst *_alias_rhs) { this->_alias_rhs = _alias_rhs; }

        aliasSpec2(IToken* leftIToken, IToken* rightIToken,
                   IAst *_EOF_KEY,
                   IAst *_produces,
                   IAst *_alias_rhs):ASTNode(leftIToken, rightIToken)    {
            this->_EOF_KEY = _EOF_KEY;
            ((ASTNode*) _EOF_KEY)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_alias_rhs = _alias_rhs;
            ((ASTNode*) _alias_rhs)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_EOF_KEY);
            list.push_back(_produces);
            list.push_back(_alias_rhs);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _EOF_KEY->accept(v);
                _produces->accept(v);
                _alias_rhs->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 43:  aliasSpec ::= IDENTIFIER_KEY produces alias_rhs
     *</b>
     */
    struct aliasSpec3 :public ASTNode
    {
        IAst *_IDENTIFIER_KEY;
        IAst *_produces;
        IAst *_alias_rhs;

        IAst *getIDENTIFIER_KEY() { return _IDENTIFIER_KEY; };
        void setIDENTIFIER_KEY(IAst *_IDENTIFIER_KEY) { this->_IDENTIFIER_KEY = _IDENTIFIER_KEY; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getalias_rhs() { return _alias_rhs; };
        void setalias_rhs(IAst *_alias_rhs) { this->_alias_rhs = _alias_rhs; }

        aliasSpec3(IToken* leftIToken, IToken* rightIToken,
                   IAst *_IDENTIFIER_KEY,
                   IAst *_produces,
                   IAst *_alias_rhs):ASTNode(leftIToken, rightIToken)    {
            this->_IDENTIFIER_KEY = _IDENTIFIER_KEY;
            ((ASTNode*) _IDENTIFIER_KEY)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_alias_rhs = _alias_rhs;
            ((ASTNode*) _alias_rhs)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_IDENTIFIER_KEY);
            list.push_back(_produces);
            list.push_back(_alias_rhs);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _IDENTIFIER_KEY->accept(v);
                _produces->accept(v);
                _alias_rhs->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 44:  aliasSpec ::= SYMBOL produces alias_rhs
     *</b>
     */
    struct aliasSpec4 :public ASTNode
    {
        IAst *_SYMBOL;
        IAst *_produces;
        IAst *_alias_rhs;

        IAst *getSYMBOL() { return _SYMBOL; };
        void setSYMBOL(IAst *_SYMBOL) { this->_SYMBOL = _SYMBOL; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getalias_rhs() { return _alias_rhs; };
        void setalias_rhs(IAst *_alias_rhs) { this->_alias_rhs = _alias_rhs; }

        aliasSpec4(IToken* leftIToken, IToken* rightIToken,
                   IAst *_SYMBOL,
                   IAst *_produces,
                   IAst *_alias_rhs):ASTNode(leftIToken, rightIToken)    {
            this->_SYMBOL = _SYMBOL;
            ((ASTNode*) _SYMBOL)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_alias_rhs = _alias_rhs;
            ((ASTNode*) _alias_rhs)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SYMBOL);
            list.push_back(_produces);
            list.push_back(_alias_rhs);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _SYMBOL->accept(v);
                _produces->accept(v);
                _alias_rhs->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 45:  aliasSpec ::= alias_lhs_macro_name produces alias_rhs
     *</b>
     */
    struct aliasSpec5 :public ASTNode
    {
        IAst *_alias_lhs_macro_name;
        IAst *_produces;
        IAst *_alias_rhs;

        IAst *getalias_lhs_macro_name() { return _alias_lhs_macro_name; };
        void setalias_lhs_macro_name(IAst *_alias_lhs_macro_name) { this->_alias_lhs_macro_name = _alias_lhs_macro_name; }
        IAst *getproduces() { return _produces; };
        void setproduces(IAst *_produces) { this->_produces = _produces; }
        IAst *getalias_rhs() { return _alias_rhs; };
        void setalias_rhs(IAst *_alias_rhs) { this->_alias_rhs = _alias_rhs; }

        aliasSpec5(IToken* leftIToken, IToken* rightIToken,
                   IAst *_alias_lhs_macro_name,
                   IAst *_produces,
                   IAst *_alias_rhs):ASTNode(leftIToken, rightIToken)    {
            this->_alias_lhs_macro_name = _alias_lhs_macro_name;
            ((ASTNode*) _alias_lhs_macro_name)->setParent(this);
            this->_produces = _produces;
            ((ASTNode*) _produces)->setParent(this);
            this->_alias_rhs = _alias_rhs;
            ((ASTNode*) _alias_rhs)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_alias_lhs_macro_name);
            list.push_back(_produces);
            list.push_back(_alias_rhs);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _alias_lhs_macro_name->accept(v);
                _produces->accept(v);
                _alias_rhs->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 47:  alias_rhs ::= SYMBOL
     *</b>
     */
    struct alias_rhs0 :public ASTNodeToken
    {
        IToken* getSYMBOL() { return leftIToken; }

        alias_rhs0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 48:  alias_rhs ::= MACRO_NAME
     *</b>
     */
    struct alias_rhs1 :public ASTNodeToken
    {
        IToken* getMACRO_NAME() { return leftIToken; }

        alias_rhs1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 49:  alias_rhs ::= ERROR_KEY
     *</b>
     */
    struct alias_rhs2 :public ASTNodeToken
    {
        IToken* getERROR_KEY() { return leftIToken; }

        alias_rhs2(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 50:  alias_rhs ::= EOL_KEY
     *</b>
     */
    struct alias_rhs3 :public ASTNodeToken
    {
        IToken* getEOL_KEY() { return leftIToken; }

        alias_rhs3(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 51:  alias_rhs ::= EOF_KEY
     *</b>
     */
    struct alias_rhs4 :public ASTNodeToken
    {
        IToken* getEOF_KEY() { return leftIToken; }

        alias_rhs4(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 52:  alias_rhs ::= EMPTY_KEY
     *</b>
     */
    struct alias_rhs5 :public ASTNodeToken
    {
        IToken* getEMPTY_KEY() { return leftIToken; }

        alias_rhs5(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 53:  alias_rhs ::= IDENTIFIER_KEY
     *</b>
     */
    struct alias_rhs6 :public ASTNodeToken
    {
        IToken* getIDENTIFIER_KEY() { return leftIToken; }

        alias_rhs6(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 58:  macro_name_symbol ::= MACRO_NAME
     *</b>
     */
    struct macro_name_symbol0 :public ASTNodeToken
    {
        IToken* getMACRO_NAME() { return leftIToken; }

        macro_name_symbol0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 59:  macro_name_symbol ::= SYMBOL
     *</b>
     */
    struct macro_name_symbol1 :public ASTNodeToken
    {
        IToken* getSYMBOL() { return leftIToken; }

        macro_name_symbol1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 73:  drop_command ::= DROPSYMBOLS_KEY drop_symbols
     *</b>
     */
    struct drop_command0 :public ASTNode
    {
        IAst *_DROPSYMBOLS_KEY;
        IAst *_drop_symbols;

        IAst *getDROPSYMBOLS_KEY() { return _DROPSYMBOLS_KEY; };
        void setDROPSYMBOLS_KEY(IAst *_DROPSYMBOLS_KEY) { this->_DROPSYMBOLS_KEY = _DROPSYMBOLS_KEY; }
        IAst *getdrop_symbols() { return _drop_symbols; };
        void setdrop_symbols(IAst *_drop_symbols) { this->_drop_symbols = _drop_symbols; }

        drop_command0(IToken* leftIToken, IToken* rightIToken,
                      IAst *_DROPSYMBOLS_KEY,
                      IAst *_drop_symbols):ASTNode(leftIToken, rightIToken)    {
            this->_DROPSYMBOLS_KEY = _DROPSYMBOLS_KEY;
            ((ASTNode*) _DROPSYMBOLS_KEY)->setParent(this);
            this->_drop_symbols = _drop_symbols;
            ((ASTNode*) _drop_symbols)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_DROPSYMBOLS_KEY);
            list.push_back(_drop_symbols);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _DROPSYMBOLS_KEY->accept(v);
                _drop_symbols->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 74:  drop_command ::= DROPRULES_KEY drop_rules
     *</b>
     */
    struct drop_command1 :public ASTNode
    {
        IAst *_DROPRULES_KEY;
        IAst *_drop_rules;

        IAst *getDROPRULES_KEY() { return _DROPRULES_KEY; };
        void setDROPRULES_KEY(IAst *_DROPRULES_KEY) { this->_DROPRULES_KEY = _DROPRULES_KEY; }
        IAst *getdrop_rules() { return _drop_rules; };
        void setdrop_rules(IAst *_drop_rules) { this->_drop_rules = _drop_rules; }

        drop_command1(IToken* leftIToken, IToken* rightIToken,
                      IAst *_DROPRULES_KEY,
                      IAst *_drop_rules):ASTNode(leftIToken, rightIToken)    {
            this->_DROPRULES_KEY = _DROPRULES_KEY;
            ((ASTNode*) _DROPRULES_KEY)->setParent(this);
            this->_drop_rules = _drop_rules;
            ((ASTNode*) _drop_rules)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_DROPRULES_KEY);
            list.push_back(_drop_rules);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _DROPRULES_KEY->accept(v);
                _drop_rules->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 90:  name ::= SYMBOL
     *</b>
     */
    struct name0 :public ASTNodeToken
    {
        IToken* getSYMBOL() { return leftIToken; }

        name0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 91:  name ::= MACRO_NAME
     *</b>
     */
    struct name1 :public ASTNodeToken
    {
        IToken* getMACRO_NAME() { return leftIToken; }

        name1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 92:  name ::= EMPTY_KEY
     *</b>
     */
    struct name2 :public ASTNodeToken
    {
        IToken* getEMPTY_KEY() { return leftIToken; }

        name2(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 93:  name ::= ERROR_KEY
     *</b>
     */
    struct name3 :public ASTNodeToken
    {
        IToken* getERROR_KEY() { return leftIToken; }

        name3(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 94:  name ::= EOL_KEY
     *</b>
     */
    struct name4 :public ASTNodeToken
    {
        IToken* getEOL_KEY() { return leftIToken; }

        name4(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 95:  name ::= IDENTIFIER_KEY
     *</b>
     */
    struct name5 :public ASTNodeToken
    {
        IToken* getIDENTIFIER_KEY() { return leftIToken; }

        name5(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 107:  produces ::= ::=
     *</b>
     */
    struct produces0 :public ASTNodeToken
    {
        IToken* getEQUIVALENCE() { return leftIToken; }

        produces0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 108:  produces ::= ::=?
     *</b>
     */
    struct produces1 :public ASTNodeToken
    {
        IToken* getPRIORITY_EQUIVALENCE() { return leftIToken; }

        produces1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 109:  produces ::= ->
     *</b>
     */
    struct produces2 :public ASTNodeToken
    {
        IToken* getARROW() { return leftIToken; }

        produces2(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 110:  produces ::= ->?
     *</b>
     */
    struct produces3 :public ASTNodeToken
    {
        IToken* getPRIORITY_ARROW() { return leftIToken; }

        produces3(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 114:  symWithAttrs ::= EMPTY_KEY
     *</b>
     */
    struct symWithAttrs0 :public ASTNodeToken
    {
        IToken* getEMPTY_KEY() { return leftIToken; }

        symWithAttrs0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 115:  symWithAttrs ::= SYMBOL optAttrList
     *</b>
     */
    struct symWithAttrs1 :public ASTNode
    {
        IAst *_SYMBOL;
        IAst *_optAttrList;

        IAst *getSYMBOL() { return _SYMBOL; };
        void setSYMBOL(IAst *_SYMBOL) { this->_SYMBOL = _SYMBOL; }
        /**
         * The value returned by <b>getoptAttrList</b> may be <b>nullptr</b>
         */
        IAst *getoptAttrList() { return _optAttrList; };
        void setoptAttrList(IAst *_optAttrList) { this->_optAttrList = _optAttrList; }

        symWithAttrs1(IToken* leftIToken, IToken* rightIToken,
                      IAst *_SYMBOL,
                      IAst *_optAttrList):ASTNode(leftIToken, rightIToken)    {
            this->_SYMBOL = _SYMBOL;
            ((ASTNode*) _SYMBOL)->setParent(this);
            this->_optAttrList = _optAttrList;
            if (_optAttrList != nullptr) ((ASTNode*) _optAttrList)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SYMBOL);
            list.push_back(_optAttrList);
            return list;
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            bool checkChildren = v->visit(this);
            if (checkChildren)
            {
                _SYMBOL->accept(v);
                if (_optAttrList != nullptr) _optAttrList->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 123:  start_symbol ::= SYMBOL
     *</b>
     */
    struct start_symbol0 :public ASTNodeToken
    {
        IToken* getSYMBOL() { return leftIToken; }

        start_symbol0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 124:  start_symbol ::= MACRO_NAME
     *</b>
     */
    struct start_symbol1 :public ASTNodeToken
    {
        IToken* getMACRO_NAME() { return leftIToken; }

        start_symbol1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 130:  terminal_symbol ::= SYMBOL
     *</b>
     */
    struct terminal_symbol0 :public ASTNodeToken
    {
        LPGParser* environment;
        LPGParser* getEnvironment() { return environment; }

        IToken* getSYMBOL() { return leftIToken; }

        terminal_symbol0(LPGParser *environment, IToken* token):ASTNodeToken    (token)
        {
            this->environment = environment;
            initialize();
        }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }

    //#line 264 "LPGParser.g

  
     };

    /**
     *<b>
     *<li>Rule 131:  terminal_symbol ::= MACRO_NAME
     *</b>
     */
    struct terminal_symbol1 :public ASTNodeToken
    {
        IToken* getMACRO_NAME() { return leftIToken; }

        terminal_symbol1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

        void accept(IAstVisitor* v)
        {
            if (! v->preVisit(this)) return;
            enter((Visitor*) v);
            v->postVisit(this);
        }

        void enter(Visitor *v)
        {
            v->visit(this);
            v->endVisit(this);
        }
    };

    struct Visitor :public IAstVisitor
    {
      virtual  bool visit(ASTNode *n)=0;
     virtual   void endVisit(ASTNode *n)=0;

     virtual   bool visit(ASTNodeToken *n)=0;
      virtual  void endVisit(ASTNodeToken *n)=0;

     virtual   bool visit(LPG *n)=0;
      virtual  void endVisit(LPG *n)=0;

     virtual   bool visit(LPG_itemList *n)=0;
      virtual  void endVisit(LPG_itemList *n)=0;

     virtual   bool visit(AliasSeg *n)=0;
      virtual  void endVisit(AliasSeg *n)=0;

     virtual   bool visit(AstSeg *n)=0;
      virtual  void endVisit(AstSeg *n)=0;

     virtual   bool visit(DefineSeg *n)=0;
      virtual  void endVisit(DefineSeg *n)=0;

     virtual   bool visit(EofSeg *n)=0;
      virtual  void endVisit(EofSeg *n)=0;

     virtual   bool visit(EolSeg *n)=0;
      virtual  void endVisit(EolSeg *n)=0;

     virtual   bool visit(ErrorSeg *n)=0;
      virtual  void endVisit(ErrorSeg *n)=0;

     virtual   bool visit(ExportSeg *n)=0;
      virtual  void endVisit(ExportSeg *n)=0;

     virtual   bool visit(GlobalsSeg *n)=0;
      virtual  void endVisit(GlobalsSeg *n)=0;

     virtual   bool visit(HeadersSeg *n)=0;
      virtual  void endVisit(HeadersSeg *n)=0;

     virtual   bool visit(IdentifierSeg *n)=0;
      virtual  void endVisit(IdentifierSeg *n)=0;

     virtual   bool visit(ImportSeg *n)=0;
      virtual  void endVisit(ImportSeg *n)=0;

     virtual   bool visit(IncludeSeg *n)=0;
      virtual  void endVisit(IncludeSeg *n)=0;

     virtual   bool visit(KeywordsSeg *n)=0;
      virtual  void endVisit(KeywordsSeg *n)=0;

     virtual   bool visit(NamesSeg *n)=0;
      virtual  void endVisit(NamesSeg *n)=0;

     virtual   bool visit(NoticeSeg *n)=0;
      virtual  void endVisit(NoticeSeg *n)=0;

     virtual   bool visit(RulesSeg *n)=0;
      virtual  void endVisit(RulesSeg *n)=0;

     virtual   bool visit(SoftKeywordsSeg *n)=0;
      virtual  void endVisit(SoftKeywordsSeg *n)=0;

     virtual   bool visit(StartSeg *n)=0;
      virtual  void endVisit(StartSeg *n)=0;

     virtual   bool visit(TerminalsSeg *n)=0;
      virtual  void endVisit(TerminalsSeg *n)=0;

     virtual   bool visit(TrailersSeg *n)=0;
      virtual  void endVisit(TrailersSeg *n)=0;

     virtual   bool visit(TypesSeg *n)=0;
      virtual  void endVisit(TypesSeg *n)=0;

     virtual   bool visit(RecoverSeg *n)=0;
      virtual  void endVisit(RecoverSeg *n)=0;

     virtual   bool visit(PredecessorSeg *n)=0;
      virtual  void endVisit(PredecessorSeg *n)=0;

     virtual   bool visit(option_specList *n)=0;
      virtual  void endVisit(option_specList *n)=0;

     virtual   bool visit(option_spec *n)=0;
      virtual  void endVisit(option_spec *n)=0;

     virtual   bool visit(optionList *n)=0;
      virtual  void endVisit(optionList *n)=0;

     virtual   bool visit(option *n)=0;
      virtual  void endVisit(option *n)=0;

     virtual   bool visit(SYMBOLList *n)=0;
      virtual  void endVisit(SYMBOLList *n)=0;

     virtual   bool visit(aliasSpecList *n)=0;
      virtual  void endVisit(aliasSpecList *n)=0;

     virtual   bool visit(alias_lhs_macro_name *n)=0;
      virtual  void endVisit(alias_lhs_macro_name *n)=0;

     virtual   bool visit(defineSpecList *n)=0;
      virtual  void endVisit(defineSpecList *n)=0;

     virtual   bool visit(defineSpec *n)=0;
      virtual  void endVisit(defineSpec *n)=0;

     virtual   bool visit(macro_segment *n)=0;
      virtual  void endVisit(macro_segment *n)=0;

     virtual   bool visit(terminal_symbolList *n)=0;
      virtual  void endVisit(terminal_symbolList *n)=0;

     virtual   bool visit(action_segmentList *n)=0;
      virtual  void endVisit(action_segmentList *n)=0;

     virtual   bool visit(import_segment *n)=0;
      virtual  void endVisit(import_segment *n)=0;

     virtual   bool visit(drop_commandList *n)=0;
      virtual  void endVisit(drop_commandList *n)=0;

     virtual   bool visit(drop_ruleList *n)=0;
      virtual  void endVisit(drop_ruleList *n)=0;

     virtual   bool visit(drop_rule *n)=0;
      virtual  void endVisit(drop_rule *n)=0;

     virtual   bool visit(optMacroName *n)=0;
      virtual  void endVisit(optMacroName *n)=0;

     virtual   bool visit(include_segment *n)=0;
      virtual  void endVisit(include_segment *n)=0;

     virtual   bool visit(keywordSpecList *n)=0;
      virtual  void endVisit(keywordSpecList *n)=0;

     virtual   bool visit(keywordSpec *n)=0;
      virtual  void endVisit(keywordSpec *n)=0;

     virtual   bool visit(nameSpecList *n)=0;
      virtual  void endVisit(nameSpecList *n)=0;

     virtual   bool visit(nameSpec *n)=0;
      virtual  void endVisit(nameSpec *n)=0;

     virtual   bool visit(rules_segment *n)=0;
      virtual  void endVisit(rules_segment *n)=0;

     virtual   bool visit(nonTermList *n)=0;
      virtual  void endVisit(nonTermList *n)=0;

     virtual   bool visit(nonTerm *n)=0;
      virtual  void endVisit(nonTerm *n)=0;

     virtual   bool visit(RuleName *n)=0;
      virtual  void endVisit(RuleName *n)=0;

     virtual   bool visit(ruleList *n)=0;
      virtual  void endVisit(ruleList *n)=0;

     virtual   bool visit(rule *n)=0;
      virtual  void endVisit(rule *n)=0;

     virtual   bool visit(symWithAttrsList *n)=0;
      virtual  void endVisit(symWithAttrsList *n)=0;

     virtual   bool visit(symAttrs *n)=0;
      virtual  void endVisit(symAttrs *n)=0;

     virtual   bool visit(action_segment *n)=0;
      virtual  void endVisit(action_segment *n)=0;

     virtual   bool visit(start_symbolList *n)=0;
      virtual  void endVisit(start_symbolList *n)=0;

     virtual   bool visit(terminalList *n)=0;
      virtual  void endVisit(terminalList *n)=0;

     virtual   bool visit(terminal *n)=0;
      virtual  void endVisit(terminal *n)=0;

     virtual   bool visit(optTerminalAlias *n)=0;
      virtual  void endVisit(optTerminalAlias *n)=0;

     virtual   bool visit(type_declarationsList *n)=0;
      virtual  void endVisit(type_declarationsList *n)=0;

     virtual   bool visit(type_declarations *n)=0;
      virtual  void endVisit(type_declarations *n)=0;

     virtual   bool visit(symbol_pairList *n)=0;
      virtual  void endVisit(symbol_pairList *n)=0;

     virtual   bool visit(symbol_pair *n)=0;
      virtual  void endVisit(symbol_pair *n)=0;

     virtual   bool visit(recover_symbol *n)=0;
      virtual  void endVisit(recover_symbol *n)=0;

     virtual   bool visit(END_KEY_OPT *n)=0;
      virtual  void endVisit(END_KEY_OPT *n)=0;

     virtual   bool visit(option_value0 *n)=0;
      virtual  void endVisit(option_value0 *n)=0;

     virtual   bool visit(option_value1 *n)=0;
      virtual  void endVisit(option_value1 *n)=0;

     virtual   bool visit(aliasSpec0 *n)=0;
      virtual  void endVisit(aliasSpec0 *n)=0;

     virtual   bool visit(aliasSpec1 *n)=0;
      virtual  void endVisit(aliasSpec1 *n)=0;

     virtual   bool visit(aliasSpec2 *n)=0;
      virtual  void endVisit(aliasSpec2 *n)=0;

     virtual   bool visit(aliasSpec3 *n)=0;
      virtual  void endVisit(aliasSpec3 *n)=0;

     virtual   bool visit(aliasSpec4 *n)=0;
      virtual  void endVisit(aliasSpec4 *n)=0;

     virtual   bool visit(aliasSpec5 *n)=0;
      virtual  void endVisit(aliasSpec5 *n)=0;

     virtual   bool visit(alias_rhs0 *n)=0;
      virtual  void endVisit(alias_rhs0 *n)=0;

     virtual   bool visit(alias_rhs1 *n)=0;
      virtual  void endVisit(alias_rhs1 *n)=0;

     virtual   bool visit(alias_rhs2 *n)=0;
      virtual  void endVisit(alias_rhs2 *n)=0;

     virtual   bool visit(alias_rhs3 *n)=0;
      virtual  void endVisit(alias_rhs3 *n)=0;

     virtual   bool visit(alias_rhs4 *n)=0;
      virtual  void endVisit(alias_rhs4 *n)=0;

     virtual   bool visit(alias_rhs5 *n)=0;
      virtual  void endVisit(alias_rhs5 *n)=0;

     virtual   bool visit(alias_rhs6 *n)=0;
      virtual  void endVisit(alias_rhs6 *n)=0;

     virtual   bool visit(macro_name_symbol0 *n)=0;
      virtual  void endVisit(macro_name_symbol0 *n)=0;

     virtual   bool visit(macro_name_symbol1 *n)=0;
      virtual  void endVisit(macro_name_symbol1 *n)=0;

     virtual   bool visit(drop_command0 *n)=0;
      virtual  void endVisit(drop_command0 *n)=0;

     virtual   bool visit(drop_command1 *n)=0;
      virtual  void endVisit(drop_command1 *n)=0;

     virtual   bool visit(name0 *n)=0;
      virtual  void endVisit(name0 *n)=0;

     virtual   bool visit(name1 *n)=0;
      virtual  void endVisit(name1 *n)=0;

     virtual   bool visit(name2 *n)=0;
      virtual  void endVisit(name2 *n)=0;

     virtual   bool visit(name3 *n)=0;
      virtual  void endVisit(name3 *n)=0;

     virtual   bool visit(name4 *n)=0;
      virtual  void endVisit(name4 *n)=0;

     virtual   bool visit(name5 *n)=0;
      virtual  void endVisit(name5 *n)=0;

     virtual   bool visit(produces0 *n)=0;
      virtual  void endVisit(produces0 *n)=0;

     virtual   bool visit(produces1 *n)=0;
      virtual  void endVisit(produces1 *n)=0;

     virtual   bool visit(produces2 *n)=0;
      virtual  void endVisit(produces2 *n)=0;

     virtual   bool visit(produces3 *n)=0;
      virtual  void endVisit(produces3 *n)=0;

     virtual   bool visit(symWithAttrs0 *n)=0;
      virtual  void endVisit(symWithAttrs0 *n)=0;

     virtual   bool visit(symWithAttrs1 *n)=0;
      virtual  void endVisit(symWithAttrs1 *n)=0;

     virtual   bool visit(start_symbol0 *n)=0;
      virtual  void endVisit(start_symbol0 *n)=0;

     virtual   bool visit(start_symbol1 *n)=0;
      virtual  void endVisit(start_symbol1 *n)=0;

     virtual   bool visit(terminal_symbol0 *n)=0;
      virtual  void endVisit(terminal_symbol0 *n)=0;

     virtual   bool visit(terminal_symbol1 *n)=0;
      virtual  void endVisit(terminal_symbol1 *n)=0;

    };

    struct AbstractVisitor :public Visitor
    {
        virtual void unimplementedVisitor(const std::string& s)=0;

       virtual bool preVisit(IAst* element) { return true; }

       virtual void postVisit(IAst* element) {}

     virtual   bool visit(ASTNodeToken *n) { unimplementedVisitor("visit(ASTNodeToken)"); return true; }
      virtual  void endVisit(ASTNodeToken *n) { unimplementedVisitor("endVisit(ASTNodeToken)"); }

     virtual   bool visit(LPG *n) { unimplementedVisitor("visit(LPG)"); return true; }
      virtual  void endVisit(LPG *n) { unimplementedVisitor("endVisit(LPG)"); }

     virtual   bool visit(LPG_itemList *n) { unimplementedVisitor("visit(LPG_itemList)"); return true; }
      virtual  void endVisit(LPG_itemList *n) { unimplementedVisitor("endVisit(LPG_itemList)"); }

     virtual   bool visit(AliasSeg *n) { unimplementedVisitor("visit(AliasSeg)"); return true; }
      virtual  void endVisit(AliasSeg *n) { unimplementedVisitor("endVisit(AliasSeg)"); }

     virtual   bool visit(AstSeg *n) { unimplementedVisitor("visit(AstSeg)"); return true; }
      virtual  void endVisit(AstSeg *n) { unimplementedVisitor("endVisit(AstSeg)"); }

     virtual   bool visit(DefineSeg *n) { unimplementedVisitor("visit(DefineSeg)"); return true; }
      virtual  void endVisit(DefineSeg *n) { unimplementedVisitor("endVisit(DefineSeg)"); }

     virtual   bool visit(EofSeg *n) { unimplementedVisitor("visit(EofSeg)"); return true; }
      virtual  void endVisit(EofSeg *n) { unimplementedVisitor("endVisit(EofSeg)"); }

     virtual   bool visit(EolSeg *n) { unimplementedVisitor("visit(EolSeg)"); return true; }
      virtual  void endVisit(EolSeg *n) { unimplementedVisitor("endVisit(EolSeg)"); }

     virtual   bool visit(ErrorSeg *n) { unimplementedVisitor("visit(ErrorSeg)"); return true; }
      virtual  void endVisit(ErrorSeg *n) { unimplementedVisitor("endVisit(ErrorSeg)"); }

     virtual   bool visit(ExportSeg *n) { unimplementedVisitor("visit(ExportSeg)"); return true; }
      virtual  void endVisit(ExportSeg *n) { unimplementedVisitor("endVisit(ExportSeg)"); }

     virtual   bool visit(GlobalsSeg *n) { unimplementedVisitor("visit(GlobalsSeg)"); return true; }
      virtual  void endVisit(GlobalsSeg *n) { unimplementedVisitor("endVisit(GlobalsSeg)"); }

     virtual   bool visit(HeadersSeg *n) { unimplementedVisitor("visit(HeadersSeg)"); return true; }
      virtual  void endVisit(HeadersSeg *n) { unimplementedVisitor("endVisit(HeadersSeg)"); }

     virtual   bool visit(IdentifierSeg *n) { unimplementedVisitor("visit(IdentifierSeg)"); return true; }
      virtual  void endVisit(IdentifierSeg *n) { unimplementedVisitor("endVisit(IdentifierSeg)"); }

     virtual   bool visit(ImportSeg *n) { unimplementedVisitor("visit(ImportSeg)"); return true; }
      virtual  void endVisit(ImportSeg *n) { unimplementedVisitor("endVisit(ImportSeg)"); }

     virtual   bool visit(IncludeSeg *n) { unimplementedVisitor("visit(IncludeSeg)"); return true; }
      virtual  void endVisit(IncludeSeg *n) { unimplementedVisitor("endVisit(IncludeSeg)"); }

     virtual   bool visit(KeywordsSeg *n) { unimplementedVisitor("visit(KeywordsSeg)"); return true; }
      virtual  void endVisit(KeywordsSeg *n) { unimplementedVisitor("endVisit(KeywordsSeg)"); }

     virtual   bool visit(NamesSeg *n) { unimplementedVisitor("visit(NamesSeg)"); return true; }
      virtual  void endVisit(NamesSeg *n) { unimplementedVisitor("endVisit(NamesSeg)"); }

     virtual   bool visit(NoticeSeg *n) { unimplementedVisitor("visit(NoticeSeg)"); return true; }
      virtual  void endVisit(NoticeSeg *n) { unimplementedVisitor("endVisit(NoticeSeg)"); }

     virtual   bool visit(RulesSeg *n) { unimplementedVisitor("visit(RulesSeg)"); return true; }
      virtual  void endVisit(RulesSeg *n) { unimplementedVisitor("endVisit(RulesSeg)"); }

     virtual   bool visit(SoftKeywordsSeg *n) { unimplementedVisitor("visit(SoftKeywordsSeg)"); return true; }
      virtual  void endVisit(SoftKeywordsSeg *n) { unimplementedVisitor("endVisit(SoftKeywordsSeg)"); }

     virtual   bool visit(StartSeg *n) { unimplementedVisitor("visit(StartSeg)"); return true; }
      virtual  void endVisit(StartSeg *n) { unimplementedVisitor("endVisit(StartSeg)"); }

     virtual   bool visit(TerminalsSeg *n) { unimplementedVisitor("visit(TerminalsSeg)"); return true; }
      virtual  void endVisit(TerminalsSeg *n) { unimplementedVisitor("endVisit(TerminalsSeg)"); }

     virtual   bool visit(TrailersSeg *n) { unimplementedVisitor("visit(TrailersSeg)"); return true; }
      virtual  void endVisit(TrailersSeg *n) { unimplementedVisitor("endVisit(TrailersSeg)"); }

     virtual   bool visit(TypesSeg *n) { unimplementedVisitor("visit(TypesSeg)"); return true; }
      virtual  void endVisit(TypesSeg *n) { unimplementedVisitor("endVisit(TypesSeg)"); }

     virtual   bool visit(RecoverSeg *n) { unimplementedVisitor("visit(RecoverSeg)"); return true; }
      virtual  void endVisit(RecoverSeg *n) { unimplementedVisitor("endVisit(RecoverSeg)"); }

     virtual   bool visit(PredecessorSeg *n) { unimplementedVisitor("visit(PredecessorSeg)"); return true; }
      virtual  void endVisit(PredecessorSeg *n) { unimplementedVisitor("endVisit(PredecessorSeg)"); }

     virtual   bool visit(option_specList *n) { unimplementedVisitor("visit(option_specList)"); return true; }
      virtual  void endVisit(option_specList *n) { unimplementedVisitor("endVisit(option_specList)"); }

     virtual   bool visit(option_spec *n) { unimplementedVisitor("visit(option_spec)"); return true; }
      virtual  void endVisit(option_spec *n) { unimplementedVisitor("endVisit(option_spec)"); }

     virtual   bool visit(optionList *n) { unimplementedVisitor("visit(optionList)"); return true; }
      virtual  void endVisit(optionList *n) { unimplementedVisitor("endVisit(optionList)"); }

     virtual   bool visit(option *n) { unimplementedVisitor("visit(option)"); return true; }
      virtual  void endVisit(option *n) { unimplementedVisitor("endVisit(option)"); }

     virtual   bool visit(SYMBOLList *n) { unimplementedVisitor("visit(SYMBOLList)"); return true; }
      virtual  void endVisit(SYMBOLList *n) { unimplementedVisitor("endVisit(SYMBOLList)"); }

     virtual   bool visit(aliasSpecList *n) { unimplementedVisitor("visit(aliasSpecList)"); return true; }
      virtual  void endVisit(aliasSpecList *n) { unimplementedVisitor("endVisit(aliasSpecList)"); }

     virtual   bool visit(alias_lhs_macro_name *n) { unimplementedVisitor("visit(alias_lhs_macro_name)"); return true; }
      virtual  void endVisit(alias_lhs_macro_name *n) { unimplementedVisitor("endVisit(alias_lhs_macro_name)"); }

     virtual   bool visit(defineSpecList *n) { unimplementedVisitor("visit(defineSpecList)"); return true; }
      virtual  void endVisit(defineSpecList *n) { unimplementedVisitor("endVisit(defineSpecList)"); }

     virtual   bool visit(defineSpec *n) { unimplementedVisitor("visit(defineSpec)"); return true; }
      virtual  void endVisit(defineSpec *n) { unimplementedVisitor("endVisit(defineSpec)"); }

     virtual   bool visit(macro_segment *n) { unimplementedVisitor("visit(macro_segment)"); return true; }
      virtual  void endVisit(macro_segment *n) { unimplementedVisitor("endVisit(macro_segment)"); }

     virtual   bool visit(terminal_symbolList *n) { unimplementedVisitor("visit(terminal_symbolList)"); return true; }
      virtual  void endVisit(terminal_symbolList *n) { unimplementedVisitor("endVisit(terminal_symbolList)"); }

     virtual   bool visit(action_segmentList *n) { unimplementedVisitor("visit(action_segmentList)"); return true; }
      virtual  void endVisit(action_segmentList *n) { unimplementedVisitor("endVisit(action_segmentList)"); }

     virtual   bool visit(import_segment *n) { unimplementedVisitor("visit(import_segment)"); return true; }
      virtual  void endVisit(import_segment *n) { unimplementedVisitor("endVisit(import_segment)"); }

     virtual   bool visit(drop_commandList *n) { unimplementedVisitor("visit(drop_commandList)"); return true; }
      virtual  void endVisit(drop_commandList *n) { unimplementedVisitor("endVisit(drop_commandList)"); }

     virtual   bool visit(drop_ruleList *n) { unimplementedVisitor("visit(drop_ruleList)"); return true; }
      virtual  void endVisit(drop_ruleList *n) { unimplementedVisitor("endVisit(drop_ruleList)"); }

     virtual   bool visit(drop_rule *n) { unimplementedVisitor("visit(drop_rule)"); return true; }
      virtual  void endVisit(drop_rule *n) { unimplementedVisitor("endVisit(drop_rule)"); }

     virtual   bool visit(optMacroName *n) { unimplementedVisitor("visit(optMacroName)"); return true; }
      virtual  void endVisit(optMacroName *n) { unimplementedVisitor("endVisit(optMacroName)"); }

     virtual   bool visit(include_segment *n) { unimplementedVisitor("visit(include_segment)"); return true; }
      virtual  void endVisit(include_segment *n) { unimplementedVisitor("endVisit(include_segment)"); }

     virtual   bool visit(keywordSpecList *n) { unimplementedVisitor("visit(keywordSpecList)"); return true; }
      virtual  void endVisit(keywordSpecList *n) { unimplementedVisitor("endVisit(keywordSpecList)"); }

     virtual   bool visit(keywordSpec *n) { unimplementedVisitor("visit(keywordSpec)"); return true; }
      virtual  void endVisit(keywordSpec *n) { unimplementedVisitor("endVisit(keywordSpec)"); }

     virtual   bool visit(nameSpecList *n) { unimplementedVisitor("visit(nameSpecList)"); return true; }
      virtual  void endVisit(nameSpecList *n) { unimplementedVisitor("endVisit(nameSpecList)"); }

     virtual   bool visit(nameSpec *n) { unimplementedVisitor("visit(nameSpec)"); return true; }
      virtual  void endVisit(nameSpec *n) { unimplementedVisitor("endVisit(nameSpec)"); }

     virtual   bool visit(rules_segment *n) { unimplementedVisitor("visit(rules_segment)"); return true; }
      virtual  void endVisit(rules_segment *n) { unimplementedVisitor("endVisit(rules_segment)"); }

     virtual   bool visit(nonTermList *n) { unimplementedVisitor("visit(nonTermList)"); return true; }
      virtual  void endVisit(nonTermList *n) { unimplementedVisitor("endVisit(nonTermList)"); }

     virtual   bool visit(nonTerm *n) { unimplementedVisitor("visit(nonTerm)"); return true; }
      virtual  void endVisit(nonTerm *n) { unimplementedVisitor("endVisit(nonTerm)"); }

     virtual   bool visit(RuleName *n) { unimplementedVisitor("visit(RuleName)"); return true; }
      virtual  void endVisit(RuleName *n) { unimplementedVisitor("endVisit(RuleName)"); }

     virtual   bool visit(ruleList *n) { unimplementedVisitor("visit(ruleList)"); return true; }
      virtual  void endVisit(ruleList *n) { unimplementedVisitor("endVisit(ruleList)"); }

     virtual   bool visit(rule *n) { unimplementedVisitor("visit(rule)"); return true; }
      virtual  void endVisit(rule *n) { unimplementedVisitor("endVisit(rule)"); }

     virtual   bool visit(symWithAttrsList *n) { unimplementedVisitor("visit(symWithAttrsList)"); return true; }
      virtual  void endVisit(symWithAttrsList *n) { unimplementedVisitor("endVisit(symWithAttrsList)"); }

     virtual   bool visit(symAttrs *n) { unimplementedVisitor("visit(symAttrs)"); return true; }
      virtual  void endVisit(symAttrs *n) { unimplementedVisitor("endVisit(symAttrs)"); }

     virtual   bool visit(action_segment *n) { unimplementedVisitor("visit(action_segment)"); return true; }
      virtual  void endVisit(action_segment *n) { unimplementedVisitor("endVisit(action_segment)"); }

     virtual   bool visit(start_symbolList *n) { unimplementedVisitor("visit(start_symbolList)"); return true; }
      virtual  void endVisit(start_symbolList *n) { unimplementedVisitor("endVisit(start_symbolList)"); }

     virtual   bool visit(terminalList *n) { unimplementedVisitor("visit(terminalList)"); return true; }
      virtual  void endVisit(terminalList *n) { unimplementedVisitor("endVisit(terminalList)"); }

     virtual   bool visit(terminal *n) { unimplementedVisitor("visit(terminal)"); return true; }
      virtual  void endVisit(terminal *n) { unimplementedVisitor("endVisit(terminal)"); }

     virtual   bool visit(optTerminalAlias *n) { unimplementedVisitor("visit(optTerminalAlias)"); return true; }
      virtual  void endVisit(optTerminalAlias *n) { unimplementedVisitor("endVisit(optTerminalAlias)"); }

     virtual   bool visit(type_declarationsList *n) { unimplementedVisitor("visit(type_declarationsList)"); return true; }
      virtual  void endVisit(type_declarationsList *n) { unimplementedVisitor("endVisit(type_declarationsList)"); }

     virtual   bool visit(type_declarations *n) { unimplementedVisitor("visit(type_declarations)"); return true; }
      virtual  void endVisit(type_declarations *n) { unimplementedVisitor("endVisit(type_declarations)"); }

     virtual   bool visit(symbol_pairList *n) { unimplementedVisitor("visit(symbol_pairList)"); return true; }
      virtual  void endVisit(symbol_pairList *n) { unimplementedVisitor("endVisit(symbol_pairList)"); }

     virtual   bool visit(symbol_pair *n) { unimplementedVisitor("visit(symbol_pair)"); return true; }
      virtual  void endVisit(symbol_pair *n) { unimplementedVisitor("endVisit(symbol_pair)"); }

     virtual   bool visit(recover_symbol *n) { unimplementedVisitor("visit(recover_symbol)"); return true; }
      virtual  void endVisit(recover_symbol *n) { unimplementedVisitor("endVisit(recover_symbol)"); }

     virtual   bool visit(END_KEY_OPT *n) { unimplementedVisitor("visit(END_KEY_OPT)"); return true; }
      virtual  void endVisit(END_KEY_OPT *n) { unimplementedVisitor("endVisit(END_KEY_OPT)"); }

     virtual   bool visit(option_value0 *n) { unimplementedVisitor("visit(option_value0)"); return true; }
      virtual  void endVisit(option_value0 *n) { unimplementedVisitor("endVisit(option_value0)"); }

     virtual   bool visit(option_value1 *n) { unimplementedVisitor("visit(option_value1)"); return true; }
      virtual  void endVisit(option_value1 *n) { unimplementedVisitor("endVisit(option_value1)"); }

     virtual   bool visit(aliasSpec0 *n) { unimplementedVisitor("visit(aliasSpec0)"); return true; }
      virtual  void endVisit(aliasSpec0 *n) { unimplementedVisitor("endVisit(aliasSpec0)"); }

     virtual   bool visit(aliasSpec1 *n) { unimplementedVisitor("visit(aliasSpec1)"); return true; }
      virtual  void endVisit(aliasSpec1 *n) { unimplementedVisitor("endVisit(aliasSpec1)"); }

     virtual   bool visit(aliasSpec2 *n) { unimplementedVisitor("visit(aliasSpec2)"); return true; }
      virtual  void endVisit(aliasSpec2 *n) { unimplementedVisitor("endVisit(aliasSpec2)"); }

     virtual   bool visit(aliasSpec3 *n) { unimplementedVisitor("visit(aliasSpec3)"); return true; }
      virtual  void endVisit(aliasSpec3 *n) { unimplementedVisitor("endVisit(aliasSpec3)"); }

     virtual   bool visit(aliasSpec4 *n) { unimplementedVisitor("visit(aliasSpec4)"); return true; }
      virtual  void endVisit(aliasSpec4 *n) { unimplementedVisitor("endVisit(aliasSpec4)"); }

     virtual   bool visit(aliasSpec5 *n) { unimplementedVisitor("visit(aliasSpec5)"); return true; }
      virtual  void endVisit(aliasSpec5 *n) { unimplementedVisitor("endVisit(aliasSpec5)"); }

     virtual   bool visit(alias_rhs0 *n) { unimplementedVisitor("visit(alias_rhs0)"); return true; }
      virtual  void endVisit(alias_rhs0 *n) { unimplementedVisitor("endVisit(alias_rhs0)"); }

     virtual   bool visit(alias_rhs1 *n) { unimplementedVisitor("visit(alias_rhs1)"); return true; }
      virtual  void endVisit(alias_rhs1 *n) { unimplementedVisitor("endVisit(alias_rhs1)"); }

     virtual   bool visit(alias_rhs2 *n) { unimplementedVisitor("visit(alias_rhs2)"); return true; }
      virtual  void endVisit(alias_rhs2 *n) { unimplementedVisitor("endVisit(alias_rhs2)"); }

     virtual   bool visit(alias_rhs3 *n) { unimplementedVisitor("visit(alias_rhs3)"); return true; }
      virtual  void endVisit(alias_rhs3 *n) { unimplementedVisitor("endVisit(alias_rhs3)"); }

     virtual   bool visit(alias_rhs4 *n) { unimplementedVisitor("visit(alias_rhs4)"); return true; }
      virtual  void endVisit(alias_rhs4 *n) { unimplementedVisitor("endVisit(alias_rhs4)"); }

     virtual   bool visit(alias_rhs5 *n) { unimplementedVisitor("visit(alias_rhs5)"); return true; }
      virtual  void endVisit(alias_rhs5 *n) { unimplementedVisitor("endVisit(alias_rhs5)"); }

     virtual   bool visit(alias_rhs6 *n) { unimplementedVisitor("visit(alias_rhs6)"); return true; }
      virtual  void endVisit(alias_rhs6 *n) { unimplementedVisitor("endVisit(alias_rhs6)"); }

     virtual   bool visit(macro_name_symbol0 *n) { unimplementedVisitor("visit(macro_name_symbol0)"); return true; }
      virtual  void endVisit(macro_name_symbol0 *n) { unimplementedVisitor("endVisit(macro_name_symbol0)"); }

     virtual   bool visit(macro_name_symbol1 *n) { unimplementedVisitor("visit(macro_name_symbol1)"); return true; }
      virtual  void endVisit(macro_name_symbol1 *n) { unimplementedVisitor("endVisit(macro_name_symbol1)"); }

     virtual   bool visit(drop_command0 *n) { unimplementedVisitor("visit(drop_command0)"); return true; }
      virtual  void endVisit(drop_command0 *n) { unimplementedVisitor("endVisit(drop_command0)"); }

     virtual   bool visit(drop_command1 *n) { unimplementedVisitor("visit(drop_command1)"); return true; }
      virtual  void endVisit(drop_command1 *n) { unimplementedVisitor("endVisit(drop_command1)"); }

     virtual   bool visit(name0 *n) { unimplementedVisitor("visit(name0)"); return true; }
      virtual  void endVisit(name0 *n) { unimplementedVisitor("endVisit(name0)"); }

     virtual   bool visit(name1 *n) { unimplementedVisitor("visit(name1)"); return true; }
      virtual  void endVisit(name1 *n) { unimplementedVisitor("endVisit(name1)"); }

     virtual   bool visit(name2 *n) { unimplementedVisitor("visit(name2)"); return true; }
      virtual  void endVisit(name2 *n) { unimplementedVisitor("endVisit(name2)"); }

     virtual   bool visit(name3 *n) { unimplementedVisitor("visit(name3)"); return true; }
      virtual  void endVisit(name3 *n) { unimplementedVisitor("endVisit(name3)"); }

     virtual   bool visit(name4 *n) { unimplementedVisitor("visit(name4)"); return true; }
      virtual  void endVisit(name4 *n) { unimplementedVisitor("endVisit(name4)"); }

     virtual   bool visit(name5 *n) { unimplementedVisitor("visit(name5)"); return true; }
      virtual  void endVisit(name5 *n) { unimplementedVisitor("endVisit(name5)"); }

     virtual   bool visit(produces0 *n) { unimplementedVisitor("visit(produces0)"); return true; }
      virtual  void endVisit(produces0 *n) { unimplementedVisitor("endVisit(produces0)"); }

     virtual   bool visit(produces1 *n) { unimplementedVisitor("visit(produces1)"); return true; }
      virtual  void endVisit(produces1 *n) { unimplementedVisitor("endVisit(produces1)"); }

     virtual   bool visit(produces2 *n) { unimplementedVisitor("visit(produces2)"); return true; }
      virtual  void endVisit(produces2 *n) { unimplementedVisitor("endVisit(produces2)"); }

     virtual   bool visit(produces3 *n) { unimplementedVisitor("visit(produces3)"); return true; }
      virtual  void endVisit(produces3 *n) { unimplementedVisitor("endVisit(produces3)"); }

     virtual   bool visit(symWithAttrs0 *n) { unimplementedVisitor("visit(symWithAttrs0)"); return true; }
      virtual  void endVisit(symWithAttrs0 *n) { unimplementedVisitor("endVisit(symWithAttrs0)"); }

     virtual   bool visit(symWithAttrs1 *n) { unimplementedVisitor("visit(symWithAttrs1)"); return true; }
      virtual  void endVisit(symWithAttrs1 *n) { unimplementedVisitor("endVisit(symWithAttrs1)"); }

     virtual   bool visit(start_symbol0 *n) { unimplementedVisitor("visit(start_symbol0)"); return true; }
      virtual  void endVisit(start_symbol0 *n) { unimplementedVisitor("endVisit(start_symbol0)"); }

     virtual   bool visit(start_symbol1 *n) { unimplementedVisitor("visit(start_symbol1)"); return true; }
      virtual  void endVisit(start_symbol1 *n) { unimplementedVisitor("endVisit(start_symbol1)"); }

     virtual   bool visit(terminal_symbol0 *n) { unimplementedVisitor("visit(terminal_symbol0)"); return true; }
      virtual  void endVisit(terminal_symbol0 *n) { unimplementedVisitor("endVisit(terminal_symbol0)"); }

     virtual   bool visit(terminal_symbol1 *n) { unimplementedVisitor("visit(terminal_symbol1)"); return true; }
      virtual  void endVisit(terminal_symbol1 *n) { unimplementedVisitor("endVisit(terminal_symbol1)"); }


     virtual   bool visit(ASTNode *n)
        {
            if (dynamic_cast<ASTNodeToken*>(n) ) return visit((ASTNodeToken*) n);
            else if (dynamic_cast<LPG*>(n) ) return visit((LPG*) n);
            else if (dynamic_cast<LPG_itemList*>(n) ) return visit((LPG_itemList*) n);
            else if (dynamic_cast<AliasSeg*>(n) ) return visit((AliasSeg*) n);
            else if (dynamic_cast<AstSeg*>(n) ) return visit((AstSeg*) n);
            else if (dynamic_cast<DefineSeg*>(n) ) return visit((DefineSeg*) n);
            else if (dynamic_cast<EofSeg*>(n) ) return visit((EofSeg*) n);
            else if (dynamic_cast<EolSeg*>(n) ) return visit((EolSeg*) n);
            else if (dynamic_cast<ErrorSeg*>(n) ) return visit((ErrorSeg*) n);
            else if (dynamic_cast<ExportSeg*>(n) ) return visit((ExportSeg*) n);
            else if (dynamic_cast<GlobalsSeg*>(n) ) return visit((GlobalsSeg*) n);
            else if (dynamic_cast<HeadersSeg*>(n) ) return visit((HeadersSeg*) n);
            else if (dynamic_cast<IdentifierSeg*>(n) ) return visit((IdentifierSeg*) n);
            else if (dynamic_cast<ImportSeg*>(n) ) return visit((ImportSeg*) n);
            else if (dynamic_cast<IncludeSeg*>(n) ) return visit((IncludeSeg*) n);
            else if (dynamic_cast<KeywordsSeg*>(n) ) return visit((KeywordsSeg*) n);
            else if (dynamic_cast<NamesSeg*>(n) ) return visit((NamesSeg*) n);
            else if (dynamic_cast<NoticeSeg*>(n) ) return visit((NoticeSeg*) n);
            else if (dynamic_cast<RulesSeg*>(n) ) return visit((RulesSeg*) n);
            else if (dynamic_cast<SoftKeywordsSeg*>(n) ) return visit((SoftKeywordsSeg*) n);
            else if (dynamic_cast<StartSeg*>(n) ) return visit((StartSeg*) n);
            else if (dynamic_cast<TerminalsSeg*>(n) ) return visit((TerminalsSeg*) n);
            else if (dynamic_cast<TrailersSeg*>(n) ) return visit((TrailersSeg*) n);
            else if (dynamic_cast<TypesSeg*>(n) ) return visit((TypesSeg*) n);
            else if (dynamic_cast<RecoverSeg*>(n) ) return visit((RecoverSeg*) n);
            else if (dynamic_cast<PredecessorSeg*>(n) ) return visit((PredecessorSeg*) n);
            else if (dynamic_cast<option_specList*>(n) ) return visit((option_specList*) n);
            else if (dynamic_cast<option_spec*>(n) ) return visit((option_spec*) n);
            else if (dynamic_cast<optionList*>(n) ) return visit((optionList*) n);
            else if (dynamic_cast<option*>(n) ) return visit((option*) n);
            else if (dynamic_cast<SYMBOLList*>(n) ) return visit((SYMBOLList*) n);
            else if (dynamic_cast<aliasSpecList*>(n) ) return visit((aliasSpecList*) n);
            else if (dynamic_cast<alias_lhs_macro_name*>(n) ) return visit((alias_lhs_macro_name*) n);
            else if (dynamic_cast<defineSpecList*>(n) ) return visit((defineSpecList*) n);
            else if (dynamic_cast<defineSpec*>(n) ) return visit((defineSpec*) n);
            else if (dynamic_cast<macro_segment*>(n) ) return visit((macro_segment*) n);
            else if (dynamic_cast<terminal_symbolList*>(n) ) return visit((terminal_symbolList*) n);
            else if (dynamic_cast<action_segmentList*>(n) ) return visit((action_segmentList*) n);
            else if (dynamic_cast<import_segment*>(n) ) return visit((import_segment*) n);
            else if (dynamic_cast<drop_commandList*>(n) ) return visit((drop_commandList*) n);
            else if (dynamic_cast<drop_ruleList*>(n) ) return visit((drop_ruleList*) n);
            else if (dynamic_cast<drop_rule*>(n) ) return visit((drop_rule*) n);
            else if (dynamic_cast<optMacroName*>(n) ) return visit((optMacroName*) n);
            else if (dynamic_cast<include_segment*>(n) ) return visit((include_segment*) n);
            else if (dynamic_cast<keywordSpecList*>(n) ) return visit((keywordSpecList*) n);
            else if (dynamic_cast<keywordSpec*>(n) ) return visit((keywordSpec*) n);
            else if (dynamic_cast<nameSpecList*>(n) ) return visit((nameSpecList*) n);
            else if (dynamic_cast<nameSpec*>(n) ) return visit((nameSpec*) n);
            else if (dynamic_cast<rules_segment*>(n) ) return visit((rules_segment*) n);
            else if (dynamic_cast<nonTermList*>(n) ) return visit((nonTermList*) n);
            else if (dynamic_cast<nonTerm*>(n) ) return visit((nonTerm*) n);
            else if (dynamic_cast<RuleName*>(n) ) return visit((RuleName*) n);
            else if (dynamic_cast<ruleList*>(n) ) return visit((ruleList*) n);
            else if (dynamic_cast<rule*>(n) ) return visit((rule*) n);
            else if (dynamic_cast<symWithAttrsList*>(n) ) return visit((symWithAttrsList*) n);
            else if (dynamic_cast<symAttrs*>(n) ) return visit((symAttrs*) n);
            else if (dynamic_cast<action_segment*>(n) ) return visit((action_segment*) n);
            else if (dynamic_cast<start_symbolList*>(n) ) return visit((start_symbolList*) n);
            else if (dynamic_cast<terminalList*>(n) ) return visit((terminalList*) n);
            else if (dynamic_cast<terminal*>(n) ) return visit((terminal*) n);
            else if (dynamic_cast<optTerminalAlias*>(n) ) return visit((optTerminalAlias*) n);
            else if (dynamic_cast<type_declarationsList*>(n) ) return visit((type_declarationsList*) n);
            else if (dynamic_cast<type_declarations*>(n) ) return visit((type_declarations*) n);
            else if (dynamic_cast<symbol_pairList*>(n) ) return visit((symbol_pairList*) n);
            else if (dynamic_cast<symbol_pair*>(n) ) return visit((symbol_pair*) n);
            else if (dynamic_cast<recover_symbol*>(n) ) return visit((recover_symbol*) n);
            else if (dynamic_cast<END_KEY_OPT*>(n) ) return visit((END_KEY_OPT*) n);
            else if (dynamic_cast<option_value0*>(n) ) return visit((option_value0*) n);
            else if (dynamic_cast<option_value1*>(n) ) return visit((option_value1*) n);
            else if (dynamic_cast<aliasSpec0*>(n) ) return visit((aliasSpec0*) n);
            else if (dynamic_cast<aliasSpec1*>(n) ) return visit((aliasSpec1*) n);
            else if (dynamic_cast<aliasSpec2*>(n) ) return visit((aliasSpec2*) n);
            else if (dynamic_cast<aliasSpec3*>(n) ) return visit((aliasSpec3*) n);
            else if (dynamic_cast<aliasSpec4*>(n) ) return visit((aliasSpec4*) n);
            else if (dynamic_cast<aliasSpec5*>(n) ) return visit((aliasSpec5*) n);
            else if (dynamic_cast<alias_rhs0*>(n) ) return visit((alias_rhs0*) n);
            else if (dynamic_cast<alias_rhs1*>(n) ) return visit((alias_rhs1*) n);
            else if (dynamic_cast<alias_rhs2*>(n) ) return visit((alias_rhs2*) n);
            else if (dynamic_cast<alias_rhs3*>(n) ) return visit((alias_rhs3*) n);
            else if (dynamic_cast<alias_rhs4*>(n) ) return visit((alias_rhs4*) n);
            else if (dynamic_cast<alias_rhs5*>(n) ) return visit((alias_rhs5*) n);
            else if (dynamic_cast<alias_rhs6*>(n) ) return visit((alias_rhs6*) n);
            else if (dynamic_cast<macro_name_symbol0*>(n) ) return visit((macro_name_symbol0*) n);
            else if (dynamic_cast<macro_name_symbol1*>(n) ) return visit((macro_name_symbol1*) n);
            else if (dynamic_cast<drop_command0*>(n) ) return visit((drop_command0*) n);
            else if (dynamic_cast<drop_command1*>(n) ) return visit((drop_command1*) n);
            else if (dynamic_cast<name0*>(n) ) return visit((name0*) n);
            else if (dynamic_cast<name1*>(n) ) return visit((name1*) n);
            else if (dynamic_cast<name2*>(n) ) return visit((name2*) n);
            else if (dynamic_cast<name3*>(n) ) return visit((name3*) n);
            else if (dynamic_cast<name4*>(n) ) return visit((name4*) n);
            else if (dynamic_cast<name5*>(n) ) return visit((name5*) n);
            else if (dynamic_cast<produces0*>(n) ) return visit((produces0*) n);
            else if (dynamic_cast<produces1*>(n) ) return visit((produces1*) n);
            else if (dynamic_cast<produces2*>(n) ) return visit((produces2*) n);
            else if (dynamic_cast<produces3*>(n) ) return visit((produces3*) n);
            else if (dynamic_cast<symWithAttrs0*>(n) ) return visit((symWithAttrs0*) n);
            else if (dynamic_cast<symWithAttrs1*>(n) ) return visit((symWithAttrs1*) n);
            else if (dynamic_cast<start_symbol0*>(n) ) return visit((start_symbol0*) n);
            else if (dynamic_cast<start_symbol1*>(n) ) return visit((start_symbol1*) n);
            else if (dynamic_cast<terminal_symbol0*>(n) ) return visit((terminal_symbol0*) n);
            else if (dynamic_cast<terminal_symbol1*>(n) ) return visit((terminal_symbol1*) n);
            throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
        }
      virtual  void endVisit(ASTNode *n)
        {
            if (dynamic_cast<ASTNodeToken*>(n) ) endVisit((ASTNodeToken*) n);
            else if (dynamic_cast<LPG*>(n) ) endVisit((LPG*) n);
            else if (dynamic_cast<LPG_itemList*>(n) ) endVisit((LPG_itemList*) n);
            else if (dynamic_cast<AliasSeg*>(n) ) endVisit((AliasSeg*) n);
            else if (dynamic_cast<AstSeg*>(n) ) endVisit((AstSeg*) n);
            else if (dynamic_cast<DefineSeg*>(n) ) endVisit((DefineSeg*) n);
            else if (dynamic_cast<EofSeg*>(n) ) endVisit((EofSeg*) n);
            else if (dynamic_cast<EolSeg*>(n) ) endVisit((EolSeg*) n);
            else if (dynamic_cast<ErrorSeg*>(n) ) endVisit((ErrorSeg*) n);
            else if (dynamic_cast<ExportSeg*>(n) ) endVisit((ExportSeg*) n);
            else if (dynamic_cast<GlobalsSeg*>(n) ) endVisit((GlobalsSeg*) n);
            else if (dynamic_cast<HeadersSeg*>(n) ) endVisit((HeadersSeg*) n);
            else if (dynamic_cast<IdentifierSeg*>(n) ) endVisit((IdentifierSeg*) n);
            else if (dynamic_cast<ImportSeg*>(n) ) endVisit((ImportSeg*) n);
            else if (dynamic_cast<IncludeSeg*>(n) ) endVisit((IncludeSeg*) n);
            else if (dynamic_cast<KeywordsSeg*>(n) ) endVisit((KeywordsSeg*) n);
            else if (dynamic_cast<NamesSeg*>(n) ) endVisit((NamesSeg*) n);
            else if (dynamic_cast<NoticeSeg*>(n) ) endVisit((NoticeSeg*) n);
            else if (dynamic_cast<RulesSeg*>(n) ) endVisit((RulesSeg*) n);
            else if (dynamic_cast<SoftKeywordsSeg*>(n) ) endVisit((SoftKeywordsSeg*) n);
            else if (dynamic_cast<StartSeg*>(n) ) endVisit((StartSeg*) n);
            else if (dynamic_cast<TerminalsSeg*>(n) ) endVisit((TerminalsSeg*) n);
            else if (dynamic_cast<TrailersSeg*>(n) ) endVisit((TrailersSeg*) n);
            else if (dynamic_cast<TypesSeg*>(n) ) endVisit((TypesSeg*) n);
            else if (dynamic_cast<RecoverSeg*>(n) ) endVisit((RecoverSeg*) n);
            else if (dynamic_cast<PredecessorSeg*>(n) ) endVisit((PredecessorSeg*) n);
            else if (dynamic_cast<option_specList*>(n) ) endVisit((option_specList*) n);
            else if (dynamic_cast<option_spec*>(n) ) endVisit((option_spec*) n);
            else if (dynamic_cast<optionList*>(n) ) endVisit((optionList*) n);
            else if (dynamic_cast<option*>(n) ) endVisit((option*) n);
            else if (dynamic_cast<SYMBOLList*>(n) ) endVisit((SYMBOLList*) n);
            else if (dynamic_cast<aliasSpecList*>(n) ) endVisit((aliasSpecList*) n);
            else if (dynamic_cast<alias_lhs_macro_name*>(n) ) endVisit((alias_lhs_macro_name*) n);
            else if (dynamic_cast<defineSpecList*>(n) ) endVisit((defineSpecList*) n);
            else if (dynamic_cast<defineSpec*>(n) ) endVisit((defineSpec*) n);
            else if (dynamic_cast<macro_segment*>(n) ) endVisit((macro_segment*) n);
            else if (dynamic_cast<terminal_symbolList*>(n) ) endVisit((terminal_symbolList*) n);
            else if (dynamic_cast<action_segmentList*>(n) ) endVisit((action_segmentList*) n);
            else if (dynamic_cast<import_segment*>(n) ) endVisit((import_segment*) n);
            else if (dynamic_cast<drop_commandList*>(n) ) endVisit((drop_commandList*) n);
            else if (dynamic_cast<drop_ruleList*>(n) ) endVisit((drop_ruleList*) n);
            else if (dynamic_cast<drop_rule*>(n) ) endVisit((drop_rule*) n);
            else if (dynamic_cast<optMacroName*>(n) ) endVisit((optMacroName*) n);
            else if (dynamic_cast<include_segment*>(n) ) endVisit((include_segment*) n);
            else if (dynamic_cast<keywordSpecList*>(n) ) endVisit((keywordSpecList*) n);
            else if (dynamic_cast<keywordSpec*>(n) ) endVisit((keywordSpec*) n);
            else if (dynamic_cast<nameSpecList*>(n) ) endVisit((nameSpecList*) n);
            else if (dynamic_cast<nameSpec*>(n) ) endVisit((nameSpec*) n);
            else if (dynamic_cast<rules_segment*>(n) ) endVisit((rules_segment*) n);
            else if (dynamic_cast<nonTermList*>(n) ) endVisit((nonTermList*) n);
            else if (dynamic_cast<nonTerm*>(n) ) endVisit((nonTerm*) n);
            else if (dynamic_cast<RuleName*>(n) ) endVisit((RuleName*) n);
            else if (dynamic_cast<ruleList*>(n) ) endVisit((ruleList*) n);
            else if (dynamic_cast<rule*>(n) ) endVisit((rule*) n);
            else if (dynamic_cast<symWithAttrsList*>(n) ) endVisit((symWithAttrsList*) n);
            else if (dynamic_cast<symAttrs*>(n) ) endVisit((symAttrs*) n);
            else if (dynamic_cast<action_segment*>(n) ) endVisit((action_segment*) n);
            else if (dynamic_cast<start_symbolList*>(n) ) endVisit((start_symbolList*) n);
            else if (dynamic_cast<terminalList*>(n) ) endVisit((terminalList*) n);
            else if (dynamic_cast<terminal*>(n) ) endVisit((terminal*) n);
            else if (dynamic_cast<optTerminalAlias*>(n) ) endVisit((optTerminalAlias*) n);
            else if (dynamic_cast<type_declarationsList*>(n) ) endVisit((type_declarationsList*) n);
            else if (dynamic_cast<type_declarations*>(n) ) endVisit((type_declarations*) n);
            else if (dynamic_cast<symbol_pairList*>(n) ) endVisit((symbol_pairList*) n);
            else if (dynamic_cast<symbol_pair*>(n) ) endVisit((symbol_pair*) n);
            else if (dynamic_cast<recover_symbol*>(n) ) endVisit((recover_symbol*) n);
            else if (dynamic_cast<END_KEY_OPT*>(n) ) endVisit((END_KEY_OPT*) n);
            else if (dynamic_cast<option_value0*>(n) ) endVisit((option_value0*) n);
            else if (dynamic_cast<option_value1*>(n) ) endVisit((option_value1*) n);
            else if (dynamic_cast<aliasSpec0*>(n) ) endVisit((aliasSpec0*) n);
            else if (dynamic_cast<aliasSpec1*>(n) ) endVisit((aliasSpec1*) n);
            else if (dynamic_cast<aliasSpec2*>(n) ) endVisit((aliasSpec2*) n);
            else if (dynamic_cast<aliasSpec3*>(n) ) endVisit((aliasSpec3*) n);
            else if (dynamic_cast<aliasSpec4*>(n) ) endVisit((aliasSpec4*) n);
            else if (dynamic_cast<aliasSpec5*>(n) ) endVisit((aliasSpec5*) n);
            else if (dynamic_cast<alias_rhs0*>(n) ) endVisit((alias_rhs0*) n);
            else if (dynamic_cast<alias_rhs1*>(n) ) endVisit((alias_rhs1*) n);
            else if (dynamic_cast<alias_rhs2*>(n) ) endVisit((alias_rhs2*) n);
            else if (dynamic_cast<alias_rhs3*>(n) ) endVisit((alias_rhs3*) n);
            else if (dynamic_cast<alias_rhs4*>(n) ) endVisit((alias_rhs4*) n);
            else if (dynamic_cast<alias_rhs5*>(n) ) endVisit((alias_rhs5*) n);
            else if (dynamic_cast<alias_rhs6*>(n) ) endVisit((alias_rhs6*) n);
            else if (dynamic_cast<macro_name_symbol0*>(n) ) endVisit((macro_name_symbol0*) n);
            else if (dynamic_cast<macro_name_symbol1*>(n) ) endVisit((macro_name_symbol1*) n);
            else if (dynamic_cast<drop_command0*>(n) ) endVisit((drop_command0*) n);
            else if (dynamic_cast<drop_command1*>(n) ) endVisit((drop_command1*) n);
            else if (dynamic_cast<name0*>(n) ) endVisit((name0*) n);
            else if (dynamic_cast<name1*>(n) ) endVisit((name1*) n);
            else if (dynamic_cast<name2*>(n) ) endVisit((name2*) n);
            else if (dynamic_cast<name3*>(n) ) endVisit((name3*) n);
            else if (dynamic_cast<name4*>(n) ) endVisit((name4*) n);
            else if (dynamic_cast<name5*>(n) ) endVisit((name5*) n);
            else if (dynamic_cast<produces0*>(n) ) endVisit((produces0*) n);
            else if (dynamic_cast<produces1*>(n) ) endVisit((produces1*) n);
            else if (dynamic_cast<produces2*>(n) ) endVisit((produces2*) n);
            else if (dynamic_cast<produces3*>(n) ) endVisit((produces3*) n);
            else if (dynamic_cast<symWithAttrs0*>(n) ) endVisit((symWithAttrs0*) n);
            else if (dynamic_cast<symWithAttrs1*>(n) ) endVisit((symWithAttrs1*) n);
            else if (dynamic_cast<start_symbol0*>(n) ) endVisit((start_symbol0*) n);
            else if (dynamic_cast<start_symbol1*>(n) ) endVisit((start_symbol1*) n);
            else if (dynamic_cast<terminal_symbol0*>(n) ) endVisit((terminal_symbol0*) n);
            else if (dynamic_cast<terminal_symbol1*>(n) ) endVisit((terminal_symbol1*) n);
            throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
        }
    };

    //#line 323 "dtParserTemplateF.gi

     void ruleAction(int ruleNumber)
    {
        switch (ruleNumber)
        {
            //#line 324 "dtParserTemplateF.gi"

            //
            // Rule 1:  LPG ::= options_segment LPG_INPUT
            //
            case 1: {
                //#line 61 "LPGParser.g"
                setResult(
                    //#line 61 LPGParser.g
                    ast_pool.Next()=new LPG(this, getLeftIToken(), getRightIToken(),
                            //#line 61 LPGParser.g
                            (IAst*)getRhsSym(1),
                            //#line 61 LPGParser.g
                            (IAst*)getRhsSym(2))
                //#line 61 LPGParser.g
                );
            break;
            }
            //
            // Rule 2:  LPG_INPUT ::= $Empty
            //
            case 2: {
                //#line 66 "LPGParser.g"
                setResult(
                    //#line 66 LPGParser.g
                    ast_pool.Next()=new LPG_itemList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 66 LPGParser.g
                );
            break;
            }
            //
            // Rule 3:  LPG_INPUT ::= LPG_INPUT LPG_item
            //
            case 3: {
                //#line 67 "LPGParser.g"
                ((LPG_itemList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 4:  LPG_item ::= ALIAS_KEY$ alias_segment END_KEY_OPT$
            //
            case 4: {
                //#line 70 "LPGParser.g"
                setResult(
                    //#line 70 LPGParser.g
                    ast_pool.Next()=new AliasSeg(getLeftIToken(), getRightIToken(),
                                 //#line 70 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 70 LPGParser.g
                );
            break;
            }
            //
            // Rule 5:  LPG_item ::= AST_KEY$ ast_segment END_KEY_OPT$
            //
            case 5: {
                //#line 71 "LPGParser.g"
                setResult(
                    //#line 71 LPGParser.g
                    ast_pool.Next()=new AstSeg(getLeftIToken(), getRightIToken(),
                               //#line 71 LPGParser.g
                               (IAst*)getRhsSym(2))
                //#line 71 LPGParser.g
                );
            break;
            }
            //
            // Rule 6:  LPG_item ::= DEFINE_KEY$ define_segment END_KEY_OPT$
            //
            case 6: {
                //#line 72 "LPGParser.g"
                setResult(
                    //#line 72 LPGParser.g
                    ast_pool.Next()=new DefineSeg(getLeftIToken(), getRightIToken(),
                                  //#line 72 LPGParser.g
                                  (IAst*)getRhsSym(2))
                //#line 72 LPGParser.g
                );
            break;
            }
            //
            // Rule 7:  LPG_item ::= EOF_KEY$ eof_segment END_KEY_OPT$
            //
            case 7: {
                //#line 73 "LPGParser.g"
                setResult(
                    //#line 73 LPGParser.g
                    ast_pool.Next()=new EofSeg(getLeftIToken(), getRightIToken(),
                               //#line 73 LPGParser.g
                               (IAst*)getRhsSym(2))
                //#line 73 LPGParser.g
                );
            break;
            }
            //
            // Rule 8:  LPG_item ::= EOL_KEY$ eol_segment END_KEY_OPT$
            //
            case 8: {
                //#line 74 "LPGParser.g"
                setResult(
                    //#line 74 LPGParser.g
                    ast_pool.Next()=new EolSeg(getLeftIToken(), getRightIToken(),
                               //#line 74 LPGParser.g
                               (IAst*)getRhsSym(2))
                //#line 74 LPGParser.g
                );
            break;
            }
            //
            // Rule 9:  LPG_item ::= ERROR_KEY$ error_segment END_KEY_OPT$
            //
            case 9: {
                //#line 75 "LPGParser.g"
                setResult(
                    //#line 75 LPGParser.g
                    ast_pool.Next()=new ErrorSeg(getLeftIToken(), getRightIToken(),
                                 //#line 75 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 75 LPGParser.g
                );
            break;
            }
            //
            // Rule 10:  LPG_item ::= EXPORT_KEY$ export_segment END_KEY_OPT$
            //
            case 10: {
                //#line 76 "LPGParser.g"
                setResult(
                    //#line 76 LPGParser.g
                    ast_pool.Next()=new ExportSeg(getLeftIToken(), getRightIToken(),
                                  //#line 76 LPGParser.g
                                  (IAst*)getRhsSym(2))
                //#line 76 LPGParser.g
                );
            break;
            }
            //
            // Rule 11:  LPG_item ::= GLOBALS_KEY$ globals_segment END_KEY_OPT$
            //
            case 11: {
                //#line 77 "LPGParser.g"
                setResult(
                    //#line 77 LPGParser.g
                    ast_pool.Next()=new GlobalsSeg(getLeftIToken(), getRightIToken(),
                                   //#line 77 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 77 LPGParser.g
                );
            break;
            }
            //
            // Rule 12:  LPG_item ::= HEADERS_KEY$ headers_segment END_KEY_OPT$
            //
            case 12: {
                //#line 78 "LPGParser.g"
                setResult(
                    //#line 78 LPGParser.g
                    ast_pool.Next()=new HeadersSeg(getLeftIToken(), getRightIToken(),
                                   //#line 78 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 78 LPGParser.g
                );
            break;
            }
            //
            // Rule 13:  LPG_item ::= IDENTIFIER_KEY$ identifier_segment END_KEY_OPT$
            //
            case 13: {
                //#line 79 "LPGParser.g"
                setResult(
                    //#line 79 LPGParser.g
                    ast_pool.Next()=new IdentifierSeg(getLeftIToken(), getRightIToken(),
                                      //#line 79 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 79 LPGParser.g
                );
            break;
            }
            //
            // Rule 14:  LPG_item ::= IMPORT_KEY$ import_segment END_KEY_OPT$
            //
            case 14: {
                //#line 80 "LPGParser.g"
                setResult(
                    //#line 80 LPGParser.g
                    ast_pool.Next()=new ImportSeg(getLeftIToken(), getRightIToken(),
                                  //#line 80 LPGParser.g
                                  (IAst*)getRhsSym(2))
                //#line 80 LPGParser.g
                );
            break;
            }
            //
            // Rule 15:  LPG_item ::= INCLUDE_KEY$ include_segment END_KEY_OPT$
            //
            case 15: {
                //#line 81 "LPGParser.g"
                setResult(
                    //#line 81 LPGParser.g
                    ast_pool.Next()=new IncludeSeg(getLeftIToken(), getRightIToken(),
                                   //#line 81 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 81 LPGParser.g
                );
            break;
            }
            //
            // Rule 16:  LPG_item ::= KEYWORDS_KEY$ keywords_segment END_KEY_OPT$
            //
            case 16: {
                //#line 82 "LPGParser.g"
                setResult(
                    //#line 82 LPGParser.g
                    ast_pool.Next()=new KeywordsSeg(getLeftIToken(), getRightIToken(),
                                    //#line 82 LPGParser.g
                                    (IAst*)getRhsSym(2))
                //#line 82 LPGParser.g
                );
            break;
            }
            //
            // Rule 17:  LPG_item ::= NAMES_KEY$ names_segment END_KEY_OPT$
            //
            case 17: {
                //#line 83 "LPGParser.g"
                setResult(
                    //#line 83 LPGParser.g
                    ast_pool.Next()=new NamesSeg(getLeftIToken(), getRightIToken(),
                                 //#line 83 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 83 LPGParser.g
                );
            break;
            }
            //
            // Rule 18:  LPG_item ::= NOTICE_KEY$ notice_segment END_KEY_OPT$
            //
            case 18: {
                //#line 84 "LPGParser.g"
                setResult(
                    //#line 84 LPGParser.g
                    ast_pool.Next()=new NoticeSeg(getLeftIToken(), getRightIToken(),
                                  //#line 84 LPGParser.g
                                  (IAst*)getRhsSym(2))
                //#line 84 LPGParser.g
                );
            break;
            }
            //
            // Rule 19:  LPG_item ::= RULES_KEY$ rules_segment END_KEY_OPT$
            //
            case 19: {
                //#line 85 "LPGParser.g"
                setResult(
                    //#line 85 LPGParser.g
                    ast_pool.Next()=new RulesSeg(getLeftIToken(), getRightIToken(),
                                 //#line 85 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 85 LPGParser.g
                );
            break;
            }
            //
            // Rule 20:  LPG_item ::= SOFT_KEYWORDS_KEY$ keywords_segment END_KEY_OPT$
            //
            case 20: {
                //#line 86 "LPGParser.g"
                setResult(
                    //#line 86 LPGParser.g
                    ast_pool.Next()=new SoftKeywordsSeg(getLeftIToken(), getRightIToken(),
                                        //#line 86 LPGParser.g
                                        (IAst*)getRhsSym(2))
                //#line 86 LPGParser.g
                );
            break;
            }
            //
            // Rule 21:  LPG_item ::= START_KEY$ start_segment END_KEY_OPT$
            //
            case 21: {
                //#line 87 "LPGParser.g"
                setResult(
                    //#line 87 LPGParser.g
                    ast_pool.Next()=new StartSeg(getLeftIToken(), getRightIToken(),
                                 //#line 87 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 87 LPGParser.g
                );
            break;
            }
            //
            // Rule 22:  LPG_item ::= TERMINALS_KEY$ terminals_segment END_KEY_OPT$
            //
            case 22: {
                //#line 88 "LPGParser.g"
                setResult(
                    //#line 88 LPGParser.g
                    ast_pool.Next()=new TerminalsSeg(getLeftIToken(), getRightIToken(),
                                     //#line 88 LPGParser.g
                                     (IAst*)getRhsSym(2))
                //#line 88 LPGParser.g
                );
            break;
            }
            //
            // Rule 23:  LPG_item ::= TRAILERS_KEY$ trailers_segment END_KEY_OPT$
            //
            case 23: {
                //#line 89 "LPGParser.g"
                setResult(
                    //#line 89 LPGParser.g
                    ast_pool.Next()=new TrailersSeg(getLeftIToken(), getRightIToken(),
                                    //#line 89 LPGParser.g
                                    (IAst*)getRhsSym(2))
                //#line 89 LPGParser.g
                );
            break;
            }
            //
            // Rule 24:  LPG_item ::= TYPES_KEY$ types_segment END_KEY_OPT$
            //
            case 24: {
                //#line 90 "LPGParser.g"
                setResult(
                    //#line 90 LPGParser.g
                    ast_pool.Next()=new TypesSeg(getLeftIToken(), getRightIToken(),
                                 //#line 90 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 90 LPGParser.g
                );
            break;
            }
            //
            // Rule 25:  LPG_item ::= RECOVER_KEY$ recover_segment END_KEY_OPT$
            //
            case 25: {
                //#line 91 "LPGParser.g"
                setResult(
                    //#line 91 LPGParser.g
                    ast_pool.Next()=new RecoverSeg(getLeftIToken(), getRightIToken(),
                                   //#line 91 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 91 LPGParser.g
                );
            break;
            }
            //
            // Rule 26:  LPG_item ::= DISJOINTPREDECESSORSETS_KEY$ predecessor_segment END_KEY_OPT$
            //
            case 26: {
                //#line 92 "LPGParser.g"
                setResult(
                    //#line 92 LPGParser.g
                    ast_pool.Next()=new PredecessorSeg(getLeftIToken(), getRightIToken(),
                                       //#line 92 LPGParser.g
                                       (IAst*)getRhsSym(2))
                //#line 92 LPGParser.g
                );
            break;
            }
            //
            // Rule 27:  options_segment ::= $Empty
            //
            case 27: {
                //#line 95 "LPGParser.g"
                setResult(
                    //#line 95 LPGParser.g
                    ast_pool.Next()=new option_specList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 95 LPGParser.g
                );
            break;
            }
            //
            // Rule 28:  options_segment ::= options_segment option_spec
            //
            case 28: {
                //#line 95 "LPGParser.g"
                ((option_specList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 29:  option_spec ::= OPTIONS_KEY$ option_list
            //
            case 29: {
                //#line 96 "LPGParser.g"
                setResult(
                    //#line 96 LPGParser.g
                    ast_pool.Next()=new option_spec(getLeftIToken(), getRightIToken(),
                                    //#line 96 LPGParser.g
                                    (IAst*)getRhsSym(2))
                //#line 96 LPGParser.g
                );
            break;
            }
            //
            // Rule 30:  option_list ::= option
            //
            case 30: {
                //#line 97 "LPGParser.g"
                setResult(
                    //#line 97 LPGParser.g
                    ast_pool.Next()=new optionList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 97 LPGParser.g
                );
            break;
            }
            //
            // Rule 31:  option_list ::= option_list ,$ option
            //
            case 31: {
                //#line 97 "LPGParser.g"
                ((optionList*)getRhsSym(1))->addElement((IAst*)getRhsSym(3));
            break;
            }
            //
            // Rule 32:  option ::= SYMBOL option_value
            //
            case 32: {
                //#line 98 "LPGParser.g"
                setResult(
                    //#line 98 LPGParser.g
                    ast_pool.Next()=new option(getLeftIToken(), getRightIToken(),
                               //#line 98 LPGParser.g
                               ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                               //#line 98 LPGParser.g
                               (IAst*)getRhsSym(2))
                //#line 98 LPGParser.g
                );
            break;
            }
            //
            // Rule 33:  option_value ::= $Empty
            //
            case 33: {
                //#line 99 "LPGParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 34:  option_value ::= =$ SYMBOL
            //
            case 34: {
                //#line 99 "LPGParser.g"
                setResult(
                    //#line 99 LPGParser.g
                    ast_pool.Next()=new option_value0(getLeftIToken(), getRightIToken(),
                                      //#line 99 LPGParser.g
                                      ast_pool.Next()=new ASTNodeToken(getRhsIToken(2)))
                //#line 99 LPGParser.g
                );
            break;
            }
            //
            // Rule 35:  option_value ::= =$ ($ symbol_list )$
            //
            case 35: {
                //#line 99 "LPGParser.g"
                setResult(
                    //#line 99 LPGParser.g
                    ast_pool.Next()=new option_value1(getLeftIToken(), getRightIToken(),
                                      //#line 99 LPGParser.g
                                      (IAst*)getRhsSym(3))
                //#line 99 LPGParser.g
                );
            break;
            }
            //
            // Rule 36:  symbol_list ::= SYMBOL
            //
            case 36: {
                //#line 101 "LPGParser.g"
                setResult(
                    //#line 101 LPGParser.g
                    ast_pool.Next()=new SYMBOLList(ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)), true /* left recursive */)
                //#line 101 LPGParser.g
                );
            break;
            }
            //
            // Rule 37:  symbol_list ::= symbol_list ,$ SYMBOL
            //
            case 37: {
                //#line 102 "LPGParser.g"
                ((SYMBOLList*)getRhsSym(1))->addElement(ast_pool.Next()=new ASTNodeToken(getRhsIToken(3)));
            break;
            }
            //
            // Rule 38:  alias_segment ::= aliasSpec
            //
            case 38: {
                //#line 105 "LPGParser.g"
                setResult(
                    //#line 105 LPGParser.g
                    ast_pool.Next()=new aliasSpecList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 105 LPGParser.g
                );
            break;
            }
            //
            // Rule 39:  alias_segment ::= alias_segment aliasSpec
            //
            case 39: {
                //#line 105 "LPGParser.g"
                ((aliasSpecList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 40:  aliasSpec ::= ERROR_KEY produces alias_rhs
            //
            case 40: {
                //#line 107 "LPGParser.g"
                setResult(
                    //#line 107 LPGParser.g
                    ast_pool.Next()=new aliasSpec0(getLeftIToken(), getRightIToken(),
                                   //#line 107 LPGParser.g
                                   ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                   //#line 107 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 107 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 107 LPGParser.g
                );
            break;
            }
            //
            // Rule 41:  aliasSpec ::= EOL_KEY produces alias_rhs
            //
            case 41: {
                //#line 108 "LPGParser.g"
                setResult(
                    //#line 108 LPGParser.g
                    ast_pool.Next()=new aliasSpec1(getLeftIToken(), getRightIToken(),
                                   //#line 108 LPGParser.g
                                   ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                   //#line 108 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 108 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 108 LPGParser.g
                );
            break;
            }
            //
            // Rule 42:  aliasSpec ::= EOF_KEY produces alias_rhs
            //
            case 42: {
                //#line 109 "LPGParser.g"
                setResult(
                    //#line 109 LPGParser.g
                    ast_pool.Next()=new aliasSpec2(getLeftIToken(), getRightIToken(),
                                   //#line 109 LPGParser.g
                                   ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                   //#line 109 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 109 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 109 LPGParser.g
                );
            break;
            }
            //
            // Rule 43:  aliasSpec ::= IDENTIFIER_KEY produces alias_rhs
            //
            case 43: {
                //#line 110 "LPGParser.g"
                setResult(
                    //#line 110 LPGParser.g
                    ast_pool.Next()=new aliasSpec3(getLeftIToken(), getRightIToken(),
                                   //#line 110 LPGParser.g
                                   ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                   //#line 110 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 110 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 110 LPGParser.g
                );
            break;
            }
            //
            // Rule 44:  aliasSpec ::= SYMBOL produces alias_rhs
            //
            case 44: {
                //#line 111 "LPGParser.g"
                setResult(
                    //#line 111 LPGParser.g
                    ast_pool.Next()=new aliasSpec4(getLeftIToken(), getRightIToken(),
                                   //#line 111 LPGParser.g
                                   ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                   //#line 111 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 111 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 111 LPGParser.g
                );
            break;
            }
            //
            // Rule 45:  aliasSpec ::= alias_lhs_macro_name produces alias_rhs
            //
            case 45: {
                //#line 112 "LPGParser.g"
                setResult(
                    //#line 112 LPGParser.g
                    ast_pool.Next()=new aliasSpec5(getLeftIToken(), getRightIToken(),
                                   //#line 112 LPGParser.g
                                   (IAst*)getRhsSym(1),
                                   //#line 112 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 112 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 112 LPGParser.g
                );
            break;
            }
            //
            // Rule 46:  alias_lhs_macro_name ::= MACRO_NAME
            //
            case 46: {
                //#line 114 "LPGParser.g"
                setResult(
                    //#line 114 LPGParser.g
                    ast_pool.Next()=new alias_lhs_macro_name(getRhsIToken(1))
                //#line 114 LPGParser.g
                );
            break;
            }
            //
            // Rule 47:  alias_rhs ::= SYMBOL
            //
            case 47: {
                //#line 116 "LPGParser.g"
                setResult(
                    //#line 116 LPGParser.g
                    ast_pool.Next()=new alias_rhs0(getRhsIToken(1))
                //#line 116 LPGParser.g
                );
            break;
            }
            //
            // Rule 48:  alias_rhs ::= MACRO_NAME
            //
            case 48: {
                //#line 117 "LPGParser.g"
                setResult(
                    //#line 117 LPGParser.g
                    ast_pool.Next()=new alias_rhs1(getRhsIToken(1))
                //#line 117 LPGParser.g
                );
            break;
            }
            //
            // Rule 49:  alias_rhs ::= ERROR_KEY
            //
            case 49: {
                //#line 118 "LPGParser.g"
                setResult(
                    //#line 118 LPGParser.g
                    ast_pool.Next()=new alias_rhs2(getRhsIToken(1))
                //#line 118 LPGParser.g
                );
            break;
            }
            //
            // Rule 50:  alias_rhs ::= EOL_KEY
            //
            case 50: {
                //#line 119 "LPGParser.g"
                setResult(
                    //#line 119 LPGParser.g
                    ast_pool.Next()=new alias_rhs3(getRhsIToken(1))
                //#line 119 LPGParser.g
                );
            break;
            }
            //
            // Rule 51:  alias_rhs ::= EOF_KEY
            //
            case 51: {
                //#line 120 "LPGParser.g"
                setResult(
                    //#line 120 LPGParser.g
                    ast_pool.Next()=new alias_rhs4(getRhsIToken(1))
                //#line 120 LPGParser.g
                );
            break;
            }
            //
            // Rule 52:  alias_rhs ::= EMPTY_KEY
            //
            case 52: {
                //#line 121 "LPGParser.g"
                setResult(
                    //#line 121 LPGParser.g
                    ast_pool.Next()=new alias_rhs5(getRhsIToken(1))
                //#line 121 LPGParser.g
                );
            break;
            }
            //
            // Rule 53:  alias_rhs ::= IDENTIFIER_KEY
            //
            case 53: {
                //#line 122 "LPGParser.g"
                setResult(
                    //#line 122 LPGParser.g
                    ast_pool.Next()=new alias_rhs6(getRhsIToken(1))
                //#line 122 LPGParser.g
                );
            break;
            }
            //
            // Rule 54:  ast_segment ::= action_segment_list
            //
            case 54:
                break;
            //
            // Rule 55:  define_segment ::= defineSpec
            //
            case 55: {
                //#line 128 "LPGParser.g"
                setResult(
                    //#line 128 LPGParser.g
                    ast_pool.Next()=new defineSpecList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 128 LPGParser.g
                );
            break;
            }
            //
            // Rule 56:  define_segment ::= define_segment defineSpec
            //
            case 56: {
                //#line 128 "LPGParser.g"
                ((defineSpecList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 57:  defineSpec ::= macro_name_symbol macro_segment
            //
            case 57: {
                //#line 129 "LPGParser.g"
                setResult(
                    //#line 129 LPGParser.g
                    ast_pool.Next()=new defineSpec(this, getLeftIToken(), getRightIToken(),
                                   //#line 129 LPGParser.g
                                   (IAst*)getRhsSym(1),
                                   //#line 129 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 129 LPGParser.g
                );
            break;
            }
            //
            // Rule 58:  macro_name_symbol ::= MACRO_NAME
            //
            case 58: {
                //#line 134 "LPGParser.g"
                setResult(
                    //#line 134 LPGParser.g
                    ast_pool.Next()=new macro_name_symbol0(getRhsIToken(1))
                //#line 134 LPGParser.g
                );
            break;
            }
            //
            // Rule 59:  macro_name_symbol ::= SYMBOL
            //
            case 59: {
                //#line 135 "LPGParser.g"
                setResult(
                    //#line 135 LPGParser.g
                    ast_pool.Next()=new macro_name_symbol1(getRhsIToken(1))
                //#line 135 LPGParser.g
                );
            break;
            }
            //
            // Rule 60:  macro_segment ::= BLOCK
            //
            case 60: {
                //#line 136 "LPGParser.g"
                setResult(
                    //#line 136 LPGParser.g
                    ast_pool.Next()=new macro_segment(getRhsIToken(1))
                //#line 136 LPGParser.g
                );
            break;
            }
            //
            // Rule 61:  eol_segment ::= terminal_symbol
            //
            case 61:
                break;
            //
            // Rule 62:  eof_segment ::= terminal_symbol
            //
            case 62:
                break;
            //
            // Rule 63:  error_segment ::= terminal_symbol
            //
            case 63:
                break;
            //
            // Rule 64:  export_segment ::= terminal_symbol
            //
            case 64: {
                //#line 146 "LPGParser.g"
                setResult(
                    //#line 146 LPGParser.g
                    ast_pool.Next()=new terminal_symbolList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 146 LPGParser.g
                );
            break;
            }
            //
            // Rule 65:  export_segment ::= export_segment terminal_symbol
            //
            case 65: {
                //#line 146 "LPGParser.g"
                ((terminal_symbolList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 66:  globals_segment ::= action_segment
            //
            case 66: {
                //#line 149 "LPGParser.g"
                setResult(
                    //#line 149 LPGParser.g
                    ast_pool.Next()=new action_segmentList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 149 LPGParser.g
                );
            break;
            }
            //
            // Rule 67:  globals_segment ::= globals_segment action_segment
            //
            case 67: {
                //#line 149 "LPGParser.g"
                ((action_segmentList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 68:  headers_segment ::= action_segment_list
            //
            case 68:
                break;
            //
            // Rule 69:  identifier_segment ::= terminal_symbol
            //
            case 69:
                break;
            //
            // Rule 70:  import_segment ::= SYMBOL drop_command_list
            //
            case 70: {
                //#line 158 "LPGParser.g"
                setResult(
                    //#line 158 LPGParser.g
                    ast_pool.Next()=new import_segment(getLeftIToken(), getRightIToken(),
                                       //#line 158 LPGParser.g
                                       ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                       //#line 158 LPGParser.g
                                       (IAst*)getRhsSym(2))
                //#line 158 LPGParser.g
                );
            break;
            }
            //
            // Rule 71:  drop_command_list ::= $Empty
            //
            case 71: {
                //#line 160 "LPGParser.g"
                setResult(
                    //#line 160 LPGParser.g
                    ast_pool.Next()=new drop_commandList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 160 LPGParser.g
                );
            break;
            }
            //
            // Rule 72:  drop_command_list ::= drop_command_list drop_command
            //
            case 72: {
                //#line 160 "LPGParser.g"
                ((drop_commandList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 73:  drop_command ::= DROPSYMBOLS_KEY drop_symbols
            //
            case 73: {
                //#line 162 "LPGParser.g"
                setResult(
                    //#line 162 LPGParser.g
                    ast_pool.Next()=new drop_command0(getLeftIToken(), getRightIToken(),
                                      //#line 162 LPGParser.g
                                      ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                      //#line 162 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 162 LPGParser.g
                );
            break;
            }
            //
            // Rule 74:  drop_command ::= DROPRULES_KEY drop_rules
            //
            case 74: {
                //#line 163 "LPGParser.g"
                setResult(
                    //#line 163 LPGParser.g
                    ast_pool.Next()=new drop_command1(getLeftIToken(), getRightIToken(),
                                      //#line 163 LPGParser.g
                                      ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                      //#line 163 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 163 LPGParser.g
                );
            break;
            }
            //
            // Rule 75:  drop_symbols ::= SYMBOL
            //
            case 75: {
                //#line 165 "LPGParser.g"
                setResult(
                    //#line 165 LPGParser.g
                    ast_pool.Next()=new SYMBOLList(ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)), true /* left recursive */)
                //#line 165 LPGParser.g
                );
            break;
            }
            //
            // Rule 76:  drop_symbols ::= drop_symbols SYMBOL
            //
            case 76: {
                //#line 166 "LPGParser.g"
                ((SYMBOLList*)getRhsSym(1))->addElement(ast_pool.Next()=new ASTNodeToken(getRhsIToken(2)));
            break;
            }
            //
            // Rule 77:  drop_rules ::= drop_rule
            //
            case 77: {
                //#line 167 "LPGParser.g"
                setResult(
                    //#line 167 LPGParser.g
                    ast_pool.Next()=new drop_ruleList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 167 LPGParser.g
                );
            break;
            }
            //
            // Rule 78:  drop_rules ::= drop_rules drop_rule
            //
            case 78: {
                //#line 168 "LPGParser.g"
                ((drop_ruleList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 79:  drop_rule ::= SYMBOL optMacroName produces ruleList
            //
            case 79: {
                //#line 170 "LPGParser.g"
                setResult(
                    //#line 170 LPGParser.g
                    ast_pool.Next()=new drop_rule(getLeftIToken(), getRightIToken(),
                                  //#line 170 LPGParser.g
                                  ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                  //#line 170 LPGParser.g
                                  (IAst*)getRhsSym(2),
                                  //#line 170 LPGParser.g
                                  (IAst*)getRhsSym(3),
                                  //#line 170 LPGParser.g
                                  (IAst*)getRhsSym(4))
                //#line 170 LPGParser.g
                );
            break;
            }
            //
            // Rule 80:  optMacroName ::= $Empty
            //
            case 80: {
                //#line 172 "LPGParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 81:  optMacroName ::= MACRO_NAME
            //
            case 81: {
                //#line 172 "LPGParser.g"
                setResult(
                    //#line 172 LPGParser.g
                    ast_pool.Next()=new optMacroName(getRhsIToken(1))
                //#line 172 LPGParser.g
                );
            break;
            }
            //
            // Rule 82:  include_segment ::= SYMBOL
            //
            case 82: {
                //#line 175 "LPGParser.g"
                setResult(
                    //#line 175 LPGParser.g
                    ast_pool.Next()=new include_segment(getRhsIToken(1))
                //#line 175 LPGParser.g
                );
            break;
            }
            //
            // Rule 83:  keywords_segment ::= keywordSpec
            //
            case 83: {
                //#line 178 "LPGParser.g"
                setResult(
                    //#line 178 LPGParser.g
                    ast_pool.Next()=new keywordSpecList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 178 LPGParser.g
                );
            break;
            }
            //
            // Rule 84:  keywords_segment ::= keywords_segment keywordSpec
            //
            case 84: {
                //#line 178 "LPGParser.g"
                ((keywordSpecList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 85:  keywordSpec ::= terminal_symbol
            //
            case 85:
                break;
            //
            // Rule 86:  keywordSpec ::= terminal_symbol produces name
            //
            case 86: {
                //#line 180 "LPGParser.g"
                setResult(
                    //#line 180 LPGParser.g
                    ast_pool.Next()=new keywordSpec(getLeftIToken(), getRightIToken(),
                                    //#line 180 LPGParser.g
                                    (IAst*)getRhsSym(1),
                                    //#line 180 LPGParser.g
                                    (IAst*)getRhsSym(2),
                                    //#line 180 LPGParser.g
                                    (IAst*)getRhsSym(3))
                //#line 180 LPGParser.g
                );
            break;
            }
            //
            // Rule 87:  names_segment ::= nameSpec
            //
            case 87: {
                //#line 183 "LPGParser.g"
                setResult(
                    //#line 183 LPGParser.g
                    ast_pool.Next()=new nameSpecList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 183 LPGParser.g
                );
            break;
            }
            //
            // Rule 88:  names_segment ::= names_segment nameSpec
            //
            case 88: {
                //#line 183 "LPGParser.g"
                ((nameSpecList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 89:  nameSpec ::= name produces name
            //
            case 89: {
                //#line 184 "LPGParser.g"
                setResult(
                    //#line 184 LPGParser.g
                    ast_pool.Next()=new nameSpec(getLeftIToken(), getRightIToken(),
                                 //#line 184 LPGParser.g
                                 (IAst*)getRhsSym(1),
                                 //#line 184 LPGParser.g
                                 (IAst*)getRhsSym(2),
                                 //#line 184 LPGParser.g
                                 (IAst*)getRhsSym(3))
                //#line 184 LPGParser.g
                );
            break;
            }
            //
            // Rule 90:  name ::= SYMBOL
            //
            case 90: {
                //#line 186 "LPGParser.g"
                setResult(
                    //#line 186 LPGParser.g
                    ast_pool.Next()=new name0(getRhsIToken(1))
                //#line 186 LPGParser.g
                );
            break;
            }
            //
            // Rule 91:  name ::= MACRO_NAME
            //
            case 91: {
                //#line 187 "LPGParser.g"
                setResult(
                    //#line 187 LPGParser.g
                    ast_pool.Next()=new name1(getRhsIToken(1))
                //#line 187 LPGParser.g
                );
            break;
            }
            //
            // Rule 92:  name ::= EMPTY_KEY
            //
            case 92: {
                //#line 188 "LPGParser.g"
                setResult(
                    //#line 188 LPGParser.g
                    ast_pool.Next()=new name2(getRhsIToken(1))
                //#line 188 LPGParser.g
                );
            break;
            }
            //
            // Rule 93:  name ::= ERROR_KEY
            //
            case 93: {
                //#line 189 "LPGParser.g"
                setResult(
                    //#line 189 LPGParser.g
                    ast_pool.Next()=new name3(getRhsIToken(1))
                //#line 189 LPGParser.g
                );
            break;
            }
            //
            // Rule 94:  name ::= EOL_KEY
            //
            case 94: {
                //#line 190 "LPGParser.g"
                setResult(
                    //#line 190 LPGParser.g
                    ast_pool.Next()=new name4(getRhsIToken(1))
                //#line 190 LPGParser.g
                );
            break;
            }
            //
            // Rule 95:  name ::= IDENTIFIER_KEY
            //
            case 95: {
                //#line 191 "LPGParser.g"
                setResult(
                    //#line 191 LPGParser.g
                    ast_pool.Next()=new name5(getRhsIToken(1))
                //#line 191 LPGParser.g
                );
            break;
            }
            //
            // Rule 96:  notice_segment ::= action_segment
            //
            case 96: {
                //#line 194 "LPGParser.g"
                setResult(
                    //#line 194 LPGParser.g
                    ast_pool.Next()=new action_segmentList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 194 LPGParser.g
                );
            break;
            }
            //
            // Rule 97:  notice_segment ::= notice_segment action_segment
            //
            case 97: {
                //#line 194 "LPGParser.g"
                ((action_segmentList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 98:  rules_segment ::= action_segment_list nonTermList
            //
            case 98: {
                //#line 197 "LPGParser.g"
                setResult(
                    //#line 197 LPGParser.g
                    ast_pool.Next()=new rules_segment(getLeftIToken(), getRightIToken(),
                                      //#line 197 LPGParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 197 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 197 LPGParser.g
                );
            break;
            }
            //
            // Rule 99:  nonTermList ::= $Empty
            //
            case 99: {
                //#line 199 "LPGParser.g"
                setResult(
                    //#line 199 LPGParser.g
                    ast_pool.Next()=new nonTermList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 199 LPGParser.g
                );
            break;
            }
            //
            // Rule 100:  nonTermList ::= nonTermList nonTerm
            //
            case 100: {
                //#line 199 "LPGParser.g"
                ((nonTermList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 101:  nonTerm ::= ruleNameWithAttributes produces ruleList
            //
            case 101: {
                //#line 201 "LPGParser.g"
                setResult(
                    //#line 201 LPGParser.g
                    ast_pool.Next()=new nonTerm(this, getLeftIToken(), getRightIToken(),
                                //#line 201 LPGParser.g
                                (IAst*)getRhsSym(1),
                                //#line 201 LPGParser.g
                                (IAst*)getRhsSym(2),
                                //#line 201 LPGParser.g
                                (IAst*)getRhsSym(3))
                //#line 201 LPGParser.g
                );
            break;
            }
            //
            // Rule 102:  ruleNameWithAttributes ::= SYMBOL
            //
            case 102: {
                //#line 207 "LPGParser.g"
                setResult(
                    //#line 207 LPGParser.g
                    ast_pool.Next()=new RuleName(getLeftIToken(), getRightIToken(),
                                 //#line 207 LPGParser.g
                                 ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                 //#line 207 LPGParser.g
                                 nullptr,
                                 //#line 207 LPGParser.g
                                 nullptr)
                //#line 207 LPGParser.g
                );
            break;
            }
            //
            // Rule 103:  ruleNameWithAttributes ::= SYMBOL MACRO_NAME$className
            //
            case 103: {
                //#line 208 "LPGParser.g"
                setResult(
                    //#line 208 LPGParser.g
                    ast_pool.Next()=new RuleName(getLeftIToken(), getRightIToken(),
                                 //#line 208 LPGParser.g
                                 ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                 //#line 208 LPGParser.g
                                 ast_pool.Next()=new ASTNodeToken(getRhsIToken(2)),
                                 //#line 208 LPGParser.g
                                 nullptr)
                //#line 208 LPGParser.g
                );
            break;
            }
            //
            // Rule 104:  ruleNameWithAttributes ::= SYMBOL MACRO_NAME$className MACRO_NAME$arrayElement
            //
            case 104: {
                //#line 209 "LPGParser.g"
                setResult(
                    //#line 209 LPGParser.g
                    ast_pool.Next()=new RuleName(getLeftIToken(), getRightIToken(),
                                 //#line 209 LPGParser.g
                                 ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                 //#line 209 LPGParser.g
                                 ast_pool.Next()=new ASTNodeToken(getRhsIToken(2)),
                                 //#line 209 LPGParser.g
                                 ast_pool.Next()=new ASTNodeToken(getRhsIToken(3)))
                //#line 209 LPGParser.g
                );
            break;
            }
            //
            // Rule 105:  ruleList ::= rule
            //
            case 105: {
                //#line 223 "LPGParser.g"
                setResult(
                    //#line 223 LPGParser.g
                    ast_pool.Next()=new ruleList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 223 LPGParser.g
                );
            break;
            }
            //
            // Rule 106:  ruleList ::= ruleList |$ rule
            //
            case 106: {
                //#line 223 "LPGParser.g"
                ((ruleList*)getRhsSym(1))->addElement((IAst*)getRhsSym(3));
            break;
            }
            //
            // Rule 107:  produces ::= ::=
            //
            case 107: {
                //#line 225 "LPGParser.g"
                setResult(
                    //#line 225 LPGParser.g
                    ast_pool.Next()=new produces0(getRhsIToken(1))
                //#line 225 LPGParser.g
                );
            break;
            }
            //
            // Rule 108:  produces ::= ::=?
            //
            case 108: {
                //#line 226 "LPGParser.g"
                setResult(
                    //#line 226 LPGParser.g
                    ast_pool.Next()=new produces1(getRhsIToken(1))
                //#line 226 LPGParser.g
                );
            break;
            }
            //
            // Rule 109:  produces ::= ->
            //
            case 109: {
                //#line 227 "LPGParser.g"
                setResult(
                    //#line 227 LPGParser.g
                    ast_pool.Next()=new produces2(getRhsIToken(1))
                //#line 227 LPGParser.g
                );
            break;
            }
            //
            // Rule 110:  produces ::= ->?
            //
            case 110: {
                //#line 228 "LPGParser.g"
                setResult(
                    //#line 228 LPGParser.g
                    ast_pool.Next()=new produces3(getRhsIToken(1))
                //#line 228 LPGParser.g
                );
            break;
            }
            //
            // Rule 111:  rule ::= symWithAttrsList opt_action_segment
            //
            case 111: {
                //#line 230 "LPGParser.g"
                setResult(
                    //#line 230 LPGParser.g
                    ast_pool.Next()=new rule(getLeftIToken(), getRightIToken(),
                             //#line 230 LPGParser.g
                             (IAst*)getRhsSym(1),
                             //#line 230 LPGParser.g
                             (IAst*)getRhsSym(2))
                //#line 230 LPGParser.g
                );
            break;
            }
            //
            // Rule 112:  symWithAttrsList ::= $Empty
            //
            case 112: {
                //#line 232 "LPGParser.g"
                setResult(
                    //#line 232 LPGParser.g
                    ast_pool.Next()=new symWithAttrsList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 232 LPGParser.g
                );
            break;
            }
            //
            // Rule 113:  symWithAttrsList ::= symWithAttrsList symWithAttrs
            //
            case 113: {
                //#line 232 "LPGParser.g"
                ((symWithAttrsList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 114:  symWithAttrs ::= EMPTY_KEY
            //
            case 114: {
                //#line 234 "LPGParser.g"
                setResult(
                    //#line 234 LPGParser.g
                    ast_pool.Next()=new symWithAttrs0(getRhsIToken(1))
                //#line 234 LPGParser.g
                );
            break;
            }
            //
            // Rule 115:  symWithAttrs ::= SYMBOL optAttrList
            //
            case 115: {
                //#line 235 "LPGParser.g"
                setResult(
                    //#line 235 LPGParser.g
                    ast_pool.Next()=new symWithAttrs1(getLeftIToken(), getRightIToken(),
                                      //#line 235 LPGParser.g
                                      ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                      //#line 235 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 235 LPGParser.g
                );
            break;
            }
            //
            // Rule 116:  optAttrList ::= $Empty
            //
            case 116: {
                //#line 238 "LPGParser.g"
                setResult(
                    //#line 238 LPGParser.g
                    ast_pool.Next()=new symAttrs(getLeftIToken(), getRightIToken(),
                                 //#line 238 LPGParser.g
                                 nullptr)
                //#line 238 LPGParser.g
                );
            break;
            }
            //
            // Rule 117:  optAttrList ::= MACRO_NAME
            //
            case 117: {
                //#line 239 "LPGParser.g"
                setResult(
                    //#line 239 LPGParser.g
                    ast_pool.Next()=new symAttrs(getLeftIToken(), getRightIToken(),
                                 //#line 239 LPGParser.g
                                 ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)))
                //#line 239 LPGParser.g
                );
            break;
            }
            //
            // Rule 118:  opt_action_segment ::= $Empty
            //
            case 118: {
                //#line 241 "LPGParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 119:  opt_action_segment ::= action_segment
            //
            case 119:
                break;
            //
            // Rule 120:  action_segment ::= BLOCK
            //
            case 120: {
                //#line 243 "LPGParser.g"
                setResult(
                    //#line 243 LPGParser.g
                    ast_pool.Next()=new action_segment(this, getRhsIToken(1))
                //#line 243 LPGParser.g
                );
            break;
            }
            //
            // Rule 121:  start_segment ::= start_symbol
            //
            case 121: {
                //#line 249 "LPGParser.g"
                setResult(
                    //#line 249 LPGParser.g
                    ast_pool.Next()=new start_symbolList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 249 LPGParser.g
                );
            break;
            }
            //
            // Rule 122:  start_segment ::= start_segment start_symbol
            //
            case 122: {
                //#line 249 "LPGParser.g"
                ((start_symbolList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 123:  start_symbol ::= SYMBOL
            //
            case 123: {
                //#line 250 "LPGParser.g"
                setResult(
                    //#line 250 LPGParser.g
                    ast_pool.Next()=new start_symbol0(getRhsIToken(1))
                //#line 250 LPGParser.g
                );
            break;
            }
            //
            // Rule 124:  start_symbol ::= MACRO_NAME
            //
            case 124: {
                //#line 251 "LPGParser.g"
                setResult(
                    //#line 251 LPGParser.g
                    ast_pool.Next()=new start_symbol1(getRhsIToken(1))
                //#line 251 LPGParser.g
                );
            break;
            }
            //
            // Rule 125:  terminals_segment ::= terminal
            //
            case 125: {
                //#line 254 "LPGParser.g"
                setResult(
                    //#line 254 LPGParser.g
                    ast_pool.Next()=new terminalList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 254 LPGParser.g
                );
            break;
            }
            //
            // Rule 126:  terminals_segment ::= terminals_segment terminal
            //
            case 126: {
                //#line 254 "LPGParser.g"
                ((terminalList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 127:  terminal ::= terminal_symbol optTerminalAlias
            //
            case 127: {
                //#line 257 "LPGParser.g"
                setResult(
                    //#line 257 LPGParser.g
                    ast_pool.Next()=new terminal(this, getLeftIToken(), getRightIToken(),
                                 //#line 257 LPGParser.g
                                 (IAst*)getRhsSym(1),
                                 //#line 257 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 257 LPGParser.g
                );
            break;
            }
            //
            // Rule 128:  optTerminalAlias ::= $Empty
            //
            case 128: {
                //#line 261 "LPGParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 129:  optTerminalAlias ::= produces name
            //
            case 129: {
                //#line 261 "LPGParser.g"
                setResult(
                    //#line 261 LPGParser.g
                    ast_pool.Next()=new optTerminalAlias(getLeftIToken(), getRightIToken(),
                                         //#line 261 LPGParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 261 LPGParser.g
                                         (IAst*)getRhsSym(2))
                //#line 261 LPGParser.g
                );
            break;
            }
            //
            // Rule 130:  terminal_symbol ::= SYMBOL
            //
            case 130: {
                //#line 263 "LPGParser.g"
                setResult(
                    //#line 263 LPGParser.g
                    ast_pool.Next()=new terminal_symbol0(this, getRhsIToken(1))
                //#line 263 LPGParser.g
                );
            break;
            }
            //
            // Rule 131:  terminal_symbol ::= MACRO_NAME
            //
            case 131: {
                //#line 267 "LPGParser.g"
                setResult(
                    //#line 267 LPGParser.g
                    ast_pool.Next()=new terminal_symbol1(getRhsIToken(1))
                //#line 267 LPGParser.g
                );
            break;
            }
            //
            // Rule 132:  trailers_segment ::= action_segment_list
            //
            case 132:
                break;
            //
            // Rule 133:  types_segment ::= type_declarations
            //
            case 133: {
                //#line 273 "LPGParser.g"
                setResult(
                    //#line 273 LPGParser.g
                    ast_pool.Next()=new type_declarationsList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 273 LPGParser.g
                );
            break;
            }
            //
            // Rule 134:  types_segment ::= types_segment type_declarations
            //
            case 134: {
                //#line 273 "LPGParser.g"
                ((type_declarationsList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 135:  type_declarations ::= SYMBOL produces barSymbolList
            //
            case 135: {
                //#line 275 "LPGParser.g"
                setResult(
                    //#line 275 LPGParser.g
                    ast_pool.Next()=new type_declarations(getLeftIToken(), getRightIToken(),
                                          //#line 275 LPGParser.g
                                          ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                          //#line 275 LPGParser.g
                                          (IAst*)getRhsSym(2),
                                          //#line 275 LPGParser.g
                                          (IAst*)getRhsSym(3))
                //#line 275 LPGParser.g
                );
            break;
            }
            //
            // Rule 136:  barSymbolList ::= SYMBOL
            //
            case 136: {
                //#line 276 "LPGParser.g"
                setResult(
                    //#line 276 LPGParser.g
                    ast_pool.Next()=new SYMBOLList(ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)), true /* left recursive */)
                //#line 276 LPGParser.g
                );
            break;
            }
            //
            // Rule 137:  barSymbolList ::= barSymbolList |$ SYMBOL
            //
            case 137: {
                //#line 276 "LPGParser.g"
                ((SYMBOLList*)getRhsSym(1))->addElement(ast_pool.Next()=new ASTNodeToken(getRhsIToken(3)));
            break;
            }
            //
            // Rule 138:  predecessor_segment ::= $Empty
            //
            case 138: {
                //#line 279 "LPGParser.g"
                setResult(
                    //#line 279 LPGParser.g
                    ast_pool.Next()=new symbol_pairList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 279 LPGParser.g
                );
            break;
            }
            //
            // Rule 139:  predecessor_segment ::= predecessor_segment symbol_pair
            //
            case 139: {
                //#line 279 "LPGParser.g"
                ((symbol_pairList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 140:  symbol_pair ::= SYMBOL SYMBOL
            //
            case 140: {
                //#line 281 "LPGParser.g"
                setResult(
                    //#line 281 LPGParser.g
                    ast_pool.Next()=new symbol_pair(getLeftIToken(), getRightIToken(),
                                    //#line 281 LPGParser.g
                                    ast_pool.Next()=new ASTNodeToken(getRhsIToken(1)),
                                    //#line 281 LPGParser.g
                                    ast_pool.Next()=new ASTNodeToken(getRhsIToken(2)))
                //#line 281 LPGParser.g
                );
            break;
            }
            //
            // Rule 141:  recover_segment ::= $Empty
            //
            case 141: {
                //#line 284 "LPGParser.g"
                setResult(
                    //#line 284 LPGParser.g
                    ast_pool.Next()=new SYMBOLList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 284 LPGParser.g
                );
            break;
            }
            //
            // Rule 142:  recover_segment ::= recover_segment recover_symbol
            //
            case 142: {
                //#line 284 "LPGParser.g"
                setResult((SYMBOLList*)getRhsSym(1));
            break;
            }
            //
            // Rule 143:  recover_symbol ::= SYMBOL
            //
            case 143: {
                //#line 286 "LPGParser.g"
                setResult(
                    //#line 286 LPGParser.g
                    ast_pool.Next()=new recover_symbol(this, getRhsIToken(1))
                //#line 286 LPGParser.g
                );
            break;
            }
            //
            // Rule 144:  END_KEY_OPT ::= $Empty
            //
            case 144: {
                //#line 291 "LPGParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 145:  END_KEY_OPT ::= END_KEY
            //
            case 145: {
                //#line 292 "LPGParser.g"
                setResult(
                    //#line 292 LPGParser.g
                    ast_pool.Next()=new END_KEY_OPT(getRhsIToken(1))
                //#line 292 LPGParser.g
                );
            break;
            }
            //
            // Rule 146:  action_segment_list ::= $Empty
            //
            case 146: {
                //#line 294 "LPGParser.g"
                setResult(
                    //#line 294 LPGParser.g
                    ast_pool.Next()=new action_segmentList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 294 LPGParser.g
                );
            break;
            }
            //
            // Rule 147:  action_segment_list ::= action_segment_list action_segment
            //
            case 147: {
                //#line 295 "LPGParser.g"
                ((action_segmentList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
    //#line 327 "dtParserTemplateF.gi

    
            default:
                break;
        }
        return;
    }
};

