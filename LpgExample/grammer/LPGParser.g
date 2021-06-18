%options la=6
%options automatic_ast=topLevel,ast_type=ASTNode,visitor=preorder,parent_saved
%options template= btParserTemplateF.gi
%options import_terminals=LPGLexer.gi

%Globals
    /.
        #include <unordered_map>
        #include "LpgData.h"
     ./
%End

%Define
    $ast_class /.Object./
   
%End

%Terminals
    EQUIVALENCE ::= '::='
    PRIORITY_EQUIVALENCE ::= '::=?'
    ARROW ::= '->'
    PRIORITY_ARROW ::= '->?'
    OR_MARKER ::= '|'
    EQUAL ::= '='
    COMMA ::= ','
    LEFT_PAREN  ::= '('
    RIGHT_PAREN ::= ')'
    LEFT_BRACKET ::= '['
    RIGHT_BRACKET ::= ']'
    SHARP ::= '#'
%End

%Start
    LPG
%End

%Headers
    /.

 std::unordered_multimap<std::wstring, LPGParser_top_level_ast::terminal_symbol0*>  terminal_symbol_produce_SYMBOL;
 std::unordered_multimap<std::wstring, LPGParser_top_level_ast::recover_symbol*>  _recover_symbols;
 std::unordered_multimap<std::wstring, LPGParser_top_level_ast::defineSpec*>  _define_specs;
 
 std::unordered_multimap<std::wstring, LPGParser_top_level_ast::nonTerm*>  _non_terms;
 std::unordered_multimap<std::wstring, LPGParser_top_level_ast::terminal*>  _terms;
 std::vector<LPGParser_top_level_ast::ASTNodeToken*>  _macro_name_symbo;
     ./
%End

