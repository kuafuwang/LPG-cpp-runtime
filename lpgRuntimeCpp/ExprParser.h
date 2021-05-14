
//#line 156 "dtParserTemplateD.g

#include <iostream>

#include "ExprParserprs.h"
#include "src/DeterministicParser.h"
#include "src/diagnose.h"
#include "src/ErrorToken.h"
#include "src/Exception.h"
#include "src/IAbstractArrayList.h"
#include "src/IAst.h"
#include "src/ILexStream.h"
#include "src/ParseTable.h"
#include "src/PrsStream.h"
#include "src/RuleAction.h"


    //#line 175 "dtParserTemplateD.g

struct ExprParser :public PrsStream, public RuleAction
{
    bool unimplementedSymbolsWarning = false;

    inline static ParseTable* prs = new ExprParserprs();
    ParseTable* getParseTable() { return prs; }

    DeterministicParser* dtParser = nullptr;
    DeterministicParser* getParser() { return dtParser; }

    void setResult(Object* object) { dtParser->setSym1(object); }
    Object* getRhsSym(int i) { return dtParser->getSym(i); }

    int getRhsTokenIndex(int i) { return dtParser->getToken(i); }
    IToken* getRhsIToken(int i) { return PrsStream::getIToken(getRhsTokenIndex(i)); }

    int getRhsFirstTokenIndex(int i) { return dtParser->getFirstToken(i); }
    IToken* getRhsFirstIToken(int i) { return PrsStream::getIToken(getRhsFirstTokenIndex(i)); }

    int getRhsLastTokenIndex(int i) { return dtParser->getLastToken(i); }
    IToken* getRhsLastIToken(int i) { return PrsStream::getIToken(getRhsLastTokenIndex(i)); }

    int getLeftSpan() { return dtParser->getFirstToken(); }
    IToken* getLeftIToken() { return PrsStream::getIToken(getLeftSpan()); }

    int getRightSpan() { return dtParser->getLastToken(); }
    IToken* getRightIToken() { return PrsStream::getIToken(getRightSpan()); }

    int getRhsErrorTokenIndex(int i)
    {
        int index = dtParser->getToken(i);
        IToken* err = PrsStream::getIToken(index);
        return (dynamic_cast<ErrorToken*>(err) ? index : 0);
    }
    ErrorToken* getRhsErrorIToken(int i)
    {
        int index = dtParser->getToken(i);
        IToken* err = PrsStream::getIToken(index);
        return (ErrorToken*)(dynamic_cast<ErrorToken*>(err) ? err : nullptr);
    }

    ExprParser(ILexStream* lexStream) :PrsStream(lexStream)
    {
        try
        {
            PrsStream::remapTerminalSymbols(orderedTerminalSymbols(), ExprParserprs::EOFT_SYMBOL);
        }
        catch (NullExportedSymbolsException& e) {
        }
        catch (NullTerminalSymbolsException& e) {
        }
        catch (UnimplementedTerminalsException& e)
        {
            if (unimplementedSymbolsWarning) {
                auto unimplemented_symbols = e.getSymbols();
                std::cout << ("The Lexer will not scan the following token(s):");
                for (int i = 0; i < unimplemented_symbols.size(); i++)
                {
                    auto id = unimplemented_symbols.at(i);
                    std::wcout << L"    " << ExprParsersym::orderedTerminalSymbols[id];
                }
                std::cout << std::endl;
            }
        }
        catch (UndefinedEofSymbolException& e)
        {

            //throw ( UndefinedEofSymbolException
                //                ("The Lexer does not implement the Eof symbol " +
                //                 ExprParsersym::orderedTerminalSymbols[ExprParserprs::EOFT_SYMBOL]));
        }

        try
        {
            dtParser = new DeterministicParser(this, prs, this);
        }
        catch (NotDeterministicParseTableException& e)
        {
            throw  (NotDeterministicParseTableException
            ("Regenerate ExprParserprs.java with -NOBACKTRACK option"));
        }
        catch (BadParseSymFileException& e)
        {
            throw  (BadParseSymFileException("Bad Parser Symbol File -- ExprParsersym.java. Regenerate ExprParserprs.java"));
        }
    }

