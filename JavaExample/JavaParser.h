//
// This is the grammar specification from the Final Draft of the generic spec.
//
////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2007 IBM Corporation.
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v1.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v10.html
//
//Contributors:
//    Philippe Charles (pcharles@us.ibm.com) - initial API and implementation

////////////////////////////////////////////////////////////////////////////////


    //#line 161 "btParserTemplateF.gi

#pragma once

#include <iostream>

#include "BacktrackingParser.h"
#include "DeterministicParser.h"
#include "diagnose.h"
#include "ErrorToken.h"
#include "Exception.h"
#include "IAbstractArrayList.h"
#include "IAst.h"
#include "IAstVisitor.h"
#include "ILexStream.h"
#include "JavaParsersym.h"
#include "JavaParserprs.h"
#include "Object.h"
#include "ParseTable.h"
#include "PrsStream.h"
#include "RuleAction.h"
#include "IcuUtil.h"

    //#line 17 "GJavaParser.g



    //#line 186 "btParserTemplateF.gi

 struct JavaParser :public Object ,public RuleAction
{
     PrsStream* prsStream = nullptr;
    
     bool unimplementedSymbolsWarning = false;

     inline static ParseTable* prsTable = new JavaParserprs();
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
                std::cout << "The Lexer will not scan the following token(s):" << std::endl;
                for (int i = 0; i < unimplemented_symbols.size(); i++)
                {
                    auto id = unimplemented_symbols.at(i);
                    std::wcout <<L"    " << JavaParsersym::orderedTerminalSymbols[id] << std::endl;               
                }
               std::cout <<std::endl;  
            }
        }
        catch (UndefinedEofSymbolException& e)
        {
            std::stringex str= "The Lexer does not implement the Eof symbol ";
            str += IcuUtil::ws2s(JavaParsersym::orderedTerminalSymbols[prsTable->getEoftSymbol()]);
            throw  UndefinedEofSymbolException(str);
        } 
    }
    
     JavaParser(ILexStream* lexStream = nullptr)
    {
        try
        {
            btParser = new BacktrackingParser(prsStream, prsTable,  this);
        }
        catch (NotBacktrackParseTableException& e)
        {
            throw ( NotBacktrackParseTableException
                                ("Regenerate JavaParserprs.java with -BACKTRACK option"));
        }
        catch (BadParseSymFileException& e)
        {
            throw ( BadParseSymFileException("Bad Parser Symbol File -- JavaParsersym::java"));
        }

        if(lexStream)
        {
            reset(lexStream);
        }
    }
    

    
     int numTokenKinds() { return JavaParsersym::numTokenKinds; }
     std::vector<std::wstring> orderedTerminalSymbols() { 
         return JavaParsersym::orderedTerminalSymbols; 
    }
     std::wstring getTokenKindName(int kind) { return JavaParsersym::orderedTerminalSymbols[kind]; }
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
     struct Ast;
     Ast* parser()
    {
        return parser(nullptr, 0);
    }
    
     Ast* parser(Monitor* monitor)
    {
        return parser(monitor, 0);
    }
    
     Ast * parser(int error_repair_count)
    {
        return parser(nullptr, error_repair_count);
    }

     Ast * parser(Monitor* monitor, int error_repair_count)
    {
        btParser->setMonitor(monitor);
        
        try
        {
            return (Ast *) btParser->fuzzyParse(error_repair_count);
        }
        catch (BadParseException& e)
        {
            prsStream->reset(e.error_token); // point to error token

            std::shared_ptr< DiagnoseParser> diagnoseParser = std::make_shared<DiagnoseParser>(prsStream, prsTable);
            diagnoseParser->diagnose(e.error_token);
        }

        return nullptr;
    }

    //
    // Additional entry points, if any
    //
    
     Ast * parseClassBodyDeclarationsopt()
    {
        return parseClassBodyDeclarationsopt(nullptr, 0);
    }
        
     Ast * parseClassBodyDeclarationsopt(Monitor* monitor)
    {
        return parseClassBodyDeclarationsopt(monitor, 0);
    }
        
     Ast * parseClassBodyDeclarationsopt(int error_repair_count)
    {
        return parseClassBodyDeclarationsopt(nullptr, error_repair_count);
    }
        
     Ast * parseClassBodyDeclarationsopt(Monitor* monitor, int error_repair_count)
    {
        btParser->setMonitor(monitor);
        
        try
        {
            return (Ast *) btParser->fuzzyParseEntry(JavaParsersym::TK_ClassBodyDeclarationsoptMarker, error_repair_count);
        }
        catch (BadParseException& e)
        {
            prsStream->reset(e.error_token); // point to error token

             std::shared_ptr< DiagnoseParser> diagnoseParser = std::make_shared<DiagnoseParser>(prsStream, prsTable);
            diagnoseParser->diagnoseEntry(JavaParsersym::TK_ClassBodyDeclarationsoptMarker, e.error_token);
        }

        return nullptr;
    }

     Ast * parseLPGUserAction()
    {
        return parseLPGUserAction(nullptr, 0);
    }
        
     Ast * parseLPGUserAction(Monitor* monitor)
    {
        return parseLPGUserAction(monitor, 0);
    }
        
     Ast * parseLPGUserAction(int error_repair_count)
    {
        return parseLPGUserAction(nullptr, error_repair_count);
    }
        
     Ast * parseLPGUserAction(Monitor *monitor, int error_repair_count)
    {
        btParser->setMonitor(monitor);
        
        try
        {
            return (Ast *) btParser->fuzzyParseEntry(JavaParsersym::TK_LPGUserActionMarker, error_repair_count);
        }
        catch (BadParseException& e)
        {
            prsStream->reset(e.error_token); // point to error token

             std::shared_ptr< DiagnoseParser> diagnoseParser = std::make_shared<DiagnoseParser>(prsStream, prsTable);
            diagnoseParser->diagnoseEntry(JavaParsersym::TK_LPGUserActionMarker, e.error_token);
        }

        return nullptr;
    }


  struct AbstractAstList;
  struct AstToken;
  struct identifier;
  struct PrimitiveType;
  struct ClassType;
  struct InterfaceType;
  struct TypeName;
  struct ArrayType;
  struct TypeParameter;
  struct TypeBound;
  struct AdditionalBoundList;
  struct AdditionalBound;
  struct TypeArguments;
  struct ActualTypeArgumentList;
  struct Wildcard;
  struct PackageName;
  struct ExpressionName;
  struct MethodName;
  struct PackageOrTypeName;
  struct AmbiguousName;
  struct CompilationUnit;
  struct ImportDeclarations;
  struct TypeDeclarations;
  struct PackageDeclaration;
  struct SingleTypeImportDeclaration;
  struct TypeImportOnDemandDeclaration;
  struct SingleStaticImportDeclaration;
  struct StaticImportOnDemandDeclaration;
  struct TypeDeclaration;
  struct NormalClassDeclaration;
  struct ClassModifiers;
  struct TypeParameters;
  struct TypeParameterList;
  struct Super;
  struct Interfaces;
  struct InterfaceTypeList;
  struct ClassBody;
  struct ClassBodyDeclarations;
  struct ClassMemberDeclaration;
  struct FieldDeclaration;
  struct VariableDeclarators;
  struct VariableDeclarator;
  struct VariableDeclaratorId;
  struct FieldModifiers;
  struct MethodDeclaration;
  struct MethodHeader;
  struct ResultType;
  struct FormalParameterList;
  struct FormalParameters;
  struct FormalParameter;
  struct VariableModifiers;
  struct VariableModifier;
  struct LastFormalParameter;
  struct MethodModifiers;
  struct Throws;
  struct ExceptionTypeList;
  struct MethodBody;
  struct StaticInitializer;
  struct ConstructorDeclaration;
  struct ConstructorDeclarator;
  struct ConstructorModifiers;
  struct ConstructorBody;
  struct EnumDeclaration;
  struct EnumBody;
  struct EnumConstants;
  struct EnumConstant;
  struct Arguments;
  struct EnumBodyDeclarations;
  struct NormalInterfaceDeclaration;
  struct InterfaceModifiers;
  struct InterfaceBody;
  struct InterfaceMemberDeclarations;
  struct InterfaceMemberDeclaration;
  struct ConstantDeclaration;
  struct ConstantModifiers;
  struct AbstractMethodDeclaration;
  struct AbstractMethodModifiers;
  struct AnnotationTypeDeclaration;
  struct AnnotationTypeBody;
  struct AnnotationTypeElementDeclarations;
  struct DefaultValue;
  struct Annotations;
  struct NormalAnnotation;
  struct ElementValuePairs;
  struct ElementValuePair;
  struct ElementValueArrayInitializer;
  struct ElementValues;
  struct MarkerAnnotation;
  struct SingleElementAnnotation;
  struct ArrayInitializer;
  struct VariableInitializers;
  struct Block;
  struct BlockStatements;
  struct LocalVariableDeclarationStatement;
  struct LocalVariableDeclaration;
  struct IfThenStatement;
  struct IfThenElseStatement;
  struct IfThenElseStatementNoShortIf;
  struct EmptyStatement;
  struct LabeledStatement;
  struct LabeledStatementNoShortIf;
  struct ExpressionStatement;
  struct SwitchStatement;
  struct SwitchBlock;
  struct SwitchBlockStatementGroups;
  struct SwitchBlockStatementGroup;
  struct SwitchLabels;
  struct WhileStatement;
  struct WhileStatementNoShortIf;
  struct DoStatement;
  struct BasicForStatement;
  struct ForStatementNoShortIf;
  struct StatementExpressionList;
  struct EnhancedForStatement;
  struct BreakStatement;
  struct ContinueStatement;
  struct ReturnStatement;
  struct ThrowStatement;
  struct SynchronizedStatement;
  struct Catches;
  struct CatchClause;
  struct Finally;
  struct ArgumentList;
  struct DimExprs;
  struct DimExpr;
  struct PostIncrementExpression;
  struct PostDecrementExpression;
  struct PreIncrementExpression;
  struct PreDecrementExpression;
  struct AndExpression;
  struct ExclusiveOrExpression;
  struct InclusiveOrExpression;
  struct ConditionalAndExpression;
  struct ConditionalOrExpression;
  struct ConditionalExpression;
  struct Assignment;
  struct Commaopt;
  struct Ellipsisopt;
  struct LPGUserAction0;
  struct LPGUserAction1;
  struct LPGUserAction2;
  struct LPGUserAction3;
  struct LPGUserAction4;
  struct IntegralType0;
  struct IntegralType1;
  struct IntegralType2;
  struct IntegralType3;
  struct IntegralType4;
  struct FloatingPointType0;
  struct FloatingPointType1;
  struct WildcardBounds0;
  struct WildcardBounds1;
  struct ClassModifier0;
  struct ClassModifier1;
  struct ClassModifier2;
  struct ClassModifier3;
  struct ClassModifier4;
  struct ClassModifier5;
  struct ClassModifier6;
  struct FieldModifier0;
  struct FieldModifier1;
  struct FieldModifier2;
  struct FieldModifier3;
  struct FieldModifier4;
  struct FieldModifier5;
  struct FieldModifier6;
  struct MethodDeclarator0;
  struct MethodDeclarator1;
  struct MethodModifier0;
  struct MethodModifier1;
  struct MethodModifier2;
  struct MethodModifier3;
  struct MethodModifier4;
  struct MethodModifier5;
  struct MethodModifier6;
  struct MethodModifier7;
  struct MethodModifier8;
  struct ConstructorModifier0;
  struct ConstructorModifier1;
  struct ConstructorModifier2;
  struct ExplicitConstructorInvocation0;
  struct ExplicitConstructorInvocation1;
  struct ExplicitConstructorInvocation2;
  struct InterfaceModifier0;
  struct InterfaceModifier1;
  struct InterfaceModifier2;
  struct InterfaceModifier3;
  struct InterfaceModifier4;
  struct InterfaceModifier5;
  struct ExtendsInterfaces0;
  struct ExtendsInterfaces1;
  struct ConstantModifier0;
  struct ConstantModifier1;
  struct ConstantModifier2;
  struct AbstractMethodModifier0;
  struct AbstractMethodModifier1;
  struct AnnotationTypeElementDeclaration0;
  struct AnnotationTypeElementDeclaration1;
  struct AssertStatement0;
  struct AssertStatement1;
  struct SwitchLabel0;
  struct SwitchLabel1;
  struct SwitchLabel2;
  struct TryStatement0;
  struct TryStatement1;
  struct PrimaryNoNewArray0;
  struct PrimaryNoNewArray1;
  struct PrimaryNoNewArray2;
  struct PrimaryNoNewArray3;
  struct PrimaryNoNewArray4;
  struct Literal0;
  struct Literal1;
  struct Literal2;
  struct Literal3;
  struct Literal4;
  struct Literal5;
  struct Literal6;
  struct BooleanLiteral0;
  struct BooleanLiteral1;
  struct ClassInstanceCreationExpression0;
  struct ClassInstanceCreationExpression1;
  struct ArrayCreationExpression0;
  struct ArrayCreationExpression1;
  struct ArrayCreationExpression2;
  struct ArrayCreationExpression3;
  struct Dims0;
  struct Dims1;
  struct FieldAccess0;
  struct FieldAccess1;
  struct FieldAccess2;
  struct MethodInvocation0;
  struct MethodInvocation1;
  struct MethodInvocation2;
  struct MethodInvocation3;
  struct MethodInvocation4;
  struct ArrayAccess0;
  struct ArrayAccess1;
  struct UnaryExpression0;
  struct UnaryExpression1;
  struct UnaryExpressionNotPlusMinus0;
  struct UnaryExpressionNotPlusMinus1;
  struct CastExpression0;
  struct CastExpression1;
  struct MultiplicativeExpression0;
  struct MultiplicativeExpression1;
  struct MultiplicativeExpression2;
  struct AdditiveExpression0;
  struct AdditiveExpression1;
  struct ShiftExpression0;
  struct ShiftExpression1;
  struct ShiftExpression2;
  struct RelationalExpression0;
  struct RelationalExpression1;
  struct RelationalExpression2;
  struct RelationalExpression3;
  struct RelationalExpression4;
  struct EqualityExpression0;
  struct EqualityExpression1;
  struct AssignmentOperator0;
  struct AssignmentOperator1;
  struct AssignmentOperator2;
  struct AssignmentOperator3;
  struct AssignmentOperator4;
  struct AssignmentOperator5;
  struct AssignmentOperator6;
  struct AssignmentOperator7;
  struct AssignmentOperator8;
  struct AssignmentOperator9;
  struct AssignmentOperator10;
  struct AssignmentOperator11;
  struct Visitor;
  struct AbstractVisitor;
 Tuple<IAst*> ast_pool;
    struct Ast :public IAst
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

        Ast(IToken* token) { this->leftIToken = this->rightIToken = token; }
        Ast(IToken* leftIToken, IToken* rightIToken)
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

    struct AbstractAstList :public Ast ,public IAbstractArrayList<Ast*>
    {
        bool leftRecursive;
        int size() { return list.size(); }
       std::vector<Ast       *> getList() { return list; }
        Ast *getElementAt(int i) { return (Ast*) list.at(leftRecursive ? i : list.size() - 1 - i); }
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
        bool add(Ast *element)
        {
            addElement(element);
            return true;
        }

        void addElement(Ast *element)
        {
            list.push_back(element);
            if (leftRecursive)
                 rightIToken = element->getRightIToken();
            else leftIToken =  element->getLeftIToken();
        }

        AbstractAstList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):Ast(leftIToken, rightIToken)
        {
            this->leftRecursive = leftRecursive;
        }

        AbstractAstList(Ast *element, bool leftRecursive):Ast(element->getLeftIToken(), element->getRightIToken())
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

    struct AstToken :public  Ast
    {
        AstToken(IToken* token):Ast(token){ }
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
     *<li>Rule 3:  identifier ::= IDENTIFIER
     *</b>
     */
    struct identifier :public AstToken
    {
        JavaParser* environment;
        JavaParser* getEnvironment() { return environment; }

        IToken* getIDENTIFIER() { return leftIToken; }

        identifier(JavaParser *environment, IToken* token):AstToken    (token)
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

    //#line 185 "GJavaParser.g

                void initialize()
                {
                    if (getIDENTIFIER()->getKind() != JavaParserprs ::TK_IDENTIFIER)
                       std::wcout <<L"Turning keyword " << getIDENTIFIER()->toString() << L" into an identifier" << std::endl;
                }
        };

    /**
     *<em>
     *<li>Rule 12:  PrimitiveType ::= NumericType
     *</em>
     *<p>
     *<b>
     *<li>Rule 13:  PrimitiveType ::= boolean
     *</b>
     */
    struct PrimitiveType :public AstToken
    {
        IToken* getboolean() { return leftIToken; }

        PrimitiveType(IToken* token) :AstToken(token)
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
     *<li>Rule 27:  ClassType ::= TypeName TypeArgumentsopt
     *</b>
     */
    struct ClassType :public Ast
    {
        IAst *_TypeName;
        IAst *_TypeArgumentsopt;

        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }
        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }

        ClassType(IToken* leftIToken, IToken* rightIToken,
                  IAst *_TypeName,
                  IAst *_TypeArgumentsopt):Ast(leftIToken, rightIToken)    {
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeName);
            list.push_back(_TypeArgumentsopt);
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
                _TypeName->accept(v);
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 28:  InterfaceType ::= TypeName TypeArgumentsopt
     *</b>
     */
    struct InterfaceType :public Ast
    {
        IAst *_TypeName;
        IAst *_TypeArgumentsopt;

        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }
        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }

        InterfaceType(IToken* leftIToken, IToken* rightIToken,
                      IAst *_TypeName,
                      IAst *_TypeArgumentsopt):Ast(leftIToken, rightIToken)    {
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeName);
            list.push_back(_TypeArgumentsopt);
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
                _TypeName->accept(v);
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 29:  TypeName ::= identifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 30:  TypeName ::= TypeName . identifier
     *</b>
     */
    struct TypeName :public Ast
    {
        IAst *_TypeName;
        IAst *_DOT;
        IAst *_identifier;

        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }

        TypeName(IToken* leftIToken, IToken* rightIToken,
                 IAst *_TypeName,
                 IAst *_DOT,
                 IAst *_identifier):Ast(leftIToken, rightIToken)    {
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeName);
            list.push_back(_DOT);
            list.push_back(_identifier);
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
                _TypeName->accept(v);
                _DOT->accept(v);
                _identifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 33:  ArrayType ::= Type [ ]
     *</b>
     */
    struct ArrayType :public Ast
    {
        IAst *_Type;
        IAst *_LBRACKET;
        IAst *_RBRACKET;

        IAst *getType() { return _Type; };
        void setType(IAst *_Type) { this->_Type = _Type; }
        IAst *getLBRACKET() { return _LBRACKET; };
        void setLBRACKET(IAst *_LBRACKET) { this->_LBRACKET = _LBRACKET; }
        IAst *getRBRACKET() { return _RBRACKET; };
        void setRBRACKET(IAst *_RBRACKET) { this->_RBRACKET = _RBRACKET; }

        ArrayType(IToken* leftIToken, IToken* rightIToken,
                  IAst *_Type,
                  IAst *_LBRACKET,
                  IAst *_RBRACKET):Ast(leftIToken, rightIToken)    {
            this->_Type = _Type;
            ((Ast*) _Type)->setParent(this);
            this->_LBRACKET = _LBRACKET;
            ((Ast*) _LBRACKET)->setParent(this);
            this->_RBRACKET = _RBRACKET;
            ((Ast*) _RBRACKET)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Type);
            list.push_back(_LBRACKET);
            list.push_back(_RBRACKET);
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
                _Type->accept(v);
                _LBRACKET->accept(v);
                _RBRACKET->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 34:  TypeParameter ::= TypeVariable TypeBoundopt
     *</b>
     */
    struct TypeParameter :public Ast
    {
        IAst *_TypeVariable;
        IAst *_TypeBoundopt;

        IAst *getTypeVariable() { return _TypeVariable; };
        void setTypeVariable(IAst *_TypeVariable) { this->_TypeVariable = _TypeVariable; }
        /**
         * The value returned by <b>getTypeBoundopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeBoundopt() { return _TypeBoundopt; };
        void setTypeBoundopt(IAst *_TypeBoundopt) { this->_TypeBoundopt = _TypeBoundopt; }

        TypeParameter(IToken* leftIToken, IToken* rightIToken,
                      IAst *_TypeVariable,
                      IAst *_TypeBoundopt):Ast(leftIToken, rightIToken)    {
            this->_TypeVariable = _TypeVariable;
            ((Ast*) _TypeVariable)->setParent(this);
            this->_TypeBoundopt = _TypeBoundopt;
            if (_TypeBoundopt != nullptr) ((Ast*) _TypeBoundopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeVariable);
            list.push_back(_TypeBoundopt);
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
                _TypeVariable->accept(v);
                if (_TypeBoundopt != nullptr) _TypeBoundopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 35:  TypeBound ::= extends ClassOrInterfaceType AdditionalBoundListopt
     *</b>
     */
    struct TypeBound :public Ast
    {
        IAst *_extends;
        IAst *_ClassOrInterfaceType;
        IAst *_AdditionalBoundListopt;

        IAst *getextends() { return _extends; };
        void setextends(IAst *_extends) { this->_extends = _extends; }
        IAst *getClassOrInterfaceType() { return _ClassOrInterfaceType; };
        void setClassOrInterfaceType(IAst *_ClassOrInterfaceType) { this->_ClassOrInterfaceType = _ClassOrInterfaceType; }
        /**
         * The value returned by <b>getAdditionalBoundListopt</b> may be <b>nullptr</b>
         */
        IAst *getAdditionalBoundListopt() { return _AdditionalBoundListopt; };
        void setAdditionalBoundListopt(IAst *_AdditionalBoundListopt) { this->_AdditionalBoundListopt = _AdditionalBoundListopt; }

        TypeBound(IToken* leftIToken, IToken* rightIToken,
                  IAst *_extends,
                  IAst *_ClassOrInterfaceType,
                  IAst *_AdditionalBoundListopt):Ast(leftIToken, rightIToken)    {
            this->_extends = _extends;
            ((Ast*) _extends)->setParent(this);
            this->_ClassOrInterfaceType = _ClassOrInterfaceType;
            ((Ast*) _ClassOrInterfaceType)->setParent(this);
            this->_AdditionalBoundListopt = _AdditionalBoundListopt;
            if (_AdditionalBoundListopt != nullptr) ((Ast*) _AdditionalBoundListopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_extends);
            list.push_back(_ClassOrInterfaceType);
            list.push_back(_AdditionalBoundListopt);
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
                _extends->accept(v);
                _ClassOrInterfaceType->accept(v);
                if (_AdditionalBoundListopt != nullptr) _AdditionalBoundListopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 36:  AdditionalBoundList ::= AdditionalBound
     *</em>
     *<p>
     *<b>
     *<li>Rule 37:  AdditionalBoundList ::= AdditionalBoundList AdditionalBound
     *</b>
     */
    struct AdditionalBoundList :public Ast
    {
        IAst *_AdditionalBoundList;
        IAst *_AdditionalBound;

        IAst *getAdditionalBoundList() { return _AdditionalBoundList; };
        void setAdditionalBoundList(IAst *_AdditionalBoundList) { this->_AdditionalBoundList = _AdditionalBoundList; }
        IAst *getAdditionalBound() { return _AdditionalBound; };
        void setAdditionalBound(IAst *_AdditionalBound) { this->_AdditionalBound = _AdditionalBound; }

        AdditionalBoundList(IToken* leftIToken, IToken* rightIToken,
                            IAst *_AdditionalBoundList,
                            IAst *_AdditionalBound):Ast(leftIToken, rightIToken)    {
            this->_AdditionalBoundList = _AdditionalBoundList;
            ((Ast*) _AdditionalBoundList)->setParent(this);
            this->_AdditionalBound = _AdditionalBound;
            ((Ast*) _AdditionalBound)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AdditionalBoundList);
            list.push_back(_AdditionalBound);
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
                _AdditionalBoundList->accept(v);
                _AdditionalBound->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 38:  AdditionalBound ::= & InterfaceType
     *</b>
     */
    struct AdditionalBound :public Ast
    {
        IAst *_AND;
        IAst *_InterfaceType;

        IAst *getAND() { return _AND; };
        void setAND(IAst *_AND) { this->_AND = _AND; }
        IAst *getInterfaceType() { return _InterfaceType; };
        void setInterfaceType(IAst *_InterfaceType) { this->_InterfaceType = _InterfaceType; }

        AdditionalBound(IToken* leftIToken, IToken* rightIToken,
                        IAst *_AND,
                        IAst *_InterfaceType):Ast(leftIToken, rightIToken)    {
            this->_AND = _AND;
            ((Ast*) _AND)->setParent(this);
            this->_InterfaceType = _InterfaceType;
            ((Ast*) _InterfaceType)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AND);
            list.push_back(_InterfaceType);
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
                _AND->accept(v);
                _InterfaceType->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 39:  TypeArguments ::= < ActualTypeArgumentList >
     *</b>
     */
    struct TypeArguments :public Ast
    {
        IAst *_LESS;
        IAst *_ActualTypeArgumentList;
        IAst *_GREATER;

        IAst *getLESS() { return _LESS; };
        void setLESS(IAst *_LESS) { this->_LESS = _LESS; }
        IAst *getActualTypeArgumentList() { return _ActualTypeArgumentList; };
        void setActualTypeArgumentList(IAst *_ActualTypeArgumentList) { this->_ActualTypeArgumentList = _ActualTypeArgumentList; }
        IAst *getGREATER() { return _GREATER; };
        void setGREATER(IAst *_GREATER) { this->_GREATER = _GREATER; }

        TypeArguments(IToken* leftIToken, IToken* rightIToken,
                      IAst *_LESS,
                      IAst *_ActualTypeArgumentList,
                      IAst *_GREATER):Ast(leftIToken, rightIToken)    {
            this->_LESS = _LESS;
            ((Ast*) _LESS)->setParent(this);
            this->_ActualTypeArgumentList = _ActualTypeArgumentList;
            ((Ast*) _ActualTypeArgumentList)->setParent(this);
            this->_GREATER = _GREATER;
            ((Ast*) _GREATER)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LESS);
            list.push_back(_ActualTypeArgumentList);
            list.push_back(_GREATER);
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
                _LESS->accept(v);
                _ActualTypeArgumentList->accept(v);
                _GREATER->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 40:  ActualTypeArgumentList ::= ActualTypeArgument
     *</em>
     *<p>
     *<b>
     *<li>Rule 41:  ActualTypeArgumentList ::= ActualTypeArgumentList , ActualTypeArgument
     *</b>
     */
    struct ActualTypeArgumentList :public Ast
    {
        IAst *_ActualTypeArgumentList;
        IAst *_COMMA;
        IAst *_ActualTypeArgument;

        IAst *getActualTypeArgumentList() { return _ActualTypeArgumentList; };
        void setActualTypeArgumentList(IAst *_ActualTypeArgumentList) { this->_ActualTypeArgumentList = _ActualTypeArgumentList; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getActualTypeArgument() { return _ActualTypeArgument; };
        void setActualTypeArgument(IAst *_ActualTypeArgument) { this->_ActualTypeArgument = _ActualTypeArgument; }

        ActualTypeArgumentList(IToken* leftIToken, IToken* rightIToken,
                               IAst *_ActualTypeArgumentList,
                               IAst *_COMMA,
                               IAst *_ActualTypeArgument):Ast(leftIToken, rightIToken)    {
            this->_ActualTypeArgumentList = _ActualTypeArgumentList;
            ((Ast*) _ActualTypeArgumentList)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_ActualTypeArgument = _ActualTypeArgument;
            ((Ast*) _ActualTypeArgument)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ActualTypeArgumentList);
            list.push_back(_COMMA);
            list.push_back(_ActualTypeArgument);
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
                _ActualTypeArgumentList->accept(v);
                _COMMA->accept(v);
                _ActualTypeArgument->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 44:  Wildcard ::= ? WildcardBoundsOpt
     *</b>
     */
    struct Wildcard :public Ast
    {
        IAst *_QUESTION;
        IAst *_WildcardBoundsOpt;

        IAst *getQUESTION() { return _QUESTION; };
        void setQUESTION(IAst *_QUESTION) { this->_QUESTION = _QUESTION; }
        /**
         * The value returned by <b>getWildcardBoundsOpt</b> may be <b>nullptr</b>
         */
        IAst *getWildcardBoundsOpt() { return _WildcardBoundsOpt; };
        void setWildcardBoundsOpt(IAst *_WildcardBoundsOpt) { this->_WildcardBoundsOpt = _WildcardBoundsOpt; }

        Wildcard(IToken* leftIToken, IToken* rightIToken,
                 IAst *_QUESTION,
                 IAst *_WildcardBoundsOpt):Ast(leftIToken, rightIToken)    {
            this->_QUESTION = _QUESTION;
            ((Ast*) _QUESTION)->setParent(this);
            this->_WildcardBoundsOpt = _WildcardBoundsOpt;
            if (_WildcardBoundsOpt != nullptr) ((Ast*) _WildcardBoundsOpt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_QUESTION);
            list.push_back(_WildcardBoundsOpt);
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
                _QUESTION->accept(v);
                if (_WildcardBoundsOpt != nullptr) _WildcardBoundsOpt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 47:  PackageName ::= identifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 48:  PackageName ::= PackageName . identifier
     *</b>
     */
    struct PackageName :public Ast
    {
        IAst *_PackageName;
        IAst *_DOT;
        IAst *_identifier;

        IAst *getPackageName() { return _PackageName; };
        void setPackageName(IAst *_PackageName) { this->_PackageName = _PackageName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }

        PackageName(IToken* leftIToken, IToken* rightIToken,
                    IAst *_PackageName,
                    IAst *_DOT,
                    IAst *_identifier):Ast(leftIToken, rightIToken)    {
            this->_PackageName = _PackageName;
            ((Ast*) _PackageName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_PackageName);
            list.push_back(_DOT);
            list.push_back(_identifier);
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
                _PackageName->accept(v);
                _DOT->accept(v);
                _identifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 49:  ExpressionName ::= identifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 50:  ExpressionName ::= AmbiguousName . identifier
     *</b>
     */
    struct ExpressionName :public Ast
    {
        IAst *_AmbiguousName;
        IAst *_DOT;
        IAst *_identifier;

        IAst *getAmbiguousName() { return _AmbiguousName; };
        void setAmbiguousName(IAst *_AmbiguousName) { this->_AmbiguousName = _AmbiguousName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }

        ExpressionName(IToken* leftIToken, IToken* rightIToken,
                       IAst *_AmbiguousName,
                       IAst *_DOT,
                       IAst *_identifier):Ast(leftIToken, rightIToken)    {
            this->_AmbiguousName = _AmbiguousName;
            ((Ast*) _AmbiguousName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AmbiguousName);
            list.push_back(_DOT);
            list.push_back(_identifier);
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
                _AmbiguousName->accept(v);
                _DOT->accept(v);
                _identifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 51:  MethodName ::= identifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 52:  MethodName ::= AmbiguousName . identifier
     *</b>
     */
    struct MethodName :public Ast
    {
        IAst *_AmbiguousName;
        IAst *_DOT;
        IAst *_identifier;

        IAst *getAmbiguousName() { return _AmbiguousName; };
        void setAmbiguousName(IAst *_AmbiguousName) { this->_AmbiguousName = _AmbiguousName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }

        MethodName(IToken* leftIToken, IToken* rightIToken,
                   IAst *_AmbiguousName,
                   IAst *_DOT,
                   IAst *_identifier):Ast(leftIToken, rightIToken)    {
            this->_AmbiguousName = _AmbiguousName;
            ((Ast*) _AmbiguousName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AmbiguousName);
            list.push_back(_DOT);
            list.push_back(_identifier);
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
                _AmbiguousName->accept(v);
                _DOT->accept(v);
                _identifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 53:  PackageOrTypeName ::= identifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 54:  PackageOrTypeName ::= PackageOrTypeName . identifier
     *</b>
     */
    struct PackageOrTypeName :public Ast
    {
        IAst *_PackageOrTypeName;
        IAst *_DOT;
        IAst *_identifier;

        IAst *getPackageOrTypeName() { return _PackageOrTypeName; };
        void setPackageOrTypeName(IAst *_PackageOrTypeName) { this->_PackageOrTypeName = _PackageOrTypeName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }

        PackageOrTypeName(IToken* leftIToken, IToken* rightIToken,
                          IAst *_PackageOrTypeName,
                          IAst *_DOT,
                          IAst *_identifier):Ast(leftIToken, rightIToken)    {
            this->_PackageOrTypeName = _PackageOrTypeName;
            ((Ast*) _PackageOrTypeName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_PackageOrTypeName);
            list.push_back(_DOT);
            list.push_back(_identifier);
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
                _PackageOrTypeName->accept(v);
                _DOT->accept(v);
                _identifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 55:  AmbiguousName ::= identifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 56:  AmbiguousName ::= AmbiguousName . identifier
     *</b>
     */
    struct AmbiguousName :public Ast
    {
        IAst *_AmbiguousName;
        IAst *_DOT;
        IAst *_identifier;

        IAst *getAmbiguousName() { return _AmbiguousName; };
        void setAmbiguousName(IAst *_AmbiguousName) { this->_AmbiguousName = _AmbiguousName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }

        AmbiguousName(IToken* leftIToken, IToken* rightIToken,
                      IAst *_AmbiguousName,
                      IAst *_DOT,
                      IAst *_identifier):Ast(leftIToken, rightIToken)    {
            this->_AmbiguousName = _AmbiguousName;
            ((Ast*) _AmbiguousName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AmbiguousName);
            list.push_back(_DOT);
            list.push_back(_identifier);
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
                _AmbiguousName->accept(v);
                _DOT->accept(v);
                _identifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 57:  CompilationUnit ::= PackageDeclarationopt ImportDeclarationsopt TypeDeclarationsopt
     *</b>
     */
    struct CompilationUnit :public Ast
    {
        IAst *_PackageDeclarationopt;
        IAst *_ImportDeclarationsopt;
        IAst *_TypeDeclarationsopt;

        /**
         * The value returned by <b>getPackageDeclarationopt</b> may be <b>nullptr</b>
         */
        IAst *getPackageDeclarationopt() { return _PackageDeclarationopt; };
        void setPackageDeclarationopt(IAst *_PackageDeclarationopt) { this->_PackageDeclarationopt = _PackageDeclarationopt; }
        /**
         * The value returned by <b>getImportDeclarationsopt</b> may be <b>nullptr</b>
         */
        IAst *getImportDeclarationsopt() { return _ImportDeclarationsopt; };
        void setImportDeclarationsopt(IAst *_ImportDeclarationsopt) { this->_ImportDeclarationsopt = _ImportDeclarationsopt; }
        /**
         * The value returned by <b>getTypeDeclarationsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeDeclarationsopt() { return _TypeDeclarationsopt; };
        void setTypeDeclarationsopt(IAst *_TypeDeclarationsopt) { this->_TypeDeclarationsopt = _TypeDeclarationsopt; }

        CompilationUnit(IToken* leftIToken, IToken* rightIToken,
                        IAst *_PackageDeclarationopt,
                        IAst *_ImportDeclarationsopt,
                        IAst *_TypeDeclarationsopt):Ast(leftIToken, rightIToken)    {
            this->_PackageDeclarationopt = _PackageDeclarationopt;
            if (_PackageDeclarationopt != nullptr) ((Ast*) _PackageDeclarationopt)->setParent(this);
            this->_ImportDeclarationsopt = _ImportDeclarationsopt;
            if (_ImportDeclarationsopt != nullptr) ((Ast*) _ImportDeclarationsopt)->setParent(this);
            this->_TypeDeclarationsopt = _TypeDeclarationsopt;
            if (_TypeDeclarationsopt != nullptr) ((Ast*) _TypeDeclarationsopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_PackageDeclarationopt);
            list.push_back(_ImportDeclarationsopt);
            list.push_back(_TypeDeclarationsopt);
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
                if (_PackageDeclarationopt != nullptr) _PackageDeclarationopt->accept(v);
                if (_ImportDeclarationsopt != nullptr) _ImportDeclarationsopt->accept(v);
                if (_TypeDeclarationsopt != nullptr) _TypeDeclarationsopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 58:  ImportDeclarations ::= ImportDeclaration
     *</em>
     *<p>
     *<b>
     *<li>Rule 59:  ImportDeclarations ::= ImportDeclarations ImportDeclaration
     *</b>
     */
    struct ImportDeclarations :public Ast
    {
        IAst *_ImportDeclarations;
        IAst *_ImportDeclaration;

        IAst *getImportDeclarations() { return _ImportDeclarations; };
        void setImportDeclarations(IAst *_ImportDeclarations) { this->_ImportDeclarations = _ImportDeclarations; }
        IAst *getImportDeclaration() { return _ImportDeclaration; };
        void setImportDeclaration(IAst *_ImportDeclaration) { this->_ImportDeclaration = _ImportDeclaration; }

        ImportDeclarations(IToken* leftIToken, IToken* rightIToken,
                           IAst *_ImportDeclarations,
                           IAst *_ImportDeclaration):Ast(leftIToken, rightIToken)    {
            this->_ImportDeclarations = _ImportDeclarations;
            ((Ast*) _ImportDeclarations)->setParent(this);
            this->_ImportDeclaration = _ImportDeclaration;
            ((Ast*) _ImportDeclaration)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ImportDeclarations);
            list.push_back(_ImportDeclaration);
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
                _ImportDeclarations->accept(v);
                _ImportDeclaration->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 60:  TypeDeclarations ::= TypeDeclaration
     *</em>
     *<p>
     *<b>
     *<li>Rule 61:  TypeDeclarations ::= TypeDeclarations TypeDeclaration
     *</b>
     */
    struct TypeDeclarations :public Ast
    {
        IAst *_TypeDeclarations;
        IAst *_TypeDeclaration;

        IAst *getTypeDeclarations() { return _TypeDeclarations; };
        void setTypeDeclarations(IAst *_TypeDeclarations) { this->_TypeDeclarations = _TypeDeclarations; }
        IAst *getTypeDeclaration() { return _TypeDeclaration; };
        void setTypeDeclaration(IAst *_TypeDeclaration) { this->_TypeDeclaration = _TypeDeclaration; }

        TypeDeclarations(IToken* leftIToken, IToken* rightIToken,
                         IAst *_TypeDeclarations,
                         IAst *_TypeDeclaration):Ast(leftIToken, rightIToken)    {
            this->_TypeDeclarations = _TypeDeclarations;
            ((Ast*) _TypeDeclarations)->setParent(this);
            this->_TypeDeclaration = _TypeDeclaration;
            ((Ast*) _TypeDeclaration)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeDeclarations);
            list.push_back(_TypeDeclaration);
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
                _TypeDeclarations->accept(v);
                _TypeDeclaration->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 62:  PackageDeclaration ::= Annotationsopt package PackageName ;
     *</b>
     */
    struct PackageDeclaration :public Ast
    {
        IAst *_Annotationsopt;
        IAst *_package;
        IAst *_PackageName;
        IAst *_SEMICOLON;

        /**
         * The value returned by <b>getAnnotationsopt</b> may be <b>nullptr</b>
         */
        IAst *getAnnotationsopt() { return _Annotationsopt; };
        void setAnnotationsopt(IAst *_Annotationsopt) { this->_Annotationsopt = _Annotationsopt; }
        IAst *getpackage() { return _package; };
        void setpackage(IAst *_package) { this->_package = _package; }
        IAst *getPackageName() { return _PackageName; };
        void setPackageName(IAst *_PackageName) { this->_PackageName = _PackageName; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        PackageDeclaration(IToken* leftIToken, IToken* rightIToken,
                           IAst *_Annotationsopt,
                           IAst *_package,
                           IAst *_PackageName,
                           IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_Annotationsopt = _Annotationsopt;
            if (_Annotationsopt != nullptr) ((Ast*) _Annotationsopt)->setParent(this);
            this->_package = _package;
            ((Ast*) _package)->setParent(this);
            this->_PackageName = _PackageName;
            ((Ast*) _PackageName)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Annotationsopt);
            list.push_back(_package);
            list.push_back(_PackageName);
            list.push_back(_SEMICOLON);
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
                if (_Annotationsopt != nullptr) _Annotationsopt->accept(v);
                _package->accept(v);
                _PackageName->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 67:  SingleTypeImportDeclaration ::= import TypeName ;
     *</b>
     */
    struct SingleTypeImportDeclaration :public Ast
    {
        IAst *_import;
        IAst *_TypeName;
        IAst *_SEMICOLON;

        IAst *getimport() { return _import; };
        void setimport(IAst *_import) { this->_import = _import; }
        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        SingleTypeImportDeclaration(IToken* leftIToken, IToken* rightIToken,
                                    IAst *_import,
                                    IAst *_TypeName,
                                    IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_import = _import;
            ((Ast*) _import)->setParent(this);
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_import);
            list.push_back(_TypeName);
            list.push_back(_SEMICOLON);
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
                _import->accept(v);
                _TypeName->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 68:  TypeImportOnDemandDeclaration ::= import PackageOrTypeName . * ;
     *</b>
     */
    struct TypeImportOnDemandDeclaration :public Ast
    {
        IAst *_import;
        IAst *_PackageOrTypeName;
        IAst *_DOT;
        IAst *_MULTIPLY;
        IAst *_SEMICOLON;

        IAst *getimport() { return _import; };
        void setimport(IAst *_import) { this->_import = _import; }
        IAst *getPackageOrTypeName() { return _PackageOrTypeName; };
        void setPackageOrTypeName(IAst *_PackageOrTypeName) { this->_PackageOrTypeName = _PackageOrTypeName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getMULTIPLY() { return _MULTIPLY; };
        void setMULTIPLY(IAst *_MULTIPLY) { this->_MULTIPLY = _MULTIPLY; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        TypeImportOnDemandDeclaration(IToken* leftIToken, IToken* rightIToken,
                                      IAst *_import,
                                      IAst *_PackageOrTypeName,
                                      IAst *_DOT,
                                      IAst *_MULTIPLY,
                                      IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_import = _import;
            ((Ast*) _import)->setParent(this);
            this->_PackageOrTypeName = _PackageOrTypeName;
            ((Ast*) _PackageOrTypeName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_MULTIPLY = _MULTIPLY;
            ((Ast*) _MULTIPLY)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_import);
            list.push_back(_PackageOrTypeName);
            list.push_back(_DOT);
            list.push_back(_MULTIPLY);
            list.push_back(_SEMICOLON);
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
                _import->accept(v);
                _PackageOrTypeName->accept(v);
                _DOT->accept(v);
                _MULTIPLY->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 69:  SingleStaticImportDeclaration ::= import static TypeName . identifier ;
     *</b>
     */
    struct SingleStaticImportDeclaration :public Ast
    {
        IAst *_import;
        IAst *_static;
        IAst *_TypeName;
        IAst *_DOT;
        IAst *_identifier;
        IAst *_SEMICOLON;

        IAst *getimport() { return _import; };
        void setimport(IAst *_import) { this->_import = _import; }
        IAst *getstatic() { return _static; };
        void setstatic(IAst *_static) { this->_static = _static; }
        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        SingleStaticImportDeclaration(IToken* leftIToken, IToken* rightIToken,
                                      IAst *_import,
                                      IAst *_static,
                                      IAst *_TypeName,
                                      IAst *_DOT,
                                      IAst *_identifier,
                                      IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_import = _import;
            ((Ast*) _import)->setParent(this);
            this->_static = _static;
            ((Ast*) _static)->setParent(this);
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_import);
            list.push_back(_static);
            list.push_back(_TypeName);
            list.push_back(_DOT);
            list.push_back(_identifier);
            list.push_back(_SEMICOLON);
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
                _import->accept(v);
                _static->accept(v);
                _TypeName->accept(v);
                _DOT->accept(v);
                _identifier->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 70:  StaticImportOnDemandDeclaration ::= import static TypeName . * ;
     *</b>
     */
    struct StaticImportOnDemandDeclaration :public Ast
    {
        IAst *_import;
        IAst *_static;
        IAst *_TypeName;
        IAst *_DOT;
        IAst *_MULTIPLY;
        IAst *_SEMICOLON;

        IAst *getimport() { return _import; };
        void setimport(IAst *_import) { this->_import = _import; }
        IAst *getstatic() { return _static; };
        void setstatic(IAst *_static) { this->_static = _static; }
        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getMULTIPLY() { return _MULTIPLY; };
        void setMULTIPLY(IAst *_MULTIPLY) { this->_MULTIPLY = _MULTIPLY; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        StaticImportOnDemandDeclaration(IToken* leftIToken, IToken* rightIToken,
                                        IAst *_import,
                                        IAst *_static,
                                        IAst *_TypeName,
                                        IAst *_DOT,
                                        IAst *_MULTIPLY,
                                        IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_import = _import;
            ((Ast*) _import)->setParent(this);
            this->_static = _static;
            ((Ast*) _static)->setParent(this);
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_MULTIPLY = _MULTIPLY;
            ((Ast*) _MULTIPLY)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_import);
            list.push_back(_static);
            list.push_back(_TypeName);
            list.push_back(_DOT);
            list.push_back(_MULTIPLY);
            list.push_back(_SEMICOLON);
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
                _import->accept(v);
                _static->accept(v);
                _TypeName->accept(v);
                _DOT->accept(v);
                _MULTIPLY->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 71:  TypeDeclaration ::= ClassDeclaration
     *<li>Rule 72:  TypeDeclaration ::= InterfaceDeclaration
     *</em>
     *<p>
     *<b>
     *<li>Rule 73:  TypeDeclaration ::= ;
     *</b>
     */
    struct TypeDeclaration :public AstToken
    {
        IToken* getSEMICOLON() { return leftIToken; }

        TypeDeclaration(IToken* token) :AstToken(token)
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
     *<li>Rule 76:  NormalClassDeclaration ::= ClassModifiersopt class identifier TypeParametersopt Superopt Interfacesopt ClassBody
     *</b>
     */
    struct NormalClassDeclaration :public Ast
    {
        IAst *_ClassModifiersopt;
        IAst *_class;
        IAst *_identifier;
        IAst *_TypeParametersopt;
        IAst *_Superopt;
        IAst *_Interfacesopt;
        IAst *_ClassBody;

        /**
         * The value returned by <b>getClassModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getClassModifiersopt() { return _ClassModifiersopt; };
        void setClassModifiersopt(IAst *_ClassModifiersopt) { this->_ClassModifiersopt = _ClassModifiersopt; }
        IAst *getclass() { return _class; };
        void setclass(IAst *_class) { this->_class = _class; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        /**
         * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeParametersopt() { return _TypeParametersopt; };
        void setTypeParametersopt(IAst *_TypeParametersopt) { this->_TypeParametersopt = _TypeParametersopt; }
        /**
         * The value returned by <b>getSuperopt</b> may be <b>nullptr</b>
         */
        IAst *getSuperopt() { return _Superopt; };
        void setSuperopt(IAst *_Superopt) { this->_Superopt = _Superopt; }
        /**
         * The value returned by <b>getInterfacesopt</b> may be <b>nullptr</b>
         */
        IAst *getInterfacesopt() { return _Interfacesopt; };
        void setInterfacesopt(IAst *_Interfacesopt) { this->_Interfacesopt = _Interfacesopt; }
        IAst *getClassBody() { return _ClassBody; };
        void setClassBody(IAst *_ClassBody) { this->_ClassBody = _ClassBody; }

        NormalClassDeclaration(IToken* leftIToken, IToken* rightIToken,
                               IAst *_ClassModifiersopt,
                               IAst *_class,
                               IAst *_identifier,
                               IAst *_TypeParametersopt,
                               IAst *_Superopt,
                               IAst *_Interfacesopt,
                               IAst *_ClassBody):Ast(leftIToken, rightIToken)    {
            this->_ClassModifiersopt = _ClassModifiersopt;
            if (_ClassModifiersopt != nullptr) ((Ast*) _ClassModifiersopt)->setParent(this);
            this->_class = _class;
            ((Ast*) _class)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_TypeParametersopt = _TypeParametersopt;
            if (_TypeParametersopt != nullptr) ((Ast*) _TypeParametersopt)->setParent(this);
            this->_Superopt = _Superopt;
            if (_Superopt != nullptr) ((Ast*) _Superopt)->setParent(this);
            this->_Interfacesopt = _Interfacesopt;
            if (_Interfacesopt != nullptr) ((Ast*) _Interfacesopt)->setParent(this);
            this->_ClassBody = _ClassBody;
            ((Ast*) _ClassBody)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ClassModifiersopt);
            list.push_back(_class);
            list.push_back(_identifier);
            list.push_back(_TypeParametersopt);
            list.push_back(_Superopt);
            list.push_back(_Interfacesopt);
            list.push_back(_ClassBody);
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
                if (_ClassModifiersopt != nullptr) _ClassModifiersopt->accept(v);
                _class->accept(v);
                _identifier->accept(v);
                if (_TypeParametersopt != nullptr) _TypeParametersopt->accept(v);
                if (_Superopt != nullptr) _Superopt->accept(v);
                if (_Interfacesopt != nullptr) _Interfacesopt->accept(v);
                _ClassBody->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 77:  ClassModifiers ::= ClassModifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 78:  ClassModifiers ::= ClassModifiers ClassModifier
     *</b>
     */
    struct ClassModifiers :public Ast
    {
        IAst *_ClassModifiers;
        IAst *_ClassModifier;

        IAst *getClassModifiers() { return _ClassModifiers; };
        void setClassModifiers(IAst *_ClassModifiers) { this->_ClassModifiers = _ClassModifiers; }
        IAst *getClassModifier() { return _ClassModifier; };
        void setClassModifier(IAst *_ClassModifier) { this->_ClassModifier = _ClassModifier; }

        ClassModifiers(IToken* leftIToken, IToken* rightIToken,
                       IAst *_ClassModifiers,
                       IAst *_ClassModifier):Ast(leftIToken, rightIToken)    {
            this->_ClassModifiers = _ClassModifiers;
            ((Ast*) _ClassModifiers)->setParent(this);
            this->_ClassModifier = _ClassModifier;
            ((Ast*) _ClassModifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ClassModifiers);
            list.push_back(_ClassModifier);
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
                _ClassModifiers->accept(v);
                _ClassModifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 87:  TypeParameters ::= < TypeParameterList >
     *</b>
     */
    struct TypeParameters :public Ast
    {
        IAst *_LESS;
        IAst *_TypeParameterList;
        IAst *_GREATER;

        IAst *getLESS() { return _LESS; };
        void setLESS(IAst *_LESS) { this->_LESS = _LESS; }
        IAst *getTypeParameterList() { return _TypeParameterList; };
        void setTypeParameterList(IAst *_TypeParameterList) { this->_TypeParameterList = _TypeParameterList; }
        IAst *getGREATER() { return _GREATER; };
        void setGREATER(IAst *_GREATER) { this->_GREATER = _GREATER; }

        TypeParameters(IToken* leftIToken, IToken* rightIToken,
                       IAst *_LESS,
                       IAst *_TypeParameterList,
                       IAst *_GREATER):Ast(leftIToken, rightIToken)    {
            this->_LESS = _LESS;
            ((Ast*) _LESS)->setParent(this);
            this->_TypeParameterList = _TypeParameterList;
            ((Ast*) _TypeParameterList)->setParent(this);
            this->_GREATER = _GREATER;
            ((Ast*) _GREATER)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LESS);
            list.push_back(_TypeParameterList);
            list.push_back(_GREATER);
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
                _LESS->accept(v);
                _TypeParameterList->accept(v);
                _GREATER->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 88:  TypeParameterList ::= TypeParameter
     *</em>
     *<p>
     *<b>
     *<li>Rule 89:  TypeParameterList ::= TypeParameterList , TypeParameter
     *</b>
     */
    struct TypeParameterList :public Ast
    {
        IAst *_TypeParameterList;
        IAst *_COMMA;
        IAst *_TypeParameter;

        IAst *getTypeParameterList() { return _TypeParameterList; };
        void setTypeParameterList(IAst *_TypeParameterList) { this->_TypeParameterList = _TypeParameterList; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getTypeParameter() { return _TypeParameter; };
        void setTypeParameter(IAst *_TypeParameter) { this->_TypeParameter = _TypeParameter; }

        TypeParameterList(IToken* leftIToken, IToken* rightIToken,
                          IAst *_TypeParameterList,
                          IAst *_COMMA,
                          IAst *_TypeParameter):Ast(leftIToken, rightIToken)    {
            this->_TypeParameterList = _TypeParameterList;
            ((Ast*) _TypeParameterList)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_TypeParameter = _TypeParameter;
            ((Ast*) _TypeParameter)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeParameterList);
            list.push_back(_COMMA);
            list.push_back(_TypeParameter);
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
                _TypeParameterList->accept(v);
                _COMMA->accept(v);
                _TypeParameter->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 90:  Super ::= extends ClassType
     *</b>
     */
    struct Super :public Ast
    {
        IAst *_extends;
        IAst *_ClassType;

        IAst *getextends() { return _extends; };
        void setextends(IAst *_extends) { this->_extends = _extends; }
        IAst *getClassType() { return _ClassType; };
        void setClassType(IAst *_ClassType) { this->_ClassType = _ClassType; }

        Super(IToken* leftIToken, IToken* rightIToken,
              IAst *_extends,
              IAst *_ClassType):Ast(leftIToken, rightIToken)    {
            this->_extends = _extends;
            ((Ast*) _extends)->setParent(this);
            this->_ClassType = _ClassType;
            ((Ast*) _ClassType)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_extends);
            list.push_back(_ClassType);
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
                _extends->accept(v);
                _ClassType->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 91:  Interfaces ::= implements InterfaceTypeList
     *</b>
     */
    struct Interfaces :public Ast
    {
        IAst *_implements;
        IAst *_InterfaceTypeList;

        IAst *getimplements() { return _implements; };
        void setimplements(IAst *_implements) { this->_implements = _implements; }
        IAst *getInterfaceTypeList() { return _InterfaceTypeList; };
        void setInterfaceTypeList(IAst *_InterfaceTypeList) { this->_InterfaceTypeList = _InterfaceTypeList; }

        Interfaces(IToken* leftIToken, IToken* rightIToken,
                   IAst *_implements,
                   IAst *_InterfaceTypeList):Ast(leftIToken, rightIToken)    {
            this->_implements = _implements;
            ((Ast*) _implements)->setParent(this);
            this->_InterfaceTypeList = _InterfaceTypeList;
            ((Ast*) _InterfaceTypeList)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_implements);
            list.push_back(_InterfaceTypeList);
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
                _implements->accept(v);
                _InterfaceTypeList->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 92:  InterfaceTypeList ::= InterfaceType
     *</em>
     *<p>
     *<b>
     *<li>Rule 93:  InterfaceTypeList ::= InterfaceTypeList , InterfaceType
     *</b>
     */
    struct InterfaceTypeList :public Ast
    {
        IAst *_InterfaceTypeList;
        IAst *_COMMA;
        IAst *_InterfaceType;

        IAst *getInterfaceTypeList() { return _InterfaceTypeList; };
        void setInterfaceTypeList(IAst *_InterfaceTypeList) { this->_InterfaceTypeList = _InterfaceTypeList; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getInterfaceType() { return _InterfaceType; };
        void setInterfaceType(IAst *_InterfaceType) { this->_InterfaceType = _InterfaceType; }

        InterfaceTypeList(IToken* leftIToken, IToken* rightIToken,
                          IAst *_InterfaceTypeList,
                          IAst *_COMMA,
                          IAst *_InterfaceType):Ast(leftIToken, rightIToken)    {
            this->_InterfaceTypeList = _InterfaceTypeList;
            ((Ast*) _InterfaceTypeList)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_InterfaceType = _InterfaceType;
            ((Ast*) _InterfaceType)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_InterfaceTypeList);
            list.push_back(_COMMA);
            list.push_back(_InterfaceType);
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
                _InterfaceTypeList->accept(v);
                _COMMA->accept(v);
                _InterfaceType->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 94:  ClassBody ::= { ClassBodyDeclarationsopt }
     *</b>
     */
    struct ClassBody :public Ast
    {
        IAst *_LBRACE;
        IAst *_ClassBodyDeclarationsopt;
        IAst *_RBRACE;

        IAst *getLBRACE() { return _LBRACE; };
        void setLBRACE(IAst *_LBRACE) { this->_LBRACE = _LBRACE; }
        /**
         * The value returned by <b>getClassBodyDeclarationsopt</b> may be <b>nullptr</b>
         */
        IAst *getClassBodyDeclarationsopt() { return _ClassBodyDeclarationsopt; };
        void setClassBodyDeclarationsopt(IAst *_ClassBodyDeclarationsopt) { this->_ClassBodyDeclarationsopt = _ClassBodyDeclarationsopt; }
        IAst *getRBRACE() { return _RBRACE; };
        void setRBRACE(IAst *_RBRACE) { this->_RBRACE = _RBRACE; }

        ClassBody(IToken* leftIToken, IToken* rightIToken,
                  IAst *_LBRACE,
                  IAst *_ClassBodyDeclarationsopt,
                  IAst *_RBRACE):Ast(leftIToken, rightIToken)    {
            this->_LBRACE = _LBRACE;
            ((Ast*) _LBRACE)->setParent(this);
            this->_ClassBodyDeclarationsopt = _ClassBodyDeclarationsopt;
            if (_ClassBodyDeclarationsopt != nullptr) ((Ast*) _ClassBodyDeclarationsopt)->setParent(this);
            this->_RBRACE = _RBRACE;
            ((Ast*) _RBRACE)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACE);
            list.push_back(_ClassBodyDeclarationsopt);
            list.push_back(_RBRACE);
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
                _LBRACE->accept(v);
                if (_ClassBodyDeclarationsopt != nullptr) _ClassBodyDeclarationsopt->accept(v);
                _RBRACE->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 95:  ClassBodyDeclarations ::= ClassBodyDeclaration
     *</em>
     *<p>
     *<b>
     *<li>Rule 96:  ClassBodyDeclarations ::= ClassBodyDeclarations ClassBodyDeclaration
     *</b>
     */
    struct ClassBodyDeclarations :public Ast
    {
        IAst *_ClassBodyDeclarations;
        IAst *_ClassBodyDeclaration;

        IAst *getClassBodyDeclarations() { return _ClassBodyDeclarations; };
        void setClassBodyDeclarations(IAst *_ClassBodyDeclarations) { this->_ClassBodyDeclarations = _ClassBodyDeclarations; }
        IAst *getClassBodyDeclaration() { return _ClassBodyDeclaration; };
        void setClassBodyDeclaration(IAst *_ClassBodyDeclaration) { this->_ClassBodyDeclaration = _ClassBodyDeclaration; }

        ClassBodyDeclarations(IToken* leftIToken, IToken* rightIToken,
                              IAst *_ClassBodyDeclarations,
                              IAst *_ClassBodyDeclaration):Ast(leftIToken, rightIToken)    {
            this->_ClassBodyDeclarations = _ClassBodyDeclarations;
            ((Ast*) _ClassBodyDeclarations)->setParent(this);
            this->_ClassBodyDeclaration = _ClassBodyDeclaration;
            ((Ast*) _ClassBodyDeclaration)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ClassBodyDeclarations);
            list.push_back(_ClassBodyDeclaration);
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
                _ClassBodyDeclarations->accept(v);
                _ClassBodyDeclaration->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 101:  ClassMemberDeclaration ::= FieldDeclaration
     *<li>Rule 102:  ClassMemberDeclaration ::= MethodDeclaration
     *<li>Rule 103:  ClassMemberDeclaration ::= ClassDeclaration
     *<li>Rule 104:  ClassMemberDeclaration ::= InterfaceDeclaration
     *</em>
     *<p>
     *<b>
     *<li>Rule 105:  ClassMemberDeclaration ::= ;
     *</b>
     */
    struct ClassMemberDeclaration :public AstToken
    {
        IToken* getSEMICOLON() { return leftIToken; }

        ClassMemberDeclaration(IToken* token) :AstToken(token)
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
     *<li>Rule 106:  FieldDeclaration ::= FieldModifiersopt Type VariableDeclarators ;
     *</b>
     */
    struct FieldDeclaration :public Ast
    {
        IAst *_FieldModifiersopt;
        IAst *_Type;
        IAst *_VariableDeclarators;
        IAst *_SEMICOLON;

        /**
         * The value returned by <b>getFieldModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getFieldModifiersopt() { return _FieldModifiersopt; };
        void setFieldModifiersopt(IAst *_FieldModifiersopt) { this->_FieldModifiersopt = _FieldModifiersopt; }
        IAst *getType() { return _Type; };
        void setType(IAst *_Type) { this->_Type = _Type; }
        IAst *getVariableDeclarators() { return _VariableDeclarators; };
        void setVariableDeclarators(IAst *_VariableDeclarators) { this->_VariableDeclarators = _VariableDeclarators; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        FieldDeclaration(IToken* leftIToken, IToken* rightIToken,
                         IAst *_FieldModifiersopt,
                         IAst *_Type,
                         IAst *_VariableDeclarators,
                         IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_FieldModifiersopt = _FieldModifiersopt;
            if (_FieldModifiersopt != nullptr) ((Ast*) _FieldModifiersopt)->setParent(this);
            this->_Type = _Type;
            ((Ast*) _Type)->setParent(this);
            this->_VariableDeclarators = _VariableDeclarators;
            ((Ast*) _VariableDeclarators)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_FieldModifiersopt);
            list.push_back(_Type);
            list.push_back(_VariableDeclarators);
            list.push_back(_SEMICOLON);
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
                if (_FieldModifiersopt != nullptr) _FieldModifiersopt->accept(v);
                _Type->accept(v);
                _VariableDeclarators->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 107:  VariableDeclarators ::= VariableDeclarator
     *</em>
     *<p>
     *<b>
     *<li>Rule 108:  VariableDeclarators ::= VariableDeclarators , VariableDeclarator
     *</b>
     */
    struct VariableDeclarators :public Ast
    {
        IAst *_VariableDeclarators;
        IAst *_COMMA;
        IAst *_VariableDeclarator;

        IAst *getVariableDeclarators() { return _VariableDeclarators; };
        void setVariableDeclarators(IAst *_VariableDeclarators) { this->_VariableDeclarators = _VariableDeclarators; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getVariableDeclarator() { return _VariableDeclarator; };
        void setVariableDeclarator(IAst *_VariableDeclarator) { this->_VariableDeclarator = _VariableDeclarator; }

        VariableDeclarators(IToken* leftIToken, IToken* rightIToken,
                            IAst *_VariableDeclarators,
                            IAst *_COMMA,
                            IAst *_VariableDeclarator):Ast(leftIToken, rightIToken)    {
            this->_VariableDeclarators = _VariableDeclarators;
            ((Ast*) _VariableDeclarators)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_VariableDeclarator = _VariableDeclarator;
            ((Ast*) _VariableDeclarator)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_VariableDeclarators);
            list.push_back(_COMMA);
            list.push_back(_VariableDeclarator);
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
                _VariableDeclarators->accept(v);
                _COMMA->accept(v);
                _VariableDeclarator->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 109:  VariableDeclarator ::= VariableDeclaratorId
     *</em>
     *<p>
     *<b>
     *<li>Rule 110:  VariableDeclarator ::= VariableDeclaratorId = VariableInitializer
     *</b>
     */
    struct VariableDeclarator :public Ast
    {
        IAst *_VariableDeclaratorId;
        IAst *_EQUAL;
        IAst *_VariableInitializer;

        IAst *getVariableDeclaratorId() { return _VariableDeclaratorId; };
        void setVariableDeclaratorId(IAst *_VariableDeclaratorId) { this->_VariableDeclaratorId = _VariableDeclaratorId; }
        IAst *getEQUAL() { return _EQUAL; };
        void setEQUAL(IAst *_EQUAL) { this->_EQUAL = _EQUAL; }
        IAst *getVariableInitializer() { return _VariableInitializer; };
        void setVariableInitializer(IAst *_VariableInitializer) { this->_VariableInitializer = _VariableInitializer; }

        VariableDeclarator(IToken* leftIToken, IToken* rightIToken,
                           IAst *_VariableDeclaratorId,
                           IAst *_EQUAL,
                           IAst *_VariableInitializer):Ast(leftIToken, rightIToken)    {
            this->_VariableDeclaratorId = _VariableDeclaratorId;
            ((Ast*) _VariableDeclaratorId)->setParent(this);
            this->_EQUAL = _EQUAL;
            ((Ast*) _EQUAL)->setParent(this);
            this->_VariableInitializer = _VariableInitializer;
            ((Ast*) _VariableInitializer)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_VariableDeclaratorId);
            list.push_back(_EQUAL);
            list.push_back(_VariableInitializer);
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
                _VariableDeclaratorId->accept(v);
                _EQUAL->accept(v);
                _VariableInitializer->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 111:  VariableDeclaratorId ::= identifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 112:  VariableDeclaratorId ::= VariableDeclaratorId [ ]
     *</b>
     */
    struct VariableDeclaratorId :public Ast
    {
        IAst *_VariableDeclaratorId;
        IAst *_LBRACKET;
        IAst *_RBRACKET;

        IAst *getVariableDeclaratorId() { return _VariableDeclaratorId; };
        void setVariableDeclaratorId(IAst *_VariableDeclaratorId) { this->_VariableDeclaratorId = _VariableDeclaratorId; }
        IAst *getLBRACKET() { return _LBRACKET; };
        void setLBRACKET(IAst *_LBRACKET) { this->_LBRACKET = _LBRACKET; }
        IAst *getRBRACKET() { return _RBRACKET; };
        void setRBRACKET(IAst *_RBRACKET) { this->_RBRACKET = _RBRACKET; }

        VariableDeclaratorId(IToken* leftIToken, IToken* rightIToken,
                             IAst *_VariableDeclaratorId,
                             IAst *_LBRACKET,
                             IAst *_RBRACKET):Ast(leftIToken, rightIToken)    {
            this->_VariableDeclaratorId = _VariableDeclaratorId;
            ((Ast*) _VariableDeclaratorId)->setParent(this);
            this->_LBRACKET = _LBRACKET;
            ((Ast*) _LBRACKET)->setParent(this);
            this->_RBRACKET = _RBRACKET;
            ((Ast*) _RBRACKET)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_VariableDeclaratorId);
            list.push_back(_LBRACKET);
            list.push_back(_RBRACKET);
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
                _VariableDeclaratorId->accept(v);
                _LBRACKET->accept(v);
                _RBRACKET->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 115:  FieldModifiers ::= FieldModifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 116:  FieldModifiers ::= FieldModifiers FieldModifier
     *</b>
     */
    struct FieldModifiers :public Ast
    {
        IAst *_FieldModifiers;
        IAst *_FieldModifier;

        IAst *getFieldModifiers() { return _FieldModifiers; };
        void setFieldModifiers(IAst *_FieldModifiers) { this->_FieldModifiers = _FieldModifiers; }
        IAst *getFieldModifier() { return _FieldModifier; };
        void setFieldModifier(IAst *_FieldModifier) { this->_FieldModifier = _FieldModifier; }

        FieldModifiers(IToken* leftIToken, IToken* rightIToken,
                       IAst *_FieldModifiers,
                       IAst *_FieldModifier):Ast(leftIToken, rightIToken)    {
            this->_FieldModifiers = _FieldModifiers;
            ((Ast*) _FieldModifiers)->setParent(this);
            this->_FieldModifier = _FieldModifier;
            ((Ast*) _FieldModifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_FieldModifiers);
            list.push_back(_FieldModifier);
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
                _FieldModifiers->accept(v);
                _FieldModifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 125:  MethodDeclaration ::= MethodHeader MethodBody
     *</b>
     */
    struct MethodDeclaration :public Ast
    {
        IAst *_MethodHeader;
        IAst *_MethodBody;

        IAst *getMethodHeader() { return _MethodHeader; };
        void setMethodHeader(IAst *_MethodHeader) { this->_MethodHeader = _MethodHeader; }
        IAst *getMethodBody() { return _MethodBody; };
        void setMethodBody(IAst *_MethodBody) { this->_MethodBody = _MethodBody; }

        MethodDeclaration(IToken* leftIToken, IToken* rightIToken,
                          IAst *_MethodHeader,
                          IAst *_MethodBody):Ast(leftIToken, rightIToken)    {
            this->_MethodHeader = _MethodHeader;
            ((Ast*) _MethodHeader)->setParent(this);
            this->_MethodBody = _MethodBody;
            ((Ast*) _MethodBody)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MethodHeader);
            list.push_back(_MethodBody);
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
                _MethodHeader->accept(v);
                _MethodBody->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 126:  MethodHeader ::= MethodModifiersopt TypeParametersopt ResultType MethodDeclarator Throwsopt
     *</b>
     */
    struct MethodHeader :public Ast
    {
        IAst *_MethodModifiersopt;
        IAst *_TypeParametersopt;
        IAst *_ResultType;
        IAst *_MethodDeclarator;
        IAst *_Throwsopt;

        /**
         * The value returned by <b>getMethodModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getMethodModifiersopt() { return _MethodModifiersopt; };
        void setMethodModifiersopt(IAst *_MethodModifiersopt) { this->_MethodModifiersopt = _MethodModifiersopt; }
        /**
         * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeParametersopt() { return _TypeParametersopt; };
        void setTypeParametersopt(IAst *_TypeParametersopt) { this->_TypeParametersopt = _TypeParametersopt; }
        IAst *getResultType() { return _ResultType; };
        void setResultType(IAst *_ResultType) { this->_ResultType = _ResultType; }
        IAst *getMethodDeclarator() { return _MethodDeclarator; };
        void setMethodDeclarator(IAst *_MethodDeclarator) { this->_MethodDeclarator = _MethodDeclarator; }
        /**
         * The value returned by <b>getThrowsopt</b> may be <b>nullptr</b>
         */
        IAst *getThrowsopt() { return _Throwsopt; };
        void setThrowsopt(IAst *_Throwsopt) { this->_Throwsopt = _Throwsopt; }

        MethodHeader(IToken* leftIToken, IToken* rightIToken,
                     IAst *_MethodModifiersopt,
                     IAst *_TypeParametersopt,
                     IAst *_ResultType,
                     IAst *_MethodDeclarator,
                     IAst *_Throwsopt):Ast(leftIToken, rightIToken)    {
            this->_MethodModifiersopt = _MethodModifiersopt;
            if (_MethodModifiersopt != nullptr) ((Ast*) _MethodModifiersopt)->setParent(this);
            this->_TypeParametersopt = _TypeParametersopt;
            if (_TypeParametersopt != nullptr) ((Ast*) _TypeParametersopt)->setParent(this);
            this->_ResultType = _ResultType;
            ((Ast*) _ResultType)->setParent(this);
            this->_MethodDeclarator = _MethodDeclarator;
            ((Ast*) _MethodDeclarator)->setParent(this);
            this->_Throwsopt = _Throwsopt;
            if (_Throwsopt != nullptr) ((Ast*) _Throwsopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MethodModifiersopt);
            list.push_back(_TypeParametersopt);
            list.push_back(_ResultType);
            list.push_back(_MethodDeclarator);
            list.push_back(_Throwsopt);
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
                if (_MethodModifiersopt != nullptr) _MethodModifiersopt->accept(v);
                if (_TypeParametersopt != nullptr) _TypeParametersopt->accept(v);
                _ResultType->accept(v);
                _MethodDeclarator->accept(v);
                if (_Throwsopt != nullptr) _Throwsopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 127:  ResultType ::= Type
     *</em>
     *<p>
     *<b>
     *<li>Rule 128:  ResultType ::= void
     *</b>
     */
    struct ResultType :public AstToken
    {
        IToken* getvoid() { return leftIToken; }

        ResultType(IToken* token) :AstToken(token)
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
     *<em>
     *<li>Rule 131:  FormalParameterList ::= LastFormalParameter
     *</em>
     *<p>
     *<b>
     *<li>Rule 132:  FormalParameterList ::= FormalParameters , LastFormalParameter
     *</b>
     */
    struct FormalParameterList :public Ast
    {
        IAst *_FormalParameters;
        IAst *_COMMA;
        IAst *_LastFormalParameter;

        IAst *getFormalParameters() { return _FormalParameters; };
        void setFormalParameters(IAst *_FormalParameters) { this->_FormalParameters = _FormalParameters; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getLastFormalParameter() { return _LastFormalParameter; };
        void setLastFormalParameter(IAst *_LastFormalParameter) { this->_LastFormalParameter = _LastFormalParameter; }

        FormalParameterList(IToken* leftIToken, IToken* rightIToken,
                            IAst *_FormalParameters,
                            IAst *_COMMA,
                            IAst *_LastFormalParameter):Ast(leftIToken, rightIToken)    {
            this->_FormalParameters = _FormalParameters;
            ((Ast*) _FormalParameters)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_LastFormalParameter = _LastFormalParameter;
            ((Ast*) _LastFormalParameter)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_FormalParameters);
            list.push_back(_COMMA);
            list.push_back(_LastFormalParameter);
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
                _FormalParameters->accept(v);
                _COMMA->accept(v);
                _LastFormalParameter->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 133:  FormalParameters ::= FormalParameter
     *</em>
     *<p>
     *<b>
     *<li>Rule 134:  FormalParameters ::= FormalParameters , FormalParameter
     *</b>
     */
    struct FormalParameters :public Ast
    {
        IAst *_FormalParameters;
        IAst *_COMMA;
        IAst *_FormalParameter;

        IAst *getFormalParameters() { return _FormalParameters; };
        void setFormalParameters(IAst *_FormalParameters) { this->_FormalParameters = _FormalParameters; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getFormalParameter() { return _FormalParameter; };
        void setFormalParameter(IAst *_FormalParameter) { this->_FormalParameter = _FormalParameter; }

        FormalParameters(IToken* leftIToken, IToken* rightIToken,
                         IAst *_FormalParameters,
                         IAst *_COMMA,
                         IAst *_FormalParameter):Ast(leftIToken, rightIToken)    {
            this->_FormalParameters = _FormalParameters;
            ((Ast*) _FormalParameters)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_FormalParameter = _FormalParameter;
            ((Ast*) _FormalParameter)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_FormalParameters);
            list.push_back(_COMMA);
            list.push_back(_FormalParameter);
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
                _FormalParameters->accept(v);
                _COMMA->accept(v);
                _FormalParameter->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 135:  FormalParameter ::= VariableModifiersopt Type VariableDeclaratorId
     *</b>
     */
    struct FormalParameter :public Ast
    {
        IAst *_VariableModifiersopt;
        IAst *_Type;
        IAst *_VariableDeclaratorId;

        /**
         * The value returned by <b>getVariableModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getVariableModifiersopt() { return _VariableModifiersopt; };
        void setVariableModifiersopt(IAst *_VariableModifiersopt) { this->_VariableModifiersopt = _VariableModifiersopt; }
        IAst *getType() { return _Type; };
        void setType(IAst *_Type) { this->_Type = _Type; }
        IAst *getVariableDeclaratorId() { return _VariableDeclaratorId; };
        void setVariableDeclaratorId(IAst *_VariableDeclaratorId) { this->_VariableDeclaratorId = _VariableDeclaratorId; }

        FormalParameter(IToken* leftIToken, IToken* rightIToken,
                        IAst *_VariableModifiersopt,
                        IAst *_Type,
                        IAst *_VariableDeclaratorId):Ast(leftIToken, rightIToken)    {
            this->_VariableModifiersopt = _VariableModifiersopt;
            if (_VariableModifiersopt != nullptr) ((Ast*) _VariableModifiersopt)->setParent(this);
            this->_Type = _Type;
            ((Ast*) _Type)->setParent(this);
            this->_VariableDeclaratorId = _VariableDeclaratorId;
            ((Ast*) _VariableDeclaratorId)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_VariableModifiersopt);
            list.push_back(_Type);
            list.push_back(_VariableDeclaratorId);
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
                if (_VariableModifiersopt != nullptr) _VariableModifiersopt->accept(v);
                _Type->accept(v);
                _VariableDeclaratorId->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 136:  VariableModifiers ::= VariableModifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 137:  VariableModifiers ::= VariableModifiers VariableModifier
     *</b>
     */
    struct VariableModifiers :public Ast
    {
        IAst *_VariableModifiers;
        IAst *_VariableModifier;

        IAst *getVariableModifiers() { return _VariableModifiers; };
        void setVariableModifiers(IAst *_VariableModifiers) { this->_VariableModifiers = _VariableModifiers; }
        IAst *getVariableModifier() { return _VariableModifier; };
        void setVariableModifier(IAst *_VariableModifier) { this->_VariableModifier = _VariableModifier; }

        VariableModifiers(IToken* leftIToken, IToken* rightIToken,
                          IAst *_VariableModifiers,
                          IAst *_VariableModifier):Ast(leftIToken, rightIToken)    {
            this->_VariableModifiers = _VariableModifiers;
            ((Ast*) _VariableModifiers)->setParent(this);
            this->_VariableModifier = _VariableModifier;
            ((Ast*) _VariableModifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_VariableModifiers);
            list.push_back(_VariableModifier);
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
                _VariableModifiers->accept(v);
                _VariableModifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 139:  VariableModifier ::= Annotations
     *</em>
     *<p>
     *<b>
     *<li>Rule 138:  VariableModifier ::= final
     *</b>
     */
    struct VariableModifier :public AstToken
    {
        IToken* getfinal() { return leftIToken; }

        VariableModifier(IToken* token) :AstToken(token)
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
     *<li>Rule 140:  LastFormalParameter ::= VariableModifiersopt Type ...opt VariableDeclaratorId
     *</b>
     */
    struct LastFormalParameter :public Ast
    {
        IAst *_VariableModifiersopt;
        IAst *_Type;
        IAst *_Ellipsisopt;
        IAst *_VariableDeclaratorId;

        /**
         * The value returned by <b>getVariableModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getVariableModifiersopt() { return _VariableModifiersopt; };
        void setVariableModifiersopt(IAst *_VariableModifiersopt) { this->_VariableModifiersopt = _VariableModifiersopt; }
        IAst *getType() { return _Type; };
        void setType(IAst *_Type) { this->_Type = _Type; }
        /**
         * The value returned by <b>getEllipsisopt</b> may be <b>nullptr</b>
         */
        IAst *getEllipsisopt() { return _Ellipsisopt; };
        void setEllipsisopt(IAst *_Ellipsisopt) { this->_Ellipsisopt = _Ellipsisopt; }
        IAst *getVariableDeclaratorId() { return _VariableDeclaratorId; };
        void setVariableDeclaratorId(IAst *_VariableDeclaratorId) { this->_VariableDeclaratorId = _VariableDeclaratorId; }

        LastFormalParameter(IToken* leftIToken, IToken* rightIToken,
                            IAst *_VariableModifiersopt,
                            IAst *_Type,
                            IAst *_Ellipsisopt,
                            IAst *_VariableDeclaratorId):Ast(leftIToken, rightIToken)    {
            this->_VariableModifiersopt = _VariableModifiersopt;
            if (_VariableModifiersopt != nullptr) ((Ast*) _VariableModifiersopt)->setParent(this);
            this->_Type = _Type;
            ((Ast*) _Type)->setParent(this);
            this->_Ellipsisopt = _Ellipsisopt;
            if (_Ellipsisopt != nullptr) ((Ast*) _Ellipsisopt)->setParent(this);
            this->_VariableDeclaratorId = _VariableDeclaratorId;
            ((Ast*) _VariableDeclaratorId)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_VariableModifiersopt);
            list.push_back(_Type);
            list.push_back(_Ellipsisopt);
            list.push_back(_VariableDeclaratorId);
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
                if (_VariableModifiersopt != nullptr) _VariableModifiersopt->accept(v);
                _Type->accept(v);
                if (_Ellipsisopt != nullptr) _Ellipsisopt->accept(v);
                _VariableDeclaratorId->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 141:  MethodModifiers ::= MethodModifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 142:  MethodModifiers ::= MethodModifiers MethodModifier
     *</b>
     */
    struct MethodModifiers :public Ast
    {
        IAst *_MethodModifiers;
        IAst *_MethodModifier;

        IAst *getMethodModifiers() { return _MethodModifiers; };
        void setMethodModifiers(IAst *_MethodModifiers) { this->_MethodModifiers = _MethodModifiers; }
        IAst *getMethodModifier() { return _MethodModifier; };
        void setMethodModifier(IAst *_MethodModifier) { this->_MethodModifier = _MethodModifier; }

        MethodModifiers(IToken* leftIToken, IToken* rightIToken,
                        IAst *_MethodModifiers,
                        IAst *_MethodModifier):Ast(leftIToken, rightIToken)    {
            this->_MethodModifiers = _MethodModifiers;
            ((Ast*) _MethodModifiers)->setParent(this);
            this->_MethodModifier = _MethodModifier;
            ((Ast*) _MethodModifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MethodModifiers);
            list.push_back(_MethodModifier);
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
                _MethodModifiers->accept(v);
                _MethodModifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 153:  Throws ::= throws ExceptionTypeList
     *</b>
     */
    struct Throws :public Ast
    {
        IAst *_throws;
        IAst *_ExceptionTypeList;

        IAst *getthrows() { return _throws; };
        void setthrows(IAst *_throws) { this->_throws = _throws; }
        IAst *getExceptionTypeList() { return _ExceptionTypeList; };
        void setExceptionTypeList(IAst *_ExceptionTypeList) { this->_ExceptionTypeList = _ExceptionTypeList; }

        Throws(IToken* leftIToken, IToken* rightIToken,
               IAst *_throws,
               IAst *_ExceptionTypeList):Ast(leftIToken, rightIToken)    {
            this->_throws = _throws;
            ((Ast*) _throws)->setParent(this);
            this->_ExceptionTypeList = _ExceptionTypeList;
            ((Ast*) _ExceptionTypeList)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_throws);
            list.push_back(_ExceptionTypeList);
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
                _throws->accept(v);
                _ExceptionTypeList->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 154:  ExceptionTypeList ::= ExceptionType
     *</em>
     *<p>
     *<b>
     *<li>Rule 155:  ExceptionTypeList ::= ExceptionTypeList , ExceptionType
     *</b>
     */
    struct ExceptionTypeList :public Ast
    {
        IAst *_ExceptionTypeList;
        IAst *_COMMA;
        IAst *_ExceptionType;

        IAst *getExceptionTypeList() { return _ExceptionTypeList; };
        void setExceptionTypeList(IAst *_ExceptionTypeList) { this->_ExceptionTypeList = _ExceptionTypeList; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getExceptionType() { return _ExceptionType; };
        void setExceptionType(IAst *_ExceptionType) { this->_ExceptionType = _ExceptionType; }

        ExceptionTypeList(IToken* leftIToken, IToken* rightIToken,
                          IAst *_ExceptionTypeList,
                          IAst *_COMMA,
                          IAst *_ExceptionType):Ast(leftIToken, rightIToken)    {
            this->_ExceptionTypeList = _ExceptionTypeList;
            ((Ast*) _ExceptionTypeList)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_ExceptionType = _ExceptionType;
            ((Ast*) _ExceptionType)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ExceptionTypeList);
            list.push_back(_COMMA);
            list.push_back(_ExceptionType);
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
                _ExceptionTypeList->accept(v);
                _COMMA->accept(v);
                _ExceptionType->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 158:  MethodBody ::= Block
     *</em>
     *<p>
     *<b>
     *<li>Rule 159:  MethodBody ::= ;
     *</b>
     */
    struct MethodBody :public AstToken
    {
        IToken* getSEMICOLON() { return leftIToken; }

        MethodBody(IToken* token) :AstToken(token)
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
     *<li>Rule 161:  StaticInitializer ::= static Block
     *</b>
     */
    struct StaticInitializer :public Ast
    {
        IAst *_static;
        IAst *_Block;

        IAst *getstatic() { return _static; };
        void setstatic(IAst *_static) { this->_static = _static; }
        IAst *getBlock() { return _Block; };
        void setBlock(IAst *_Block) { this->_Block = _Block; }

        StaticInitializer(IToken* leftIToken, IToken* rightIToken,
                          IAst *_static,
                          IAst *_Block):Ast(leftIToken, rightIToken)    {
            this->_static = _static;
            ((Ast*) _static)->setParent(this);
            this->_Block = _Block;
            ((Ast*) _Block)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_static);
            list.push_back(_Block);
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
                _static->accept(v);
                _Block->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 162:  ConstructorDeclaration ::= ConstructorModifiersopt ConstructorDeclarator Throwsopt ConstructorBody
     *</b>
     */
    struct ConstructorDeclaration :public Ast
    {
        IAst *_ConstructorModifiersopt;
        IAst *_ConstructorDeclarator;
        IAst *_Throwsopt;
        IAst *_ConstructorBody;

        /**
         * The value returned by <b>getConstructorModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getConstructorModifiersopt() { return _ConstructorModifiersopt; };
        void setConstructorModifiersopt(IAst *_ConstructorModifiersopt) { this->_ConstructorModifiersopt = _ConstructorModifiersopt; }
        IAst *getConstructorDeclarator() { return _ConstructorDeclarator; };
        void setConstructorDeclarator(IAst *_ConstructorDeclarator) { this->_ConstructorDeclarator = _ConstructorDeclarator; }
        /**
         * The value returned by <b>getThrowsopt</b> may be <b>nullptr</b>
         */
        IAst *getThrowsopt() { return _Throwsopt; };
        void setThrowsopt(IAst *_Throwsopt) { this->_Throwsopt = _Throwsopt; }
        IAst *getConstructorBody() { return _ConstructorBody; };
        void setConstructorBody(IAst *_ConstructorBody) { this->_ConstructorBody = _ConstructorBody; }

        ConstructorDeclaration(IToken* leftIToken, IToken* rightIToken,
                               IAst *_ConstructorModifiersopt,
                               IAst *_ConstructorDeclarator,
                               IAst *_Throwsopt,
                               IAst *_ConstructorBody):Ast(leftIToken, rightIToken)    {
            this->_ConstructorModifiersopt = _ConstructorModifiersopt;
            if (_ConstructorModifiersopt != nullptr) ((Ast*) _ConstructorModifiersopt)->setParent(this);
            this->_ConstructorDeclarator = _ConstructorDeclarator;
            ((Ast*) _ConstructorDeclarator)->setParent(this);
            this->_Throwsopt = _Throwsopt;
            if (_Throwsopt != nullptr) ((Ast*) _Throwsopt)->setParent(this);
            this->_ConstructorBody = _ConstructorBody;
            ((Ast*) _ConstructorBody)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ConstructorModifiersopt);
            list.push_back(_ConstructorDeclarator);
            list.push_back(_Throwsopt);
            list.push_back(_ConstructorBody);
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
                if (_ConstructorModifiersopt != nullptr) _ConstructorModifiersopt->accept(v);
                _ConstructorDeclarator->accept(v);
                if (_Throwsopt != nullptr) _Throwsopt->accept(v);
                _ConstructorBody->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 163:  ConstructorDeclarator ::= TypeParametersopt SimpleTypeName ( FormalParameterListopt )
     *</b>
     */
    struct ConstructorDeclarator :public Ast
    {
        IAst *_TypeParametersopt;
        IAst *_SimpleTypeName;
        IAst *_LPAREN;
        IAst *_FormalParameterListopt;
        IAst *_RPAREN;

        /**
         * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeParametersopt() { return _TypeParametersopt; };
        void setTypeParametersopt(IAst *_TypeParametersopt) { this->_TypeParametersopt = _TypeParametersopt; }
        IAst *getSimpleTypeName() { return _SimpleTypeName; };
        void setSimpleTypeName(IAst *_SimpleTypeName) { this->_SimpleTypeName = _SimpleTypeName; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getFormalParameterListopt</b> may be <b>nullptr</b>
         */
        IAst *getFormalParameterListopt() { return _FormalParameterListopt; };
        void setFormalParameterListopt(IAst *_FormalParameterListopt) { this->_FormalParameterListopt = _FormalParameterListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        ConstructorDeclarator(IToken* leftIToken, IToken* rightIToken,
                              IAst *_TypeParametersopt,
                              IAst *_SimpleTypeName,
                              IAst *_LPAREN,
                              IAst *_FormalParameterListopt,
                              IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_TypeParametersopt = _TypeParametersopt;
            if (_TypeParametersopt != nullptr) ((Ast*) _TypeParametersopt)->setParent(this);
            this->_SimpleTypeName = _SimpleTypeName;
            ((Ast*) _SimpleTypeName)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_FormalParameterListopt = _FormalParameterListopt;
            if (_FormalParameterListopt != nullptr) ((Ast*) _FormalParameterListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeParametersopt);
            list.push_back(_SimpleTypeName);
            list.push_back(_LPAREN);
            list.push_back(_FormalParameterListopt);
            list.push_back(_RPAREN);
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
                if (_TypeParametersopt != nullptr) _TypeParametersopt->accept(v);
                _SimpleTypeName->accept(v);
                _LPAREN->accept(v);
                if (_FormalParameterListopt != nullptr) _FormalParameterListopt->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 165:  ConstructorModifiers ::= ConstructorModifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 166:  ConstructorModifiers ::= ConstructorModifiers ConstructorModifier
     *</b>
     */
    struct ConstructorModifiers :public Ast
    {
        IAst *_ConstructorModifiers;
        IAst *_ConstructorModifier;

        IAst *getConstructorModifiers() { return _ConstructorModifiers; };
        void setConstructorModifiers(IAst *_ConstructorModifiers) { this->_ConstructorModifiers = _ConstructorModifiers; }
        IAst *getConstructorModifier() { return _ConstructorModifier; };
        void setConstructorModifier(IAst *_ConstructorModifier) { this->_ConstructorModifier = _ConstructorModifier; }

        ConstructorModifiers(IToken* leftIToken, IToken* rightIToken,
                             IAst *_ConstructorModifiers,
                             IAst *_ConstructorModifier):Ast(leftIToken, rightIToken)    {
            this->_ConstructorModifiers = _ConstructorModifiers;
            ((Ast*) _ConstructorModifiers)->setParent(this);
            this->_ConstructorModifier = _ConstructorModifier;
            ((Ast*) _ConstructorModifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ConstructorModifiers);
            list.push_back(_ConstructorModifier);
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
                _ConstructorModifiers->accept(v);
                _ConstructorModifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 171:  ConstructorBody ::= { ExplicitConstructorInvocationopt BlockStatementsopt }
     *</b>
     */
    struct ConstructorBody :public Ast
    {
        IAst *_LBRACE;
        IAst *_ExplicitConstructorInvocationopt;
        IAst *_BlockStatementsopt;
        IAst *_RBRACE;

        IAst *getLBRACE() { return _LBRACE; };
        void setLBRACE(IAst *_LBRACE) { this->_LBRACE = _LBRACE; }
        /**
         * The value returned by <b>getExplicitConstructorInvocationopt</b> may be <b>nullptr</b>
         */
        IAst *getExplicitConstructorInvocationopt() { return _ExplicitConstructorInvocationopt; };
        void setExplicitConstructorInvocationopt(IAst *_ExplicitConstructorInvocationopt) { this->_ExplicitConstructorInvocationopt = _ExplicitConstructorInvocationopt; }
        /**
         * The value returned by <b>getBlockStatementsopt</b> may be <b>nullptr</b>
         */
        IAst *getBlockStatementsopt() { return _BlockStatementsopt; };
        void setBlockStatementsopt(IAst *_BlockStatementsopt) { this->_BlockStatementsopt = _BlockStatementsopt; }
        IAst *getRBRACE() { return _RBRACE; };
        void setRBRACE(IAst *_RBRACE) { this->_RBRACE = _RBRACE; }

        ConstructorBody(IToken* leftIToken, IToken* rightIToken,
                        IAst *_LBRACE,
                        IAst *_ExplicitConstructorInvocationopt,
                        IAst *_BlockStatementsopt,
                        IAst *_RBRACE):Ast(leftIToken, rightIToken)    {
            this->_LBRACE = _LBRACE;
            ((Ast*) _LBRACE)->setParent(this);
            this->_ExplicitConstructorInvocationopt = _ExplicitConstructorInvocationopt;
            if (_ExplicitConstructorInvocationopt != nullptr) ((Ast*) _ExplicitConstructorInvocationopt)->setParent(this);
            this->_BlockStatementsopt = _BlockStatementsopt;
            if (_BlockStatementsopt != nullptr) ((Ast*) _BlockStatementsopt)->setParent(this);
            this->_RBRACE = _RBRACE;
            ((Ast*) _RBRACE)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACE);
            list.push_back(_ExplicitConstructorInvocationopt);
            list.push_back(_BlockStatementsopt);
            list.push_back(_RBRACE);
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
                _LBRACE->accept(v);
                if (_ExplicitConstructorInvocationopt != nullptr) _ExplicitConstructorInvocationopt->accept(v);
                if (_BlockStatementsopt != nullptr) _BlockStatementsopt->accept(v);
                _RBRACE->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 175:  EnumDeclaration ::= ClassModifiersopt enum identifier Interfacesopt EnumBody
     *</b>
     */
    struct EnumDeclaration :public Ast
    {
        IAst *_ClassModifiersopt;
        IAst *_enum;
        IAst *_identifier;
        IAst *_Interfacesopt;
        IAst *_EnumBody;

        /**
         * The value returned by <b>getClassModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getClassModifiersopt() { return _ClassModifiersopt; };
        void setClassModifiersopt(IAst *_ClassModifiersopt) { this->_ClassModifiersopt = _ClassModifiersopt; }
        IAst *getenum() { return _enum; };
        void setenum(IAst *_enum) { this->_enum = _enum; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        /**
         * The value returned by <b>getInterfacesopt</b> may be <b>nullptr</b>
         */
        IAst *getInterfacesopt() { return _Interfacesopt; };
        void setInterfacesopt(IAst *_Interfacesopt) { this->_Interfacesopt = _Interfacesopt; }
        IAst *getEnumBody() { return _EnumBody; };
        void setEnumBody(IAst *_EnumBody) { this->_EnumBody = _EnumBody; }

        EnumDeclaration(IToken* leftIToken, IToken* rightIToken,
                        IAst *_ClassModifiersopt,
                        IAst *_enum,
                        IAst *_identifier,
                        IAst *_Interfacesopt,
                        IAst *_EnumBody):Ast(leftIToken, rightIToken)    {
            this->_ClassModifiersopt = _ClassModifiersopt;
            if (_ClassModifiersopt != nullptr) ((Ast*) _ClassModifiersopt)->setParent(this);
            this->_enum = _enum;
            ((Ast*) _enum)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_Interfacesopt = _Interfacesopt;
            if (_Interfacesopt != nullptr) ((Ast*) _Interfacesopt)->setParent(this);
            this->_EnumBody = _EnumBody;
            ((Ast*) _EnumBody)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ClassModifiersopt);
            list.push_back(_enum);
            list.push_back(_identifier);
            list.push_back(_Interfacesopt);
            list.push_back(_EnumBody);
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
                if (_ClassModifiersopt != nullptr) _ClassModifiersopt->accept(v);
                _enum->accept(v);
                _identifier->accept(v);
                if (_Interfacesopt != nullptr) _Interfacesopt->accept(v);
                _EnumBody->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 176:  EnumBody ::= { EnumConstantsopt ,opt EnumBodyDeclarationsopt }
     *</b>
     */
    struct EnumBody :public Ast
    {
        IAst *_LBRACE;
        IAst *_EnumConstantsopt;
        IAst *_Commaopt;
        IAst *_EnumBodyDeclarationsopt;
        IAst *_RBRACE;

        IAst *getLBRACE() { return _LBRACE; };
        void setLBRACE(IAst *_LBRACE) { this->_LBRACE = _LBRACE; }
        /**
         * The value returned by <b>getEnumConstantsopt</b> may be <b>nullptr</b>
         */
        IAst *getEnumConstantsopt() { return _EnumConstantsopt; };
        void setEnumConstantsopt(IAst *_EnumConstantsopt) { this->_EnumConstantsopt = _EnumConstantsopt; }
        /**
         * The value returned by <b>getCommaopt</b> may be <b>nullptr</b>
         */
        IAst *getCommaopt() { return _Commaopt; };
        void setCommaopt(IAst *_Commaopt) { this->_Commaopt = _Commaopt; }
        /**
         * The value returned by <b>getEnumBodyDeclarationsopt</b> may be <b>nullptr</b>
         */
        IAst *getEnumBodyDeclarationsopt() { return _EnumBodyDeclarationsopt; };
        void setEnumBodyDeclarationsopt(IAst *_EnumBodyDeclarationsopt) { this->_EnumBodyDeclarationsopt = _EnumBodyDeclarationsopt; }
        IAst *getRBRACE() { return _RBRACE; };
        void setRBRACE(IAst *_RBRACE) { this->_RBRACE = _RBRACE; }

        EnumBody(IToken* leftIToken, IToken* rightIToken,
                 IAst *_LBRACE,
                 IAst *_EnumConstantsopt,
                 IAst *_Commaopt,
                 IAst *_EnumBodyDeclarationsopt,
                 IAst *_RBRACE):Ast(leftIToken, rightIToken)    {
            this->_LBRACE = _LBRACE;
            ((Ast*) _LBRACE)->setParent(this);
            this->_EnumConstantsopt = _EnumConstantsopt;
            if (_EnumConstantsopt != nullptr) ((Ast*) _EnumConstantsopt)->setParent(this);
            this->_Commaopt = _Commaopt;
            if (_Commaopt != nullptr) ((Ast*) _Commaopt)->setParent(this);
            this->_EnumBodyDeclarationsopt = _EnumBodyDeclarationsopt;
            if (_EnumBodyDeclarationsopt != nullptr) ((Ast*) _EnumBodyDeclarationsopt)->setParent(this);
            this->_RBRACE = _RBRACE;
            ((Ast*) _RBRACE)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACE);
            list.push_back(_EnumConstantsopt);
            list.push_back(_Commaopt);
            list.push_back(_EnumBodyDeclarationsopt);
            list.push_back(_RBRACE);
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
                _LBRACE->accept(v);
                if (_EnumConstantsopt != nullptr) _EnumConstantsopt->accept(v);
                if (_Commaopt != nullptr) _Commaopt->accept(v);
                if (_EnumBodyDeclarationsopt != nullptr) _EnumBodyDeclarationsopt->accept(v);
                _RBRACE->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 177:  EnumConstants ::= EnumConstant
     *</em>
     *<p>
     *<b>
     *<li>Rule 178:  EnumConstants ::= EnumConstants , EnumConstant
     *</b>
     */
    struct EnumConstants :public Ast
    {
        IAst *_EnumConstants;
        IAst *_COMMA;
        IAst *_EnumConstant;

        IAst *getEnumConstants() { return _EnumConstants; };
        void setEnumConstants(IAst *_EnumConstants) { this->_EnumConstants = _EnumConstants; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getEnumConstant() { return _EnumConstant; };
        void setEnumConstant(IAst *_EnumConstant) { this->_EnumConstant = _EnumConstant; }

        EnumConstants(IToken* leftIToken, IToken* rightIToken,
                      IAst *_EnumConstants,
                      IAst *_COMMA,
                      IAst *_EnumConstant):Ast(leftIToken, rightIToken)    {
            this->_EnumConstants = _EnumConstants;
            ((Ast*) _EnumConstants)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_EnumConstant = _EnumConstant;
            ((Ast*) _EnumConstant)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_EnumConstants);
            list.push_back(_COMMA);
            list.push_back(_EnumConstant);
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
                _EnumConstants->accept(v);
                _COMMA->accept(v);
                _EnumConstant->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 307:  EnumConstant ::= identifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 179:  EnumConstant ::= Annotationsopt identifier Argumentsopt ClassBodyopt
     *</b>
     */
    struct EnumConstant :public Ast
    {
        IAst *_Annotationsopt;
        IAst *_identifier;
        IAst *_Argumentsopt;
        IAst *_ClassBodyopt;

        /**
         * The value returned by <b>getAnnotationsopt</b> may be <b>nullptr</b>
         */
        IAst *getAnnotationsopt() { return _Annotationsopt; };
        void setAnnotationsopt(IAst *_Annotationsopt) { this->_Annotationsopt = _Annotationsopt; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        /**
         * The value returned by <b>getArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentsopt() { return _Argumentsopt; };
        void setArgumentsopt(IAst *_Argumentsopt) { this->_Argumentsopt = _Argumentsopt; }
        /**
         * The value returned by <b>getClassBodyopt</b> may be <b>nullptr</b>
         */
        IAst *getClassBodyopt() { return _ClassBodyopt; };
        void setClassBodyopt(IAst *_ClassBodyopt) { this->_ClassBodyopt = _ClassBodyopt; }

        EnumConstant(IToken* leftIToken, IToken* rightIToken,
                     IAst *_Annotationsopt,
                     IAst *_identifier,
                     IAst *_Argumentsopt,
                     IAst *_ClassBodyopt):Ast(leftIToken, rightIToken)    {
            this->_Annotationsopt = _Annotationsopt;
            if (_Annotationsopt != nullptr) ((Ast*) _Annotationsopt)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_Argumentsopt = _Argumentsopt;
            if (_Argumentsopt != nullptr) ((Ast*) _Argumentsopt)->setParent(this);
            this->_ClassBodyopt = _ClassBodyopt;
            if (_ClassBodyopt != nullptr) ((Ast*) _ClassBodyopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Annotationsopt);
            list.push_back(_identifier);
            list.push_back(_Argumentsopt);
            list.push_back(_ClassBodyopt);
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
                if (_Annotationsopt != nullptr) _Annotationsopt->accept(v);
                _identifier->accept(v);
                if (_Argumentsopt != nullptr) _Argumentsopt->accept(v);
                if (_ClassBodyopt != nullptr) _ClassBodyopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 180:  Arguments ::= ( ArgumentListopt )
     *</b>
     */
    struct Arguments :public Ast
    {
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;

        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        Arguments(IToken* leftIToken, IToken* rightIToken,
                  IAst *_LPAREN,
                  IAst *_ArgumentListopt,
                  IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
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
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 181:  EnumBodyDeclarations ::= ; ClassBodyDeclarationsopt
     *</b>
     */
    struct EnumBodyDeclarations :public Ast
    {
        IAst *_SEMICOLON;
        IAst *_ClassBodyDeclarationsopt;

        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }
        /**
         * The value returned by <b>getClassBodyDeclarationsopt</b> may be <b>nullptr</b>
         */
        IAst *getClassBodyDeclarationsopt() { return _ClassBodyDeclarationsopt; };
        void setClassBodyDeclarationsopt(IAst *_ClassBodyDeclarationsopt) { this->_ClassBodyDeclarationsopt = _ClassBodyDeclarationsopt; }

        EnumBodyDeclarations(IToken* leftIToken, IToken* rightIToken,
                             IAst *_SEMICOLON,
                             IAst *_ClassBodyDeclarationsopt):Ast(leftIToken, rightIToken)    {
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            this->_ClassBodyDeclarationsopt = _ClassBodyDeclarationsopt;
            if (_ClassBodyDeclarationsopt != nullptr) ((Ast*) _ClassBodyDeclarationsopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SEMICOLON);
            list.push_back(_ClassBodyDeclarationsopt);
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
                _SEMICOLON->accept(v);
                if (_ClassBodyDeclarationsopt != nullptr) _ClassBodyDeclarationsopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 184:  NormalInterfaceDeclaration ::= InterfaceModifiersopt interface identifier TypeParametersopt ExtendsInterfacesopt InterfaceBody
     *</b>
     */
    struct NormalInterfaceDeclaration :public Ast
    {
        IAst *_InterfaceModifiersopt;
        IAst *_interface;
        IAst *_identifier;
        IAst *_TypeParametersopt;
        IAst *_ExtendsInterfacesopt;
        IAst *_InterfaceBody;

        /**
         * The value returned by <b>getInterfaceModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getInterfaceModifiersopt() { return _InterfaceModifiersopt; };
        void setInterfaceModifiersopt(IAst *_InterfaceModifiersopt) { this->_InterfaceModifiersopt = _InterfaceModifiersopt; }
        IAst *getinterface() { return _interface; };
        void setinterface(IAst *_interface) { this->_interface = _interface; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        /**
         * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeParametersopt() { return _TypeParametersopt; };
        void setTypeParametersopt(IAst *_TypeParametersopt) { this->_TypeParametersopt = _TypeParametersopt; }
        /**
         * The value returned by <b>getExtendsInterfacesopt</b> may be <b>nullptr</b>
         */
        IAst *getExtendsInterfacesopt() { return _ExtendsInterfacesopt; };
        void setExtendsInterfacesopt(IAst *_ExtendsInterfacesopt) { this->_ExtendsInterfacesopt = _ExtendsInterfacesopt; }
        IAst *getInterfaceBody() { return _InterfaceBody; };
        void setInterfaceBody(IAst *_InterfaceBody) { this->_InterfaceBody = _InterfaceBody; }

        NormalInterfaceDeclaration(IToken* leftIToken, IToken* rightIToken,
                                   IAst *_InterfaceModifiersopt,
                                   IAst *_interface,
                                   IAst *_identifier,
                                   IAst *_TypeParametersopt,
                                   IAst *_ExtendsInterfacesopt,
                                   IAst *_InterfaceBody):Ast(leftIToken, rightIToken)    {
            this->_InterfaceModifiersopt = _InterfaceModifiersopt;
            if (_InterfaceModifiersopt != nullptr) ((Ast*) _InterfaceModifiersopt)->setParent(this);
            this->_interface = _interface;
            ((Ast*) _interface)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_TypeParametersopt = _TypeParametersopt;
            if (_TypeParametersopt != nullptr) ((Ast*) _TypeParametersopt)->setParent(this);
            this->_ExtendsInterfacesopt = _ExtendsInterfacesopt;
            if (_ExtendsInterfacesopt != nullptr) ((Ast*) _ExtendsInterfacesopt)->setParent(this);
            this->_InterfaceBody = _InterfaceBody;
            ((Ast*) _InterfaceBody)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_InterfaceModifiersopt);
            list.push_back(_interface);
            list.push_back(_identifier);
            list.push_back(_TypeParametersopt);
            list.push_back(_ExtendsInterfacesopt);
            list.push_back(_InterfaceBody);
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
                if (_InterfaceModifiersopt != nullptr) _InterfaceModifiersopt->accept(v);
                _interface->accept(v);
                _identifier->accept(v);
                if (_TypeParametersopt != nullptr) _TypeParametersopt->accept(v);
                if (_ExtendsInterfacesopt != nullptr) _ExtendsInterfacesopt->accept(v);
                _InterfaceBody->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 185:  InterfaceModifiers ::= InterfaceModifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 186:  InterfaceModifiers ::= InterfaceModifiers InterfaceModifier
     *</b>
     */
    struct InterfaceModifiers :public Ast
    {
        IAst *_InterfaceModifiers;
        IAst *_InterfaceModifier;

        IAst *getInterfaceModifiers() { return _InterfaceModifiers; };
        void setInterfaceModifiers(IAst *_InterfaceModifiers) { this->_InterfaceModifiers = _InterfaceModifiers; }
        IAst *getInterfaceModifier() { return _InterfaceModifier; };
        void setInterfaceModifier(IAst *_InterfaceModifier) { this->_InterfaceModifier = _InterfaceModifier; }

        InterfaceModifiers(IToken* leftIToken, IToken* rightIToken,
                           IAst *_InterfaceModifiers,
                           IAst *_InterfaceModifier):Ast(leftIToken, rightIToken)    {
            this->_InterfaceModifiers = _InterfaceModifiers;
            ((Ast*) _InterfaceModifiers)->setParent(this);
            this->_InterfaceModifier = _InterfaceModifier;
            ((Ast*) _InterfaceModifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_InterfaceModifiers);
            list.push_back(_InterfaceModifier);
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
                _InterfaceModifiers->accept(v);
                _InterfaceModifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 196:  InterfaceBody ::= { InterfaceMemberDeclarationsopt }
     *</b>
     */
    struct InterfaceBody :public Ast
    {
        IAst *_LBRACE;
        IAst *_InterfaceMemberDeclarationsopt;
        IAst *_RBRACE;

        IAst *getLBRACE() { return _LBRACE; };
        void setLBRACE(IAst *_LBRACE) { this->_LBRACE = _LBRACE; }
        /**
         * The value returned by <b>getInterfaceMemberDeclarationsopt</b> may be <b>nullptr</b>
         */
        IAst *getInterfaceMemberDeclarationsopt() { return _InterfaceMemberDeclarationsopt; };
        void setInterfaceMemberDeclarationsopt(IAst *_InterfaceMemberDeclarationsopt) { this->_InterfaceMemberDeclarationsopt = _InterfaceMemberDeclarationsopt; }
        IAst *getRBRACE() { return _RBRACE; };
        void setRBRACE(IAst *_RBRACE) { this->_RBRACE = _RBRACE; }

        InterfaceBody(IToken* leftIToken, IToken* rightIToken,
                      IAst *_LBRACE,
                      IAst *_InterfaceMemberDeclarationsopt,
                      IAst *_RBRACE):Ast(leftIToken, rightIToken)    {
            this->_LBRACE = _LBRACE;
            ((Ast*) _LBRACE)->setParent(this);
            this->_InterfaceMemberDeclarationsopt = _InterfaceMemberDeclarationsopt;
            if (_InterfaceMemberDeclarationsopt != nullptr) ((Ast*) _InterfaceMemberDeclarationsopt)->setParent(this);
            this->_RBRACE = _RBRACE;
            ((Ast*) _RBRACE)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACE);
            list.push_back(_InterfaceMemberDeclarationsopt);
            list.push_back(_RBRACE);
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
                _LBRACE->accept(v);
                if (_InterfaceMemberDeclarationsopt != nullptr) _InterfaceMemberDeclarationsopt->accept(v);
                _RBRACE->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 197:  InterfaceMemberDeclarations ::= InterfaceMemberDeclaration
     *</em>
     *<p>
     *<b>
     *<li>Rule 198:  InterfaceMemberDeclarations ::= InterfaceMemberDeclarations InterfaceMemberDeclaration
     *</b>
     */
    struct InterfaceMemberDeclarations :public Ast
    {
        IAst *_InterfaceMemberDeclarations;
        IAst *_InterfaceMemberDeclaration;

        IAst *getInterfaceMemberDeclarations() { return _InterfaceMemberDeclarations; };
        void setInterfaceMemberDeclarations(IAst *_InterfaceMemberDeclarations) { this->_InterfaceMemberDeclarations = _InterfaceMemberDeclarations; }
        IAst *getInterfaceMemberDeclaration() { return _InterfaceMemberDeclaration; };
        void setInterfaceMemberDeclaration(IAst *_InterfaceMemberDeclaration) { this->_InterfaceMemberDeclaration = _InterfaceMemberDeclaration; }

        InterfaceMemberDeclarations(IToken* leftIToken, IToken* rightIToken,
                                    IAst *_InterfaceMemberDeclarations,
                                    IAst *_InterfaceMemberDeclaration):Ast(leftIToken, rightIToken)    {
            this->_InterfaceMemberDeclarations = _InterfaceMemberDeclarations;
            ((Ast*) _InterfaceMemberDeclarations)->setParent(this);
            this->_InterfaceMemberDeclaration = _InterfaceMemberDeclaration;
            ((Ast*) _InterfaceMemberDeclaration)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_InterfaceMemberDeclarations);
            list.push_back(_InterfaceMemberDeclaration);
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
                _InterfaceMemberDeclarations->accept(v);
                _InterfaceMemberDeclaration->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 199:  InterfaceMemberDeclaration ::= ConstantDeclaration
     *<li>Rule 200:  InterfaceMemberDeclaration ::= AbstractMethodDeclaration
     *<li>Rule 201:  InterfaceMemberDeclaration ::= ClassDeclaration
     *<li>Rule 202:  InterfaceMemberDeclaration ::= InterfaceDeclaration
     *</em>
     *<p>
     *<b>
     *<li>Rule 203:  InterfaceMemberDeclaration ::= ;
     *</b>
     */
    struct InterfaceMemberDeclaration :public AstToken
    {
        IToken* getSEMICOLON() { return leftIToken; }

        InterfaceMemberDeclaration(IToken* token) :AstToken(token)
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
     *<li>Rule 204:  ConstantDeclaration ::= ConstantModifiersopt Type VariableDeclarators
     *</b>
     */
    struct ConstantDeclaration :public Ast
    {
        IAst *_ConstantModifiersopt;
        IAst *_Type;
        IAst *_VariableDeclarators;

        /**
         * The value returned by <b>getConstantModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getConstantModifiersopt() { return _ConstantModifiersopt; };
        void setConstantModifiersopt(IAst *_ConstantModifiersopt) { this->_ConstantModifiersopt = _ConstantModifiersopt; }
        IAst *getType() { return _Type; };
        void setType(IAst *_Type) { this->_Type = _Type; }
        IAst *getVariableDeclarators() { return _VariableDeclarators; };
        void setVariableDeclarators(IAst *_VariableDeclarators) { this->_VariableDeclarators = _VariableDeclarators; }

        ConstantDeclaration(IToken* leftIToken, IToken* rightIToken,
                            IAst *_ConstantModifiersopt,
                            IAst *_Type,
                            IAst *_VariableDeclarators):Ast(leftIToken, rightIToken)    {
            this->_ConstantModifiersopt = _ConstantModifiersopt;
            if (_ConstantModifiersopt != nullptr) ((Ast*) _ConstantModifiersopt)->setParent(this);
            this->_Type = _Type;
            ((Ast*) _Type)->setParent(this);
            this->_VariableDeclarators = _VariableDeclarators;
            ((Ast*) _VariableDeclarators)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ConstantModifiersopt);
            list.push_back(_Type);
            list.push_back(_VariableDeclarators);
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
                if (_ConstantModifiersopt != nullptr) _ConstantModifiersopt->accept(v);
                _Type->accept(v);
                _VariableDeclarators->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 205:  ConstantModifiers ::= ConstantModifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 206:  ConstantModifiers ::= ConstantModifiers ConstantModifier
     *</b>
     */
    struct ConstantModifiers :public Ast
    {
        IAst *_ConstantModifiers;
        IAst *_ConstantModifier;

        IAst *getConstantModifiers() { return _ConstantModifiers; };
        void setConstantModifiers(IAst *_ConstantModifiers) { this->_ConstantModifiers = _ConstantModifiers; }
        IAst *getConstantModifier() { return _ConstantModifier; };
        void setConstantModifier(IAst *_ConstantModifier) { this->_ConstantModifier = _ConstantModifier; }

        ConstantModifiers(IToken* leftIToken, IToken* rightIToken,
                          IAst *_ConstantModifiers,
                          IAst *_ConstantModifier):Ast(leftIToken, rightIToken)    {
            this->_ConstantModifiers = _ConstantModifiers;
            ((Ast*) _ConstantModifiers)->setParent(this);
            this->_ConstantModifier = _ConstantModifier;
            ((Ast*) _ConstantModifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ConstantModifiers);
            list.push_back(_ConstantModifier);
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
                _ConstantModifiers->accept(v);
                _ConstantModifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 211:  AbstractMethodDeclaration ::= AbstractMethodModifiersopt TypeParametersopt ResultType MethodDeclarator Throwsopt ;
     *</b>
     */
    struct AbstractMethodDeclaration :public Ast
    {
        IAst *_AbstractMethodModifiersopt;
        IAst *_TypeParametersopt;
        IAst *_ResultType;
        IAst *_MethodDeclarator;
        IAst *_Throwsopt;
        IAst *_SEMICOLON;

        /**
         * The value returned by <b>getAbstractMethodModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getAbstractMethodModifiersopt() { return _AbstractMethodModifiersopt; };
        void setAbstractMethodModifiersopt(IAst *_AbstractMethodModifiersopt) { this->_AbstractMethodModifiersopt = _AbstractMethodModifiersopt; }
        /**
         * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeParametersopt() { return _TypeParametersopt; };
        void setTypeParametersopt(IAst *_TypeParametersopt) { this->_TypeParametersopt = _TypeParametersopt; }
        IAst *getResultType() { return _ResultType; };
        void setResultType(IAst *_ResultType) { this->_ResultType = _ResultType; }
        IAst *getMethodDeclarator() { return _MethodDeclarator; };
        void setMethodDeclarator(IAst *_MethodDeclarator) { this->_MethodDeclarator = _MethodDeclarator; }
        /**
         * The value returned by <b>getThrowsopt</b> may be <b>nullptr</b>
         */
        IAst *getThrowsopt() { return _Throwsopt; };
        void setThrowsopt(IAst *_Throwsopt) { this->_Throwsopt = _Throwsopt; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        AbstractMethodDeclaration(IToken* leftIToken, IToken* rightIToken,
                                  IAst *_AbstractMethodModifiersopt,
                                  IAst *_TypeParametersopt,
                                  IAst *_ResultType,
                                  IAst *_MethodDeclarator,
                                  IAst *_Throwsopt,
                                  IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_AbstractMethodModifiersopt = _AbstractMethodModifiersopt;
            if (_AbstractMethodModifiersopt != nullptr) ((Ast*) _AbstractMethodModifiersopt)->setParent(this);
            this->_TypeParametersopt = _TypeParametersopt;
            if (_TypeParametersopt != nullptr) ((Ast*) _TypeParametersopt)->setParent(this);
            this->_ResultType = _ResultType;
            ((Ast*) _ResultType)->setParent(this);
            this->_MethodDeclarator = _MethodDeclarator;
            ((Ast*) _MethodDeclarator)->setParent(this);
            this->_Throwsopt = _Throwsopt;
            if (_Throwsopt != nullptr) ((Ast*) _Throwsopt)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AbstractMethodModifiersopt);
            list.push_back(_TypeParametersopt);
            list.push_back(_ResultType);
            list.push_back(_MethodDeclarator);
            list.push_back(_Throwsopt);
            list.push_back(_SEMICOLON);
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
                if (_AbstractMethodModifiersopt != nullptr) _AbstractMethodModifiersopt->accept(v);
                if (_TypeParametersopt != nullptr) _TypeParametersopt->accept(v);
                _ResultType->accept(v);
                _MethodDeclarator->accept(v);
                if (_Throwsopt != nullptr) _Throwsopt->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 212:  AbstractMethodModifiers ::= AbstractMethodModifier
     *</em>
     *<p>
     *<b>
     *<li>Rule 213:  AbstractMethodModifiers ::= AbstractMethodModifiers AbstractMethodModifier
     *</b>
     */
    struct AbstractMethodModifiers :public Ast
    {
        IAst *_AbstractMethodModifiers;
        IAst *_AbstractMethodModifier;

        IAst *getAbstractMethodModifiers() { return _AbstractMethodModifiers; };
        void setAbstractMethodModifiers(IAst *_AbstractMethodModifiers) { this->_AbstractMethodModifiers = _AbstractMethodModifiers; }
        IAst *getAbstractMethodModifier() { return _AbstractMethodModifier; };
        void setAbstractMethodModifier(IAst *_AbstractMethodModifier) { this->_AbstractMethodModifier = _AbstractMethodModifier; }

        AbstractMethodModifiers(IToken* leftIToken, IToken* rightIToken,
                                IAst *_AbstractMethodModifiers,
                                IAst *_AbstractMethodModifier):Ast(leftIToken, rightIToken)    {
            this->_AbstractMethodModifiers = _AbstractMethodModifiers;
            ((Ast*) _AbstractMethodModifiers)->setParent(this);
            this->_AbstractMethodModifier = _AbstractMethodModifier;
            ((Ast*) _AbstractMethodModifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AbstractMethodModifiers);
            list.push_back(_AbstractMethodModifier);
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
                _AbstractMethodModifiers->accept(v);
                _AbstractMethodModifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 217:  AnnotationTypeDeclaration ::= InterfaceModifiersopt @ interface identifier AnnotationTypeBody
     *</b>
     */
    struct AnnotationTypeDeclaration :public Ast
    {
        IAst *_InterfaceModifiersopt;
        IAst *_AT;
        IAst *_interface;
        IAst *_identifier;
        IAst *_AnnotationTypeBody;

        /**
         * The value returned by <b>getInterfaceModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getInterfaceModifiersopt() { return _InterfaceModifiersopt; };
        void setInterfaceModifiersopt(IAst *_InterfaceModifiersopt) { this->_InterfaceModifiersopt = _InterfaceModifiersopt; }
        IAst *getAT() { return _AT; };
        void setAT(IAst *_AT) { this->_AT = _AT; }
        IAst *getinterface() { return _interface; };
        void setinterface(IAst *_interface) { this->_interface = _interface; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getAnnotationTypeBody() { return _AnnotationTypeBody; };
        void setAnnotationTypeBody(IAst *_AnnotationTypeBody) { this->_AnnotationTypeBody = _AnnotationTypeBody; }

        AnnotationTypeDeclaration(IToken* leftIToken, IToken* rightIToken,
                                  IAst *_InterfaceModifiersopt,
                                  IAst *_AT,
                                  IAst *_interface,
                                  IAst *_identifier,
                                  IAst *_AnnotationTypeBody):Ast(leftIToken, rightIToken)    {
            this->_InterfaceModifiersopt = _InterfaceModifiersopt;
            if (_InterfaceModifiersopt != nullptr) ((Ast*) _InterfaceModifiersopt)->setParent(this);
            this->_AT = _AT;
            ((Ast*) _AT)->setParent(this);
            this->_interface = _interface;
            ((Ast*) _interface)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_AnnotationTypeBody = _AnnotationTypeBody;
            ((Ast*) _AnnotationTypeBody)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_InterfaceModifiersopt);
            list.push_back(_AT);
            list.push_back(_interface);
            list.push_back(_identifier);
            list.push_back(_AnnotationTypeBody);
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
                if (_InterfaceModifiersopt != nullptr) _InterfaceModifiersopt->accept(v);
                _AT->accept(v);
                _interface->accept(v);
                _identifier->accept(v);
                _AnnotationTypeBody->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 218:  AnnotationTypeBody ::= { AnnotationTypeElementDeclarationsopt }
     *</b>
     */
    struct AnnotationTypeBody :public Ast
    {
        IAst *_LBRACE;
        IAst *_AnnotationTypeElementDeclarationsopt;
        IAst *_RBRACE;

        IAst *getLBRACE() { return _LBRACE; };
        void setLBRACE(IAst *_LBRACE) { this->_LBRACE = _LBRACE; }
        /**
         * The value returned by <b>getAnnotationTypeElementDeclarationsopt</b> may be <b>nullptr</b>
         */
        IAst *getAnnotationTypeElementDeclarationsopt() { return _AnnotationTypeElementDeclarationsopt; };
        void setAnnotationTypeElementDeclarationsopt(IAst *_AnnotationTypeElementDeclarationsopt) { this->_AnnotationTypeElementDeclarationsopt = _AnnotationTypeElementDeclarationsopt; }
        IAst *getRBRACE() { return _RBRACE; };
        void setRBRACE(IAst *_RBRACE) { this->_RBRACE = _RBRACE; }

        AnnotationTypeBody(IToken* leftIToken, IToken* rightIToken,
                           IAst *_LBRACE,
                           IAst *_AnnotationTypeElementDeclarationsopt,
                           IAst *_RBRACE):Ast(leftIToken, rightIToken)    {
            this->_LBRACE = _LBRACE;
            ((Ast*) _LBRACE)->setParent(this);
            this->_AnnotationTypeElementDeclarationsopt = _AnnotationTypeElementDeclarationsopt;
            if (_AnnotationTypeElementDeclarationsopt != nullptr) ((Ast*) _AnnotationTypeElementDeclarationsopt)->setParent(this);
            this->_RBRACE = _RBRACE;
            ((Ast*) _RBRACE)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACE);
            list.push_back(_AnnotationTypeElementDeclarationsopt);
            list.push_back(_RBRACE);
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
                _LBRACE->accept(v);
                if (_AnnotationTypeElementDeclarationsopt != nullptr) _AnnotationTypeElementDeclarationsopt->accept(v);
                _RBRACE->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 219:  AnnotationTypeElementDeclarations ::= AnnotationTypeElementDeclaration
     *</em>
     *<p>
     *<b>
     *<li>Rule 220:  AnnotationTypeElementDeclarations ::= AnnotationTypeElementDeclarations AnnotationTypeElementDeclaration
     *</b>
     */
    struct AnnotationTypeElementDeclarations :public Ast
    {
        IAst *_AnnotationTypeElementDeclarations;
        IAst *_AnnotationTypeElementDeclaration;

        IAst *getAnnotationTypeElementDeclarations() { return _AnnotationTypeElementDeclarations; };
        void setAnnotationTypeElementDeclarations(IAst *_AnnotationTypeElementDeclarations) { this->_AnnotationTypeElementDeclarations = _AnnotationTypeElementDeclarations; }
        IAst *getAnnotationTypeElementDeclaration() { return _AnnotationTypeElementDeclaration; };
        void setAnnotationTypeElementDeclaration(IAst *_AnnotationTypeElementDeclaration) { this->_AnnotationTypeElementDeclaration = _AnnotationTypeElementDeclaration; }

        AnnotationTypeElementDeclarations(IToken* leftIToken, IToken* rightIToken,
                                          IAst *_AnnotationTypeElementDeclarations,
                                          IAst *_AnnotationTypeElementDeclaration):Ast(leftIToken, rightIToken)    {
            this->_AnnotationTypeElementDeclarations = _AnnotationTypeElementDeclarations;
            ((Ast*) _AnnotationTypeElementDeclarations)->setParent(this);
            this->_AnnotationTypeElementDeclaration = _AnnotationTypeElementDeclaration;
            ((Ast*) _AnnotationTypeElementDeclaration)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AnnotationTypeElementDeclarations);
            list.push_back(_AnnotationTypeElementDeclaration);
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
                _AnnotationTypeElementDeclarations->accept(v);
                _AnnotationTypeElementDeclaration->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 228:  DefaultValue ::= default ElementValue
     *</b>
     */
    struct DefaultValue :public Ast
    {
        IAst *_default;
        IAst *_ElementValue;

        IAst *getdefault() { return _default; };
        void setdefault(IAst *_default) { this->_default = _default; }
        IAst *getElementValue() { return _ElementValue; };
        void setElementValue(IAst *_ElementValue) { this->_ElementValue = _ElementValue; }

        DefaultValue(IToken* leftIToken, IToken* rightIToken,
                     IAst *_default,
                     IAst *_ElementValue):Ast(leftIToken, rightIToken)    {
            this->_default = _default;
            ((Ast*) _default)->setParent(this);
            this->_ElementValue = _ElementValue;
            ((Ast*) _ElementValue)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_default);
            list.push_back(_ElementValue);
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
                _default->accept(v);
                _ElementValue->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 229:  Annotations ::= Annotation
     *</em>
     *<p>
     *<b>
     *<li>Rule 230:  Annotations ::= Annotations Annotation
     *</b>
     */
    struct Annotations :public Ast
    {
        IAst *_Annotations;
        IAst *_Annotation;

        IAst *getAnnotations() { return _Annotations; };
        void setAnnotations(IAst *_Annotations) { this->_Annotations = _Annotations; }
        IAst *getAnnotation() { return _Annotation; };
        void setAnnotation(IAst *_Annotation) { this->_Annotation = _Annotation; }

        Annotations(IToken* leftIToken, IToken* rightIToken,
                    IAst *_Annotations,
                    IAst *_Annotation):Ast(leftIToken, rightIToken)    {
            this->_Annotations = _Annotations;
            ((Ast*) _Annotations)->setParent(this);
            this->_Annotation = _Annotation;
            ((Ast*) _Annotation)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Annotations);
            list.push_back(_Annotation);
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
                _Annotations->accept(v);
                _Annotation->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 234:  NormalAnnotation ::= @ TypeName ( ElementValuePairsopt )
     *</b>
     */
    struct NormalAnnotation :public Ast
    {
        IAst *_AT;
        IAst *_TypeName;
        IAst *_LPAREN;
        IAst *_ElementValuePairsopt;
        IAst *_RPAREN;

        IAst *getAT() { return _AT; };
        void setAT(IAst *_AT) { this->_AT = _AT; }
        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getElementValuePairsopt</b> may be <b>nullptr</b>
         */
        IAst *getElementValuePairsopt() { return _ElementValuePairsopt; };
        void setElementValuePairsopt(IAst *_ElementValuePairsopt) { this->_ElementValuePairsopt = _ElementValuePairsopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        NormalAnnotation(IToken* leftIToken, IToken* rightIToken,
                         IAst *_AT,
                         IAst *_TypeName,
                         IAst *_LPAREN,
                         IAst *_ElementValuePairsopt,
                         IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_AT = _AT;
            ((Ast*) _AT)->setParent(this);
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ElementValuePairsopt = _ElementValuePairsopt;
            if (_ElementValuePairsopt != nullptr) ((Ast*) _ElementValuePairsopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AT);
            list.push_back(_TypeName);
            list.push_back(_LPAREN);
            list.push_back(_ElementValuePairsopt);
            list.push_back(_RPAREN);
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
                _AT->accept(v);
                _TypeName->accept(v);
                _LPAREN->accept(v);
                if (_ElementValuePairsopt != nullptr) _ElementValuePairsopt->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 235:  ElementValuePairs ::= ElementValuePair
     *</em>
     *<p>
     *<b>
     *<li>Rule 236:  ElementValuePairs ::= ElementValuePairs , ElementValuePair
     *</b>
     */
    struct ElementValuePairs :public Ast
    {
        IAst *_ElementValuePairs;
        IAst *_COMMA;
        IAst *_ElementValuePair;

        IAst *getElementValuePairs() { return _ElementValuePairs; };
        void setElementValuePairs(IAst *_ElementValuePairs) { this->_ElementValuePairs = _ElementValuePairs; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getElementValuePair() { return _ElementValuePair; };
        void setElementValuePair(IAst *_ElementValuePair) { this->_ElementValuePair = _ElementValuePair; }

        ElementValuePairs(IToken* leftIToken, IToken* rightIToken,
                          IAst *_ElementValuePairs,
                          IAst *_COMMA,
                          IAst *_ElementValuePair):Ast(leftIToken, rightIToken)    {
            this->_ElementValuePairs = _ElementValuePairs;
            ((Ast*) _ElementValuePairs)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_ElementValuePair = _ElementValuePair;
            ((Ast*) _ElementValuePair)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ElementValuePairs);
            list.push_back(_COMMA);
            list.push_back(_ElementValuePair);
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
                _ElementValuePairs->accept(v);
                _COMMA->accept(v);
                _ElementValuePair->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 237:  ElementValuePair ::= SimpleName = ElementValue
     *</b>
     */
    struct ElementValuePair :public Ast
    {
        IAst *_SimpleName;
        IAst *_EQUAL;
        IAst *_ElementValue;

        IAst *getSimpleName() { return _SimpleName; };
        void setSimpleName(IAst *_SimpleName) { this->_SimpleName = _SimpleName; }
        IAst *getEQUAL() { return _EQUAL; };
        void setEQUAL(IAst *_EQUAL) { this->_EQUAL = _EQUAL; }
        IAst *getElementValue() { return _ElementValue; };
        void setElementValue(IAst *_ElementValue) { this->_ElementValue = _ElementValue; }

        ElementValuePair(IToken* leftIToken, IToken* rightIToken,
                         IAst *_SimpleName,
                         IAst *_EQUAL,
                         IAst *_ElementValue):Ast(leftIToken, rightIToken)    {
            this->_SimpleName = _SimpleName;
            ((Ast*) _SimpleName)->setParent(this);
            this->_EQUAL = _EQUAL;
            ((Ast*) _EQUAL)->setParent(this);
            this->_ElementValue = _ElementValue;
            ((Ast*) _ElementValue)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SimpleName);
            list.push_back(_EQUAL);
            list.push_back(_ElementValue);
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
                _SimpleName->accept(v);
                _EQUAL->accept(v);
                _ElementValue->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 242:  ElementValueArrayInitializer ::= { ElementValuesopt ,opt }
     *</b>
     */
    struct ElementValueArrayInitializer :public Ast
    {
        IAst *_LBRACE;
        IAst *_ElementValuesopt;
        IAst *_Commaopt;
        IAst *_RBRACE;

        IAst *getLBRACE() { return _LBRACE; };
        void setLBRACE(IAst *_LBRACE) { this->_LBRACE = _LBRACE; }
        /**
         * The value returned by <b>getElementValuesopt</b> may be <b>nullptr</b>
         */
        IAst *getElementValuesopt() { return _ElementValuesopt; };
        void setElementValuesopt(IAst *_ElementValuesopt) { this->_ElementValuesopt = _ElementValuesopt; }
        /**
         * The value returned by <b>getCommaopt</b> may be <b>nullptr</b>
         */
        IAst *getCommaopt() { return _Commaopt; };
        void setCommaopt(IAst *_Commaopt) { this->_Commaopt = _Commaopt; }
        IAst *getRBRACE() { return _RBRACE; };
        void setRBRACE(IAst *_RBRACE) { this->_RBRACE = _RBRACE; }

        ElementValueArrayInitializer(IToken* leftIToken, IToken* rightIToken,
                                     IAst *_LBRACE,
                                     IAst *_ElementValuesopt,
                                     IAst *_Commaopt,
                                     IAst *_RBRACE):Ast(leftIToken, rightIToken)    {
            this->_LBRACE = _LBRACE;
            ((Ast*) _LBRACE)->setParent(this);
            this->_ElementValuesopt = _ElementValuesopt;
            if (_ElementValuesopt != nullptr) ((Ast*) _ElementValuesopt)->setParent(this);
            this->_Commaopt = _Commaopt;
            if (_Commaopt != nullptr) ((Ast*) _Commaopt)->setParent(this);
            this->_RBRACE = _RBRACE;
            ((Ast*) _RBRACE)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACE);
            list.push_back(_ElementValuesopt);
            list.push_back(_Commaopt);
            list.push_back(_RBRACE);
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
                _LBRACE->accept(v);
                if (_ElementValuesopt != nullptr) _ElementValuesopt->accept(v);
                if (_Commaopt != nullptr) _Commaopt->accept(v);
                _RBRACE->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 243:  ElementValues ::= ElementValue
     *</em>
     *<p>
     *<b>
     *<li>Rule 244:  ElementValues ::= ElementValues , ElementValue
     *</b>
     */
    struct ElementValues :public Ast
    {
        IAst *_ElementValues;
        IAst *_COMMA;
        IAst *_ElementValue;

        IAst *getElementValues() { return _ElementValues; };
        void setElementValues(IAst *_ElementValues) { this->_ElementValues = _ElementValues; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getElementValue() { return _ElementValue; };
        void setElementValue(IAst *_ElementValue) { this->_ElementValue = _ElementValue; }

        ElementValues(IToken* leftIToken, IToken* rightIToken,
                      IAst *_ElementValues,
                      IAst *_COMMA,
                      IAst *_ElementValue):Ast(leftIToken, rightIToken)    {
            this->_ElementValues = _ElementValues;
            ((Ast*) _ElementValues)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_ElementValue = _ElementValue;
            ((Ast*) _ElementValue)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ElementValues);
            list.push_back(_COMMA);
            list.push_back(_ElementValue);
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
                _ElementValues->accept(v);
                _COMMA->accept(v);
                _ElementValue->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 245:  MarkerAnnotation ::= @ TypeName
     *</b>
     */
    struct MarkerAnnotation :public Ast
    {
        IAst *_AT;
        IAst *_TypeName;

        IAst *getAT() { return _AT; };
        void setAT(IAst *_AT) { this->_AT = _AT; }
        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }

        MarkerAnnotation(IToken* leftIToken, IToken* rightIToken,
                         IAst *_AT,
                         IAst *_TypeName):Ast(leftIToken, rightIToken)    {
            this->_AT = _AT;
            ((Ast*) _AT)->setParent(this);
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AT);
            list.push_back(_TypeName);
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
                _AT->accept(v);
                _TypeName->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 246:  SingleElementAnnotation ::= @ TypeName ( ElementValue )
     *</b>
     */
    struct SingleElementAnnotation :public Ast
    {
        IAst *_AT;
        IAst *_TypeName;
        IAst *_LPAREN;
        IAst *_ElementValue;
        IAst *_RPAREN;

        IAst *getAT() { return _AT; };
        void setAT(IAst *_AT) { this->_AT = _AT; }
        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getElementValue() { return _ElementValue; };
        void setElementValue(IAst *_ElementValue) { this->_ElementValue = _ElementValue; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        SingleElementAnnotation(IToken* leftIToken, IToken* rightIToken,
                                IAst *_AT,
                                IAst *_TypeName,
                                IAst *_LPAREN,
                                IAst *_ElementValue,
                                IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_AT = _AT;
            ((Ast*) _AT)->setParent(this);
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ElementValue = _ElementValue;
            ((Ast*) _ElementValue)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AT);
            list.push_back(_TypeName);
            list.push_back(_LPAREN);
            list.push_back(_ElementValue);
            list.push_back(_RPAREN);
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
                _AT->accept(v);
                _TypeName->accept(v);
                _LPAREN->accept(v);
                _ElementValue->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 247:  ArrayInitializer ::= { VariableInitializersopt ,opt }
     *</b>
     */
    struct ArrayInitializer :public Ast
    {
        IAst *_LBRACE;
        IAst *_VariableInitializersopt;
        IAst *_Commaopt;
        IAst *_RBRACE;

        IAst *getLBRACE() { return _LBRACE; };
        void setLBRACE(IAst *_LBRACE) { this->_LBRACE = _LBRACE; }
        /**
         * The value returned by <b>getVariableInitializersopt</b> may be <b>nullptr</b>
         */
        IAst *getVariableInitializersopt() { return _VariableInitializersopt; };
        void setVariableInitializersopt(IAst *_VariableInitializersopt) { this->_VariableInitializersopt = _VariableInitializersopt; }
        /**
         * The value returned by <b>getCommaopt</b> may be <b>nullptr</b>
         */
        IAst *getCommaopt() { return _Commaopt; };
        void setCommaopt(IAst *_Commaopt) { this->_Commaopt = _Commaopt; }
        IAst *getRBRACE() { return _RBRACE; };
        void setRBRACE(IAst *_RBRACE) { this->_RBRACE = _RBRACE; }

        ArrayInitializer(IToken* leftIToken, IToken* rightIToken,
                         IAst *_LBRACE,
                         IAst *_VariableInitializersopt,
                         IAst *_Commaopt,
                         IAst *_RBRACE):Ast(leftIToken, rightIToken)    {
            this->_LBRACE = _LBRACE;
            ((Ast*) _LBRACE)->setParent(this);
            this->_VariableInitializersopt = _VariableInitializersopt;
            if (_VariableInitializersopt != nullptr) ((Ast*) _VariableInitializersopt)->setParent(this);
            this->_Commaopt = _Commaopt;
            if (_Commaopt != nullptr) ((Ast*) _Commaopt)->setParent(this);
            this->_RBRACE = _RBRACE;
            ((Ast*) _RBRACE)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACE);
            list.push_back(_VariableInitializersopt);
            list.push_back(_Commaopt);
            list.push_back(_RBRACE);
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
                _LBRACE->accept(v);
                if (_VariableInitializersopt != nullptr) _VariableInitializersopt->accept(v);
                if (_Commaopt != nullptr) _Commaopt->accept(v);
                _RBRACE->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 248:  VariableInitializers ::= VariableInitializer
     *</em>
     *<p>
     *<b>
     *<li>Rule 249:  VariableInitializers ::= VariableInitializers , VariableInitializer
     *</b>
     */
    struct VariableInitializers :public Ast
    {
        IAst *_VariableInitializers;
        IAst *_COMMA;
        IAst *_VariableInitializer;

        IAst *getVariableInitializers() { return _VariableInitializers; };
        void setVariableInitializers(IAst *_VariableInitializers) { this->_VariableInitializers = _VariableInitializers; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getVariableInitializer() { return _VariableInitializer; };
        void setVariableInitializer(IAst *_VariableInitializer) { this->_VariableInitializer = _VariableInitializer; }

        VariableInitializers(IToken* leftIToken, IToken* rightIToken,
                             IAst *_VariableInitializers,
                             IAst *_COMMA,
                             IAst *_VariableInitializer):Ast(leftIToken, rightIToken)    {
            this->_VariableInitializers = _VariableInitializers;
            ((Ast*) _VariableInitializers)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_VariableInitializer = _VariableInitializer;
            ((Ast*) _VariableInitializer)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_VariableInitializers);
            list.push_back(_COMMA);
            list.push_back(_VariableInitializer);
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
                _VariableInitializers->accept(v);
                _COMMA->accept(v);
                _VariableInitializer->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 250:  Block ::= { BlockStatementsopt }
     *</b>
     */
    struct Block :public Ast
    {
        IAst *_LBRACE;
        IAst *_BlockStatementsopt;
        IAst *_RBRACE;

        IAst *getLBRACE() { return _LBRACE; };
        void setLBRACE(IAst *_LBRACE) { this->_LBRACE = _LBRACE; }
        /**
         * The value returned by <b>getBlockStatementsopt</b> may be <b>nullptr</b>
         */
        IAst *getBlockStatementsopt() { return _BlockStatementsopt; };
        void setBlockStatementsopt(IAst *_BlockStatementsopt) { this->_BlockStatementsopt = _BlockStatementsopt; }
        IAst *getRBRACE() { return _RBRACE; };
        void setRBRACE(IAst *_RBRACE) { this->_RBRACE = _RBRACE; }

        Block(IToken* leftIToken, IToken* rightIToken,
              IAst *_LBRACE,
              IAst *_BlockStatementsopt,
              IAst *_RBRACE):Ast(leftIToken, rightIToken)    {
            this->_LBRACE = _LBRACE;
            ((Ast*) _LBRACE)->setParent(this);
            this->_BlockStatementsopt = _BlockStatementsopt;
            if (_BlockStatementsopt != nullptr) ((Ast*) _BlockStatementsopt)->setParent(this);
            this->_RBRACE = _RBRACE;
            ((Ast*) _RBRACE)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACE);
            list.push_back(_BlockStatementsopt);
            list.push_back(_RBRACE);
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
                _LBRACE->accept(v);
                if (_BlockStatementsopt != nullptr) _BlockStatementsopt->accept(v);
                _RBRACE->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 251:  BlockStatements ::= BlockStatement
     *</em>
     *<p>
     *<b>
     *<li>Rule 252:  BlockStatements ::= BlockStatements BlockStatement
     *</b>
     */
    struct BlockStatements :public Ast
    {
        IAst *_BlockStatements;
        IAst *_BlockStatement;

        IAst *getBlockStatements() { return _BlockStatements; };
        void setBlockStatements(IAst *_BlockStatements) { this->_BlockStatements = _BlockStatements; }
        IAst *getBlockStatement() { return _BlockStatement; };
        void setBlockStatement(IAst *_BlockStatement) { this->_BlockStatement = _BlockStatement; }

        BlockStatements(IToken* leftIToken, IToken* rightIToken,
                        IAst *_BlockStatements,
                        IAst *_BlockStatement):Ast(leftIToken, rightIToken)    {
            this->_BlockStatements = _BlockStatements;
            ((Ast*) _BlockStatements)->setParent(this);
            this->_BlockStatement = _BlockStatement;
            ((Ast*) _BlockStatement)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_BlockStatements);
            list.push_back(_BlockStatement);
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
                _BlockStatements->accept(v);
                _BlockStatement->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 256:  LocalVariableDeclarationStatement ::= LocalVariableDeclaration ;
     *</b>
     */
    struct LocalVariableDeclarationStatement :public Ast
    {
        IAst *_LocalVariableDeclaration;
        IAst *_SEMICOLON;

        IAst *getLocalVariableDeclaration() { return _LocalVariableDeclaration; };
        void setLocalVariableDeclaration(IAst *_LocalVariableDeclaration) { this->_LocalVariableDeclaration = _LocalVariableDeclaration; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        LocalVariableDeclarationStatement(IToken* leftIToken, IToken* rightIToken,
                                          IAst *_LocalVariableDeclaration,
                                          IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_LocalVariableDeclaration = _LocalVariableDeclaration;
            ((Ast*) _LocalVariableDeclaration)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LocalVariableDeclaration);
            list.push_back(_SEMICOLON);
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
                _LocalVariableDeclaration->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 257:  LocalVariableDeclaration ::= VariableModifiersopt Type VariableDeclarators
     *</b>
     */
    struct LocalVariableDeclaration :public Ast
    {
        IAst *_VariableModifiersopt;
        IAst *_Type;
        IAst *_VariableDeclarators;

        /**
         * The value returned by <b>getVariableModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getVariableModifiersopt() { return _VariableModifiersopt; };
        void setVariableModifiersopt(IAst *_VariableModifiersopt) { this->_VariableModifiersopt = _VariableModifiersopt; }
        IAst *getType() { return _Type; };
        void setType(IAst *_Type) { this->_Type = _Type; }
        IAst *getVariableDeclarators() { return _VariableDeclarators; };
        void setVariableDeclarators(IAst *_VariableDeclarators) { this->_VariableDeclarators = _VariableDeclarators; }

        LocalVariableDeclaration(IToken* leftIToken, IToken* rightIToken,
                                 IAst *_VariableModifiersopt,
                                 IAst *_Type,
                                 IAst *_VariableDeclarators):Ast(leftIToken, rightIToken)    {
            this->_VariableModifiersopt = _VariableModifiersopt;
            if (_VariableModifiersopt != nullptr) ((Ast*) _VariableModifiersopt)->setParent(this);
            this->_Type = _Type;
            ((Ast*) _Type)->setParent(this);
            this->_VariableDeclarators = _VariableDeclarators;
            ((Ast*) _VariableDeclarators)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_VariableModifiersopt);
            list.push_back(_Type);
            list.push_back(_VariableDeclarators);
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
                if (_VariableModifiersopt != nullptr) _VariableModifiersopt->accept(v);
                _Type->accept(v);
                _VariableDeclarators->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 281:  IfThenStatement ::= if ( Expression ) Statement
     *</b>
     */
    struct IfThenStatement :public Ast
    {
        IAst *_if;
        IAst *_LPAREN;
        IAst *_Expression;
        IAst *_RPAREN;
        IAst *_Statement;

        IAst *getif() { return _if; };
        void setif(IAst *_if) { this->_if = _if; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getStatement() { return _Statement; };
        void setStatement(IAst *_Statement) { this->_Statement = _Statement; }

        IfThenStatement(IToken* leftIToken, IToken* rightIToken,
                        IAst *_if,
                        IAst *_LPAREN,
                        IAst *_Expression,
                        IAst *_RPAREN,
                        IAst *_Statement):Ast(leftIToken, rightIToken)    {
            this->_if = _if;
            ((Ast*) _if)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_Statement = _Statement;
            ((Ast*) _Statement)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_if);
            list.push_back(_LPAREN);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
            list.push_back(_Statement);
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
                _if->accept(v);
                _LPAREN->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
                _Statement->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 282:  IfThenElseStatement ::= if ( Expression ) StatementNoShortIf else Statement
     *</b>
     */
    struct IfThenElseStatement :public Ast
    {
        IAst *_if;
        IAst *_LPAREN;
        IAst *_Expression;
        IAst *_RPAREN;
        IAst *_StatementNoShortIf;
        IAst *_else;
        IAst *_Statement;

        IAst *getif() { return _if; };
        void setif(IAst *_if) { this->_if = _if; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getStatementNoShortIf() { return _StatementNoShortIf; };
        void setStatementNoShortIf(IAst *_StatementNoShortIf) { this->_StatementNoShortIf = _StatementNoShortIf; }
        IAst *getelse() { return _else; };
        void setelse(IAst *_else) { this->_else = _else; }
        IAst *getStatement() { return _Statement; };
        void setStatement(IAst *_Statement) { this->_Statement = _Statement; }

        IfThenElseStatement(IToken* leftIToken, IToken* rightIToken,
                            IAst *_if,
                            IAst *_LPAREN,
                            IAst *_Expression,
                            IAst *_RPAREN,
                            IAst *_StatementNoShortIf,
                            IAst *_else,
                            IAst *_Statement):Ast(leftIToken, rightIToken)    {
            this->_if = _if;
            ((Ast*) _if)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_StatementNoShortIf = _StatementNoShortIf;
            ((Ast*) _StatementNoShortIf)->setParent(this);
            this->_else = _else;
            ((Ast*) _else)->setParent(this);
            this->_Statement = _Statement;
            ((Ast*) _Statement)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_if);
            list.push_back(_LPAREN);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
            list.push_back(_StatementNoShortIf);
            list.push_back(_else);
            list.push_back(_Statement);
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
                _if->accept(v);
                _LPAREN->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
                _StatementNoShortIf->accept(v);
                _else->accept(v);
                _Statement->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 283:  IfThenElseStatementNoShortIf ::= if ( Expression ) StatementNoShortIf else StatementNoShortIf
     *</b>
     */
    struct IfThenElseStatementNoShortIf :public Ast
    {
        IAst *_if;
        IAst *_LPAREN;
        IAst *_Expression;
        IAst *_RPAREN;
        IAst *_StatementNoShortIf;
        IAst *_else;
        IAst *_StatementNoShortIf7;

        IAst *getif() { return _if; };
        void setif(IAst *_if) { this->_if = _if; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getStatementNoShortIf() { return _StatementNoShortIf; };
        void setStatementNoShortIf(IAst *_StatementNoShortIf) { this->_StatementNoShortIf = _StatementNoShortIf; }
        IAst *getelse() { return _else; };
        void setelse(IAst *_else) { this->_else = _else; }
        IAst *getStatementNoShortIf7() { return _StatementNoShortIf7; };
        void setStatementNoShortIf7(IAst *_StatementNoShortIf7) { this->_StatementNoShortIf7 = _StatementNoShortIf7; }

        IfThenElseStatementNoShortIf(IToken* leftIToken, IToken* rightIToken,
                                     IAst *_if,
                                     IAst *_LPAREN,
                                     IAst *_Expression,
                                     IAst *_RPAREN,
                                     IAst *_StatementNoShortIf,
                                     IAst *_else,
                                     IAst *_StatementNoShortIf7):Ast(leftIToken, rightIToken)    {
            this->_if = _if;
            ((Ast*) _if)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_StatementNoShortIf = _StatementNoShortIf;
            ((Ast*) _StatementNoShortIf)->setParent(this);
            this->_else = _else;
            ((Ast*) _else)->setParent(this);
            this->_StatementNoShortIf7 = _StatementNoShortIf7;
            ((Ast*) _StatementNoShortIf7)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_if);
            list.push_back(_LPAREN);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
            list.push_back(_StatementNoShortIf);
            list.push_back(_else);
            list.push_back(_StatementNoShortIf7);
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
                _if->accept(v);
                _LPAREN->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
                _StatementNoShortIf->accept(v);
                _else->accept(v);
                _StatementNoShortIf7->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 284:  EmptyStatement ::= ;
     *</b>
     */
    struct EmptyStatement :public AstToken
    {
        IToken* getSEMICOLON() { return leftIToken; }

        EmptyStatement(IToken* token) :AstToken(token)
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
     *<li>Rule 285:  LabeledStatement ::= identifier : Statement
     *</b>
     */
    struct LabeledStatement :public Ast
    {
        IAst *_identifier;
        IAst *_COLON;
        IAst *_Statement;

        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getCOLON() { return _COLON; };
        void setCOLON(IAst *_COLON) { this->_COLON = _COLON; }
        IAst *getStatement() { return _Statement; };
        void setStatement(IAst *_Statement) { this->_Statement = _Statement; }

        LabeledStatement(IToken* leftIToken, IToken* rightIToken,
                         IAst *_identifier,
                         IAst *_COLON,
                         IAst *_Statement):Ast(leftIToken, rightIToken)    {
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_COLON = _COLON;
            ((Ast*) _COLON)->setParent(this);
            this->_Statement = _Statement;
            ((Ast*) _Statement)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_identifier);
            list.push_back(_COLON);
            list.push_back(_Statement);
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
                _identifier->accept(v);
                _COLON->accept(v);
                _Statement->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 286:  LabeledStatementNoShortIf ::= identifier : StatementNoShortIf
     *</b>
     */
    struct LabeledStatementNoShortIf :public Ast
    {
        IAst *_identifier;
        IAst *_COLON;
        IAst *_StatementNoShortIf;

        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getCOLON() { return _COLON; };
        void setCOLON(IAst *_COLON) { this->_COLON = _COLON; }
        IAst *getStatementNoShortIf() { return _StatementNoShortIf; };
        void setStatementNoShortIf(IAst *_StatementNoShortIf) { this->_StatementNoShortIf = _StatementNoShortIf; }

        LabeledStatementNoShortIf(IToken* leftIToken, IToken* rightIToken,
                                  IAst *_identifier,
                                  IAst *_COLON,
                                  IAst *_StatementNoShortIf):Ast(leftIToken, rightIToken)    {
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_COLON = _COLON;
            ((Ast*) _COLON)->setParent(this);
            this->_StatementNoShortIf = _StatementNoShortIf;
            ((Ast*) _StatementNoShortIf)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_identifier);
            list.push_back(_COLON);
            list.push_back(_StatementNoShortIf);
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
                _identifier->accept(v);
                _COLON->accept(v);
                _StatementNoShortIf->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 287:  ExpressionStatement ::= StatementExpression ;
     *</b>
     */
    struct ExpressionStatement :public Ast
    {
        IAst *_StatementExpression;
        IAst *_SEMICOLON;

        IAst *getStatementExpression() { return _StatementExpression; };
        void setStatementExpression(IAst *_StatementExpression) { this->_StatementExpression = _StatementExpression; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        ExpressionStatement(IToken* leftIToken, IToken* rightIToken,
                            IAst *_StatementExpression,
                            IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_StatementExpression = _StatementExpression;
            ((Ast*) _StatementExpression)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_StatementExpression);
            list.push_back(_SEMICOLON);
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
                _StatementExpression->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 297:  SwitchStatement ::= switch ( Expression ) SwitchBlock
     *</b>
     */
    struct SwitchStatement :public Ast
    {
        IAst *_switch;
        IAst *_LPAREN;
        IAst *_Expression;
        IAst *_RPAREN;
        IAst *_SwitchBlock;

        IAst *getswitch() { return _switch; };
        void setswitch(IAst *_switch) { this->_switch = _switch; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getSwitchBlock() { return _SwitchBlock; };
        void setSwitchBlock(IAst *_SwitchBlock) { this->_SwitchBlock = _SwitchBlock; }

        SwitchStatement(IToken* leftIToken, IToken* rightIToken,
                        IAst *_switch,
                        IAst *_LPAREN,
                        IAst *_Expression,
                        IAst *_RPAREN,
                        IAst *_SwitchBlock):Ast(leftIToken, rightIToken)    {
            this->_switch = _switch;
            ((Ast*) _switch)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_SwitchBlock = _SwitchBlock;
            ((Ast*) _SwitchBlock)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_switch);
            list.push_back(_LPAREN);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
            list.push_back(_SwitchBlock);
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
                _switch->accept(v);
                _LPAREN->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
                _SwitchBlock->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 298:  SwitchBlock ::= { SwitchBlockStatementGroupsopt SwitchLabelsopt }
     *</b>
     */
    struct SwitchBlock :public Ast
    {
        IAst *_LBRACE;
        IAst *_SwitchBlockStatementGroupsopt;
        IAst *_SwitchLabelsopt;
        IAst *_RBRACE;

        IAst *getLBRACE() { return _LBRACE; };
        void setLBRACE(IAst *_LBRACE) { this->_LBRACE = _LBRACE; }
        /**
         * The value returned by <b>getSwitchBlockStatementGroupsopt</b> may be <b>nullptr</b>
         */
        IAst *getSwitchBlockStatementGroupsopt() { return _SwitchBlockStatementGroupsopt; };
        void setSwitchBlockStatementGroupsopt(IAst *_SwitchBlockStatementGroupsopt) { this->_SwitchBlockStatementGroupsopt = _SwitchBlockStatementGroupsopt; }
        /**
         * The value returned by <b>getSwitchLabelsopt</b> may be <b>nullptr</b>
         */
        IAst *getSwitchLabelsopt() { return _SwitchLabelsopt; };
        void setSwitchLabelsopt(IAst *_SwitchLabelsopt) { this->_SwitchLabelsopt = _SwitchLabelsopt; }
        IAst *getRBRACE() { return _RBRACE; };
        void setRBRACE(IAst *_RBRACE) { this->_RBRACE = _RBRACE; }

        SwitchBlock(IToken* leftIToken, IToken* rightIToken,
                    IAst *_LBRACE,
                    IAst *_SwitchBlockStatementGroupsopt,
                    IAst *_SwitchLabelsopt,
                    IAst *_RBRACE):Ast(leftIToken, rightIToken)    {
            this->_LBRACE = _LBRACE;
            ((Ast*) _LBRACE)->setParent(this);
            this->_SwitchBlockStatementGroupsopt = _SwitchBlockStatementGroupsopt;
            if (_SwitchBlockStatementGroupsopt != nullptr) ((Ast*) _SwitchBlockStatementGroupsopt)->setParent(this);
            this->_SwitchLabelsopt = _SwitchLabelsopt;
            if (_SwitchLabelsopt != nullptr) ((Ast*) _SwitchLabelsopt)->setParent(this);
            this->_RBRACE = _RBRACE;
            ((Ast*) _RBRACE)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACE);
            list.push_back(_SwitchBlockStatementGroupsopt);
            list.push_back(_SwitchLabelsopt);
            list.push_back(_RBRACE);
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
                _LBRACE->accept(v);
                if (_SwitchBlockStatementGroupsopt != nullptr) _SwitchBlockStatementGroupsopt->accept(v);
                if (_SwitchLabelsopt != nullptr) _SwitchLabelsopt->accept(v);
                _RBRACE->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 299:  SwitchBlockStatementGroups ::= SwitchBlockStatementGroup
     *</em>
     *<p>
     *<b>
     *<li>Rule 300:  SwitchBlockStatementGroups ::= SwitchBlockStatementGroups SwitchBlockStatementGroup
     *</b>
     */
    struct SwitchBlockStatementGroups :public Ast
    {
        IAst *_SwitchBlockStatementGroups;
        IAst *_SwitchBlockStatementGroup;

        IAst *getSwitchBlockStatementGroups() { return _SwitchBlockStatementGroups; };
        void setSwitchBlockStatementGroups(IAst *_SwitchBlockStatementGroups) { this->_SwitchBlockStatementGroups = _SwitchBlockStatementGroups; }
        IAst *getSwitchBlockStatementGroup() { return _SwitchBlockStatementGroup; };
        void setSwitchBlockStatementGroup(IAst *_SwitchBlockStatementGroup) { this->_SwitchBlockStatementGroup = _SwitchBlockStatementGroup; }

        SwitchBlockStatementGroups(IToken* leftIToken, IToken* rightIToken,
                                   IAst *_SwitchBlockStatementGroups,
                                   IAst *_SwitchBlockStatementGroup):Ast(leftIToken, rightIToken)    {
            this->_SwitchBlockStatementGroups = _SwitchBlockStatementGroups;
            ((Ast*) _SwitchBlockStatementGroups)->setParent(this);
            this->_SwitchBlockStatementGroup = _SwitchBlockStatementGroup;
            ((Ast*) _SwitchBlockStatementGroup)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SwitchBlockStatementGroups);
            list.push_back(_SwitchBlockStatementGroup);
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
                _SwitchBlockStatementGroups->accept(v);
                _SwitchBlockStatementGroup->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 301:  SwitchBlockStatementGroup ::= SwitchLabels BlockStatements
     *</b>
     */
    struct SwitchBlockStatementGroup :public Ast
    {
        IAst *_SwitchLabels;
        IAst *_BlockStatements;

        IAst *getSwitchLabels() { return _SwitchLabels; };
        void setSwitchLabels(IAst *_SwitchLabels) { this->_SwitchLabels = _SwitchLabels; }
        IAst *getBlockStatements() { return _BlockStatements; };
        void setBlockStatements(IAst *_BlockStatements) { this->_BlockStatements = _BlockStatements; }

        SwitchBlockStatementGroup(IToken* leftIToken, IToken* rightIToken,
                                  IAst *_SwitchLabels,
                                  IAst *_BlockStatements):Ast(leftIToken, rightIToken)    {
            this->_SwitchLabels = _SwitchLabels;
            ((Ast*) _SwitchLabels)->setParent(this);
            this->_BlockStatements = _BlockStatements;
            ((Ast*) _BlockStatements)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SwitchLabels);
            list.push_back(_BlockStatements);
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
                _SwitchLabels->accept(v);
                _BlockStatements->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 302:  SwitchLabels ::= SwitchLabel
     *</em>
     *<p>
     *<b>
     *<li>Rule 303:  SwitchLabels ::= SwitchLabels SwitchLabel
     *</b>
     */
    struct SwitchLabels :public Ast
    {
        IAst *_SwitchLabels;
        IAst *_SwitchLabel;

        IAst *getSwitchLabels() { return _SwitchLabels; };
        void setSwitchLabels(IAst *_SwitchLabels) { this->_SwitchLabels = _SwitchLabels; }
        IAst *getSwitchLabel() { return _SwitchLabel; };
        void setSwitchLabel(IAst *_SwitchLabel) { this->_SwitchLabel = _SwitchLabel; }

        SwitchLabels(IToken* leftIToken, IToken* rightIToken,
                     IAst *_SwitchLabels,
                     IAst *_SwitchLabel):Ast(leftIToken, rightIToken)    {
            this->_SwitchLabels = _SwitchLabels;
            ((Ast*) _SwitchLabels)->setParent(this);
            this->_SwitchLabel = _SwitchLabel;
            ((Ast*) _SwitchLabel)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_SwitchLabels);
            list.push_back(_SwitchLabel);
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
                _SwitchLabels->accept(v);
                _SwitchLabel->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 308:  WhileStatement ::= while ( Expression ) Statement
     *</b>
     */
    struct WhileStatement :public Ast
    {
        IAst *_while;
        IAst *_LPAREN;
        IAst *_Expression;
        IAst *_RPAREN;
        IAst *_Statement;

        IAst *getwhile() { return _while; };
        void setwhile(IAst *_while) { this->_while = _while; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getStatement() { return _Statement; };
        void setStatement(IAst *_Statement) { this->_Statement = _Statement; }

        WhileStatement(IToken* leftIToken, IToken* rightIToken,
                       IAst *_while,
                       IAst *_LPAREN,
                       IAst *_Expression,
                       IAst *_RPAREN,
                       IAst *_Statement):Ast(leftIToken, rightIToken)    {
            this->_while = _while;
            ((Ast*) _while)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_Statement = _Statement;
            ((Ast*) _Statement)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_while);
            list.push_back(_LPAREN);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
            list.push_back(_Statement);
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
                _while->accept(v);
                _LPAREN->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
                _Statement->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 309:  WhileStatementNoShortIf ::= while ( Expression ) StatementNoShortIf
     *</b>
     */
    struct WhileStatementNoShortIf :public Ast
    {
        IAst *_while;
        IAst *_LPAREN;
        IAst *_Expression;
        IAst *_RPAREN;
        IAst *_StatementNoShortIf;

        IAst *getwhile() { return _while; };
        void setwhile(IAst *_while) { this->_while = _while; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getStatementNoShortIf() { return _StatementNoShortIf; };
        void setStatementNoShortIf(IAst *_StatementNoShortIf) { this->_StatementNoShortIf = _StatementNoShortIf; }

        WhileStatementNoShortIf(IToken* leftIToken, IToken* rightIToken,
                                IAst *_while,
                                IAst *_LPAREN,
                                IAst *_Expression,
                                IAst *_RPAREN,
                                IAst *_StatementNoShortIf):Ast(leftIToken, rightIToken)    {
            this->_while = _while;
            ((Ast*) _while)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_StatementNoShortIf = _StatementNoShortIf;
            ((Ast*) _StatementNoShortIf)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_while);
            list.push_back(_LPAREN);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
            list.push_back(_StatementNoShortIf);
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
                _while->accept(v);
                _LPAREN->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
                _StatementNoShortIf->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 310:  DoStatement ::= do Statement while ( Expression ) ;
     *</b>
     */
    struct DoStatement :public Ast
    {
        IAst *_do;
        IAst *_Statement;
        IAst *_while;
        IAst *_LPAREN;
        IAst *_Expression;
        IAst *_RPAREN;
        IAst *_SEMICOLON;

        IAst *getdo() { return _do; };
        void setdo(IAst *_do) { this->_do = _do; }
        IAst *getStatement() { return _Statement; };
        void setStatement(IAst *_Statement) { this->_Statement = _Statement; }
        IAst *getwhile() { return _while; };
        void setwhile(IAst *_while) { this->_while = _while; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        DoStatement(IToken* leftIToken, IToken* rightIToken,
                    IAst *_do,
                    IAst *_Statement,
                    IAst *_while,
                    IAst *_LPAREN,
                    IAst *_Expression,
                    IAst *_RPAREN,
                    IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_do = _do;
            ((Ast*) _do)->setParent(this);
            this->_Statement = _Statement;
            ((Ast*) _Statement)->setParent(this);
            this->_while = _while;
            ((Ast*) _while)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_do);
            list.push_back(_Statement);
            list.push_back(_while);
            list.push_back(_LPAREN);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
            list.push_back(_SEMICOLON);
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
                _do->accept(v);
                _Statement->accept(v);
                _while->accept(v);
                _LPAREN->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 313:  BasicForStatement ::= for ( ForInitopt ; Expressionopt ; ForUpdateopt ) Statement
     *</b>
     */
    struct BasicForStatement :public Ast
    {
        IAst *_for;
        IAst *_LPAREN;
        IAst *_ForInitopt;
        IAst *_SEMICOLON;
        IAst *_Expressionopt;
        IAst *_SEMICOLON6;
        IAst *_ForUpdateopt;
        IAst *_RPAREN;
        IAst *_Statement;

        IAst *getfor() { return _for; };
        void setfor(IAst *_for) { this->_for = _for; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getForInitopt</b> may be <b>nullptr</b>
         */
        IAst *getForInitopt() { return _ForInitopt; };
        void setForInitopt(IAst *_ForInitopt) { this->_ForInitopt = _ForInitopt; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }
        /**
         * The value returned by <b>getExpressionopt</b> may be <b>nullptr</b>
         */
        IAst *getExpressionopt() { return _Expressionopt; };
        void setExpressionopt(IAst *_Expressionopt) { this->_Expressionopt = _Expressionopt; }
        IAst *getSEMICOLON6() { return _SEMICOLON6; };
        void setSEMICOLON6(IAst *_SEMICOLON6) { this->_SEMICOLON6 = _SEMICOLON6; }
        /**
         * The value returned by <b>getForUpdateopt</b> may be <b>nullptr</b>
         */
        IAst *getForUpdateopt() { return _ForUpdateopt; };
        void setForUpdateopt(IAst *_ForUpdateopt) { this->_ForUpdateopt = _ForUpdateopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getStatement() { return _Statement; };
        void setStatement(IAst *_Statement) { this->_Statement = _Statement; }

        BasicForStatement(IToken* leftIToken, IToken* rightIToken,
                          IAst *_for,
                          IAst *_LPAREN,
                          IAst *_ForInitopt,
                          IAst *_SEMICOLON,
                          IAst *_Expressionopt,
                          IAst *_SEMICOLON6,
                          IAst *_ForUpdateopt,
                          IAst *_RPAREN,
                          IAst *_Statement):Ast(leftIToken, rightIToken)    {
            this->_for = _for;
            ((Ast*) _for)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ForInitopt = _ForInitopt;
            if (_ForInitopt != nullptr) ((Ast*) _ForInitopt)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            this->_Expressionopt = _Expressionopt;
            if (_Expressionopt != nullptr) ((Ast*) _Expressionopt)->setParent(this);
            this->_SEMICOLON6 = _SEMICOLON6;
            ((Ast*) _SEMICOLON6)->setParent(this);
            this->_ForUpdateopt = _ForUpdateopt;
            if (_ForUpdateopt != nullptr) ((Ast*) _ForUpdateopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_Statement = _Statement;
            ((Ast*) _Statement)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_for);
            list.push_back(_LPAREN);
            list.push_back(_ForInitopt);
            list.push_back(_SEMICOLON);
            list.push_back(_Expressionopt);
            list.push_back(_SEMICOLON6);
            list.push_back(_ForUpdateopt);
            list.push_back(_RPAREN);
            list.push_back(_Statement);
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
                _for->accept(v);
                _LPAREN->accept(v);
                if (_ForInitopt != nullptr) _ForInitopt->accept(v);
                _SEMICOLON->accept(v);
                if (_Expressionopt != nullptr) _Expressionopt->accept(v);
                _SEMICOLON6->accept(v);
                if (_ForUpdateopt != nullptr) _ForUpdateopt->accept(v);
                _RPAREN->accept(v);
                _Statement->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 314:  ForStatementNoShortIf ::= for ( ForInitopt ; Expressionopt ; ForUpdateopt ) StatementNoShortIf
     *</b>
     */
    struct ForStatementNoShortIf :public Ast
    {
        IAst *_for;
        IAst *_LPAREN;
        IAst *_ForInitopt;
        IAst *_SEMICOLON;
        IAst *_Expressionopt;
        IAst *_SEMICOLON6;
        IAst *_ForUpdateopt;
        IAst *_RPAREN;
        IAst *_StatementNoShortIf;

        IAst *getfor() { return _for; };
        void setfor(IAst *_for) { this->_for = _for; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getForInitopt</b> may be <b>nullptr</b>
         */
        IAst *getForInitopt() { return _ForInitopt; };
        void setForInitopt(IAst *_ForInitopt) { this->_ForInitopt = _ForInitopt; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }
        /**
         * The value returned by <b>getExpressionopt</b> may be <b>nullptr</b>
         */
        IAst *getExpressionopt() { return _Expressionopt; };
        void setExpressionopt(IAst *_Expressionopt) { this->_Expressionopt = _Expressionopt; }
        IAst *getSEMICOLON6() { return _SEMICOLON6; };
        void setSEMICOLON6(IAst *_SEMICOLON6) { this->_SEMICOLON6 = _SEMICOLON6; }
        /**
         * The value returned by <b>getForUpdateopt</b> may be <b>nullptr</b>
         */
        IAst *getForUpdateopt() { return _ForUpdateopt; };
        void setForUpdateopt(IAst *_ForUpdateopt) { this->_ForUpdateopt = _ForUpdateopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getStatementNoShortIf() { return _StatementNoShortIf; };
        void setStatementNoShortIf(IAst *_StatementNoShortIf) { this->_StatementNoShortIf = _StatementNoShortIf; }

        ForStatementNoShortIf(IToken* leftIToken, IToken* rightIToken,
                              IAst *_for,
                              IAst *_LPAREN,
                              IAst *_ForInitopt,
                              IAst *_SEMICOLON,
                              IAst *_Expressionopt,
                              IAst *_SEMICOLON6,
                              IAst *_ForUpdateopt,
                              IAst *_RPAREN,
                              IAst *_StatementNoShortIf):Ast(leftIToken, rightIToken)    {
            this->_for = _for;
            ((Ast*) _for)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ForInitopt = _ForInitopt;
            if (_ForInitopt != nullptr) ((Ast*) _ForInitopt)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            this->_Expressionopt = _Expressionopt;
            if (_Expressionopt != nullptr) ((Ast*) _Expressionopt)->setParent(this);
            this->_SEMICOLON6 = _SEMICOLON6;
            ((Ast*) _SEMICOLON6)->setParent(this);
            this->_ForUpdateopt = _ForUpdateopt;
            if (_ForUpdateopt != nullptr) ((Ast*) _ForUpdateopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_StatementNoShortIf = _StatementNoShortIf;
            ((Ast*) _StatementNoShortIf)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_for);
            list.push_back(_LPAREN);
            list.push_back(_ForInitopt);
            list.push_back(_SEMICOLON);
            list.push_back(_Expressionopt);
            list.push_back(_SEMICOLON6);
            list.push_back(_ForUpdateopt);
            list.push_back(_RPAREN);
            list.push_back(_StatementNoShortIf);
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
                _for->accept(v);
                _LPAREN->accept(v);
                if (_ForInitopt != nullptr) _ForInitopt->accept(v);
                _SEMICOLON->accept(v);
                if (_Expressionopt != nullptr) _Expressionopt->accept(v);
                _SEMICOLON6->accept(v);
                if (_ForUpdateopt != nullptr) _ForUpdateopt->accept(v);
                _RPAREN->accept(v);
                _StatementNoShortIf->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 318:  StatementExpressionList ::= StatementExpression
     *</em>
     *<p>
     *<b>
     *<li>Rule 319:  StatementExpressionList ::= StatementExpressionList , StatementExpression
     *</b>
     */
    struct StatementExpressionList :public Ast
    {
        IAst *_StatementExpressionList;
        IAst *_COMMA;
        IAst *_StatementExpression;

        IAst *getStatementExpressionList() { return _StatementExpressionList; };
        void setStatementExpressionList(IAst *_StatementExpressionList) { this->_StatementExpressionList = _StatementExpressionList; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getStatementExpression() { return _StatementExpression; };
        void setStatementExpression(IAst *_StatementExpression) { this->_StatementExpression = _StatementExpression; }

        StatementExpressionList(IToken* leftIToken, IToken* rightIToken,
                                IAst *_StatementExpressionList,
                                IAst *_COMMA,
                                IAst *_StatementExpression):Ast(leftIToken, rightIToken)    {
            this->_StatementExpressionList = _StatementExpressionList;
            ((Ast*) _StatementExpressionList)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_StatementExpression = _StatementExpression;
            ((Ast*) _StatementExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_StatementExpressionList);
            list.push_back(_COMMA);
            list.push_back(_StatementExpression);
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
                _StatementExpressionList->accept(v);
                _COMMA->accept(v);
                _StatementExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 320:  EnhancedForStatement ::= for ( FormalParameter : Expression ) Statement
     *</b>
     */
    struct EnhancedForStatement :public Ast
    {
        IAst *_for;
        IAst *_LPAREN;
        IAst *_FormalParameter;
        IAst *_COLON;
        IAst *_Expression;
        IAst *_RPAREN;
        IAst *_Statement;

        IAst *getfor() { return _for; };
        void setfor(IAst *_for) { this->_for = _for; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getFormalParameter() { return _FormalParameter; };
        void setFormalParameter(IAst *_FormalParameter) { this->_FormalParameter = _FormalParameter; }
        IAst *getCOLON() { return _COLON; };
        void setCOLON(IAst *_COLON) { this->_COLON = _COLON; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getStatement() { return _Statement; };
        void setStatement(IAst *_Statement) { this->_Statement = _Statement; }

        EnhancedForStatement(IToken* leftIToken, IToken* rightIToken,
                             IAst *_for,
                             IAst *_LPAREN,
                             IAst *_FormalParameter,
                             IAst *_COLON,
                             IAst *_Expression,
                             IAst *_RPAREN,
                             IAst *_Statement):Ast(leftIToken, rightIToken)    {
            this->_for = _for;
            ((Ast*) _for)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_FormalParameter = _FormalParameter;
            ((Ast*) _FormalParameter)->setParent(this);
            this->_COLON = _COLON;
            ((Ast*) _COLON)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_Statement = _Statement;
            ((Ast*) _Statement)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_for);
            list.push_back(_LPAREN);
            list.push_back(_FormalParameter);
            list.push_back(_COLON);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
            list.push_back(_Statement);
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
                _for->accept(v);
                _LPAREN->accept(v);
                _FormalParameter->accept(v);
                _COLON->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
                _Statement->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 321:  BreakStatement ::= break identifieropt ;
     *</b>
     */
    struct BreakStatement :public Ast
    {
        IAst *_break;
        IAst *_identifieropt;
        IAst *_SEMICOLON;

        IAst *getbreak() { return _break; };
        void setbreak(IAst *_break) { this->_break = _break; }
        /**
         * The value returned by <b>getidentifieropt</b> may be <b>nullptr</b>
         */
        IAst *getidentifieropt() { return _identifieropt; };
        void setidentifieropt(IAst *_identifieropt) { this->_identifieropt = _identifieropt; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        BreakStatement(IToken* leftIToken, IToken* rightIToken,
                       IAst *_break,
                       IAst *_identifieropt,
                       IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_break = _break;
            ((Ast*) _break)->setParent(this);
            this->_identifieropt = _identifieropt;
            if (_identifieropt != nullptr) ((Ast*) _identifieropt)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_break);
            list.push_back(_identifieropt);
            list.push_back(_SEMICOLON);
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
                _break->accept(v);
                if (_identifieropt != nullptr) _identifieropt->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 322:  ContinueStatement ::= continue identifieropt ;
     *</b>
     */
    struct ContinueStatement :public Ast
    {
        IAst *_continue;
        IAst *_identifieropt;
        IAst *_SEMICOLON;

        IAst *getcontinue() { return _continue; };
        void setcontinue(IAst *_continue) { this->_continue = _continue; }
        /**
         * The value returned by <b>getidentifieropt</b> may be <b>nullptr</b>
         */
        IAst *getidentifieropt() { return _identifieropt; };
        void setidentifieropt(IAst *_identifieropt) { this->_identifieropt = _identifieropt; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        ContinueStatement(IToken* leftIToken, IToken* rightIToken,
                          IAst *_continue,
                          IAst *_identifieropt,
                          IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_continue = _continue;
            ((Ast*) _continue)->setParent(this);
            this->_identifieropt = _identifieropt;
            if (_identifieropt != nullptr) ((Ast*) _identifieropt)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_continue);
            list.push_back(_identifieropt);
            list.push_back(_SEMICOLON);
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
                _continue->accept(v);
                if (_identifieropt != nullptr) _identifieropt->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 323:  ReturnStatement ::= return Expressionopt ;
     *</b>
     */
    struct ReturnStatement :public Ast
    {
        IAst *_return;
        IAst *_Expressionopt;
        IAst *_SEMICOLON;

        IAst *getreturn() { return _return; };
        void setreturn(IAst *_return) { this->_return = _return; }
        /**
         * The value returned by <b>getExpressionopt</b> may be <b>nullptr</b>
         */
        IAst *getExpressionopt() { return _Expressionopt; };
        void setExpressionopt(IAst *_Expressionopt) { this->_Expressionopt = _Expressionopt; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        ReturnStatement(IToken* leftIToken, IToken* rightIToken,
                        IAst *_return,
                        IAst *_Expressionopt,
                        IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_return = _return;
            ((Ast*) _return)->setParent(this);
            this->_Expressionopt = _Expressionopt;
            if (_Expressionopt != nullptr) ((Ast*) _Expressionopt)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_return);
            list.push_back(_Expressionopt);
            list.push_back(_SEMICOLON);
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
                _return->accept(v);
                if (_Expressionopt != nullptr) _Expressionopt->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 324:  ThrowStatement ::= throw Expression ;
     *</b>
     */
    struct ThrowStatement :public Ast
    {
        IAst *_throw;
        IAst *_Expression;
        IAst *_SEMICOLON;

        IAst *getthrow() { return _throw; };
        void setthrow(IAst *_throw) { this->_throw = _throw; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        ThrowStatement(IToken* leftIToken, IToken* rightIToken,
                       IAst *_throw,
                       IAst *_Expression,
                       IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_throw = _throw;
            ((Ast*) _throw)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_throw);
            list.push_back(_Expression);
            list.push_back(_SEMICOLON);
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
                _throw->accept(v);
                _Expression->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 325:  SynchronizedStatement ::= synchronized ( Expression ) Block
     *</b>
     */
    struct SynchronizedStatement :public Ast
    {
        IAst *_synchronized;
        IAst *_LPAREN;
        IAst *_Expression;
        IAst *_RPAREN;
        IAst *_Block;

        IAst *getsynchronized() { return _synchronized; };
        void setsynchronized(IAst *_synchronized) { this->_synchronized = _synchronized; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getBlock() { return _Block; };
        void setBlock(IAst *_Block) { this->_Block = _Block; }

        SynchronizedStatement(IToken* leftIToken, IToken* rightIToken,
                              IAst *_synchronized,
                              IAst *_LPAREN,
                              IAst *_Expression,
                              IAst *_RPAREN,
                              IAst *_Block):Ast(leftIToken, rightIToken)    {
            this->_synchronized = _synchronized;
            ((Ast*) _synchronized)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_Block = _Block;
            ((Ast*) _Block)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_synchronized);
            list.push_back(_LPAREN);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
            list.push_back(_Block);
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
                _synchronized->accept(v);
                _LPAREN->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
                _Block->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 328:  Catches ::= CatchClause
     *</em>
     *<p>
     *<b>
     *<li>Rule 329:  Catches ::= Catches CatchClause
     *</b>
     */
    struct Catches :public Ast
    {
        IAst *_Catches;
        IAst *_CatchClause;

        IAst *getCatches() { return _Catches; };
        void setCatches(IAst *_Catches) { this->_Catches = _Catches; }
        IAst *getCatchClause() { return _CatchClause; };
        void setCatchClause(IAst *_CatchClause) { this->_CatchClause = _CatchClause; }

        Catches(IToken* leftIToken, IToken* rightIToken,
                IAst *_Catches,
                IAst *_CatchClause):Ast(leftIToken, rightIToken)    {
            this->_Catches = _Catches;
            ((Ast*) _Catches)->setParent(this);
            this->_CatchClause = _CatchClause;
            ((Ast*) _CatchClause)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Catches);
            list.push_back(_CatchClause);
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
                _Catches->accept(v);
                _CatchClause->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 330:  CatchClause ::= catch ( FormalParameter ) Block
     *</b>
     */
    struct CatchClause :public Ast
    {
        IAst *_catch;
        IAst *_LPAREN;
        IAst *_FormalParameter;
        IAst *_RPAREN;
        IAst *_Block;

        IAst *getcatch() { return _catch; };
        void setcatch(IAst *_catch) { this->_catch = _catch; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getFormalParameter() { return _FormalParameter; };
        void setFormalParameter(IAst *_FormalParameter) { this->_FormalParameter = _FormalParameter; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getBlock() { return _Block; };
        void setBlock(IAst *_Block) { this->_Block = _Block; }

        CatchClause(IToken* leftIToken, IToken* rightIToken,
                    IAst *_catch,
                    IAst *_LPAREN,
                    IAst *_FormalParameter,
                    IAst *_RPAREN,
                    IAst *_Block):Ast(leftIToken, rightIToken)    {
            this->_catch = _catch;
            ((Ast*) _catch)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_FormalParameter = _FormalParameter;
            ((Ast*) _FormalParameter)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_Block = _Block;
            ((Ast*) _Block)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_catch);
            list.push_back(_LPAREN);
            list.push_back(_FormalParameter);
            list.push_back(_RPAREN);
            list.push_back(_Block);
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
                _catch->accept(v);
                _LPAREN->accept(v);
                _FormalParameter->accept(v);
                _RPAREN->accept(v);
                _Block->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 331:  Finally ::= finally Block
     *</b>
     */
    struct Finally :public Ast
    {
        IAst *m_finally;
        IAst *_Block;

        IAst *getfinally() { return m_finally; };
        void setfinally(IAst *m_finally) { this->m_finally = m_finally; }
        IAst *getBlock() { return _Block; };
        void setBlock(IAst *_Block) { this->_Block = _Block; }

        Finally(IToken* leftIToken, IToken* rightIToken,
                IAst *m_finally,
                IAst *_Block):Ast(leftIToken, rightIToken)    {
            this->m_finally = m_finally;
            ((Ast*) m_finally)->setParent(this);
            this->_Block = _Block;
            ((Ast*) _Block)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(m_finally);
            list.push_back(_Block);
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
                m_finally->accept(v);
                _Block->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 356:  ArgumentList ::= Expression
     *</em>
     *<p>
     *<b>
     *<li>Rule 357:  ArgumentList ::= ArgumentList , Expression
     *</b>
     */
    struct ArgumentList :public Ast
    {
        IAst *_ArgumentList;
        IAst *_COMMA;
        IAst *_Expression;

        IAst *getArgumentList() { return _ArgumentList; };
        void setArgumentList(IAst *_ArgumentList) { this->_ArgumentList = _ArgumentList; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }

        ArgumentList(IToken* leftIToken, IToken* rightIToken,
                     IAst *_ArgumentList,
                     IAst *_COMMA,
                     IAst *_Expression):Ast(leftIToken, rightIToken)    {
            this->_ArgumentList = _ArgumentList;
            ((Ast*) _ArgumentList)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ArgumentList);
            list.push_back(_COMMA);
            list.push_back(_Expression);
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
                _ArgumentList->accept(v);
                _COMMA->accept(v);
                _Expression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 362:  DimExprs ::= DimExpr
     *</em>
     *<p>
     *<b>
     *<li>Rule 363:  DimExprs ::= DimExprs DimExpr
     *</b>
     */
    struct DimExprs :public Ast
    {
        IAst *_DimExprs;
        IAst *_DimExpr;

        IAst *getDimExprs() { return _DimExprs; };
        void setDimExprs(IAst *_DimExprs) { this->_DimExprs = _DimExprs; }
        IAst *getDimExpr() { return _DimExpr; };
        void setDimExpr(IAst *_DimExpr) { this->_DimExpr = _DimExpr; }

        DimExprs(IToken* leftIToken, IToken* rightIToken,
                 IAst *_DimExprs,
                 IAst *_DimExpr):Ast(leftIToken, rightIToken)    {
            this->_DimExprs = _DimExprs;
            ((Ast*) _DimExprs)->setParent(this);
            this->_DimExpr = _DimExpr;
            ((Ast*) _DimExpr)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_DimExprs);
            list.push_back(_DimExpr);
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
                _DimExprs->accept(v);
                _DimExpr->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 364:  DimExpr ::= [ Expression ]
     *</b>
     */
    struct DimExpr :public Ast
    {
        IAst *_LBRACKET;
        IAst *_Expression;
        IAst *_RBRACKET;

        IAst *getLBRACKET() { return _LBRACKET; };
        void setLBRACKET(IAst *_LBRACKET) { this->_LBRACKET = _LBRACKET; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRBRACKET() { return _RBRACKET; };
        void setRBRACKET(IAst *_RBRACKET) { this->_RBRACKET = _RBRACKET; }

        DimExpr(IToken* leftIToken, IToken* rightIToken,
                IAst *_LBRACKET,
                IAst *_Expression,
                IAst *_RBRACKET):Ast(leftIToken, rightIToken)    {
            this->_LBRACKET = _LBRACKET;
            ((Ast*) _LBRACKET)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RBRACKET = _RBRACKET;
            ((Ast*) _RBRACKET)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACKET);
            list.push_back(_Expression);
            list.push_back(_RBRACKET);
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
                _LBRACKET->accept(v);
                _Expression->accept(v);
                _RBRACKET->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 381:  PostIncrementExpression ::= PostfixExpression ++
     *</b>
     */
    struct PostIncrementExpression :public Ast
    {
        IAst *_PostfixExpression;
        IAst *_PLUS_PLUS;

        IAst *getPostfixExpression() { return _PostfixExpression; };
        void setPostfixExpression(IAst *_PostfixExpression) { this->_PostfixExpression = _PostfixExpression; }
        IAst *getPLUS_PLUS() { return _PLUS_PLUS; };
        void setPLUS_PLUS(IAst *_PLUS_PLUS) { this->_PLUS_PLUS = _PLUS_PLUS; }

        PostIncrementExpression(IToken* leftIToken, IToken* rightIToken,
                                IAst *_PostfixExpression,
                                IAst *_PLUS_PLUS):Ast(leftIToken, rightIToken)    {
            this->_PostfixExpression = _PostfixExpression;
            ((Ast*) _PostfixExpression)->setParent(this);
            this->_PLUS_PLUS = _PLUS_PLUS;
            ((Ast*) _PLUS_PLUS)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_PostfixExpression);
            list.push_back(_PLUS_PLUS);
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
                _PostfixExpression->accept(v);
                _PLUS_PLUS->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 382:  PostDecrementExpression ::= PostfixExpression --
     *</b>
     */
    struct PostDecrementExpression :public Ast
    {
        IAst *_PostfixExpression;
        IAst *_MINUS_MINUS;

        IAst *getPostfixExpression() { return _PostfixExpression; };
        void setPostfixExpression(IAst *_PostfixExpression) { this->_PostfixExpression = _PostfixExpression; }
        IAst *getMINUS_MINUS() { return _MINUS_MINUS; };
        void setMINUS_MINUS(IAst *_MINUS_MINUS) { this->_MINUS_MINUS = _MINUS_MINUS; }

        PostDecrementExpression(IToken* leftIToken, IToken* rightIToken,
                                IAst *_PostfixExpression,
                                IAst *_MINUS_MINUS):Ast(leftIToken, rightIToken)    {
            this->_PostfixExpression = _PostfixExpression;
            ((Ast*) _PostfixExpression)->setParent(this);
            this->_MINUS_MINUS = _MINUS_MINUS;
            ((Ast*) _MINUS_MINUS)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_PostfixExpression);
            list.push_back(_MINUS_MINUS);
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
                _PostfixExpression->accept(v);
                _MINUS_MINUS->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 388:  PreIncrementExpression ::= ++ UnaryExpression
     *</b>
     */
    struct PreIncrementExpression :public Ast
    {
        IAst *_PLUS_PLUS;
        IAst *_UnaryExpression;

        IAst *getPLUS_PLUS() { return _PLUS_PLUS; };
        void setPLUS_PLUS(IAst *_PLUS_PLUS) { this->_PLUS_PLUS = _PLUS_PLUS; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        PreIncrementExpression(IToken* leftIToken, IToken* rightIToken,
                               IAst *_PLUS_PLUS,
                               IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_PLUS_PLUS = _PLUS_PLUS;
            ((Ast*) _PLUS_PLUS)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_PLUS_PLUS);
            list.push_back(_UnaryExpression);
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
                _PLUS_PLUS->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 389:  PreDecrementExpression ::= -- UnaryExpression
     *</b>
     */
    struct PreDecrementExpression :public Ast
    {
        IAst *_MINUS_MINUS;
        IAst *_UnaryExpression;

        IAst *getMINUS_MINUS() { return _MINUS_MINUS; };
        void setMINUS_MINUS(IAst *_MINUS_MINUS) { this->_MINUS_MINUS = _MINUS_MINUS; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        PreDecrementExpression(IToken* leftIToken, IToken* rightIToken,
                               IAst *_MINUS_MINUS,
                               IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_MINUS_MINUS = _MINUS_MINUS;
            ((Ast*) _MINUS_MINUS)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MINUS_MINUS);
            list.push_back(_UnaryExpression);
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
                _MINUS_MINUS->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 416:  AndExpression ::= EqualityExpression
     *</em>
     *<p>
     *<b>
     *<li>Rule 417:  AndExpression ::= AndExpression & EqualityExpression
     *</b>
     */
    struct AndExpression :public Ast
    {
        IAst *_AndExpression;
        IAst *_AND;
        IAst *_EqualityExpression;

        IAst *getAndExpression() { return _AndExpression; };
        void setAndExpression(IAst *_AndExpression) { this->_AndExpression = _AndExpression; }
        IAst *getAND() { return _AND; };
        void setAND(IAst *_AND) { this->_AND = _AND; }
        IAst *getEqualityExpression() { return _EqualityExpression; };
        void setEqualityExpression(IAst *_EqualityExpression) { this->_EqualityExpression = _EqualityExpression; }

        AndExpression(IToken* leftIToken, IToken* rightIToken,
                      IAst *_AndExpression,
                      IAst *_AND,
                      IAst *_EqualityExpression):Ast(leftIToken, rightIToken)    {
            this->_AndExpression = _AndExpression;
            ((Ast*) _AndExpression)->setParent(this);
            this->_AND = _AND;
            ((Ast*) _AND)->setParent(this);
            this->_EqualityExpression = _EqualityExpression;
            ((Ast*) _EqualityExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AndExpression);
            list.push_back(_AND);
            list.push_back(_EqualityExpression);
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
                _AndExpression->accept(v);
                _AND->accept(v);
                _EqualityExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 418:  ExclusiveOrExpression ::= AndExpression
     *</em>
     *<p>
     *<b>
     *<li>Rule 419:  ExclusiveOrExpression ::= ExclusiveOrExpression ^ AndExpression
     *</b>
     */
    struct ExclusiveOrExpression :public Ast
    {
        IAst *_ExclusiveOrExpression;
        IAst *_XOR;
        IAst *_AndExpression;

        IAst *getExclusiveOrExpression() { return _ExclusiveOrExpression; };
        void setExclusiveOrExpression(IAst *_ExclusiveOrExpression) { this->_ExclusiveOrExpression = _ExclusiveOrExpression; }
        IAst *getXOR() { return _XOR; };
        void setXOR(IAst *_XOR) { this->_XOR = _XOR; }
        IAst *getAndExpression() { return _AndExpression; };
        void setAndExpression(IAst *_AndExpression) { this->_AndExpression = _AndExpression; }

        ExclusiveOrExpression(IToken* leftIToken, IToken* rightIToken,
                              IAst *_ExclusiveOrExpression,
                              IAst *_XOR,
                              IAst *_AndExpression):Ast(leftIToken, rightIToken)    {
            this->_ExclusiveOrExpression = _ExclusiveOrExpression;
            ((Ast*) _ExclusiveOrExpression)->setParent(this);
            this->_XOR = _XOR;
            ((Ast*) _XOR)->setParent(this);
            this->_AndExpression = _AndExpression;
            ((Ast*) _AndExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ExclusiveOrExpression);
            list.push_back(_XOR);
            list.push_back(_AndExpression);
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
                _ExclusiveOrExpression->accept(v);
                _XOR->accept(v);
                _AndExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 420:  InclusiveOrExpression ::= ExclusiveOrExpression
     *</em>
     *<p>
     *<b>
     *<li>Rule 421:  InclusiveOrExpression ::= InclusiveOrExpression | ExclusiveOrExpression
     *</b>
     */
    struct InclusiveOrExpression :public Ast
    {
        IAst *_InclusiveOrExpression;
        IAst *_OR;
        IAst *_ExclusiveOrExpression;

        IAst *getInclusiveOrExpression() { return _InclusiveOrExpression; };
        void setInclusiveOrExpression(IAst *_InclusiveOrExpression) { this->_InclusiveOrExpression = _InclusiveOrExpression; }
        IAst *getOR() { return _OR; };
        void setOR(IAst *_OR) { this->_OR = _OR; }
        IAst *getExclusiveOrExpression() { return _ExclusiveOrExpression; };
        void setExclusiveOrExpression(IAst *_ExclusiveOrExpression) { this->_ExclusiveOrExpression = _ExclusiveOrExpression; }

        InclusiveOrExpression(IToken* leftIToken, IToken* rightIToken,
                              IAst *_InclusiveOrExpression,
                              IAst *_OR,
                              IAst *_ExclusiveOrExpression):Ast(leftIToken, rightIToken)    {
            this->_InclusiveOrExpression = _InclusiveOrExpression;
            ((Ast*) _InclusiveOrExpression)->setParent(this);
            this->_OR = _OR;
            ((Ast*) _OR)->setParent(this);
            this->_ExclusiveOrExpression = _ExclusiveOrExpression;
            ((Ast*) _ExclusiveOrExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_InclusiveOrExpression);
            list.push_back(_OR);
            list.push_back(_ExclusiveOrExpression);
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
                _InclusiveOrExpression->accept(v);
                _OR->accept(v);
                _ExclusiveOrExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 422:  ConditionalAndExpression ::= InclusiveOrExpression
     *</em>
     *<p>
     *<b>
     *<li>Rule 423:  ConditionalAndExpression ::= ConditionalAndExpression && InclusiveOrExpression
     *</b>
     */
    struct ConditionalAndExpression :public Ast
    {
        IAst *_ConditionalAndExpression;
        IAst *_AND_AND;
        IAst *_InclusiveOrExpression;

        IAst *getConditionalAndExpression() { return _ConditionalAndExpression; };
        void setConditionalAndExpression(IAst *_ConditionalAndExpression) { this->_ConditionalAndExpression = _ConditionalAndExpression; }
        IAst *getAND_AND() { return _AND_AND; };
        void setAND_AND(IAst *_AND_AND) { this->_AND_AND = _AND_AND; }
        IAst *getInclusiveOrExpression() { return _InclusiveOrExpression; };
        void setInclusiveOrExpression(IAst *_InclusiveOrExpression) { this->_InclusiveOrExpression = _InclusiveOrExpression; }

        ConditionalAndExpression(IToken* leftIToken, IToken* rightIToken,
                                 IAst *_ConditionalAndExpression,
                                 IAst *_AND_AND,
                                 IAst *_InclusiveOrExpression):Ast(leftIToken, rightIToken)    {
            this->_ConditionalAndExpression = _ConditionalAndExpression;
            ((Ast*) _ConditionalAndExpression)->setParent(this);
            this->_AND_AND = _AND_AND;
            ((Ast*) _AND_AND)->setParent(this);
            this->_InclusiveOrExpression = _InclusiveOrExpression;
            ((Ast*) _InclusiveOrExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ConditionalAndExpression);
            list.push_back(_AND_AND);
            list.push_back(_InclusiveOrExpression);
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
                _ConditionalAndExpression->accept(v);
                _AND_AND->accept(v);
                _InclusiveOrExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 424:  ConditionalOrExpression ::= ConditionalAndExpression
     *</em>
     *<p>
     *<b>
     *<li>Rule 425:  ConditionalOrExpression ::= ConditionalOrExpression || ConditionalAndExpression
     *</b>
     */
    struct ConditionalOrExpression :public Ast
    {
        IAst *_ConditionalOrExpression;
        IAst *_OR_OR;
        IAst *_ConditionalAndExpression;

        IAst *getConditionalOrExpression() { return _ConditionalOrExpression; };
        void setConditionalOrExpression(IAst *_ConditionalOrExpression) { this->_ConditionalOrExpression = _ConditionalOrExpression; }
        IAst *getOR_OR() { return _OR_OR; };
        void setOR_OR(IAst *_OR_OR) { this->_OR_OR = _OR_OR; }
        IAst *getConditionalAndExpression() { return _ConditionalAndExpression; };
        void setConditionalAndExpression(IAst *_ConditionalAndExpression) { this->_ConditionalAndExpression = _ConditionalAndExpression; }

        ConditionalOrExpression(IToken* leftIToken, IToken* rightIToken,
                                IAst *_ConditionalOrExpression,
                                IAst *_OR_OR,
                                IAst *_ConditionalAndExpression):Ast(leftIToken, rightIToken)    {
            this->_ConditionalOrExpression = _ConditionalOrExpression;
            ((Ast*) _ConditionalOrExpression)->setParent(this);
            this->_OR_OR = _OR_OR;
            ((Ast*) _OR_OR)->setParent(this);
            this->_ConditionalAndExpression = _ConditionalAndExpression;
            ((Ast*) _ConditionalAndExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ConditionalOrExpression);
            list.push_back(_OR_OR);
            list.push_back(_ConditionalAndExpression);
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
                _ConditionalOrExpression->accept(v);
                _OR_OR->accept(v);
                _ConditionalAndExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 426:  ConditionalExpression ::= ConditionalOrExpression
     *</em>
     *<p>
     *<b>
     *<li>Rule 427:  ConditionalExpression ::= ConditionalOrExpression ? Expression : ConditionalExpression
     *</b>
     */
    struct ConditionalExpression :public Ast
    {
        IAst *_ConditionalOrExpression;
        IAst *_QUESTION;
        IAst *_Expression;
        IAst *_COLON;
        IAst *_ConditionalExpression;

        IAst *getConditionalOrExpression() { return _ConditionalOrExpression; };
        void setConditionalOrExpression(IAst *_ConditionalOrExpression) { this->_ConditionalOrExpression = _ConditionalOrExpression; }
        IAst *getQUESTION() { return _QUESTION; };
        void setQUESTION(IAst *_QUESTION) { this->_QUESTION = _QUESTION; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getCOLON() { return _COLON; };
        void setCOLON(IAst *_COLON) { this->_COLON = _COLON; }
        IAst *getConditionalExpression() { return _ConditionalExpression; };
        void setConditionalExpression(IAst *_ConditionalExpression) { this->_ConditionalExpression = _ConditionalExpression; }

        ConditionalExpression(IToken* leftIToken, IToken* rightIToken,
                              IAst *_ConditionalOrExpression,
                              IAst *_QUESTION,
                              IAst *_Expression,
                              IAst *_COLON,
                              IAst *_ConditionalExpression):Ast(leftIToken, rightIToken)    {
            this->_ConditionalOrExpression = _ConditionalOrExpression;
            ((Ast*) _ConditionalOrExpression)->setParent(this);
            this->_QUESTION = _QUESTION;
            ((Ast*) _QUESTION)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_COLON = _COLON;
            ((Ast*) _COLON)->setParent(this);
            this->_ConditionalExpression = _ConditionalExpression;
            ((Ast*) _ConditionalExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ConditionalOrExpression);
            list.push_back(_QUESTION);
            list.push_back(_Expression);
            list.push_back(_COLON);
            list.push_back(_ConditionalExpression);
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
                _ConditionalOrExpression->accept(v);
                _QUESTION->accept(v);
                _Expression->accept(v);
                _COLON->accept(v);
                _ConditionalExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 430:  Assignment ::= LeftHandSide AssignmentOperator AssignmentExpression
     *</b>
     */
    struct Assignment :public Ast
    {
        IAst *_LeftHandSide;
        IAst *_AssignmentOperator;
        IAst *_AssignmentExpression;

        IAst *getLeftHandSide() { return _LeftHandSide; };
        void setLeftHandSide(IAst *_LeftHandSide) { this->_LeftHandSide = _LeftHandSide; }
        IAst *getAssignmentOperator() { return _AssignmentOperator; };
        void setAssignmentOperator(IAst *_AssignmentOperator) { this->_AssignmentOperator = _AssignmentOperator; }
        IAst *getAssignmentExpression() { return _AssignmentExpression; };
        void setAssignmentExpression(IAst *_AssignmentExpression) { this->_AssignmentExpression = _AssignmentExpression; }

        Assignment(IToken* leftIToken, IToken* rightIToken,
                   IAst *_LeftHandSide,
                   IAst *_AssignmentOperator,
                   IAst *_AssignmentExpression):Ast(leftIToken, rightIToken)    {
            this->_LeftHandSide = _LeftHandSide;
            ((Ast*) _LeftHandSide)->setParent(this);
            this->_AssignmentOperator = _AssignmentOperator;
            ((Ast*) _AssignmentOperator)->setParent(this);
            this->_AssignmentExpression = _AssignmentExpression;
            ((Ast*) _AssignmentExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LeftHandSide);
            list.push_back(_AssignmentOperator);
            list.push_back(_AssignmentExpression);
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
                _LeftHandSide->accept(v);
                _AssignmentOperator->accept(v);
                _AssignmentExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<em>
     *<li>Rule 492:  ,opt ::= $Empty
     *</em>
     *<p>
     *<b>
     *<li>Rule 493:  ,opt ::= ,
     *</b>
     */
    struct Commaopt :public AstToken
    {
        IToken* getCOMMA() { return leftIToken; }

        Commaopt(IToken* token) :AstToken(token)
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
     *<em>
     *<li>Rule 504:  ...opt ::= $Empty
     *</em>
     *<p>
     *<b>
     *<li>Rule 505:  ...opt ::= ...
     *</b>
     */
    struct Ellipsisopt :public AstToken
    {
        IToken* getELLIPSIS() { return leftIToken; }

        Ellipsisopt(IToken* token) :AstToken(token)
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
     *<li>Rule 5:  LPGUserAction ::= $BeginAction BlockStatementsopt $EndAction
     *</b>
     */
    struct LPGUserAction0 :public Ast
    {
        IAst *_BeginAction;
        IAst *_BlockStatementsopt;
        IAst *_EndAction;

        IAst *getBeginAction() { return _BeginAction; };
        void setBeginAction(IAst *_BeginAction) { this->_BeginAction = _BeginAction; }
        /**
         * The value returned by <b>getBlockStatementsopt</b> may be <b>nullptr</b>
         */
        IAst *getBlockStatementsopt() { return _BlockStatementsopt; };
        void setBlockStatementsopt(IAst *_BlockStatementsopt) { this->_BlockStatementsopt = _BlockStatementsopt; }
        IAst *getEndAction() { return _EndAction; };
        void setEndAction(IAst *_EndAction) { this->_EndAction = _EndAction; }

        LPGUserAction0(IToken* leftIToken, IToken* rightIToken,
                       IAst *_BeginAction,
                       IAst *_BlockStatementsopt,
                       IAst *_EndAction):Ast(leftIToken, rightIToken)    {
            this->_BeginAction = _BeginAction;
            ((Ast*) _BeginAction)->setParent(this);
            this->_BlockStatementsopt = _BlockStatementsopt;
            if (_BlockStatementsopt != nullptr) ((Ast*) _BlockStatementsopt)->setParent(this);
            this->_EndAction = _EndAction;
            ((Ast*) _EndAction)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_BeginAction);
            list.push_back(_BlockStatementsopt);
            list.push_back(_EndAction);
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
                _BeginAction->accept(v);
                if (_BlockStatementsopt != nullptr) _BlockStatementsopt->accept(v);
                _EndAction->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 6:  LPGUserAction ::= $BeginJava BlockStatementsopt $EndJava
     *</b>
     */
    struct LPGUserAction1 :public Ast
    {
        IAst *_BeginJava;
        IAst *_BlockStatementsopt;
        IAst *_EndJava;

        IAst *getBeginJava() { return _BeginJava; };
        void setBeginJava(IAst *_BeginJava) { this->_BeginJava = _BeginJava; }
        /**
         * The value returned by <b>getBlockStatementsopt</b> may be <b>nullptr</b>
         */
        IAst *getBlockStatementsopt() { return _BlockStatementsopt; };
        void setBlockStatementsopt(IAst *_BlockStatementsopt) { this->_BlockStatementsopt = _BlockStatementsopt; }
        IAst *getEndJava() { return _EndJava; };
        void setEndJava(IAst *_EndJava) { this->_EndJava = _EndJava; }

        LPGUserAction1(IToken* leftIToken, IToken* rightIToken,
                       IAst *_BeginJava,
                       IAst *_BlockStatementsopt,
                       IAst *_EndJava):Ast(leftIToken, rightIToken)    {
            this->_BeginJava = _BeginJava;
            ((Ast*) _BeginJava)->setParent(this);
            this->_BlockStatementsopt = _BlockStatementsopt;
            if (_BlockStatementsopt != nullptr) ((Ast*) _BlockStatementsopt)->setParent(this);
            this->_EndJava = _EndJava;
            ((Ast*) _EndJava)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_BeginJava);
            list.push_back(_BlockStatementsopt);
            list.push_back(_EndJava);
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
                _BeginJava->accept(v);
                if (_BlockStatementsopt != nullptr) _BlockStatementsopt->accept(v);
                _EndJava->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 7:  LPGUserAction ::= $NoAction
     *</b>
     */
    struct LPGUserAction2 :public AstToken
    {
        IToken* getNoAction() { return leftIToken; }

        LPGUserAction2(IToken* token) :AstToken(token)
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
     *<li>Rule 8:  LPGUserAction ::= $NullAction
     *</b>
     */
    struct LPGUserAction3 :public AstToken
    {
        IToken* getNullAction() { return leftIToken; }

        LPGUserAction3(IToken* token) :AstToken(token)
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
     *<li>Rule 9:  LPGUserAction ::= $BadAction
     *</b>
     */
    struct LPGUserAction4 :public AstToken
    {
        IToken* getBadAction() { return leftIToken; }

        LPGUserAction4(IToken* token) :AstToken(token)
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
     *<li>Rule 16:  IntegralType ::= byte
     *</b>
     */
    struct IntegralType0 :public AstToken
    {
        IToken* getbyte() { return leftIToken; }

        IntegralType0(IToken* token) :AstToken(token)
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
     *<li>Rule 17:  IntegralType ::= short
     *</b>
     */
    struct IntegralType1 :public AstToken
    {
        IToken* getshort() { return leftIToken; }

        IntegralType1(IToken* token) :AstToken(token)
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
     *<li>Rule 18:  IntegralType ::= int
     *</b>
     */
    struct IntegralType2 :public AstToken
    {
        IToken* getint() { return leftIToken; }

        IntegralType2(IToken* token) :AstToken(token)
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
     *<li>Rule 19:  IntegralType ::= long
     *</b>
     */
    struct IntegralType3 :public AstToken
    {
        IToken* getlong() { return leftIToken; }

        IntegralType3(IToken* token) :AstToken(token)
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
     *<li>Rule 20:  IntegralType ::= char
     *</b>
     */
    struct IntegralType4 :public AstToken
    {
        IToken* getchar() { return leftIToken; }

        IntegralType4(IToken* token) :AstToken(token)
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
     *<li>Rule 21:  FloatingPointType ::= float
     *</b>
     */
    struct FloatingPointType0 :public AstToken
    {
        IToken* getfloat() { return leftIToken; }

        FloatingPointType0(IToken* token) :AstToken(token)
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
     *<li>Rule 22:  FloatingPointType ::= double
     *</b>
     */
    struct FloatingPointType1 :public AstToken
    {
        IToken* getdouble() { return leftIToken; }

        FloatingPointType1(IToken* token) :AstToken(token)
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
     *<li>Rule 45:  WildcardBounds ::= extends ReferenceType
     *</b>
     */
    struct WildcardBounds0 :public Ast
    {
        IAst *_extends;
        IAst *_ReferenceType;

        IAst *getextends() { return _extends; };
        void setextends(IAst *_extends) { this->_extends = _extends; }
        IAst *getReferenceType() { return _ReferenceType; };
        void setReferenceType(IAst *_ReferenceType) { this->_ReferenceType = _ReferenceType; }

        WildcardBounds0(IToken* leftIToken, IToken* rightIToken,
                        IAst *_extends,
                        IAst *_ReferenceType):Ast(leftIToken, rightIToken)    {
            this->_extends = _extends;
            ((Ast*) _extends)->setParent(this);
            this->_ReferenceType = _ReferenceType;
            ((Ast*) _ReferenceType)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_extends);
            list.push_back(_ReferenceType);
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
                _extends->accept(v);
                _ReferenceType->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 46:  WildcardBounds ::= super ReferenceType
     *</b>
     */
    struct WildcardBounds1 :public Ast
    {
        IAst *_super;
        IAst *_ReferenceType;

        IAst *getsuper() { return _super; };
        void setsuper(IAst *_super) { this->_super = _super; }
        IAst *getReferenceType() { return _ReferenceType; };
        void setReferenceType(IAst *_ReferenceType) { this->_ReferenceType = _ReferenceType; }

        WildcardBounds1(IToken* leftIToken, IToken* rightIToken,
                        IAst *_super,
                        IAst *_ReferenceType):Ast(leftIToken, rightIToken)    {
            this->_super = _super;
            ((Ast*) _super)->setParent(this);
            this->_ReferenceType = _ReferenceType;
            ((Ast*) _ReferenceType)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_super);
            list.push_back(_ReferenceType);
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
                _super->accept(v);
                _ReferenceType->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 80:  ClassModifier ::= public
     *</b>
     */
    struct ClassModifier0 :public AstToken
    {
        IToken* getpublic() { return leftIToken; }

        ClassModifier0(IToken* token) :AstToken(token)
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
     *<li>Rule 81:  ClassModifier ::= protected
     *</b>
     */
    struct ClassModifier1 :public AstToken
    {
        IToken* getprotected() { return leftIToken; }

        ClassModifier1(IToken* token) :AstToken(token)
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
     *<li>Rule 82:  ClassModifier ::= private
     *</b>
     */
    struct ClassModifier2 :public AstToken
    {
        IToken* getprivate() { return leftIToken; }

        ClassModifier2(IToken* token) :AstToken(token)
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
     *<li>Rule 83:  ClassModifier ::= abstract
     *</b>
     */
    struct ClassModifier3 :public AstToken
    {
        IToken* getabstract() { return leftIToken; }

        ClassModifier3(IToken* token) :AstToken(token)
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
     *<li>Rule 84:  ClassModifier ::= static
     *</b>
     */
    struct ClassModifier4 :public AstToken
    {
        IToken* getstatic() { return leftIToken; }

        ClassModifier4(IToken* token) :AstToken(token)
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
     *<li>Rule 85:  ClassModifier ::= final
     *</b>
     */
    struct ClassModifier5 :public AstToken
    {
        IToken* getfinal() { return leftIToken; }

        ClassModifier5(IToken* token) :AstToken(token)
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
     *<li>Rule 86:  ClassModifier ::= strictfp
     *</b>
     */
    struct ClassModifier6 :public AstToken
    {
        IToken* getstrictfp() { return leftIToken; }

        ClassModifier6(IToken* token) :AstToken(token)
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
     *<li>Rule 118:  FieldModifier ::= public
     *</b>
     */
    struct FieldModifier0 :public AstToken
    {
        IToken* getpublic() { return leftIToken; }

        FieldModifier0(IToken* token) :AstToken(token)
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
     *<li>Rule 119:  FieldModifier ::= protected
     *</b>
     */
    struct FieldModifier1 :public AstToken
    {
        IToken* getprotected() { return leftIToken; }

        FieldModifier1(IToken* token) :AstToken(token)
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
     *<li>Rule 120:  FieldModifier ::= private
     *</b>
     */
    struct FieldModifier2 :public AstToken
    {
        IToken* getprivate() { return leftIToken; }

        FieldModifier2(IToken* token) :AstToken(token)
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
     *<li>Rule 121:  FieldModifier ::= static
     *</b>
     */
    struct FieldModifier3 :public AstToken
    {
        IToken* getstatic() { return leftIToken; }

        FieldModifier3(IToken* token) :AstToken(token)
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
     *<li>Rule 122:  FieldModifier ::= final
     *</b>
     */
    struct FieldModifier4 :public AstToken
    {
        IToken* getfinal() { return leftIToken; }

        FieldModifier4(IToken* token) :AstToken(token)
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
     *<li>Rule 123:  FieldModifier ::= transient
     *</b>
     */
    struct FieldModifier5 :public AstToken
    {
        IToken* gettransient() { return leftIToken; }

        FieldModifier5(IToken* token) :AstToken(token)
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
     *<li>Rule 124:  FieldModifier ::= volatile
     *</b>
     */
    struct FieldModifier6 :public AstToken
    {
        IToken* getvolatile() { return leftIToken; }

        FieldModifier6(IToken* token) :AstToken(token)
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
     *<li>Rule 129:  MethodDeclarator ::= identifier ( FormalParameterListopt )
     *</b>
     */
    struct MethodDeclarator0 :public Ast
    {
        IAst *_identifier;
        IAst *_LPAREN;
        IAst *_FormalParameterListopt;
        IAst *_RPAREN;

        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getFormalParameterListopt</b> may be <b>nullptr</b>
         */
        IAst *getFormalParameterListopt() { return _FormalParameterListopt; };
        void setFormalParameterListopt(IAst *_FormalParameterListopt) { this->_FormalParameterListopt = _FormalParameterListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        MethodDeclarator0(IToken* leftIToken, IToken* rightIToken,
                          IAst *_identifier,
                          IAst *_LPAREN,
                          IAst *_FormalParameterListopt,
                          IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_FormalParameterListopt = _FormalParameterListopt;
            if (_FormalParameterListopt != nullptr) ((Ast*) _FormalParameterListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_identifier);
            list.push_back(_LPAREN);
            list.push_back(_FormalParameterListopt);
            list.push_back(_RPAREN);
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
                _identifier->accept(v);
                _LPAREN->accept(v);
                if (_FormalParameterListopt != nullptr) _FormalParameterListopt->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 130:  MethodDeclarator ::= MethodDeclarator [ ]
     *</b>
     */
    struct MethodDeclarator1 :public Ast
    {
        IAst *_MethodDeclarator;
        IAst *_LBRACKET;
        IAst *_RBRACKET;

        IAst *getMethodDeclarator() { return _MethodDeclarator; };
        void setMethodDeclarator(IAst *_MethodDeclarator) { this->_MethodDeclarator = _MethodDeclarator; }
        IAst *getLBRACKET() { return _LBRACKET; };
        void setLBRACKET(IAst *_LBRACKET) { this->_LBRACKET = _LBRACKET; }
        IAst *getRBRACKET() { return _RBRACKET; };
        void setRBRACKET(IAst *_RBRACKET) { this->_RBRACKET = _RBRACKET; }

        MethodDeclarator1(IToken* leftIToken, IToken* rightIToken,
                          IAst *_MethodDeclarator,
                          IAst *_LBRACKET,
                          IAst *_RBRACKET):Ast(leftIToken, rightIToken)    {
            this->_MethodDeclarator = _MethodDeclarator;
            ((Ast*) _MethodDeclarator)->setParent(this);
            this->_LBRACKET = _LBRACKET;
            ((Ast*) _LBRACKET)->setParent(this);
            this->_RBRACKET = _RBRACKET;
            ((Ast*) _RBRACKET)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MethodDeclarator);
            list.push_back(_LBRACKET);
            list.push_back(_RBRACKET);
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
                _MethodDeclarator->accept(v);
                _LBRACKET->accept(v);
                _RBRACKET->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 144:  MethodModifier ::= public
     *</b>
     */
    struct MethodModifier0 :public AstToken
    {
        IToken* getpublic() { return leftIToken; }

        MethodModifier0(IToken* token) :AstToken(token)
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
     *<li>Rule 145:  MethodModifier ::= protected
     *</b>
     */
    struct MethodModifier1 :public AstToken
    {
        IToken* getprotected() { return leftIToken; }

        MethodModifier1(IToken* token) :AstToken(token)
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
     *<li>Rule 146:  MethodModifier ::= private
     *</b>
     */
    struct MethodModifier2 :public AstToken
    {
        IToken* getprivate() { return leftIToken; }

        MethodModifier2(IToken* token) :AstToken(token)
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
     *<li>Rule 147:  MethodModifier ::= abstract
     *</b>
     */
    struct MethodModifier3 :public AstToken
    {
        IToken* getabstract() { return leftIToken; }

        MethodModifier3(IToken* token) :AstToken(token)
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
     *<li>Rule 148:  MethodModifier ::= static
     *</b>
     */
    struct MethodModifier4 :public AstToken
    {
        IToken* getstatic() { return leftIToken; }

        MethodModifier4(IToken* token) :AstToken(token)
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
     *<li>Rule 149:  MethodModifier ::= final
     *</b>
     */
    struct MethodModifier5 :public AstToken
    {
        IToken* getfinal() { return leftIToken; }

        MethodModifier5(IToken* token) :AstToken(token)
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
     *<li>Rule 150:  MethodModifier ::= synchronized
     *</b>
     */
    struct MethodModifier6 :public AstToken
    {
        IToken* getsynchronized() { return leftIToken; }

        MethodModifier6(IToken* token) :AstToken(token)
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
     *<li>Rule 151:  MethodModifier ::= native
     *</b>
     */
    struct MethodModifier7 :public AstToken
    {
        IToken* getnative() { return leftIToken; }

        MethodModifier7(IToken* token) :AstToken(token)
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
     *<li>Rule 152:  MethodModifier ::= strictfp
     *</b>
     */
    struct MethodModifier8 :public AstToken
    {
        IToken* getstrictfp() { return leftIToken; }

        MethodModifier8(IToken* token) :AstToken(token)
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
     *<li>Rule 168:  ConstructorModifier ::= public
     *</b>
     */
    struct ConstructorModifier0 :public AstToken
    {
        IToken* getpublic() { return leftIToken; }

        ConstructorModifier0(IToken* token) :AstToken(token)
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
     *<li>Rule 169:  ConstructorModifier ::= protected
     *</b>
     */
    struct ConstructorModifier1 :public AstToken
    {
        IToken* getprotected() { return leftIToken; }

        ConstructorModifier1(IToken* token) :AstToken(token)
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
     *<li>Rule 170:  ConstructorModifier ::= private
     *</b>
     */
    struct ConstructorModifier2 :public AstToken
    {
        IToken* getprivate() { return leftIToken; }

        ConstructorModifier2(IToken* token) :AstToken(token)
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
     *<li>Rule 172:  ExplicitConstructorInvocation ::= TypeArgumentsopt this ( ArgumentListopt ) ;
     *</b>
     */
    struct ExplicitConstructorInvocation0 :public Ast
    {
        IAst *_TypeArgumentsopt;
        IAst *_this;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;
        IAst *_SEMICOLON;

        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }
        IAst *getthis() { return _this; };
        void setthis(IAst *_this) { this->_this = _this; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        ExplicitConstructorInvocation0(IToken* leftIToken, IToken* rightIToken,
                                       IAst *_TypeArgumentsopt,
                                       IAst *_this,
                                       IAst *_LPAREN,
                                       IAst *_ArgumentListopt,
                                       IAst *_RPAREN,
                                       IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            this->_this = _this;
            ((Ast*) _this)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeArgumentsopt);
            list.push_back(_this);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
            list.push_back(_SEMICOLON);
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
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
                _this->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 173:  ExplicitConstructorInvocation ::= TypeArgumentsopt super ( ArgumentListopt ) ;
     *</b>
     */
    struct ExplicitConstructorInvocation1 :public Ast
    {
        IAst *_TypeArgumentsopt;
        IAst *_super;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;
        IAst *_SEMICOLON;

        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }
        IAst *getsuper() { return _super; };
        void setsuper(IAst *_super) { this->_super = _super; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        ExplicitConstructorInvocation1(IToken* leftIToken, IToken* rightIToken,
                                       IAst *_TypeArgumentsopt,
                                       IAst *_super,
                                       IAst *_LPAREN,
                                       IAst *_ArgumentListopt,
                                       IAst *_RPAREN,
                                       IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            this->_super = _super;
            ((Ast*) _super)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeArgumentsopt);
            list.push_back(_super);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
            list.push_back(_SEMICOLON);
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
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
                _super->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 174:  ExplicitConstructorInvocation ::= Primary . TypeArgumentsopt super ( ArgumentListopt ) ;
     *</b>
     */
    struct ExplicitConstructorInvocation2 :public Ast
    {
        IAst *_Primary;
        IAst *_DOT;
        IAst *_TypeArgumentsopt;
        IAst *_super;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;
        IAst *_SEMICOLON;

        IAst *getPrimary() { return _Primary; };
        void setPrimary(IAst *_Primary) { this->_Primary = _Primary; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }
        IAst *getsuper() { return _super; };
        void setsuper(IAst *_super) { this->_super = _super; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        ExplicitConstructorInvocation2(IToken* leftIToken, IToken* rightIToken,
                                       IAst *_Primary,
                                       IAst *_DOT,
                                       IAst *_TypeArgumentsopt,
                                       IAst *_super,
                                       IAst *_LPAREN,
                                       IAst *_ArgumentListopt,
                                       IAst *_RPAREN,
                                       IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_Primary = _Primary;
            ((Ast*) _Primary)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            this->_super = _super;
            ((Ast*) _super)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Primary);
            list.push_back(_DOT);
            list.push_back(_TypeArgumentsopt);
            list.push_back(_super);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
            list.push_back(_SEMICOLON);
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
                _Primary->accept(v);
                _DOT->accept(v);
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
                _super->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 188:  InterfaceModifier ::= public
     *</b>
     */
    struct InterfaceModifier0 :public AstToken
    {
        IToken* getpublic() { return leftIToken; }

        InterfaceModifier0(IToken* token) :AstToken(token)
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
     *<li>Rule 189:  InterfaceModifier ::= protected
     *</b>
     */
    struct InterfaceModifier1 :public AstToken
    {
        IToken* getprotected() { return leftIToken; }

        InterfaceModifier1(IToken* token) :AstToken(token)
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
     *<li>Rule 190:  InterfaceModifier ::= private
     *</b>
     */
    struct InterfaceModifier2 :public AstToken
    {
        IToken* getprivate() { return leftIToken; }

        InterfaceModifier2(IToken* token) :AstToken(token)
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
     *<li>Rule 191:  InterfaceModifier ::= abstract
     *</b>
     */
    struct InterfaceModifier3 :public AstToken
    {
        IToken* getabstract() { return leftIToken; }

        InterfaceModifier3(IToken* token) :AstToken(token)
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
     *<li>Rule 192:  InterfaceModifier ::= static
     *</b>
     */
    struct InterfaceModifier4 :public AstToken
    {
        IToken* getstatic() { return leftIToken; }

        InterfaceModifier4(IToken* token) :AstToken(token)
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
     *<li>Rule 193:  InterfaceModifier ::= strictfp
     *</b>
     */
    struct InterfaceModifier5 :public AstToken
    {
        IToken* getstrictfp() { return leftIToken; }

        InterfaceModifier5(IToken* token) :AstToken(token)
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
     *<li>Rule 194:  ExtendsInterfaces ::= extends InterfaceType
     *</b>
     */
    struct ExtendsInterfaces0 :public Ast
    {
        IAst *_extends;
        IAst *_InterfaceType;

        IAst *getextends() { return _extends; };
        void setextends(IAst *_extends) { this->_extends = _extends; }
        IAst *getInterfaceType() { return _InterfaceType; };
        void setInterfaceType(IAst *_InterfaceType) { this->_InterfaceType = _InterfaceType; }

        ExtendsInterfaces0(IToken* leftIToken, IToken* rightIToken,
                           IAst *_extends,
                           IAst *_InterfaceType):Ast(leftIToken, rightIToken)    {
            this->_extends = _extends;
            ((Ast*) _extends)->setParent(this);
            this->_InterfaceType = _InterfaceType;
            ((Ast*) _InterfaceType)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_extends);
            list.push_back(_InterfaceType);
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
                _extends->accept(v);
                _InterfaceType->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 195:  ExtendsInterfaces ::= ExtendsInterfaces , InterfaceType
     *</b>
     */
    struct ExtendsInterfaces1 :public Ast
    {
        IAst *_ExtendsInterfaces;
        IAst *_COMMA;
        IAst *_InterfaceType;

        IAst *getExtendsInterfaces() { return _ExtendsInterfaces; };
        void setExtendsInterfaces(IAst *_ExtendsInterfaces) { this->_ExtendsInterfaces = _ExtendsInterfaces; }
        IAst *getCOMMA() { return _COMMA; };
        void setCOMMA(IAst *_COMMA) { this->_COMMA = _COMMA; }
        IAst *getInterfaceType() { return _InterfaceType; };
        void setInterfaceType(IAst *_InterfaceType) { this->_InterfaceType = _InterfaceType; }

        ExtendsInterfaces1(IToken* leftIToken, IToken* rightIToken,
                           IAst *_ExtendsInterfaces,
                           IAst *_COMMA,
                           IAst *_InterfaceType):Ast(leftIToken, rightIToken)    {
            this->_ExtendsInterfaces = _ExtendsInterfaces;
            ((Ast*) _ExtendsInterfaces)->setParent(this);
            this->_COMMA = _COMMA;
            ((Ast*) _COMMA)->setParent(this);
            this->_InterfaceType = _InterfaceType;
            ((Ast*) _InterfaceType)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ExtendsInterfaces);
            list.push_back(_COMMA);
            list.push_back(_InterfaceType);
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
                _ExtendsInterfaces->accept(v);
                _COMMA->accept(v);
                _InterfaceType->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 208:  ConstantModifier ::= public
     *</b>
     */
    struct ConstantModifier0 :public AstToken
    {
        IToken* getpublic() { return leftIToken; }

        ConstantModifier0(IToken* token) :AstToken(token)
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
     *<li>Rule 209:  ConstantModifier ::= static
     *</b>
     */
    struct ConstantModifier1 :public AstToken
    {
        IToken* getstatic() { return leftIToken; }

        ConstantModifier1(IToken* token) :AstToken(token)
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
     *<li>Rule 210:  ConstantModifier ::= final
     *</b>
     */
    struct ConstantModifier2 :public AstToken
    {
        IToken* getfinal() { return leftIToken; }

        ConstantModifier2(IToken* token) :AstToken(token)
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
     *<li>Rule 215:  AbstractMethodModifier ::= public
     *</b>
     */
    struct AbstractMethodModifier0 :public AstToken
    {
        IToken* getpublic() { return leftIToken; }

        AbstractMethodModifier0(IToken* token) :AstToken(token)
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
     *<li>Rule 216:  AbstractMethodModifier ::= abstract
     *</b>
     */
    struct AbstractMethodModifier1 :public AstToken
    {
        IToken* getabstract() { return leftIToken; }

        AbstractMethodModifier1(IToken* token) :AstToken(token)
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
     *<li>Rule 221:  AnnotationTypeElementDeclaration ::= AbstractMethodModifiersopt Type identifier ( ) DefaultValueopt ;
     *</b>
     */
    struct AnnotationTypeElementDeclaration0 :public Ast
    {
        IAst *_AbstractMethodModifiersopt;
        IAst *_Type;
        IAst *_identifier;
        IAst *_LPAREN;
        IAst *_RPAREN;
        IAst *_DefaultValueopt;
        IAst *_SEMICOLON;

        /**
         * The value returned by <b>getAbstractMethodModifiersopt</b> may be <b>nullptr</b>
         */
        IAst *getAbstractMethodModifiersopt() { return _AbstractMethodModifiersopt; };
        void setAbstractMethodModifiersopt(IAst *_AbstractMethodModifiersopt) { this->_AbstractMethodModifiersopt = _AbstractMethodModifiersopt; }
        IAst *getType() { return _Type; };
        void setType(IAst *_Type) { this->_Type = _Type; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        /**
         * The value returned by <b>getDefaultValueopt</b> may be <b>nullptr</b>
         */
        IAst *getDefaultValueopt() { return _DefaultValueopt; };
        void setDefaultValueopt(IAst *_DefaultValueopt) { this->_DefaultValueopt = _DefaultValueopt; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        AnnotationTypeElementDeclaration0(IToken* leftIToken, IToken* rightIToken,
                                          IAst *_AbstractMethodModifiersopt,
                                          IAst *_Type,
                                          IAst *_identifier,
                                          IAst *_LPAREN,
                                          IAst *_RPAREN,
                                          IAst *_DefaultValueopt,
                                          IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_AbstractMethodModifiersopt = _AbstractMethodModifiersopt;
            if (_AbstractMethodModifiersopt != nullptr) ((Ast*) _AbstractMethodModifiersopt)->setParent(this);
            this->_Type = _Type;
            ((Ast*) _Type)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_DefaultValueopt = _DefaultValueopt;
            if (_DefaultValueopt != nullptr) ((Ast*) _DefaultValueopt)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AbstractMethodModifiersopt);
            list.push_back(_Type);
            list.push_back(_identifier);
            list.push_back(_LPAREN);
            list.push_back(_RPAREN);
            list.push_back(_DefaultValueopt);
            list.push_back(_SEMICOLON);
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
                if (_AbstractMethodModifiersopt != nullptr) _AbstractMethodModifiersopt->accept(v);
                _Type->accept(v);
                _identifier->accept(v);
                _LPAREN->accept(v);
                _RPAREN->accept(v);
                if (_DefaultValueopt != nullptr) _DefaultValueopt->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 227:  AnnotationTypeElementDeclaration ::= ;
     *</b>
     */
    struct AnnotationTypeElementDeclaration1 :public AstToken
    {
        IToken* getSEMICOLON() { return leftIToken; }

        AnnotationTypeElementDeclaration1(IToken* token) :AstToken(token)
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
     *<li>Rule 295:  AssertStatement ::= assert Expression ;
     *</b>
     */
    struct AssertStatement0 :public Ast
    {
        IAst *_assert;
        IAst *_Expression;
        IAst *_SEMICOLON;

        IAst *getassert() { return _assert; };
        void setassert(IAst *_assert) { this->_assert = _assert; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        AssertStatement0(IToken* leftIToken, IToken* rightIToken,
                         IAst *_assert,
                         IAst *_Expression,
                         IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_assert = _assert;
            ((Ast*) _assert)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_assert);
            list.push_back(_Expression);
            list.push_back(_SEMICOLON);
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
                _assert->accept(v);
                _Expression->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 296:  AssertStatement ::= assert Expression : Expression ;
     *</b>
     */
    struct AssertStatement1 :public Ast
    {
        IAst *_assert;
        IAst *_Expression;
        IAst *_COLON;
        IAst *_Expression4;
        IAst *_SEMICOLON;

        IAst *getassert() { return _assert; };
        void setassert(IAst *_assert) { this->_assert = _assert; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getCOLON() { return _COLON; };
        void setCOLON(IAst *_COLON) { this->_COLON = _COLON; }
        IAst *getExpression4() { return _Expression4; };
        void setExpression4(IAst *_Expression4) { this->_Expression4 = _Expression4; }
        IAst *getSEMICOLON() { return _SEMICOLON; };
        void setSEMICOLON(IAst *_SEMICOLON) { this->_SEMICOLON = _SEMICOLON; }

        AssertStatement1(IToken* leftIToken, IToken* rightIToken,
                         IAst *_assert,
                         IAst *_Expression,
                         IAst *_COLON,
                         IAst *_Expression4,
                         IAst *_SEMICOLON):Ast(leftIToken, rightIToken)    {
            this->_assert = _assert;
            ((Ast*) _assert)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_COLON = _COLON;
            ((Ast*) _COLON)->setParent(this);
            this->_Expression4 = _Expression4;
            ((Ast*) _Expression4)->setParent(this);
            this->_SEMICOLON = _SEMICOLON;
            ((Ast*) _SEMICOLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_assert);
            list.push_back(_Expression);
            list.push_back(_COLON);
            list.push_back(_Expression4);
            list.push_back(_SEMICOLON);
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
                _assert->accept(v);
                _Expression->accept(v);
                _COLON->accept(v);
                _Expression4->accept(v);
                _SEMICOLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 304:  SwitchLabel ::= case ConstantExpression :
     *</b>
     */
    struct SwitchLabel0 :public Ast
    {
        IAst *_case;
        IAst *_ConstantExpression;
        IAst *_COLON;

        IAst *getcase() { return _case; };
        void setcase(IAst *_case) { this->_case = _case; }
        IAst *getConstantExpression() { return _ConstantExpression; };
        void setConstantExpression(IAst *_ConstantExpression) { this->_ConstantExpression = _ConstantExpression; }
        IAst *getCOLON() { return _COLON; };
        void setCOLON(IAst *_COLON) { this->_COLON = _COLON; }

        SwitchLabel0(IToken* leftIToken, IToken* rightIToken,
                     IAst *_case,
                     IAst *_ConstantExpression,
                     IAst *_COLON):Ast(leftIToken, rightIToken)    {
            this->_case = _case;
            ((Ast*) _case)->setParent(this);
            this->_ConstantExpression = _ConstantExpression;
            ((Ast*) _ConstantExpression)->setParent(this);
            this->_COLON = _COLON;
            ((Ast*) _COLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_case);
            list.push_back(_ConstantExpression);
            list.push_back(_COLON);
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
                _case->accept(v);
                _ConstantExpression->accept(v);
                _COLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 305:  SwitchLabel ::= case EnumConstant :
     *</b>
     */
    struct SwitchLabel1 :public Ast
    {
        IAst *_case;
        IAst *_EnumConstant;
        IAst *_COLON;

        IAst *getcase() { return _case; };
        void setcase(IAst *_case) { this->_case = _case; }
        IAst *getEnumConstant() { return _EnumConstant; };
        void setEnumConstant(IAst *_EnumConstant) { this->_EnumConstant = _EnumConstant; }
        IAst *getCOLON() { return _COLON; };
        void setCOLON(IAst *_COLON) { this->_COLON = _COLON; }

        SwitchLabel1(IToken* leftIToken, IToken* rightIToken,
                     IAst *_case,
                     IAst *_EnumConstant,
                     IAst *_COLON):Ast(leftIToken, rightIToken)    {
            this->_case = _case;
            ((Ast*) _case)->setParent(this);
            this->_EnumConstant = _EnumConstant;
            ((Ast*) _EnumConstant)->setParent(this);
            this->_COLON = _COLON;
            ((Ast*) _COLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_case);
            list.push_back(_EnumConstant);
            list.push_back(_COLON);
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
                _case->accept(v);
                _EnumConstant->accept(v);
                _COLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 306:  SwitchLabel ::= default :
     *</b>
     */
    struct SwitchLabel2 :public Ast
    {
        IAst *_default;
        IAst *_COLON;

        IAst *getdefault() { return _default; };
        void setdefault(IAst *_default) { this->_default = _default; }
        IAst *getCOLON() { return _COLON; };
        void setCOLON(IAst *_COLON) { this->_COLON = _COLON; }

        SwitchLabel2(IToken* leftIToken, IToken* rightIToken,
                     IAst *_default,
                     IAst *_COLON):Ast(leftIToken, rightIToken)    {
            this->_default = _default;
            ((Ast*) _default)->setParent(this);
            this->_COLON = _COLON;
            ((Ast*) _COLON)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_default);
            list.push_back(_COLON);
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
                _default->accept(v);
                _COLON->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 326:  TryStatement ::= try Block Catches
     *</b>
     */
    struct TryStatement0 :public Ast
    {
        IAst *m_try;
        IAst *_Block;
        IAst *_Catches;

        IAst *gettry() { return m_try; };
        void settry(IAst *m_try) { this->m_try = m_try; }
        IAst *getBlock() { return _Block; };
        void setBlock(IAst *_Block) { this->_Block = _Block; }
        IAst *getCatches() { return _Catches; };
        void setCatches(IAst *_Catches) { this->_Catches = _Catches; }

        TryStatement0(IToken* leftIToken, IToken* rightIToken,
                      IAst *m_try,
                      IAst *_Block,
                      IAst *_Catches):Ast(leftIToken, rightIToken)    {
            this->m_try = m_try;
            ((Ast*) m_try)->setParent(this);
            this->_Block = _Block;
            ((Ast*) _Block)->setParent(this);
            this->_Catches = _Catches;
            ((Ast*) _Catches)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(m_try);
            list.push_back(_Block);
            list.push_back(_Catches);
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
                m_try->accept(v);
                _Block->accept(v);
                _Catches->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 327:  TryStatement ::= try Block Catchesopt Finally
     *</b>
     */
    struct TryStatement1 :public Ast
    {
        IAst *m_try;
        IAst *_Block;
        IAst *_Catchesopt;
        IAst *_Finally;

        IAst *gettry() { return m_try; };
        void settry(IAst *m_try) { this->m_try = m_try; }
        IAst *getBlock() { return _Block; };
        void setBlock(IAst *_Block) { this->_Block = _Block; }
        /**
         * The value returned by <b>getCatchesopt</b> may be <b>nullptr</b>
         */
        IAst *getCatchesopt() { return _Catchesopt; };
        void setCatchesopt(IAst *_Catchesopt) { this->_Catchesopt = _Catchesopt; }
        IAst *getFinally() { return _Finally; };
        void setFinally(IAst *_Finally) { this->_Finally = _Finally; }

        TryStatement1(IToken* leftIToken, IToken* rightIToken,
                      IAst *m_try,
                      IAst *_Block,
                      IAst *_Catchesopt,
                      IAst *_Finally):Ast(leftIToken, rightIToken)    {
            this->m_try = m_try;
            ((Ast*) m_try)->setParent(this);
            this->_Block = _Block;
            ((Ast*) _Block)->setParent(this);
            this->_Catchesopt = _Catchesopt;
            if (_Catchesopt != nullptr) ((Ast*) _Catchesopt)->setParent(this);
            this->_Finally = _Finally;
            ((Ast*) _Finally)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(m_try);
            list.push_back(_Block);
            list.push_back(_Catchesopt);
            list.push_back(_Finally);
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
                m_try->accept(v);
                _Block->accept(v);
                if (_Catchesopt != nullptr) _Catchesopt->accept(v);
                _Finally->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 335:  PrimaryNoNewArray ::= Type . class
     *</b>
     */
    struct PrimaryNoNewArray0 :public Ast
    {
        IAst *_Type;
        IAst *_DOT;
        IAst *_class;

        IAst *getType() { return _Type; };
        void setType(IAst *_Type) { this->_Type = _Type; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getclass() { return _class; };
        void setclass(IAst *_class) { this->_class = _class; }

        PrimaryNoNewArray0(IToken* leftIToken, IToken* rightIToken,
                           IAst *_Type,
                           IAst *_DOT,
                           IAst *_class):Ast(leftIToken, rightIToken)    {
            this->_Type = _Type;
            ((Ast*) _Type)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_class = _class;
            ((Ast*) _class)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Type);
            list.push_back(_DOT);
            list.push_back(_class);
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
                _Type->accept(v);
                _DOT->accept(v);
                _class->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 336:  PrimaryNoNewArray ::= void . class
     *</b>
     */
    struct PrimaryNoNewArray1 :public Ast
    {
        IAst *_void;
        IAst *_DOT;
        IAst *_class;

        IAst *getvoid() { return _void; };
        void setvoid(IAst *_void) { this->_void = _void; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getclass() { return _class; };
        void setclass(IAst *_class) { this->_class = _class; }

        PrimaryNoNewArray1(IToken* leftIToken, IToken* rightIToken,
                           IAst *_void,
                           IAst *_DOT,
                           IAst *_class):Ast(leftIToken, rightIToken)    {
            this->_void = _void;
            ((Ast*) _void)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_class = _class;
            ((Ast*) _class)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_void);
            list.push_back(_DOT);
            list.push_back(_class);
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
                _void->accept(v);
                _DOT->accept(v);
                _class->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 337:  PrimaryNoNewArray ::= this
     *</b>
     */
    struct PrimaryNoNewArray2 :public AstToken
    {
        IToken* getthis() { return leftIToken; }

        PrimaryNoNewArray2(IToken* token) :AstToken(token)
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
     *<li>Rule 338:  PrimaryNoNewArray ::= ClassName . this
     *</b>
     */
    struct PrimaryNoNewArray3 :public Ast
    {
        IAst *_ClassName;
        IAst *_DOT;
        IAst *_this;

        IAst *getClassName() { return _ClassName; };
        void setClassName(IAst *_ClassName) { this->_ClassName = _ClassName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getthis() { return _this; };
        void setthis(IAst *_this) { this->_this = _this; }

        PrimaryNoNewArray3(IToken* leftIToken, IToken* rightIToken,
                           IAst *_ClassName,
                           IAst *_DOT,
                           IAst *_this):Ast(leftIToken, rightIToken)    {
            this->_ClassName = _ClassName;
            ((Ast*) _ClassName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_this = _this;
            ((Ast*) _this)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ClassName);
            list.push_back(_DOT);
            list.push_back(_this);
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
                _ClassName->accept(v);
                _DOT->accept(v);
                _this->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 339:  PrimaryNoNewArray ::= ( Expression )
     *</b>
     */
    struct PrimaryNoNewArray4 :public Ast
    {
        IAst *_LPAREN;
        IAst *_Expression;
        IAst *_RPAREN;

        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        PrimaryNoNewArray4(IToken* leftIToken, IToken* rightIToken,
                           IAst *_LPAREN,
                           IAst *_Expression,
                           IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LPAREN);
            list.push_back(_Expression);
            list.push_back(_RPAREN);
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
                _LPAREN->accept(v);
                _Expression->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 344:  Literal ::= IntegerLiteral
     *</b>
     */
    struct Literal0 :public AstToken
    {
        IToken* getIntegerLiteral() { return leftIToken; }

        Literal0(IToken* token) :AstToken(token)
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
     *<li>Rule 345:  Literal ::= LongLiteral
     *</b>
     */
    struct Literal1 :public AstToken
    {
        IToken* getLongLiteral() { return leftIToken; }

        Literal1(IToken* token) :AstToken(token)
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
     *<li>Rule 346:  Literal ::= FloatingPointLiteral
     *</b>
     */
    struct Literal2 :public AstToken
    {
        IToken* getFloatingPointLiteral() { return leftIToken; }

        Literal2(IToken* token) :AstToken(token)
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
     *<li>Rule 347:  Literal ::= DoubleLiteral
     *</b>
     */
    struct Literal3 :public AstToken
    {
        IToken* getDoubleLiteral() { return leftIToken; }

        Literal3(IToken* token) :AstToken(token)
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
     *<li>Rule 349:  Literal ::= CharacterLiteral
     *</b>
     */
    struct Literal4 :public AstToken
    {
        IToken* getCharacterLiteral() { return leftIToken; }

        Literal4(IToken* token) :AstToken(token)
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
     *<li>Rule 350:  Literal ::= StringLiteral
     *</b>
     */
    struct Literal5 :public AstToken
    {
        IToken* getStringLiteral() { return leftIToken; }

        Literal5(IToken* token) :AstToken(token)
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
     *<li>Rule 351:  Literal ::= null
     *</b>
     */
    struct Literal6 :public AstToken
    {
        IToken* getnull() { return leftIToken; }

        Literal6(IToken* token) :AstToken(token)
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
     *<li>Rule 352:  BooleanLiteral ::= true
     *</b>
     */
    struct BooleanLiteral0 :public AstToken
    {
        IToken* gettrue() { return leftIToken; }

        BooleanLiteral0(IToken* token) :AstToken(token)
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
     *<li>Rule 353:  BooleanLiteral ::= false
     *</b>
     */
    struct BooleanLiteral1 :public AstToken
    {
        IToken* getfalse() { return leftIToken; }

        BooleanLiteral1(IToken* token) :AstToken(token)
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
     *<li>Rule 354:  ClassInstanceCreationExpression ::= new TypeArgumentsopt ClassOrInterfaceType TypeArgumentsopt ( ArgumentListopt ) ClassBodyopt
     *</b>
     */
    struct ClassInstanceCreationExpression0 :public Ast
    {
        IAst *_new;
        IAst *_TypeArgumentsopt;
        IAst *_ClassOrInterfaceType;
        IAst *_TypeArgumentsopt4;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;
        IAst *_ClassBodyopt;

        IAst *getnew() { return _new; };
        void setnew(IAst *_new) { this->_new = _new; }
        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }
        IAst *getClassOrInterfaceType() { return _ClassOrInterfaceType; };
        void setClassOrInterfaceType(IAst *_ClassOrInterfaceType) { this->_ClassOrInterfaceType = _ClassOrInterfaceType; }
        /**
         * The value returned by <b>getTypeArgumentsopt4</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt4() { return _TypeArgumentsopt4; };
        void setTypeArgumentsopt4(IAst *_TypeArgumentsopt4) { this->_TypeArgumentsopt4 = _TypeArgumentsopt4; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        /**
         * The value returned by <b>getClassBodyopt</b> may be <b>nullptr</b>
         */
        IAst *getClassBodyopt() { return _ClassBodyopt; };
        void setClassBodyopt(IAst *_ClassBodyopt) { this->_ClassBodyopt = _ClassBodyopt; }

        ClassInstanceCreationExpression0(IToken* leftIToken, IToken* rightIToken,
                                         IAst *_new,
                                         IAst *_TypeArgumentsopt,
                                         IAst *_ClassOrInterfaceType,
                                         IAst *_TypeArgumentsopt4,
                                         IAst *_LPAREN,
                                         IAst *_ArgumentListopt,
                                         IAst *_RPAREN,
                                         IAst *_ClassBodyopt):Ast(leftIToken, rightIToken)    {
            this->_new = _new;
            ((Ast*) _new)->setParent(this);
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            this->_ClassOrInterfaceType = _ClassOrInterfaceType;
            ((Ast*) _ClassOrInterfaceType)->setParent(this);
            this->_TypeArgumentsopt4 = _TypeArgumentsopt4;
            if (_TypeArgumentsopt4 != nullptr) ((Ast*) _TypeArgumentsopt4)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_ClassBodyopt = _ClassBodyopt;
            if (_ClassBodyopt != nullptr) ((Ast*) _ClassBodyopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_new);
            list.push_back(_TypeArgumentsopt);
            list.push_back(_ClassOrInterfaceType);
            list.push_back(_TypeArgumentsopt4);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
            list.push_back(_ClassBodyopt);
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
                _new->accept(v);
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
                _ClassOrInterfaceType->accept(v);
                if (_TypeArgumentsopt4 != nullptr) _TypeArgumentsopt4->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
                if (_ClassBodyopt != nullptr) _ClassBodyopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 355:  ClassInstanceCreationExpression ::= Primary . new TypeArgumentsopt identifier TypeArgumentsopt ( ArgumentListopt ) ClassBodyopt
     *</b>
     */
    struct ClassInstanceCreationExpression1 :public Ast
    {
        IAst *_Primary;
        IAst *_DOT;
        IAst *_new;
        IAst *_TypeArgumentsopt;
        IAst *_identifier;
        IAst *_TypeArgumentsopt6;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;
        IAst *_ClassBodyopt;

        IAst *getPrimary() { return _Primary; };
        void setPrimary(IAst *_Primary) { this->_Primary = _Primary; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getnew() { return _new; };
        void setnew(IAst *_new) { this->_new = _new; }
        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        /**
         * The value returned by <b>getTypeArgumentsopt6</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt6() { return _TypeArgumentsopt6; };
        void setTypeArgumentsopt6(IAst *_TypeArgumentsopt6) { this->_TypeArgumentsopt6 = _TypeArgumentsopt6; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        /**
         * The value returned by <b>getClassBodyopt</b> may be <b>nullptr</b>
         */
        IAst *getClassBodyopt() { return _ClassBodyopt; };
        void setClassBodyopt(IAst *_ClassBodyopt) { this->_ClassBodyopt = _ClassBodyopt; }

        ClassInstanceCreationExpression1(IToken* leftIToken, IToken* rightIToken,
                                         IAst *_Primary,
                                         IAst *_DOT,
                                         IAst *_new,
                                         IAst *_TypeArgumentsopt,
                                         IAst *_identifier,
                                         IAst *_TypeArgumentsopt6,
                                         IAst *_LPAREN,
                                         IAst *_ArgumentListopt,
                                         IAst *_RPAREN,
                                         IAst *_ClassBodyopt):Ast(leftIToken, rightIToken)    {
            this->_Primary = _Primary;
            ((Ast*) _Primary)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_new = _new;
            ((Ast*) _new)->setParent(this);
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_TypeArgumentsopt6 = _TypeArgumentsopt6;
            if (_TypeArgumentsopt6 != nullptr) ((Ast*) _TypeArgumentsopt6)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_ClassBodyopt = _ClassBodyopt;
            if (_ClassBodyopt != nullptr) ((Ast*) _ClassBodyopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Primary);
            list.push_back(_DOT);
            list.push_back(_new);
            list.push_back(_TypeArgumentsopt);
            list.push_back(_identifier);
            list.push_back(_TypeArgumentsopt6);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
            list.push_back(_ClassBodyopt);
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
                _Primary->accept(v);
                _DOT->accept(v);
                _new->accept(v);
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
                _identifier->accept(v);
                if (_TypeArgumentsopt6 != nullptr) _TypeArgumentsopt6->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
                if (_ClassBodyopt != nullptr) _ClassBodyopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 358:  ArrayCreationExpression ::= new PrimitiveType DimExprs Dimsopt
     *</b>
     */
    struct ArrayCreationExpression0 :public Ast
    {
        IAst *_new;
        IAst *_PrimitiveType;
        IAst *_DimExprs;
        IAst *_Dimsopt;

        IAst *getnew() { return _new; };
        void setnew(IAst *_new) { this->_new = _new; }
        IAst *getPrimitiveType() { return _PrimitiveType; };
        void setPrimitiveType(IAst *_PrimitiveType) { this->_PrimitiveType = _PrimitiveType; }
        IAst *getDimExprs() { return _DimExprs; };
        void setDimExprs(IAst *_DimExprs) { this->_DimExprs = _DimExprs; }
        /**
         * The value returned by <b>getDimsopt</b> may be <b>nullptr</b>
         */
        IAst *getDimsopt() { return _Dimsopt; };
        void setDimsopt(IAst *_Dimsopt) { this->_Dimsopt = _Dimsopt; }

        ArrayCreationExpression0(IToken* leftIToken, IToken* rightIToken,
                                 IAst *_new,
                                 IAst *_PrimitiveType,
                                 IAst *_DimExprs,
                                 IAst *_Dimsopt):Ast(leftIToken, rightIToken)    {
            this->_new = _new;
            ((Ast*) _new)->setParent(this);
            this->_PrimitiveType = _PrimitiveType;
            ((Ast*) _PrimitiveType)->setParent(this);
            this->_DimExprs = _DimExprs;
            ((Ast*) _DimExprs)->setParent(this);
            this->_Dimsopt = _Dimsopt;
            if (_Dimsopt != nullptr) ((Ast*) _Dimsopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_new);
            list.push_back(_PrimitiveType);
            list.push_back(_DimExprs);
            list.push_back(_Dimsopt);
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
                _new->accept(v);
                _PrimitiveType->accept(v);
                _DimExprs->accept(v);
                if (_Dimsopt != nullptr) _Dimsopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 359:  ArrayCreationExpression ::= new ClassOrInterfaceType DimExprs Dimsopt
     *</b>
     */
    struct ArrayCreationExpression1 :public Ast
    {
        IAst *_new;
        IAst *_ClassOrInterfaceType;
        IAst *_DimExprs;
        IAst *_Dimsopt;

        IAst *getnew() { return _new; };
        void setnew(IAst *_new) { this->_new = _new; }
        IAst *getClassOrInterfaceType() { return _ClassOrInterfaceType; };
        void setClassOrInterfaceType(IAst *_ClassOrInterfaceType) { this->_ClassOrInterfaceType = _ClassOrInterfaceType; }
        IAst *getDimExprs() { return _DimExprs; };
        void setDimExprs(IAst *_DimExprs) { this->_DimExprs = _DimExprs; }
        /**
         * The value returned by <b>getDimsopt</b> may be <b>nullptr</b>
         */
        IAst *getDimsopt() { return _Dimsopt; };
        void setDimsopt(IAst *_Dimsopt) { this->_Dimsopt = _Dimsopt; }

        ArrayCreationExpression1(IToken* leftIToken, IToken* rightIToken,
                                 IAst *_new,
                                 IAst *_ClassOrInterfaceType,
                                 IAst *_DimExprs,
                                 IAst *_Dimsopt):Ast(leftIToken, rightIToken)    {
            this->_new = _new;
            ((Ast*) _new)->setParent(this);
            this->_ClassOrInterfaceType = _ClassOrInterfaceType;
            ((Ast*) _ClassOrInterfaceType)->setParent(this);
            this->_DimExprs = _DimExprs;
            ((Ast*) _DimExprs)->setParent(this);
            this->_Dimsopt = _Dimsopt;
            if (_Dimsopt != nullptr) ((Ast*) _Dimsopt)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_new);
            list.push_back(_ClassOrInterfaceType);
            list.push_back(_DimExprs);
            list.push_back(_Dimsopt);
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
                _new->accept(v);
                _ClassOrInterfaceType->accept(v);
                _DimExprs->accept(v);
                if (_Dimsopt != nullptr) _Dimsopt->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 360:  ArrayCreationExpression ::= new PrimitiveType Dims ArrayInitializer
     *</b>
     */
    struct ArrayCreationExpression2 :public Ast
    {
        IAst *_new;
        IAst *_PrimitiveType;
        IAst *_Dims;
        IAst *_ArrayInitializer;

        IAst *getnew() { return _new; };
        void setnew(IAst *_new) { this->_new = _new; }
        IAst *getPrimitiveType() { return _PrimitiveType; };
        void setPrimitiveType(IAst *_PrimitiveType) { this->_PrimitiveType = _PrimitiveType; }
        IAst *getDims() { return _Dims; };
        void setDims(IAst *_Dims) { this->_Dims = _Dims; }
        IAst *getArrayInitializer() { return _ArrayInitializer; };
        void setArrayInitializer(IAst *_ArrayInitializer) { this->_ArrayInitializer = _ArrayInitializer; }

        ArrayCreationExpression2(IToken* leftIToken, IToken* rightIToken,
                                 IAst *_new,
                                 IAst *_PrimitiveType,
                                 IAst *_Dims,
                                 IAst *_ArrayInitializer):Ast(leftIToken, rightIToken)    {
            this->_new = _new;
            ((Ast*) _new)->setParent(this);
            this->_PrimitiveType = _PrimitiveType;
            ((Ast*) _PrimitiveType)->setParent(this);
            this->_Dims = _Dims;
            ((Ast*) _Dims)->setParent(this);
            this->_ArrayInitializer = _ArrayInitializer;
            ((Ast*) _ArrayInitializer)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_new);
            list.push_back(_PrimitiveType);
            list.push_back(_Dims);
            list.push_back(_ArrayInitializer);
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
                _new->accept(v);
                _PrimitiveType->accept(v);
                _Dims->accept(v);
                _ArrayInitializer->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 361:  ArrayCreationExpression ::= new ClassOrInterfaceType Dims ArrayInitializer
     *</b>
     */
    struct ArrayCreationExpression3 :public Ast
    {
        IAst *_new;
        IAst *_ClassOrInterfaceType;
        IAst *_Dims;
        IAst *_ArrayInitializer;

        IAst *getnew() { return _new; };
        void setnew(IAst *_new) { this->_new = _new; }
        IAst *getClassOrInterfaceType() { return _ClassOrInterfaceType; };
        void setClassOrInterfaceType(IAst *_ClassOrInterfaceType) { this->_ClassOrInterfaceType = _ClassOrInterfaceType; }
        IAst *getDims() { return _Dims; };
        void setDims(IAst *_Dims) { this->_Dims = _Dims; }
        IAst *getArrayInitializer() { return _ArrayInitializer; };
        void setArrayInitializer(IAst *_ArrayInitializer) { this->_ArrayInitializer = _ArrayInitializer; }

        ArrayCreationExpression3(IToken* leftIToken, IToken* rightIToken,
                                 IAst *_new,
                                 IAst *_ClassOrInterfaceType,
                                 IAst *_Dims,
                                 IAst *_ArrayInitializer):Ast(leftIToken, rightIToken)    {
            this->_new = _new;
            ((Ast*) _new)->setParent(this);
            this->_ClassOrInterfaceType = _ClassOrInterfaceType;
            ((Ast*) _ClassOrInterfaceType)->setParent(this);
            this->_Dims = _Dims;
            ((Ast*) _Dims)->setParent(this);
            this->_ArrayInitializer = _ArrayInitializer;
            ((Ast*) _ArrayInitializer)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_new);
            list.push_back(_ClassOrInterfaceType);
            list.push_back(_Dims);
            list.push_back(_ArrayInitializer);
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
                _new->accept(v);
                _ClassOrInterfaceType->accept(v);
                _Dims->accept(v);
                _ArrayInitializer->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 365:  Dims ::= [ ]
     *</b>
     */
    struct Dims0 :public Ast
    {
        IAst *_LBRACKET;
        IAst *_RBRACKET;

        IAst *getLBRACKET() { return _LBRACKET; };
        void setLBRACKET(IAst *_LBRACKET) { this->_LBRACKET = _LBRACKET; }
        IAst *getRBRACKET() { return _RBRACKET; };
        void setRBRACKET(IAst *_RBRACKET) { this->_RBRACKET = _RBRACKET; }

        Dims0(IToken* leftIToken, IToken* rightIToken,
              IAst *_LBRACKET,
              IAst *_RBRACKET):Ast(leftIToken, rightIToken)    {
            this->_LBRACKET = _LBRACKET;
            ((Ast*) _LBRACKET)->setParent(this);
            this->_RBRACKET = _RBRACKET;
            ((Ast*) _RBRACKET)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LBRACKET);
            list.push_back(_RBRACKET);
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
                _LBRACKET->accept(v);
                _RBRACKET->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 366:  Dims ::= Dims [ ]
     *</b>
     */
    struct Dims1 :public Ast
    {
        IAst *_Dims;
        IAst *_LBRACKET;
        IAst *_RBRACKET;

        IAst *getDims() { return _Dims; };
        void setDims(IAst *_Dims) { this->_Dims = _Dims; }
        IAst *getLBRACKET() { return _LBRACKET; };
        void setLBRACKET(IAst *_LBRACKET) { this->_LBRACKET = _LBRACKET; }
        IAst *getRBRACKET() { return _RBRACKET; };
        void setRBRACKET(IAst *_RBRACKET) { this->_RBRACKET = _RBRACKET; }

        Dims1(IToken* leftIToken, IToken* rightIToken,
              IAst *_Dims,
              IAst *_LBRACKET,
              IAst *_RBRACKET):Ast(leftIToken, rightIToken)    {
            this->_Dims = _Dims;
            ((Ast*) _Dims)->setParent(this);
            this->_LBRACKET = _LBRACKET;
            ((Ast*) _LBRACKET)->setParent(this);
            this->_RBRACKET = _RBRACKET;
            ((Ast*) _RBRACKET)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Dims);
            list.push_back(_LBRACKET);
            list.push_back(_RBRACKET);
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
                _Dims->accept(v);
                _LBRACKET->accept(v);
                _RBRACKET->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 367:  FieldAccess ::= Primary . identifier
     *</b>
     */
    struct FieldAccess0 :public Ast
    {
        IAst *_Primary;
        IAst *_DOT;
        IAst *_identifier;

        IAst *getPrimary() { return _Primary; };
        void setPrimary(IAst *_Primary) { this->_Primary = _Primary; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }

        FieldAccess0(IToken* leftIToken, IToken* rightIToken,
                     IAst *_Primary,
                     IAst *_DOT,
                     IAst *_identifier):Ast(leftIToken, rightIToken)    {
            this->_Primary = _Primary;
            ((Ast*) _Primary)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Primary);
            list.push_back(_DOT);
            list.push_back(_identifier);
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
                _Primary->accept(v);
                _DOT->accept(v);
                _identifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 368:  FieldAccess ::= super . identifier
     *</b>
     */
    struct FieldAccess1 :public Ast
    {
        IAst *_super;
        IAst *_DOT;
        IAst *_identifier;

        IAst *getsuper() { return _super; };
        void setsuper(IAst *_super) { this->_super = _super; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }

        FieldAccess1(IToken* leftIToken, IToken* rightIToken,
                     IAst *_super,
                     IAst *_DOT,
                     IAst *_identifier):Ast(leftIToken, rightIToken)    {
            this->_super = _super;
            ((Ast*) _super)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_super);
            list.push_back(_DOT);
            list.push_back(_identifier);
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
                _super->accept(v);
                _DOT->accept(v);
                _identifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 369:  FieldAccess ::= ClassName . super . identifier
     *</b>
     */
    struct FieldAccess2 :public Ast
    {
        IAst *_ClassName;
        IAst *_DOT;
        IAst *_super;
        IAst *_DOT4;
        IAst *_identifier;

        IAst *getClassName() { return _ClassName; };
        void setClassName(IAst *_ClassName) { this->_ClassName = _ClassName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getsuper() { return _super; };
        void setsuper(IAst *_super) { this->_super = _super; }
        IAst *getDOT4() { return _DOT4; };
        void setDOT4(IAst *_DOT4) { this->_DOT4 = _DOT4; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }

        FieldAccess2(IToken* leftIToken, IToken* rightIToken,
                     IAst *_ClassName,
                     IAst *_DOT,
                     IAst *_super,
                     IAst *_DOT4,
                     IAst *_identifier):Ast(leftIToken, rightIToken)    {
            this->_ClassName = _ClassName;
            ((Ast*) _ClassName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_super = _super;
            ((Ast*) _super)->setParent(this);
            this->_DOT4 = _DOT4;
            ((Ast*) _DOT4)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ClassName);
            list.push_back(_DOT);
            list.push_back(_super);
            list.push_back(_DOT4);
            list.push_back(_identifier);
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
                _ClassName->accept(v);
                _DOT->accept(v);
                _super->accept(v);
                _DOT4->accept(v);
                _identifier->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 370:  MethodInvocation ::= MethodName ( ArgumentListopt )
     *</b>
     */
    struct MethodInvocation0 :public Ast
    {
        IAst *_MethodName;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;

        IAst *getMethodName() { return _MethodName; };
        void setMethodName(IAst *_MethodName) { this->_MethodName = _MethodName; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        MethodInvocation0(IToken* leftIToken, IToken* rightIToken,
                          IAst *_MethodName,
                          IAst *_LPAREN,
                          IAst *_ArgumentListopt,
                          IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_MethodName = _MethodName;
            ((Ast*) _MethodName)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MethodName);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
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
                _MethodName->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 371:  MethodInvocation ::= Primary . TypeArgumentsopt identifier ( ArgumentListopt )
     *</b>
     */
    struct MethodInvocation1 :public Ast
    {
        IAst *_Primary;
        IAst *_DOT;
        IAst *_TypeArgumentsopt;
        IAst *_identifier;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;

        IAst *getPrimary() { return _Primary; };
        void setPrimary(IAst *_Primary) { this->_Primary = _Primary; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        MethodInvocation1(IToken* leftIToken, IToken* rightIToken,
                          IAst *_Primary,
                          IAst *_DOT,
                          IAst *_TypeArgumentsopt,
                          IAst *_identifier,
                          IAst *_LPAREN,
                          IAst *_ArgumentListopt,
                          IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_Primary = _Primary;
            ((Ast*) _Primary)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_Primary);
            list.push_back(_DOT);
            list.push_back(_TypeArgumentsopt);
            list.push_back(_identifier);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
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
                _Primary->accept(v);
                _DOT->accept(v);
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
                _identifier->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 372:  MethodInvocation ::= super . TypeArgumentsopt identifier ( ArgumentListopt )
     *</b>
     */
    struct MethodInvocation2 :public Ast
    {
        IAst *_super;
        IAst *_DOT;
        IAst *_TypeArgumentsopt;
        IAst *_identifier;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;

        IAst *getsuper() { return _super; };
        void setsuper(IAst *_super) { this->_super = _super; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        MethodInvocation2(IToken* leftIToken, IToken* rightIToken,
                          IAst *_super,
                          IAst *_DOT,
                          IAst *_TypeArgumentsopt,
                          IAst *_identifier,
                          IAst *_LPAREN,
                          IAst *_ArgumentListopt,
                          IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_super = _super;
            ((Ast*) _super)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_super);
            list.push_back(_DOT);
            list.push_back(_TypeArgumentsopt);
            list.push_back(_identifier);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
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
                _super->accept(v);
                _DOT->accept(v);
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
                _identifier->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 373:  MethodInvocation ::= ClassName . super . TypeArgumentsopt identifier ( ArgumentListopt )
     *</b>
     */
    struct MethodInvocation3 :public Ast
    {
        IAst *_ClassName;
        IAst *_DOT;
        IAst *_super;
        IAst *_DOT4;
        IAst *_TypeArgumentsopt;
        IAst *_identifier;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;

        IAst *getClassName() { return _ClassName; };
        void setClassName(IAst *_ClassName) { this->_ClassName = _ClassName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getsuper() { return _super; };
        void setsuper(IAst *_super) { this->_super = _super; }
        IAst *getDOT4() { return _DOT4; };
        void setDOT4(IAst *_DOT4) { this->_DOT4 = _DOT4; }
        /**
         * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
         */
        IAst *getTypeArgumentsopt() { return _TypeArgumentsopt; };
        void setTypeArgumentsopt(IAst *_TypeArgumentsopt) { this->_TypeArgumentsopt = _TypeArgumentsopt; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        MethodInvocation3(IToken* leftIToken, IToken* rightIToken,
                          IAst *_ClassName,
                          IAst *_DOT,
                          IAst *_super,
                          IAst *_DOT4,
                          IAst *_TypeArgumentsopt,
                          IAst *_identifier,
                          IAst *_LPAREN,
                          IAst *_ArgumentListopt,
                          IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_ClassName = _ClassName;
            ((Ast*) _ClassName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_super = _super;
            ((Ast*) _super)->setParent(this);
            this->_DOT4 = _DOT4;
            ((Ast*) _DOT4)->setParent(this);
            this->_TypeArgumentsopt = _TypeArgumentsopt;
            if (_TypeArgumentsopt != nullptr) ((Ast*) _TypeArgumentsopt)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ClassName);
            list.push_back(_DOT);
            list.push_back(_super);
            list.push_back(_DOT4);
            list.push_back(_TypeArgumentsopt);
            list.push_back(_identifier);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
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
                _ClassName->accept(v);
                _DOT->accept(v);
                _super->accept(v);
                _DOT4->accept(v);
                if (_TypeArgumentsopt != nullptr) _TypeArgumentsopt->accept(v);
                _identifier->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 374:  MethodInvocation ::= TypeName . TypeArguments identifier ( ArgumentListopt )
     *</b>
     */
    struct MethodInvocation4 :public Ast
    {
        IAst *_TypeName;
        IAst *_DOT;
        IAst *_TypeArguments;
        IAst *_identifier;
        IAst *_LPAREN;
        IAst *_ArgumentListopt;
        IAst *_RPAREN;

        IAst *getTypeName() { return _TypeName; };
        void setTypeName(IAst *_TypeName) { this->_TypeName = _TypeName; }
        IAst *getDOT() { return _DOT; };
        void setDOT(IAst *_DOT) { this->_DOT = _DOT; }
        IAst *getTypeArguments() { return _TypeArguments; };
        void setTypeArguments(IAst *_TypeArguments) { this->_TypeArguments = _TypeArguments; }
        IAst *getidentifier() { return _identifier; };
        void setidentifier(IAst *_identifier) { this->_identifier = _identifier; }
        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        /**
         * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
         */
        IAst *getArgumentListopt() { return _ArgumentListopt; };
        void setArgumentListopt(IAst *_ArgumentListopt) { this->_ArgumentListopt = _ArgumentListopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }

        MethodInvocation4(IToken* leftIToken, IToken* rightIToken,
                          IAst *_TypeName,
                          IAst *_DOT,
                          IAst *_TypeArguments,
                          IAst *_identifier,
                          IAst *_LPAREN,
                          IAst *_ArgumentListopt,
                          IAst *_RPAREN):Ast(leftIToken, rightIToken)    {
            this->_TypeName = _TypeName;
            ((Ast*) _TypeName)->setParent(this);
            this->_DOT = _DOT;
            ((Ast*) _DOT)->setParent(this);
            this->_TypeArguments = _TypeArguments;
            ((Ast*) _TypeArguments)->setParent(this);
            this->_identifier = _identifier;
            ((Ast*) _identifier)->setParent(this);
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ArgumentListopt = _ArgumentListopt;
            if (_ArgumentListopt != nullptr) ((Ast*) _ArgumentListopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TypeName);
            list.push_back(_DOT);
            list.push_back(_TypeArguments);
            list.push_back(_identifier);
            list.push_back(_LPAREN);
            list.push_back(_ArgumentListopt);
            list.push_back(_RPAREN);
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
                _TypeName->accept(v);
                _DOT->accept(v);
                _TypeArguments->accept(v);
                _identifier->accept(v);
                _LPAREN->accept(v);
                if (_ArgumentListopt != nullptr) _ArgumentListopt->accept(v);
                _RPAREN->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 375:  ArrayAccess ::= ExpressionName [ Expression ]
     *</b>
     */
    struct ArrayAccess0 :public Ast
    {
        IAst *_ExpressionName;
        IAst *_LBRACKET;
        IAst *_Expression;
        IAst *_RBRACKET;

        IAst *getExpressionName() { return _ExpressionName; };
        void setExpressionName(IAst *_ExpressionName) { this->_ExpressionName = _ExpressionName; }
        IAst *getLBRACKET() { return _LBRACKET; };
        void setLBRACKET(IAst *_LBRACKET) { this->_LBRACKET = _LBRACKET; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRBRACKET() { return _RBRACKET; };
        void setRBRACKET(IAst *_RBRACKET) { this->_RBRACKET = _RBRACKET; }

        ArrayAccess0(IToken* leftIToken, IToken* rightIToken,
                     IAst *_ExpressionName,
                     IAst *_LBRACKET,
                     IAst *_Expression,
                     IAst *_RBRACKET):Ast(leftIToken, rightIToken)    {
            this->_ExpressionName = _ExpressionName;
            ((Ast*) _ExpressionName)->setParent(this);
            this->_LBRACKET = _LBRACKET;
            ((Ast*) _LBRACKET)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RBRACKET = _RBRACKET;
            ((Ast*) _RBRACKET)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ExpressionName);
            list.push_back(_LBRACKET);
            list.push_back(_Expression);
            list.push_back(_RBRACKET);
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
                _ExpressionName->accept(v);
                _LBRACKET->accept(v);
                _Expression->accept(v);
                _RBRACKET->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 376:  ArrayAccess ::= PrimaryNoNewArray [ Expression ]
     *</b>
     */
    struct ArrayAccess1 :public Ast
    {
        IAst *_PrimaryNoNewArray;
        IAst *_LBRACKET;
        IAst *_Expression;
        IAst *_RBRACKET;

        IAst *getPrimaryNoNewArray() { return _PrimaryNoNewArray; };
        void setPrimaryNoNewArray(IAst *_PrimaryNoNewArray) { this->_PrimaryNoNewArray = _PrimaryNoNewArray; }
        IAst *getLBRACKET() { return _LBRACKET; };
        void setLBRACKET(IAst *_LBRACKET) { this->_LBRACKET = _LBRACKET; }
        IAst *getExpression() { return _Expression; };
        void setExpression(IAst *_Expression) { this->_Expression = _Expression; }
        IAst *getRBRACKET() { return _RBRACKET; };
        void setRBRACKET(IAst *_RBRACKET) { this->_RBRACKET = _RBRACKET; }

        ArrayAccess1(IToken* leftIToken, IToken* rightIToken,
                     IAst *_PrimaryNoNewArray,
                     IAst *_LBRACKET,
                     IAst *_Expression,
                     IAst *_RBRACKET):Ast(leftIToken, rightIToken)    {
            this->_PrimaryNoNewArray = _PrimaryNoNewArray;
            ((Ast*) _PrimaryNoNewArray)->setParent(this);
            this->_LBRACKET = _LBRACKET;
            ((Ast*) _LBRACKET)->setParent(this);
            this->_Expression = _Expression;
            ((Ast*) _Expression)->setParent(this);
            this->_RBRACKET = _RBRACKET;
            ((Ast*) _RBRACKET)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_PrimaryNoNewArray);
            list.push_back(_LBRACKET);
            list.push_back(_Expression);
            list.push_back(_RBRACKET);
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
                _PrimaryNoNewArray->accept(v);
                _LBRACKET->accept(v);
                _Expression->accept(v);
                _RBRACKET->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 385:  UnaryExpression ::= + UnaryExpression
     *</b>
     */
    struct UnaryExpression0 :public Ast
    {
        IAst *_PLUS;
        IAst *_UnaryExpression;

        IAst *getPLUS() { return _PLUS; };
        void setPLUS(IAst *_PLUS) { this->_PLUS = _PLUS; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        UnaryExpression0(IToken* leftIToken, IToken* rightIToken,
                         IAst *_PLUS,
                         IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_PLUS = _PLUS;
            ((Ast*) _PLUS)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_PLUS);
            list.push_back(_UnaryExpression);
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
                _PLUS->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 386:  UnaryExpression ::= - UnaryExpression
     *</b>
     */
    struct UnaryExpression1 :public Ast
    {
        IAst *_MINUS;
        IAst *_UnaryExpression;

        IAst *getMINUS() { return _MINUS; };
        void setMINUS(IAst *_MINUS) { this->_MINUS = _MINUS; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        UnaryExpression1(IToken* leftIToken, IToken* rightIToken,
                         IAst *_MINUS,
                         IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_MINUS = _MINUS;
            ((Ast*) _MINUS)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MINUS);
            list.push_back(_UnaryExpression);
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
                _MINUS->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 391:  UnaryExpressionNotPlusMinus ::= ~ UnaryExpression
     *</b>
     */
    struct UnaryExpressionNotPlusMinus0 :public Ast
    {
        IAst *_TWIDDLE;
        IAst *_UnaryExpression;

        IAst *getTWIDDLE() { return _TWIDDLE; };
        void setTWIDDLE(IAst *_TWIDDLE) { this->_TWIDDLE = _TWIDDLE; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        UnaryExpressionNotPlusMinus0(IToken* leftIToken, IToken* rightIToken,
                                     IAst *_TWIDDLE,
                                     IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_TWIDDLE = _TWIDDLE;
            ((Ast*) _TWIDDLE)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_TWIDDLE);
            list.push_back(_UnaryExpression);
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
                _TWIDDLE->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 392:  UnaryExpressionNotPlusMinus ::= ! UnaryExpression
     *</b>
     */
    struct UnaryExpressionNotPlusMinus1 :public Ast
    {
        IAst *_NOT;
        IAst *_UnaryExpression;

        IAst *getNOT() { return _NOT; };
        void setNOT(IAst *_NOT) { this->_NOT = _NOT; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        UnaryExpressionNotPlusMinus1(IToken* leftIToken, IToken* rightIToken,
                                     IAst *_NOT,
                                     IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_NOT = _NOT;
            ((Ast*) _NOT)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_NOT);
            list.push_back(_UnaryExpression);
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
                _NOT->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 394:  CastExpression ::= ( PrimitiveType Dimsopt ) UnaryExpression
     *</b>
     */
    struct CastExpression0 :public Ast
    {
        IAst *_LPAREN;
        IAst *_PrimitiveType;
        IAst *_Dimsopt;
        IAst *_RPAREN;
        IAst *_UnaryExpression;

        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getPrimitiveType() { return _PrimitiveType; };
        void setPrimitiveType(IAst *_PrimitiveType) { this->_PrimitiveType = _PrimitiveType; }
        /**
         * The value returned by <b>getDimsopt</b> may be <b>nullptr</b>
         */
        IAst *getDimsopt() { return _Dimsopt; };
        void setDimsopt(IAst *_Dimsopt) { this->_Dimsopt = _Dimsopt; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        CastExpression0(IToken* leftIToken, IToken* rightIToken,
                        IAst *_LPAREN,
                        IAst *_PrimitiveType,
                        IAst *_Dimsopt,
                        IAst *_RPAREN,
                        IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_PrimitiveType = _PrimitiveType;
            ((Ast*) _PrimitiveType)->setParent(this);
            this->_Dimsopt = _Dimsopt;
            if (_Dimsopt != nullptr) ((Ast*) _Dimsopt)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LPAREN);
            list.push_back(_PrimitiveType);
            list.push_back(_Dimsopt);
            list.push_back(_RPAREN);
            list.push_back(_UnaryExpression);
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
                _LPAREN->accept(v);
                _PrimitiveType->accept(v);
                if (_Dimsopt != nullptr) _Dimsopt->accept(v);
                _RPAREN->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 395:  CastExpression ::= ( ReferenceType ) UnaryExpressionNotPlusMinus
     *</b>
     */
    struct CastExpression1 :public Ast
    {
        IAst *_LPAREN;
        IAst *_ReferenceType;
        IAst *_RPAREN;
        IAst *_UnaryExpressionNotPlusMinus;

        IAst *getLPAREN() { return _LPAREN; };
        void setLPAREN(IAst *_LPAREN) { this->_LPAREN = _LPAREN; }
        IAst *getReferenceType() { return _ReferenceType; };
        void setReferenceType(IAst *_ReferenceType) { this->_ReferenceType = _ReferenceType; }
        IAst *getRPAREN() { return _RPAREN; };
        void setRPAREN(IAst *_RPAREN) { this->_RPAREN = _RPAREN; }
        IAst *getUnaryExpressionNotPlusMinus() { return _UnaryExpressionNotPlusMinus; };
        void setUnaryExpressionNotPlusMinus(IAst *_UnaryExpressionNotPlusMinus) { this->_UnaryExpressionNotPlusMinus = _UnaryExpressionNotPlusMinus; }

        CastExpression1(IToken* leftIToken, IToken* rightIToken,
                        IAst *_LPAREN,
                        IAst *_ReferenceType,
                        IAst *_RPAREN,
                        IAst *_UnaryExpressionNotPlusMinus):Ast(leftIToken, rightIToken)    {
            this->_LPAREN = _LPAREN;
            ((Ast*) _LPAREN)->setParent(this);
            this->_ReferenceType = _ReferenceType;
            ((Ast*) _ReferenceType)->setParent(this);
            this->_RPAREN = _RPAREN;
            ((Ast*) _RPAREN)->setParent(this);
            this->_UnaryExpressionNotPlusMinus = _UnaryExpressionNotPlusMinus;
            ((Ast*) _UnaryExpressionNotPlusMinus)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_LPAREN);
            list.push_back(_ReferenceType);
            list.push_back(_RPAREN);
            list.push_back(_UnaryExpressionNotPlusMinus);
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
                _LPAREN->accept(v);
                _ReferenceType->accept(v);
                _RPAREN->accept(v);
                _UnaryExpressionNotPlusMinus->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 397:  MultiplicativeExpression ::= MultiplicativeExpression * UnaryExpression
     *</b>
     */
    struct MultiplicativeExpression0 :public Ast
    {
        IAst *_MultiplicativeExpression;
        IAst *_MULTIPLY;
        IAst *_UnaryExpression;

        IAst *getMultiplicativeExpression() { return _MultiplicativeExpression; };
        void setMultiplicativeExpression(IAst *_MultiplicativeExpression) { this->_MultiplicativeExpression = _MultiplicativeExpression; }
        IAst *getMULTIPLY() { return _MULTIPLY; };
        void setMULTIPLY(IAst *_MULTIPLY) { this->_MULTIPLY = _MULTIPLY; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        MultiplicativeExpression0(IToken* leftIToken, IToken* rightIToken,
                                  IAst *_MultiplicativeExpression,
                                  IAst *_MULTIPLY,
                                  IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_MultiplicativeExpression = _MultiplicativeExpression;
            ((Ast*) _MultiplicativeExpression)->setParent(this);
            this->_MULTIPLY = _MULTIPLY;
            ((Ast*) _MULTIPLY)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MultiplicativeExpression);
            list.push_back(_MULTIPLY);
            list.push_back(_UnaryExpression);
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
                _MultiplicativeExpression->accept(v);
                _MULTIPLY->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 398:  MultiplicativeExpression ::= MultiplicativeExpression / UnaryExpression
     *</b>
     */
    struct MultiplicativeExpression1 :public Ast
    {
        IAst *_MultiplicativeExpression;
        IAst *_DIVIDE;
        IAst *_UnaryExpression;

        IAst *getMultiplicativeExpression() { return _MultiplicativeExpression; };
        void setMultiplicativeExpression(IAst *_MultiplicativeExpression) { this->_MultiplicativeExpression = _MultiplicativeExpression; }
        IAst *getDIVIDE() { return _DIVIDE; };
        void setDIVIDE(IAst *_DIVIDE) { this->_DIVIDE = _DIVIDE; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        MultiplicativeExpression1(IToken* leftIToken, IToken* rightIToken,
                                  IAst *_MultiplicativeExpression,
                                  IAst *_DIVIDE,
                                  IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_MultiplicativeExpression = _MultiplicativeExpression;
            ((Ast*) _MultiplicativeExpression)->setParent(this);
            this->_DIVIDE = _DIVIDE;
            ((Ast*) _DIVIDE)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MultiplicativeExpression);
            list.push_back(_DIVIDE);
            list.push_back(_UnaryExpression);
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
                _MultiplicativeExpression->accept(v);
                _DIVIDE->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 399:  MultiplicativeExpression ::= MultiplicativeExpression % UnaryExpression
     *</b>
     */
    struct MultiplicativeExpression2 :public Ast
    {
        IAst *_MultiplicativeExpression;
        IAst *_REMAINDER;
        IAst *_UnaryExpression;

        IAst *getMultiplicativeExpression() { return _MultiplicativeExpression; };
        void setMultiplicativeExpression(IAst *_MultiplicativeExpression) { this->_MultiplicativeExpression = _MultiplicativeExpression; }
        IAst *getREMAINDER() { return _REMAINDER; };
        void setREMAINDER(IAst *_REMAINDER) { this->_REMAINDER = _REMAINDER; }
        IAst *getUnaryExpression() { return _UnaryExpression; };
        void setUnaryExpression(IAst *_UnaryExpression) { this->_UnaryExpression = _UnaryExpression; }

        MultiplicativeExpression2(IToken* leftIToken, IToken* rightIToken,
                                  IAst *_MultiplicativeExpression,
                                  IAst *_REMAINDER,
                                  IAst *_UnaryExpression):Ast(leftIToken, rightIToken)    {
            this->_MultiplicativeExpression = _MultiplicativeExpression;
            ((Ast*) _MultiplicativeExpression)->setParent(this);
            this->_REMAINDER = _REMAINDER;
            ((Ast*) _REMAINDER)->setParent(this);
            this->_UnaryExpression = _UnaryExpression;
            ((Ast*) _UnaryExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_MultiplicativeExpression);
            list.push_back(_REMAINDER);
            list.push_back(_UnaryExpression);
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
                _MultiplicativeExpression->accept(v);
                _REMAINDER->accept(v);
                _UnaryExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 401:  AdditiveExpression ::= AdditiveExpression + MultiplicativeExpression
     *</b>
     */
    struct AdditiveExpression0 :public Ast
    {
        IAst *_AdditiveExpression;
        IAst *_PLUS;
        IAst *_MultiplicativeExpression;

        IAst *getAdditiveExpression() { return _AdditiveExpression; };
        void setAdditiveExpression(IAst *_AdditiveExpression) { this->_AdditiveExpression = _AdditiveExpression; }
        IAst *getPLUS() { return _PLUS; };
        void setPLUS(IAst *_PLUS) { this->_PLUS = _PLUS; }
        IAst *getMultiplicativeExpression() { return _MultiplicativeExpression; };
        void setMultiplicativeExpression(IAst *_MultiplicativeExpression) { this->_MultiplicativeExpression = _MultiplicativeExpression; }

        AdditiveExpression0(IToken* leftIToken, IToken* rightIToken,
                            IAst *_AdditiveExpression,
                            IAst *_PLUS,
                            IAst *_MultiplicativeExpression):Ast(leftIToken, rightIToken)    {
            this->_AdditiveExpression = _AdditiveExpression;
            ((Ast*) _AdditiveExpression)->setParent(this);
            this->_PLUS = _PLUS;
            ((Ast*) _PLUS)->setParent(this);
            this->_MultiplicativeExpression = _MultiplicativeExpression;
            ((Ast*) _MultiplicativeExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AdditiveExpression);
            list.push_back(_PLUS);
            list.push_back(_MultiplicativeExpression);
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
                _AdditiveExpression->accept(v);
                _PLUS->accept(v);
                _MultiplicativeExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 402:  AdditiveExpression ::= AdditiveExpression - MultiplicativeExpression
     *</b>
     */
    struct AdditiveExpression1 :public Ast
    {
        IAst *_AdditiveExpression;
        IAst *_MINUS;
        IAst *_MultiplicativeExpression;

        IAst *getAdditiveExpression() { return _AdditiveExpression; };
        void setAdditiveExpression(IAst *_AdditiveExpression) { this->_AdditiveExpression = _AdditiveExpression; }
        IAst *getMINUS() { return _MINUS; };
        void setMINUS(IAst *_MINUS) { this->_MINUS = _MINUS; }
        IAst *getMultiplicativeExpression() { return _MultiplicativeExpression; };
        void setMultiplicativeExpression(IAst *_MultiplicativeExpression) { this->_MultiplicativeExpression = _MultiplicativeExpression; }

        AdditiveExpression1(IToken* leftIToken, IToken* rightIToken,
                            IAst *_AdditiveExpression,
                            IAst *_MINUS,
                            IAst *_MultiplicativeExpression):Ast(leftIToken, rightIToken)    {
            this->_AdditiveExpression = _AdditiveExpression;
            ((Ast*) _AdditiveExpression)->setParent(this);
            this->_MINUS = _MINUS;
            ((Ast*) _MINUS)->setParent(this);
            this->_MultiplicativeExpression = _MultiplicativeExpression;
            ((Ast*) _MultiplicativeExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_AdditiveExpression);
            list.push_back(_MINUS);
            list.push_back(_MultiplicativeExpression);
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
                _AdditiveExpression->accept(v);
                _MINUS->accept(v);
                _MultiplicativeExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 404:  ShiftExpression ::= ShiftExpression << AdditiveExpression
     *</b>
     */
    struct ShiftExpression0 :public Ast
    {
        IAst *_ShiftExpression;
        IAst *_LEFT_SHIFT;
        IAst *_AdditiveExpression;

        IAst *getShiftExpression() { return _ShiftExpression; };
        void setShiftExpression(IAst *_ShiftExpression) { this->_ShiftExpression = _ShiftExpression; }
        IAst *getLEFT_SHIFT() { return _LEFT_SHIFT; };
        void setLEFT_SHIFT(IAst *_LEFT_SHIFT) { this->_LEFT_SHIFT = _LEFT_SHIFT; }
        IAst *getAdditiveExpression() { return _AdditiveExpression; };
        void setAdditiveExpression(IAst *_AdditiveExpression) { this->_AdditiveExpression = _AdditiveExpression; }

        ShiftExpression0(IToken* leftIToken, IToken* rightIToken,
                         IAst *_ShiftExpression,
                         IAst *_LEFT_SHIFT,
                         IAst *_AdditiveExpression):Ast(leftIToken, rightIToken)    {
            this->_ShiftExpression = _ShiftExpression;
            ((Ast*) _ShiftExpression)->setParent(this);
            this->_LEFT_SHIFT = _LEFT_SHIFT;
            ((Ast*) _LEFT_SHIFT)->setParent(this);
            this->_AdditiveExpression = _AdditiveExpression;
            ((Ast*) _AdditiveExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ShiftExpression);
            list.push_back(_LEFT_SHIFT);
            list.push_back(_AdditiveExpression);
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
                _ShiftExpression->accept(v);
                _LEFT_SHIFT->accept(v);
                _AdditiveExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 405:  ShiftExpression ::= ShiftExpression > > AdditiveExpression
     *</b>
     */
    struct ShiftExpression1 :public Ast
    {
        IAst *_ShiftExpression;
        IAst *_GREATER;
        IAst *_GREATER3;
        IAst *_AdditiveExpression;

        IAst *getShiftExpression() { return _ShiftExpression; };
        void setShiftExpression(IAst *_ShiftExpression) { this->_ShiftExpression = _ShiftExpression; }
        IAst *getGREATER() { return _GREATER; };
        void setGREATER(IAst *_GREATER) { this->_GREATER = _GREATER; }
        IAst *getGREATER3() { return _GREATER3; };
        void setGREATER3(IAst *_GREATER3) { this->_GREATER3 = _GREATER3; }
        IAst *getAdditiveExpression() { return _AdditiveExpression; };
        void setAdditiveExpression(IAst *_AdditiveExpression) { this->_AdditiveExpression = _AdditiveExpression; }

        ShiftExpression1(IToken* leftIToken, IToken* rightIToken,
                         IAst *_ShiftExpression,
                         IAst *_GREATER,
                         IAst *_GREATER3,
                         IAst *_AdditiveExpression):Ast(leftIToken, rightIToken)    {
            this->_ShiftExpression = _ShiftExpression;
            ((Ast*) _ShiftExpression)->setParent(this);
            this->_GREATER = _GREATER;
            ((Ast*) _GREATER)->setParent(this);
            this->_GREATER3 = _GREATER3;
            ((Ast*) _GREATER3)->setParent(this);
            this->_AdditiveExpression = _AdditiveExpression;
            ((Ast*) _AdditiveExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ShiftExpression);
            list.push_back(_GREATER);
            list.push_back(_GREATER3);
            list.push_back(_AdditiveExpression);
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
                _ShiftExpression->accept(v);
                _GREATER->accept(v);
                _GREATER3->accept(v);
                _AdditiveExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 406:  ShiftExpression ::= ShiftExpression > > > AdditiveExpression
     *</b>
     */
    struct ShiftExpression2 :public Ast
    {
        IAst *_ShiftExpression;
        IAst *_GREATER;
        IAst *_GREATER3;
        IAst *_GREATER4;
        IAst *_AdditiveExpression;

        IAst *getShiftExpression() { return _ShiftExpression; };
        void setShiftExpression(IAst *_ShiftExpression) { this->_ShiftExpression = _ShiftExpression; }
        IAst *getGREATER() { return _GREATER; };
        void setGREATER(IAst *_GREATER) { this->_GREATER = _GREATER; }
        IAst *getGREATER3() { return _GREATER3; };
        void setGREATER3(IAst *_GREATER3) { this->_GREATER3 = _GREATER3; }
        IAst *getGREATER4() { return _GREATER4; };
        void setGREATER4(IAst *_GREATER4) { this->_GREATER4 = _GREATER4; }
        IAst *getAdditiveExpression() { return _AdditiveExpression; };
        void setAdditiveExpression(IAst *_AdditiveExpression) { this->_AdditiveExpression = _AdditiveExpression; }

        ShiftExpression2(IToken* leftIToken, IToken* rightIToken,
                         IAst *_ShiftExpression,
                         IAst *_GREATER,
                         IAst *_GREATER3,
                         IAst *_GREATER4,
                         IAst *_AdditiveExpression):Ast(leftIToken, rightIToken)    {
            this->_ShiftExpression = _ShiftExpression;
            ((Ast*) _ShiftExpression)->setParent(this);
            this->_GREATER = _GREATER;
            ((Ast*) _GREATER)->setParent(this);
            this->_GREATER3 = _GREATER3;
            ((Ast*) _GREATER3)->setParent(this);
            this->_GREATER4 = _GREATER4;
            ((Ast*) _GREATER4)->setParent(this);
            this->_AdditiveExpression = _AdditiveExpression;
            ((Ast*) _AdditiveExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_ShiftExpression);
            list.push_back(_GREATER);
            list.push_back(_GREATER3);
            list.push_back(_GREATER4);
            list.push_back(_AdditiveExpression);
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
                _ShiftExpression->accept(v);
                _GREATER->accept(v);
                _GREATER3->accept(v);
                _GREATER4->accept(v);
                _AdditiveExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 408:  RelationalExpression ::= RelationalExpression < ShiftExpression
     *</b>
     */
    struct RelationalExpression0 :public Ast
    {
        IAst *_RelationalExpression;
        IAst *_LESS;
        IAst *_ShiftExpression;

        IAst *getRelationalExpression() { return _RelationalExpression; };
        void setRelationalExpression(IAst *_RelationalExpression) { this->_RelationalExpression = _RelationalExpression; }
        IAst *getLESS() { return _LESS; };
        void setLESS(IAst *_LESS) { this->_LESS = _LESS; }
        IAst *getShiftExpression() { return _ShiftExpression; };
        void setShiftExpression(IAst *_ShiftExpression) { this->_ShiftExpression = _ShiftExpression; }

        RelationalExpression0(IToken* leftIToken, IToken* rightIToken,
                              IAst *_RelationalExpression,
                              IAst *_LESS,
                              IAst *_ShiftExpression):Ast(leftIToken, rightIToken)    {
            this->_RelationalExpression = _RelationalExpression;
            ((Ast*) _RelationalExpression)->setParent(this);
            this->_LESS = _LESS;
            ((Ast*) _LESS)->setParent(this);
            this->_ShiftExpression = _ShiftExpression;
            ((Ast*) _ShiftExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_RelationalExpression);
            list.push_back(_LESS);
            list.push_back(_ShiftExpression);
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
                _RelationalExpression->accept(v);
                _LESS->accept(v);
                _ShiftExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 409:  RelationalExpression ::= RelationalExpression > ShiftExpression
     *</b>
     */
    struct RelationalExpression1 :public Ast
    {
        IAst *_RelationalExpression;
        IAst *_GREATER;
        IAst *_ShiftExpression;

        IAst *getRelationalExpression() { return _RelationalExpression; };
        void setRelationalExpression(IAst *_RelationalExpression) { this->_RelationalExpression = _RelationalExpression; }
        IAst *getGREATER() { return _GREATER; };
        void setGREATER(IAst *_GREATER) { this->_GREATER = _GREATER; }
        IAst *getShiftExpression() { return _ShiftExpression; };
        void setShiftExpression(IAst *_ShiftExpression) { this->_ShiftExpression = _ShiftExpression; }

        RelationalExpression1(IToken* leftIToken, IToken* rightIToken,
                              IAst *_RelationalExpression,
                              IAst *_GREATER,
                              IAst *_ShiftExpression):Ast(leftIToken, rightIToken)    {
            this->_RelationalExpression = _RelationalExpression;
            ((Ast*) _RelationalExpression)->setParent(this);
            this->_GREATER = _GREATER;
            ((Ast*) _GREATER)->setParent(this);
            this->_ShiftExpression = _ShiftExpression;
            ((Ast*) _ShiftExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_RelationalExpression);
            list.push_back(_GREATER);
            list.push_back(_ShiftExpression);
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
                _RelationalExpression->accept(v);
                _GREATER->accept(v);
                _ShiftExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 410:  RelationalExpression ::= RelationalExpression <= ShiftExpression
     *</b>
     */
    struct RelationalExpression2 :public Ast
    {
        IAst *_RelationalExpression;
        IAst *_LESS_EQUAL;
        IAst *_ShiftExpression;

        IAst *getRelationalExpression() { return _RelationalExpression; };
        void setRelationalExpression(IAst *_RelationalExpression) { this->_RelationalExpression = _RelationalExpression; }
        IAst *getLESS_EQUAL() { return _LESS_EQUAL; };
        void setLESS_EQUAL(IAst *_LESS_EQUAL) { this->_LESS_EQUAL = _LESS_EQUAL; }
        IAst *getShiftExpression() { return _ShiftExpression; };
        void setShiftExpression(IAst *_ShiftExpression) { this->_ShiftExpression = _ShiftExpression; }

        RelationalExpression2(IToken* leftIToken, IToken* rightIToken,
                              IAst *_RelationalExpression,
                              IAst *_LESS_EQUAL,
                              IAst *_ShiftExpression):Ast(leftIToken, rightIToken)    {
            this->_RelationalExpression = _RelationalExpression;
            ((Ast*) _RelationalExpression)->setParent(this);
            this->_LESS_EQUAL = _LESS_EQUAL;
            ((Ast*) _LESS_EQUAL)->setParent(this);
            this->_ShiftExpression = _ShiftExpression;
            ((Ast*) _ShiftExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_RelationalExpression);
            list.push_back(_LESS_EQUAL);
            list.push_back(_ShiftExpression);
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
                _RelationalExpression->accept(v);
                _LESS_EQUAL->accept(v);
                _ShiftExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 411:  RelationalExpression ::= RelationalExpression > = ShiftExpression
     *</b>
     */
    struct RelationalExpression3 :public Ast
    {
        IAst *_RelationalExpression;
        IAst *_GREATER;
        IAst *_EQUAL;
        IAst *_ShiftExpression;

        IAst *getRelationalExpression() { return _RelationalExpression; };
        void setRelationalExpression(IAst *_RelationalExpression) { this->_RelationalExpression = _RelationalExpression; }
        IAst *getGREATER() { return _GREATER; };
        void setGREATER(IAst *_GREATER) { this->_GREATER = _GREATER; }
        IAst *getEQUAL() { return _EQUAL; };
        void setEQUAL(IAst *_EQUAL) { this->_EQUAL = _EQUAL; }
        IAst *getShiftExpression() { return _ShiftExpression; };
        void setShiftExpression(IAst *_ShiftExpression) { this->_ShiftExpression = _ShiftExpression; }

        RelationalExpression3(IToken* leftIToken, IToken* rightIToken,
                              IAst *_RelationalExpression,
                              IAst *_GREATER,
                              IAst *_EQUAL,
                              IAst *_ShiftExpression):Ast(leftIToken, rightIToken)    {
            this->_RelationalExpression = _RelationalExpression;
            ((Ast*) _RelationalExpression)->setParent(this);
            this->_GREATER = _GREATER;
            ((Ast*) _GREATER)->setParent(this);
            this->_EQUAL = _EQUAL;
            ((Ast*) _EQUAL)->setParent(this);
            this->_ShiftExpression = _ShiftExpression;
            ((Ast*) _ShiftExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_RelationalExpression);
            list.push_back(_GREATER);
            list.push_back(_EQUAL);
            list.push_back(_ShiftExpression);
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
                _RelationalExpression->accept(v);
                _GREATER->accept(v);
                _EQUAL->accept(v);
                _ShiftExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 412:  RelationalExpression ::= RelationalExpression instanceof ReferenceType
     *</b>
     */
    struct RelationalExpression4 :public Ast
    {
        IAst *_RelationalExpression;
        IAst *_instanceof;
        IAst *_ReferenceType;

        IAst *getRelationalExpression() { return _RelationalExpression; };
        void setRelationalExpression(IAst *_RelationalExpression) { this->_RelationalExpression = _RelationalExpression; }
        IAst *getinstanceof() { return _instanceof; };
        void setinstanceof(IAst *_instanceof) { this->_instanceof = _instanceof; }
        IAst *getReferenceType() { return _ReferenceType; };
        void setReferenceType(IAst *_ReferenceType) { this->_ReferenceType = _ReferenceType; }

        RelationalExpression4(IToken* leftIToken, IToken* rightIToken,
                              IAst *_RelationalExpression,
                              IAst *_instanceof,
                              IAst *_ReferenceType):Ast(leftIToken, rightIToken)    {
            this->_RelationalExpression = _RelationalExpression;
            ((Ast*) _RelationalExpression)->setParent(this);
            this->_instanceof = _instanceof;
            ((Ast*) _instanceof)->setParent(this);
            this->_ReferenceType = _ReferenceType;
            ((Ast*) _ReferenceType)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_RelationalExpression);
            list.push_back(_instanceof);
            list.push_back(_ReferenceType);
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
                _RelationalExpression->accept(v);
                _instanceof->accept(v);
                _ReferenceType->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 414:  EqualityExpression ::= EqualityExpression == RelationalExpression
     *</b>
     */
    struct EqualityExpression0 :public Ast
    {
        IAst *_EqualityExpression;
        IAst *_EQUAL_EQUAL;
        IAst *_RelationalExpression;

        IAst *getEqualityExpression() { return _EqualityExpression; };
        void setEqualityExpression(IAst *_EqualityExpression) { this->_EqualityExpression = _EqualityExpression; }
        IAst *getEQUAL_EQUAL() { return _EQUAL_EQUAL; };
        void setEQUAL_EQUAL(IAst *_EQUAL_EQUAL) { this->_EQUAL_EQUAL = _EQUAL_EQUAL; }
        IAst *getRelationalExpression() { return _RelationalExpression; };
        void setRelationalExpression(IAst *_RelationalExpression) { this->_RelationalExpression = _RelationalExpression; }

        EqualityExpression0(IToken* leftIToken, IToken* rightIToken,
                            IAst *_EqualityExpression,
                            IAst *_EQUAL_EQUAL,
                            IAst *_RelationalExpression):Ast(leftIToken, rightIToken)    {
            this->_EqualityExpression = _EqualityExpression;
            ((Ast*) _EqualityExpression)->setParent(this);
            this->_EQUAL_EQUAL = _EQUAL_EQUAL;
            ((Ast*) _EQUAL_EQUAL)->setParent(this);
            this->_RelationalExpression = _RelationalExpression;
            ((Ast*) _RelationalExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_EqualityExpression);
            list.push_back(_EQUAL_EQUAL);
            list.push_back(_RelationalExpression);
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
                _EqualityExpression->accept(v);
                _EQUAL_EQUAL->accept(v);
                _RelationalExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 415:  EqualityExpression ::= EqualityExpression != RelationalExpression
     *</b>
     */
    struct EqualityExpression1 :public Ast
    {
        IAst *_EqualityExpression;
        IAst *_NOT_EQUAL;
        IAst *_RelationalExpression;

        IAst *getEqualityExpression() { return _EqualityExpression; };
        void setEqualityExpression(IAst *_EqualityExpression) { this->_EqualityExpression = _EqualityExpression; }
        IAst *getNOT_EQUAL() { return _NOT_EQUAL; };
        void setNOT_EQUAL(IAst *_NOT_EQUAL) { this->_NOT_EQUAL = _NOT_EQUAL; }
        IAst *getRelationalExpression() { return _RelationalExpression; };
        void setRelationalExpression(IAst *_RelationalExpression) { this->_RelationalExpression = _RelationalExpression; }

        EqualityExpression1(IToken* leftIToken, IToken* rightIToken,
                            IAst *_EqualityExpression,
                            IAst *_NOT_EQUAL,
                            IAst *_RelationalExpression):Ast(leftIToken, rightIToken)    {
            this->_EqualityExpression = _EqualityExpression;
            ((Ast*) _EqualityExpression)->setParent(this);
            this->_NOT_EQUAL = _NOT_EQUAL;
            ((Ast*) _NOT_EQUAL)->setParent(this);
            this->_RelationalExpression = _RelationalExpression;
            ((Ast*) _RelationalExpression)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_EqualityExpression);
            list.push_back(_NOT_EQUAL);
            list.push_back(_RelationalExpression);
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
                _EqualityExpression->accept(v);
                _NOT_EQUAL->accept(v);
                _RelationalExpression->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 434:  AssignmentOperator ::= =
     *</b>
     */
    struct AssignmentOperator0 :public AstToken
    {
        IToken* getEQUAL() { return leftIToken; }

        AssignmentOperator0(IToken* token) :AstToken(token)
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
     *<li>Rule 435:  AssignmentOperator ::= *=
     *</b>
     */
    struct AssignmentOperator1 :public AstToken
    {
        IToken* getMULTIPLY_EQUAL() { return leftIToken; }

        AssignmentOperator1(IToken* token) :AstToken(token)
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
     *<li>Rule 436:  AssignmentOperator ::= /=
     *</b>
     */
    struct AssignmentOperator2 :public AstToken
    {
        IToken* getDIVIDE_EQUAL() { return leftIToken; }

        AssignmentOperator2(IToken* token) :AstToken(token)
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
     *<li>Rule 437:  AssignmentOperator ::= %=
     *</b>
     */
    struct AssignmentOperator3 :public AstToken
    {
        IToken* getREMAINDER_EQUAL() { return leftIToken; }

        AssignmentOperator3(IToken* token) :AstToken(token)
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
     *<li>Rule 438:  AssignmentOperator ::= +=
     *</b>
     */
    struct AssignmentOperator4 :public AstToken
    {
        IToken* getPLUS_EQUAL() { return leftIToken; }

        AssignmentOperator4(IToken* token) :AstToken(token)
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
     *<li>Rule 439:  AssignmentOperator ::= -=
     *</b>
     */
    struct AssignmentOperator5 :public AstToken
    {
        IToken* getMINUS_EQUAL() { return leftIToken; }

        AssignmentOperator5(IToken* token) :AstToken(token)
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
     *<li>Rule 440:  AssignmentOperator ::= <<=
     *</b>
     */
    struct AssignmentOperator6 :public AstToken
    {
        IToken* getLEFT_SHIFT_EQUAL() { return leftIToken; }

        AssignmentOperator6(IToken* token) :AstToken(token)
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
     *<li>Rule 441:  AssignmentOperator ::= > > =
     *</b>
     */
    struct AssignmentOperator7 :public Ast
    {
        IAst *_GREATER;
        IAst *_GREATER2;
        IAst *_EQUAL;

        IAst *getGREATER() { return _GREATER; };
        void setGREATER(IAst *_GREATER) { this->_GREATER = _GREATER; }
        IAst *getGREATER2() { return _GREATER2; };
        void setGREATER2(IAst *_GREATER2) { this->_GREATER2 = _GREATER2; }
        IAst *getEQUAL() { return _EQUAL; };
        void setEQUAL(IAst *_EQUAL) { this->_EQUAL = _EQUAL; }

        AssignmentOperator7(IToken* leftIToken, IToken* rightIToken,
                            IAst *_GREATER,
                            IAst *_GREATER2,
                            IAst *_EQUAL):Ast(leftIToken, rightIToken)    {
            this->_GREATER = _GREATER;
            ((Ast*) _GREATER)->setParent(this);
            this->_GREATER2 = _GREATER2;
            ((Ast*) _GREATER2)->setParent(this);
            this->_EQUAL = _EQUAL;
            ((Ast*) _EQUAL)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_GREATER);
            list.push_back(_GREATER2);
            list.push_back(_EQUAL);
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
                _GREATER->accept(v);
                _GREATER2->accept(v);
                _EQUAL->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 442:  AssignmentOperator ::= > > > =
     *</b>
     */
    struct AssignmentOperator8 :public Ast
    {
        IAst *_GREATER;
        IAst *_GREATER2;
        IAst *_GREATER3;
        IAst *_EQUAL;

        IAst *getGREATER() { return _GREATER; };
        void setGREATER(IAst *_GREATER) { this->_GREATER = _GREATER; }
        IAst *getGREATER2() { return _GREATER2; };
        void setGREATER2(IAst *_GREATER2) { this->_GREATER2 = _GREATER2; }
        IAst *getGREATER3() { return _GREATER3; };
        void setGREATER3(IAst *_GREATER3) { this->_GREATER3 = _GREATER3; }
        IAst *getEQUAL() { return _EQUAL; };
        void setEQUAL(IAst *_EQUAL) { this->_EQUAL = _EQUAL; }

        AssignmentOperator8(IToken* leftIToken, IToken* rightIToken,
                            IAst *_GREATER,
                            IAst *_GREATER2,
                            IAst *_GREATER3,
                            IAst *_EQUAL):Ast(leftIToken, rightIToken)    {
            this->_GREATER = _GREATER;
            ((Ast*) _GREATER)->setParent(this);
            this->_GREATER2 = _GREATER2;
            ((Ast*) _GREATER2)->setParent(this);
            this->_GREATER3 = _GREATER3;
            ((Ast*) _GREATER3)->setParent(this);
            this->_EQUAL = _EQUAL;
            ((Ast*) _EQUAL)->setParent(this);
            initialize();
        }

        /**
         * A list of all children of this node, including the nullptr ones.
         */
        std::vector<IAst*> getAllChildren()
        {
            std::vector<IAst*> list;
            list.push_back(_GREATER);
            list.push_back(_GREATER2);
            list.push_back(_GREATER3);
            list.push_back(_EQUAL);
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
                _GREATER->accept(v);
                _GREATER2->accept(v);
                _GREATER3->accept(v);
                _EQUAL->accept(v);
            }
            v->endVisit(this);
        }
    };

    /**
     *<b>
     *<li>Rule 443:  AssignmentOperator ::= &=
     *</b>
     */
    struct AssignmentOperator9 :public AstToken
    {
        IToken* getAND_EQUAL() { return leftIToken; }

        AssignmentOperator9(IToken* token) :AstToken(token)
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
     *<li>Rule 444:  AssignmentOperator ::= ^=
     *</b>
     */
    struct AssignmentOperator10 :public AstToken
    {
        IToken* getXOR_EQUAL() { return leftIToken; }

        AssignmentOperator10(IToken* token) :AstToken(token)
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
     *<li>Rule 445:  AssignmentOperator ::= |=
     *</b>
     */
    struct AssignmentOperator11 :public AstToken
    {
        IToken* getOR_EQUAL() { return leftIToken; }

        AssignmentOperator11(IToken* token) :AstToken(token)
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
      virtual  bool visit(Ast *n)=0;
     virtual   void endVisit(Ast *n)=0;

     virtual   bool visit(AstToken *n)=0;
      virtual  void endVisit(AstToken *n)=0;

     virtual   bool visit(identifier *n)=0;
      virtual  void endVisit(identifier *n)=0;

     virtual   bool visit(PrimitiveType *n)=0;
      virtual  void endVisit(PrimitiveType *n)=0;

     virtual   bool visit(ClassType *n)=0;
      virtual  void endVisit(ClassType *n)=0;

     virtual   bool visit(InterfaceType *n)=0;
      virtual  void endVisit(InterfaceType *n)=0;

     virtual   bool visit(TypeName *n)=0;
      virtual  void endVisit(TypeName *n)=0;

     virtual   bool visit(ArrayType *n)=0;
      virtual  void endVisit(ArrayType *n)=0;

     virtual   bool visit(TypeParameter *n)=0;
      virtual  void endVisit(TypeParameter *n)=0;

     virtual   bool visit(TypeBound *n)=0;
      virtual  void endVisit(TypeBound *n)=0;

     virtual   bool visit(AdditionalBoundList *n)=0;
      virtual  void endVisit(AdditionalBoundList *n)=0;

     virtual   bool visit(AdditionalBound *n)=0;
      virtual  void endVisit(AdditionalBound *n)=0;

     virtual   bool visit(TypeArguments *n)=0;
      virtual  void endVisit(TypeArguments *n)=0;

     virtual   bool visit(ActualTypeArgumentList *n)=0;
      virtual  void endVisit(ActualTypeArgumentList *n)=0;

     virtual   bool visit(Wildcard *n)=0;
      virtual  void endVisit(Wildcard *n)=0;

     virtual   bool visit(PackageName *n)=0;
      virtual  void endVisit(PackageName *n)=0;

     virtual   bool visit(ExpressionName *n)=0;
      virtual  void endVisit(ExpressionName *n)=0;

     virtual   bool visit(MethodName *n)=0;
      virtual  void endVisit(MethodName *n)=0;

     virtual   bool visit(PackageOrTypeName *n)=0;
      virtual  void endVisit(PackageOrTypeName *n)=0;

     virtual   bool visit(AmbiguousName *n)=0;
      virtual  void endVisit(AmbiguousName *n)=0;

     virtual   bool visit(CompilationUnit *n)=0;
      virtual  void endVisit(CompilationUnit *n)=0;

     virtual   bool visit(ImportDeclarations *n)=0;
      virtual  void endVisit(ImportDeclarations *n)=0;

     virtual   bool visit(TypeDeclarations *n)=0;
      virtual  void endVisit(TypeDeclarations *n)=0;

     virtual   bool visit(PackageDeclaration *n)=0;
      virtual  void endVisit(PackageDeclaration *n)=0;

     virtual   bool visit(SingleTypeImportDeclaration *n)=0;
      virtual  void endVisit(SingleTypeImportDeclaration *n)=0;

     virtual   bool visit(TypeImportOnDemandDeclaration *n)=0;
      virtual  void endVisit(TypeImportOnDemandDeclaration *n)=0;

     virtual   bool visit(SingleStaticImportDeclaration *n)=0;
      virtual  void endVisit(SingleStaticImportDeclaration *n)=0;

     virtual   bool visit(StaticImportOnDemandDeclaration *n)=0;
      virtual  void endVisit(StaticImportOnDemandDeclaration *n)=0;

     virtual   bool visit(TypeDeclaration *n)=0;
      virtual  void endVisit(TypeDeclaration *n)=0;

     virtual   bool visit(NormalClassDeclaration *n)=0;
      virtual  void endVisit(NormalClassDeclaration *n)=0;

     virtual   bool visit(ClassModifiers *n)=0;
      virtual  void endVisit(ClassModifiers *n)=0;

     virtual   bool visit(TypeParameters *n)=0;
      virtual  void endVisit(TypeParameters *n)=0;

     virtual   bool visit(TypeParameterList *n)=0;
      virtual  void endVisit(TypeParameterList *n)=0;

     virtual   bool visit(Super *n)=0;
      virtual  void endVisit(Super *n)=0;

     virtual   bool visit(Interfaces *n)=0;
      virtual  void endVisit(Interfaces *n)=0;

     virtual   bool visit(InterfaceTypeList *n)=0;
      virtual  void endVisit(InterfaceTypeList *n)=0;

     virtual   bool visit(ClassBody *n)=0;
      virtual  void endVisit(ClassBody *n)=0;

     virtual   bool visit(ClassBodyDeclarations *n)=0;
      virtual  void endVisit(ClassBodyDeclarations *n)=0;

     virtual   bool visit(ClassMemberDeclaration *n)=0;
      virtual  void endVisit(ClassMemberDeclaration *n)=0;

     virtual   bool visit(FieldDeclaration *n)=0;
      virtual  void endVisit(FieldDeclaration *n)=0;

     virtual   bool visit(VariableDeclarators *n)=0;
      virtual  void endVisit(VariableDeclarators *n)=0;

     virtual   bool visit(VariableDeclarator *n)=0;
      virtual  void endVisit(VariableDeclarator *n)=0;

     virtual   bool visit(VariableDeclaratorId *n)=0;
      virtual  void endVisit(VariableDeclaratorId *n)=0;

     virtual   bool visit(FieldModifiers *n)=0;
      virtual  void endVisit(FieldModifiers *n)=0;

     virtual   bool visit(MethodDeclaration *n)=0;
      virtual  void endVisit(MethodDeclaration *n)=0;

     virtual   bool visit(MethodHeader *n)=0;
      virtual  void endVisit(MethodHeader *n)=0;

     virtual   bool visit(ResultType *n)=0;
      virtual  void endVisit(ResultType *n)=0;

     virtual   bool visit(FormalParameterList *n)=0;
      virtual  void endVisit(FormalParameterList *n)=0;

     virtual   bool visit(FormalParameters *n)=0;
      virtual  void endVisit(FormalParameters *n)=0;

     virtual   bool visit(FormalParameter *n)=0;
      virtual  void endVisit(FormalParameter *n)=0;

     virtual   bool visit(VariableModifiers *n)=0;
      virtual  void endVisit(VariableModifiers *n)=0;

     virtual   bool visit(VariableModifier *n)=0;
      virtual  void endVisit(VariableModifier *n)=0;

     virtual   bool visit(LastFormalParameter *n)=0;
      virtual  void endVisit(LastFormalParameter *n)=0;

     virtual   bool visit(MethodModifiers *n)=0;
      virtual  void endVisit(MethodModifiers *n)=0;

     virtual   bool visit(Throws *n)=0;
      virtual  void endVisit(Throws *n)=0;

     virtual   bool visit(ExceptionTypeList *n)=0;
      virtual  void endVisit(ExceptionTypeList *n)=0;

     virtual   bool visit(MethodBody *n)=0;
      virtual  void endVisit(MethodBody *n)=0;

     virtual   bool visit(StaticInitializer *n)=0;
      virtual  void endVisit(StaticInitializer *n)=0;

     virtual   bool visit(ConstructorDeclaration *n)=0;
      virtual  void endVisit(ConstructorDeclaration *n)=0;

     virtual   bool visit(ConstructorDeclarator *n)=0;
      virtual  void endVisit(ConstructorDeclarator *n)=0;

     virtual   bool visit(ConstructorModifiers *n)=0;
      virtual  void endVisit(ConstructorModifiers *n)=0;

     virtual   bool visit(ConstructorBody *n)=0;
      virtual  void endVisit(ConstructorBody *n)=0;

     virtual   bool visit(EnumDeclaration *n)=0;
      virtual  void endVisit(EnumDeclaration *n)=0;

     virtual   bool visit(EnumBody *n)=0;
      virtual  void endVisit(EnumBody *n)=0;

     virtual   bool visit(EnumConstants *n)=0;
      virtual  void endVisit(EnumConstants *n)=0;

     virtual   bool visit(EnumConstant *n)=0;
      virtual  void endVisit(EnumConstant *n)=0;

     virtual   bool visit(Arguments *n)=0;
      virtual  void endVisit(Arguments *n)=0;

     virtual   bool visit(EnumBodyDeclarations *n)=0;
      virtual  void endVisit(EnumBodyDeclarations *n)=0;

     virtual   bool visit(NormalInterfaceDeclaration *n)=0;
      virtual  void endVisit(NormalInterfaceDeclaration *n)=0;

     virtual   bool visit(InterfaceModifiers *n)=0;
      virtual  void endVisit(InterfaceModifiers *n)=0;

     virtual   bool visit(InterfaceBody *n)=0;
      virtual  void endVisit(InterfaceBody *n)=0;

     virtual   bool visit(InterfaceMemberDeclarations *n)=0;
      virtual  void endVisit(InterfaceMemberDeclarations *n)=0;

     virtual   bool visit(InterfaceMemberDeclaration *n)=0;
      virtual  void endVisit(InterfaceMemberDeclaration *n)=0;

     virtual   bool visit(ConstantDeclaration *n)=0;
      virtual  void endVisit(ConstantDeclaration *n)=0;

     virtual   bool visit(ConstantModifiers *n)=0;
      virtual  void endVisit(ConstantModifiers *n)=0;

     virtual   bool visit(AbstractMethodDeclaration *n)=0;
      virtual  void endVisit(AbstractMethodDeclaration *n)=0;

     virtual   bool visit(AbstractMethodModifiers *n)=0;
      virtual  void endVisit(AbstractMethodModifiers *n)=0;

     virtual   bool visit(AnnotationTypeDeclaration *n)=0;
      virtual  void endVisit(AnnotationTypeDeclaration *n)=0;

     virtual   bool visit(AnnotationTypeBody *n)=0;
      virtual  void endVisit(AnnotationTypeBody *n)=0;

     virtual   bool visit(AnnotationTypeElementDeclarations *n)=0;
      virtual  void endVisit(AnnotationTypeElementDeclarations *n)=0;

     virtual   bool visit(DefaultValue *n)=0;
      virtual  void endVisit(DefaultValue *n)=0;

     virtual   bool visit(Annotations *n)=0;
      virtual  void endVisit(Annotations *n)=0;

     virtual   bool visit(NormalAnnotation *n)=0;
      virtual  void endVisit(NormalAnnotation *n)=0;

     virtual   bool visit(ElementValuePairs *n)=0;
      virtual  void endVisit(ElementValuePairs *n)=0;

     virtual   bool visit(ElementValuePair *n)=0;
      virtual  void endVisit(ElementValuePair *n)=0;

     virtual   bool visit(ElementValueArrayInitializer *n)=0;
      virtual  void endVisit(ElementValueArrayInitializer *n)=0;

     virtual   bool visit(ElementValues *n)=0;
      virtual  void endVisit(ElementValues *n)=0;

     virtual   bool visit(MarkerAnnotation *n)=0;
      virtual  void endVisit(MarkerAnnotation *n)=0;

     virtual   bool visit(SingleElementAnnotation *n)=0;
      virtual  void endVisit(SingleElementAnnotation *n)=0;

     virtual   bool visit(ArrayInitializer *n)=0;
      virtual  void endVisit(ArrayInitializer *n)=0;

     virtual   bool visit(VariableInitializers *n)=0;
      virtual  void endVisit(VariableInitializers *n)=0;

     virtual   bool visit(Block *n)=0;
      virtual  void endVisit(Block *n)=0;

     virtual   bool visit(BlockStatements *n)=0;
      virtual  void endVisit(BlockStatements *n)=0;

     virtual   bool visit(LocalVariableDeclarationStatement *n)=0;
      virtual  void endVisit(LocalVariableDeclarationStatement *n)=0;

     virtual   bool visit(LocalVariableDeclaration *n)=0;
      virtual  void endVisit(LocalVariableDeclaration *n)=0;

     virtual   bool visit(IfThenStatement *n)=0;
      virtual  void endVisit(IfThenStatement *n)=0;

     virtual   bool visit(IfThenElseStatement *n)=0;
      virtual  void endVisit(IfThenElseStatement *n)=0;

     virtual   bool visit(IfThenElseStatementNoShortIf *n)=0;
      virtual  void endVisit(IfThenElseStatementNoShortIf *n)=0;

     virtual   bool visit(EmptyStatement *n)=0;
      virtual  void endVisit(EmptyStatement *n)=0;

     virtual   bool visit(LabeledStatement *n)=0;
      virtual  void endVisit(LabeledStatement *n)=0;

     virtual   bool visit(LabeledStatementNoShortIf *n)=0;
      virtual  void endVisit(LabeledStatementNoShortIf *n)=0;

     virtual   bool visit(ExpressionStatement *n)=0;
      virtual  void endVisit(ExpressionStatement *n)=0;

     virtual   bool visit(SwitchStatement *n)=0;
      virtual  void endVisit(SwitchStatement *n)=0;

     virtual   bool visit(SwitchBlock *n)=0;
      virtual  void endVisit(SwitchBlock *n)=0;

     virtual   bool visit(SwitchBlockStatementGroups *n)=0;
      virtual  void endVisit(SwitchBlockStatementGroups *n)=0;

     virtual   bool visit(SwitchBlockStatementGroup *n)=0;
      virtual  void endVisit(SwitchBlockStatementGroup *n)=0;

     virtual   bool visit(SwitchLabels *n)=0;
      virtual  void endVisit(SwitchLabels *n)=0;

     virtual   bool visit(WhileStatement *n)=0;
      virtual  void endVisit(WhileStatement *n)=0;

     virtual   bool visit(WhileStatementNoShortIf *n)=0;
      virtual  void endVisit(WhileStatementNoShortIf *n)=0;

     virtual   bool visit(DoStatement *n)=0;
      virtual  void endVisit(DoStatement *n)=0;

     virtual   bool visit(BasicForStatement *n)=0;
      virtual  void endVisit(BasicForStatement *n)=0;

     virtual   bool visit(ForStatementNoShortIf *n)=0;
      virtual  void endVisit(ForStatementNoShortIf *n)=0;

     virtual   bool visit(StatementExpressionList *n)=0;
      virtual  void endVisit(StatementExpressionList *n)=0;

     virtual   bool visit(EnhancedForStatement *n)=0;
      virtual  void endVisit(EnhancedForStatement *n)=0;

     virtual   bool visit(BreakStatement *n)=0;
      virtual  void endVisit(BreakStatement *n)=0;

     virtual   bool visit(ContinueStatement *n)=0;
      virtual  void endVisit(ContinueStatement *n)=0;

     virtual   bool visit(ReturnStatement *n)=0;
      virtual  void endVisit(ReturnStatement *n)=0;

     virtual   bool visit(ThrowStatement *n)=0;
      virtual  void endVisit(ThrowStatement *n)=0;

     virtual   bool visit(SynchronizedStatement *n)=0;
      virtual  void endVisit(SynchronizedStatement *n)=0;

     virtual   bool visit(Catches *n)=0;
      virtual  void endVisit(Catches *n)=0;

     virtual   bool visit(CatchClause *n)=0;
      virtual  void endVisit(CatchClause *n)=0;

     virtual   bool visit(Finally *n)=0;
      virtual  void endVisit(Finally *n)=0;

     virtual   bool visit(ArgumentList *n)=0;
      virtual  void endVisit(ArgumentList *n)=0;

     virtual   bool visit(DimExprs *n)=0;
      virtual  void endVisit(DimExprs *n)=0;

     virtual   bool visit(DimExpr *n)=0;
      virtual  void endVisit(DimExpr *n)=0;

     virtual   bool visit(PostIncrementExpression *n)=0;
      virtual  void endVisit(PostIncrementExpression *n)=0;

     virtual   bool visit(PostDecrementExpression *n)=0;
      virtual  void endVisit(PostDecrementExpression *n)=0;

     virtual   bool visit(PreIncrementExpression *n)=0;
      virtual  void endVisit(PreIncrementExpression *n)=0;

     virtual   bool visit(PreDecrementExpression *n)=0;
      virtual  void endVisit(PreDecrementExpression *n)=0;

     virtual   bool visit(AndExpression *n)=0;
      virtual  void endVisit(AndExpression *n)=0;

     virtual   bool visit(ExclusiveOrExpression *n)=0;
      virtual  void endVisit(ExclusiveOrExpression *n)=0;

     virtual   bool visit(InclusiveOrExpression *n)=0;
      virtual  void endVisit(InclusiveOrExpression *n)=0;

     virtual   bool visit(ConditionalAndExpression *n)=0;
      virtual  void endVisit(ConditionalAndExpression *n)=0;

     virtual   bool visit(ConditionalOrExpression *n)=0;
      virtual  void endVisit(ConditionalOrExpression *n)=0;

     virtual   bool visit(ConditionalExpression *n)=0;
      virtual  void endVisit(ConditionalExpression *n)=0;

     virtual   bool visit(Assignment *n)=0;
      virtual  void endVisit(Assignment *n)=0;

     virtual   bool visit(Commaopt *n)=0;
      virtual  void endVisit(Commaopt *n)=0;

     virtual   bool visit(Ellipsisopt *n)=0;
      virtual  void endVisit(Ellipsisopt *n)=0;

     virtual   bool visit(LPGUserAction0 *n)=0;
      virtual  void endVisit(LPGUserAction0 *n)=0;

     virtual   bool visit(LPGUserAction1 *n)=0;
      virtual  void endVisit(LPGUserAction1 *n)=0;

     virtual   bool visit(LPGUserAction2 *n)=0;
      virtual  void endVisit(LPGUserAction2 *n)=0;

     virtual   bool visit(LPGUserAction3 *n)=0;
      virtual  void endVisit(LPGUserAction3 *n)=0;

     virtual   bool visit(LPGUserAction4 *n)=0;
      virtual  void endVisit(LPGUserAction4 *n)=0;

     virtual   bool visit(IntegralType0 *n)=0;
      virtual  void endVisit(IntegralType0 *n)=0;

     virtual   bool visit(IntegralType1 *n)=0;
      virtual  void endVisit(IntegralType1 *n)=0;

     virtual   bool visit(IntegralType2 *n)=0;
      virtual  void endVisit(IntegralType2 *n)=0;

     virtual   bool visit(IntegralType3 *n)=0;
      virtual  void endVisit(IntegralType3 *n)=0;

     virtual   bool visit(IntegralType4 *n)=0;
      virtual  void endVisit(IntegralType4 *n)=0;

     virtual   bool visit(FloatingPointType0 *n)=0;
      virtual  void endVisit(FloatingPointType0 *n)=0;

     virtual   bool visit(FloatingPointType1 *n)=0;
      virtual  void endVisit(FloatingPointType1 *n)=0;

     virtual   bool visit(WildcardBounds0 *n)=0;
      virtual  void endVisit(WildcardBounds0 *n)=0;

     virtual   bool visit(WildcardBounds1 *n)=0;
      virtual  void endVisit(WildcardBounds1 *n)=0;

     virtual   bool visit(ClassModifier0 *n)=0;
      virtual  void endVisit(ClassModifier0 *n)=0;

     virtual   bool visit(ClassModifier1 *n)=0;
      virtual  void endVisit(ClassModifier1 *n)=0;

     virtual   bool visit(ClassModifier2 *n)=0;
      virtual  void endVisit(ClassModifier2 *n)=0;

     virtual   bool visit(ClassModifier3 *n)=0;
      virtual  void endVisit(ClassModifier3 *n)=0;

     virtual   bool visit(ClassModifier4 *n)=0;
      virtual  void endVisit(ClassModifier4 *n)=0;

     virtual   bool visit(ClassModifier5 *n)=0;
      virtual  void endVisit(ClassModifier5 *n)=0;

     virtual   bool visit(ClassModifier6 *n)=0;
      virtual  void endVisit(ClassModifier6 *n)=0;

     virtual   bool visit(FieldModifier0 *n)=0;
      virtual  void endVisit(FieldModifier0 *n)=0;

     virtual   bool visit(FieldModifier1 *n)=0;
      virtual  void endVisit(FieldModifier1 *n)=0;

     virtual   bool visit(FieldModifier2 *n)=0;
      virtual  void endVisit(FieldModifier2 *n)=0;

     virtual   bool visit(FieldModifier3 *n)=0;
      virtual  void endVisit(FieldModifier3 *n)=0;

     virtual   bool visit(FieldModifier4 *n)=0;
      virtual  void endVisit(FieldModifier4 *n)=0;

     virtual   bool visit(FieldModifier5 *n)=0;
      virtual  void endVisit(FieldModifier5 *n)=0;

     virtual   bool visit(FieldModifier6 *n)=0;
      virtual  void endVisit(FieldModifier6 *n)=0;

     virtual   bool visit(MethodDeclarator0 *n)=0;
      virtual  void endVisit(MethodDeclarator0 *n)=0;

     virtual   bool visit(MethodDeclarator1 *n)=0;
      virtual  void endVisit(MethodDeclarator1 *n)=0;

     virtual   bool visit(MethodModifier0 *n)=0;
      virtual  void endVisit(MethodModifier0 *n)=0;

     virtual   bool visit(MethodModifier1 *n)=0;
      virtual  void endVisit(MethodModifier1 *n)=0;

     virtual   bool visit(MethodModifier2 *n)=0;
      virtual  void endVisit(MethodModifier2 *n)=0;

     virtual   bool visit(MethodModifier3 *n)=0;
      virtual  void endVisit(MethodModifier3 *n)=0;

     virtual   bool visit(MethodModifier4 *n)=0;
      virtual  void endVisit(MethodModifier4 *n)=0;

     virtual   bool visit(MethodModifier5 *n)=0;
      virtual  void endVisit(MethodModifier5 *n)=0;

     virtual   bool visit(MethodModifier6 *n)=0;
      virtual  void endVisit(MethodModifier6 *n)=0;

     virtual   bool visit(MethodModifier7 *n)=0;
      virtual  void endVisit(MethodModifier7 *n)=0;

     virtual   bool visit(MethodModifier8 *n)=0;
      virtual  void endVisit(MethodModifier8 *n)=0;

     virtual   bool visit(ConstructorModifier0 *n)=0;
      virtual  void endVisit(ConstructorModifier0 *n)=0;

     virtual   bool visit(ConstructorModifier1 *n)=0;
      virtual  void endVisit(ConstructorModifier1 *n)=0;

     virtual   bool visit(ConstructorModifier2 *n)=0;
      virtual  void endVisit(ConstructorModifier2 *n)=0;

     virtual   bool visit(ExplicitConstructorInvocation0 *n)=0;
      virtual  void endVisit(ExplicitConstructorInvocation0 *n)=0;

     virtual   bool visit(ExplicitConstructorInvocation1 *n)=0;
      virtual  void endVisit(ExplicitConstructorInvocation1 *n)=0;

     virtual   bool visit(ExplicitConstructorInvocation2 *n)=0;
      virtual  void endVisit(ExplicitConstructorInvocation2 *n)=0;

     virtual   bool visit(InterfaceModifier0 *n)=0;
      virtual  void endVisit(InterfaceModifier0 *n)=0;

     virtual   bool visit(InterfaceModifier1 *n)=0;
      virtual  void endVisit(InterfaceModifier1 *n)=0;

     virtual   bool visit(InterfaceModifier2 *n)=0;
      virtual  void endVisit(InterfaceModifier2 *n)=0;

     virtual   bool visit(InterfaceModifier3 *n)=0;
      virtual  void endVisit(InterfaceModifier3 *n)=0;

     virtual   bool visit(InterfaceModifier4 *n)=0;
      virtual  void endVisit(InterfaceModifier4 *n)=0;

     virtual   bool visit(InterfaceModifier5 *n)=0;
      virtual  void endVisit(InterfaceModifier5 *n)=0;

     virtual   bool visit(ExtendsInterfaces0 *n)=0;
      virtual  void endVisit(ExtendsInterfaces0 *n)=0;

     virtual   bool visit(ExtendsInterfaces1 *n)=0;
      virtual  void endVisit(ExtendsInterfaces1 *n)=0;

     virtual   bool visit(ConstantModifier0 *n)=0;
      virtual  void endVisit(ConstantModifier0 *n)=0;

     virtual   bool visit(ConstantModifier1 *n)=0;
      virtual  void endVisit(ConstantModifier1 *n)=0;

     virtual   bool visit(ConstantModifier2 *n)=0;
      virtual  void endVisit(ConstantModifier2 *n)=0;

     virtual   bool visit(AbstractMethodModifier0 *n)=0;
      virtual  void endVisit(AbstractMethodModifier0 *n)=0;

     virtual   bool visit(AbstractMethodModifier1 *n)=0;
      virtual  void endVisit(AbstractMethodModifier1 *n)=0;

     virtual   bool visit(AnnotationTypeElementDeclaration0 *n)=0;
      virtual  void endVisit(AnnotationTypeElementDeclaration0 *n)=0;

     virtual   bool visit(AnnotationTypeElementDeclaration1 *n)=0;
      virtual  void endVisit(AnnotationTypeElementDeclaration1 *n)=0;

     virtual   bool visit(AssertStatement0 *n)=0;
      virtual  void endVisit(AssertStatement0 *n)=0;

     virtual   bool visit(AssertStatement1 *n)=0;
      virtual  void endVisit(AssertStatement1 *n)=0;

     virtual   bool visit(SwitchLabel0 *n)=0;
      virtual  void endVisit(SwitchLabel0 *n)=0;

     virtual   bool visit(SwitchLabel1 *n)=0;
      virtual  void endVisit(SwitchLabel1 *n)=0;

     virtual   bool visit(SwitchLabel2 *n)=0;
      virtual  void endVisit(SwitchLabel2 *n)=0;

     virtual   bool visit(TryStatement0 *n)=0;
      virtual  void endVisit(TryStatement0 *n)=0;

     virtual   bool visit(TryStatement1 *n)=0;
      virtual  void endVisit(TryStatement1 *n)=0;

     virtual   bool visit(PrimaryNoNewArray0 *n)=0;
      virtual  void endVisit(PrimaryNoNewArray0 *n)=0;

     virtual   bool visit(PrimaryNoNewArray1 *n)=0;
      virtual  void endVisit(PrimaryNoNewArray1 *n)=0;

     virtual   bool visit(PrimaryNoNewArray2 *n)=0;
      virtual  void endVisit(PrimaryNoNewArray2 *n)=0;

     virtual   bool visit(PrimaryNoNewArray3 *n)=0;
      virtual  void endVisit(PrimaryNoNewArray3 *n)=0;

     virtual   bool visit(PrimaryNoNewArray4 *n)=0;
      virtual  void endVisit(PrimaryNoNewArray4 *n)=0;

     virtual   bool visit(Literal0 *n)=0;
      virtual  void endVisit(Literal0 *n)=0;

     virtual   bool visit(Literal1 *n)=0;
      virtual  void endVisit(Literal1 *n)=0;

     virtual   bool visit(Literal2 *n)=0;
      virtual  void endVisit(Literal2 *n)=0;

     virtual   bool visit(Literal3 *n)=0;
      virtual  void endVisit(Literal3 *n)=0;

     virtual   bool visit(Literal4 *n)=0;
      virtual  void endVisit(Literal4 *n)=0;

     virtual   bool visit(Literal5 *n)=0;
      virtual  void endVisit(Literal5 *n)=0;

     virtual   bool visit(Literal6 *n)=0;
      virtual  void endVisit(Literal6 *n)=0;

     virtual   bool visit(BooleanLiteral0 *n)=0;
      virtual  void endVisit(BooleanLiteral0 *n)=0;

     virtual   bool visit(BooleanLiteral1 *n)=0;
      virtual  void endVisit(BooleanLiteral1 *n)=0;

     virtual   bool visit(ClassInstanceCreationExpression0 *n)=0;
      virtual  void endVisit(ClassInstanceCreationExpression0 *n)=0;

     virtual   bool visit(ClassInstanceCreationExpression1 *n)=0;
      virtual  void endVisit(ClassInstanceCreationExpression1 *n)=0;

     virtual   bool visit(ArrayCreationExpression0 *n)=0;
      virtual  void endVisit(ArrayCreationExpression0 *n)=0;

     virtual   bool visit(ArrayCreationExpression1 *n)=0;
      virtual  void endVisit(ArrayCreationExpression1 *n)=0;

     virtual   bool visit(ArrayCreationExpression2 *n)=0;
      virtual  void endVisit(ArrayCreationExpression2 *n)=0;

     virtual   bool visit(ArrayCreationExpression3 *n)=0;
      virtual  void endVisit(ArrayCreationExpression3 *n)=0;

     virtual   bool visit(Dims0 *n)=0;
      virtual  void endVisit(Dims0 *n)=0;

     virtual   bool visit(Dims1 *n)=0;
      virtual  void endVisit(Dims1 *n)=0;

     virtual   bool visit(FieldAccess0 *n)=0;
      virtual  void endVisit(FieldAccess0 *n)=0;

     virtual   bool visit(FieldAccess1 *n)=0;
      virtual  void endVisit(FieldAccess1 *n)=0;

     virtual   bool visit(FieldAccess2 *n)=0;
      virtual  void endVisit(FieldAccess2 *n)=0;

     virtual   bool visit(MethodInvocation0 *n)=0;
      virtual  void endVisit(MethodInvocation0 *n)=0;

     virtual   bool visit(MethodInvocation1 *n)=0;
      virtual  void endVisit(MethodInvocation1 *n)=0;

     virtual   bool visit(MethodInvocation2 *n)=0;
      virtual  void endVisit(MethodInvocation2 *n)=0;

     virtual   bool visit(MethodInvocation3 *n)=0;
      virtual  void endVisit(MethodInvocation3 *n)=0;

     virtual   bool visit(MethodInvocation4 *n)=0;
      virtual  void endVisit(MethodInvocation4 *n)=0;

     virtual   bool visit(ArrayAccess0 *n)=0;
      virtual  void endVisit(ArrayAccess0 *n)=0;

     virtual   bool visit(ArrayAccess1 *n)=0;
      virtual  void endVisit(ArrayAccess1 *n)=0;

     virtual   bool visit(UnaryExpression0 *n)=0;
      virtual  void endVisit(UnaryExpression0 *n)=0;

     virtual   bool visit(UnaryExpression1 *n)=0;
      virtual  void endVisit(UnaryExpression1 *n)=0;

     virtual   bool visit(UnaryExpressionNotPlusMinus0 *n)=0;
      virtual  void endVisit(UnaryExpressionNotPlusMinus0 *n)=0;

     virtual   bool visit(UnaryExpressionNotPlusMinus1 *n)=0;
      virtual  void endVisit(UnaryExpressionNotPlusMinus1 *n)=0;

     virtual   bool visit(CastExpression0 *n)=0;
      virtual  void endVisit(CastExpression0 *n)=0;

     virtual   bool visit(CastExpression1 *n)=0;
      virtual  void endVisit(CastExpression1 *n)=0;

     virtual   bool visit(MultiplicativeExpression0 *n)=0;
      virtual  void endVisit(MultiplicativeExpression0 *n)=0;

     virtual   bool visit(MultiplicativeExpression1 *n)=0;
      virtual  void endVisit(MultiplicativeExpression1 *n)=0;

     virtual   bool visit(MultiplicativeExpression2 *n)=0;
      virtual  void endVisit(MultiplicativeExpression2 *n)=0;

     virtual   bool visit(AdditiveExpression0 *n)=0;
      virtual  void endVisit(AdditiveExpression0 *n)=0;

     virtual   bool visit(AdditiveExpression1 *n)=0;
      virtual  void endVisit(AdditiveExpression1 *n)=0;

     virtual   bool visit(ShiftExpression0 *n)=0;
      virtual  void endVisit(ShiftExpression0 *n)=0;

     virtual   bool visit(ShiftExpression1 *n)=0;
      virtual  void endVisit(ShiftExpression1 *n)=0;

     virtual   bool visit(ShiftExpression2 *n)=0;
      virtual  void endVisit(ShiftExpression2 *n)=0;

     virtual   bool visit(RelationalExpression0 *n)=0;
      virtual  void endVisit(RelationalExpression0 *n)=0;

     virtual   bool visit(RelationalExpression1 *n)=0;
      virtual  void endVisit(RelationalExpression1 *n)=0;

     virtual   bool visit(RelationalExpression2 *n)=0;
      virtual  void endVisit(RelationalExpression2 *n)=0;

     virtual   bool visit(RelationalExpression3 *n)=0;
      virtual  void endVisit(RelationalExpression3 *n)=0;

     virtual   bool visit(RelationalExpression4 *n)=0;
      virtual  void endVisit(RelationalExpression4 *n)=0;

     virtual   bool visit(EqualityExpression0 *n)=0;
      virtual  void endVisit(EqualityExpression0 *n)=0;

     virtual   bool visit(EqualityExpression1 *n)=0;
      virtual  void endVisit(EqualityExpression1 *n)=0;

     virtual   bool visit(AssignmentOperator0 *n)=0;
      virtual  void endVisit(AssignmentOperator0 *n)=0;

     virtual   bool visit(AssignmentOperator1 *n)=0;
      virtual  void endVisit(AssignmentOperator1 *n)=0;

     virtual   bool visit(AssignmentOperator2 *n)=0;
      virtual  void endVisit(AssignmentOperator2 *n)=0;

     virtual   bool visit(AssignmentOperator3 *n)=0;
      virtual  void endVisit(AssignmentOperator3 *n)=0;

     virtual   bool visit(AssignmentOperator4 *n)=0;
      virtual  void endVisit(AssignmentOperator4 *n)=0;

     virtual   bool visit(AssignmentOperator5 *n)=0;
      virtual  void endVisit(AssignmentOperator5 *n)=0;

     virtual   bool visit(AssignmentOperator6 *n)=0;
      virtual  void endVisit(AssignmentOperator6 *n)=0;

     virtual   bool visit(AssignmentOperator7 *n)=0;
      virtual  void endVisit(AssignmentOperator7 *n)=0;

     virtual   bool visit(AssignmentOperator8 *n)=0;
      virtual  void endVisit(AssignmentOperator8 *n)=0;

     virtual   bool visit(AssignmentOperator9 *n)=0;
      virtual  void endVisit(AssignmentOperator9 *n)=0;

     virtual   bool visit(AssignmentOperator10 *n)=0;
      virtual  void endVisit(AssignmentOperator10 *n)=0;

     virtual   bool visit(AssignmentOperator11 *n)=0;
      virtual  void endVisit(AssignmentOperator11 *n)=0;

    };

    struct AbstractVisitor :public Visitor
    {
        virtual void unimplementedVisitor(const std::string& s)=0;

       virtual bool preVisit(IAst* element) { return true; }

       virtual void postVisit(IAst* element) {}

     virtual   bool visit(AstToken *n) { unimplementedVisitor("visit(AstToken)"); return true; }
      virtual  void endVisit(AstToken *n) { unimplementedVisitor("endVisit(AstToken)"); }

     virtual   bool visit(identifier *n) { unimplementedVisitor("visit(identifier)"); return true; }
      virtual  void endVisit(identifier *n) { unimplementedVisitor("endVisit(identifier)"); }

     virtual   bool visit(PrimitiveType *n) { unimplementedVisitor("visit(PrimitiveType)"); return true; }
      virtual  void endVisit(PrimitiveType *n) { unimplementedVisitor("endVisit(PrimitiveType)"); }

     virtual   bool visit(ClassType *n) { unimplementedVisitor("visit(ClassType)"); return true; }
      virtual  void endVisit(ClassType *n) { unimplementedVisitor("endVisit(ClassType)"); }

     virtual   bool visit(InterfaceType *n) { unimplementedVisitor("visit(InterfaceType)"); return true; }
      virtual  void endVisit(InterfaceType *n) { unimplementedVisitor("endVisit(InterfaceType)"); }

     virtual   bool visit(TypeName *n) { unimplementedVisitor("visit(TypeName)"); return true; }
      virtual  void endVisit(TypeName *n) { unimplementedVisitor("endVisit(TypeName)"); }

     virtual   bool visit(ArrayType *n) { unimplementedVisitor("visit(ArrayType)"); return true; }
      virtual  void endVisit(ArrayType *n) { unimplementedVisitor("endVisit(ArrayType)"); }

     virtual   bool visit(TypeParameter *n) { unimplementedVisitor("visit(TypeParameter)"); return true; }
      virtual  void endVisit(TypeParameter *n) { unimplementedVisitor("endVisit(TypeParameter)"); }

     virtual   bool visit(TypeBound *n) { unimplementedVisitor("visit(TypeBound)"); return true; }
      virtual  void endVisit(TypeBound *n) { unimplementedVisitor("endVisit(TypeBound)"); }

     virtual   bool visit(AdditionalBoundList *n) { unimplementedVisitor("visit(AdditionalBoundList)"); return true; }
      virtual  void endVisit(AdditionalBoundList *n) { unimplementedVisitor("endVisit(AdditionalBoundList)"); }

     virtual   bool visit(AdditionalBound *n) { unimplementedVisitor("visit(AdditionalBound)"); return true; }
      virtual  void endVisit(AdditionalBound *n) { unimplementedVisitor("endVisit(AdditionalBound)"); }

     virtual   bool visit(TypeArguments *n) { unimplementedVisitor("visit(TypeArguments)"); return true; }
      virtual  void endVisit(TypeArguments *n) { unimplementedVisitor("endVisit(TypeArguments)"); }

     virtual   bool visit(ActualTypeArgumentList *n) { unimplementedVisitor("visit(ActualTypeArgumentList)"); return true; }
      virtual  void endVisit(ActualTypeArgumentList *n) { unimplementedVisitor("endVisit(ActualTypeArgumentList)"); }

     virtual   bool visit(Wildcard *n) { unimplementedVisitor("visit(Wildcard)"); return true; }
      virtual  void endVisit(Wildcard *n) { unimplementedVisitor("endVisit(Wildcard)"); }

     virtual   bool visit(PackageName *n) { unimplementedVisitor("visit(PackageName)"); return true; }
      virtual  void endVisit(PackageName *n) { unimplementedVisitor("endVisit(PackageName)"); }

     virtual   bool visit(ExpressionName *n) { unimplementedVisitor("visit(ExpressionName)"); return true; }
      virtual  void endVisit(ExpressionName *n) { unimplementedVisitor("endVisit(ExpressionName)"); }

     virtual   bool visit(MethodName *n) { unimplementedVisitor("visit(MethodName)"); return true; }
      virtual  void endVisit(MethodName *n) { unimplementedVisitor("endVisit(MethodName)"); }

     virtual   bool visit(PackageOrTypeName *n) { unimplementedVisitor("visit(PackageOrTypeName)"); return true; }
      virtual  void endVisit(PackageOrTypeName *n) { unimplementedVisitor("endVisit(PackageOrTypeName)"); }

     virtual   bool visit(AmbiguousName *n) { unimplementedVisitor("visit(AmbiguousName)"); return true; }
      virtual  void endVisit(AmbiguousName *n) { unimplementedVisitor("endVisit(AmbiguousName)"); }

     virtual   bool visit(CompilationUnit *n) { unimplementedVisitor("visit(CompilationUnit)"); return true; }
      virtual  void endVisit(CompilationUnit *n) { unimplementedVisitor("endVisit(CompilationUnit)"); }

     virtual   bool visit(ImportDeclarations *n) { unimplementedVisitor("visit(ImportDeclarations)"); return true; }
      virtual  void endVisit(ImportDeclarations *n) { unimplementedVisitor("endVisit(ImportDeclarations)"); }

     virtual   bool visit(TypeDeclarations *n) { unimplementedVisitor("visit(TypeDeclarations)"); return true; }
      virtual  void endVisit(TypeDeclarations *n) { unimplementedVisitor("endVisit(TypeDeclarations)"); }

     virtual   bool visit(PackageDeclaration *n) { unimplementedVisitor("visit(PackageDeclaration)"); return true; }
      virtual  void endVisit(PackageDeclaration *n) { unimplementedVisitor("endVisit(PackageDeclaration)"); }

     virtual   bool visit(SingleTypeImportDeclaration *n) { unimplementedVisitor("visit(SingleTypeImportDeclaration)"); return true; }
      virtual  void endVisit(SingleTypeImportDeclaration *n) { unimplementedVisitor("endVisit(SingleTypeImportDeclaration)"); }

     virtual   bool visit(TypeImportOnDemandDeclaration *n) { unimplementedVisitor("visit(TypeImportOnDemandDeclaration)"); return true; }
      virtual  void endVisit(TypeImportOnDemandDeclaration *n) { unimplementedVisitor("endVisit(TypeImportOnDemandDeclaration)"); }

     virtual   bool visit(SingleStaticImportDeclaration *n) { unimplementedVisitor("visit(SingleStaticImportDeclaration)"); return true; }
      virtual  void endVisit(SingleStaticImportDeclaration *n) { unimplementedVisitor("endVisit(SingleStaticImportDeclaration)"); }

     virtual   bool visit(StaticImportOnDemandDeclaration *n) { unimplementedVisitor("visit(StaticImportOnDemandDeclaration)"); return true; }
      virtual  void endVisit(StaticImportOnDemandDeclaration *n) { unimplementedVisitor("endVisit(StaticImportOnDemandDeclaration)"); }

     virtual   bool visit(TypeDeclaration *n) { unimplementedVisitor("visit(TypeDeclaration)"); return true; }
      virtual  void endVisit(TypeDeclaration *n) { unimplementedVisitor("endVisit(TypeDeclaration)"); }

     virtual   bool visit(NormalClassDeclaration *n) { unimplementedVisitor("visit(NormalClassDeclaration)"); return true; }
      virtual  void endVisit(NormalClassDeclaration *n) { unimplementedVisitor("endVisit(NormalClassDeclaration)"); }

     virtual   bool visit(ClassModifiers *n) { unimplementedVisitor("visit(ClassModifiers)"); return true; }
      virtual  void endVisit(ClassModifiers *n) { unimplementedVisitor("endVisit(ClassModifiers)"); }

     virtual   bool visit(TypeParameters *n) { unimplementedVisitor("visit(TypeParameters)"); return true; }
      virtual  void endVisit(TypeParameters *n) { unimplementedVisitor("endVisit(TypeParameters)"); }

     virtual   bool visit(TypeParameterList *n) { unimplementedVisitor("visit(TypeParameterList)"); return true; }
      virtual  void endVisit(TypeParameterList *n) { unimplementedVisitor("endVisit(TypeParameterList)"); }

     virtual   bool visit(Super *n) { unimplementedVisitor("visit(Super)"); return true; }
      virtual  void endVisit(Super *n) { unimplementedVisitor("endVisit(Super)"); }

     virtual   bool visit(Interfaces *n) { unimplementedVisitor("visit(Interfaces)"); return true; }
      virtual  void endVisit(Interfaces *n) { unimplementedVisitor("endVisit(Interfaces)"); }

     virtual   bool visit(InterfaceTypeList *n) { unimplementedVisitor("visit(InterfaceTypeList)"); return true; }
      virtual  void endVisit(InterfaceTypeList *n) { unimplementedVisitor("endVisit(InterfaceTypeList)"); }

     virtual   bool visit(ClassBody *n) { unimplementedVisitor("visit(ClassBody)"); return true; }
      virtual  void endVisit(ClassBody *n) { unimplementedVisitor("endVisit(ClassBody)"); }

     virtual   bool visit(ClassBodyDeclarations *n) { unimplementedVisitor("visit(ClassBodyDeclarations)"); return true; }
      virtual  void endVisit(ClassBodyDeclarations *n) { unimplementedVisitor("endVisit(ClassBodyDeclarations)"); }

     virtual   bool visit(ClassMemberDeclaration *n) { unimplementedVisitor("visit(ClassMemberDeclaration)"); return true; }
      virtual  void endVisit(ClassMemberDeclaration *n) { unimplementedVisitor("endVisit(ClassMemberDeclaration)"); }

     virtual   bool visit(FieldDeclaration *n) { unimplementedVisitor("visit(FieldDeclaration)"); return true; }
      virtual  void endVisit(FieldDeclaration *n) { unimplementedVisitor("endVisit(FieldDeclaration)"); }

     virtual   bool visit(VariableDeclarators *n) { unimplementedVisitor("visit(VariableDeclarators)"); return true; }
      virtual  void endVisit(VariableDeclarators *n) { unimplementedVisitor("endVisit(VariableDeclarators)"); }

     virtual   bool visit(VariableDeclarator *n) { unimplementedVisitor("visit(VariableDeclarator)"); return true; }
      virtual  void endVisit(VariableDeclarator *n) { unimplementedVisitor("endVisit(VariableDeclarator)"); }

     virtual   bool visit(VariableDeclaratorId *n) { unimplementedVisitor("visit(VariableDeclaratorId)"); return true; }
      virtual  void endVisit(VariableDeclaratorId *n) { unimplementedVisitor("endVisit(VariableDeclaratorId)"); }

     virtual   bool visit(FieldModifiers *n) { unimplementedVisitor("visit(FieldModifiers)"); return true; }
      virtual  void endVisit(FieldModifiers *n) { unimplementedVisitor("endVisit(FieldModifiers)"); }

     virtual   bool visit(MethodDeclaration *n) { unimplementedVisitor("visit(MethodDeclaration)"); return true; }
      virtual  void endVisit(MethodDeclaration *n) { unimplementedVisitor("endVisit(MethodDeclaration)"); }

     virtual   bool visit(MethodHeader *n) { unimplementedVisitor("visit(MethodHeader)"); return true; }
      virtual  void endVisit(MethodHeader *n) { unimplementedVisitor("endVisit(MethodHeader)"); }

     virtual   bool visit(ResultType *n) { unimplementedVisitor("visit(ResultType)"); return true; }
      virtual  void endVisit(ResultType *n) { unimplementedVisitor("endVisit(ResultType)"); }

     virtual   bool visit(FormalParameterList *n) { unimplementedVisitor("visit(FormalParameterList)"); return true; }
      virtual  void endVisit(FormalParameterList *n) { unimplementedVisitor("endVisit(FormalParameterList)"); }

     virtual   bool visit(FormalParameters *n) { unimplementedVisitor("visit(FormalParameters)"); return true; }
      virtual  void endVisit(FormalParameters *n) { unimplementedVisitor("endVisit(FormalParameters)"); }

     virtual   bool visit(FormalParameter *n) { unimplementedVisitor("visit(FormalParameter)"); return true; }
      virtual  void endVisit(FormalParameter *n) { unimplementedVisitor("endVisit(FormalParameter)"); }

     virtual   bool visit(VariableModifiers *n) { unimplementedVisitor("visit(VariableModifiers)"); return true; }
      virtual  void endVisit(VariableModifiers *n) { unimplementedVisitor("endVisit(VariableModifiers)"); }

     virtual   bool visit(VariableModifier *n) { unimplementedVisitor("visit(VariableModifier)"); return true; }
      virtual  void endVisit(VariableModifier *n) { unimplementedVisitor("endVisit(VariableModifier)"); }

     virtual   bool visit(LastFormalParameter *n) { unimplementedVisitor("visit(LastFormalParameter)"); return true; }
      virtual  void endVisit(LastFormalParameter *n) { unimplementedVisitor("endVisit(LastFormalParameter)"); }

     virtual   bool visit(MethodModifiers *n) { unimplementedVisitor("visit(MethodModifiers)"); return true; }
      virtual  void endVisit(MethodModifiers *n) { unimplementedVisitor("endVisit(MethodModifiers)"); }

     virtual   bool visit(Throws *n) { unimplementedVisitor("visit(Throws)"); return true; }
      virtual  void endVisit(Throws *n) { unimplementedVisitor("endVisit(Throws)"); }

     virtual   bool visit(ExceptionTypeList *n) { unimplementedVisitor("visit(ExceptionTypeList)"); return true; }
      virtual  void endVisit(ExceptionTypeList *n) { unimplementedVisitor("endVisit(ExceptionTypeList)"); }

     virtual   bool visit(MethodBody *n) { unimplementedVisitor("visit(MethodBody)"); return true; }
      virtual  void endVisit(MethodBody *n) { unimplementedVisitor("endVisit(MethodBody)"); }

     virtual   bool visit(StaticInitializer *n) { unimplementedVisitor("visit(StaticInitializer)"); return true; }
      virtual  void endVisit(StaticInitializer *n) { unimplementedVisitor("endVisit(StaticInitializer)"); }

     virtual   bool visit(ConstructorDeclaration *n) { unimplementedVisitor("visit(ConstructorDeclaration)"); return true; }
      virtual  void endVisit(ConstructorDeclaration *n) { unimplementedVisitor("endVisit(ConstructorDeclaration)"); }

     virtual   bool visit(ConstructorDeclarator *n) { unimplementedVisitor("visit(ConstructorDeclarator)"); return true; }
      virtual  void endVisit(ConstructorDeclarator *n) { unimplementedVisitor("endVisit(ConstructorDeclarator)"); }

     virtual   bool visit(ConstructorModifiers *n) { unimplementedVisitor("visit(ConstructorModifiers)"); return true; }
      virtual  void endVisit(ConstructorModifiers *n) { unimplementedVisitor("endVisit(ConstructorModifiers)"); }

     virtual   bool visit(ConstructorBody *n) { unimplementedVisitor("visit(ConstructorBody)"); return true; }
      virtual  void endVisit(ConstructorBody *n) { unimplementedVisitor("endVisit(ConstructorBody)"); }

     virtual   bool visit(EnumDeclaration *n) { unimplementedVisitor("visit(EnumDeclaration)"); return true; }
      virtual  void endVisit(EnumDeclaration *n) { unimplementedVisitor("endVisit(EnumDeclaration)"); }

     virtual   bool visit(EnumBody *n) { unimplementedVisitor("visit(EnumBody)"); return true; }
      virtual  void endVisit(EnumBody *n) { unimplementedVisitor("endVisit(EnumBody)"); }

     virtual   bool visit(EnumConstants *n) { unimplementedVisitor("visit(EnumConstants)"); return true; }
      virtual  void endVisit(EnumConstants *n) { unimplementedVisitor("endVisit(EnumConstants)"); }

     virtual   bool visit(EnumConstant *n) { unimplementedVisitor("visit(EnumConstant)"); return true; }
      virtual  void endVisit(EnumConstant *n) { unimplementedVisitor("endVisit(EnumConstant)"); }

     virtual   bool visit(Arguments *n) { unimplementedVisitor("visit(Arguments)"); return true; }
      virtual  void endVisit(Arguments *n) { unimplementedVisitor("endVisit(Arguments)"); }

     virtual   bool visit(EnumBodyDeclarations *n) { unimplementedVisitor("visit(EnumBodyDeclarations)"); return true; }
      virtual  void endVisit(EnumBodyDeclarations *n) { unimplementedVisitor("endVisit(EnumBodyDeclarations)"); }

     virtual   bool visit(NormalInterfaceDeclaration *n) { unimplementedVisitor("visit(NormalInterfaceDeclaration)"); return true; }
      virtual  void endVisit(NormalInterfaceDeclaration *n) { unimplementedVisitor("endVisit(NormalInterfaceDeclaration)"); }

     virtual   bool visit(InterfaceModifiers *n) { unimplementedVisitor("visit(InterfaceModifiers)"); return true; }
      virtual  void endVisit(InterfaceModifiers *n) { unimplementedVisitor("endVisit(InterfaceModifiers)"); }

     virtual   bool visit(InterfaceBody *n) { unimplementedVisitor("visit(InterfaceBody)"); return true; }
      virtual  void endVisit(InterfaceBody *n) { unimplementedVisitor("endVisit(InterfaceBody)"); }

     virtual   bool visit(InterfaceMemberDeclarations *n) { unimplementedVisitor("visit(InterfaceMemberDeclarations)"); return true; }
      virtual  void endVisit(InterfaceMemberDeclarations *n) { unimplementedVisitor("endVisit(InterfaceMemberDeclarations)"); }

     virtual   bool visit(InterfaceMemberDeclaration *n) { unimplementedVisitor("visit(InterfaceMemberDeclaration)"); return true; }
      virtual  void endVisit(InterfaceMemberDeclaration *n) { unimplementedVisitor("endVisit(InterfaceMemberDeclaration)"); }

     virtual   bool visit(ConstantDeclaration *n) { unimplementedVisitor("visit(ConstantDeclaration)"); return true; }
      virtual  void endVisit(ConstantDeclaration *n) { unimplementedVisitor("endVisit(ConstantDeclaration)"); }

     virtual   bool visit(ConstantModifiers *n) { unimplementedVisitor("visit(ConstantModifiers)"); return true; }
      virtual  void endVisit(ConstantModifiers *n) { unimplementedVisitor("endVisit(ConstantModifiers)"); }

     virtual   bool visit(AbstractMethodDeclaration *n) { unimplementedVisitor("visit(AbstractMethodDeclaration)"); return true; }
      virtual  void endVisit(AbstractMethodDeclaration *n) { unimplementedVisitor("endVisit(AbstractMethodDeclaration)"); }

     virtual   bool visit(AbstractMethodModifiers *n) { unimplementedVisitor("visit(AbstractMethodModifiers)"); return true; }
      virtual  void endVisit(AbstractMethodModifiers *n) { unimplementedVisitor("endVisit(AbstractMethodModifiers)"); }

     virtual   bool visit(AnnotationTypeDeclaration *n) { unimplementedVisitor("visit(AnnotationTypeDeclaration)"); return true; }
      virtual  void endVisit(AnnotationTypeDeclaration *n) { unimplementedVisitor("endVisit(AnnotationTypeDeclaration)"); }

     virtual   bool visit(AnnotationTypeBody *n) { unimplementedVisitor("visit(AnnotationTypeBody)"); return true; }
      virtual  void endVisit(AnnotationTypeBody *n) { unimplementedVisitor("endVisit(AnnotationTypeBody)"); }

     virtual   bool visit(AnnotationTypeElementDeclarations *n) { unimplementedVisitor("visit(AnnotationTypeElementDeclarations)"); return true; }
      virtual  void endVisit(AnnotationTypeElementDeclarations *n) { unimplementedVisitor("endVisit(AnnotationTypeElementDeclarations)"); }

     virtual   bool visit(DefaultValue *n) { unimplementedVisitor("visit(DefaultValue)"); return true; }
      virtual  void endVisit(DefaultValue *n) { unimplementedVisitor("endVisit(DefaultValue)"); }

     virtual   bool visit(Annotations *n) { unimplementedVisitor("visit(Annotations)"); return true; }
      virtual  void endVisit(Annotations *n) { unimplementedVisitor("endVisit(Annotations)"); }

     virtual   bool visit(NormalAnnotation *n) { unimplementedVisitor("visit(NormalAnnotation)"); return true; }
      virtual  void endVisit(NormalAnnotation *n) { unimplementedVisitor("endVisit(NormalAnnotation)"); }

     virtual   bool visit(ElementValuePairs *n) { unimplementedVisitor("visit(ElementValuePairs)"); return true; }
      virtual  void endVisit(ElementValuePairs *n) { unimplementedVisitor("endVisit(ElementValuePairs)"); }

     virtual   bool visit(ElementValuePair *n) { unimplementedVisitor("visit(ElementValuePair)"); return true; }
      virtual  void endVisit(ElementValuePair *n) { unimplementedVisitor("endVisit(ElementValuePair)"); }

     virtual   bool visit(ElementValueArrayInitializer *n) { unimplementedVisitor("visit(ElementValueArrayInitializer)"); return true; }
      virtual  void endVisit(ElementValueArrayInitializer *n) { unimplementedVisitor("endVisit(ElementValueArrayInitializer)"); }

     virtual   bool visit(ElementValues *n) { unimplementedVisitor("visit(ElementValues)"); return true; }
      virtual  void endVisit(ElementValues *n) { unimplementedVisitor("endVisit(ElementValues)"); }

     virtual   bool visit(MarkerAnnotation *n) { unimplementedVisitor("visit(MarkerAnnotation)"); return true; }
      virtual  void endVisit(MarkerAnnotation *n) { unimplementedVisitor("endVisit(MarkerAnnotation)"); }

     virtual   bool visit(SingleElementAnnotation *n) { unimplementedVisitor("visit(SingleElementAnnotation)"); return true; }
      virtual  void endVisit(SingleElementAnnotation *n) { unimplementedVisitor("endVisit(SingleElementAnnotation)"); }

     virtual   bool visit(ArrayInitializer *n) { unimplementedVisitor("visit(ArrayInitializer)"); return true; }
      virtual  void endVisit(ArrayInitializer *n) { unimplementedVisitor("endVisit(ArrayInitializer)"); }

     virtual   bool visit(VariableInitializers *n) { unimplementedVisitor("visit(VariableInitializers)"); return true; }
      virtual  void endVisit(VariableInitializers *n) { unimplementedVisitor("endVisit(VariableInitializers)"); }

     virtual   bool visit(Block *n) { unimplementedVisitor("visit(Block)"); return true; }
      virtual  void endVisit(Block *n) { unimplementedVisitor("endVisit(Block)"); }

     virtual   bool visit(BlockStatements *n) { unimplementedVisitor("visit(BlockStatements)"); return true; }
      virtual  void endVisit(BlockStatements *n) { unimplementedVisitor("endVisit(BlockStatements)"); }

     virtual   bool visit(LocalVariableDeclarationStatement *n) { unimplementedVisitor("visit(LocalVariableDeclarationStatement)"); return true; }
      virtual  void endVisit(LocalVariableDeclarationStatement *n) { unimplementedVisitor("endVisit(LocalVariableDeclarationStatement)"); }

     virtual   bool visit(LocalVariableDeclaration *n) { unimplementedVisitor("visit(LocalVariableDeclaration)"); return true; }
      virtual  void endVisit(LocalVariableDeclaration *n) { unimplementedVisitor("endVisit(LocalVariableDeclaration)"); }

     virtual   bool visit(IfThenStatement *n) { unimplementedVisitor("visit(IfThenStatement)"); return true; }
      virtual  void endVisit(IfThenStatement *n) { unimplementedVisitor("endVisit(IfThenStatement)"); }

     virtual   bool visit(IfThenElseStatement *n) { unimplementedVisitor("visit(IfThenElseStatement)"); return true; }
      virtual  void endVisit(IfThenElseStatement *n) { unimplementedVisitor("endVisit(IfThenElseStatement)"); }

     virtual   bool visit(IfThenElseStatementNoShortIf *n) { unimplementedVisitor("visit(IfThenElseStatementNoShortIf)"); return true; }
      virtual  void endVisit(IfThenElseStatementNoShortIf *n) { unimplementedVisitor("endVisit(IfThenElseStatementNoShortIf)"); }

     virtual   bool visit(EmptyStatement *n) { unimplementedVisitor("visit(EmptyStatement)"); return true; }
      virtual  void endVisit(EmptyStatement *n) { unimplementedVisitor("endVisit(EmptyStatement)"); }

     virtual   bool visit(LabeledStatement *n) { unimplementedVisitor("visit(LabeledStatement)"); return true; }
      virtual  void endVisit(LabeledStatement *n) { unimplementedVisitor("endVisit(LabeledStatement)"); }

     virtual   bool visit(LabeledStatementNoShortIf *n) { unimplementedVisitor("visit(LabeledStatementNoShortIf)"); return true; }
      virtual  void endVisit(LabeledStatementNoShortIf *n) { unimplementedVisitor("endVisit(LabeledStatementNoShortIf)"); }

     virtual   bool visit(ExpressionStatement *n) { unimplementedVisitor("visit(ExpressionStatement)"); return true; }
      virtual  void endVisit(ExpressionStatement *n) { unimplementedVisitor("endVisit(ExpressionStatement)"); }

     virtual   bool visit(SwitchStatement *n) { unimplementedVisitor("visit(SwitchStatement)"); return true; }
      virtual  void endVisit(SwitchStatement *n) { unimplementedVisitor("endVisit(SwitchStatement)"); }

     virtual   bool visit(SwitchBlock *n) { unimplementedVisitor("visit(SwitchBlock)"); return true; }
      virtual  void endVisit(SwitchBlock *n) { unimplementedVisitor("endVisit(SwitchBlock)"); }

     virtual   bool visit(SwitchBlockStatementGroups *n) { unimplementedVisitor("visit(SwitchBlockStatementGroups)"); return true; }
      virtual  void endVisit(SwitchBlockStatementGroups *n) { unimplementedVisitor("endVisit(SwitchBlockStatementGroups)"); }

     virtual   bool visit(SwitchBlockStatementGroup *n) { unimplementedVisitor("visit(SwitchBlockStatementGroup)"); return true; }
      virtual  void endVisit(SwitchBlockStatementGroup *n) { unimplementedVisitor("endVisit(SwitchBlockStatementGroup)"); }

     virtual   bool visit(SwitchLabels *n) { unimplementedVisitor("visit(SwitchLabels)"); return true; }
      virtual  void endVisit(SwitchLabels *n) { unimplementedVisitor("endVisit(SwitchLabels)"); }

     virtual   bool visit(WhileStatement *n) { unimplementedVisitor("visit(WhileStatement)"); return true; }
      virtual  void endVisit(WhileStatement *n) { unimplementedVisitor("endVisit(WhileStatement)"); }

     virtual   bool visit(WhileStatementNoShortIf *n) { unimplementedVisitor("visit(WhileStatementNoShortIf)"); return true; }
      virtual  void endVisit(WhileStatementNoShortIf *n) { unimplementedVisitor("endVisit(WhileStatementNoShortIf)"); }

     virtual   bool visit(DoStatement *n) { unimplementedVisitor("visit(DoStatement)"); return true; }
      virtual  void endVisit(DoStatement *n) { unimplementedVisitor("endVisit(DoStatement)"); }

     virtual   bool visit(BasicForStatement *n) { unimplementedVisitor("visit(BasicForStatement)"); return true; }
      virtual  void endVisit(BasicForStatement *n) { unimplementedVisitor("endVisit(BasicForStatement)"); }

     virtual   bool visit(ForStatementNoShortIf *n) { unimplementedVisitor("visit(ForStatementNoShortIf)"); return true; }
      virtual  void endVisit(ForStatementNoShortIf *n) { unimplementedVisitor("endVisit(ForStatementNoShortIf)"); }

     virtual   bool visit(StatementExpressionList *n) { unimplementedVisitor("visit(StatementExpressionList)"); return true; }
      virtual  void endVisit(StatementExpressionList *n) { unimplementedVisitor("endVisit(StatementExpressionList)"); }

     virtual   bool visit(EnhancedForStatement *n) { unimplementedVisitor("visit(EnhancedForStatement)"); return true; }
      virtual  void endVisit(EnhancedForStatement *n) { unimplementedVisitor("endVisit(EnhancedForStatement)"); }

     virtual   bool visit(BreakStatement *n) { unimplementedVisitor("visit(BreakStatement)"); return true; }
      virtual  void endVisit(BreakStatement *n) { unimplementedVisitor("endVisit(BreakStatement)"); }

     virtual   bool visit(ContinueStatement *n) { unimplementedVisitor("visit(ContinueStatement)"); return true; }
      virtual  void endVisit(ContinueStatement *n) { unimplementedVisitor("endVisit(ContinueStatement)"); }

     virtual   bool visit(ReturnStatement *n) { unimplementedVisitor("visit(ReturnStatement)"); return true; }
      virtual  void endVisit(ReturnStatement *n) { unimplementedVisitor("endVisit(ReturnStatement)"); }

     virtual   bool visit(ThrowStatement *n) { unimplementedVisitor("visit(ThrowStatement)"); return true; }
      virtual  void endVisit(ThrowStatement *n) { unimplementedVisitor("endVisit(ThrowStatement)"); }

     virtual   bool visit(SynchronizedStatement *n) { unimplementedVisitor("visit(SynchronizedStatement)"); return true; }
      virtual  void endVisit(SynchronizedStatement *n) { unimplementedVisitor("endVisit(SynchronizedStatement)"); }

     virtual   bool visit(Catches *n) { unimplementedVisitor("visit(Catches)"); return true; }
      virtual  void endVisit(Catches *n) { unimplementedVisitor("endVisit(Catches)"); }

     virtual   bool visit(CatchClause *n) { unimplementedVisitor("visit(CatchClause)"); return true; }
      virtual  void endVisit(CatchClause *n) { unimplementedVisitor("endVisit(CatchClause)"); }

     virtual   bool visit(Finally *n) { unimplementedVisitor("visit(Finally)"); return true; }
      virtual  void endVisit(Finally *n) { unimplementedVisitor("endVisit(Finally)"); }

     virtual   bool visit(ArgumentList *n) { unimplementedVisitor("visit(ArgumentList)"); return true; }
      virtual  void endVisit(ArgumentList *n) { unimplementedVisitor("endVisit(ArgumentList)"); }

     virtual   bool visit(DimExprs *n) { unimplementedVisitor("visit(DimExprs)"); return true; }
      virtual  void endVisit(DimExprs *n) { unimplementedVisitor("endVisit(DimExprs)"); }

     virtual   bool visit(DimExpr *n) { unimplementedVisitor("visit(DimExpr)"); return true; }
      virtual  void endVisit(DimExpr *n) { unimplementedVisitor("endVisit(DimExpr)"); }

     virtual   bool visit(PostIncrementExpression *n) { unimplementedVisitor("visit(PostIncrementExpression)"); return true; }
      virtual  void endVisit(PostIncrementExpression *n) { unimplementedVisitor("endVisit(PostIncrementExpression)"); }

     virtual   bool visit(PostDecrementExpression *n) { unimplementedVisitor("visit(PostDecrementExpression)"); return true; }
      virtual  void endVisit(PostDecrementExpression *n) { unimplementedVisitor("endVisit(PostDecrementExpression)"); }

     virtual   bool visit(PreIncrementExpression *n) { unimplementedVisitor("visit(PreIncrementExpression)"); return true; }
      virtual  void endVisit(PreIncrementExpression *n) { unimplementedVisitor("endVisit(PreIncrementExpression)"); }

     virtual   bool visit(PreDecrementExpression *n) { unimplementedVisitor("visit(PreDecrementExpression)"); return true; }
      virtual  void endVisit(PreDecrementExpression *n) { unimplementedVisitor("endVisit(PreDecrementExpression)"); }

     virtual   bool visit(AndExpression *n) { unimplementedVisitor("visit(AndExpression)"); return true; }
      virtual  void endVisit(AndExpression *n) { unimplementedVisitor("endVisit(AndExpression)"); }

     virtual   bool visit(ExclusiveOrExpression *n) { unimplementedVisitor("visit(ExclusiveOrExpression)"); return true; }
      virtual  void endVisit(ExclusiveOrExpression *n) { unimplementedVisitor("endVisit(ExclusiveOrExpression)"); }

     virtual   bool visit(InclusiveOrExpression *n) { unimplementedVisitor("visit(InclusiveOrExpression)"); return true; }
      virtual  void endVisit(InclusiveOrExpression *n) { unimplementedVisitor("endVisit(InclusiveOrExpression)"); }

     virtual   bool visit(ConditionalAndExpression *n) { unimplementedVisitor("visit(ConditionalAndExpression)"); return true; }
      virtual  void endVisit(ConditionalAndExpression *n) { unimplementedVisitor("endVisit(ConditionalAndExpression)"); }

     virtual   bool visit(ConditionalOrExpression *n) { unimplementedVisitor("visit(ConditionalOrExpression)"); return true; }
      virtual  void endVisit(ConditionalOrExpression *n) { unimplementedVisitor("endVisit(ConditionalOrExpression)"); }

     virtual   bool visit(ConditionalExpression *n) { unimplementedVisitor("visit(ConditionalExpression)"); return true; }
      virtual  void endVisit(ConditionalExpression *n) { unimplementedVisitor("endVisit(ConditionalExpression)"); }

     virtual   bool visit(Assignment *n) { unimplementedVisitor("visit(Assignment)"); return true; }
      virtual  void endVisit(Assignment *n) { unimplementedVisitor("endVisit(Assignment)"); }

     virtual   bool visit(Commaopt *n) { unimplementedVisitor("visit(Commaopt)"); return true; }
      virtual  void endVisit(Commaopt *n) { unimplementedVisitor("endVisit(Commaopt)"); }

     virtual   bool visit(Ellipsisopt *n) { unimplementedVisitor("visit(Ellipsisopt)"); return true; }
      virtual  void endVisit(Ellipsisopt *n) { unimplementedVisitor("endVisit(Ellipsisopt)"); }

     virtual   bool visit(LPGUserAction0 *n) { unimplementedVisitor("visit(LPGUserAction0)"); return true; }
      virtual  void endVisit(LPGUserAction0 *n) { unimplementedVisitor("endVisit(LPGUserAction0)"); }

     virtual   bool visit(LPGUserAction1 *n) { unimplementedVisitor("visit(LPGUserAction1)"); return true; }
      virtual  void endVisit(LPGUserAction1 *n) { unimplementedVisitor("endVisit(LPGUserAction1)"); }

     virtual   bool visit(LPGUserAction2 *n) { unimplementedVisitor("visit(LPGUserAction2)"); return true; }
      virtual  void endVisit(LPGUserAction2 *n) { unimplementedVisitor("endVisit(LPGUserAction2)"); }

     virtual   bool visit(LPGUserAction3 *n) { unimplementedVisitor("visit(LPGUserAction3)"); return true; }
      virtual  void endVisit(LPGUserAction3 *n) { unimplementedVisitor("endVisit(LPGUserAction3)"); }

     virtual   bool visit(LPGUserAction4 *n) { unimplementedVisitor("visit(LPGUserAction4)"); return true; }
      virtual  void endVisit(LPGUserAction4 *n) { unimplementedVisitor("endVisit(LPGUserAction4)"); }

     virtual   bool visit(IntegralType0 *n) { unimplementedVisitor("visit(IntegralType0)"); return true; }
      virtual  void endVisit(IntegralType0 *n) { unimplementedVisitor("endVisit(IntegralType0)"); }

     virtual   bool visit(IntegralType1 *n) { unimplementedVisitor("visit(IntegralType1)"); return true; }
      virtual  void endVisit(IntegralType1 *n) { unimplementedVisitor("endVisit(IntegralType1)"); }

     virtual   bool visit(IntegralType2 *n) { unimplementedVisitor("visit(IntegralType2)"); return true; }
      virtual  void endVisit(IntegralType2 *n) { unimplementedVisitor("endVisit(IntegralType2)"); }

     virtual   bool visit(IntegralType3 *n) { unimplementedVisitor("visit(IntegralType3)"); return true; }
      virtual  void endVisit(IntegralType3 *n) { unimplementedVisitor("endVisit(IntegralType3)"); }

     virtual   bool visit(IntegralType4 *n) { unimplementedVisitor("visit(IntegralType4)"); return true; }
      virtual  void endVisit(IntegralType4 *n) { unimplementedVisitor("endVisit(IntegralType4)"); }

     virtual   bool visit(FloatingPointType0 *n) { unimplementedVisitor("visit(FloatingPointType0)"); return true; }
      virtual  void endVisit(FloatingPointType0 *n) { unimplementedVisitor("endVisit(FloatingPointType0)"); }

     virtual   bool visit(FloatingPointType1 *n) { unimplementedVisitor("visit(FloatingPointType1)"); return true; }
      virtual  void endVisit(FloatingPointType1 *n) { unimplementedVisitor("endVisit(FloatingPointType1)"); }

     virtual   bool visit(WildcardBounds0 *n) { unimplementedVisitor("visit(WildcardBounds0)"); return true; }
      virtual  void endVisit(WildcardBounds0 *n) { unimplementedVisitor("endVisit(WildcardBounds0)"); }

     virtual   bool visit(WildcardBounds1 *n) { unimplementedVisitor("visit(WildcardBounds1)"); return true; }
      virtual  void endVisit(WildcardBounds1 *n) { unimplementedVisitor("endVisit(WildcardBounds1)"); }

     virtual   bool visit(ClassModifier0 *n) { unimplementedVisitor("visit(ClassModifier0)"); return true; }
      virtual  void endVisit(ClassModifier0 *n) { unimplementedVisitor("endVisit(ClassModifier0)"); }

     virtual   bool visit(ClassModifier1 *n) { unimplementedVisitor("visit(ClassModifier1)"); return true; }
      virtual  void endVisit(ClassModifier1 *n) { unimplementedVisitor("endVisit(ClassModifier1)"); }

     virtual   bool visit(ClassModifier2 *n) { unimplementedVisitor("visit(ClassModifier2)"); return true; }
      virtual  void endVisit(ClassModifier2 *n) { unimplementedVisitor("endVisit(ClassModifier2)"); }

     virtual   bool visit(ClassModifier3 *n) { unimplementedVisitor("visit(ClassModifier3)"); return true; }
      virtual  void endVisit(ClassModifier3 *n) { unimplementedVisitor("endVisit(ClassModifier3)"); }

     virtual   bool visit(ClassModifier4 *n) { unimplementedVisitor("visit(ClassModifier4)"); return true; }
      virtual  void endVisit(ClassModifier4 *n) { unimplementedVisitor("endVisit(ClassModifier4)"); }

     virtual   bool visit(ClassModifier5 *n) { unimplementedVisitor("visit(ClassModifier5)"); return true; }
      virtual  void endVisit(ClassModifier5 *n) { unimplementedVisitor("endVisit(ClassModifier5)"); }

     virtual   bool visit(ClassModifier6 *n) { unimplementedVisitor("visit(ClassModifier6)"); return true; }
      virtual  void endVisit(ClassModifier6 *n) { unimplementedVisitor("endVisit(ClassModifier6)"); }

     virtual   bool visit(FieldModifier0 *n) { unimplementedVisitor("visit(FieldModifier0)"); return true; }
      virtual  void endVisit(FieldModifier0 *n) { unimplementedVisitor("endVisit(FieldModifier0)"); }

     virtual   bool visit(FieldModifier1 *n) { unimplementedVisitor("visit(FieldModifier1)"); return true; }
      virtual  void endVisit(FieldModifier1 *n) { unimplementedVisitor("endVisit(FieldModifier1)"); }

     virtual   bool visit(FieldModifier2 *n) { unimplementedVisitor("visit(FieldModifier2)"); return true; }
      virtual  void endVisit(FieldModifier2 *n) { unimplementedVisitor("endVisit(FieldModifier2)"); }

     virtual   bool visit(FieldModifier3 *n) { unimplementedVisitor("visit(FieldModifier3)"); return true; }
      virtual  void endVisit(FieldModifier3 *n) { unimplementedVisitor("endVisit(FieldModifier3)"); }

     virtual   bool visit(FieldModifier4 *n) { unimplementedVisitor("visit(FieldModifier4)"); return true; }
      virtual  void endVisit(FieldModifier4 *n) { unimplementedVisitor("endVisit(FieldModifier4)"); }

     virtual   bool visit(FieldModifier5 *n) { unimplementedVisitor("visit(FieldModifier5)"); return true; }
      virtual  void endVisit(FieldModifier5 *n) { unimplementedVisitor("endVisit(FieldModifier5)"); }

     virtual   bool visit(FieldModifier6 *n) { unimplementedVisitor("visit(FieldModifier6)"); return true; }
      virtual  void endVisit(FieldModifier6 *n) { unimplementedVisitor("endVisit(FieldModifier6)"); }

     virtual   bool visit(MethodDeclarator0 *n) { unimplementedVisitor("visit(MethodDeclarator0)"); return true; }
      virtual  void endVisit(MethodDeclarator0 *n) { unimplementedVisitor("endVisit(MethodDeclarator0)"); }

     virtual   bool visit(MethodDeclarator1 *n) { unimplementedVisitor("visit(MethodDeclarator1)"); return true; }
      virtual  void endVisit(MethodDeclarator1 *n) { unimplementedVisitor("endVisit(MethodDeclarator1)"); }

     virtual   bool visit(MethodModifier0 *n) { unimplementedVisitor("visit(MethodModifier0)"); return true; }
      virtual  void endVisit(MethodModifier0 *n) { unimplementedVisitor("endVisit(MethodModifier0)"); }

     virtual   bool visit(MethodModifier1 *n) { unimplementedVisitor("visit(MethodModifier1)"); return true; }
      virtual  void endVisit(MethodModifier1 *n) { unimplementedVisitor("endVisit(MethodModifier1)"); }

     virtual   bool visit(MethodModifier2 *n) { unimplementedVisitor("visit(MethodModifier2)"); return true; }
      virtual  void endVisit(MethodModifier2 *n) { unimplementedVisitor("endVisit(MethodModifier2)"); }

     virtual   bool visit(MethodModifier3 *n) { unimplementedVisitor("visit(MethodModifier3)"); return true; }
      virtual  void endVisit(MethodModifier3 *n) { unimplementedVisitor("endVisit(MethodModifier3)"); }

     virtual   bool visit(MethodModifier4 *n) { unimplementedVisitor("visit(MethodModifier4)"); return true; }
      virtual  void endVisit(MethodModifier4 *n) { unimplementedVisitor("endVisit(MethodModifier4)"); }

     virtual   bool visit(MethodModifier5 *n) { unimplementedVisitor("visit(MethodModifier5)"); return true; }
      virtual  void endVisit(MethodModifier5 *n) { unimplementedVisitor("endVisit(MethodModifier5)"); }

     virtual   bool visit(MethodModifier6 *n) { unimplementedVisitor("visit(MethodModifier6)"); return true; }
      virtual  void endVisit(MethodModifier6 *n) { unimplementedVisitor("endVisit(MethodModifier6)"); }

     virtual   bool visit(MethodModifier7 *n) { unimplementedVisitor("visit(MethodModifier7)"); return true; }
      virtual  void endVisit(MethodModifier7 *n) { unimplementedVisitor("endVisit(MethodModifier7)"); }

     virtual   bool visit(MethodModifier8 *n) { unimplementedVisitor("visit(MethodModifier8)"); return true; }
      virtual  void endVisit(MethodModifier8 *n) { unimplementedVisitor("endVisit(MethodModifier8)"); }

     virtual   bool visit(ConstructorModifier0 *n) { unimplementedVisitor("visit(ConstructorModifier0)"); return true; }
      virtual  void endVisit(ConstructorModifier0 *n) { unimplementedVisitor("endVisit(ConstructorModifier0)"); }

     virtual   bool visit(ConstructorModifier1 *n) { unimplementedVisitor("visit(ConstructorModifier1)"); return true; }
      virtual  void endVisit(ConstructorModifier1 *n) { unimplementedVisitor("endVisit(ConstructorModifier1)"); }

     virtual   bool visit(ConstructorModifier2 *n) { unimplementedVisitor("visit(ConstructorModifier2)"); return true; }
      virtual  void endVisit(ConstructorModifier2 *n) { unimplementedVisitor("endVisit(ConstructorModifier2)"); }

     virtual   bool visit(ExplicitConstructorInvocation0 *n) { unimplementedVisitor("visit(ExplicitConstructorInvocation0)"); return true; }
      virtual  void endVisit(ExplicitConstructorInvocation0 *n) { unimplementedVisitor("endVisit(ExplicitConstructorInvocation0)"); }

     virtual   bool visit(ExplicitConstructorInvocation1 *n) { unimplementedVisitor("visit(ExplicitConstructorInvocation1)"); return true; }
      virtual  void endVisit(ExplicitConstructorInvocation1 *n) { unimplementedVisitor("endVisit(ExplicitConstructorInvocation1)"); }

     virtual   bool visit(ExplicitConstructorInvocation2 *n) { unimplementedVisitor("visit(ExplicitConstructorInvocation2)"); return true; }
      virtual  void endVisit(ExplicitConstructorInvocation2 *n) { unimplementedVisitor("endVisit(ExplicitConstructorInvocation2)"); }

     virtual   bool visit(InterfaceModifier0 *n) { unimplementedVisitor("visit(InterfaceModifier0)"); return true; }
      virtual  void endVisit(InterfaceModifier0 *n) { unimplementedVisitor("endVisit(InterfaceModifier0)"); }

     virtual   bool visit(InterfaceModifier1 *n) { unimplementedVisitor("visit(InterfaceModifier1)"); return true; }
      virtual  void endVisit(InterfaceModifier1 *n) { unimplementedVisitor("endVisit(InterfaceModifier1)"); }

     virtual   bool visit(InterfaceModifier2 *n) { unimplementedVisitor("visit(InterfaceModifier2)"); return true; }
      virtual  void endVisit(InterfaceModifier2 *n) { unimplementedVisitor("endVisit(InterfaceModifier2)"); }

     virtual   bool visit(InterfaceModifier3 *n) { unimplementedVisitor("visit(InterfaceModifier3)"); return true; }
      virtual  void endVisit(InterfaceModifier3 *n) { unimplementedVisitor("endVisit(InterfaceModifier3)"); }

     virtual   bool visit(InterfaceModifier4 *n) { unimplementedVisitor("visit(InterfaceModifier4)"); return true; }
      virtual  void endVisit(InterfaceModifier4 *n) { unimplementedVisitor("endVisit(InterfaceModifier4)"); }

     virtual   bool visit(InterfaceModifier5 *n) { unimplementedVisitor("visit(InterfaceModifier5)"); return true; }
      virtual  void endVisit(InterfaceModifier5 *n) { unimplementedVisitor("endVisit(InterfaceModifier5)"); }

     virtual   bool visit(ExtendsInterfaces0 *n) { unimplementedVisitor("visit(ExtendsInterfaces0)"); return true; }
      virtual  void endVisit(ExtendsInterfaces0 *n) { unimplementedVisitor("endVisit(ExtendsInterfaces0)"); }

     virtual   bool visit(ExtendsInterfaces1 *n) { unimplementedVisitor("visit(ExtendsInterfaces1)"); return true; }
      virtual  void endVisit(ExtendsInterfaces1 *n) { unimplementedVisitor("endVisit(ExtendsInterfaces1)"); }

     virtual   bool visit(ConstantModifier0 *n) { unimplementedVisitor("visit(ConstantModifier0)"); return true; }
      virtual  void endVisit(ConstantModifier0 *n) { unimplementedVisitor("endVisit(ConstantModifier0)"); }

     virtual   bool visit(ConstantModifier1 *n) { unimplementedVisitor("visit(ConstantModifier1)"); return true; }
      virtual  void endVisit(ConstantModifier1 *n) { unimplementedVisitor("endVisit(ConstantModifier1)"); }

     virtual   bool visit(ConstantModifier2 *n) { unimplementedVisitor("visit(ConstantModifier2)"); return true; }
      virtual  void endVisit(ConstantModifier2 *n) { unimplementedVisitor("endVisit(ConstantModifier2)"); }

     virtual   bool visit(AbstractMethodModifier0 *n) { unimplementedVisitor("visit(AbstractMethodModifier0)"); return true; }
      virtual  void endVisit(AbstractMethodModifier0 *n) { unimplementedVisitor("endVisit(AbstractMethodModifier0)"); }

     virtual   bool visit(AbstractMethodModifier1 *n) { unimplementedVisitor("visit(AbstractMethodModifier1)"); return true; }
      virtual  void endVisit(AbstractMethodModifier1 *n) { unimplementedVisitor("endVisit(AbstractMethodModifier1)"); }

     virtual   bool visit(AnnotationTypeElementDeclaration0 *n) { unimplementedVisitor("visit(AnnotationTypeElementDeclaration0)"); return true; }
      virtual  void endVisit(AnnotationTypeElementDeclaration0 *n) { unimplementedVisitor("endVisit(AnnotationTypeElementDeclaration0)"); }

     virtual   bool visit(AnnotationTypeElementDeclaration1 *n) { unimplementedVisitor("visit(AnnotationTypeElementDeclaration1)"); return true; }
      virtual  void endVisit(AnnotationTypeElementDeclaration1 *n) { unimplementedVisitor("endVisit(AnnotationTypeElementDeclaration1)"); }

     virtual   bool visit(AssertStatement0 *n) { unimplementedVisitor("visit(AssertStatement0)"); return true; }
      virtual  void endVisit(AssertStatement0 *n) { unimplementedVisitor("endVisit(AssertStatement0)"); }

     virtual   bool visit(AssertStatement1 *n) { unimplementedVisitor("visit(AssertStatement1)"); return true; }
      virtual  void endVisit(AssertStatement1 *n) { unimplementedVisitor("endVisit(AssertStatement1)"); }

     virtual   bool visit(SwitchLabel0 *n) { unimplementedVisitor("visit(SwitchLabel0)"); return true; }
      virtual  void endVisit(SwitchLabel0 *n) { unimplementedVisitor("endVisit(SwitchLabel0)"); }

     virtual   bool visit(SwitchLabel1 *n) { unimplementedVisitor("visit(SwitchLabel1)"); return true; }
      virtual  void endVisit(SwitchLabel1 *n) { unimplementedVisitor("endVisit(SwitchLabel1)"); }

     virtual   bool visit(SwitchLabel2 *n) { unimplementedVisitor("visit(SwitchLabel2)"); return true; }
      virtual  void endVisit(SwitchLabel2 *n) { unimplementedVisitor("endVisit(SwitchLabel2)"); }

     virtual   bool visit(TryStatement0 *n) { unimplementedVisitor("visit(TryStatement0)"); return true; }
      virtual  void endVisit(TryStatement0 *n) { unimplementedVisitor("endVisit(TryStatement0)"); }

     virtual   bool visit(TryStatement1 *n) { unimplementedVisitor("visit(TryStatement1)"); return true; }
      virtual  void endVisit(TryStatement1 *n) { unimplementedVisitor("endVisit(TryStatement1)"); }

     virtual   bool visit(PrimaryNoNewArray0 *n) { unimplementedVisitor("visit(PrimaryNoNewArray0)"); return true; }
      virtual  void endVisit(PrimaryNoNewArray0 *n) { unimplementedVisitor("endVisit(PrimaryNoNewArray0)"); }

     virtual   bool visit(PrimaryNoNewArray1 *n) { unimplementedVisitor("visit(PrimaryNoNewArray1)"); return true; }
      virtual  void endVisit(PrimaryNoNewArray1 *n) { unimplementedVisitor("endVisit(PrimaryNoNewArray1)"); }

     virtual   bool visit(PrimaryNoNewArray2 *n) { unimplementedVisitor("visit(PrimaryNoNewArray2)"); return true; }
      virtual  void endVisit(PrimaryNoNewArray2 *n) { unimplementedVisitor("endVisit(PrimaryNoNewArray2)"); }

     virtual   bool visit(PrimaryNoNewArray3 *n) { unimplementedVisitor("visit(PrimaryNoNewArray3)"); return true; }
      virtual  void endVisit(PrimaryNoNewArray3 *n) { unimplementedVisitor("endVisit(PrimaryNoNewArray3)"); }

     virtual   bool visit(PrimaryNoNewArray4 *n) { unimplementedVisitor("visit(PrimaryNoNewArray4)"); return true; }
      virtual  void endVisit(PrimaryNoNewArray4 *n) { unimplementedVisitor("endVisit(PrimaryNoNewArray4)"); }

     virtual   bool visit(Literal0 *n) { unimplementedVisitor("visit(Literal0)"); return true; }
      virtual  void endVisit(Literal0 *n) { unimplementedVisitor("endVisit(Literal0)"); }

     virtual   bool visit(Literal1 *n) { unimplementedVisitor("visit(Literal1)"); return true; }
      virtual  void endVisit(Literal1 *n) { unimplementedVisitor("endVisit(Literal1)"); }

     virtual   bool visit(Literal2 *n) { unimplementedVisitor("visit(Literal2)"); return true; }
      virtual  void endVisit(Literal2 *n) { unimplementedVisitor("endVisit(Literal2)"); }

     virtual   bool visit(Literal3 *n) { unimplementedVisitor("visit(Literal3)"); return true; }
      virtual  void endVisit(Literal3 *n) { unimplementedVisitor("endVisit(Literal3)"); }

     virtual   bool visit(Literal4 *n) { unimplementedVisitor("visit(Literal4)"); return true; }
      virtual  void endVisit(Literal4 *n) { unimplementedVisitor("endVisit(Literal4)"); }

     virtual   bool visit(Literal5 *n) { unimplementedVisitor("visit(Literal5)"); return true; }
      virtual  void endVisit(Literal5 *n) { unimplementedVisitor("endVisit(Literal5)"); }

     virtual   bool visit(Literal6 *n) { unimplementedVisitor("visit(Literal6)"); return true; }
      virtual  void endVisit(Literal6 *n) { unimplementedVisitor("endVisit(Literal6)"); }

     virtual   bool visit(BooleanLiteral0 *n) { unimplementedVisitor("visit(BooleanLiteral0)"); return true; }
      virtual  void endVisit(BooleanLiteral0 *n) { unimplementedVisitor("endVisit(BooleanLiteral0)"); }

     virtual   bool visit(BooleanLiteral1 *n) { unimplementedVisitor("visit(BooleanLiteral1)"); return true; }
      virtual  void endVisit(BooleanLiteral1 *n) { unimplementedVisitor("endVisit(BooleanLiteral1)"); }

     virtual   bool visit(ClassInstanceCreationExpression0 *n) { unimplementedVisitor("visit(ClassInstanceCreationExpression0)"); return true; }
      virtual  void endVisit(ClassInstanceCreationExpression0 *n) { unimplementedVisitor("endVisit(ClassInstanceCreationExpression0)"); }

     virtual   bool visit(ClassInstanceCreationExpression1 *n) { unimplementedVisitor("visit(ClassInstanceCreationExpression1)"); return true; }
      virtual  void endVisit(ClassInstanceCreationExpression1 *n) { unimplementedVisitor("endVisit(ClassInstanceCreationExpression1)"); }

     virtual   bool visit(ArrayCreationExpression0 *n) { unimplementedVisitor("visit(ArrayCreationExpression0)"); return true; }
      virtual  void endVisit(ArrayCreationExpression0 *n) { unimplementedVisitor("endVisit(ArrayCreationExpression0)"); }

     virtual   bool visit(ArrayCreationExpression1 *n) { unimplementedVisitor("visit(ArrayCreationExpression1)"); return true; }
      virtual  void endVisit(ArrayCreationExpression1 *n) { unimplementedVisitor("endVisit(ArrayCreationExpression1)"); }

     virtual   bool visit(ArrayCreationExpression2 *n) { unimplementedVisitor("visit(ArrayCreationExpression2)"); return true; }
      virtual  void endVisit(ArrayCreationExpression2 *n) { unimplementedVisitor("endVisit(ArrayCreationExpression2)"); }

     virtual   bool visit(ArrayCreationExpression3 *n) { unimplementedVisitor("visit(ArrayCreationExpression3)"); return true; }
      virtual  void endVisit(ArrayCreationExpression3 *n) { unimplementedVisitor("endVisit(ArrayCreationExpression3)"); }

     virtual   bool visit(Dims0 *n) { unimplementedVisitor("visit(Dims0)"); return true; }
      virtual  void endVisit(Dims0 *n) { unimplementedVisitor("endVisit(Dims0)"); }

     virtual   bool visit(Dims1 *n) { unimplementedVisitor("visit(Dims1)"); return true; }
      virtual  void endVisit(Dims1 *n) { unimplementedVisitor("endVisit(Dims1)"); }

     virtual   bool visit(FieldAccess0 *n) { unimplementedVisitor("visit(FieldAccess0)"); return true; }
      virtual  void endVisit(FieldAccess0 *n) { unimplementedVisitor("endVisit(FieldAccess0)"); }

     virtual   bool visit(FieldAccess1 *n) { unimplementedVisitor("visit(FieldAccess1)"); return true; }
      virtual  void endVisit(FieldAccess1 *n) { unimplementedVisitor("endVisit(FieldAccess1)"); }

     virtual   bool visit(FieldAccess2 *n) { unimplementedVisitor("visit(FieldAccess2)"); return true; }
      virtual  void endVisit(FieldAccess2 *n) { unimplementedVisitor("endVisit(FieldAccess2)"); }

     virtual   bool visit(MethodInvocation0 *n) { unimplementedVisitor("visit(MethodInvocation0)"); return true; }
      virtual  void endVisit(MethodInvocation0 *n) { unimplementedVisitor("endVisit(MethodInvocation0)"); }

     virtual   bool visit(MethodInvocation1 *n) { unimplementedVisitor("visit(MethodInvocation1)"); return true; }
      virtual  void endVisit(MethodInvocation1 *n) { unimplementedVisitor("endVisit(MethodInvocation1)"); }

     virtual   bool visit(MethodInvocation2 *n) { unimplementedVisitor("visit(MethodInvocation2)"); return true; }
      virtual  void endVisit(MethodInvocation2 *n) { unimplementedVisitor("endVisit(MethodInvocation2)"); }

     virtual   bool visit(MethodInvocation3 *n) { unimplementedVisitor("visit(MethodInvocation3)"); return true; }
      virtual  void endVisit(MethodInvocation3 *n) { unimplementedVisitor("endVisit(MethodInvocation3)"); }

     virtual   bool visit(MethodInvocation4 *n) { unimplementedVisitor("visit(MethodInvocation4)"); return true; }
      virtual  void endVisit(MethodInvocation4 *n) { unimplementedVisitor("endVisit(MethodInvocation4)"); }

     virtual   bool visit(ArrayAccess0 *n) { unimplementedVisitor("visit(ArrayAccess0)"); return true; }
      virtual  void endVisit(ArrayAccess0 *n) { unimplementedVisitor("endVisit(ArrayAccess0)"); }

     virtual   bool visit(ArrayAccess1 *n) { unimplementedVisitor("visit(ArrayAccess1)"); return true; }
      virtual  void endVisit(ArrayAccess1 *n) { unimplementedVisitor("endVisit(ArrayAccess1)"); }

     virtual   bool visit(UnaryExpression0 *n) { unimplementedVisitor("visit(UnaryExpression0)"); return true; }
      virtual  void endVisit(UnaryExpression0 *n) { unimplementedVisitor("endVisit(UnaryExpression0)"); }

     virtual   bool visit(UnaryExpression1 *n) { unimplementedVisitor("visit(UnaryExpression1)"); return true; }
      virtual  void endVisit(UnaryExpression1 *n) { unimplementedVisitor("endVisit(UnaryExpression1)"); }

     virtual   bool visit(UnaryExpressionNotPlusMinus0 *n) { unimplementedVisitor("visit(UnaryExpressionNotPlusMinus0)"); return true; }
      virtual  void endVisit(UnaryExpressionNotPlusMinus0 *n) { unimplementedVisitor("endVisit(UnaryExpressionNotPlusMinus0)"); }

     virtual   bool visit(UnaryExpressionNotPlusMinus1 *n) { unimplementedVisitor("visit(UnaryExpressionNotPlusMinus1)"); return true; }
      virtual  void endVisit(UnaryExpressionNotPlusMinus1 *n) { unimplementedVisitor("endVisit(UnaryExpressionNotPlusMinus1)"); }

     virtual   bool visit(CastExpression0 *n) { unimplementedVisitor("visit(CastExpression0)"); return true; }
      virtual  void endVisit(CastExpression0 *n) { unimplementedVisitor("endVisit(CastExpression0)"); }

     virtual   bool visit(CastExpression1 *n) { unimplementedVisitor("visit(CastExpression1)"); return true; }
      virtual  void endVisit(CastExpression1 *n) { unimplementedVisitor("endVisit(CastExpression1)"); }

     virtual   bool visit(MultiplicativeExpression0 *n) { unimplementedVisitor("visit(MultiplicativeExpression0)"); return true; }
      virtual  void endVisit(MultiplicativeExpression0 *n) { unimplementedVisitor("endVisit(MultiplicativeExpression0)"); }

     virtual   bool visit(MultiplicativeExpression1 *n) { unimplementedVisitor("visit(MultiplicativeExpression1)"); return true; }
      virtual  void endVisit(MultiplicativeExpression1 *n) { unimplementedVisitor("endVisit(MultiplicativeExpression1)"); }

     virtual   bool visit(MultiplicativeExpression2 *n) { unimplementedVisitor("visit(MultiplicativeExpression2)"); return true; }
      virtual  void endVisit(MultiplicativeExpression2 *n) { unimplementedVisitor("endVisit(MultiplicativeExpression2)"); }

     virtual   bool visit(AdditiveExpression0 *n) { unimplementedVisitor("visit(AdditiveExpression0)"); return true; }
      virtual  void endVisit(AdditiveExpression0 *n) { unimplementedVisitor("endVisit(AdditiveExpression0)"); }

     virtual   bool visit(AdditiveExpression1 *n) { unimplementedVisitor("visit(AdditiveExpression1)"); return true; }
      virtual  void endVisit(AdditiveExpression1 *n) { unimplementedVisitor("endVisit(AdditiveExpression1)"); }

     virtual   bool visit(ShiftExpression0 *n) { unimplementedVisitor("visit(ShiftExpression0)"); return true; }
      virtual  void endVisit(ShiftExpression0 *n) { unimplementedVisitor("endVisit(ShiftExpression0)"); }

     virtual   bool visit(ShiftExpression1 *n) { unimplementedVisitor("visit(ShiftExpression1)"); return true; }
      virtual  void endVisit(ShiftExpression1 *n) { unimplementedVisitor("endVisit(ShiftExpression1)"); }

     virtual   bool visit(ShiftExpression2 *n) { unimplementedVisitor("visit(ShiftExpression2)"); return true; }
      virtual  void endVisit(ShiftExpression2 *n) { unimplementedVisitor("endVisit(ShiftExpression2)"); }

     virtual   bool visit(RelationalExpression0 *n) { unimplementedVisitor("visit(RelationalExpression0)"); return true; }
      virtual  void endVisit(RelationalExpression0 *n) { unimplementedVisitor("endVisit(RelationalExpression0)"); }

     virtual   bool visit(RelationalExpression1 *n) { unimplementedVisitor("visit(RelationalExpression1)"); return true; }
      virtual  void endVisit(RelationalExpression1 *n) { unimplementedVisitor("endVisit(RelationalExpression1)"); }

     virtual   bool visit(RelationalExpression2 *n) { unimplementedVisitor("visit(RelationalExpression2)"); return true; }
      virtual  void endVisit(RelationalExpression2 *n) { unimplementedVisitor("endVisit(RelationalExpression2)"); }

     virtual   bool visit(RelationalExpression3 *n) { unimplementedVisitor("visit(RelationalExpression3)"); return true; }
      virtual  void endVisit(RelationalExpression3 *n) { unimplementedVisitor("endVisit(RelationalExpression3)"); }

     virtual   bool visit(RelationalExpression4 *n) { unimplementedVisitor("visit(RelationalExpression4)"); return true; }
      virtual  void endVisit(RelationalExpression4 *n) { unimplementedVisitor("endVisit(RelationalExpression4)"); }

     virtual   bool visit(EqualityExpression0 *n) { unimplementedVisitor("visit(EqualityExpression0)"); return true; }
      virtual  void endVisit(EqualityExpression0 *n) { unimplementedVisitor("endVisit(EqualityExpression0)"); }

     virtual   bool visit(EqualityExpression1 *n) { unimplementedVisitor("visit(EqualityExpression1)"); return true; }
      virtual  void endVisit(EqualityExpression1 *n) { unimplementedVisitor("endVisit(EqualityExpression1)"); }

     virtual   bool visit(AssignmentOperator0 *n) { unimplementedVisitor("visit(AssignmentOperator0)"); return true; }
      virtual  void endVisit(AssignmentOperator0 *n) { unimplementedVisitor("endVisit(AssignmentOperator0)"); }

     virtual   bool visit(AssignmentOperator1 *n) { unimplementedVisitor("visit(AssignmentOperator1)"); return true; }
      virtual  void endVisit(AssignmentOperator1 *n) { unimplementedVisitor("endVisit(AssignmentOperator1)"); }

     virtual   bool visit(AssignmentOperator2 *n) { unimplementedVisitor("visit(AssignmentOperator2)"); return true; }
      virtual  void endVisit(AssignmentOperator2 *n) { unimplementedVisitor("endVisit(AssignmentOperator2)"); }

     virtual   bool visit(AssignmentOperator3 *n) { unimplementedVisitor("visit(AssignmentOperator3)"); return true; }
      virtual  void endVisit(AssignmentOperator3 *n) { unimplementedVisitor("endVisit(AssignmentOperator3)"); }

     virtual   bool visit(AssignmentOperator4 *n) { unimplementedVisitor("visit(AssignmentOperator4)"); return true; }
      virtual  void endVisit(AssignmentOperator4 *n) { unimplementedVisitor("endVisit(AssignmentOperator4)"); }

     virtual   bool visit(AssignmentOperator5 *n) { unimplementedVisitor("visit(AssignmentOperator5)"); return true; }
      virtual  void endVisit(AssignmentOperator5 *n) { unimplementedVisitor("endVisit(AssignmentOperator5)"); }

     virtual   bool visit(AssignmentOperator6 *n) { unimplementedVisitor("visit(AssignmentOperator6)"); return true; }
      virtual  void endVisit(AssignmentOperator6 *n) { unimplementedVisitor("endVisit(AssignmentOperator6)"); }

     virtual   bool visit(AssignmentOperator7 *n) { unimplementedVisitor("visit(AssignmentOperator7)"); return true; }
      virtual  void endVisit(AssignmentOperator7 *n) { unimplementedVisitor("endVisit(AssignmentOperator7)"); }

     virtual   bool visit(AssignmentOperator8 *n) { unimplementedVisitor("visit(AssignmentOperator8)"); return true; }
      virtual  void endVisit(AssignmentOperator8 *n) { unimplementedVisitor("endVisit(AssignmentOperator8)"); }

     virtual   bool visit(AssignmentOperator9 *n) { unimplementedVisitor("visit(AssignmentOperator9)"); return true; }
      virtual  void endVisit(AssignmentOperator9 *n) { unimplementedVisitor("endVisit(AssignmentOperator9)"); }

     virtual   bool visit(AssignmentOperator10 *n) { unimplementedVisitor("visit(AssignmentOperator10)"); return true; }
      virtual  void endVisit(AssignmentOperator10 *n) { unimplementedVisitor("endVisit(AssignmentOperator10)"); }

     virtual   bool visit(AssignmentOperator11 *n) { unimplementedVisitor("visit(AssignmentOperator11)"); return true; }
      virtual  void endVisit(AssignmentOperator11 *n) { unimplementedVisitor("endVisit(AssignmentOperator11)"); }

      virtual   bool visit(Ast* n)
      {
          if (dynamic_cast<AstToken*>(n)) return visit((AstToken*)n);
          if (dynamic_cast<identifier*>(n)) return visit((identifier*)n);
          if (dynamic_cast<PrimitiveType*>(n)) return visit((PrimitiveType*)n);
          if (dynamic_cast<ClassType*>(n)) return visit((ClassType*)n);
          if (dynamic_cast<InterfaceType*>(n)) return visit((InterfaceType*)n);
          if (dynamic_cast<TypeName*>(n)) return visit((TypeName*)n);
          if (dynamic_cast<ArrayType*>(n)) return visit((ArrayType*)n);
          if (dynamic_cast<TypeParameter*>(n)) return visit((TypeParameter*)n);
          if (dynamic_cast<TypeBound*>(n)) return visit((TypeBound*)n);
          if (dynamic_cast<AdditionalBoundList*>(n)) return visit((AdditionalBoundList*)n);
          if (dynamic_cast<AdditionalBound*>(n)) return visit((AdditionalBound*)n);
          if (dynamic_cast<TypeArguments*>(n)) return visit((TypeArguments*)n);
          if (dynamic_cast<ActualTypeArgumentList*>(n)) return visit((ActualTypeArgumentList*)n);
          if (dynamic_cast<Wildcard*>(n)) return visit((Wildcard*)n);
          if (dynamic_cast<PackageName*>(n)) return visit((PackageName*)n);
          if (dynamic_cast<ExpressionName*>(n)) return visit((ExpressionName*)n);
          if (dynamic_cast<MethodName*>(n)) return visit((MethodName*)n);
          if (dynamic_cast<PackageOrTypeName*>(n)) return visit((PackageOrTypeName*)n);
          if (dynamic_cast<AmbiguousName*>(n)) return visit((AmbiguousName*)n);
          if (dynamic_cast<CompilationUnit*>(n)) return visit((CompilationUnit*)n);
          if (dynamic_cast<ImportDeclarations*>(n)) return visit((ImportDeclarations*)n);
          if (dynamic_cast<TypeDeclarations*>(n)) return visit((TypeDeclarations*)n);
          if (dynamic_cast<PackageDeclaration*>(n)) return visit((PackageDeclaration*)n);
          if (dynamic_cast<SingleTypeImportDeclaration*>(n)) return visit((SingleTypeImportDeclaration*)n);
          if (dynamic_cast<TypeImportOnDemandDeclaration*>(n)) return visit((TypeImportOnDemandDeclaration*)n);
          if (dynamic_cast<SingleStaticImportDeclaration*>(n)) return visit((SingleStaticImportDeclaration*)n);
          if (dynamic_cast<StaticImportOnDemandDeclaration*>(n)) return visit((StaticImportOnDemandDeclaration*)n);
          if (dynamic_cast<TypeDeclaration*>(n)) return visit((TypeDeclaration*)n);
          if (dynamic_cast<NormalClassDeclaration*>(n)) return visit((NormalClassDeclaration*)n);
          if (dynamic_cast<ClassModifiers*>(n)) return visit((ClassModifiers*)n);
          if (dynamic_cast<TypeParameters*>(n)) return visit((TypeParameters*)n);
          if (dynamic_cast<TypeParameterList*>(n)) return visit((TypeParameterList*)n);
          if (dynamic_cast<Super*>(n)) return visit((Super*)n);
          if (dynamic_cast<Interfaces*>(n)) return visit((Interfaces*)n);
          if (dynamic_cast<InterfaceTypeList*>(n)) return visit((InterfaceTypeList*)n);
          if (dynamic_cast<ClassBody*>(n)) return visit((ClassBody*)n);
          if (dynamic_cast<ClassBodyDeclarations*>(n)) return visit((ClassBodyDeclarations*)n);
          if (dynamic_cast<ClassMemberDeclaration*>(n)) return visit((ClassMemberDeclaration*)n);
          if (dynamic_cast<FieldDeclaration*>(n)) return visit((FieldDeclaration*)n);
          if (dynamic_cast<VariableDeclarators*>(n)) return visit((VariableDeclarators*)n);
          if (dynamic_cast<VariableDeclarator*>(n)) return visit((VariableDeclarator*)n);
          if (dynamic_cast<VariableDeclaratorId*>(n)) return visit((VariableDeclaratorId*)n);
          if (dynamic_cast<FieldModifiers*>(n)) return visit((FieldModifiers*)n);
          if (dynamic_cast<MethodDeclaration*>(n)) return visit((MethodDeclaration*)n);
          if (dynamic_cast<MethodHeader*>(n)) return visit((MethodHeader*)n);
          if (dynamic_cast<ResultType*>(n)) return visit((ResultType*)n);
          if (dynamic_cast<FormalParameterList*>(n)) return visit((FormalParameterList*)n);
          if (dynamic_cast<FormalParameters*>(n)) return visit((FormalParameters*)n);
          if (dynamic_cast<FormalParameter*>(n)) return visit((FormalParameter*)n);
          if (dynamic_cast<VariableModifiers*>(n)) return visit((VariableModifiers*)n);
          if (dynamic_cast<VariableModifier*>(n)) return visit((VariableModifier*)n);
          if (dynamic_cast<LastFormalParameter*>(n)) return visit((LastFormalParameter*)n);
          if (dynamic_cast<MethodModifiers*>(n)) return visit((MethodModifiers*)n);
          if (dynamic_cast<Throws*>(n)) return visit((Throws*)n);
          if (dynamic_cast<ExceptionTypeList*>(n)) return visit((ExceptionTypeList*)n);
          if (dynamic_cast<MethodBody*>(n)) return visit((MethodBody*)n);
          if (dynamic_cast<StaticInitializer*>(n)) return visit((StaticInitializer*)n);
          if (dynamic_cast<ConstructorDeclaration*>(n)) return visit((ConstructorDeclaration*)n);
          if (dynamic_cast<ConstructorDeclarator*>(n)) return visit((ConstructorDeclarator*)n);
          if (dynamic_cast<ConstructorModifiers*>(n)) return visit((ConstructorModifiers*)n);
          if (dynamic_cast<ConstructorBody*>(n)) return visit((ConstructorBody*)n);
          if (dynamic_cast<EnumDeclaration*>(n)) return visit((EnumDeclaration*)n);
          if (dynamic_cast<EnumBody*>(n)) return visit((EnumBody*)n);
          if (dynamic_cast<EnumConstants*>(n)) return visit((EnumConstants*)n);
          if (dynamic_cast<EnumConstant*>(n)) return visit((EnumConstant*)n);
          if (dynamic_cast<Arguments*>(n)) return visit((Arguments*)n);
          if (dynamic_cast<EnumBodyDeclarations*>(n)) return visit((EnumBodyDeclarations*)n);
          if (dynamic_cast<NormalInterfaceDeclaration*>(n)) return visit((NormalInterfaceDeclaration*)n);
          if (dynamic_cast<InterfaceModifiers*>(n)) return visit((InterfaceModifiers*)n);
          if (dynamic_cast<InterfaceBody*>(n)) return visit((InterfaceBody*)n);
          if (dynamic_cast<InterfaceMemberDeclarations*>(n)) return visit((InterfaceMemberDeclarations*)n);
          if (dynamic_cast<InterfaceMemberDeclaration*>(n)) return visit((InterfaceMemberDeclaration*)n);
          if (dynamic_cast<ConstantDeclaration*>(n)) return visit((ConstantDeclaration*)n);
          if (dynamic_cast<ConstantModifiers*>(n)) return visit((ConstantModifiers*)n);
          if (dynamic_cast<AbstractMethodDeclaration*>(n)) return visit((AbstractMethodDeclaration*)n);
          if (dynamic_cast<AbstractMethodModifiers*>(n)) return visit((AbstractMethodModifiers*)n);
          if (dynamic_cast<AnnotationTypeDeclaration*>(n)) return visit((AnnotationTypeDeclaration*)n);
          if (dynamic_cast<AnnotationTypeBody*>(n)) return visit((AnnotationTypeBody*)n);
          if (dynamic_cast<AnnotationTypeElementDeclarations*>(n)) return visit((AnnotationTypeElementDeclarations*)n);
          if (dynamic_cast<DefaultValue*>(n)) return visit((DefaultValue*)n);
          if (dynamic_cast<Annotations*>(n)) return visit((Annotations*)n);
          if (dynamic_cast<NormalAnnotation*>(n)) return visit((NormalAnnotation*)n);
          if (dynamic_cast<ElementValuePairs*>(n)) return visit((ElementValuePairs*)n);
          if (dynamic_cast<ElementValuePair*>(n)) return visit((ElementValuePair*)n);
          if (dynamic_cast<ElementValueArrayInitializer*>(n)) return visit((ElementValueArrayInitializer*)n);
          if (dynamic_cast<ElementValues*>(n)) return visit((ElementValues*)n);
          if (dynamic_cast<MarkerAnnotation*>(n)) return visit((MarkerAnnotation*)n);
          if (dynamic_cast<SingleElementAnnotation*>(n)) return visit((SingleElementAnnotation*)n);
          if (dynamic_cast<ArrayInitializer*>(n)) return visit((ArrayInitializer*)n);
          if (dynamic_cast<VariableInitializers*>(n)) return visit((VariableInitializers*)n);
          if (dynamic_cast<Block*>(n)) return visit((Block*)n);
          if (dynamic_cast<BlockStatements*>(n)) return visit((BlockStatements*)n);
          if (dynamic_cast<LocalVariableDeclarationStatement*>(n)) return visit((LocalVariableDeclarationStatement*)n);
          if (dynamic_cast<LocalVariableDeclaration*>(n)) return visit((LocalVariableDeclaration*)n);
          if (dynamic_cast<IfThenStatement*>(n)) return visit((IfThenStatement*)n);
          if (dynamic_cast<IfThenElseStatement*>(n)) return visit((IfThenElseStatement*)n);
          if (dynamic_cast<IfThenElseStatementNoShortIf*>(n)) return visit((IfThenElseStatementNoShortIf*)n);
          if (dynamic_cast<EmptyStatement*>(n)) return visit((EmptyStatement*)n);
          if (dynamic_cast<LabeledStatement*>(n)) return visit((LabeledStatement*)n);
          if (dynamic_cast<LabeledStatementNoShortIf*>(n)) return visit((LabeledStatementNoShortIf*)n);
          if (dynamic_cast<ExpressionStatement*>(n)) return visit((ExpressionStatement*)n);
          if (dynamic_cast<SwitchStatement*>(n)) return visit((SwitchStatement*)n);
          if (dynamic_cast<SwitchBlock*>(n)) return visit((SwitchBlock*)n);
          if (dynamic_cast<SwitchBlockStatementGroups*>(n)) return visit((SwitchBlockStatementGroups*)n);
          if (dynamic_cast<SwitchBlockStatementGroup*>(n)) return visit((SwitchBlockStatementGroup*)n);
          if (dynamic_cast<SwitchLabels*>(n)) return visit((SwitchLabels*)n);
          if (dynamic_cast<WhileStatement*>(n)) return visit((WhileStatement*)n);
          if (dynamic_cast<WhileStatementNoShortIf*>(n)) return visit((WhileStatementNoShortIf*)n);
          if (dynamic_cast<DoStatement*>(n)) return visit((DoStatement*)n);
          if (dynamic_cast<BasicForStatement*>(n)) return visit((BasicForStatement*)n);
          if (dynamic_cast<ForStatementNoShortIf*>(n)) return visit((ForStatementNoShortIf*)n);
          if (dynamic_cast<StatementExpressionList*>(n)) return visit((StatementExpressionList*)n);
          if (dynamic_cast<EnhancedForStatement*>(n)) return visit((EnhancedForStatement*)n);
          if (dynamic_cast<BreakStatement*>(n)) return visit((BreakStatement*)n);
          if (dynamic_cast<ContinueStatement*>(n)) return visit((ContinueStatement*)n);
          if (dynamic_cast<ReturnStatement*>(n)) return visit((ReturnStatement*)n);
          if (dynamic_cast<ThrowStatement*>(n)) return visit((ThrowStatement*)n);
          if (dynamic_cast<SynchronizedStatement*>(n)) return visit((SynchronizedStatement*)n);
          if (dynamic_cast<Catches*>(n)) return visit((Catches*)n);
          if (dynamic_cast<CatchClause*>(n)) return visit((CatchClause*)n);
          if (dynamic_cast<Finally*>(n)) return visit((Finally*)n);
          if (dynamic_cast<ArgumentList*>(n)) return visit((ArgumentList*)n);
          if (dynamic_cast<DimExprs*>(n)) return visit((DimExprs*)n);
          if (dynamic_cast<DimExpr*>(n)) return visit((DimExpr*)n);
          if (dynamic_cast<PostIncrementExpression*>(n)) return visit((PostIncrementExpression*)n);
          if (dynamic_cast<PostDecrementExpression*>(n)) return visit((PostDecrementExpression*)n);
          if (dynamic_cast<PreIncrementExpression*>(n)) return visit((PreIncrementExpression*)n);
          if (dynamic_cast<PreDecrementExpression*>(n)) return visit((PreDecrementExpression*)n);
          if (dynamic_cast<AndExpression*>(n)) return visit((AndExpression*)n);
          if (dynamic_cast<ExclusiveOrExpression*>(n)) return visit((ExclusiveOrExpression*)n);
          if (dynamic_cast<InclusiveOrExpression*>(n)) return visit((InclusiveOrExpression*)n);
          if (dynamic_cast<ConditionalAndExpression*>(n)) return visit((ConditionalAndExpression*)n);
          if (dynamic_cast<ConditionalOrExpression*>(n)) return visit((ConditionalOrExpression*)n);
          if (dynamic_cast<ConditionalExpression*>(n)) return visit((ConditionalExpression*)n);
          if (dynamic_cast<Assignment*>(n)) return visit((Assignment*)n);
          if (dynamic_cast<Commaopt*>(n)) return visit((Commaopt*)n);
          if (dynamic_cast<Ellipsisopt*>(n)) return visit((Ellipsisopt*)n);
          if (dynamic_cast<LPGUserAction0*>(n)) return visit((LPGUserAction0*)n);
          if (dynamic_cast<LPGUserAction1*>(n)) return visit((LPGUserAction1*)n);
          if (dynamic_cast<LPGUserAction2*>(n)) return visit((LPGUserAction2*)n);
          if (dynamic_cast<LPGUserAction3*>(n)) return visit((LPGUserAction3*)n);
          if (dynamic_cast<LPGUserAction4*>(n)) return visit((LPGUserAction4*)n);
          if (dynamic_cast<IntegralType0*>(n)) return visit((IntegralType0*)n);
          if (dynamic_cast<IntegralType1*>(n)) return visit((IntegralType1*)n);
          if (dynamic_cast<IntegralType2*>(n)) return visit((IntegralType2*)n);
          if (dynamic_cast<IntegralType3*>(n)) return visit((IntegralType3*)n);
          if (dynamic_cast<IntegralType4*>(n)) return visit((IntegralType4*)n);
          if (dynamic_cast<FloatingPointType0*>(n)) return visit((FloatingPointType0*)n);
          if (dynamic_cast<FloatingPointType1*>(n)) return visit((FloatingPointType1*)n);
          if (dynamic_cast<WildcardBounds0*>(n)) return visit((WildcardBounds0*)n);
          if (dynamic_cast<WildcardBounds1*>(n)) return visit((WildcardBounds1*)n);
          if (dynamic_cast<ClassModifier0*>(n)) return visit((ClassModifier0*)n);
          if (dynamic_cast<ClassModifier1*>(n)) return visit((ClassModifier1*)n);
          if (dynamic_cast<ClassModifier2*>(n)) return visit((ClassModifier2*)n);
          if (dynamic_cast<ClassModifier3*>(n)) return visit((ClassModifier3*)n);
          if (dynamic_cast<ClassModifier4*>(n)) return visit((ClassModifier4*)n);
          if (dynamic_cast<ClassModifier5*>(n)) return visit((ClassModifier5*)n);
          if (dynamic_cast<ClassModifier6*>(n)) return visit((ClassModifier6*)n);
          if (dynamic_cast<FieldModifier0*>(n)) return visit((FieldModifier0*)n);
          if (dynamic_cast<FieldModifier1*>(n)) return visit((FieldModifier1*)n);
          if (dynamic_cast<FieldModifier2*>(n)) return visit((FieldModifier2*)n);
          if (dynamic_cast<FieldModifier3*>(n)) return visit((FieldModifier3*)n);
          if (dynamic_cast<FieldModifier4*>(n)) return visit((FieldModifier4*)n);
          if (dynamic_cast<FieldModifier5*>(n)) return visit((FieldModifier5*)n);
          if (dynamic_cast<FieldModifier6*>(n)) return visit((FieldModifier6*)n);
          if (dynamic_cast<MethodDeclarator0*>(n)) return visit((MethodDeclarator0*)n);
          if (dynamic_cast<MethodDeclarator1*>(n)) return visit((MethodDeclarator1*)n);
          if (dynamic_cast<MethodModifier0*>(n)) return visit((MethodModifier0*)n);
          if (dynamic_cast<MethodModifier1*>(n)) return visit((MethodModifier1*)n);
          if (dynamic_cast<MethodModifier2*>(n)) return visit((MethodModifier2*)n);
          if (dynamic_cast<MethodModifier3*>(n)) return visit((MethodModifier3*)n);
          if (dynamic_cast<MethodModifier4*>(n)) return visit((MethodModifier4*)n);
          if (dynamic_cast<MethodModifier5*>(n)) return visit((MethodModifier5*)n);
          if (dynamic_cast<MethodModifier6*>(n)) return visit((MethodModifier6*)n);
          if (dynamic_cast<MethodModifier7*>(n)) return visit((MethodModifier7*)n);
          if (dynamic_cast<MethodModifier8*>(n)) return visit((MethodModifier8*)n);
          if (dynamic_cast<ConstructorModifier0*>(n)) return visit((ConstructorModifier0*)n);
          if (dynamic_cast<ConstructorModifier1*>(n)) return visit((ConstructorModifier1*)n);
          if (dynamic_cast<ConstructorModifier2*>(n)) return visit((ConstructorModifier2*)n);
          if (dynamic_cast<ExplicitConstructorInvocation0*>(n)) return visit((ExplicitConstructorInvocation0*)n);
          if (dynamic_cast<ExplicitConstructorInvocation1*>(n)) return visit((ExplicitConstructorInvocation1*)n);
          if (dynamic_cast<ExplicitConstructorInvocation2*>(n)) return visit((ExplicitConstructorInvocation2*)n);
          if (dynamic_cast<InterfaceModifier0*>(n)) return visit((InterfaceModifier0*)n);
          if (dynamic_cast<InterfaceModifier1*>(n)) return visit((InterfaceModifier1*)n);
          if (dynamic_cast<InterfaceModifier2*>(n)) return visit((InterfaceModifier2*)n);
          if (dynamic_cast<InterfaceModifier3*>(n)) return visit((InterfaceModifier3*)n);
          if (dynamic_cast<InterfaceModifier4*>(n)) return visit((InterfaceModifier4*)n);
          if (dynamic_cast<InterfaceModifier5*>(n)) return visit((InterfaceModifier5*)n);
          if (dynamic_cast<ExtendsInterfaces0*>(n)) return visit((ExtendsInterfaces0*)n);
          if (dynamic_cast<ExtendsInterfaces1*>(n)) return visit((ExtendsInterfaces1*)n);
          if (dynamic_cast<ConstantModifier0*>(n)) return visit((ConstantModifier0*)n);
          if (dynamic_cast<ConstantModifier1*>(n)) return visit((ConstantModifier1*)n);
          if (dynamic_cast<ConstantModifier2*>(n)) return visit((ConstantModifier2*)n);
          if (dynamic_cast<AbstractMethodModifier0*>(n)) return visit((AbstractMethodModifier0*)n);
          if (dynamic_cast<AbstractMethodModifier1*>(n)) return visit((AbstractMethodModifier1*)n);
          if (dynamic_cast<AnnotationTypeElementDeclaration0*>(n)) return visit((AnnotationTypeElementDeclaration0*)n);
          if (dynamic_cast<AnnotationTypeElementDeclaration1*>(n)) return visit((AnnotationTypeElementDeclaration1*)n);
          if (dynamic_cast<AssertStatement0*>(n)) return visit((AssertStatement0*)n);
          if (dynamic_cast<AssertStatement1*>(n)) return visit((AssertStatement1*)n);
          if (dynamic_cast<SwitchLabel0*>(n)) return visit((SwitchLabel0*)n);
          if (dynamic_cast<SwitchLabel1*>(n)) return visit((SwitchLabel1*)n);
          if (dynamic_cast<SwitchLabel2*>(n)) return visit((SwitchLabel2*)n);
          if (dynamic_cast<TryStatement0*>(n)) return visit((TryStatement0*)n);
          if (dynamic_cast<TryStatement1*>(n)) return visit((TryStatement1*)n);
          if (dynamic_cast<PrimaryNoNewArray0*>(n)) return visit((PrimaryNoNewArray0*)n);
          if (dynamic_cast<PrimaryNoNewArray1*>(n)) return visit((PrimaryNoNewArray1*)n);
          if (dynamic_cast<PrimaryNoNewArray2*>(n)) return visit((PrimaryNoNewArray2*)n);
          if (dynamic_cast<PrimaryNoNewArray3*>(n)) return visit((PrimaryNoNewArray3*)n);
          if (dynamic_cast<PrimaryNoNewArray4*>(n)) return visit((PrimaryNoNewArray4*)n);
          if (dynamic_cast<Literal0*>(n)) return visit((Literal0*)n);
          if (dynamic_cast<Literal1*>(n)) return visit((Literal1*)n);
          if (dynamic_cast<Literal2*>(n)) return visit((Literal2*)n);
          if (dynamic_cast<Literal3*>(n)) return visit((Literal3*)n);
          if (dynamic_cast<Literal4*>(n)) return visit((Literal4*)n);
          if (dynamic_cast<Literal5*>(n)) return visit((Literal5*)n);
          if (dynamic_cast<Literal6*>(n)) return visit((Literal6*)n);
          if (dynamic_cast<BooleanLiteral0*>(n)) return visit((BooleanLiteral0*)n);
          if (dynamic_cast<BooleanLiteral1*>(n)) return visit((BooleanLiteral1*)n);
          if (dynamic_cast<ClassInstanceCreationExpression0*>(n)) return visit((ClassInstanceCreationExpression0*)n);
          if (dynamic_cast<ClassInstanceCreationExpression1*>(n)) return visit((ClassInstanceCreationExpression1*)n);
          if (dynamic_cast<ArrayCreationExpression0*>(n)) return visit((ArrayCreationExpression0*)n);
          if (dynamic_cast<ArrayCreationExpression1*>(n)) return visit((ArrayCreationExpression1*)n);
          if (dynamic_cast<ArrayCreationExpression2*>(n)) return visit((ArrayCreationExpression2*)n);
          if (dynamic_cast<ArrayCreationExpression3*>(n)) return visit((ArrayCreationExpression3*)n);
          if (dynamic_cast<Dims0*>(n)) return visit((Dims0*)n);
          if (dynamic_cast<Dims1*>(n)) return visit((Dims1*)n);
          if (dynamic_cast<FieldAccess0*>(n)) return visit((FieldAccess0*)n);
          if (dynamic_cast<FieldAccess1*>(n)) return visit((FieldAccess1*)n);
          if (dynamic_cast<FieldAccess2*>(n)) return visit((FieldAccess2*)n);
          if (dynamic_cast<MethodInvocation0*>(n)) return visit((MethodInvocation0*)n);
          if (dynamic_cast<MethodInvocation1*>(n)) return visit((MethodInvocation1*)n);
          if (dynamic_cast<MethodInvocation2*>(n)) return visit((MethodInvocation2*)n);
          if (dynamic_cast<MethodInvocation3*>(n)) return visit((MethodInvocation3*)n);
          if (dynamic_cast<MethodInvocation4*>(n)) return visit((MethodInvocation4*)n);
          if (dynamic_cast<ArrayAccess0*>(n)) return visit((ArrayAccess0*)n);
          if (dynamic_cast<ArrayAccess1*>(n)) return visit((ArrayAccess1*)n);
          if (dynamic_cast<UnaryExpression0*>(n)) return visit((UnaryExpression0*)n);
          if (dynamic_cast<UnaryExpression1*>(n)) return visit((UnaryExpression1*)n);
          if (dynamic_cast<UnaryExpressionNotPlusMinus0*>(n)) return visit((UnaryExpressionNotPlusMinus0*)n);
          if (dynamic_cast<UnaryExpressionNotPlusMinus1*>(n)) return visit((UnaryExpressionNotPlusMinus1*)n);
          if (dynamic_cast<CastExpression0*>(n)) return visit((CastExpression0*)n);
          if (dynamic_cast<CastExpression1*>(n)) return visit((CastExpression1*)n);
          if (dynamic_cast<MultiplicativeExpression0*>(n)) return visit((MultiplicativeExpression0*)n);
          if (dynamic_cast<MultiplicativeExpression1*>(n)) return visit((MultiplicativeExpression1*)n);
          if (dynamic_cast<MultiplicativeExpression2*>(n)) return visit((MultiplicativeExpression2*)n);
          if (dynamic_cast<AdditiveExpression0*>(n)) return visit((AdditiveExpression0*)n);
          if (dynamic_cast<AdditiveExpression1*>(n)) return visit((AdditiveExpression1*)n);
          if (dynamic_cast<ShiftExpression0*>(n)) return visit((ShiftExpression0*)n);
          if (dynamic_cast<ShiftExpression1*>(n)) return visit((ShiftExpression1*)n);
          if (dynamic_cast<ShiftExpression2*>(n)) return visit((ShiftExpression2*)n);
          if (dynamic_cast<RelationalExpression0*>(n)) return visit((RelationalExpression0*)n);
          if (dynamic_cast<RelationalExpression1*>(n)) return visit((RelationalExpression1*)n);
          if (dynamic_cast<RelationalExpression2*>(n)) return visit((RelationalExpression2*)n);
          if (dynamic_cast<RelationalExpression3*>(n)) return visit((RelationalExpression3*)n);
          if (dynamic_cast<RelationalExpression4*>(n)) return visit((RelationalExpression4*)n);
          if (dynamic_cast<EqualityExpression0*>(n)) return visit((EqualityExpression0*)n);
          if (dynamic_cast<EqualityExpression1*>(n)) return visit((EqualityExpression1*)n);
          if (dynamic_cast<AssignmentOperator0*>(n)) return visit((AssignmentOperator0*)n);
          if (dynamic_cast<AssignmentOperator1*>(n)) return visit((AssignmentOperator1*)n);
          if (dynamic_cast<AssignmentOperator2*>(n)) return visit((AssignmentOperator2*)n);
          if (dynamic_cast<AssignmentOperator3*>(n)) return visit((AssignmentOperator3*)n);
          if (dynamic_cast<AssignmentOperator4*>(n)) return visit((AssignmentOperator4*)n);
          if (dynamic_cast<AssignmentOperator5*>(n)) return visit((AssignmentOperator5*)n);
          if (dynamic_cast<AssignmentOperator6*>(n)) return visit((AssignmentOperator6*)n);
          if (dynamic_cast<AssignmentOperator7*>(n)) return visit((AssignmentOperator7*)n);
          if (dynamic_cast<AssignmentOperator8*>(n)) return visit((AssignmentOperator8*)n);
          if (dynamic_cast<AssignmentOperator9*>(n)) return visit((AssignmentOperator9*)n);
          if (dynamic_cast<AssignmentOperator10*>(n)) return visit((AssignmentOperator10*)n);
          if (dynamic_cast<AssignmentOperator11*>(n)) return visit((AssignmentOperator11*)n);
          else throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
      }
      virtual  void endVisit(Ast* n)
      {
          if (dynamic_cast<AstToken*>(n)) endVisit((AstToken*)n);
          if (dynamic_cast<identifier*>(n)) endVisit((identifier*)n);
          if (dynamic_cast<PrimitiveType*>(n)) endVisit((PrimitiveType*)n);
          if (dynamic_cast<ClassType*>(n)) endVisit((ClassType*)n);
          if (dynamic_cast<InterfaceType*>(n)) endVisit((InterfaceType*)n);
          if (dynamic_cast<TypeName*>(n)) endVisit((TypeName*)n);
          if (dynamic_cast<ArrayType*>(n)) endVisit((ArrayType*)n);
          if (dynamic_cast<TypeParameter*>(n)) endVisit((TypeParameter*)n);
          if (dynamic_cast<TypeBound*>(n)) endVisit((TypeBound*)n);
          if (dynamic_cast<AdditionalBoundList*>(n)) endVisit((AdditionalBoundList*)n);
          if (dynamic_cast<AdditionalBound*>(n)) endVisit((AdditionalBound*)n);
          if (dynamic_cast<TypeArguments*>(n)) endVisit((TypeArguments*)n);
          if (dynamic_cast<ActualTypeArgumentList*>(n)) endVisit((ActualTypeArgumentList*)n);
          if (dynamic_cast<Wildcard*>(n)) endVisit((Wildcard*)n);
          if (dynamic_cast<PackageName*>(n)) endVisit((PackageName*)n);
          if (dynamic_cast<ExpressionName*>(n)) endVisit((ExpressionName*)n);
          if (dynamic_cast<MethodName*>(n)) endVisit((MethodName*)n);
          if (dynamic_cast<PackageOrTypeName*>(n)) endVisit((PackageOrTypeName*)n);
          if (dynamic_cast<AmbiguousName*>(n)) endVisit((AmbiguousName*)n);
          if (dynamic_cast<CompilationUnit*>(n)) endVisit((CompilationUnit*)n);
          if (dynamic_cast<ImportDeclarations*>(n)) endVisit((ImportDeclarations*)n);
          if (dynamic_cast<TypeDeclarations*>(n)) endVisit((TypeDeclarations*)n);
          if (dynamic_cast<PackageDeclaration*>(n)) endVisit((PackageDeclaration*)n);
          if (dynamic_cast<SingleTypeImportDeclaration*>(n)) endVisit((SingleTypeImportDeclaration*)n);
          if (dynamic_cast<TypeImportOnDemandDeclaration*>(n)) endVisit((TypeImportOnDemandDeclaration*)n);
          if (dynamic_cast<SingleStaticImportDeclaration*>(n)) endVisit((SingleStaticImportDeclaration*)n);
          if (dynamic_cast<StaticImportOnDemandDeclaration*>(n)) endVisit((StaticImportOnDemandDeclaration*)n);
          if (dynamic_cast<TypeDeclaration*>(n)) endVisit((TypeDeclaration*)n);
          if (dynamic_cast<NormalClassDeclaration*>(n)) endVisit((NormalClassDeclaration*)n);
          if (dynamic_cast<ClassModifiers*>(n)) endVisit((ClassModifiers*)n);
          if (dynamic_cast<TypeParameters*>(n)) endVisit((TypeParameters*)n);
          if (dynamic_cast<TypeParameterList*>(n)) endVisit((TypeParameterList*)n);
          if (dynamic_cast<Super*>(n)) endVisit((Super*)n);
          if (dynamic_cast<Interfaces*>(n)) endVisit((Interfaces*)n);
          if (dynamic_cast<InterfaceTypeList*>(n)) endVisit((InterfaceTypeList*)n);
          if (dynamic_cast<ClassBody*>(n)) endVisit((ClassBody*)n);
          if (dynamic_cast<ClassBodyDeclarations*>(n)) endVisit((ClassBodyDeclarations*)n);
          if (dynamic_cast<ClassMemberDeclaration*>(n)) endVisit((ClassMemberDeclaration*)n);
          if (dynamic_cast<FieldDeclaration*>(n)) endVisit((FieldDeclaration*)n);
          if (dynamic_cast<VariableDeclarators*>(n)) endVisit((VariableDeclarators*)n);
          if (dynamic_cast<VariableDeclarator*>(n)) endVisit((VariableDeclarator*)n);
          if (dynamic_cast<VariableDeclaratorId*>(n)) endVisit((VariableDeclaratorId*)n);
          if (dynamic_cast<FieldModifiers*>(n)) endVisit((FieldModifiers*)n);
          if (dynamic_cast<MethodDeclaration*>(n)) endVisit((MethodDeclaration*)n);
          if (dynamic_cast<MethodHeader*>(n)) endVisit((MethodHeader*)n);
          if (dynamic_cast<ResultType*>(n)) endVisit((ResultType*)n);
          if (dynamic_cast<FormalParameterList*>(n)) endVisit((FormalParameterList*)n);
          if (dynamic_cast<FormalParameters*>(n)) endVisit((FormalParameters*)n);
          if (dynamic_cast<FormalParameter*>(n)) endVisit((FormalParameter*)n);
          if (dynamic_cast<VariableModifiers*>(n)) endVisit((VariableModifiers*)n);
          if (dynamic_cast<VariableModifier*>(n)) endVisit((VariableModifier*)n);
          if (dynamic_cast<LastFormalParameter*>(n)) endVisit((LastFormalParameter*)n);
          if (dynamic_cast<MethodModifiers*>(n)) endVisit((MethodModifiers*)n);
          if (dynamic_cast<Throws*>(n)) endVisit((Throws*)n);
          if (dynamic_cast<ExceptionTypeList*>(n)) endVisit((ExceptionTypeList*)n);
          if (dynamic_cast<MethodBody*>(n)) endVisit((MethodBody*)n);
          if (dynamic_cast<StaticInitializer*>(n)) endVisit((StaticInitializer*)n);
          if (dynamic_cast<ConstructorDeclaration*>(n)) endVisit((ConstructorDeclaration*)n);
          if (dynamic_cast<ConstructorDeclarator*>(n)) endVisit((ConstructorDeclarator*)n);
          if (dynamic_cast<ConstructorModifiers*>(n)) endVisit((ConstructorModifiers*)n);
          if (dynamic_cast<ConstructorBody*>(n)) endVisit((ConstructorBody*)n);
          if (dynamic_cast<EnumDeclaration*>(n)) endVisit((EnumDeclaration*)n);
          if (dynamic_cast<EnumBody*>(n)) endVisit((EnumBody*)n);
          if (dynamic_cast<EnumConstants*>(n)) endVisit((EnumConstants*)n);
          if (dynamic_cast<EnumConstant*>(n)) endVisit((EnumConstant*)n);
          if (dynamic_cast<Arguments*>(n)) endVisit((Arguments*)n);
          if (dynamic_cast<EnumBodyDeclarations*>(n)) endVisit((EnumBodyDeclarations*)n);
          if (dynamic_cast<NormalInterfaceDeclaration*>(n)) endVisit((NormalInterfaceDeclaration*)n);
          if (dynamic_cast<InterfaceModifiers*>(n)) endVisit((InterfaceModifiers*)n);
          if (dynamic_cast<InterfaceBody*>(n)) endVisit((InterfaceBody*)n);
          if (dynamic_cast<InterfaceMemberDeclarations*>(n)) endVisit((InterfaceMemberDeclarations*)n);
          if (dynamic_cast<InterfaceMemberDeclaration*>(n)) endVisit((InterfaceMemberDeclaration*)n);
          if (dynamic_cast<ConstantDeclaration*>(n)) endVisit((ConstantDeclaration*)n);
          if (dynamic_cast<ConstantModifiers*>(n)) endVisit((ConstantModifiers*)n);
          if (dynamic_cast<AbstractMethodDeclaration*>(n)) endVisit((AbstractMethodDeclaration*)n);
          if (dynamic_cast<AbstractMethodModifiers*>(n)) endVisit((AbstractMethodModifiers*)n);
          if (dynamic_cast<AnnotationTypeDeclaration*>(n)) endVisit((AnnotationTypeDeclaration*)n);
          if (dynamic_cast<AnnotationTypeBody*>(n)) endVisit((AnnotationTypeBody*)n);
          if (dynamic_cast<AnnotationTypeElementDeclarations*>(n)) endVisit((AnnotationTypeElementDeclarations*)n);
          if (dynamic_cast<DefaultValue*>(n)) endVisit((DefaultValue*)n);
          if (dynamic_cast<Annotations*>(n)) endVisit((Annotations*)n);
          if (dynamic_cast<NormalAnnotation*>(n)) endVisit((NormalAnnotation*)n);
          if (dynamic_cast<ElementValuePairs*>(n)) endVisit((ElementValuePairs*)n);
          if (dynamic_cast<ElementValuePair*>(n)) endVisit((ElementValuePair*)n);
          if (dynamic_cast<ElementValueArrayInitializer*>(n)) endVisit((ElementValueArrayInitializer*)n);
          if (dynamic_cast<ElementValues*>(n)) endVisit((ElementValues*)n);
          if (dynamic_cast<MarkerAnnotation*>(n)) endVisit((MarkerAnnotation*)n);
          if (dynamic_cast<SingleElementAnnotation*>(n)) endVisit((SingleElementAnnotation*)n);
          if (dynamic_cast<ArrayInitializer*>(n)) endVisit((ArrayInitializer*)n);
          if (dynamic_cast<VariableInitializers*>(n)) endVisit((VariableInitializers*)n);
          if (dynamic_cast<Block*>(n)) endVisit((Block*)n);
          if (dynamic_cast<BlockStatements*>(n)) endVisit((BlockStatements*)n);
          if (dynamic_cast<LocalVariableDeclarationStatement*>(n)) endVisit((LocalVariableDeclarationStatement*)n);
          if (dynamic_cast<LocalVariableDeclaration*>(n)) endVisit((LocalVariableDeclaration*)n);
          if (dynamic_cast<IfThenStatement*>(n)) endVisit((IfThenStatement*)n);
          if (dynamic_cast<IfThenElseStatement*>(n)) endVisit((IfThenElseStatement*)n);
          if (dynamic_cast<IfThenElseStatementNoShortIf*>(n)) endVisit((IfThenElseStatementNoShortIf*)n);
          if (dynamic_cast<EmptyStatement*>(n)) endVisit((EmptyStatement*)n);
          if (dynamic_cast<LabeledStatement*>(n)) endVisit((LabeledStatement*)n);
          if (dynamic_cast<LabeledStatementNoShortIf*>(n)) endVisit((LabeledStatementNoShortIf*)n);
          if (dynamic_cast<ExpressionStatement*>(n)) endVisit((ExpressionStatement*)n);
          if (dynamic_cast<SwitchStatement*>(n)) endVisit((SwitchStatement*)n);
          if (dynamic_cast<SwitchBlock*>(n)) endVisit((SwitchBlock*)n);
          if (dynamic_cast<SwitchBlockStatementGroups*>(n)) endVisit((SwitchBlockStatementGroups*)n);
          if (dynamic_cast<SwitchBlockStatementGroup*>(n)) endVisit((SwitchBlockStatementGroup*)n);
          if (dynamic_cast<SwitchLabels*>(n)) endVisit((SwitchLabels*)n);
          if (dynamic_cast<WhileStatement*>(n)) endVisit((WhileStatement*)n);
          if (dynamic_cast<WhileStatementNoShortIf*>(n)) endVisit((WhileStatementNoShortIf*)n);
          if (dynamic_cast<DoStatement*>(n)) endVisit((DoStatement*)n);
          if (dynamic_cast<BasicForStatement*>(n)) endVisit((BasicForStatement*)n);
          if (dynamic_cast<ForStatementNoShortIf*>(n)) endVisit((ForStatementNoShortIf*)n);
          if (dynamic_cast<StatementExpressionList*>(n)) endVisit((StatementExpressionList*)n);
          if (dynamic_cast<EnhancedForStatement*>(n)) endVisit((EnhancedForStatement*)n);
          if (dynamic_cast<BreakStatement*>(n)) endVisit((BreakStatement*)n);
          if (dynamic_cast<ContinueStatement*>(n)) endVisit((ContinueStatement*)n);
          if (dynamic_cast<ReturnStatement*>(n)) endVisit((ReturnStatement*)n);
          if (dynamic_cast<ThrowStatement*>(n)) endVisit((ThrowStatement*)n);
          if (dynamic_cast<SynchronizedStatement*>(n)) endVisit((SynchronizedStatement*)n);
          if (dynamic_cast<Catches*>(n)) endVisit((Catches*)n);
          if (dynamic_cast<CatchClause*>(n)) endVisit((CatchClause*)n);
          if (dynamic_cast<Finally*>(n)) endVisit((Finally*)n);
          if (dynamic_cast<ArgumentList*>(n)) endVisit((ArgumentList*)n);
          if (dynamic_cast<DimExprs*>(n)) endVisit((DimExprs*)n);
          if (dynamic_cast<DimExpr*>(n)) endVisit((DimExpr*)n);
          if (dynamic_cast<PostIncrementExpression*>(n)) endVisit((PostIncrementExpression*)n);
          if (dynamic_cast<PostDecrementExpression*>(n)) endVisit((PostDecrementExpression*)n);
          if (dynamic_cast<PreIncrementExpression*>(n)) endVisit((PreIncrementExpression*)n);
          if (dynamic_cast<PreDecrementExpression*>(n)) endVisit((PreDecrementExpression*)n);
          if (dynamic_cast<AndExpression*>(n)) endVisit((AndExpression*)n);
          if (dynamic_cast<ExclusiveOrExpression*>(n)) endVisit((ExclusiveOrExpression*)n);
          if (dynamic_cast<InclusiveOrExpression*>(n)) endVisit((InclusiveOrExpression*)n);
          if (dynamic_cast<ConditionalAndExpression*>(n)) endVisit((ConditionalAndExpression*)n);
          if (dynamic_cast<ConditionalOrExpression*>(n)) endVisit((ConditionalOrExpression*)n);
          if (dynamic_cast<ConditionalExpression*>(n)) endVisit((ConditionalExpression*)n);
          if (dynamic_cast<Assignment*>(n)) endVisit((Assignment*)n);
          if (dynamic_cast<Commaopt*>(n)) endVisit((Commaopt*)n);
          if (dynamic_cast<Ellipsisopt*>(n)) endVisit((Ellipsisopt*)n);
          if (dynamic_cast<LPGUserAction0*>(n)) endVisit((LPGUserAction0*)n);
          if (dynamic_cast<LPGUserAction1*>(n)) endVisit((LPGUserAction1*)n);
          if (dynamic_cast<LPGUserAction2*>(n)) endVisit((LPGUserAction2*)n);
          if (dynamic_cast<LPGUserAction3*>(n)) endVisit((LPGUserAction3*)n);
          if (dynamic_cast<LPGUserAction4*>(n)) endVisit((LPGUserAction4*)n);
          if (dynamic_cast<IntegralType0*>(n)) endVisit((IntegralType0*)n);
          if (dynamic_cast<IntegralType1*>(n)) endVisit((IntegralType1*)n);
          if (dynamic_cast<IntegralType2*>(n)) endVisit((IntegralType2*)n);
          if (dynamic_cast<IntegralType3*>(n)) endVisit((IntegralType3*)n);
          if (dynamic_cast<IntegralType4*>(n)) endVisit((IntegralType4*)n);
          if (dynamic_cast<FloatingPointType0*>(n)) endVisit((FloatingPointType0*)n);
          if (dynamic_cast<FloatingPointType1*>(n)) endVisit((FloatingPointType1*)n);
          if (dynamic_cast<WildcardBounds0*>(n)) endVisit((WildcardBounds0*)n);
          if (dynamic_cast<WildcardBounds1*>(n)) endVisit((WildcardBounds1*)n);
          if (dynamic_cast<ClassModifier0*>(n)) endVisit((ClassModifier0*)n);
          if (dynamic_cast<ClassModifier1*>(n)) endVisit((ClassModifier1*)n);
          if (dynamic_cast<ClassModifier2*>(n)) endVisit((ClassModifier2*)n);
          if (dynamic_cast<ClassModifier3*>(n)) endVisit((ClassModifier3*)n);
          if (dynamic_cast<ClassModifier4*>(n)) endVisit((ClassModifier4*)n);
          if (dynamic_cast<ClassModifier5*>(n)) endVisit((ClassModifier5*)n);
          if (dynamic_cast<ClassModifier6*>(n)) endVisit((ClassModifier6*)n);
          if (dynamic_cast<FieldModifier0*>(n)) endVisit((FieldModifier0*)n);
          if (dynamic_cast<FieldModifier1*>(n)) endVisit((FieldModifier1*)n);
          if (dynamic_cast<FieldModifier2*>(n)) endVisit((FieldModifier2*)n);
          if (dynamic_cast<FieldModifier3*>(n)) endVisit((FieldModifier3*)n);
          if (dynamic_cast<FieldModifier4*>(n)) endVisit((FieldModifier4*)n);
          if (dynamic_cast<FieldModifier5*>(n)) endVisit((FieldModifier5*)n);
          if (dynamic_cast<FieldModifier6*>(n)) endVisit((FieldModifier6*)n);
          if (dynamic_cast<MethodDeclarator0*>(n)) endVisit((MethodDeclarator0*)n);
          if (dynamic_cast<MethodDeclarator1*>(n)) endVisit((MethodDeclarator1*)n);
          if (dynamic_cast<MethodModifier0*>(n)) endVisit((MethodModifier0*)n);
          if (dynamic_cast<MethodModifier1*>(n)) endVisit((MethodModifier1*)n);
          if (dynamic_cast<MethodModifier2*>(n)) endVisit((MethodModifier2*)n);
          if (dynamic_cast<MethodModifier3*>(n)) endVisit((MethodModifier3*)n);
          if (dynamic_cast<MethodModifier4*>(n)) endVisit((MethodModifier4*)n);
          if (dynamic_cast<MethodModifier5*>(n)) endVisit((MethodModifier5*)n);
          if (dynamic_cast<MethodModifier6*>(n)) endVisit((MethodModifier6*)n);
          if (dynamic_cast<MethodModifier7*>(n)) endVisit((MethodModifier7*)n);
          if (dynamic_cast<MethodModifier8*>(n)) endVisit((MethodModifier8*)n);
          if (dynamic_cast<ConstructorModifier0*>(n)) endVisit((ConstructorModifier0*)n);
          if (dynamic_cast<ConstructorModifier1*>(n)) endVisit((ConstructorModifier1*)n);
          if (dynamic_cast<ConstructorModifier2*>(n)) endVisit((ConstructorModifier2*)n);
          if (dynamic_cast<ExplicitConstructorInvocation0*>(n)) endVisit((ExplicitConstructorInvocation0*)n);
          if (dynamic_cast<ExplicitConstructorInvocation1*>(n)) endVisit((ExplicitConstructorInvocation1*)n);
          if (dynamic_cast<ExplicitConstructorInvocation2*>(n)) endVisit((ExplicitConstructorInvocation2*)n);
          if (dynamic_cast<InterfaceModifier0*>(n)) endVisit((InterfaceModifier0*)n);
          if (dynamic_cast<InterfaceModifier1*>(n)) endVisit((InterfaceModifier1*)n);
          if (dynamic_cast<InterfaceModifier2*>(n)) endVisit((InterfaceModifier2*)n);
          if (dynamic_cast<InterfaceModifier3*>(n)) endVisit((InterfaceModifier3*)n);
          if (dynamic_cast<InterfaceModifier4*>(n)) endVisit((InterfaceModifier4*)n);
          if (dynamic_cast<InterfaceModifier5*>(n)) endVisit((InterfaceModifier5*)n);
          if (dynamic_cast<ExtendsInterfaces0*>(n)) endVisit((ExtendsInterfaces0*)n);
          if (dynamic_cast<ExtendsInterfaces1*>(n)) endVisit((ExtendsInterfaces1*)n);
          if (dynamic_cast<ConstantModifier0*>(n)) endVisit((ConstantModifier0*)n);
          if (dynamic_cast<ConstantModifier1*>(n)) endVisit((ConstantModifier1*)n);
          if (dynamic_cast<ConstantModifier2*>(n)) endVisit((ConstantModifier2*)n);
          if (dynamic_cast<AbstractMethodModifier0*>(n)) endVisit((AbstractMethodModifier0*)n);
          if (dynamic_cast<AbstractMethodModifier1*>(n)) endVisit((AbstractMethodModifier1*)n);
          if (dynamic_cast<AnnotationTypeElementDeclaration0*>(n)) endVisit((AnnotationTypeElementDeclaration0*)n);
          if (dynamic_cast<AnnotationTypeElementDeclaration1*>(n)) endVisit((AnnotationTypeElementDeclaration1*)n);
          if (dynamic_cast<AssertStatement0*>(n)) endVisit((AssertStatement0*)n);
          if (dynamic_cast<AssertStatement1*>(n)) endVisit((AssertStatement1*)n);
          if (dynamic_cast<SwitchLabel0*>(n)) endVisit((SwitchLabel0*)n);
          if (dynamic_cast<SwitchLabel1*>(n)) endVisit((SwitchLabel1*)n);
          if (dynamic_cast<SwitchLabel2*>(n)) endVisit((SwitchLabel2*)n);
          if (dynamic_cast<TryStatement0*>(n)) endVisit((TryStatement0*)n);
          if (dynamic_cast<TryStatement1*>(n)) endVisit((TryStatement1*)n);
          if (dynamic_cast<PrimaryNoNewArray0*>(n)) endVisit((PrimaryNoNewArray0*)n);
          if (dynamic_cast<PrimaryNoNewArray1*>(n)) endVisit((PrimaryNoNewArray1*)n);
          if (dynamic_cast<PrimaryNoNewArray2*>(n)) endVisit((PrimaryNoNewArray2*)n);
          if (dynamic_cast<PrimaryNoNewArray3*>(n)) endVisit((PrimaryNoNewArray3*)n);
          if (dynamic_cast<PrimaryNoNewArray4*>(n)) endVisit((PrimaryNoNewArray4*)n);
          if (dynamic_cast<Literal0*>(n)) endVisit((Literal0*)n);
          if (dynamic_cast<Literal1*>(n)) endVisit((Literal1*)n);
          if (dynamic_cast<Literal2*>(n)) endVisit((Literal2*)n);
          if (dynamic_cast<Literal3*>(n)) endVisit((Literal3*)n);
          if (dynamic_cast<Literal4*>(n)) endVisit((Literal4*)n);
          if (dynamic_cast<Literal5*>(n)) endVisit((Literal5*)n);
          if (dynamic_cast<Literal6*>(n)) endVisit((Literal6*)n);
          if (dynamic_cast<BooleanLiteral0*>(n)) endVisit((BooleanLiteral0*)n);
          if (dynamic_cast<BooleanLiteral1*>(n)) endVisit((BooleanLiteral1*)n);
          if (dynamic_cast<ClassInstanceCreationExpression0*>(n)) endVisit((ClassInstanceCreationExpression0*)n);
          if (dynamic_cast<ClassInstanceCreationExpression1*>(n)) endVisit((ClassInstanceCreationExpression1*)n);
          if (dynamic_cast<ArrayCreationExpression0*>(n)) endVisit((ArrayCreationExpression0*)n);
          if (dynamic_cast<ArrayCreationExpression1*>(n)) endVisit((ArrayCreationExpression1*)n);
          if (dynamic_cast<ArrayCreationExpression2*>(n)) endVisit((ArrayCreationExpression2*)n);
          if (dynamic_cast<ArrayCreationExpression3*>(n)) endVisit((ArrayCreationExpression3*)n);
          if (dynamic_cast<Dims0*>(n)) endVisit((Dims0*)n);
          if (dynamic_cast<Dims1*>(n)) endVisit((Dims1*)n);
          if (dynamic_cast<FieldAccess0*>(n)) endVisit((FieldAccess0*)n);
          if (dynamic_cast<FieldAccess1*>(n)) endVisit((FieldAccess1*)n);
          if (dynamic_cast<FieldAccess2*>(n)) endVisit((FieldAccess2*)n);
          if (dynamic_cast<MethodInvocation0*>(n)) endVisit((MethodInvocation0*)n);
          if (dynamic_cast<MethodInvocation1*>(n)) endVisit((MethodInvocation1*)n);
          if (dynamic_cast<MethodInvocation2*>(n)) endVisit((MethodInvocation2*)n);
          if (dynamic_cast<MethodInvocation3*>(n)) endVisit((MethodInvocation3*)n);
          if (dynamic_cast<MethodInvocation4*>(n)) endVisit((MethodInvocation4*)n);
          if (dynamic_cast<ArrayAccess0*>(n)) endVisit((ArrayAccess0*)n);
          if (dynamic_cast<ArrayAccess1*>(n)) endVisit((ArrayAccess1*)n);
          if (dynamic_cast<UnaryExpression0*>(n)) endVisit((UnaryExpression0*)n);
          if (dynamic_cast<UnaryExpression1*>(n)) endVisit((UnaryExpression1*)n);
          if (dynamic_cast<UnaryExpressionNotPlusMinus0*>(n)) endVisit((UnaryExpressionNotPlusMinus0*)n);
          if (dynamic_cast<UnaryExpressionNotPlusMinus1*>(n)) endVisit((UnaryExpressionNotPlusMinus1*)n);
          if (dynamic_cast<CastExpression0*>(n)) endVisit((CastExpression0*)n);
          if (dynamic_cast<CastExpression1*>(n)) endVisit((CastExpression1*)n);
          if (dynamic_cast<MultiplicativeExpression0*>(n)) endVisit((MultiplicativeExpression0*)n);
          if (dynamic_cast<MultiplicativeExpression1*>(n)) endVisit((MultiplicativeExpression1*)n);
          if (dynamic_cast<MultiplicativeExpression2*>(n)) endVisit((MultiplicativeExpression2*)n);
          if (dynamic_cast<AdditiveExpression0*>(n)) endVisit((AdditiveExpression0*)n);
          if (dynamic_cast<AdditiveExpression1*>(n)) endVisit((AdditiveExpression1*)n);
          if (dynamic_cast<ShiftExpression0*>(n)) endVisit((ShiftExpression0*)n);
          if (dynamic_cast<ShiftExpression1*>(n)) endVisit((ShiftExpression1*)n);
          if (dynamic_cast<ShiftExpression2*>(n)) endVisit((ShiftExpression2*)n);
          if (dynamic_cast<RelationalExpression0*>(n)) endVisit((RelationalExpression0*)n);
          if (dynamic_cast<RelationalExpression1*>(n)) endVisit((RelationalExpression1*)n);
          if (dynamic_cast<RelationalExpression2*>(n)) endVisit((RelationalExpression2*)n);
          if (dynamic_cast<RelationalExpression3*>(n)) endVisit((RelationalExpression3*)n);
          if (dynamic_cast<RelationalExpression4*>(n)) endVisit((RelationalExpression4*)n);
          if (dynamic_cast<EqualityExpression0*>(n)) endVisit((EqualityExpression0*)n);
          if (dynamic_cast<EqualityExpression1*>(n)) endVisit((EqualityExpression1*)n);
          if (dynamic_cast<AssignmentOperator0*>(n)) endVisit((AssignmentOperator0*)n);
          if (dynamic_cast<AssignmentOperator1*>(n)) endVisit((AssignmentOperator1*)n);
          if (dynamic_cast<AssignmentOperator2*>(n)) endVisit((AssignmentOperator2*)n);
          if (dynamic_cast<AssignmentOperator3*>(n)) endVisit((AssignmentOperator3*)n);
          if (dynamic_cast<AssignmentOperator4*>(n)) endVisit((AssignmentOperator4*)n);
          if (dynamic_cast<AssignmentOperator5*>(n)) endVisit((AssignmentOperator5*)n);
          if (dynamic_cast<AssignmentOperator6*>(n)) endVisit((AssignmentOperator6*)n);
          if (dynamic_cast<AssignmentOperator7*>(n)) endVisit((AssignmentOperator7*)n);
          if (dynamic_cast<AssignmentOperator8*>(n)) endVisit((AssignmentOperator8*)n);
          if (dynamic_cast<AssignmentOperator9*>(n)) endVisit((AssignmentOperator9*)n);
          if (dynamic_cast<AssignmentOperator10*>(n)) endVisit((AssignmentOperator10*)n);
          if (dynamic_cast<AssignmentOperator11*>(n)) endVisit((AssignmentOperator11*)n);
          throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
      }
     
    };

    //#line 351 "btParserTemplateF.gi

 
     void ruleAction(int ruleNumber)
    {
        switch (ruleNumber)
        {

            //
            // Rule 3:  identifier ::= IDENTIFIER
            //
            case 3: {
               //#line 184 "GJavaParser.g"
                setResult(
                    //#line 184 GJavaParser.g
                    ast_pool.Next()=new identifier(this, getRhsIToken(1))
                //#line 184 GJavaParser.g
                );
            break;
            }
            //
            // Rule 4:  LPGUserAction ::= BlockStatementsopt
            //
            case 4:
                break;
            //
            // Rule 5:  LPGUserAction ::= $BeginAction BlockStatementsopt $EndAction
            //
            case 5: {
               //#line 194 "GJavaParser.g"
                setResult(
                    //#line 194 GJavaParser.g
                    ast_pool.Next()=new LPGUserAction0(getLeftIToken(), getRightIToken(),
                                       //#line 194 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                       //#line 194 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 194 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 194 GJavaParser.g
                );
            break;
            }
            //
            // Rule 6:  LPGUserAction ::= $BeginJava BlockStatementsopt $EndJava
            //
            case 6: {
               //#line 195 "GJavaParser.g"
                setResult(
                    //#line 195 GJavaParser.g
                    ast_pool.Next()=new LPGUserAction1(getLeftIToken(), getRightIToken(),
                                       //#line 195 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                       //#line 195 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 195 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 195 GJavaParser.g
                );
            break;
            }
            //
            // Rule 7:  LPGUserAction ::= $NoAction
            //
            case 7: {
               //#line 196 "GJavaParser.g"
                setResult(
                    //#line 196 GJavaParser.g
                    ast_pool.Next()=new LPGUserAction2(getRhsIToken(1))
                //#line 196 GJavaParser.g
                );
            break;
            }
            //
            // Rule 8:  LPGUserAction ::= $NullAction
            //
            case 8: {
               //#line 197 "GJavaParser.g"
                setResult(
                    //#line 197 GJavaParser.g
                    ast_pool.Next()=new LPGUserAction3(getRhsIToken(1))
                //#line 197 GJavaParser.g
                );
            break;
            }
            //
            // Rule 9:  LPGUserAction ::= $BadAction
            //
            case 9: {
               //#line 198 "GJavaParser.g"
                setResult(
                    //#line 198 GJavaParser.g
                    ast_pool.Next()=new LPGUserAction4(getRhsIToken(1))
                //#line 198 GJavaParser.g
                );
            break;
            }
            //
            // Rule 10:  Type ::= PrimitiveType
            //
            case 10:
                break;
            //
            // Rule 11:  Type ::= ReferenceType
            //
            case 11:
                break;
            //
            // Rule 12:  PrimitiveType ::= NumericType
            //
            case 12:
                break;
            //
            // Rule 13:  PrimitiveType ::= boolean
            //
            case 13: {
               //#line 207 "GJavaParser.g"
                setResult(
                    //#line 207 GJavaParser.g
                    ast_pool.Next()=new PrimitiveType(getRhsIToken(1))
                //#line 207 GJavaParser.g
                );
            break;
            }
            //
            // Rule 14:  NumericType ::= IntegralType
            //
            case 14:
                break;
            //
            // Rule 15:  NumericType ::= FloatingPointType
            //
            case 15:
                break;
            //
            // Rule 16:  IntegralType ::= byte
            //
            case 16: {
               //#line 212 "GJavaParser.g"
                setResult(
                    //#line 212 GJavaParser.g
                    ast_pool.Next()=new IntegralType0(getRhsIToken(1))
                //#line 212 GJavaParser.g
                );
            break;
            }
            //
            // Rule 17:  IntegralType ::= short
            //
            case 17: {
               //#line 213 "GJavaParser.g"
                setResult(
                    //#line 213 GJavaParser.g
                    ast_pool.Next()=new IntegralType1(getRhsIToken(1))
                //#line 213 GJavaParser.g
                );
            break;
            }
            //
            // Rule 18:  IntegralType ::= int
            //
            case 18: {
               //#line 214 "GJavaParser.g"
                setResult(
                    //#line 214 GJavaParser.g
                    ast_pool.Next()=new IntegralType2(getRhsIToken(1))
                //#line 214 GJavaParser.g
                );
            break;
            }
            //
            // Rule 19:  IntegralType ::= long
            //
            case 19: {
               //#line 215 "GJavaParser.g"
                setResult(
                    //#line 215 GJavaParser.g
                    ast_pool.Next()=new IntegralType3(getRhsIToken(1))
                //#line 215 GJavaParser.g
                );
            break;
            }
            //
            // Rule 20:  IntegralType ::= char
            //
            case 20: {
               //#line 216 "GJavaParser.g"
                setResult(
                    //#line 216 GJavaParser.g
                    ast_pool.Next()=new IntegralType4(getRhsIToken(1))
                //#line 216 GJavaParser.g
                );
            break;
            }
            //
            // Rule 21:  FloatingPointType ::= float
            //
            case 21: {
               //#line 218 "GJavaParser.g"
                setResult(
                    //#line 218 GJavaParser.g
                    ast_pool.Next()=new FloatingPointType0(getRhsIToken(1))
                //#line 218 GJavaParser.g
                );
            break;
            }
            //
            // Rule 22:  FloatingPointType ::= double
            //
            case 22: {
               //#line 219 "GJavaParser.g"
                setResult(
                    //#line 219 GJavaParser.g
                    ast_pool.Next()=new FloatingPointType1(getRhsIToken(1))
                //#line 219 GJavaParser.g
                );
            break;
            }
            //
            // Rule 23:  ReferenceType ::= ClassOrInterfaceType
            //
            case 23:
                break;
            //
            // Rule 24:  ReferenceType ::= TypeVariable
            //
            case 24:
                break;
            //
            // Rule 25:  ReferenceType ::= ArrayType
            //
            case 25:
                break;
            //
            // Rule 26:  ClassOrInterfaceType ::= ClassType
            //
            case 26:
                break;
            //
            // Rule 27:  ClassType ::= TypeName TypeArgumentsopt
            //
            case 27: {
               //#line 231 "GJavaParser.g"
                setResult(
                    //#line 231 GJavaParser.g
                    ast_pool.Next()=new ClassType(getLeftIToken(), getRightIToken(),
                                  //#line 231 GJavaParser.g
                                  (IAst*)getRhsSym(1),
                                  //#line 231 GJavaParser.g
                                  (IAst*)getRhsSym(2))
                //#line 231 GJavaParser.g
                );
            break;
            }
            //
            // Rule 28:  InterfaceType ::= TypeName TypeArgumentsopt
            //
            case 28: {
               //#line 233 "GJavaParser.g"
                setResult(
                    //#line 233 GJavaParser.g
                    ast_pool.Next()=new InterfaceType(getLeftIToken(), getRightIToken(),
                                      //#line 233 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 233 GJavaParser.g
                                      (IAst*)getRhsSym(2))
                //#line 233 GJavaParser.g
                );
            break;
            }
            //
            // Rule 29:  TypeName ::= identifier
            //
            case 29:
                break;
            //
            // Rule 30:  TypeName ::= TypeName . identifier
            //
            case 30: {
               //#line 236 "GJavaParser.g"
                setResult(
                    //#line 236 GJavaParser.g
                    ast_pool.Next()=new TypeName(getLeftIToken(), getRightIToken(),
                                 //#line 236 GJavaParser.g
                                 (IAst*)getRhsSym(1),
                                 //#line 236 GJavaParser.g
                                 ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                 //#line 236 GJavaParser.g
                                 (IAst*)getRhsSym(3))
                //#line 236 GJavaParser.g
                );
            break;
            }
            //
            // Rule 31:  ClassName ::= TypeName
            //
            case 31:
                break;
            //
            // Rule 32:  TypeVariable ::= identifier
            //
            case 32:
                break;
            //
            // Rule 33:  ArrayType ::= Type [ ]
            //
            case 33: {
               //#line 242 "GJavaParser.g"
                setResult(
                    //#line 242 GJavaParser.g
                    ast_pool.Next()=new ArrayType(getLeftIToken(), getRightIToken(),
                                  //#line 242 GJavaParser.g
                                  (IAst*)getRhsSym(1),
                                  //#line 242 GJavaParser.g
                                  ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                  //#line 242 GJavaParser.g
                                  ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 242 GJavaParser.g
                );
            break;
            }
            //
            // Rule 34:  TypeParameter ::= TypeVariable TypeBoundopt
            //
            case 34: {
               //#line 244 "GJavaParser.g"
                setResult(
                    //#line 244 GJavaParser.g
                    ast_pool.Next()=new TypeParameter(getLeftIToken(), getRightIToken(),
                                      //#line 244 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 244 GJavaParser.g
                                      (IAst*)getRhsSym(2))
                //#line 244 GJavaParser.g
                );
            break;
            }
            //
            // Rule 35:  TypeBound ::= extends ClassOrInterfaceType AdditionalBoundListopt
            //
            case 35: {
               //#line 246 "GJavaParser.g"
                setResult(
                    //#line 246 GJavaParser.g
                    ast_pool.Next()=new TypeBound(getLeftIToken(), getRightIToken(),
                                  //#line 246 GJavaParser.g
                                  ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                  //#line 246 GJavaParser.g
                                  (IAst*)getRhsSym(2),
                                  //#line 246 GJavaParser.g
                                  (IAst*)getRhsSym(3))
                //#line 246 GJavaParser.g
                );
            break;
            }
            //
            // Rule 36:  AdditionalBoundList ::= AdditionalBound
            //
            case 36:
                break;
            //
            // Rule 37:  AdditionalBoundList ::= AdditionalBoundList AdditionalBound
            //
            case 37: {
               //#line 249 "GJavaParser.g"
                setResult(
                    //#line 249 GJavaParser.g
                    ast_pool.Next()=new AdditionalBoundList(getLeftIToken(), getRightIToken(),
                                            //#line 249 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 249 GJavaParser.g
                                            (IAst*)getRhsSym(2))
                //#line 249 GJavaParser.g
                );
            break;
            }
            //
            // Rule 38:  AdditionalBound ::= & InterfaceType
            //
            case 38: {
               //#line 251 "GJavaParser.g"
                setResult(
                    //#line 251 GJavaParser.g
                    ast_pool.Next()=new AdditionalBound(getLeftIToken(), getRightIToken(),
                                        //#line 251 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                        //#line 251 GJavaParser.g
                                        (IAst*)getRhsSym(2))
                //#line 251 GJavaParser.g
                );
            break;
            }
            //
            // Rule 39:  TypeArguments ::= < ActualTypeArgumentList >
            //
            case 39: {
               //#line 253 "GJavaParser.g"
                setResult(
                    //#line 253 GJavaParser.g
                    ast_pool.Next()=new TypeArguments(getLeftIToken(), getRightIToken(),
                                      //#line 253 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                      //#line 253 GJavaParser.g
                                      (IAst*)getRhsSym(2),
                                      //#line 253 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 253 GJavaParser.g
                );
            break;
            }
            //
            // Rule 40:  ActualTypeArgumentList ::= ActualTypeArgument
            //
            case 40:
                break;
            //
            // Rule 41:  ActualTypeArgumentList ::= ActualTypeArgumentList , ActualTypeArgument
            //
            case 41: {
               //#line 256 "GJavaParser.g"
                setResult(
                    //#line 256 GJavaParser.g
                    ast_pool.Next()=new ActualTypeArgumentList(getLeftIToken(), getRightIToken(),
                                               //#line 256 GJavaParser.g
                                               (IAst*)getRhsSym(1),
                                               //#line 256 GJavaParser.g
                                               ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                               //#line 256 GJavaParser.g
                                               (IAst*)getRhsSym(3))
                //#line 256 GJavaParser.g
                );
            break;
            }
            //
            // Rule 42:  ActualTypeArgument ::= ReferenceType
            //
            case 42:
                break;
            //
            // Rule 43:  ActualTypeArgument ::= Wildcard
            //
            case 43:
                break;
            //
            // Rule 44:  Wildcard ::= ? WildcardBoundsOpt
            //
            case 44: {
               //#line 261 "GJavaParser.g"
                setResult(
                    //#line 261 GJavaParser.g
                    ast_pool.Next()=new Wildcard(getLeftIToken(), getRightIToken(),
                                 //#line 261 GJavaParser.g
                                 ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                 //#line 261 GJavaParser.g
                                 (IAst*)getRhsSym(2))
                //#line 261 GJavaParser.g
                );
            break;
            }
            //
            // Rule 45:  WildcardBounds ::= extends ReferenceType
            //
            case 45: {
               //#line 263 "GJavaParser.g"
                setResult(
                    //#line 263 GJavaParser.g
                    ast_pool.Next()=new WildcardBounds0(getLeftIToken(), getRightIToken(),
                                        //#line 263 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                        //#line 263 GJavaParser.g
                                        (IAst*)getRhsSym(2))
                //#line 263 GJavaParser.g
                );
            break;
            }
            //
            // Rule 46:  WildcardBounds ::= super ReferenceType
            //
            case 46: {
               //#line 264 "GJavaParser.g"
                setResult(
                    //#line 264 GJavaParser.g
                    ast_pool.Next()=new WildcardBounds1(getLeftIToken(), getRightIToken(),
                                        //#line 264 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                        //#line 264 GJavaParser.g
                                        (IAst*)getRhsSym(2))
                //#line 264 GJavaParser.g
                );
            break;
            }
            //
            // Rule 47:  PackageName ::= identifier
            //
            case 47:
                break;
            //
            // Rule 48:  PackageName ::= PackageName . identifier
            //
            case 48: {
               //#line 271 "GJavaParser.g"
                setResult(
                    //#line 271 GJavaParser.g
                    ast_pool.Next()=new PackageName(getLeftIToken(), getRightIToken(),
                                    //#line 271 GJavaParser.g
                                    (IAst*)getRhsSym(1),
                                    //#line 271 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                    //#line 271 GJavaParser.g
                                    (IAst*)getRhsSym(3))
                //#line 271 GJavaParser.g
                );
            break;
            }
            //
            // Rule 49:  ExpressionName ::= identifier
            //
            case 49:
                break;
            //
            // Rule 50:  ExpressionName ::= AmbiguousName . identifier
            //
            case 50: {
               //#line 280 "GJavaParser.g"
                setResult(
                    //#line 280 GJavaParser.g
                    ast_pool.Next()=new ExpressionName(getLeftIToken(), getRightIToken(),
                                       //#line 280 GJavaParser.g
                                       (IAst*)getRhsSym(1),
                                       //#line 280 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                       //#line 280 GJavaParser.g
                                       (IAst*)getRhsSym(3))
                //#line 280 GJavaParser.g
                );
            break;
            }
            //
            // Rule 51:  MethodName ::= identifier
            //
            case 51:
                break;
            //
            // Rule 52:  MethodName ::= AmbiguousName . identifier
            //
            case 52: {
               //#line 283 "GJavaParser.g"
                setResult(
                    //#line 283 GJavaParser.g
                    ast_pool.Next()=new MethodName(getLeftIToken(), getRightIToken(),
                                   //#line 283 GJavaParser.g
                                   (IAst*)getRhsSym(1),
                                   //#line 283 GJavaParser.g
                                   ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                   //#line 283 GJavaParser.g
                                   (IAst*)getRhsSym(3))
                //#line 283 GJavaParser.g
                );
            break;
            }
            //
            // Rule 53:  PackageOrTypeName ::= identifier
            //
            case 53:
                break;
            //
            // Rule 54:  PackageOrTypeName ::= PackageOrTypeName . identifier
            //
            case 54: {
               //#line 286 "GJavaParser.g"
                setResult(
                    //#line 286 GJavaParser.g
                    ast_pool.Next()=new PackageOrTypeName(getLeftIToken(), getRightIToken(),
                                          //#line 286 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 286 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 286 GJavaParser.g
                                          (IAst*)getRhsSym(3))
                //#line 286 GJavaParser.g
                );
            break;
            }
            //
            // Rule 55:  AmbiguousName ::= identifier
            //
            case 55:
                break;
            //
            // Rule 56:  AmbiguousName ::= AmbiguousName . identifier
            //
            case 56: {
               //#line 289 "GJavaParser.g"
                setResult(
                    //#line 289 GJavaParser.g
                    ast_pool.Next()=new AmbiguousName(getLeftIToken(), getRightIToken(),
                                      //#line 289 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 289 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                      //#line 289 GJavaParser.g
                                      (IAst*)getRhsSym(3))
                //#line 289 GJavaParser.g
                );
            break;
            }
            //
            // Rule 57:  CompilationUnit ::= PackageDeclarationopt ImportDeclarationsopt TypeDeclarationsopt
            //
            case 57: {
               //#line 293 "GJavaParser.g"
                setResult(
                    //#line 293 GJavaParser.g
                    ast_pool.Next()=new CompilationUnit(getLeftIToken(), getRightIToken(),
                                        //#line 293 GJavaParser.g
                                        (IAst*)getRhsSym(1),
                                        //#line 293 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 293 GJavaParser.g
                                        (IAst*)getRhsSym(3))
                //#line 293 GJavaParser.g
                );
            break;
            }
            //
            // Rule 58:  ImportDeclarations ::= ImportDeclaration
            //
            case 58:
                break;
            //
            // Rule 59:  ImportDeclarations ::= ImportDeclarations ImportDeclaration
            //
            case 59: {
               //#line 296 "GJavaParser.g"
                setResult(
                    //#line 296 GJavaParser.g
                    ast_pool.Next()=new ImportDeclarations(getLeftIToken(), getRightIToken(),
                                           //#line 296 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 296 GJavaParser.g
                                           (IAst*)getRhsSym(2))
                //#line 296 GJavaParser.g
                );
            break;
            }
            //
            // Rule 60:  TypeDeclarations ::= TypeDeclaration
            //
            case 60:
                break;
            //
            // Rule 61:  TypeDeclarations ::= TypeDeclarations TypeDeclaration
            //
            case 61: {
               //#line 299 "GJavaParser.g"
                setResult(
                    //#line 299 GJavaParser.g
                    ast_pool.Next()=new TypeDeclarations(getLeftIToken(), getRightIToken(),
                                         //#line 299 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 299 GJavaParser.g
                                         (IAst*)getRhsSym(2))
                //#line 299 GJavaParser.g
                );
            break;
            }
            //
            // Rule 62:  PackageDeclaration ::= Annotationsopt package PackageName ;
            //
            case 62: {
               //#line 301 "GJavaParser.g"
                setResult(
                    //#line 301 GJavaParser.g
                    ast_pool.Next()=new PackageDeclaration(getLeftIToken(), getRightIToken(),
                                           //#line 301 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 301 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                           //#line 301 GJavaParser.g
                                           (IAst*)getRhsSym(3),
                                           //#line 301 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 301 GJavaParser.g
                );
            break;
            }
            //
            // Rule 63:  ImportDeclaration ::= SingleTypeImportDeclaration
            //
            case 63:
                break;
            //
            // Rule 64:  ImportDeclaration ::= TypeImportOnDemandDeclaration
            //
            case 64:
                break;
            //
            // Rule 65:  ImportDeclaration ::= SingleStaticImportDeclaration
            //
            case 65:
                break;
            //
            // Rule 66:  ImportDeclaration ::= StaticImportOnDemandDeclaration
            //
            case 66:
                break;
            //
            // Rule 67:  SingleTypeImportDeclaration ::= import TypeName ;
            //
            case 67: {
               //#line 308 "GJavaParser.g"
                setResult(
                    //#line 308 GJavaParser.g
                    ast_pool.Next()=new SingleTypeImportDeclaration(getLeftIToken(), getRightIToken(),
                                                    //#line 308 GJavaParser.g
                                                    ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                    //#line 308 GJavaParser.g
                                                    (IAst*)getRhsSym(2),
                                                    //#line 308 GJavaParser.g
                                                    ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 308 GJavaParser.g
                );
            break;
            }
            //
            // Rule 68:  TypeImportOnDemandDeclaration ::= import PackageOrTypeName . * ;
            //
            case 68: {
               //#line 310 "GJavaParser.g"
                setResult(
                    //#line 310 GJavaParser.g
                    ast_pool.Next()=new TypeImportOnDemandDeclaration(getLeftIToken(), getRightIToken(),
                                                      //#line 310 GJavaParser.g
                                                      ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                      //#line 310 GJavaParser.g
                                                      (IAst*)getRhsSym(2),
                                                      //#line 310 GJavaParser.g
                                                      ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                                      //#line 310 GJavaParser.g
                                                      ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                                      //#line 310 GJavaParser.g
                                                      ast_pool.Next()=new AstToken(getRhsIToken(5)))
                //#line 310 GJavaParser.g
                );
            break;
            }
            //
            // Rule 69:  SingleStaticImportDeclaration ::= import static TypeName . identifier ;
            //
            case 69: {
               //#line 312 "GJavaParser.g"
                setResult(
                    //#line 312 GJavaParser.g
                    ast_pool.Next()=new SingleStaticImportDeclaration(getLeftIToken(), getRightIToken(),
                                                      //#line 312 GJavaParser.g
                                                      ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                      //#line 312 GJavaParser.g
                                                      ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                      //#line 312 GJavaParser.g
                                                      (IAst*)getRhsSym(3),
                                                      //#line 312 GJavaParser.g
                                                      ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                                      //#line 312 GJavaParser.g
                                                      (IAst*)getRhsSym(5),
                                                      //#line 312 GJavaParser.g
                                                      ast_pool.Next()=new AstToken(getRhsIToken(6)))
                //#line 312 GJavaParser.g
                );
            break;
            }
            //
            // Rule 70:  StaticImportOnDemandDeclaration ::= import static TypeName . * ;
            //
            case 70: {
               //#line 314 "GJavaParser.g"
                setResult(
                    //#line 314 GJavaParser.g
                    ast_pool.Next()=new StaticImportOnDemandDeclaration(getLeftIToken(), getRightIToken(),
                                                        //#line 314 GJavaParser.g
                                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                        //#line 314 GJavaParser.g
                                                        ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                        //#line 314 GJavaParser.g
                                                        (IAst*)getRhsSym(3),
                                                        //#line 314 GJavaParser.g
                                                        ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                                        //#line 314 GJavaParser.g
                                                        ast_pool.Next()=new AstToken(getRhsIToken(5)),
                                                        //#line 314 GJavaParser.g
                                                        ast_pool.Next()=new AstToken(getRhsIToken(6)))
                //#line 314 GJavaParser.g
                );
            break;
            }
            //
            // Rule 71:  TypeDeclaration ::= ClassDeclaration
            //
            case 71:
                break;
            //
            // Rule 72:  TypeDeclaration ::= InterfaceDeclaration
            //
            case 72:
                break;
            //
            // Rule 73:  TypeDeclaration ::= ;
            //
            case 73: {
               //#line 318 "GJavaParser.g"
                setResult(
                    //#line 318 GJavaParser.g
                    ast_pool.Next()=new TypeDeclaration(getRhsIToken(1))
                //#line 318 GJavaParser.g
                );
            break;
            }
            //
            // Rule 74:  ClassDeclaration ::= NormalClassDeclaration
            //
            case 74:
                break;
            //
            // Rule 75:  ClassDeclaration ::= EnumDeclaration
            //
            case 75:
                break;
            //
            // Rule 76:  NormalClassDeclaration ::= ClassModifiersopt class identifier TypeParametersopt Superopt Interfacesopt ClassBody
            //
            case 76: {
               //#line 325 "GJavaParser.g"
                setResult(
                    //#line 325 GJavaParser.g
                    ast_pool.Next()=new NormalClassDeclaration(getLeftIToken(), getRightIToken(),
                                               //#line 325 GJavaParser.g
                                               (IAst*)getRhsSym(1),
                                               //#line 325 GJavaParser.g
                                               ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                               //#line 325 GJavaParser.g
                                               (IAst*)getRhsSym(3),
                                               //#line 325 GJavaParser.g
                                               (IAst*)getRhsSym(4),
                                               //#line 325 GJavaParser.g
                                               (IAst*)getRhsSym(5),
                                               //#line 325 GJavaParser.g
                                               (IAst*)getRhsSym(6),
                                               //#line 325 GJavaParser.g
                                               (IAst*)getRhsSym(7))
                //#line 325 GJavaParser.g
                );
            break;
            }
            //
            // Rule 77:  ClassModifiers ::= ClassModifier
            //
            case 77:
                break;
            //
            // Rule 78:  ClassModifiers ::= ClassModifiers ClassModifier
            //
            case 78: {
               //#line 328 "GJavaParser.g"
                setResult(
                    //#line 328 GJavaParser.g
                    ast_pool.Next()=new ClassModifiers(getLeftIToken(), getRightIToken(),
                                       //#line 328 GJavaParser.g
                                       (IAst*)getRhsSym(1),
                                       //#line 328 GJavaParser.g
                                       (IAst*)getRhsSym(2))
                //#line 328 GJavaParser.g
                );
            break;
            }
            //
            // Rule 79:  ClassModifier ::= Annotation
            //
            case 79:
                break;
            //
            // Rule 80:  ClassModifier ::= public
            //
            case 80: {
               //#line 331 "GJavaParser.g"
                setResult(
                    //#line 331 GJavaParser.g
                    ast_pool.Next()=new ClassModifier0(getRhsIToken(1))
                //#line 331 GJavaParser.g
                );
            break;
            }
            //
            // Rule 81:  ClassModifier ::= protected
            //
            case 81: {
               //#line 332 "GJavaParser.g"
                setResult(
                    //#line 332 GJavaParser.g
                    ast_pool.Next()=new ClassModifier1(getRhsIToken(1))
                //#line 332 GJavaParser.g
                );
            break;
            }
            //
            // Rule 82:  ClassModifier ::= private
            //
            case 82: {
               //#line 333 "GJavaParser.g"
                setResult(
                    //#line 333 GJavaParser.g
                    ast_pool.Next()=new ClassModifier2(getRhsIToken(1))
                //#line 333 GJavaParser.g
                );
            break;
            }
            //
            // Rule 83:  ClassModifier ::= abstract
            //
            case 83: {
               //#line 334 "GJavaParser.g"
                setResult(
                    //#line 334 GJavaParser.g
                    ast_pool.Next()=new ClassModifier3(getRhsIToken(1))
                //#line 334 GJavaParser.g
                );
            break;
            }
            //
            // Rule 84:  ClassModifier ::= static
            //
            case 84: {
               //#line 335 "GJavaParser.g"
                setResult(
                    //#line 335 GJavaParser.g
                    ast_pool.Next()=new ClassModifier4(getRhsIToken(1))
                //#line 335 GJavaParser.g
                );
            break;
            }
            //
            // Rule 85:  ClassModifier ::= final
            //
            case 85: {
               //#line 336 "GJavaParser.g"
                setResult(
                    //#line 336 GJavaParser.g
                    ast_pool.Next()=new ClassModifier5(getRhsIToken(1))
                //#line 336 GJavaParser.g
                );
            break;
            }
            //
            // Rule 86:  ClassModifier ::= strictfp
            //
            case 86: {
               //#line 337 "GJavaParser.g"
                setResult(
                    //#line 337 GJavaParser.g
                    ast_pool.Next()=new ClassModifier6(getRhsIToken(1))
                //#line 337 GJavaParser.g
                );
            break;
            }
            //
            // Rule 87:  TypeParameters ::= < TypeParameterList >
            //
            case 87: {
               //#line 339 "GJavaParser.g"
                setResult(
                    //#line 339 GJavaParser.g
                    ast_pool.Next()=new TypeParameters(getLeftIToken(), getRightIToken(),
                                       //#line 339 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                       //#line 339 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 339 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 339 GJavaParser.g
                );
            break;
            }
            //
            // Rule 88:  TypeParameterList ::= TypeParameter
            //
            case 88:
                break;
            //
            // Rule 89:  TypeParameterList ::= TypeParameterList , TypeParameter
            //
            case 89: {
               //#line 342 "GJavaParser.g"
                setResult(
                    //#line 342 GJavaParser.g
                    ast_pool.Next()=new TypeParameterList(getLeftIToken(), getRightIToken(),
                                          //#line 342 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 342 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 342 GJavaParser.g
                                          (IAst*)getRhsSym(3))
                //#line 342 GJavaParser.g
                );
            break;
            }
            //
            // Rule 90:  Super ::= extends ClassType
            //
            case 90: {
               //#line 344 "GJavaParser.g"
                setResult(
                    //#line 344 GJavaParser.g
                    ast_pool.Next()=new Super(getLeftIToken(), getRightIToken(),
                              //#line 344 GJavaParser.g
                              ast_pool.Next()=new AstToken(getRhsIToken(1)),
                              //#line 344 GJavaParser.g
                              (IAst*)getRhsSym(2))
                //#line 344 GJavaParser.g
                );
            break;
            }
            //
            // Rule 91:  Interfaces ::= implements InterfaceTypeList
            //
            case 91: {
               //#line 351 "GJavaParser.g"
                setResult(
                    //#line 351 GJavaParser.g
                    ast_pool.Next()=new Interfaces(getLeftIToken(), getRightIToken(),
                                   //#line 351 GJavaParser.g
                                   ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                   //#line 351 GJavaParser.g
                                   (IAst*)getRhsSym(2))
                //#line 351 GJavaParser.g
                );
            break;
            }
            //
            // Rule 92:  InterfaceTypeList ::= InterfaceType
            //
            case 92:
                break;
            //
            // Rule 93:  InterfaceTypeList ::= InterfaceTypeList , InterfaceType
            //
            case 93: {
               //#line 354 "GJavaParser.g"
                setResult(
                    //#line 354 GJavaParser.g
                    ast_pool.Next()=new InterfaceTypeList(getLeftIToken(), getRightIToken(),
                                          //#line 354 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 354 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 354 GJavaParser.g
                                          (IAst*)getRhsSym(3))
                //#line 354 GJavaParser.g
                );
            break;
            }
            //
            // Rule 94:  ClassBody ::= { ClassBodyDeclarationsopt }
            //
            case 94: {
               //#line 361 "GJavaParser.g"
                setResult(
                    //#line 361 GJavaParser.g
                    ast_pool.Next()=new ClassBody(getLeftIToken(), getRightIToken(),
                                  //#line 361 GJavaParser.g
                                  ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                  //#line 361 GJavaParser.g
                                  (IAst*)getRhsSym(2),
                                  //#line 361 GJavaParser.g
                                  ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 361 GJavaParser.g
                );
            break;
            }
            //
            // Rule 95:  ClassBodyDeclarations ::= ClassBodyDeclaration
            //
            case 95:
                break;
            //
            // Rule 96:  ClassBodyDeclarations ::= ClassBodyDeclarations ClassBodyDeclaration
            //
            case 96: {
               //#line 364 "GJavaParser.g"
                setResult(
                    //#line 364 GJavaParser.g
                    ast_pool.Next()=new ClassBodyDeclarations(getLeftIToken(), getRightIToken(),
                                              //#line 364 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 364 GJavaParser.g
                                              (IAst*)getRhsSym(2))
                //#line 364 GJavaParser.g
                );
            break;
            }
            //
            // Rule 97:  ClassBodyDeclaration ::= ClassMemberDeclaration
            //
            case 97:
                break;
            //
            // Rule 98:  ClassBodyDeclaration ::= InstanceInitializer
            //
            case 98:
                break;
            //
            // Rule 99:  ClassBodyDeclaration ::= StaticInitializer
            //
            case 99:
                break;
            //
            // Rule 100:  ClassBodyDeclaration ::= ConstructorDeclaration
            //
            case 100:
                break;
            //
            // Rule 101:  ClassMemberDeclaration ::= FieldDeclaration
            //
            case 101:
                break;
            //
            // Rule 102:  ClassMemberDeclaration ::= MethodDeclaration
            //
            case 102:
                break;
            //
            // Rule 103:  ClassMemberDeclaration ::= ClassDeclaration
            //
            case 103:
                break;
            //
            // Rule 104:  ClassMemberDeclaration ::= InterfaceDeclaration
            //
            case 104:
                break;
            //
            // Rule 105:  ClassMemberDeclaration ::= ;
            //
            case 105: {
               //#line 375 "GJavaParser.g"
                setResult(
                    //#line 375 GJavaParser.g
                    ast_pool.Next()=new ClassMemberDeclaration(getRhsIToken(1))
                //#line 375 GJavaParser.g
                );
            break;
            }
            //
            // Rule 106:  FieldDeclaration ::= FieldModifiersopt Type VariableDeclarators ;
            //
            case 106: {
               //#line 377 "GJavaParser.g"
                setResult(
                    //#line 377 GJavaParser.g
                    ast_pool.Next()=new FieldDeclaration(getLeftIToken(), getRightIToken(),
                                         //#line 377 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 377 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 377 GJavaParser.g
                                         (IAst*)getRhsSym(3),
                                         //#line 377 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 377 GJavaParser.g
                );
            break;
            }
            //
            // Rule 107:  VariableDeclarators ::= VariableDeclarator
            //
            case 107:
                break;
            //
            // Rule 108:  VariableDeclarators ::= VariableDeclarators , VariableDeclarator
            //
            case 108: {
               //#line 380 "GJavaParser.g"
                setResult(
                    //#line 380 GJavaParser.g
                    ast_pool.Next()=new VariableDeclarators(getLeftIToken(), getRightIToken(),
                                            //#line 380 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 380 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                            //#line 380 GJavaParser.g
                                            (IAst*)getRhsSym(3))
                //#line 380 GJavaParser.g
                );
            break;
            }
            //
            // Rule 109:  VariableDeclarator ::= VariableDeclaratorId
            //
            case 109:
                break;
            //
            // Rule 110:  VariableDeclarator ::= VariableDeclaratorId = VariableInitializer
            //
            case 110: {
               //#line 383 "GJavaParser.g"
                setResult(
                    //#line 383 GJavaParser.g
                    ast_pool.Next()=new VariableDeclarator(getLeftIToken(), getRightIToken(),
                                           //#line 383 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 383 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                           //#line 383 GJavaParser.g
                                           (IAst*)getRhsSym(3))
                //#line 383 GJavaParser.g
                );
            break;
            }
            //
            // Rule 111:  VariableDeclaratorId ::= identifier
            //
            case 111:
                break;
            //
            // Rule 112:  VariableDeclaratorId ::= VariableDeclaratorId [ ]
            //
            case 112: {
               //#line 386 "GJavaParser.g"
                setResult(
                    //#line 386 GJavaParser.g
                    ast_pool.Next()=new VariableDeclaratorId(getLeftIToken(), getRightIToken(),
                                             //#line 386 GJavaParser.g
                                             (IAst*)getRhsSym(1),
                                             //#line 386 GJavaParser.g
                                             ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                             //#line 386 GJavaParser.g
                                             ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 386 GJavaParser.g
                );
            break;
            }
            //
            // Rule 113:  VariableInitializer ::= Expression
            //
            case 113:
                break;
            //
            // Rule 114:  VariableInitializer ::= ArrayInitializer
            //
            case 114:
                break;
            //
            // Rule 115:  FieldModifiers ::= FieldModifier
            //
            case 115:
                break;
            //
            // Rule 116:  FieldModifiers ::= FieldModifiers FieldModifier
            //
            case 116: {
               //#line 392 "GJavaParser.g"
                setResult(
                    //#line 392 GJavaParser.g
                    ast_pool.Next()=new FieldModifiers(getLeftIToken(), getRightIToken(),
                                       //#line 392 GJavaParser.g
                                       (IAst*)getRhsSym(1),
                                       //#line 392 GJavaParser.g
                                       (IAst*)getRhsSym(2))
                //#line 392 GJavaParser.g
                );
            break;
            }
            //
            // Rule 117:  FieldModifier ::= Annotation
            //
            case 117:
                break;
            //
            // Rule 118:  FieldModifier ::= public
            //
            case 118: {
               //#line 395 "GJavaParser.g"
                setResult(
                    //#line 395 GJavaParser.g
                    ast_pool.Next()=new FieldModifier0(getRhsIToken(1))
                //#line 395 GJavaParser.g
                );
            break;
            }
            //
            // Rule 119:  FieldModifier ::= protected
            //
            case 119: {
               //#line 396 "GJavaParser.g"
                setResult(
                    //#line 396 GJavaParser.g
                    ast_pool.Next()=new FieldModifier1(getRhsIToken(1))
                //#line 396 GJavaParser.g
                );
            break;
            }
            //
            // Rule 120:  FieldModifier ::= private
            //
            case 120: {
               //#line 397 "GJavaParser.g"
                setResult(
                    //#line 397 GJavaParser.g
                    ast_pool.Next()=new FieldModifier2(getRhsIToken(1))
                //#line 397 GJavaParser.g
                );
            break;
            }
            //
            // Rule 121:  FieldModifier ::= static
            //
            case 121: {
               //#line 398 "GJavaParser.g"
                setResult(
                    //#line 398 GJavaParser.g
                    ast_pool.Next()=new FieldModifier3(getRhsIToken(1))
                //#line 398 GJavaParser.g
                );
            break;
            }
            //
            // Rule 122:  FieldModifier ::= final
            //
            case 122: {
               //#line 399 "GJavaParser.g"
                setResult(
                    //#line 399 GJavaParser.g
                    ast_pool.Next()=new FieldModifier4(getRhsIToken(1))
                //#line 399 GJavaParser.g
                );
            break;
            }
            //
            // Rule 123:  FieldModifier ::= transient
            //
            case 123: {
               //#line 400 "GJavaParser.g"
                setResult(
                    //#line 400 GJavaParser.g
                    ast_pool.Next()=new FieldModifier5(getRhsIToken(1))
                //#line 400 GJavaParser.g
                );
            break;
            }
            //
            // Rule 124:  FieldModifier ::= volatile
            //
            case 124: {
               //#line 401 "GJavaParser.g"
                setResult(
                    //#line 401 GJavaParser.g
                    ast_pool.Next()=new FieldModifier6(getRhsIToken(1))
                //#line 401 GJavaParser.g
                );
            break;
            }
            //
            // Rule 125:  MethodDeclaration ::= MethodHeader MethodBody
            //
            case 125: {
               //#line 403 "GJavaParser.g"
                setResult(
                    //#line 403 GJavaParser.g
                    ast_pool.Next()=new MethodDeclaration(getLeftIToken(), getRightIToken(),
                                          //#line 403 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 403 GJavaParser.g
                                          (IAst*)getRhsSym(2))
                //#line 403 GJavaParser.g
                );
            break;
            }
            //
            // Rule 126:  MethodHeader ::= MethodModifiersopt TypeParametersopt ResultType MethodDeclarator Throwsopt
            //
            case 126: {
               //#line 405 "GJavaParser.g"
                setResult(
                    //#line 405 GJavaParser.g
                    ast_pool.Next()=new MethodHeader(getLeftIToken(), getRightIToken(),
                                     //#line 405 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 405 GJavaParser.g
                                     (IAst*)getRhsSym(2),
                                     //#line 405 GJavaParser.g
                                     (IAst*)getRhsSym(3),
                                     //#line 405 GJavaParser.g
                                     (IAst*)getRhsSym(4),
                                     //#line 405 GJavaParser.g
                                     (IAst*)getRhsSym(5))
                //#line 405 GJavaParser.g
                );
            break;
            }
            //
            // Rule 127:  ResultType ::= Type
            //
            case 127:
                break;
            //
            // Rule 128:  ResultType ::= void
            //
            case 128: {
               //#line 408 "GJavaParser.g"
                setResult(
                    //#line 408 GJavaParser.g
                    ast_pool.Next()=new ResultType(getRhsIToken(1))
                //#line 408 GJavaParser.g
                );
            break;
            }
            //
            // Rule 129:  MethodDeclarator ::= identifier ( FormalParameterListopt )
            //
            case 129: {
               //#line 410 "GJavaParser.g"
                setResult(
                    //#line 410 GJavaParser.g
                    ast_pool.Next()=new MethodDeclarator0(getLeftIToken(), getRightIToken(),
                                          //#line 410 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 410 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 410 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 410 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 410 GJavaParser.g
                );
            break;
            }
            //
            // Rule 130:  MethodDeclarator ::= MethodDeclarator [ ]
            //
            case 130: {
               //#line 412 "GJavaParser.g"
                setResult(
                    //#line 412 GJavaParser.g
                    ast_pool.Next()=new MethodDeclarator1(getLeftIToken(), getRightIToken(),
                                          //#line 412 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 412 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 412 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 412 GJavaParser.g
                );
            break;
            }
            //
            // Rule 131:  FormalParameterList ::= LastFormalParameter
            //
            case 131:
                break;
            //
            // Rule 132:  FormalParameterList ::= FormalParameters , LastFormalParameter
            //
            case 132: {
               //#line 415 "GJavaParser.g"
                setResult(
                    //#line 415 GJavaParser.g
                    ast_pool.Next()=new FormalParameterList(getLeftIToken(), getRightIToken(),
                                            //#line 415 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 415 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                            //#line 415 GJavaParser.g
                                            (IAst*)getRhsSym(3))
                //#line 415 GJavaParser.g
                );
            break;
            }
            //
            // Rule 133:  FormalParameters ::= FormalParameter
            //
            case 133:
                break;
            //
            // Rule 134:  FormalParameters ::= FormalParameters , FormalParameter
            //
            case 134: {
               //#line 418 "GJavaParser.g"
                setResult(
                    //#line 418 GJavaParser.g
                    ast_pool.Next()=new FormalParameters(getLeftIToken(), getRightIToken(),
                                         //#line 418 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 418 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                         //#line 418 GJavaParser.g
                                         (IAst*)getRhsSym(3))
                //#line 418 GJavaParser.g
                );
            break;
            }
            //
            // Rule 135:  FormalParameter ::= VariableModifiersopt Type VariableDeclaratorId
            //
            case 135: {
               //#line 420 "GJavaParser.g"
                setResult(
                    //#line 420 GJavaParser.g
                    ast_pool.Next()=new FormalParameter(getLeftIToken(), getRightIToken(),
                                        //#line 420 GJavaParser.g
                                        (IAst*)getRhsSym(1),
                                        //#line 420 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 420 GJavaParser.g
                                        (IAst*)getRhsSym(3))
                //#line 420 GJavaParser.g
                );
            break;
            }
            //
            // Rule 136:  VariableModifiers ::= VariableModifier
            //
            case 136:
                break;
            //
            // Rule 137:  VariableModifiers ::= VariableModifiers VariableModifier
            //
            case 137: {
               //#line 423 "GJavaParser.g"
                setResult(
                    //#line 423 GJavaParser.g
                    ast_pool.Next()=new VariableModifiers(getLeftIToken(), getRightIToken(),
                                          //#line 423 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 423 GJavaParser.g
                                          (IAst*)getRhsSym(2))
                //#line 423 GJavaParser.g
                );
            break;
            }
            //
            // Rule 138:  VariableModifier ::= final
            //
            case 138: {
               //#line 425 "GJavaParser.g"
                setResult(
                    //#line 425 GJavaParser.g
                    ast_pool.Next()=new VariableModifier(getRhsIToken(1))
                //#line 425 GJavaParser.g
                );
            break;
            }
            //
            // Rule 139:  VariableModifier ::= Annotations
            //
            case 139:
                break;
            //
            // Rule 140:  LastFormalParameter ::= VariableModifiersopt Type ...opt VariableDeclaratorId
            //
            case 140: {
               //#line 428 "GJavaParser.g"
                setResult(
                    //#line 428 GJavaParser.g
                    ast_pool.Next()=new LastFormalParameter(getLeftIToken(), getRightIToken(),
                                            //#line 428 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 428 GJavaParser.g
                                            (IAst*)getRhsSym(2),
                                            //#line 428 GJavaParser.g
                                            (IAst*)getRhsSym(3),
                                            //#line 428 GJavaParser.g
                                            (IAst*)getRhsSym(4))
                //#line 428 GJavaParser.g
                );
            break;
            }
            //
            // Rule 141:  MethodModifiers ::= MethodModifier
            //
            case 141:
                break;
            //
            // Rule 142:  MethodModifiers ::= MethodModifiers MethodModifier
            //
            case 142: {
               //#line 437 "GJavaParser.g"
                setResult(
                    //#line 437 GJavaParser.g
                    ast_pool.Next()=new MethodModifiers(getLeftIToken(), getRightIToken(),
                                        //#line 437 GJavaParser.g
                                        (IAst*)getRhsSym(1),
                                        //#line 437 GJavaParser.g
                                        (IAst*)getRhsSym(2))
                //#line 437 GJavaParser.g
                );
            break;
            }
            //
            // Rule 143:  MethodModifier ::= Annotations
            //
            case 143:
                break;
            //
            // Rule 144:  MethodModifier ::= public
            //
            case 144: {
               //#line 440 "GJavaParser.g"
                setResult(
                    //#line 440 GJavaParser.g
                    ast_pool.Next()=new MethodModifier0(getRhsIToken(1))
                //#line 440 GJavaParser.g
                );
            break;
            }
            //
            // Rule 145:  MethodModifier ::= protected
            //
            case 145: {
               //#line 441 "GJavaParser.g"
                setResult(
                    //#line 441 GJavaParser.g
                    ast_pool.Next()=new MethodModifier1(getRhsIToken(1))
                //#line 441 GJavaParser.g
                );
            break;
            }
            //
            // Rule 146:  MethodModifier ::= private
            //
            case 146: {
               //#line 442 "GJavaParser.g"
                setResult(
                    //#line 442 GJavaParser.g
                    ast_pool.Next()=new MethodModifier2(getRhsIToken(1))
                //#line 442 GJavaParser.g
                );
            break;
            }
            //
            // Rule 147:  MethodModifier ::= abstract
            //
            case 147: {
               //#line 443 "GJavaParser.g"
                setResult(
                    //#line 443 GJavaParser.g
                    ast_pool.Next()=new MethodModifier3(getRhsIToken(1))
                //#line 443 GJavaParser.g
                );
            break;
            }
            //
            // Rule 148:  MethodModifier ::= static
            //
            case 148: {
               //#line 444 "GJavaParser.g"
                setResult(
                    //#line 444 GJavaParser.g
                    ast_pool.Next()=new MethodModifier4(getRhsIToken(1))
                //#line 444 GJavaParser.g
                );
            break;
            }
            //
            // Rule 149:  MethodModifier ::= final
            //
            case 149: {
               //#line 445 "GJavaParser.g"
                setResult(
                    //#line 445 GJavaParser.g
                    ast_pool.Next()=new MethodModifier5(getRhsIToken(1))
                //#line 445 GJavaParser.g
                );
            break;
            }
            //
            // Rule 150:  MethodModifier ::= synchronized
            //
            case 150: {
               //#line 446 "GJavaParser.g"
                setResult(
                    //#line 446 GJavaParser.g
                    ast_pool.Next()=new MethodModifier6(getRhsIToken(1))
                //#line 446 GJavaParser.g
                );
            break;
            }
            //
            // Rule 151:  MethodModifier ::= native
            //
            case 151: {
               //#line 447 "GJavaParser.g"
                setResult(
                    //#line 447 GJavaParser.g
                    ast_pool.Next()=new MethodModifier7(getRhsIToken(1))
                //#line 447 GJavaParser.g
                );
            break;
            }
            //
            // Rule 152:  MethodModifier ::= strictfp
            //
            case 152: {
               //#line 448 "GJavaParser.g"
                setResult(
                    //#line 448 GJavaParser.g
                    ast_pool.Next()=new MethodModifier8(getRhsIToken(1))
                //#line 448 GJavaParser.g
                );
            break;
            }
            //
            // Rule 153:  Throws ::= throws ExceptionTypeList
            //
            case 153: {
               //#line 450 "GJavaParser.g"
                setResult(
                    //#line 450 GJavaParser.g
                    ast_pool.Next()=new Throws(getLeftIToken(), getRightIToken(),
                               //#line 450 GJavaParser.g
                               ast_pool.Next()=new AstToken(getRhsIToken(1)),
                               //#line 450 GJavaParser.g
                               (IAst*)getRhsSym(2))
                //#line 450 GJavaParser.g
                );
            break;
            }
            //
            // Rule 154:  ExceptionTypeList ::= ExceptionType
            //
            case 154:
                break;
            //
            // Rule 155:  ExceptionTypeList ::= ExceptionTypeList , ExceptionType
            //
            case 155: {
               //#line 453 "GJavaParser.g"
                setResult(
                    //#line 453 GJavaParser.g
                    ast_pool.Next()=new ExceptionTypeList(getLeftIToken(), getRightIToken(),
                                          //#line 453 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 453 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 453 GJavaParser.g
                                          (IAst*)getRhsSym(3))
                //#line 453 GJavaParser.g
                );
            break;
            }
            //
            // Rule 156:  ExceptionType ::= ClassType
            //
            case 156:
                break;
            //
            // Rule 157:  ExceptionType ::= TypeVariable
            //
            case 157:
                break;
            //
            // Rule 158:  MethodBody ::= Block
            //
            case 158:
                break;
            //
            // Rule 159:  MethodBody ::= ;
            //
            case 159: {
               //#line 459 "GJavaParser.g"
                setResult(
                    //#line 459 GJavaParser.g
                    ast_pool.Next()=new MethodBody(getRhsIToken(1))
                //#line 459 GJavaParser.g
                );
            break;
            }
            //
            // Rule 160:  InstanceInitializer ::= Block
            //
            case 160:
                break;
            //
            // Rule 161:  StaticInitializer ::= static Block
            //
            case 161: {
               //#line 463 "GJavaParser.g"
                setResult(
                    //#line 463 GJavaParser.g
                    ast_pool.Next()=new StaticInitializer(getLeftIToken(), getRightIToken(),
                                          //#line 463 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                          //#line 463 GJavaParser.g
                                          (IAst*)getRhsSym(2))
                //#line 463 GJavaParser.g
                );
            break;
            }
            //
            // Rule 162:  ConstructorDeclaration ::= ConstructorModifiersopt ConstructorDeclarator Throwsopt ConstructorBody
            //
            case 162: {
               //#line 465 "GJavaParser.g"
                setResult(
                    //#line 465 GJavaParser.g
                    ast_pool.Next()=new ConstructorDeclaration(getLeftIToken(), getRightIToken(),
                                               //#line 465 GJavaParser.g
                                               (IAst*)getRhsSym(1),
                                               //#line 465 GJavaParser.g
                                               (IAst*)getRhsSym(2),
                                               //#line 465 GJavaParser.g
                                               (IAst*)getRhsSym(3),
                                               //#line 465 GJavaParser.g
                                               (IAst*)getRhsSym(4))
                //#line 465 GJavaParser.g
                );
            break;
            }
            //
            // Rule 163:  ConstructorDeclarator ::= TypeParametersopt SimpleTypeName ( FormalParameterListopt )
            //
            case 163: {
               //#line 467 "GJavaParser.g"
                setResult(
                    //#line 467 GJavaParser.g
                    ast_pool.Next()=new ConstructorDeclarator(getLeftIToken(), getRightIToken(),
                                              //#line 467 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 467 GJavaParser.g
                                              (IAst*)getRhsSym(2),
                                              //#line 467 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                              //#line 467 GJavaParser.g
                                              (IAst*)getRhsSym(4),
                                              //#line 467 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(5)))
                //#line 467 GJavaParser.g
                );
            break;
            }
            //
            // Rule 164:  SimpleTypeName ::= identifier
            //
            case 164:
                break;
            //
            // Rule 165:  ConstructorModifiers ::= ConstructorModifier
            //
            case 165:
                break;
            //
            // Rule 166:  ConstructorModifiers ::= ConstructorModifiers ConstructorModifier
            //
            case 166: {
               //#line 472 "GJavaParser.g"
                setResult(
                    //#line 472 GJavaParser.g
                    ast_pool.Next()=new ConstructorModifiers(getLeftIToken(), getRightIToken(),
                                             //#line 472 GJavaParser.g
                                             (IAst*)getRhsSym(1),
                                             //#line 472 GJavaParser.g
                                             (IAst*)getRhsSym(2))
                //#line 472 GJavaParser.g
                );
            break;
            }
            //
            // Rule 167:  ConstructorModifier ::= Annotations
            //
            case 167:
                break;
            //
            // Rule 168:  ConstructorModifier ::= public
            //
            case 168: {
               //#line 475 "GJavaParser.g"
                setResult(
                    //#line 475 GJavaParser.g
                    ast_pool.Next()=new ConstructorModifier0(getRhsIToken(1))
                //#line 475 GJavaParser.g
                );
            break;
            }
            //
            // Rule 169:  ConstructorModifier ::= protected
            //
            case 169: {
               //#line 476 "GJavaParser.g"
                setResult(
                    //#line 476 GJavaParser.g
                    ast_pool.Next()=new ConstructorModifier1(getRhsIToken(1))
                //#line 476 GJavaParser.g
                );
            break;
            }
            //
            // Rule 170:  ConstructorModifier ::= private
            //
            case 170: {
               //#line 477 "GJavaParser.g"
                setResult(
                    //#line 477 GJavaParser.g
                    ast_pool.Next()=new ConstructorModifier2(getRhsIToken(1))
                //#line 477 GJavaParser.g
                );
            break;
            }
            //
            // Rule 171:  ConstructorBody ::= { ExplicitConstructorInvocationopt BlockStatementsopt }
            //
            case 171: {
               //#line 479 "GJavaParser.g"
                setResult(
                    //#line 479 GJavaParser.g
                    ast_pool.Next()=new ConstructorBody(getLeftIToken(), getRightIToken(),
                                        //#line 479 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                        //#line 479 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 479 GJavaParser.g
                                        (IAst*)getRhsSym(3),
                                        //#line 479 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 479 GJavaParser.g
                );
            break;
            }
            //
            // Rule 172:  ExplicitConstructorInvocation ::= TypeArgumentsopt this ( ArgumentListopt ) ;
            //
            case 172: {
               //#line 481 "GJavaParser.g"
                setResult(
                    //#line 481 GJavaParser.g
                    ast_pool.Next()=new ExplicitConstructorInvocation0(getLeftIToken(), getRightIToken(),
                                                       //#line 481 GJavaParser.g
                                                       (IAst*)getRhsSym(1),
                                                       //#line 481 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                       //#line 481 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                                       //#line 481 GJavaParser.g
                                                       (IAst*)getRhsSym(4),
                                                       //#line 481 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(5)),
                                                       //#line 481 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(6)))
                //#line 481 GJavaParser.g
                );
            break;
            }
            //
            // Rule 173:  ExplicitConstructorInvocation ::= TypeArgumentsopt super ( ArgumentListopt ) ;
            //
            case 173: {
               //#line 482 "GJavaParser.g"
                setResult(
                    //#line 482 GJavaParser.g
                    ast_pool.Next()=new ExplicitConstructorInvocation1(getLeftIToken(), getRightIToken(),
                                                       //#line 482 GJavaParser.g
                                                       (IAst*)getRhsSym(1),
                                                       //#line 482 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                       //#line 482 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                                       //#line 482 GJavaParser.g
                                                       (IAst*)getRhsSym(4),
                                                       //#line 482 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(5)),
                                                       //#line 482 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(6)))
                //#line 482 GJavaParser.g
                );
            break;
            }
            //
            // Rule 174:  ExplicitConstructorInvocation ::= Primary . TypeArgumentsopt super ( ArgumentListopt ) ;
            //
            case 174: {
               //#line 483 "GJavaParser.g"
                setResult(
                    //#line 483 GJavaParser.g
                    ast_pool.Next()=new ExplicitConstructorInvocation2(getLeftIToken(), getRightIToken(),
                                                       //#line 483 GJavaParser.g
                                                       (IAst*)getRhsSym(1),
                                                       //#line 483 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                       //#line 483 GJavaParser.g
                                                       (IAst*)getRhsSym(3),
                                                       //#line 483 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                                       //#line 483 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(5)),
                                                       //#line 483 GJavaParser.g
                                                       (IAst*)getRhsSym(6),
                                                       //#line 483 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(7)),
                                                       //#line 483 GJavaParser.g
                                                       ast_pool.Next()=new AstToken(getRhsIToken(8)))
                //#line 483 GJavaParser.g
                );
            break;
            }
            //
            // Rule 175:  EnumDeclaration ::= ClassModifiersopt enum identifier Interfacesopt EnumBody
            //
            case 175: {
               //#line 485 "GJavaParser.g"
                setResult(
                    //#line 485 GJavaParser.g
                    ast_pool.Next()=new EnumDeclaration(getLeftIToken(), getRightIToken(),
                                        //#line 485 GJavaParser.g
                                        (IAst*)getRhsSym(1),
                                        //#line 485 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                        //#line 485 GJavaParser.g
                                        (IAst*)getRhsSym(3),
                                        //#line 485 GJavaParser.g
                                        (IAst*)getRhsSym(4),
                                        //#line 485 GJavaParser.g
                                        (IAst*)getRhsSym(5))
                //#line 485 GJavaParser.g
                );
            break;
            }
            //
            // Rule 176:  EnumBody ::= { EnumConstantsopt ,opt EnumBodyDeclarationsopt }
            //
            case 176: {
               //#line 487 "GJavaParser.g"
                setResult(
                    //#line 487 GJavaParser.g
                    ast_pool.Next()=new EnumBody(getLeftIToken(), getRightIToken(),
                                 //#line 487 GJavaParser.g
                                 ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                 //#line 487 GJavaParser.g
                                 (IAst*)getRhsSym(2),
                                 //#line 487 GJavaParser.g
                                 (IAst*)getRhsSym(3),
                                 //#line 487 GJavaParser.g
                                 (IAst*)getRhsSym(4),
                                 //#line 487 GJavaParser.g
                                 ast_pool.Next()=new AstToken(getRhsIToken(5)))
                //#line 487 GJavaParser.g
                );
            break;
            }
            //
            // Rule 177:  EnumConstants ::= EnumConstant
            //
            case 177:
                break;
            //
            // Rule 178:  EnumConstants ::= EnumConstants , EnumConstant
            //
            case 178: {
               //#line 490 "GJavaParser.g"
                setResult(
                    //#line 490 GJavaParser.g
                    ast_pool.Next()=new EnumConstants(getLeftIToken(), getRightIToken(),
                                      //#line 490 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 490 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                      //#line 490 GJavaParser.g
                                      (IAst*)getRhsSym(3))
                //#line 490 GJavaParser.g
                );
            break;
            }
            //
            // Rule 179:  EnumConstant ::= Annotationsopt identifier Argumentsopt ClassBodyopt
            //
            case 179: {
               //#line 492 "GJavaParser.g"
                setResult(
                    //#line 492 GJavaParser.g
                    ast_pool.Next()=new EnumConstant(getLeftIToken(), getRightIToken(),
                                     //#line 492 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 492 GJavaParser.g
                                     (IAst*)getRhsSym(2),
                                     //#line 492 GJavaParser.g
                                     (IAst*)getRhsSym(3),
                                     //#line 492 GJavaParser.g
                                     (IAst*)getRhsSym(4))
                //#line 492 GJavaParser.g
                );
            break;
            }
            //
            // Rule 180:  Arguments ::= ( ArgumentListopt )
            //
            case 180: {
               //#line 494 "GJavaParser.g"
                setResult(
                    //#line 494 GJavaParser.g
                    ast_pool.Next()=new Arguments(getLeftIToken(), getRightIToken(),
                                  //#line 494 GJavaParser.g
                                  ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                  //#line 494 GJavaParser.g
                                  (IAst*)getRhsSym(2),
                                  //#line 494 GJavaParser.g
                                  ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 494 GJavaParser.g
                );
            break;
            }
            //
            // Rule 181:  EnumBodyDeclarations ::= ; ClassBodyDeclarationsopt
            //
            case 181: {
               //#line 496 "GJavaParser.g"
                setResult(
                    //#line 496 GJavaParser.g
                    ast_pool.Next()=new EnumBodyDeclarations(getLeftIToken(), getRightIToken(),
                                             //#line 496 GJavaParser.g
                                             ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                             //#line 496 GJavaParser.g
                                             (IAst*)getRhsSym(2))
                //#line 496 GJavaParser.g
                );
            break;
            }
            //
            // Rule 182:  InterfaceDeclaration ::= NormalInterfaceDeclaration
            //
            case 182:
                break;
            //
            // Rule 183:  InterfaceDeclaration ::= AnnotationTypeDeclaration
            //
            case 183:
                break;
            //
            // Rule 184:  NormalInterfaceDeclaration ::= InterfaceModifiersopt interface identifier TypeParametersopt ExtendsInterfacesopt InterfaceBody
            //
            case 184: {
               //#line 503 "GJavaParser.g"
                setResult(
                    //#line 503 GJavaParser.g
                    ast_pool.Next()=new NormalInterfaceDeclaration(getLeftIToken(), getRightIToken(),
                                                   //#line 503 GJavaParser.g
                                                   (IAst*)getRhsSym(1),
                                                   //#line 503 GJavaParser.g
                                                   ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                   //#line 503 GJavaParser.g
                                                   (IAst*)getRhsSym(3),
                                                   //#line 503 GJavaParser.g
                                                   (IAst*)getRhsSym(4),
                                                   //#line 503 GJavaParser.g
                                                   (IAst*)getRhsSym(5),
                                                   //#line 503 GJavaParser.g
                                                   (IAst*)getRhsSym(6))
                //#line 503 GJavaParser.g
                );
            break;
            }
            //
            // Rule 185:  InterfaceModifiers ::= InterfaceModifier
            //
            case 185:
                break;
            //
            // Rule 186:  InterfaceModifiers ::= InterfaceModifiers InterfaceModifier
            //
            case 186: {
               //#line 506 "GJavaParser.g"
                setResult(
                    //#line 506 GJavaParser.g
                    ast_pool.Next()=new InterfaceModifiers(getLeftIToken(), getRightIToken(),
                                           //#line 506 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 506 GJavaParser.g
                                           (IAst*)getRhsSym(2))
                //#line 506 GJavaParser.g
                );
            break;
            }
            //
            // Rule 187:  InterfaceModifier ::= Annotation
            //
            case 187:
                break;
            //
            // Rule 188:  InterfaceModifier ::= public
            //
            case 188: {
               //#line 509 "GJavaParser.g"
                setResult(
                    //#line 509 GJavaParser.g
                    ast_pool.Next()=new InterfaceModifier0(getRhsIToken(1))
                //#line 509 GJavaParser.g
                );
            break;
            }
            //
            // Rule 189:  InterfaceModifier ::= protected
            //
            case 189: {
               //#line 510 "GJavaParser.g"
                setResult(
                    //#line 510 GJavaParser.g
                    ast_pool.Next()=new InterfaceModifier1(getRhsIToken(1))
                //#line 510 GJavaParser.g
                );
            break;
            }
            //
            // Rule 190:  InterfaceModifier ::= private
            //
            case 190: {
               //#line 511 "GJavaParser.g"
                setResult(
                    //#line 511 GJavaParser.g
                    ast_pool.Next()=new InterfaceModifier2(getRhsIToken(1))
                //#line 511 GJavaParser.g
                );
            break;
            }
            //
            // Rule 191:  InterfaceModifier ::= abstract
            //
            case 191: {
               //#line 512 "GJavaParser.g"
                setResult(
                    //#line 512 GJavaParser.g
                    ast_pool.Next()=new InterfaceModifier3(getRhsIToken(1))
                //#line 512 GJavaParser.g
                );
            break;
            }
            //
            // Rule 192:  InterfaceModifier ::= static
            //
            case 192: {
               //#line 513 "GJavaParser.g"
                setResult(
                    //#line 513 GJavaParser.g
                    ast_pool.Next()=new InterfaceModifier4(getRhsIToken(1))
                //#line 513 GJavaParser.g
                );
            break;
            }
            //
            // Rule 193:  InterfaceModifier ::= strictfp
            //
            case 193: {
               //#line 514 "GJavaParser.g"
                setResult(
                    //#line 514 GJavaParser.g
                    ast_pool.Next()=new InterfaceModifier5(getRhsIToken(1))
                //#line 514 GJavaParser.g
                );
            break;
            }
            //
            // Rule 194:  ExtendsInterfaces ::= extends InterfaceType
            //
            case 194: {
               //#line 516 "GJavaParser.g"
                setResult(
                    //#line 516 GJavaParser.g
                    ast_pool.Next()=new ExtendsInterfaces0(getLeftIToken(), getRightIToken(),
                                           //#line 516 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                           //#line 516 GJavaParser.g
                                           (IAst*)getRhsSym(2))
                //#line 516 GJavaParser.g
                );
            break;
            }
            //
            // Rule 195:  ExtendsInterfaces ::= ExtendsInterfaces , InterfaceType
            //
            case 195: {
               //#line 517 "GJavaParser.g"
                setResult(
                    //#line 517 GJavaParser.g
                    ast_pool.Next()=new ExtendsInterfaces1(getLeftIToken(), getRightIToken(),
                                           //#line 517 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 517 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                           //#line 517 GJavaParser.g
                                           (IAst*)getRhsSym(3))
                //#line 517 GJavaParser.g
                );
            break;
            }
            //
            // Rule 196:  InterfaceBody ::= { InterfaceMemberDeclarationsopt }
            //
            case 196: {
               //#line 524 "GJavaParser.g"
                setResult(
                    //#line 524 GJavaParser.g
                    ast_pool.Next()=new InterfaceBody(getLeftIToken(), getRightIToken(),
                                      //#line 524 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                      //#line 524 GJavaParser.g
                                      (IAst*)getRhsSym(2),
                                      //#line 524 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 524 GJavaParser.g
                );
            break;
            }
            //
            // Rule 197:  InterfaceMemberDeclarations ::= InterfaceMemberDeclaration
            //
            case 197:
                break;
            //
            // Rule 198:  InterfaceMemberDeclarations ::= InterfaceMemberDeclarations InterfaceMemberDeclaration
            //
            case 198: {
               //#line 527 "GJavaParser.g"
                setResult(
                    //#line 527 GJavaParser.g
                    ast_pool.Next()=new InterfaceMemberDeclarations(getLeftIToken(), getRightIToken(),
                                                    //#line 527 GJavaParser.g
                                                    (IAst*)getRhsSym(1),
                                                    //#line 527 GJavaParser.g
                                                    (IAst*)getRhsSym(2))
                //#line 527 GJavaParser.g
                );
            break;
            }
            //
            // Rule 199:  InterfaceMemberDeclaration ::= ConstantDeclaration
            //
            case 199:
                break;
            //
            // Rule 200:  InterfaceMemberDeclaration ::= AbstractMethodDeclaration
            //
            case 200:
                break;
            //
            // Rule 201:  InterfaceMemberDeclaration ::= ClassDeclaration
            //
            case 201:
                break;
            //
            // Rule 202:  InterfaceMemberDeclaration ::= InterfaceDeclaration
            //
            case 202:
                break;
            //
            // Rule 203:  InterfaceMemberDeclaration ::= ;
            //
            case 203: {
               //#line 533 "GJavaParser.g"
                setResult(
                    //#line 533 GJavaParser.g
                    ast_pool.Next()=new InterfaceMemberDeclaration(getRhsIToken(1))
                //#line 533 GJavaParser.g
                );
            break;
            }
            //
            // Rule 204:  ConstantDeclaration ::= ConstantModifiersopt Type VariableDeclarators
            //
            case 204: {
               //#line 535 "GJavaParser.g"
                setResult(
                    //#line 535 GJavaParser.g
                    ast_pool.Next()=new ConstantDeclaration(getLeftIToken(), getRightIToken(),
                                            //#line 535 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 535 GJavaParser.g
                                            (IAst*)getRhsSym(2),
                                            //#line 535 GJavaParser.g
                                            (IAst*)getRhsSym(3))
                //#line 535 GJavaParser.g
                );
            break;
            }
            //
            // Rule 205:  ConstantModifiers ::= ConstantModifier
            //
            case 205:
                break;
            //
            // Rule 206:  ConstantModifiers ::= ConstantModifiers ConstantModifier
            //
            case 206: {
               //#line 538 "GJavaParser.g"
                setResult(
                    //#line 538 GJavaParser.g
                    ast_pool.Next()=new ConstantModifiers(getLeftIToken(), getRightIToken(),
                                          //#line 538 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 538 GJavaParser.g
                                          (IAst*)getRhsSym(2))
                //#line 538 GJavaParser.g
                );
            break;
            }
            //
            // Rule 207:  ConstantModifier ::= Annotation
            //
            case 207:
                break;
            //
            // Rule 208:  ConstantModifier ::= public
            //
            case 208: {
               //#line 541 "GJavaParser.g"
                setResult(
                    //#line 541 GJavaParser.g
                    ast_pool.Next()=new ConstantModifier0(getRhsIToken(1))
                //#line 541 GJavaParser.g
                );
            break;
            }
            //
            // Rule 209:  ConstantModifier ::= static
            //
            case 209: {
               //#line 542 "GJavaParser.g"
                setResult(
                    //#line 542 GJavaParser.g
                    ast_pool.Next()=new ConstantModifier1(getRhsIToken(1))
                //#line 542 GJavaParser.g
                );
            break;
            }
            //
            // Rule 210:  ConstantModifier ::= final
            //
            case 210: {
               //#line 543 "GJavaParser.g"
                setResult(
                    //#line 543 GJavaParser.g
                    ast_pool.Next()=new ConstantModifier2(getRhsIToken(1))
                //#line 543 GJavaParser.g
                );
            break;
            }
            //
            // Rule 211:  AbstractMethodDeclaration ::= AbstractMethodModifiersopt TypeParametersopt ResultType MethodDeclarator Throwsopt ;
            //
            case 211: {
               //#line 545 "GJavaParser.g"
                setResult(
                    //#line 545 GJavaParser.g
                    ast_pool.Next()=new AbstractMethodDeclaration(getLeftIToken(), getRightIToken(),
                                                  //#line 545 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 545 GJavaParser.g
                                                  (IAst*)getRhsSym(2),
                                                  //#line 545 GJavaParser.g
                                                  (IAst*)getRhsSym(3),
                                                  //#line 545 GJavaParser.g
                                                  (IAst*)getRhsSym(4),
                                                  //#line 545 GJavaParser.g
                                                  (IAst*)getRhsSym(5),
                                                  //#line 545 GJavaParser.g
                                                  ast_pool.Next()=new AstToken(getRhsIToken(6)))
                //#line 545 GJavaParser.g
                );
            break;
            }
            //
            // Rule 212:  AbstractMethodModifiers ::= AbstractMethodModifier
            //
            case 212:
                break;
            //
            // Rule 213:  AbstractMethodModifiers ::= AbstractMethodModifiers AbstractMethodModifier
            //
            case 213: {
               //#line 548 "GJavaParser.g"
                setResult(
                    //#line 548 GJavaParser.g
                    ast_pool.Next()=new AbstractMethodModifiers(getLeftIToken(), getRightIToken(),
                                                //#line 548 GJavaParser.g
                                                (IAst*)getRhsSym(1),
                                                //#line 548 GJavaParser.g
                                                (IAst*)getRhsSym(2))
                //#line 548 GJavaParser.g
                );
            break;
            }
            //
            // Rule 214:  AbstractMethodModifier ::= Annotations
            //
            case 214:
                break;
            //
            // Rule 215:  AbstractMethodModifier ::= public
            //
            case 215: {
               //#line 551 "GJavaParser.g"
                setResult(
                    //#line 551 GJavaParser.g
                    ast_pool.Next()=new AbstractMethodModifier0(getRhsIToken(1))
                //#line 551 GJavaParser.g
                );
            break;
            }
            //
            // Rule 216:  AbstractMethodModifier ::= abstract
            //
            case 216: {
               //#line 552 "GJavaParser.g"
                setResult(
                    //#line 552 GJavaParser.g
                    ast_pool.Next()=new AbstractMethodModifier1(getRhsIToken(1))
                //#line 552 GJavaParser.g
                );
            break;
            }
            //
            // Rule 217:  AnnotationTypeDeclaration ::= InterfaceModifiersopt @ interface identifier AnnotationTypeBody
            //
            case 217: {
               //#line 554 "GJavaParser.g"
                setResult(
                    //#line 554 GJavaParser.g
                    ast_pool.Next()=new AnnotationTypeDeclaration(getLeftIToken(), getRightIToken(),
                                                  //#line 554 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 554 GJavaParser.g
                                                  ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                  //#line 554 GJavaParser.g
                                                  ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                                  //#line 554 GJavaParser.g
                                                  (IAst*)getRhsSym(4),
                                                  //#line 554 GJavaParser.g
                                                  (IAst*)getRhsSym(5))
                //#line 554 GJavaParser.g
                );
            break;
            }
            //
            // Rule 218:  AnnotationTypeBody ::= { AnnotationTypeElementDeclarationsopt }
            //
            case 218: {
               //#line 556 "GJavaParser.g"
                setResult(
                    //#line 556 GJavaParser.g
                    ast_pool.Next()=new AnnotationTypeBody(getLeftIToken(), getRightIToken(),
                                           //#line 556 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                           //#line 556 GJavaParser.g
                                           (IAst*)getRhsSym(2),
                                           //#line 556 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 556 GJavaParser.g
                );
            break;
            }
            //
            // Rule 219:  AnnotationTypeElementDeclarations ::= AnnotationTypeElementDeclaration
            //
            case 219:
                break;
            //
            // Rule 220:  AnnotationTypeElementDeclarations ::= AnnotationTypeElementDeclarations AnnotationTypeElementDeclaration
            //
            case 220: {
               //#line 559 "GJavaParser.g"
                setResult(
                    //#line 559 GJavaParser.g
                    ast_pool.Next()=new AnnotationTypeElementDeclarations(getLeftIToken(), getRightIToken(),
                                                          //#line 559 GJavaParser.g
                                                          (IAst*)getRhsSym(1),
                                                          //#line 559 GJavaParser.g
                                                          (IAst*)getRhsSym(2))
                //#line 559 GJavaParser.g
                );
            break;
            }
            //
            // Rule 221:  AnnotationTypeElementDeclaration ::= AbstractMethodModifiersopt Type identifier ( ) DefaultValueopt ;
            //
            case 221: {
               //#line 561 "GJavaParser.g"
                setResult(
                    //#line 561 GJavaParser.g
                    ast_pool.Next()=new AnnotationTypeElementDeclaration0(getLeftIToken(), getRightIToken(),
                                                          //#line 561 GJavaParser.g
                                                          (IAst*)getRhsSym(1),
                                                          //#line 561 GJavaParser.g
                                                          (IAst*)getRhsSym(2),
                                                          //#line 561 GJavaParser.g
                                                          (IAst*)getRhsSym(3),
                                                          //#line 561 GJavaParser.g
                                                          ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                                          //#line 561 GJavaParser.g
                                                          ast_pool.Next()=new AstToken(getRhsIToken(5)),
                                                          //#line 561 GJavaParser.g
                                                          (IAst*)getRhsSym(6),
                                                          //#line 561 GJavaParser.g
                                                          ast_pool.Next()=new AstToken(getRhsIToken(7)))
                //#line 561 GJavaParser.g
                );
            break;
            }
            //
            // Rule 222:  AnnotationTypeElementDeclaration ::= ConstantDeclaration
            //
            case 222:
                break;
            //
            // Rule 223:  AnnotationTypeElementDeclaration ::= ClassDeclaration
            //
            case 223:
                break;
            //
            // Rule 224:  AnnotationTypeElementDeclaration ::= InterfaceDeclaration
            //
            case 224:
                break;
            //
            // Rule 225:  AnnotationTypeElementDeclaration ::= EnumDeclaration
            //
            case 225:
                break;
            //
            // Rule 226:  AnnotationTypeElementDeclaration ::= AnnotationTypeDeclaration
            //
            case 226:
                break;
            //
            // Rule 227:  AnnotationTypeElementDeclaration ::= ;
            //
            case 227: {
               //#line 567 "GJavaParser.g"
                setResult(
                    //#line 567 GJavaParser.g
                    ast_pool.Next()=new AnnotationTypeElementDeclaration1(getRhsIToken(1))
                //#line 567 GJavaParser.g
                );
            break;
            }
            //
            // Rule 228:  DefaultValue ::= default ElementValue
            //
            case 228: {
               //#line 569 "GJavaParser.g"
                setResult(
                    //#line 569 GJavaParser.g
                    ast_pool.Next()=new DefaultValue(getLeftIToken(), getRightIToken(),
                                     //#line 569 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                     //#line 569 GJavaParser.g
                                     (IAst*)getRhsSym(2))
                //#line 569 GJavaParser.g
                );
            break;
            }
            //
            // Rule 229:  Annotations ::= Annotation
            //
            case 229:
                break;
            //
            // Rule 230:  Annotations ::= Annotations Annotation
            //
            case 230: {
               //#line 572 "GJavaParser.g"
                setResult(
                    //#line 572 GJavaParser.g
                    ast_pool.Next()=new Annotations(getLeftIToken(), getRightIToken(),
                                    //#line 572 GJavaParser.g
                                    (IAst*)getRhsSym(1),
                                    //#line 572 GJavaParser.g
                                    (IAst*)getRhsSym(2))
                //#line 572 GJavaParser.g
                );
            break;
            }
            //
            // Rule 231:  Annotation ::= NormalAnnotation
            //
            case 231:
                break;
            //
            // Rule 232:  Annotation ::= MarkerAnnotation
            //
            case 232:
                break;
            //
            // Rule 233:  Annotation ::= SingleElementAnnotation
            //
            case 233:
                break;
            //
            // Rule 234:  NormalAnnotation ::= @ TypeName ( ElementValuePairsopt )
            //
            case 234: {
               //#line 578 "GJavaParser.g"
                setResult(
                    //#line 578 GJavaParser.g
                    ast_pool.Next()=new NormalAnnotation(getLeftIToken(), getRightIToken(),
                                         //#line 578 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                         //#line 578 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 578 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                         //#line 578 GJavaParser.g
                                         (IAst*)getRhsSym(4),
                                         //#line 578 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(5)))
                //#line 578 GJavaParser.g
                );
            break;
            }
            //
            // Rule 235:  ElementValuePairs ::= ElementValuePair
            //
            case 235:
                break;
            //
            // Rule 236:  ElementValuePairs ::= ElementValuePairs , ElementValuePair
            //
            case 236: {
               //#line 581 "GJavaParser.g"
                setResult(
                    //#line 581 GJavaParser.g
                    ast_pool.Next()=new ElementValuePairs(getLeftIToken(), getRightIToken(),
                                          //#line 581 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 581 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 581 GJavaParser.g
                                          (IAst*)getRhsSym(3))
                //#line 581 GJavaParser.g
                );
            break;
            }
            //
            // Rule 237:  ElementValuePair ::= SimpleName = ElementValue
            //
            case 237: {
               //#line 583 "GJavaParser.g"
                setResult(
                    //#line 583 GJavaParser.g
                    ast_pool.Next()=new ElementValuePair(getLeftIToken(), getRightIToken(),
                                         //#line 583 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 583 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                         //#line 583 GJavaParser.g
                                         (IAst*)getRhsSym(3))
                //#line 583 GJavaParser.g
                );
            break;
            }
            //
            // Rule 238:  SimpleName ::= identifier
            //
            case 238:
                break;
            //
            // Rule 239:  ElementValue ::= ConditionalExpression
            //
            case 239:
                break;
            //
            // Rule 240:  ElementValue ::= Annotation
            //
            case 240:
                break;
            //
            // Rule 241:  ElementValue ::= ElementValueArrayInitializer
            //
            case 241:
                break;
            //
            // Rule 242:  ElementValueArrayInitializer ::= { ElementValuesopt ,opt }
            //
            case 242: {
               //#line 591 "GJavaParser.g"
                setResult(
                    //#line 591 GJavaParser.g
                    ast_pool.Next()=new ElementValueArrayInitializer(getLeftIToken(), getRightIToken(),
                                                     //#line 591 GJavaParser.g
                                                     ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                     //#line 591 GJavaParser.g
                                                     (IAst*)getRhsSym(2),
                                                     //#line 591 GJavaParser.g
                                                     (IAst*)getRhsSym(3),
                                                     //#line 591 GJavaParser.g
                                                     ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 591 GJavaParser.g
                );
            break;
            }
            //
            // Rule 243:  ElementValues ::= ElementValue
            //
            case 243:
                break;
            //
            // Rule 244:  ElementValues ::= ElementValues , ElementValue
            //
            case 244: {
               //#line 594 "GJavaParser.g"
                setResult(
                    //#line 594 GJavaParser.g
                    ast_pool.Next()=new ElementValues(getLeftIToken(), getRightIToken(),
                                      //#line 594 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 594 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                      //#line 594 GJavaParser.g
                                      (IAst*)getRhsSym(3))
                //#line 594 GJavaParser.g
                );
            break;
            }
            //
            // Rule 245:  MarkerAnnotation ::= @ TypeName
            //
            case 245: {
               //#line 596 "GJavaParser.g"
                setResult(
                    //#line 596 GJavaParser.g
                    ast_pool.Next()=new MarkerAnnotation(getLeftIToken(), getRightIToken(),
                                         //#line 596 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                         //#line 596 GJavaParser.g
                                         (IAst*)getRhsSym(2))
                //#line 596 GJavaParser.g
                );
            break;
            }
            //
            // Rule 246:  SingleElementAnnotation ::= @ TypeName ( ElementValue )
            //
            case 246: {
               //#line 598 "GJavaParser.g"
                setResult(
                    //#line 598 GJavaParser.g
                    ast_pool.Next()=new SingleElementAnnotation(getLeftIToken(), getRightIToken(),
                                                //#line 598 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                //#line 598 GJavaParser.g
                                                (IAst*)getRhsSym(2),
                                                //#line 598 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                                //#line 598 GJavaParser.g
                                                (IAst*)getRhsSym(4),
                                                //#line 598 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(5)))
                //#line 598 GJavaParser.g
                );
            break;
            }
            //
            // Rule 247:  ArrayInitializer ::= { VariableInitializersopt ,opt }
            //
            case 247: {
               //#line 602 "GJavaParser.g"
                setResult(
                    //#line 602 GJavaParser.g
                    ast_pool.Next()=new ArrayInitializer(getLeftIToken(), getRightIToken(),
                                         //#line 602 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                         //#line 602 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 602 GJavaParser.g
                                         (IAst*)getRhsSym(3),
                                         //#line 602 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 602 GJavaParser.g
                );
            break;
            }
            //
            // Rule 248:  VariableInitializers ::= VariableInitializer
            //
            case 248:
                break;
            //
            // Rule 249:  VariableInitializers ::= VariableInitializers , VariableInitializer
            //
            case 249: {
               //#line 605 "GJavaParser.g"
                setResult(
                    //#line 605 GJavaParser.g
                    ast_pool.Next()=new VariableInitializers(getLeftIToken(), getRightIToken(),
                                             //#line 605 GJavaParser.g
                                             (IAst*)getRhsSym(1),
                                             //#line 605 GJavaParser.g
                                             ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                             //#line 605 GJavaParser.g
                                             (IAst*)getRhsSym(3))
                //#line 605 GJavaParser.g
                );
            break;
            }
            //
            // Rule 250:  Block ::= { BlockStatementsopt }
            //
            case 250: {
               //#line 621 "GJavaParser.g"
                setResult(
                    //#line 621 GJavaParser.g
                    ast_pool.Next()=new Block(getLeftIToken(), getRightIToken(),
                              //#line 621 GJavaParser.g
                              ast_pool.Next()=new AstToken(getRhsIToken(1)),
                              //#line 621 GJavaParser.g
                              (IAst*)getRhsSym(2),
                              //#line 621 GJavaParser.g
                              ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 621 GJavaParser.g
                );
            break;
            }
            //
            // Rule 251:  BlockStatements ::= BlockStatement
            //
            case 251:
                break;
            //
            // Rule 252:  BlockStatements ::= BlockStatements BlockStatement
            //
            case 252: {
               //#line 624 "GJavaParser.g"
                setResult(
                    //#line 624 GJavaParser.g
                    ast_pool.Next()=new BlockStatements(getLeftIToken(), getRightIToken(),
                                        //#line 624 GJavaParser.g
                                        (IAst*)getRhsSym(1),
                                        //#line 624 GJavaParser.g
                                        (IAst*)getRhsSym(2))
                //#line 624 GJavaParser.g
                );
            break;
            }
            //
            // Rule 253:  BlockStatement ::= LocalVariableDeclarationStatement
            //
            case 253:
                break;
            //
            // Rule 254:  BlockStatement ::= ClassDeclaration
            //
            case 254:
                break;
            //
            // Rule 255:  BlockStatement ::= Statement
            //
            case 255:
                break;
            //
            // Rule 256:  LocalVariableDeclarationStatement ::= LocalVariableDeclaration ;
            //
            case 256: {
               //#line 630 "GJavaParser.g"
                setResult(
                    //#line 630 GJavaParser.g
                    ast_pool.Next()=new LocalVariableDeclarationStatement(getLeftIToken(), getRightIToken(),
                                                          //#line 630 GJavaParser.g
                                                          (IAst*)getRhsSym(1),
                                                          //#line 630 GJavaParser.g
                                                          ast_pool.Next()=new AstToken(getRhsIToken(2)))
                //#line 630 GJavaParser.g
                );
            break;
            }
            //
            // Rule 257:  LocalVariableDeclaration ::= VariableModifiersopt Type VariableDeclarators
            //
            case 257: {
               //#line 632 "GJavaParser.g"
                setResult(
                    //#line 632 GJavaParser.g
                    ast_pool.Next()=new LocalVariableDeclaration(getLeftIToken(), getRightIToken(),
                                                 //#line 632 GJavaParser.g
                                                 (IAst*)getRhsSym(1),
                                                 //#line 632 GJavaParser.g
                                                 (IAst*)getRhsSym(2),
                                                 //#line 632 GJavaParser.g
                                                 (IAst*)getRhsSym(3))
                //#line 632 GJavaParser.g
                );
            break;
            }
            //
            // Rule 258:  Statement ::= StatementWithoutTrailingSubstatement
            //
            case 258:
                break;
            //
            // Rule 259:  Statement ::= LabeledStatement
            //
            case 259:
                break;
            //
            // Rule 260:  Statement ::= IfThenStatement
            //
            case 260:
                break;
            //
            // Rule 261:  Statement ::= IfThenElseStatement
            //
            case 261:
                break;
            //
            // Rule 262:  Statement ::= WhileStatement
            //
            case 262:
                break;
            //
            // Rule 263:  Statement ::= ForStatement
            //
            case 263:
                break;
            //
            // Rule 264:  StatementWithoutTrailingSubstatement ::= Block
            //
            case 264:
                break;
            //
            // Rule 265:  StatementWithoutTrailingSubstatement ::= EmptyStatement
            //
            case 265:
                break;
            //
            // Rule 266:  StatementWithoutTrailingSubstatement ::= ExpressionStatement
            //
            case 266:
                break;
            //
            // Rule 267:  StatementWithoutTrailingSubstatement ::= AssertStatement
            //
            case 267:
                break;
            //
            // Rule 268:  StatementWithoutTrailingSubstatement ::= SwitchStatement
            //
            case 268:
                break;
            //
            // Rule 269:  StatementWithoutTrailingSubstatement ::= DoStatement
            //
            case 269:
                break;
            //
            // Rule 270:  StatementWithoutTrailingSubstatement ::= BreakStatement
            //
            case 270:
                break;
            //
            // Rule 271:  StatementWithoutTrailingSubstatement ::= ContinueStatement
            //
            case 271:
                break;
            //
            // Rule 272:  StatementWithoutTrailingSubstatement ::= ReturnStatement
            //
            case 272:
                break;
            //
            // Rule 273:  StatementWithoutTrailingSubstatement ::= SynchronizedStatement
            //
            case 273:
                break;
            //
            // Rule 274:  StatementWithoutTrailingSubstatement ::= ThrowStatement
            //
            case 274:
                break;
            //
            // Rule 275:  StatementWithoutTrailingSubstatement ::= TryStatement
            //
            case 275:
                break;
            //
            // Rule 276:  StatementNoShortIf ::= StatementWithoutTrailingSubstatement
            //
            case 276:
                break;
            //
            // Rule 277:  StatementNoShortIf ::= LabeledStatementNoShortIf
            //
            case 277:
                break;
            //
            // Rule 278:  StatementNoShortIf ::= IfThenElseStatementNoShortIf
            //
            case 278:
                break;
            //
            // Rule 279:  StatementNoShortIf ::= WhileStatementNoShortIf
            //
            case 279:
                break;
            //
            // Rule 280:  StatementNoShortIf ::= ForStatementNoShortIf
            //
            case 280:
                break;
            //
            // Rule 281:  IfThenStatement ::= if ( Expression ) Statement
            //
            case 281: {
               //#line 675 "GJavaParser.g"
                setResult(
                    //#line 675 GJavaParser.g
                    ast_pool.Next()=new IfThenStatement(getLeftIToken(), getRightIToken(),
                                        //#line 675 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                        //#line 675 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                        //#line 675 GJavaParser.g
                                        (IAst*)getRhsSym(3),
                                        //#line 675 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                        //#line 675 GJavaParser.g
                                        (IAst*)getRhsSym(5))
                //#line 675 GJavaParser.g
                );
            break;
            }
            //
            // Rule 282:  IfThenElseStatement ::= if ( Expression ) StatementNoShortIf else Statement
            //
            case 282: {
               //#line 677 "GJavaParser.g"
                setResult(
                    //#line 677 GJavaParser.g
                    ast_pool.Next()=new IfThenElseStatement(getLeftIToken(), getRightIToken(),
                                            //#line 677 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                            //#line 677 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                            //#line 677 GJavaParser.g
                                            (IAst*)getRhsSym(3),
                                            //#line 677 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                            //#line 677 GJavaParser.g
                                            (IAst*)getRhsSym(5),
                                            //#line 677 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(6)),
                                            //#line 677 GJavaParser.g
                                            (IAst*)getRhsSym(7))
                //#line 677 GJavaParser.g
                );
            break;
            }
            //
            // Rule 283:  IfThenElseStatementNoShortIf ::= if ( Expression ) StatementNoShortIf else StatementNoShortIf
            //
            case 283: {
               //#line 679 "GJavaParser.g"
                setResult(
                    //#line 679 GJavaParser.g
                    ast_pool.Next()=new IfThenElseStatementNoShortIf(getLeftIToken(), getRightIToken(),
                                                     //#line 679 GJavaParser.g
                                                     ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                     //#line 679 GJavaParser.g
                                                     ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                     //#line 679 GJavaParser.g
                                                     (IAst*)getRhsSym(3),
                                                     //#line 679 GJavaParser.g
                                                     ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                                     //#line 679 GJavaParser.g
                                                     (IAst*)getRhsSym(5),
                                                     //#line 679 GJavaParser.g
                                                     ast_pool.Next()=new AstToken(getRhsIToken(6)),
                                                     //#line 679 GJavaParser.g
                                                     (IAst*)getRhsSym(7))
                //#line 679 GJavaParser.g
                );
            break;
            }
            //
            // Rule 284:  EmptyStatement ::= ;
            //
            case 284: {
               //#line 681 "GJavaParser.g"
                setResult(
                    //#line 681 GJavaParser.g
                    ast_pool.Next()=new EmptyStatement(getRhsIToken(1))
                //#line 681 GJavaParser.g
                );
            break;
            }
            //
            // Rule 285:  LabeledStatement ::= identifier : Statement
            //
            case 285: {
               //#line 683 "GJavaParser.g"
                setResult(
                    //#line 683 GJavaParser.g
                    ast_pool.Next()=new LabeledStatement(getLeftIToken(), getRightIToken(),
                                         //#line 683 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 683 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                         //#line 683 GJavaParser.g
                                         (IAst*)getRhsSym(3))
                //#line 683 GJavaParser.g
                );
            break;
            }
            //
            // Rule 286:  LabeledStatementNoShortIf ::= identifier : StatementNoShortIf
            //
            case 286: {
               //#line 685 "GJavaParser.g"
                setResult(
                    //#line 685 GJavaParser.g
                    ast_pool.Next()=new LabeledStatementNoShortIf(getLeftIToken(), getRightIToken(),
                                                  //#line 685 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 685 GJavaParser.g
                                                  ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                  //#line 685 GJavaParser.g
                                                  (IAst*)getRhsSym(3))
                //#line 685 GJavaParser.g
                );
            break;
            }
            //
            // Rule 287:  ExpressionStatement ::= StatementExpression ;
            //
            case 287: {
               //#line 687 "GJavaParser.g"
                setResult(
                    //#line 687 GJavaParser.g
                    ast_pool.Next()=new ExpressionStatement(getLeftIToken(), getRightIToken(),
                                            //#line 687 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 687 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)))
                //#line 687 GJavaParser.g
                );
            break;
            }
            //
            // Rule 288:  StatementExpression ::= Assignment
            //
            case 288:
                break;
            //
            // Rule 289:  StatementExpression ::= PreIncrementExpression
            //
            case 289:
                break;
            //
            // Rule 290:  StatementExpression ::= PreDecrementExpression
            //
            case 290:
                break;
            //
            // Rule 291:  StatementExpression ::= PostIncrementExpression
            //
            case 291:
                break;
            //
            // Rule 292:  StatementExpression ::= PostDecrementExpression
            //
            case 292:
                break;
            //
            // Rule 293:  StatementExpression ::= MethodInvocation
            //
            case 293:
                break;
            //
            // Rule 294:  StatementExpression ::= ClassInstanceCreationExpression
            //
            case 294:
                break;
            //
            // Rule 295:  AssertStatement ::= assert Expression ;
            //
            case 295: {
               //#line 706 "GJavaParser.g"
                setResult(
                    //#line 706 GJavaParser.g
                    ast_pool.Next()=new AssertStatement0(getLeftIToken(), getRightIToken(),
                                         //#line 706 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                         //#line 706 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 706 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 706 GJavaParser.g
                );
            break;
            }
            //
            // Rule 296:  AssertStatement ::= assert Expression : Expression ;
            //
            case 296: {
               //#line 707 "GJavaParser.g"
                setResult(
                    //#line 707 GJavaParser.g
                    ast_pool.Next()=new AssertStatement1(getLeftIToken(), getRightIToken(),
                                         //#line 707 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                         //#line 707 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 707 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                         //#line 707 GJavaParser.g
                                         (IAst*)getRhsSym(4),
                                         //#line 707 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(5)))
                //#line 707 GJavaParser.g
                );
            break;
            }
            //
            // Rule 297:  SwitchStatement ::= switch ( Expression ) SwitchBlock
            //
            case 297: {
               //#line 709 "GJavaParser.g"
                setResult(
                    //#line 709 GJavaParser.g
                    ast_pool.Next()=new SwitchStatement(getLeftIToken(), getRightIToken(),
                                        //#line 709 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                        //#line 709 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                        //#line 709 GJavaParser.g
                                        (IAst*)getRhsSym(3),
                                        //#line 709 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                        //#line 709 GJavaParser.g
                                        (IAst*)getRhsSym(5))
                //#line 709 GJavaParser.g
                );
            break;
            }
            //
            // Rule 298:  SwitchBlock ::= { SwitchBlockStatementGroupsopt SwitchLabelsopt }
            //
            case 298: {
               //#line 711 "GJavaParser.g"
                setResult(
                    //#line 711 GJavaParser.g
                    ast_pool.Next()=new SwitchBlock(getLeftIToken(), getRightIToken(),
                                    //#line 711 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                    //#line 711 GJavaParser.g
                                    (IAst*)getRhsSym(2),
                                    //#line 711 GJavaParser.g
                                    (IAst*)getRhsSym(3),
                                    //#line 711 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 711 GJavaParser.g
                );
            break;
            }
            //
            // Rule 299:  SwitchBlockStatementGroups ::= SwitchBlockStatementGroup
            //
            case 299:
                break;
            //
            // Rule 300:  SwitchBlockStatementGroups ::= SwitchBlockStatementGroups SwitchBlockStatementGroup
            //
            case 300: {
               //#line 714 "GJavaParser.g"
                setResult(
                    //#line 714 GJavaParser.g
                    ast_pool.Next()=new SwitchBlockStatementGroups(getLeftIToken(), getRightIToken(),
                                                   //#line 714 GJavaParser.g
                                                   (IAst*)getRhsSym(1),
                                                   //#line 714 GJavaParser.g
                                                   (IAst*)getRhsSym(2))
                //#line 714 GJavaParser.g
                );
            break;
            }
            //
            // Rule 301:  SwitchBlockStatementGroup ::= SwitchLabels BlockStatements
            //
            case 301: {
               //#line 716 "GJavaParser.g"
                setResult(
                    //#line 716 GJavaParser.g
                    ast_pool.Next()=new SwitchBlockStatementGroup(getLeftIToken(), getRightIToken(),
                                                  //#line 716 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 716 GJavaParser.g
                                                  (IAst*)getRhsSym(2))
                //#line 716 GJavaParser.g
                );
            break;
            }
            //
            // Rule 302:  SwitchLabels ::= SwitchLabel
            //
            case 302:
                break;
            //
            // Rule 303:  SwitchLabels ::= SwitchLabels SwitchLabel
            //
            case 303: {
               //#line 719 "GJavaParser.g"
                setResult(
                    //#line 719 GJavaParser.g
                    ast_pool.Next()=new SwitchLabels(getLeftIToken(), getRightIToken(),
                                     //#line 719 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 719 GJavaParser.g
                                     (IAst*)getRhsSym(2))
                //#line 719 GJavaParser.g
                );
            break;
            }
            //
            // Rule 304:  SwitchLabel ::= case ConstantExpression :
            //
            case 304: {
               //#line 721 "GJavaParser.g"
                setResult(
                    //#line 721 GJavaParser.g
                    ast_pool.Next()=new SwitchLabel0(getLeftIToken(), getRightIToken(),
                                     //#line 721 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                     //#line 721 GJavaParser.g
                                     (IAst*)getRhsSym(2),
                                     //#line 721 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 721 GJavaParser.g
                );
            break;
            }
            //
            // Rule 305:  SwitchLabel ::= case EnumConstant :
            //
            case 305: {
               //#line 722 "GJavaParser.g"
                setResult(
                    //#line 722 GJavaParser.g
                    ast_pool.Next()=new SwitchLabel1(getLeftIToken(), getRightIToken(),
                                     //#line 722 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                     //#line 722 GJavaParser.g
                                     (IAst*)getRhsSym(2),
                                     //#line 722 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 722 GJavaParser.g
                );
            break;
            }
            //
            // Rule 306:  SwitchLabel ::= default :
            //
            case 306: {
               //#line 723 "GJavaParser.g"
                setResult(
                    //#line 723 GJavaParser.g
                    ast_pool.Next()=new SwitchLabel2(getLeftIToken(), getRightIToken(),
                                     //#line 723 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                     //#line 723 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(2)))
                //#line 723 GJavaParser.g
                );
            break;
            }
            //
            // Rule 307:  EnumConstant ::= identifier
            //
            case 307:
                break;
            //
            // Rule 308:  WhileStatement ::= while ( Expression ) Statement
            //
            case 308: {
               //#line 727 "GJavaParser.g"
                setResult(
                    //#line 727 GJavaParser.g
                    ast_pool.Next()=new WhileStatement(getLeftIToken(), getRightIToken(),
                                       //#line 727 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                       //#line 727 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                       //#line 727 GJavaParser.g
                                       (IAst*)getRhsSym(3),
                                       //#line 727 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                       //#line 727 GJavaParser.g
                                       (IAst*)getRhsSym(5))
                //#line 727 GJavaParser.g
                );
            break;
            }
            //
            // Rule 309:  WhileStatementNoShortIf ::= while ( Expression ) StatementNoShortIf
            //
            case 309: {
               //#line 729 "GJavaParser.g"
                setResult(
                    //#line 729 GJavaParser.g
                    ast_pool.Next()=new WhileStatementNoShortIf(getLeftIToken(), getRightIToken(),
                                                //#line 729 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                //#line 729 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                //#line 729 GJavaParser.g
                                                (IAst*)getRhsSym(3),
                                                //#line 729 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                                //#line 729 GJavaParser.g
                                                (IAst*)getRhsSym(5))
                //#line 729 GJavaParser.g
                );
            break;
            }
            //
            // Rule 310:  DoStatement ::= do Statement while ( Expression ) ;
            //
            case 310: {
               //#line 731 "GJavaParser.g"
                setResult(
                    //#line 731 GJavaParser.g
                    ast_pool.Next()=new DoStatement(getLeftIToken(), getRightIToken(),
                                    //#line 731 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                    //#line 731 GJavaParser.g
                                    (IAst*)getRhsSym(2),
                                    //#line 731 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                    //#line 731 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                    //#line 731 GJavaParser.g
                                    (IAst*)getRhsSym(5),
                                    //#line 731 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(6)),
                                    //#line 731 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(7)))
                //#line 731 GJavaParser.g
                );
            break;
            }
            //
            // Rule 311:  ForStatement ::= BasicForStatement
            //
            case 311:
                break;
            //
            // Rule 312:  ForStatement ::= EnhancedForStatement
            //
            case 312:
                break;
            //
            // Rule 313:  BasicForStatement ::= for ( ForInitopt ; Expressionopt ; ForUpdateopt ) Statement
            //
            case 313: {
               //#line 736 "GJavaParser.g"
                setResult(
                    //#line 736 GJavaParser.g
                    ast_pool.Next()=new BasicForStatement(getLeftIToken(), getRightIToken(),
                                          //#line 736 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                          //#line 736 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 736 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 736 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                          //#line 736 GJavaParser.g
                                          (IAst*)getRhsSym(5),
                                          //#line 736 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(6)),
                                          //#line 736 GJavaParser.g
                                          (IAst*)getRhsSym(7),
                                          //#line 736 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(8)),
                                          //#line 736 GJavaParser.g
                                          (IAst*)getRhsSym(9))
                //#line 736 GJavaParser.g
                );
            break;
            }
            //
            // Rule 314:  ForStatementNoShortIf ::= for ( ForInitopt ; Expressionopt ; ForUpdateopt ) StatementNoShortIf
            //
            case 314: {
               //#line 738 "GJavaParser.g"
                setResult(
                    //#line 738 GJavaParser.g
                    ast_pool.Next()=new ForStatementNoShortIf(getLeftIToken(), getRightIToken(),
                                              //#line 738 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                              //#line 738 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 738 GJavaParser.g
                                              (IAst*)getRhsSym(3),
                                              //#line 738 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                              //#line 738 GJavaParser.g
                                              (IAst*)getRhsSym(5),
                                              //#line 738 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(6)),
                                              //#line 738 GJavaParser.g
                                              (IAst*)getRhsSym(7),
                                              //#line 738 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(8)),
                                              //#line 738 GJavaParser.g
                                              (IAst*)getRhsSym(9))
                //#line 738 GJavaParser.g
                );
            break;
            }
            //
            // Rule 315:  ForInit ::= StatementExpressionList
            //
            case 315:
                break;
            //
            // Rule 316:  ForInit ::= LocalVariableDeclaration
            //
            case 316:
                break;
            //
            // Rule 317:  ForUpdate ::= StatementExpressionList
            //
            case 317:
                break;
            //
            // Rule 318:  StatementExpressionList ::= StatementExpression
            //
            case 318:
                break;
            //
            // Rule 319:  StatementExpressionList ::= StatementExpressionList , StatementExpression
            //
            case 319: {
               //#line 746 "GJavaParser.g"
                setResult(
                    //#line 746 GJavaParser.g
                    ast_pool.Next()=new StatementExpressionList(getLeftIToken(), getRightIToken(),
                                                //#line 746 GJavaParser.g
                                                (IAst*)getRhsSym(1),
                                                //#line 746 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                //#line 746 GJavaParser.g
                                                (IAst*)getRhsSym(3))
                //#line 746 GJavaParser.g
                );
            break;
            }
            //
            // Rule 320:  EnhancedForStatement ::= for ( FormalParameter : Expression ) Statement
            //
            case 320: {
               //#line 748 "GJavaParser.g"
                setResult(
                    //#line 748 GJavaParser.g
                    ast_pool.Next()=new EnhancedForStatement(getLeftIToken(), getRightIToken(),
                                             //#line 748 GJavaParser.g
                                             ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                             //#line 748 GJavaParser.g
                                             ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                             //#line 748 GJavaParser.g
                                             (IAst*)getRhsSym(3),
                                             //#line 748 GJavaParser.g
                                             ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                             //#line 748 GJavaParser.g
                                             (IAst*)getRhsSym(5),
                                             //#line 748 GJavaParser.g
                                             ast_pool.Next()=new AstToken(getRhsIToken(6)),
                                             //#line 748 GJavaParser.g
                                             (IAst*)getRhsSym(7))
                //#line 748 GJavaParser.g
                );
            break;
            }
            //
            // Rule 321:  BreakStatement ::= break identifieropt ;
            //
            case 321: {
               //#line 750 "GJavaParser.g"
                setResult(
                    //#line 750 GJavaParser.g
                    ast_pool.Next()=new BreakStatement(getLeftIToken(), getRightIToken(),
                                       //#line 750 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                       //#line 750 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 750 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 750 GJavaParser.g
                );
            break;
            }
            //
            // Rule 322:  ContinueStatement ::= continue identifieropt ;
            //
            case 322: {
               //#line 752 "GJavaParser.g"
                setResult(
                    //#line 752 GJavaParser.g
                    ast_pool.Next()=new ContinueStatement(getLeftIToken(), getRightIToken(),
                                          //#line 752 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                          //#line 752 GJavaParser.g
                                          (IAst*)getRhsSym(2),
                                          //#line 752 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 752 GJavaParser.g
                );
            break;
            }
            //
            // Rule 323:  ReturnStatement ::= return Expressionopt ;
            //
            case 323: {
               //#line 754 "GJavaParser.g"
                setResult(
                    //#line 754 GJavaParser.g
                    ast_pool.Next()=new ReturnStatement(getLeftIToken(), getRightIToken(),
                                        //#line 754 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                        //#line 754 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 754 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 754 GJavaParser.g
                );
            break;
            }
            //
            // Rule 324:  ThrowStatement ::= throw Expression ;
            //
            case 324: {
               //#line 756 "GJavaParser.g"
                setResult(
                    //#line 756 GJavaParser.g
                    ast_pool.Next()=new ThrowStatement(getLeftIToken(), getRightIToken(),
                                       //#line 756 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                       //#line 756 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 756 GJavaParser.g
                                       ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 756 GJavaParser.g
                );
            break;
            }
            //
            // Rule 325:  SynchronizedStatement ::= synchronized ( Expression ) Block
            //
            case 325: {
               //#line 758 "GJavaParser.g"
                setResult(
                    //#line 758 GJavaParser.g
                    ast_pool.Next()=new SynchronizedStatement(getLeftIToken(), getRightIToken(),
                                              //#line 758 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                              //#line 758 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 758 GJavaParser.g
                                              (IAst*)getRhsSym(3),
                                              //#line 758 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                              //#line 758 GJavaParser.g
                                              (IAst*)getRhsSym(5))
                //#line 758 GJavaParser.g
                );
            break;
            }
            //
            // Rule 326:  TryStatement ::= try Block Catches
            //
            case 326: {
               //#line 760 "GJavaParser.g"
                setResult(
                    //#line 760 GJavaParser.g
                    ast_pool.Next()=new TryStatement0(getLeftIToken(), getRightIToken(),
                                      //#line 760 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                      //#line 760 GJavaParser.g
                                      (IAst*)getRhsSym(2),
                                      //#line 760 GJavaParser.g
                                      (IAst*)getRhsSym(3))
                //#line 760 GJavaParser.g
                );
            break;
            }
            //
            // Rule 327:  TryStatement ::= try Block Catchesopt Finally
            //
            case 327: {
               //#line 761 "GJavaParser.g"
                setResult(
                    //#line 761 GJavaParser.g
                    ast_pool.Next()=new TryStatement1(getLeftIToken(), getRightIToken(),
                                      //#line 761 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                      //#line 761 GJavaParser.g
                                      (IAst*)getRhsSym(2),
                                      //#line 761 GJavaParser.g
                                      (IAst*)getRhsSym(3),
                                      //#line 761 GJavaParser.g
                                      (IAst*)getRhsSym(4))
                //#line 761 GJavaParser.g
                );
            break;
            }
            //
            // Rule 328:  Catches ::= CatchClause
            //
            case 328:
                break;
            //
            // Rule 329:  Catches ::= Catches CatchClause
            //
            case 329: {
               //#line 764 "GJavaParser.g"
                setResult(
                    //#line 764 GJavaParser.g
                    ast_pool.Next()=new Catches(getLeftIToken(), getRightIToken(),
                                //#line 764 GJavaParser.g
                                (IAst*)getRhsSym(1),
                                //#line 764 GJavaParser.g
                                (IAst*)getRhsSym(2))
                //#line 764 GJavaParser.g
                );
            break;
            }
            //
            // Rule 330:  CatchClause ::= catch ( FormalParameter ) Block
            //
            case 330: {
               //#line 766 "GJavaParser.g"
                setResult(
                    //#line 766 GJavaParser.g
                    ast_pool.Next()=new CatchClause(getLeftIToken(), getRightIToken(),
                                    //#line 766 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                    //#line 766 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                    //#line 766 GJavaParser.g
                                    (IAst*)getRhsSym(3),
                                    //#line 766 GJavaParser.g
                                    ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                    //#line 766 GJavaParser.g
                                    (IAst*)getRhsSym(5))
                //#line 766 GJavaParser.g
                );
            break;
            }
            //
            // Rule 331:  Finally ::= finally Block
            //
            case 331: {
               //#line 768 "GJavaParser.g"
                setResult(
                    //#line 768 GJavaParser.g
                    ast_pool.Next()=new Finally(getLeftIToken(), getRightIToken(),
                                //#line 768 GJavaParser.g
                                ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                //#line 768 GJavaParser.g
                                (IAst*)getRhsSym(2))
                //#line 768 GJavaParser.g
                );
            break;
            }
            //
            // Rule 332:  Primary ::= PrimaryNoNewArray
            //
            case 332:
                break;
            //
            // Rule 333:  Primary ::= ArrayCreationExpression
            //
            case 333:
                break;
            //
            // Rule 334:  PrimaryNoNewArray ::= Literal
            //
            case 334:
                break;
            //
            // Rule 335:  PrimaryNoNewArray ::= Type . class
            //
            case 335: {
               //#line 784 "GJavaParser.g"
                setResult(
                    //#line 784 GJavaParser.g
                    ast_pool.Next()=new PrimaryNoNewArray0(getLeftIToken(), getRightIToken(),
                                           //#line 784 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 784 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                           //#line 784 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 784 GJavaParser.g
                );
            break;
            }
            //
            // Rule 336:  PrimaryNoNewArray ::= void . class
            //
            case 336: {
               //#line 785 "GJavaParser.g"
                setResult(
                    //#line 785 GJavaParser.g
                    ast_pool.Next()=new PrimaryNoNewArray1(getLeftIToken(), getRightIToken(),
                                           //#line 785 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                           //#line 785 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                           //#line 785 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 785 GJavaParser.g
                );
            break;
            }
            //
            // Rule 337:  PrimaryNoNewArray ::= this
            //
            case 337: {
               //#line 786 "GJavaParser.g"
                setResult(
                    //#line 786 GJavaParser.g
                    ast_pool.Next()=new PrimaryNoNewArray2(getRhsIToken(1))
                //#line 786 GJavaParser.g
                );
            break;
            }
            //
            // Rule 338:  PrimaryNoNewArray ::= ClassName . this
            //
            case 338: {
               //#line 787 "GJavaParser.g"
                setResult(
                    //#line 787 GJavaParser.g
                    ast_pool.Next()=new PrimaryNoNewArray3(getLeftIToken(), getRightIToken(),
                                           //#line 787 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 787 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                           //#line 787 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 787 GJavaParser.g
                );
            break;
            }
            //
            // Rule 339:  PrimaryNoNewArray ::= ( Expression )
            //
            case 339: {
               //#line 788 "GJavaParser.g"
                setResult(
                    //#line 788 GJavaParser.g
                    ast_pool.Next()=new PrimaryNoNewArray4(getLeftIToken(), getRightIToken(),
                                           //#line 788 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                           //#line 788 GJavaParser.g
                                           (IAst*)getRhsSym(2),
                                           //#line 788 GJavaParser.g
                                           ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 788 GJavaParser.g
                );
            break;
            }
            //
            // Rule 340:  PrimaryNoNewArray ::= ClassInstanceCreationExpression
            //
            case 340:
                break;
            //
            // Rule 341:  PrimaryNoNewArray ::= FieldAccess
            //
            case 341:
                break;
            //
            // Rule 342:  PrimaryNoNewArray ::= MethodInvocation
            //
            case 342:
                break;
            //
            // Rule 343:  PrimaryNoNewArray ::= ArrayAccess
            //
            case 343:
                break;
            //
            // Rule 344:  Literal ::= IntegerLiteral
            //
            case 344: {
               //#line 794 "GJavaParser.g"
                setResult(
                    //#line 794 GJavaParser.g
                    ast_pool.Next()=new Literal0(getRhsIToken(1))
                //#line 794 GJavaParser.g
                );
            break;
            }
            //
            // Rule 345:  Literal ::= LongLiteral
            //
            case 345: {
               //#line 795 "GJavaParser.g"
                setResult(
                    //#line 795 GJavaParser.g
                    ast_pool.Next()=new Literal1(getRhsIToken(1))
                //#line 795 GJavaParser.g
                );
            break;
            }
            //
            // Rule 346:  Literal ::= FloatingPointLiteral
            //
            case 346: {
               //#line 796 "GJavaParser.g"
                setResult(
                    //#line 796 GJavaParser.g
                    ast_pool.Next()=new Literal2(getRhsIToken(1))
                //#line 796 GJavaParser.g
                );
            break;
            }
            //
            // Rule 347:  Literal ::= DoubleLiteral
            //
            case 347: {
               //#line 797 "GJavaParser.g"
                setResult(
                    //#line 797 GJavaParser.g
                    ast_pool.Next()=new Literal3(getRhsIToken(1))
                //#line 797 GJavaParser.g
                );
            break;
            }
            //
            // Rule 348:  Literal ::= BooleanLiteral
            //
            case 348:
                break;
            //
            // Rule 349:  Literal ::= CharacterLiteral
            //
            case 349: {
               //#line 799 "GJavaParser.g"
                setResult(
                    //#line 799 GJavaParser.g
                    ast_pool.Next()=new Literal4(getRhsIToken(1))
                //#line 799 GJavaParser.g
                );
            break;
            }
            //
            // Rule 350:  Literal ::= StringLiteral
            //
            case 350: {
               //#line 800 "GJavaParser.g"
                setResult(
                    //#line 800 GJavaParser.g
                    ast_pool.Next()=new Literal5(getRhsIToken(1))
                //#line 800 GJavaParser.g
                );
            break;
            }
            //
            // Rule 351:  Literal ::= null
            //
            case 351: {
               //#line 801 "GJavaParser.g"
                setResult(
                    //#line 801 GJavaParser.g
                    ast_pool.Next()=new Literal6(getRhsIToken(1))
                //#line 801 GJavaParser.g
                );
            break;
            }
            //
            // Rule 352:  BooleanLiteral ::= true
            //
            case 352: {
               //#line 803 "GJavaParser.g"
                setResult(
                    //#line 803 GJavaParser.g
                    ast_pool.Next()=new BooleanLiteral0(getRhsIToken(1))
                //#line 803 GJavaParser.g
                );
            break;
            }
            //
            // Rule 353:  BooleanLiteral ::= false
            //
            case 353: {
               //#line 804 "GJavaParser.g"
                setResult(
                    //#line 804 GJavaParser.g
                    ast_pool.Next()=new BooleanLiteral1(getRhsIToken(1))
                //#line 804 GJavaParser.g
                );
            break;
            }
            //
            // Rule 354:  ClassInstanceCreationExpression ::= new TypeArgumentsopt ClassOrInterfaceType TypeArgumentsopt ( ArgumentListopt ) ClassBodyopt
            //
            case 354: {
               //#line 811 "GJavaParser.g"
                setResult(
                    //#line 811 GJavaParser.g
                    ast_pool.Next()=new ClassInstanceCreationExpression0(getLeftIToken(), getRightIToken(),
                                                         //#line 811 GJavaParser.g
                                                         ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                         //#line 811 GJavaParser.g
                                                         (IAst*)getRhsSym(2),
                                                         //#line 811 GJavaParser.g
                                                         (IAst*)getRhsSym(3),
                                                         //#line 811 GJavaParser.g
                                                         (IAst*)getRhsSym(4),
                                                         //#line 811 GJavaParser.g
                                                         ast_pool.Next()=new AstToken(getRhsIToken(5)),
                                                         //#line 811 GJavaParser.g
                                                         (IAst*)getRhsSym(6),
                                                         //#line 811 GJavaParser.g
                                                         ast_pool.Next()=new AstToken(getRhsIToken(7)),
                                                         //#line 811 GJavaParser.g
                                                         (IAst*)getRhsSym(8))
                //#line 811 GJavaParser.g
                );
            break;
            }
            //
            // Rule 355:  ClassInstanceCreationExpression ::= Primary . new TypeArgumentsopt identifier TypeArgumentsopt ( ArgumentListopt ) ClassBodyopt
            //
            case 355: {
               //#line 812 "GJavaParser.g"
                setResult(
                    //#line 812 GJavaParser.g
                    ast_pool.Next()=new ClassInstanceCreationExpression1(getLeftIToken(), getRightIToken(),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(1),
                                                         //#line 812 GJavaParser.g
                                                         ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                         //#line 812 GJavaParser.g
                                                         ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(4),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(5),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(6),
                                                         //#line 812 GJavaParser.g
                                                         ast_pool.Next()=new AstToken(getRhsIToken(7)),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(8),
                                                         //#line 812 GJavaParser.g
                                                         ast_pool.Next()=new AstToken(getRhsIToken(9)),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(10))
                //#line 812 GJavaParser.g
                );
            break;
            }
            //
            // Rule 356:  ArgumentList ::= Expression
            //
            case 356:
                break;
            //
            // Rule 357:  ArgumentList ::= ArgumentList , Expression
            //
            case 357: {
               //#line 816 "GJavaParser.g"
                setResult(
                    //#line 816 GJavaParser.g
                    ast_pool.Next()=new ArgumentList(getLeftIToken(), getRightIToken(),
                                     //#line 816 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 816 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                     //#line 816 GJavaParser.g
                                     (IAst*)getRhsSym(3))
                //#line 816 GJavaParser.g
                );
            break;
            }
            //
            // Rule 358:  ArrayCreationExpression ::= new PrimitiveType DimExprs Dimsopt
            //
            case 358: {
               //#line 826 "GJavaParser.g"
                setResult(
                    //#line 826 GJavaParser.g
                    ast_pool.Next()=new ArrayCreationExpression0(getLeftIToken(), getRightIToken(),
                                                 //#line 826 GJavaParser.g
                                                 ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                 //#line 826 GJavaParser.g
                                                 (IAst*)getRhsSym(2),
                                                 //#line 826 GJavaParser.g
                                                 (IAst*)getRhsSym(3),
                                                 //#line 826 GJavaParser.g
                                                 (IAst*)getRhsSym(4))
                //#line 826 GJavaParser.g
                );
            break;
            }
            //
            // Rule 359:  ArrayCreationExpression ::= new ClassOrInterfaceType DimExprs Dimsopt
            //
            case 359: {
               //#line 827 "GJavaParser.g"
                setResult(
                    //#line 827 GJavaParser.g
                    ast_pool.Next()=new ArrayCreationExpression1(getLeftIToken(), getRightIToken(),
                                                 //#line 827 GJavaParser.g
                                                 ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                 //#line 827 GJavaParser.g
                                                 (IAst*)getRhsSym(2),
                                                 //#line 827 GJavaParser.g
                                                 (IAst*)getRhsSym(3),
                                                 //#line 827 GJavaParser.g
                                                 (IAst*)getRhsSym(4))
                //#line 827 GJavaParser.g
                );
            break;
            }
            //
            // Rule 360:  ArrayCreationExpression ::= new PrimitiveType Dims ArrayInitializer
            //
            case 360: {
               //#line 828 "GJavaParser.g"
                setResult(
                    //#line 828 GJavaParser.g
                    ast_pool.Next()=new ArrayCreationExpression2(getLeftIToken(), getRightIToken(),
                                                 //#line 828 GJavaParser.g
                                                 ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                 //#line 828 GJavaParser.g
                                                 (IAst*)getRhsSym(2),
                                                 //#line 828 GJavaParser.g
                                                 (IAst*)getRhsSym(3),
                                                 //#line 828 GJavaParser.g
                                                 (IAst*)getRhsSym(4))
                //#line 828 GJavaParser.g
                );
            break;
            }
            //
            // Rule 361:  ArrayCreationExpression ::= new ClassOrInterfaceType Dims ArrayInitializer
            //
            case 361: {
               //#line 829 "GJavaParser.g"
                setResult(
                    //#line 829 GJavaParser.g
                    ast_pool.Next()=new ArrayCreationExpression3(getLeftIToken(), getRightIToken(),
                                                 //#line 829 GJavaParser.g
                                                 ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                 //#line 829 GJavaParser.g
                                                 (IAst*)getRhsSym(2),
                                                 //#line 829 GJavaParser.g
                                                 (IAst*)getRhsSym(3),
                                                 //#line 829 GJavaParser.g
                                                 (IAst*)getRhsSym(4))
                //#line 829 GJavaParser.g
                );
            break;
            }
            //
            // Rule 362:  DimExprs ::= DimExpr
            //
            case 362:
                break;
            //
            // Rule 363:  DimExprs ::= DimExprs DimExpr
            //
            case 363: {
               //#line 832 "GJavaParser.g"
                setResult(
                    //#line 832 GJavaParser.g
                    ast_pool.Next()=new DimExprs(getLeftIToken(), getRightIToken(),
                                 //#line 832 GJavaParser.g
                                 (IAst*)getRhsSym(1),
                                 //#line 832 GJavaParser.g
                                 (IAst*)getRhsSym(2))
                //#line 832 GJavaParser.g
                );
            break;
            }
            //
            // Rule 364:  DimExpr ::= [ Expression ]
            //
            case 364: {
               //#line 834 "GJavaParser.g"
                setResult(
                    //#line 834 GJavaParser.g
                    ast_pool.Next()=new DimExpr(getLeftIToken(), getRightIToken(),
                                //#line 834 GJavaParser.g
                                ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                //#line 834 GJavaParser.g
                                (IAst*)getRhsSym(2),
                                //#line 834 GJavaParser.g
                                ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 834 GJavaParser.g
                );
            break;
            }
            //
            // Rule 365:  Dims ::= [ ]
            //
            case 365: {
               //#line 836 "GJavaParser.g"
                setResult(
                    //#line 836 GJavaParser.g
                    ast_pool.Next()=new Dims0(getLeftIToken(), getRightIToken(),
                              //#line 836 GJavaParser.g
                              ast_pool.Next()=new AstToken(getRhsIToken(1)),
                              //#line 836 GJavaParser.g
                              ast_pool.Next()=new AstToken(getRhsIToken(2)))
                //#line 836 GJavaParser.g
                );
            break;
            }
            //
            // Rule 366:  Dims ::= Dims [ ]
            //
            case 366: {
               //#line 837 "GJavaParser.g"
                setResult(
                    //#line 837 GJavaParser.g
                    ast_pool.Next()=new Dims1(getLeftIToken(), getRightIToken(),
                              //#line 837 GJavaParser.g
                              (IAst*)getRhsSym(1),
                              //#line 837 GJavaParser.g
                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                              //#line 837 GJavaParser.g
                              ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 837 GJavaParser.g
                );
            break;
            }
            //
            // Rule 367:  FieldAccess ::= Primary . identifier
            //
            case 367: {
               //#line 839 "GJavaParser.g"
                setResult(
                    //#line 839 GJavaParser.g
                    ast_pool.Next()=new FieldAccess0(getLeftIToken(), getRightIToken(),
                                     //#line 839 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 839 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                     //#line 839 GJavaParser.g
                                     (IAst*)getRhsSym(3))
                //#line 839 GJavaParser.g
                );
            break;
            }
            //
            // Rule 368:  FieldAccess ::= super . identifier
            //
            case 368: {
               //#line 840 "GJavaParser.g"
                setResult(
                    //#line 840 GJavaParser.g
                    ast_pool.Next()=new FieldAccess1(getLeftIToken(), getRightIToken(),
                                     //#line 840 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                     //#line 840 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                     //#line 840 GJavaParser.g
                                     (IAst*)getRhsSym(3))
                //#line 840 GJavaParser.g
                );
            break;
            }
            //
            // Rule 369:  FieldAccess ::= ClassName . super . identifier
            //
            case 369: {
               //#line 841 "GJavaParser.g"
                setResult(
                    //#line 841 GJavaParser.g
                    ast_pool.Next()=new FieldAccess2(getLeftIToken(), getRightIToken(),
                                     //#line 841 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 841 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                     //#line 841 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                     //#line 841 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                     //#line 841 GJavaParser.g
                                     (IAst*)getRhsSym(5))
                //#line 841 GJavaParser.g
                );
            break;
            }
            //
            // Rule 370:  MethodInvocation ::= MethodName ( ArgumentListopt )
            //
            case 370: {
               //#line 843 "GJavaParser.g"
                setResult(
                    //#line 843 GJavaParser.g
                    ast_pool.Next()=new MethodInvocation0(getLeftIToken(), getRightIToken(),
                                          //#line 843 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 843 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 843 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 843 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 843 GJavaParser.g
                );
            break;
            }
            //
            // Rule 371:  MethodInvocation ::= Primary . TypeArgumentsopt identifier ( ArgumentListopt )
            //
            case 371: {
               //#line 844 "GJavaParser.g"
                setResult(
                    //#line 844 GJavaParser.g
                    ast_pool.Next()=new MethodInvocation1(getLeftIToken(), getRightIToken(),
                                          //#line 844 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 844 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 844 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 844 GJavaParser.g
                                          (IAst*)getRhsSym(4),
                                          //#line 844 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(5)),
                                          //#line 844 GJavaParser.g
                                          (IAst*)getRhsSym(6),
                                          //#line 844 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(7)))
                //#line 844 GJavaParser.g
                );
            break;
            }
            //
            // Rule 372:  MethodInvocation ::= super . TypeArgumentsopt identifier ( ArgumentListopt )
            //
            case 372: {
               //#line 845 "GJavaParser.g"
                setResult(
                    //#line 845 GJavaParser.g
                    ast_pool.Next()=new MethodInvocation2(getLeftIToken(), getRightIToken(),
                                          //#line 845 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                          //#line 845 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 845 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 845 GJavaParser.g
                                          (IAst*)getRhsSym(4),
                                          //#line 845 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(5)),
                                          //#line 845 GJavaParser.g
                                          (IAst*)getRhsSym(6),
                                          //#line 845 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(7)))
                //#line 845 GJavaParser.g
                );
            break;
            }
            //
            // Rule 373:  MethodInvocation ::= ClassName . super . TypeArgumentsopt identifier ( ArgumentListopt )
            //
            case 373: {
               //#line 846 "GJavaParser.g"
                setResult(
                    //#line 846 GJavaParser.g
                    ast_pool.Next()=new MethodInvocation3(getLeftIToken(), getRightIToken(),
                                          //#line 846 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 846 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 846 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                          //#line 846 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                          //#line 846 GJavaParser.g
                                          (IAst*)getRhsSym(5),
                                          //#line 846 GJavaParser.g
                                          (IAst*)getRhsSym(6),
                                          //#line 846 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(7)),
                                          //#line 846 GJavaParser.g
                                          (IAst*)getRhsSym(8),
                                          //#line 846 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(9)))
                //#line 846 GJavaParser.g
                );
            break;
            }
            //
            // Rule 374:  MethodInvocation ::= TypeName . TypeArguments identifier ( ArgumentListopt )
            //
            case 374: {
               //#line 847 "GJavaParser.g"
                setResult(
                    //#line 847 GJavaParser.g
                    ast_pool.Next()=new MethodInvocation4(getLeftIToken(), getRightIToken(),
                                          //#line 847 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 847 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                          //#line 847 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 847 GJavaParser.g
                                          (IAst*)getRhsSym(4),
                                          //#line 847 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(5)),
                                          //#line 847 GJavaParser.g
                                          (IAst*)getRhsSym(6),
                                          //#line 847 GJavaParser.g
                                          ast_pool.Next()=new AstToken(getRhsIToken(7)))
                //#line 847 GJavaParser.g
                );
            break;
            }
            //
            // Rule 375:  ArrayAccess ::= ExpressionName [ Expression ]
            //
            case 375: {
               //#line 855 "GJavaParser.g"
                setResult(
                    //#line 855 GJavaParser.g
                    ast_pool.Next()=new ArrayAccess0(getLeftIToken(), getRightIToken(),
                                     //#line 855 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 855 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                     //#line 855 GJavaParser.g
                                     (IAst*)getRhsSym(3),
                                     //#line 855 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 855 GJavaParser.g
                );
            break;
            }
            //
            // Rule 376:  ArrayAccess ::= PrimaryNoNewArray [ Expression ]
            //
            case 376: {
               //#line 856 "GJavaParser.g"
                setResult(
                    //#line 856 GJavaParser.g
                    ast_pool.Next()=new ArrayAccess1(getLeftIToken(), getRightIToken(),
                                     //#line 856 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 856 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                     //#line 856 GJavaParser.g
                                     (IAst*)getRhsSym(3),
                                     //#line 856 GJavaParser.g
                                     ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 856 GJavaParser.g
                );
            break;
            }
            //
            // Rule 377:  PostfixExpression ::= Primary
            //
            case 377:
                break;
            //
            // Rule 378:  PostfixExpression ::= ExpressionName
            //
            case 378:
                break;
            //
            // Rule 379:  PostfixExpression ::= PostIncrementExpression
            //
            case 379:
                break;
            //
            // Rule 380:  PostfixExpression ::= PostDecrementExpression
            //
            case 380:
                break;
            //
            // Rule 381:  PostIncrementExpression ::= PostfixExpression ++
            //
            case 381: {
               //#line 863 "GJavaParser.g"
                setResult(
                    //#line 863 GJavaParser.g
                    ast_pool.Next()=new PostIncrementExpression(getLeftIToken(), getRightIToken(),
                                                //#line 863 GJavaParser.g
                                                (IAst*)getRhsSym(1),
                                                //#line 863 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(2)))
                //#line 863 GJavaParser.g
                );
            break;
            }
            //
            // Rule 382:  PostDecrementExpression ::= PostfixExpression --
            //
            case 382: {
               //#line 865 "GJavaParser.g"
                setResult(
                    //#line 865 GJavaParser.g
                    ast_pool.Next()=new PostDecrementExpression(getLeftIToken(), getRightIToken(),
                                                //#line 865 GJavaParser.g
                                                (IAst*)getRhsSym(1),
                                                //#line 865 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(2)))
                //#line 865 GJavaParser.g
                );
            break;
            }
            //
            // Rule 383:  UnaryExpression ::= PreIncrementExpression
            //
            case 383:
                break;
            //
            // Rule 384:  UnaryExpression ::= PreDecrementExpression
            //
            case 384:
                break;
            //
            // Rule 385:  UnaryExpression ::= + UnaryExpression
            //
            case 385: {
               //#line 869 "GJavaParser.g"
                setResult(
                    //#line 869 GJavaParser.g
                    ast_pool.Next()=new UnaryExpression0(getLeftIToken(), getRightIToken(),
                                         //#line 869 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                         //#line 869 GJavaParser.g
                                         (IAst*)getRhsSym(2))
                //#line 869 GJavaParser.g
                );
            break;
            }
            //
            // Rule 386:  UnaryExpression ::= - UnaryExpression
            //
            case 386: {
               //#line 870 "GJavaParser.g"
                setResult(
                    //#line 870 GJavaParser.g
                    ast_pool.Next()=new UnaryExpression1(getLeftIToken(), getRightIToken(),
                                         //#line 870 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                         //#line 870 GJavaParser.g
                                         (IAst*)getRhsSym(2))
                //#line 870 GJavaParser.g
                );
            break;
            }
            //
            // Rule 387:  UnaryExpression ::= UnaryExpressionNotPlusMinus
            //
            case 387:
                break;
            //
            // Rule 388:  PreIncrementExpression ::= ++ UnaryExpression
            //
            case 388: {
               //#line 873 "GJavaParser.g"
                setResult(
                    //#line 873 GJavaParser.g
                    ast_pool.Next()=new PreIncrementExpression(getLeftIToken(), getRightIToken(),
                                               //#line 873 GJavaParser.g
                                               ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                               //#line 873 GJavaParser.g
                                               (IAst*)getRhsSym(2))
                //#line 873 GJavaParser.g
                );
            break;
            }
            //
            // Rule 389:  PreDecrementExpression ::= -- UnaryExpression
            //
            case 389: {
               //#line 875 "GJavaParser.g"
                setResult(
                    //#line 875 GJavaParser.g
                    ast_pool.Next()=new PreDecrementExpression(getLeftIToken(), getRightIToken(),
                                               //#line 875 GJavaParser.g
                                               ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                               //#line 875 GJavaParser.g
                                               (IAst*)getRhsSym(2))
                //#line 875 GJavaParser.g
                );
            break;
            }
            //
            // Rule 390:  UnaryExpressionNotPlusMinus ::= PostfixExpression
            //
            case 390:
                break;
            //
            // Rule 391:  UnaryExpressionNotPlusMinus ::= ~ UnaryExpression
            //
            case 391: {
               //#line 878 "GJavaParser.g"
                setResult(
                    //#line 878 GJavaParser.g
                    ast_pool.Next()=new UnaryExpressionNotPlusMinus0(getLeftIToken(), getRightIToken(),
                                                     //#line 878 GJavaParser.g
                                                     ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                     //#line 878 GJavaParser.g
                                                     (IAst*)getRhsSym(2))
                //#line 878 GJavaParser.g
                );
            break;
            }
            //
            // Rule 392:  UnaryExpressionNotPlusMinus ::= ! UnaryExpression
            //
            case 392: {
               //#line 879 "GJavaParser.g"
                setResult(
                    //#line 879 GJavaParser.g
                    ast_pool.Next()=new UnaryExpressionNotPlusMinus1(getLeftIToken(), getRightIToken(),
                                                     //#line 879 GJavaParser.g
                                                     ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                                     //#line 879 GJavaParser.g
                                                     (IAst*)getRhsSym(2))
                //#line 879 GJavaParser.g
                );
            break;
            }
            //
            // Rule 393:  UnaryExpressionNotPlusMinus ::= CastExpression
            //
            case 393:
                break;
            //
            // Rule 394:  CastExpression ::= ( PrimitiveType Dimsopt ) UnaryExpression
            //
            case 394: {
               //#line 882 "GJavaParser.g"
                setResult(
                    //#line 882 GJavaParser.g
                    ast_pool.Next()=new CastExpression0(getLeftIToken(), getRightIToken(),
                                        //#line 882 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                        //#line 882 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 882 GJavaParser.g
                                        (IAst*)getRhsSym(3),
                                        //#line 882 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                        //#line 882 GJavaParser.g
                                        (IAst*)getRhsSym(5))
                //#line 882 GJavaParser.g
                );
            break;
            }
            //
            // Rule 395:  CastExpression ::= ( ReferenceType ) UnaryExpressionNotPlusMinus
            //
            case 395: {
               //#line 883 "GJavaParser.g"
                setResult(
                    //#line 883 GJavaParser.g
                    ast_pool.Next()=new CastExpression1(getLeftIToken(), getRightIToken(),
                                        //#line 883 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                        //#line 883 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 883 GJavaParser.g
                                        ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                        //#line 883 GJavaParser.g
                                        (IAst*)getRhsSym(4))
                //#line 883 GJavaParser.g
                );
            break;
            }
            //
            // Rule 396:  MultiplicativeExpression ::= UnaryExpression
            //
            case 396:
                break;
            //
            // Rule 397:  MultiplicativeExpression ::= MultiplicativeExpression * UnaryExpression
            //
            case 397: {
               //#line 886 "GJavaParser.g"
                setResult(
                    //#line 886 GJavaParser.g
                    ast_pool.Next()=new MultiplicativeExpression0(getLeftIToken(), getRightIToken(),
                                                  //#line 886 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 886 GJavaParser.g
                                                  ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                  //#line 886 GJavaParser.g
                                                  (IAst*)getRhsSym(3))
                //#line 886 GJavaParser.g
                );
            break;
            }
            //
            // Rule 398:  MultiplicativeExpression ::= MultiplicativeExpression / UnaryExpression
            //
            case 398: {
               //#line 887 "GJavaParser.g"
                setResult(
                    //#line 887 GJavaParser.g
                    ast_pool.Next()=new MultiplicativeExpression1(getLeftIToken(), getRightIToken(),
                                                  //#line 887 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 887 GJavaParser.g
                                                  ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                  //#line 887 GJavaParser.g
                                                  (IAst*)getRhsSym(3))
                //#line 887 GJavaParser.g
                );
            break;
            }
            //
            // Rule 399:  MultiplicativeExpression ::= MultiplicativeExpression % UnaryExpression
            //
            case 399: {
               //#line 888 "GJavaParser.g"
                setResult(
                    //#line 888 GJavaParser.g
                    ast_pool.Next()=new MultiplicativeExpression2(getLeftIToken(), getRightIToken(),
                                                  //#line 888 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 888 GJavaParser.g
                                                  ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                  //#line 888 GJavaParser.g
                                                  (IAst*)getRhsSym(3))
                //#line 888 GJavaParser.g
                );
            break;
            }
            //
            // Rule 400:  AdditiveExpression ::= MultiplicativeExpression
            //
            case 400:
                break;
            //
            // Rule 401:  AdditiveExpression ::= AdditiveExpression + MultiplicativeExpression
            //
            case 401: {
               //#line 891 "GJavaParser.g"
                setResult(
                    //#line 891 GJavaParser.g
                    ast_pool.Next()=new AdditiveExpression0(getLeftIToken(), getRightIToken(),
                                            //#line 891 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 891 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                            //#line 891 GJavaParser.g
                                            (IAst*)getRhsSym(3))
                //#line 891 GJavaParser.g
                );
            break;
            }
            //
            // Rule 402:  AdditiveExpression ::= AdditiveExpression - MultiplicativeExpression
            //
            case 402: {
               //#line 892 "GJavaParser.g"
                setResult(
                    //#line 892 GJavaParser.g
                    ast_pool.Next()=new AdditiveExpression1(getLeftIToken(), getRightIToken(),
                                            //#line 892 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 892 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                            //#line 892 GJavaParser.g
                                            (IAst*)getRhsSym(3))
                //#line 892 GJavaParser.g
                );
            break;
            }
            //
            // Rule 403:  ShiftExpression ::= AdditiveExpression
            //
            case 403:
                break;
            //
            // Rule 404:  ShiftExpression ::= ShiftExpression << AdditiveExpression
            //
            case 404: {
               //#line 895 "GJavaParser.g"
                setResult(
                    //#line 895 GJavaParser.g
                    ast_pool.Next()=new ShiftExpression0(getLeftIToken(), getRightIToken(),
                                         //#line 895 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 895 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                         //#line 895 GJavaParser.g
                                         (IAst*)getRhsSym(3))
                //#line 895 GJavaParser.g
                );
            break;
            }
            //
            // Rule 405:  ShiftExpression ::= ShiftExpression > > AdditiveExpression
            //
            case 405: {
               //#line 896 "GJavaParser.g"
                setResult(
                    //#line 896 GJavaParser.g
                    ast_pool.Next()=new ShiftExpression1(getLeftIToken(), getRightIToken(),
                                         //#line 896 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 896 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                         //#line 896 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                         //#line 896 GJavaParser.g
                                         (IAst*)getRhsSym(4))
                //#line 896 GJavaParser.g
                );
            break;
            }
            //
            // Rule 406:  ShiftExpression ::= ShiftExpression > > > AdditiveExpression
            //
            case 406: {
               //#line 897 "GJavaParser.g"
                setResult(
                    //#line 897 GJavaParser.g
                    ast_pool.Next()=new ShiftExpression2(getLeftIToken(), getRightIToken(),
                                         //#line 897 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 897 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                         //#line 897 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                         //#line 897 GJavaParser.g
                                         ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                         //#line 897 GJavaParser.g
                                         (IAst*)getRhsSym(5))
                //#line 897 GJavaParser.g
                );
            break;
            }
            //
            // Rule 407:  RelationalExpression ::= ShiftExpression
            //
            case 407:
                break;
            //
            // Rule 408:  RelationalExpression ::= RelationalExpression < ShiftExpression
            //
            case 408: {
               //#line 900 "GJavaParser.g"
                setResult(
                    //#line 900 GJavaParser.g
                    ast_pool.Next()=new RelationalExpression0(getLeftIToken(), getRightIToken(),
                                              //#line 900 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 900 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 900 GJavaParser.g
                                              (IAst*)getRhsSym(3))
                //#line 900 GJavaParser.g
                );
            break;
            }
            //
            // Rule 409:  RelationalExpression ::= RelationalExpression > ShiftExpression
            //
            case 409: {
               //#line 901 "GJavaParser.g"
                setResult(
                    //#line 901 GJavaParser.g
                    ast_pool.Next()=new RelationalExpression1(getLeftIToken(), getRightIToken(),
                                              //#line 901 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 901 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 901 GJavaParser.g
                                              (IAst*)getRhsSym(3))
                //#line 901 GJavaParser.g
                );
            break;
            }
            //
            // Rule 410:  RelationalExpression ::= RelationalExpression <= ShiftExpression
            //
            case 410: {
               //#line 902 "GJavaParser.g"
                setResult(
                    //#line 902 GJavaParser.g
                    ast_pool.Next()=new RelationalExpression2(getLeftIToken(), getRightIToken(),
                                              //#line 902 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 902 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 902 GJavaParser.g
                                              (IAst*)getRhsSym(3))
                //#line 902 GJavaParser.g
                );
            break;
            }
            //
            // Rule 411:  RelationalExpression ::= RelationalExpression > = ShiftExpression
            //
            case 411: {
               //#line 903 "GJavaParser.g"
                setResult(
                    //#line 903 GJavaParser.g
                    ast_pool.Next()=new RelationalExpression3(getLeftIToken(), getRightIToken(),
                                              //#line 903 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 903 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 903 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                              //#line 903 GJavaParser.g
                                              (IAst*)getRhsSym(4))
                //#line 903 GJavaParser.g
                );
            break;
            }
            //
            // Rule 412:  RelationalExpression ::= RelationalExpression instanceof ReferenceType
            //
            case 412: {
               //#line 904 "GJavaParser.g"
                setResult(
                    //#line 904 GJavaParser.g
                    ast_pool.Next()=new RelationalExpression4(getLeftIToken(), getRightIToken(),
                                              //#line 904 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 904 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 904 GJavaParser.g
                                              (IAst*)getRhsSym(3))
                //#line 904 GJavaParser.g
                );
            break;
            }
            //
            // Rule 413:  EqualityExpression ::= RelationalExpression
            //
            case 413:
                break;
            //
            // Rule 414:  EqualityExpression ::= EqualityExpression == RelationalExpression
            //
            case 414: {
               //#line 907 "GJavaParser.g"
                setResult(
                    //#line 907 GJavaParser.g
                    ast_pool.Next()=new EqualityExpression0(getLeftIToken(), getRightIToken(),
                                            //#line 907 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 907 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                            //#line 907 GJavaParser.g
                                            (IAst*)getRhsSym(3))
                //#line 907 GJavaParser.g
                );
            break;
            }
            //
            // Rule 415:  EqualityExpression ::= EqualityExpression != RelationalExpression
            //
            case 415: {
               //#line 908 "GJavaParser.g"
                setResult(
                    //#line 908 GJavaParser.g
                    ast_pool.Next()=new EqualityExpression1(getLeftIToken(), getRightIToken(),
                                            //#line 908 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 908 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                            //#line 908 GJavaParser.g
                                            (IAst*)getRhsSym(3))
                //#line 908 GJavaParser.g
                );
            break;
            }
            //
            // Rule 416:  AndExpression ::= EqualityExpression
            //
            case 416:
                break;
            //
            // Rule 417:  AndExpression ::= AndExpression & EqualityExpression
            //
            case 417: {
               //#line 911 "GJavaParser.g"
                setResult(
                    //#line 911 GJavaParser.g
                    ast_pool.Next()=new AndExpression(getLeftIToken(), getRightIToken(),
                                      //#line 911 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 911 GJavaParser.g
                                      ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                      //#line 911 GJavaParser.g
                                      (IAst*)getRhsSym(3))
                //#line 911 GJavaParser.g
                );
            break;
            }
            //
            // Rule 418:  ExclusiveOrExpression ::= AndExpression
            //
            case 418:
                break;
            //
            // Rule 419:  ExclusiveOrExpression ::= ExclusiveOrExpression ^ AndExpression
            //
            case 419: {
               //#line 914 "GJavaParser.g"
                setResult(
                    //#line 914 GJavaParser.g
                    ast_pool.Next()=new ExclusiveOrExpression(getLeftIToken(), getRightIToken(),
                                              //#line 914 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 914 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 914 GJavaParser.g
                                              (IAst*)getRhsSym(3))
                //#line 914 GJavaParser.g
                );
            break;
            }
            //
            // Rule 420:  InclusiveOrExpression ::= ExclusiveOrExpression
            //
            case 420:
                break;
            //
            // Rule 421:  InclusiveOrExpression ::= InclusiveOrExpression | ExclusiveOrExpression
            //
            case 421: {
               //#line 917 "GJavaParser.g"
                setResult(
                    //#line 917 GJavaParser.g
                    ast_pool.Next()=new InclusiveOrExpression(getLeftIToken(), getRightIToken(),
                                              //#line 917 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 917 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 917 GJavaParser.g
                                              (IAst*)getRhsSym(3))
                //#line 917 GJavaParser.g
                );
            break;
            }
            //
            // Rule 422:  ConditionalAndExpression ::= InclusiveOrExpression
            //
            case 422:
                break;
            //
            // Rule 423:  ConditionalAndExpression ::= ConditionalAndExpression && InclusiveOrExpression
            //
            case 423: {
               //#line 920 "GJavaParser.g"
                setResult(
                    //#line 920 GJavaParser.g
                    ast_pool.Next()=new ConditionalAndExpression(getLeftIToken(), getRightIToken(),
                                                 //#line 920 GJavaParser.g
                                                 (IAst*)getRhsSym(1),
                                                 //#line 920 GJavaParser.g
                                                 ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                 //#line 920 GJavaParser.g
                                                 (IAst*)getRhsSym(3))
                //#line 920 GJavaParser.g
                );
            break;
            }
            //
            // Rule 424:  ConditionalOrExpression ::= ConditionalAndExpression
            //
            case 424:
                break;
            //
            // Rule 425:  ConditionalOrExpression ::= ConditionalOrExpression || ConditionalAndExpression
            //
            case 425: {
               //#line 923 "GJavaParser.g"
                setResult(
                    //#line 923 GJavaParser.g
                    ast_pool.Next()=new ConditionalOrExpression(getLeftIToken(), getRightIToken(),
                                                //#line 923 GJavaParser.g
                                                (IAst*)getRhsSym(1),
                                                //#line 923 GJavaParser.g
                                                ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                                //#line 923 GJavaParser.g
                                                (IAst*)getRhsSym(3))
                //#line 923 GJavaParser.g
                );
            break;
            }
            //
            // Rule 426:  ConditionalExpression ::= ConditionalOrExpression
            //
            case 426:
                break;
            //
            // Rule 427:  ConditionalExpression ::= ConditionalOrExpression ? Expression : ConditionalExpression
            //
            case 427: {
               //#line 926 "GJavaParser.g"
                setResult(
                    //#line 926 GJavaParser.g
                    ast_pool.Next()=new ConditionalExpression(getLeftIToken(), getRightIToken(),
                                              //#line 926 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 926 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                              //#line 926 GJavaParser.g
                                              (IAst*)getRhsSym(3),
                                              //#line 926 GJavaParser.g
                                              ast_pool.Next()=new AstToken(getRhsIToken(4)),
                                              //#line 926 GJavaParser.g
                                              (IAst*)getRhsSym(5))
                //#line 926 GJavaParser.g
                );
            break;
            }
            //
            // Rule 428:  AssignmentExpression ::= ConditionalExpression
            //
            case 428:
                break;
            //
            // Rule 429:  AssignmentExpression ::= Assignment
            //
            case 429:
                break;
            //
            // Rule 430:  Assignment ::= LeftHandSide AssignmentOperator AssignmentExpression
            //
            case 430: {
               //#line 931 "GJavaParser.g"
                setResult(
                    //#line 931 GJavaParser.g
                    ast_pool.Next()=new Assignment(getLeftIToken(), getRightIToken(),
                                   //#line 931 GJavaParser.g
                                   (IAst*)getRhsSym(1),
                                   //#line 931 GJavaParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 931 GJavaParser.g
                                   (IAst*)getRhsSym(3))
                //#line 931 GJavaParser.g
                );
            break;
            }
            //
            // Rule 431:  LeftHandSide ::= ExpressionName
            //
            case 431:
                break;
            //
            // Rule 432:  LeftHandSide ::= FieldAccess
            //
            case 432:
                break;
            //
            // Rule 433:  LeftHandSide ::= ArrayAccess
            //
            case 433:
                break;
            //
            // Rule 434:  AssignmentOperator ::= =
            //
            case 434: {
               //#line 937 "GJavaParser.g"
                setResult(
                    //#line 937 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator0(getRhsIToken(1))
                //#line 937 GJavaParser.g
                );
            break;
            }
            //
            // Rule 435:  AssignmentOperator ::= *=
            //
            case 435: {
               //#line 938 "GJavaParser.g"
                setResult(
                    //#line 938 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator1(getRhsIToken(1))
                //#line 938 GJavaParser.g
                );
            break;
            }
            //
            // Rule 436:  AssignmentOperator ::= /=
            //
            case 436: {
               //#line 939 "GJavaParser.g"
                setResult(
                    //#line 939 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator2(getRhsIToken(1))
                //#line 939 GJavaParser.g
                );
            break;
            }
            //
            // Rule 437:  AssignmentOperator ::= %=
            //
            case 437: {
               //#line 940 "GJavaParser.g"
                setResult(
                    //#line 940 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator3(getRhsIToken(1))
                //#line 940 GJavaParser.g
                );
            break;
            }
            //
            // Rule 438:  AssignmentOperator ::= +=
            //
            case 438: {
               //#line 941 "GJavaParser.g"
                setResult(
                    //#line 941 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator4(getRhsIToken(1))
                //#line 941 GJavaParser.g
                );
            break;
            }
            //
            // Rule 439:  AssignmentOperator ::= -=
            //
            case 439: {
               //#line 942 "GJavaParser.g"
                setResult(
                    //#line 942 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator5(getRhsIToken(1))
                //#line 942 GJavaParser.g
                );
            break;
            }
            //
            // Rule 440:  AssignmentOperator ::= <<=
            //
            case 440: {
               //#line 943 "GJavaParser.g"
                setResult(
                    //#line 943 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator6(getRhsIToken(1))
                //#line 943 GJavaParser.g
                );
            break;
            }
            //
            // Rule 441:  AssignmentOperator ::= > > =
            //
            case 441: {
               //#line 944 "GJavaParser.g"
                setResult(
                    //#line 944 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator7(getLeftIToken(), getRightIToken(),
                                            //#line 944 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                            //#line 944 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                            //#line 944 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(3)))
                //#line 944 GJavaParser.g
                );
            break;
            }
            //
            // Rule 442:  AssignmentOperator ::= > > > =
            //
            case 442: {
               //#line 945 "GJavaParser.g"
                setResult(
                    //#line 945 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator8(getLeftIToken(), getRightIToken(),
                                            //#line 945 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(1)),
                                            //#line 945 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(2)),
                                            //#line 945 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(3)),
                                            //#line 945 GJavaParser.g
                                            ast_pool.Next()=new AstToken(getRhsIToken(4)))
                //#line 945 GJavaParser.g
                );
            break;
            }
            //
            // Rule 443:  AssignmentOperator ::= &=
            //
            case 443: {
               //#line 946 "GJavaParser.g"
                setResult(
                    //#line 946 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator9(getRhsIToken(1))
                //#line 946 GJavaParser.g
                );
            break;
            }
            //
            // Rule 444:  AssignmentOperator ::= ^=
            //
            case 444: {
               //#line 947 "GJavaParser.g"
                setResult(
                    //#line 947 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator10(getRhsIToken(1))
                //#line 947 GJavaParser.g
                );
            break;
            }
            //
            // Rule 445:  AssignmentOperator ::= |=
            //
            case 445: {
               //#line 948 "GJavaParser.g"
                setResult(
                    //#line 948 GJavaParser.g
                    ast_pool.Next()=new AssignmentOperator11(getRhsIToken(1))
                //#line 948 GJavaParser.g
                );
            break;
            }
            //
            // Rule 446:  Expression ::= AssignmentExpression
            //
            case 446:
                break;
            //
            // Rule 447:  ConstantExpression ::= Expression
            //
            case 447:
                break;
            //
            // Rule 448:  Dimsopt ::= $Empty
            //
            case 448: {
               //#line 957 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 449:  Dimsopt ::= Dims
            //
            case 449:
                break;
            //
            // Rule 450:  Catchesopt ::= $Empty
            //
            case 450: {
               //#line 960 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 451:  Catchesopt ::= Catches
            //
            case 451:
                break;
            //
            // Rule 452:  identifieropt ::= $Empty
            //
            case 452: {
               //#line 963 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 453:  identifieropt ::= identifier
            //
            case 453:
                break;
            //
            // Rule 454:  ForUpdateopt ::= $Empty
            //
            case 454: {
               //#line 966 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 455:  ForUpdateopt ::= ForUpdate
            //
            case 455:
                break;
            //
            // Rule 456:  Expressionopt ::= $Empty
            //
            case 456: {
               //#line 969 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 457:  Expressionopt ::= Expression
            //
            case 457:
                break;
            //
            // Rule 458:  ForInitopt ::= $Empty
            //
            case 458: {
               //#line 972 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 459:  ForInitopt ::= ForInit
            //
            case 459:
                break;
            //
            // Rule 460:  SwitchLabelsopt ::= $Empty
            //
            case 460: {
               //#line 975 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 461:  SwitchLabelsopt ::= SwitchLabels
            //
            case 461:
                break;
            //
            // Rule 462:  SwitchBlockStatementGroupsopt ::= $Empty
            //
            case 462: {
               //#line 978 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 463:  SwitchBlockStatementGroupsopt ::= SwitchBlockStatementGroups
            //
            case 463:
                break;
            //
            // Rule 464:  VariableModifiersopt ::= $Empty
            //
            case 464: {
               //#line 981 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 465:  VariableModifiersopt ::= VariableModifiers
            //
            case 465:
                break;
            //
            // Rule 466:  VariableInitializersopt ::= $Empty
            //
            case 466: {
               //#line 984 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 467:  VariableInitializersopt ::= VariableInitializers
            //
            case 467:
                break;
            //
            // Rule 468:  ElementValuesopt ::= $Empty
            //
            case 468: {
               //#line 987 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 469:  ElementValuesopt ::= ElementValues
            //
            case 469:
                break;
            //
            // Rule 470:  ElementValuePairsopt ::= $Empty
            //
            case 470: {
               //#line 990 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 471:  ElementValuePairsopt ::= ElementValuePairs
            //
            case 471:
                break;
            //
            // Rule 472:  DefaultValueopt ::= $Empty
            //
            case 472: {
               //#line 993 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 473:  DefaultValueopt ::= DefaultValue
            //
            case 473:
                break;
            //
            // Rule 474:  AnnotationTypeElementDeclarationsopt ::= $Empty
            //
            case 474: {
               //#line 996 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 475:  AnnotationTypeElementDeclarationsopt ::= AnnotationTypeElementDeclarations
            //
            case 475:
                break;
            //
            // Rule 476:  AbstractMethodModifiersopt ::= $Empty
            //
            case 476: {
               //#line 999 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 477:  AbstractMethodModifiersopt ::= AbstractMethodModifiers
            //
            case 477:
                break;
            //
            // Rule 478:  ConstantModifiersopt ::= $Empty
            //
            case 478: {
               //#line 1002 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 479:  ConstantModifiersopt ::= ConstantModifiers
            //
            case 479:
                break;
            //
            // Rule 480:  InterfaceMemberDeclarationsopt ::= $Empty
            //
            case 480: {
               //#line 1005 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 481:  InterfaceMemberDeclarationsopt ::= InterfaceMemberDeclarations
            //
            case 481:
                break;
            //
            // Rule 482:  ExtendsInterfacesopt ::= $Empty
            //
            case 482: {
               //#line 1008 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 483:  ExtendsInterfacesopt ::= ExtendsInterfaces
            //
            case 483:
                break;
            //
            // Rule 484:  InterfaceModifiersopt ::= $Empty
            //
            case 484: {
               //#line 1011 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 485:  InterfaceModifiersopt ::= InterfaceModifiers
            //
            case 485:
                break;
            //
            // Rule 486:  ClassBodyopt ::= $Empty
            //
            case 486: {
               //#line 1014 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 487:  ClassBodyopt ::= ClassBody
            //
            case 487:
                break;
            //
            // Rule 488:  Argumentsopt ::= $Empty
            //
            case 488: {
               //#line 1017 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 489:  Argumentsopt ::= Arguments
            //
            case 489:
                break;
            //
            // Rule 490:  EnumBodyDeclarationsopt ::= $Empty
            //
            case 490: {
               //#line 1020 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 491:  EnumBodyDeclarationsopt ::= EnumBodyDeclarations
            //
            case 491:
                break;
            //
            // Rule 492:  ,opt ::= $Empty
            //
            case 492: {
               //#line 1023 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 493:  ,opt ::= ,
            //
            case 493: {
               //#line 1024 "GJavaParser.g"
                setResult(
                    //#line 1024 GJavaParser.g
                    ast_pool.Next()=new Commaopt(getRhsIToken(1))
                //#line 1024 GJavaParser.g
                );
            break;
            }
            //
            // Rule 494:  EnumConstantsopt ::= $Empty
            //
            case 494: {
               //#line 1026 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 495:  EnumConstantsopt ::= EnumConstants
            //
            case 495:
                break;
            //
            // Rule 496:  ArgumentListopt ::= $Empty
            //
            case 496: {
               //#line 1029 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 497:  ArgumentListopt ::= ArgumentList
            //
            case 497:
                break;
            //
            // Rule 498:  BlockStatementsopt ::= $Empty
            //
            case 498: {
               //#line 1032 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 499:  BlockStatementsopt ::= BlockStatements
            //
            case 499:
                break;
            //
            // Rule 500:  ExplicitConstructorInvocationopt ::= $Empty
            //
            case 500: {
               //#line 1035 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 501:  ExplicitConstructorInvocationopt ::= ExplicitConstructorInvocation
            //
            case 501:
                break;
            //
            // Rule 502:  ConstructorModifiersopt ::= $Empty
            //
            case 502: {
               //#line 1038 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 503:  ConstructorModifiersopt ::= ConstructorModifiers
            //
            case 503:
                break;
            //
            // Rule 504:  ...opt ::= $Empty
            //
            case 504: {
               //#line 1041 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 505:  ...opt ::= ...
            //
            case 505: {
               //#line 1042 "GJavaParser.g"
                setResult(
                    //#line 1042 GJavaParser.g
                    ast_pool.Next()=new Ellipsisopt(getRhsIToken(1))
                //#line 1042 GJavaParser.g
                );
            break;
            }
            //
            // Rule 506:  FormalParameterListopt ::= $Empty
            //
            case 506: {
               //#line 1044 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 507:  FormalParameterListopt ::= FormalParameterList
            //
            case 507:
                break;
            //
            // Rule 508:  Throwsopt ::= $Empty
            //
            case 508: {
               //#line 1047 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 509:  Throwsopt ::= Throws
            //
            case 509:
                break;
            //
            // Rule 510:  MethodModifiersopt ::= $Empty
            //
            case 510: {
               //#line 1050 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 511:  MethodModifiersopt ::= MethodModifiers
            //
            case 511:
                break;
            //
            // Rule 512:  FieldModifiersopt ::= $Empty
            //
            case 512: {
               //#line 1053 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 513:  FieldModifiersopt ::= FieldModifiers
            //
            case 513:
                break;
            //
            // Rule 514:  ClassBodyDeclarationsopt ::= $Empty
            //
            case 514: {
               //#line 1056 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 515:  ClassBodyDeclarationsopt ::= ClassBodyDeclarations
            //
            case 515:
                break;
            //
            // Rule 516:  Interfacesopt ::= $Empty
            //
            case 516: {
               //#line 1059 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 517:  Interfacesopt ::= Interfaces
            //
            case 517:
                break;
            //
            // Rule 518:  Superopt ::= $Empty
            //
            case 518: {
               //#line 1062 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 519:  Superopt ::= Super
            //
            case 519:
                break;
            //
            // Rule 520:  TypeParametersopt ::= $Empty
            //
            case 520: {
               //#line 1065 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 521:  TypeParametersopt ::= TypeParameters
            //
            case 521:
                break;
            //
            // Rule 522:  ClassModifiersopt ::= $Empty
            //
            case 522: {
               //#line 1068 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 523:  ClassModifiersopt ::= ClassModifiers
            //
            case 523:
                break;
            //
            // Rule 524:  Annotationsopt ::= $Empty
            //
            case 524: {
               //#line 1071 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 525:  Annotationsopt ::= Annotations
            //
            case 525:
                break;
            //
            // Rule 526:  TypeDeclarationsopt ::= $Empty
            //
            case 526: {
               //#line 1074 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 527:  TypeDeclarationsopt ::= TypeDeclarations
            //
            case 527:
                break;
            //
            // Rule 528:  ImportDeclarationsopt ::= $Empty
            //
            case 528: {
               //#line 1077 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 529:  ImportDeclarationsopt ::= ImportDeclarations
            //
            case 529:
                break;
            //
            // Rule 530:  PackageDeclarationopt ::= $Empty
            //
            case 530: {
               //#line 1080 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 531:  PackageDeclarationopt ::= PackageDeclaration
            //
            case 531:
                break;
            //
            // Rule 532:  WildcardBoundsOpt ::= $Empty
            //
            case 532: {
               //#line 1083 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 533:  WildcardBoundsOpt ::= WildcardBounds
            //
            case 533:
                break;
            //
            // Rule 534:  AdditionalBoundListopt ::= $Empty
            //
            case 534: {
               //#line 1086 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 535:  AdditionalBoundListopt ::= AdditionalBoundList
            //
            case 535:
                break;
            //
            // Rule 536:  TypeBoundopt ::= $Empty
            //
            case 536: {
               //#line 1089 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 537:  TypeBoundopt ::= TypeBound
            //
            case 537:
                break;
            //
            // Rule 538:  TypeArgumentsopt ::= $Empty
            //
            case 538: {
               //#line 1092 "GJavaParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 539:  TypeArgumentsopt ::= TypeArguments
            //
            case 539:
                break;
    //#line 355 "btParserTemplateF.gi

    
            default:
                break;
        }
        return;
    }
};

