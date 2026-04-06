%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
int yylex();
void yyerror(const char *s);

typedef void* YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char *);
extern void yy_delete_buffer(YY_BUFFER_STATE);

#define MAX_STACK 100
char stack_trace[MAX_STACK][50];
int top = -1;

char input_buffer[8192];
int input_pos = 0;

int error_count = 0;

void push(const char *symbol) {
    if (top >= MAX_STACK - 1) return;
    strcpy(stack_trace[++top], symbol);
}

void pop_n(int n) {
    if (top < n - 1) { top = -1; return; }
    top -= n;
}

void print_stack() {
    printf("$ ");
    for (int i = 0; i <= top; i++)
        printf("%s ", stack_trace[i]);
}

void print_input() {
    for (int i = input_pos; input_buffer[i] != '\0'; i++)
        printf("%c", input_buffer[i]);
}

void print_action(const char *action) {
    printf("%-25s", "");
    print_stack();
    printf("\t");
    print_input();
    printf("\t%s\n", action);
}

typedef struct node {
    char* token;
    struct node *left, *mid, *right;
} node;

node* mknode(char* token, node* left, node* mid, node* right) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->token = strdup(token);
    newnode->left  = left;
    newnode->mid   = mid;
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
    for (int i = 0; i < 3; i++) if (children[i]) lastIdx = i;
    for (int i = 0; i <= lastIdx; i++)
        if (children[i]) printGraphicalTree(children[i], newPrefix, i == lastIdx);
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

node* root;

#define MAX_NT       15     
#define MAX_T        40    
#define MAX_RHS      10      
#define MAX_PROD    50     
#define SYM_LEN      20     

#define NT_PROGRAM      0
#define NT_STMT_LIST    1
#define NT_STMT         2
#define NT_TYPE         3
#define NT_DECLARATION  4
#define NT_ASSIGNMENT   5
#define NT_IF_STMT      6
#define NT_WHILE_STMT   7
#define NT_PRINT_STMT   8
#define NT_BLOCK        9
#define NT_EXPR        10
#define NT_TERM        11
#define NT_FACTOR      12
#define NT_BOOL_EXPR   13
#define NT_RELOP       14

static const char *nt_name[MAX_NT] = {
    "program", "stmt_list", "stmt", "type", "declaration",
    "assignment", "if_stmt", "while_stmt", "print_stmt", "block",
    "expr", "term", "factor", "bool_expr", "relop"
};

typedef struct {
    int  lhs;                       
    char rhs[MAX_RHS][SYM_LEN];    
    int  rhs_len;
    int  has_eps;                
} Production;

static Production prods[MAX_PROD];
static int        prod_count = 0;

typedef struct {
    char terms[MAX_T][SYM_LEN];
    int  count;
    int  has_eps;   
} TermSet;

static TermSet first_set[MAX_NT];
static TermSet follow_set[MAX_NT];

static void ts_add(TermSet *s, const char *t) {
    for (int i = 0; i < s->count; i++)
        if (strcmp(s->terms[i], t) == 0) return;
    if (s->count < MAX_T)
        strcpy(s->terms[s->count++], t);
}

static int ts_merge(TermSet *dst, const TermSet *src) {
    int changed = 0;
    for (int i = 0; i < src->count; i++) {
        int found = 0;
        for (int j = 0; j < dst->count; j++)
            if (strcmp(dst->terms[j], src->terms[i]) == 0) { found = 1; break; }
        if (!found && dst->count < MAX_T) {
            strcpy(dst->terms[dst->count++], src->terms[i]);
            changed = 1;
        }
    }
    return changed;
}

static int is_nt(const char *sym) { return sym[0] == '#'; }
static int nt_idx(const char *sym) { return atoi(sym + 1); }

static Production *begin_prod(int lhs_idx) {
    Production *p = &prods[prod_count++];
    p->lhs = lhs_idx; p->rhs_len = 0; p->has_eps = 0;
    return p;
}
static void prod_sym(Production *p, const char *s) {
    if (p->rhs_len < MAX_RHS) strcpy(p->rhs[p->rhs_len++], s);
}
static void prod_nt(Production *p, int idx) {
    char buf[8]; sprintf(buf, "#%d", idx);
    if (p->rhs_len < MAX_RHS) strcpy(p->rhs[p->rhs_len++], buf);
}
static void end_prod(Production *p) { p->has_eps = (p->rhs_len == 0); }

