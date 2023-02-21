// CUNIT IMPORTS
#include "stdbool.h"
#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
// @TODO: Add concerned file imports ---------------------------------------------------
#include "eg.c"

// @TODO: Add unit tests below ---------------------------------------------------
void test_sorting_1(void){
    int arr[] = {12, 3, 45, 56, 0};
    int cor[] = {0, 3, 12, 45, 56};
    selectionSort(arr, 5);
    CU_ASSERT_EQUAL(0, memcmp(arr, cor, 5));
}
void test_sorting_2(void){
    int arr[] = {3, 56, 0};
    int cor[] = {0, 3, 56};
    selectionSort(arr, 3);
    for(int i = 0; i < 3; i += 1){
        CU_ASSERT_EQUAL(arr[i], cor[i]);
    }
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
   if ((NULL == CU_add_test(pSuite, "Sorting_Test 1", test_sorting_1)) 
        || (NULL == CU_add_test(pSuite, "Sorting_Test 2", test_sorting_2)))
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
   CU_automated_run_tests();
   CU_list_tests_to_file();

    // MANUAL TESTING
   /* Run all tests using the console interface */
   /* CU_console_run_tests(); */

    // ROUTINE
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
    //--------------------------------------------------- @NOTE: Ignore above configs ---------------------------------------------------
}
