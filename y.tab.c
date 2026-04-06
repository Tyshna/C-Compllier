/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

#line 448 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    FLOAT = 259,                   /* FLOAT  */
    IF = 260,                      /* IF  */
    ELSE = 261,                    /* ELSE  */
    WHILE = 262,                   /* WHILE  */
    PRINT = 263,                   /* PRINT  */
    ID = 264,                      /* ID  */
    Int_num = 265,                 /* Int_num  */
    Float_num = 266,               /* Float_num  */
    AND = 267,                     /* AND  */
    OR = 268,                      /* OR  */
    NOT = 269,                     /* NOT  */
    LE = 270,                      /* LE  */
    GE = 271,                      /* GE  */
    EQ = 272,                      /* EQ  */
    NE = 273,                      /* NE  */
    LT = 274,                      /* LT  */
    GT = 275                       /* GT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT 258
#define FLOAT 259
#define IF 260
#define ELSE 261
#define WHILE 262
#define PRINT 263
#define ID 264
#define Int_num 265
#define Float_num 266
#define AND 267
#define OR 268
#define NOT 269
#define LE 270
#define GE 271
#define EQ 272
#define NE 273
#define LT 274
#define GT 275

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 378 "parser.y"

    char* sval;
    struct node* n;

#line 546 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_PRINT = 8,                      /* PRINT  */
  YYSYMBOL_ID = 9,                         /* ID  */
  YYSYMBOL_Int_num = 10,                   /* Int_num  */
  YYSYMBOL_Float_num = 11,                 /* Float_num  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_OR = 13,                        /* OR  */
  YYSYMBOL_NOT = 14,                       /* NOT  */
  YYSYMBOL_LE = 15,                        /* LE  */
  YYSYMBOL_GE = 16,                        /* GE  */
  YYSYMBOL_EQ = 17,                        /* EQ  */
  YYSYMBOL_NE = 18,                        /* NE  */
  YYSYMBOL_LT = 19,                        /* LT  */
  YYSYMBOL_GT = 20,                        /* GT  */
  YYSYMBOL_21_ = 21,                       /* '+'  */
  YYSYMBOL_22_ = 22,                       /* '-'  */
  YYSYMBOL_23_ = 23,                       /* '*'  */
  YYSYMBOL_24_ = 24,                       /* '/'  */
  YYSYMBOL_25_ = 25,                       /* '%'  */
  YYSYMBOL_26_ = 26,                       /* ';'  */
  YYSYMBOL_27_ = 27,                       /* '}'  */
  YYSYMBOL_28_ = 28,                       /* '='  */
  YYSYMBOL_29_ = 29,                       /* '('  */
  YYSYMBOL_30_ = 30,                       /* ')'  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_program = 33,                   /* program  */
  YYSYMBOL_stmt_list = 34,                 /* stmt_list  */
  YYSYMBOL_stmt = 35,                      /* stmt  */
  YYSYMBOL_type = 36,                      /* type  */
  YYSYMBOL_declaration = 37,               /* declaration  */
  YYSYMBOL_assignment = 38,                /* assignment  */
  YYSYMBOL_print_stmt = 39,                /* print_stmt  */
  YYSYMBOL_block = 40,                     /* block  */
  YYSYMBOL_if_stmt = 41,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 42,                /* while_stmt  */
  YYSYMBOL_expr = 43,                      /* expr  */
  YYSYMBOL_term = 44,                      /* term  */
  YYSYMBOL_factor = 45,                    /* factor  */
  YYSYMBOL_bool_expr = 46,                 /* bool_expr  */
  YYSYMBOL_relop = 47                      /* relop  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   165

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  107

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   275


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    25,     2,     2,
      29,    30,    23,    21,     2,    22,     2,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    27,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   404,   404,   408,   412,   419,   420,   421,   422,   423,
     424,   426,   431,   439,   440,   444,   450,   456,   464,   470,
     475,   483,   489,   494,   502,   503,   511,   517,   523,   528,
     536,   542,   547,   555,   556,   557,   561,   562,   563,   564,
     568,   569,   570,   571,   575,   576,   577,   578,   579,   583,
     584,   585,   586,   587,   588
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "IF",
  "ELSE", "WHILE", "PRINT", "ID", "Int_num", "Float_num", "AND", "OR",
  "NOT", "LE", "GE", "EQ", "NE", "LT", "GT", "'+'", "'-'", "'*'", "'/'",
  "'%'", "';'", "'}'", "'='", "'('", "')'", "'{'", "$accept", "program",
  "stmt_list", "stmt", "type", "declaration", "assignment", "print_stmt",
  "block", "if_stmt", "while_stmt", "expr", "term", "factor", "bool_expr",
  "relop", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-24)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-26)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      59,   134,   -24,   -24,    15,    18,    21,     8,    71,     7,
      25,   -24,     1,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,    59,    72,    59,    83,   -11,    48,    -2,    95,   138,
      34,   -24,   -24,    19,   -14,   -24,    -3,   -24,   -24,   -24,
      89,    89,   135,    64,   -24,    96,   -24,    55,    98,   -24,
      61,    -6,    99,   -24,    22,   122,    46,   -24,   -24,   -24,
      -6,    59,   -24,   117,   101,   -24,   -24,   -24,   -24,   -24,
     -24,    -6,    -6,    -6,    -6,    -6,    -6,    89,    89,    59,
      59,    59,    81,   119,    93,   -24,   -24,   137,   -24,   -24,
     -24,    64,    64,   124,   -24,   -24,   -24,   -24,   113,   121,
     -24,   -24,   -24,   -24,   -24,    59,   -24
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    13,    14,     0,     0,     0,     0,     0,     0,
       0,     4,     0,     5,     6,     9,    10,     7,     8,    11,
      12,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     3,     0,     0,    29,     0,    43,    41,    42,
       0,     0,     0,    35,    39,     0,    32,     0,     0,    23,
       0,     0,     0,    20,     0,     0,    12,    24,    17,    15,
       0,     0,    46,     0,     0,    51,    52,    53,    54,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,    18,     0,    28,    40,
      48,    33,    34,    47,    36,    37,    38,    44,    45,    26,
      31,    30,    22,    21,    16,     0,    27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -24,   -24,   154,   -10,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -20,    51,    41,   -23,   -24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    42,    43,    44,    45,    73
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    48,    33,    37,    38,    39,    52,    31,    55,    27,
      34,    35,    59,    46,    60,    49,    21,    62,    64,    23,
      32,    63,    25,    51,    53,    -2,     1,    61,     2,     3,
       4,    83,     5,     6,     7,     1,    28,     2,     3,     4,
      87,     5,     6,     7,    22,    58,   -25,    24,    85,    50,
      26,    88,   -25,    93,    97,    98,     8,    37,    38,    39,
       1,    57,     2,     3,     4,     8,     5,     6,     7,    99,
     100,   101,    29,    36,     2,     3,     4,    51,     5,     6,
       7,    37,    38,    39,    47,    80,    40,    74,    75,    76,
       8,    82,    37,    38,    39,   106,    54,    40,    37,    38,
      39,    41,     8,    40,    37,    38,    39,   102,    77,    78,
      77,    78,    41,    77,    78,    94,    95,    96,    41,   103,
      71,    72,    91,    92,    51,    77,    79,   105,    81,    84,
       0,    90,    65,    66,    67,    68,    69,    70,    71,    72,
      71,    72,     0,    71,    72,    71,    72,    89,    86,    89,
      65,    66,    67,    68,    69,    70,    71,    72,    71,    72,
      19,    20,    30,   104,    19,    56
};

static const yytype_int8 yycheck[] =
{
      10,    24,     1,     9,    10,    11,    26,     0,    28,     1,
       9,    21,    26,    23,    28,    26,     1,    40,    41,     1,
      30,    41,     1,    29,    26,     0,     1,    30,     3,     4,
       5,    51,     7,     8,     9,     1,    28,     3,     4,     5,
      60,     7,     8,     9,    29,    26,     0,    29,    26,     1,
      29,    61,     6,    73,    77,    78,    31,     9,    10,    11,
       1,    27,     3,     4,     5,    31,     7,     8,     9,    79,
      80,    81,     1,     1,     3,     4,     5,    29,     7,     8,
       9,     9,    10,    11,     1,    30,    14,    23,    24,    25,
      31,    30,     9,    10,    11,   105,     1,    14,     9,    10,
      11,    29,    31,    14,     9,    10,    11,    26,    12,    13,
      12,    13,    29,    12,    13,    74,    75,    76,    29,    26,
      21,    22,    71,    72,    29,    12,    30,     6,    30,    30,
      -1,    30,    15,    16,    17,    18,    19,    20,    21,    22,
      21,    22,    -1,    21,    22,    21,    22,    30,    26,    30,
      15,    16,    17,    18,    19,    20,    21,    22,    21,    22,
      26,    27,     8,    26,    26,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,     7,     8,     9,    31,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    26,
      27,     1,    29,     1,    29,     1,    29,     1,    28,     1,
      34,     0,    35,     1,     9,    35,     1,     9,    10,    11,
      14,    29,    43,    44,    45,    46,    35,     1,    46,    26,
       1,    29,    43,    26,     1,    43,    27,    27,    26,    26,
      28,    30,    46,    43,    46,    15,    16,    17,    18,    19,
      20,    21,    22,    47,    23,    24,    25,    12,    13,    30,
      30,    30,    30,    43,    30,    26,    26,    43,    35,    30,
      30,    44,    44,    43,    45,    45,    45,    46,    46,    35,
      35,    35,    26,    26,    26,     6,    35
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      35,    35,    35,    36,    36,    37,    37,    37,    38,    38,
      38,    39,    39,    39,    40,    40,    41,    41,    41,    41,
      42,    42,    42,    43,    43,    43,    44,    44,    44,    44,
      45,    45,    45,    45,    46,    46,    46,    46,    46,    47,
      47,    47,    47,    47,    47
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     3,     5,     3,     4,     4,
       3,     5,     5,     3,     3,     3,     5,     7,     5,     3,
       5,     5,     3,     3,     3,     1,     3,     3,     3,     1,
       3,     1,     1,     1,     3,     3,     2,     3,     3,     1,
       1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmt_list  */
