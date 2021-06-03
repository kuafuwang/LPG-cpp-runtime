
#ifndef U_chars_Jikes_INCLUDED
#define U_chars_Jikes_INCLUDED


namespace Jikes { // Open namespace Jikes block

	enum U_chars
	{
		U_NULL = 0, U_NU = U_NULL,            // L'\0'
		U_BACKSPACE = 8, U_BS = U_BACKSPACE,       // L'\b'
		U_HORIZONTAL_TAB = 9, U_HT = U_HORIZONTAL_TAB,  // L'\t'
		U_LINE_FEED = 10, U_LF = U_LINE_FEED,       // L'\n'
		U_FORM_FEED = 12, U_FF = U_FORM_FEED,       // L'\f'
		U_CARRIAGE_RETURN = 13, U_CR = U_CARRIAGE_RETURN, // L'\r'

		U_CTL_Z = 26,
		U_ESCAPE = 27,

		U_SPACE = 32, U_SP = U_SPACE,             // L' '
		U_EXCLAMATION = 33, U_EX = U_EXCLAMATION,       // L'!'
		U_DOUBLE_QUOTE = 34, U_DQ = U_DOUBLE_QUOTE,      // L'"'
		U_POUND = 35, U_SH = U_POUND,             // L'#'
		U_DOLLAR = 36, U_DS = U_DOLLAR,            // L'$'
		U_PERCENT = 37, U_PE = U_PERCENT,           // L'%'
		U_AMPERSAND = 38, U_AM = U_AMPERSAND,         // L'&'
		U_SINGLE_QUOTE = 39, U_SQ = U_SINGLE_QUOTE,      // L'\''
		U_LEFT_PARENTHESIS = 40, U_LP = U_LEFT_PARENTHESIS,  // L'('
		U_RIGHT_PARENTHESIS = 41, U_RP = U_RIGHT_PARENTHESIS, // L')'
		U_STAR = 42, U_ST = U_STAR,              // L'*'
		U_PLUS = 43, U_PL = U_PLUS,              // L'+'
		U_MINUS = 45, U_MI = U_MINUS,             // L'-'
		U_COMMA = 44, U_CM = U_COMMA,             // L','
		U_DOT = 46, U_DO = U_DOT,               // L'.'
		U_SLASH = 47, U_SL = U_SLASH,             // L'/'

		U_0 = 48, // L'0'
		U_1 = 49, // L'1'
		U_2 = 50, // L'2'
		U_3 = 51, // L'3'
		U_4 = 52, // L'4'
		U_5 = 53, // L'5'
		U_6 = 54, // L'6'
		U_7 = 55, // L'7'
		U_8 = 56, // L'8'
		U_9 = 57, // L'9'

		U_COLON = 58, U_CO = U_COLON,     // L':'
		U_SEMICOLON = 59, U_SC = U_SEMICOLON, // L';'
		U_LESS = 60, U_LT = U_LESS,      // L'<'
		U_EQUAL = 61, U_EQ = U_EQUAL,     // L'='
		U_GREATER = 62, U_GT = U_GREATER,   // L'>'
		U_QUESTION = 63, U_QU = U_QUESTION,  // L'?'
		U_AT = 64,                                    // L'@'

		U_A = 65, // L'A'
		U_B = 66, // L'B'
		U_C = 67, // L'C'
		U_D = 68, // L'D'
		U_E = 69, // L'E'
		U_F = 70, // L'F'
		U_G = 71, // L'G'
		U_H = 72, // L'H'
		U_I = 73, // L'I'
		U_J = 74, // L'J'
		U_K = 75, // L'K'
		U_L = 76, // L'L'
		U_M = 77, // L'M'
		U_N = 78, // L'N'
		U_O = 79, // L'O'
		U_P = 80, // L'P'
		U_Q = 81, // L'Q'
		U_R = 82, // L'R'
		U_S = 83, // L'S'
		U_T = 84, // L'T'
		U_U = 85, // L'U'
		U_V = 86, // L'V'
		U_W = 87, // L'W'
		U_X = 88, // L'X'
		U_Y = 89, // L'Y'
		U_Z = 90, // L'Z'

		U_LEFT_BRACKET = 91, U_LB = U_LEFT_BRACKET,  // L'['
		U_BACKSLASH = 92, U_RS = U_BACKSLASH,     // L'\\'
		U_RIGHT_BRACKET = 93, U_RB = U_RIGHT_BRACKET, // L']'
		U_CARET = 94, U_CA = U_CARET,         // L'^'
		U_UNDERSCORE = 95, U_UN = U_UNDERSCORE,    // L'_'

		U_a = 97, // L'a'
		U_b = 98, // L'b'
		U_c = 99, // L'c'
		U_d = 100, // L'd'
		U_e = 101, // L'e'
		U_f = 102, // L'f'
		U_g = 103, // L'g'
		U_h = 104, // L'h'
		U_i = 105, // L'i'
		U_j = 106, // L'j'
		U_k = 107, // L'k'
		U_l = 108, // L'l'
		U_m = 109, // L'm'
		U_n = 110, // L'n',
		U_o = 111, // L'o'
		U_p = 112, // L'p'
		U_q = 113, // L'q'
		U_r = 114, // L'r'
		U_s = 115, // L's'
		U_t = 116, // L't'
		U_u = 117, // L'u'
		U_v = 118, // L'v'
		U_w = 119, // L'w'
		U_x = 120, // L'x'
		U_y = 121, // L'y'
		U_z = 122, // L'z'

		U_LEFT_BRACE = 123, U_OS = U_LEFT_BRACE,  // L'{'
		U_BAR = 124, U_BA = U_BAR,         // L'|'
		U_RIGHT_BRACE = 125, U_CS = U_RIGHT_BRACE, // L'}'
		U_TILDE = 126, U_TI = U_TILDE,       // L'~'

		U_BOM = 0xfeff,
		U_REVERSE_BOM = 0xfffe
	};

	

} // Close namespace Jikes block


#endif // _INCLUDED

