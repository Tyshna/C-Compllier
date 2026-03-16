%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%token INT FLOAT IF ELSE WHILE PRINT
%token ID
%token Int_num Float_num
%token AND OR NOT
%token LE GE EQ NE LT GT

%%
program
    : stmt_list
    ;

stmt_list
    : stmt_list stmt
    | stmt
    ;

stmt
    : declaration
    | assignment
    | if_stmt
    | while_stmt
    | print_stmt
    | block
    ;

declaration
    : type ID ';'
    | type ID '=' expr ';'
    ;

type
    : INT
    | FLOAT
    ;

assignment
    : ID '=' expr ';'
    ;

print_stmt
    : PRINT '(' expr ')' ';'
    ;

block
    : '{' stmt_list '}'
    ;

if_stmt
    : IF '(' bool_expr ')' stmt
    | IF '(' bool_expr ')' stmt ELSE stmt
    ;

while_stmt
    : WHILE '(' bool_expr ')' stmt
    ;

expr
    : expr '+' term
    | expr '-' term
    | term
    ;

term
    : term '*' factor
    | term '/' factor
    | term '%' factor
    | factor
    ;

factor
    : '(' expr ')'
    | ID
    | Int_num
    | Float_num
    ;

bool_expr
    : bool_expr AND bool_expr
    | bool_expr OR bool_expr
    | NOT bool_expr
    | expr relop expr
    | '(' bool_expr ')'
    ;

relop
    : LT
    | GT
    | LE
    | GE
    | EQ
    | NE
    ;
%%

void yyerror(const char *s)
{
printf("Syntax error: %s\n", s);
}

int main()
{
printf("Parsing started...\n");
yyparse();
printf("Parsing finished\n");
return 0;
}