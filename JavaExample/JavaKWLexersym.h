
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
  struct JavaKWLexersym {
     typedef  unsigned char byte;
      static constexpr int
      Char_DollarSign = 35,
      Char_Percent = 42,
      Char__ = 43,
      Char_a = 3,
      Char_b = 19,
      Char_c = 8,
      Char_d = 14,
      Char_e = 2,
      Char_f = 16,
      Char_g = 23,
      Char_h = 15,
      Char_i = 6,
      Char_j = 28,
      Char_k = 29,
      Char_l = 7,
      Char_m = 27,
      Char_n = 4,
      Char_o = 5,
      Char_p = 24,
      Char_q = 44,
      Char_r = 9,
      Char_s = 10,
      Char_t = 1,
      Char_u = 11,
      Char_v = 20,
      Char_w = 25,
      Char_x = 36,
      Char_y = 26,
      Char_z = 37,
      Char_A = 12,
      Char_B = 38,
      Char_C = 21,
      Char_D = 30,
      Char_E = 31,
      Char_F = 45,
      Char_G = 39,
      Char_H = 46,
      Char_I = 17,
      Char_J = 32,
      Char_K = 47,
      Char_L = 33,
      Char_M = 48,
      Char_N = 13,
      Char_O = 18,
      Char_P = 49,
      Char_Q = 50,
      Char_R = 51,
      Char_S = 52,
      Char_T = 22,
      Char_U = 40,
      Char_V = 34,
      Char_W = 53,
      Char_X = 54,
      Char_Y = 55,
      Char_Z = 56,
      Char_EOF = 41;

      inline const static std::vector<std::wstring> orderedTerminalSymbols = {
                 L"",
                 L"t",
                 L"e",
                 L"a",
                 L"n",
                 L"o",
                 L"i",
                 L"l",
                 L"c",
                 L"r",
                 L"s",
                 L"u",
                 L"A",
                 L"N",
                 L"d",
                 L"h",
                 L"f",
                 L"I",
                 L"O",
                 L"b",
                 L"v",
                 L"C",
                 L"T",
                 L"g",
                 L"p",
                 L"w",
                 L"y",
                 L"m",
                 L"j",
                 L"k",
                 L"D",
                 L"E",
                 L"J",
                 L"L",
                 L"V",
                 L"DollarSign",
                 L"x",
                 L"z",
                 L"B",
                 L"G",
                 L"U",
                 L"EOF",
                 L"Percent",
                 L"_",
                 L"q",
                 L"F",
                 L"H",
                 L"K",
                 L"M",
                 L"P",
                 L"Q",
                 L"R",
                 L"S",
                 L"W",
                 L"X",
                 L"Y",
                 L"Z"
             };

     static constexpr  int numTokenKinds = 57;
     static constexpr  bool isValidForParser = true;
};
