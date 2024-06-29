#include <string.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "hash_table.h"

int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

void test1(void)
{
  CU_ASSERT(true);
}

void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
}

int main()
{
  CU_pSuite test_suite1 = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  test_suite1 = CU_add_suite("Test Suite 1", init_suite, clean_suite);
  if (NULL == test_suite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
    (NULL == CU_add_test(test_suite1, "test 1", test1)) ||
    (NULL == CU_add_test(test_suite1, "Testing creating and destroying", test_create_destroy))
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
