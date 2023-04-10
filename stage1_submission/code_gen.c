#include "inter_code_gen.c"
#include <stdio.h>

char *temp_to_reg(char *temp) {
  if (compare(temp, "t0") == 0)
    return "RAX";
  else if (compare(temp, "t1") == 0)
    return "RBX";
  else if (compare(temp, "t2") == 0)
    return "RCX";
  else if (compare(temp, "t3") == 0)
    return "RDX";
  else if (compare(temp, "t4") == 0)
    return "RSI";
  else if (compare(temp, "t5") == 0)
    return "RDI";
  else if (compare(temp, "t6") == 0)
    return "R8";
  else if (compare(temp, "t7") == 0)
    return "R9";
  else if (compare(temp, "t8") == 0)
    return "R10";
  else if (compare(temp, "t9") == 0)
    return "R11";
  else if (compare(temp, "t10") == 0)
    return "R12";
  else if (compare(temp, "t11") == 0)
    return "R13";
  else if (compare(temp, "t12") == 0)
    return "R14";
  else if (compare(temp, "t13") == 0)
    return "R15";
  return "REGISTERS FINISHED";
}

void generate_assembly(Quadruple *quadruple) {
  FILE *fp = fopen("code.asm", "w+");

  fprintf(fp, "%sifidn __OUTPUT_FORMAT__,elf64\n", "%");
  fprintf(fp, "section .note.GNU-stack noalloc noexec nowrite progbits\n");
  fprintf(fp, "%sendif\n", "%");
  fprintf(fp, "\nsys_exit equ 60");
  fprintf(fp, "\n\tdefault rel\n");
  fprintf(fp, "\tglobal _start\n");
  fprintf(fp, "\nsection .text\n");
  fprintf(fp, "_start:\n");
  fprintf(fp, "mov rax, 1\n");
  fprintf(fp, "mov rax, sys_exit\n\n");
  fprintf(fp, "syscall\n");

  QuadNode *node = quadruple->head;

  while (node != NULL) {

    switch (node->op) {

    case PLUS:
    case SUB:
    case MUL:
    case DIV:
    case GE:
    case GT:
    case LE:
    case LT:
    case EQ:
    case NE:
    case AND:
    case OR:
    case UPLUS:
    case UMINUS:
    case LABEL:
    case GET_VALUE:
    case PRINT:
    case ASSIGN:
    case GOTO_UNCOND:
    case IF_TRUE_GOTO:
    case INP_PARAM:
    case OUTP_PARAM:
    case ACTUAL_PARAM:
    case RETURN_PARAM:
    case FUNC_CALL:
    case INDEXED_COPY:
    case ARRAY_ACCESS:
    case DECLARE_DYN_ARR:
    case DECLARE_STATIC_ARR:
    case RETURN:
    case FN_DEFN:
    case EXIT_PROGRAM_IF_TRUE:
      break;
    }

    node = node->next;
  }

  fclose(fp);
}

void run_code_gen(char *prog_file, char *out_file) {
  Quadruple *quadruple = run_inter_code_gen(prog_file, out_file);

  generate_assembly(quadruple);
}
