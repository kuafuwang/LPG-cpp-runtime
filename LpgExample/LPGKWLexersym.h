
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
  struct LPGKWLexersym {
     typedef  unsigned char byte;
      static constexpr int
      Char_DollarSign = 20,
      Char_Percent = 21,
      Char__ = 28,
      Char_a = 8,
      Char_b = 17,
      Char_c = 14,
      Char_d = 9,
      Char_e = 1,
      Char_f = 15,
      Char_g = 22,
      Char_h = 23,
      Char_i = 6,
      Char_j = 24,
      Char_k = 18,
      Char_l = 7,
      Char_m = 12,
      Char_n = 10,
      Char_o = 4,
      Char_p = 11,
      Char_q = 29,
      Char_r = 3,
      Char_s = 2,
      Char_t = 5,
      Char_u = 16,
      Char_v = 25,
      Char_w = 19,
      Char_x = 26,
      Char_y = 13,
      Char_z = 30,
      Char_EOF = 27;

      inline const static std::vector<std::wstring> orderedTerminalSymbols = {
                 L"",
                 L"e",
                 L"s",
                 L"r",
                 L"o",
                 L"t",
                 L"i",
                 L"l",
                 L"a",
                 L"d",
                 L"n",
                 L"p",
                 L"m",
                 L"y",
                 L"c",
                 L"f",
                 L"u",
                 L"b",
                 L"k",
                 L"w",
                 L"DollarSign",
                 L"Percent",
                 L"g",
                 L"h",
                 L"j",
                 L"v",
                 L"x",
                 L"EOF",
                 L"_",
                 L"q",
                 L"z"
             };

     static constexpr  int numTokenKinds = 31;
     static constexpr  bool isValidForParser = true;
};