%Rules
    LPG ::= options_segment LPG_INPUT
    /.
       
        void initialize() {
            
        }
     ./

    LPG_INPUT$$LPG_item ::= %empty
                                |   LPG_INPUT LPG_item

    -- RMF 11/15/2006 - The following non-terminals should be renamed alias_segment_body, etc.
    LPG_item$AliasSeg       ::= ALIAS_KEY$                   alias_segment       END_KEY_OPT$
    LPG_item$AstSeg         ::= AST_KEY$                     ast_segment         END_KEY_OPT$
    LPG_item$DefineSeg      ::= DEFINE_KEY$                  define_segment      END_KEY_OPT$
    LPG_item$EofSeg         ::= EOF_KEY$                     eof_segment         END_KEY_OPT$
    LPG_item$EolSeg         ::= EOL_KEY$                     eol_segment         END_KEY_OPT$
    LPG_item$ErrorSeg       ::= ERROR_KEY$                   error_segment       END_KEY_OPT$
    LPG_item$ExportSeg      ::= EXPORT_KEY$                  export_segment      END_KEY_OPT$
    LPG_item$GlobalsSeg     ::= GLOBALS_KEY$                 globals_segment     END_KEY_OPT$
    LPG_item$HeadersSeg     ::= HEADERS_KEY$                 headers_segment     END_KEY_OPT$
    LPG_item$IdentifierSeg  ::= IDENTIFIER_KEY$              identifier_segment  END_KEY_OPT$
    LPG_item$ImportSeg      ::= IMPORT_KEY$                  import_segment      END_KEY_OPT$
    LPG_item$IncludeSeg     ::= INCLUDE_KEY$                 include_segment     END_KEY_OPT$
    LPG_item$KeywordsSeg    ::= KEYWORDS_KEY$                keywords_segment    END_KEY_OPT$
    LPG_item$NamesSeg       ::= NAMES_KEY$                   names_segment       END_KEY_OPT$
    LPG_item$NoticeSeg      ::= NOTICE_KEY$                  notice_segment      END_KEY_OPT$
    LPG_item$RulesSeg       ::= RULES_KEY$                   rules_segment       END_KEY_OPT$
    LPG_item$SoftKeywordsSeg::= SOFT_KEYWORDS_KEY$           keywords_segment    END_KEY_OPT$
    LPG_item$StartSeg       ::= START_KEY$                   start_segment       END_KEY_OPT$
    LPG_item$TerminalsSeg   ::= TERMINALS_KEY$               terminals_segment   END_KEY_OPT$
    LPG_item$TrailersSeg    ::= TRAILERS_KEY$                trailers_segment    END_KEY_OPT$
    LPG_item$TypesSeg       ::= TYPES_KEY$                   types_segment       END_KEY_OPT$
    LPG_item$RecoverSeg     ::= RECOVER_KEY$                 recover_segment     END_KEY_OPT$
    LPG_item$PredecessorSeg ::= DISJOINTPREDECESSORSETS_KEY$ predecessor_segment END_KEY_OPT$

    -- %options
    options_segment$$option_spec ::= %empty | options_segment option_spec
    option_spec$option_spec ::= OPTIONS_KEY$ option_list
    option_list$$option ::= option | option_list ','$ option
    option ::= SYMBOL option_value
    option_value ::= %empty | '='$ SYMBOL | '='$ '('$ symbol_list ')'$

    symbol_list$$SYMBOL ::= SYMBOL
                          | symbol_list ','$ SYMBOL

    -- $alias
    alias_segment$$aliasSpec ::= aliasSpec | alias_segment aliasSpec

    aliasSpec ::= ERROR_KEY produces alias_rhs
    aliasSpec ::= EOL_KEY produces alias_rhs
    aliasSpec ::= EOF_KEY produces alias_rhs
    aliasSpec ::= IDENTIFIER_KEY produces alias_rhs
    aliasSpec ::= SYMBOL produces alias_rhs
    aliasSpec ::= alias_lhs_macro_name produces alias_rhs

    alias_lhs_macro_name ::= MACRO_NAME -- warning: escape prefix used in symbol

    alias_rhs ::= SYMBOL
    alias_rhs ::= MACRO_NAME -- warning: escape prefix used in symbol
    alias_rhs ::= ERROR_KEY
    alias_rhs ::= EOL_KEY
    alias_rhs ::= EOF_KEY
    alias_rhs ::= EMPTY_KEY
    alias_rhs ::= IDENTIFIER_KEY

    -- $ast
    ast_segment ::= action_segment_list

    -- $define
    define_segment$$defineSpec ::= defineSpec | define_segment defineSpec
    defineSpec ::= macro_name_symbol macro_segment
    /.
        void initialize() {
	environment->_define_specs.insert({getmacro_name_symbol()->toString(), this});
	environment->_macro_name_symbo.push_back(static_cast<ASTNodeToken*>(getmacro_name_symbol()));
        }
     ./

    macro_name_symbol ::= MACRO_NAME
    macro_name_symbol ::= SYMBOL -- warning: escape prefix missing...
    macro_segment ::= BLOCK 

    -- $eol/$eof
    eol_segment ::= terminal_symbol
    eof_segment ::= terminal_symbol

    -- $error
    error_segment ::= terminal_symbol

    -- $export
    export_segment$$terminal_symbol ::= terminal_symbol | export_segment terminal_symbol

    -- $globals
    globals_segment$$action_segment ::= action_segment | globals_segment action_segment

    -- $headers
    headers_segment  ::= action_segment_list

    -- $identifier
    identifier_segment ::= terminal_symbol

    -- $import
    import_segment  ::= SYMBOL drop_command_list

    drop_command_list$$drop_command ::= %empty | drop_command_list drop_command

    drop_command ::= DROPSYMBOLS_KEY drop_symbols
    drop_command ::= DROPRULES_KEY drop_rules

    drop_symbols$$SYMBOL  ::= SYMBOL
    drop_symbols$$SYMBOL  ::= drop_symbols SYMBOL
    drop_rules$$drop_rule ::= drop_rule
    drop_rules$$drop_rule ::= drop_rules drop_rule

    drop_rule ::= SYMBOL optMacroName produces ruleList

    optMacroName ::= %empty | MACRO_NAME

    -- $include
    include_segment ::= SYMBOL

    -- $keywords
    keywords_segment$$keywordSpec ::= keywordSpec | keywords_segment keywordSpec
    keywordSpec ::= terminal_symbol
    keywordSpec ::= terminal_symbol produces name

    -- $names
    names_segment$$nameSpec ::= nameSpec | names_segment nameSpec
    nameSpec ::= name produces name

    name ::= SYMBOL
    name ::= MACRO_NAME -- warning: escape prefix used in symbol
    name ::= EMPTY_KEY 
    name ::= ERROR_KEY 
    name ::= EOL_KEY 
    name ::= IDENTIFIER_KEY

    -- $notice
    notice_segment$$action_segment ::= action_segment | notice_segment action_segment

    -- $rules
    rules_segment ::= action_segment_list nonTermList

    nonTermList$$nonTerm ::= %empty | nonTermList nonTerm

    nonTerm ::= ruleNameWithAttributes produces ruleList
    /.
        void initialize() {
         environment->_non_terms.insert({getruleNameWithAttributes()->getSYMBOL()->toString(), this});
        }
     ./

    -- TODO Rename to nonTermNameWithAttributes
    ruleNameWithAttributes$RuleName ::= SYMBOL -- ruleNameAttributes
    ruleNameWithAttributes$RuleName ::= SYMBOL MACRO_NAME$className
    ruleNameWithAttributes$RuleName ::= SYMBOL MACRO_NAME$className MACRO_NAME$arrayElement

