%Options fp=LPGKWLexer
%options single-productions
%options template=KeywordTemplateF.gi

%Include
    --
    -- Each upper case letter is mapped into is corresponding
    -- lower case counterpart. For example, if an 'A' appears
    -- in the input, it is mapped into Char_a just like 'a'.
    --
    KWLexerFoldedCaseMapF.gi
%End

%Export
   ALIAS_KEY
   AST_KEY
   DEFINE_KEY
   DISJOINTPREDECESSORSETS_KEY
   DROPRULES_KEY
   DROPSYMBOLS_KEY
   EMPTY_KEY
   END_KEY
   ERROR_KEY
   EOL_KEY
   EOF_KEY 
   EXPORT_KEY
   GLOBALS_KEY
   HEADERS_KEY
   IDENTIFIER_KEY
   IMPORT_KEY
   INCLUDE_KEY
   KEYWORDS_KEY
   NAMES_KEY
   NOTICE_KEY
   OPTIONS_KEY
   RECOVER_KEY
   RULES_KEY
   SOFT_KEYWORDS_KEY
   START_KEY
   TERMINALS_KEY
   TRAILERS_KEY
   TYPES_KEY
%End
%Globals
    /.
#pragma once
#include "LPGLexerprs.h"
#include "tuple.h"
#include "LPGKWLexerprs.h"
#include "LPGParsersym.h"
    ./
%End
%Start
    Keyword
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
    Keyword ::= KeyPrefix a l i a s
        /.$BeginJava
            $setResult($_ALIAS_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix a s t
        /.$BeginJava
            $setResult($_AST_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix d e f i n e
        /.$BeginJava
            $setResult($_DEFINE_KEY);
          $EndJava
        ./
     Keyword ::= KeyPrefix d i s j o i n t p r e d e c e s s o r s e t s
        /.$BeginJava
            $setResult($_DISJOINTPREDECESSORSETS_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix d r o p r u l e s
        /.$BeginJava
            $setResult($_DROPRULES_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix d r o p s y m b o l s
        /.$BeginJava
            $setResult($_DROPSYMBOLS_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix e m p t y
        /.$BeginJava
            $setResult($_EMPTY_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix e n d
        /.$BeginJava
            $setResult($_END_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix e r r o r
        /.$BeginJava
            $setResult($_ERROR_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix e o l
        /.$BeginJava
            $setResult($_EOL_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix e o f
        /.$BeginJava
            $setResult($_EOF_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix e x p o r t
        /.$BeginJava
            $setResult($_EXPORT_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix g l o b a l s
        /.$BeginJava
            $setResult($_GLOBALS_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix h e a d e r s
        /.$BeginJava
            $setResult($_HEADERS_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix i d e n t i f i e r
        /.$BeginJava
            $setResult($_IDENTIFIER_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix i m p o r t
        /.$BeginJava
            $setResult($_IMPORT_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix i n c l u d e
        /.$BeginJava
            $setResult($_INCLUDE_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix k e y w o r d s
        /.$BeginJava
            $setResult($_KEYWORDS_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix s o f t k e y w o r d s
        /.$BeginJava
            $setResult($_SOFT_KEYWORDS_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix n a m e s
        /.$BeginJava
            $setResult($_NAMES_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix n o t i c e
        /.$BeginJava
            $setResult($_NOTICE_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix t e r m i n a l s
        /.$BeginJava
            $setResult($_TERMINALS_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix r e c o v e r
        /.$BeginJava
            $setResult($_RECOVER_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix r u l e s
        /.$BeginJava
            $setResult($_RULES_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix s t a r t 
        /.$BeginJava
            $setResult($_START_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix t r a i l e r s
        /.$BeginJava
            $setResult($_TRAILERS_KEY);
          $EndJava
        ./
    Keyword ::= KeyPrefix t y p e s
        /.$BeginJava
            $setResult($_TYPES_KEY);
          $EndJava
        ./
        
    KeyPrefix -> '$' | '%'
%End
