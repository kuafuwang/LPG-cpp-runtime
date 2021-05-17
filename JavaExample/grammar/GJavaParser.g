%options visitor=preorder
%options parent_saved
%options variables
%options automatic_ast
%options fp=JavaParser
%options verbose
%options template=btParserTemplateF.gi
%options import_terminals=GJavaLexer.gi

%Notice
    /.//
    // This is the grammar specification from the Final Draft of the generic spec.
    //./
%End

%Globals
    /.

    ./
%End

%Identifier
    IDENTIFIER
%End

%Keywords
    abstract
    assert
    boolean
    break    
    byte
    case 
    catch 
    char
    class
    continue 
    default  
    do 
    double    
    else
    enum    
    extends 
    final
    finally    
    float
    for  
    if
    implements
    import
    instanceof
    int
    interface    
    long
    native 
    new 
    null
    package
    private  
    protected
    public 
    return 
    short
    static
    strictfp
    super  
    switch  
    synchronized 
    this 
    throw
    throws  
    transient
    try 
    void 
    volatile      
    while 
    false
    true
%End

%Alias
    ,opt ::= Commaopt
    ...opt ::= Ellipsisopt
%End

%Terminals

    IntegerLiteral        -- the usual
    LongLiteral           -- IntegerLiteral followed by 'l' or 'L'
    FloatingPointLiteral  --
                          -- FloatingPointLiteral ::= Digits . Digits? ExponentPart? FloatingTypeSuffix?
                          --                        | . Digits ExponentPart? FloatingTypeSuffix?
                          --                        | Digits ExponentPart FloatingTypeSuffix?
                          --                        | Digits ExponentPart? FloatingTypeSuffix
                          --
                          -- ExponentPart ::= ('e'|'E') ('+'|'-')? Digits
                          -- FloatingTypeSuffix ::= 'f' |  'F'
                          --
    DoubleLiteral         -- See FloatingPointLiteral except that
                          -- FloatingTypeSuffix ::= 'd' | 'D'
                          --
    CharacterLiteral      -- the usual
    StringLiteral         -- the usual

    MINUS_MINUS                ::= '--'
    OR                         ::= '|' 
    MINUS                      ::= -
    MINUS_EQUAL                ::= -=
    NOT                        ::= !
    NOT_EQUAL                  ::= !=
    REMAINDER                  ::= '%'
    REMAINDER_EQUAL            ::= '%='
    AND                        ::= &
    AND_AND                    ::= && 
    AND_EQUAL                  ::= &= 
    LPAREN                     ::= (
    RPAREN                     ::= )
    MULTIPLY                   ::= *
    MULTIPLY_EQUAL             ::= *=
    COMMA                      ::= ,
    DOT                        ::= .
    DIVIDE                     ::= / 
    DIVIDE_EQUAL               ::= /= 
    COLON                      ::= :
    SEMICOLON                  ::= ;
    QUESTION                   ::= ?
    AT                         ::= @  
    LBRACKET                   ::= '['
    RBRACKET                   ::= ']'
    XOR                        ::= ^ 
    XOR_EQUAL                  ::= ^=
    LBRACE                     ::= {
    OR_OR                      ::= || 
    OR_EQUAL                   ::= |=  
    RBRACE                     ::= }  
    TWIDDLE                    ::= ~  
    PLUS                       ::= + 
    PLUS_PLUS                  ::= ++
    PLUS_EQUAL                 ::= +=
    LESS                       ::= <  
    LEFT_SHIFT                 ::= << 
    LEFT_SHIFT_EQUAL           ::= <<= 
    LESS_EQUAL                 ::= <=
    EQUAL                      ::= =  
    EQUAL_EQUAL                ::= ==  
    GREATER                    ::= >
    GREATER_EQUAL              ::= >=
    RIGHT_SHIFT                ::= >>
    RIGHT_SHIFT_EQUAL          ::= >>= 
    UNSIGNED_RIGHT_SHIFT       ::= >>>
    UNSIGNED_RIGHT_SHIFT_EQUAL ::= >>>=
    ELLIPSIS                   ::= ...
    
    BeginAction                ::= "$BeginAction"
    EndAction                  ::= "$EndAction"
    BeginJava                  ::= "$BeginJava"
    EndJava                    ::= "$EndJava"
    NoAction                   ::= "$NoAction"
    NullAction                 ::= "$NullAction"
    BadAction                  ::= "$BadAction"
