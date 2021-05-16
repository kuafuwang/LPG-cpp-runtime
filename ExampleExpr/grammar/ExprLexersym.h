#pragma once
 #include <vector>
#include<string>
  struct ExprLexersym {
     typedef  unsigned char byte;
      static constexpr int
      Char_WSChar = 1,
      Char_Digit = 2,
      Char_Unused = 8,
      Char_EOF = 3,
      Char_Plus = 4,
      Char_Star = 5,
      Char_LeftParen = 6,
      Char_RightParen = 7;

      inline const static std::vector<std::wstring> orderedTerminalSymbols = {
                 L"",
                 L"WSChar",
                 L"Digit",
                 L"EOF",
                 L"Plus",
                 L"Star",
                 L"LeftParen",
                 L"RightParen",
                 L"Unused"
             };

     static constexpr  int numTokenKinds = 9;
     static constexpr  bool isValidForParser = true;
};
