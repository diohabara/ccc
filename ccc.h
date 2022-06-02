#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// tokenize.c
//
typedef enum {
  TK_RESERVED,  // symbol
  TK_IDENT,     // indentifier
  TK_NUM,       // integer
  TK_EOF,       // end of line
} TokenKind;
typedef struct Token Token;
struct Token {
  TokenKind kind;
  Token* next;
  int val;    // value if it's integer token
  char* str;  // token string
  int len;    // the length of a token
};
typedef struct LVar LVar;
// local variable
struct LVar {
  LVar* next;  // next variable or NULL
  char* name;  // variable's name
  int len;     // length of the name
  int offset;  // offset from RBP
};
extern char* user_input;  // input program
extern Token* token;      // token currently focused on
void error_at(char*, char* fmt, ...);
void error(char* fmt, ...);
void iprintf(char*, ...);
bool consume(char* op);
void expect(char* op);
int expect_number();
bool at_eof();
Token* new_token(TokenKind, Token*, char*, int);
Token* consume_ident();
bool startswith(char*, char*);
Token* tokenize(char*);

//
// parse.c
//
typedef enum {
  ND_ADD,     // +
  ND_SUB,     // -
  ND_MUL,     // *
  ND_DIV,     // /
  ND_NUM,     // integer
  ND_EQ,      // ==
  ND_NE,      // !=
  ND_LT,      // <
  ND_LE,      // <=
  ND_ASSIGN,  // =
  ND_LVAR,    // local variable
} NodeKind;
typedef struct Node Node;
// AST node's types
struct Node {
  NodeKind kind;
  Node* next;
  Node* lhs;
  Node* rhs;
  int val;     // used in the case of ND_NUM
  int offset;  // used in the case of ND_LVAR
};
extern LVar* locals;  // local variables
LVar* find_lvar(Token*);
Node* new_node(NodeKind, Node*, Node*);
Node* new_node_num(int);
Node* program();
Node* stmt();
Node* expr();
Node* assign();
Node* equality();
Node* relational();
Node* add();
Node* mul();
Node* unary();
Node* primary();

//
// codegen.c
//
void gen_lval(Node*);
void load();
void store();
void gen(Node*);
void codegen(Node*);