#define BP(lhs)  { Production *p = begin_prod(lhs);
#define S(s)       prod_sym(p, s);
#define N(idx)     prod_nt(p,  idx);
#define EP()       end_prod(p); }

static void build_grammar(void) {
    prod_count = 0;

    BP(NT_PROGRAM)    N(NT_STMT_LIST)                                          EP()

    BP(NT_STMT_LIST)  N(NT_STMT_LIST)  N(NT_STMT)                              EP()
    BP(NT_STMT_LIST)  N(NT_STMT)                                               EP()

    BP(NT_STMT)       N(NT_DECLARATION)                                        EP()
    BP(NT_STMT)       N(NT_ASSIGNMENT)                                         EP()
    BP(NT_STMT)       N(NT_IF_STMT)                                            EP()
    BP(NT_STMT)       N(NT_WHILE_STMT)                                         EP()
    BP(NT_STMT)       N(NT_PRINT_STMT)                                         EP()
    BP(NT_STMT)       N(NT_BLOCK)                                              EP()

    BP(NT_TYPE)       S("int")                                                 EP()
    BP(NT_TYPE)       S("float")                                               EP()

    BP(NT_DECLARATION) N(NT_TYPE) S("id") S(";")                              EP()
    BP(NT_DECLARATION) N(NT_TYPE) S("id") S("=") N(NT_EXPR) S(";")           EP()

    BP(NT_ASSIGNMENT)  S("id") S("=") N(NT_EXPR) S(";")                      EP()

    BP(NT_IF_STMT)    S("if") S("(") N(NT_BOOL_EXPR) S(")") N(NT_STMT)       EP()
    BP(NT_IF_STMT)    S("if") S("(") N(NT_BOOL_EXPR) S(")") N(NT_STMT) S("else") N(NT_STMT) EP()

    BP(NT_WHILE_STMT) S("while") S("(") N(NT_BOOL_EXPR) S(")") N(NT_STMT)   EP()

    BP(NT_PRINT_STMT) S("print") S("(") N(NT_EXPR) S(")") S(";")            EP()

    BP(NT_BLOCK)      S("{") N(NT_STMT_LIST) S("}")                           EP()

    BP(NT_EXPR)       N(NT_EXPR) S("+") N(NT_TERM)                           EP()
    BP(NT_EXPR)       N(NT_EXPR) S("-") N(NT_TERM)                           EP()
    BP(NT_EXPR)       N(NT_TERM)                                              EP()

    BP(NT_TERM)       N(NT_TERM) S("*") N(NT_FACTOR)                         EP()
    BP(NT_TERM)       N(NT_TERM) S("/") N(NT_FACTOR)                         EP()
    BP(NT_TERM)       N(NT_TERM) S("%") N(NT_FACTOR)                         EP()
    BP(NT_TERM)       N(NT_FACTOR)                                            EP()

    BP(NT_FACTOR)     S("(") N(NT_EXPR) S(")")                               EP()
    BP(NT_FACTOR)     S("Int_num")                                            EP()
    BP(NT_FACTOR)     S("Float_num")                                          EP()
    BP(NT_FACTOR)     S("id")                                                 EP()

    BP(NT_BOOL_EXPR)  N(NT_BOOL_EXPR) S("&&") N(NT_BOOL_EXPR)               EP()
    BP(NT_BOOL_EXPR)  N(NT_BOOL_EXPR) S("||") N(NT_BOOL_EXPR)               EP()
    BP(NT_BOOL_EXPR)  S("!")  N(NT_BOOL_EXPR)                                EP()
    BP(NT_BOOL_EXPR)  N(NT_EXPR) N(NT_RELOP) N(NT_EXPR)                      EP()
    BP(NT_BOOL_EXPR)  S("(") N(NT_BOOL_EXPR) S(")")                          EP()

    BP(NT_RELOP)      S("<")                                                  EP()
    BP(NT_RELOP)      S(">")                                                  EP()
    BP(NT_RELOP)      S("<=")                                                 EP()
    BP(NT_RELOP)      S(">=")                                                 EP()
    BP(NT_RELOP)      S("==")                                                 EP()
    BP(NT_RELOP)      S("!=")                                                 EP()

#undef BP
#undef S
#undef N
#undef EP
}