#line 404 "parser.y"
              { root = (yyvsp[0].n); }
#line 1644 "y.tab.c"
    break;

  case 3: /* stmt_list: stmt_list stmt  */
#line 408 "parser.y"
                   {
        pop_n(2); push("STMT_LIST");
        (yyval.n) = mknode("STMT_LIST", (yyvsp[-1].n), (yyvsp[0].n), NULL);
    }
#line 1653 "y.tab.c"
    break;

  case 4: /* stmt_list: stmt  */
#line 412 "parser.y"
         {
        pop_n(1); push("STMT_LIST");
        (yyval.n) = (yyvsp[0].n);
    }
#line 1662 "y.tab.c"
    break;

  case 5: /* stmt: declaration  */
#line 419 "parser.y"
                 { (yyval.n) = (yyvsp[0].n); }
#line 1668 "y.tab.c"
    break;

  case 6: /* stmt: assignment  */
#line 420 "parser.y"
                 { (yyval.n) = (yyvsp[0].n); }
#line 1674 "y.tab.c"
    break;

  case 7: /* stmt: if_stmt  */
#line 421 "parser.y"
                 { (yyval.n) = (yyvsp[0].n); }
#line 1680 "y.tab.c"
    break;

  case 8: /* stmt: while_stmt  */
#line 422 "parser.y"
                 { (yyval.n) = (yyvsp[0].n); }
