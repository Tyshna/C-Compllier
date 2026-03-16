%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int line;
int yylex();
void yyerror(const char *s);

/* 1. Node Structure */
typedef struct node {
    char *token;
    struct node *left;
    struct node *mid;
    struct node *right;
} node;

node* mknode(char* token, node* left, node* mid, node* right);
void printGraphicalTree(node* root, char* prefix, int isLast);
void printLMD(node* root);
void printRMD(node* root);

node *final_root = NULL;
%}

%union {
    char* sval;
    struct node* nval;
}

%token INT FLOAT IF ELSE WHILE PRINT
%token <sval> ID Int_num Float_num
%token AND OR NOT
%token LE GE EQ NE LT GT

/* Non-terminal types */
%type <nval> program stmt_list stmt declaration type assignment print_stmt block if_stmt while_stmt expr term factor bool_expr relop

%left OR
%left AND
%right NOT
%left EQ NE
%left LT GT LE GE
%left '+' '-'
%left '*' '/' '%'

%%
program:
    stmt_list { final_root = $1; }
    ;

stmt_list:
    stmt_list stmt { $$ = mknode("STMT_LIST", $1, $2, NULL); }
    | stmt         { $$ = $1; }
    ;

stmt:
    declaration    { $$ = $1; }
    | assignment   { $$ = $1; }
    | if_stmt      { $$ = $1; }
    | while_stmt   { $$ = $1; }
    | print_stmt   { $$ = $1; }
    | block        { $$ = $1; }
    ;

declaration:
    type ID ';' { 
        printf("Line %d: Syntactic Validation [Declaration: %s]\n", line, $2);
        $$ = mknode("Decl", $1, mknode($2, NULL, NULL, NULL), NULL); 
    }
    | type ID '=' expr ';' { 
        printf("Line %d: Syntactic Validation [Decl & Assign: %s]\n", line, $2);
        $$ = mknode("Decl=", $1, mknode($2, NULL, NULL, NULL), $4); 
    }
    ;

type:
    INT   { $$ = mknode("int", NULL, NULL, NULL); }
    | FLOAT { $$ = mknode("float", NULL, NULL, NULL); }
    ;

assignment:
    ID '=' expr ';' { 
        printf("Line %d: Syntactic Validation [Assignment to %s]\n", line, $1);
        $$ = mknode("=", mknode($1, NULL, NULL, NULL), $3, NULL); 
    }
    ;

print_stmt:
    PRINT '(' expr ')' ';' { 
        printf("Line %d: Syntactic Validation [Print Statement]\n", line);
        $$ = mknode("PRINT", $3, NULL, NULL); 
    }
    ;

block:
    '{' stmt_list '}' { $$ = $2; }
    ;

if_stmt:
    IF '(' bool_expr ')' stmt { 
        printf("Line %d: Syntactic Validation [If Block]\n", line);
        $$ = mknode("IF", $3, $5, NULL); 
    }
    | IF '(' bool_expr ')' stmt ELSE stmt { 
        printf("Line %d: Syntactic Validation [If-Else Block]\n", line);
        $$ = mknode("IF-ELSE", $3, $5, $7); 
    }
    ;

while_stmt:
    WHILE '(' bool_expr ')' stmt { 
        printf("Line %d: Syntactic Validation [While Loop]\n", line);
        $$ = mknode("WHILE", $3, $5, NULL); 
    }
    ;

expr:
    expr '+' term { $$ = mknode("+", $1, $3, NULL); }
    | expr '-' term { $$ = mknode("-", $1, $3, NULL); }
    | term { $$ = $1; }
    ;

term:
    term '*' factor { $$ = mknode("*", $1, $3, NULL); }
    | term '/' factor { $$ = mknode("/", $1, $3, NULL); }
    | term '%' factor { $$ = mknode("%", $1, $3, NULL); }
    | factor { $$ = $1; }
    ;

factor:
    '(' expr ')' { $$ = $2; }
    | ID        { $$ = mknode($1, NULL, NULL, NULL); }
    | Int_num   { $$ = mknode($1, NULL, NULL, NULL); }
    | Float_num { $$ = mknode($1, NULL, NULL, NULL); }
    ;

bool_expr:
    bool_expr AND bool_expr { $$ = mknode("&&", $1, $3, NULL); }
    | bool_expr OR bool_expr  { $$ = mknode("||", $1, $3, NULL); }
    | NOT bool_expr           { $$ = mknode("!", $2, NULL, NULL); }
    | expr relop expr         { $$ = mknode("RELOP", $1, $2, $3); }
    | '(' bool_expr ')'       { $$ = $2; }
    ;

relop:
    LT { $$ = mknode("<", NULL, NULL, NULL); }
    | GT { $$ = mknode(">", NULL, NULL, NULL); }
    | LE { $$ = mknode("<=", NULL, NULL, NULL); }
    | GE { $$ = mknode(">=", NULL, NULL, NULL); }
    | EQ { $$ = mknode("==", NULL, NULL, NULL); }
    | NE { $$ = mknode("!=", NULL, NULL, NULL); }
    ;
%%

/* --- Helper Functions --- */

node* mknode(char* token, node* left, node* mid, node* right) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->token = strdup(token);
    newnode->left = left;
    newnode->mid = mid;
    newnode->right = right;
    return newnode;
}

void printGraphicalTree(node* root, char* prefix, int isLast) {
    if (root == NULL) return;
    printf("%s%s%s\n", prefix, (isLast ? "└── " : "├── "), root->token);
    char newPrefix[512];
    sprintf(newPrefix, "%s%s", prefix, (isLast ? "    " : "│   "));

    node *children[3] = {root->left, root->mid, root->right};
    int lastIdx = -1;
    for(int i=0; i<3; i++) if(children[i]) lastIdx = i;
    for(int i=0; i<=lastIdx; i++) {
        if(children[i]) printGraphicalTree(children[i], newPrefix, i == lastIdx);
    }
}

void printLMD(node* root) {
    if (root == NULL) return;
    printf("%s ", root->token);
    printLMD(root->left);
    printLMD(root->mid);
    printLMD(root->right);
}

void printRMD(node* root) {
    if (root == NULL) return;
    printf("%s ", root->token);
    printRMD(root->right);
    printRMD(root->mid);
    printRMD(root->left);
}

int main() {
    printf("--- PARSING STARTED ---\n\n");
    if (yyparse() == 0) {
        printf("\nRESULT: Success.\n");
        printf("\n>>> GRAPHICAL SYNTAX TREE:\n\n");
        printGraphicalTree(final_root, "", 1);

        printf("\n>>> LEFTMOST DERIVATION:\n");
        printLMD(final_root);
        printf("\n\n>>> RIGHTMOST DERIVATION:\n");
        printRMD(final_root);
        printf("\n");
    } else {
        printf("\nRESULT: Failed.\n");
    }
    return 0;
}

void yyerror(const char *s) {
    extern int line;
    fprintf(stderr, "Syntax error at line %d: %s\n", line, s);
}