static int first_of_string(char rhs[][SYM_LEN], int len, TermSet *out) {
    if (len == 0) { out->has_eps = 1; return 1; }
    int all_nullable = 1;
    for (int i = 0; i < len; i++) {
        if (is_nt(rhs[i])) {
            int ni = nt_idx(rhs[i]);
            ts_merge(out, &first_set[ni]);
            if (!first_set[ni].has_eps) { all_nullable = 0; break; }
        } else {
            ts_add(out, rhs[i]);
            all_nullable = 0;
            break;
        }
    }
    if (all_nullable) out->has_eps = 1;
    return all_nullable;
}

static void compute_first(void) {
    memset(first_set, 0, sizeof(first_set));
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < prod_count; i++) {
            Production *p = &prods[i];
            TermSet tmp; memset(&tmp, 0, sizeof(tmp));
            int nullable = first_of_string(p->rhs, p->rhs_len, &tmp);
            if (nullable && !first_set[p->lhs].has_eps) {
                first_set[p->lhs].has_eps = 1; changed = 1;
            }
            if (ts_merge(&first_set[p->lhs], &tmp)) changed = 1;
        }
    }
}

static void compute_follow(void) {
    memset(follow_set, 0, sizeof(follow_set));
    ts_add(&follow_set[NT_PROGRAM], "$");

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < prod_count; i++) {
            Production *p = &prods[i];
            for (int j = 0; j < p->rhs_len; j++) {
                if (!is_nt(p->rhs[j])) continue;
                int B = nt_idx(p->rhs[j]);
                TermSet tmp; memset(&tmp, 0, sizeof(tmp));
                int beta_nullable = first_of_string(p->rhs + j + 1,
                                                    p->rhs_len - j - 1, &tmp);
                if (ts_merge(&follow_set[B], &tmp)) changed = 1;
                if (beta_nullable) {
                    if (ts_merge(&follow_set[B], &follow_set[p->lhs])) changed = 1;
                }
            }
        }
    }
}

static void print_term_set(const TermSet *s) {
    printf("{ ");
    for (int i = 0; i < s->count; i++) printf("%s, ", s->terms[i]);
    if (s->has_eps) printf("ε ");
    printf("}");
}

void printFirstSets(void) {
    printf("\nFIRST sets:\n");
    for (int i = 0; i < MAX_NT; i++) {
        printf("  FIRST(%-14s) = ", nt_name[i]);
        print_term_set(&first_set[i]);
        printf("\n");
    }
}

void printFollowSets(void) {
    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < MAX_NT; i++) {
        printf("  FOLLOW(%-14s) = ", nt_name[i]);
        print_term_set(&follow_set[i]);
        printf("\n");
    }
}

void printLL1Table() {
    printf("\nLL(1) Parsing Table:\n");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "Non-terminal","int/float","id","if","while","print","{","$");
    printf("%-15s-+-%-10s-+-%-9s-+-%-9s-+-%-9s-+-%-9s-+-%-7s-+%s\n",
           "---------------","-----------","----------","----------","----------","----------","--------","----");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "program","->SL","->SL","->SL","->SL","->SL","->SL","-");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "stmt_list","->SL stmt","->SL stmt","->SL stmt","->SL stmt","->SL stmt","->SL stmt","-");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "stmt","->decl","->assign","->if","->while","->print","->block","-");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "type","->int/flt","-","-","-","-","-","-");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "declaration","->type id;","-","-","-","-","-","-");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "assignment","-","->id=e;","-","-","-","-","-");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "if_stmt","-","-","->if(b)s","-","-","-","-");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "while_stmt","-","-","-","->wh(b)s","-","-","-");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "print_stmt","-","-","-","-","->pr(e);","-","-");
    printf("%-15s | %-10s | %-9s | %-9s | %-9s | %-9s | %-7s | %s\n",
           "block","-","-","-","-","-","->{SL}","-");
    printf("%-15s | %-16s | %-12s | %-8s | %s\n",
           "Non-terminal","id/Int_num/Float","( ... )","!","relops");
    printf("%-15s-+-%-16s-+-%-12s-+-%-8s-+%s\n",
           "---------------","-----------------","-------------","---------","-------------------");
    printf("%-15s | %-16s | %-12s | %-8s | %s\n",
           "expr","->term","->term","-","-");
    printf("%-15s | %-16s | %-12s | %-8s | %s\n",
           "term","->factor","->factor","-","-");
    printf("%-15s | %-16s | %-12s | %-8s | %s\n",
           "factor","->id/Int/Float","->(expr)","-","-");
    printf("%-15s | %-16s | %-12s | %-8s | %s\n",
           "bool_expr","->e relop e","->e relop e","->!bool","-");
    printf("%-15s | %-16s | %-12s | %-8s | %s\n",
           "relop","-","-","-","-> operator node");
}
%}

