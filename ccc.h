#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Type Type;
typedef struct Member Member;
//
// tokenize.c
//
// Token
typedef enum {
  TK_RESERVED,  // Keywords or punctuators
  TK_IDENT,     // Identifiers
  TK_STR,       // string literals
  TK_NUM,       // Integer literals
  TK_EOF,       // End-of-file markers
} TokenKind;
// Token type
typedef struct Token Token;
struct Token {
  TokenKind kind;  // Token kind
  Token *next;     // Next token
  int val;         // If kind is TK_NUM, its value
  char *str;       // Token string
  int len;         // Token length
  char *contents;  // string literal contents including terminating '\0'
  char cont_len;   // string literal length
};
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
void error_tok(Token *tok, char *fmt, ...);
Token *peek(char *s);
Token *consume(char *op);
char *strndup(char *p, int len);
Token *consume_ident();
void expect(char *op);
int expect_number();
char *expect_ident();
bool at_eof();
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
Token *tokenize();
extern char *filename;
extern char *user_input;
extern Token *token;
//
// parse.c
//
// Variable
typedef struct Var Var;
struct Var {
  char *name;     // Variable name
  Type *ty;       // Type
  bool is_local;  // local or global
  // local variable
  int offset;  // Offset from RBP
  // global variable
  char *contents;
  int cont_len;
};
typedef struct VarList VarList;
struct VarList {
  VarList *next;
  Var *var;
};

// AST node
typedef enum {
  ND_ADD,        // +
  ND_SUB,        // -
  ND_MUL,        // *
  ND_DIV,        // /
  ND_EQ,         // ==
  ND_NE,         // !=
  ND_LT,         // <
  ND_LE,         // <=
  ND_ASSIGN,     // =
  ND_RETURN,     // "return"
  ND_IF,         // "if"
  ND_WHILE,      // "while"
  ND_FOR,        // "for"
  ND_BLOCK,      // { ... }
  ND_FUNCALL,    // Function call
  ND_EXPR_STMT,  // Expression statement
  ND_STMT_EXPR,  // statement expression
  ND_VAR,        // Variable
  ND_NUM,        // Integer
  ND_ADDR,       // unary &
  ND_DEREF,      // unary *
  ND_NULL,       // empty statement
  ND_SIZEOF,     // "sizeof"
  ND_MEMBER,     // . (struct member access)
} NodeKind;
// AST node type
typedef struct Node Node;
struct Node {
  NodeKind kind;  // Node kind
  Node *next;     // Next node
  Type *ty;       // Type, e.g., int or pointer to int
  Token *tok;     // representative token
  Node *lhs;      // Left-hand side
  Node *rhs;      // Right-hand side
  // "if, "while" or "for" statement
  Node *cond;
  Node *then;
  Node *els;
  Node *init;
  Node *inc;
  // Block or statement expression
  Node *body;
  // Function call
  char *funcname;
  Node *args;
  Var *var;  // Used if kind == ND_VAR
  int val;   // Used if kind == ND_NUM
  // Struct member access
  char *member_name;
  Member *member;
};

typedef struct Function Function;
struct Function {
  Function *next;
  char *name;
  VarList *params;
  Node *node;
  VarList *locals;
  int stack_size;
};

typedef struct {
  VarList *globals;
  Function *fns;
} Program;
Program *program();

//
// type.c
//
typedef enum { TY_CHAR, TY_INT, TY_PTR, TY_ARRAY, TY_STRUCT } TypeKind;
struct Type {
  TypeKind kind;
  Type *base;       // pointer or array
  int array_size;   // array
  Member *members;  // struct
};

// Struct member
struct Member {
  Member *next;
  Type *ty;
  char *name;
  int offset;
};
Type *char_type();
Type *int_type();
Type *pointer_to(Type *base);
Type *array_of(Type *base, int size);
int size_of(Type *ty);
void add_type(Program *prog);

//
// codegen.c
//
void codegen(Program *prog);