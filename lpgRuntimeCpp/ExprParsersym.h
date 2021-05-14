#pragma once
 #include <vector>
#include<string>
  struct ExprParsersym {
     typedef  unsigned char byte;
      static constexpr int
      TK_IntegerLiteral = 3,
      TK_PLUS = 1,
      TK_MULTIPLY = 2,
      TK_LPAREN = 4,
      TK_RPAREN = 5,
      TK_EOF_TOKEN = 6,
      TK_ERROR_TOKEN = 7;

      inline const static std::vector<std::wstring> orderedTerminalSymbols = {
                 L"",
                 L"PLUS",
                 L"MULTIPLY",
                 L"IntegerLiteral",
                 L"LPAREN",
                 L"RPAREN",
                 L"EOF_TOKEN",
                 L"ERROR_TOKEN"
             };

     static constexpr  int numTokenKinds = 8;
     static constexpr  bool isValidForParser = true;
};
