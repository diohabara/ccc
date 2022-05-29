#include "ccc.h"

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
    case ND_EQ:
      iprintf("cmp rax, rdi\n");
      iprintf("sete al\n");
      iprintf("movzb rax, al\n");
      break;
    case ND_NE:
      iprintf("cmp rax, rdi\n");
      iprintf("setne al\n");
      iprintf("movzb rax, al\n");
      break;
    case ND_LT:
      iprintf("cmp rax, rdi\n");
      iprintf("setl al\n");
      iprintf("movzb rax, al\n");
      break;
    case ND_LE:
      iprintf("cmp rax, rdi\n");
      iprintf("setle al\n");
      iprintf("movzb rax, al\n");
      break;
  }
  iprintf("push rax\n");
}

void codegen(Node* node) {
  // initial part of assembly
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  gen(node);

  // there remains a value in the stack top,
  // load it into rax
  iprintf("pop rax\n");
  iprintf("ret\n");
}