
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
 #include <vector>
#include<string>
  struct JavaLexersym {
     typedef  unsigned char byte;
      static constexpr int
      Char_CtlCharNotWS = 102,
      Char_LF = 100,
      Char_CR = 101,
      Char_HT = 37,
      Char_FF = 38,
      Char_a = 19,
      Char_b = 15,
      Char_c = 20,
      Char_d = 12,
      Char_e = 16,
      Char_f = 11,
      Char_g = 39,
      Char_h = 40,
      Char_i = 41,
      Char_j = 42,
      Char_k = 43,
      Char_l = 25,
      Char_m = 44,
      Char_n = 26,
      Char_o = 45,
      Char_p = 46,
      Char_q = 47,
      Char_r = 27,
      Char_s = 48,
      Char_t = 28,
      Char_u = 29,
      Char_v = 49,
      Char_w = 50,
      Char_x = 32,
      Char_y = 51,
      Char_z = 52,
      Char__ = 53,
      Char_A = 21,
      Char_B = 22,
      Char_C = 23,
      Char_D = 13,
      Char_E = 17,
      Char_F = 14,
      Char_G = 54,
      Char_H = 55,
      Char_I = 56,
      Char_J = 57,
      Char_K = 58,
      Char_L = 30,
      Char_M = 59,
      Char_N = 60,
      Char_O = 61,
      Char_P = 62,
      Char_Q = 63,
      Char_R = 64,
      Char_S = 65,
      Char_T = 66,
      Char_U = 67,
      Char_V = 68,
      Char_W = 69,
      Char_X = 33,
      Char_Y = 70,
      Char_Z = 71,
      Char_0 = 1,
      Char_1 = 2,
      Char_2 = 3,
      Char_3 = 4,
      Char_4 = 5,
      Char_5 = 6,
      Char_6 = 7,
      Char_7 = 8,
      Char_8 = 9,
      Char_9 = 10,
      Char_AfterASCII = 72,
      Char_Space = 73,
      Char_DoubleQuote = 34,
      Char_SingleQuote = 24,
      Char_Percent = 81,
      Char_VerticalBar = 74,
      Char_Exclamation = 82,
      Char_AtSign = 83,
      Char_BackQuote = 97,
      Char_Tilde = 84,
      Char_Sharp = 98,
      Char_DollarSign = 75,
      Char_Ampersand = 76,
      Char_Caret = 85,
      Char_Colon = 86,
      Char_SemiColon = 87,
      Char_BackSlash = 77,
      Char_LeftBrace = 88,
      Char_RightBrace = 89,
      Char_LeftBracket = 90,
      Char_RightBracket = 91,
      Char_QuestionMark = 92,
      Char_Comma = 93,
      Char_Dot = 31,
      Char_LessThan = 78,
      Char_GreaterThan = 94,
      Char_Plus = 35,
      Char_Minus = 36,
      Char_Slash = 79,
      Char_Star = 80,
      Char_LeftParen = 95,
      Char_RightParen = 96,
      Char_Equal = 18,
      Char_EOF = 99;

      inline const static std::vector<std::wstring> orderedTerminalSymbols = {
                 L"",
                 L"0",
                 L"1",
                 L"2",
                 L"3",
                 L"4",
                 L"5",
                 L"6",
                 L"7",
                 L"8",
                 L"9",
                 L"f",
                 L"d",
                 L"D",
                 L"F",
                 L"b",
                 L"e",
                 L"E",
                 L"Equal",
                 L"a",
                 L"c",
                 L"A",
                 L"B",
                 L"C",
                 L"SingleQuote",
                 L"l",
                 L"n",
                 L"r",
                 L"t",
                 L"u",
                 L"L",
                 L"Dot",
                 L"x",
                 L"X",
                 L"DoubleQuote",
                 L"Plus",
                 L"Minus",
                 L"HT",
                 L"FF",
                 L"g",
                 L"h",
                 L"i",
                 L"j",
                 L"k",
                 L"m",
                 L"o",
                 L"p",
                 L"q",
                 L"s",
                 L"v",
                 L"w",
                 L"y",
                 L"z",
                 L"_",
                 L"G",
                 L"H",
                 L"I",
                 L"J",
                 L"K",
                 L"M",
                 L"N",
                 L"O",
                 L"P",
                 L"Q",
                 L"R",
                 L"S",
                 L"T",
                 L"U",
                 L"V",
                 L"W",
                 L"Y",
                 L"Z",
                 L"AfterASCII",
                 L"Space",
                 L"VerticalBar",
                 L"DollarSign",
                 L"Ampersand",
                 L"BackSlash",
                 L"LessThan",
                 L"Slash",
                 L"Star",
                 L"Percent",
                 L"Exclamation",
                 L"AtSign",
                 L"Tilde",
                 L"Caret",
                 L"Colon",
                 L"SemiColon",
                 L"LeftBrace",
                 L"RightBrace",
                 L"LeftBracket",
                 L"RightBracket",
                 L"QuestionMark",
                 L"Comma",
                 L"GreaterThan",
                 L"LeftParen",
                 L"RightParen",
                 L"BackQuote",
                 L"Sharp",
                 L"EOF",
                 L"LF",
                 L"CR",
                 L"CtlCharNotWS"
             };

     static constexpr  int numTokenKinds = 103;
     static constexpr  bool isValidForParser = true;
};
