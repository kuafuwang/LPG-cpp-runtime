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

     constexpr   static int NUM_STATES = 106;
     int getNumStates() { return NUM_STATES; }

     constexpr   static int NT_OFFSET = 47;
     int getNtOffset() { return NT_OFFSET; }

     constexpr   static int LA_STATE_OFFSET = 601;
     int getLaStateOffset() { return LA_STATE_OFFSET; }

     constexpr   static int MAX_LA = 3;
     int getMaxLa() { return MAX_LA; }

     constexpr   static int NUM_RULES = 147;
     int getNumRules() { return NUM_RULES; }

     constexpr   static int NUM_NONTERMINALS = 68;
     int getNumNonterminals() { return NUM_NONTERMINALS; }

     constexpr   static int NUM_SYMBOLS = 115;
     int getNumSymbols() { return NUM_SYMBOLS; }

     constexpr   static int START_STATE = 208;
     int getStartState() { return START_STATE; }

     constexpr   static int IDENTIFIER_SYMBOL = 0;
     int getIdentifier_SYMBOL() { return IDENTIFIER_SYMBOL; }

     constexpr   static int EOFT_SYMBOL = 36;
     int getEoftSymbol() { return EOFT_SYMBOL; }

     constexpr   static int EOLT_SYMBOL = 36;
     int getEoltSymbol() { return EOLT_SYMBOL; }

     constexpr   static int ACCEPT_ACTION = 453;
     int getAcceptAction() { return ACCEPT_ACTION; }

     constexpr   static int ERROR_ACTION = 454;
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
            0,0,1,0,0,1,1,0,0,0,
            0,0,0,0,1,0,0,0,0,1,
            1,1,0,0,1,0,0,0,0,0,
            0,1,0,0,0,0,0,1,0,0,
            1,0,1,1,0,0,1,0,0,1,
            0,0,0,1,1,0,0,0,1,1,
            1,0,0,0,0
        };
char * get_isNullable_data(){ return  _isNullable;}
      bool isNullable(int index) { return _isNullable[index] != 0; }
inline static signed int _prosthesesIndex[] = {0,
            7,35,42,43,36,38,52,51,57,58,
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
            1,1,1,2,4,1,3,0,2,2,
            0,2,1,0,1,0,2,-10,-12,-18,
            3,3,-9,-15,-16,-26,8,3,6,11,
            7,-28,8,-35,1,11,-37,1,21,3,
            15,16,19,-2,13,14,-7,-40,1,-5,
            3,-29,-45,1,29,8,37,21,27,7,
            43,12,39,-8,-47,1,44,3,-59,1,
            -93,19,8,-63,1,-11,-20,-1,-3,9,
            10,-105,6,15,16,22,13,14,18,-14,
            9,10,46,4,-19,20,-13,3,49,18,
            23,24,6,25,-38,-21,2,-22,45,4,
            3,35,-23,-76,-27,3,-24,42,-25,3,
            6,3,-31,1,-32,1,48,-33,1,40,
            36,-39,1,-89,-43,-6,-17,41,4,34,
            33,-86,28,-4,32,4,-30,31,30,22,
            17,20,-44,1,-54,1,4,-100,4,-55,
            1,-102,3,6,-34,-41,2,2,64,26,
            9,10,59,60,38,-36,-42,1,-46,4,
            2,-50,47,-48,1,-49,1,-60,66,56,
            -73,67,58,-51,1,-53,50,-52,1,4,
            -56,1,-57,1,63,-58,1,-61,1,-62,
            -64,-78,2,4,-65,-66,2,2,61,-67,
            -68,2,2,-69,-70,2,-74,-79,-75,-85,
            -77,-90,5,7,53,7,12,7,-80,52,
            -81,-82,-83,5,-84,5,5,5,-87,5,
            2,-95,-96,-103,-101,65,2,4,-104,-71,
            -72,-88,-91,-92,-94,54,-97,-98,17,-99,
            -106,0,0,0,0,0,0,0,0,0,
            51,0,0,0,0,0,55,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,57,
            0,0,0,0,0,0,0,0,0,0,
            62,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0
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
            7,7,7,7,7,7,40,40,41,58,
            58,59,60,60,60,18,18,2,2,2,
            2,9,10,10,61,61,62,62,63,63,
            4,42,42,20,20,43,43,21,64,64,
            3,3,44,45,45,22,65,65,47,47,
            66,46,46,67,1,1,6,6,80,80,
            247,235,296,137,134,80,153,83,296,306,
            178,309,147,83,251,23,195,6,22,125,
            235,55,318,87,83,38,341,132,6,20,
            174,296,230,111,17,199,84,316,126,204,
            309,167,30,183,186,6,16,164,296,76,
            6,266,88,84,115,4,150,137,40,200,
            105,288,266,326,56,318,133,39,341,400,
            239,105,288,255,96,80,121,137,69,182,
            401,174,209,265,274,163,239,357,80,258,
            66,64,328,80,270,137,63,80,262,80,
            61,340,62,224,26,228,25,28,232,24,
            283,324,43,21,274,255,87,213,307,147,
            285,290,236,338,75,331,119,89,333,336,
            134,77,122,234,18,234,11,97,161,67,
            6,10,266,65,384,159,172,321,359,127,
            3,106,288,100,379,314,253,251,19,159,
            147,361,188,253,251,15,251,14,258,139,
            382,268,142,244,251,13,256,32,251,12,
            147,251,9,251,8,135,251,7,251,5,
            261,159,226,358,147,159,159,369,371,113,
            159,159,372,373,159,174,375,134,129,134,
            272,134,276,45,129,342,86,31,89,129,
            57,129,129,129,44,129,43,42,41,159,
            40,201,280,282,289,159,272,212,147,290,
            94,263,199,212,278,242,72,285,287,78,
            283,291,454,454,454,454,454,454,454,454,
            454,393,454,454,454,454,454,397,454,454,
            454,454,454,454,454,454,454,454,454,454,
            454,454,454,454,454,454,454,454,454,454,
            385,454,454,454,454,454,454,454,454,454,
            454,115,454,0
        };
