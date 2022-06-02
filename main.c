#include "ccc.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    error("%s: invalid number of arguments", argv[0]);
  }

  // tokenize and parse
  user_input = argv[1];
  token = tokenize(user_input);
  locals = calloc(1, sizeof(LVar));
  Node* node = program();

  codegen(node);
  return 0;
}