%End

%Start
    CompilationUnit ClassBodyDeclarationsopt LPGUserAction
%End

%Notice
/.
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
./
%End

%Rules

    identifier ::= IDENTIFIER
        /.
                    void initialize()
                    {
                        if (getIDENTIFIER()->getKind() != $prs_type ::TK_IDENTIFIER)
                           std::wcout <<L"Turning keyword " << getIDENTIFIER()->toString() << L" into an identifier" << std::endl;
                    }
        ./
        
    LPGUserAction ::= BlockStatementsopt
                    | "$BeginAction" BlockStatementsopt "$EndAction"
                    | "$BeginJava"   BlockStatementsopt "$EndJava"
                    | "$NoAction"
                    | "$NullAction"
                    | "$BadAction"
                    

    -- Chapter 4

    Type ::= PrimitiveType
           | ReferenceType

    PrimitiveType ::= NumericType
                    | boolean

    NumericType ::= IntegralType
                  | FloatingPointType

    IntegralType ::= byte
                   | short
                   | int
                   | long
                   | char

    FloatingPointType ::= float
                        | double

    ReferenceType ::= ClassOrInterfaceType
                    | TypeVariable
                    | ArrayType

    ClassOrInterfaceType ::= ClassType
    --
    -- Remove an obvious conflict.
    --
    --                       | InterfaceType

    ClassType ::= TypeName TypeArgumentsopt

    InterfaceType ::= TypeName TypeArgumentsopt

    TypeName ::= identifier
               | TypeName . identifier

    ClassName ::= TypeName

    TypeVariable ::= identifier

    ArrayType ::= Type '[' ']'

    TypeParameter ::= TypeVariable TypeBoundopt

    TypeBound ::= extends ClassOrInterfaceType AdditionalBoundListopt

    AdditionalBoundList ::= AdditionalBound
                          | AdditionalBoundList AdditionalBound

    AdditionalBound ::= & InterfaceType

    TypeArguments ::= < ActualTypeArgumentList >

    ActualTypeArgumentList ::= ActualTypeArgument
                             | ActualTypeArgumentList , ActualTypeArgument

    ActualTypeArgument ::= ReferenceType
                         | Wildcard

    Wildcard ::= ? WildcardBoundsOpt

    WildcardBounds ::= extends ReferenceType
                     | super ReferenceType

    -- Chapter 5

    -- Chapter 6

    PackageName ::= identifier
                  | PackageName . identifier

    --
    -- See Chapter 4
    --
    -- TypeName ::= identifier
    --           | PackageOrTypeName . identifier
    --
    ExpressionName ::= identifier
                     | AmbiguousName . identifier

    MethodName ::= identifier
                 | AmbiguousName . identifier

    PackageOrTypeName ::= identifier
                        | PackageOrTypeName . identifier

    AmbiguousName ::= identifier
                    | AmbiguousName . identifier

    -- Chapter 7

    CompilationUnit ::= PackageDeclarationopt ImportDeclarationsopt TypeDeclarationsopt

    ImportDeclarations ::= ImportDeclaration
                         | ImportDeclarations ImportDeclaration

    TypeDeclarations ::= TypeDeclaration
                       | TypeDeclarations TypeDeclaration

    PackageDeclaration ::= Annotationsopt package PackageName ;

    ImportDeclaration ::= SingleTypeImportDeclaration
                        | TypeImportOnDemandDeclaration
                        | SingleStaticImportDeclaration
                        | StaticImportOnDemandDeclaration

    SingleTypeImportDeclaration ::= import TypeName ;

    TypeImportOnDemandDeclaration ::= import PackageOrTypeName . * ;
    
    SingleStaticImportDeclaration ::= import static TypeName . identifier ;

    StaticImportOnDemandDeclaration ::= import static TypeName . * ;

    TypeDeclaration ::= ClassDeclaration
                      | InterfaceDeclaration
                      | ;

    -- Chapter 8

    ClassDeclaration ::= NormalClassDeclaration
                       | EnumDeclaration

    NormalClassDeclaration ::= ClassModifiersopt class identifier TypeParametersopt Superopt Interfacesopt ClassBody

    ClassModifiers ::= ClassModifier
                     | ClassModifiers ClassModifier

    ClassModifier ::= Annotation
                    | public
                    | protected
                    | private
                    | abstract
                    | static
                    | final
                    | strictfp

    TypeParameters ::= < TypeParameterList >
    
    TypeParameterList ::= TypeParameter
                        | TypeParameterList , TypeParameter

    Super ::= extends ClassType

    --
    -- See Chapter 4
    --
    --ClassType ::= TypeName TypeArgumentsopt
    --
    Interfaces ::= implements InterfaceTypeList

    InterfaceTypeList ::= InterfaceType
                        | InterfaceTypeList , InterfaceType

    --
    -- See Chapter 4
    --
    --InterfaceType ::= TypeName TypeArgumentsopt
    --
    ClassBody ::= { ClassBodyDeclarationsopt }

    ClassBodyDeclarations ::= ClassBodyDeclaration
                            | ClassBodyDeclarations ClassBodyDeclaration

    ClassBodyDeclaration ::= ClassMemberDeclaration
                           | InstanceInitializer
                           | StaticInitializer
                           | ConstructorDeclaration

    ClassMemberDeclaration ::= FieldDeclaration
                             | MethodDeclaration
                             | ClassDeclaration
                             | InterfaceDeclaration
                             | ;
    
    FieldDeclaration ::= FieldModifiersopt Type VariableDeclarators ;
    
    VariableDeclarators ::= VariableDeclarator
                          | VariableDeclarators , VariableDeclarator
    
    VariableDeclarator ::= VariableDeclaratorId
                         | VariableDeclaratorId = VariableInitializer
    
    VariableDeclaratorId ::= identifier
                           | VariableDeclaratorId '[' ']'
    
    VariableInitializer ::= Expression
                          | ArrayInitializer
    
    FieldModifiers ::= FieldModifier
                     | FieldModifiers FieldModifier
    
    FieldModifier ::= Annotation
                    | public
                    | protected
                    | private
                    | static
                    | final
                    | transient
                    | volatile
    
    MethodDeclaration ::= MethodHeader MethodBody
    
    MethodHeader ::= MethodModifiersopt TypeParametersopt ResultType MethodDeclarator Throwsopt
    
    ResultType ::= Type
                 | void
    
    MethodDeclarator ::= identifier ( FormalParameterListopt )
    
    MethodDeclarator ::= MethodDeclarator '[' ']'
    
    FormalParameterList ::= LastFormalParameter
                          | FormalParameters , LastFormalParameter
    
    FormalParameters ::= FormalParameter
                       | FormalParameters , FormalParameter
    
    FormalParameter ::= VariableModifiersopt Type VariableDeclaratorId
    
    VariableModifiers ::= VariableModifier
                        | VariableModifiers VariableModifier
    
    VariableModifier ::= final
                       | Annotations
    
    LastFormalParameter ::= VariableModifiersopt Type ...opt VariableDeclaratorId

    --
    -- See above
    --
    --VariableDeclaratorId ::= identifier
    --                       | VariableDeclaratorId '[' ']'
    --    
    MethodModifiers ::= MethodModifier
                      | MethodModifiers MethodModifier
    
    MethodModifier ::= Annotations
                     | public
                     | protected
                     | private
                     | abstract
                     | static
                     | final
                     | synchronized
                     | native
                     | strictfp
    
    Throws ::= throws ExceptionTypeList
    
    ExceptionTypeList ::= ExceptionType
                        | ExceptionTypeList , ExceptionType
    
    ExceptionType ::= ClassType
                    | TypeVariable
    
    MethodBody ::= Block
                 | ;

    InstanceInitializer ::= Block
    
    StaticInitializer ::= static Block
    
    ConstructorDeclaration ::= ConstructorModifiersopt ConstructorDeclarator Throwsopt ConstructorBody
    
    ConstructorDeclarator ::= TypeParametersopt SimpleTypeName ( FormalParameterListopt )
    
    SimpleTypeName ::= identifier

    ConstructorModifiers ::= ConstructorModifier
                           | ConstructorModifiers ConstructorModifier
    
    ConstructorModifier ::= Annotations
                          | public
                          | protected
                          | private
    
    ConstructorBody ::= { ExplicitConstructorInvocationopt BlockStatementsopt }
    
    ExplicitConstructorInvocation ::= TypeArgumentsopt this ( ArgumentListopt ) ;
                                    | TypeArgumentsopt super ( ArgumentListopt ) ;
                                    | Primary . TypeArgumentsopt super ( ArgumentListopt ) ;
    
    EnumDeclaration ::= ClassModifiersopt enum identifier Interfacesopt EnumBody
    
    EnumBody ::= { EnumConstantsopt ,opt EnumBodyDeclarationsopt }
    
    EnumConstants ::= EnumConstant
                    | EnumConstants , EnumConstant
    
    EnumConstant ::= Annotationsopt identifier Argumentsopt ClassBodyopt
    
    Arguments ::= ( ArgumentListopt )
    
    EnumBodyDeclarations ::= ; ClassBodyDeclarationsopt
    
    -- chapter 9
    
    InterfaceDeclaration ::= NormalInterfaceDeclaration
                           | AnnotationTypeDeclaration
    
    NormalInterfaceDeclaration ::= InterfaceModifiersopt interface identifier TypeParametersopt ExtendsInterfacesopt InterfaceBody
    
    InterfaceModifiers ::= InterfaceModifier
                         | InterfaceModifiers InterfaceModifier
    
    InterfaceModifier ::= Annotation
                        | public
                        | protected
                        | private
                        | abstract
                        | static
                        | strictfp
    
    ExtendsInterfaces ::= extends InterfaceType
                        | ExtendsInterfaces , InterfaceType
    
    --
    -- See Chapter 4
    --
    --InterfaceType ::= TypeName TypeArgumentsOpt
    
    InterfaceBody ::= { InterfaceMemberDeclarationsopt }
    
    InterfaceMemberDeclarations ::= InterfaceMemberDeclaration
                                  | InterfaceMemberDeclarations InterfaceMemberDeclaration
    
    InterfaceMemberDeclaration ::= ConstantDeclaration
                                 | AbstractMethodDeclaration
                                 | ClassDeclaration
                                 | InterfaceDeclaration
                                 | ;
    
    ConstantDeclaration ::= ConstantModifiersopt Type VariableDeclarators
    
    ConstantModifiers ::= ConstantModifier
                        | ConstantModifiers ConstantModifier
    
    ConstantModifier ::= Annotation
                       | public
                       | static
                       | final
    
    AbstractMethodDeclaration ::= AbstractMethodModifiersopt TypeParametersopt ResultType MethodDeclarator Throwsopt ;
    
    AbstractMethodModifiers ::= AbstractMethodModifier
                              | AbstractMethodModifiers AbstractMethodModifier
    
    AbstractMethodModifier ::= Annotations
                             | public
                             | abstract
    
    AnnotationTypeDeclaration ::= InterfaceModifiersopt @ interface identifier AnnotationTypeBody
    
    AnnotationTypeBody ::= { AnnotationTypeElementDeclarationsopt }
    
    AnnotationTypeElementDeclarations ::= AnnotationTypeElementDeclaration
                                        | AnnotationTypeElementDeclarations AnnotationTypeElementDeclaration
    
    AnnotationTypeElementDeclaration ::= AbstractMethodModifiersopt Type identifier ( ) DefaultValueopt ;
                                       | ConstantDeclaration
                                       | ClassDeclaration
                                       | InterfaceDeclaration
                                       | EnumDeclaration
                                       | AnnotationTypeDeclaration
                                       | ;
    
    DefaultValue ::= default ElementValue
    
    Annotations ::= Annotation
                  | Annotations Annotation
    
    Annotation ::= NormalAnnotation
                 | MarkerAnnotation
                 | SingleElementAnnotation
    
    NormalAnnotation ::= @ TypeName ( ElementValuePairsopt )
    
    ElementValuePairs ::= ElementValuePair
                        | ElementValuePairs , ElementValuePair
    
    ElementValuePair ::= SimpleName = ElementValue
    
    SimpleName ::= identifier

    ElementValue ::= ConditionalExpression
                   | Annotation
                   | ElementValueArrayInitializer
    
    ElementValueArrayInitializer ::= { ElementValuesopt ,opt }
    
    ElementValues ::= ElementValue
                    | ElementValues , ElementValue
    
    MarkerAnnotation ::= @ TypeName
    
    SingleElementAnnotation ::= @ TypeName ( ElementValue )
    
    -- Chapter 10
    
    ArrayInitializer ::= { VariableInitializersopt ,opt }
    
    VariableInitializers ::= VariableInitializer
                           | VariableInitializers , VariableInitializer
    
    --
    -- See Chapter 8
    --
    --VariableInitializer ::= Expression
    --                      | ArrayInitializer
    
    -- Chapter 11
    
    -- Chapter 12
    
    -- Chapter 13
    
    -- Chapter 14
    
    Block ::= { BlockStatementsopt }
    
    BlockStatements ::= BlockStatement
                      | BlockStatements BlockStatement
    
    BlockStatement ::= LocalVariableDeclarationStatement
                     | ClassDeclaration
                     | Statement
    
    LocalVariableDeclarationStatement ::= LocalVariableDeclaration ;
    
    LocalVariableDeclaration ::= VariableModifiersopt Type VariableDeclarators
    
    --
    -- See Chapter 8
    --
    --VariableDeclarators ::= VariableDeclarator
    --                      | VariableDeclarators , VariableDeclarator
    --
    --VariableDeclarator ::= VariableDeclaratorId
    --                     | VariableDeclaratorId = VariableInitializer
    --
    --VariableDeclaratorId ::= identifier
    --                       | VariableDeclaratorId '[' ']'
    --
    --VariableInitializer ::= Expression
    --                      | ArrayInitializer
    
    Statement ::= StatementWithoutTrailingSubstatement
                | LabeledStatement
                | IfThenStatement
                | IfThenElseStatement
                | WhileStatement
                | ForStatement

    StatementWithoutTrailingSubstatement ::= Block
                                           | EmptyStatement
                                           | ExpressionStatement
                                           | AssertStatement
                                           | SwitchStatement
                                           | DoStatement
                                           | BreakStatement
                                           | ContinueStatement
                                           | ReturnStatement
                                           | SynchronizedStatement
                                           | ThrowStatement
                                           | TryStatement
    
    StatementNoShortIf ::= StatementWithoutTrailingSubstatement
                         | LabeledStatementNoShortIf
                         | IfThenElseStatementNoShortIf
                         | WhileStatementNoShortIf
                         | ForStatementNoShortIf
    
    IfThenStatement ::= if ( Expression ) Statement
    
    IfThenElseStatement ::= if ( Expression ) StatementNoShortIf else Statement
    
    IfThenElseStatementNoShortIf ::= if ( Expression ) StatementNoShortIf else StatementNoShortIf
    
    EmptyStatement ::= ;

    LabeledStatement ::= identifier : Statement
    
    LabeledStatementNoShortIf ::= identifier : StatementNoShortIf
    
    ExpressionStatement ::= StatementExpression ;
    
    StatementExpression ::= Assignment
                          | PreIncrementExpression
                          | PreDecrementExpression
                          | PostIncrementExpression
                          | PostDecrementExpression
                          | MethodInvocation
                          | ClassInstanceCreationExpression
    
    --
    -- Already specified above
    --
    --IfThenStatement ::= if ( Expression ) Statement
    --
    --IfThenElseStatement ::= if ( Expression ) StatementNoShortIf else Statement
    --
    --IfThenElseStatementNoShortIf ::= if ( Expression ) StatementNoShortIf else StatementNoShortIf
    
    AssertStatement ::= assert Expression ;
                      | assert Expression : Expression ;
    
    SwitchStatement ::= switch ( Expression ) SwitchBlock
    
    SwitchBlock ::= { SwitchBlockStatementGroupsopt SwitchLabelsopt }
    
    SwitchBlockStatementGroups ::= SwitchBlockStatementGroup
                                 | SwitchBlockStatementGroups SwitchBlockStatementGroup
    
    SwitchBlockStatementGroup ::= SwitchLabels BlockStatements
    
    SwitchLabels ::= SwitchLabel
                   | SwitchLabels SwitchLabel
    
    SwitchLabel ::= case ConstantExpression :
                  | case EnumConstant :
                  | default :

    EnumConstant ::= identifier
    
    WhileStatement ::= while ( Expression ) Statement
    
    WhileStatementNoShortIf ::= while ( Expression ) StatementNoShortIf
    
    DoStatement ::= do Statement while ( Expression ) ;
    
    ForStatement ::= BasicForStatement
                   | EnhancedForStatement
    
    BasicForStatement ::= for ( ForInitopt ; Expressionopt ; ForUpdateopt ) Statement
    
    ForStatementNoShortIf ::= for ( ForInitopt ; Expressionopt ; ForUpdateopt ) StatementNoShortIf
    
    ForInit ::= StatementExpressionList
              | LocalVariableDeclaration
    
    ForUpdate ::= StatementExpressionList
    
    StatementExpressionList ::= StatementExpression
                              | StatementExpressionList , StatementExpression
    
    EnhancedForStatement ::= for ( FormalParameter : Expression ) Statement
    
    BreakStatement ::= break identifieropt ;
    
    ContinueStatement ::= continue identifieropt ;
    
    ReturnStatement ::= return Expressionopt ;
    
    ThrowStatement ::= throw Expression ;
    
    SynchronizedStatement ::= synchronized ( Expression ) Block
    
    TryStatement ::= try Block Catches
                   | try Block Catchesopt Finally
    
    Catches ::= CatchClause
              | Catches CatchClause
    
    CatchClause ::= catch ( FormalParameter ) Block
    
    Finally ::= finally Block
    
    --
    -- See Chapter 8
    --
    --FormalParameter ::= VariableModifiersopt Type VariableDeclaratorId
    --
    --VariableDeclaratorId ::= identifier
    --                       | VariableDeclaratorId '[' ']'
    
    -- Chapter 15
    
    Primary ::= PrimaryNoNewArray
              | ArrayCreationExpression
    
    PrimaryNoNewArray ::= Literal
                        | Type . class
                        | void . class
                        | this
                        | ClassName . this
                        | ( Expression )
                        | ClassInstanceCreationExpression
                        | FieldAccess
                        | MethodInvocation
                        | ArrayAccess
    
    Literal ::= IntegerLiteral
              | LongLiteral
              | FloatingPointLiteral
              | DoubleLiteral
              | BooleanLiteral
              | CharacterLiteral
              | StringLiteral
              | null
    
    BooleanLiteral ::= true
                     | false

    --
    -- The following case appeared to be missing from the spec:
    --
    --                                | identifier . new TypeArgumentsopt identifier TypeArgumentsopt ( ArgumentListopt ) ClassBodyopt
    --
    ClassInstanceCreationExpression ::=  new TypeArgumentsopt ClassOrInterfaceType TypeArgumentsopt ( ArgumentListopt ) ClassBodyopt
                                      | Primary . new TypeArgumentsopt identifier TypeArgumentsopt ( ArgumentListopt ) ClassBodyopt