--  ruleNameAttributes$$ruleNameAttribute ::= %empty | ruleNameAttributes ruleNameAttribute
--  ruleNameAttribute ::= MACRO_NAME
--  ruleNameAttribute ::= enumListSpec
--  ruleNameAttribute ::= enumValueSpec
--  ruleNameAttribute ::= enumBitSpec

--  enumListSpec  ::= '['$ className ']'$
--  enumValueSpec ::= '#'$ className '#'$
--  enumBitSpec   ::= '|'$ className '|'$

--  className ::= SYMBOL

    ruleList$$rule ::= rule | ruleList '|'$ rule

    produces ::= '::='
    produces ::= '::=?'
    produces ::= '->'
    produces ::= '->?'

    rule ::= symWithAttrsList opt_action_segment

    symWithAttrsList$$symWithAttrs ::= %empty | symWithAttrsList symWithAttrs

    symWithAttrs ::= EMPTY_KEY
    symWithAttrs ::= SYMBOL optAttrList

    -- TODO rename to 'symAttr'
    optAttrList$symAttrs ::= %empty
    optAttrList$symAttrs ::= MACRO_NAME

    opt_action_segment ::= %empty | action_segment

    action_segment ::= BLOCK 
    /.
    ./

    -- $start
    start_segment$$start_symbol ::= start_symbol | start_segment start_symbol
    start_symbol  ::= SYMBOL 
    start_symbol  ::= MACRO_NAME

    -- $terminals
    terminals_segment$$terminal ::= terminal | terminals_segment terminal
--  terminals_segment ::= terminals_segment terminal_symbol produces name

    terminal ::= terminal_symbol optTerminalAlias
    /.
        void initialize() {
         	environment->_terms.insert({getterminal_symbol()->toString(), this});
        }
     ./
    optTerminalAlias ::= %empty | produces name

    terminal_symbol ::= SYMBOL
    /.
        void initialize() {
            environment->terminal_symbol_produce_SYMBOL.insert({getSYMBOL()->toString(), this});
        }
     ./
    terminal_symbol ::= MACRO_NAME -- warning: escape prefix used in symbol

    -- $trailers
    trailers_segment ::= action_segment_list

    -- $types
    types_segment$$type_declarations ::= type_declarations | types_segment type_declarations
  
    type_declarations     ::= SYMBOL produces barSymbolList opt_action_segment
    barSymbolList$$SYMBOL ::= SYMBOL | barSymbolList '|'$ SYMBOL

    --
    predecessor_segment$$symbol_pair ::= %empty | predecessor_segment symbol_pair

    symbol_pair ::= SYMBOL SYMBOL

    --
    recover_segment$$SYMBOL ::= %empty | recover_segment recover_symbol
    
    recover_symbol ::= SYMBOL
    /.
        void initialize() {
            environment->_recover_symbols.insert({ getSYMBOL()->toString(), this });
        }
     ./

    END_KEY_OPT ::= %empty
    END_KEY_OPT ::= END_KEY 

    action_segment_list$$action_segment ::= %empty
    action_segment_list$$action_segment ::= action_segment_list action_segment 
%End