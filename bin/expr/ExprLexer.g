%Options la=2
%options package=expr1
%options template=LexerTemplateD.g
%options export_terminals=("ExprParsersym.h", "TK_")

$Export
    IntegerLiteral PLUS MULTIPLY LPAREN RPAREN
$End

$Headers
    /.
         void makeToken(int kind)
        {
            int startOffset = getLeftSpan(), endOffset = getRightSpan();
            $super_stream_class ::makeToken(startOffset, endOffset, kind);
        }
      
        int getKind(int i)  // Classify character at ith location
        {
            char c = (i >= getStreamLength() ? '\uffff' : getCharValue(i));
            return (c <  33		? Char_WSChar : 
            		c>= '0' && c <= '9' ? Char_Digit :
            		c == '+' 		? Char_Plus :
            		c == '*' 		? Char_Star :
            		c == '(' 		? Char_LeftParen :
            		c == ')' 		? Char_RightParen :
            		c == '\uffff' 	? Char_EOF : 
            					  Char_Unused);
        }
    ./
$End

$Terminals
    WSChar Digit Unused EOF

    Plus         ::= '+'
    Star         ::= '*'
    LeftParen    ::= '('
    RightParen   ::= ')'
$End

$Start
    Token
$End

$Rules
   Token ::= IntegerLiteral
        /.$BeginAction
                    makeToken($_IntegerLiteral);
          $EndAction
        ./
    Token ::= '+'
        /.$BeginAction
                    makeToken($_PLUS);
          $EndAction
        ./
    Token ::= '*'
        /.$BeginAction
                    makeToken($_MULTIPLY);
          $EndAction
        ./
    Token ::= '('
        /.$BeginAction
                    makeToken($_LPAREN);
          $EndAction
        ./
    Token ::= ')'
        /.$BeginAction
                    makeToken($_RPAREN);
          $EndAction
        ./
    Token ::= WS -- White Space is scanned and ignored

    IntegerLiteral -> Digit 
    			| IntegerLiteral Digit

    WS -> WSChar
        | WS WSChar

$End