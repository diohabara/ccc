#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  TK_RESERVED,  // symbol
  TK_NUM,       // integer
  TK_EOF,       // end of line
} TokenKind;

typedef struct Token Token;

struct Token {
  TokenKind kind;
  Token* next;
  int val;    // value if it's integer token
  char* str;  // token string
};

// currently focused on token
Token* token;
// input program
char* user_input;

// report where an error happens
void error_at(char* loc, char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, " ");  // output `pos` blanks
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

// report errors
void error(char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

// print with indents
void iprintf(char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  printf("\t");
  vfprintf(stdout, fmt, ap);
}

// tokenizer

// if the next token is an expected symbol, read through to the next token
// return true if so. otherwise, return false
bool consume(char op) {
  if (token->kind != TK_RESERVED || token->str[0] != op) {
    return false;
  }
  token = token->next;
  return true;
}

// if the next token is an expected symbol, read through to the next token
// return true if so. otherwise, return false
void expect(char op) {
  if (token->kind != TK_RESERVED || token->str[0] != op) {
    error("Token is not '%c'", op);
  }
  token = token->next;
}

// if the next token is an expected integer, read through to the next token
// return true if so. otherwise, return false
int expect_number() {
  if (token->kind != TK_NUM) {
    error("not a number");
  }
  int val = token->val;
  token = token->next;
  return val;
}

bool at_eof() { return token->kind == TK_EOF; }

// create another token and connect it to `cur`
Token* new_token(TokenKind kind, Token* cur, char* str) {
  Token* tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  cur->next = tok;
  return tok;
}

// tokenize input `p`
Token* tokenize(char* p) {
  Token head;
  head.next = NULL;
  Token* cur = &head;
  while (*p) {
    if (isspace(*p)) {
      p++;
      continue;
    }
    if (strchr("+-*/()", *p)) {
      cur = new_token(TK_RESERVED, cur, p++);
      continue;
    }
    if (isdigit(*p)) {
      cur = new_token(TK_NUM, cur, p);
      cur->val = strtol(p, &p, 10);
      continue;
    }
    error("There is no tokenizing");
  }
  new_token(TK_EOF, cur, p);
  return head.next;
}

// parser

typedef enum {
  ND_ADD,  // +
  ND_SUB,  // -
  ND_MUL,  // *
  ND_DIV,  // /
  ND_NUM,  // integer
} NodeKind;

typedef struct Node Node;

// AST node's types
struct Node {
  NodeKind kind;
  Node* lhs;
  Node* rhs;
  int val;  // used when it's an integer
};
// function declarations
Node* expr();
Node* mul();
Node* primary();

Node* new_node(NodeKind kind, Node* lhs, Node* rhs) {
  Node* node = calloc(1, sizeof(Node));
  node->kind = kind;
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node* new_node_num(int val) {
  Node* node = calloc(1, sizeof(Node));
  node->kind = ND_NUM;
  node->val = val;
  return node;
}

// expr = mul ("+" mul | "-" mul)*
Node* expr() {
  Node* node = mul();

  for (;;) {
    if (consume('+')) {
      node = new_node(ND_ADD, node, mul());
    } else if (consume('-')) {
      node = new_node(ND_SUB, node, mul());
    } else {
      return node;
    }
  }
}

// mul = primary ("*" primary | "/" priamry)*
Node* mul() {
  Node* node = primary();

  for (;;) {
    if (consume('*')) {
      node = new_node(ND_MUL, node, primary());
    } else if (consume('/')) {
      node = new_node(ND_DIV, node, primary());
    } else {
      return node;
    }
  }
}

// primary = "(" expr ")" | num
Node* primary() {
  if (consume('(')) {
    Node* node = expr();
    expect(')');
    return node;
  }
  return new_node_num(expect_number());
}

// code generator

void gen(Node* node) {
  if (node->kind == ND_NUM) {
    iprintf("push %d\n", node->val);
    return;
  }
  gen(node->lhs);
  gen(node->rhs);

  iprintf("pop rdi\n");
  iprintf("pop rax\n");

  switch (node->kind) {
    case ND_ADD:
      iprintf("add rax, rdi\n");
      break;
    case ND_SUB:
      iprintf("sub rax, rdi\n");
      break;
    case ND_MUL:
      iprintf("imul rax, rdi\n");
      break;
    case ND_DIV:
      iprintf("cqo\n");
      iprintf("idiv rdi\n");
      break;
  }
  iprintf("push rax\n");
}

int main(int argc, char** argv) {
  if (argc != 2) {
    error("%s: invalid number of arguments", argv[0]);
  }

  // tokenize and parse
  user_input = argv[1];
  token = tokenize(user_input);
  Node* node = expr();

  // initial part of assembly
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // code genaration
  gen(node);

  // there remains a value in the stack top,
  // load it into rax
  iprintf("pop rax\n");
  iprintf("ret\n");
  return 0;
}