%union {
    char* sval;
    struct node* n;
}

%token INT FLOAT IF ELSE WHILE PRINT
%token <sval> ID Int_num Float_num
%token AND OR NOT
%token LE GE EQ NE LT GT

%type <n> program stmt stmt_list declaration type assignment
%type <n> if_stmt while_stmt print_stmt block
%type <n> expr term factor bool_expr relop


%left OR
%left AND
%right NOT
%left EQ NE
%left LT GT LE GE
%left '+' '-'
%left '*' '/' '%'

%%

program:
    stmt_list { root = $1; }
;

stmt_list:
    stmt_list stmt {
        pop_n(2); push("STMT_LIST");
        $$ = mknode("STMT_LIST", $1, $2, NULL);
    }
  | stmt {
        pop_n(1); push("STMT_LIST");
        $$ = $1;
    }
;

stmt:
    declaration  { $$ = $1; }
  | assignment   { $$ = $1; }
  | if_stmt      { $$ = $1; }
  | while_stmt   { $$ = $1; }
  | print_stmt   { $$ = $1; }
  | block        { $$ = $1; }

  | error ';' {
        fprintf(stderr, "Reason: Ill-formed statement — possibly missing ';' or ')'\n\n");
        $$ = mknode("ERROR_STMT", NULL, NULL, NULL);
        yyerrok;
    }
  | error '}' {
        fprintf(stderr, "Reason: Ill-formed block — possibly missing '{' or extra '}'\n\n");
        $$ = mknode("ERROR_BLOCK", NULL, NULL, NULL);
        yyerrok;
    }
;

type:
    INT   { $$ = mknode("int",   NULL, NULL, NULL); }
  | FLOAT { $$ = mknode("float", NULL, NULL, NULL); }
;

declaration:
    type ID ';' {
        pop_n(3); push("DECL");
        printf("------Line %d: Syntactic Validation [Declaration: %s]\n", yylineno, $2);
        print_action("reduce declaration");
        $$ = mknode("Decl", $1, mknode($2, NULL, NULL, NULL), NULL);
    }
  | type ID '=' expr ';' {
        pop_n(5); push("DECL");
        printf("------Line %d: Syntactic Validation [Decl & Assign: %s]\n", yylineno, $2);
        print_action("reduce decl-assign");
        $$ = mknode("Decl=", $1, mknode($2, NULL, NULL, NULL), $4);
    }
  | type error ';' {
        fprintf(stderr, "Reason: Invalid declaration — expected variable name after type\n\n");
        $$ = mknode("ERROR_DECL", $1, NULL, NULL);
        yyerrok;
    }
;

assignment:
    ID '=' expr ';' {
        pop_n(4); push("ASSIGN");
        printf("------Line %d: Syntactic Validation [Assignment to %s]\n", yylineno, $1);
        print_action("reduce assignment");
        $$ = mknode("=", mknode($1, NULL, NULL, NULL), $3, NULL);
    }
  | ID '=' error ';' {
        fprintf(stderr, "Reason: Invalid assignment — ill-formed expression\n\n");
        $$ = mknode("ERROR_ASSIGN", mknode($1, NULL, NULL, NULL), NULL, NULL);
        yyerrok;
    }
  | ID error ';' {
        fprintf(stderr, "Reason: Invalid assignment — missing '=' after '%s'\n\n", $1);
        $$ = mknode("ERROR_ASSIGN", mknode($1, NULL, NULL, NULL), NULL, NULL);
        yyerrok;
    }
