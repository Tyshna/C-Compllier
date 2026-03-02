%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line = 1;
%}

DIGIT      [0-9]
LETTER     [a-zA-Z_]
ID         {LETTER}({LETTER}|{DIGIT})*
INTNUM     {DIGIT}+
FLOATNUM   {DIGIT}+"."{DIGIT}+

%%

"int"           { printf("INT_KEYWORD\n"); }
"float"         { printf("FLOAT_KEYWORD\n"); }
"if"            { printf("IF\n"); }
"else"          { printf("ELSE\n"); }
"while"         { printf("WHILE\n"); }
"print"         { printf("PRINT\n"); }

"&&"            { printf("AND\n"); }
"||"            { printf("OR\n"); }
"!"             { printf("NOT\n"); }

"<="            { printf("LE\n"); }
">="            { printf("GE\n"); }
"=="            { printf("EQ\n"); }
"!="            { printf("NE\n"); }
"<"             { printf("LT\n"); }
">"             { printf("GT\n"); }

"+"             { printf("PLUS\n"); }
"-"             { printf("MINUS\n"); }
"*"             { printf("MUL\n"); }
"/"             { printf("DIV\n"); }
"%"             { printf("MOD\n"); }

";"             { printf("SEMICOLON\n"); }
"{"             { printf("LBRACE\n"); }
"}"             { printf("RBRACE\n"); }
"("             { printf("LPAREN\n"); }
")"             { printf("RPAREN\n"); }

{FLOATNUM}      { printf("FLOAT_LITERAL(%s)\n", yytext); }
{INTNUM}        { printf("INT_LITERAL(%s)\n", yytext); }
{ID}            { printf("IDENTIFIER(%s)\n", yytext); }

[ \t]+          { /* ignore whitespace */ }
\n              { line++; }

.               { printf("LEXICAL ERROR at line %d: %s\n", line, yytext); }

%%

int main() {
    yylex();
    return 0;
}   