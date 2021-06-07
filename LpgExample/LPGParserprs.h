#pragma once
 #include <string>
  #include "LPGParsersym.h"
 #include "ParseTable.h"
 struct LPGParserprs :public ParseTable,public LPGParsersym {
             typedef  unsigned char byte;
     constexpr   static int ERROR_SYMBOL = 47;
     int getErrorSymbol() { return ERROR_SYMBOL; }

     constexpr   static int SCOPE_UBOUND = -1;
     int getScopeUbound() { return SCOPE_UBOUND; }

     constexpr   static int SCOPE_SIZE = 0;
     int getScopeSize() { return SCOPE_SIZE; }

     constexpr   static int MAX_NAME_LENGTH = 27;
     int getMaxNameLength() { return MAX_NAME_LENGTH; }

     constexpr   static int NUM_STATES = 105;
     int getNumStates() { return NUM_STATES; }

     constexpr   static int NT_OFFSET = 47;
     int getNtOffset() { return NT_OFFSET; }

     constexpr   static int LA_STATE_OFFSET = 597;
     int getLaStateOffset() { return LA_STATE_OFFSET; }

     constexpr   static int MAX_LA = 3;
     int getMaxLa() { return MAX_LA; }

     constexpr   static int NUM_RULES = 147;
     int getNumRules() { return NUM_RULES; }

     constexpr   static int NUM_NONTERMINALS = 68;
     int getNumNonterminals() { return NUM_NONTERMINALS; }

     constexpr   static int NUM_SYMBOLS = 115;
     int getNumSymbols() { return NUM_SYMBOLS; }

     constexpr   static int START_STATE = 201;
     int getStartState() { return START_STATE; }

     constexpr   static int IDENTIFIER_SYMBOL = 0;
     int getIdentifier_SYMBOL() { return IDENTIFIER_SYMBOL; }

     constexpr   static int EOFT_SYMBOL = 36;
     int getEoftSymbol() { return EOFT_SYMBOL; }

     constexpr   static int EOLT_SYMBOL = 36;
     int getEoltSymbol() { return EOLT_SYMBOL; }

     constexpr   static int ACCEPT_ACTION = 449;
     int getAcceptAction() { return ACCEPT_ACTION; }

     constexpr   static int ERROR_ACTION = 450;
     int getErrorAction() { return ERROR_ACTION; }

   constexpr   static bool BACKTRACK = true;
      bool getBacktrack() { return BACKTRACK; }

     int getStartSymbol() { return lhs(0); }
      bool isValidForParser() { return LPGParsersym::isValidForParser; }

inline static char _isNullable[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,1,0,0,
            0,0,0,1,0,1,1,0,0,0,
            0,0,0,0,1,0,0,0,0,1,
            1,1,0,0,1,0,0,0,0,0,
            0,1,0,0,0,0,0,1,0,0,
            1,0,1,1,0,0,1,0,0,1,
            0,0,0,1,1,0,0,1,0,1,
            1,0,0,0,0
        };
char * get_isNullable_data(){ return  _isNullable;}
      bool isNullable(int index) { return _isNullable[index] != 0; }
inline static signed int _prosthesesIndex[] = {0,
            7,35,42,43,36,52,38,51,57,58,
            19,31,34,37,39,40,48,50,53,62,
            63,65,2,3,4,5,6,8,9,10,
            11,12,13,14,15,16,17,18,20,21,
            22,23,24,25,26,27,28,29,30,32,
            33,41,44,45,46,47,49,54,55,56,
            59,60,61,64,66,67,68,1
        };
signed int * get_prosthesesIndex_data(){ return  _prosthesesIndex;}
      int prosthesesIndex(int index) { return _prosthesesIndex[index]; }
inline static char _isKeyword[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0
        };
char * get_isKeyword_data(){ return  _isKeyword;}
      bool isKeyword(int index) { return _isKeyword[index] != 0; }
inline static signed int _baseCheck[] = {0,
            2,0,2,3,3,3,3,3,3,3,
            3,3,3,3,3,3,3,3,3,3,
            3,3,3,3,3,3,0,2,2,1,
            3,2,0,2,4,1,3,1,2,3,
            3,3,3,3,3,1,1,1,1,1,
            1,1,1,1,1,2,2,1,1,1,
            1,1,1,1,2,1,2,1,1,2,
            0,2,2,2,1,2,1,2,4,0,
            1,1,1,2,1,3,1,2,3,1,
            1,1,1,1,1,1,2,2,0,2,
            3,1,2,3,1,3,1,1,1,1,
            2,0,2,1,2,0,1,0,1,1,
            1,2,1,1,1,2,2,0,2,1,
            1,1,1,2,3,1,3,0,2,2,
            0,2,1,0,1,0,2,-10,-12,-74,
            3,3,-15,-28,-16,6,8,3,6,11,
            -26,-34,8,2,-2,11,13,14,21,-40,
            1,19,3,-32,1,15,16,8,-37,1,
            27,3,-45,1,-47,1,-93,3,6,29,
            43,39,8,-59,1,9,10,-63,1,21,
            -1,19,-100,-104,18,-3,4,-5,15,16,
            13,14,9,10,-8,-11,-31,1,-9,12,
            -13,18,-29,23,24,7,-23,7,-14,3,
            25,-19,4,-71,3,20,22,-20,-22,-21,
            67,3,-27,4,7,-24,-76,-25,3,7,
            3,-43,-38,48,2,4,49,42,32,45,
            -6,41,44,61,62,-33,1,36,40,-89,
            28,33,35,34,-39,1,31,30,-4,-44,
            1,-7,66,4,-54,1,17,22,4,-55,
            1,-102,3,-17,20,-18,-30,-35,1,-36,
            9,10,-50,4,26,59,60,47,-41,58,
            2,-42,1,-46,-60,2,64,-48,1,-49,
            1,-51,1,-52,1,56,-53,46,-56,1,
            4,38,37,-57,1,-58,1,-61,1,-62,
            -64,-70,2,4,-73,-65,50,2,-66,-67,
            2,2,-68,12,2,53,-69,-75,2,-77,
            -78,-85,-79,6,-80,6,52,5,-81,5,
            -82,-83,-84,5,-90,5,5,5,-87,-95,
            2,-96,-101,-103,2,-72,-86,-88,-91,-92,
            -94,-97,-98,-99,-105,0,17,0,0,0,
            0,0,0,0,0,0,0,0,0,65,
            0,0,51,0,54,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,55,
            0,0,0,0,0,0,0,0,57,0,
            0,0,0,0,0,0,63,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0
        };
signed int * get_baseCheck_data(){ return  _baseCheck;}
      int baseCheck(int index) { return _baseCheck[index]; }
inline      static signed int*  _rhs = _baseCheck;
     int rhs(int index) { return _rhs[index]; };
signed int*  get_rhs_data(){ return _rhs;}
inline static signed int _baseAction[] = {
            23,23,25,25,26,26,26,26,26,26,
            26,26,26,26,26,26,26,26,26,26,
            26,26,26,26,26,26,26,24,24,48,
            49,49,12,50,50,50,51,51,27,27,
            13,13,13,13,13,13,14,5,5,5,
            5,5,5,5,28,29,29,15,16,16,
            52,31,30,32,33,33,34,34,35,36,
            37,53,53,54,54,55,55,56,56,17,
            57,57,38,11,11,8,8,39,39,19,
            6,6,6,6,6,6,40,40,41,58,
            58,59,60,60,60,18,18,2,2,2,
            2,9,10,10,62,62,63,63,61,61,
            4,42,42,20,20,43,43,21,64,64,
            3,3,44,45,45,22,65,65,47,47,
            66,46,46,67,1,1,7,7,77,77,
            134,253,309,134,147,77,129,83,309,314,
            170,176,76,83,345,119,185,38,341,125,
            5,20,87,309,238,25,55,315,84,5,
            22,198,253,111,17,5,16,233,309,314,
            194,179,183,84,150,6,105,203,115,4,
            126,40,88,224,233,394,161,119,184,56,
            315,39,341,105,203,192,168,234,26,137,
            30,137,395,218,165,206,300,77,252,154,
            63,279,77,96,94,69,121,133,137,77,
            154,142,64,137,66,327,77,267,77,61,
            340,62,240,159,28,150,147,223,275,329,
            266,87,312,298,111,113,242,24,322,280,
            271,338,290,324,285,42,21,334,336,75,
            244,18,132,139,97,244,11,77,134,67,
            5,10,233,65,200,122,216,89,253,23,
            186,106,203,226,147,3,100,379,217,167,
            247,358,253,19,76,257,360,127,253,15,
            253,14,253,13,253,12,380,254,174,253,
            9,147,318,320,253,8,253,7,253,5,
            258,76,184,363,147,263,76,32,365,76,
            76,369,371,76,31,372,361,76,134,373,
            134,231,269,129,86,129,89,57,45,129,
            44,129,129,129,43,273,42,41,40,76,
            281,187,283,76,290,204,259,261,208,209,
            276,278,286,288,279,284,450,78,450,450,
            450,450,450,450,450,450,450,450,450,450,
            387,450,450,389,450,72,450,450,450,450,
            450,450,450,450,450,450,450,450,450,450,
            392,450,450,450,450,450,450,450,450,383,
            450,450,450,450,450,450,450,115,450,0
        };
signed int * get_baseAction_data(){ return  _baseAction;}
      int baseAction(int index) { return _baseAction[index]; }
 inline     static signed int * _lhs = _baseAction;
     int lhs(int index) { return _lhs[index]; };
signed int*  get_lhs_data(){ return _lhs;}
inline static signed int _termCheck[] = {0,
            0,1,2,3,0,1,2,3,8,9,
            10,11,12,13,14,15,16,17,18,19,
            20,21,22,23,24,25,26,27,28,29,
            30,31,32,33,34,35,36,0,1,0,
            3,0,1,2,3,8,9,10,11,12,
            13,14,15,16,17,18,19,20,21,22,
            23,24,25,26,27,28,29,30,31,32,
            33,34,35,36,0,0,0,1,2,4,
            5,6,7,9,10,11,0,13,0,15,
            16,17,18,0,1,21,22,23,24,25,
            26,27,28,29,30,31,32,33,34,35,
            0,1,2,3,0,1,2,3,0,9,
            10,11,12,9,10,11,38,13,0,1,
            2,0,39,0,1,2,0,9,10,11,
            12,13,9,10,11,12,0,1,2,0,
            1,2,3,0,36,9,10,11,0,13,
            0,8,4,5,6,7,0,0,1,2,
            4,5,6,7,0,0,1,2,4,5,
            6,7,0,0,1,0,4,5,6,7,
            0,0,1,8,4,5,6,7,0,0,
            1,41,4,5,6,7,0,0,0,2,
            4,5,6,7,0,0,1,0,4,5,
            6,7,0,0,1,0,4,5,6,7,
            0,8,0,0,1,12,3,0,1,0,
            3,0,1,0,3,37,3,8,40,19,
            20,8,0,0,37,3,0,0,0,1,
            0,8,0,1,8,8,0,1,0,1,
            0,1,0,1,14,0,1,0,0,2,
            0,1,0,0,2,0,1,0,1,0,
            0,2,14,0,0,0,0,14,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0
        };
signed int * get_termCheck_data(){ return  _termCheck;}
      int termCheck(int index) { return _termCheck[index]; }
inline static signed int _termAction[] = {0,
            118,384,635,384,144,580,581,595,384,384,
            384,384,384,384,384,384,384,384,384,384,
            384,384,384,384,384,384,384,384,384,384,
            384,384,384,384,384,384,384,118,384,27,
            384,144,573,574,595,384,384,384,384,384,
            384,384,384,384,384,384,384,384,384,384,
            384,384,384,384,384,384,384,384,384,384,
            384,384,384,384,1,450,450,580,581,557,
            558,559,560,227,246,232,138,248,33,154,
            243,161,261,450,484,239,240,238,296,294,
            155,153,229,282,221,149,216,148,219,215,
            144,540,541,595,144,346,496,595,450,788,
            780,772,542,820,812,796,234,804,450,497,
            498,141,362,450,540,541,146,499,500,503,
            502,501,543,544,545,542,450,346,496,144,
            509,508,595,450,449,357,353,349,128,350,
            2,570,557,558,559,560,85,450,573,574,
            557,558,559,560,144,450,509,508,545,545,
            545,545,144,450,297,132,544,544,544,544,
            144,450,162,570,543,543,543,543,144,450,
            532,208,349,349,349,349,144,102,450,391,
            350,350,350,350,144,450,303,29,353,353,
            353,353,144,118,598,71,357,357,357,357,
            70,570,112,144,386,564,595,144,593,99,
            595,144,162,144,595,393,595,570,485,270,
            375,570,144,68,342,595,450,54,450,590,
            135,570,450,586,510,570,98,388,450,486,
            450,382,450,525,390,450,587,103,101,554,
            74,382,80,79,531,73,526,450,487,116,
            450,567,292,450,450,450,450,292
        };
signed int * get_termAction_data(){ return  _termAction;}
      int termAction(int index) { return _termAction[index]; }
inline static signed int _asb[] = {0,
            132,189,132,166,128,103,103,128,68,34,
            34,34,67,93,1,34,128,128,34,68,
            93,34,34,34,34,34,68,30,131,130,
            103,103,103,192,165,68,102,98,102,102,
            98,165,67,68,8,192,102,165,165,163,
            165,165,68,68,102,165,165,165,102,93,
            165,68,102,192,192,192,192,192,192,128,
            95,128,128,1,1,103,1,163,29,29,
            29,29,29,29,128,39,192,191,128,128,
            197,128,37,191,162,191,162,128,39,159,
            192,159,158,159,161
        };
signed int * get_asb_data(){ return  _asb;}
      int asb(int index) { return _asb[index]; }
inline static signed int _asr[] = {0,
            1,2,12,9,10,11,0,15,16,17,
            18,21,22,23,24,25,26,27,28,29,
            30,31,32,33,34,35,36,3,12,9,
            10,13,11,1,2,0,12,8,15,16,
            17,18,3,9,10,13,21,22,23,11,
            24,25,26,27,28,29,30,31,32,33,
            34,35,36,1,14,0,1,15,16,17,
            18,3,9,10,13,21,22,23,11,24,
            25,26,27,28,29,30,31,32,33,34,
            35,36,8,0,1,39,0,4,5,6,
            7,2,15,16,17,18,3,9,10,13,
            21,22,23,11,24,25,26,27,28,29,
            30,31,32,33,34,35,36,1,0,38,
            37,15,16,17,18,9,10,13,21,22,
            23,11,24,25,26,27,28,41,29,30,
            31,32,33,34,35,36,0,2,12,8,
            14,1,19,20,3,15,16,17,13,10,
            9,21,22,23,11,24,25,26,27,28,
            30,31,32,33,34,35,29,18,36,0,
            2,4,5,6,7,0,40,37,0
        };
signed int * get_asr_data(){ return  _asr;}
      int asr(int index) { return _asr[index]; }
inline static signed int _nasb[] = {0,
            30,29,35,82,38,72,87,40,47,14,
            42,14,47,51,1,14,89,91,53,47,
            57,55,49,59,64,7,47,4,29,93,
            44,10,74,70,28,85,13,69,79,13,
            70,28,66,84,16,70,13,28,28,95,
            28,28,85,84,13,28,28,28,22,97,
            28,85,26,70,70,70,70,70,70,99,
            29,29,101,18,18,61,18,103,107,107,
            107,107,107,107,105,29,70,29,77,109,
            29,29,20,29,111,113,29,29,29,32,
            70,20,115,20,29
        };
signed int * get_nasb_data(){ return  _nasb;}
      int nasb(int index) { return _nasb[index]; }
inline static signed int _nasr[] = {0,
            6,39,0,14,27,0,16,29,0,1,
            67,0,1,3,0,1,19,6,0,10,
            0,16,1,15,0,14,13,1,0,24,
            0,61,62,0,25,48,0,49,0,45,
            0,42,0,1,66,0,7,0,32,0,
            40,0,36,0,33,0,34,0,31,0,
            60,59,0,30,0,58,4,0,64,2,
            0,47,0,1,22,0,56,0,1,20,
            0,26,0,1,4,0,46,0,38,0,
            37,0,50,0,53,0,52,0,12,0,
            65,0,54,0,51,0,5,0,55,0,
            17,0,57,0,63,0
        };
signed int * get_nasr_data(){ return  _nasr;}
      int nasr(int index) { return _nasr[index]; }
inline static signed int _terminalIndex[] = {0,
            45,44,21,1,2,3,4,46,22,23,
            28,20,24,5,14,15,16,17,18,19,
            25,26,27,29,30,31,32,33,35,36,
            37,38,39,40,41,42,7,6,8,9,
            34,10,11,12,43,47,48
        };
signed int * get_terminalIndex_data(){ return  _terminalIndex;}
      int terminalIndex(int index) { return _terminalIndex[index]; }
inline static signed int _nonterminalIndex[] = {0,
            0,71,77,78,72,84,0,83,0,0,
            60,68,70,73,74,75,82,0,85,89,
            90,91,0,0,0,49,50,0,51,52,
            53,54,55,56,0,57,58,59,61,62,
            0,63,64,0,65,0,0,66,67,0,
            69,76,0,79,80,81,0,0,86,87,
            0,88,0,0,92,93,94,0
        };
signed int * get_nonterminalIndex_data(){ return  _nonterminalIndex;}
      int nonterminalIndex(int index) { return _nonterminalIndex[index]; }
  inline    static int* _scopePrefix = NULL;
     int scopePrefix(int index) { return 0;}

   inline   static int* _scopeSuffix = NULL;
     int scopeSuffix(int index) { return 0;}

    inline  static int* _scopeLhs = NULL;
     int scopeLhs(int index) { return 0;}

    inline  static int* _scopeLa = NULL;
     int scopeLa(int index) { return 0;}

    inline  static int* _scopeStateSet = NULL;
     int scopeStateSet(int index) { return 0;}

   inline   static int* _scopeRhs = NULL;
     int scopeRhs(int index) { return 0;}

   inline   static int* _scopeState = NULL;
     int scopeState(int index) { return 0;}

   inline   static int* _inSymb = NULL;
     int inSymb(int index) { return 0;}

inline static std::wstring _name[] = {
            L"",
            L"::=",
            L"::=?",
            L"->",
            L"->?",
            L"|",
            L"=",
            L",",
            L"(",
            L")",
            L"[",
            L"]",
            L"#",
            L"$empty",
            L"ALIAS_KEY",
            L"AST_KEY",
            L"DEFINE_KEY",
            L"DISJOINTPREDECESSORSETS_KEY",
            L"DROPRULES_KEY",
            L"DROPSYMBOLS_KEY",
            L"EMPTY_KEY",
            L"END_KEY",
            L"ERROR_KEY",
            L"EOL_KEY",
            L"EOF_KEY",
            L"EXPORT_KEY",
            L"GLOBALS_KEY",
            L"HEADERS_KEY",
            L"IDENTIFIER_KEY",
            L"IMPORT_KEY",
            L"INCLUDE_KEY",
            L"KEYWORDS_KEY",
            L"NAMES_KEY",
            L"NOTICE_KEY",
            L"OPTIONS_KEY",
            L"RECOVER_KEY",
            L"RULES_KEY",
            L"SOFT_KEYWORDS_KEY",
            L"START_KEY",
            L"TERMINALS_KEY",
            L"TRAILERS_KEY",
            L"TYPES_KEY",
            L"EOF_TOKEN",
            L"SINGLE_LINE_COMMENT",
            L"MACRO_NAME",
            L"SYMBOL",
            L"BLOCK",
            L"VBAR",
            L"ERROR_TOKEN",
            L"LPG_item",
            L"alias_segment",
            L"define_segment",
            L"eof_segment",
            L"eol_segment",
            L"error_segment",
            L"export_segment",
            L"globals_segment",
            L"identifier_segment",
            L"import_segment",
            L"include_segment",
            L"keywords_segment",
            L"names_segment",
            L"notice_segment",
            L"start_segment",
            L"terminals_segment",
            L"types_segment",
            L"option_spec",
            L"option_list",
            L"option",
            L"symbol_list",
            L"aliasSpec",
            L"produces",
            L"alias_rhs",
            L"alias_lhs_macro_name",
            L"defineSpec",
            L"macro_name_symbol",
            L"macro_segment",
            L"terminal_symbol",
            L"action_segment",
            L"drop_command",
            L"drop_symbols",
            L"drop_rules",
            L"drop_rule",
            L"keywordSpec",
            L"name",
            L"nameSpec",
            L"nonTerm",
            L"ruleNameWithAttributes",
            L"symWithAttrs",
            L"start_symbol",
            L"terminal",
            L"type_declarations",
            L"barSymbolList",
            L"symbol_pair",
            L"recover_symbol"
        };
      std::wstring name(int index) { return _name[index]; }

     int originalState(int state) {
        return - _baseCheck[state];
    }
     int asi(int state) {
        return _asb[originalState(state)];
    }
     int nasi(int state) {
        return _nasb[originalState(state)];
    }
     int inSymbol(int state) {
        return _inSymb[originalState(state)];
    }

    /**
     * assert(! goto_default);
     */
     int ntAction(int state, int sym) {
        return _baseAction[state + sym];
    }

    /**
     * assert(! shift_default);
     */
     int tAction(int state, int sym) {
        int i = _baseAction[state],
            k = i + sym;
        return _termAction[_termCheck[k] == sym ? k : i];
    }
     int lookAhead(int la_state, int sym) {
        int k = la_state + sym;
        return _termAction[_termCheck[k] == sym ? k : la_state];
    }
};