#line 1686 "y.tab.c"
    break;

  case 9: /* stmt: print_stmt  */
#line 423 "parser.y"
                 { (yyval.n) = (yyvsp[0].n); }
#line 1692 "y.tab.c"
    break;

  case 10: /* stmt: block  */
#line 424 "parser.y"
                 { (yyval.n) = (yyvsp[0].n); }
#line 1698 "y.tab.c"
    break;

  case 11: /* stmt: error ';'  */
#line 426 "parser.y"
              {
        fprintf(stderr, "Reason: Ill-formed statement — possibly missing ';' or ')'\n\n");
        (yyval.n) = mknode("ERROR_STMT", NULL, NULL, NULL);
        yyerrok;
    }
#line 1708 "y.tab.c"
    break;

  case 12: /* stmt: error '}'  */
#line 431 "parser.y"
              {
        fprintf(stderr, "Reason: Ill-formed block — possibly missing '{' or extra '}'\n\n");
        (yyval.n) = mknode("ERROR_BLOCK", NULL, NULL, NULL);
        yyerrok;
    }
#line 1718 "y.tab.c"
    break;

  case 13: /* type: INT  */
#line 439 "parser.y"
          { (yyval.n) = mknode("int",   NULL, NULL, NULL); }
#line 1724 "y.tab.c"
    break;

  case 14: /* type: FLOAT  */