signed int * get_baseAction_data(){ return  _baseAction;}
      int baseAction(int index) { return _baseAction[index]; }
 inline     static signed int * _lhs = _baseAction;
     int lhs(int index) { return _lhs[index]; };
signed int*  get_lhs_data(){ return _lhs;}
inline static signed int _termCheck[] = {0,
            0,1,2,3,4,0,1,2,3,9,
            10,11,12,13,14,15,16,17,18,19,
            20,21,22,23,24,25,26,27,28,29,
            30,31,32,33,34,35,36,0,1,0,
            3,4,0,1,2,3,9,10,11,12,
            13,14,15,16,17,18,19,20,21,22,
            23,24,25,26,27,28,29,30,31,32,
            33,34,35,36,0,0,1,2,3,0,
            1,2,0,9,10,11,0,13,0,15,
            16,17,18,0,1,21,22,23,24,25,
            26,27,28,29,30,31,32,33,34,35,
            0,1,2,3,0,1,2,3,36,9,
            10,11,12,9,10,11,38,13,0,1,
            2,0,39,0,1,2,0,9,10,11,
            12,13,9,10,11,12,0,1,2,0,
            1,2,0,1,2,9,10,11,0,13,
            0,1,0,5,6,7,8,5,6,7,
            8,0,12,0,1,0,5,6,7,8,
            5,6,7,8,0,0,1,0,0,5,
            6,7,8,5,6,7,8,0,0,0,
            2,0,5,6,7,8,5,6,7,8,
            0,0,0,1,0,5,6,7,8,5,
            6,7,8,0,1,0,3,0,1,0,
            3,0,1,0,3,0,3,4,0,4,
            41,0,4,2,19,20,0,1,37,14,
            0,40,0,3,0,0,4,0,4,4,
            0,4,0,1,4,0,37,0,1,0,
            1,0,1,0,1,0,1,0,1,0,
            1,0,0,2,0,1,0,1,0,0,
            0,2,4,0,0,0,14,0,0,0,
            0,0,0,0,14,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0
        };
signed int * get_termCheck_data(){ return  _termCheck;}
      int termCheck(int index) { return _termCheck[index]; }
inline static signed int _termAction[] = {0,
            146,389,639,389,389,144,584,585,599,389,
            389,389,389,389,389,389,389,389,389,389,
            389,389,389,389,389,389,389,389,389,389,
            389,389,389,389,389,389,389,146,389,27,
            389,389,144,577,578,599,389,389,389,389,
            389,389,389,389,389,389,389,389,389,389,
            389,389,389,389,389,389,389,389,389,389,
            389,389,389,389,1,144,513,512,599,454,
            584,585,454,243,247,225,138,249,33,162,
            245,156,266,454,488,238,236,207,150,267,
            155,154,220,177,227,149,206,148,153,194,
            144,544,545,599,144,345,500,599,453,790,
            786,777,546,816,812,799,390,803,454,501,
            502,141,360,454,544,545,146,503,504,507,
            506,505,547,548,549,546,454,345,500,454,
            577,578,454,513,512,354,351,346,454,350,
            146,602,128,561,562,563,564,561,562,563,
            564,85,568,454,277,144,561,562,563,564,
            549,549,549,549,144,454,295,71,144,548,
            548,548,548,547,547,547,547,144,102,2,
            395,144,346,346,346,346,350,350,350,350,
            144,454,454,536,144,351,351,351,351,354,
            354,354,354,144,391,70,599,144,597,29,
            599,144,295,144,599,118,599,574,454,574,
            180,103,574,558,264,362,454,312,398,394,
            144,489,132,599,99,68,574,454,574,574,
            54,514,454,594,574,112,355,454,590,98,
            392,454,490,454,383,454,529,454,591,74,
            383,80,101,535,73,530,454,491,111,116,
            79,571,574,454,454,454,292,454,454,454,
            454,454,454,454,292
        };
