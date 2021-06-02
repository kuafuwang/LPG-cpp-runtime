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
#include "JavaParsersym.h"
#include "JavaParserprs.h"
#include "Object.h"
#include "ParseTable.h"
#include "PrsStream.h"
#include "RuleAction.h"
#include "IcuUtil.h"
#include "stringex.h"
#include "Any.h"




#pragma once
#include "IAbstractArrayList.h"
#include "IAst.h"
namespace JavaParser_top_level_ast{
  struct Visitor;
  struct Ast;
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
  struct AbstractVisitor;
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
   std::vector<Ast   *> getList() { return list; }
    Ast *getElementAt(int i) { return (Ast*) list.at(leftRecursive ? i : list.size() - 1 - i); }
   std::vector<IAst    *> getArrayList()
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
   std::vector<IAst    *> getAllChildren()
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

    identifier(JavaParser *environment, IToken* token):AstToken(token)
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
    Ast *lpg_TypeName;
    TypeArguments *lpg_TypeArgumentsopt;

    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }
    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }

    ClassType(IToken* leftIToken, IToken* rightIToken,
              Ast *lpg_TypeName,
              TypeArguments *lpg_TypeArgumentsopt):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeName);
        list.push_back((IAst*)lpg_TypeArgumentsopt);
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
            ((IAst*)lpg_TypeName)->accept(v);
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
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
    Ast *lpg_TypeName;
    TypeArguments *lpg_TypeArgumentsopt;

    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }
    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }

    InterfaceType(IToken* leftIToken, IToken* rightIToken,
                  Ast *lpg_TypeName,
                  TypeArguments *lpg_TypeArgumentsopt):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeName);
        list.push_back((IAst*)lpg_TypeArgumentsopt);
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
            ((IAst*)lpg_TypeName)->accept(v);
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
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
    Ast *lpg_TypeName;
    AstToken *lpg_DOT;
    identifier *lpg_identifier;

    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }

    TypeName(IToken* leftIToken, IToken* rightIToken,
             Ast *lpg_TypeName,
             AstToken *lpg_DOT,
             identifier *lpg_identifier):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_identifier);
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
            ((IAst*)lpg_TypeName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
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
    Ast *lpg_Type;
    AstToken *lpg_LBRACKET;
    AstToken *lpg_RBRACKET;

    Ast *getType() { return lpg_Type; };
    void setType(Ast *lpg_Type) { this->lpg_Type = lpg_Type; }
    AstToken *getLBRACKET() { return lpg_LBRACKET; };
    void setLBRACKET(AstToken *lpg_LBRACKET) { this->lpg_LBRACKET = lpg_LBRACKET; }
    AstToken *getRBRACKET() { return lpg_RBRACKET; };
    void setRBRACKET(AstToken *lpg_RBRACKET) { this->lpg_RBRACKET = lpg_RBRACKET; }

    ArrayType(IToken* leftIToken, IToken* rightIToken,
              Ast *lpg_Type,
              AstToken *lpg_LBRACKET,
              AstToken *lpg_RBRACKET):Ast(leftIToken, rightIToken)    {
        this->lpg_Type = lpg_Type;
        ((Ast*) lpg_Type)->setParent(this);
        this->lpg_LBRACKET = lpg_LBRACKET;
        ((Ast*) lpg_LBRACKET)->setParent(this);
        this->lpg_RBRACKET = lpg_RBRACKET;
        ((Ast*) lpg_RBRACKET)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Type);
        list.push_back((IAst*)lpg_LBRACKET);
        list.push_back((IAst*)lpg_RBRACKET);
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
            ((IAst*)lpg_Type)->accept(v);
            ((IAst*)lpg_LBRACKET)->accept(v);
            ((IAst*)lpg_RBRACKET)->accept(v);
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
    identifier *lpg_TypeVariable;
    TypeBound *lpg_TypeBoundopt;

    identifier *getTypeVariable() { return lpg_TypeVariable; };
    void setTypeVariable(identifier *lpg_TypeVariable) { this->lpg_TypeVariable = lpg_TypeVariable; }
    /**
     * The value returned by <b>getTypeBoundopt</b> may be <b>nullptr</b>
     */
    TypeBound *getTypeBoundopt() { return lpg_TypeBoundopt; };
    void setTypeBoundopt(TypeBound *lpg_TypeBoundopt) { this->lpg_TypeBoundopt = lpg_TypeBoundopt; }

    TypeParameter(IToken* leftIToken, IToken* rightIToken,
                  identifier *lpg_TypeVariable,
                  TypeBound *lpg_TypeBoundopt):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeVariable = lpg_TypeVariable;
        ((Ast*) lpg_TypeVariable)->setParent(this);
        this->lpg_TypeBoundopt = lpg_TypeBoundopt;
        if (lpg_TypeBoundopt != nullptr) ((Ast*) lpg_TypeBoundopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeVariable);
        list.push_back((IAst*)lpg_TypeBoundopt);
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
            ((IAst*)lpg_TypeVariable)->accept(v);
            if (lpg_TypeBoundopt != nullptr) ((IAst*)lpg_TypeBoundopt)->accept(v);
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
    AstToken *lpg_extends;
    ClassType *lpg_ClassOrInterfaceType;
    Ast *lpg_AdditionalBoundListopt;

    AstToken *getextends() { return lpg_extends; };
    void setextends(AstToken *lpg_extends) { this->lpg_extends = lpg_extends; }
    ClassType *getClassOrInterfaceType() { return lpg_ClassOrInterfaceType; };
    void setClassOrInterfaceType(ClassType *lpg_ClassOrInterfaceType) { this->lpg_ClassOrInterfaceType = lpg_ClassOrInterfaceType; }
    /**
     * The value returned by <b>getAdditionalBoundListopt</b> may be <b>nullptr</b>
     */
    Ast *getAdditionalBoundListopt() { return lpg_AdditionalBoundListopt; };
    void setAdditionalBoundListopt(Ast *lpg_AdditionalBoundListopt) { this->lpg_AdditionalBoundListopt = lpg_AdditionalBoundListopt; }

    TypeBound(IToken* leftIToken, IToken* rightIToken,
              AstToken *lpg_extends,
              ClassType *lpg_ClassOrInterfaceType,
              Ast *lpg_AdditionalBoundListopt):Ast(leftIToken, rightIToken)    {
        this->lpg_extends = lpg_extends;
        ((Ast*) lpg_extends)->setParent(this);
        this->lpg_ClassOrInterfaceType = lpg_ClassOrInterfaceType;
        ((Ast*) lpg_ClassOrInterfaceType)->setParent(this);
        this->lpg_AdditionalBoundListopt = lpg_AdditionalBoundListopt;
        if (lpg_AdditionalBoundListopt != nullptr) ((Ast*) lpg_AdditionalBoundListopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_extends);
        list.push_back((IAst*)lpg_ClassOrInterfaceType);
        list.push_back((IAst*)lpg_AdditionalBoundListopt);
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
            ((IAst*)lpg_extends)->accept(v);
            ((IAst*)lpg_ClassOrInterfaceType)->accept(v);
            if (lpg_AdditionalBoundListopt != nullptr) ((IAst*)lpg_AdditionalBoundListopt)->accept(v);
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
    Ast *lpg_AdditionalBoundList;
    AdditionalBound *lpg_AdditionalBound;

    Ast *getAdditionalBoundList() { return lpg_AdditionalBoundList; };
    void setAdditionalBoundList(Ast *lpg_AdditionalBoundList) { this->lpg_AdditionalBoundList = lpg_AdditionalBoundList; }
    AdditionalBound *getAdditionalBound() { return lpg_AdditionalBound; };
    void setAdditionalBound(AdditionalBound *lpg_AdditionalBound) { this->lpg_AdditionalBound = lpg_AdditionalBound; }

    AdditionalBoundList(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_AdditionalBoundList,
                        AdditionalBound *lpg_AdditionalBound):Ast(leftIToken, rightIToken)    {
        this->lpg_AdditionalBoundList = lpg_AdditionalBoundList;
        ((Ast*) lpg_AdditionalBoundList)->setParent(this);
        this->lpg_AdditionalBound = lpg_AdditionalBound;
        ((Ast*) lpg_AdditionalBound)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AdditionalBoundList);
        list.push_back((IAst*)lpg_AdditionalBound);
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
            ((IAst*)lpg_AdditionalBoundList)->accept(v);
            ((IAst*)lpg_AdditionalBound)->accept(v);
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
    AstToken *lpg_AND;
    InterfaceType *lpg_InterfaceType;

    AstToken *getAND() { return lpg_AND; };
    void setAND(AstToken *lpg_AND) { this->lpg_AND = lpg_AND; }
    InterfaceType *getInterfaceType() { return lpg_InterfaceType; };
    void setInterfaceType(InterfaceType *lpg_InterfaceType) { this->lpg_InterfaceType = lpg_InterfaceType; }

    AdditionalBound(IToken* leftIToken, IToken* rightIToken,
                    AstToken *lpg_AND,
                    InterfaceType *lpg_InterfaceType):Ast(leftIToken, rightIToken)    {
        this->lpg_AND = lpg_AND;
        ((Ast*) lpg_AND)->setParent(this);
        this->lpg_InterfaceType = lpg_InterfaceType;
        ((Ast*) lpg_InterfaceType)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AND);
        list.push_back((IAst*)lpg_InterfaceType);
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
            ((IAst*)lpg_AND)->accept(v);
            ((IAst*)lpg_InterfaceType)->accept(v);
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
    AstToken *lpg_LESS;
    Ast *lpg_ActualTypeArgumentList;
    AstToken *lpg_GREATER;

    AstToken *getLESS() { return lpg_LESS; };
    void setLESS(AstToken *lpg_LESS) { this->lpg_LESS = lpg_LESS; }
    Ast *getActualTypeArgumentList() { return lpg_ActualTypeArgumentList; };
    void setActualTypeArgumentList(Ast *lpg_ActualTypeArgumentList) { this->lpg_ActualTypeArgumentList = lpg_ActualTypeArgumentList; }
    AstToken *getGREATER() { return lpg_GREATER; };
    void setGREATER(AstToken *lpg_GREATER) { this->lpg_GREATER = lpg_GREATER; }

    TypeArguments(IToken* leftIToken, IToken* rightIToken,
                  AstToken *lpg_LESS,
                  Ast *lpg_ActualTypeArgumentList,
                  AstToken *lpg_GREATER):Ast(leftIToken, rightIToken)    {
        this->lpg_LESS = lpg_LESS;
        ((Ast*) lpg_LESS)->setParent(this);
        this->lpg_ActualTypeArgumentList = lpg_ActualTypeArgumentList;
        ((Ast*) lpg_ActualTypeArgumentList)->setParent(this);
        this->lpg_GREATER = lpg_GREATER;
        ((Ast*) lpg_GREATER)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LESS);
        list.push_back((IAst*)lpg_ActualTypeArgumentList);
        list.push_back((IAst*)lpg_GREATER);
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
            ((IAst*)lpg_LESS)->accept(v);
            ((IAst*)lpg_ActualTypeArgumentList)->accept(v);
            ((IAst*)lpg_GREATER)->accept(v);
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
    Ast *lpg_ActualTypeArgumentList;
    AstToken *lpg_COMMA;
    Ast *lpg_ActualTypeArgument;

    Ast *getActualTypeArgumentList() { return lpg_ActualTypeArgumentList; };
    void setActualTypeArgumentList(Ast *lpg_ActualTypeArgumentList) { this->lpg_ActualTypeArgumentList = lpg_ActualTypeArgumentList; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    Ast *getActualTypeArgument() { return lpg_ActualTypeArgument; };
    void setActualTypeArgument(Ast *lpg_ActualTypeArgument) { this->lpg_ActualTypeArgument = lpg_ActualTypeArgument; }

    ActualTypeArgumentList(IToken* leftIToken, IToken* rightIToken,
                           Ast *lpg_ActualTypeArgumentList,
                           AstToken *lpg_COMMA,
                           Ast *lpg_ActualTypeArgument):Ast(leftIToken, rightIToken)    {
        this->lpg_ActualTypeArgumentList = lpg_ActualTypeArgumentList;
        ((Ast*) lpg_ActualTypeArgumentList)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_ActualTypeArgument = lpg_ActualTypeArgument;
        ((Ast*) lpg_ActualTypeArgument)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ActualTypeArgumentList);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_ActualTypeArgument);
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
            ((IAst*)lpg_ActualTypeArgumentList)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_ActualTypeArgument)->accept(v);
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
    AstToken *lpg_QUESTION;
    Ast *lpg_WildcardBoundsOpt;

    AstToken *getQUESTION() { return lpg_QUESTION; };
    void setQUESTION(AstToken *lpg_QUESTION) { this->lpg_QUESTION = lpg_QUESTION; }
    /**
     * The value returned by <b>getWildcardBoundsOpt</b> may be <b>nullptr</b>
     */
    Ast *getWildcardBoundsOpt() { return lpg_WildcardBoundsOpt; };
    void setWildcardBoundsOpt(Ast *lpg_WildcardBoundsOpt) { this->lpg_WildcardBoundsOpt = lpg_WildcardBoundsOpt; }

    Wildcard(IToken* leftIToken, IToken* rightIToken,
             AstToken *lpg_QUESTION,
             Ast *lpg_WildcardBoundsOpt):Ast(leftIToken, rightIToken)    {
        this->lpg_QUESTION = lpg_QUESTION;
        ((Ast*) lpg_QUESTION)->setParent(this);
        this->lpg_WildcardBoundsOpt = lpg_WildcardBoundsOpt;
        if (lpg_WildcardBoundsOpt != nullptr) ((Ast*) lpg_WildcardBoundsOpt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_QUESTION);
        list.push_back((IAst*)lpg_WildcardBoundsOpt);
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
            ((IAst*)lpg_QUESTION)->accept(v);
            if (lpg_WildcardBoundsOpt != nullptr) ((IAst*)lpg_WildcardBoundsOpt)->accept(v);
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
    Ast *lpg_PackageName;
    AstToken *lpg_DOT;
    identifier *lpg_identifier;

    Ast *getPackageName() { return lpg_PackageName; };
    void setPackageName(Ast *lpg_PackageName) { this->lpg_PackageName = lpg_PackageName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }

    PackageName(IToken* leftIToken, IToken* rightIToken,
                Ast *lpg_PackageName,
                AstToken *lpg_DOT,
                identifier *lpg_identifier):Ast(leftIToken, rightIToken)    {
        this->lpg_PackageName = lpg_PackageName;
        ((Ast*) lpg_PackageName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_PackageName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_identifier);
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
            ((IAst*)lpg_PackageName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
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
    Ast *lpg_AmbiguousName;
    AstToken *lpg_DOT;
    identifier *lpg_identifier;

    Ast *getAmbiguousName() { return lpg_AmbiguousName; };
    void setAmbiguousName(Ast *lpg_AmbiguousName) { this->lpg_AmbiguousName = lpg_AmbiguousName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }

    ExpressionName(IToken* leftIToken, IToken* rightIToken,
                   Ast *lpg_AmbiguousName,
                   AstToken *lpg_DOT,
                   identifier *lpg_identifier):Ast(leftIToken, rightIToken)    {
        this->lpg_AmbiguousName = lpg_AmbiguousName;
        ((Ast*) lpg_AmbiguousName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AmbiguousName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_identifier);
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
            ((IAst*)lpg_AmbiguousName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
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
    Ast *lpg_AmbiguousName;
    AstToken *lpg_DOT;
    identifier *lpg_identifier;

    Ast *getAmbiguousName() { return lpg_AmbiguousName; };
    void setAmbiguousName(Ast *lpg_AmbiguousName) { this->lpg_AmbiguousName = lpg_AmbiguousName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }

    MethodName(IToken* leftIToken, IToken* rightIToken,
               Ast *lpg_AmbiguousName,
               AstToken *lpg_DOT,
               identifier *lpg_identifier):Ast(leftIToken, rightIToken)    {
        this->lpg_AmbiguousName = lpg_AmbiguousName;
        ((Ast*) lpg_AmbiguousName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AmbiguousName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_identifier);
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
            ((IAst*)lpg_AmbiguousName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
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
    Ast *lpg_PackageOrTypeName;
    AstToken *lpg_DOT;
    identifier *lpg_identifier;

    Ast *getPackageOrTypeName() { return lpg_PackageOrTypeName; };
    void setPackageOrTypeName(Ast *lpg_PackageOrTypeName) { this->lpg_PackageOrTypeName = lpg_PackageOrTypeName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }

    PackageOrTypeName(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_PackageOrTypeName,
                      AstToken *lpg_DOT,
                      identifier *lpg_identifier):Ast(leftIToken, rightIToken)    {
        this->lpg_PackageOrTypeName = lpg_PackageOrTypeName;
        ((Ast*) lpg_PackageOrTypeName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_PackageOrTypeName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_identifier);
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
            ((IAst*)lpg_PackageOrTypeName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
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
    Ast *lpg_AmbiguousName;
    AstToken *lpg_DOT;
    identifier *lpg_identifier;

    Ast *getAmbiguousName() { return lpg_AmbiguousName; };
    void setAmbiguousName(Ast *lpg_AmbiguousName) { this->lpg_AmbiguousName = lpg_AmbiguousName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }

    AmbiguousName(IToken* leftIToken, IToken* rightIToken,
                  Ast *lpg_AmbiguousName,
                  AstToken *lpg_DOT,
                  identifier *lpg_identifier):Ast(leftIToken, rightIToken)    {
        this->lpg_AmbiguousName = lpg_AmbiguousName;
        ((Ast*) lpg_AmbiguousName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AmbiguousName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_identifier);
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
            ((IAst*)lpg_AmbiguousName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
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
    PackageDeclaration *lpg_PackageDeclarationopt;
    Ast *lpg_ImportDeclarationsopt;
    Ast *lpg_TypeDeclarationsopt;

    /**
     * The value returned by <b>getPackageDeclarationopt</b> may be <b>nullptr</b>
     */
    PackageDeclaration *getPackageDeclarationopt() { return lpg_PackageDeclarationopt; };
    void setPackageDeclarationopt(PackageDeclaration *lpg_PackageDeclarationopt) { this->lpg_PackageDeclarationopt = lpg_PackageDeclarationopt; }
    /**
     * The value returned by <b>getImportDeclarationsopt</b> may be <b>nullptr</b>
     */
    Ast *getImportDeclarationsopt() { return lpg_ImportDeclarationsopt; };
    void setImportDeclarationsopt(Ast *lpg_ImportDeclarationsopt) { this->lpg_ImportDeclarationsopt = lpg_ImportDeclarationsopt; }
    /**
     * The value returned by <b>getTypeDeclarationsopt</b> may be <b>nullptr</b>
     */
    Ast *getTypeDeclarationsopt() { return lpg_TypeDeclarationsopt; };
    void setTypeDeclarationsopt(Ast *lpg_TypeDeclarationsopt) { this->lpg_TypeDeclarationsopt = lpg_TypeDeclarationsopt; }

    CompilationUnit(IToken* leftIToken, IToken* rightIToken,
                    PackageDeclaration *lpg_PackageDeclarationopt,
                    Ast *lpg_ImportDeclarationsopt,
                    Ast *lpg_TypeDeclarationsopt):Ast(leftIToken, rightIToken)    {
        this->lpg_PackageDeclarationopt = lpg_PackageDeclarationopt;
        if (lpg_PackageDeclarationopt != nullptr) ((Ast*) lpg_PackageDeclarationopt)->setParent(this);
        this->lpg_ImportDeclarationsopt = lpg_ImportDeclarationsopt;
        if (lpg_ImportDeclarationsopt != nullptr) ((Ast*) lpg_ImportDeclarationsopt)->setParent(this);
        this->lpg_TypeDeclarationsopt = lpg_TypeDeclarationsopt;
        if (lpg_TypeDeclarationsopt != nullptr) ((Ast*) lpg_TypeDeclarationsopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_PackageDeclarationopt);
        list.push_back((IAst*)lpg_ImportDeclarationsopt);
        list.push_back((IAst*)lpg_TypeDeclarationsopt);
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
            if (lpg_PackageDeclarationopt != nullptr) ((IAst*)lpg_PackageDeclarationopt)->accept(v);
            if (lpg_ImportDeclarationsopt != nullptr) ((IAst*)lpg_ImportDeclarationsopt)->accept(v);
            if (lpg_TypeDeclarationsopt != nullptr) ((IAst*)lpg_TypeDeclarationsopt)->accept(v);
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
    Ast *lpg_ImportDeclarations;
    Ast *lpg_ImportDeclaration;

    Ast *getImportDeclarations() { return lpg_ImportDeclarations; };
    void setImportDeclarations(Ast *lpg_ImportDeclarations) { this->lpg_ImportDeclarations = lpg_ImportDeclarations; }
    Ast *getImportDeclaration() { return lpg_ImportDeclaration; };
    void setImportDeclaration(Ast *lpg_ImportDeclaration) { this->lpg_ImportDeclaration = lpg_ImportDeclaration; }

    ImportDeclarations(IToken* leftIToken, IToken* rightIToken,
                       Ast *lpg_ImportDeclarations,
                       Ast *lpg_ImportDeclaration):Ast(leftIToken, rightIToken)    {
        this->lpg_ImportDeclarations = lpg_ImportDeclarations;
        ((Ast*) lpg_ImportDeclarations)->setParent(this);
        this->lpg_ImportDeclaration = lpg_ImportDeclaration;
        ((Ast*) lpg_ImportDeclaration)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ImportDeclarations);
        list.push_back((IAst*)lpg_ImportDeclaration);
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
            ((IAst*)lpg_ImportDeclarations)->accept(v);
            ((IAst*)lpg_ImportDeclaration)->accept(v);
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
    Ast *lpg_TypeDeclarations;
    Ast *lpg_TypeDeclaration;

    Ast *getTypeDeclarations() { return lpg_TypeDeclarations; };
    void setTypeDeclarations(Ast *lpg_TypeDeclarations) { this->lpg_TypeDeclarations = lpg_TypeDeclarations; }
    Ast *getTypeDeclaration() { return lpg_TypeDeclaration; };
    void setTypeDeclaration(Ast *lpg_TypeDeclaration) { this->lpg_TypeDeclaration = lpg_TypeDeclaration; }

    TypeDeclarations(IToken* leftIToken, IToken* rightIToken,
                     Ast *lpg_TypeDeclarations,
                     Ast *lpg_TypeDeclaration):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeDeclarations = lpg_TypeDeclarations;
        ((Ast*) lpg_TypeDeclarations)->setParent(this);
        this->lpg_TypeDeclaration = lpg_TypeDeclaration;
        ((Ast*) lpg_TypeDeclaration)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeDeclarations);
        list.push_back((IAst*)lpg_TypeDeclaration);
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
            ((IAst*)lpg_TypeDeclarations)->accept(v);
            ((IAst*)lpg_TypeDeclaration)->accept(v);
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
    Ast *lpg_Annotationsopt;
    AstToken *lpg_package;
    Ast *lpg_PackageName;
    AstToken *lpg_SEMICOLON;

    /**
     * The value returned by <b>getAnnotationsopt</b> may be <b>nullptr</b>
     */
    Ast *getAnnotationsopt() { return lpg_Annotationsopt; };
    void setAnnotationsopt(Ast *lpg_Annotationsopt) { this->lpg_Annotationsopt = lpg_Annotationsopt; }
    AstToken *getpackage() { return lpg_package; };
    void setpackage(AstToken *lpg_package) { this->lpg_package = lpg_package; }
    Ast *getPackageName() { return lpg_PackageName; };
    void setPackageName(Ast *lpg_PackageName) { this->lpg_PackageName = lpg_PackageName; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    PackageDeclaration(IToken* leftIToken, IToken* rightIToken,
                       Ast *lpg_Annotationsopt,
                       AstToken *lpg_package,
                       Ast *lpg_PackageName,
                       AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_Annotationsopt = lpg_Annotationsopt;
        if (lpg_Annotationsopt != nullptr) ((Ast*) lpg_Annotationsopt)->setParent(this);
        this->lpg_package = lpg_package;
        ((Ast*) lpg_package)->setParent(this);
        this->lpg_PackageName = lpg_PackageName;
        ((Ast*) lpg_PackageName)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Annotationsopt);
        list.push_back((IAst*)lpg_package);
        list.push_back((IAst*)lpg_PackageName);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            if (lpg_Annotationsopt != nullptr) ((IAst*)lpg_Annotationsopt)->accept(v);
            ((IAst*)lpg_package)->accept(v);
            ((IAst*)lpg_PackageName)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_import;
    Ast *lpg_TypeName;
    AstToken *lpg_SEMICOLON;

    AstToken *getimport() { return lpg_import; };
    void setimport(AstToken *lpg_import) { this->lpg_import = lpg_import; }
    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    SingleTypeImportDeclaration(IToken* leftIToken, IToken* rightIToken,
                                AstToken *lpg_import,
                                Ast *lpg_TypeName,
                                AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_import = lpg_import;
        ((Ast*) lpg_import)->setParent(this);
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_import);
        list.push_back((IAst*)lpg_TypeName);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_import)->accept(v);
            ((IAst*)lpg_TypeName)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_import;
    Ast *lpg_PackageOrTypeName;
    AstToken *lpg_DOT;
    AstToken *lpg_MULTIPLY;
    AstToken *lpg_SEMICOLON;

    AstToken *getimport() { return lpg_import; };
    void setimport(AstToken *lpg_import) { this->lpg_import = lpg_import; }
    Ast *getPackageOrTypeName() { return lpg_PackageOrTypeName; };
    void setPackageOrTypeName(Ast *lpg_PackageOrTypeName) { this->lpg_PackageOrTypeName = lpg_PackageOrTypeName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    AstToken *getMULTIPLY() { return lpg_MULTIPLY; };
    void setMULTIPLY(AstToken *lpg_MULTIPLY) { this->lpg_MULTIPLY = lpg_MULTIPLY; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    TypeImportOnDemandDeclaration(IToken* leftIToken, IToken* rightIToken,
                                  AstToken *lpg_import,
                                  Ast *lpg_PackageOrTypeName,
                                  AstToken *lpg_DOT,
                                  AstToken *lpg_MULTIPLY,
                                  AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_import = lpg_import;
        ((Ast*) lpg_import)->setParent(this);
        this->lpg_PackageOrTypeName = lpg_PackageOrTypeName;
        ((Ast*) lpg_PackageOrTypeName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_MULTIPLY = lpg_MULTIPLY;
        ((Ast*) lpg_MULTIPLY)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_import);
        list.push_back((IAst*)lpg_PackageOrTypeName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_MULTIPLY);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_import)->accept(v);
            ((IAst*)lpg_PackageOrTypeName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_MULTIPLY)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_import;
    AstToken *lpg_static;
    Ast *lpg_TypeName;
    AstToken *lpg_DOT;
    identifier *lpg_identifier;
    AstToken *lpg_SEMICOLON;

    AstToken *getimport() { return lpg_import; };
    void setimport(AstToken *lpg_import) { this->lpg_import = lpg_import; }
    AstToken *getstatic() { return lpg_static; };
    void setstatic(AstToken *lpg_static) { this->lpg_static = lpg_static; }
    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    SingleStaticImportDeclaration(IToken* leftIToken, IToken* rightIToken,
                                  AstToken *lpg_import,
                                  AstToken *lpg_static,
                                  Ast *lpg_TypeName,
                                  AstToken *lpg_DOT,
                                  identifier *lpg_identifier,
                                  AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_import = lpg_import;
        ((Ast*) lpg_import)->setParent(this);
        this->lpg_static = lpg_static;
        ((Ast*) lpg_static)->setParent(this);
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_import);
        list.push_back((IAst*)lpg_static);
        list.push_back((IAst*)lpg_TypeName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_import)->accept(v);
            ((IAst*)lpg_static)->accept(v);
            ((IAst*)lpg_TypeName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_import;
    AstToken *lpg_static;
    Ast *lpg_TypeName;
    AstToken *lpg_DOT;
    AstToken *lpg_MULTIPLY;
    AstToken *lpg_SEMICOLON;

    AstToken *getimport() { return lpg_import; };
    void setimport(AstToken *lpg_import) { this->lpg_import = lpg_import; }
    AstToken *getstatic() { return lpg_static; };
    void setstatic(AstToken *lpg_static) { this->lpg_static = lpg_static; }
    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    AstToken *getMULTIPLY() { return lpg_MULTIPLY; };
    void setMULTIPLY(AstToken *lpg_MULTIPLY) { this->lpg_MULTIPLY = lpg_MULTIPLY; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    StaticImportOnDemandDeclaration(IToken* leftIToken, IToken* rightIToken,
                                    AstToken *lpg_import,
                                    AstToken *lpg_static,
                                    Ast *lpg_TypeName,
                                    AstToken *lpg_DOT,
                                    AstToken *lpg_MULTIPLY,
                                    AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_import = lpg_import;
        ((Ast*) lpg_import)->setParent(this);
        this->lpg_static = lpg_static;
        ((Ast*) lpg_static)->setParent(this);
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_MULTIPLY = lpg_MULTIPLY;
        ((Ast*) lpg_MULTIPLY)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_import);
        list.push_back((IAst*)lpg_static);
        list.push_back((IAst*)lpg_TypeName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_MULTIPLY);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_import)->accept(v);
            ((IAst*)lpg_static)->accept(v);
            ((IAst*)lpg_TypeName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_MULTIPLY)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    Ast *lpg_ClassModifiersopt;
    AstToken *lpg_class;
    identifier *lpg_identifier;
    TypeParameters *lpg_TypeParametersopt;
    Super *lpg_Superopt;
    Interfaces *lpg_Interfacesopt;
    ClassBody *lpg_ClassBody;

    /**
     * The value returned by <b>getClassModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getClassModifiersopt() { return lpg_ClassModifiersopt; };
    void setClassModifiersopt(Ast *lpg_ClassModifiersopt) { this->lpg_ClassModifiersopt = lpg_ClassModifiersopt; }
    AstToken *getclass() { return lpg_class; };
    void setclass(AstToken *lpg_class) { this->lpg_class = lpg_class; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    /**
     * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
     */
    TypeParameters *getTypeParametersopt() { return lpg_TypeParametersopt; };
    void setTypeParametersopt(TypeParameters *lpg_TypeParametersopt) { this->lpg_TypeParametersopt = lpg_TypeParametersopt; }
    /**
     * The value returned by <b>getSuperopt</b> may be <b>nullptr</b>
     */
    Super *getSuperopt() { return lpg_Superopt; };
    void setSuperopt(Super *lpg_Superopt) { this->lpg_Superopt = lpg_Superopt; }
    /**
     * The value returned by <b>getInterfacesopt</b> may be <b>nullptr</b>
     */
    Interfaces *getInterfacesopt() { return lpg_Interfacesopt; };
    void setInterfacesopt(Interfaces *lpg_Interfacesopt) { this->lpg_Interfacesopt = lpg_Interfacesopt; }
    ClassBody *getClassBody() { return lpg_ClassBody; };
    void setClassBody(ClassBody *lpg_ClassBody) { this->lpg_ClassBody = lpg_ClassBody; }

    NormalClassDeclaration(IToken* leftIToken, IToken* rightIToken,
                           Ast *lpg_ClassModifiersopt,
                           AstToken *lpg_class,
                           identifier *lpg_identifier,
                           TypeParameters *lpg_TypeParametersopt,
                           Super *lpg_Superopt,
                           Interfaces *lpg_Interfacesopt,
                           ClassBody *lpg_ClassBody):Ast(leftIToken, rightIToken)    {
        this->lpg_ClassModifiersopt = lpg_ClassModifiersopt;
        if (lpg_ClassModifiersopt != nullptr) ((Ast*) lpg_ClassModifiersopt)->setParent(this);
        this->lpg_class = lpg_class;
        ((Ast*) lpg_class)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_TypeParametersopt = lpg_TypeParametersopt;
        if (lpg_TypeParametersopt != nullptr) ((Ast*) lpg_TypeParametersopt)->setParent(this);
        this->lpg_Superopt = lpg_Superopt;
        if (lpg_Superopt != nullptr) ((Ast*) lpg_Superopt)->setParent(this);
        this->lpg_Interfacesopt = lpg_Interfacesopt;
        if (lpg_Interfacesopt != nullptr) ((Ast*) lpg_Interfacesopt)->setParent(this);
        this->lpg_ClassBody = lpg_ClassBody;
        ((Ast*) lpg_ClassBody)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ClassModifiersopt);
        list.push_back((IAst*)lpg_class);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_TypeParametersopt);
        list.push_back((IAst*)lpg_Superopt);
        list.push_back((IAst*)lpg_Interfacesopt);
        list.push_back((IAst*)lpg_ClassBody);
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
            if (lpg_ClassModifiersopt != nullptr) ((IAst*)lpg_ClassModifiersopt)->accept(v);
            ((IAst*)lpg_class)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            if (lpg_TypeParametersopt != nullptr) ((IAst*)lpg_TypeParametersopt)->accept(v);
            if (lpg_Superopt != nullptr) ((IAst*)lpg_Superopt)->accept(v);
            if (lpg_Interfacesopt != nullptr) ((IAst*)lpg_Interfacesopt)->accept(v);
            ((IAst*)lpg_ClassBody)->accept(v);
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
    Ast *lpg_ClassModifiers;
    Ast *lpg_ClassModifier;

    Ast *getClassModifiers() { return lpg_ClassModifiers; };
    void setClassModifiers(Ast *lpg_ClassModifiers) { this->lpg_ClassModifiers = lpg_ClassModifiers; }
    Ast *getClassModifier() { return lpg_ClassModifier; };
    void setClassModifier(Ast *lpg_ClassModifier) { this->lpg_ClassModifier = lpg_ClassModifier; }

    ClassModifiers(IToken* leftIToken, IToken* rightIToken,
                   Ast *lpg_ClassModifiers,
                   Ast *lpg_ClassModifier):Ast(leftIToken, rightIToken)    {
        this->lpg_ClassModifiers = lpg_ClassModifiers;
        ((Ast*) lpg_ClassModifiers)->setParent(this);
        this->lpg_ClassModifier = lpg_ClassModifier;
        ((Ast*) lpg_ClassModifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ClassModifiers);
        list.push_back((IAst*)lpg_ClassModifier);
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
            ((IAst*)lpg_ClassModifiers)->accept(v);
            ((IAst*)lpg_ClassModifier)->accept(v);
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
    AstToken *lpg_LESS;
    Ast *lpg_TypeParameterList;
    AstToken *lpg_GREATER;

    AstToken *getLESS() { return lpg_LESS; };
    void setLESS(AstToken *lpg_LESS) { this->lpg_LESS = lpg_LESS; }
    Ast *getTypeParameterList() { return lpg_TypeParameterList; };
    void setTypeParameterList(Ast *lpg_TypeParameterList) { this->lpg_TypeParameterList = lpg_TypeParameterList; }
    AstToken *getGREATER() { return lpg_GREATER; };
    void setGREATER(AstToken *lpg_GREATER) { this->lpg_GREATER = lpg_GREATER; }

    TypeParameters(IToken* leftIToken, IToken* rightIToken,
                   AstToken *lpg_LESS,
                   Ast *lpg_TypeParameterList,
                   AstToken *lpg_GREATER):Ast(leftIToken, rightIToken)    {
        this->lpg_LESS = lpg_LESS;
        ((Ast*) lpg_LESS)->setParent(this);
        this->lpg_TypeParameterList = lpg_TypeParameterList;
        ((Ast*) lpg_TypeParameterList)->setParent(this);
        this->lpg_GREATER = lpg_GREATER;
        ((Ast*) lpg_GREATER)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LESS);
        list.push_back((IAst*)lpg_TypeParameterList);
        list.push_back((IAst*)lpg_GREATER);
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
            ((IAst*)lpg_LESS)->accept(v);
            ((IAst*)lpg_TypeParameterList)->accept(v);
            ((IAst*)lpg_GREATER)->accept(v);
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
    Ast *lpg_TypeParameterList;
    AstToken *lpg_COMMA;
    TypeParameter *lpg_TypeParameter;

    Ast *getTypeParameterList() { return lpg_TypeParameterList; };
    void setTypeParameterList(Ast *lpg_TypeParameterList) { this->lpg_TypeParameterList = lpg_TypeParameterList; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    TypeParameter *getTypeParameter() { return lpg_TypeParameter; };
    void setTypeParameter(TypeParameter *lpg_TypeParameter) { this->lpg_TypeParameter = lpg_TypeParameter; }

    TypeParameterList(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_TypeParameterList,
                      AstToken *lpg_COMMA,
                      TypeParameter *lpg_TypeParameter):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeParameterList = lpg_TypeParameterList;
        ((Ast*) lpg_TypeParameterList)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_TypeParameter = lpg_TypeParameter;
        ((Ast*) lpg_TypeParameter)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeParameterList);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_TypeParameter);
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
            ((IAst*)lpg_TypeParameterList)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_TypeParameter)->accept(v);
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
    AstToken *lpg_extends;
    ClassType *lpg_ClassType;

    AstToken *getextends() { return lpg_extends; };
    void setextends(AstToken *lpg_extends) { this->lpg_extends = lpg_extends; }
    ClassType *getClassType() { return lpg_ClassType; };
    void setClassType(ClassType *lpg_ClassType) { this->lpg_ClassType = lpg_ClassType; }

    Super(IToken* leftIToken, IToken* rightIToken,
          AstToken *lpg_extends,
          ClassType *lpg_ClassType):Ast(leftIToken, rightIToken)    {
        this->lpg_extends = lpg_extends;
        ((Ast*) lpg_extends)->setParent(this);
        this->lpg_ClassType = lpg_ClassType;
        ((Ast*) lpg_ClassType)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_extends);
        list.push_back((IAst*)lpg_ClassType);
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
            ((IAst*)lpg_extends)->accept(v);
            ((IAst*)lpg_ClassType)->accept(v);
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
    AstToken *lpg_implements;
    Ast *lpg_InterfaceTypeList;

    AstToken *getimplements() { return lpg_implements; };
    void setimplements(AstToken *lpg_implements) { this->lpg_implements = lpg_implements; }
    Ast *getInterfaceTypeList() { return lpg_InterfaceTypeList; };
    void setInterfaceTypeList(Ast *lpg_InterfaceTypeList) { this->lpg_InterfaceTypeList = lpg_InterfaceTypeList; }

    Interfaces(IToken* leftIToken, IToken* rightIToken,
               AstToken *lpg_implements,
               Ast *lpg_InterfaceTypeList):Ast(leftIToken, rightIToken)    {
        this->lpg_implements = lpg_implements;
        ((Ast*) lpg_implements)->setParent(this);
        this->lpg_InterfaceTypeList = lpg_InterfaceTypeList;
        ((Ast*) lpg_InterfaceTypeList)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_implements);
        list.push_back((IAst*)lpg_InterfaceTypeList);
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
            ((IAst*)lpg_implements)->accept(v);
            ((IAst*)lpg_InterfaceTypeList)->accept(v);
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
    Ast *lpg_InterfaceTypeList;
    AstToken *lpg_COMMA;
    InterfaceType *lpg_InterfaceType;

    Ast *getInterfaceTypeList() { return lpg_InterfaceTypeList; };
    void setInterfaceTypeList(Ast *lpg_InterfaceTypeList) { this->lpg_InterfaceTypeList = lpg_InterfaceTypeList; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    InterfaceType *getInterfaceType() { return lpg_InterfaceType; };
    void setInterfaceType(InterfaceType *lpg_InterfaceType) { this->lpg_InterfaceType = lpg_InterfaceType; }

    InterfaceTypeList(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_InterfaceTypeList,
                      AstToken *lpg_COMMA,
                      InterfaceType *lpg_InterfaceType):Ast(leftIToken, rightIToken)    {
        this->lpg_InterfaceTypeList = lpg_InterfaceTypeList;
        ((Ast*) lpg_InterfaceTypeList)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_InterfaceType = lpg_InterfaceType;
        ((Ast*) lpg_InterfaceType)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_InterfaceTypeList);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_InterfaceType);
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
            ((IAst*)lpg_InterfaceTypeList)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_InterfaceType)->accept(v);
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
    AstToken *lpg_LBRACE;
    Ast *lpg_ClassBodyDeclarationsopt;
    AstToken *lpg_RBRACE;

    AstToken *getLBRACE() { return lpg_LBRACE; };
    void setLBRACE(AstToken *lpg_LBRACE) { this->lpg_LBRACE = lpg_LBRACE; }
    /**
     * The value returned by <b>getClassBodyDeclarationsopt</b> may be <b>nullptr</b>
     */
    Ast *getClassBodyDeclarationsopt() { return lpg_ClassBodyDeclarationsopt; };
    void setClassBodyDeclarationsopt(Ast *lpg_ClassBodyDeclarationsopt) { this->lpg_ClassBodyDeclarationsopt = lpg_ClassBodyDeclarationsopt; }
    AstToken *getRBRACE() { return lpg_RBRACE; };
    void setRBRACE(AstToken *lpg_RBRACE) { this->lpg_RBRACE = lpg_RBRACE; }

    ClassBody(IToken* leftIToken, IToken* rightIToken,
              AstToken *lpg_LBRACE,
              Ast *lpg_ClassBodyDeclarationsopt,
              AstToken *lpg_RBRACE):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACE = lpg_LBRACE;
        ((Ast*) lpg_LBRACE)->setParent(this);
        this->lpg_ClassBodyDeclarationsopt = lpg_ClassBodyDeclarationsopt;
        if (lpg_ClassBodyDeclarationsopt != nullptr) ((Ast*) lpg_ClassBodyDeclarationsopt)->setParent(this);
        this->lpg_RBRACE = lpg_RBRACE;
        ((Ast*) lpg_RBRACE)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACE);
        list.push_back((IAst*)lpg_ClassBodyDeclarationsopt);
        list.push_back((IAst*)lpg_RBRACE);
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
            ((IAst*)lpg_LBRACE)->accept(v);
            if (lpg_ClassBodyDeclarationsopt != nullptr) ((IAst*)lpg_ClassBodyDeclarationsopt)->accept(v);
            ((IAst*)lpg_RBRACE)->accept(v);
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
    Ast *lpg_ClassBodyDeclarations;
    Ast *lpg_ClassBodyDeclaration;

    Ast *getClassBodyDeclarations() { return lpg_ClassBodyDeclarations; };
    void setClassBodyDeclarations(Ast *lpg_ClassBodyDeclarations) { this->lpg_ClassBodyDeclarations = lpg_ClassBodyDeclarations; }
    Ast *getClassBodyDeclaration() { return lpg_ClassBodyDeclaration; };
    void setClassBodyDeclaration(Ast *lpg_ClassBodyDeclaration) { this->lpg_ClassBodyDeclaration = lpg_ClassBodyDeclaration; }

    ClassBodyDeclarations(IToken* leftIToken, IToken* rightIToken,
                          Ast *lpg_ClassBodyDeclarations,
                          Ast *lpg_ClassBodyDeclaration):Ast(leftIToken, rightIToken)    {
        this->lpg_ClassBodyDeclarations = lpg_ClassBodyDeclarations;
        ((Ast*) lpg_ClassBodyDeclarations)->setParent(this);
        this->lpg_ClassBodyDeclaration = lpg_ClassBodyDeclaration;
        ((Ast*) lpg_ClassBodyDeclaration)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ClassBodyDeclarations);
        list.push_back((IAst*)lpg_ClassBodyDeclaration);
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
            ((IAst*)lpg_ClassBodyDeclarations)->accept(v);
            ((IAst*)lpg_ClassBodyDeclaration)->accept(v);
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
    Ast *lpg_FieldModifiersopt;
    Ast *lpg_Type;
    Ast *lpg_VariableDeclarators;
    AstToken *lpg_SEMICOLON;

    /**
     * The value returned by <b>getFieldModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getFieldModifiersopt() { return lpg_FieldModifiersopt; };
    void setFieldModifiersopt(Ast *lpg_FieldModifiersopt) { this->lpg_FieldModifiersopt = lpg_FieldModifiersopt; }
    Ast *getType() { return lpg_Type; };
    void setType(Ast *lpg_Type) { this->lpg_Type = lpg_Type; }
    Ast *getVariableDeclarators() { return lpg_VariableDeclarators; };
    void setVariableDeclarators(Ast *lpg_VariableDeclarators) { this->lpg_VariableDeclarators = lpg_VariableDeclarators; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    FieldDeclaration(IToken* leftIToken, IToken* rightIToken,
                     Ast *lpg_FieldModifiersopt,
                     Ast *lpg_Type,
                     Ast *lpg_VariableDeclarators,
                     AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_FieldModifiersopt = lpg_FieldModifiersopt;
        if (lpg_FieldModifiersopt != nullptr) ((Ast*) lpg_FieldModifiersopt)->setParent(this);
        this->lpg_Type = lpg_Type;
        ((Ast*) lpg_Type)->setParent(this);
        this->lpg_VariableDeclarators = lpg_VariableDeclarators;
        ((Ast*) lpg_VariableDeclarators)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_FieldModifiersopt);
        list.push_back((IAst*)lpg_Type);
        list.push_back((IAst*)lpg_VariableDeclarators);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            if (lpg_FieldModifiersopt != nullptr) ((IAst*)lpg_FieldModifiersopt)->accept(v);
            ((IAst*)lpg_Type)->accept(v);
            ((IAst*)lpg_VariableDeclarators)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    Ast *lpg_VariableDeclarators;
    AstToken *lpg_COMMA;
    Ast *lpg_VariableDeclarator;

    Ast *getVariableDeclarators() { return lpg_VariableDeclarators; };
    void setVariableDeclarators(Ast *lpg_VariableDeclarators) { this->lpg_VariableDeclarators = lpg_VariableDeclarators; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    Ast *getVariableDeclarator() { return lpg_VariableDeclarator; };
    void setVariableDeclarator(Ast *lpg_VariableDeclarator) { this->lpg_VariableDeclarator = lpg_VariableDeclarator; }

    VariableDeclarators(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_VariableDeclarators,
                        AstToken *lpg_COMMA,
                        Ast *lpg_VariableDeclarator):Ast(leftIToken, rightIToken)    {
        this->lpg_VariableDeclarators = lpg_VariableDeclarators;
        ((Ast*) lpg_VariableDeclarators)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_VariableDeclarator = lpg_VariableDeclarator;
        ((Ast*) lpg_VariableDeclarator)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_VariableDeclarators);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_VariableDeclarator);
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
            ((IAst*)lpg_VariableDeclarators)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_VariableDeclarator)->accept(v);
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
    Ast *lpg_VariableDeclaratorId;
    AstToken *lpg_EQUAL;
    Ast *lpg_VariableInitializer;

    Ast *getVariableDeclaratorId() { return lpg_VariableDeclaratorId; };
    void setVariableDeclaratorId(Ast *lpg_VariableDeclaratorId) { this->lpg_VariableDeclaratorId = lpg_VariableDeclaratorId; }
    AstToken *getEQUAL() { return lpg_EQUAL; };
    void setEQUAL(AstToken *lpg_EQUAL) { this->lpg_EQUAL = lpg_EQUAL; }
    Ast *getVariableInitializer() { return lpg_VariableInitializer; };
    void setVariableInitializer(Ast *lpg_VariableInitializer) { this->lpg_VariableInitializer = lpg_VariableInitializer; }

    VariableDeclarator(IToken* leftIToken, IToken* rightIToken,
                       Ast *lpg_VariableDeclaratorId,
                       AstToken *lpg_EQUAL,
                       Ast *lpg_VariableInitializer):Ast(leftIToken, rightIToken)    {
        this->lpg_VariableDeclaratorId = lpg_VariableDeclaratorId;
        ((Ast*) lpg_VariableDeclaratorId)->setParent(this);
        this->lpg_EQUAL = lpg_EQUAL;
        ((Ast*) lpg_EQUAL)->setParent(this);
        this->lpg_VariableInitializer = lpg_VariableInitializer;
        ((Ast*) lpg_VariableInitializer)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_VariableDeclaratorId);
        list.push_back((IAst*)lpg_EQUAL);
        list.push_back((IAst*)lpg_VariableInitializer);
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
            ((IAst*)lpg_VariableDeclaratorId)->accept(v);
            ((IAst*)lpg_EQUAL)->accept(v);
            ((IAst*)lpg_VariableInitializer)->accept(v);
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
    Ast *lpg_VariableDeclaratorId;
    AstToken *lpg_LBRACKET;
    AstToken *lpg_RBRACKET;

    Ast *getVariableDeclaratorId() { return lpg_VariableDeclaratorId; };
    void setVariableDeclaratorId(Ast *lpg_VariableDeclaratorId) { this->lpg_VariableDeclaratorId = lpg_VariableDeclaratorId; }
    AstToken *getLBRACKET() { return lpg_LBRACKET; };
    void setLBRACKET(AstToken *lpg_LBRACKET) { this->lpg_LBRACKET = lpg_LBRACKET; }
    AstToken *getRBRACKET() { return lpg_RBRACKET; };
    void setRBRACKET(AstToken *lpg_RBRACKET) { this->lpg_RBRACKET = lpg_RBRACKET; }

    VariableDeclaratorId(IToken* leftIToken, IToken* rightIToken,
                         Ast *lpg_VariableDeclaratorId,
                         AstToken *lpg_LBRACKET,
                         AstToken *lpg_RBRACKET):Ast(leftIToken, rightIToken)    {
        this->lpg_VariableDeclaratorId = lpg_VariableDeclaratorId;
        ((Ast*) lpg_VariableDeclaratorId)->setParent(this);
        this->lpg_LBRACKET = lpg_LBRACKET;
        ((Ast*) lpg_LBRACKET)->setParent(this);
        this->lpg_RBRACKET = lpg_RBRACKET;
        ((Ast*) lpg_RBRACKET)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_VariableDeclaratorId);
        list.push_back((IAst*)lpg_LBRACKET);
        list.push_back((IAst*)lpg_RBRACKET);
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
            ((IAst*)lpg_VariableDeclaratorId)->accept(v);
            ((IAst*)lpg_LBRACKET)->accept(v);
            ((IAst*)lpg_RBRACKET)->accept(v);
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
    Ast *lpg_FieldModifiers;
    Ast *lpg_FieldModifier;

    Ast *getFieldModifiers() { return lpg_FieldModifiers; };
    void setFieldModifiers(Ast *lpg_FieldModifiers) { this->lpg_FieldModifiers = lpg_FieldModifiers; }
    Ast *getFieldModifier() { return lpg_FieldModifier; };
    void setFieldModifier(Ast *lpg_FieldModifier) { this->lpg_FieldModifier = lpg_FieldModifier; }

    FieldModifiers(IToken* leftIToken, IToken* rightIToken,
                   Ast *lpg_FieldModifiers,
                   Ast *lpg_FieldModifier):Ast(leftIToken, rightIToken)    {
        this->lpg_FieldModifiers = lpg_FieldModifiers;
        ((Ast*) lpg_FieldModifiers)->setParent(this);
        this->lpg_FieldModifier = lpg_FieldModifier;
        ((Ast*) lpg_FieldModifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_FieldModifiers);
        list.push_back((IAst*)lpg_FieldModifier);
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
            ((IAst*)lpg_FieldModifiers)->accept(v);
            ((IAst*)lpg_FieldModifier)->accept(v);
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
    MethodHeader *lpg_MethodHeader;
    Ast *lpg_MethodBody;

    MethodHeader *getMethodHeader() { return lpg_MethodHeader; };
    void setMethodHeader(MethodHeader *lpg_MethodHeader) { this->lpg_MethodHeader = lpg_MethodHeader; }
    Ast *getMethodBody() { return lpg_MethodBody; };
    void setMethodBody(Ast *lpg_MethodBody) { this->lpg_MethodBody = lpg_MethodBody; }

    MethodDeclaration(IToken* leftIToken, IToken* rightIToken,
                      MethodHeader *lpg_MethodHeader,
                      Ast *lpg_MethodBody):Ast(leftIToken, rightIToken)    {
        this->lpg_MethodHeader = lpg_MethodHeader;
        ((Ast*) lpg_MethodHeader)->setParent(this);
        this->lpg_MethodBody = lpg_MethodBody;
        ((Ast*) lpg_MethodBody)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MethodHeader);
        list.push_back((IAst*)lpg_MethodBody);
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
            ((IAst*)lpg_MethodHeader)->accept(v);
            ((IAst*)lpg_MethodBody)->accept(v);
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
    Ast *lpg_MethodModifiersopt;
    TypeParameters *lpg_TypeParametersopt;
    Ast *lpg_ResultType;
    Ast *lpg_MethodDeclarator;
    Throws *lpg_Throwsopt;

    /**
     * The value returned by <b>getMethodModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getMethodModifiersopt() { return lpg_MethodModifiersopt; };
    void setMethodModifiersopt(Ast *lpg_MethodModifiersopt) { this->lpg_MethodModifiersopt = lpg_MethodModifiersopt; }
    /**
     * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
     */
    TypeParameters *getTypeParametersopt() { return lpg_TypeParametersopt; };
    void setTypeParametersopt(TypeParameters *lpg_TypeParametersopt) { this->lpg_TypeParametersopt = lpg_TypeParametersopt; }
    Ast *getResultType() { return lpg_ResultType; };
    void setResultType(Ast *lpg_ResultType) { this->lpg_ResultType = lpg_ResultType; }
    Ast *getMethodDeclarator() { return lpg_MethodDeclarator; };
    void setMethodDeclarator(Ast *lpg_MethodDeclarator) { this->lpg_MethodDeclarator = lpg_MethodDeclarator; }
    /**
     * The value returned by <b>getThrowsopt</b> may be <b>nullptr</b>
     */
    Throws *getThrowsopt() { return lpg_Throwsopt; };
    void setThrowsopt(Throws *lpg_Throwsopt) { this->lpg_Throwsopt = lpg_Throwsopt; }

    MethodHeader(IToken* leftIToken, IToken* rightIToken,
                 Ast *lpg_MethodModifiersopt,
                 TypeParameters *lpg_TypeParametersopt,
                 Ast *lpg_ResultType,
                 Ast *lpg_MethodDeclarator,
                 Throws *lpg_Throwsopt):Ast(leftIToken, rightIToken)    {
        this->lpg_MethodModifiersopt = lpg_MethodModifiersopt;
        if (lpg_MethodModifiersopt != nullptr) ((Ast*) lpg_MethodModifiersopt)->setParent(this);
        this->lpg_TypeParametersopt = lpg_TypeParametersopt;
        if (lpg_TypeParametersopt != nullptr) ((Ast*) lpg_TypeParametersopt)->setParent(this);
        this->lpg_ResultType = lpg_ResultType;
        ((Ast*) lpg_ResultType)->setParent(this);
        this->lpg_MethodDeclarator = lpg_MethodDeclarator;
        ((Ast*) lpg_MethodDeclarator)->setParent(this);
        this->lpg_Throwsopt = lpg_Throwsopt;
        if (lpg_Throwsopt != nullptr) ((Ast*) lpg_Throwsopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MethodModifiersopt);
        list.push_back((IAst*)lpg_TypeParametersopt);
        list.push_back((IAst*)lpg_ResultType);
        list.push_back((IAst*)lpg_MethodDeclarator);
        list.push_back((IAst*)lpg_Throwsopt);
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
            if (lpg_MethodModifiersopt != nullptr) ((IAst*)lpg_MethodModifiersopt)->accept(v);
            if (lpg_TypeParametersopt != nullptr) ((IAst*)lpg_TypeParametersopt)->accept(v);
            ((IAst*)lpg_ResultType)->accept(v);
            ((IAst*)lpg_MethodDeclarator)->accept(v);
            if (lpg_Throwsopt != nullptr) ((IAst*)lpg_Throwsopt)->accept(v);
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
    Ast *lpg_FormalParameters;
    AstToken *lpg_COMMA;
    LastFormalParameter *lpg_LastFormalParameter;

    Ast *getFormalParameters() { return lpg_FormalParameters; };
    void setFormalParameters(Ast *lpg_FormalParameters) { this->lpg_FormalParameters = lpg_FormalParameters; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    LastFormalParameter *getLastFormalParameter() { return lpg_LastFormalParameter; };
    void setLastFormalParameter(LastFormalParameter *lpg_LastFormalParameter) { this->lpg_LastFormalParameter = lpg_LastFormalParameter; }

    FormalParameterList(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_FormalParameters,
                        AstToken *lpg_COMMA,
                        LastFormalParameter *lpg_LastFormalParameter):Ast(leftIToken, rightIToken)    {
        this->lpg_FormalParameters = lpg_FormalParameters;
        ((Ast*) lpg_FormalParameters)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_LastFormalParameter = lpg_LastFormalParameter;
        ((Ast*) lpg_LastFormalParameter)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_FormalParameters);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_LastFormalParameter);
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
            ((IAst*)lpg_FormalParameters)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_LastFormalParameter)->accept(v);
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
    Ast *lpg_FormalParameters;
    AstToken *lpg_COMMA;
    FormalParameter *lpg_FormalParameter;

    Ast *getFormalParameters() { return lpg_FormalParameters; };
    void setFormalParameters(Ast *lpg_FormalParameters) { this->lpg_FormalParameters = lpg_FormalParameters; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    FormalParameter *getFormalParameter() { return lpg_FormalParameter; };
    void setFormalParameter(FormalParameter *lpg_FormalParameter) { this->lpg_FormalParameter = lpg_FormalParameter; }

    FormalParameters(IToken* leftIToken, IToken* rightIToken,
                     Ast *lpg_FormalParameters,
                     AstToken *lpg_COMMA,
                     FormalParameter *lpg_FormalParameter):Ast(leftIToken, rightIToken)    {
        this->lpg_FormalParameters = lpg_FormalParameters;
        ((Ast*) lpg_FormalParameters)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_FormalParameter = lpg_FormalParameter;
        ((Ast*) lpg_FormalParameter)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_FormalParameters);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_FormalParameter);
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
            ((IAst*)lpg_FormalParameters)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_FormalParameter)->accept(v);
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
    Ast *lpg_VariableModifiersopt;
    Ast *lpg_Type;
    Ast *lpg_VariableDeclaratorId;

    /**
     * The value returned by <b>getVariableModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getVariableModifiersopt() { return lpg_VariableModifiersopt; };
    void setVariableModifiersopt(Ast *lpg_VariableModifiersopt) { this->lpg_VariableModifiersopt = lpg_VariableModifiersopt; }
    Ast *getType() { return lpg_Type; };
    void setType(Ast *lpg_Type) { this->lpg_Type = lpg_Type; }
    Ast *getVariableDeclaratorId() { return lpg_VariableDeclaratorId; };
    void setVariableDeclaratorId(Ast *lpg_VariableDeclaratorId) { this->lpg_VariableDeclaratorId = lpg_VariableDeclaratorId; }

    FormalParameter(IToken* leftIToken, IToken* rightIToken,
                    Ast *lpg_VariableModifiersopt,
                    Ast *lpg_Type,
                    Ast *lpg_VariableDeclaratorId):Ast(leftIToken, rightIToken)    {
        this->lpg_VariableModifiersopt = lpg_VariableModifiersopt;
        if (lpg_VariableModifiersopt != nullptr) ((Ast*) lpg_VariableModifiersopt)->setParent(this);
        this->lpg_Type = lpg_Type;
        ((Ast*) lpg_Type)->setParent(this);
        this->lpg_VariableDeclaratorId = lpg_VariableDeclaratorId;
        ((Ast*) lpg_VariableDeclaratorId)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_VariableModifiersopt);
        list.push_back((IAst*)lpg_Type);
        list.push_back((IAst*)lpg_VariableDeclaratorId);
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
            if (lpg_VariableModifiersopt != nullptr) ((IAst*)lpg_VariableModifiersopt)->accept(v);
            ((IAst*)lpg_Type)->accept(v);
            ((IAst*)lpg_VariableDeclaratorId)->accept(v);
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
    Ast *lpg_VariableModifiers;
    Ast *lpg_VariableModifier;

    Ast *getVariableModifiers() { return lpg_VariableModifiers; };
    void setVariableModifiers(Ast *lpg_VariableModifiers) { this->lpg_VariableModifiers = lpg_VariableModifiers; }
    Ast *getVariableModifier() { return lpg_VariableModifier; };
    void setVariableModifier(Ast *lpg_VariableModifier) { this->lpg_VariableModifier = lpg_VariableModifier; }

    VariableModifiers(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_VariableModifiers,
                      Ast *lpg_VariableModifier):Ast(leftIToken, rightIToken)    {
        this->lpg_VariableModifiers = lpg_VariableModifiers;
        ((Ast*) lpg_VariableModifiers)->setParent(this);
        this->lpg_VariableModifier = lpg_VariableModifier;
        ((Ast*) lpg_VariableModifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_VariableModifiers);
        list.push_back((IAst*)lpg_VariableModifier);
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
            ((IAst*)lpg_VariableModifiers)->accept(v);
            ((IAst*)lpg_VariableModifier)->accept(v);
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
    Ast *lpg_VariableModifiersopt;
    Ast *lpg_Type;
    Ellipsisopt *lpg_Ellipsisopt;
    Ast *lpg_VariableDeclaratorId;

    /**
     * The value returned by <b>getVariableModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getVariableModifiersopt() { return lpg_VariableModifiersopt; };
    void setVariableModifiersopt(Ast *lpg_VariableModifiersopt) { this->lpg_VariableModifiersopt = lpg_VariableModifiersopt; }
    Ast *getType() { return lpg_Type; };
    void setType(Ast *lpg_Type) { this->lpg_Type = lpg_Type; }
    /**
     * The value returned by <b>getEllipsisopt</b> may be <b>nullptr</b>
     */
    Ellipsisopt *getEllipsisopt() { return lpg_Ellipsisopt; };
    void setEllipsisopt(Ellipsisopt *lpg_Ellipsisopt) { this->lpg_Ellipsisopt = lpg_Ellipsisopt; }
    Ast *getVariableDeclaratorId() { return lpg_VariableDeclaratorId; };
    void setVariableDeclaratorId(Ast *lpg_VariableDeclaratorId) { this->lpg_VariableDeclaratorId = lpg_VariableDeclaratorId; }

    LastFormalParameter(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_VariableModifiersopt,
                        Ast *lpg_Type,
                        Ellipsisopt *lpg_Ellipsisopt,
                        Ast *lpg_VariableDeclaratorId):Ast(leftIToken, rightIToken)    {
        this->lpg_VariableModifiersopt = lpg_VariableModifiersopt;
        if (lpg_VariableModifiersopt != nullptr) ((Ast*) lpg_VariableModifiersopt)->setParent(this);
        this->lpg_Type = lpg_Type;
        ((Ast*) lpg_Type)->setParent(this);
        this->lpg_Ellipsisopt = lpg_Ellipsisopt;
        if (lpg_Ellipsisopt != nullptr) ((Ast*) lpg_Ellipsisopt)->setParent(this);
        this->lpg_VariableDeclaratorId = lpg_VariableDeclaratorId;
        ((Ast*) lpg_VariableDeclaratorId)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_VariableModifiersopt);
        list.push_back((IAst*)lpg_Type);
        list.push_back((IAst*)lpg_Ellipsisopt);
        list.push_back((IAst*)lpg_VariableDeclaratorId);
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
            if (lpg_VariableModifiersopt != nullptr) ((IAst*)lpg_VariableModifiersopt)->accept(v);
            ((IAst*)lpg_Type)->accept(v);
            if (lpg_Ellipsisopt != nullptr) ((IAst*)lpg_Ellipsisopt)->accept(v);
            ((IAst*)lpg_VariableDeclaratorId)->accept(v);
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
    Ast *lpg_MethodModifiers;
    Ast *lpg_MethodModifier;

    Ast *getMethodModifiers() { return lpg_MethodModifiers; };
    void setMethodModifiers(Ast *lpg_MethodModifiers) { this->lpg_MethodModifiers = lpg_MethodModifiers; }
    Ast *getMethodModifier() { return lpg_MethodModifier; };
    void setMethodModifier(Ast *lpg_MethodModifier) { this->lpg_MethodModifier = lpg_MethodModifier; }

    MethodModifiers(IToken* leftIToken, IToken* rightIToken,
                    Ast *lpg_MethodModifiers,
                    Ast *lpg_MethodModifier):Ast(leftIToken, rightIToken)    {
        this->lpg_MethodModifiers = lpg_MethodModifiers;
        ((Ast*) lpg_MethodModifiers)->setParent(this);
        this->lpg_MethodModifier = lpg_MethodModifier;
        ((Ast*) lpg_MethodModifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MethodModifiers);
        list.push_back((IAst*)lpg_MethodModifier);
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
            ((IAst*)lpg_MethodModifiers)->accept(v);
            ((IAst*)lpg_MethodModifier)->accept(v);
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
    AstToken *lpg_throws;
    Ast *lpg_ExceptionTypeList;

    AstToken *getthrows() { return lpg_throws; };
    void setthrows(AstToken *lpg_throws) { this->lpg_throws = lpg_throws; }
    Ast *getExceptionTypeList() { return lpg_ExceptionTypeList; };
    void setExceptionTypeList(Ast *lpg_ExceptionTypeList) { this->lpg_ExceptionTypeList = lpg_ExceptionTypeList; }

    Throws(IToken* leftIToken, IToken* rightIToken,
           AstToken *lpg_throws,
           Ast *lpg_ExceptionTypeList):Ast(leftIToken, rightIToken)    {
        this->lpg_throws = lpg_throws;
        ((Ast*) lpg_throws)->setParent(this);
        this->lpg_ExceptionTypeList = lpg_ExceptionTypeList;
        ((Ast*) lpg_ExceptionTypeList)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_throws);
        list.push_back((IAst*)lpg_ExceptionTypeList);
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
            ((IAst*)lpg_throws)->accept(v);
            ((IAst*)lpg_ExceptionTypeList)->accept(v);
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
    Ast *lpg_ExceptionTypeList;
    AstToken *lpg_COMMA;
    Ast *lpg_ExceptionType;

    Ast *getExceptionTypeList() { return lpg_ExceptionTypeList; };
    void setExceptionTypeList(Ast *lpg_ExceptionTypeList) { this->lpg_ExceptionTypeList = lpg_ExceptionTypeList; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    Ast *getExceptionType() { return lpg_ExceptionType; };
    void setExceptionType(Ast *lpg_ExceptionType) { this->lpg_ExceptionType = lpg_ExceptionType; }

    ExceptionTypeList(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_ExceptionTypeList,
                      AstToken *lpg_COMMA,
                      Ast *lpg_ExceptionType):Ast(leftIToken, rightIToken)    {
        this->lpg_ExceptionTypeList = lpg_ExceptionTypeList;
        ((Ast*) lpg_ExceptionTypeList)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_ExceptionType = lpg_ExceptionType;
        ((Ast*) lpg_ExceptionType)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ExceptionTypeList);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_ExceptionType);
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
            ((IAst*)lpg_ExceptionTypeList)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_ExceptionType)->accept(v);
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
    AstToken *lpg_static;
    Block *lpg_Block;

    AstToken *getstatic() { return lpg_static; };
    void setstatic(AstToken *lpg_static) { this->lpg_static = lpg_static; }
    Block *getBlock() { return lpg_Block; };
    void setBlock(Block *lpg_Block) { this->lpg_Block = lpg_Block; }

    StaticInitializer(IToken* leftIToken, IToken* rightIToken,
                      AstToken *lpg_static,
                      Block *lpg_Block):Ast(leftIToken, rightIToken)    {
        this->lpg_static = lpg_static;
        ((Ast*) lpg_static)->setParent(this);
        this->lpg_Block = lpg_Block;
        ((Ast*) lpg_Block)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_static);
        list.push_back((IAst*)lpg_Block);
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
            ((IAst*)lpg_static)->accept(v);
            ((IAst*)lpg_Block)->accept(v);
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
    Ast *lpg_ConstructorModifiersopt;
    ConstructorDeclarator *lpg_ConstructorDeclarator;
    Throws *lpg_Throwsopt;
    ConstructorBody *lpg_ConstructorBody;

    /**
     * The value returned by <b>getConstructorModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getConstructorModifiersopt() { return lpg_ConstructorModifiersopt; };
    void setConstructorModifiersopt(Ast *lpg_ConstructorModifiersopt) { this->lpg_ConstructorModifiersopt = lpg_ConstructorModifiersopt; }
    ConstructorDeclarator *getConstructorDeclarator() { return lpg_ConstructorDeclarator; };
    void setConstructorDeclarator(ConstructorDeclarator *lpg_ConstructorDeclarator) { this->lpg_ConstructorDeclarator = lpg_ConstructorDeclarator; }
    /**
     * The value returned by <b>getThrowsopt</b> may be <b>nullptr</b>
     */
    Throws *getThrowsopt() { return lpg_Throwsopt; };
    void setThrowsopt(Throws *lpg_Throwsopt) { this->lpg_Throwsopt = lpg_Throwsopt; }
    ConstructorBody *getConstructorBody() { return lpg_ConstructorBody; };
    void setConstructorBody(ConstructorBody *lpg_ConstructorBody) { this->lpg_ConstructorBody = lpg_ConstructorBody; }

    ConstructorDeclaration(IToken* leftIToken, IToken* rightIToken,
                           Ast *lpg_ConstructorModifiersopt,
                           ConstructorDeclarator *lpg_ConstructorDeclarator,
                           Throws *lpg_Throwsopt,
                           ConstructorBody *lpg_ConstructorBody):Ast(leftIToken, rightIToken)    {
        this->lpg_ConstructorModifiersopt = lpg_ConstructorModifiersopt;
        if (lpg_ConstructorModifiersopt != nullptr) ((Ast*) lpg_ConstructorModifiersopt)->setParent(this);
        this->lpg_ConstructorDeclarator = lpg_ConstructorDeclarator;
        ((Ast*) lpg_ConstructorDeclarator)->setParent(this);
        this->lpg_Throwsopt = lpg_Throwsopt;
        if (lpg_Throwsopt != nullptr) ((Ast*) lpg_Throwsopt)->setParent(this);
        this->lpg_ConstructorBody = lpg_ConstructorBody;
        ((Ast*) lpg_ConstructorBody)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ConstructorModifiersopt);
        list.push_back((IAst*)lpg_ConstructorDeclarator);
        list.push_back((IAst*)lpg_Throwsopt);
        list.push_back((IAst*)lpg_ConstructorBody);
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
            if (lpg_ConstructorModifiersopt != nullptr) ((IAst*)lpg_ConstructorModifiersopt)->accept(v);
            ((IAst*)lpg_ConstructorDeclarator)->accept(v);
            if (lpg_Throwsopt != nullptr) ((IAst*)lpg_Throwsopt)->accept(v);
            ((IAst*)lpg_ConstructorBody)->accept(v);
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
    TypeParameters *lpg_TypeParametersopt;
    identifier *lpg_SimpleTypeName;
    AstToken *lpg_LPAREN;
    Ast *lpg_FormalParameterListopt;
    AstToken *lpg_RPAREN;

    /**
     * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
     */
    TypeParameters *getTypeParametersopt() { return lpg_TypeParametersopt; };
    void setTypeParametersopt(TypeParameters *lpg_TypeParametersopt) { this->lpg_TypeParametersopt = lpg_TypeParametersopt; }
    identifier *getSimpleTypeName() { return lpg_SimpleTypeName; };
    void setSimpleTypeName(identifier *lpg_SimpleTypeName) { this->lpg_SimpleTypeName = lpg_SimpleTypeName; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getFormalParameterListopt</b> may be <b>nullptr</b>
     */
    Ast *getFormalParameterListopt() { return lpg_FormalParameterListopt; };
    void setFormalParameterListopt(Ast *lpg_FormalParameterListopt) { this->lpg_FormalParameterListopt = lpg_FormalParameterListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    ConstructorDeclarator(IToken* leftIToken, IToken* rightIToken,
                          TypeParameters *lpg_TypeParametersopt,
                          identifier *lpg_SimpleTypeName,
                          AstToken *lpg_LPAREN,
                          Ast *lpg_FormalParameterListopt,
                          AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeParametersopt = lpg_TypeParametersopt;
        if (lpg_TypeParametersopt != nullptr) ((Ast*) lpg_TypeParametersopt)->setParent(this);
        this->lpg_SimpleTypeName = lpg_SimpleTypeName;
        ((Ast*) lpg_SimpleTypeName)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_FormalParameterListopt = lpg_FormalParameterListopt;
        if (lpg_FormalParameterListopt != nullptr) ((Ast*) lpg_FormalParameterListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeParametersopt);
        list.push_back((IAst*)lpg_SimpleTypeName);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_FormalParameterListopt);
        list.push_back((IAst*)lpg_RPAREN);
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
            if (lpg_TypeParametersopt != nullptr) ((IAst*)lpg_TypeParametersopt)->accept(v);
            ((IAst*)lpg_SimpleTypeName)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_FormalParameterListopt != nullptr) ((IAst*)lpg_FormalParameterListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    Ast *lpg_ConstructorModifiers;
    Ast *lpg_ConstructorModifier;

    Ast *getConstructorModifiers() { return lpg_ConstructorModifiers; };
    void setConstructorModifiers(Ast *lpg_ConstructorModifiers) { this->lpg_ConstructorModifiers = lpg_ConstructorModifiers; }
    Ast *getConstructorModifier() { return lpg_ConstructorModifier; };
    void setConstructorModifier(Ast *lpg_ConstructorModifier) { this->lpg_ConstructorModifier = lpg_ConstructorModifier; }

    ConstructorModifiers(IToken* leftIToken, IToken* rightIToken,
                         Ast *lpg_ConstructorModifiers,
                         Ast *lpg_ConstructorModifier):Ast(leftIToken, rightIToken)    {
        this->lpg_ConstructorModifiers = lpg_ConstructorModifiers;
        ((Ast*) lpg_ConstructorModifiers)->setParent(this);
        this->lpg_ConstructorModifier = lpg_ConstructorModifier;
        ((Ast*) lpg_ConstructorModifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ConstructorModifiers);
        list.push_back((IAst*)lpg_ConstructorModifier);
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
            ((IAst*)lpg_ConstructorModifiers)->accept(v);
            ((IAst*)lpg_ConstructorModifier)->accept(v);
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
    AstToken *lpg_LBRACE;
    Ast *lpg_ExplicitConstructorInvocationopt;
    Ast *lpg_BlockStatementsopt;
    AstToken *lpg_RBRACE;

    AstToken *getLBRACE() { return lpg_LBRACE; };
    void setLBRACE(AstToken *lpg_LBRACE) { this->lpg_LBRACE = lpg_LBRACE; }
    /**
     * The value returned by <b>getExplicitConstructorInvocationopt</b> may be <b>nullptr</b>
     */
    Ast *getExplicitConstructorInvocationopt() { return lpg_ExplicitConstructorInvocationopt; };
    void setExplicitConstructorInvocationopt(Ast *lpg_ExplicitConstructorInvocationopt) { this->lpg_ExplicitConstructorInvocationopt = lpg_ExplicitConstructorInvocationopt; }
    /**
     * The value returned by <b>getBlockStatementsopt</b> may be <b>nullptr</b>
     */
    Ast *getBlockStatementsopt() { return lpg_BlockStatementsopt; };
    void setBlockStatementsopt(Ast *lpg_BlockStatementsopt) { this->lpg_BlockStatementsopt = lpg_BlockStatementsopt; }
    AstToken *getRBRACE() { return lpg_RBRACE; };
    void setRBRACE(AstToken *lpg_RBRACE) { this->lpg_RBRACE = lpg_RBRACE; }

    ConstructorBody(IToken* leftIToken, IToken* rightIToken,
                    AstToken *lpg_LBRACE,
                    Ast *lpg_ExplicitConstructorInvocationopt,
                    Ast *lpg_BlockStatementsopt,
                    AstToken *lpg_RBRACE):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACE = lpg_LBRACE;
        ((Ast*) lpg_LBRACE)->setParent(this);
        this->lpg_ExplicitConstructorInvocationopt = lpg_ExplicitConstructorInvocationopt;
        if (lpg_ExplicitConstructorInvocationopt != nullptr) ((Ast*) lpg_ExplicitConstructorInvocationopt)->setParent(this);
        this->lpg_BlockStatementsopt = lpg_BlockStatementsopt;
        if (lpg_BlockStatementsopt != nullptr) ((Ast*) lpg_BlockStatementsopt)->setParent(this);
        this->lpg_RBRACE = lpg_RBRACE;
        ((Ast*) lpg_RBRACE)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACE);
        list.push_back((IAst*)lpg_ExplicitConstructorInvocationopt);
        list.push_back((IAst*)lpg_BlockStatementsopt);
        list.push_back((IAst*)lpg_RBRACE);
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
            ((IAst*)lpg_LBRACE)->accept(v);
            if (lpg_ExplicitConstructorInvocationopt != nullptr) ((IAst*)lpg_ExplicitConstructorInvocationopt)->accept(v);
            if (lpg_BlockStatementsopt != nullptr) ((IAst*)lpg_BlockStatementsopt)->accept(v);
            ((IAst*)lpg_RBRACE)->accept(v);
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
    Ast *lpg_ClassModifiersopt;
    AstToken *lpg_enum;
    identifier *lpg_identifier;
    Interfaces *lpg_Interfacesopt;
    EnumBody *lpg_EnumBody;

    /**
     * The value returned by <b>getClassModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getClassModifiersopt() { return lpg_ClassModifiersopt; };
    void setClassModifiersopt(Ast *lpg_ClassModifiersopt) { this->lpg_ClassModifiersopt = lpg_ClassModifiersopt; }
    AstToken *getenum() { return lpg_enum; };
    void setenum(AstToken *lpg_enum) { this->lpg_enum = lpg_enum; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    /**
     * The value returned by <b>getInterfacesopt</b> may be <b>nullptr</b>
     */
    Interfaces *getInterfacesopt() { return lpg_Interfacesopt; };
    void setInterfacesopt(Interfaces *lpg_Interfacesopt) { this->lpg_Interfacesopt = lpg_Interfacesopt; }
    EnumBody *getEnumBody() { return lpg_EnumBody; };
    void setEnumBody(EnumBody *lpg_EnumBody) { this->lpg_EnumBody = lpg_EnumBody; }

    EnumDeclaration(IToken* leftIToken, IToken* rightIToken,
                    Ast *lpg_ClassModifiersopt,
                    AstToken *lpg_enum,
                    identifier *lpg_identifier,
                    Interfaces *lpg_Interfacesopt,
                    EnumBody *lpg_EnumBody):Ast(leftIToken, rightIToken)    {
        this->lpg_ClassModifiersopt = lpg_ClassModifiersopt;
        if (lpg_ClassModifiersopt != nullptr) ((Ast*) lpg_ClassModifiersopt)->setParent(this);
        this->lpg_enum = lpg_enum;
        ((Ast*) lpg_enum)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_Interfacesopt = lpg_Interfacesopt;
        if (lpg_Interfacesopt != nullptr) ((Ast*) lpg_Interfacesopt)->setParent(this);
        this->lpg_EnumBody = lpg_EnumBody;
        ((Ast*) lpg_EnumBody)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ClassModifiersopt);
        list.push_back((IAst*)lpg_enum);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_Interfacesopt);
        list.push_back((IAst*)lpg_EnumBody);
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
            if (lpg_ClassModifiersopt != nullptr) ((IAst*)lpg_ClassModifiersopt)->accept(v);
            ((IAst*)lpg_enum)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            if (lpg_Interfacesopt != nullptr) ((IAst*)lpg_Interfacesopt)->accept(v);
            ((IAst*)lpg_EnumBody)->accept(v);
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
    AstToken *lpg_LBRACE;
    Ast *lpg_EnumConstantsopt;
    Commaopt *lpg_Commaopt;
    EnumBodyDeclarations *lpg_EnumBodyDeclarationsopt;
    AstToken *lpg_RBRACE;

    AstToken *getLBRACE() { return lpg_LBRACE; };
    void setLBRACE(AstToken *lpg_LBRACE) { this->lpg_LBRACE = lpg_LBRACE; }
    /**
     * The value returned by <b>getEnumConstantsopt</b> may be <b>nullptr</b>
     */
    Ast *getEnumConstantsopt() { return lpg_EnumConstantsopt; };
    void setEnumConstantsopt(Ast *lpg_EnumConstantsopt) { this->lpg_EnumConstantsopt = lpg_EnumConstantsopt; }
    /**
     * The value returned by <b>getCommaopt</b> may be <b>nullptr</b>
     */
    Commaopt *getCommaopt() { return lpg_Commaopt; };
    void setCommaopt(Commaopt *lpg_Commaopt) { this->lpg_Commaopt = lpg_Commaopt; }
    /**
     * The value returned by <b>getEnumBodyDeclarationsopt</b> may be <b>nullptr</b>
     */
    EnumBodyDeclarations *getEnumBodyDeclarationsopt() { return lpg_EnumBodyDeclarationsopt; };
    void setEnumBodyDeclarationsopt(EnumBodyDeclarations *lpg_EnumBodyDeclarationsopt) { this->lpg_EnumBodyDeclarationsopt = lpg_EnumBodyDeclarationsopt; }
    AstToken *getRBRACE() { return lpg_RBRACE; };
    void setRBRACE(AstToken *lpg_RBRACE) { this->lpg_RBRACE = lpg_RBRACE; }

    EnumBody(IToken* leftIToken, IToken* rightIToken,
             AstToken *lpg_LBRACE,
             Ast *lpg_EnumConstantsopt,
             Commaopt *lpg_Commaopt,
             EnumBodyDeclarations *lpg_EnumBodyDeclarationsopt,
             AstToken *lpg_RBRACE):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACE = lpg_LBRACE;
        ((Ast*) lpg_LBRACE)->setParent(this);
        this->lpg_EnumConstantsopt = lpg_EnumConstantsopt;
        if (lpg_EnumConstantsopt != nullptr) ((Ast*) lpg_EnumConstantsopt)->setParent(this);
        this->lpg_Commaopt = lpg_Commaopt;
        if (lpg_Commaopt != nullptr) ((Ast*) lpg_Commaopt)->setParent(this);
        this->lpg_EnumBodyDeclarationsopt = lpg_EnumBodyDeclarationsopt;
        if (lpg_EnumBodyDeclarationsopt != nullptr) ((Ast*) lpg_EnumBodyDeclarationsopt)->setParent(this);
        this->lpg_RBRACE = lpg_RBRACE;
        ((Ast*) lpg_RBRACE)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACE);
        list.push_back((IAst*)lpg_EnumConstantsopt);
        list.push_back((IAst*)lpg_Commaopt);
        list.push_back((IAst*)lpg_EnumBodyDeclarationsopt);
        list.push_back((IAst*)lpg_RBRACE);
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
            ((IAst*)lpg_LBRACE)->accept(v);
            if (lpg_EnumConstantsopt != nullptr) ((IAst*)lpg_EnumConstantsopt)->accept(v);
            if (lpg_Commaopt != nullptr) ((IAst*)lpg_Commaopt)->accept(v);
            if (lpg_EnumBodyDeclarationsopt != nullptr) ((IAst*)lpg_EnumBodyDeclarationsopt)->accept(v);
            ((IAst*)lpg_RBRACE)->accept(v);
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
    Ast *lpg_EnumConstants;
    AstToken *lpg_COMMA;
    Ast *lpg_EnumConstant;

    Ast *getEnumConstants() { return lpg_EnumConstants; };
    void setEnumConstants(Ast *lpg_EnumConstants) { this->lpg_EnumConstants = lpg_EnumConstants; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    Ast *getEnumConstant() { return lpg_EnumConstant; };
    void setEnumConstant(Ast *lpg_EnumConstant) { this->lpg_EnumConstant = lpg_EnumConstant; }

    EnumConstants(IToken* leftIToken, IToken* rightIToken,
                  Ast *lpg_EnumConstants,
                  AstToken *lpg_COMMA,
                  Ast *lpg_EnumConstant):Ast(leftIToken, rightIToken)    {
        this->lpg_EnumConstants = lpg_EnumConstants;
        ((Ast*) lpg_EnumConstants)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_EnumConstant = lpg_EnumConstant;
        ((Ast*) lpg_EnumConstant)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_EnumConstants);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_EnumConstant);
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
            ((IAst*)lpg_EnumConstants)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_EnumConstant)->accept(v);
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
    Ast *lpg_Annotationsopt;
    identifier *lpg_identifier;
    Arguments *lpg_Argumentsopt;
    ClassBody *lpg_ClassBodyopt;

    /**
     * The value returned by <b>getAnnotationsopt</b> may be <b>nullptr</b>
     */
    Ast *getAnnotationsopt() { return lpg_Annotationsopt; };
    void setAnnotationsopt(Ast *lpg_Annotationsopt) { this->lpg_Annotationsopt = lpg_Annotationsopt; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    /**
     * The value returned by <b>getArgumentsopt</b> may be <b>nullptr</b>
     */
    Arguments *getArgumentsopt() { return lpg_Argumentsopt; };
    void setArgumentsopt(Arguments *lpg_Argumentsopt) { this->lpg_Argumentsopt = lpg_Argumentsopt; }
    /**
     * The value returned by <b>getClassBodyopt</b> may be <b>nullptr</b>
     */
    ClassBody *getClassBodyopt() { return lpg_ClassBodyopt; };
    void setClassBodyopt(ClassBody *lpg_ClassBodyopt) { this->lpg_ClassBodyopt = lpg_ClassBodyopt; }

    EnumConstant(IToken* leftIToken, IToken* rightIToken,
                 Ast *lpg_Annotationsopt,
                 identifier *lpg_identifier,
                 Arguments *lpg_Argumentsopt,
                 ClassBody *lpg_ClassBodyopt):Ast(leftIToken, rightIToken)    {
        this->lpg_Annotationsopt = lpg_Annotationsopt;
        if (lpg_Annotationsopt != nullptr) ((Ast*) lpg_Annotationsopt)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_Argumentsopt = lpg_Argumentsopt;
        if (lpg_Argumentsopt != nullptr) ((Ast*) lpg_Argumentsopt)->setParent(this);
        this->lpg_ClassBodyopt = lpg_ClassBodyopt;
        if (lpg_ClassBodyopt != nullptr) ((Ast*) lpg_ClassBodyopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Annotationsopt);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_Argumentsopt);
        list.push_back((IAst*)lpg_ClassBodyopt);
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
            if (lpg_Annotationsopt != nullptr) ((IAst*)lpg_Annotationsopt)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            if (lpg_Argumentsopt != nullptr) ((IAst*)lpg_Argumentsopt)->accept(v);
            if (lpg_ClassBodyopt != nullptr) ((IAst*)lpg_ClassBodyopt)->accept(v);
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
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;

    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    Arguments(IToken* leftIToken, IToken* rightIToken,
              AstToken *lpg_LPAREN,
              Ast *lpg_ArgumentListopt,
              AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    AstToken *lpg_SEMICOLON;
    Ast *lpg_ClassBodyDeclarationsopt;

    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }
    /**
     * The value returned by <b>getClassBodyDeclarationsopt</b> may be <b>nullptr</b>
     */
    Ast *getClassBodyDeclarationsopt() { return lpg_ClassBodyDeclarationsopt; };
    void setClassBodyDeclarationsopt(Ast *lpg_ClassBodyDeclarationsopt) { this->lpg_ClassBodyDeclarationsopt = lpg_ClassBodyDeclarationsopt; }

    EnumBodyDeclarations(IToken* leftIToken, IToken* rightIToken,
                         AstToken *lpg_SEMICOLON,
                         Ast *lpg_ClassBodyDeclarationsopt):Ast(leftIToken, rightIToken)    {
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        this->lpg_ClassBodyDeclarationsopt = lpg_ClassBodyDeclarationsopt;
        if (lpg_ClassBodyDeclarationsopt != nullptr) ((Ast*) lpg_ClassBodyDeclarationsopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_SEMICOLON);
        list.push_back((IAst*)lpg_ClassBodyDeclarationsopt);
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
            ((IAst*)lpg_SEMICOLON)->accept(v);
            if (lpg_ClassBodyDeclarationsopt != nullptr) ((IAst*)lpg_ClassBodyDeclarationsopt)->accept(v);
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
    Ast *lpg_InterfaceModifiersopt;
    AstToken *lpg_interface;
    identifier *lpg_identifier;
    TypeParameters *lpg_TypeParametersopt;
    Ast *lpg_ExtendsInterfacesopt;
    InterfaceBody *lpg_InterfaceBody;

    /**
     * The value returned by <b>getInterfaceModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getInterfaceModifiersopt() { return lpg_InterfaceModifiersopt; };
    void setInterfaceModifiersopt(Ast *lpg_InterfaceModifiersopt) { this->lpg_InterfaceModifiersopt = lpg_InterfaceModifiersopt; }
    AstToken *getinterface() { return lpg_interface; };
    void setinterface(AstToken *lpg_interface) { this->lpg_interface = lpg_interface; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    /**
     * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
     */
    TypeParameters *getTypeParametersopt() { return lpg_TypeParametersopt; };
    void setTypeParametersopt(TypeParameters *lpg_TypeParametersopt) { this->lpg_TypeParametersopt = lpg_TypeParametersopt; }
    /**
     * The value returned by <b>getExtendsInterfacesopt</b> may be <b>nullptr</b>
     */
    Ast *getExtendsInterfacesopt() { return lpg_ExtendsInterfacesopt; };
    void setExtendsInterfacesopt(Ast *lpg_ExtendsInterfacesopt) { this->lpg_ExtendsInterfacesopt = lpg_ExtendsInterfacesopt; }
    InterfaceBody *getInterfaceBody() { return lpg_InterfaceBody; };
    void setInterfaceBody(InterfaceBody *lpg_InterfaceBody) { this->lpg_InterfaceBody = lpg_InterfaceBody; }

    NormalInterfaceDeclaration(IToken* leftIToken, IToken* rightIToken,
                               Ast *lpg_InterfaceModifiersopt,
                               AstToken *lpg_interface,
                               identifier *lpg_identifier,
                               TypeParameters *lpg_TypeParametersopt,
                               Ast *lpg_ExtendsInterfacesopt,
                               InterfaceBody *lpg_InterfaceBody):Ast(leftIToken, rightIToken)    {
        this->lpg_InterfaceModifiersopt = lpg_InterfaceModifiersopt;
        if (lpg_InterfaceModifiersopt != nullptr) ((Ast*) lpg_InterfaceModifiersopt)->setParent(this);
        this->lpg_interface = lpg_interface;
        ((Ast*) lpg_interface)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_TypeParametersopt = lpg_TypeParametersopt;
        if (lpg_TypeParametersopt != nullptr) ((Ast*) lpg_TypeParametersopt)->setParent(this);
        this->lpg_ExtendsInterfacesopt = lpg_ExtendsInterfacesopt;
        if (lpg_ExtendsInterfacesopt != nullptr) ((Ast*) lpg_ExtendsInterfacesopt)->setParent(this);
        this->lpg_InterfaceBody = lpg_InterfaceBody;
        ((Ast*) lpg_InterfaceBody)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_InterfaceModifiersopt);
        list.push_back((IAst*)lpg_interface);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_TypeParametersopt);
        list.push_back((IAst*)lpg_ExtendsInterfacesopt);
        list.push_back((IAst*)lpg_InterfaceBody);
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
            if (lpg_InterfaceModifiersopt != nullptr) ((IAst*)lpg_InterfaceModifiersopt)->accept(v);
            ((IAst*)lpg_interface)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            if (lpg_TypeParametersopt != nullptr) ((IAst*)lpg_TypeParametersopt)->accept(v);
            if (lpg_ExtendsInterfacesopt != nullptr) ((IAst*)lpg_ExtendsInterfacesopt)->accept(v);
            ((IAst*)lpg_InterfaceBody)->accept(v);
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
    Ast *lpg_InterfaceModifiers;
    Ast *lpg_InterfaceModifier;

    Ast *getInterfaceModifiers() { return lpg_InterfaceModifiers; };
    void setInterfaceModifiers(Ast *lpg_InterfaceModifiers) { this->lpg_InterfaceModifiers = lpg_InterfaceModifiers; }
    Ast *getInterfaceModifier() { return lpg_InterfaceModifier; };
    void setInterfaceModifier(Ast *lpg_InterfaceModifier) { this->lpg_InterfaceModifier = lpg_InterfaceModifier; }

    InterfaceModifiers(IToken* leftIToken, IToken* rightIToken,
                       Ast *lpg_InterfaceModifiers,
                       Ast *lpg_InterfaceModifier):Ast(leftIToken, rightIToken)    {
        this->lpg_InterfaceModifiers = lpg_InterfaceModifiers;
        ((Ast*) lpg_InterfaceModifiers)->setParent(this);
        this->lpg_InterfaceModifier = lpg_InterfaceModifier;
        ((Ast*) lpg_InterfaceModifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_InterfaceModifiers);
        list.push_back((IAst*)lpg_InterfaceModifier);
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
            ((IAst*)lpg_InterfaceModifiers)->accept(v);
            ((IAst*)lpg_InterfaceModifier)->accept(v);
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
    AstToken *lpg_LBRACE;
    Ast *lpg_InterfaceMemberDeclarationsopt;
    AstToken *lpg_RBRACE;

    AstToken *getLBRACE() { return lpg_LBRACE; };
    void setLBRACE(AstToken *lpg_LBRACE) { this->lpg_LBRACE = lpg_LBRACE; }
    /**
     * The value returned by <b>getInterfaceMemberDeclarationsopt</b> may be <b>nullptr</b>
     */
    Ast *getInterfaceMemberDeclarationsopt() { return lpg_InterfaceMemberDeclarationsopt; };
    void setInterfaceMemberDeclarationsopt(Ast *lpg_InterfaceMemberDeclarationsopt) { this->lpg_InterfaceMemberDeclarationsopt = lpg_InterfaceMemberDeclarationsopt; }
    AstToken *getRBRACE() { return lpg_RBRACE; };
    void setRBRACE(AstToken *lpg_RBRACE) { this->lpg_RBRACE = lpg_RBRACE; }

    InterfaceBody(IToken* leftIToken, IToken* rightIToken,
                  AstToken *lpg_LBRACE,
                  Ast *lpg_InterfaceMemberDeclarationsopt,
                  AstToken *lpg_RBRACE):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACE = lpg_LBRACE;
        ((Ast*) lpg_LBRACE)->setParent(this);
        this->lpg_InterfaceMemberDeclarationsopt = lpg_InterfaceMemberDeclarationsopt;
        if (lpg_InterfaceMemberDeclarationsopt != nullptr) ((Ast*) lpg_InterfaceMemberDeclarationsopt)->setParent(this);
        this->lpg_RBRACE = lpg_RBRACE;
        ((Ast*) lpg_RBRACE)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACE);
        list.push_back((IAst*)lpg_InterfaceMemberDeclarationsopt);
        list.push_back((IAst*)lpg_RBRACE);
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
            ((IAst*)lpg_LBRACE)->accept(v);
            if (lpg_InterfaceMemberDeclarationsopt != nullptr) ((IAst*)lpg_InterfaceMemberDeclarationsopt)->accept(v);
            ((IAst*)lpg_RBRACE)->accept(v);
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
    Ast *lpg_InterfaceMemberDeclarations;
    Ast *lpg_InterfaceMemberDeclaration;

    Ast *getInterfaceMemberDeclarations() { return lpg_InterfaceMemberDeclarations; };
    void setInterfaceMemberDeclarations(Ast *lpg_InterfaceMemberDeclarations) { this->lpg_InterfaceMemberDeclarations = lpg_InterfaceMemberDeclarations; }
    Ast *getInterfaceMemberDeclaration() { return lpg_InterfaceMemberDeclaration; };
    void setInterfaceMemberDeclaration(Ast *lpg_InterfaceMemberDeclaration) { this->lpg_InterfaceMemberDeclaration = lpg_InterfaceMemberDeclaration; }

    InterfaceMemberDeclarations(IToken* leftIToken, IToken* rightIToken,
                                Ast *lpg_InterfaceMemberDeclarations,
                                Ast *lpg_InterfaceMemberDeclaration):Ast(leftIToken, rightIToken)    {
        this->lpg_InterfaceMemberDeclarations = lpg_InterfaceMemberDeclarations;
        ((Ast*) lpg_InterfaceMemberDeclarations)->setParent(this);
        this->lpg_InterfaceMemberDeclaration = lpg_InterfaceMemberDeclaration;
        ((Ast*) lpg_InterfaceMemberDeclaration)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_InterfaceMemberDeclarations);
        list.push_back((IAst*)lpg_InterfaceMemberDeclaration);
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
            ((IAst*)lpg_InterfaceMemberDeclarations)->accept(v);
            ((IAst*)lpg_InterfaceMemberDeclaration)->accept(v);
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
    Ast *lpg_ConstantModifiersopt;
    Ast *lpg_Type;
    Ast *lpg_VariableDeclarators;

    /**
     * The value returned by <b>getConstantModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getConstantModifiersopt() { return lpg_ConstantModifiersopt; };
    void setConstantModifiersopt(Ast *lpg_ConstantModifiersopt) { this->lpg_ConstantModifiersopt = lpg_ConstantModifiersopt; }
    Ast *getType() { return lpg_Type; };
    void setType(Ast *lpg_Type) { this->lpg_Type = lpg_Type; }
    Ast *getVariableDeclarators() { return lpg_VariableDeclarators; };
    void setVariableDeclarators(Ast *lpg_VariableDeclarators) { this->lpg_VariableDeclarators = lpg_VariableDeclarators; }

    ConstantDeclaration(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_ConstantModifiersopt,
                        Ast *lpg_Type,
                        Ast *lpg_VariableDeclarators):Ast(leftIToken, rightIToken)    {
        this->lpg_ConstantModifiersopt = lpg_ConstantModifiersopt;
        if (lpg_ConstantModifiersopt != nullptr) ((Ast*) lpg_ConstantModifiersopt)->setParent(this);
        this->lpg_Type = lpg_Type;
        ((Ast*) lpg_Type)->setParent(this);
        this->lpg_VariableDeclarators = lpg_VariableDeclarators;
        ((Ast*) lpg_VariableDeclarators)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ConstantModifiersopt);
        list.push_back((IAst*)lpg_Type);
        list.push_back((IAst*)lpg_VariableDeclarators);
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
            if (lpg_ConstantModifiersopt != nullptr) ((IAst*)lpg_ConstantModifiersopt)->accept(v);
            ((IAst*)lpg_Type)->accept(v);
            ((IAst*)lpg_VariableDeclarators)->accept(v);
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
    Ast *lpg_ConstantModifiers;
    Ast *lpg_ConstantModifier;

    Ast *getConstantModifiers() { return lpg_ConstantModifiers; };
    void setConstantModifiers(Ast *lpg_ConstantModifiers) { this->lpg_ConstantModifiers = lpg_ConstantModifiers; }
    Ast *getConstantModifier() { return lpg_ConstantModifier; };
    void setConstantModifier(Ast *lpg_ConstantModifier) { this->lpg_ConstantModifier = lpg_ConstantModifier; }

    ConstantModifiers(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_ConstantModifiers,
                      Ast *lpg_ConstantModifier):Ast(leftIToken, rightIToken)    {
        this->lpg_ConstantModifiers = lpg_ConstantModifiers;
        ((Ast*) lpg_ConstantModifiers)->setParent(this);
        this->lpg_ConstantModifier = lpg_ConstantModifier;
        ((Ast*) lpg_ConstantModifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ConstantModifiers);
        list.push_back((IAst*)lpg_ConstantModifier);
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
            ((IAst*)lpg_ConstantModifiers)->accept(v);
            ((IAst*)lpg_ConstantModifier)->accept(v);
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
    Ast *lpg_AbstractMethodModifiersopt;
    TypeParameters *lpg_TypeParametersopt;
    Ast *lpg_ResultType;
    Ast *lpg_MethodDeclarator;
    Throws *lpg_Throwsopt;
    AstToken *lpg_SEMICOLON;

    /**
     * The value returned by <b>getAbstractMethodModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getAbstractMethodModifiersopt() { return lpg_AbstractMethodModifiersopt; };
    void setAbstractMethodModifiersopt(Ast *lpg_AbstractMethodModifiersopt) { this->lpg_AbstractMethodModifiersopt = lpg_AbstractMethodModifiersopt; }
    /**
     * The value returned by <b>getTypeParametersopt</b> may be <b>nullptr</b>
     */
    TypeParameters *getTypeParametersopt() { return lpg_TypeParametersopt; };
    void setTypeParametersopt(TypeParameters *lpg_TypeParametersopt) { this->lpg_TypeParametersopt = lpg_TypeParametersopt; }
    Ast *getResultType() { return lpg_ResultType; };
    void setResultType(Ast *lpg_ResultType) { this->lpg_ResultType = lpg_ResultType; }
    Ast *getMethodDeclarator() { return lpg_MethodDeclarator; };
    void setMethodDeclarator(Ast *lpg_MethodDeclarator) { this->lpg_MethodDeclarator = lpg_MethodDeclarator; }
    /**
     * The value returned by <b>getThrowsopt</b> may be <b>nullptr</b>
     */
    Throws *getThrowsopt() { return lpg_Throwsopt; };
    void setThrowsopt(Throws *lpg_Throwsopt) { this->lpg_Throwsopt = lpg_Throwsopt; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    AbstractMethodDeclaration(IToken* leftIToken, IToken* rightIToken,
                              Ast *lpg_AbstractMethodModifiersopt,
                              TypeParameters *lpg_TypeParametersopt,
                              Ast *lpg_ResultType,
                              Ast *lpg_MethodDeclarator,
                              Throws *lpg_Throwsopt,
                              AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_AbstractMethodModifiersopt = lpg_AbstractMethodModifiersopt;
        if (lpg_AbstractMethodModifiersopt != nullptr) ((Ast*) lpg_AbstractMethodModifiersopt)->setParent(this);
        this->lpg_TypeParametersopt = lpg_TypeParametersopt;
        if (lpg_TypeParametersopt != nullptr) ((Ast*) lpg_TypeParametersopt)->setParent(this);
        this->lpg_ResultType = lpg_ResultType;
        ((Ast*) lpg_ResultType)->setParent(this);
        this->lpg_MethodDeclarator = lpg_MethodDeclarator;
        ((Ast*) lpg_MethodDeclarator)->setParent(this);
        this->lpg_Throwsopt = lpg_Throwsopt;
        if (lpg_Throwsopt != nullptr) ((Ast*) lpg_Throwsopt)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AbstractMethodModifiersopt);
        list.push_back((IAst*)lpg_TypeParametersopt);
        list.push_back((IAst*)lpg_ResultType);
        list.push_back((IAst*)lpg_MethodDeclarator);
        list.push_back((IAst*)lpg_Throwsopt);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            if (lpg_AbstractMethodModifiersopt != nullptr) ((IAst*)lpg_AbstractMethodModifiersopt)->accept(v);
            if (lpg_TypeParametersopt != nullptr) ((IAst*)lpg_TypeParametersopt)->accept(v);
            ((IAst*)lpg_ResultType)->accept(v);
            ((IAst*)lpg_MethodDeclarator)->accept(v);
            if (lpg_Throwsopt != nullptr) ((IAst*)lpg_Throwsopt)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    Ast *lpg_AbstractMethodModifiers;
    Ast *lpg_AbstractMethodModifier;

    Ast *getAbstractMethodModifiers() { return lpg_AbstractMethodModifiers; };
    void setAbstractMethodModifiers(Ast *lpg_AbstractMethodModifiers) { this->lpg_AbstractMethodModifiers = lpg_AbstractMethodModifiers; }
    Ast *getAbstractMethodModifier() { return lpg_AbstractMethodModifier; };
    void setAbstractMethodModifier(Ast *lpg_AbstractMethodModifier) { this->lpg_AbstractMethodModifier = lpg_AbstractMethodModifier; }

    AbstractMethodModifiers(IToken* leftIToken, IToken* rightIToken,
                            Ast *lpg_AbstractMethodModifiers,
                            Ast *lpg_AbstractMethodModifier):Ast(leftIToken, rightIToken)    {
        this->lpg_AbstractMethodModifiers = lpg_AbstractMethodModifiers;
        ((Ast*) lpg_AbstractMethodModifiers)->setParent(this);
        this->lpg_AbstractMethodModifier = lpg_AbstractMethodModifier;
        ((Ast*) lpg_AbstractMethodModifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AbstractMethodModifiers);
        list.push_back((IAst*)lpg_AbstractMethodModifier);
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
            ((IAst*)lpg_AbstractMethodModifiers)->accept(v);
            ((IAst*)lpg_AbstractMethodModifier)->accept(v);
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
    Ast *lpg_InterfaceModifiersopt;
    AstToken *lpg_AT;
    AstToken *lpg_interface;
    identifier *lpg_identifier;
    AnnotationTypeBody *lpg_AnnotationTypeBody;

    /**
     * The value returned by <b>getInterfaceModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getInterfaceModifiersopt() { return lpg_InterfaceModifiersopt; };
    void setInterfaceModifiersopt(Ast *lpg_InterfaceModifiersopt) { this->lpg_InterfaceModifiersopt = lpg_InterfaceModifiersopt; }
    AstToken *getAT() { return lpg_AT; };
    void setAT(AstToken *lpg_AT) { this->lpg_AT = lpg_AT; }
    AstToken *getinterface() { return lpg_interface; };
    void setinterface(AstToken *lpg_interface) { this->lpg_interface = lpg_interface; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AnnotationTypeBody *getAnnotationTypeBody() { return lpg_AnnotationTypeBody; };
    void setAnnotationTypeBody(AnnotationTypeBody *lpg_AnnotationTypeBody) { this->lpg_AnnotationTypeBody = lpg_AnnotationTypeBody; }

    AnnotationTypeDeclaration(IToken* leftIToken, IToken* rightIToken,
                              Ast *lpg_InterfaceModifiersopt,
                              AstToken *lpg_AT,
                              AstToken *lpg_interface,
                              identifier *lpg_identifier,
                              AnnotationTypeBody *lpg_AnnotationTypeBody):Ast(leftIToken, rightIToken)    {
        this->lpg_InterfaceModifiersopt = lpg_InterfaceModifiersopt;
        if (lpg_InterfaceModifiersopt != nullptr) ((Ast*) lpg_InterfaceModifiersopt)->setParent(this);
        this->lpg_AT = lpg_AT;
        ((Ast*) lpg_AT)->setParent(this);
        this->lpg_interface = lpg_interface;
        ((Ast*) lpg_interface)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_AnnotationTypeBody = lpg_AnnotationTypeBody;
        ((Ast*) lpg_AnnotationTypeBody)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_InterfaceModifiersopt);
        list.push_back((IAst*)lpg_AT);
        list.push_back((IAst*)lpg_interface);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_AnnotationTypeBody);
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
            if (lpg_InterfaceModifiersopt != nullptr) ((IAst*)lpg_InterfaceModifiersopt)->accept(v);
            ((IAst*)lpg_AT)->accept(v);
            ((IAst*)lpg_interface)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_AnnotationTypeBody)->accept(v);
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
    AstToken *lpg_LBRACE;
    Ast *lpg_AnnotationTypeElementDeclarationsopt;
    AstToken *lpg_RBRACE;

    AstToken *getLBRACE() { return lpg_LBRACE; };
    void setLBRACE(AstToken *lpg_LBRACE) { this->lpg_LBRACE = lpg_LBRACE; }
    /**
     * The value returned by <b>getAnnotationTypeElementDeclarationsopt</b> may be <b>nullptr</b>
     */
    Ast *getAnnotationTypeElementDeclarationsopt() { return lpg_AnnotationTypeElementDeclarationsopt; };
    void setAnnotationTypeElementDeclarationsopt(Ast *lpg_AnnotationTypeElementDeclarationsopt) { this->lpg_AnnotationTypeElementDeclarationsopt = lpg_AnnotationTypeElementDeclarationsopt; }
    AstToken *getRBRACE() { return lpg_RBRACE; };
    void setRBRACE(AstToken *lpg_RBRACE) { this->lpg_RBRACE = lpg_RBRACE; }

    AnnotationTypeBody(IToken* leftIToken, IToken* rightIToken,
                       AstToken *lpg_LBRACE,
                       Ast *lpg_AnnotationTypeElementDeclarationsopt,
                       AstToken *lpg_RBRACE):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACE = lpg_LBRACE;
        ((Ast*) lpg_LBRACE)->setParent(this);
        this->lpg_AnnotationTypeElementDeclarationsopt = lpg_AnnotationTypeElementDeclarationsopt;
        if (lpg_AnnotationTypeElementDeclarationsopt != nullptr) ((Ast*) lpg_AnnotationTypeElementDeclarationsopt)->setParent(this);
        this->lpg_RBRACE = lpg_RBRACE;
        ((Ast*) lpg_RBRACE)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACE);
        list.push_back((IAst*)lpg_AnnotationTypeElementDeclarationsopt);
        list.push_back((IAst*)lpg_RBRACE);
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
            ((IAst*)lpg_LBRACE)->accept(v);
            if (lpg_AnnotationTypeElementDeclarationsopt != nullptr) ((IAst*)lpg_AnnotationTypeElementDeclarationsopt)->accept(v);
            ((IAst*)lpg_RBRACE)->accept(v);
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
    Ast *lpg_AnnotationTypeElementDeclarations;
    Ast *lpg_AnnotationTypeElementDeclaration;

    Ast *getAnnotationTypeElementDeclarations() { return lpg_AnnotationTypeElementDeclarations; };
    void setAnnotationTypeElementDeclarations(Ast *lpg_AnnotationTypeElementDeclarations) { this->lpg_AnnotationTypeElementDeclarations = lpg_AnnotationTypeElementDeclarations; }
    Ast *getAnnotationTypeElementDeclaration() { return lpg_AnnotationTypeElementDeclaration; };
    void setAnnotationTypeElementDeclaration(Ast *lpg_AnnotationTypeElementDeclaration) { this->lpg_AnnotationTypeElementDeclaration = lpg_AnnotationTypeElementDeclaration; }

    AnnotationTypeElementDeclarations(IToken* leftIToken, IToken* rightIToken,
                                      Ast *lpg_AnnotationTypeElementDeclarations,
                                      Ast *lpg_AnnotationTypeElementDeclaration):Ast(leftIToken, rightIToken)    {
        this->lpg_AnnotationTypeElementDeclarations = lpg_AnnotationTypeElementDeclarations;
        ((Ast*) lpg_AnnotationTypeElementDeclarations)->setParent(this);
        this->lpg_AnnotationTypeElementDeclaration = lpg_AnnotationTypeElementDeclaration;
        ((Ast*) lpg_AnnotationTypeElementDeclaration)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AnnotationTypeElementDeclarations);
        list.push_back((IAst*)lpg_AnnotationTypeElementDeclaration);
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
            ((IAst*)lpg_AnnotationTypeElementDeclarations)->accept(v);
            ((IAst*)lpg_AnnotationTypeElementDeclaration)->accept(v);
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
    AstToken *lpg_default;
    Ast *lpg_ElementValue;

    AstToken *getdefault() { return lpg_default; };
    void setdefault(AstToken *lpg_default) { this->lpg_default = lpg_default; }
    Ast *getElementValue() { return lpg_ElementValue; };
    void setElementValue(Ast *lpg_ElementValue) { this->lpg_ElementValue = lpg_ElementValue; }

    DefaultValue(IToken* leftIToken, IToken* rightIToken,
                 AstToken *lpg_default,
                 Ast *lpg_ElementValue):Ast(leftIToken, rightIToken)    {
        this->lpg_default = lpg_default;
        ((Ast*) lpg_default)->setParent(this);
        this->lpg_ElementValue = lpg_ElementValue;
        ((Ast*) lpg_ElementValue)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_default);
        list.push_back((IAst*)lpg_ElementValue);
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
            ((IAst*)lpg_default)->accept(v);
            ((IAst*)lpg_ElementValue)->accept(v);
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
    Ast *lpg_Annotations;
    Ast *lpg_Annotation;

    Ast *getAnnotations() { return lpg_Annotations; };
    void setAnnotations(Ast *lpg_Annotations) { this->lpg_Annotations = lpg_Annotations; }
    Ast *getAnnotation() { return lpg_Annotation; };
    void setAnnotation(Ast *lpg_Annotation) { this->lpg_Annotation = lpg_Annotation; }

    Annotations(IToken* leftIToken, IToken* rightIToken,
                Ast *lpg_Annotations,
                Ast *lpg_Annotation):Ast(leftIToken, rightIToken)    {
        this->lpg_Annotations = lpg_Annotations;
        ((Ast*) lpg_Annotations)->setParent(this);
        this->lpg_Annotation = lpg_Annotation;
        ((Ast*) lpg_Annotation)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Annotations);
        list.push_back((IAst*)lpg_Annotation);
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
            ((IAst*)lpg_Annotations)->accept(v);
            ((IAst*)lpg_Annotation)->accept(v);
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
    AstToken *lpg_AT;
    Ast *lpg_TypeName;
    AstToken *lpg_LPAREN;
    Ast *lpg_ElementValuePairsopt;
    AstToken *lpg_RPAREN;

    AstToken *getAT() { return lpg_AT; };
    void setAT(AstToken *lpg_AT) { this->lpg_AT = lpg_AT; }
    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getElementValuePairsopt</b> may be <b>nullptr</b>
     */
    Ast *getElementValuePairsopt() { return lpg_ElementValuePairsopt; };
    void setElementValuePairsopt(Ast *lpg_ElementValuePairsopt) { this->lpg_ElementValuePairsopt = lpg_ElementValuePairsopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    NormalAnnotation(IToken* leftIToken, IToken* rightIToken,
                     AstToken *lpg_AT,
                     Ast *lpg_TypeName,
                     AstToken *lpg_LPAREN,
                     Ast *lpg_ElementValuePairsopt,
                     AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_AT = lpg_AT;
        ((Ast*) lpg_AT)->setParent(this);
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ElementValuePairsopt = lpg_ElementValuePairsopt;
        if (lpg_ElementValuePairsopt != nullptr) ((Ast*) lpg_ElementValuePairsopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AT);
        list.push_back((IAst*)lpg_TypeName);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ElementValuePairsopt);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_AT)->accept(v);
            ((IAst*)lpg_TypeName)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ElementValuePairsopt != nullptr) ((IAst*)lpg_ElementValuePairsopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    Ast *lpg_ElementValuePairs;
    AstToken *lpg_COMMA;
    ElementValuePair *lpg_ElementValuePair;

    Ast *getElementValuePairs() { return lpg_ElementValuePairs; };
    void setElementValuePairs(Ast *lpg_ElementValuePairs) { this->lpg_ElementValuePairs = lpg_ElementValuePairs; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    ElementValuePair *getElementValuePair() { return lpg_ElementValuePair; };
    void setElementValuePair(ElementValuePair *lpg_ElementValuePair) { this->lpg_ElementValuePair = lpg_ElementValuePair; }

    ElementValuePairs(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_ElementValuePairs,
                      AstToken *lpg_COMMA,
                      ElementValuePair *lpg_ElementValuePair):Ast(leftIToken, rightIToken)    {
        this->lpg_ElementValuePairs = lpg_ElementValuePairs;
        ((Ast*) lpg_ElementValuePairs)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_ElementValuePair = lpg_ElementValuePair;
        ((Ast*) lpg_ElementValuePair)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ElementValuePairs);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_ElementValuePair);
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
            ((IAst*)lpg_ElementValuePairs)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_ElementValuePair)->accept(v);
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
    identifier *lpg_SimpleName;
    AstToken *lpg_EQUAL;
    Ast *lpg_ElementValue;

    identifier *getSimpleName() { return lpg_SimpleName; };
    void setSimpleName(identifier *lpg_SimpleName) { this->lpg_SimpleName = lpg_SimpleName; }
    AstToken *getEQUAL() { return lpg_EQUAL; };
    void setEQUAL(AstToken *lpg_EQUAL) { this->lpg_EQUAL = lpg_EQUAL; }
    Ast *getElementValue() { return lpg_ElementValue; };
    void setElementValue(Ast *lpg_ElementValue) { this->lpg_ElementValue = lpg_ElementValue; }

    ElementValuePair(IToken* leftIToken, IToken* rightIToken,
                     identifier *lpg_SimpleName,
                     AstToken *lpg_EQUAL,
                     Ast *lpg_ElementValue):Ast(leftIToken, rightIToken)    {
        this->lpg_SimpleName = lpg_SimpleName;
        ((Ast*) lpg_SimpleName)->setParent(this);
        this->lpg_EQUAL = lpg_EQUAL;
        ((Ast*) lpg_EQUAL)->setParent(this);
        this->lpg_ElementValue = lpg_ElementValue;
        ((Ast*) lpg_ElementValue)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_SimpleName);
        list.push_back((IAst*)lpg_EQUAL);
        list.push_back((IAst*)lpg_ElementValue);
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
            ((IAst*)lpg_SimpleName)->accept(v);
            ((IAst*)lpg_EQUAL)->accept(v);
            ((IAst*)lpg_ElementValue)->accept(v);
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
    AstToken *lpg_LBRACE;
    Ast *lpg_ElementValuesopt;
    Commaopt *lpg_Commaopt;
    AstToken *lpg_RBRACE;

    AstToken *getLBRACE() { return lpg_LBRACE; };
    void setLBRACE(AstToken *lpg_LBRACE) { this->lpg_LBRACE = lpg_LBRACE; }
    /**
     * The value returned by <b>getElementValuesopt</b> may be <b>nullptr</b>
     */
    Ast *getElementValuesopt() { return lpg_ElementValuesopt; };
    void setElementValuesopt(Ast *lpg_ElementValuesopt) { this->lpg_ElementValuesopt = lpg_ElementValuesopt; }
    /**
     * The value returned by <b>getCommaopt</b> may be <b>nullptr</b>
     */
    Commaopt *getCommaopt() { return lpg_Commaopt; };
    void setCommaopt(Commaopt *lpg_Commaopt) { this->lpg_Commaopt = lpg_Commaopt; }
    AstToken *getRBRACE() { return lpg_RBRACE; };
    void setRBRACE(AstToken *lpg_RBRACE) { this->lpg_RBRACE = lpg_RBRACE; }

    ElementValueArrayInitializer(IToken* leftIToken, IToken* rightIToken,
                                 AstToken *lpg_LBRACE,
                                 Ast *lpg_ElementValuesopt,
                                 Commaopt *lpg_Commaopt,
                                 AstToken *lpg_RBRACE):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACE = lpg_LBRACE;
        ((Ast*) lpg_LBRACE)->setParent(this);
        this->lpg_ElementValuesopt = lpg_ElementValuesopt;
        if (lpg_ElementValuesopt != nullptr) ((Ast*) lpg_ElementValuesopt)->setParent(this);
        this->lpg_Commaopt = lpg_Commaopt;
        if (lpg_Commaopt != nullptr) ((Ast*) lpg_Commaopt)->setParent(this);
        this->lpg_RBRACE = lpg_RBRACE;
        ((Ast*) lpg_RBRACE)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACE);
        list.push_back((IAst*)lpg_ElementValuesopt);
        list.push_back((IAst*)lpg_Commaopt);
        list.push_back((IAst*)lpg_RBRACE);
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
            ((IAst*)lpg_LBRACE)->accept(v);
            if (lpg_ElementValuesopt != nullptr) ((IAst*)lpg_ElementValuesopt)->accept(v);
            if (lpg_Commaopt != nullptr) ((IAst*)lpg_Commaopt)->accept(v);
            ((IAst*)lpg_RBRACE)->accept(v);
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
    Ast *lpg_ElementValues;
    AstToken *lpg_COMMA;
    Ast *lpg_ElementValue;

    Ast *getElementValues() { return lpg_ElementValues; };
    void setElementValues(Ast *lpg_ElementValues) { this->lpg_ElementValues = lpg_ElementValues; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    Ast *getElementValue() { return lpg_ElementValue; };
    void setElementValue(Ast *lpg_ElementValue) { this->lpg_ElementValue = lpg_ElementValue; }

    ElementValues(IToken* leftIToken, IToken* rightIToken,
                  Ast *lpg_ElementValues,
                  AstToken *lpg_COMMA,
                  Ast *lpg_ElementValue):Ast(leftIToken, rightIToken)    {
        this->lpg_ElementValues = lpg_ElementValues;
        ((Ast*) lpg_ElementValues)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_ElementValue = lpg_ElementValue;
        ((Ast*) lpg_ElementValue)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ElementValues);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_ElementValue);
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
            ((IAst*)lpg_ElementValues)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_ElementValue)->accept(v);
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
    AstToken *lpg_AT;
    Ast *lpg_TypeName;

    AstToken *getAT() { return lpg_AT; };
    void setAT(AstToken *lpg_AT) { this->lpg_AT = lpg_AT; }
    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }

    MarkerAnnotation(IToken* leftIToken, IToken* rightIToken,
                     AstToken *lpg_AT,
                     Ast *lpg_TypeName):Ast(leftIToken, rightIToken)    {
        this->lpg_AT = lpg_AT;
        ((Ast*) lpg_AT)->setParent(this);
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AT);
        list.push_back((IAst*)lpg_TypeName);
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
            ((IAst*)lpg_AT)->accept(v);
            ((IAst*)lpg_TypeName)->accept(v);
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
    AstToken *lpg_AT;
    Ast *lpg_TypeName;
    AstToken *lpg_LPAREN;
    Ast *lpg_ElementValue;
    AstToken *lpg_RPAREN;

    AstToken *getAT() { return lpg_AT; };
    void setAT(AstToken *lpg_AT) { this->lpg_AT = lpg_AT; }
    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getElementValue() { return lpg_ElementValue; };
    void setElementValue(Ast *lpg_ElementValue) { this->lpg_ElementValue = lpg_ElementValue; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    SingleElementAnnotation(IToken* leftIToken, IToken* rightIToken,
                            AstToken *lpg_AT,
                            Ast *lpg_TypeName,
                            AstToken *lpg_LPAREN,
                            Ast *lpg_ElementValue,
                            AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_AT = lpg_AT;
        ((Ast*) lpg_AT)->setParent(this);
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ElementValue = lpg_ElementValue;
        ((Ast*) lpg_ElementValue)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AT);
        list.push_back((IAst*)lpg_TypeName);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ElementValue);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_AT)->accept(v);
            ((IAst*)lpg_TypeName)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_ElementValue)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    AstToken *lpg_LBRACE;
    Ast *lpg_VariableInitializersopt;
    Commaopt *lpg_Commaopt;
    AstToken *lpg_RBRACE;

    AstToken *getLBRACE() { return lpg_LBRACE; };
    void setLBRACE(AstToken *lpg_LBRACE) { this->lpg_LBRACE = lpg_LBRACE; }
    /**
     * The value returned by <b>getVariableInitializersopt</b> may be <b>nullptr</b>
     */
    Ast *getVariableInitializersopt() { return lpg_VariableInitializersopt; };
    void setVariableInitializersopt(Ast *lpg_VariableInitializersopt) { this->lpg_VariableInitializersopt = lpg_VariableInitializersopt; }
    /**
     * The value returned by <b>getCommaopt</b> may be <b>nullptr</b>
     */
    Commaopt *getCommaopt() { return lpg_Commaopt; };
    void setCommaopt(Commaopt *lpg_Commaopt) { this->lpg_Commaopt = lpg_Commaopt; }
    AstToken *getRBRACE() { return lpg_RBRACE; };
    void setRBRACE(AstToken *lpg_RBRACE) { this->lpg_RBRACE = lpg_RBRACE; }

    ArrayInitializer(IToken* leftIToken, IToken* rightIToken,
                     AstToken *lpg_LBRACE,
                     Ast *lpg_VariableInitializersopt,
                     Commaopt *lpg_Commaopt,
                     AstToken *lpg_RBRACE):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACE = lpg_LBRACE;
        ((Ast*) lpg_LBRACE)->setParent(this);
        this->lpg_VariableInitializersopt = lpg_VariableInitializersopt;
        if (lpg_VariableInitializersopt != nullptr) ((Ast*) lpg_VariableInitializersopt)->setParent(this);
        this->lpg_Commaopt = lpg_Commaopt;
        if (lpg_Commaopt != nullptr) ((Ast*) lpg_Commaopt)->setParent(this);
        this->lpg_RBRACE = lpg_RBRACE;
        ((Ast*) lpg_RBRACE)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACE);
        list.push_back((IAst*)lpg_VariableInitializersopt);
        list.push_back((IAst*)lpg_Commaopt);
        list.push_back((IAst*)lpg_RBRACE);
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
            ((IAst*)lpg_LBRACE)->accept(v);
            if (lpg_VariableInitializersopt != nullptr) ((IAst*)lpg_VariableInitializersopt)->accept(v);
            if (lpg_Commaopt != nullptr) ((IAst*)lpg_Commaopt)->accept(v);
            ((IAst*)lpg_RBRACE)->accept(v);
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
    Ast *lpg_VariableInitializers;
    AstToken *lpg_COMMA;
    Ast *lpg_VariableInitializer;

    Ast *getVariableInitializers() { return lpg_VariableInitializers; };
    void setVariableInitializers(Ast *lpg_VariableInitializers) { this->lpg_VariableInitializers = lpg_VariableInitializers; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    Ast *getVariableInitializer() { return lpg_VariableInitializer; };
    void setVariableInitializer(Ast *lpg_VariableInitializer) { this->lpg_VariableInitializer = lpg_VariableInitializer; }

    VariableInitializers(IToken* leftIToken, IToken* rightIToken,
                         Ast *lpg_VariableInitializers,
                         AstToken *lpg_COMMA,
                         Ast *lpg_VariableInitializer):Ast(leftIToken, rightIToken)    {
        this->lpg_VariableInitializers = lpg_VariableInitializers;
        ((Ast*) lpg_VariableInitializers)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_VariableInitializer = lpg_VariableInitializer;
        ((Ast*) lpg_VariableInitializer)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_VariableInitializers);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_VariableInitializer);
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
            ((IAst*)lpg_VariableInitializers)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_VariableInitializer)->accept(v);
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
    AstToken *lpg_LBRACE;
    Ast *lpg_BlockStatementsopt;
    AstToken *lpg_RBRACE;

    AstToken *getLBRACE() { return lpg_LBRACE; };
    void setLBRACE(AstToken *lpg_LBRACE) { this->lpg_LBRACE = lpg_LBRACE; }
    /**
     * The value returned by <b>getBlockStatementsopt</b> may be <b>nullptr</b>
     */
    Ast *getBlockStatementsopt() { return lpg_BlockStatementsopt; };
    void setBlockStatementsopt(Ast *lpg_BlockStatementsopt) { this->lpg_BlockStatementsopt = lpg_BlockStatementsopt; }
    AstToken *getRBRACE() { return lpg_RBRACE; };
    void setRBRACE(AstToken *lpg_RBRACE) { this->lpg_RBRACE = lpg_RBRACE; }

    Block(IToken* leftIToken, IToken* rightIToken,
          AstToken *lpg_LBRACE,
          Ast *lpg_BlockStatementsopt,
          AstToken *lpg_RBRACE):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACE = lpg_LBRACE;
        ((Ast*) lpg_LBRACE)->setParent(this);
        this->lpg_BlockStatementsopt = lpg_BlockStatementsopt;
        if (lpg_BlockStatementsopt != nullptr) ((Ast*) lpg_BlockStatementsopt)->setParent(this);
        this->lpg_RBRACE = lpg_RBRACE;
        ((Ast*) lpg_RBRACE)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACE);
        list.push_back((IAst*)lpg_BlockStatementsopt);
        list.push_back((IAst*)lpg_RBRACE);
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
            ((IAst*)lpg_LBRACE)->accept(v);
            if (lpg_BlockStatementsopt != nullptr) ((IAst*)lpg_BlockStatementsopt)->accept(v);
            ((IAst*)lpg_RBRACE)->accept(v);
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
    Ast *lpg_BlockStatements;
    Ast *lpg_BlockStatement;

    Ast *getBlockStatements() { return lpg_BlockStatements; };
    void setBlockStatements(Ast *lpg_BlockStatements) { this->lpg_BlockStatements = lpg_BlockStatements; }
    Ast *getBlockStatement() { return lpg_BlockStatement; };
    void setBlockStatement(Ast *lpg_BlockStatement) { this->lpg_BlockStatement = lpg_BlockStatement; }

    BlockStatements(IToken* leftIToken, IToken* rightIToken,
                    Ast *lpg_BlockStatements,
                    Ast *lpg_BlockStatement):Ast(leftIToken, rightIToken)    {
        this->lpg_BlockStatements = lpg_BlockStatements;
        ((Ast*) lpg_BlockStatements)->setParent(this);
        this->lpg_BlockStatement = lpg_BlockStatement;
        ((Ast*) lpg_BlockStatement)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_BlockStatements);
        list.push_back((IAst*)lpg_BlockStatement);
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
            ((IAst*)lpg_BlockStatements)->accept(v);
            ((IAst*)lpg_BlockStatement)->accept(v);
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
    LocalVariableDeclaration *lpg_LocalVariableDeclaration;
    AstToken *lpg_SEMICOLON;

    LocalVariableDeclaration *getLocalVariableDeclaration() { return lpg_LocalVariableDeclaration; };
    void setLocalVariableDeclaration(LocalVariableDeclaration *lpg_LocalVariableDeclaration) { this->lpg_LocalVariableDeclaration = lpg_LocalVariableDeclaration; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    LocalVariableDeclarationStatement(IToken* leftIToken, IToken* rightIToken,
                                      LocalVariableDeclaration *lpg_LocalVariableDeclaration,
                                      AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_LocalVariableDeclaration = lpg_LocalVariableDeclaration;
        ((Ast*) lpg_LocalVariableDeclaration)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LocalVariableDeclaration);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_LocalVariableDeclaration)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    Ast *lpg_VariableModifiersopt;
    Ast *lpg_Type;
    Ast *lpg_VariableDeclarators;

    /**
     * The value returned by <b>getVariableModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getVariableModifiersopt() { return lpg_VariableModifiersopt; };
    void setVariableModifiersopt(Ast *lpg_VariableModifiersopt) { this->lpg_VariableModifiersopt = lpg_VariableModifiersopt; }
    Ast *getType() { return lpg_Type; };
    void setType(Ast *lpg_Type) { this->lpg_Type = lpg_Type; }
    Ast *getVariableDeclarators() { return lpg_VariableDeclarators; };
    void setVariableDeclarators(Ast *lpg_VariableDeclarators) { this->lpg_VariableDeclarators = lpg_VariableDeclarators; }

    LocalVariableDeclaration(IToken* leftIToken, IToken* rightIToken,
                             Ast *lpg_VariableModifiersopt,
                             Ast *lpg_Type,
                             Ast *lpg_VariableDeclarators):Ast(leftIToken, rightIToken)    {
        this->lpg_VariableModifiersopt = lpg_VariableModifiersopt;
        if (lpg_VariableModifiersopt != nullptr) ((Ast*) lpg_VariableModifiersopt)->setParent(this);
        this->lpg_Type = lpg_Type;
        ((Ast*) lpg_Type)->setParent(this);
        this->lpg_VariableDeclarators = lpg_VariableDeclarators;
        ((Ast*) lpg_VariableDeclarators)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_VariableModifiersopt);
        list.push_back((IAst*)lpg_Type);
        list.push_back((IAst*)lpg_VariableDeclarators);
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
            if (lpg_VariableModifiersopt != nullptr) ((IAst*)lpg_VariableModifiersopt)->accept(v);
            ((IAst*)lpg_Type)->accept(v);
            ((IAst*)lpg_VariableDeclarators)->accept(v);
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
    AstToken *lpg_if;
    AstToken *lpg_LPAREN;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;
    Ast *lpg_Statement;

    AstToken *getif() { return lpg_if; };
    void setif(AstToken *lpg_if) { this->lpg_if = lpg_if; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getStatement() { return lpg_Statement; };
    void setStatement(Ast *lpg_Statement) { this->lpg_Statement = lpg_Statement; }

    IfThenStatement(IToken* leftIToken, IToken* rightIToken,
                    AstToken *lpg_if,
                    AstToken *lpg_LPAREN,
                    Ast *lpg_Expression,
                    AstToken *lpg_RPAREN,
                    Ast *lpg_Statement):Ast(leftIToken, rightIToken)    {
        this->lpg_if = lpg_if;
        ((Ast*) lpg_if)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_Statement = lpg_Statement;
        ((Ast*) lpg_Statement)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_if);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_Statement);
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
            ((IAst*)lpg_if)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_Statement)->accept(v);
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
    AstToken *lpg_if;
    AstToken *lpg_LPAREN;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;
    Ast *lpg_StatementNoShortIf;
    AstToken *lpg_else;
    Ast *lpg_Statement;

    AstToken *getif() { return lpg_if; };
    void setif(AstToken *lpg_if) { this->lpg_if = lpg_if; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getStatementNoShortIf() { return lpg_StatementNoShortIf; };
    void setStatementNoShortIf(Ast *lpg_StatementNoShortIf) { this->lpg_StatementNoShortIf = lpg_StatementNoShortIf; }
    AstToken *getelse() { return lpg_else; };
    void setelse(AstToken *lpg_else) { this->lpg_else = lpg_else; }
    Ast *getStatement() { return lpg_Statement; };
    void setStatement(Ast *lpg_Statement) { this->lpg_Statement = lpg_Statement; }

    IfThenElseStatement(IToken* leftIToken, IToken* rightIToken,
                        AstToken *lpg_if,
                        AstToken *lpg_LPAREN,
                        Ast *lpg_Expression,
                        AstToken *lpg_RPAREN,
                        Ast *lpg_StatementNoShortIf,
                        AstToken *lpg_else,
                        Ast *lpg_Statement):Ast(leftIToken, rightIToken)    {
        this->lpg_if = lpg_if;
        ((Ast*) lpg_if)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_StatementNoShortIf = lpg_StatementNoShortIf;
        ((Ast*) lpg_StatementNoShortIf)->setParent(this);
        this->lpg_else = lpg_else;
        ((Ast*) lpg_else)->setParent(this);
        this->lpg_Statement = lpg_Statement;
        ((Ast*) lpg_Statement)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_if);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_StatementNoShortIf);
        list.push_back((IAst*)lpg_else);
        list.push_back((IAst*)lpg_Statement);
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
            ((IAst*)lpg_if)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_StatementNoShortIf)->accept(v);
            ((IAst*)lpg_else)->accept(v);
            ((IAst*)lpg_Statement)->accept(v);
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
    AstToken *lpg_if;
    AstToken *lpg_LPAREN;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;
    Ast *lpg_StatementNoShortIf;
    AstToken *lpg_else;
    Ast *lpg_StatementNoShortIf7;

    AstToken *getif() { return lpg_if; };
    void setif(AstToken *lpg_if) { this->lpg_if = lpg_if; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getStatementNoShortIf() { return lpg_StatementNoShortIf; };
    void setStatementNoShortIf(Ast *lpg_StatementNoShortIf) { this->lpg_StatementNoShortIf = lpg_StatementNoShortIf; }
    AstToken *getelse() { return lpg_else; };
    void setelse(AstToken *lpg_else) { this->lpg_else = lpg_else; }
    Ast *getStatementNoShortIf7() { return lpg_StatementNoShortIf7; };
    void setStatementNoShortIf7(Ast *lpg_StatementNoShortIf7) { this->lpg_StatementNoShortIf7 = lpg_StatementNoShortIf7; }

    IfThenElseStatementNoShortIf(IToken* leftIToken, IToken* rightIToken,
                                 AstToken *lpg_if,
                                 AstToken *lpg_LPAREN,
                                 Ast *lpg_Expression,
                                 AstToken *lpg_RPAREN,
                                 Ast *lpg_StatementNoShortIf,
                                 AstToken *lpg_else,
                                 Ast *lpg_StatementNoShortIf7):Ast(leftIToken, rightIToken)    {
        this->lpg_if = lpg_if;
        ((Ast*) lpg_if)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_StatementNoShortIf = lpg_StatementNoShortIf;
        ((Ast*) lpg_StatementNoShortIf)->setParent(this);
        this->lpg_else = lpg_else;
        ((Ast*) lpg_else)->setParent(this);
        this->lpg_StatementNoShortIf7 = lpg_StatementNoShortIf7;
        ((Ast*) lpg_StatementNoShortIf7)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_if);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_StatementNoShortIf);
        list.push_back((IAst*)lpg_else);
        list.push_back((IAst*)lpg_StatementNoShortIf7);
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
            ((IAst*)lpg_if)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_StatementNoShortIf)->accept(v);
            ((IAst*)lpg_else)->accept(v);
            ((IAst*)lpg_StatementNoShortIf7)->accept(v);
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
    identifier *lpg_identifier;
    AstToken *lpg_COLON;
    Ast *lpg_Statement;

    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AstToken *getCOLON() { return lpg_COLON; };
    void setCOLON(AstToken *lpg_COLON) { this->lpg_COLON = lpg_COLON; }
    Ast *getStatement() { return lpg_Statement; };
    void setStatement(Ast *lpg_Statement) { this->lpg_Statement = lpg_Statement; }

    LabeledStatement(IToken* leftIToken, IToken* rightIToken,
                     identifier *lpg_identifier,
                     AstToken *lpg_COLON,
                     Ast *lpg_Statement):Ast(leftIToken, rightIToken)    {
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_COLON = lpg_COLON;
        ((Ast*) lpg_COLON)->setParent(this);
        this->lpg_Statement = lpg_Statement;
        ((Ast*) lpg_Statement)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_COLON);
        list.push_back((IAst*)lpg_Statement);
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
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_COLON)->accept(v);
            ((IAst*)lpg_Statement)->accept(v);
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
    identifier *lpg_identifier;
    AstToken *lpg_COLON;
    Ast *lpg_StatementNoShortIf;

    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AstToken *getCOLON() { return lpg_COLON; };
    void setCOLON(AstToken *lpg_COLON) { this->lpg_COLON = lpg_COLON; }
    Ast *getStatementNoShortIf() { return lpg_StatementNoShortIf; };
    void setStatementNoShortIf(Ast *lpg_StatementNoShortIf) { this->lpg_StatementNoShortIf = lpg_StatementNoShortIf; }

    LabeledStatementNoShortIf(IToken* leftIToken, IToken* rightIToken,
                              identifier *lpg_identifier,
                              AstToken *lpg_COLON,
                              Ast *lpg_StatementNoShortIf):Ast(leftIToken, rightIToken)    {
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_COLON = lpg_COLON;
        ((Ast*) lpg_COLON)->setParent(this);
        this->lpg_StatementNoShortIf = lpg_StatementNoShortIf;
        ((Ast*) lpg_StatementNoShortIf)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_COLON);
        list.push_back((IAst*)lpg_StatementNoShortIf);
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
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_COLON)->accept(v);
            ((IAst*)lpg_StatementNoShortIf)->accept(v);
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
    Ast *lpg_StatementExpression;
    AstToken *lpg_SEMICOLON;

    Ast *getStatementExpression() { return lpg_StatementExpression; };
    void setStatementExpression(Ast *lpg_StatementExpression) { this->lpg_StatementExpression = lpg_StatementExpression; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    ExpressionStatement(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_StatementExpression,
                        AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_StatementExpression = lpg_StatementExpression;
        ((Ast*) lpg_StatementExpression)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_StatementExpression);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_StatementExpression)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_switch;
    AstToken *lpg_LPAREN;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;
    SwitchBlock *lpg_SwitchBlock;

    AstToken *getswitch() { return lpg_switch; };
    void setswitch(AstToken *lpg_switch) { this->lpg_switch = lpg_switch; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    SwitchBlock *getSwitchBlock() { return lpg_SwitchBlock; };
    void setSwitchBlock(SwitchBlock *lpg_SwitchBlock) { this->lpg_SwitchBlock = lpg_SwitchBlock; }

    SwitchStatement(IToken* leftIToken, IToken* rightIToken,
                    AstToken *lpg_switch,
                    AstToken *lpg_LPAREN,
                    Ast *lpg_Expression,
                    AstToken *lpg_RPAREN,
                    SwitchBlock *lpg_SwitchBlock):Ast(leftIToken, rightIToken)    {
        this->lpg_switch = lpg_switch;
        ((Ast*) lpg_switch)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_SwitchBlock = lpg_SwitchBlock;
        ((Ast*) lpg_SwitchBlock)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_switch);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_SwitchBlock);
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
            ((IAst*)lpg_switch)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_SwitchBlock)->accept(v);
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
    AstToken *lpg_LBRACE;
    Ast *lpg_SwitchBlockStatementGroupsopt;
    Ast *lpg_SwitchLabelsopt;
    AstToken *lpg_RBRACE;

    AstToken *getLBRACE() { return lpg_LBRACE; };
    void setLBRACE(AstToken *lpg_LBRACE) { this->lpg_LBRACE = lpg_LBRACE; }
    /**
     * The value returned by <b>getSwitchBlockStatementGroupsopt</b> may be <b>nullptr</b>
     */
    Ast *getSwitchBlockStatementGroupsopt() { return lpg_SwitchBlockStatementGroupsopt; };
    void setSwitchBlockStatementGroupsopt(Ast *lpg_SwitchBlockStatementGroupsopt) { this->lpg_SwitchBlockStatementGroupsopt = lpg_SwitchBlockStatementGroupsopt; }
    /**
     * The value returned by <b>getSwitchLabelsopt</b> may be <b>nullptr</b>
     */
    Ast *getSwitchLabelsopt() { return lpg_SwitchLabelsopt; };
    void setSwitchLabelsopt(Ast *lpg_SwitchLabelsopt) { this->lpg_SwitchLabelsopt = lpg_SwitchLabelsopt; }
    AstToken *getRBRACE() { return lpg_RBRACE; };
    void setRBRACE(AstToken *lpg_RBRACE) { this->lpg_RBRACE = lpg_RBRACE; }

    SwitchBlock(IToken* leftIToken, IToken* rightIToken,
                AstToken *lpg_LBRACE,
                Ast *lpg_SwitchBlockStatementGroupsopt,
                Ast *lpg_SwitchLabelsopt,
                AstToken *lpg_RBRACE):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACE = lpg_LBRACE;
        ((Ast*) lpg_LBRACE)->setParent(this);
        this->lpg_SwitchBlockStatementGroupsopt = lpg_SwitchBlockStatementGroupsopt;
        if (lpg_SwitchBlockStatementGroupsopt != nullptr) ((Ast*) lpg_SwitchBlockStatementGroupsopt)->setParent(this);
        this->lpg_SwitchLabelsopt = lpg_SwitchLabelsopt;
        if (lpg_SwitchLabelsopt != nullptr) ((Ast*) lpg_SwitchLabelsopt)->setParent(this);
        this->lpg_RBRACE = lpg_RBRACE;
        ((Ast*) lpg_RBRACE)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACE);
        list.push_back((IAst*)lpg_SwitchBlockStatementGroupsopt);
        list.push_back((IAst*)lpg_SwitchLabelsopt);
        list.push_back((IAst*)lpg_RBRACE);
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
            ((IAst*)lpg_LBRACE)->accept(v);
            if (lpg_SwitchBlockStatementGroupsopt != nullptr) ((IAst*)lpg_SwitchBlockStatementGroupsopt)->accept(v);
            if (lpg_SwitchLabelsopt != nullptr) ((IAst*)lpg_SwitchLabelsopt)->accept(v);
            ((IAst*)lpg_RBRACE)->accept(v);
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
    Ast *lpg_SwitchBlockStatementGroups;
    SwitchBlockStatementGroup *lpg_SwitchBlockStatementGroup;

    Ast *getSwitchBlockStatementGroups() { return lpg_SwitchBlockStatementGroups; };
    void setSwitchBlockStatementGroups(Ast *lpg_SwitchBlockStatementGroups) { this->lpg_SwitchBlockStatementGroups = lpg_SwitchBlockStatementGroups; }
    SwitchBlockStatementGroup *getSwitchBlockStatementGroup() { return lpg_SwitchBlockStatementGroup; };
    void setSwitchBlockStatementGroup(SwitchBlockStatementGroup *lpg_SwitchBlockStatementGroup) { this->lpg_SwitchBlockStatementGroup = lpg_SwitchBlockStatementGroup; }

    SwitchBlockStatementGroups(IToken* leftIToken, IToken* rightIToken,
                               Ast *lpg_SwitchBlockStatementGroups,
                               SwitchBlockStatementGroup *lpg_SwitchBlockStatementGroup):Ast(leftIToken, rightIToken)    {
        this->lpg_SwitchBlockStatementGroups = lpg_SwitchBlockStatementGroups;
        ((Ast*) lpg_SwitchBlockStatementGroups)->setParent(this);
        this->lpg_SwitchBlockStatementGroup = lpg_SwitchBlockStatementGroup;
        ((Ast*) lpg_SwitchBlockStatementGroup)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_SwitchBlockStatementGroups);
        list.push_back((IAst*)lpg_SwitchBlockStatementGroup);
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
            ((IAst*)lpg_SwitchBlockStatementGroups)->accept(v);
            ((IAst*)lpg_SwitchBlockStatementGroup)->accept(v);
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
    Ast *lpg_SwitchLabels;
    Ast *lpg_BlockStatements;

    Ast *getSwitchLabels() { return lpg_SwitchLabels; };
    void setSwitchLabels(Ast *lpg_SwitchLabels) { this->lpg_SwitchLabels = lpg_SwitchLabels; }
    Ast *getBlockStatements() { return lpg_BlockStatements; };
    void setBlockStatements(Ast *lpg_BlockStatements) { this->lpg_BlockStatements = lpg_BlockStatements; }

    SwitchBlockStatementGroup(IToken* leftIToken, IToken* rightIToken,
                              Ast *lpg_SwitchLabels,
                              Ast *lpg_BlockStatements):Ast(leftIToken, rightIToken)    {
        this->lpg_SwitchLabels = lpg_SwitchLabels;
        ((Ast*) lpg_SwitchLabels)->setParent(this);
        this->lpg_BlockStatements = lpg_BlockStatements;
        ((Ast*) lpg_BlockStatements)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_SwitchLabels);
        list.push_back((IAst*)lpg_BlockStatements);
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
            ((IAst*)lpg_SwitchLabels)->accept(v);
            ((IAst*)lpg_BlockStatements)->accept(v);
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
    Ast *lpg_SwitchLabels;
    Ast *lpg_SwitchLabel;

    Ast *getSwitchLabels() { return lpg_SwitchLabels; };
    void setSwitchLabels(Ast *lpg_SwitchLabels) { this->lpg_SwitchLabels = lpg_SwitchLabels; }
    Ast *getSwitchLabel() { return lpg_SwitchLabel; };
    void setSwitchLabel(Ast *lpg_SwitchLabel) { this->lpg_SwitchLabel = lpg_SwitchLabel; }

    SwitchLabels(IToken* leftIToken, IToken* rightIToken,
                 Ast *lpg_SwitchLabels,
                 Ast *lpg_SwitchLabel):Ast(leftIToken, rightIToken)    {
        this->lpg_SwitchLabels = lpg_SwitchLabels;
        ((Ast*) lpg_SwitchLabels)->setParent(this);
        this->lpg_SwitchLabel = lpg_SwitchLabel;
        ((Ast*) lpg_SwitchLabel)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_SwitchLabels);
        list.push_back((IAst*)lpg_SwitchLabel);
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
            ((IAst*)lpg_SwitchLabels)->accept(v);
            ((IAst*)lpg_SwitchLabel)->accept(v);
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
    AstToken *lpg_while;
    AstToken *lpg_LPAREN;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;
    Ast *lpg_Statement;

    AstToken *getwhile() { return lpg_while; };
    void setwhile(AstToken *lpg_while) { this->lpg_while = lpg_while; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getStatement() { return lpg_Statement; };
    void setStatement(Ast *lpg_Statement) { this->lpg_Statement = lpg_Statement; }

    WhileStatement(IToken* leftIToken, IToken* rightIToken,
                   AstToken *lpg_while,
                   AstToken *lpg_LPAREN,
                   Ast *lpg_Expression,
                   AstToken *lpg_RPAREN,
                   Ast *lpg_Statement):Ast(leftIToken, rightIToken)    {
        this->lpg_while = lpg_while;
        ((Ast*) lpg_while)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_Statement = lpg_Statement;
        ((Ast*) lpg_Statement)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_while);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_Statement);
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
            ((IAst*)lpg_while)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_Statement)->accept(v);
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
    AstToken *lpg_while;
    AstToken *lpg_LPAREN;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;
    Ast *lpg_StatementNoShortIf;

    AstToken *getwhile() { return lpg_while; };
    void setwhile(AstToken *lpg_while) { this->lpg_while = lpg_while; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getStatementNoShortIf() { return lpg_StatementNoShortIf; };
    void setStatementNoShortIf(Ast *lpg_StatementNoShortIf) { this->lpg_StatementNoShortIf = lpg_StatementNoShortIf; }

    WhileStatementNoShortIf(IToken* leftIToken, IToken* rightIToken,
                            AstToken *lpg_while,
                            AstToken *lpg_LPAREN,
                            Ast *lpg_Expression,
                            AstToken *lpg_RPAREN,
                            Ast *lpg_StatementNoShortIf):Ast(leftIToken, rightIToken)    {
        this->lpg_while = lpg_while;
        ((Ast*) lpg_while)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_StatementNoShortIf = lpg_StatementNoShortIf;
        ((Ast*) lpg_StatementNoShortIf)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_while);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_StatementNoShortIf);
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
            ((IAst*)lpg_while)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_StatementNoShortIf)->accept(v);
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
    AstToken *lpg_do;
    Ast *lpg_Statement;
    AstToken *lpg_while;
    AstToken *lpg_LPAREN;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;
    AstToken *lpg_SEMICOLON;

    AstToken *getdo() { return lpg_do; };
    void setdo(AstToken *lpg_do) { this->lpg_do = lpg_do; }
    Ast *getStatement() { return lpg_Statement; };
    void setStatement(Ast *lpg_Statement) { this->lpg_Statement = lpg_Statement; }
    AstToken *getwhile() { return lpg_while; };
    void setwhile(AstToken *lpg_while) { this->lpg_while = lpg_while; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    DoStatement(IToken* leftIToken, IToken* rightIToken,
                AstToken *lpg_do,
                Ast *lpg_Statement,
                AstToken *lpg_while,
                AstToken *lpg_LPAREN,
                Ast *lpg_Expression,
                AstToken *lpg_RPAREN,
                AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_do = lpg_do;
        ((Ast*) lpg_do)->setParent(this);
        this->lpg_Statement = lpg_Statement;
        ((Ast*) lpg_Statement)->setParent(this);
        this->lpg_while = lpg_while;
        ((Ast*) lpg_while)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_do);
        list.push_back((IAst*)lpg_Statement);
        list.push_back((IAst*)lpg_while);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_do)->accept(v);
            ((IAst*)lpg_Statement)->accept(v);
            ((IAst*)lpg_while)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_for;
    AstToken *lpg_LPAREN;
    Ast *lpg_ForInitopt;
    AstToken *lpg_SEMICOLON;
    Ast *lpg_Expressionopt;
    AstToken *lpg_SEMICOLON6;
    Ast *lpg_ForUpdateopt;
    AstToken *lpg_RPAREN;
    Ast *lpg_Statement;

    AstToken *getfor() { return lpg_for; };
    void setfor(AstToken *lpg_for) { this->lpg_for = lpg_for; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getForInitopt</b> may be <b>nullptr</b>
     */
    Ast *getForInitopt() { return lpg_ForInitopt; };
    void setForInitopt(Ast *lpg_ForInitopt) { this->lpg_ForInitopt = lpg_ForInitopt; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }
    /**
     * The value returned by <b>getExpressionopt</b> may be <b>nullptr</b>
     */
    Ast *getExpressionopt() { return lpg_Expressionopt; };
    void setExpressionopt(Ast *lpg_Expressionopt) { this->lpg_Expressionopt = lpg_Expressionopt; }
    AstToken *getSEMICOLON6() { return lpg_SEMICOLON6; };
    void setSEMICOLON6(AstToken *lpg_SEMICOLON6) { this->lpg_SEMICOLON6 = lpg_SEMICOLON6; }
    /**
     * The value returned by <b>getForUpdateopt</b> may be <b>nullptr</b>
     */
    Ast *getForUpdateopt() { return lpg_ForUpdateopt; };
    void setForUpdateopt(Ast *lpg_ForUpdateopt) { this->lpg_ForUpdateopt = lpg_ForUpdateopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getStatement() { return lpg_Statement; };
    void setStatement(Ast *lpg_Statement) { this->lpg_Statement = lpg_Statement; }

    BasicForStatement(IToken* leftIToken, IToken* rightIToken,
                      AstToken *lpg_for,
                      AstToken *lpg_LPAREN,
                      Ast *lpg_ForInitopt,
                      AstToken *lpg_SEMICOLON,
                      Ast *lpg_Expressionopt,
                      AstToken *lpg_SEMICOLON6,
                      Ast *lpg_ForUpdateopt,
                      AstToken *lpg_RPAREN,
                      Ast *lpg_Statement):Ast(leftIToken, rightIToken)    {
        this->lpg_for = lpg_for;
        ((Ast*) lpg_for)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ForInitopt = lpg_ForInitopt;
        if (lpg_ForInitopt != nullptr) ((Ast*) lpg_ForInitopt)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        this->lpg_Expressionopt = lpg_Expressionopt;
        if (lpg_Expressionopt != nullptr) ((Ast*) lpg_Expressionopt)->setParent(this);
        this->lpg_SEMICOLON6 = lpg_SEMICOLON6;
        ((Ast*) lpg_SEMICOLON6)->setParent(this);
        this->lpg_ForUpdateopt = lpg_ForUpdateopt;
        if (lpg_ForUpdateopt != nullptr) ((Ast*) lpg_ForUpdateopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_Statement = lpg_Statement;
        ((Ast*) lpg_Statement)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_for);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ForInitopt);
        list.push_back((IAst*)lpg_SEMICOLON);
        list.push_back((IAst*)lpg_Expressionopt);
        list.push_back((IAst*)lpg_SEMICOLON6);
        list.push_back((IAst*)lpg_ForUpdateopt);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_Statement);
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
            ((IAst*)lpg_for)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ForInitopt != nullptr) ((IAst*)lpg_ForInitopt)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
            if (lpg_Expressionopt != nullptr) ((IAst*)lpg_Expressionopt)->accept(v);
            ((IAst*)lpg_SEMICOLON6)->accept(v);
            if (lpg_ForUpdateopt != nullptr) ((IAst*)lpg_ForUpdateopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_Statement)->accept(v);
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
    AstToken *lpg_for;
    AstToken *lpg_LPAREN;
    Ast *lpg_ForInitopt;
    AstToken *lpg_SEMICOLON;
    Ast *lpg_Expressionopt;
    AstToken *lpg_SEMICOLON6;
    Ast *lpg_ForUpdateopt;
    AstToken *lpg_RPAREN;
    Ast *lpg_StatementNoShortIf;

    AstToken *getfor() { return lpg_for; };
    void setfor(AstToken *lpg_for) { this->lpg_for = lpg_for; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getForInitopt</b> may be <b>nullptr</b>
     */
    Ast *getForInitopt() { return lpg_ForInitopt; };
    void setForInitopt(Ast *lpg_ForInitopt) { this->lpg_ForInitopt = lpg_ForInitopt; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }
    /**
     * The value returned by <b>getExpressionopt</b> may be <b>nullptr</b>
     */
    Ast *getExpressionopt() { return lpg_Expressionopt; };
    void setExpressionopt(Ast *lpg_Expressionopt) { this->lpg_Expressionopt = lpg_Expressionopt; }
    AstToken *getSEMICOLON6() { return lpg_SEMICOLON6; };
    void setSEMICOLON6(AstToken *lpg_SEMICOLON6) { this->lpg_SEMICOLON6 = lpg_SEMICOLON6; }
    /**
     * The value returned by <b>getForUpdateopt</b> may be <b>nullptr</b>
     */
    Ast *getForUpdateopt() { return lpg_ForUpdateopt; };
    void setForUpdateopt(Ast *lpg_ForUpdateopt) { this->lpg_ForUpdateopt = lpg_ForUpdateopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getStatementNoShortIf() { return lpg_StatementNoShortIf; };
    void setStatementNoShortIf(Ast *lpg_StatementNoShortIf) { this->lpg_StatementNoShortIf = lpg_StatementNoShortIf; }

    ForStatementNoShortIf(IToken* leftIToken, IToken* rightIToken,
                          AstToken *lpg_for,
                          AstToken *lpg_LPAREN,
                          Ast *lpg_ForInitopt,
                          AstToken *lpg_SEMICOLON,
                          Ast *lpg_Expressionopt,
                          AstToken *lpg_SEMICOLON6,
                          Ast *lpg_ForUpdateopt,
                          AstToken *lpg_RPAREN,
                          Ast *lpg_StatementNoShortIf):Ast(leftIToken, rightIToken)    {
        this->lpg_for = lpg_for;
        ((Ast*) lpg_for)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ForInitopt = lpg_ForInitopt;
        if (lpg_ForInitopt != nullptr) ((Ast*) lpg_ForInitopt)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        this->lpg_Expressionopt = lpg_Expressionopt;
        if (lpg_Expressionopt != nullptr) ((Ast*) lpg_Expressionopt)->setParent(this);
        this->lpg_SEMICOLON6 = lpg_SEMICOLON6;
        ((Ast*) lpg_SEMICOLON6)->setParent(this);
        this->lpg_ForUpdateopt = lpg_ForUpdateopt;
        if (lpg_ForUpdateopt != nullptr) ((Ast*) lpg_ForUpdateopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_StatementNoShortIf = lpg_StatementNoShortIf;
        ((Ast*) lpg_StatementNoShortIf)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_for);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ForInitopt);
        list.push_back((IAst*)lpg_SEMICOLON);
        list.push_back((IAst*)lpg_Expressionopt);
        list.push_back((IAst*)lpg_SEMICOLON6);
        list.push_back((IAst*)lpg_ForUpdateopt);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_StatementNoShortIf);
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
            ((IAst*)lpg_for)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ForInitopt != nullptr) ((IAst*)lpg_ForInitopt)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
            if (lpg_Expressionopt != nullptr) ((IAst*)lpg_Expressionopt)->accept(v);
            ((IAst*)lpg_SEMICOLON6)->accept(v);
            if (lpg_ForUpdateopt != nullptr) ((IAst*)lpg_ForUpdateopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_StatementNoShortIf)->accept(v);
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
    Ast *lpg_StatementExpressionList;
    AstToken *lpg_COMMA;
    Ast *lpg_StatementExpression;

    Ast *getStatementExpressionList() { return lpg_StatementExpressionList; };
    void setStatementExpressionList(Ast *lpg_StatementExpressionList) { this->lpg_StatementExpressionList = lpg_StatementExpressionList; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    Ast *getStatementExpression() { return lpg_StatementExpression; };
    void setStatementExpression(Ast *lpg_StatementExpression) { this->lpg_StatementExpression = lpg_StatementExpression; }

    StatementExpressionList(IToken* leftIToken, IToken* rightIToken,
                            Ast *lpg_StatementExpressionList,
                            AstToken *lpg_COMMA,
                            Ast *lpg_StatementExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_StatementExpressionList = lpg_StatementExpressionList;
        ((Ast*) lpg_StatementExpressionList)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_StatementExpression = lpg_StatementExpression;
        ((Ast*) lpg_StatementExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_StatementExpressionList);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_StatementExpression);
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
            ((IAst*)lpg_StatementExpressionList)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_StatementExpression)->accept(v);
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
    AstToken *lpg_for;
    AstToken *lpg_LPAREN;
    FormalParameter *lpg_FormalParameter;
    AstToken *lpg_COLON;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;
    Ast *lpg_Statement;

    AstToken *getfor() { return lpg_for; };
    void setfor(AstToken *lpg_for) { this->lpg_for = lpg_for; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    FormalParameter *getFormalParameter() { return lpg_FormalParameter; };
    void setFormalParameter(FormalParameter *lpg_FormalParameter) { this->lpg_FormalParameter = lpg_FormalParameter; }
    AstToken *getCOLON() { return lpg_COLON; };
    void setCOLON(AstToken *lpg_COLON) { this->lpg_COLON = lpg_COLON; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getStatement() { return lpg_Statement; };
    void setStatement(Ast *lpg_Statement) { this->lpg_Statement = lpg_Statement; }

    EnhancedForStatement(IToken* leftIToken, IToken* rightIToken,
                         AstToken *lpg_for,
                         AstToken *lpg_LPAREN,
                         FormalParameter *lpg_FormalParameter,
                         AstToken *lpg_COLON,
                         Ast *lpg_Expression,
                         AstToken *lpg_RPAREN,
                         Ast *lpg_Statement):Ast(leftIToken, rightIToken)    {
        this->lpg_for = lpg_for;
        ((Ast*) lpg_for)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_FormalParameter = lpg_FormalParameter;
        ((Ast*) lpg_FormalParameter)->setParent(this);
        this->lpg_COLON = lpg_COLON;
        ((Ast*) lpg_COLON)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_Statement = lpg_Statement;
        ((Ast*) lpg_Statement)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_for);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_FormalParameter);
        list.push_back((IAst*)lpg_COLON);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_Statement);
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
            ((IAst*)lpg_for)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_FormalParameter)->accept(v);
            ((IAst*)lpg_COLON)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_Statement)->accept(v);
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
    AstToken *lpg_break;
    identifier *lpg_identifieropt;
    AstToken *lpg_SEMICOLON;

    AstToken *getbreak() { return lpg_break; };
    void setbreak(AstToken *lpg_break) { this->lpg_break = lpg_break; }
    /**
     * The value returned by <b>getidentifieropt</b> may be <b>nullptr</b>
     */
    identifier *getidentifieropt() { return lpg_identifieropt; };
    void setidentifieropt(identifier *lpg_identifieropt) { this->lpg_identifieropt = lpg_identifieropt; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    BreakStatement(IToken* leftIToken, IToken* rightIToken,
                   AstToken *lpg_break,
                   identifier *lpg_identifieropt,
                   AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_break = lpg_break;
        ((Ast*) lpg_break)->setParent(this);
        this->lpg_identifieropt = lpg_identifieropt;
        if (lpg_identifieropt != nullptr) ((Ast*) lpg_identifieropt)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_break);
        list.push_back((IAst*)lpg_identifieropt);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_break)->accept(v);
            if (lpg_identifieropt != nullptr) ((IAst*)lpg_identifieropt)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_continue;
    identifier *lpg_identifieropt;
    AstToken *lpg_SEMICOLON;

    AstToken *getcontinue() { return lpg_continue; };
    void setcontinue(AstToken *lpg_continue) { this->lpg_continue = lpg_continue; }
    /**
     * The value returned by <b>getidentifieropt</b> may be <b>nullptr</b>
     */
    identifier *getidentifieropt() { return lpg_identifieropt; };
    void setidentifieropt(identifier *lpg_identifieropt) { this->lpg_identifieropt = lpg_identifieropt; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    ContinueStatement(IToken* leftIToken, IToken* rightIToken,
                      AstToken *lpg_continue,
                      identifier *lpg_identifieropt,
                      AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_continue = lpg_continue;
        ((Ast*) lpg_continue)->setParent(this);
        this->lpg_identifieropt = lpg_identifieropt;
        if (lpg_identifieropt != nullptr) ((Ast*) lpg_identifieropt)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_continue);
        list.push_back((IAst*)lpg_identifieropt);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_continue)->accept(v);
            if (lpg_identifieropt != nullptr) ((IAst*)lpg_identifieropt)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_return;
    Ast *lpg_Expressionopt;
    AstToken *lpg_SEMICOLON;

    AstToken *getreturn() { return lpg_return; };
    void setreturn(AstToken *lpg_return) { this->lpg_return = lpg_return; }
    /**
     * The value returned by <b>getExpressionopt</b> may be <b>nullptr</b>
     */
    Ast *getExpressionopt() { return lpg_Expressionopt; };
    void setExpressionopt(Ast *lpg_Expressionopt) { this->lpg_Expressionopt = lpg_Expressionopt; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    ReturnStatement(IToken* leftIToken, IToken* rightIToken,
                    AstToken *lpg_return,
                    Ast *lpg_Expressionopt,
                    AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_return = lpg_return;
        ((Ast*) lpg_return)->setParent(this);
        this->lpg_Expressionopt = lpg_Expressionopt;
        if (lpg_Expressionopt != nullptr) ((Ast*) lpg_Expressionopt)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_return);
        list.push_back((IAst*)lpg_Expressionopt);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_return)->accept(v);
            if (lpg_Expressionopt != nullptr) ((IAst*)lpg_Expressionopt)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_throw;
    Ast *lpg_Expression;
    AstToken *lpg_SEMICOLON;

    AstToken *getthrow() { return lpg_throw; };
    void setthrow(AstToken *lpg_throw) { this->lpg_throw = lpg_throw; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    ThrowStatement(IToken* leftIToken, IToken* rightIToken,
                   AstToken *lpg_throw,
                   Ast *lpg_Expression,
                   AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_throw = lpg_throw;
        ((Ast*) lpg_throw)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_throw);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_throw)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_synchronized;
    AstToken *lpg_LPAREN;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;
    Block *lpg_Block;

    AstToken *getsynchronized() { return lpg_synchronized; };
    void setsynchronized(AstToken *lpg_synchronized) { this->lpg_synchronized = lpg_synchronized; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Block *getBlock() { return lpg_Block; };
    void setBlock(Block *lpg_Block) { this->lpg_Block = lpg_Block; }

    SynchronizedStatement(IToken* leftIToken, IToken* rightIToken,
                          AstToken *lpg_synchronized,
                          AstToken *lpg_LPAREN,
                          Ast *lpg_Expression,
                          AstToken *lpg_RPAREN,
                          Block *lpg_Block):Ast(leftIToken, rightIToken)    {
        this->lpg_synchronized = lpg_synchronized;
        ((Ast*) lpg_synchronized)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_Block = lpg_Block;
        ((Ast*) lpg_Block)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_synchronized);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_Block);
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
            ((IAst*)lpg_synchronized)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_Block)->accept(v);
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
    Ast *lpg_Catches;
    CatchClause *lpg_CatchClause;

    Ast *getCatches() { return lpg_Catches; };
    void setCatches(Ast *lpg_Catches) { this->lpg_Catches = lpg_Catches; }
    CatchClause *getCatchClause() { return lpg_CatchClause; };
    void setCatchClause(CatchClause *lpg_CatchClause) { this->lpg_CatchClause = lpg_CatchClause; }

    Catches(IToken* leftIToken, IToken* rightIToken,
            Ast *lpg_Catches,
            CatchClause *lpg_CatchClause):Ast(leftIToken, rightIToken)    {
        this->lpg_Catches = lpg_Catches;
        ((Ast*) lpg_Catches)->setParent(this);
        this->lpg_CatchClause = lpg_CatchClause;
        ((Ast*) lpg_CatchClause)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Catches);
        list.push_back((IAst*)lpg_CatchClause);
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
            ((IAst*)lpg_Catches)->accept(v);
            ((IAst*)lpg_CatchClause)->accept(v);
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
    AstToken *lpg_catch;
    AstToken *lpg_LPAREN;
    FormalParameter *lpg_FormalParameter;
    AstToken *lpg_RPAREN;
    Block *lpg_Block;

    AstToken *getcatch() { return lpg_catch; };
    void setcatch(AstToken *lpg_catch) { this->lpg_catch = lpg_catch; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    FormalParameter *getFormalParameter() { return lpg_FormalParameter; };
    void setFormalParameter(FormalParameter *lpg_FormalParameter) { this->lpg_FormalParameter = lpg_FormalParameter; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Block *getBlock() { return lpg_Block; };
    void setBlock(Block *lpg_Block) { this->lpg_Block = lpg_Block; }

    CatchClause(IToken* leftIToken, IToken* rightIToken,
                AstToken *lpg_catch,
                AstToken *lpg_LPAREN,
                FormalParameter *lpg_FormalParameter,
                AstToken *lpg_RPAREN,
                Block *lpg_Block):Ast(leftIToken, rightIToken)    {
        this->lpg_catch = lpg_catch;
        ((Ast*) lpg_catch)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_FormalParameter = lpg_FormalParameter;
        ((Ast*) lpg_FormalParameter)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_Block = lpg_Block;
        ((Ast*) lpg_Block)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_catch);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_FormalParameter);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_Block);
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
            ((IAst*)lpg_catch)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_FormalParameter)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_Block)->accept(v);
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
    AstToken *lpg_finally;
    Block *lpg_Block;

    AstToken *getfinally() { return lpg_finally; };
    void setfinally(AstToken *lpg_finally) { this->lpg_finally = lpg_finally; }
    Block *getBlock() { return lpg_Block; };
    void setBlock(Block *lpg_Block) { this->lpg_Block = lpg_Block; }

    Finally(IToken* leftIToken, IToken* rightIToken,
            AstToken *lpg_finally,
            Block *lpg_Block):Ast(leftIToken, rightIToken)    {
        this->lpg_finally = lpg_finally;
        ((Ast*) lpg_finally)->setParent(this);
        this->lpg_Block = lpg_Block;
        ((Ast*) lpg_Block)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_finally);
        list.push_back((IAst*)lpg_Block);
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
            ((IAst*)lpg_finally)->accept(v);
            ((IAst*)lpg_Block)->accept(v);
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
    Ast *lpg_ArgumentList;
    AstToken *lpg_COMMA;
    Ast *lpg_Expression;

    Ast *getArgumentList() { return lpg_ArgumentList; };
    void setArgumentList(Ast *lpg_ArgumentList) { this->lpg_ArgumentList = lpg_ArgumentList; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }

    ArgumentList(IToken* leftIToken, IToken* rightIToken,
                 Ast *lpg_ArgumentList,
                 AstToken *lpg_COMMA,
                 Ast *lpg_Expression):Ast(leftIToken, rightIToken)    {
        this->lpg_ArgumentList = lpg_ArgumentList;
        ((Ast*) lpg_ArgumentList)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ArgumentList);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_Expression);
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
            ((IAst*)lpg_ArgumentList)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
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
    Ast *lpg_DimExprs;
    DimExpr *lpg_DimExpr;

    Ast *getDimExprs() { return lpg_DimExprs; };
    void setDimExprs(Ast *lpg_DimExprs) { this->lpg_DimExprs = lpg_DimExprs; }
    DimExpr *getDimExpr() { return lpg_DimExpr; };
    void setDimExpr(DimExpr *lpg_DimExpr) { this->lpg_DimExpr = lpg_DimExpr; }

    DimExprs(IToken* leftIToken, IToken* rightIToken,
             Ast *lpg_DimExprs,
             DimExpr *lpg_DimExpr):Ast(leftIToken, rightIToken)    {
        this->lpg_DimExprs = lpg_DimExprs;
        ((Ast*) lpg_DimExprs)->setParent(this);
        this->lpg_DimExpr = lpg_DimExpr;
        ((Ast*) lpg_DimExpr)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_DimExprs);
        list.push_back((IAst*)lpg_DimExpr);
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
            ((IAst*)lpg_DimExprs)->accept(v);
            ((IAst*)lpg_DimExpr)->accept(v);
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
    AstToken *lpg_LBRACKET;
    Ast *lpg_Expression;
    AstToken *lpg_RBRACKET;

    AstToken *getLBRACKET() { return lpg_LBRACKET; };
    void setLBRACKET(AstToken *lpg_LBRACKET) { this->lpg_LBRACKET = lpg_LBRACKET; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRBRACKET() { return lpg_RBRACKET; };
    void setRBRACKET(AstToken *lpg_RBRACKET) { this->lpg_RBRACKET = lpg_RBRACKET; }

    DimExpr(IToken* leftIToken, IToken* rightIToken,
            AstToken *lpg_LBRACKET,
            Ast *lpg_Expression,
            AstToken *lpg_RBRACKET):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACKET = lpg_LBRACKET;
        ((Ast*) lpg_LBRACKET)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RBRACKET = lpg_RBRACKET;
        ((Ast*) lpg_RBRACKET)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACKET);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RBRACKET);
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
            ((IAst*)lpg_LBRACKET)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RBRACKET)->accept(v);
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
    Ast *lpg_PostfixExpression;
    AstToken *lpg_PLUS_PLUS;

    Ast *getPostfixExpression() { return lpg_PostfixExpression; };
    void setPostfixExpression(Ast *lpg_PostfixExpression) { this->lpg_PostfixExpression = lpg_PostfixExpression; }
    AstToken *getPLUS_PLUS() { return lpg_PLUS_PLUS; };
    void setPLUS_PLUS(AstToken *lpg_PLUS_PLUS) { this->lpg_PLUS_PLUS = lpg_PLUS_PLUS; }

    PostIncrementExpression(IToken* leftIToken, IToken* rightIToken,
                            Ast *lpg_PostfixExpression,
                            AstToken *lpg_PLUS_PLUS):Ast(leftIToken, rightIToken)    {
        this->lpg_PostfixExpression = lpg_PostfixExpression;
        ((Ast*) lpg_PostfixExpression)->setParent(this);
        this->lpg_PLUS_PLUS = lpg_PLUS_PLUS;
        ((Ast*) lpg_PLUS_PLUS)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_PostfixExpression);
        list.push_back((IAst*)lpg_PLUS_PLUS);
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
            ((IAst*)lpg_PostfixExpression)->accept(v);
            ((IAst*)lpg_PLUS_PLUS)->accept(v);
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
    Ast *lpg_PostfixExpression;
    AstToken *lpg_MINUS_MINUS;

    Ast *getPostfixExpression() { return lpg_PostfixExpression; };
    void setPostfixExpression(Ast *lpg_PostfixExpression) { this->lpg_PostfixExpression = lpg_PostfixExpression; }
    AstToken *getMINUS_MINUS() { return lpg_MINUS_MINUS; };
    void setMINUS_MINUS(AstToken *lpg_MINUS_MINUS) { this->lpg_MINUS_MINUS = lpg_MINUS_MINUS; }

    PostDecrementExpression(IToken* leftIToken, IToken* rightIToken,
                            Ast *lpg_PostfixExpression,
                            AstToken *lpg_MINUS_MINUS):Ast(leftIToken, rightIToken)    {
        this->lpg_PostfixExpression = lpg_PostfixExpression;
        ((Ast*) lpg_PostfixExpression)->setParent(this);
        this->lpg_MINUS_MINUS = lpg_MINUS_MINUS;
        ((Ast*) lpg_MINUS_MINUS)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_PostfixExpression);
        list.push_back((IAst*)lpg_MINUS_MINUS);
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
            ((IAst*)lpg_PostfixExpression)->accept(v);
            ((IAst*)lpg_MINUS_MINUS)->accept(v);
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
    AstToken *lpg_PLUS_PLUS;
    Ast *lpg_UnaryExpression;

    AstToken *getPLUS_PLUS() { return lpg_PLUS_PLUS; };
    void setPLUS_PLUS(AstToken *lpg_PLUS_PLUS) { this->lpg_PLUS_PLUS = lpg_PLUS_PLUS; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    PreIncrementExpression(IToken* leftIToken, IToken* rightIToken,
                           AstToken *lpg_PLUS_PLUS,
                           Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_PLUS_PLUS = lpg_PLUS_PLUS;
        ((Ast*) lpg_PLUS_PLUS)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_PLUS_PLUS);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_PLUS_PLUS)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    AstToken *lpg_MINUS_MINUS;
    Ast *lpg_UnaryExpression;

    AstToken *getMINUS_MINUS() { return lpg_MINUS_MINUS; };
    void setMINUS_MINUS(AstToken *lpg_MINUS_MINUS) { this->lpg_MINUS_MINUS = lpg_MINUS_MINUS; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    PreDecrementExpression(IToken* leftIToken, IToken* rightIToken,
                           AstToken *lpg_MINUS_MINUS,
                           Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_MINUS_MINUS = lpg_MINUS_MINUS;
        ((Ast*) lpg_MINUS_MINUS)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MINUS_MINUS);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_MINUS_MINUS)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    Ast *lpg_AndExpression;
    AstToken *lpg_AND;
    Ast *lpg_EqualityExpression;

    Ast *getAndExpression() { return lpg_AndExpression; };
    void setAndExpression(Ast *lpg_AndExpression) { this->lpg_AndExpression = lpg_AndExpression; }
    AstToken *getAND() { return lpg_AND; };
    void setAND(AstToken *lpg_AND) { this->lpg_AND = lpg_AND; }
    Ast *getEqualityExpression() { return lpg_EqualityExpression; };
    void setEqualityExpression(Ast *lpg_EqualityExpression) { this->lpg_EqualityExpression = lpg_EqualityExpression; }

    AndExpression(IToken* leftIToken, IToken* rightIToken,
                  Ast *lpg_AndExpression,
                  AstToken *lpg_AND,
                  Ast *lpg_EqualityExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_AndExpression = lpg_AndExpression;
        ((Ast*) lpg_AndExpression)->setParent(this);
        this->lpg_AND = lpg_AND;
        ((Ast*) lpg_AND)->setParent(this);
        this->lpg_EqualityExpression = lpg_EqualityExpression;
        ((Ast*) lpg_EqualityExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AndExpression);
        list.push_back((IAst*)lpg_AND);
        list.push_back((IAst*)lpg_EqualityExpression);
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
            ((IAst*)lpg_AndExpression)->accept(v);
            ((IAst*)lpg_AND)->accept(v);
            ((IAst*)lpg_EqualityExpression)->accept(v);
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
    Ast *lpg_ExclusiveOrExpression;
    AstToken *lpg_XOR;
    Ast *lpg_AndExpression;

    Ast *getExclusiveOrExpression() { return lpg_ExclusiveOrExpression; };
    void setExclusiveOrExpression(Ast *lpg_ExclusiveOrExpression) { this->lpg_ExclusiveOrExpression = lpg_ExclusiveOrExpression; }
    AstToken *getXOR() { return lpg_XOR; };
    void setXOR(AstToken *lpg_XOR) { this->lpg_XOR = lpg_XOR; }
    Ast *getAndExpression() { return lpg_AndExpression; };
    void setAndExpression(Ast *lpg_AndExpression) { this->lpg_AndExpression = lpg_AndExpression; }

    ExclusiveOrExpression(IToken* leftIToken, IToken* rightIToken,
                          Ast *lpg_ExclusiveOrExpression,
                          AstToken *lpg_XOR,
                          Ast *lpg_AndExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_ExclusiveOrExpression = lpg_ExclusiveOrExpression;
        ((Ast*) lpg_ExclusiveOrExpression)->setParent(this);
        this->lpg_XOR = lpg_XOR;
        ((Ast*) lpg_XOR)->setParent(this);
        this->lpg_AndExpression = lpg_AndExpression;
        ((Ast*) lpg_AndExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ExclusiveOrExpression);
        list.push_back((IAst*)lpg_XOR);
        list.push_back((IAst*)lpg_AndExpression);
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
            ((IAst*)lpg_ExclusiveOrExpression)->accept(v);
            ((IAst*)lpg_XOR)->accept(v);
            ((IAst*)lpg_AndExpression)->accept(v);
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
    Ast *lpg_InclusiveOrExpression;
    AstToken *lpg_OR;
    Ast *lpg_ExclusiveOrExpression;

    Ast *getInclusiveOrExpression() { return lpg_InclusiveOrExpression; };
    void setInclusiveOrExpression(Ast *lpg_InclusiveOrExpression) { this->lpg_InclusiveOrExpression = lpg_InclusiveOrExpression; }
    AstToken *getOR() { return lpg_OR; };
    void setOR(AstToken *lpg_OR) { this->lpg_OR = lpg_OR; }
    Ast *getExclusiveOrExpression() { return lpg_ExclusiveOrExpression; };
    void setExclusiveOrExpression(Ast *lpg_ExclusiveOrExpression) { this->lpg_ExclusiveOrExpression = lpg_ExclusiveOrExpression; }

    InclusiveOrExpression(IToken* leftIToken, IToken* rightIToken,
                          Ast *lpg_InclusiveOrExpression,
                          AstToken *lpg_OR,
                          Ast *lpg_ExclusiveOrExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_InclusiveOrExpression = lpg_InclusiveOrExpression;
        ((Ast*) lpg_InclusiveOrExpression)->setParent(this);
        this->lpg_OR = lpg_OR;
        ((Ast*) lpg_OR)->setParent(this);
        this->lpg_ExclusiveOrExpression = lpg_ExclusiveOrExpression;
        ((Ast*) lpg_ExclusiveOrExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_InclusiveOrExpression);
        list.push_back((IAst*)lpg_OR);
        list.push_back((IAst*)lpg_ExclusiveOrExpression);
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
            ((IAst*)lpg_InclusiveOrExpression)->accept(v);
            ((IAst*)lpg_OR)->accept(v);
            ((IAst*)lpg_ExclusiveOrExpression)->accept(v);
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
    Ast *lpg_ConditionalAndExpression;
    AstToken *lpg_AND_AND;
    Ast *lpg_InclusiveOrExpression;

    Ast *getConditionalAndExpression() { return lpg_ConditionalAndExpression; };
    void setConditionalAndExpression(Ast *lpg_ConditionalAndExpression) { this->lpg_ConditionalAndExpression = lpg_ConditionalAndExpression; }
    AstToken *getAND_AND() { return lpg_AND_AND; };
    void setAND_AND(AstToken *lpg_AND_AND) { this->lpg_AND_AND = lpg_AND_AND; }
    Ast *getInclusiveOrExpression() { return lpg_InclusiveOrExpression; };
    void setInclusiveOrExpression(Ast *lpg_InclusiveOrExpression) { this->lpg_InclusiveOrExpression = lpg_InclusiveOrExpression; }

    ConditionalAndExpression(IToken* leftIToken, IToken* rightIToken,
                             Ast *lpg_ConditionalAndExpression,
                             AstToken *lpg_AND_AND,
                             Ast *lpg_InclusiveOrExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_ConditionalAndExpression = lpg_ConditionalAndExpression;
        ((Ast*) lpg_ConditionalAndExpression)->setParent(this);
        this->lpg_AND_AND = lpg_AND_AND;
        ((Ast*) lpg_AND_AND)->setParent(this);
        this->lpg_InclusiveOrExpression = lpg_InclusiveOrExpression;
        ((Ast*) lpg_InclusiveOrExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ConditionalAndExpression);
        list.push_back((IAst*)lpg_AND_AND);
        list.push_back((IAst*)lpg_InclusiveOrExpression);
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
            ((IAst*)lpg_ConditionalAndExpression)->accept(v);
            ((IAst*)lpg_AND_AND)->accept(v);
            ((IAst*)lpg_InclusiveOrExpression)->accept(v);
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
    Ast *lpg_ConditionalOrExpression;
    AstToken *lpg_OR_OR;
    Ast *lpg_ConditionalAndExpression;

    Ast *getConditionalOrExpression() { return lpg_ConditionalOrExpression; };
    void setConditionalOrExpression(Ast *lpg_ConditionalOrExpression) { this->lpg_ConditionalOrExpression = lpg_ConditionalOrExpression; }
    AstToken *getOR_OR() { return lpg_OR_OR; };
    void setOR_OR(AstToken *lpg_OR_OR) { this->lpg_OR_OR = lpg_OR_OR; }
    Ast *getConditionalAndExpression() { return lpg_ConditionalAndExpression; };
    void setConditionalAndExpression(Ast *lpg_ConditionalAndExpression) { this->lpg_ConditionalAndExpression = lpg_ConditionalAndExpression; }

    ConditionalOrExpression(IToken* leftIToken, IToken* rightIToken,
                            Ast *lpg_ConditionalOrExpression,
                            AstToken *lpg_OR_OR,
                            Ast *lpg_ConditionalAndExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_ConditionalOrExpression = lpg_ConditionalOrExpression;
        ((Ast*) lpg_ConditionalOrExpression)->setParent(this);
        this->lpg_OR_OR = lpg_OR_OR;
        ((Ast*) lpg_OR_OR)->setParent(this);
        this->lpg_ConditionalAndExpression = lpg_ConditionalAndExpression;
        ((Ast*) lpg_ConditionalAndExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ConditionalOrExpression);
        list.push_back((IAst*)lpg_OR_OR);
        list.push_back((IAst*)lpg_ConditionalAndExpression);
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
            ((IAst*)lpg_ConditionalOrExpression)->accept(v);
            ((IAst*)lpg_OR_OR)->accept(v);
            ((IAst*)lpg_ConditionalAndExpression)->accept(v);
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
    Ast *lpg_ConditionalOrExpression;
    AstToken *lpg_QUESTION;
    Ast *lpg_Expression;
    AstToken *lpg_COLON;
    Ast *lpg_ConditionalExpression;

    Ast *getConditionalOrExpression() { return lpg_ConditionalOrExpression; };
    void setConditionalOrExpression(Ast *lpg_ConditionalOrExpression) { this->lpg_ConditionalOrExpression = lpg_ConditionalOrExpression; }
    AstToken *getQUESTION() { return lpg_QUESTION; };
    void setQUESTION(AstToken *lpg_QUESTION) { this->lpg_QUESTION = lpg_QUESTION; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getCOLON() { return lpg_COLON; };
    void setCOLON(AstToken *lpg_COLON) { this->lpg_COLON = lpg_COLON; }
    Ast *getConditionalExpression() { return lpg_ConditionalExpression; };
    void setConditionalExpression(Ast *lpg_ConditionalExpression) { this->lpg_ConditionalExpression = lpg_ConditionalExpression; }

    ConditionalExpression(IToken* leftIToken, IToken* rightIToken,
                          Ast *lpg_ConditionalOrExpression,
                          AstToken *lpg_QUESTION,
                          Ast *lpg_Expression,
                          AstToken *lpg_COLON,
                          Ast *lpg_ConditionalExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_ConditionalOrExpression = lpg_ConditionalOrExpression;
        ((Ast*) lpg_ConditionalOrExpression)->setParent(this);
        this->lpg_QUESTION = lpg_QUESTION;
        ((Ast*) lpg_QUESTION)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_COLON = lpg_COLON;
        ((Ast*) lpg_COLON)->setParent(this);
        this->lpg_ConditionalExpression = lpg_ConditionalExpression;
        ((Ast*) lpg_ConditionalExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ConditionalOrExpression);
        list.push_back((IAst*)lpg_QUESTION);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_COLON);
        list.push_back((IAst*)lpg_ConditionalExpression);
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
            ((IAst*)lpg_ConditionalOrExpression)->accept(v);
            ((IAst*)lpg_QUESTION)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_COLON)->accept(v);
            ((IAst*)lpg_ConditionalExpression)->accept(v);
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
    Ast *lpg_LeftHandSide;
    Ast *lpg_AssignmentOperator;
    Ast *lpg_AssignmentExpression;

    Ast *getLeftHandSide() { return lpg_LeftHandSide; };
    void setLeftHandSide(Ast *lpg_LeftHandSide) { this->lpg_LeftHandSide = lpg_LeftHandSide; }
    Ast *getAssignmentOperator() { return lpg_AssignmentOperator; };
    void setAssignmentOperator(Ast *lpg_AssignmentOperator) { this->lpg_AssignmentOperator = lpg_AssignmentOperator; }
    Ast *getAssignmentExpression() { return lpg_AssignmentExpression; };
    void setAssignmentExpression(Ast *lpg_AssignmentExpression) { this->lpg_AssignmentExpression = lpg_AssignmentExpression; }

    Assignment(IToken* leftIToken, IToken* rightIToken,
               Ast *lpg_LeftHandSide,
               Ast *lpg_AssignmentOperator,
               Ast *lpg_AssignmentExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_LeftHandSide = lpg_LeftHandSide;
        ((Ast*) lpg_LeftHandSide)->setParent(this);
        this->lpg_AssignmentOperator = lpg_AssignmentOperator;
        ((Ast*) lpg_AssignmentOperator)->setParent(this);
        this->lpg_AssignmentExpression = lpg_AssignmentExpression;
        ((Ast*) lpg_AssignmentExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LeftHandSide);
        list.push_back((IAst*)lpg_AssignmentOperator);
        list.push_back((IAst*)lpg_AssignmentExpression);
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
            ((IAst*)lpg_LeftHandSide)->accept(v);
            ((IAst*)lpg_AssignmentOperator)->accept(v);
            ((IAst*)lpg_AssignmentExpression)->accept(v);
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
    AstToken *lpg_BeginAction;
    Ast *lpg_BlockStatementsopt;
    AstToken *lpg_EndAction;

    AstToken *getBeginAction() { return lpg_BeginAction; };
    void setBeginAction(AstToken *lpg_BeginAction) { this->lpg_BeginAction = lpg_BeginAction; }
    /**
     * The value returned by <b>getBlockStatementsopt</b> may be <b>nullptr</b>
     */
    Ast *getBlockStatementsopt() { return lpg_BlockStatementsopt; };
    void setBlockStatementsopt(Ast *lpg_BlockStatementsopt) { this->lpg_BlockStatementsopt = lpg_BlockStatementsopt; }
    AstToken *getEndAction() { return lpg_EndAction; };
    void setEndAction(AstToken *lpg_EndAction) { this->lpg_EndAction = lpg_EndAction; }

    LPGUserAction0(IToken* leftIToken, IToken* rightIToken,
                   AstToken *lpg_BeginAction,
                   Ast *lpg_BlockStatementsopt,
                   AstToken *lpg_EndAction):Ast(leftIToken, rightIToken)    {
        this->lpg_BeginAction = lpg_BeginAction;
        ((Ast*) lpg_BeginAction)->setParent(this);
        this->lpg_BlockStatementsopt = lpg_BlockStatementsopt;
        if (lpg_BlockStatementsopt != nullptr) ((Ast*) lpg_BlockStatementsopt)->setParent(this);
        this->lpg_EndAction = lpg_EndAction;
        ((Ast*) lpg_EndAction)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_BeginAction);
        list.push_back((IAst*)lpg_BlockStatementsopt);
        list.push_back((IAst*)lpg_EndAction);
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
            ((IAst*)lpg_BeginAction)->accept(v);
            if (lpg_BlockStatementsopt != nullptr) ((IAst*)lpg_BlockStatementsopt)->accept(v);
            ((IAst*)lpg_EndAction)->accept(v);
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
    AstToken *lpg_BeginJava;
    Ast *lpg_BlockStatementsopt;
    AstToken *lpg_EndJava;

    AstToken *getBeginJava() { return lpg_BeginJava; };
    void setBeginJava(AstToken *lpg_BeginJava) { this->lpg_BeginJava = lpg_BeginJava; }
    /**
     * The value returned by <b>getBlockStatementsopt</b> may be <b>nullptr</b>
     */
    Ast *getBlockStatementsopt() { return lpg_BlockStatementsopt; };
    void setBlockStatementsopt(Ast *lpg_BlockStatementsopt) { this->lpg_BlockStatementsopt = lpg_BlockStatementsopt; }
    AstToken *getEndJava() { return lpg_EndJava; };
    void setEndJava(AstToken *lpg_EndJava) { this->lpg_EndJava = lpg_EndJava; }

    LPGUserAction1(IToken* leftIToken, IToken* rightIToken,
                   AstToken *lpg_BeginJava,
                   Ast *lpg_BlockStatementsopt,
                   AstToken *lpg_EndJava):Ast(leftIToken, rightIToken)    {
        this->lpg_BeginJava = lpg_BeginJava;
        ((Ast*) lpg_BeginJava)->setParent(this);
        this->lpg_BlockStatementsopt = lpg_BlockStatementsopt;
        if (lpg_BlockStatementsopt != nullptr) ((Ast*) lpg_BlockStatementsopt)->setParent(this);
        this->lpg_EndJava = lpg_EndJava;
        ((Ast*) lpg_EndJava)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_BeginJava);
        list.push_back((IAst*)lpg_BlockStatementsopt);
        list.push_back((IAst*)lpg_EndJava);
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
            ((IAst*)lpg_BeginJava)->accept(v);
            if (lpg_BlockStatementsopt != nullptr) ((IAst*)lpg_BlockStatementsopt)->accept(v);
            ((IAst*)lpg_EndJava)->accept(v);
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
    AstToken *lpg_extends;
    Ast *lpg_ReferenceType;

    AstToken *getextends() { return lpg_extends; };
    void setextends(AstToken *lpg_extends) { this->lpg_extends = lpg_extends; }
    Ast *getReferenceType() { return lpg_ReferenceType; };
    void setReferenceType(Ast *lpg_ReferenceType) { this->lpg_ReferenceType = lpg_ReferenceType; }

    WildcardBounds0(IToken* leftIToken, IToken* rightIToken,
                    AstToken *lpg_extends,
                    Ast *lpg_ReferenceType):Ast(leftIToken, rightIToken)    {
        this->lpg_extends = lpg_extends;
        ((Ast*) lpg_extends)->setParent(this);
        this->lpg_ReferenceType = lpg_ReferenceType;
        ((Ast*) lpg_ReferenceType)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_extends);
        list.push_back((IAst*)lpg_ReferenceType);
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
            ((IAst*)lpg_extends)->accept(v);
            ((IAst*)lpg_ReferenceType)->accept(v);
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
    AstToken *lpg_super;
    Ast *lpg_ReferenceType;

    AstToken *getsuper() { return lpg_super; };
    void setsuper(AstToken *lpg_super) { this->lpg_super = lpg_super; }
    Ast *getReferenceType() { return lpg_ReferenceType; };
    void setReferenceType(Ast *lpg_ReferenceType) { this->lpg_ReferenceType = lpg_ReferenceType; }

    WildcardBounds1(IToken* leftIToken, IToken* rightIToken,
                    AstToken *lpg_super,
                    Ast *lpg_ReferenceType):Ast(leftIToken, rightIToken)    {
        this->lpg_super = lpg_super;
        ((Ast*) lpg_super)->setParent(this);
        this->lpg_ReferenceType = lpg_ReferenceType;
        ((Ast*) lpg_ReferenceType)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_super);
        list.push_back((IAst*)lpg_ReferenceType);
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
            ((IAst*)lpg_super)->accept(v);
            ((IAst*)lpg_ReferenceType)->accept(v);
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
    identifier *lpg_identifier;
    AstToken *lpg_LPAREN;
    Ast *lpg_FormalParameterListopt;
    AstToken *lpg_RPAREN;

    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getFormalParameterListopt</b> may be <b>nullptr</b>
     */
    Ast *getFormalParameterListopt() { return lpg_FormalParameterListopt; };
    void setFormalParameterListopt(Ast *lpg_FormalParameterListopt) { this->lpg_FormalParameterListopt = lpg_FormalParameterListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    MethodDeclarator0(IToken* leftIToken, IToken* rightIToken,
                      identifier *lpg_identifier,
                      AstToken *lpg_LPAREN,
                      Ast *lpg_FormalParameterListopt,
                      AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_FormalParameterListopt = lpg_FormalParameterListopt;
        if (lpg_FormalParameterListopt != nullptr) ((Ast*) lpg_FormalParameterListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_FormalParameterListopt);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_FormalParameterListopt != nullptr) ((IAst*)lpg_FormalParameterListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    Ast *lpg_MethodDeclarator;
    AstToken *lpg_LBRACKET;
    AstToken *lpg_RBRACKET;

    Ast *getMethodDeclarator() { return lpg_MethodDeclarator; };
    void setMethodDeclarator(Ast *lpg_MethodDeclarator) { this->lpg_MethodDeclarator = lpg_MethodDeclarator; }
    AstToken *getLBRACKET() { return lpg_LBRACKET; };
    void setLBRACKET(AstToken *lpg_LBRACKET) { this->lpg_LBRACKET = lpg_LBRACKET; }
    AstToken *getRBRACKET() { return lpg_RBRACKET; };
    void setRBRACKET(AstToken *lpg_RBRACKET) { this->lpg_RBRACKET = lpg_RBRACKET; }

    MethodDeclarator1(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_MethodDeclarator,
                      AstToken *lpg_LBRACKET,
                      AstToken *lpg_RBRACKET):Ast(leftIToken, rightIToken)    {
        this->lpg_MethodDeclarator = lpg_MethodDeclarator;
        ((Ast*) lpg_MethodDeclarator)->setParent(this);
        this->lpg_LBRACKET = lpg_LBRACKET;
        ((Ast*) lpg_LBRACKET)->setParent(this);
        this->lpg_RBRACKET = lpg_RBRACKET;
        ((Ast*) lpg_RBRACKET)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MethodDeclarator);
        list.push_back((IAst*)lpg_LBRACKET);
        list.push_back((IAst*)lpg_RBRACKET);
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
            ((IAst*)lpg_MethodDeclarator)->accept(v);
            ((IAst*)lpg_LBRACKET)->accept(v);
            ((IAst*)lpg_RBRACKET)->accept(v);
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
    TypeArguments *lpg_TypeArgumentsopt;
    AstToken *lpg_this;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;
    AstToken *lpg_SEMICOLON;

    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }
    AstToken *getthis() { return lpg_this; };
    void setthis(AstToken *lpg_this) { this->lpg_this = lpg_this; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    ExplicitConstructorInvocation0(IToken* leftIToken, IToken* rightIToken,
                                   TypeArguments *lpg_TypeArgumentsopt,
                                   AstToken *lpg_this,
                                   AstToken *lpg_LPAREN,
                                   Ast *lpg_ArgumentListopt,
                                   AstToken *lpg_RPAREN,
                                   AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        this->lpg_this = lpg_this;
        ((Ast*) lpg_this)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeArgumentsopt);
        list.push_back((IAst*)lpg_this);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
            ((IAst*)lpg_this)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    TypeArguments *lpg_TypeArgumentsopt;
    AstToken *lpg_super;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;
    AstToken *lpg_SEMICOLON;

    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }
    AstToken *getsuper() { return lpg_super; };
    void setsuper(AstToken *lpg_super) { this->lpg_super = lpg_super; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    ExplicitConstructorInvocation1(IToken* leftIToken, IToken* rightIToken,
                                   TypeArguments *lpg_TypeArgumentsopt,
                                   AstToken *lpg_super,
                                   AstToken *lpg_LPAREN,
                                   Ast *lpg_ArgumentListopt,
                                   AstToken *lpg_RPAREN,
                                   AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        this->lpg_super = lpg_super;
        ((Ast*) lpg_super)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeArgumentsopt);
        list.push_back((IAst*)lpg_super);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
            ((IAst*)lpg_super)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    Ast *lpg_Primary;
    AstToken *lpg_DOT;
    TypeArguments *lpg_TypeArgumentsopt;
    AstToken *lpg_super;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;
    AstToken *lpg_SEMICOLON;

    Ast *getPrimary() { return lpg_Primary; };
    void setPrimary(Ast *lpg_Primary) { this->lpg_Primary = lpg_Primary; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }
    AstToken *getsuper() { return lpg_super; };
    void setsuper(AstToken *lpg_super) { this->lpg_super = lpg_super; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    ExplicitConstructorInvocation2(IToken* leftIToken, IToken* rightIToken,
                                   Ast *lpg_Primary,
                                   AstToken *lpg_DOT,
                                   TypeArguments *lpg_TypeArgumentsopt,
                                   AstToken *lpg_super,
                                   AstToken *lpg_LPAREN,
                                   Ast *lpg_ArgumentListopt,
                                   AstToken *lpg_RPAREN,
                                   AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_Primary = lpg_Primary;
        ((Ast*) lpg_Primary)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        this->lpg_super = lpg_super;
        ((Ast*) lpg_super)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Primary);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_TypeArgumentsopt);
        list.push_back((IAst*)lpg_super);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_Primary)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
            ((IAst*)lpg_super)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_extends;
    InterfaceType *lpg_InterfaceType;

    AstToken *getextends() { return lpg_extends; };
    void setextends(AstToken *lpg_extends) { this->lpg_extends = lpg_extends; }
    InterfaceType *getInterfaceType() { return lpg_InterfaceType; };
    void setInterfaceType(InterfaceType *lpg_InterfaceType) { this->lpg_InterfaceType = lpg_InterfaceType; }

    ExtendsInterfaces0(IToken* leftIToken, IToken* rightIToken,
                       AstToken *lpg_extends,
                       InterfaceType *lpg_InterfaceType):Ast(leftIToken, rightIToken)    {
        this->lpg_extends = lpg_extends;
        ((Ast*) lpg_extends)->setParent(this);
        this->lpg_InterfaceType = lpg_InterfaceType;
        ((Ast*) lpg_InterfaceType)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_extends);
        list.push_back((IAst*)lpg_InterfaceType);
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
            ((IAst*)lpg_extends)->accept(v);
            ((IAst*)lpg_InterfaceType)->accept(v);
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
    Ast *lpg_ExtendsInterfaces;
    AstToken *lpg_COMMA;
    InterfaceType *lpg_InterfaceType;

    Ast *getExtendsInterfaces() { return lpg_ExtendsInterfaces; };
    void setExtendsInterfaces(Ast *lpg_ExtendsInterfaces) { this->lpg_ExtendsInterfaces = lpg_ExtendsInterfaces; }
    AstToken *getCOMMA() { return lpg_COMMA; };
    void setCOMMA(AstToken *lpg_COMMA) { this->lpg_COMMA = lpg_COMMA; }
    InterfaceType *getInterfaceType() { return lpg_InterfaceType; };
    void setInterfaceType(InterfaceType *lpg_InterfaceType) { this->lpg_InterfaceType = lpg_InterfaceType; }

    ExtendsInterfaces1(IToken* leftIToken, IToken* rightIToken,
                       Ast *lpg_ExtendsInterfaces,
                       AstToken *lpg_COMMA,
                       InterfaceType *lpg_InterfaceType):Ast(leftIToken, rightIToken)    {
        this->lpg_ExtendsInterfaces = lpg_ExtendsInterfaces;
        ((Ast*) lpg_ExtendsInterfaces)->setParent(this);
        this->lpg_COMMA = lpg_COMMA;
        ((Ast*) lpg_COMMA)->setParent(this);
        this->lpg_InterfaceType = lpg_InterfaceType;
        ((Ast*) lpg_InterfaceType)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ExtendsInterfaces);
        list.push_back((IAst*)lpg_COMMA);
        list.push_back((IAst*)lpg_InterfaceType);
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
            ((IAst*)lpg_ExtendsInterfaces)->accept(v);
            ((IAst*)lpg_COMMA)->accept(v);
            ((IAst*)lpg_InterfaceType)->accept(v);
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
    Ast *lpg_AbstractMethodModifiersopt;
    Ast *lpg_Type;
    identifier *lpg_identifier;
    AstToken *lpg_LPAREN;
    AstToken *lpg_RPAREN;
    DefaultValue *lpg_DefaultValueopt;
    AstToken *lpg_SEMICOLON;

    /**
     * The value returned by <b>getAbstractMethodModifiersopt</b> may be <b>nullptr</b>
     */
    Ast *getAbstractMethodModifiersopt() { return lpg_AbstractMethodModifiersopt; };
    void setAbstractMethodModifiersopt(Ast *lpg_AbstractMethodModifiersopt) { this->lpg_AbstractMethodModifiersopt = lpg_AbstractMethodModifiersopt; }
    Ast *getType() { return lpg_Type; };
    void setType(Ast *lpg_Type) { this->lpg_Type = lpg_Type; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    /**
     * The value returned by <b>getDefaultValueopt</b> may be <b>nullptr</b>
     */
    DefaultValue *getDefaultValueopt() { return lpg_DefaultValueopt; };
    void setDefaultValueopt(DefaultValue *lpg_DefaultValueopt) { this->lpg_DefaultValueopt = lpg_DefaultValueopt; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    AnnotationTypeElementDeclaration0(IToken* leftIToken, IToken* rightIToken,
                                      Ast *lpg_AbstractMethodModifiersopt,
                                      Ast *lpg_Type,
                                      identifier *lpg_identifier,
                                      AstToken *lpg_LPAREN,
                                      AstToken *lpg_RPAREN,
                                      DefaultValue *lpg_DefaultValueopt,
                                      AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_AbstractMethodModifiersopt = lpg_AbstractMethodModifiersopt;
        if (lpg_AbstractMethodModifiersopt != nullptr) ((Ast*) lpg_AbstractMethodModifiersopt)->setParent(this);
        this->lpg_Type = lpg_Type;
        ((Ast*) lpg_Type)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_DefaultValueopt = lpg_DefaultValueopt;
        if (lpg_DefaultValueopt != nullptr) ((Ast*) lpg_DefaultValueopt)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AbstractMethodModifiersopt);
        list.push_back((IAst*)lpg_Type);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_DefaultValueopt);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            if (lpg_AbstractMethodModifiersopt != nullptr) ((IAst*)lpg_AbstractMethodModifiersopt)->accept(v);
            ((IAst*)lpg_Type)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            if (lpg_DefaultValueopt != nullptr) ((IAst*)lpg_DefaultValueopt)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_assert;
    Ast *lpg_Expression;
    AstToken *lpg_SEMICOLON;

    AstToken *getassert() { return lpg_assert; };
    void setassert(AstToken *lpg_assert) { this->lpg_assert = lpg_assert; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    AssertStatement0(IToken* leftIToken, IToken* rightIToken,
                     AstToken *lpg_assert,
                     Ast *lpg_Expression,
                     AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_assert = lpg_assert;
        ((Ast*) lpg_assert)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_assert);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_assert)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_assert;
    Ast *lpg_Expression;
    AstToken *lpg_COLON;
    Ast *lpg_Expression4;
    AstToken *lpg_SEMICOLON;

    AstToken *getassert() { return lpg_assert; };
    void setassert(AstToken *lpg_assert) { this->lpg_assert = lpg_assert; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getCOLON() { return lpg_COLON; };
    void setCOLON(AstToken *lpg_COLON) { this->lpg_COLON = lpg_COLON; }
    Ast *getExpression4() { return lpg_Expression4; };
    void setExpression4(Ast *lpg_Expression4) { this->lpg_Expression4 = lpg_Expression4; }
    AstToken *getSEMICOLON() { return lpg_SEMICOLON; };
    void setSEMICOLON(AstToken *lpg_SEMICOLON) { this->lpg_SEMICOLON = lpg_SEMICOLON; }

    AssertStatement1(IToken* leftIToken, IToken* rightIToken,
                     AstToken *lpg_assert,
                     Ast *lpg_Expression,
                     AstToken *lpg_COLON,
                     Ast *lpg_Expression4,
                     AstToken *lpg_SEMICOLON):Ast(leftIToken, rightIToken)    {
        this->lpg_assert = lpg_assert;
        ((Ast*) lpg_assert)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_COLON = lpg_COLON;
        ((Ast*) lpg_COLON)->setParent(this);
        this->lpg_Expression4 = lpg_Expression4;
        ((Ast*) lpg_Expression4)->setParent(this);
        this->lpg_SEMICOLON = lpg_SEMICOLON;
        ((Ast*) lpg_SEMICOLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_assert);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_COLON);
        list.push_back((IAst*)lpg_Expression4);
        list.push_back((IAst*)lpg_SEMICOLON);
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
            ((IAst*)lpg_assert)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_COLON)->accept(v);
            ((IAst*)lpg_Expression4)->accept(v);
            ((IAst*)lpg_SEMICOLON)->accept(v);
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
    AstToken *lpg_case;
    Ast *lpg_ConstantExpression;
    AstToken *lpg_COLON;

    AstToken *getcase() { return lpg_case; };
    void setcase(AstToken *lpg_case) { this->lpg_case = lpg_case; }
    Ast *getConstantExpression() { return lpg_ConstantExpression; };
    void setConstantExpression(Ast *lpg_ConstantExpression) { this->lpg_ConstantExpression = lpg_ConstantExpression; }
    AstToken *getCOLON() { return lpg_COLON; };
    void setCOLON(AstToken *lpg_COLON) { this->lpg_COLON = lpg_COLON; }

    SwitchLabel0(IToken* leftIToken, IToken* rightIToken,
                 AstToken *lpg_case,
                 Ast *lpg_ConstantExpression,
                 AstToken *lpg_COLON):Ast(leftIToken, rightIToken)    {
        this->lpg_case = lpg_case;
        ((Ast*) lpg_case)->setParent(this);
        this->lpg_ConstantExpression = lpg_ConstantExpression;
        ((Ast*) lpg_ConstantExpression)->setParent(this);
        this->lpg_COLON = lpg_COLON;
        ((Ast*) lpg_COLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_case);
        list.push_back((IAst*)lpg_ConstantExpression);
        list.push_back((IAst*)lpg_COLON);
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
            ((IAst*)lpg_case)->accept(v);
            ((IAst*)lpg_ConstantExpression)->accept(v);
            ((IAst*)lpg_COLON)->accept(v);
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
    AstToken *lpg_case;
    Ast *lpg_EnumConstant;
    AstToken *lpg_COLON;

    AstToken *getcase() { return lpg_case; };
    void setcase(AstToken *lpg_case) { this->lpg_case = lpg_case; }
    Ast *getEnumConstant() { return lpg_EnumConstant; };
    void setEnumConstant(Ast *lpg_EnumConstant) { this->lpg_EnumConstant = lpg_EnumConstant; }
    AstToken *getCOLON() { return lpg_COLON; };
    void setCOLON(AstToken *lpg_COLON) { this->lpg_COLON = lpg_COLON; }

    SwitchLabel1(IToken* leftIToken, IToken* rightIToken,
                 AstToken *lpg_case,
                 Ast *lpg_EnumConstant,
                 AstToken *lpg_COLON):Ast(leftIToken, rightIToken)    {
        this->lpg_case = lpg_case;
        ((Ast*) lpg_case)->setParent(this);
        this->lpg_EnumConstant = lpg_EnumConstant;
        ((Ast*) lpg_EnumConstant)->setParent(this);
        this->lpg_COLON = lpg_COLON;
        ((Ast*) lpg_COLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_case);
        list.push_back((IAst*)lpg_EnumConstant);
        list.push_back((IAst*)lpg_COLON);
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
            ((IAst*)lpg_case)->accept(v);
            ((IAst*)lpg_EnumConstant)->accept(v);
            ((IAst*)lpg_COLON)->accept(v);
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
    AstToken *lpg_default;
    AstToken *lpg_COLON;

    AstToken *getdefault() { return lpg_default; };
    void setdefault(AstToken *lpg_default) { this->lpg_default = lpg_default; }
    AstToken *getCOLON() { return lpg_COLON; };
    void setCOLON(AstToken *lpg_COLON) { this->lpg_COLON = lpg_COLON; }

    SwitchLabel2(IToken* leftIToken, IToken* rightIToken,
                 AstToken *lpg_default,
                 AstToken *lpg_COLON):Ast(leftIToken, rightIToken)    {
        this->lpg_default = lpg_default;
        ((Ast*) lpg_default)->setParent(this);
        this->lpg_COLON = lpg_COLON;
        ((Ast*) lpg_COLON)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_default);
        list.push_back((IAst*)lpg_COLON);
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
            ((IAst*)lpg_default)->accept(v);
            ((IAst*)lpg_COLON)->accept(v);
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
    AstToken *lpg_try;
    Block *lpg_Block;
    Ast *lpg_Catches;

    AstToken *gettry() { return lpg_try; };
    void settry(AstToken *lpg_try) { this->lpg_try = lpg_try; }
    Block *getBlock() { return lpg_Block; };
    void setBlock(Block *lpg_Block) { this->lpg_Block = lpg_Block; }
    Ast *getCatches() { return lpg_Catches; };
    void setCatches(Ast *lpg_Catches) { this->lpg_Catches = lpg_Catches; }

    TryStatement0(IToken* leftIToken, IToken* rightIToken,
                  AstToken *lpg_try,
                  Block *lpg_Block,
                  Ast *lpg_Catches):Ast(leftIToken, rightIToken)    {
        this->lpg_try = lpg_try;
        ((Ast*) lpg_try)->setParent(this);
        this->lpg_Block = lpg_Block;
        ((Ast*) lpg_Block)->setParent(this);
        this->lpg_Catches = lpg_Catches;
        ((Ast*) lpg_Catches)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_try);
        list.push_back((IAst*)lpg_Block);
        list.push_back((IAst*)lpg_Catches);
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
            ((IAst*)lpg_try)->accept(v);
            ((IAst*)lpg_Block)->accept(v);
            ((IAst*)lpg_Catches)->accept(v);
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
    AstToken *lpg_try;
    Block *lpg_Block;
    Ast *lpg_Catchesopt;
    Finally *lpg_Finally;

    AstToken *gettry() { return lpg_try; };
    void settry(AstToken *lpg_try) { this->lpg_try = lpg_try; }
    Block *getBlock() { return lpg_Block; };
    void setBlock(Block *lpg_Block) { this->lpg_Block = lpg_Block; }
    /**
     * The value returned by <b>getCatchesopt</b> may be <b>nullptr</b>
     */
    Ast *getCatchesopt() { return lpg_Catchesopt; };
    void setCatchesopt(Ast *lpg_Catchesopt) { this->lpg_Catchesopt = lpg_Catchesopt; }
    Finally *getFinally() { return lpg_Finally; };
    void setFinally(Finally *lpg_Finally) { this->lpg_Finally = lpg_Finally; }

    TryStatement1(IToken* leftIToken, IToken* rightIToken,
                  AstToken *lpg_try,
                  Block *lpg_Block,
                  Ast *lpg_Catchesopt,
                  Finally *lpg_Finally):Ast(leftIToken, rightIToken)    {
        this->lpg_try = lpg_try;
        ((Ast*) lpg_try)->setParent(this);
        this->lpg_Block = lpg_Block;
        ((Ast*) lpg_Block)->setParent(this);
        this->lpg_Catchesopt = lpg_Catchesopt;
        if (lpg_Catchesopt != nullptr) ((Ast*) lpg_Catchesopt)->setParent(this);
        this->lpg_Finally = lpg_Finally;
        ((Ast*) lpg_Finally)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_try);
        list.push_back((IAst*)lpg_Block);
        list.push_back((IAst*)lpg_Catchesopt);
        list.push_back((IAst*)lpg_Finally);
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
            ((IAst*)lpg_try)->accept(v);
            ((IAst*)lpg_Block)->accept(v);
            if (lpg_Catchesopt != nullptr) ((IAst*)lpg_Catchesopt)->accept(v);
            ((IAst*)lpg_Finally)->accept(v);
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
    Ast *lpg_Type;
    AstToken *lpg_DOT;
    AstToken *lpg_class;

    Ast *getType() { return lpg_Type; };
    void setType(Ast *lpg_Type) { this->lpg_Type = lpg_Type; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    AstToken *getclass() { return lpg_class; };
    void setclass(AstToken *lpg_class) { this->lpg_class = lpg_class; }

    PrimaryNoNewArray0(IToken* leftIToken, IToken* rightIToken,
                       Ast *lpg_Type,
                       AstToken *lpg_DOT,
                       AstToken *lpg_class):Ast(leftIToken, rightIToken)    {
        this->lpg_Type = lpg_Type;
        ((Ast*) lpg_Type)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_class = lpg_class;
        ((Ast*) lpg_class)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Type);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_class);
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
            ((IAst*)lpg_Type)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_class)->accept(v);
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
    AstToken *lpg_void;
    AstToken *lpg_DOT;
    AstToken *lpg_class;

    AstToken *getvoid() { return lpg_void; };
    void setvoid(AstToken *lpg_void) { this->lpg_void = lpg_void; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    AstToken *getclass() { return lpg_class; };
    void setclass(AstToken *lpg_class) { this->lpg_class = lpg_class; }

    PrimaryNoNewArray1(IToken* leftIToken, IToken* rightIToken,
                       AstToken *lpg_void,
                       AstToken *lpg_DOT,
                       AstToken *lpg_class):Ast(leftIToken, rightIToken)    {
        this->lpg_void = lpg_void;
        ((Ast*) lpg_void)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_class = lpg_class;
        ((Ast*) lpg_class)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_void);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_class);
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
            ((IAst*)lpg_void)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_class)->accept(v);
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
    Ast *lpg_ClassName;
    AstToken *lpg_DOT;
    AstToken *lpg_this;

    Ast *getClassName() { return lpg_ClassName; };
    void setClassName(Ast *lpg_ClassName) { this->lpg_ClassName = lpg_ClassName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    AstToken *getthis() { return lpg_this; };
    void setthis(AstToken *lpg_this) { this->lpg_this = lpg_this; }

    PrimaryNoNewArray3(IToken* leftIToken, IToken* rightIToken,
                       Ast *lpg_ClassName,
                       AstToken *lpg_DOT,
                       AstToken *lpg_this):Ast(leftIToken, rightIToken)    {
        this->lpg_ClassName = lpg_ClassName;
        ((Ast*) lpg_ClassName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_this = lpg_this;
        ((Ast*) lpg_this)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ClassName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_this);
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
            ((IAst*)lpg_ClassName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_this)->accept(v);
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
    AstToken *lpg_LPAREN;
    Ast *lpg_Expression;
    AstToken *lpg_RPAREN;

    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    PrimaryNoNewArray4(IToken* leftIToken, IToken* rightIToken,
                       AstToken *lpg_LPAREN,
                       Ast *lpg_Expression,
                       AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    AstToken *lpg_new;
    TypeArguments *lpg_TypeArgumentsopt;
    ClassType *lpg_ClassOrInterfaceType;
    TypeArguments *lpg_TypeArgumentsopt4;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;
    ClassBody *lpg_ClassBodyopt;

    AstToken *getnew() { return lpg_new; };
    void setnew(AstToken *lpg_new) { this->lpg_new = lpg_new; }
    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }
    ClassType *getClassOrInterfaceType() { return lpg_ClassOrInterfaceType; };
    void setClassOrInterfaceType(ClassType *lpg_ClassOrInterfaceType) { this->lpg_ClassOrInterfaceType = lpg_ClassOrInterfaceType; }
    /**
     * The value returned by <b>getTypeArgumentsopt4</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt4() { return lpg_TypeArgumentsopt4; };
    void setTypeArgumentsopt4(TypeArguments *lpg_TypeArgumentsopt4) { this->lpg_TypeArgumentsopt4 = lpg_TypeArgumentsopt4; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    /**
     * The value returned by <b>getClassBodyopt</b> may be <b>nullptr</b>
     */
    ClassBody *getClassBodyopt() { return lpg_ClassBodyopt; };
    void setClassBodyopt(ClassBody *lpg_ClassBodyopt) { this->lpg_ClassBodyopt = lpg_ClassBodyopt; }

    ClassInstanceCreationExpression0(IToken* leftIToken, IToken* rightIToken,
                                     AstToken *lpg_new,
                                     TypeArguments *lpg_TypeArgumentsopt,
                                     ClassType *lpg_ClassOrInterfaceType,
                                     TypeArguments *lpg_TypeArgumentsopt4,
                                     AstToken *lpg_LPAREN,
                                     Ast *lpg_ArgumentListopt,
                                     AstToken *lpg_RPAREN,
                                     ClassBody *lpg_ClassBodyopt):Ast(leftIToken, rightIToken)    {
        this->lpg_new = lpg_new;
        ((Ast*) lpg_new)->setParent(this);
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        this->lpg_ClassOrInterfaceType = lpg_ClassOrInterfaceType;
        ((Ast*) lpg_ClassOrInterfaceType)->setParent(this);
        this->lpg_TypeArgumentsopt4 = lpg_TypeArgumentsopt4;
        if (lpg_TypeArgumentsopt4 != nullptr) ((Ast*) lpg_TypeArgumentsopt4)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_ClassBodyopt = lpg_ClassBodyopt;
        if (lpg_ClassBodyopt != nullptr) ((Ast*) lpg_ClassBodyopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_new);
        list.push_back((IAst*)lpg_TypeArgumentsopt);
        list.push_back((IAst*)lpg_ClassOrInterfaceType);
        list.push_back((IAst*)lpg_TypeArgumentsopt4);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_ClassBodyopt);
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
            ((IAst*)lpg_new)->accept(v);
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
            ((IAst*)lpg_ClassOrInterfaceType)->accept(v);
            if (lpg_TypeArgumentsopt4 != nullptr) ((IAst*)lpg_TypeArgumentsopt4)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            if (lpg_ClassBodyopt != nullptr) ((IAst*)lpg_ClassBodyopt)->accept(v);
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
    Ast *lpg_Primary;
    AstToken *lpg_DOT;
    AstToken *lpg_new;
    TypeArguments *lpg_TypeArgumentsopt;
    identifier *lpg_identifier;
    TypeArguments *lpg_TypeArgumentsopt6;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;
    ClassBody *lpg_ClassBodyopt;

    Ast *getPrimary() { return lpg_Primary; };
    void setPrimary(Ast *lpg_Primary) { this->lpg_Primary = lpg_Primary; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    AstToken *getnew() { return lpg_new; };
    void setnew(AstToken *lpg_new) { this->lpg_new = lpg_new; }
    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    /**
     * The value returned by <b>getTypeArgumentsopt6</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt6() { return lpg_TypeArgumentsopt6; };
    void setTypeArgumentsopt6(TypeArguments *lpg_TypeArgumentsopt6) { this->lpg_TypeArgumentsopt6 = lpg_TypeArgumentsopt6; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    /**
     * The value returned by <b>getClassBodyopt</b> may be <b>nullptr</b>
     */
    ClassBody *getClassBodyopt() { return lpg_ClassBodyopt; };
    void setClassBodyopt(ClassBody *lpg_ClassBodyopt) { this->lpg_ClassBodyopt = lpg_ClassBodyopt; }

    ClassInstanceCreationExpression1(IToken* leftIToken, IToken* rightIToken,
                                     Ast *lpg_Primary,
                                     AstToken *lpg_DOT,
                                     AstToken *lpg_new,
                                     TypeArguments *lpg_TypeArgumentsopt,
                                     identifier *lpg_identifier,
                                     TypeArguments *lpg_TypeArgumentsopt6,
                                     AstToken *lpg_LPAREN,
                                     Ast *lpg_ArgumentListopt,
                                     AstToken *lpg_RPAREN,
                                     ClassBody *lpg_ClassBodyopt):Ast(leftIToken, rightIToken)    {
        this->lpg_Primary = lpg_Primary;
        ((Ast*) lpg_Primary)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_new = lpg_new;
        ((Ast*) lpg_new)->setParent(this);
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_TypeArgumentsopt6 = lpg_TypeArgumentsopt6;
        if (lpg_TypeArgumentsopt6 != nullptr) ((Ast*) lpg_TypeArgumentsopt6)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_ClassBodyopt = lpg_ClassBodyopt;
        if (lpg_ClassBodyopt != nullptr) ((Ast*) lpg_ClassBodyopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Primary);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_new);
        list.push_back((IAst*)lpg_TypeArgumentsopt);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_TypeArgumentsopt6);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_ClassBodyopt);
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
            ((IAst*)lpg_Primary)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_new)->accept(v);
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            if (lpg_TypeArgumentsopt6 != nullptr) ((IAst*)lpg_TypeArgumentsopt6)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            if (lpg_ClassBodyopt != nullptr) ((IAst*)lpg_ClassBodyopt)->accept(v);
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
    AstToken *lpg_new;
    Ast *lpg_PrimitiveType;
    Ast *lpg_DimExprs;
    Ast *lpg_Dimsopt;

    AstToken *getnew() { return lpg_new; };
    void setnew(AstToken *lpg_new) { this->lpg_new = lpg_new; }
    Ast *getPrimitiveType() { return lpg_PrimitiveType; };
    void setPrimitiveType(Ast *lpg_PrimitiveType) { this->lpg_PrimitiveType = lpg_PrimitiveType; }
    Ast *getDimExprs() { return lpg_DimExprs; };
    void setDimExprs(Ast *lpg_DimExprs) { this->lpg_DimExprs = lpg_DimExprs; }
    /**
     * The value returned by <b>getDimsopt</b> may be <b>nullptr</b>
     */
    Ast *getDimsopt() { return lpg_Dimsopt; };
    void setDimsopt(Ast *lpg_Dimsopt) { this->lpg_Dimsopt = lpg_Dimsopt; }

    ArrayCreationExpression0(IToken* leftIToken, IToken* rightIToken,
                             AstToken *lpg_new,
                             Ast *lpg_PrimitiveType,
                             Ast *lpg_DimExprs,
                             Ast *lpg_Dimsopt):Ast(leftIToken, rightIToken)    {
        this->lpg_new = lpg_new;
        ((Ast*) lpg_new)->setParent(this);
        this->lpg_PrimitiveType = lpg_PrimitiveType;
        ((Ast*) lpg_PrimitiveType)->setParent(this);
        this->lpg_DimExprs = lpg_DimExprs;
        ((Ast*) lpg_DimExprs)->setParent(this);
        this->lpg_Dimsopt = lpg_Dimsopt;
        if (lpg_Dimsopt != nullptr) ((Ast*) lpg_Dimsopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_new);
        list.push_back((IAst*)lpg_PrimitiveType);
        list.push_back((IAst*)lpg_DimExprs);
        list.push_back((IAst*)lpg_Dimsopt);
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
            ((IAst*)lpg_new)->accept(v);
            ((IAst*)lpg_PrimitiveType)->accept(v);
            ((IAst*)lpg_DimExprs)->accept(v);
            if (lpg_Dimsopt != nullptr) ((IAst*)lpg_Dimsopt)->accept(v);
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
    AstToken *lpg_new;
    ClassType *lpg_ClassOrInterfaceType;
    Ast *lpg_DimExprs;
    Ast *lpg_Dimsopt;

    AstToken *getnew() { return lpg_new; };
    void setnew(AstToken *lpg_new) { this->lpg_new = lpg_new; }
    ClassType *getClassOrInterfaceType() { return lpg_ClassOrInterfaceType; };
    void setClassOrInterfaceType(ClassType *lpg_ClassOrInterfaceType) { this->lpg_ClassOrInterfaceType = lpg_ClassOrInterfaceType; }
    Ast *getDimExprs() { return lpg_DimExprs; };
    void setDimExprs(Ast *lpg_DimExprs) { this->lpg_DimExprs = lpg_DimExprs; }
    /**
     * The value returned by <b>getDimsopt</b> may be <b>nullptr</b>
     */
    Ast *getDimsopt() { return lpg_Dimsopt; };
    void setDimsopt(Ast *lpg_Dimsopt) { this->lpg_Dimsopt = lpg_Dimsopt; }

    ArrayCreationExpression1(IToken* leftIToken, IToken* rightIToken,
                             AstToken *lpg_new,
                             ClassType *lpg_ClassOrInterfaceType,
                             Ast *lpg_DimExprs,
                             Ast *lpg_Dimsopt):Ast(leftIToken, rightIToken)    {
        this->lpg_new = lpg_new;
        ((Ast*) lpg_new)->setParent(this);
        this->lpg_ClassOrInterfaceType = lpg_ClassOrInterfaceType;
        ((Ast*) lpg_ClassOrInterfaceType)->setParent(this);
        this->lpg_DimExprs = lpg_DimExprs;
        ((Ast*) lpg_DimExprs)->setParent(this);
        this->lpg_Dimsopt = lpg_Dimsopt;
        if (lpg_Dimsopt != nullptr) ((Ast*) lpg_Dimsopt)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_new);
        list.push_back((IAst*)lpg_ClassOrInterfaceType);
        list.push_back((IAst*)lpg_DimExprs);
        list.push_back((IAst*)lpg_Dimsopt);
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
            ((IAst*)lpg_new)->accept(v);
            ((IAst*)lpg_ClassOrInterfaceType)->accept(v);
            ((IAst*)lpg_DimExprs)->accept(v);
            if (lpg_Dimsopt != nullptr) ((IAst*)lpg_Dimsopt)->accept(v);
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
    AstToken *lpg_new;
    Ast *lpg_PrimitiveType;
    Ast *lpg_Dims;
    ArrayInitializer *lpg_ArrayInitializer;

    AstToken *getnew() { return lpg_new; };
    void setnew(AstToken *lpg_new) { this->lpg_new = lpg_new; }
    Ast *getPrimitiveType() { return lpg_PrimitiveType; };
    void setPrimitiveType(Ast *lpg_PrimitiveType) { this->lpg_PrimitiveType = lpg_PrimitiveType; }
    Ast *getDims() { return lpg_Dims; };
    void setDims(Ast *lpg_Dims) { this->lpg_Dims = lpg_Dims; }
    ArrayInitializer *getArrayInitializer() { return lpg_ArrayInitializer; };
    void setArrayInitializer(ArrayInitializer *lpg_ArrayInitializer) { this->lpg_ArrayInitializer = lpg_ArrayInitializer; }

    ArrayCreationExpression2(IToken* leftIToken, IToken* rightIToken,
                             AstToken *lpg_new,
                             Ast *lpg_PrimitiveType,
                             Ast *lpg_Dims,
                             ArrayInitializer *lpg_ArrayInitializer):Ast(leftIToken, rightIToken)    {
        this->lpg_new = lpg_new;
        ((Ast*) lpg_new)->setParent(this);
        this->lpg_PrimitiveType = lpg_PrimitiveType;
        ((Ast*) lpg_PrimitiveType)->setParent(this);
        this->lpg_Dims = lpg_Dims;
        ((Ast*) lpg_Dims)->setParent(this);
        this->lpg_ArrayInitializer = lpg_ArrayInitializer;
        ((Ast*) lpg_ArrayInitializer)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_new);
        list.push_back((IAst*)lpg_PrimitiveType);
        list.push_back((IAst*)lpg_Dims);
        list.push_back((IAst*)lpg_ArrayInitializer);
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
            ((IAst*)lpg_new)->accept(v);
            ((IAst*)lpg_PrimitiveType)->accept(v);
            ((IAst*)lpg_Dims)->accept(v);
            ((IAst*)lpg_ArrayInitializer)->accept(v);
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
    AstToken *lpg_new;
    ClassType *lpg_ClassOrInterfaceType;
    Ast *lpg_Dims;
    ArrayInitializer *lpg_ArrayInitializer;

    AstToken *getnew() { return lpg_new; };
    void setnew(AstToken *lpg_new) { this->lpg_new = lpg_new; }
    ClassType *getClassOrInterfaceType() { return lpg_ClassOrInterfaceType; };
    void setClassOrInterfaceType(ClassType *lpg_ClassOrInterfaceType) { this->lpg_ClassOrInterfaceType = lpg_ClassOrInterfaceType; }
    Ast *getDims() { return lpg_Dims; };
    void setDims(Ast *lpg_Dims) { this->lpg_Dims = lpg_Dims; }
    ArrayInitializer *getArrayInitializer() { return lpg_ArrayInitializer; };
    void setArrayInitializer(ArrayInitializer *lpg_ArrayInitializer) { this->lpg_ArrayInitializer = lpg_ArrayInitializer; }

    ArrayCreationExpression3(IToken* leftIToken, IToken* rightIToken,
                             AstToken *lpg_new,
                             ClassType *lpg_ClassOrInterfaceType,
                             Ast *lpg_Dims,
                             ArrayInitializer *lpg_ArrayInitializer):Ast(leftIToken, rightIToken)    {
        this->lpg_new = lpg_new;
        ((Ast*) lpg_new)->setParent(this);
        this->lpg_ClassOrInterfaceType = lpg_ClassOrInterfaceType;
        ((Ast*) lpg_ClassOrInterfaceType)->setParent(this);
        this->lpg_Dims = lpg_Dims;
        ((Ast*) lpg_Dims)->setParent(this);
        this->lpg_ArrayInitializer = lpg_ArrayInitializer;
        ((Ast*) lpg_ArrayInitializer)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_new);
        list.push_back((IAst*)lpg_ClassOrInterfaceType);
        list.push_back((IAst*)lpg_Dims);
        list.push_back((IAst*)lpg_ArrayInitializer);
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
            ((IAst*)lpg_new)->accept(v);
            ((IAst*)lpg_ClassOrInterfaceType)->accept(v);
            ((IAst*)lpg_Dims)->accept(v);
            ((IAst*)lpg_ArrayInitializer)->accept(v);
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
    AstToken *lpg_LBRACKET;
    AstToken *lpg_RBRACKET;

    AstToken *getLBRACKET() { return lpg_LBRACKET; };
    void setLBRACKET(AstToken *lpg_LBRACKET) { this->lpg_LBRACKET = lpg_LBRACKET; }
    AstToken *getRBRACKET() { return lpg_RBRACKET; };
    void setRBRACKET(AstToken *lpg_RBRACKET) { this->lpg_RBRACKET = lpg_RBRACKET; }

    Dims0(IToken* leftIToken, IToken* rightIToken,
          AstToken *lpg_LBRACKET,
          AstToken *lpg_RBRACKET):Ast(leftIToken, rightIToken)    {
        this->lpg_LBRACKET = lpg_LBRACKET;
        ((Ast*) lpg_LBRACKET)->setParent(this);
        this->lpg_RBRACKET = lpg_RBRACKET;
        ((Ast*) lpg_RBRACKET)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LBRACKET);
        list.push_back((IAst*)lpg_RBRACKET);
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
            ((IAst*)lpg_LBRACKET)->accept(v);
            ((IAst*)lpg_RBRACKET)->accept(v);
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
    Ast *lpg_Dims;
    AstToken *lpg_LBRACKET;
    AstToken *lpg_RBRACKET;

    Ast *getDims() { return lpg_Dims; };
    void setDims(Ast *lpg_Dims) { this->lpg_Dims = lpg_Dims; }
    AstToken *getLBRACKET() { return lpg_LBRACKET; };
    void setLBRACKET(AstToken *lpg_LBRACKET) { this->lpg_LBRACKET = lpg_LBRACKET; }
    AstToken *getRBRACKET() { return lpg_RBRACKET; };
    void setRBRACKET(AstToken *lpg_RBRACKET) { this->lpg_RBRACKET = lpg_RBRACKET; }

    Dims1(IToken* leftIToken, IToken* rightIToken,
          Ast *lpg_Dims,
          AstToken *lpg_LBRACKET,
          AstToken *lpg_RBRACKET):Ast(leftIToken, rightIToken)    {
        this->lpg_Dims = lpg_Dims;
        ((Ast*) lpg_Dims)->setParent(this);
        this->lpg_LBRACKET = lpg_LBRACKET;
        ((Ast*) lpg_LBRACKET)->setParent(this);
        this->lpg_RBRACKET = lpg_RBRACKET;
        ((Ast*) lpg_RBRACKET)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Dims);
        list.push_back((IAst*)lpg_LBRACKET);
        list.push_back((IAst*)lpg_RBRACKET);
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
            ((IAst*)lpg_Dims)->accept(v);
            ((IAst*)lpg_LBRACKET)->accept(v);
            ((IAst*)lpg_RBRACKET)->accept(v);
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
    Ast *lpg_Primary;
    AstToken *lpg_DOT;
    identifier *lpg_identifier;

    Ast *getPrimary() { return lpg_Primary; };
    void setPrimary(Ast *lpg_Primary) { this->lpg_Primary = lpg_Primary; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }

    FieldAccess0(IToken* leftIToken, IToken* rightIToken,
                 Ast *lpg_Primary,
                 AstToken *lpg_DOT,
                 identifier *lpg_identifier):Ast(leftIToken, rightIToken)    {
        this->lpg_Primary = lpg_Primary;
        ((Ast*) lpg_Primary)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Primary);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_identifier);
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
            ((IAst*)lpg_Primary)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
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
    AstToken *lpg_super;
    AstToken *lpg_DOT;
    identifier *lpg_identifier;

    AstToken *getsuper() { return lpg_super; };
    void setsuper(AstToken *lpg_super) { this->lpg_super = lpg_super; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }

    FieldAccess1(IToken* leftIToken, IToken* rightIToken,
                 AstToken *lpg_super,
                 AstToken *lpg_DOT,
                 identifier *lpg_identifier):Ast(leftIToken, rightIToken)    {
        this->lpg_super = lpg_super;
        ((Ast*) lpg_super)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_super);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_identifier);
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
            ((IAst*)lpg_super)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
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
    Ast *lpg_ClassName;
    AstToken *lpg_DOT;
    AstToken *lpg_super;
    AstToken *lpg_DOT4;
    identifier *lpg_identifier;

    Ast *getClassName() { return lpg_ClassName; };
    void setClassName(Ast *lpg_ClassName) { this->lpg_ClassName = lpg_ClassName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    AstToken *getsuper() { return lpg_super; };
    void setsuper(AstToken *lpg_super) { this->lpg_super = lpg_super; }
    AstToken *getDOT4() { return lpg_DOT4; };
    void setDOT4(AstToken *lpg_DOT4) { this->lpg_DOT4 = lpg_DOT4; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }

    FieldAccess2(IToken* leftIToken, IToken* rightIToken,
                 Ast *lpg_ClassName,
                 AstToken *lpg_DOT,
                 AstToken *lpg_super,
                 AstToken *lpg_DOT4,
                 identifier *lpg_identifier):Ast(leftIToken, rightIToken)    {
        this->lpg_ClassName = lpg_ClassName;
        ((Ast*) lpg_ClassName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_super = lpg_super;
        ((Ast*) lpg_super)->setParent(this);
        this->lpg_DOT4 = lpg_DOT4;
        ((Ast*) lpg_DOT4)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ClassName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_super);
        list.push_back((IAst*)lpg_DOT4);
        list.push_back((IAst*)lpg_identifier);
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
            ((IAst*)lpg_ClassName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_super)->accept(v);
            ((IAst*)lpg_DOT4)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
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
    Ast *lpg_MethodName;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;

    Ast *getMethodName() { return lpg_MethodName; };
    void setMethodName(Ast *lpg_MethodName) { this->lpg_MethodName = lpg_MethodName; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    MethodInvocation0(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_MethodName,
                      AstToken *lpg_LPAREN,
                      Ast *lpg_ArgumentListopt,
                      AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_MethodName = lpg_MethodName;
        ((Ast*) lpg_MethodName)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MethodName);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_MethodName)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    Ast *lpg_Primary;
    AstToken *lpg_DOT;
    TypeArguments *lpg_TypeArgumentsopt;
    identifier *lpg_identifier;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;

    Ast *getPrimary() { return lpg_Primary; };
    void setPrimary(Ast *lpg_Primary) { this->lpg_Primary = lpg_Primary; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    MethodInvocation1(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_Primary,
                      AstToken *lpg_DOT,
                      TypeArguments *lpg_TypeArgumentsopt,
                      identifier *lpg_identifier,
                      AstToken *lpg_LPAREN,
                      Ast *lpg_ArgumentListopt,
                      AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_Primary = lpg_Primary;
        ((Ast*) lpg_Primary)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_Primary);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_TypeArgumentsopt);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_Primary)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    AstToken *lpg_super;
    AstToken *lpg_DOT;
    TypeArguments *lpg_TypeArgumentsopt;
    identifier *lpg_identifier;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;

    AstToken *getsuper() { return lpg_super; };
    void setsuper(AstToken *lpg_super) { this->lpg_super = lpg_super; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    MethodInvocation2(IToken* leftIToken, IToken* rightIToken,
                      AstToken *lpg_super,
                      AstToken *lpg_DOT,
                      TypeArguments *lpg_TypeArgumentsopt,
                      identifier *lpg_identifier,
                      AstToken *lpg_LPAREN,
                      Ast *lpg_ArgumentListopt,
                      AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_super = lpg_super;
        ((Ast*) lpg_super)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_super);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_TypeArgumentsopt);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_super)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    Ast *lpg_ClassName;
    AstToken *lpg_DOT;
    AstToken *lpg_super;
    AstToken *lpg_DOT4;
    TypeArguments *lpg_TypeArgumentsopt;
    identifier *lpg_identifier;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;

    Ast *getClassName() { return lpg_ClassName; };
    void setClassName(Ast *lpg_ClassName) { this->lpg_ClassName = lpg_ClassName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    AstToken *getsuper() { return lpg_super; };
    void setsuper(AstToken *lpg_super) { this->lpg_super = lpg_super; }
    AstToken *getDOT4() { return lpg_DOT4; };
    void setDOT4(AstToken *lpg_DOT4) { this->lpg_DOT4 = lpg_DOT4; }
    /**
     * The value returned by <b>getTypeArgumentsopt</b> may be <b>nullptr</b>
     */
    TypeArguments *getTypeArgumentsopt() { return lpg_TypeArgumentsopt; };
    void setTypeArgumentsopt(TypeArguments *lpg_TypeArgumentsopt) { this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    MethodInvocation3(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_ClassName,
                      AstToken *lpg_DOT,
                      AstToken *lpg_super,
                      AstToken *lpg_DOT4,
                      TypeArguments *lpg_TypeArgumentsopt,
                      identifier *lpg_identifier,
                      AstToken *lpg_LPAREN,
                      Ast *lpg_ArgumentListopt,
                      AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_ClassName = lpg_ClassName;
        ((Ast*) lpg_ClassName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_super = lpg_super;
        ((Ast*) lpg_super)->setParent(this);
        this->lpg_DOT4 = lpg_DOT4;
        ((Ast*) lpg_DOT4)->setParent(this);
        this->lpg_TypeArgumentsopt = lpg_TypeArgumentsopt;
        if (lpg_TypeArgumentsopt != nullptr) ((Ast*) lpg_TypeArgumentsopt)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ClassName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_super);
        list.push_back((IAst*)lpg_DOT4);
        list.push_back((IAst*)lpg_TypeArgumentsopt);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_ClassName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_super)->accept(v);
            ((IAst*)lpg_DOT4)->accept(v);
            if (lpg_TypeArgumentsopt != nullptr) ((IAst*)lpg_TypeArgumentsopt)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    Ast *lpg_TypeName;
    AstToken *lpg_DOT;
    TypeArguments *lpg_TypeArguments;
    identifier *lpg_identifier;
    AstToken *lpg_LPAREN;
    Ast *lpg_ArgumentListopt;
    AstToken *lpg_RPAREN;

    Ast *getTypeName() { return lpg_TypeName; };
    void setTypeName(Ast *lpg_TypeName) { this->lpg_TypeName = lpg_TypeName; }
    AstToken *getDOT() { return lpg_DOT; };
    void setDOT(AstToken *lpg_DOT) { this->lpg_DOT = lpg_DOT; }
    TypeArguments *getTypeArguments() { return lpg_TypeArguments; };
    void setTypeArguments(TypeArguments *lpg_TypeArguments) { this->lpg_TypeArguments = lpg_TypeArguments; }
    identifier *getidentifier() { return lpg_identifier; };
    void setidentifier(identifier *lpg_identifier) { this->lpg_identifier = lpg_identifier; }
    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    /**
     * The value returned by <b>getArgumentListopt</b> may be <b>nullptr</b>
     */
    Ast *getArgumentListopt() { return lpg_ArgumentListopt; };
    void setArgumentListopt(Ast *lpg_ArgumentListopt) { this->lpg_ArgumentListopt = lpg_ArgumentListopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }

    MethodInvocation4(IToken* leftIToken, IToken* rightIToken,
                      Ast *lpg_TypeName,
                      AstToken *lpg_DOT,
                      TypeArguments *lpg_TypeArguments,
                      identifier *lpg_identifier,
                      AstToken *lpg_LPAREN,
                      Ast *lpg_ArgumentListopt,
                      AstToken *lpg_RPAREN):Ast(leftIToken, rightIToken)    {
        this->lpg_TypeName = lpg_TypeName;
        ((Ast*) lpg_TypeName)->setParent(this);
        this->lpg_DOT = lpg_DOT;
        ((Ast*) lpg_DOT)->setParent(this);
        this->lpg_TypeArguments = lpg_TypeArguments;
        ((Ast*) lpg_TypeArguments)->setParent(this);
        this->lpg_identifier = lpg_identifier;
        ((Ast*) lpg_identifier)->setParent(this);
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ArgumentListopt = lpg_ArgumentListopt;
        if (lpg_ArgumentListopt != nullptr) ((Ast*) lpg_ArgumentListopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TypeName);
        list.push_back((IAst*)lpg_DOT);
        list.push_back((IAst*)lpg_TypeArguments);
        list.push_back((IAst*)lpg_identifier);
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ArgumentListopt);
        list.push_back((IAst*)lpg_RPAREN);
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
            ((IAst*)lpg_TypeName)->accept(v);
            ((IAst*)lpg_DOT)->accept(v);
            ((IAst*)lpg_TypeArguments)->accept(v);
            ((IAst*)lpg_identifier)->accept(v);
            ((IAst*)lpg_LPAREN)->accept(v);
            if (lpg_ArgumentListopt != nullptr) ((IAst*)lpg_ArgumentListopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
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
    Ast *lpg_ExpressionName;
    AstToken *lpg_LBRACKET;
    Ast *lpg_Expression;
    AstToken *lpg_RBRACKET;

    Ast *getExpressionName() { return lpg_ExpressionName; };
    void setExpressionName(Ast *lpg_ExpressionName) { this->lpg_ExpressionName = lpg_ExpressionName; }
    AstToken *getLBRACKET() { return lpg_LBRACKET; };
    void setLBRACKET(AstToken *lpg_LBRACKET) { this->lpg_LBRACKET = lpg_LBRACKET; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRBRACKET() { return lpg_RBRACKET; };
    void setRBRACKET(AstToken *lpg_RBRACKET) { this->lpg_RBRACKET = lpg_RBRACKET; }

    ArrayAccess0(IToken* leftIToken, IToken* rightIToken,
                 Ast *lpg_ExpressionName,
                 AstToken *lpg_LBRACKET,
                 Ast *lpg_Expression,
                 AstToken *lpg_RBRACKET):Ast(leftIToken, rightIToken)    {
        this->lpg_ExpressionName = lpg_ExpressionName;
        ((Ast*) lpg_ExpressionName)->setParent(this);
        this->lpg_LBRACKET = lpg_LBRACKET;
        ((Ast*) lpg_LBRACKET)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RBRACKET = lpg_RBRACKET;
        ((Ast*) lpg_RBRACKET)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ExpressionName);
        list.push_back((IAst*)lpg_LBRACKET);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RBRACKET);
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
            ((IAst*)lpg_ExpressionName)->accept(v);
            ((IAst*)lpg_LBRACKET)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RBRACKET)->accept(v);
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
    Ast *lpg_PrimaryNoNewArray;
    AstToken *lpg_LBRACKET;
    Ast *lpg_Expression;
    AstToken *lpg_RBRACKET;

    Ast *getPrimaryNoNewArray() { return lpg_PrimaryNoNewArray; };
    void setPrimaryNoNewArray(Ast *lpg_PrimaryNoNewArray) { this->lpg_PrimaryNoNewArray = lpg_PrimaryNoNewArray; }
    AstToken *getLBRACKET() { return lpg_LBRACKET; };
    void setLBRACKET(AstToken *lpg_LBRACKET) { this->lpg_LBRACKET = lpg_LBRACKET; }
    Ast *getExpression() { return lpg_Expression; };
    void setExpression(Ast *lpg_Expression) { this->lpg_Expression = lpg_Expression; }
    AstToken *getRBRACKET() { return lpg_RBRACKET; };
    void setRBRACKET(AstToken *lpg_RBRACKET) { this->lpg_RBRACKET = lpg_RBRACKET; }

    ArrayAccess1(IToken* leftIToken, IToken* rightIToken,
                 Ast *lpg_PrimaryNoNewArray,
                 AstToken *lpg_LBRACKET,
                 Ast *lpg_Expression,
                 AstToken *lpg_RBRACKET):Ast(leftIToken, rightIToken)    {
        this->lpg_PrimaryNoNewArray = lpg_PrimaryNoNewArray;
        ((Ast*) lpg_PrimaryNoNewArray)->setParent(this);
        this->lpg_LBRACKET = lpg_LBRACKET;
        ((Ast*) lpg_LBRACKET)->setParent(this);
        this->lpg_Expression = lpg_Expression;
        ((Ast*) lpg_Expression)->setParent(this);
        this->lpg_RBRACKET = lpg_RBRACKET;
        ((Ast*) lpg_RBRACKET)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_PrimaryNoNewArray);
        list.push_back((IAst*)lpg_LBRACKET);
        list.push_back((IAst*)lpg_Expression);
        list.push_back((IAst*)lpg_RBRACKET);
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
            ((IAst*)lpg_PrimaryNoNewArray)->accept(v);
            ((IAst*)lpg_LBRACKET)->accept(v);
            ((IAst*)lpg_Expression)->accept(v);
            ((IAst*)lpg_RBRACKET)->accept(v);
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
    AstToken *lpg_PLUS;
    Ast *lpg_UnaryExpression;

    AstToken *getPLUS() { return lpg_PLUS; };
    void setPLUS(AstToken *lpg_PLUS) { this->lpg_PLUS = lpg_PLUS; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    UnaryExpression0(IToken* leftIToken, IToken* rightIToken,
                     AstToken *lpg_PLUS,
                     Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_PLUS = lpg_PLUS;
        ((Ast*) lpg_PLUS)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_PLUS);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_PLUS)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    AstToken *lpg_MINUS;
    Ast *lpg_UnaryExpression;

    AstToken *getMINUS() { return lpg_MINUS; };
    void setMINUS(AstToken *lpg_MINUS) { this->lpg_MINUS = lpg_MINUS; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    UnaryExpression1(IToken* leftIToken, IToken* rightIToken,
                     AstToken *lpg_MINUS,
                     Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_MINUS = lpg_MINUS;
        ((Ast*) lpg_MINUS)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MINUS);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_MINUS)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    AstToken *lpg_TWIDDLE;
    Ast *lpg_UnaryExpression;

    AstToken *getTWIDDLE() { return lpg_TWIDDLE; };
    void setTWIDDLE(AstToken *lpg_TWIDDLE) { this->lpg_TWIDDLE = lpg_TWIDDLE; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    UnaryExpressionNotPlusMinus0(IToken* leftIToken, IToken* rightIToken,
                                 AstToken *lpg_TWIDDLE,
                                 Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_TWIDDLE = lpg_TWIDDLE;
        ((Ast*) lpg_TWIDDLE)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_TWIDDLE);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_TWIDDLE)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    AstToken *lpg_NOT;
    Ast *lpg_UnaryExpression;

    AstToken *getNOT() { return lpg_NOT; };
    void setNOT(AstToken *lpg_NOT) { this->lpg_NOT = lpg_NOT; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    UnaryExpressionNotPlusMinus1(IToken* leftIToken, IToken* rightIToken,
                                 AstToken *lpg_NOT,
                                 Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_NOT = lpg_NOT;
        ((Ast*) lpg_NOT)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_NOT);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_NOT)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    AstToken *lpg_LPAREN;
    Ast *lpg_PrimitiveType;
    Ast *lpg_Dimsopt;
    AstToken *lpg_RPAREN;
    Ast *lpg_UnaryExpression;

    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getPrimitiveType() { return lpg_PrimitiveType; };
    void setPrimitiveType(Ast *lpg_PrimitiveType) { this->lpg_PrimitiveType = lpg_PrimitiveType; }
    /**
     * The value returned by <b>getDimsopt</b> may be <b>nullptr</b>
     */
    Ast *getDimsopt() { return lpg_Dimsopt; };
    void setDimsopt(Ast *lpg_Dimsopt) { this->lpg_Dimsopt = lpg_Dimsopt; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    CastExpression0(IToken* leftIToken, IToken* rightIToken,
                    AstToken *lpg_LPAREN,
                    Ast *lpg_PrimitiveType,
                    Ast *lpg_Dimsopt,
                    AstToken *lpg_RPAREN,
                    Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_PrimitiveType = lpg_PrimitiveType;
        ((Ast*) lpg_PrimitiveType)->setParent(this);
        this->lpg_Dimsopt = lpg_Dimsopt;
        if (lpg_Dimsopt != nullptr) ((Ast*) lpg_Dimsopt)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_PrimitiveType);
        list.push_back((IAst*)lpg_Dimsopt);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_PrimitiveType)->accept(v);
            if (lpg_Dimsopt != nullptr) ((IAst*)lpg_Dimsopt)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    AstToken *lpg_LPAREN;
    Ast *lpg_ReferenceType;
    AstToken *lpg_RPAREN;
    Ast *lpg_UnaryExpressionNotPlusMinus;

    AstToken *getLPAREN() { return lpg_LPAREN; };
    void setLPAREN(AstToken *lpg_LPAREN) { this->lpg_LPAREN = lpg_LPAREN; }
    Ast *getReferenceType() { return lpg_ReferenceType; };
    void setReferenceType(Ast *lpg_ReferenceType) { this->lpg_ReferenceType = lpg_ReferenceType; }
    AstToken *getRPAREN() { return lpg_RPAREN; };
    void setRPAREN(AstToken *lpg_RPAREN) { this->lpg_RPAREN = lpg_RPAREN; }
    Ast *getUnaryExpressionNotPlusMinus() { return lpg_UnaryExpressionNotPlusMinus; };
    void setUnaryExpressionNotPlusMinus(Ast *lpg_UnaryExpressionNotPlusMinus) { this->lpg_UnaryExpressionNotPlusMinus = lpg_UnaryExpressionNotPlusMinus; }

    CastExpression1(IToken* leftIToken, IToken* rightIToken,
                    AstToken *lpg_LPAREN,
                    Ast *lpg_ReferenceType,
                    AstToken *lpg_RPAREN,
                    Ast *lpg_UnaryExpressionNotPlusMinus):Ast(leftIToken, rightIToken)    {
        this->lpg_LPAREN = lpg_LPAREN;
        ((Ast*) lpg_LPAREN)->setParent(this);
        this->lpg_ReferenceType = lpg_ReferenceType;
        ((Ast*) lpg_ReferenceType)->setParent(this);
        this->lpg_RPAREN = lpg_RPAREN;
        ((Ast*) lpg_RPAREN)->setParent(this);
        this->lpg_UnaryExpressionNotPlusMinus = lpg_UnaryExpressionNotPlusMinus;
        ((Ast*) lpg_UnaryExpressionNotPlusMinus)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_LPAREN);
        list.push_back((IAst*)lpg_ReferenceType);
        list.push_back((IAst*)lpg_RPAREN);
        list.push_back((IAst*)lpg_UnaryExpressionNotPlusMinus);
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
            ((IAst*)lpg_LPAREN)->accept(v);
            ((IAst*)lpg_ReferenceType)->accept(v);
            ((IAst*)lpg_RPAREN)->accept(v);
            ((IAst*)lpg_UnaryExpressionNotPlusMinus)->accept(v);
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
    Ast *lpg_MultiplicativeExpression;
    AstToken *lpg_MULTIPLY;
    Ast *lpg_UnaryExpression;

    Ast *getMultiplicativeExpression() { return lpg_MultiplicativeExpression; };
    void setMultiplicativeExpression(Ast *lpg_MultiplicativeExpression) { this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression; }
    AstToken *getMULTIPLY() { return lpg_MULTIPLY; };
    void setMULTIPLY(AstToken *lpg_MULTIPLY) { this->lpg_MULTIPLY = lpg_MULTIPLY; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    MultiplicativeExpression0(IToken* leftIToken, IToken* rightIToken,
                              Ast *lpg_MultiplicativeExpression,
                              AstToken *lpg_MULTIPLY,
                              Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression;
        ((Ast*) lpg_MultiplicativeExpression)->setParent(this);
        this->lpg_MULTIPLY = lpg_MULTIPLY;
        ((Ast*) lpg_MULTIPLY)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MultiplicativeExpression);
        list.push_back((IAst*)lpg_MULTIPLY);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_MultiplicativeExpression)->accept(v);
            ((IAst*)lpg_MULTIPLY)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    Ast *lpg_MultiplicativeExpression;
    AstToken *lpg_DIVIDE;
    Ast *lpg_UnaryExpression;

    Ast *getMultiplicativeExpression() { return lpg_MultiplicativeExpression; };
    void setMultiplicativeExpression(Ast *lpg_MultiplicativeExpression) { this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression; }
    AstToken *getDIVIDE() { return lpg_DIVIDE; };
    void setDIVIDE(AstToken *lpg_DIVIDE) { this->lpg_DIVIDE = lpg_DIVIDE; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    MultiplicativeExpression1(IToken* leftIToken, IToken* rightIToken,
                              Ast *lpg_MultiplicativeExpression,
                              AstToken *lpg_DIVIDE,
                              Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression;
        ((Ast*) lpg_MultiplicativeExpression)->setParent(this);
        this->lpg_DIVIDE = lpg_DIVIDE;
        ((Ast*) lpg_DIVIDE)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MultiplicativeExpression);
        list.push_back((IAst*)lpg_DIVIDE);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_MultiplicativeExpression)->accept(v);
            ((IAst*)lpg_DIVIDE)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    Ast *lpg_MultiplicativeExpression;
    AstToken *lpg_REMAINDER;
    Ast *lpg_UnaryExpression;

    Ast *getMultiplicativeExpression() { return lpg_MultiplicativeExpression; };
    void setMultiplicativeExpression(Ast *lpg_MultiplicativeExpression) { this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression; }
    AstToken *getREMAINDER() { return lpg_REMAINDER; };
    void setREMAINDER(AstToken *lpg_REMAINDER) { this->lpg_REMAINDER = lpg_REMAINDER; }
    Ast *getUnaryExpression() { return lpg_UnaryExpression; };
    void setUnaryExpression(Ast *lpg_UnaryExpression) { this->lpg_UnaryExpression = lpg_UnaryExpression; }

    MultiplicativeExpression2(IToken* leftIToken, IToken* rightIToken,
                              Ast *lpg_MultiplicativeExpression,
                              AstToken *lpg_REMAINDER,
                              Ast *lpg_UnaryExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression;
        ((Ast*) lpg_MultiplicativeExpression)->setParent(this);
        this->lpg_REMAINDER = lpg_REMAINDER;
        ((Ast*) lpg_REMAINDER)->setParent(this);
        this->lpg_UnaryExpression = lpg_UnaryExpression;
        ((Ast*) lpg_UnaryExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_MultiplicativeExpression);
        list.push_back((IAst*)lpg_REMAINDER);
        list.push_back((IAst*)lpg_UnaryExpression);
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
            ((IAst*)lpg_MultiplicativeExpression)->accept(v);
            ((IAst*)lpg_REMAINDER)->accept(v);
            ((IAst*)lpg_UnaryExpression)->accept(v);
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
    Ast *lpg_AdditiveExpression;
    AstToken *lpg_PLUS;
    Ast *lpg_MultiplicativeExpression;

    Ast *getAdditiveExpression() { return lpg_AdditiveExpression; };
    void setAdditiveExpression(Ast *lpg_AdditiveExpression) { this->lpg_AdditiveExpression = lpg_AdditiveExpression; }
    AstToken *getPLUS() { return lpg_PLUS; };
    void setPLUS(AstToken *lpg_PLUS) { this->lpg_PLUS = lpg_PLUS; }
    Ast *getMultiplicativeExpression() { return lpg_MultiplicativeExpression; };
    void setMultiplicativeExpression(Ast *lpg_MultiplicativeExpression) { this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression; }

    AdditiveExpression0(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_AdditiveExpression,
                        AstToken *lpg_PLUS,
                        Ast *lpg_MultiplicativeExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_AdditiveExpression = lpg_AdditiveExpression;
        ((Ast*) lpg_AdditiveExpression)->setParent(this);
        this->lpg_PLUS = lpg_PLUS;
        ((Ast*) lpg_PLUS)->setParent(this);
        this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression;
        ((Ast*) lpg_MultiplicativeExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AdditiveExpression);
        list.push_back((IAst*)lpg_PLUS);
        list.push_back((IAst*)lpg_MultiplicativeExpression);
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
            ((IAst*)lpg_AdditiveExpression)->accept(v);
            ((IAst*)lpg_PLUS)->accept(v);
            ((IAst*)lpg_MultiplicativeExpression)->accept(v);
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
    Ast *lpg_AdditiveExpression;
    AstToken *lpg_MINUS;
    Ast *lpg_MultiplicativeExpression;

    Ast *getAdditiveExpression() { return lpg_AdditiveExpression; };
    void setAdditiveExpression(Ast *lpg_AdditiveExpression) { this->lpg_AdditiveExpression = lpg_AdditiveExpression; }
    AstToken *getMINUS() { return lpg_MINUS; };
    void setMINUS(AstToken *lpg_MINUS) { this->lpg_MINUS = lpg_MINUS; }
    Ast *getMultiplicativeExpression() { return lpg_MultiplicativeExpression; };
    void setMultiplicativeExpression(Ast *lpg_MultiplicativeExpression) { this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression; }

    AdditiveExpression1(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_AdditiveExpression,
                        AstToken *lpg_MINUS,
                        Ast *lpg_MultiplicativeExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_AdditiveExpression = lpg_AdditiveExpression;
        ((Ast*) lpg_AdditiveExpression)->setParent(this);
        this->lpg_MINUS = lpg_MINUS;
        ((Ast*) lpg_MINUS)->setParent(this);
        this->lpg_MultiplicativeExpression = lpg_MultiplicativeExpression;
        ((Ast*) lpg_MultiplicativeExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_AdditiveExpression);
        list.push_back((IAst*)lpg_MINUS);
        list.push_back((IAst*)lpg_MultiplicativeExpression);
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
            ((IAst*)lpg_AdditiveExpression)->accept(v);
            ((IAst*)lpg_MINUS)->accept(v);
            ((IAst*)lpg_MultiplicativeExpression)->accept(v);
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
    Ast *lpg_ShiftExpression;
    AstToken *lpg_LEFT_SHIFT;
    Ast *lpg_AdditiveExpression;

    Ast *getShiftExpression() { return lpg_ShiftExpression; };
    void setShiftExpression(Ast *lpg_ShiftExpression) { this->lpg_ShiftExpression = lpg_ShiftExpression; }
    AstToken *getLEFT_SHIFT() { return lpg_LEFT_SHIFT; };
    void setLEFT_SHIFT(AstToken *lpg_LEFT_SHIFT) { this->lpg_LEFT_SHIFT = lpg_LEFT_SHIFT; }
    Ast *getAdditiveExpression() { return lpg_AdditiveExpression; };
    void setAdditiveExpression(Ast *lpg_AdditiveExpression) { this->lpg_AdditiveExpression = lpg_AdditiveExpression; }

    ShiftExpression0(IToken* leftIToken, IToken* rightIToken,
                     Ast *lpg_ShiftExpression,
                     AstToken *lpg_LEFT_SHIFT,
                     Ast *lpg_AdditiveExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_ShiftExpression = lpg_ShiftExpression;
        ((Ast*) lpg_ShiftExpression)->setParent(this);
        this->lpg_LEFT_SHIFT = lpg_LEFT_SHIFT;
        ((Ast*) lpg_LEFT_SHIFT)->setParent(this);
        this->lpg_AdditiveExpression = lpg_AdditiveExpression;
        ((Ast*) lpg_AdditiveExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ShiftExpression);
        list.push_back((IAst*)lpg_LEFT_SHIFT);
        list.push_back((IAst*)lpg_AdditiveExpression);
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
            ((IAst*)lpg_ShiftExpression)->accept(v);
            ((IAst*)lpg_LEFT_SHIFT)->accept(v);
            ((IAst*)lpg_AdditiveExpression)->accept(v);
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
    Ast *lpg_ShiftExpression;
    AstToken *lpg_GREATER;
    AstToken *lpg_GREATER3;
    Ast *lpg_AdditiveExpression;

    Ast *getShiftExpression() { return lpg_ShiftExpression; };
    void setShiftExpression(Ast *lpg_ShiftExpression) { this->lpg_ShiftExpression = lpg_ShiftExpression; }
    AstToken *getGREATER() { return lpg_GREATER; };
    void setGREATER(AstToken *lpg_GREATER) { this->lpg_GREATER = lpg_GREATER; }
    AstToken *getGREATER3() { return lpg_GREATER3; };
    void setGREATER3(AstToken *lpg_GREATER3) { this->lpg_GREATER3 = lpg_GREATER3; }
    Ast *getAdditiveExpression() { return lpg_AdditiveExpression; };
    void setAdditiveExpression(Ast *lpg_AdditiveExpression) { this->lpg_AdditiveExpression = lpg_AdditiveExpression; }

    ShiftExpression1(IToken* leftIToken, IToken* rightIToken,
                     Ast *lpg_ShiftExpression,
                     AstToken *lpg_GREATER,
                     AstToken *lpg_GREATER3,
                     Ast *lpg_AdditiveExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_ShiftExpression = lpg_ShiftExpression;
        ((Ast*) lpg_ShiftExpression)->setParent(this);
        this->lpg_GREATER = lpg_GREATER;
        ((Ast*) lpg_GREATER)->setParent(this);
        this->lpg_GREATER3 = lpg_GREATER3;
        ((Ast*) lpg_GREATER3)->setParent(this);
        this->lpg_AdditiveExpression = lpg_AdditiveExpression;
        ((Ast*) lpg_AdditiveExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ShiftExpression);
        list.push_back((IAst*)lpg_GREATER);
        list.push_back((IAst*)lpg_GREATER3);
        list.push_back((IAst*)lpg_AdditiveExpression);
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
            ((IAst*)lpg_ShiftExpression)->accept(v);
            ((IAst*)lpg_GREATER)->accept(v);
            ((IAst*)lpg_GREATER3)->accept(v);
            ((IAst*)lpg_AdditiveExpression)->accept(v);
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
    Ast *lpg_ShiftExpression;
    AstToken *lpg_GREATER;
    AstToken *lpg_GREATER3;
    AstToken *lpg_GREATER4;
    Ast *lpg_AdditiveExpression;

    Ast *getShiftExpression() { return lpg_ShiftExpression; };
    void setShiftExpression(Ast *lpg_ShiftExpression) { this->lpg_ShiftExpression = lpg_ShiftExpression; }
    AstToken *getGREATER() { return lpg_GREATER; };
    void setGREATER(AstToken *lpg_GREATER) { this->lpg_GREATER = lpg_GREATER; }
    AstToken *getGREATER3() { return lpg_GREATER3; };
    void setGREATER3(AstToken *lpg_GREATER3) { this->lpg_GREATER3 = lpg_GREATER3; }
    AstToken *getGREATER4() { return lpg_GREATER4; };
    void setGREATER4(AstToken *lpg_GREATER4) { this->lpg_GREATER4 = lpg_GREATER4; }
    Ast *getAdditiveExpression() { return lpg_AdditiveExpression; };
    void setAdditiveExpression(Ast *lpg_AdditiveExpression) { this->lpg_AdditiveExpression = lpg_AdditiveExpression; }

    ShiftExpression2(IToken* leftIToken, IToken* rightIToken,
                     Ast *lpg_ShiftExpression,
                     AstToken *lpg_GREATER,
                     AstToken *lpg_GREATER3,
                     AstToken *lpg_GREATER4,
                     Ast *lpg_AdditiveExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_ShiftExpression = lpg_ShiftExpression;
        ((Ast*) lpg_ShiftExpression)->setParent(this);
        this->lpg_GREATER = lpg_GREATER;
        ((Ast*) lpg_GREATER)->setParent(this);
        this->lpg_GREATER3 = lpg_GREATER3;
        ((Ast*) lpg_GREATER3)->setParent(this);
        this->lpg_GREATER4 = lpg_GREATER4;
        ((Ast*) lpg_GREATER4)->setParent(this);
        this->lpg_AdditiveExpression = lpg_AdditiveExpression;
        ((Ast*) lpg_AdditiveExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_ShiftExpression);
        list.push_back((IAst*)lpg_GREATER);
        list.push_back((IAst*)lpg_GREATER3);
        list.push_back((IAst*)lpg_GREATER4);
        list.push_back((IAst*)lpg_AdditiveExpression);
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
            ((IAst*)lpg_ShiftExpression)->accept(v);
            ((IAst*)lpg_GREATER)->accept(v);
            ((IAst*)lpg_GREATER3)->accept(v);
            ((IAst*)lpg_GREATER4)->accept(v);
            ((IAst*)lpg_AdditiveExpression)->accept(v);
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
    Ast *lpg_RelationalExpression;
    AstToken *lpg_LESS;
    Ast *lpg_ShiftExpression;

    Ast *getRelationalExpression() { return lpg_RelationalExpression; };
    void setRelationalExpression(Ast *lpg_RelationalExpression) { this->lpg_RelationalExpression = lpg_RelationalExpression; }
    AstToken *getLESS() { return lpg_LESS; };
    void setLESS(AstToken *lpg_LESS) { this->lpg_LESS = lpg_LESS; }
    Ast *getShiftExpression() { return lpg_ShiftExpression; };
    void setShiftExpression(Ast *lpg_ShiftExpression) { this->lpg_ShiftExpression = lpg_ShiftExpression; }

    RelationalExpression0(IToken* leftIToken, IToken* rightIToken,
                          Ast *lpg_RelationalExpression,
                          AstToken *lpg_LESS,
                          Ast *lpg_ShiftExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_RelationalExpression = lpg_RelationalExpression;
        ((Ast*) lpg_RelationalExpression)->setParent(this);
        this->lpg_LESS = lpg_LESS;
        ((Ast*) lpg_LESS)->setParent(this);
        this->lpg_ShiftExpression = lpg_ShiftExpression;
        ((Ast*) lpg_ShiftExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_RelationalExpression);
        list.push_back((IAst*)lpg_LESS);
        list.push_back((IAst*)lpg_ShiftExpression);
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
            ((IAst*)lpg_RelationalExpression)->accept(v);
            ((IAst*)lpg_LESS)->accept(v);
            ((IAst*)lpg_ShiftExpression)->accept(v);
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
    Ast *lpg_RelationalExpression;
    AstToken *lpg_GREATER;
    Ast *lpg_ShiftExpression;

    Ast *getRelationalExpression() { return lpg_RelationalExpression; };
    void setRelationalExpression(Ast *lpg_RelationalExpression) { this->lpg_RelationalExpression = lpg_RelationalExpression; }
    AstToken *getGREATER() { return lpg_GREATER; };
    void setGREATER(AstToken *lpg_GREATER) { this->lpg_GREATER = lpg_GREATER; }
    Ast *getShiftExpression() { return lpg_ShiftExpression; };
    void setShiftExpression(Ast *lpg_ShiftExpression) { this->lpg_ShiftExpression = lpg_ShiftExpression; }

    RelationalExpression1(IToken* leftIToken, IToken* rightIToken,
                          Ast *lpg_RelationalExpression,
                          AstToken *lpg_GREATER,
                          Ast *lpg_ShiftExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_RelationalExpression = lpg_RelationalExpression;
        ((Ast*) lpg_RelationalExpression)->setParent(this);
        this->lpg_GREATER = lpg_GREATER;
        ((Ast*) lpg_GREATER)->setParent(this);
        this->lpg_ShiftExpression = lpg_ShiftExpression;
        ((Ast*) lpg_ShiftExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_RelationalExpression);
        list.push_back((IAst*)lpg_GREATER);
        list.push_back((IAst*)lpg_ShiftExpression);
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
            ((IAst*)lpg_RelationalExpression)->accept(v);
            ((IAst*)lpg_GREATER)->accept(v);
            ((IAst*)lpg_ShiftExpression)->accept(v);
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
    Ast *lpg_RelationalExpression;
    AstToken *lpg_LESS_EQUAL;
    Ast *lpg_ShiftExpression;

    Ast *getRelationalExpression() { return lpg_RelationalExpression; };
    void setRelationalExpression(Ast *lpg_RelationalExpression) { this->lpg_RelationalExpression = lpg_RelationalExpression; }
    AstToken *getLESS_EQUAL() { return lpg_LESS_EQUAL; };
    void setLESS_EQUAL(AstToken *lpg_LESS_EQUAL) { this->lpg_LESS_EQUAL = lpg_LESS_EQUAL; }
    Ast *getShiftExpression() { return lpg_ShiftExpression; };
    void setShiftExpression(Ast *lpg_ShiftExpression) { this->lpg_ShiftExpression = lpg_ShiftExpression; }

    RelationalExpression2(IToken* leftIToken, IToken* rightIToken,
                          Ast *lpg_RelationalExpression,
                          AstToken *lpg_LESS_EQUAL,
                          Ast *lpg_ShiftExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_RelationalExpression = lpg_RelationalExpression;
        ((Ast*) lpg_RelationalExpression)->setParent(this);
        this->lpg_LESS_EQUAL = lpg_LESS_EQUAL;
        ((Ast*) lpg_LESS_EQUAL)->setParent(this);
        this->lpg_ShiftExpression = lpg_ShiftExpression;
        ((Ast*) lpg_ShiftExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_RelationalExpression);
        list.push_back((IAst*)lpg_LESS_EQUAL);
        list.push_back((IAst*)lpg_ShiftExpression);
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
            ((IAst*)lpg_RelationalExpression)->accept(v);
            ((IAst*)lpg_LESS_EQUAL)->accept(v);
            ((IAst*)lpg_ShiftExpression)->accept(v);
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
    Ast *lpg_RelationalExpression;
    AstToken *lpg_GREATER;
    AstToken *lpg_EQUAL;
    Ast *lpg_ShiftExpression;

    Ast *getRelationalExpression() { return lpg_RelationalExpression; };
    void setRelationalExpression(Ast *lpg_RelationalExpression) { this->lpg_RelationalExpression = lpg_RelationalExpression; }
    AstToken *getGREATER() { return lpg_GREATER; };
    void setGREATER(AstToken *lpg_GREATER) { this->lpg_GREATER = lpg_GREATER; }
    AstToken *getEQUAL() { return lpg_EQUAL; };
    void setEQUAL(AstToken *lpg_EQUAL) { this->lpg_EQUAL = lpg_EQUAL; }
    Ast *getShiftExpression() { return lpg_ShiftExpression; };
    void setShiftExpression(Ast *lpg_ShiftExpression) { this->lpg_ShiftExpression = lpg_ShiftExpression; }

    RelationalExpression3(IToken* leftIToken, IToken* rightIToken,
                          Ast *lpg_RelationalExpression,
                          AstToken *lpg_GREATER,
                          AstToken *lpg_EQUAL,
                          Ast *lpg_ShiftExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_RelationalExpression = lpg_RelationalExpression;
        ((Ast*) lpg_RelationalExpression)->setParent(this);
        this->lpg_GREATER = lpg_GREATER;
        ((Ast*) lpg_GREATER)->setParent(this);
        this->lpg_EQUAL = lpg_EQUAL;
        ((Ast*) lpg_EQUAL)->setParent(this);
        this->lpg_ShiftExpression = lpg_ShiftExpression;
        ((Ast*) lpg_ShiftExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_RelationalExpression);
        list.push_back((IAst*)lpg_GREATER);
        list.push_back((IAst*)lpg_EQUAL);
        list.push_back((IAst*)lpg_ShiftExpression);
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
            ((IAst*)lpg_RelationalExpression)->accept(v);
            ((IAst*)lpg_GREATER)->accept(v);
            ((IAst*)lpg_EQUAL)->accept(v);
            ((IAst*)lpg_ShiftExpression)->accept(v);
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
    Ast *lpg_RelationalExpression;
    AstToken *lpg_instanceof;
    Ast *lpg_ReferenceType;

    Ast *getRelationalExpression() { return lpg_RelationalExpression; };
    void setRelationalExpression(Ast *lpg_RelationalExpression) { this->lpg_RelationalExpression = lpg_RelationalExpression; }
    AstToken *getinstanceof() { return lpg_instanceof; };
    void setinstanceof(AstToken *lpg_instanceof) { this->lpg_instanceof = lpg_instanceof; }
    Ast *getReferenceType() { return lpg_ReferenceType; };
    void setReferenceType(Ast *lpg_ReferenceType) { this->lpg_ReferenceType = lpg_ReferenceType; }

    RelationalExpression4(IToken* leftIToken, IToken* rightIToken,
                          Ast *lpg_RelationalExpression,
                          AstToken *lpg_instanceof,
                          Ast *lpg_ReferenceType):Ast(leftIToken, rightIToken)    {
        this->lpg_RelationalExpression = lpg_RelationalExpression;
        ((Ast*) lpg_RelationalExpression)->setParent(this);
        this->lpg_instanceof = lpg_instanceof;
        ((Ast*) lpg_instanceof)->setParent(this);
        this->lpg_ReferenceType = lpg_ReferenceType;
        ((Ast*) lpg_ReferenceType)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_RelationalExpression);
        list.push_back((IAst*)lpg_instanceof);
        list.push_back((IAst*)lpg_ReferenceType);
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
            ((IAst*)lpg_RelationalExpression)->accept(v);
            ((IAst*)lpg_instanceof)->accept(v);
            ((IAst*)lpg_ReferenceType)->accept(v);
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
    Ast *lpg_EqualityExpression;
    AstToken *lpg_EQUAL_EQUAL;
    Ast *lpg_RelationalExpression;

    Ast *getEqualityExpression() { return lpg_EqualityExpression; };
    void setEqualityExpression(Ast *lpg_EqualityExpression) { this->lpg_EqualityExpression = lpg_EqualityExpression; }
    AstToken *getEQUAL_EQUAL() { return lpg_EQUAL_EQUAL; };
    void setEQUAL_EQUAL(AstToken *lpg_EQUAL_EQUAL) { this->lpg_EQUAL_EQUAL = lpg_EQUAL_EQUAL; }
    Ast *getRelationalExpression() { return lpg_RelationalExpression; };
    void setRelationalExpression(Ast *lpg_RelationalExpression) { this->lpg_RelationalExpression = lpg_RelationalExpression; }

    EqualityExpression0(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_EqualityExpression,
                        AstToken *lpg_EQUAL_EQUAL,
                        Ast *lpg_RelationalExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_EqualityExpression = lpg_EqualityExpression;
        ((Ast*) lpg_EqualityExpression)->setParent(this);
        this->lpg_EQUAL_EQUAL = lpg_EQUAL_EQUAL;
        ((Ast*) lpg_EQUAL_EQUAL)->setParent(this);
        this->lpg_RelationalExpression = lpg_RelationalExpression;
        ((Ast*) lpg_RelationalExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_EqualityExpression);
        list.push_back((IAst*)lpg_EQUAL_EQUAL);
        list.push_back((IAst*)lpg_RelationalExpression);
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
            ((IAst*)lpg_EqualityExpression)->accept(v);
            ((IAst*)lpg_EQUAL_EQUAL)->accept(v);
            ((IAst*)lpg_RelationalExpression)->accept(v);
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
    Ast *lpg_EqualityExpression;
    AstToken *lpg_NOT_EQUAL;
    Ast *lpg_RelationalExpression;

    Ast *getEqualityExpression() { return lpg_EqualityExpression; };
    void setEqualityExpression(Ast *lpg_EqualityExpression) { this->lpg_EqualityExpression = lpg_EqualityExpression; }
    AstToken *getNOT_EQUAL() { return lpg_NOT_EQUAL; };
    void setNOT_EQUAL(AstToken *lpg_NOT_EQUAL) { this->lpg_NOT_EQUAL = lpg_NOT_EQUAL; }
    Ast *getRelationalExpression() { return lpg_RelationalExpression; };
    void setRelationalExpression(Ast *lpg_RelationalExpression) { this->lpg_RelationalExpression = lpg_RelationalExpression; }

    EqualityExpression1(IToken* leftIToken, IToken* rightIToken,
                        Ast *lpg_EqualityExpression,
                        AstToken *lpg_NOT_EQUAL,
                        Ast *lpg_RelationalExpression):Ast(leftIToken, rightIToken)    {
        this->lpg_EqualityExpression = lpg_EqualityExpression;
        ((Ast*) lpg_EqualityExpression)->setParent(this);
        this->lpg_NOT_EQUAL = lpg_NOT_EQUAL;
        ((Ast*) lpg_NOT_EQUAL)->setParent(this);
        this->lpg_RelationalExpression = lpg_RelationalExpression;
        ((Ast*) lpg_RelationalExpression)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_EqualityExpression);
        list.push_back((IAst*)lpg_NOT_EQUAL);
        list.push_back((IAst*)lpg_RelationalExpression);
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
            ((IAst*)lpg_EqualityExpression)->accept(v);
            ((IAst*)lpg_NOT_EQUAL)->accept(v);
            ((IAst*)lpg_RelationalExpression)->accept(v);
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
    AstToken *lpg_GREATER;
    AstToken *lpg_GREATER2;
    AstToken *lpg_EQUAL;

    AstToken *getGREATER() { return lpg_GREATER; };
    void setGREATER(AstToken *lpg_GREATER) { this->lpg_GREATER = lpg_GREATER; }
    AstToken *getGREATER2() { return lpg_GREATER2; };
    void setGREATER2(AstToken *lpg_GREATER2) { this->lpg_GREATER2 = lpg_GREATER2; }
    AstToken *getEQUAL() { return lpg_EQUAL; };
    void setEQUAL(AstToken *lpg_EQUAL) { this->lpg_EQUAL = lpg_EQUAL; }

    AssignmentOperator7(IToken* leftIToken, IToken* rightIToken,
                        AstToken *lpg_GREATER,
                        AstToken *lpg_GREATER2,
                        AstToken *lpg_EQUAL):Ast(leftIToken, rightIToken)    {
        this->lpg_GREATER = lpg_GREATER;
        ((Ast*) lpg_GREATER)->setParent(this);
        this->lpg_GREATER2 = lpg_GREATER2;
        ((Ast*) lpg_GREATER2)->setParent(this);
        this->lpg_EQUAL = lpg_EQUAL;
        ((Ast*) lpg_EQUAL)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_GREATER);
        list.push_back((IAst*)lpg_GREATER2);
        list.push_back((IAst*)lpg_EQUAL);
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
            ((IAst*)lpg_GREATER)->accept(v);
            ((IAst*)lpg_GREATER2)->accept(v);
            ((IAst*)lpg_EQUAL)->accept(v);
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
    AstToken *lpg_GREATER;
    AstToken *lpg_GREATER2;
    AstToken *lpg_GREATER3;
    AstToken *lpg_EQUAL;

    AstToken *getGREATER() { return lpg_GREATER; };
    void setGREATER(AstToken *lpg_GREATER) { this->lpg_GREATER = lpg_GREATER; }
    AstToken *getGREATER2() { return lpg_GREATER2; };
    void setGREATER2(AstToken *lpg_GREATER2) { this->lpg_GREATER2 = lpg_GREATER2; }
    AstToken *getGREATER3() { return lpg_GREATER3; };
    void setGREATER3(AstToken *lpg_GREATER3) { this->lpg_GREATER3 = lpg_GREATER3; }
    AstToken *getEQUAL() { return lpg_EQUAL; };
    void setEQUAL(AstToken *lpg_EQUAL) { this->lpg_EQUAL = lpg_EQUAL; }

    AssignmentOperator8(IToken* leftIToken, IToken* rightIToken,
                        AstToken *lpg_GREATER,
                        AstToken *lpg_GREATER2,
                        AstToken *lpg_GREATER3,
                        AstToken *lpg_EQUAL):Ast(leftIToken, rightIToken)    {
        this->lpg_GREATER = lpg_GREATER;
        ((Ast*) lpg_GREATER)->setParent(this);
        this->lpg_GREATER2 = lpg_GREATER2;
        ((Ast*) lpg_GREATER2)->setParent(this);
        this->lpg_GREATER3 = lpg_GREATER3;
        ((Ast*) lpg_GREATER3)->setParent(this);
        this->lpg_EQUAL = lpg_EQUAL;
        ((Ast*) lpg_EQUAL)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        list.push_back((IAst*)lpg_GREATER);
        list.push_back((IAst*)lpg_GREATER2);
        list.push_back((IAst*)lpg_GREATER3);
        list.push_back((IAst*)lpg_EQUAL);
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
            ((IAst*)lpg_GREATER)->accept(v);
            ((IAst*)lpg_GREATER2)->accept(v);
            ((IAst*)lpg_GREATER3)->accept(v);
            ((IAst*)lpg_EQUAL)->accept(v);
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


 virtual   bool visit(Ast *n)
    {
        if (dynamic_cast<AstToken*>(n) ) return visit((AstToken*) n);
        if (dynamic_cast<identifier*>(n) ) return visit((identifier*) n);
        if (dynamic_cast<PrimitiveType*>(n) ) return visit((PrimitiveType*) n);
        if (dynamic_cast<ClassType*>(n) ) return visit((ClassType*) n);
        if (dynamic_cast<InterfaceType*>(n) ) return visit((InterfaceType*) n);
        if (dynamic_cast<TypeName*>(n) ) return visit((TypeName*) n);
        if (dynamic_cast<ArrayType*>(n) ) return visit((ArrayType*) n);
        if (dynamic_cast<TypeParameter*>(n) ) return visit((TypeParameter*) n);
        if (dynamic_cast<TypeBound*>(n) ) return visit((TypeBound*) n);
        if (dynamic_cast<AdditionalBoundList*>(n) ) return visit((AdditionalBoundList*) n);
        if (dynamic_cast<AdditionalBound*>(n) ) return visit((AdditionalBound*) n);
        if (dynamic_cast<TypeArguments*>(n) ) return visit((TypeArguments*) n);
        if (dynamic_cast<ActualTypeArgumentList*>(n) ) return visit((ActualTypeArgumentList*) n);
        if (dynamic_cast<Wildcard*>(n) ) return visit((Wildcard*) n);
        if (dynamic_cast<PackageName*>(n) ) return visit((PackageName*) n);
        if (dynamic_cast<ExpressionName*>(n) ) return visit((ExpressionName*) n);
        if (dynamic_cast<MethodName*>(n) ) return visit((MethodName*) n);
        if (dynamic_cast<PackageOrTypeName*>(n) ) return visit((PackageOrTypeName*) n);
        if (dynamic_cast<AmbiguousName*>(n) ) return visit((AmbiguousName*) n);
        if (dynamic_cast<CompilationUnit*>(n) ) return visit((CompilationUnit*) n);
        if (dynamic_cast<ImportDeclarations*>(n) ) return visit((ImportDeclarations*) n);
        if (dynamic_cast<TypeDeclarations*>(n) ) return visit((TypeDeclarations*) n);
        if (dynamic_cast<PackageDeclaration*>(n) ) return visit((PackageDeclaration*) n);
        if (dynamic_cast<SingleTypeImportDeclaration*>(n) ) return visit((SingleTypeImportDeclaration*) n);
        if (dynamic_cast<TypeImportOnDemandDeclaration*>(n) ) return visit((TypeImportOnDemandDeclaration*) n);
        if (dynamic_cast<SingleStaticImportDeclaration*>(n) ) return visit((SingleStaticImportDeclaration*) n);
        if (dynamic_cast<StaticImportOnDemandDeclaration*>(n) ) return visit((StaticImportOnDemandDeclaration*) n);
        if (dynamic_cast<TypeDeclaration*>(n) ) return visit((TypeDeclaration*) n);
        if (dynamic_cast<NormalClassDeclaration*>(n) ) return visit((NormalClassDeclaration*) n);
        if (dynamic_cast<ClassModifiers*>(n) ) return visit((ClassModifiers*) n);
        if (dynamic_cast<TypeParameters*>(n) ) return visit((TypeParameters*) n);
        if (dynamic_cast<TypeParameterList*>(n) ) return visit((TypeParameterList*) n);
        if (dynamic_cast<Super*>(n) ) return visit((Super*) n);
        if (dynamic_cast<Interfaces*>(n) ) return visit((Interfaces*) n);
        if (dynamic_cast<InterfaceTypeList*>(n) ) return visit((InterfaceTypeList*) n);
        if (dynamic_cast<ClassBody*>(n) ) return visit((ClassBody*) n);
        if (dynamic_cast<ClassBodyDeclarations*>(n) ) return visit((ClassBodyDeclarations*) n);
        if (dynamic_cast<ClassMemberDeclaration*>(n) ) return visit((ClassMemberDeclaration*) n);
        if (dynamic_cast<FieldDeclaration*>(n) ) return visit((FieldDeclaration*) n);
        if (dynamic_cast<VariableDeclarators*>(n) ) return visit((VariableDeclarators*) n);
        if (dynamic_cast<VariableDeclarator*>(n) ) return visit((VariableDeclarator*) n);
        if (dynamic_cast<VariableDeclaratorId*>(n) ) return visit((VariableDeclaratorId*) n);
        if (dynamic_cast<FieldModifiers*>(n) ) return visit((FieldModifiers*) n);
        if (dynamic_cast<MethodDeclaration*>(n) ) return visit((MethodDeclaration*) n);
        if (dynamic_cast<MethodHeader*>(n) ) return visit((MethodHeader*) n);
        if (dynamic_cast<ResultType*>(n) ) return visit((ResultType*) n);
        if (dynamic_cast<FormalParameterList*>(n) ) return visit((FormalParameterList*) n);
        if (dynamic_cast<FormalParameters*>(n) ) return visit((FormalParameters*) n);
        if (dynamic_cast<FormalParameter*>(n) ) return visit((FormalParameter*) n);
        if (dynamic_cast<VariableModifiers*>(n) ) return visit((VariableModifiers*) n);
        if (dynamic_cast<VariableModifier*>(n) ) return visit((VariableModifier*) n);
        if (dynamic_cast<LastFormalParameter*>(n) ) return visit((LastFormalParameter*) n);
        if (dynamic_cast<MethodModifiers*>(n) ) return visit((MethodModifiers*) n);
        if (dynamic_cast<Throws*>(n) ) return visit((Throws*) n);
        if (dynamic_cast<ExceptionTypeList*>(n) ) return visit((ExceptionTypeList*) n);
        if (dynamic_cast<MethodBody*>(n) ) return visit((MethodBody*) n);
        if (dynamic_cast<StaticInitializer*>(n) ) return visit((StaticInitializer*) n);
        if (dynamic_cast<ConstructorDeclaration*>(n) ) return visit((ConstructorDeclaration*) n);
        if (dynamic_cast<ConstructorDeclarator*>(n) ) return visit((ConstructorDeclarator*) n);
        if (dynamic_cast<ConstructorModifiers*>(n) ) return visit((ConstructorModifiers*) n);
        if (dynamic_cast<ConstructorBody*>(n) ) return visit((ConstructorBody*) n);
        if (dynamic_cast<EnumDeclaration*>(n) ) return visit((EnumDeclaration*) n);
        if (dynamic_cast<EnumBody*>(n) ) return visit((EnumBody*) n);
        if (dynamic_cast<EnumConstants*>(n) ) return visit((EnumConstants*) n);
        if (dynamic_cast<EnumConstant*>(n) ) return visit((EnumConstant*) n);
        if (dynamic_cast<Arguments*>(n) ) return visit((Arguments*) n);
        if (dynamic_cast<EnumBodyDeclarations*>(n) ) return visit((EnumBodyDeclarations*) n);
        if (dynamic_cast<NormalInterfaceDeclaration*>(n) ) return visit((NormalInterfaceDeclaration*) n);
        if (dynamic_cast<InterfaceModifiers*>(n) ) return visit((InterfaceModifiers*) n);
        if (dynamic_cast<InterfaceBody*>(n) ) return visit((InterfaceBody*) n);
        if (dynamic_cast<InterfaceMemberDeclarations*>(n) ) return visit((InterfaceMemberDeclarations*) n);
        if (dynamic_cast<InterfaceMemberDeclaration*>(n) ) return visit((InterfaceMemberDeclaration*) n);
        if (dynamic_cast<ConstantDeclaration*>(n) ) return visit((ConstantDeclaration*) n);
        if (dynamic_cast<ConstantModifiers*>(n) ) return visit((ConstantModifiers*) n);
        if (dynamic_cast<AbstractMethodDeclaration*>(n) ) return visit((AbstractMethodDeclaration*) n);
        if (dynamic_cast<AbstractMethodModifiers*>(n) ) return visit((AbstractMethodModifiers*) n);
        if (dynamic_cast<AnnotationTypeDeclaration*>(n) ) return visit((AnnotationTypeDeclaration*) n);
        if (dynamic_cast<AnnotationTypeBody*>(n) ) return visit((AnnotationTypeBody*) n);
        if (dynamic_cast<AnnotationTypeElementDeclarations*>(n) ) return visit((AnnotationTypeElementDeclarations*) n);
        if (dynamic_cast<DefaultValue*>(n) ) return visit((DefaultValue*) n);
        if (dynamic_cast<Annotations*>(n) ) return visit((Annotations*) n);
        if (dynamic_cast<NormalAnnotation*>(n) ) return visit((NormalAnnotation*) n);
        if (dynamic_cast<ElementValuePairs*>(n) ) return visit((ElementValuePairs*) n);
        if (dynamic_cast<ElementValuePair*>(n) ) return visit((ElementValuePair*) n);
        if (dynamic_cast<ElementValueArrayInitializer*>(n) ) return visit((ElementValueArrayInitializer*) n);
        if (dynamic_cast<ElementValues*>(n) ) return visit((ElementValues*) n);
        if (dynamic_cast<MarkerAnnotation*>(n) ) return visit((MarkerAnnotation*) n);
        if (dynamic_cast<SingleElementAnnotation*>(n) ) return visit((SingleElementAnnotation*) n);
        if (dynamic_cast<ArrayInitializer*>(n) ) return visit((ArrayInitializer*) n);
        if (dynamic_cast<VariableInitializers*>(n) ) return visit((VariableInitializers*) n);
        if (dynamic_cast<Block*>(n) ) return visit((Block*) n);
        if (dynamic_cast<BlockStatements*>(n) ) return visit((BlockStatements*) n);
        if (dynamic_cast<LocalVariableDeclarationStatement*>(n) ) return visit((LocalVariableDeclarationStatement*) n);
        if (dynamic_cast<LocalVariableDeclaration*>(n) ) return visit((LocalVariableDeclaration*) n);
        if (dynamic_cast<IfThenStatement*>(n) ) return visit((IfThenStatement*) n);
        if (dynamic_cast<IfThenElseStatement*>(n) ) return visit((IfThenElseStatement*) n);
        if (dynamic_cast<IfThenElseStatementNoShortIf*>(n) ) return visit((IfThenElseStatementNoShortIf*) n);
        if (dynamic_cast<EmptyStatement*>(n) ) return visit((EmptyStatement*) n);
        if (dynamic_cast<LabeledStatement*>(n) ) return visit((LabeledStatement*) n);
        if (dynamic_cast<LabeledStatementNoShortIf*>(n) ) return visit((LabeledStatementNoShortIf*) n);
        if (dynamic_cast<ExpressionStatement*>(n) ) return visit((ExpressionStatement*) n);
        if (dynamic_cast<SwitchStatement*>(n) ) return visit((SwitchStatement*) n);
        if (dynamic_cast<SwitchBlock*>(n) ) return visit((SwitchBlock*) n);
        if (dynamic_cast<SwitchBlockStatementGroups*>(n) ) return visit((SwitchBlockStatementGroups*) n);
        if (dynamic_cast<SwitchBlockStatementGroup*>(n) ) return visit((SwitchBlockStatementGroup*) n);
        if (dynamic_cast<SwitchLabels*>(n) ) return visit((SwitchLabels*) n);
        if (dynamic_cast<WhileStatement*>(n) ) return visit((WhileStatement*) n);
        if (dynamic_cast<WhileStatementNoShortIf*>(n) ) return visit((WhileStatementNoShortIf*) n);
        if (dynamic_cast<DoStatement*>(n) ) return visit((DoStatement*) n);
        if (dynamic_cast<BasicForStatement*>(n) ) return visit((BasicForStatement*) n);
        if (dynamic_cast<ForStatementNoShortIf*>(n) ) return visit((ForStatementNoShortIf*) n);
        if (dynamic_cast<StatementExpressionList*>(n) ) return visit((StatementExpressionList*) n);
        if (dynamic_cast<EnhancedForStatement*>(n) ) return visit((EnhancedForStatement*) n);
        if (dynamic_cast<BreakStatement*>(n) ) return visit((BreakStatement*) n);
        if (dynamic_cast<ContinueStatement*>(n) ) return visit((ContinueStatement*) n);
        if (dynamic_cast<ReturnStatement*>(n) ) return visit((ReturnStatement*) n);
        if (dynamic_cast<ThrowStatement*>(n) ) return visit((ThrowStatement*) n);
        if (dynamic_cast<SynchronizedStatement*>(n) ) return visit((SynchronizedStatement*) n);
        if (dynamic_cast<Catches*>(n) ) return visit((Catches*) n);
        if (dynamic_cast<CatchClause*>(n) ) return visit((CatchClause*) n);
        if (dynamic_cast<Finally*>(n) ) return visit((Finally*) n);
        if (dynamic_cast<ArgumentList*>(n) ) return visit((ArgumentList*) n);
        if (dynamic_cast<DimExprs*>(n) ) return visit((DimExprs*) n);
        if (dynamic_cast<DimExpr*>(n) ) return visit((DimExpr*) n);
        if (dynamic_cast<PostIncrementExpression*>(n) ) return visit((PostIncrementExpression*) n);
        if (dynamic_cast<PostDecrementExpression*>(n) ) return visit((PostDecrementExpression*) n);
        if (dynamic_cast<PreIncrementExpression*>(n) ) return visit((PreIncrementExpression*) n);
        if (dynamic_cast<PreDecrementExpression*>(n) ) return visit((PreDecrementExpression*) n);
        if (dynamic_cast<AndExpression*>(n) ) return visit((AndExpression*) n);
        if (dynamic_cast<ExclusiveOrExpression*>(n) ) return visit((ExclusiveOrExpression*) n);
        if (dynamic_cast<InclusiveOrExpression*>(n) ) return visit((InclusiveOrExpression*) n);
        if (dynamic_cast<ConditionalAndExpression*>(n) ) return visit((ConditionalAndExpression*) n);
        if (dynamic_cast<ConditionalOrExpression*>(n) ) return visit((ConditionalOrExpression*) n);
        if (dynamic_cast<ConditionalExpression*>(n) ) return visit((ConditionalExpression*) n);
        if (dynamic_cast<Assignment*>(n) ) return visit((Assignment*) n);
        if (dynamic_cast<Commaopt*>(n) ) return visit((Commaopt*) n);
        if (dynamic_cast<Ellipsisopt*>(n) ) return visit((Ellipsisopt*) n);
        if (dynamic_cast<LPGUserAction0*>(n) ) return visit((LPGUserAction0*) n);
        if (dynamic_cast<LPGUserAction1*>(n) ) return visit((LPGUserAction1*) n);
        if (dynamic_cast<LPGUserAction2*>(n) ) return visit((LPGUserAction2*) n);
        if (dynamic_cast<LPGUserAction3*>(n) ) return visit((LPGUserAction3*) n);
        if (dynamic_cast<LPGUserAction4*>(n) ) return visit((LPGUserAction4*) n);
        if (dynamic_cast<IntegralType0*>(n) ) return visit((IntegralType0*) n);
        if (dynamic_cast<IntegralType1*>(n) ) return visit((IntegralType1*) n);
        if (dynamic_cast<IntegralType2*>(n) ) return visit((IntegralType2*) n);
        if (dynamic_cast<IntegralType3*>(n) ) return visit((IntegralType3*) n);
        if (dynamic_cast<IntegralType4*>(n) ) return visit((IntegralType4*) n);
        if (dynamic_cast<FloatingPointType0*>(n) ) return visit((FloatingPointType0*) n);
        if (dynamic_cast<FloatingPointType1*>(n) ) return visit((FloatingPointType1*) n);
        if (dynamic_cast<WildcardBounds0*>(n) ) return visit((WildcardBounds0*) n);
        if (dynamic_cast<WildcardBounds1*>(n) ) return visit((WildcardBounds1*) n);
        if (dynamic_cast<ClassModifier0*>(n) ) return visit((ClassModifier0*) n);
        if (dynamic_cast<ClassModifier1*>(n) ) return visit((ClassModifier1*) n);
        if (dynamic_cast<ClassModifier2*>(n) ) return visit((ClassModifier2*) n);
        if (dynamic_cast<ClassModifier3*>(n) ) return visit((ClassModifier3*) n);
        if (dynamic_cast<ClassModifier4*>(n) ) return visit((ClassModifier4*) n);
        if (dynamic_cast<ClassModifier5*>(n) ) return visit((ClassModifier5*) n);
        if (dynamic_cast<ClassModifier6*>(n) ) return visit((ClassModifier6*) n);
        if (dynamic_cast<FieldModifier0*>(n) ) return visit((FieldModifier0*) n);
        if (dynamic_cast<FieldModifier1*>(n) ) return visit((FieldModifier1*) n);
        if (dynamic_cast<FieldModifier2*>(n) ) return visit((FieldModifier2*) n);
        if (dynamic_cast<FieldModifier3*>(n) ) return visit((FieldModifier3*) n);
        if (dynamic_cast<FieldModifier4*>(n) ) return visit((FieldModifier4*) n);
        if (dynamic_cast<FieldModifier5*>(n) ) return visit((FieldModifier5*) n);
        if (dynamic_cast<FieldModifier6*>(n) ) return visit((FieldModifier6*) n);
        if (dynamic_cast<MethodDeclarator0*>(n) ) return visit((MethodDeclarator0*) n);
        if (dynamic_cast<MethodDeclarator1*>(n) ) return visit((MethodDeclarator1*) n);
        if (dynamic_cast<MethodModifier0*>(n) ) return visit((MethodModifier0*) n);
        if (dynamic_cast<MethodModifier1*>(n) ) return visit((MethodModifier1*) n);
        if (dynamic_cast<MethodModifier2*>(n) ) return visit((MethodModifier2*) n);
        if (dynamic_cast<MethodModifier3*>(n) ) return visit((MethodModifier3*) n);
        if (dynamic_cast<MethodModifier4*>(n) ) return visit((MethodModifier4*) n);
        if (dynamic_cast<MethodModifier5*>(n) ) return visit((MethodModifier5*) n);
        if (dynamic_cast<MethodModifier6*>(n) ) return visit((MethodModifier6*) n);
        if (dynamic_cast<MethodModifier7*>(n) ) return visit((MethodModifier7*) n);
        if (dynamic_cast<MethodModifier8*>(n) ) return visit((MethodModifier8*) n);
        if (dynamic_cast<ConstructorModifier0*>(n) ) return visit((ConstructorModifier0*) n);
        if (dynamic_cast<ConstructorModifier1*>(n) ) return visit((ConstructorModifier1*) n);
        if (dynamic_cast<ConstructorModifier2*>(n) ) return visit((ConstructorModifier2*) n);
        if (dynamic_cast<ExplicitConstructorInvocation0*>(n) ) return visit((ExplicitConstructorInvocation0*) n);
        if (dynamic_cast<ExplicitConstructorInvocation1*>(n) ) return visit((ExplicitConstructorInvocation1*) n);
        if (dynamic_cast<ExplicitConstructorInvocation2*>(n) ) return visit((ExplicitConstructorInvocation2*) n);
        if (dynamic_cast<InterfaceModifier0*>(n) ) return visit((InterfaceModifier0*) n);
        if (dynamic_cast<InterfaceModifier1*>(n) ) return visit((InterfaceModifier1*) n);
        if (dynamic_cast<InterfaceModifier2*>(n) ) return visit((InterfaceModifier2*) n);
        if (dynamic_cast<InterfaceModifier3*>(n) ) return visit((InterfaceModifier3*) n);
        if (dynamic_cast<InterfaceModifier4*>(n) ) return visit((InterfaceModifier4*) n);
        if (dynamic_cast<InterfaceModifier5*>(n) ) return visit((InterfaceModifier5*) n);
        if (dynamic_cast<ExtendsInterfaces0*>(n) ) return visit((ExtendsInterfaces0*) n);
        if (dynamic_cast<ExtendsInterfaces1*>(n) ) return visit((ExtendsInterfaces1*) n);
        if (dynamic_cast<ConstantModifier0*>(n) ) return visit((ConstantModifier0*) n);
        if (dynamic_cast<ConstantModifier1*>(n) ) return visit((ConstantModifier1*) n);
        if (dynamic_cast<ConstantModifier2*>(n) ) return visit((ConstantModifier2*) n);
        if (dynamic_cast<AbstractMethodModifier0*>(n) ) return visit((AbstractMethodModifier0*) n);
        if (dynamic_cast<AbstractMethodModifier1*>(n) ) return visit((AbstractMethodModifier1*) n);
        if (dynamic_cast<AnnotationTypeElementDeclaration0*>(n) ) return visit((AnnotationTypeElementDeclaration0*) n);
        if (dynamic_cast<AnnotationTypeElementDeclaration1*>(n) ) return visit((AnnotationTypeElementDeclaration1*) n);
        if (dynamic_cast<AssertStatement0*>(n) ) return visit((AssertStatement0*) n);
        if (dynamic_cast<AssertStatement1*>(n) ) return visit((AssertStatement1*) n);
        if (dynamic_cast<SwitchLabel0*>(n) ) return visit((SwitchLabel0*) n);
        if (dynamic_cast<SwitchLabel1*>(n) ) return visit((SwitchLabel1*) n);
        if (dynamic_cast<SwitchLabel2*>(n) ) return visit((SwitchLabel2*) n);
        if (dynamic_cast<TryStatement0*>(n) ) return visit((TryStatement0*) n);
        if (dynamic_cast<TryStatement1*>(n) ) return visit((TryStatement1*) n);
        if (dynamic_cast<PrimaryNoNewArray0*>(n) ) return visit((PrimaryNoNewArray0*) n);
        if (dynamic_cast<PrimaryNoNewArray1*>(n) ) return visit((PrimaryNoNewArray1*) n);
        if (dynamic_cast<PrimaryNoNewArray2*>(n) ) return visit((PrimaryNoNewArray2*) n);
        if (dynamic_cast<PrimaryNoNewArray3*>(n) ) return visit((PrimaryNoNewArray3*) n);
        if (dynamic_cast<PrimaryNoNewArray4*>(n) ) return visit((PrimaryNoNewArray4*) n);
        if (dynamic_cast<Literal0*>(n) ) return visit((Literal0*) n);
        if (dynamic_cast<Literal1*>(n) ) return visit((Literal1*) n);
        if (dynamic_cast<Literal2*>(n) ) return visit((Literal2*) n);
        if (dynamic_cast<Literal3*>(n) ) return visit((Literal3*) n);
        if (dynamic_cast<Literal4*>(n) ) return visit((Literal4*) n);
        if (dynamic_cast<Literal5*>(n) ) return visit((Literal5*) n);
        if (dynamic_cast<Literal6*>(n) ) return visit((Literal6*) n);
        if (dynamic_cast<BooleanLiteral0*>(n) ) return visit((BooleanLiteral0*) n);
        if (dynamic_cast<BooleanLiteral1*>(n) ) return visit((BooleanLiteral1*) n);
        if (dynamic_cast<ClassInstanceCreationExpression0*>(n) ) return visit((ClassInstanceCreationExpression0*) n);
        if (dynamic_cast<ClassInstanceCreationExpression1*>(n) ) return visit((ClassInstanceCreationExpression1*) n);
        if (dynamic_cast<ArrayCreationExpression0*>(n) ) return visit((ArrayCreationExpression0*) n);
        if (dynamic_cast<ArrayCreationExpression1*>(n) ) return visit((ArrayCreationExpression1*) n);
        if (dynamic_cast<ArrayCreationExpression2*>(n) ) return visit((ArrayCreationExpression2*) n);
        if (dynamic_cast<ArrayCreationExpression3*>(n) ) return visit((ArrayCreationExpression3*) n);
        if (dynamic_cast<Dims0*>(n) ) return visit((Dims0*) n);
        if (dynamic_cast<Dims1*>(n) ) return visit((Dims1*) n);
        if (dynamic_cast<FieldAccess0*>(n) ) return visit((FieldAccess0*) n);
        if (dynamic_cast<FieldAccess1*>(n) ) return visit((FieldAccess1*) n);
        if (dynamic_cast<FieldAccess2*>(n) ) return visit((FieldAccess2*) n);
        if (dynamic_cast<MethodInvocation0*>(n) ) return visit((MethodInvocation0*) n);
        if (dynamic_cast<MethodInvocation1*>(n) ) return visit((MethodInvocation1*) n);
        if (dynamic_cast<MethodInvocation2*>(n) ) return visit((MethodInvocation2*) n);
        if (dynamic_cast<MethodInvocation3*>(n) ) return visit((MethodInvocation3*) n);
        if (dynamic_cast<MethodInvocation4*>(n) ) return visit((MethodInvocation4*) n);
        if (dynamic_cast<ArrayAccess0*>(n) ) return visit((ArrayAccess0*) n);
        if (dynamic_cast<ArrayAccess1*>(n) ) return visit((ArrayAccess1*) n);
        if (dynamic_cast<UnaryExpression0*>(n) ) return visit((UnaryExpression0*) n);
        if (dynamic_cast<UnaryExpression1*>(n) ) return visit((UnaryExpression1*) n);
        if (dynamic_cast<UnaryExpressionNotPlusMinus0*>(n) ) return visit((UnaryExpressionNotPlusMinus0*) n);
        if (dynamic_cast<UnaryExpressionNotPlusMinus1*>(n) ) return visit((UnaryExpressionNotPlusMinus1*) n);
        if (dynamic_cast<CastExpression0*>(n) ) return visit((CastExpression0*) n);
        if (dynamic_cast<CastExpression1*>(n) ) return visit((CastExpression1*) n);
        if (dynamic_cast<MultiplicativeExpression0*>(n) ) return visit((MultiplicativeExpression0*) n);
        if (dynamic_cast<MultiplicativeExpression1*>(n) ) return visit((MultiplicativeExpression1*) n);
        if (dynamic_cast<MultiplicativeExpression2*>(n) ) return visit((MultiplicativeExpression2*) n);
        if (dynamic_cast<AdditiveExpression0*>(n) ) return visit((AdditiveExpression0*) n);
        if (dynamic_cast<AdditiveExpression1*>(n) ) return visit((AdditiveExpression1*) n);
        if (dynamic_cast<ShiftExpression0*>(n) ) return visit((ShiftExpression0*) n);
        if (dynamic_cast<ShiftExpression1*>(n) ) return visit((ShiftExpression1*) n);
        if (dynamic_cast<ShiftExpression2*>(n) ) return visit((ShiftExpression2*) n);
        if (dynamic_cast<RelationalExpression0*>(n) ) return visit((RelationalExpression0*) n);
        if (dynamic_cast<RelationalExpression1*>(n) ) return visit((RelationalExpression1*) n);
        if (dynamic_cast<RelationalExpression2*>(n) ) return visit((RelationalExpression2*) n);
        if (dynamic_cast<RelationalExpression3*>(n) ) return visit((RelationalExpression3*) n);
        if (dynamic_cast<RelationalExpression4*>(n) ) return visit((RelationalExpression4*) n);
        if (dynamic_cast<EqualityExpression0*>(n) ) return visit((EqualityExpression0*) n);
        if (dynamic_cast<EqualityExpression1*>(n) ) return visit((EqualityExpression1*) n);
        if (dynamic_cast<AssignmentOperator0*>(n) ) return visit((AssignmentOperator0*) n);
        if (dynamic_cast<AssignmentOperator1*>(n) ) return visit((AssignmentOperator1*) n);
        if (dynamic_cast<AssignmentOperator2*>(n) ) return visit((AssignmentOperator2*) n);
        if (dynamic_cast<AssignmentOperator3*>(n) ) return visit((AssignmentOperator3*) n);
        if (dynamic_cast<AssignmentOperator4*>(n) ) return visit((AssignmentOperator4*) n);
        if (dynamic_cast<AssignmentOperator5*>(n) ) return visit((AssignmentOperator5*) n);
        if (dynamic_cast<AssignmentOperator6*>(n) ) return visit((AssignmentOperator6*) n);
        if (dynamic_cast<AssignmentOperator7*>(n) ) return visit((AssignmentOperator7*) n);
        if (dynamic_cast<AssignmentOperator8*>(n) ) return visit((AssignmentOperator8*) n);
        if (dynamic_cast<AssignmentOperator9*>(n) ) return visit((AssignmentOperator9*) n);
        if (dynamic_cast<AssignmentOperator10*>(n) ) return visit((AssignmentOperator10*) n);
        if (dynamic_cast<AssignmentOperator11*>(n) ) return visit((AssignmentOperator11*) n);
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
  virtual  void endVisit(Ast *n)
    {
        if (dynamic_cast<AstToken*>(n) ){ endVisit((AstToken*) n);return;}
        if (dynamic_cast<identifier*>(n) ){ endVisit((identifier*) n);return;}
        if (dynamic_cast<PrimitiveType*>(n) ){ endVisit((PrimitiveType*) n);return;}
        if (dynamic_cast<ClassType*>(n) ){ endVisit((ClassType*) n);return;}
        if (dynamic_cast<InterfaceType*>(n) ){ endVisit((InterfaceType*) n);return;}
        if (dynamic_cast<TypeName*>(n) ){ endVisit((TypeName*) n);return;}
        if (dynamic_cast<ArrayType*>(n) ){ endVisit((ArrayType*) n);return;}
        if (dynamic_cast<TypeParameter*>(n) ){ endVisit((TypeParameter*) n);return;}
        if (dynamic_cast<TypeBound*>(n) ){ endVisit((TypeBound*) n);return;}
        if (dynamic_cast<AdditionalBoundList*>(n) ){ endVisit((AdditionalBoundList*) n);return;}
        if (dynamic_cast<AdditionalBound*>(n) ){ endVisit((AdditionalBound*) n);return;}
        if (dynamic_cast<TypeArguments*>(n) ){ endVisit((TypeArguments*) n);return;}
        if (dynamic_cast<ActualTypeArgumentList*>(n) ){ endVisit((ActualTypeArgumentList*) n);return;}
        if (dynamic_cast<Wildcard*>(n) ){ endVisit((Wildcard*) n);return;}
        if (dynamic_cast<PackageName*>(n) ){ endVisit((PackageName*) n);return;}
        if (dynamic_cast<ExpressionName*>(n) ){ endVisit((ExpressionName*) n);return;}
        if (dynamic_cast<MethodName*>(n) ){ endVisit((MethodName*) n);return;}
        if (dynamic_cast<PackageOrTypeName*>(n) ){ endVisit((PackageOrTypeName*) n);return;}
        if (dynamic_cast<AmbiguousName*>(n) ){ endVisit((AmbiguousName*) n);return;}
        if (dynamic_cast<CompilationUnit*>(n) ){ endVisit((CompilationUnit*) n);return;}
        if (dynamic_cast<ImportDeclarations*>(n) ){ endVisit((ImportDeclarations*) n);return;}
        if (dynamic_cast<TypeDeclarations*>(n) ){ endVisit((TypeDeclarations*) n);return;}
        if (dynamic_cast<PackageDeclaration*>(n) ){ endVisit((PackageDeclaration*) n);return;}
        if (dynamic_cast<SingleTypeImportDeclaration*>(n) ){ endVisit((SingleTypeImportDeclaration*) n);return;}
        if (dynamic_cast<TypeImportOnDemandDeclaration*>(n) ){ endVisit((TypeImportOnDemandDeclaration*) n);return;}
        if (dynamic_cast<SingleStaticImportDeclaration*>(n) ){ endVisit((SingleStaticImportDeclaration*) n);return;}
        if (dynamic_cast<StaticImportOnDemandDeclaration*>(n) ){ endVisit((StaticImportOnDemandDeclaration*) n);return;}
        if (dynamic_cast<TypeDeclaration*>(n) ){ endVisit((TypeDeclaration*) n);return;}
        if (dynamic_cast<NormalClassDeclaration*>(n) ){ endVisit((NormalClassDeclaration*) n);return;}
        if (dynamic_cast<ClassModifiers*>(n) ){ endVisit((ClassModifiers*) n);return;}
        if (dynamic_cast<TypeParameters*>(n) ){ endVisit((TypeParameters*) n);return;}
        if (dynamic_cast<TypeParameterList*>(n) ){ endVisit((TypeParameterList*) n);return;}
        if (dynamic_cast<Super*>(n) ){ endVisit((Super*) n);return;}
        if (dynamic_cast<Interfaces*>(n) ){ endVisit((Interfaces*) n);return;}
        if (dynamic_cast<InterfaceTypeList*>(n) ){ endVisit((InterfaceTypeList*) n);return;}
        if (dynamic_cast<ClassBody*>(n) ){ endVisit((ClassBody*) n);return;}
        if (dynamic_cast<ClassBodyDeclarations*>(n) ){ endVisit((ClassBodyDeclarations*) n);return;}
        if (dynamic_cast<ClassMemberDeclaration*>(n) ){ endVisit((ClassMemberDeclaration*) n);return;}
        if (dynamic_cast<FieldDeclaration*>(n) ){ endVisit((FieldDeclaration*) n);return;}
        if (dynamic_cast<VariableDeclarators*>(n) ){ endVisit((VariableDeclarators*) n);return;}
        if (dynamic_cast<VariableDeclarator*>(n) ){ endVisit((VariableDeclarator*) n);return;}
        if (dynamic_cast<VariableDeclaratorId*>(n) ){ endVisit((VariableDeclaratorId*) n);return;}
        if (dynamic_cast<FieldModifiers*>(n) ){ endVisit((FieldModifiers*) n);return;}
        if (dynamic_cast<MethodDeclaration*>(n) ){ endVisit((MethodDeclaration*) n);return;}
        if (dynamic_cast<MethodHeader*>(n) ){ endVisit((MethodHeader*) n);return;}
        if (dynamic_cast<ResultType*>(n) ){ endVisit((ResultType*) n);return;}
        if (dynamic_cast<FormalParameterList*>(n) ){ endVisit((FormalParameterList*) n);return;}
        if (dynamic_cast<FormalParameters*>(n) ){ endVisit((FormalParameters*) n);return;}
        if (dynamic_cast<FormalParameter*>(n) ){ endVisit((FormalParameter*) n);return;}
        if (dynamic_cast<VariableModifiers*>(n) ){ endVisit((VariableModifiers*) n);return;}
        if (dynamic_cast<VariableModifier*>(n) ){ endVisit((VariableModifier*) n);return;}
        if (dynamic_cast<LastFormalParameter*>(n) ){ endVisit((LastFormalParameter*) n);return;}
        if (dynamic_cast<MethodModifiers*>(n) ){ endVisit((MethodModifiers*) n);return;}
        if (dynamic_cast<Throws*>(n) ){ endVisit((Throws*) n);return;}
        if (dynamic_cast<ExceptionTypeList*>(n) ){ endVisit((ExceptionTypeList*) n);return;}
        if (dynamic_cast<MethodBody*>(n) ){ endVisit((MethodBody*) n);return;}
        if (dynamic_cast<StaticInitializer*>(n) ){ endVisit((StaticInitializer*) n);return;}
        if (dynamic_cast<ConstructorDeclaration*>(n) ){ endVisit((ConstructorDeclaration*) n);return;}
        if (dynamic_cast<ConstructorDeclarator*>(n) ){ endVisit((ConstructorDeclarator*) n);return;}
        if (dynamic_cast<ConstructorModifiers*>(n) ){ endVisit((ConstructorModifiers*) n);return;}
        if (dynamic_cast<ConstructorBody*>(n) ){ endVisit((ConstructorBody*) n);return;}
        if (dynamic_cast<EnumDeclaration*>(n) ){ endVisit((EnumDeclaration*) n);return;}
        if (dynamic_cast<EnumBody*>(n) ){ endVisit((EnumBody*) n);return;}
        if (dynamic_cast<EnumConstants*>(n) ){ endVisit((EnumConstants*) n);return;}
        if (dynamic_cast<EnumConstant*>(n) ){ endVisit((EnumConstant*) n);return;}
        if (dynamic_cast<Arguments*>(n) ){ endVisit((Arguments*) n);return;}
        if (dynamic_cast<EnumBodyDeclarations*>(n) ){ endVisit((EnumBodyDeclarations*) n);return;}
        if (dynamic_cast<NormalInterfaceDeclaration*>(n) ){ endVisit((NormalInterfaceDeclaration*) n);return;}
        if (dynamic_cast<InterfaceModifiers*>(n) ){ endVisit((InterfaceModifiers*) n);return;}
        if (dynamic_cast<InterfaceBody*>(n) ){ endVisit((InterfaceBody*) n);return;}
        if (dynamic_cast<InterfaceMemberDeclarations*>(n) ){ endVisit((InterfaceMemberDeclarations*) n);return;}
        if (dynamic_cast<InterfaceMemberDeclaration*>(n) ){ endVisit((InterfaceMemberDeclaration*) n);return;}
        if (dynamic_cast<ConstantDeclaration*>(n) ){ endVisit((ConstantDeclaration*) n);return;}
        if (dynamic_cast<ConstantModifiers*>(n) ){ endVisit((ConstantModifiers*) n);return;}
        if (dynamic_cast<AbstractMethodDeclaration*>(n) ){ endVisit((AbstractMethodDeclaration*) n);return;}
        if (dynamic_cast<AbstractMethodModifiers*>(n) ){ endVisit((AbstractMethodModifiers*) n);return;}
        if (dynamic_cast<AnnotationTypeDeclaration*>(n) ){ endVisit((AnnotationTypeDeclaration*) n);return;}
        if (dynamic_cast<AnnotationTypeBody*>(n) ){ endVisit((AnnotationTypeBody*) n);return;}
        if (dynamic_cast<AnnotationTypeElementDeclarations*>(n) ){ endVisit((AnnotationTypeElementDeclarations*) n);return;}
        if (dynamic_cast<DefaultValue*>(n) ){ endVisit((DefaultValue*) n);return;}
        if (dynamic_cast<Annotations*>(n) ){ endVisit((Annotations*) n);return;}
        if (dynamic_cast<NormalAnnotation*>(n) ){ endVisit((NormalAnnotation*) n);return;}
        if (dynamic_cast<ElementValuePairs*>(n) ){ endVisit((ElementValuePairs*) n);return;}
        if (dynamic_cast<ElementValuePair*>(n) ){ endVisit((ElementValuePair*) n);return;}
        if (dynamic_cast<ElementValueArrayInitializer*>(n) ){ endVisit((ElementValueArrayInitializer*) n);return;}
        if (dynamic_cast<ElementValues*>(n) ){ endVisit((ElementValues*) n);return;}
        if (dynamic_cast<MarkerAnnotation*>(n) ){ endVisit((MarkerAnnotation*) n);return;}
        if (dynamic_cast<SingleElementAnnotation*>(n) ){ endVisit((SingleElementAnnotation*) n);return;}
        if (dynamic_cast<ArrayInitializer*>(n) ){ endVisit((ArrayInitializer*) n);return;}
        if (dynamic_cast<VariableInitializers*>(n) ){ endVisit((VariableInitializers*) n);return;}
        if (dynamic_cast<Block*>(n) ){ endVisit((Block*) n);return;}
        if (dynamic_cast<BlockStatements*>(n) ){ endVisit((BlockStatements*) n);return;}
        if (dynamic_cast<LocalVariableDeclarationStatement*>(n) ){ endVisit((LocalVariableDeclarationStatement*) n);return;}
        if (dynamic_cast<LocalVariableDeclaration*>(n) ){ endVisit((LocalVariableDeclaration*) n);return;}
        if (dynamic_cast<IfThenStatement*>(n) ){ endVisit((IfThenStatement*) n);return;}
        if (dynamic_cast<IfThenElseStatement*>(n) ){ endVisit((IfThenElseStatement*) n);return;}
        if (dynamic_cast<IfThenElseStatementNoShortIf*>(n) ){ endVisit((IfThenElseStatementNoShortIf*) n);return;}
        if (dynamic_cast<EmptyStatement*>(n) ){ endVisit((EmptyStatement*) n);return;}
        if (dynamic_cast<LabeledStatement*>(n) ){ endVisit((LabeledStatement*) n);return;}
        if (dynamic_cast<LabeledStatementNoShortIf*>(n) ){ endVisit((LabeledStatementNoShortIf*) n);return;}
        if (dynamic_cast<ExpressionStatement*>(n) ){ endVisit((ExpressionStatement*) n);return;}
        if (dynamic_cast<SwitchStatement*>(n) ){ endVisit((SwitchStatement*) n);return;}
        if (dynamic_cast<SwitchBlock*>(n) ){ endVisit((SwitchBlock*) n);return;}
        if (dynamic_cast<SwitchBlockStatementGroups*>(n) ){ endVisit((SwitchBlockStatementGroups*) n);return;}
        if (dynamic_cast<SwitchBlockStatementGroup*>(n) ){ endVisit((SwitchBlockStatementGroup*) n);return;}
        if (dynamic_cast<SwitchLabels*>(n) ){ endVisit((SwitchLabels*) n);return;}
        if (dynamic_cast<WhileStatement*>(n) ){ endVisit((WhileStatement*) n);return;}
        if (dynamic_cast<WhileStatementNoShortIf*>(n) ){ endVisit((WhileStatementNoShortIf*) n);return;}
        if (dynamic_cast<DoStatement*>(n) ){ endVisit((DoStatement*) n);return;}
        if (dynamic_cast<BasicForStatement*>(n) ){ endVisit((BasicForStatement*) n);return;}
        if (dynamic_cast<ForStatementNoShortIf*>(n) ){ endVisit((ForStatementNoShortIf*) n);return;}
        if (dynamic_cast<StatementExpressionList*>(n) ){ endVisit((StatementExpressionList*) n);return;}
        if (dynamic_cast<EnhancedForStatement*>(n) ){ endVisit((EnhancedForStatement*) n);return;}
        if (dynamic_cast<BreakStatement*>(n) ){ endVisit((BreakStatement*) n);return;}
        if (dynamic_cast<ContinueStatement*>(n) ){ endVisit((ContinueStatement*) n);return;}
        if (dynamic_cast<ReturnStatement*>(n) ){ endVisit((ReturnStatement*) n);return;}
        if (dynamic_cast<ThrowStatement*>(n) ){ endVisit((ThrowStatement*) n);return;}
        if (dynamic_cast<SynchronizedStatement*>(n) ){ endVisit((SynchronizedStatement*) n);return;}
        if (dynamic_cast<Catches*>(n) ){ endVisit((Catches*) n);return;}
        if (dynamic_cast<CatchClause*>(n) ){ endVisit((CatchClause*) n);return;}
        if (dynamic_cast<Finally*>(n) ){ endVisit((Finally*) n);return;}
        if (dynamic_cast<ArgumentList*>(n) ){ endVisit((ArgumentList*) n);return;}
        if (dynamic_cast<DimExprs*>(n) ){ endVisit((DimExprs*) n);return;}
        if (dynamic_cast<DimExpr*>(n) ){ endVisit((DimExpr*) n);return;}
        if (dynamic_cast<PostIncrementExpression*>(n) ){ endVisit((PostIncrementExpression*) n);return;}
        if (dynamic_cast<PostDecrementExpression*>(n) ){ endVisit((PostDecrementExpression*) n);return;}
        if (dynamic_cast<PreIncrementExpression*>(n) ){ endVisit((PreIncrementExpression*) n);return;}
        if (dynamic_cast<PreDecrementExpression*>(n) ){ endVisit((PreDecrementExpression*) n);return;}
        if (dynamic_cast<AndExpression*>(n) ){ endVisit((AndExpression*) n);return;}
        if (dynamic_cast<ExclusiveOrExpression*>(n) ){ endVisit((ExclusiveOrExpression*) n);return;}
        if (dynamic_cast<InclusiveOrExpression*>(n) ){ endVisit((InclusiveOrExpression*) n);return;}
        if (dynamic_cast<ConditionalAndExpression*>(n) ){ endVisit((ConditionalAndExpression*) n);return;}
        if (dynamic_cast<ConditionalOrExpression*>(n) ){ endVisit((ConditionalOrExpression*) n);return;}
        if (dynamic_cast<ConditionalExpression*>(n) ){ endVisit((ConditionalExpression*) n);return;}
        if (dynamic_cast<Assignment*>(n) ){ endVisit((Assignment*) n);return;}
        if (dynamic_cast<Commaopt*>(n) ){ endVisit((Commaopt*) n);return;}
        if (dynamic_cast<Ellipsisopt*>(n) ){ endVisit((Ellipsisopt*) n);return;}
        if (dynamic_cast<LPGUserAction0*>(n) ){ endVisit((LPGUserAction0*) n);return;}
        if (dynamic_cast<LPGUserAction1*>(n) ){ endVisit((LPGUserAction1*) n);return;}
        if (dynamic_cast<LPGUserAction2*>(n) ){ endVisit((LPGUserAction2*) n);return;}
        if (dynamic_cast<LPGUserAction3*>(n) ){ endVisit((LPGUserAction3*) n);return;}
        if (dynamic_cast<LPGUserAction4*>(n) ){ endVisit((LPGUserAction4*) n);return;}
        if (dynamic_cast<IntegralType0*>(n) ){ endVisit((IntegralType0*) n);return;}
        if (dynamic_cast<IntegralType1*>(n) ){ endVisit((IntegralType1*) n);return;}
        if (dynamic_cast<IntegralType2*>(n) ){ endVisit((IntegralType2*) n);return;}
        if (dynamic_cast<IntegralType3*>(n) ){ endVisit((IntegralType3*) n);return;}
        if (dynamic_cast<IntegralType4*>(n) ){ endVisit((IntegralType4*) n);return;}
        if (dynamic_cast<FloatingPointType0*>(n) ){ endVisit((FloatingPointType0*) n);return;}
        if (dynamic_cast<FloatingPointType1*>(n) ){ endVisit((FloatingPointType1*) n);return;}
        if (dynamic_cast<WildcardBounds0*>(n) ){ endVisit((WildcardBounds0*) n);return;}
        if (dynamic_cast<WildcardBounds1*>(n) ){ endVisit((WildcardBounds1*) n);return;}
        if (dynamic_cast<ClassModifier0*>(n) ){ endVisit((ClassModifier0*) n);return;}
        if (dynamic_cast<ClassModifier1*>(n) ){ endVisit((ClassModifier1*) n);return;}
        if (dynamic_cast<ClassModifier2*>(n) ){ endVisit((ClassModifier2*) n);return;}
        if (dynamic_cast<ClassModifier3*>(n) ){ endVisit((ClassModifier3*) n);return;}
        if (dynamic_cast<ClassModifier4*>(n) ){ endVisit((ClassModifier4*) n);return;}
        if (dynamic_cast<ClassModifier5*>(n) ){ endVisit((ClassModifier5*) n);return;}
        if (dynamic_cast<ClassModifier6*>(n) ){ endVisit((ClassModifier6*) n);return;}
        if (dynamic_cast<FieldModifier0*>(n) ){ endVisit((FieldModifier0*) n);return;}
        if (dynamic_cast<FieldModifier1*>(n) ){ endVisit((FieldModifier1*) n);return;}
        if (dynamic_cast<FieldModifier2*>(n) ){ endVisit((FieldModifier2*) n);return;}
        if (dynamic_cast<FieldModifier3*>(n) ){ endVisit((FieldModifier3*) n);return;}
        if (dynamic_cast<FieldModifier4*>(n) ){ endVisit((FieldModifier4*) n);return;}
        if (dynamic_cast<FieldModifier5*>(n) ){ endVisit((FieldModifier5*) n);return;}
        if (dynamic_cast<FieldModifier6*>(n) ){ endVisit((FieldModifier6*) n);return;}
        if (dynamic_cast<MethodDeclarator0*>(n) ){ endVisit((MethodDeclarator0*) n);return;}
        if (dynamic_cast<MethodDeclarator1*>(n) ){ endVisit((MethodDeclarator1*) n);return;}
        if (dynamic_cast<MethodModifier0*>(n) ){ endVisit((MethodModifier0*) n);return;}
        if (dynamic_cast<MethodModifier1*>(n) ){ endVisit((MethodModifier1*) n);return;}
        if (dynamic_cast<MethodModifier2*>(n) ){ endVisit((MethodModifier2*) n);return;}
        if (dynamic_cast<MethodModifier3*>(n) ){ endVisit((MethodModifier3*) n);return;}
        if (dynamic_cast<MethodModifier4*>(n) ){ endVisit((MethodModifier4*) n);return;}
        if (dynamic_cast<MethodModifier5*>(n) ){ endVisit((MethodModifier5*) n);return;}
        if (dynamic_cast<MethodModifier6*>(n) ){ endVisit((MethodModifier6*) n);return;}
        if (dynamic_cast<MethodModifier7*>(n) ){ endVisit((MethodModifier7*) n);return;}
        if (dynamic_cast<MethodModifier8*>(n) ){ endVisit((MethodModifier8*) n);return;}
        if (dynamic_cast<ConstructorModifier0*>(n) ){ endVisit((ConstructorModifier0*) n);return;}
        if (dynamic_cast<ConstructorModifier1*>(n) ){ endVisit((ConstructorModifier1*) n);return;}
        if (dynamic_cast<ConstructorModifier2*>(n) ){ endVisit((ConstructorModifier2*) n);return;}
        if (dynamic_cast<ExplicitConstructorInvocation0*>(n) ){ endVisit((ExplicitConstructorInvocation0*) n);return;}
        if (dynamic_cast<ExplicitConstructorInvocation1*>(n) ){ endVisit((ExplicitConstructorInvocation1*) n);return;}
        if (dynamic_cast<ExplicitConstructorInvocation2*>(n) ){ endVisit((ExplicitConstructorInvocation2*) n);return;}
        if (dynamic_cast<InterfaceModifier0*>(n) ){ endVisit((InterfaceModifier0*) n);return;}
        if (dynamic_cast<InterfaceModifier1*>(n) ){ endVisit((InterfaceModifier1*) n);return;}
        if (dynamic_cast<InterfaceModifier2*>(n) ){ endVisit((InterfaceModifier2*) n);return;}
        if (dynamic_cast<InterfaceModifier3*>(n) ){ endVisit((InterfaceModifier3*) n);return;}
        if (dynamic_cast<InterfaceModifier4*>(n) ){ endVisit((InterfaceModifier4*) n);return;}
        if (dynamic_cast<InterfaceModifier5*>(n) ){ endVisit((InterfaceModifier5*) n);return;}
        if (dynamic_cast<ExtendsInterfaces0*>(n) ){ endVisit((ExtendsInterfaces0*) n);return;}
        if (dynamic_cast<ExtendsInterfaces1*>(n) ){ endVisit((ExtendsInterfaces1*) n);return;}
        if (dynamic_cast<ConstantModifier0*>(n) ){ endVisit((ConstantModifier0*) n);return;}
        if (dynamic_cast<ConstantModifier1*>(n) ){ endVisit((ConstantModifier1*) n);return;}
        if (dynamic_cast<ConstantModifier2*>(n) ){ endVisit((ConstantModifier2*) n);return;}
        if (dynamic_cast<AbstractMethodModifier0*>(n) ){ endVisit((AbstractMethodModifier0*) n);return;}
        if (dynamic_cast<AbstractMethodModifier1*>(n) ){ endVisit((AbstractMethodModifier1*) n);return;}
        if (dynamic_cast<AnnotationTypeElementDeclaration0*>(n) ){ endVisit((AnnotationTypeElementDeclaration0*) n);return;}
        if (dynamic_cast<AnnotationTypeElementDeclaration1*>(n) ){ endVisit((AnnotationTypeElementDeclaration1*) n);return;}
        if (dynamic_cast<AssertStatement0*>(n) ){ endVisit((AssertStatement0*) n);return;}
        if (dynamic_cast<AssertStatement1*>(n) ){ endVisit((AssertStatement1*) n);return;}
        if (dynamic_cast<SwitchLabel0*>(n) ){ endVisit((SwitchLabel0*) n);return;}
        if (dynamic_cast<SwitchLabel1*>(n) ){ endVisit((SwitchLabel1*) n);return;}
        if (dynamic_cast<SwitchLabel2*>(n) ){ endVisit((SwitchLabel2*) n);return;}
        if (dynamic_cast<TryStatement0*>(n) ){ endVisit((TryStatement0*) n);return;}
        if (dynamic_cast<TryStatement1*>(n) ){ endVisit((TryStatement1*) n);return;}
        if (dynamic_cast<PrimaryNoNewArray0*>(n) ){ endVisit((PrimaryNoNewArray0*) n);return;}
        if (dynamic_cast<PrimaryNoNewArray1*>(n) ){ endVisit((PrimaryNoNewArray1*) n);return;}
        if (dynamic_cast<PrimaryNoNewArray2*>(n) ){ endVisit((PrimaryNoNewArray2*) n);return;}
        if (dynamic_cast<PrimaryNoNewArray3*>(n) ){ endVisit((PrimaryNoNewArray3*) n);return;}
        if (dynamic_cast<PrimaryNoNewArray4*>(n) ){ endVisit((PrimaryNoNewArray4*) n);return;}
        if (dynamic_cast<Literal0*>(n) ){ endVisit((Literal0*) n);return;}
        if (dynamic_cast<Literal1*>(n) ){ endVisit((Literal1*) n);return;}
        if (dynamic_cast<Literal2*>(n) ){ endVisit((Literal2*) n);return;}
        if (dynamic_cast<Literal3*>(n) ){ endVisit((Literal3*) n);return;}
        if (dynamic_cast<Literal4*>(n) ){ endVisit((Literal4*) n);return;}
        if (dynamic_cast<Literal5*>(n) ){ endVisit((Literal5*) n);return;}
        if (dynamic_cast<Literal6*>(n) ){ endVisit((Literal6*) n);return;}
        if (dynamic_cast<BooleanLiteral0*>(n) ){ endVisit((BooleanLiteral0*) n);return;}
        if (dynamic_cast<BooleanLiteral1*>(n) ){ endVisit((BooleanLiteral1*) n);return;}
        if (dynamic_cast<ClassInstanceCreationExpression0*>(n) ){ endVisit((ClassInstanceCreationExpression0*) n);return;}
        if (dynamic_cast<ClassInstanceCreationExpression1*>(n) ){ endVisit((ClassInstanceCreationExpression1*) n);return;}
        if (dynamic_cast<ArrayCreationExpression0*>(n) ){ endVisit((ArrayCreationExpression0*) n);return;}
        if (dynamic_cast<ArrayCreationExpression1*>(n) ){ endVisit((ArrayCreationExpression1*) n);return;}
        if (dynamic_cast<ArrayCreationExpression2*>(n) ){ endVisit((ArrayCreationExpression2*) n);return;}
        if (dynamic_cast<ArrayCreationExpression3*>(n) ){ endVisit((ArrayCreationExpression3*) n);return;}
        if (dynamic_cast<Dims0*>(n) ){ endVisit((Dims0*) n);return;}
        if (dynamic_cast<Dims1*>(n) ){ endVisit((Dims1*) n);return;}
        if (dynamic_cast<FieldAccess0*>(n) ){ endVisit((FieldAccess0*) n);return;}
        if (dynamic_cast<FieldAccess1*>(n) ){ endVisit((FieldAccess1*) n);return;}
        if (dynamic_cast<FieldAccess2*>(n) ){ endVisit((FieldAccess2*) n);return;}
        if (dynamic_cast<MethodInvocation0*>(n) ){ endVisit((MethodInvocation0*) n);return;}
        if (dynamic_cast<MethodInvocation1*>(n) ){ endVisit((MethodInvocation1*) n);return;}
        if (dynamic_cast<MethodInvocation2*>(n) ){ endVisit((MethodInvocation2*) n);return;}
        if (dynamic_cast<MethodInvocation3*>(n) ){ endVisit((MethodInvocation3*) n);return;}
        if (dynamic_cast<MethodInvocation4*>(n) ){ endVisit((MethodInvocation4*) n);return;}
        if (dynamic_cast<ArrayAccess0*>(n) ){ endVisit((ArrayAccess0*) n);return;}
        if (dynamic_cast<ArrayAccess1*>(n) ){ endVisit((ArrayAccess1*) n);return;}
        if (dynamic_cast<UnaryExpression0*>(n) ){ endVisit((UnaryExpression0*) n);return;}
        if (dynamic_cast<UnaryExpression1*>(n) ){ endVisit((UnaryExpression1*) n);return;}
        if (dynamic_cast<UnaryExpressionNotPlusMinus0*>(n) ){ endVisit((UnaryExpressionNotPlusMinus0*) n);return;}
        if (dynamic_cast<UnaryExpressionNotPlusMinus1*>(n) ){ endVisit((UnaryExpressionNotPlusMinus1*) n);return;}
        if (dynamic_cast<CastExpression0*>(n) ){ endVisit((CastExpression0*) n);return;}
        if (dynamic_cast<CastExpression1*>(n) ){ endVisit((CastExpression1*) n);return;}
        if (dynamic_cast<MultiplicativeExpression0*>(n) ){ endVisit((MultiplicativeExpression0*) n);return;}
        if (dynamic_cast<MultiplicativeExpression1*>(n) ){ endVisit((MultiplicativeExpression1*) n);return;}
        if (dynamic_cast<MultiplicativeExpression2*>(n) ){ endVisit((MultiplicativeExpression2*) n);return;}
        if (dynamic_cast<AdditiveExpression0*>(n) ){ endVisit((AdditiveExpression0*) n);return;}
        if (dynamic_cast<AdditiveExpression1*>(n) ){ endVisit((AdditiveExpression1*) n);return;}
        if (dynamic_cast<ShiftExpression0*>(n) ){ endVisit((ShiftExpression0*) n);return;}
        if (dynamic_cast<ShiftExpression1*>(n) ){ endVisit((ShiftExpression1*) n);return;}
        if (dynamic_cast<ShiftExpression2*>(n) ){ endVisit((ShiftExpression2*) n);return;}
        if (dynamic_cast<RelationalExpression0*>(n) ){ endVisit((RelationalExpression0*) n);return;}
        if (dynamic_cast<RelationalExpression1*>(n) ){ endVisit((RelationalExpression1*) n);return;}
        if (dynamic_cast<RelationalExpression2*>(n) ){ endVisit((RelationalExpression2*) n);return;}
        if (dynamic_cast<RelationalExpression3*>(n) ){ endVisit((RelationalExpression3*) n);return;}
        if (dynamic_cast<RelationalExpression4*>(n) ){ endVisit((RelationalExpression4*) n);return;}
        if (dynamic_cast<EqualityExpression0*>(n) ){ endVisit((EqualityExpression0*) n);return;}
        if (dynamic_cast<EqualityExpression1*>(n) ){ endVisit((EqualityExpression1*) n);return;}
        if (dynamic_cast<AssignmentOperator0*>(n) ){ endVisit((AssignmentOperator0*) n);return;}
        if (dynamic_cast<AssignmentOperator1*>(n) ){ endVisit((AssignmentOperator1*) n);return;}
        if (dynamic_cast<AssignmentOperator2*>(n) ){ endVisit((AssignmentOperator2*) n);return;}
        if (dynamic_cast<AssignmentOperator3*>(n) ){ endVisit((AssignmentOperator3*) n);return;}
        if (dynamic_cast<AssignmentOperator4*>(n) ){ endVisit((AssignmentOperator4*) n);return;}
        if (dynamic_cast<AssignmentOperator5*>(n) ){ endVisit((AssignmentOperator5*) n);return;}
        if (dynamic_cast<AssignmentOperator6*>(n) ){ endVisit((AssignmentOperator6*) n);return;}
        if (dynamic_cast<AssignmentOperator7*>(n) ){ endVisit((AssignmentOperator7*) n);return;}
        if (dynamic_cast<AssignmentOperator8*>(n) ){ endVisit((AssignmentOperator8*) n);return;}
        if (dynamic_cast<AssignmentOperator9*>(n) ){ endVisit((AssignmentOperator9*) n);return;}
        if (dynamic_cast<AssignmentOperator10*>(n) ){ endVisit((AssignmentOperator10*) n);return;}
        if (dynamic_cast<AssignmentOperator11*>(n) ){ endVisit((AssignmentOperator11*) n);return;}
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
};

};