    std::vector<std::wstring> orderedTerminalSymbols() { return ExprParsersym::orderedTerminalSymbols; }
    std::wstring getTokenKindName(int kind) { return ExprParsersym::orderedTerminalSymbols[kind]; }
    int getEOFTokenKind() { return ExprParserprs::EOFT_SYMBOL; }
    PrsStream* getParseStream() { return (PrsStream*)this; }
    struct Ast;
    Ast* parser()
    {
        return parser(nullptr, 0);
    }

    Ast* parser(Monitor* monitor)
    {
        return parser(monitor, 0);
    }

    Ast* parser(int error_repair_count)
    {
        return parser(nullptr, error_repair_count);
    }

    Ast* parser(Monitor* monitor, int error_repair_count)
    {
        dtParser->setMonitor(monitor);

        try
        {
            return (Ast*)dtParser->parse();
        }
        catch (BadParseException e)
        {
            reset(e.error_token); // point to error token

            DiagnoseParser diagnoseParser(this, prs);
            diagnoseParser.diagnose(e.error_token);
        }

        return nullptr;
    }

    //
    // Additional entry points, if any
    //

    struct Ast;
    struct AbstractAstList;
    struct AstToken;
    struct E;
    struct T;
    struct F;
    struct ParenExpr;
    struct Visitor;
    struct ArgumentVisitor;
    struct ResultVisitor;
    struct ResultArgumentVisitor;
    struct AbstractVisitor;
    struct AbstractResultVisitor;
    Tuple<IAst*> ast_pool;
    struct Ast :public IAst
    {
        IAst* getNextAst() { return nullptr; }
        IToken* leftIToken = nullptr;
        IToken* rightIToken = nullptr;
        IAst* getParent()
        {
            throw UnsupportedOperationException("noparent-saved option in effect");
        }

        IToken* getLeftIToken() { return leftIToken; }
        IToken* getRightIToken() { return rightIToken; }
        std::vector<IToken*> getPrecedingAdjuncts() { return leftIToken->getPrecedingAdjuncts(); }
        std::vector<IToken*> getFollowingAdjuncts() { return rightIToken->getFollowingAdjuncts(); }

        std::wstring toString()
        {
            return leftIToken->getILexStream()->toString(leftIToken->getStartOffset(), rightIToken->getEndOffset());
        }

        Ast(IToken* token) { this->leftIToken = this->rightIToken = token; }
        Ast(IToken* leftIToken, IToken* rightIToken)
        {
            this->leftIToken = leftIToken;
            this->rightIToken = rightIToken;
        }

        void initialize() {}

        std::vector<IAst*> getChildren()
        {
            throw UnsupportedOperationException("noparent-saved option in effect");
        }
        std::vector<IAst*> getAllChildren() { return getChildren(); }

        virtual void accept(Visitor* v) = 0;
        virtual void accept(ArgumentVisitor* v, Object* o) = 0;
        virtual Object* accept(ResultVisitor* v) = 0;
        virtual Object* accept(ResultArgumentVisitor* v, Object* o) = 0;
        void accept(IAstVisitor* v) {}
    };

    struct AbstractAstList :public Ast, public IAbstractArrayList<Ast*>
    {
        bool leftRecursive;
        int size() { return list.size(); }
        std::vector<Ast*> getList() { return list; }
        Ast* getElementAt(int i) { return (Ast*)list.at(leftRecursive ? i : list.size() - 1 - i); }
        std::vector<    Ast*> getArrayList()
        {
            if (!leftRecursive) // reverse the list 
            {
                for (int i = 0, n = list.size() - 1; i < n; i++, n--)
                {
                    auto ith = list[i];
                    auto nth = list[n];
                    list[i] = (nth);
                    list[n] = (ith);
                }
                leftRecursive = true;
            }
            return list;
        }
        /**
         * @deprecated replaced by {@link #addElement()}
         *
         */
        bool add(Ast* element)
        {
            addElement(element);
            return true;
        }

