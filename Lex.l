%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int line = 1;
%}

Digit [0-9]
Letter [a-zA-Z_]
ID {Letter}({Letter}|{Digit})*
Int_num {Digit}+
Float_num {Digit}+"."{Digit}+

%%
"int" { printf("Int keyword\n"); }
"float" { printf("Float keyword\n"); }
"if" { printf("If\n"); }
"else"  { printf("Else\n"); }
"while" { printf("While Statement\n"); }
"print" { printf("Print Statement\n"); }

"&&" { printf("And\n"); }
"||" { printf("Or\n"); }
"!" { printf("Not\n"); }

"<=" { printf("Less Than Equal\n"); }
">=" { printf("Greater Than Equal\n"); }
"==" { printf("Equal\n"); }
"!=" { printf("Not Equal\n"); }
"<" { printf("Less Than\n"); }
">" { printf("Greater Than\n"); }

"+" { printf("Plus\n"); }
"-" { printf("Minus\n"); }
"*" { printf("Multiply"); }
"/" { printf("Divide\n"); }
"%" { printf("Mod\n"); }

";" { printf("Semicolon\n"); }
"{" { printf("Left Brace\n"); }
"}" { printf("Right Brace\n"); }
"(" { printf("Left Paren\n"); }
")" { printf("Right Paren\n"); }

{Float_num} { printf("Float Literal(%s)\n", yytext); }
{Int_num} { printf("Int Literal(%s)\n", yytext); }
{ID} { printf("Identifier(%s)\n", yytext); }

[ \t]+ { /* ignore whitespace */ }
\n { line++; }

. { printf("Lexical error at line %d: %s\n", line, yytext); }
%%

int main() {
    yylex();
    return 0;
}   