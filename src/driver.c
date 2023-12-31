/*
 * Group 22
 * Samay Gandhi 2020A7PS0299P
 * Mohit Makwana 2020A7PS0048P
 * Kathan Patel 2020A7PS0058P
 * Aditya Sheth 2020A7PS1511P
 * Aryan Chavan 2020A7PS1692P
 */

#include "code_gen.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void time_calculate(char *prog_file, char *tree_file) {
  clock_t start_time, end_time;

  double total_CPU_time, total_CPU_time_in_seconds;

  start_time = clock();

  run_parser(prog_file, tree_file);

  end_time = clock();

  total_CPU_time = (double)(end_time - start_time);

  total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;

  printf("Time taken by CPU is %f microseconds (%f seconds)\n", total_CPU_time,
         total_CPU_time_in_seconds);
}

// 1: remove comments: remove_comment(FILE *fp, char string)
// 2: lexer
// 3: parser
// 4: time

int main(int argc, char **argv) {
  if (argc < 4) {
    printf("Run command: ./compiler <testfile> <file_name_to_store_parse_tree> "
           "<buffer_size>");
    exit(0);
  }

  BUFFER_SIZE = atoi(argv[3]);
  Buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);

  printf("Building Grammar (Populating symbols)...\n");
  build_grammar("grammar.txt");
  printf("Generating parse table...\n");
  generate_parse_table();
  parse_table_make();

  while (true) {
    // printf("
    // ______________________________________________________________________________________________________________________________________\n");
    // printf(" |\n");
    printf(
        "  0 : For exit                                                        "
        "                                                                \n");
    printf(
        "  1 : For removal of comments                                         "
        "                                                                \n");
    printf(
        "  2 : For printing the token list (on the console) generated by the "
        "lexer                                                             \n");
    printf("  3 : For parsing to verify the syntactic correctness of the input "
           "source code and printing the parse tree appropriately              "
           "\n");
    printf(
        "  4 : For printing (on the console) the total time taken by our stage "
        "1 code of lexer and parser to verify the syntactic correctness   \n");
    // printf("|______________________________________________________________________________________________________________________________________|\n\n");
    printf("Your input: ");

    int x = 0;
    scanf("%d", &x);

    FILE *fp = fopen(argv[1], "r");

    switch (x) {
    case 0: {
      free(grammar);
      free(parser_table);
      printf("Thank you. Have a Good day ahead!\n");
      return 0;
    }
    case 1: {
      removeComments(fp);
      break;
    }
    case 2: {
      test_lexer_run(argv[1]);
      break;
    }
    case 3: {
      run_parser(argv[1], argv[2]);
      break;
    }
    case 4: {
      time_calculate(argv[1], argv[2]);
      break;
    }
    case 5: {
      create_scopes(argv[1], argv[2]);
      run_ast(argv[1], argv[2]);
      break;
    }
    case 6: {
      create_scopes(argv[1], argv[2]);
      // SYMBOL_TABLE_ELEMENT* ele1 =
      // create_symbol_table_element("hey",false,iNTEGER,0,0,3456,7);
      // SYMBOL_TABLE_ELEMENT* ele2 =
      // create_symbol_table_element("heyo",false,iNTEGER,0,0,456,6);
      // insert_symbol_table(ele1,find_scope(GLOBAL_SCOPE,ele1->declare_lineno)->table);
      // insert_symbol_table(ele2,find_scope(GLOBAL_SCOPE,ele2->declare_lineno)->table);

      // // SYMBOL_TABLE_ELEMENT* test =
      // search_symbol_table("hey",find_scope(GLOBAL_SCOPE,ele1->declare_lineno)->table);
      // // printf("id: %s\n offset: %d",test->id,test->offset);
      // print_symbol_table(find_scope(GLOBAL_SCOPE,ele1->declare_lineno)->table);
      // break;
    }

    case 7: {
      run_code_gen(argv[1], argv[2]);
      break;
    }
    default:
      printf("Wrong input\n");
      break;
    }
  }
}
