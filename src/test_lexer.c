// CUNIT IMPORTS
#include "stdbool.h"
#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
// @TODO: Add concerned file imports ---------------------------------------------------
#include "lexer.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// @TODO: Add unit tests below ---------------------------------------------------
int helper_compare_files(FILE *file1, FILE *file2, int verbose){
   char ch1 = getc(file1);
   char ch2 = getc(file2);
   int error = 0, pos = 0, line = 1;
   while (ch1 != EOF && ch2 != EOF){
      pos++;
      if (ch1 == ' ' && ch2 == ' '){
         line++;
         pos = 0;
      }
      if (ch1 != ch2){
         error++;
         if (verbose == 1) printf("Line Number : %d \tError" " Position : %d ", line, pos);
      }
      ch1 = getc(file1);
      ch2 = getc(file2);
   }
    return error;
}

int helper_lexer_comments_remover(char* test_file, char* correct_uncommented_file) {
    FILE* f = fopen(test_file, "r");
    char* uncommented_file = "test_uncommented.txt";
    remove_comments(f, uncommented_file);
    FILE* file = fopen(uncommented_file, "r");
    FILE* correct_file = fopen(correct_uncommented_file, "r");
    int errors = helper_compare_files(file, correct_file, 0);
    fclose(f);
    fclose(file);
    fclose(correct_file);
    return errors;
}

void test_lexer_comments_remover(){
    char* test_file_1 = "../tests/test_lexer_1.txt";
    char* correct_uncommented_file_1 = "../tests/test_lexer_1.txt.uncommented.txt";
    int results_1 = helper_lexer_comments_remover(test_file_1, correct_uncommented_file_1);

    char* test_file_2 = "../tests/test_lexer_2.txt";
    char* correct_uncommented_file_2 = "../tests/test_lexer_2.txt.uncommented.txt";
    int results_2 = helper_lexer_comments_remover(test_file_2, correct_uncommented_file_2);

    char* test_file_3 = "../tests/test_lexer_3.txt";
    char* correct_uncommented_file_3 = "../tests/test_lexer_3.txt.uncommented.txt";
    int results_3 = helper_lexer_comments_remover(test_file_3, correct_uncommented_file_3);

    char* test_file_4 = "../tests/test_lexer_4.txt";
    char* correct_uncommented_file_4 = "../tests/test_lexer_4.txt.uncommented.txt";
    int results_4 = helper_lexer_comments_remover(test_file_4, correct_uncommented_file_4);

    char* test_file_5 = "../tests/test_lexer_5.txt";
    char* correct_uncommented_file_5 = "../tests/test_lexer_5.txt.uncommented.txt";
    int results_5 = helper_lexer_comments_remover(test_file_5, correct_uncommented_file_5);

    char* test_file_6 = "../tests/test_lexer_6.txt";
    char* correct_uncommented_file_6 = "../tests/test_lexer_6.txt.uncommented.txt";
    int results_6 = helper_lexer_comments_remover(test_file_6, correct_uncommented_file_6);

    char* test_file_7 = "../tests/test_lexer_7.txt";
    char* correct_uncommented_file_7 = "../tests/test_lexer_7.txt.uncommented.txt";
    int results_7 = helper_lexer_comments_remover(test_file_7, correct_uncommented_file_7);

    CU_ASSERT_EQUAL(results_1, 0);
    CU_ASSERT_EQUAL(results_2, 0);
    CU_ASSERT_EQUAL(results_3, 0);
    CU_ASSERT_EQUAL(results_4, 0);
    CU_ASSERT_EQUAL(results_5, 0);
    CU_ASSERT_EQUAL(results_6, 0);
    CU_ASSERT_EQUAL(results_7, 0);
}

int helper_lexer_tokenizer(char* test_file, char* correct_tokenized_file) {
    char* tokenized_file = "test_tokenized.txt";
    int tokenized = test_lexer_run(test_file, tokenized_file);
    CU_ASSERT_EQUAL(tokenized, 1); // Lexer should have completed run successfully
    FILE* tokenized_fp = fopen(tokenized_file, "r");
    FILE* correct_tokenized_fp = fopen(correct_tokenized_file, "r");
    int errors = helper_compare_files(tokenized_fp, correct_tokenized_fp, 0);
    fclose(tokenized_fp);
    fclose(correct_tokenized_fp);
    return errors;    
}