;

print_stmt:
    PRINT '(' expr ')' ';' {
        pop_n(5); push("PRINT");
        printf("-------Line %d: Syntactic Validation [Print Statement]\n", yylineno);
        print_action("reduce print");
        $$ = mknode("PRINT", $3, NULL, NULL);
    }
  | PRINT '(' error ')' ';' {
        fprintf(stderr, "Reason: Invalid print — ill-formed expression\n\n");
        $$ = mknode("ERROR_PRINT", NULL, NULL, NULL);
        yyerrok;
    }
  | PRINT error ';' {
        fprintf(stderr, "Reason: Invalid print — missing '(' / ')'\n\n");
        $$ = mknode("ERROR_PRINT", NULL, NULL, NULL);
        yyerrok;
    }
;

block:
    '{' stmt_list '}' { $$ = $2; }
  | '{' error '}' {
        fprintf(stderr, "Reason: Ill-formed block body\n\n");
        $$ = mknode("ERROR_BLOCK", NULL, NULL, NULL);
        yyerrok;
    }
;

if_stmt:
    IF '(' bool_expr ')' stmt {
        pop_n(5); push("IF");
        printf("------Line %d: Syntactic Validation [If Block]\n", yylineno);
        print_action("reduce if");
        $$ = mknode("IF", $3, $5, NULL);
    }
  | IF '(' bool_expr ')' stmt ELSE stmt {
        pop_n(7); push("IF-ELSE");
        printf("-----Line %d: Syntactic Validation [If-Else Block]\n", yylineno);
        print_action("reduce if-else");
        $$ = mknode("IF-ELSE", $3, $5, $7);
    }
  | IF '(' error ')' stmt {
        fprintf(stderr, "Reason: Invalid if — ill-formed condition\n\n");
        $$ = mknode("ERROR_IF", NULL, $5, NULL);
        yyerrok;
    }
  | IF error stmt {
        fprintf(stderr, "Reason: Invalid if — missing '(' / ')'\n\n");
        $$ = mknode("ERROR_IF", NULL, $3, NULL);
        yyerrok;
    }
;

while_stmt:
    WHILE '(' bool_expr ')' stmt {
        pop_n(5); push("WHILE");
        printf("-----Line %d: Syntactic Validation [While Loop]\n", yylineno);
        print_action("reduce while");
        $$ = mknode("WHILE", $3, $5, NULL);
    }
  | WHILE '(' error ')' stmt {
        fprintf(stderr, "Reason: Invalid while — ill-formed condition\n\n");
        $$ = mknode("ERROR_WHILE", NULL, $5, NULL);
        yyerrok;
    }
  | WHILE error stmt {
        fprintf(stderr, "Reason: Invalid while — missing '(' / ')'\n\n");
        $$ = mknode("ERROR_WHILE", NULL, $3, NULL);
        yyerrok;
    }
;

expr:
    expr '+' term { pop_n(3); push("expr"); $$ = mknode("+", $1, $3, NULL); }
  | expr '-' term { pop_n(3); push("expr"); $$ = mknode("-", $1, $3, NULL); }
  | term          { pop_n(1); push("expr"); $$ = $1; }
;

term:
    term '*' factor { pop_n(3); push("term"); $$ = mknode("*",  $1, $3, NULL); }
  | term '/' factor { pop_n(3); push("term"); $$ = mknode("/",  $1, $3, NULL); }
  | term '%' factor { pop_n(3); push("term"); $$ = mknode("%",  $1, $3, NULL); }
  | factor          { pop_n(1); push("term"); $$ = $1; }
;

factor:
    '(' expr ')'  { pop_n(3); push("factor"); $$ = $2; }
  | Int_num       { pop_n(1); push("factor"); $$ = mknode($1, NULL, NULL, NULL); }
  | Float_num     { pop_n(1); push("factor"); $$ = mknode($1, NULL, NULL, NULL); }
  | ID            { pop_n(1); push("factor"); $$ = mknode($1, NULL, NULL, NULL); }