#line 440 "parser.y"
          { (yyval.n) = mknode("float", NULL, NULL, NULL); }
#line 1730 "y.tab.c"
    break;

  case 15: /* declaration: type ID ';'  */
#line 444 "parser.y"
                {
        pop_n(3); push("DECL");
        printf("------Line %d: Syntactic Validation [Declaration: %s]\n", yylineno, (yyvsp[-1].sval));
        print_action("reduce declaration");
        (yyval.n) = mknode("Decl", (yyvsp[-2].n), mknode((yyvsp[-1].sval), NULL, NULL, NULL), NULL);
    }
#line 1741 "y.tab.c"
    break;

  case 16: /* declaration: type ID '=' expr ';'  */
#line 450 "parser.y"
                         {
        pop_n(5); push("DECL");
        printf("------Line %d: Syntactic Validation [Decl & Assign: %s]\n", yylineno, (yyvsp[-3].sval));
        print_action("reduce decl-assign");
        (yyval.n) = mknode("Decl=", (yyvsp[-4].n), mknode((yyvsp[-3].sval), NULL, NULL, NULL), (yyvsp[-1].n));
    }
#line 1752 "y.tab.c"
    break;

  case 17: /* declaration: type error ';'  */
#line 456 "parser.y"
                   {
        fprintf(stderr, "Reason: Invalid declaration — expected variable name after type\n\n");
        (yyval.n) = mknode("ERROR_DECL", (yyvsp[-2].n), NULL, NULL);
        yyerrok;
    }
#line 1762 "y.tab.c"
    break;

  case 18: /* assignment: ID '=' expr ';'  */
#line 464 "parser.y"
                    {
        pop_n(4); push("ASSIGN");
        printf("------Line %d: Syntactic Validation [Assignment to %s]\n", yylineno, (yyvsp[-3].sval));
        print_action("reduce assignment");
        (yyval.n) = mknode("=", mknode((yyvsp[-3].sval), NULL, NULL, NULL), (yyvsp[-1].n), NULL);
    }
#line 1773 "y.tab.c"
    break;

  case 19: /* assignment: ID '=' error ';'  */
#line 470 "parser.y"
                     {
        fprintf(stderr, "Reason: Invalid assignment — ill-formed expression\n\n");
        (yyval.n) = mknode("ERROR_ASSIGN", mknode((yyvsp[-3].sval), NULL, NULL, NULL), NULL, NULL);
        yyerrok;
    }
#line 1783 "y.tab.c"
    break;

  case 20: /* assignment: ID error ';'  */
#line 475 "parser.y"
                 {
        fprintf(stderr, "Reason: Invalid assignment — missing '=' after '%s'\n\n", (yyvsp[-2].sval));
        (yyval.n) = mknode("ERROR_ASSIGN", mknode((yyvsp[-2].sval), NULL, NULL, NULL), NULL, NULL);
        yyerrok;
    }
#line 1793 "y.tab.c"
    break;

  case 21: /* print_stmt: PRINT '(' expr ')' ';'  */
#line 483 "parser.y"
                           {
        pop_n(5); push("PRINT");
        printf("-------Line %d: Syntactic Validation [Print Statement]\n", yylineno);
        print_action("reduce print");
        (yyval.n) = mknode("PRINT", (yyvsp[-2].n), NULL, NULL);
    }
#line 1804 "y.tab.c"
    break;

  case 22: /* print_stmt: PRINT '(' error ')' ';'  */
#line 489 "parser.y"
                            {
        fprintf(stderr, "Reason: Invalid print — ill-formed expression\n\n");
        (yyval.n) = mknode("ERROR_PRINT", NULL, NULL, NULL);
        yyerrok;
    }
#line 1814 "y.tab.c"
    break;

  case 23: /* print_stmt: PRINT error ';'  */
#line 494 "parser.y"
                    {
        fprintf(stderr, "Reason: Invalid print — missing '(' / ')'\n\n");
        (yyval.n) = mknode("ERROR_PRINT", NULL, NULL, NULL);
        yyerrok;
    }
#line 1824 "y.tab.c"
    break;

  case 24: /* block: '{' stmt_list '}'  */
#line 502 "parser.y"
                      { (yyval.n) = (yyvsp[-1].n); }
