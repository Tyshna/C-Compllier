%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
int line = 1;
%}

Digit       [0-9]
Letter      [a-zA-Z]
ID          {Letter}({Letter}|{Digit})*
Int_num     {Digit}+
Float_num   {Digit}+"."{Digit}+

%%
"int"   { printf("Int keyword\n"); return INT; }
"float" { printf("Float keyword\n"); return FLOAT; }
"if"    { printf("If\n"); return IF; }
"else"  { printf("Else\n"); return ELSE; }
"while" { printf("While Statement\n"); return WHILE; }
"print" { printf("Print Statement\n"); return PRINT; }

"&&" { printf("And\n"); return AND; }
"||" { printf("Or\n"); return OR; }
"!"  { printf("Not\n"); return NOT; }

"<=" { printf("Less Than Equal\n"); return LE; }
">=" { printf("Greater Than Equal\n"); return GE; }
"==" { printf("Equal\n"); return EQ; }
"!=" { printf("Not Equal\n"); return NE; }
"<"  { printf("Less Than\n"); return LT; }
">"  { printf("Greater Than\n"); return GT; }

"=" { printf("Assignment\n"); return '='; }
"+" { printf("Plus\n"); return '+'; }
"-" { printf("Minus\n"); return '-'; }
"*" { printf("Multiply\n"); return '*'; }
"/" { printf("Divide\n"); return '/'; }
"%" { printf("Mod\n"); return '%'; }

";" { printf("Semicolon\n"); return ';'; }
"{" { printf("Left Brace\n"); return '{'; }
"}" { printf("Right Brace\n"); return '}'; }
"(" { printf("Left Paren\n"); return '('; }
")" { printf("Right Paren\n"); return ')'; }

{Float_num} { printf("Float Literal(%s)\n", yytext); return Float_num; }
{Int_num}   { printf("Int Literal(%s)\n", yytext); return Int_num; }

{ID}        { printf("Identifier(%s)\n", yytext); return ID; }

[ \t]+      { /* ignore whitespace */ }
\n          { line++; }

. { printf("Lexical error at line %d: %s\n", line, yytext); }

%%

int yywrap() {
    return 1;
}