--                                      | name . new TypeArgumentsopt identifier TypeArgumentsopt ( ArgumentListopt ) ClassBodyopt
    
    ArgumentList ::= Expression
                   | ArgumentList , Expression

--
-- The rules below were specified however, from some examples,
-- it would appear that ClassOrInterfaceType is expected instead
-- of TypeName
--
--                              | new TypeName DimExprs Dimsopt
--                              | new TypeName Dims ArrayInitializer
--
    ArrayCreationExpression ::= new PrimitiveType DimExprs Dimsopt
                              | new ClassOrInterfaceType DimExprs Dimsopt
                              | new PrimitiveType Dims ArrayInitializer
                              | new ClassOrInterfaceType Dims ArrayInitializer
    
    DimExprs ::= DimExpr
               | DimExprs DimExpr
    
    DimExpr ::= '[' Expression ']'
    
    Dims ::= '[' ']'
           | Dims '[' ']'
    
    FieldAccess ::= Primary . identifier
                  | super . identifier
                  | ClassName . super . identifier
    
    MethodInvocation ::= MethodName ( ArgumentListopt )
                       | Primary . TypeArgumentsopt identifier ( ArgumentListopt )
                       | super . TypeArgumentsopt identifier ( ArgumentListopt )
                       | ClassName . super . TypeArgumentsopt identifier ( ArgumentListopt )
                       | TypeName . TypeArguments identifier ( ArgumentListopt )
    
    --
    -- See above
    --
    --ArgumentList ::= Expression
    --               | ArgumentList , Expression
    --
    ArrayAccess ::= ExpressionName '[' Expression ']'
                  | PrimaryNoNewArray '[' Expression ']'
    
    PostfixExpression ::= Primary
                        | ExpressionName
                        | PostIncrementExpression
                        | PostDecrementExpression
    
    PostIncrementExpression ::= PostfixExpression ++
    
    PostDecrementExpression ::= PostfixExpression '--'
    
    UnaryExpression ::= PreIncrementExpression
                      | PreDecrementExpression
                      | + UnaryExpression
                      | - UnaryExpression
                      | UnaryExpressionNotPlusMinus
    
    PreIncrementExpression ::= ++ UnaryExpression
    
    PreDecrementExpression ::= '--' UnaryExpression
    
    UnaryExpressionNotPlusMinus ::= PostfixExpression
                                  | ~ UnaryExpression
                                  | ! UnaryExpression
                                  | CastExpression
    
    CastExpression ::= ( PrimitiveType Dimsopt ) UnaryExpression
                     | ( ReferenceType ) UnaryExpressionNotPlusMinus
    
    MultiplicativeExpression ::= UnaryExpression
                               | MultiplicativeExpression * UnaryExpression
                               | MultiplicativeExpression / UnaryExpression
                               | MultiplicativeExpression '%' UnaryExpression
    
    AdditiveExpression ::= MultiplicativeExpression
                         | AdditiveExpression + MultiplicativeExpression
                         | AdditiveExpression - MultiplicativeExpression
    
    ShiftExpression ::= AdditiveExpression
                      | ShiftExpression << AdditiveExpression
                      | ShiftExpression > > AdditiveExpression
                      | ShiftExpression > > > AdditiveExpression
    
    RelationalExpression ::= ShiftExpression
                           | RelationalExpression < ShiftExpression
                           | RelationalExpression > ShiftExpression
                           | RelationalExpression <= ShiftExpression
                           | RelationalExpression > = ShiftExpression
                           | RelationalExpression instanceof ReferenceType
    
    EqualityExpression ::= RelationalExpression
                         | EqualityExpression == RelationalExpression
                         | EqualityExpression != RelationalExpression
    
    AndExpression ::= EqualityExpression
                    | AndExpression & EqualityExpression
    
    ExclusiveOrExpression ::= AndExpression
                            | ExclusiveOrExpression ^ AndExpression
    
    InclusiveOrExpression ::= ExclusiveOrExpression
                            | InclusiveOrExpression '|' ExclusiveOrExpression
    
    ConditionalAndExpression ::= InclusiveOrExpression
                               | ConditionalAndExpression && InclusiveOrExpression
    
    ConditionalOrExpression ::= ConditionalAndExpression
                              | ConditionalOrExpression || ConditionalAndExpression
    
    ConditionalExpression ::= ConditionalOrExpression
                            | ConditionalOrExpression ? Expression : ConditionalExpression
    
    AssignmentExpression ::= ConditionalExpression
                           | Assignment
    
    Assignment ::= LeftHandSide AssignmentOperator AssignmentExpression
    
    LeftHandSide ::= ExpressionName
                   | FieldAccess
                   | ArrayAccess
    
    AssignmentOperator ::= =
                         | *=
                         | /=
                         | '%='
                         | +=
                         | -=
                         | <<=
                         | > > =
                         | > > > =
                         | &=
                         | ^=
                         | |=
    
    Expression ::= AssignmentExpression

    ConstantExpression ::= Expression
    
    --
    -- Optional rules
    --
    Dimsopt ::= %Empty
              | Dims

    Catchesopt ::= %Empty
                 | Catches

    identifieropt ::= %Empty
                    | identifier

    ForUpdateopt ::= %Empty
                   | ForUpdate

    Expressionopt ::= %Empty
                    | Expression

    ForInitopt ::= %Empty
                 | ForInit

    SwitchLabelsopt ::= %Empty
                      | SwitchLabels

    SwitchBlockStatementGroupsopt ::= %Empty
                                    | SwitchBlockStatementGroups

    VariableModifiersopt ::= %Empty
                           | VariableModifiers

    VariableInitializersopt ::= %Empty
                              | VariableInitializers

    ElementValuesopt ::= %Empty
                       | ElementValues

    ElementValuePairsopt ::= %Empty
                           | ElementValuePairs

    DefaultValueopt ::= %Empty
                      | DefaultValue

    AnnotationTypeElementDeclarationsopt ::= %Empty
                                           | AnnotationTypeElementDeclarations

    AbstractMethodModifiersopt ::= %Empty
                                 | AbstractMethodModifiers

    ConstantModifiersopt ::= %Empty
                           | ConstantModifiers

    InterfaceMemberDeclarationsopt ::= %Empty
                                     | InterfaceMemberDeclarations

    ExtendsInterfacesopt ::= %Empty
                           | ExtendsInterfaces

    InterfaceModifiersopt ::= %Empty
                            | InterfaceModifiers

    ClassBodyopt ::= %Empty
                   | ClassBody

    Argumentsopt ::= %Empty
                   | Arguments

    EnumBodyDeclarationsopt ::= %Empty
                              | EnumBodyDeclarations

    ,opt ::= %Empty
           | ,

    EnumConstantsopt ::= %Empty
                       | EnumConstants

    ArgumentListopt ::= %Empty
                      | ArgumentList

    BlockStatementsopt ::= %Empty
                         | BlockStatements

    ExplicitConstructorInvocationopt ::= %Empty
                                       | ExplicitConstructorInvocation

    ConstructorModifiersopt ::= %Empty
                              | ConstructorModifiers

    ...opt ::= %Empty
             | ...

    FormalParameterListopt ::= %Empty
                             | FormalParameterList

    Throwsopt ::= %Empty
                | Throws

    MethodModifiersopt ::= %Empty
                         | MethodModifiers

    FieldModifiersopt ::= %Empty
                        | FieldModifiers

    ClassBodyDeclarationsopt ::= %Empty
                               | ClassBodyDeclarations

    Interfacesopt ::= %Empty
                    | Interfaces

    Superopt ::= %Empty
               | Super

    TypeParametersopt ::= %Empty
                        | TypeParameters

    ClassModifiersopt ::= %Empty
                        | ClassModifiers

    Annotationsopt ::= %Empty
                     | Annotations

    TypeDeclarationsopt ::= %Empty
                          | TypeDeclarations

    ImportDeclarationsopt ::= %Empty
                            | ImportDeclarations

    PackageDeclarationopt ::= %Empty
                            | PackageDeclaration

    WildcardBoundsOpt ::= %Empty
                        | WildcardBounds

    AdditionalBoundListopt ::= %Empty
                             | AdditionalBoundList

    TypeBoundopt ::= %Empty
                   | TypeBound

    TypeArgumentsopt ::= %Empty
                       | TypeArguments

%End