;

bool_expr:
    bool_expr AND bool_expr { pop_n(3); push("bool"); $$ = mknode("&&", $1, $3, NULL); }
  | bool_expr OR  bool_expr { pop_n(3); push("bool"); $$ = mknode("||", $1, $3, NULL); }
  | NOT bool_expr           { pop_n(2); push("bool"); $$ = mknode("!",  $2, NULL, NULL); }
  | expr relop expr         { pop_n(3); push("bool"); $$ = mknode("RELOP", $1, $2, $3); }
  | '(' bool_expr ')'       { pop_n(3); push("bool"); $$ = $2; }
;

relop:
    LT { $$ = mknode("<",  NULL, NULL, NULL); }
  | GT { $$ = mknode(">",  NULL, NULL, NULL); }
  | LE { $$ = mknode("<=", NULL, NULL, NULL); }
  | GE { $$ = mknode(">=", NULL, NULL, NULL); }
  | EQ { $$ = mknode("==", NULL, NULL, NULL); }
  | NE { $$ = mknode("!=", NULL, NULL, NULL); }
;

%%

void yyerror(const char *s) {
    extern char *yytext;
    error_count++;

    if (strcmp(yytext, "") == 0 || strcmp(yytext, "$end") == 0)
        fprintf(stderr, "Syntax error at line %d: Unexpected end of input — possibly missing ';' or '}'\n", yylineno);
    else if (strcmp(yytext, ";") == 0)
        fprintf(stderr, "Syntax error at line %d: Unexpected ';' — ill-formed statement before semicolon\n", yylineno);
    else if (strcmp(yytext, ")") == 0)
        fprintf(stderr, "Syntax error at line %d: Unexpected ')' — missing opening '(' or extra ')'\n", yylineno);
    else if (strcmp(yytext, "(") == 0)
        fprintf(stderr, "Syntax error at line %d: Unexpected '(' — missing closing ')' or ';' before this\n", yylineno);
    else if (strcmp(yytext, "}") == 0)
        fprintf(stderr, "Syntax error at line %d: Unexpected '}' — missing '{' or extra '}'\n", yylineno);
    else if (strcmp(yytext, "{") == 0)
        fprintf(stderr, "Syntax error at line %d: Unexpected '{' — missing '}' from a previous block or ';'\n", yylineno);
    else if (strcmp(yytext, "=") == 0)
        fprintf(stderr, "Syntax error at line %d: Unexpected '=' — missing variable name or invalid target\n", yylineno);
    else
        fprintf(stderr, "Syntax error at line %d: Unexpected token '%s'\n", yylineno, yytext);
}

int main() {
    /* Build grammar and compute FIRST/FOLLOW before parsing */
    build_grammar();
    compute_first();
    compute_follow();

    printf("PARSING STARTED\n\n");
    int pos = 0;
    char line[256];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        int len = strlen(line);
        if (pos + len < (int)sizeof(input_buffer) - 1) {
            strcpy(input_buffer + pos, line);
            pos += len;
        }
    }
    input_buffer[pos] = '\0';

    YY_BUFFER_STATE bp = yy_scan_string(input_buffer);

    printf("\nSTACK TRACE TABLE:\n");
    printf("STACK\t\tINPUT\t\tACTION\n");
    printf("----------------------------------------\n");

    yyparse();

    if (error_count == 0) {
        printf("\nRESULT: Parsing successful — no syntax errors detected.\n");

        printf("\nGRAPHICAL SYNTAX TREE:\n\n");
        printGraphicalTree(root, "", 1);
        printf("\n");

        printf("\nLEFTMOST DERIVATION:\n");
        printLMD(root);
        printf("\n");

        printf("\nRIGHTMOST DERIVATION:\n");
        printRMD(root);
        printf("\n");
    } else {
        printf("\nRESULT: Parsing completed with %d syntax error(s) — see errors above.\n", error_count);
    }

    printFirstSets();
    printFollowSets();
    printLL1Table();

    yy_delete_buffer(bp);
    return (error_count > 0) ? 1 : 0;
}