        void addElement(Ast* element)
        {
            list.push_back(element);
            if (leftRecursive)
                rightIToken = element->getRightIToken();
            else leftIToken = element->getLeftIToken();
        }

        AbstractAstList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive) :Ast(leftIToken, rightIToken)
        {
            this->leftRecursive = leftRecursive;
        }

        AbstractAstList(Ast* element, bool leftRecursive) :Ast(element->getLeftIToken(), element->getRightIToken())
        {
            this->leftRecursive = leftRecursive;
            list.push_back(element);
        }

    };

    struct AstToken :public  Ast
    {
        AstToken(IToken* token) :Ast(token) { }
        IToken* getIToken() { return leftIToken; }
        std::wstring toString() { return leftIToken->toString(); }


        void accept(Visitor* v) { v->visit(this); }
        void accept(ArgumentVisitor* v, Object* o) { v->visit(this, o); }
        Object* accept(ResultVisitor* v) { return v->visit(this); }
        Object* accept(ResultArgumentVisitor* v, Object* o) { return v->visit(this, o); }
    };

    /**
     *<em>
     *<li>Rule 2:  E ::= T
     *</em>
     *<p>
     *<b>
     *<li>Rule 1:  E ::= E + T
     *</b>
     */
    struct E :public Ast {
        IAst* _E;
        IAst* _T;

        IAst* getE() { return _E; };
        void setE(IAst* _E) { this->_E = _E; }
        IAst* getT() { return _T; };
        void setT(IAst* _T) { this->_T = _T; }

        E(IToken* leftIToken, IToken* rightIToken,
            IAst* _E,
            IAst* _T) :Ast(leftIToken, rightIToken) {
            this->_E = _E;
            this->_T = _T;
            initialize();
        }

        void accept(Visitor* v) { v->visit(this); }
        void accept(ArgumentVisitor* v, Object* o) { v->visit(this, o); }
        Object* accept(ResultVisitor* v) { return v->visit(this); }
        Object* accept(ResultArgumentVisitor* v, Object* o) { return v->visit(this, o); }
    };

    /**
     *<em>
     *<li>Rule 4:  T ::= F
     *</em>
     *<p>
     *<b>
     *<li>Rule 3:  T ::= T * F
     *</b>
     */
    struct T :public Ast {
        IAst* _T;
        IAst* _F;

        IAst* getT() { return _T; };
        void setT(IAst* _T) { this->_T = _T; }
        IAst* getF() { return _F; };
        void setF(IAst* _F) { this->_F = _F; }

        T(IToken* leftIToken, IToken* rightIToken,
            IAst* _T,
            IAst* _F) :Ast(leftIToken, rightIToken) {
            this->_T = _T;
            this->_F = _F;
            initialize();
        }

        void accept(Visitor* v) { v->visit(this); }
        void accept(ArgumentVisitor* v, Object* o) { v->visit(this, o); }
        Object* accept(ResultVisitor* v) { return v->visit(this); }
        Object* accept(ResultArgumentVisitor* v, Object* o) { return v->visit(this, o); }
    };

    /**
     *<b>
     *<li>Rule 5:  F ::= IntegerLiteral
     *</b>
     */
    struct F :public AstToken {
        F(IToken* token) :AstToken(token)
        {
            initialize();
        }

        void accept(Visitor* v) { v->visit(this); }
        void accept(ArgumentVisitor* v, Object* o) { v->visit(this, o); }
        Object* accept(ResultVisitor* v) { return v->visit(this); }
        Object* accept(ResultArgumentVisitor* v, Object* o) { return v->visit(this, o); }
    };

    /**
     *<b>
     *<li>Rule 6:  F ::= ( E )
     *</b>
     */
    struct ParenExpr :public Ast {
        IAst* _E;

        IAst* getE() { return _E; };
        void setE(IAst* _E) { this->_E = _E; }

        ParenExpr(IToken* leftIToken, IToken* rightIToken,
            IAst* _E) :Ast(leftIToken, rightIToken) {
            this->_E = _E;
            initialize();
        }

        void accept(Visitor* v) { v->visit(this); }
        void accept(ArgumentVisitor* v, Object* o) { v->visit(this, o); }
        Object* accept(ResultVisitor* v) { return v->visit(this); }
        Object* accept(ResultArgumentVisitor* v, Object* o) { return v->visit(this, o); }
    };

    struct Visitor
    {
        virtual void visit(AstToken* n) = 0;
        virtual void visit(E* n) = 0;
        virtual void visit(T* n) = 0;
        virtual void visit(F* n) = 0;
        virtual void visit(ParenExpr* n) = 0;

        virtual void visit(Ast* n) = 0;
    };
    struct ArgumentVisitor
    {
        virtual void visit(AstToken* n, Object* o) = 0;
        virtual void visit(E* n, Object* o) = 0;
        virtual void visit(T* n, Object* o) = 0;
        virtual void visit(F* n, Object* o) = 0;
        virtual void visit(ParenExpr* n, Object* o) = 0;

        virtual  void visit(Ast* n, Object* o) = 0;
    };
    struct ResultVisitor
    {
        virtual  Object* visit(AstToken* n) = 0;
        virtual  Object* visit(E* n) = 0;
        virtual  Object* visit(T* n) = 0;
        virtual  Object* visit(F* n) = 0;
        virtual  Object* visit(ParenExpr* n) = 0;

        virtual  Object* visit(Ast* n) = 0;
    };
    struct ResultArgumentVisitor
    {
        virtual  Object* visit(AstToken* n, Object* o) = 0;
        virtual  Object* visit(E* n, Object* o) = 0;
        virtual  Object* visit(T* n, Object* o) = 0;
        virtual  Object* visit(F* n, Object* o) = 0;
        virtual  Object* visit(ParenExpr* n, Object* o) = 0;

        virtual  Object* visit(Ast* n, Object* o) = 0;
    };
    struct AbstractVisitor :public Visitor, public ArgumentVisitor
    {
        virtual void unimplementedVisitor(const std::string& s) = 0;

        virtual   void visit(AstToken* n) { unimplementedVisitor("visit(AstToken)"); }
        virtual  void visit(AstToken* n, Object* o) { unimplementedVisitor("visit(AstToken, Object)"); }

        virtual   void visit(E* n) { unimplementedVisitor("visit(E)"); }
        virtual  void visit(E* n, Object* o) { unimplementedVisitor("visit(E, Object)"); }

        virtual   void visit(T* n) { unimplementedVisitor("visit(T)"); }
        virtual  void visit(T* n, Object* o) { unimplementedVisitor("visit(T, Object)"); }

        virtual   void visit(F* n) { unimplementedVisitor("visit(F)"); }
        virtual  void visit(F* n, Object* o) { unimplementedVisitor("visit(F, Object)"); }

        virtual   void visit(ParenExpr* n) { unimplementedVisitor("visit(ParenExpr)"); }
        virtual  void visit(ParenExpr* n, Object* o) { unimplementedVisitor("visit(ParenExpr, Object)"); }


        virtual  void visit(Ast* n)
        {
            if (dynamic_cast<AstToken*>(n)) visit((AstToken*)n);
            else if (dynamic_cast<E*>(n)) visit((E*)n);
            else if (dynamic_cast<T*>(n)) visit((T*)n);
            else if (dynamic_cast<F*>(n)) visit((F*)n);
            else if (dynamic_cast<ParenExpr*>(n)) visit((ParenExpr*)n);
            throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
        }
        void visit(Ast* n, Object* o)
        {
            if (dynamic_cast<AstToken*>(n)) visit((AstToken*)n, o);
            else if (dynamic_cast<E*>(n)) visit((E*)n, o);
            else if (dynamic_cast<T*>(n)) visit((T*)n, o);
            else if (dynamic_cast<F*>(n)) visit((F*)n, o);
            else if (dynamic_cast<ParenExpr*>(n)) visit((ParenExpr*)n, o);
            throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
        }
    };
    struct AbstractResultVisitor :public ResultVisitor, public ResultArgumentVisitor
    {
        virtual Object* unimplementedVisitor(const std::string& s);

        Object* visit(AstToken* n) { return unimplementedVisitor("visit(AstToken)"); }
        Object* visit(AstToken* n, Object* o) { return  unimplementedVisitor("visit(AstToken, Object)"); }

        Object* visit(E* n) { return unimplementedVisitor("visit(E)"); }
        Object* visit(E* n, Object* o) { return  unimplementedVisitor("visit(E, Object)"); }

        Object* visit(T* n) { return unimplementedVisitor("visit(T)"); }
        Object* visit(T* n, Object* o) { return  unimplementedVisitor("visit(T, Object)"); }

        Object* visit(F* n) { return unimplementedVisitor("visit(F)"); }
        Object* visit(F* n, Object* o) { return  unimplementedVisitor("visit(F, Object)"); }

        Object* visit(ParenExpr* n) { return unimplementedVisitor("visit(ParenExpr)"); }
        Object* visit(ParenExpr* n, Object* o) { return  unimplementedVisitor("visit(ParenExpr, Object)"); }


        Object* visit(Ast* n)
        {
            if (dynamic_cast<AstToken*>(n)) return visit((AstToken*)n);
            else if (dynamic_cast<E*>(n)) return visit((E*)n);
            else if (dynamic_cast<T*>(n)) return visit((T*)n);
            else if (dynamic_cast<F*>(n)) return visit((F*)n);
            else if (dynamic_cast<ParenExpr*>(n)) return visit((ParenExpr*)n);
            throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
        }
        Object* visit(Ast* n, Object* o)
        {
            if (dynamic_cast<AstToken*>(n)) return visit((AstToken*)n, o);
            else if (dynamic_cast<E*>(n)) return visit((E*)n, o);
            else if (dynamic_cast<T*>(n)) return visit((T*)n, o);
            else if (dynamic_cast<F*>(n)) return visit((F*)n, o);
            else if (dynamic_cast<ParenExpr*>(n)) return visit((ParenExpr*)n, o);
            throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
        }
    };

    //#line 311 "dtParserTemplateD.g

    void ruleAction(int ruleNumber)
    {
        switch (ruleNumber)
        {

            //
            // Rule 1:  E ::= E + T
            //
        case 1: {
            setResult(
                //#line 15 ExprParser.g
                ast_pool.Next() = new E(getLeftIToken(), getRightIToken(),
                    //#line 15 ExprParser.g
                    (IAst*)getRhsSym(1),
                    //#line 15 ExprParser.g
                    (IAst*)getRhsSym(3))
                //#line 15 ExprParser.g
            );
            break;
        }
              //
              // Rule 2:  E ::= T
              //
        case 2:
            break;
            //
            // Rule 3:  T ::= T * F
            //
        case 3: {
            setResult(
                //#line 17 ExprParser.g
                ast_pool.Next() = new T(getLeftIToken(), getRightIToken(),
                    //#line 17 ExprParser.g
                    (IAst*)getRhsSym(1),
                    //#line 17 ExprParser.g
                    (IAst*)getRhsSym(3))
                //#line 17 ExprParser.g
            );
            break;
        }
              //
              // Rule 4:  T ::= F
              //
        case 4:
            break;
            //
            // Rule 5:  F ::= IntegerLiteral
            //
        case 5: {
            setResult(
                //#line 19 ExprParser.g
                ast_pool.Next() = new F(getRhsIToken(1))
                //#line 19 ExprParser.g
            );
            break;
        }
              //
              // Rule 6:  F ::= ( E )
              //
        case 6: {
            setResult(
                //#line 20 ExprParser.g
                ast_pool.Next() = new ParenExpr(getLeftIToken(), getRightIToken(),
                    //#line 20 ExprParser.g
                    (IAst*)getRhsSym(2))
                //#line 20 ExprParser.g
            );
            break;
        }
              //#line 315 "dtParserTemplateD.g


        default:
            break;
        }
        return;
    }

    void remapTerminalSymbols(std::vector<std::wstring> ordered_parser_symbols, int eof_symbol) override
    {
	    
    }
};

