#include "ccc.h"

char* user_input;
Token* token;

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

// print with an indent
void iprintf(char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  printf("\t");
  vfprintf(stdout, fmt, ap);
}

// if the next token is an expected symbol, read through to the next token
// return true if so. otherwise, return false
bool consume(char* op) {
  if (token->kind != TK_RESERVED || strlen(op) != token->len ||
      memcmp(token->str, op, token->len)) {
    return false;
  }
  token = token->next;
  return true;
}

// if the next token is an expected symbol, read through to the next token
// return true if so. otherwise, return false
void expect(char* op) {
  if (token->kind != TK_RESERVED || strlen(op) != token->len ||
      memcmp(token->str, op, token->len)) {
    error_at(token->str, "expected \"%s\"", op);
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
Token* new_token(TokenKind kind, Token* cur, char* str, int len) {
  Token* tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  tok->len = len;
  cur->next = tok;
  return tok;
}

Token* consume_ident() {
  if (token->kind != TK_IDENT) {
    return NULL;
  }
  Token* t = token;
  token = token->next;
  return t;
}

bool startswith(char* p, char* q) { return memcmp(p, q, strlen(q)) == 0; }

// tokenize input `user_input` and return new tokens
Token* tokenize(char* p) {
  Token head;
  head.next = NULL;
  Token* cur = &head;
  while (*p) {
    if (isspace(*p)) {
      p++;
      continue;
    }
    // multi-char punctuator
    if (startswith(p, "==") || startswith(p, "!=") || startswith(p, ">=") ||
        startswith(p, "<=")) {
      cur = new_token(TK_RESERVED, cur, p, 2);
      p += 2;
      continue;
    }
    // single-char punctuator
    if (strchr("+-*/()<>;=", *p)) {
      cur = new_token(TK_RESERVED, cur, p++, 1);
      continue;
    }
    if ('a' <= *p && *p <= 'z') {
      cur = new_token(TK_IDENT, cur, p++, 1);
      continue;
    }
    if (isdigit(*p)) {
      cur = new_token(TK_NUM, cur, p, 0);
      char* q = p;
      cur->val = strtol(p, &p, 10);
      cur->len = p - q;
      continue;
    }
    error("There is no tokenizing");
  }
  new_token(TK_EOF, cur, p, 0);
  return head.next;
}
