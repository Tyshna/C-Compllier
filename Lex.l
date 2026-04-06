%option noyywrap
%option yylineno

%{
#include "y.tab.h"
#include <stdio.h>
#include <string.h>

void push(const char *);
void print_action(const char *);

extern char input_buffer[];
extern int input_pos;
%}

%%

"int"      { push("INT");   print_action("shift INT");   input_pos += yyleng; return INT; }
"float"    { push("FLOAT"); print_action("shift FLOAT"); input_pos += yyleng; return FLOAT; }
"if"       { push("IF");    print_action("shift IF");    input_pos += yyleng; return IF; }
"else"     { push("ELSE");  print_action("shift ELSE");  input_pos += yyleng; return ELSE; }
"while"    { push("WHILE"); print_action("shift WHILE"); input_pos += yyleng; return WHILE; }
"print"    { push("PRINT"); print_action("shift PRINT"); input_pos += yyleng; return PRINT; }

"&&"       { push("AND"); print_action("shift AND"); input_pos += yyleng; return AND; }
"||"       { push("OR");  print_action("shift OR");  input_pos += yyleng; return OR; }
"!"        { push("NOT"); print_action("shift NOT"); input_pos += yyleng; return NOT; }

"<="       { push("LE"); print_action("shift LE"); input_pos += yyleng; return LE; }
">="       { push("GE"); print_action("shift GE"); input_pos += yyleng; return GE; }
"=="       { push("EQ"); print_action("shift EQ"); input_pos += yyleng; return EQ; }
"!="       { push("NE"); print_action("shift NE"); input_pos += yyleng; return NE; }
"<"        { push("LT"); print_action("shift LT"); input_pos += yyleng; return LT; }
">"        { push("GT"); print_action("shift GT"); input_pos += yyleng; return GT; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.sval = strdup(yytext);    
    push("ID"); print_action("shift ID");
    input_pos += yyleng;
    return ID;
}

[0-9]+"."[0-9]+ {
    yylval.sval = strdup(yytext);     
    push("FLOAT_NUM"); print_action("shift FLOAT_NUM");
    input_pos += yyleng;
    return Float_num;
}

[0-9]+ {
    yylval.sval = strdup(yytext);      
    push("INT_NUM"); print_action("shift INT_NUM");
    input_pos += yyleng;
    return Int_num;
}

"="   { push("=");  print_action("shift =");  input_pos += yyleng; return '='; }
";"   { push(";");  print_action("shift ;");  input_pos += yyleng; return ';'; }
"+"   { push("+");  print_action("shift +");  input_pos += yyleng; return '+'; }
"-"   { push("-");  print_action("shift -");  input_pos += yyleng; return '-'; } 
"*"   { push("*");  print_action("shift *");  input_pos += yyleng; return '*'; }
"/"   { push("/");  print_action("shift /");  input_pos += yyleng; return '/'; }   
"%"   { push("%");  print_action("shift %");  input_pos += yyleng; return '%'; }   
"("   { push("(");  print_action("shift (");  input_pos += yyleng; return '('; }
")"   { push(")");  print_action("shift )");  input_pos += yyleng; return ')'; }
"{"   { push("{");  print_action("shift {");  input_pos += yyleng; return '{'; }  
"}"   { push("}");  print_action("shift }");  input_pos += yyleng; return '}'; }   

[ \t\n]+  { input_pos += yyleng; }

.  { printf("Unknown char: %s at line %d\n", yytext, yylineno); }

%%