--
-- The Java KeyWord Lexer
--
%Options fp=JavaKWLexer,states
%options template=KeywordTemplateF.gi

%Include
    KWLexerMapF.gi
%End

%Export
    abstract
    assert
    boolean
    break
    byte
    case
    catch
    char
    class
    const
    continue
    default
    do
    double
    enum
    else
    extends
    false
    final
    finally
    float
    for
    goto
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
    true
    try
    void
    volatile
    while
    
    BeginAction
    BeginJava
    EndAction
    EndJava
    NoAction
    NullAction
    BadAction
%End

%Terminals
    a    b    c    d    e    f    g    h    i    j    k    l    m
    n    o    p    q    r    s    t    u    v    w    x    y    z
%End

%Start
    KeyWord
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
%Globals
    /.
#include "$sym_type.h"
#include "$prs_type.h"
    ./
%End
%Rules

    -- The Goal for the parser is a single Keyword

    KeyWord ::= a b s t r a c t
        /.$BeginAction
            $setResult($_abstract);
          $EndAction
        ./

              | a s s e r t
        /.$BeginAction
            $setResult($_assert);
          $EndAction
        ./

              | b o o l e a n
        /.$BeginAction
            $setResult($_boolean);
          $EndAction
        ./

              | b r e a k
        /.$BeginAction
            $setResult($_break);
          $EndAction
        ./

              | b y t e
        /.$BeginAction
            $setResult($_byte);
          $EndAction
        ./

              | c a s e
        /.$BeginAction
            $setResult($_case);
          $EndAction
        ./

              | c a t c h
        /.$BeginAction
            $setResult($_catch);
          $EndAction
        ./

              | c h a r
        /.$BeginAction
            $setResult($_char);
          $EndAction
        ./

              | c l a s s
        /.$BeginAction
            $setResult($_class);
          $EndAction
        ./

              | c o n s t
        /.$BeginAction
            $setResult($_const);
          $EndAction
        ./

              | c o n t i n u e
        /.$BeginAction
            $setResult($_continue);
          $EndAction
        ./

              | d e f a u l t
        /.$BeginAction
            $setResult($_default);
          $EndAction
        ./

              | d o
        /.$BeginAction
            $setResult($_do);
          $EndAction
        ./

              | d o u b l e
        /.$BeginAction
            $setResult($_double);
          $EndAction
        ./

              | e l s e
        /.$BeginAction
            $setResult($_else);
          $EndAction
        ./

              | e n u m
        /.$BeginAction
            $setResult($_enum);
          $EndAction
        ./

              | e x t e n d s
        /.$BeginAction
            $setResult($_extends);
          $EndAction
        ./

              | f a l s e
        /.$BeginAction
            $setResult($_false);
          $EndAction
        ./

              | f i n a l
        /.$BeginAction
            $setResult($_final);
          $EndAction
        ./

              | f i n a l l y
        /.$BeginAction
            $setResult($_finally);
          $EndAction
        ./

              | f l o a t
        /.$BeginAction
            $setResult($_float);
          $EndAction
        ./

              | f o r
        /.$BeginAction
            $setResult($_for);
          $EndAction
        ./

              | g o t o
        /.$BeginAction
            $setResult($_goto);
          $EndAction
        ./

              | i f
        /.$BeginAction
            $setResult($_if);
          $EndAction
        ./

              | i m p l e m e n t s
        /.$BeginAction
            $setResult($_implements);
          $EndAction
        ./

              | i m p o r t
        /.$BeginAction
            $setResult($_import);
          $EndAction
        ./

              | i n s t a n c e o f
        /.$BeginAction
            $setResult($_instanceof);
          $EndAction
        ./

              | i n t
        /.$BeginAction
            $setResult($_int);
          $EndAction
        ./

              | i n t e r f a c e
        /.$BeginAction
            $setResult($_interface);
          $EndAction
        ./

              | l o n g
        /.$BeginAction
            $setResult($_long);
          $EndAction
        ./

              | n a t i v e
        /.$BeginAction
            $setResult($_native);
          $EndAction
        ./

              | n e w
        /.$BeginAction
            $setResult($_new);
          $EndAction
        ./

              | n u l l
        /.$BeginAction
            $setResult($_null);
          $EndAction
        ./

              | p a c k a g e
        /.$BeginAction
            $setResult($_package);
          $EndAction
        ./

              | p r i v a t e
        /.$BeginAction
            $setResult($_private);
          $EndAction
        ./

              | p r o t e c t e d
        /.$BeginAction
            $setResult($_protected);
          $EndAction
        ./

              | p u b l i c
        /.$BeginAction
            $setResult($_public);
          $EndAction
        ./

              | r e t u r n
        /.$BeginAction
            $setResult($_return);
          $EndAction
        ./

              | s h o r t
        /.$BeginAction
            $setResult($_short);
          $EndAction
        ./

              | s t a t i c
        /.$BeginAction
            $setResult($_static);
          $EndAction
        ./

              | s t r i c t f p
        /.$BeginAction
            $setResult($_strictfp);
          $EndAction
        ./

              | s u p e r
        /.$BeginAction
            $setResult($_super);
          $EndAction
        ./

              | s w i t c h
        /.$BeginAction
            $setResult($_switch);
          $EndAction
        ./

              | s y n c h r o n i z e d
        /.$BeginAction
            $setResult($_synchronized);
          $EndAction
        ./

              | t h i s
        /.$BeginAction
            $setResult($_this);
          $EndAction
        ./

              | t h r o w
        /.$BeginAction
            $setResult($_throw);
          $EndAction
        ./

              | t h r o w s
        /.$BeginAction
            $setResult($_throws);
          $EndAction
        ./

              | t r a n s i e n t
        /.$BeginAction
            $setResult($_transient);
          $EndAction
        ./

              | t r u e
        /.$BeginAction
            $setResult($_true);
          $EndAction
        ./

              | t r y
        /.$BeginAction
            $setResult($_try);
          $EndAction
        ./

              | v o i d
        /.$BeginAction
            $setResult($_void);
          $EndAction
        ./

              | v o l a t i l e
        /.$BeginAction
            $setResult($_volatile);
          $EndAction
        ./

              | w h i l e
        /.$BeginAction
            $setResult($_while);
          $EndAction
        ./

    KeyWord ::= '$' bB eE gG iI nN aA cC tT iI oO nN
        /.$BeginAction
            $setResult($_BeginAction);
          $EndAction
        ./
              | '$' bB eE gG iI nN jJ aA vV aA
        /.$BeginAction
            $setResult($_BeginJava);
          $EndAction
        ./

    KeyWord ::= '$' eE nN dD aA cC tT iI oO nN
        /.$BeginAction
            $setResult($_EndAction);
          $EndAction
        ./
              | '$' eE nN dD jJ aA vV aA
        /.$BeginAction
            $setResult($_EndJava);
          $EndAction
        ./

    KeyWord ::= '$' nN oO aA cC tT iI oO nN
        /.$BeginAction
            $setResult($_NoAction);
          $EndAction
        ./
    KeyWord ::= '$' nN uU lL lL aA cC tT iI oO nN
        /.$BeginAction
            $setResult($_NullAction);
          $EndAction
        ./
    KeyWord ::= '$' bB aA dD aA cC tT iI oO nN
        /.$BeginAction
            $setResult($_BadAction);
          $EndAction
        ./

    aA -> a | A
    bB -> b | B 
    cC -> c | C
    dD -> d | D
    eE -> e | E
    gG -> g | G
    iI -> i | I 
    jJ -> j | J 
    lL -> l | L 
    nN -> n | N
    oO -> o | O
    tT -> t | T
    uU -> u | U
    vV -> v | V 
%End