#line 1830 "y.tab.c"
    break;

  case 25: /* block: '{' error '}'  */
#line 503 "parser.y"
                  {
        fprintf(stderr, "Reason: Ill-formed block body\n\n");
        (yyval.n) = mknode("ERROR_BLOCK", NULL, NULL, NULL);
        yyerrok;
    }
#line 1840 "y.tab.c"
    break;

  case 26: /* if_stmt: IF '(' bool_expr ')' stmt  */
#line 511 "parser.y"
                              {
        pop_n(5); push("IF");
        printf("------Line %d: Syntactic Validation [If Block]\n", yylineno);
        print_action("reduce if");
        (yyval.n) = mknode("IF", (yyvsp[-2].n), (yyvsp[0].n), NULL);
    }
#line 1851 "y.tab.c"
    break;

  case 27: /* if_stmt: IF '(' bool_expr ')' stmt ELSE stmt  */
#line 517 "parser.y"
                                        {
        pop_n(7); push("IF-ELSE");
        printf("-----Line %d: Syntactic Validation [If-Else Block]\n", yylineno);
        print_action("reduce if-else");
        (yyval.n) = mknode("IF-ELSE", (yyvsp[-4].n), (yyvsp[-2].n), (yyvsp[0].n));
    }
#line 1862 "y.tab.c"
    break;

  case 28: /* if_stmt: IF '(' error ')' stmt  */
#line 523 "parser.y"
                          {
        fprintf(stderr, "Reason: Invalid if — ill-formed condition\n\n");
        (yyval.n) = mknode("ERROR_IF", NULL, (yyvsp[0].n), NULL);
        yyerrok;
    }
#line 1872 "y.tab.c"
    break;

  case 29: /* if_stmt: IF error stmt  */
#line 528 "parser.y"
                  {
        fprintf(stderr, "Reason: Invalid if — missing '(' / ')'\n\n");
        (yyval.n) = mknode("ERROR_IF", NULL, (yyvsp[0].n), NULL);
        yyerrok;
    }
#line 1882 "y.tab.c"
    break;

  case 30: /* while_stmt: WHILE '(' bool_expr ')' stmt  */
#line 536 "parser.y"
                                 {
        pop_n(5); push("WHILE");
        printf("-----Line %d: Syntactic Validation [While Loop]\n", yylineno);
        print_action("reduce while");
        (yyval.n) = mknode("WHILE", (yyvsp[-2].n), (yyvsp[0].n), NULL);
    }
#line 1893 "y.tab.c"
    break;

  case 31: /* while_stmt: WHILE '(' error ')' stmt  */
#line 542 "parser.y"
                             {
        fprintf(stderr, "Reason: Invalid while — ill-formed condition\n\n");
        (yyval.n) = mknode("ERROR_WHILE", NULL, (yyvsp[0].n), NULL);
        yyerrok;
    }
#line 1903 "y.tab.c"
    break;

  case 32: /* while_stmt: WHILE error stmt  */
#line 547 "parser.y"
                     {
        fprintf(stderr, "Reason: Invalid while — missing '(' / ')'\n\n");
        (yyval.n) = mknode("ERROR_WHILE", NULL, (yyvsp[0].n), NULL);
        yyerrok;
    }
#line 1913 "y.tab.c"
    break;

  case 33: /* expr: expr '+' term  */
#line 555 "parser.y"
                  { pop_n(3); push("expr"); (yyval.n) = mknode("+", (yyvsp[-2].n), (yyvsp[0].n), NULL); }
#line 1919 "y.tab.c"
    break;

  case 34: /* expr: expr '-' term  */
#line 556 "parser.y"
                  { pop_n(3); push("expr"); (yyval.n) = mknode("-", (yyvsp[-2].n), (yyvsp[0].n), NULL); }
#line 1925 "y.tab.c"
    break;

  case 35: /* expr: term  */
#line 557 "parser.y"
                  { pop_n(1); push("expr"); (yyval.n) = (yyvsp[0].n); }
#line 1931 "y.tab.c"
    break;

  case 36: /* term: term '*' factor  */
#line 561 "parser.y"
                    { pop_n(3); push("term"); (yyval.n) = mknode("*",  (yyvsp[-2].n), (yyvsp[0].n), NULL); }
#line 1937 "y.tab.c"
    break;

  case 37: /* term: term '/' factor  */
