#include "ccc.h"

char *user_input;
Token *token;

// Reports an error and exit.
void error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

// Reports an error location and exit.
void verror_at(char *loc, char *fmt, va_list ap) {
  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, "");  // print pos spaces.
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

// Reports an error location and exit.
void error_at(char *loc, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  verror_at(loc, fmt, ap);
}

// Reports an error location and exit.
void error_tok(Token *tok, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  if (tok) {
    verror_at(tok->str, fmt, ap);
  }
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

char *strndup(char *p, int len) {
  char *buf = malloc(len + 1);
  strncpy(buf, p, len);
  buf[len] = '\0';
  return buf;
}

// returns true if the current token matches a given string
Token *peek(char *s) {
  if (token->kind != TK_RESERVED || strlen(s) != token->len ||
      memcmp(token->str, s, token->len)) {
    return NULL;
  }
  return token;
}

// Consumes the current token if it matches a given string;
Token *consume(char *s) {
  if (!peek(s)) {
    return NULL;
  }
  Token *t = token;
  token = token->next;
  return t;
}

// Consumes the current token if it is an identifier.
Token *consume_ident() {
  if (token->kind != TK_IDENT) return NULL;
  Token *t = token;
  token = token->next;
  return t;
}

// Ensure that the current token is a given string
void expect(char *s) {
  if (!peek(s)) {
    error_tok(token, "expected \"%s\"", s);
  }
  token = token->next;
}

// Ensure that the current token is TK_NUM.
int expect_number() {
  if (token->kind != TK_NUM) {
    error_tok(token, "expected a number");
  }
  int val = token->val;
  token = token->next;
  return val;
}

// Ensure that the current token is TK_IDENT.
char *expect_ident() {
  if (token->kind != TK_IDENT) {
    error_tok(token, "expected an identifier");
  }
  char *s = strndup(token->str, token->len);
  token = token->next;
  return s;
}

bool at_eof() { return token->kind == TK_EOF; }

// Create a new token and add it as the next token of `cur`.
Token *new_token(TokenKind kind, Token *cur, char *str, int len) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  tok->len = len;
  cur->next = tok;
  return tok;
}
bool startswith(char *p, char *q) { return memcmp(p, q, strlen(q)) == 0; }

bool is_alpha(char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

bool is_alnum(char c) { return is_alpha(c) || ('0' <= c && c <= '9'); }

char *starts_with_reserved(char *p) {
  // Keyword
  static char *kw[] = {"return", "if", "else", "while", "for", "int", "sizeof"};
  for (int i = 0; i < sizeof(kw) / sizeof(*kw); i++) {
    int len = strlen(kw[i]);
    if (startswith(p, kw[i]) && !is_alnum(p[len])) {
      return kw[i];
    }
  }
  // Multi-letter punctuator
  static char *ops[] = {"==", "!=", "<=", ">="};
  for (int i = 0; i < sizeof(ops) / sizeof(*ops); i++)
    if (startswith(p, ops[i])) {
      return ops[i];
    }
  return NULL;
}
// Tokenize `user_input` and returns new tokens.
Token *tokenize() {
  char *p = user_input;
  Token head;
  head.next = NULL;
  Token *cur = &head;
  while (*p) {
    // Skip whitespace characters.
    if (isspace(*p)) {
      p++;
      continue;
    }
    // Keyword or multi-letter punctuator
    char *kw = starts_with_reserved(p);
    if (kw) {
      int len = strlen(kw);
      cur = new_token(TK_RESERVED, cur, p, len);
      p += len;
      continue;
    }
    // Single-letter punctuator
    if (strchr("+-*/()<>;={},&[]", *p)) {
      cur = new_token(TK_RESERVED, cur, p++, 1);
      continue;
    }
    // Identifier
    if (is_alpha(*p)) {
      char *q = p++;
      while (is_alnum(*p)) p++;
      cur = new_token(TK_IDENT, cur, q, p - q);
      continue;
    }
    // Integer literal
    if (isdigit(*p)) {
      cur = new_token(TK_NUM, cur, p, 0);
      char *q = p;
      cur->val = strtol(p, &p, 10);
      cur->len = p - q;
      continue;
    }
    error_at(p, "invalid token");
  }
  new_token(TK_EOF, cur, p, 0);
  return head.next;
}