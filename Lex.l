%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

int line = 1;
%}

%%

"int"       { return INT; }
"float"     { return FLOAT; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"print"     { return PRINT; }

"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }
"<="        { return LE; }
">="        { return GE; }
"=="        { return EQ; }
"!="        { return NE; }
"<"         { return LT; }
">"         { return GT; }

[a-zA-Z][a-zA-Z0-9]* { 
    yylval.sval = strdup(yytext); 
    return ID; 
}

[0-9]+"."[0-9]+ { 
    yylval.sval = strdup(yytext); 
    return Float_num; 
}

[0-9]+ { 
    yylval.sval = strdup(yytext); 
    return Int_num; 
}

[ \t]       { /* Ignore whitespace */ }
[\n]        { line++; }

"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"%"         { return '%'; }
"="         { return '='; }
";"         { return ';'; }
"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }

.           { printf("Unknown character: %s at line %d\n", yytext, line); }

%%

int yywrap() {
    return 1;
}