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


    //#line 169 "btParserTemplateF.gi
 
#include "JavaParser.h"

#include "JavaParser_top_level_ast.h"
ParseTable* JavaParser::prsTable = new JavaParserprs();

    //#line 364 "btParserTemplateF.gi

   
     void JavaParser::ruleAction(int ruleNumber)
    {
        switch (ruleNumber)
        {
using namespace JavaParser_top_level_ast;

            //
            // Rule 3:  identifier ::= IDENTIFIER
            //
            case 3: {
               //#line 184 "GJavaParser.g"
                setResult(
                    //#line 184 GJavaParser.g
                     _automatic_ast_pool << new identifier(this, getRhsIToken(1))
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
                     _automatic_ast_pool << new LPGUserAction0(getLeftIToken(), getRightIToken(),
                                       //#line 194 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                       //#line 194 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 194 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new LPGUserAction1(getLeftIToken(), getRightIToken(),
                                       //#line 195 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                       //#line 195 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 195 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new LPGUserAction2(getRhsIToken(1))
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
                     _automatic_ast_pool << new LPGUserAction3(getRhsIToken(1))
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
                     _automatic_ast_pool << new LPGUserAction4(getRhsIToken(1))
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
                     _automatic_ast_pool << new PrimitiveType(getRhsIToken(1))
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
                     _automatic_ast_pool << new IntegralType0(getRhsIToken(1))
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
                     _automatic_ast_pool << new IntegralType1(getRhsIToken(1))
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
                     _automatic_ast_pool << new IntegralType2(getRhsIToken(1))
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
                     _automatic_ast_pool << new IntegralType3(getRhsIToken(1))
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
                     _automatic_ast_pool << new IntegralType4(getRhsIToken(1))
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
                     _automatic_ast_pool << new FloatingPointType0(getRhsIToken(1))
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
                     _automatic_ast_pool << new FloatingPointType1(getRhsIToken(1))
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
                     _automatic_ast_pool << new ClassType(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new InterfaceType(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new TypeName(getLeftIToken(), getRightIToken(),
                                 //#line 236 GJavaParser.g
                                 (IAst*)getRhsSym(1),
                                 //#line 236 GJavaParser.g
                                  _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ArrayType(getLeftIToken(), getRightIToken(),
                                  //#line 242 GJavaParser.g
                                  (IAst*)getRhsSym(1),
                                  //#line 242 GJavaParser.g
                                   _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                  //#line 242 GJavaParser.g
                                   _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new TypeParameter(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new TypeBound(getLeftIToken(), getRightIToken(),
                                  //#line 246 GJavaParser.g
                                   _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new AdditionalBoundList(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new AdditionalBound(getLeftIToken(), getRightIToken(),
                                        //#line 251 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new TypeArguments(getLeftIToken(), getRightIToken(),
                                      //#line 253 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                      //#line 253 GJavaParser.g
                                      (IAst*)getRhsSym(2),
                                      //#line 253 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new ActualTypeArgumentList(getLeftIToken(), getRightIToken(),
                                               //#line 256 GJavaParser.g
                                               (IAst*)getRhsSym(1),
                                               //#line 256 GJavaParser.g
                                                _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new Wildcard(getLeftIToken(), getRightIToken(),
                                 //#line 261 GJavaParser.g
                                  _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new WildcardBounds0(getLeftIToken(), getRightIToken(),
                                        //#line 263 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new WildcardBounds1(getLeftIToken(), getRightIToken(),
                                        //#line 264 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new PackageName(getLeftIToken(), getRightIToken(),
                                    //#line 271 GJavaParser.g
                                    (IAst*)getRhsSym(1),
                                    //#line 271 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ExpressionName(getLeftIToken(), getRightIToken(),
                                       //#line 280 GJavaParser.g
                                       (IAst*)getRhsSym(1),
                                       //#line 280 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new MethodName(getLeftIToken(), getRightIToken(),
                                   //#line 283 GJavaParser.g
                                   (IAst*)getRhsSym(1),
                                   //#line 283 GJavaParser.g
                                    _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new PackageOrTypeName(getLeftIToken(), getRightIToken(),
                                          //#line 286 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 286 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new AmbiguousName(getLeftIToken(), getRightIToken(),
                                      //#line 289 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 289 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new CompilationUnit(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new ImportDeclarations(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new TypeDeclarations(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new PackageDeclaration(getLeftIToken(), getRightIToken(),
                                           //#line 301 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 301 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                           //#line 301 GJavaParser.g
                                           (IAst*)getRhsSym(3),
                                           //#line 301 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new SingleTypeImportDeclaration(getLeftIToken(), getRightIToken(),
                                                    //#line 308 GJavaParser.g
                                                     _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                                    //#line 308 GJavaParser.g
                                                    (IAst*)getRhsSym(2),
                                                    //#line 308 GJavaParser.g
                                                     _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new TypeImportOnDemandDeclaration(getLeftIToken(), getRightIToken(),
                                                      //#line 310 GJavaParser.g
                                                       _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                                      //#line 310 GJavaParser.g
                                                      (IAst*)getRhsSym(2),
                                                      //#line 310 GJavaParser.g
                                                       _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                                      //#line 310 GJavaParser.g
                                                       _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                                      //#line 310 GJavaParser.g
                                                       _automatic_ast_pool << new AstToken(getRhsIToken(5)))
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
                     _automatic_ast_pool << new SingleStaticImportDeclaration(getLeftIToken(), getRightIToken(),
                                                      //#line 312 GJavaParser.g
                                                       _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                                      //#line 312 GJavaParser.g
                                                       _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                                      //#line 312 GJavaParser.g
                                                      (IAst*)getRhsSym(3),
                                                      //#line 312 GJavaParser.g
                                                       _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                                      //#line 312 GJavaParser.g
                                                      (IAst*)getRhsSym(5),
                                                      //#line 312 GJavaParser.g
                                                       _automatic_ast_pool << new AstToken(getRhsIToken(6)))
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
                     _automatic_ast_pool << new StaticImportOnDemandDeclaration(getLeftIToken(), getRightIToken(),
                                                        //#line 314 GJavaParser.g
                                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                                        //#line 314 GJavaParser.g
                                                         _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                                        //#line 314 GJavaParser.g
                                                        (IAst*)getRhsSym(3),
                                                        //#line 314 GJavaParser.g
                                                         _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                                        //#line 314 GJavaParser.g
                                                         _automatic_ast_pool << new AstToken(getRhsIToken(5)),
                                                        //#line 314 GJavaParser.g
                                                         _automatic_ast_pool << new AstToken(getRhsIToken(6)))
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
                     _automatic_ast_pool << new TypeDeclaration(getRhsIToken(1))
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
                     _automatic_ast_pool << new NormalClassDeclaration(getLeftIToken(), getRightIToken(),
                                               //#line 325 GJavaParser.g
                                               (IAst*)getRhsSym(1),
                                               //#line 325 GJavaParser.g
                                                _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ClassModifiers(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new ClassModifier0(getRhsIToken(1))
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
                     _automatic_ast_pool << new ClassModifier1(getRhsIToken(1))
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
                     _automatic_ast_pool << new ClassModifier2(getRhsIToken(1))
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
                     _automatic_ast_pool << new ClassModifier3(getRhsIToken(1))
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
                     _automatic_ast_pool << new ClassModifier4(getRhsIToken(1))
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
                     _automatic_ast_pool << new ClassModifier5(getRhsIToken(1))
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
                     _automatic_ast_pool << new ClassModifier6(getRhsIToken(1))
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
                     _automatic_ast_pool << new TypeParameters(getLeftIToken(), getRightIToken(),
                                       //#line 339 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                       //#line 339 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 339 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new TypeParameterList(getLeftIToken(), getRightIToken(),
                                          //#line 342 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 342 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new Super(getLeftIToken(), getRightIToken(),
                              //#line 344 GJavaParser.g
                               _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new Interfaces(getLeftIToken(), getRightIToken(),
                                   //#line 351 GJavaParser.g
                                    _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new InterfaceTypeList(getLeftIToken(), getRightIToken(),
                                          //#line 354 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 354 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ClassBody(getLeftIToken(), getRightIToken(),
                                  //#line 361 GJavaParser.g
                                   _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                  //#line 361 GJavaParser.g
                                  (IAst*)getRhsSym(2),
                                  //#line 361 GJavaParser.g
                                   _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new ClassBodyDeclarations(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new ClassMemberDeclaration(getRhsIToken(1))
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
                     _automatic_ast_pool << new FieldDeclaration(getLeftIToken(), getRightIToken(),
                                         //#line 377 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 377 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 377 GJavaParser.g
                                         (IAst*)getRhsSym(3),
                                         //#line 377 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new VariableDeclarators(getLeftIToken(), getRightIToken(),
                                            //#line 380 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 380 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new VariableDeclarator(getLeftIToken(), getRightIToken(),
                                           //#line 383 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 383 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new VariableDeclaratorId(getLeftIToken(), getRightIToken(),
                                             //#line 386 GJavaParser.g
                                             (IAst*)getRhsSym(1),
                                             //#line 386 GJavaParser.g
                                              _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                             //#line 386 GJavaParser.g
                                              _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new FieldModifiers(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new FieldModifier0(getRhsIToken(1))
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
                     _automatic_ast_pool << new FieldModifier1(getRhsIToken(1))
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
                     _automatic_ast_pool << new FieldModifier2(getRhsIToken(1))
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
                     _automatic_ast_pool << new FieldModifier3(getRhsIToken(1))
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
                     _automatic_ast_pool << new FieldModifier4(getRhsIToken(1))
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
                     _automatic_ast_pool << new FieldModifier5(getRhsIToken(1))
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
                     _automatic_ast_pool << new FieldModifier6(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodDeclaration(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new MethodHeader(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new ResultType(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodDeclarator0(getLeftIToken(), getRightIToken(),
                                          //#line 410 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 410 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                          //#line 410 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 410 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new MethodDeclarator1(getLeftIToken(), getRightIToken(),
                                          //#line 412 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 412 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                          //#line 412 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new FormalParameterList(getLeftIToken(), getRightIToken(),
                                            //#line 415 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 415 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new FormalParameters(getLeftIToken(), getRightIToken(),
                                         //#line 418 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 418 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new FormalParameter(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new VariableModifiers(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new VariableModifier(getRhsIToken(1))
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
                     _automatic_ast_pool << new LastFormalParameter(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new MethodModifiers(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new MethodModifier0(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodModifier1(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodModifier2(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodModifier3(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodModifier4(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodModifier5(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodModifier6(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodModifier7(getRhsIToken(1))
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
                     _automatic_ast_pool << new MethodModifier8(getRhsIToken(1))
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
                     _automatic_ast_pool << new Throws(getLeftIToken(), getRightIToken(),
                               //#line 450 GJavaParser.g
                                _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new ExceptionTypeList(getLeftIToken(), getRightIToken(),
                                          //#line 453 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 453 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new MethodBody(getRhsIToken(1))
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
                     _automatic_ast_pool << new StaticInitializer(getLeftIToken(), getRightIToken(),
                                          //#line 463 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new ConstructorDeclaration(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new ConstructorDeclarator(getLeftIToken(), getRightIToken(),
                                              //#line 467 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 467 GJavaParser.g
                                              (IAst*)getRhsSym(2),
                                              //#line 467 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                              //#line 467 GJavaParser.g
                                              (IAst*)getRhsSym(4),
                                              //#line 467 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(5)))
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
                     _automatic_ast_pool << new ConstructorModifiers(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new ConstructorModifier0(getRhsIToken(1))
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
                     _automatic_ast_pool << new ConstructorModifier1(getRhsIToken(1))
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
                     _automatic_ast_pool << new ConstructorModifier2(getRhsIToken(1))
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
                     _automatic_ast_pool << new ConstructorBody(getLeftIToken(), getRightIToken(),
                                        //#line 479 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                        //#line 479 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 479 GJavaParser.g
                                        (IAst*)getRhsSym(3),
                                        //#line 479 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new ExplicitConstructorInvocation0(getLeftIToken(), getRightIToken(),
                                                       //#line 481 GJavaParser.g
                                                       (IAst*)getRhsSym(1),
                                                       //#line 481 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                                       //#line 481 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                                       //#line 481 GJavaParser.g
                                                       (IAst*)getRhsSym(4),
                                                       //#line 481 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(5)),
                                                       //#line 481 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(6)))
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
                     _automatic_ast_pool << new ExplicitConstructorInvocation1(getLeftIToken(), getRightIToken(),
                                                       //#line 482 GJavaParser.g
                                                       (IAst*)getRhsSym(1),
                                                       //#line 482 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                                       //#line 482 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                                       //#line 482 GJavaParser.g
                                                       (IAst*)getRhsSym(4),
                                                       //#line 482 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(5)),
                                                       //#line 482 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(6)))
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
                     _automatic_ast_pool << new ExplicitConstructorInvocation2(getLeftIToken(), getRightIToken(),
                                                       //#line 483 GJavaParser.g
                                                       (IAst*)getRhsSym(1),
                                                       //#line 483 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                                       //#line 483 GJavaParser.g
                                                       (IAst*)getRhsSym(3),
                                                       //#line 483 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                                       //#line 483 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(5)),
                                                       //#line 483 GJavaParser.g
                                                       (IAst*)getRhsSym(6),
                                                       //#line 483 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(7)),
                                                       //#line 483 GJavaParser.g
                                                        _automatic_ast_pool << new AstToken(getRhsIToken(8)))
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
                     _automatic_ast_pool << new EnumDeclaration(getLeftIToken(), getRightIToken(),
                                        //#line 485 GJavaParser.g
                                        (IAst*)getRhsSym(1),
                                        //#line 485 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new EnumBody(getLeftIToken(), getRightIToken(),
                                 //#line 487 GJavaParser.g
                                  _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                 //#line 487 GJavaParser.g
                                 (IAst*)getRhsSym(2),
                                 //#line 487 GJavaParser.g
                                 (IAst*)getRhsSym(3),
                                 //#line 487 GJavaParser.g
                                 (IAst*)getRhsSym(4),
                                 //#line 487 GJavaParser.g
                                  _automatic_ast_pool << new AstToken(getRhsIToken(5)))
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
                     _automatic_ast_pool << new EnumConstants(getLeftIToken(), getRightIToken(),
                                      //#line 490 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 490 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new EnumConstant(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new Arguments(getLeftIToken(), getRightIToken(),
                                  //#line 494 GJavaParser.g
                                   _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                  //#line 494 GJavaParser.g
                                  (IAst*)getRhsSym(2),
                                  //#line 494 GJavaParser.g
                                   _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new EnumBodyDeclarations(getLeftIToken(), getRightIToken(),
                                             //#line 496 GJavaParser.g
                                              _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new NormalInterfaceDeclaration(getLeftIToken(), getRightIToken(),
                                                   //#line 503 GJavaParser.g
                                                   (IAst*)getRhsSym(1),
                                                   //#line 503 GJavaParser.g
                                                    _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new InterfaceModifiers(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new InterfaceModifier0(getRhsIToken(1))
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
                     _automatic_ast_pool << new InterfaceModifier1(getRhsIToken(1))
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
                     _automatic_ast_pool << new InterfaceModifier2(getRhsIToken(1))
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
                     _automatic_ast_pool << new InterfaceModifier3(getRhsIToken(1))
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
                     _automatic_ast_pool << new InterfaceModifier4(getRhsIToken(1))
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
                     _automatic_ast_pool << new InterfaceModifier5(getRhsIToken(1))
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
                     _automatic_ast_pool << new ExtendsInterfaces0(getLeftIToken(), getRightIToken(),
                                           //#line 516 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new ExtendsInterfaces1(getLeftIToken(), getRightIToken(),
                                           //#line 517 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 517 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new InterfaceBody(getLeftIToken(), getRightIToken(),
                                      //#line 524 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                      //#line 524 GJavaParser.g
                                      (IAst*)getRhsSym(2),
                                      //#line 524 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new InterfaceMemberDeclarations(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new InterfaceMemberDeclaration(getRhsIToken(1))
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
                     _automatic_ast_pool << new ConstantDeclaration(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new ConstantModifiers(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new ConstantModifier0(getRhsIToken(1))
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
                     _automatic_ast_pool << new ConstantModifier1(getRhsIToken(1))
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
                     _automatic_ast_pool << new ConstantModifier2(getRhsIToken(1))
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
                     _automatic_ast_pool << new AbstractMethodDeclaration(getLeftIToken(), getRightIToken(),
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
                                                   _automatic_ast_pool << new AstToken(getRhsIToken(6)))
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
                     _automatic_ast_pool << new AbstractMethodModifiers(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new AbstractMethodModifier0(getRhsIToken(1))
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
                     _automatic_ast_pool << new AbstractMethodModifier1(getRhsIToken(1))
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
                     _automatic_ast_pool << new AnnotationTypeDeclaration(getLeftIToken(), getRightIToken(),
                                                  //#line 554 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 554 GJavaParser.g
                                                   _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                                  //#line 554 GJavaParser.g
                                                   _automatic_ast_pool << new AstToken(getRhsIToken(3)),
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
                     _automatic_ast_pool << new AnnotationTypeBody(getLeftIToken(), getRightIToken(),
                                           //#line 556 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                           //#line 556 GJavaParser.g
                                           (IAst*)getRhsSym(2),
                                           //#line 556 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new AnnotationTypeElementDeclarations(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new AnnotationTypeElementDeclaration0(getLeftIToken(), getRightIToken(),
                                                          //#line 561 GJavaParser.g
                                                          (IAst*)getRhsSym(1),
                                                          //#line 561 GJavaParser.g
                                                          (IAst*)getRhsSym(2),
                                                          //#line 561 GJavaParser.g
                                                          (IAst*)getRhsSym(3),
                                                          //#line 561 GJavaParser.g
                                                           _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                                          //#line 561 GJavaParser.g
                                                           _automatic_ast_pool << new AstToken(getRhsIToken(5)),
                                                          //#line 561 GJavaParser.g
                                                          (IAst*)getRhsSym(6),
                                                          //#line 561 GJavaParser.g
                                                           _automatic_ast_pool << new AstToken(getRhsIToken(7)))
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
                     _automatic_ast_pool << new AnnotationTypeElementDeclaration1(getRhsIToken(1))
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
                     _automatic_ast_pool << new DefaultValue(getLeftIToken(), getRightIToken(),
                                     //#line 569 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new Annotations(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new NormalAnnotation(getLeftIToken(), getRightIToken(),
                                         //#line 578 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                         //#line 578 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 578 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                         //#line 578 GJavaParser.g
                                         (IAst*)getRhsSym(4),
                                         //#line 578 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(5)))
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
                     _automatic_ast_pool << new ElementValuePairs(getLeftIToken(), getRightIToken(),
                                          //#line 581 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 581 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ElementValuePair(getLeftIToken(), getRightIToken(),
                                         //#line 583 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 583 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ElementValueArrayInitializer(getLeftIToken(), getRightIToken(),
                                                     //#line 591 GJavaParser.g
                                                      _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                                     //#line 591 GJavaParser.g
                                                     (IAst*)getRhsSym(2),
                                                     //#line 591 GJavaParser.g
                                                     (IAst*)getRhsSym(3),
                                                     //#line 591 GJavaParser.g
                                                      _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new ElementValues(getLeftIToken(), getRightIToken(),
                                      //#line 594 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 594 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new MarkerAnnotation(getLeftIToken(), getRightIToken(),
                                         //#line 596 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new SingleElementAnnotation(getLeftIToken(), getRightIToken(),
                                                //#line 598 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                                //#line 598 GJavaParser.g
                                                (IAst*)getRhsSym(2),
                                                //#line 598 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                                //#line 598 GJavaParser.g
                                                (IAst*)getRhsSym(4),
                                                //#line 598 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(5)))
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
                     _automatic_ast_pool << new ArrayInitializer(getLeftIToken(), getRightIToken(),
                                         //#line 602 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                         //#line 602 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 602 GJavaParser.g
                                         (IAst*)getRhsSym(3),
                                         //#line 602 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new VariableInitializers(getLeftIToken(), getRightIToken(),
                                             //#line 605 GJavaParser.g
                                             (IAst*)getRhsSym(1),
                                             //#line 605 GJavaParser.g
                                              _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new Block(getLeftIToken(), getRightIToken(),
                              //#line 621 GJavaParser.g
                               _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                              //#line 621 GJavaParser.g
                              (IAst*)getRhsSym(2),
                              //#line 621 GJavaParser.g
                               _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new BlockStatements(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new LocalVariableDeclarationStatement(getLeftIToken(), getRightIToken(),
                                                          //#line 630 GJavaParser.g
                                                          (IAst*)getRhsSym(1),
                                                          //#line 630 GJavaParser.g
                                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)))
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
                     _automatic_ast_pool << new LocalVariableDeclaration(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new IfThenStatement(getLeftIToken(), getRightIToken(),
                                        //#line 675 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                        //#line 675 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                        //#line 675 GJavaParser.g
                                        (IAst*)getRhsSym(3),
                                        //#line 675 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new IfThenElseStatement(getLeftIToken(), getRightIToken(),
                                            //#line 677 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                            //#line 677 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                            //#line 677 GJavaParser.g
                                            (IAst*)getRhsSym(3),
                                            //#line 677 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                            //#line 677 GJavaParser.g
                                            (IAst*)getRhsSym(5),
                                            //#line 677 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(6)),
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
                     _automatic_ast_pool << new IfThenElseStatementNoShortIf(getLeftIToken(), getRightIToken(),
                                                     //#line 679 GJavaParser.g
                                                      _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                                     //#line 679 GJavaParser.g
                                                      _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                                     //#line 679 GJavaParser.g
                                                     (IAst*)getRhsSym(3),
                                                     //#line 679 GJavaParser.g
                                                      _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                                     //#line 679 GJavaParser.g
                                                     (IAst*)getRhsSym(5),
                                                     //#line 679 GJavaParser.g
                                                      _automatic_ast_pool << new AstToken(getRhsIToken(6)),
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
                     _automatic_ast_pool << new EmptyStatement(getRhsIToken(1))
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
                     _automatic_ast_pool << new LabeledStatement(getLeftIToken(), getRightIToken(),
                                         //#line 683 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 683 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new LabeledStatementNoShortIf(getLeftIToken(), getRightIToken(),
                                                  //#line 685 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 685 GJavaParser.g
                                                   _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ExpressionStatement(getLeftIToken(), getRightIToken(),
                                            //#line 687 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 687 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)))
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
                     _automatic_ast_pool << new AssertStatement0(getLeftIToken(), getRightIToken(),
                                         //#line 706 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                         //#line 706 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 706 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new AssertStatement1(getLeftIToken(), getRightIToken(),
                                         //#line 707 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                         //#line 707 GJavaParser.g
                                         (IAst*)getRhsSym(2),
                                         //#line 707 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                         //#line 707 GJavaParser.g
                                         (IAst*)getRhsSym(4),
                                         //#line 707 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(5)))
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
                     _automatic_ast_pool << new SwitchStatement(getLeftIToken(), getRightIToken(),
                                        //#line 709 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                        //#line 709 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                        //#line 709 GJavaParser.g
                                        (IAst*)getRhsSym(3),
                                        //#line 709 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new SwitchBlock(getLeftIToken(), getRightIToken(),
                                    //#line 711 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                    //#line 711 GJavaParser.g
                                    (IAst*)getRhsSym(2),
                                    //#line 711 GJavaParser.g
                                    (IAst*)getRhsSym(3),
                                    //#line 711 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new SwitchBlockStatementGroups(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new SwitchBlockStatementGroup(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new SwitchLabels(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new SwitchLabel0(getLeftIToken(), getRightIToken(),
                                     //#line 721 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                     //#line 721 GJavaParser.g
                                     (IAst*)getRhsSym(2),
                                     //#line 721 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new SwitchLabel1(getLeftIToken(), getRightIToken(),
                                     //#line 722 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                     //#line 722 GJavaParser.g
                                     (IAst*)getRhsSym(2),
                                     //#line 722 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new SwitchLabel2(getLeftIToken(), getRightIToken(),
                                     //#line 723 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                     //#line 723 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(2)))
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
                     _automatic_ast_pool << new WhileStatement(getLeftIToken(), getRightIToken(),
                                       //#line 727 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                       //#line 727 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                       //#line 727 GJavaParser.g
                                       (IAst*)getRhsSym(3),
                                       //#line 727 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new WhileStatementNoShortIf(getLeftIToken(), getRightIToken(),
                                                //#line 729 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                                //#line 729 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                                //#line 729 GJavaParser.g
                                                (IAst*)getRhsSym(3),
                                                //#line 729 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new DoStatement(getLeftIToken(), getRightIToken(),
                                    //#line 731 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                    //#line 731 GJavaParser.g
                                    (IAst*)getRhsSym(2),
                                    //#line 731 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                    //#line 731 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                    //#line 731 GJavaParser.g
                                    (IAst*)getRhsSym(5),
                                    //#line 731 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(6)),
                                    //#line 731 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(7)))
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
                     _automatic_ast_pool << new BasicForStatement(getLeftIToken(), getRightIToken(),
                                          //#line 736 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                          //#line 736 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                          //#line 736 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 736 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                          //#line 736 GJavaParser.g
                                          (IAst*)getRhsSym(5),
                                          //#line 736 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(6)),
                                          //#line 736 GJavaParser.g
                                          (IAst*)getRhsSym(7),
                                          //#line 736 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(8)),
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
                     _automatic_ast_pool << new ForStatementNoShortIf(getLeftIToken(), getRightIToken(),
                                              //#line 738 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                              //#line 738 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                              //#line 738 GJavaParser.g
                                              (IAst*)getRhsSym(3),
                                              //#line 738 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                              //#line 738 GJavaParser.g
                                              (IAst*)getRhsSym(5),
                                              //#line 738 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(6)),
                                              //#line 738 GJavaParser.g
                                              (IAst*)getRhsSym(7),
                                              //#line 738 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(8)),
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
                     _automatic_ast_pool << new StatementExpressionList(getLeftIToken(), getRightIToken(),
                                                //#line 746 GJavaParser.g
                                                (IAst*)getRhsSym(1),
                                                //#line 746 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new EnhancedForStatement(getLeftIToken(), getRightIToken(),
                                             //#line 748 GJavaParser.g
                                              _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                             //#line 748 GJavaParser.g
                                              _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                             //#line 748 GJavaParser.g
                                             (IAst*)getRhsSym(3),
                                             //#line 748 GJavaParser.g
                                              _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                             //#line 748 GJavaParser.g
                                             (IAst*)getRhsSym(5),
                                             //#line 748 GJavaParser.g
                                              _automatic_ast_pool << new AstToken(getRhsIToken(6)),
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
                     _automatic_ast_pool << new BreakStatement(getLeftIToken(), getRightIToken(),
                                       //#line 750 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                       //#line 750 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 750 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new ContinueStatement(getLeftIToken(), getRightIToken(),
                                          //#line 752 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                          //#line 752 GJavaParser.g
                                          (IAst*)getRhsSym(2),
                                          //#line 752 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new ReturnStatement(getLeftIToken(), getRightIToken(),
                                        //#line 754 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                        //#line 754 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 754 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new ThrowStatement(getLeftIToken(), getRightIToken(),
                                       //#line 756 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                       //#line 756 GJavaParser.g
                                       (IAst*)getRhsSym(2),
                                       //#line 756 GJavaParser.g
                                        _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new SynchronizedStatement(getLeftIToken(), getRightIToken(),
                                              //#line 758 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                              //#line 758 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                              //#line 758 GJavaParser.g
                                              (IAst*)getRhsSym(3),
                                              //#line 758 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new TryStatement0(getLeftIToken(), getRightIToken(),
                                      //#line 760 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new TryStatement1(getLeftIToken(), getRightIToken(),
                                      //#line 761 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new Catches(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new CatchClause(getLeftIToken(), getRightIToken(),
                                    //#line 766 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                    //#line 766 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                    //#line 766 GJavaParser.g
                                    (IAst*)getRhsSym(3),
                                    //#line 766 GJavaParser.g
                                     _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new Finally(getLeftIToken(), getRightIToken(),
                                //#line 768 GJavaParser.g
                                 _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new PrimaryNoNewArray0(getLeftIToken(), getRightIToken(),
                                           //#line 784 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 784 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                           //#line 784 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new PrimaryNoNewArray1(getLeftIToken(), getRightIToken(),
                                           //#line 785 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                           //#line 785 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                           //#line 785 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new PrimaryNoNewArray2(getRhsIToken(1))
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
                     _automatic_ast_pool << new PrimaryNoNewArray3(getLeftIToken(), getRightIToken(),
                                           //#line 787 GJavaParser.g
                                           (IAst*)getRhsSym(1),
                                           //#line 787 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                           //#line 787 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new PrimaryNoNewArray4(getLeftIToken(), getRightIToken(),
                                           //#line 788 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                           //#line 788 GJavaParser.g
                                           (IAst*)getRhsSym(2),
                                           //#line 788 GJavaParser.g
                                            _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new Literal0(getRhsIToken(1))
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
                     _automatic_ast_pool << new Literal1(getRhsIToken(1))
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
                     _automatic_ast_pool << new Literal2(getRhsIToken(1))
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
                     _automatic_ast_pool << new Literal3(getRhsIToken(1))
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
                     _automatic_ast_pool << new Literal4(getRhsIToken(1))
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
                     _automatic_ast_pool << new Literal5(getRhsIToken(1))
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
                     _automatic_ast_pool << new Literal6(getRhsIToken(1))
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
                     _automatic_ast_pool << new BooleanLiteral0(getRhsIToken(1))
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
                     _automatic_ast_pool << new BooleanLiteral1(getRhsIToken(1))
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
                     _automatic_ast_pool << new ClassInstanceCreationExpression0(getLeftIToken(), getRightIToken(),
                                                         //#line 811 GJavaParser.g
                                                          _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                                         //#line 811 GJavaParser.g
                                                         (IAst*)getRhsSym(2),
                                                         //#line 811 GJavaParser.g
                                                         (IAst*)getRhsSym(3),
                                                         //#line 811 GJavaParser.g
                                                         (IAst*)getRhsSym(4),
                                                         //#line 811 GJavaParser.g
                                                          _automatic_ast_pool << new AstToken(getRhsIToken(5)),
                                                         //#line 811 GJavaParser.g
                                                         (IAst*)getRhsSym(6),
                                                         //#line 811 GJavaParser.g
                                                          _automatic_ast_pool << new AstToken(getRhsIToken(7)),
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
                     _automatic_ast_pool << new ClassInstanceCreationExpression1(getLeftIToken(), getRightIToken(),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(1),
                                                         //#line 812 GJavaParser.g
                                                          _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                                         //#line 812 GJavaParser.g
                                                          _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(4),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(5),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(6),
                                                         //#line 812 GJavaParser.g
                                                          _automatic_ast_pool << new AstToken(getRhsIToken(7)),
                                                         //#line 812 GJavaParser.g
                                                         (IAst*)getRhsSym(8),
                                                         //#line 812 GJavaParser.g
                                                          _automatic_ast_pool << new AstToken(getRhsIToken(9)),
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
                     _automatic_ast_pool << new ArgumentList(getLeftIToken(), getRightIToken(),
                                     //#line 816 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 816 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ArrayCreationExpression0(getLeftIToken(), getRightIToken(),
                                                 //#line 826 GJavaParser.g
                                                  _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new ArrayCreationExpression1(getLeftIToken(), getRightIToken(),
                                                 //#line 827 GJavaParser.g
                                                  _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new ArrayCreationExpression2(getLeftIToken(), getRightIToken(),
                                                 //#line 828 GJavaParser.g
                                                  _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new ArrayCreationExpression3(getLeftIToken(), getRightIToken(),
                                                 //#line 829 GJavaParser.g
                                                  _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new DimExprs(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new DimExpr(getLeftIToken(), getRightIToken(),
                                //#line 834 GJavaParser.g
                                 _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                //#line 834 GJavaParser.g
                                (IAst*)getRhsSym(2),
                                //#line 834 GJavaParser.g
                                 _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new Dims0(getLeftIToken(), getRightIToken(),
                              //#line 836 GJavaParser.g
                               _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                              //#line 836 GJavaParser.g
                               _automatic_ast_pool << new AstToken(getRhsIToken(2)))
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
                     _automatic_ast_pool << new Dims1(getLeftIToken(), getRightIToken(),
                              //#line 837 GJavaParser.g
                              (IAst*)getRhsSym(1),
                              //#line 837 GJavaParser.g
                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                              //#line 837 GJavaParser.g
                               _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new FieldAccess0(getLeftIToken(), getRightIToken(),
                                     //#line 839 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 839 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new FieldAccess1(getLeftIToken(), getRightIToken(),
                                     //#line 840 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                     //#line 840 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new FieldAccess2(getLeftIToken(), getRightIToken(),
                                     //#line 841 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 841 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                     //#line 841 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                     //#line 841 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new MethodInvocation0(getLeftIToken(), getRightIToken(),
                                          //#line 843 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 843 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                          //#line 843 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 843 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new MethodInvocation1(getLeftIToken(), getRightIToken(),
                                          //#line 844 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 844 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                          //#line 844 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 844 GJavaParser.g
                                          (IAst*)getRhsSym(4),
                                          //#line 844 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(5)),
                                          //#line 844 GJavaParser.g
                                          (IAst*)getRhsSym(6),
                                          //#line 844 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(7)))
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
                     _automatic_ast_pool << new MethodInvocation2(getLeftIToken(), getRightIToken(),
                                          //#line 845 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                          //#line 845 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                          //#line 845 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 845 GJavaParser.g
                                          (IAst*)getRhsSym(4),
                                          //#line 845 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(5)),
                                          //#line 845 GJavaParser.g
                                          (IAst*)getRhsSym(6),
                                          //#line 845 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(7)))
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
                     _automatic_ast_pool << new MethodInvocation3(getLeftIToken(), getRightIToken(),
                                          //#line 846 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 846 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                          //#line 846 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                          //#line 846 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(4)),
                                          //#line 846 GJavaParser.g
                                          (IAst*)getRhsSym(5),
                                          //#line 846 GJavaParser.g
                                          (IAst*)getRhsSym(6),
                                          //#line 846 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(7)),
                                          //#line 846 GJavaParser.g
                                          (IAst*)getRhsSym(8),
                                          //#line 846 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(9)))
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
                     _automatic_ast_pool << new MethodInvocation4(getLeftIToken(), getRightIToken(),
                                          //#line 847 GJavaParser.g
                                          (IAst*)getRhsSym(1),
                                          //#line 847 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                          //#line 847 GJavaParser.g
                                          (IAst*)getRhsSym(3),
                                          //#line 847 GJavaParser.g
                                          (IAst*)getRhsSym(4),
                                          //#line 847 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(5)),
                                          //#line 847 GJavaParser.g
                                          (IAst*)getRhsSym(6),
                                          //#line 847 GJavaParser.g
                                           _automatic_ast_pool << new AstToken(getRhsIToken(7)))
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
                     _automatic_ast_pool << new ArrayAccess0(getLeftIToken(), getRightIToken(),
                                     //#line 855 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 855 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                     //#line 855 GJavaParser.g
                                     (IAst*)getRhsSym(3),
                                     //#line 855 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new ArrayAccess1(getLeftIToken(), getRightIToken(),
                                     //#line 856 GJavaParser.g
                                     (IAst*)getRhsSym(1),
                                     //#line 856 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                     //#line 856 GJavaParser.g
                                     (IAst*)getRhsSym(3),
                                     //#line 856 GJavaParser.g
                                      _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new PostIncrementExpression(getLeftIToken(), getRightIToken(),
                                                //#line 863 GJavaParser.g
                                                (IAst*)getRhsSym(1),
                                                //#line 863 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(2)))
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
                     _automatic_ast_pool << new PostDecrementExpression(getLeftIToken(), getRightIToken(),
                                                //#line 865 GJavaParser.g
                                                (IAst*)getRhsSym(1),
                                                //#line 865 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(2)))
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
                     _automatic_ast_pool << new UnaryExpression0(getLeftIToken(), getRightIToken(),
                                         //#line 869 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new UnaryExpression1(getLeftIToken(), getRightIToken(),
                                         //#line 870 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new PreIncrementExpression(getLeftIToken(), getRightIToken(),
                                               //#line 873 GJavaParser.g
                                                _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new PreDecrementExpression(getLeftIToken(), getRightIToken(),
                                               //#line 875 GJavaParser.g
                                                _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new UnaryExpressionNotPlusMinus0(getLeftIToken(), getRightIToken(),
                                                     //#line 878 GJavaParser.g
                                                      _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new UnaryExpressionNotPlusMinus1(getLeftIToken(), getRightIToken(),
                                                     //#line 879 GJavaParser.g
                                                      _automatic_ast_pool << new AstToken(getRhsIToken(1)),
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
                     _automatic_ast_pool << new CastExpression0(getLeftIToken(), getRightIToken(),
                                        //#line 882 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                        //#line 882 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 882 GJavaParser.g
                                        (IAst*)getRhsSym(3),
                                        //#line 882 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new CastExpression1(getLeftIToken(), getRightIToken(),
                                        //#line 883 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                        //#line 883 GJavaParser.g
                                        (IAst*)getRhsSym(2),
                                        //#line 883 GJavaParser.g
                                         _automatic_ast_pool << new AstToken(getRhsIToken(3)),
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
                     _automatic_ast_pool << new MultiplicativeExpression0(getLeftIToken(), getRightIToken(),
                                                  //#line 886 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 886 GJavaParser.g
                                                   _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new MultiplicativeExpression1(getLeftIToken(), getRightIToken(),
                                                  //#line 887 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 887 GJavaParser.g
                                                   _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new MultiplicativeExpression2(getLeftIToken(), getRightIToken(),
                                                  //#line 888 GJavaParser.g
                                                  (IAst*)getRhsSym(1),
                                                  //#line 888 GJavaParser.g
                                                   _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new AdditiveExpression0(getLeftIToken(), getRightIToken(),
                                            //#line 891 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 891 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new AdditiveExpression1(getLeftIToken(), getRightIToken(),
                                            //#line 892 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 892 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ShiftExpression0(getLeftIToken(), getRightIToken(),
                                         //#line 895 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 895 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ShiftExpression1(getLeftIToken(), getRightIToken(),
                                         //#line 896 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 896 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                         //#line 896 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(3)),
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
                     _automatic_ast_pool << new ShiftExpression2(getLeftIToken(), getRightIToken(),
                                         //#line 897 GJavaParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 897 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                         //#line 897 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                         //#line 897 GJavaParser.g
                                          _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new RelationalExpression0(getLeftIToken(), getRightIToken(),
                                              //#line 900 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 900 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new RelationalExpression1(getLeftIToken(), getRightIToken(),
                                              //#line 901 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 901 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new RelationalExpression2(getLeftIToken(), getRightIToken(),
                                              //#line 902 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 902 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new RelationalExpression3(getLeftIToken(), getRightIToken(),
                                              //#line 903 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 903 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                              //#line 903 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(3)),
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
                     _automatic_ast_pool << new RelationalExpression4(getLeftIToken(), getRightIToken(),
                                              //#line 904 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 904 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new EqualityExpression0(getLeftIToken(), getRightIToken(),
                                            //#line 907 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 907 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new EqualityExpression1(getLeftIToken(), getRightIToken(),
                                            //#line 908 GJavaParser.g
                                            (IAst*)getRhsSym(1),
                                            //#line 908 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new AndExpression(getLeftIToken(), getRightIToken(),
                                      //#line 911 GJavaParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 911 GJavaParser.g
                                       _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ExclusiveOrExpression(getLeftIToken(), getRightIToken(),
                                              //#line 914 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 914 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new InclusiveOrExpression(getLeftIToken(), getRightIToken(),
                                              //#line 917 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 917 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ConditionalAndExpression(getLeftIToken(), getRightIToken(),
                                                 //#line 920 GJavaParser.g
                                                 (IAst*)getRhsSym(1),
                                                 //#line 920 GJavaParser.g
                                                  _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ConditionalOrExpression(getLeftIToken(), getRightIToken(),
                                                //#line 923 GJavaParser.g
                                                (IAst*)getRhsSym(1),
                                                //#line 923 GJavaParser.g
                                                 _automatic_ast_pool << new AstToken(getRhsIToken(2)),
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
                     _automatic_ast_pool << new ConditionalExpression(getLeftIToken(), getRightIToken(),
                                              //#line 926 GJavaParser.g
                                              (IAst*)getRhsSym(1),
                                              //#line 926 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                              //#line 926 GJavaParser.g
                                              (IAst*)getRhsSym(3),
                                              //#line 926 GJavaParser.g
                                               _automatic_ast_pool << new AstToken(getRhsIToken(4)),
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
                     _automatic_ast_pool << new Assignment(getLeftIToken(), getRightIToken(),
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
                     _automatic_ast_pool << new AssignmentOperator0(getRhsIToken(1))
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
                     _automatic_ast_pool << new AssignmentOperator1(getRhsIToken(1))
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
                     _automatic_ast_pool << new AssignmentOperator2(getRhsIToken(1))
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
                     _automatic_ast_pool << new AssignmentOperator3(getRhsIToken(1))
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
                     _automatic_ast_pool << new AssignmentOperator4(getRhsIToken(1))
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
                     _automatic_ast_pool << new AssignmentOperator5(getRhsIToken(1))
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
                     _automatic_ast_pool << new AssignmentOperator6(getRhsIToken(1))
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
                     _automatic_ast_pool << new AssignmentOperator7(getLeftIToken(), getRightIToken(),
                                            //#line 944 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                            //#line 944 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                            //#line 944 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(3)))
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
                     _automatic_ast_pool << new AssignmentOperator8(getLeftIToken(), getRightIToken(),
                                            //#line 945 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(1)),
                                            //#line 945 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(2)),
                                            //#line 945 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(3)),
                                            //#line 945 GJavaParser.g
                                             _automatic_ast_pool << new AstToken(getRhsIToken(4)))
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
                     _automatic_ast_pool << new AssignmentOperator9(getRhsIToken(1))
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
                     _automatic_ast_pool << new AssignmentOperator10(getRhsIToken(1))
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
                     _automatic_ast_pool << new AssignmentOperator11(getRhsIToken(1))
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
                     _automatic_ast_pool << new Commaopt(getRhsIToken(1))
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
                     _automatic_ast_pool << new Ellipsisopt(getRhsIToken(1))
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
    //#line 372 "btParserTemplateF.gi

    
            default:
                break;
        }
        return;
    }

