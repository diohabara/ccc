#include "ccc.h"

int labelseq = 0;

void gen_lval(Node* node) {
  if (node->kind != ND_LVAR) {
    error("The left-hand side value of the assignment is not a variable");
  }
  iprintf("mov rax, rbp\n");
  iprintf("sub rax, %d\n", node->offset);
  iprintf("push rax\n");
}

void load() {
  iprintf("pop rax\n");
  iprintf("mov rax, [rax]\n");
  iprintf("push rax\n");
}

void store() {
  iprintf("pop rdi\n");
  iprintf("pop rax\n");
  iprintf("mov [rax], rdi\n");
  iprintf("push rdi\n");
}

void gen(Node* node) {
  switch (node->kind) {
    case ND_NUM:
      iprintf("push %d\n", node->val);
      return;
    case ND_LVAR:
      gen_lval(node);
      load();
      return;
    case ND_ASSIGN:
      gen_lval(node->lhs);
      gen(node->rhs);
      store();
      return;
    case ND_IF:
      labelseq++;
      if (node->els) {
        gen(node->cond);
        iprintf("pop rax\n");
        iprintf("cmp rax, 0\n");
        iprintf("je .Lelse%d\n", labelseq);
        gen(node->then);
        iprintf("jmp .Lend%d\n", labelseq);
        printf(".Lelse%d:\n", labelseq);
        gen(node->els);
        printf(".Lend%d:\n", labelseq);
      } else {
        gen(node->cond);
        iprintf("pop rax\n");
        iprintf("cmp rax, 0\n");
        iprintf("je .Lend%d\n", labelseq);
        gen(node->then);
        printf(".Lend%d:\n", labelseq);
      }
      return;
    case ND_WHILE:
      labelseq++;
      printf(".Lbegin%d:\n", labelseq);
      gen(node->cond);
      iprintf("pop rax\n");
      iprintf("cmp rax, 0\n");
      iprintf("je  .Lend%d\n", labelseq);
      gen(node->then);
      iprintf("jmp .Lbegin%d\n", labelseq);
      printf(".Lend%d:\n", labelseq);
      return;
    case ND_FOR:
      labelseq++;
      if (node->init) {
        gen(node->init);
      }
      printf(".Lbegin%d:\n", labelseq);
      if (node->cond) {
        gen(node->cond);
        iprintf("pop rax\n");
        iprintf("cmp rax, 0\n");
        iprintf("je .Lend%d\n", labelseq);
      }
      gen(node->then);
      if (node->inc) {
        gen(node->inc);
      }
      iprintf("jmp .Lbegin%d\n", labelseq);
      printf(".Lend%d:\n", labelseq);
      return;
    case ND_RETURN:
      gen(node->lhs);
      iprintf("pop rax\n");
      iprintf("mov rsp, rbp\n");
      iprintf("pop rbp\n");
      iprintf("ret\n");
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

  // prologue
  // allocate space for 26 variables
  iprintf("push rbp\n");
  iprintf("mov rbp, rsp\n");
  iprintf("sub rsp, 208\n");

  // code generation from the first statement
  for (Node* n = node; n; n = n->next) {
    gen(n);

    // there remains 1 value in the stack as result of expressions
    // so, pop it so as not to overflow stack
    iprintf("pop rax\n");
  }

  // epilogue
  // the result of the last expression remains in RAX, so return it
  iprintf("mov rsp, rbp\n");
  iprintf("pop rbp\n");
  iprintf("ret\n");
}