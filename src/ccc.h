#ifdef __ccc_self__

typedef int bool;
typedef int size_t;
typedef void FILE;
typedef void *va_list;

#define SEEK_SET 0
#define SEEK_END 2

struct _reent {
  int _errno;
  void *_stdin;
  void *_stdout;
  void *_stderr;
};

extern struct _reent *_impure_ptr;

#define stdin (_impure_ptr->_stdin)
#define stderr (_impure_ptr->_stderr)

extern int errno;

#define __attribute__(x)
#define noreturn

#define NULL (0)
#define true (1)
#define false (0)
#define static

#define assert(x) 1

int printf();
int fopen();
int strncmp();
int strlen();
int fprintf();
char *strerror();
int vsnprintf();
int vfprintf();
void *calloc();
int isalnum();
int isspace();
int snprintf();
int strstr();
int strchr();
int isdigit();
int strtol();
void exit();
int fseek();
int ftell();
int fread();
int fclose();
int realloc();
int ferror();
int feof();

#else

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif
typedef struct Type Type;
typedef struct Member Member;
typedef struct Initializer Initializer;
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
  long val;        // If kind is TK_NUM, its value
  char *str;       // Token string
  int len;         // Token length
  char *contents;  // string literal contents including terminating '\0'
  char cont_len;   // string literal length
};
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
void error_tok(Token *tok, char *fmt, ...);
void warn_tok(Token *tok, char *fmt, ...);
Token *peek(char *s);
Token *consume(char *op);
char *strndup(char *p, int len);
Token *consume_ident();
void expect(char *op);
long expect_number();
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
  Token *tok;     // for error message
  bool is_local;  // local or global
  // local variable
  int offset;  // Offset from RBP
  // global variable
  Initializer *initializer;
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
  ND_COMMA,      // ,
  ND_RETURN,     // "return"
  ND_IF,         // "if"
  ND_WHILE,      // "while"
  ND_FOR,        // "for"
  ND_BLOCK,      // { ... }
  ND_BREAK,      // "break"
  ND_CONTINUE,   // "continue"
  ND_GOTO,       // "goto"
  ND_LABEL,      // Labeled statement
  ND_SWITCH,     // "switch"
  ND_CASE,       // "case"
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
  ND_CAST,       // Type cast
  ND_PRE_INC,    // pre ++
  ND_PRE_DEC,    // pre --
  ND_POST_INC,   // post ++
  ND_POST_DEC,   // post --
  ND_A_ADD,      // +=
  ND_A_SUB,      // -=
  ND_A_MUL,      // *=
  ND_A_DIV,      // /=
  ND_A_MOD,      // %=
  ND_NOT,        // !
  ND_BITNOT,     // ~
  ND_BITAND,     // &
  ND_BITOR,      // |
  ND_BITXOR,     // ^
  ND_LOGAND,     // &&
  ND_LOGOR,      // ||
  ND_SHL,        // <<
  ND_SHR,        // >>
  ND_A_SHL,      // <<=
  ND_A_SHR,      // >>=
  ND_TERNARY,    // ? :
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
  // Goto or labeled statement
  char *label_name;
  // switch-cases
  Node *case_next;
  Node *default_case;
  int case_label;
  int case_end_label;
  Var *var;  // Used if kind == ND_VAR
  long val;  // Used if kind == ND_NUM
  // Struct member access
  char *member_name;
  Member *member;
};

// global variable initializer
// global variable can be initialized either by a constant expression or a
// pointer to another global variable
struct Initializer {
  Initializer *next;

  // constant expression
  int sz;
  long val;

  // reference to another global variable
  char *label;
  long addend;
};

typedef struct Function Function;
struct Function {
  Function *next;
  char *name;
  VarList *params;
  bool is_static;
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
typedef enum {
  TY_VOID,
  TY_BOOL,
  TY_CHAR,
  TY_SHORT,
  TY_INT,
  TY_LONG,
  TY_ENUM,
  TY_PTR,
  TY_ARRAY,
  TY_STRUCT,
  TY_FUNC,
} TypeKind;
struct Type {
  TypeKind kind;
  bool is_typedef;     // typedef
  bool is_static;      // static
  bool is_extern;      // extern
  bool is_incomplete;  // incomplete array
  int align;           // alignment
  Type *base;          // pointer or array
  int array_size;      // array
  Member *members;     // struct
  Type *return_ty;     // function
};

// Struct member
struct Member {
  Member *next;
  Type *ty;
  Token *tok;
  char *name;
  int offset;
};
int align_to(int n, int align);
Type *void_type();
Type *bool_type();
Type *char_type();
Type *short_type();
Type *int_type();
Type *long_type();
Type *enum_type();
Type *struct_type();
Type *func_type(Type *return_ty);
Type *pointer_to(Type *base);
Type *array_of(Type *base, int size);
int size_of(Type *ty, Token *tok);
void add_type(Program *prog);

//
// codegen.c
//
void codegen(Program *prog);