#line 562 "parser.y"
                    { pop_n(3); push("term"); (yyval.n) = mknode("/",  (yyvsp[-2].n), (yyvsp[0].n), NULL); }
#line 1943 "y.tab.c"
    break;

  case 38: /* term: term '%' factor  */
#line 563 "parser.y"
                    { pop_n(3); push("term"); (yyval.n) = mknode("%",  (yyvsp[-2].n), (yyvsp[0].n), NULL); }
#line 1949 "y.tab.c"
    break;

  case 39: /* term: factor  */
#line 564 "parser.y"
                    { pop_n(1); push("term"); (yyval.n) = (yyvsp[0].n); }
#line 1955 "y.tab.c"
    break;

  case 40: /* factor: '(' expr ')'  */
#line 568 "parser.y"
                  { pop_n(3); push("factor"); (yyval.n) = (yyvsp[-1].n); }
#line 1961 "y.tab.c"
    break;

  case 41: /* factor: Int_num  */
#line 569 "parser.y"
                  { pop_n(1); push("factor"); (yyval.n) = mknode((yyvsp[0].sval), NULL, NULL, NULL); }
#line 1967 "y.tab.c"
    break;

  case 42: /* factor: Float_num  */
#line 570 "parser.y"
                  { pop_n(1); push("factor"); (yyval.n) = mknode((yyvsp[0].sval), NULL, NULL, NULL); }
#line 1973 "y.tab.c"
    break;

  case 43: /* factor: ID  */
#line 571 "parser.y"
                  { pop_n(1); push("factor"); (yyval.n) = mknode((yyvsp[0].sval), NULL, NULL, NULL); }
#line 1979 "y.tab.c"
    break;

  case 44: /* bool_expr: bool_expr AND bool_expr  */
#line 575 "parser.y"
                            { pop_n(3); push("bool"); (yyval.n) = mknode("&&", (yyvsp[-2].n), (yyvsp[0].n), NULL); }
#line 1985 "y.tab.c"
    break;

  case 45: /* bool_expr: bool_expr OR bool_expr  */
#line 576 "parser.y"
                            { pop_n(3); push("bool"); (yyval.n) = mknode("||", (yyvsp[-2].n), (yyvsp[0].n), NULL); }
#line 1991 "y.tab.c"
    break;

  case 46: /* bool_expr: NOT bool_expr  */
#line 577 "parser.y"
                            { pop_n(2); push("bool"); (yyval.n) = mknode("!",  (yyvsp[0].n), NULL, NULL); }
#line 1997 "y.tab.c"
    break;

  case 47: /* bool_expr: expr relop expr  */
#line 578 "parser.y"
                            { pop_n(3); push("bool"); (yyval.n) = mknode("RELOP", (yyvsp[-2].n), (yyvsp[-1].n), (yyvsp[0].n)); }
#line 2003 "y.tab.c"
    break;

  case 48: /* bool_expr: '(' bool_expr ')'  */
#line 579 "parser.y"
                            { pop_n(3); push("bool"); (yyval.n) = (yyvsp[-1].n); }
#line 2009 "y.tab.c"
    break;

  case 49: /* relop: LT  */
#line 583 "parser.y"
       { (yyval.n) = mknode("<",  NULL, NULL, NULL); }
#line 2015 "y.tab.c"
    break;

  case 50: /* relop: GT  */
#line 584 "parser.y"
       { (yyval.n) = mknode(">",  NULL, NULL, NULL); }
#line 2021 "y.tab.c"
    break;

  case 51: /* relop: LE  */
#line 585 "parser.y"
       { (yyval.n) = mknode("<=", NULL, NULL, NULL); }
#line 2027 "y.tab.c"
    break;

  case 52: /* relop: GE  */
#line 586 "parser.y"
       { (yyval.n) = mknode(">=", NULL, NULL, NULL); }
#line 2033 "y.tab.c"
    break;

  case 53: /* relop: EQ  */
#line 587 "parser.y"
       { (yyval.n) = mknode("==", NULL, NULL, NULL); }
#line 2039 "y.tab.c"
    break;

  case 54: /* relop: NE  */
#line 588 "parser.y"
       { (yyval.n) = mknode("!=", NULL, NULL, NULL); }
#line 2045 "y.tab.c"
    break;


#line 2049 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 591 "parser.y"


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