signed int * get_termAction_data(){ return  _termAction;}
      int termAction(int index) { return _termAction[index]; }
inline static signed int _asb[] = {0,
            129,186,129,163,125,100,100,125,68,34,
            34,34,67,93,1,34,125,125,34,68,
            93,34,34,34,34,34,68,30,128,127,
            100,100,100,192,162,68,99,95,99,99,
            95,162,67,68,8,192,99,162,162,160,
            162,162,68,68,99,162,162,162,99,93,
            162,68,99,192,192,192,192,192,192,125,
            188,125,125,1,1,100,1,160,29,29,
            29,29,29,29,125,38,192,191,125,125,
            197,125,37,191,159,191,159,125,39,156,
            192,156,157,155,156,158
        };
signed int * get_asb_data(){ return  _asb;}
      int asb(int index) { return _asb[index]; }
inline static signed int _asr[] = {0,
            1,2,12,9,10,11,0,15,16,17,
            18,21,22,23,24,25,26,27,28,29,
            30,31,32,33,34,35,36,3,12,9,
            10,13,11,1,2,0,12,4,15,16,
            17,18,3,9,10,13,21,22,23,11,
            24,25,26,27,28,29,30,31,32,33,
            34,35,36,1,14,0,1,15,16,17,
            18,3,9,10,13,21,22,23,11,24,
            25,26,27,28,29,30,31,32,33,34,
            35,36,4,0,5,6,7,8,2,15,
            16,17,18,3,9,10,13,21,22,23,
            11,24,25,26,27,28,29,30,31,32,
            33,34,35,36,1,0,38,37,15,16,
            17,18,9,10,13,21,22,23,11,24,
            25,26,27,28,41,29,30,31,32,33,
            34,35,36,0,2,12,4,14,1,19,
            20,3,15,16,17,13,10,9,21,22,
            23,11,24,25,26,27,28,30,31,32,
            33,34,35,29,18,36,0,1,39,0,
            2,5,6,7,8,0,40,37,0
        };
signed int * get_asr_data(){ return  _asr;}
      int asr(int index) { return _asr[index]; }
inline static signed int _nasb[] = {0,
            37,34,39,85,17,79,15,23,93,13,
            35,13,93,42,3,13,81,1,44,93,
            49,51,53,58,60,6,93,9,34,87,
            62,65,68,47,33,90,12,46,71,12,
            47,33,76,89,19,47,12,33,33,95,
            33,33,90,89,12,33,33,33,25,97,
            33,90,31,47,47,47,47,47,47,103,
            34,34,99,21,21,55,21,101,105,105,
            105,105,105,105,107,83,47,34,74,109,
            34,34,29,34,111,113,34,34,34,92,
            47,29,90,115,29,34
        };
signed int * get_nasb_data(){ return  _nasb;}
      int nasb(int index) { return _nasb[index]; }
inline static signed int _nasr[] = {0,
            37,0,7,39,0,16,29,0,14,27,
            0,1,3,0,46,0,49,0,1,19,
            7,0,45,0,16,1,15,0,10,0,
            14,13,1,0,42,0,24,0,25,48,
            0,40,0,36,0,64,2,0,34,0,
            33,0,32,0,60,59,0,31,0,30,
            0,1,66,0,1,67,0,1,22,0,
            1,20,0,56,0,58,4,0,47,0,
            38,0,63,0,26,0,50,0,1,4,
            0,61,6,0,53,0,52,0,65,0,
            54,0,12,0,5,0,51,0,55,0,
            17,0,57,0,62,0
        };
signed int * get_nasr_data(){ return  _nasr;}
      int nasr(int index) { return _nasr[index]; }
inline static signed int _terminalIndex[] = {0,
            45,44,21,46,1,2,3,4,22,23,
            28,20,24,5,14,15,16,17,18,19,
            25,26,27,29,30,31,32,33,35,36,
            37,38,39,40,41,42,7,6,8,9,
            34,10,11,12,43,47,48
        };
signed int * get_terminalIndex_data(){ return  _terminalIndex;}
      int terminalIndex(int index) { return _terminalIndex[index]; }
inline static signed int _nonterminalIndex[] = {0,
            0,71,77,78,72,0,84,83,0,0,
            60,68,70,73,74,75,82,0,85,89,
            90,91,0,0,0,49,50,0,51,52,
            53,54,55,56,0,57,58,59,61,62,
            0,63,64,0,65,0,0,66,67,0,
            69,76,0,79,80,81,0,0,86,87,
            88,0,0,0,92,93,94,0
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
