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
void error_at(char* loc, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, " "); // output `pos` blanks
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
void dprintf(int depth, char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  for (int i = 0; i < depth; i++) {
    printf("\t");
  }
  vfprintf(stdout, fmt, ap);
}

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
    if (*p == '+' || *p == '-') {
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

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "The number of input arguments is not correct.\n");
    return 1;
  }
  token = tokenize(argv[1]);

  // initial part of assembly
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // the first element of an expression must be number
  dprintf(1, "mov rax, %d\n", expect_number());

  // consume `+`, `-`, or `number` and output assembly
  while (!at_eof()) {
    if (consume('+')) {
      dprintf(1, "add rax, %d\n", expect_number());
      continue;
    }

    expect('-');
    dprintf(1, "sub rax, %d\n", expect_number());
  }
  dprintf(1, "ret\n");
  return 0;
}