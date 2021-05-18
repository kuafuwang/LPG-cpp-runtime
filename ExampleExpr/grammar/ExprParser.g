%options ast_directory=./ExprAst,automatic_ast=topLevel,var=nt,visitor=default
%options programming_language=rt_cpp
%options template=dtParserTemplateD.g
%options import_terminals=ExprLexer.g
$Terminals
 IntegerLiteral
 PLUS ::= +
 MULTIPLY ::= *
 LPAREN ::= (
 RPAREN ::= )
$end
$Rules
 E ::= E + T
 | T
 T ::= T * F
 | F
 F ::= IntegerLiteral
 F$ParenExpr ::= ( E )
$End