void test_lexer_tokenizer() {
    char* test_file_1 = "../tests/test_lexer_1.txt.uncommented.txt";
    char* correct_tokenized_file_1 = "../tests/test_lexer_1.txt.tokenized.txt";
    int results_1 = helper_lexer_tokenizer(test_file_1, correct_tokenized_file_1);

    char* test_file_2 = "../tests/test_lexer_2.txt.uncommented.txt";
    char* correct_tokenized_file_2 = "../tests/test_lexer_2.txt.tokenized.txt";
    int results_2 = helper_lexer_tokenizer(test_file_2, correct_tokenized_file_2);
    
    char* test_file_3 = "../tests/test_lexer_3.txt.uncommented.txt";
    char* correct_tokenized_file_3 = "../tests/test_lexer_3.txt.tokenized.txt";
    int results_3 = helper_lexer_tokenizer(test_file_3, correct_tokenized_file_3);
    
    char* test_file_4 = "../tests/test_lexer_4.txt.uncommented.txt";
    char* correct_tokenized_file_4 = "../tests/test_lexer_4.txt.tokenized.txt";
    int results_4 = helper_lexer_tokenizer(test_file_4, correct_tokenized_file_4);
    
    char* test_file_5 = "../tests/test_lexer_5.txt.uncommented.txt";
    char* correct_tokenized_file_5 = "../tests/test_lexer_5.txt.tokenized.txt";
    int results_5 = helper_lexer_tokenizer(test_file_5, correct_tokenized_file_5);
    
    char* test_file_6 = "../tests/test_lexer_6.txt.uncommented.txt";
    char* correct_tokenized_file_6 = "../tests/test_lexer_6.txt.tokenized.txt";
    int results_6 = helper_lexer_tokenizer(test_file_6, correct_tokenized_file_6);
    
    char* test_file_7 = "../tests/test_lexer_7.txt.uncommented.txt";
    char* correct_tokenized_file_7 = "../tests/test_lexer_7.txt.tokenized.txt";
    int results_7 = helper_lexer_tokenizer(test_file_7, correct_tokenized_file_7);
    
    CU_ASSERT_EQUAL(results_1, 0);
    CU_ASSERT_EQUAL(results_2, 0);
    CU_ASSERT_EQUAL(results_3, 0);
    CU_ASSERT_EQUAL(results_4, 0);
    CU_ASSERT_EQUAL(results_5, 0);
    CU_ASSERT_EQUAL(results_6, 0);
    CU_ASSERT_EQUAL(results_7, 0);
}
// @TODO: Add unit tests above ---------------------------------------------------

int main(){
    //--------------------------------------------------- @NOTE: Ignore below configs ---------------------------------------------------
   CU_pSuite pSuite = NULL;
   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_success", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
    //--------------------------------------------------- @NOTE: Ignore above configs ---------------------------------------------------

    // @TODO: Add tests to suite below ---------------------------------------------------
   if ((NULL == CU_add_test(pSuite, "Lexer Test - Removing Comments", test_lexer_comments_remover))
        || (NULL == CU_add_test(pSuite, "Lexer Test - Tokenizing lexemes", test_lexer_tokenizer))
    )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }
    // @TODO: Add tests to suite above ---------------------------------------------------


    //--------------------------------------------------- @NOTE: Ignore below configs ---------------------------------------------------
    // NORMAL RUN, PRINT RESULTS TO CONSOLE
   /* Run all tests using the basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n--------------------------------------------------- FAILED TESTS --------------------------------------------------- \n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");

    // AUTO RUN AND SAVE RESULTS IN XML
   /* Run all tests using the automated interface */
   /* CU_automated_run_tests(); */
   /* CU_list_tests_to_file(); */

    // MANUAL TESTING
   /* Run all tests using the console interface */
   /* CU_console_run_tests(); */

    // ROUTINE
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
    //--------------------------------------------------- @NOTE: Ignore above configs ---------------------------------------------------
}
