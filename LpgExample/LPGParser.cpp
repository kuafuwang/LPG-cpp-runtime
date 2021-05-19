
    //#line 351 "dtParserTemplateF.gi

     #include "LPGParser.h"
     void LPGParser::ruleAction(int ruleNumber)
    {
        switch (ruleNumber)
        {

            //
            // Rule 1:  LPG ::= options_segment LPG_INPUT
            //
            case 1: {
               //#line 43 "LPGParser.g"
                setResult(
                    //#line 43 LPGParser.g
                     _automatic_ast_pool << new LPG(this, getLeftIToken(), getRightIToken(),
                            //#line 43 LPGParser.g
                            (IAst*)getRhsSym(1),
                            //#line 43 LPGParser.g
                            (IAst*)getRhsSym(2))
                //#line 43 LPGParser.g
                );
            break;
            }
            //
            // Rule 2:  LPG_INPUT ::= $Empty
            //
            case 2: {
               //#line 48 "LPGParser.g"
                setResult(
                    //#line 48 LPGParser.g
                     _automatic_ast_pool << new LPG_itemList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 48 LPGParser.g
                );
            break;
            }
            //
            // Rule 3:  LPG_INPUT ::= LPG_INPUT LPG_item
            //
            case 3: {
               //#line 49 "LPGParser.g"
                ((LPG_itemList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 4:  LPG_item ::= ALIAS_KEY$ alias_segment END_KEY_OPT$
            //
            case 4: {
               //#line 52 "LPGParser.g"
                setResult(
                    //#line 52 LPGParser.g
                     _automatic_ast_pool << new AliasSeg(getLeftIToken(), getRightIToken(),
                                 //#line 52 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 52 LPGParser.g
                );
            break;
            }
            //
            // Rule 5:  LPG_item ::= AST_KEY$ ast_segment END_KEY_OPT$
            //
            case 5: {
               //#line 53 "LPGParser.g"
                setResult(
                    //#line 53 LPGParser.g
                     _automatic_ast_pool << new AstSeg(getLeftIToken(), getRightIToken(),
                               //#line 53 LPGParser.g
                               (IAst*)getRhsSym(2))
                //#line 53 LPGParser.g
                );
            break;
            }
            //
            // Rule 6:  LPG_item ::= DEFINE_KEY$ define_segment END_KEY_OPT$
            //
            case 6: {
               //#line 54 "LPGParser.g"
                setResult(
                    //#line 54 LPGParser.g
                     _automatic_ast_pool << new DefineSeg(getLeftIToken(), getRightIToken(),
                                  //#line 54 LPGParser.g
                                  (IAst*)getRhsSym(2))
                //#line 54 LPGParser.g
                );
            break;
            }
            //
            // Rule 7:  LPG_item ::= EOF_KEY$ eof_segment END_KEY_OPT$
            //
            case 7: {
               //#line 55 "LPGParser.g"
                setResult(
                    //#line 55 LPGParser.g
                     _automatic_ast_pool << new EofSeg(getLeftIToken(), getRightIToken(),
                               //#line 55 LPGParser.g
                               (IAst*)getRhsSym(2))
                //#line 55 LPGParser.g
                );
            break;
            }
            //
            // Rule 8:  LPG_item ::= EOL_KEY$ eol_segment END_KEY_OPT$
            //
            case 8: {
               //#line 56 "LPGParser.g"
                setResult(
                    //#line 56 LPGParser.g
                     _automatic_ast_pool << new EolSeg(getLeftIToken(), getRightIToken(),
                               //#line 56 LPGParser.g
                               (IAst*)getRhsSym(2))
                //#line 56 LPGParser.g
                );
            break;
            }
            //
            // Rule 9:  LPG_item ::= ERROR_KEY$ error_segment END_KEY_OPT$
            //
            case 9: {
               //#line 57 "LPGParser.g"
                setResult(
                    //#line 57 LPGParser.g
                     _automatic_ast_pool << new ErrorSeg(getLeftIToken(), getRightIToken(),
                                 //#line 57 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 57 LPGParser.g
                );
            break;
            }
            //
            // Rule 10:  LPG_item ::= EXPORT_KEY$ export_segment END_KEY_OPT$
            //
            case 10: {
               //#line 58 "LPGParser.g"
                setResult(
                    //#line 58 LPGParser.g
                     _automatic_ast_pool << new ExportSeg(getLeftIToken(), getRightIToken(),
                                  //#line 58 LPGParser.g
                                  (IAst*)getRhsSym(2))
                //#line 58 LPGParser.g
                );
            break;
            }
            //
            // Rule 11:  LPG_item ::= GLOBALS_KEY$ globals_segment END_KEY_OPT$
            //
            case 11: {
               //#line 59 "LPGParser.g"
                setResult(
                    //#line 59 LPGParser.g
                     _automatic_ast_pool << new GlobalsSeg(getLeftIToken(), getRightIToken(),
                                   //#line 59 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 59 LPGParser.g
                );
            break;
            }
            //
            // Rule 12:  LPG_item ::= HEADERS_KEY$ headers_segment END_KEY_OPT$
            //
            case 12: {
               //#line 60 "LPGParser.g"
                setResult(
                    //#line 60 LPGParser.g
                     _automatic_ast_pool << new HeadersSeg(getLeftIToken(), getRightIToken(),
                                   //#line 60 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 60 LPGParser.g
                );
            break;
            }
            //
            // Rule 13:  LPG_item ::= IDENTIFIER_KEY$ identifier_segment END_KEY_OPT$
            //
            case 13: {
               //#line 61 "LPGParser.g"
                setResult(
                    //#line 61 LPGParser.g
                     _automatic_ast_pool << new IdentifierSeg(getLeftIToken(), getRightIToken(),
                                      //#line 61 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 61 LPGParser.g
                );
            break;
            }
            //
            // Rule 14:  LPG_item ::= IMPORT_KEY$ import_segment END_KEY_OPT$
            //
            case 14: {
               //#line 62 "LPGParser.g"
                setResult(
                    //#line 62 LPGParser.g
                     _automatic_ast_pool << new ImportSeg(getLeftIToken(), getRightIToken(),
                                  //#line 62 LPGParser.g
                                  (IAst*)getRhsSym(2))
                //#line 62 LPGParser.g
                );
            break;
            }
            //
            // Rule 15:  LPG_item ::= INCLUDE_KEY$ include_segment END_KEY_OPT$
            //
            case 15: {
               //#line 63 "LPGParser.g"
                setResult(
                    //#line 63 LPGParser.g
                     _automatic_ast_pool << new IncludeSeg(getLeftIToken(), getRightIToken(),
                                   //#line 63 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 63 LPGParser.g
                );
            break;
            }
            //
            // Rule 16:  LPG_item ::= KEYWORDS_KEY$ keywords_segment END_KEY_OPT$
            //
            case 16: {
               //#line 64 "LPGParser.g"
                setResult(
                    //#line 64 LPGParser.g
                     _automatic_ast_pool << new KeywordsSeg(getLeftIToken(), getRightIToken(),
                                    //#line 64 LPGParser.g
                                    (IAst*)getRhsSym(2))
                //#line 64 LPGParser.g
                );
            break;
            }
            //
            // Rule 17:  LPG_item ::= NAMES_KEY$ names_segment END_KEY_OPT$
            //
            case 17: {
               //#line 65 "LPGParser.g"
                setResult(
                    //#line 65 LPGParser.g
                     _automatic_ast_pool << new NamesSeg(getLeftIToken(), getRightIToken(),
                                 //#line 65 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 65 LPGParser.g
                );
            break;
            }
            //
            // Rule 18:  LPG_item ::= NOTICE_KEY$ notice_segment END_KEY_OPT$
            //
            case 18: {
               //#line 66 "LPGParser.g"
                setResult(
                    //#line 66 LPGParser.g
                     _automatic_ast_pool << new NoticeSeg(getLeftIToken(), getRightIToken(),
                                  //#line 66 LPGParser.g
                                  (IAst*)getRhsSym(2))
                //#line 66 LPGParser.g
                );
            break;
            }
            //
            // Rule 19:  LPG_item ::= RULES_KEY$ rules_segment END_KEY_OPT$
            //
            case 19: {
               //#line 67 "LPGParser.g"
                setResult(
                    //#line 67 LPGParser.g
                     _automatic_ast_pool << new RulesSeg(getLeftIToken(), getRightIToken(),
                                 //#line 67 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 67 LPGParser.g
                );
            break;
            }
            //
            // Rule 20:  LPG_item ::= SOFT_KEYWORDS_KEY$ keywords_segment END_KEY_OPT$
            //
            case 20: {
               //#line 68 "LPGParser.g"
                setResult(
                    //#line 68 LPGParser.g
                     _automatic_ast_pool << new SoftKeywordsSeg(getLeftIToken(), getRightIToken(),
                                        //#line 68 LPGParser.g
                                        (IAst*)getRhsSym(2))
                //#line 68 LPGParser.g
                );
            break;
            }
            //
            // Rule 21:  LPG_item ::= START_KEY$ start_segment END_KEY_OPT$
            //
            case 21: {
               //#line 69 "LPGParser.g"
                setResult(
                    //#line 69 LPGParser.g
                     _automatic_ast_pool << new StartSeg(getLeftIToken(), getRightIToken(),
                                 //#line 69 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 69 LPGParser.g
                );
            break;
            }
            //
            // Rule 22:  LPG_item ::= TERMINALS_KEY$ terminals_segment END_KEY_OPT$
            //
            case 22: {
               //#line 70 "LPGParser.g"
                setResult(
                    //#line 70 LPGParser.g
                     _automatic_ast_pool << new TerminalsSeg(getLeftIToken(), getRightIToken(),
                                     //#line 70 LPGParser.g
                                     (IAst*)getRhsSym(2))
                //#line 70 LPGParser.g
                );
            break;
            }
            //
            // Rule 23:  LPG_item ::= TRAILERS_KEY$ trailers_segment END_KEY_OPT$
            //
            case 23: {
               //#line 71 "LPGParser.g"
                setResult(
                    //#line 71 LPGParser.g
                     _automatic_ast_pool << new TrailersSeg(getLeftIToken(), getRightIToken(),
                                    //#line 71 LPGParser.g
                                    (IAst*)getRhsSym(2))
                //#line 71 LPGParser.g
                );
            break;
            }
            //
            // Rule 24:  LPG_item ::= TYPES_KEY$ types_segment END_KEY_OPT$
            //
            case 24: {
               //#line 72 "LPGParser.g"
                setResult(
                    //#line 72 LPGParser.g
                     _automatic_ast_pool << new TypesSeg(getLeftIToken(), getRightIToken(),
                                 //#line 72 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 72 LPGParser.g
                );
            break;
            }
            //
            // Rule 25:  LPG_item ::= RECOVER_KEY$ recover_segment END_KEY_OPT$
            //
            case 25: {
               //#line 73 "LPGParser.g"
                setResult(
                    //#line 73 LPGParser.g
                     _automatic_ast_pool << new RecoverSeg(getLeftIToken(), getRightIToken(),
                                   //#line 73 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 73 LPGParser.g
                );
            break;
            }
            //
            // Rule 26:  LPG_item ::= DISJOINTPREDECESSORSETS_KEY$ predecessor_segment END_KEY_OPT$
            //
            case 26: {
               //#line 74 "LPGParser.g"
                setResult(
                    //#line 74 LPGParser.g
                     _automatic_ast_pool << new PredecessorSeg(getLeftIToken(), getRightIToken(),
                                       //#line 74 LPGParser.g
                                       (IAst*)getRhsSym(2))
                //#line 74 LPGParser.g
                );
            break;
            }
            //
            // Rule 27:  options_segment ::= $Empty
            //
            case 27: {
               //#line 77 "LPGParser.g"
                setResult(
                    //#line 77 LPGParser.g
                     _automatic_ast_pool << new option_specList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 77 LPGParser.g
                );
            break;
            }
            //
            // Rule 28:  options_segment ::= options_segment option_spec
            //
            case 28: {
               //#line 77 "LPGParser.g"
                ((option_specList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 29:  option_spec ::= OPTIONS_KEY$ option_list
            //
            case 29: {
               //#line 78 "LPGParser.g"
                setResult(
                    //#line 78 LPGParser.g
                     _automatic_ast_pool << new option_spec(getLeftIToken(), getRightIToken(),
                                    //#line 78 LPGParser.g
                                    (IAst*)getRhsSym(2))
                //#line 78 LPGParser.g
                );
            break;
            }
            //
            // Rule 30:  option_list ::= option
            //
            case 30: {
               //#line 79 "LPGParser.g"
                setResult(
                    //#line 79 LPGParser.g
                     _automatic_ast_pool << new optionList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 79 LPGParser.g
                );
            break;
            }
            //
            // Rule 31:  option_list ::= option_list ,$ option
            //
            case 31: {
               //#line 79 "LPGParser.g"
                ((optionList*)getRhsSym(1))->addElement((IAst*)getRhsSym(3));
            break;
            }
            //
            // Rule 32:  option ::= SYMBOL option_value
            //
            case 32: {
               //#line 80 "LPGParser.g"
                setResult(
                    //#line 80 LPGParser.g
                     _automatic_ast_pool << new option(getLeftIToken(), getRightIToken(),
                               //#line 80 LPGParser.g
                                _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                               //#line 80 LPGParser.g
                               (IAst*)getRhsSym(2))
                //#line 80 LPGParser.g
                );
            break;
            }
            //
            // Rule 33:  option_value ::= $Empty
            //
            case 33: {
               //#line 81 "LPGParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 34:  option_value ::= =$ SYMBOL
            //
            case 34: {
               //#line 81 "LPGParser.g"
                setResult(
                    //#line 81 LPGParser.g
                     _automatic_ast_pool << new option_value0(getLeftIToken(), getRightIToken(),
                                      //#line 81 LPGParser.g
                                       _automatic_ast_pool << new ASTNodeToken(getRhsIToken(2)))
                //#line 81 LPGParser.g
                );
            break;
            }
            //
            // Rule 35:  option_value ::= =$ ($ symbol_list )$
            //
            case 35: {
               //#line 81 "LPGParser.g"
                setResult(
                    //#line 81 LPGParser.g
                     _automatic_ast_pool << new option_value1(getLeftIToken(), getRightIToken(),
                                      //#line 81 LPGParser.g
                                      (IAst*)getRhsSym(3))
                //#line 81 LPGParser.g
                );
            break;
            }
            //
            // Rule 36:  symbol_list ::= SYMBOL
            //
            case 36: {
               //#line 83 "LPGParser.g"
                setResult(
                    //#line 83 LPGParser.g
                     _automatic_ast_pool << new SYMBOLList( _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)), true /* left recursive */)
                //#line 83 LPGParser.g
                );
            break;
            }
            //
            // Rule 37:  symbol_list ::= symbol_list ,$ SYMBOL
            //
            case 37: {
               //#line 84 "LPGParser.g"
                ((SYMBOLList*)getRhsSym(1))->addElement( _automatic_ast_pool << new ASTNodeToken(getRhsIToken(3)));
            break;
            }
            //
            // Rule 38:  alias_segment ::= aliasSpec
            //
            case 38: {
               //#line 87 "LPGParser.g"
                setResult(
                    //#line 87 LPGParser.g
                     _automatic_ast_pool << new aliasSpecList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 87 LPGParser.g
                );
            break;
            }
            //
            // Rule 39:  alias_segment ::= alias_segment aliasSpec
            //
            case 39: {
               //#line 87 "LPGParser.g"
                ((aliasSpecList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 40:  aliasSpec ::= ERROR_KEY produces alias_rhs
            //
            case 40: {
               //#line 89 "LPGParser.g"
                setResult(
                    //#line 89 LPGParser.g
                     _automatic_ast_pool << new aliasSpec0(getLeftIToken(), getRightIToken(),
                                   //#line 89 LPGParser.g
                                    _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                   //#line 89 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 89 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 89 LPGParser.g
                );
            break;
            }
            //
            // Rule 41:  aliasSpec ::= EOL_KEY produces alias_rhs
            //
            case 41: {
               //#line 90 "LPGParser.g"
                setResult(
                    //#line 90 LPGParser.g
                     _automatic_ast_pool << new aliasSpec1(getLeftIToken(), getRightIToken(),
                                   //#line 90 LPGParser.g
                                    _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                   //#line 90 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 90 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 90 LPGParser.g
                );
            break;
            }
            //
            // Rule 42:  aliasSpec ::= EOF_KEY produces alias_rhs
            //
            case 42: {
               //#line 91 "LPGParser.g"
                setResult(
                    //#line 91 LPGParser.g
                     _automatic_ast_pool << new aliasSpec2(getLeftIToken(), getRightIToken(),
                                   //#line 91 LPGParser.g
                                    _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                   //#line 91 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 91 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 91 LPGParser.g
                );
            break;
            }
            //
            // Rule 43:  aliasSpec ::= IDENTIFIER_KEY produces alias_rhs
            //
            case 43: {
               //#line 92 "LPGParser.g"
                setResult(
                    //#line 92 LPGParser.g
                     _automatic_ast_pool << new aliasSpec3(getLeftIToken(), getRightIToken(),
                                   //#line 92 LPGParser.g
                                    _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                   //#line 92 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 92 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 92 LPGParser.g
                );
            break;
            }
            //
            // Rule 44:  aliasSpec ::= SYMBOL produces alias_rhs
            //
            case 44: {
               //#line 93 "LPGParser.g"
                setResult(
                    //#line 93 LPGParser.g
                     _automatic_ast_pool << new aliasSpec4(getLeftIToken(), getRightIToken(),
                                   //#line 93 LPGParser.g
                                    _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                   //#line 93 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 93 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 93 LPGParser.g
                );
            break;
            }
            //
            // Rule 45:  aliasSpec ::= alias_lhs_macro_name produces alias_rhs
            //
            case 45: {
               //#line 94 "LPGParser.g"
                setResult(
                    //#line 94 LPGParser.g
                     _automatic_ast_pool << new aliasSpec5(getLeftIToken(), getRightIToken(),
                                   //#line 94 LPGParser.g
                                   (IAst*)getRhsSym(1),
                                   //#line 94 LPGParser.g
                                   (IAst*)getRhsSym(2),
                                   //#line 94 LPGParser.g
                                   (IAst*)getRhsSym(3))
                //#line 94 LPGParser.g
                );
            break;
            }
            //
            // Rule 46:  alias_lhs_macro_name ::= MACRO_NAME
            //
            case 46: {
               //#line 96 "LPGParser.g"
                setResult(
                    //#line 96 LPGParser.g
                     _automatic_ast_pool << new alias_lhs_macro_name(getRhsIToken(1))
                //#line 96 LPGParser.g
                );
            break;
            }
            //
            // Rule 47:  alias_rhs ::= SYMBOL
            //
            case 47: {
               //#line 98 "LPGParser.g"
                setResult(
                    //#line 98 LPGParser.g
                     _automatic_ast_pool << new alias_rhs0(getRhsIToken(1))
                //#line 98 LPGParser.g
                );
            break;
            }
            //
            // Rule 48:  alias_rhs ::= MACRO_NAME
            //
            case 48: {
               //#line 99 "LPGParser.g"
                setResult(
                    //#line 99 LPGParser.g
                     _automatic_ast_pool << new alias_rhs1(getRhsIToken(1))
                //#line 99 LPGParser.g
                );
            break;
            }
            //
            // Rule 49:  alias_rhs ::= ERROR_KEY
            //
            case 49: {
               //#line 100 "LPGParser.g"
                setResult(
                    //#line 100 LPGParser.g
                     _automatic_ast_pool << new alias_rhs2(getRhsIToken(1))
                //#line 100 LPGParser.g
                );
            break;
            }
            //
            // Rule 50:  alias_rhs ::= EOL_KEY
            //
            case 50: {
               //#line 101 "LPGParser.g"
                setResult(
                    //#line 101 LPGParser.g
                     _automatic_ast_pool << new alias_rhs3(getRhsIToken(1))
                //#line 101 LPGParser.g
                );
            break;
            }
            //
            // Rule 51:  alias_rhs ::= EOF_KEY
            //
            case 51: {
               //#line 102 "LPGParser.g"
                setResult(
                    //#line 102 LPGParser.g
                     _automatic_ast_pool << new alias_rhs4(getRhsIToken(1))
                //#line 102 LPGParser.g
                );
            break;
            }
            //
            // Rule 52:  alias_rhs ::= EMPTY_KEY
            //
            case 52: {
               //#line 103 "LPGParser.g"
                setResult(
                    //#line 103 LPGParser.g
                     _automatic_ast_pool << new alias_rhs5(getRhsIToken(1))
                //#line 103 LPGParser.g
                );
            break;
            }
            //
            // Rule 53:  alias_rhs ::= IDENTIFIER_KEY
            //
            case 53: {
               //#line 104 "LPGParser.g"
                setResult(
                    //#line 104 LPGParser.g
                     _automatic_ast_pool << new alias_rhs6(getRhsIToken(1))
                //#line 104 LPGParser.g
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
               //#line 110 "LPGParser.g"
                setResult(
                    //#line 110 LPGParser.g
                     _automatic_ast_pool << new defineSpecList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 110 LPGParser.g
                );
            break;
            }
            //
            // Rule 56:  define_segment ::= define_segment defineSpec
            //
            case 56: {
               //#line 110 "LPGParser.g"
                ((defineSpecList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 57:  defineSpec ::= macro_name_symbol macro_segment
            //
            case 57: {
               //#line 111 "LPGParser.g"
                setResult(
                    //#line 111 LPGParser.g
                     _automatic_ast_pool << new defineSpec(this, getLeftIToken(), getRightIToken(),
                                   //#line 111 LPGParser.g
                                   (IAst*)getRhsSym(1),
                                   //#line 111 LPGParser.g
                                   (IAst*)getRhsSym(2))
                //#line 111 LPGParser.g
                );
            break;
            }
            //
            // Rule 58:  macro_name_symbol ::= MACRO_NAME
            //
            case 58: {
               //#line 116 "LPGParser.g"
                setResult(
                    //#line 116 LPGParser.g
                     _automatic_ast_pool << new macro_name_symbol0(getRhsIToken(1))
                //#line 116 LPGParser.g
                );
            break;
            }
            //
            // Rule 59:  macro_name_symbol ::= SYMBOL
            //
            case 59: {
               //#line 117 "LPGParser.g"
                setResult(
                    //#line 117 LPGParser.g
                     _automatic_ast_pool << new macro_name_symbol1(getRhsIToken(1))
                //#line 117 LPGParser.g
                );
            break;
            }
            //
            // Rule 60:  macro_segment ::= BLOCK
            //
            case 60: {
               //#line 118 "LPGParser.g"
                setResult(
                    //#line 118 LPGParser.g
                     _automatic_ast_pool << new macro_segment(getRhsIToken(1))
                //#line 118 LPGParser.g
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
               //#line 128 "LPGParser.g"
                setResult(
                    //#line 128 LPGParser.g
                     _automatic_ast_pool << new terminal_symbolList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 128 LPGParser.g
                );
            break;
            }
            //
            // Rule 65:  export_segment ::= export_segment terminal_symbol
            //
            case 65: {
               //#line 128 "LPGParser.g"
                ((terminal_symbolList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 66:  globals_segment ::= action_segment
            //
            case 66: {
               //#line 131 "LPGParser.g"
                setResult(
                    //#line 131 LPGParser.g
                     _automatic_ast_pool << new action_segmentList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 131 LPGParser.g
                );
            break;
            }
            //
            // Rule 67:  globals_segment ::= globals_segment action_segment
            //
            case 67: {
               //#line 131 "LPGParser.g"
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
               //#line 140 "LPGParser.g"
                setResult(
                    //#line 140 LPGParser.g
                     _automatic_ast_pool << new import_segment(getLeftIToken(), getRightIToken(),
                                       //#line 140 LPGParser.g
                                        _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                       //#line 140 LPGParser.g
                                       (IAst*)getRhsSym(2))
                //#line 140 LPGParser.g
                );
            break;
            }
            //
            // Rule 71:  drop_command_list ::= $Empty
            //
            case 71: {
               //#line 142 "LPGParser.g"
                setResult(
                    //#line 142 LPGParser.g
                     _automatic_ast_pool << new drop_commandList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 142 LPGParser.g
                );
            break;
            }
            //
            // Rule 72:  drop_command_list ::= drop_command_list drop_command
            //
            case 72: {
               //#line 142 "LPGParser.g"
                ((drop_commandList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 73:  drop_command ::= DROPSYMBOLS_KEY drop_symbols
            //
            case 73: {
               //#line 144 "LPGParser.g"
                setResult(
                    //#line 144 LPGParser.g
                     _automatic_ast_pool << new drop_command0(getLeftIToken(), getRightIToken(),
                                      //#line 144 LPGParser.g
                                       _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                      //#line 144 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 144 LPGParser.g
                );
            break;
            }
            //
            // Rule 74:  drop_command ::= DROPRULES_KEY drop_rules
            //
            case 74: {
               //#line 145 "LPGParser.g"
                setResult(
                    //#line 145 LPGParser.g
                     _automatic_ast_pool << new drop_command1(getLeftIToken(), getRightIToken(),
                                      //#line 145 LPGParser.g
                                       _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                      //#line 145 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 145 LPGParser.g
                );
            break;
            }
            //
            // Rule 75:  drop_symbols ::= SYMBOL
            //
            case 75: {
               //#line 147 "LPGParser.g"
                setResult(
                    //#line 147 LPGParser.g
                     _automatic_ast_pool << new SYMBOLList( _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)), true /* left recursive */)
                //#line 147 LPGParser.g
                );
            break;
            }
            //
            // Rule 76:  drop_symbols ::= drop_symbols SYMBOL
            //
            case 76: {
               //#line 148 "LPGParser.g"
                ((SYMBOLList*)getRhsSym(1))->addElement( _automatic_ast_pool << new ASTNodeToken(getRhsIToken(2)));
            break;
            }
            //
            // Rule 77:  drop_rules ::= drop_rule
            //
            case 77: {
               //#line 149 "LPGParser.g"
                setResult(
                    //#line 149 LPGParser.g
                     _automatic_ast_pool << new drop_ruleList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 149 LPGParser.g
                );
            break;
            }
            //
            // Rule 78:  drop_rules ::= drop_rules drop_rule
            //
            case 78: {
               //#line 150 "LPGParser.g"
                ((drop_ruleList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 79:  drop_rule ::= SYMBOL optMacroName produces ruleList
            //
            case 79: {
               //#line 152 "LPGParser.g"
                setResult(
                    //#line 152 LPGParser.g
                     _automatic_ast_pool << new drop_rule(getLeftIToken(), getRightIToken(),
                                  //#line 152 LPGParser.g
                                   _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                  //#line 152 LPGParser.g
                                  (IAst*)getRhsSym(2),
                                  //#line 152 LPGParser.g
                                  (IAst*)getRhsSym(3),
                                  //#line 152 LPGParser.g
                                  (IAst*)getRhsSym(4))
                //#line 152 LPGParser.g
                );
            break;
            }
            //
            // Rule 80:  optMacroName ::= $Empty
            //
            case 80: {
               //#line 154 "LPGParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 81:  optMacroName ::= MACRO_NAME
            //
            case 81: {
               //#line 154 "LPGParser.g"
                setResult(
                    //#line 154 LPGParser.g
                     _automatic_ast_pool << new optMacroName(getRhsIToken(1))
                //#line 154 LPGParser.g
                );
            break;
            }
            //
            // Rule 82:  include_segment ::= SYMBOL
            //
            case 82: {
               //#line 157 "LPGParser.g"
                setResult(
                    //#line 157 LPGParser.g
                     _automatic_ast_pool << new include_segment(getRhsIToken(1))
                //#line 157 LPGParser.g
                );
            break;
            }
            //
            // Rule 83:  keywords_segment ::= keywordSpec
            //
            case 83: {
               //#line 160 "LPGParser.g"
                setResult(
                    //#line 160 LPGParser.g
                     _automatic_ast_pool << new keywordSpecList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 160 LPGParser.g
                );
            break;
            }
            //
            // Rule 84:  keywords_segment ::= keywords_segment keywordSpec
            //
            case 84: {
               //#line 160 "LPGParser.g"
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
               //#line 162 "LPGParser.g"
                setResult(
                    //#line 162 LPGParser.g
                     _automatic_ast_pool << new keywordSpec(getLeftIToken(), getRightIToken(),
                                    //#line 162 LPGParser.g
                                    (IAst*)getRhsSym(1),
                                    //#line 162 LPGParser.g
                                    (IAst*)getRhsSym(2),
                                    //#line 162 LPGParser.g
                                    (IAst*)getRhsSym(3))
                //#line 162 LPGParser.g
                );
            break;
            }
            //
            // Rule 87:  names_segment ::= nameSpec
            //
            case 87: {
               //#line 165 "LPGParser.g"
                setResult(
                    //#line 165 LPGParser.g
                     _automatic_ast_pool << new nameSpecList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 165 LPGParser.g
                );
            break;
            }
            //
            // Rule 88:  names_segment ::= names_segment nameSpec
            //
            case 88: {
               //#line 165 "LPGParser.g"
                ((nameSpecList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 89:  nameSpec ::= name produces name
            //
            case 89: {
               //#line 166 "LPGParser.g"
                setResult(
                    //#line 166 LPGParser.g
                     _automatic_ast_pool << new nameSpec(getLeftIToken(), getRightIToken(),
                                 //#line 166 LPGParser.g
                                 (IAst*)getRhsSym(1),
                                 //#line 166 LPGParser.g
                                 (IAst*)getRhsSym(2),
                                 //#line 166 LPGParser.g
                                 (IAst*)getRhsSym(3))
                //#line 166 LPGParser.g
                );
            break;
            }
            //
            // Rule 90:  name ::= SYMBOL
            //
            case 90: {
               //#line 168 "LPGParser.g"
                setResult(
                    //#line 168 LPGParser.g
                     _automatic_ast_pool << new name0(getRhsIToken(1))
                //#line 168 LPGParser.g
                );
            break;
            }
            //
            // Rule 91:  name ::= MACRO_NAME
            //
            case 91: {
               //#line 169 "LPGParser.g"
                setResult(
                    //#line 169 LPGParser.g
                     _automatic_ast_pool << new name1(getRhsIToken(1))
                //#line 169 LPGParser.g
                );
            break;
            }
            //
            // Rule 92:  name ::= EMPTY_KEY
            //
            case 92: {
               //#line 170 "LPGParser.g"
                setResult(
                    //#line 170 LPGParser.g
                     _automatic_ast_pool << new name2(getRhsIToken(1))
                //#line 170 LPGParser.g
                );
            break;
            }
            //
            // Rule 93:  name ::= ERROR_KEY
            //
            case 93: {
               //#line 171 "LPGParser.g"
                setResult(
                    //#line 171 LPGParser.g
                     _automatic_ast_pool << new name3(getRhsIToken(1))
                //#line 171 LPGParser.g
                );
            break;
            }
            //
            // Rule 94:  name ::= EOL_KEY
            //
            case 94: {
               //#line 172 "LPGParser.g"
                setResult(
                    //#line 172 LPGParser.g
                     _automatic_ast_pool << new name4(getRhsIToken(1))
                //#line 172 LPGParser.g
                );
            break;
            }
            //
            // Rule 95:  name ::= IDENTIFIER_KEY
            //
            case 95: {
               //#line 173 "LPGParser.g"
                setResult(
                    //#line 173 LPGParser.g
                     _automatic_ast_pool << new name5(getRhsIToken(1))
                //#line 173 LPGParser.g
                );
            break;
            }
            //
            // Rule 96:  notice_segment ::= action_segment
            //
            case 96: {
               //#line 176 "LPGParser.g"
                setResult(
                    //#line 176 LPGParser.g
                     _automatic_ast_pool << new action_segmentList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 176 LPGParser.g
                );
            break;
            }
            //
            // Rule 97:  notice_segment ::= notice_segment action_segment
            //
            case 97: {
               //#line 176 "LPGParser.g"
                ((action_segmentList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 98:  rules_segment ::= action_segment_list nonTermList
            //
            case 98: {
               //#line 179 "LPGParser.g"
                setResult(
                    //#line 179 LPGParser.g
                     _automatic_ast_pool << new rules_segment(getLeftIToken(), getRightIToken(),
                                      //#line 179 LPGParser.g
                                      (IAst*)getRhsSym(1),
                                      //#line 179 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 179 LPGParser.g
                );
            break;
            }
            //
            // Rule 99:  nonTermList ::= $Empty
            //
            case 99: {
               //#line 181 "LPGParser.g"
                setResult(
                    //#line 181 LPGParser.g
                     _automatic_ast_pool << new nonTermList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 181 LPGParser.g
                );
            break;
            }
            //
            // Rule 100:  nonTermList ::= nonTermList nonTerm
            //
            case 100: {
               //#line 181 "LPGParser.g"
                ((nonTermList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 101:  nonTerm ::= ruleNameWithAttributes produces ruleList
            //
            case 101: {
               //#line 183 "LPGParser.g"
                setResult(
                    //#line 183 LPGParser.g
                     _automatic_ast_pool << new nonTerm(this, getLeftIToken(), getRightIToken(),
                                //#line 183 LPGParser.g
                                (IAst*)getRhsSym(1),
                                //#line 183 LPGParser.g
                                (IAst*)getRhsSym(2),
                                //#line 183 LPGParser.g
                                (IAst*)getRhsSym(3))
                //#line 183 LPGParser.g
                );
            break;
            }
            //
            // Rule 102:  ruleNameWithAttributes ::= SYMBOL
            //
            case 102: {
               //#line 189 "LPGParser.g"
                setResult(
                    //#line 189 LPGParser.g
                     _automatic_ast_pool << new RuleName(getLeftIToken(), getRightIToken(),
                                 //#line 189 LPGParser.g
                                  _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                 //#line 189 LPGParser.g
                                 nullptr,
                                 //#line 189 LPGParser.g
                                 nullptr)
                //#line 189 LPGParser.g
                );
            break;
            }
            //
            // Rule 103:  ruleNameWithAttributes ::= SYMBOL MACRO_NAME$className
            //
            case 103: {
               //#line 190 "LPGParser.g"
                setResult(
                    //#line 190 LPGParser.g
                     _automatic_ast_pool << new RuleName(getLeftIToken(), getRightIToken(),
                                 //#line 190 LPGParser.g
                                  _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                 //#line 190 LPGParser.g
                                  _automatic_ast_pool << new ASTNodeToken(getRhsIToken(2)),
                                 //#line 190 LPGParser.g
                                 nullptr)
                //#line 190 LPGParser.g
                );
            break;
            }
            //
            // Rule 104:  ruleNameWithAttributes ::= SYMBOL MACRO_NAME$className MACRO_NAME$arrayElement
            //
            case 104: {
               //#line 191 "LPGParser.g"
                setResult(
                    //#line 191 LPGParser.g
                     _automatic_ast_pool << new RuleName(getLeftIToken(), getRightIToken(),
                                 //#line 191 LPGParser.g
                                  _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                 //#line 191 LPGParser.g
                                  _automatic_ast_pool << new ASTNodeToken(getRhsIToken(2)),
                                 //#line 191 LPGParser.g
                                  _automatic_ast_pool << new ASTNodeToken(getRhsIToken(3)))
                //#line 191 LPGParser.g
                );
            break;
            }
            //
            // Rule 105:  ruleList ::= rule
            //
            case 105: {
               //#line 205 "LPGParser.g"
                setResult(
                    //#line 205 LPGParser.g
                     _automatic_ast_pool << new ruleList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 205 LPGParser.g
                );
            break;
            }
            //
            // Rule 106:  ruleList ::= ruleList |$ rule
            //
            case 106: {
               //#line 205 "LPGParser.g"
                ((ruleList*)getRhsSym(1))->addElement((IAst*)getRhsSym(3));
            break;
            }
            //
            // Rule 107:  produces ::= ::=
            //
            case 107: {
               //#line 207 "LPGParser.g"
                setResult(
                    //#line 207 LPGParser.g
                     _automatic_ast_pool << new produces0(getRhsIToken(1))
                //#line 207 LPGParser.g
                );
            break;
            }
            //
            // Rule 108:  produces ::= ::=?
            //
            case 108: {
               //#line 208 "LPGParser.g"
                setResult(
                    //#line 208 LPGParser.g
                     _automatic_ast_pool << new produces1(getRhsIToken(1))
                //#line 208 LPGParser.g
                );
            break;
            }
            //
            // Rule 109:  produces ::= ->
            //
            case 109: {
               //#line 209 "LPGParser.g"
                setResult(
                    //#line 209 LPGParser.g
                     _automatic_ast_pool << new produces2(getRhsIToken(1))
                //#line 209 LPGParser.g
                );
            break;
            }
            //
            // Rule 110:  produces ::= ->?
            //
            case 110: {
               //#line 210 "LPGParser.g"
                setResult(
                    //#line 210 LPGParser.g
                     _automatic_ast_pool << new produces3(getRhsIToken(1))
                //#line 210 LPGParser.g
                );
            break;
            }
            //
            // Rule 111:  rule ::= symWithAttrsList opt_action_segment
            //
            case 111: {
               //#line 212 "LPGParser.g"
                setResult(
                    //#line 212 LPGParser.g
                     _automatic_ast_pool << new rule(getLeftIToken(), getRightIToken(),
                             //#line 212 LPGParser.g
                             (IAst*)getRhsSym(1),
                             //#line 212 LPGParser.g
                             (IAst*)getRhsSym(2))
                //#line 212 LPGParser.g
                );
            break;
            }
            //
            // Rule 112:  symWithAttrsList ::= $Empty
            //
            case 112: {
               //#line 214 "LPGParser.g"
                setResult(
                    //#line 214 LPGParser.g
                     _automatic_ast_pool << new symWithAttrsList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 214 LPGParser.g
                );
            break;
            }
            //
            // Rule 113:  symWithAttrsList ::= symWithAttrsList symWithAttrs
            //
            case 113: {
               //#line 214 "LPGParser.g"
                ((symWithAttrsList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 114:  symWithAttrs ::= EMPTY_KEY
            //
            case 114: {
               //#line 216 "LPGParser.g"
                setResult(
                    //#line 216 LPGParser.g
                     _automatic_ast_pool << new symWithAttrs0(getRhsIToken(1))
                //#line 216 LPGParser.g
                );
            break;
            }
            //
            // Rule 115:  symWithAttrs ::= SYMBOL optAttrList
            //
            case 115: {
               //#line 217 "LPGParser.g"
                setResult(
                    //#line 217 LPGParser.g
                     _automatic_ast_pool << new symWithAttrs1(getLeftIToken(), getRightIToken(),
                                      //#line 217 LPGParser.g
                                       _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                      //#line 217 LPGParser.g
                                      (IAst*)getRhsSym(2))
                //#line 217 LPGParser.g
                );
            break;
            }
            //
            // Rule 116:  optAttrList ::= $Empty
            //
            case 116: {
               //#line 220 "LPGParser.g"
                setResult(
                    //#line 220 LPGParser.g
                     _automatic_ast_pool << new symAttrs(getLeftIToken(), getRightIToken(),
                                 //#line 220 LPGParser.g
                                 nullptr)
                //#line 220 LPGParser.g
                );
            break;
            }
            //
            // Rule 117:  optAttrList ::= MACRO_NAME
            //
            case 117: {
               //#line 221 "LPGParser.g"
                setResult(
                    //#line 221 LPGParser.g
                     _automatic_ast_pool << new symAttrs(getLeftIToken(), getRightIToken(),
                                 //#line 221 LPGParser.g
                                  _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)))
                //#line 221 LPGParser.g
                );
            break;
            }
            //
            // Rule 118:  opt_action_segment ::= $Empty
            //
            case 118: {
               //#line 223 "LPGParser.g"
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
               //#line 225 "LPGParser.g"
                setResult(
                    //#line 225 LPGParser.g
                     _automatic_ast_pool << new action_segment(this, getRhsIToken(1))
                //#line 225 LPGParser.g
                );
            break;
            }
            //
            // Rule 121:  start_segment ::= start_symbol
            //
            case 121: {
               //#line 231 "LPGParser.g"
                setResult(
                    //#line 231 LPGParser.g
                     _automatic_ast_pool << new start_symbolList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 231 LPGParser.g
                );
            break;
            }
            //
            // Rule 122:  start_segment ::= start_segment start_symbol
            //
            case 122: {
               //#line 231 "LPGParser.g"
                ((start_symbolList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 123:  start_symbol ::= SYMBOL
            //
            case 123: {
               //#line 232 "LPGParser.g"
                setResult(
                    //#line 232 LPGParser.g
                     _automatic_ast_pool << new start_symbol0(getRhsIToken(1))
                //#line 232 LPGParser.g
                );
            break;
            }
            //
            // Rule 124:  start_symbol ::= MACRO_NAME
            //
            case 124: {
               //#line 233 "LPGParser.g"
                setResult(
                    //#line 233 LPGParser.g
                     _automatic_ast_pool << new start_symbol1(getRhsIToken(1))
                //#line 233 LPGParser.g
                );
            break;
            }
            //
            // Rule 125:  terminals_segment ::= terminal
            //
            case 125: {
               //#line 236 "LPGParser.g"
                setResult(
                    //#line 236 LPGParser.g
                     _automatic_ast_pool << new terminalList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 236 LPGParser.g
                );
            break;
            }
            //
            // Rule 126:  terminals_segment ::= terminals_segment terminal
            //
            case 126: {
               //#line 236 "LPGParser.g"
                ((terminalList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 127:  terminal ::= terminal_symbol optTerminalAlias
            //
            case 127: {
               //#line 239 "LPGParser.g"
                setResult(
                    //#line 239 LPGParser.g
                     _automatic_ast_pool << new terminal(this, getLeftIToken(), getRightIToken(),
                                 //#line 239 LPGParser.g
                                 (IAst*)getRhsSym(1),
                                 //#line 239 LPGParser.g
                                 (IAst*)getRhsSym(2))
                //#line 239 LPGParser.g
                );
            break;
            }
            //
            // Rule 128:  optTerminalAlias ::= $Empty
            //
            case 128: {
               //#line 243 "LPGParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 129:  optTerminalAlias ::= produces name
            //
            case 129: {
               //#line 243 "LPGParser.g"
                setResult(
                    //#line 243 LPGParser.g
                     _automatic_ast_pool << new optTerminalAlias(getLeftIToken(), getRightIToken(),
                                         //#line 243 LPGParser.g
                                         (IAst*)getRhsSym(1),
                                         //#line 243 LPGParser.g
                                         (IAst*)getRhsSym(2))
                //#line 243 LPGParser.g
                );
            break;
            }
            //
            // Rule 130:  terminal_symbol ::= SYMBOL
            //
            case 130: {
               //#line 245 "LPGParser.g"
                setResult(
                    //#line 245 LPGParser.g
                     _automatic_ast_pool << new terminal_symbol0(this, getRhsIToken(1))
                //#line 245 LPGParser.g
                );
            break;
            }
            //
            // Rule 131:  terminal_symbol ::= MACRO_NAME
            //
            case 131: {
               //#line 249 "LPGParser.g"
                setResult(
                    //#line 249 LPGParser.g
                     _automatic_ast_pool << new terminal_symbol1(getRhsIToken(1))
                //#line 249 LPGParser.g
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
               //#line 255 "LPGParser.g"
                setResult(
                    //#line 255 LPGParser.g
                     _automatic_ast_pool << new type_declarationsList((IAst*)getRhsSym(1), true /* left recursive */)
                //#line 255 LPGParser.g
                );
            break;
            }
            //
            // Rule 134:  types_segment ::= types_segment type_declarations
            //
            case 134: {
               //#line 255 "LPGParser.g"
                ((type_declarationsList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 135:  type_declarations ::= SYMBOL produces barSymbolList
            //
            case 135: {
               //#line 257 "LPGParser.g"
                setResult(
                    //#line 257 LPGParser.g
                     _automatic_ast_pool << new type_declarations(getLeftIToken(), getRightIToken(),
                                          //#line 257 LPGParser.g
                                           _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                          //#line 257 LPGParser.g
                                          (IAst*)getRhsSym(2),
                                          //#line 257 LPGParser.g
                                          (IAst*)getRhsSym(3))
                //#line 257 LPGParser.g
                );
            break;
            }
            //
            // Rule 136:  barSymbolList ::= SYMBOL
            //
            case 136: {
               //#line 258 "LPGParser.g"
                setResult(
                    //#line 258 LPGParser.g
                     _automatic_ast_pool << new SYMBOLList( _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)), true /* left recursive */)
                //#line 258 LPGParser.g
                );
            break;
            }
            //
            // Rule 137:  barSymbolList ::= barSymbolList |$ SYMBOL
            //
            case 137: {
               //#line 258 "LPGParser.g"
                ((SYMBOLList*)getRhsSym(1))->addElement( _automatic_ast_pool << new ASTNodeToken(getRhsIToken(3)));
            break;
            }
            //
            // Rule 138:  predecessor_segment ::= $Empty
            //
            case 138: {
               //#line 261 "LPGParser.g"
                setResult(
                    //#line 261 LPGParser.g
                     _automatic_ast_pool << new symbol_pairList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 261 LPGParser.g
                );
            break;
            }
            //
            // Rule 139:  predecessor_segment ::= predecessor_segment symbol_pair
            //
            case 139: {
               //#line 261 "LPGParser.g"
                ((symbol_pairList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
            //
            // Rule 140:  symbol_pair ::= SYMBOL SYMBOL
            //
            case 140: {
               //#line 263 "LPGParser.g"
                setResult(
                    //#line 263 LPGParser.g
                     _automatic_ast_pool << new symbol_pair(getLeftIToken(), getRightIToken(),
                                    //#line 263 LPGParser.g
                                     _automatic_ast_pool << new ASTNodeToken(getRhsIToken(1)),
                                    //#line 263 LPGParser.g
                                     _automatic_ast_pool << new ASTNodeToken(getRhsIToken(2)))
                //#line 263 LPGParser.g
                );
            break;
            }
            //
            // Rule 141:  recover_segment ::= $Empty
            //
            case 141: {
               //#line 266 "LPGParser.g"
                setResult(
                    //#line 266 LPGParser.g
                     _automatic_ast_pool << new SYMBOLList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 266 LPGParser.g
                );
            break;
            }
            //
            // Rule 142:  recover_segment ::= recover_segment recover_symbol
            //
            case 142: {
               //#line 266 "LPGParser.g"
                setResult((SYMBOLList*)getRhsSym(1));
            break;
            }
            //
            // Rule 143:  recover_symbol ::= SYMBOL
            //
            case 143: {
               //#line 268 "LPGParser.g"
                setResult(
                    //#line 268 LPGParser.g
                     _automatic_ast_pool << new recover_symbol(this, getRhsIToken(1))
                //#line 268 LPGParser.g
                );
            break;
            }
            //
            // Rule 144:  END_KEY_OPT ::= $Empty
            //
            case 144: {
               //#line 273 "LPGParser.g"
                setResult(nullptr);
            break;
            }
            //
            // Rule 145:  END_KEY_OPT ::= END_KEY
            //
            case 145: {
               //#line 274 "LPGParser.g"
                setResult(
                    //#line 274 LPGParser.g
                     _automatic_ast_pool << new END_KEY_OPT(getRhsIToken(1))
                //#line 274 LPGParser.g
                );
            break;
            }
            //
            // Rule 146:  action_segment_list ::= $Empty
            //
            case 146: {
               //#line 276 "LPGParser.g"
                setResult(
                    //#line 276 LPGParser.g
                     _automatic_ast_pool << new action_segmentList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                //#line 276 LPGParser.g
                );
            break;
            }
            //
            // Rule 147:  action_segment_list ::= action_segment_list action_segment
            //
            case 147: {
               //#line 277 "LPGParser.g"
                ((action_segmentList*)getRhsSym(1))->addElement((IAst*)getRhsSym(2));
            break;
            }
    //#line 359 "dtParserTemplateF.gi

    
            default:
                break;
        }
        return;
    }

