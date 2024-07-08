#include <string.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "hash_table.h"
#include <stdlib.h>

int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

void test1_create_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_PTR_NOT_NULL(ht);

  ioopm_hash_table_destroy(ht);
}

void test2_insert_fresh()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char **result1 = ioopm_hash_table_lookup(ht, 1);
  CU_ASSERT_PTR_NULL(result1);

  char *val = "one";
  ioopm_hash_table_insert(ht, 1, "one");
  char **result2 = ioopm_hash_table_lookup(ht, 1);
  CU_ASSERT_PTR_NOT_NULL(result2);
  CU_ASSERT_STRING_EQUAL(val, *result2);

  ioopm_hash_table_destroy(ht);
}

void test3_insert_existing()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int key = 1;
  char *val = "one";
  ioopm_hash_table_insert(ht, key, val);

  char **result1 = ioopm_hash_table_lookup(ht, 1);
  CU_ASSERT_PTR_NOT_NULL(result1);
  CU_ASSERT_STRING_EQUAL(val, *result1);

  int new_key = 1;
  char *new_val = "tasty one test";
  ioopm_hash_table_insert(ht, new_key, new_val);

  char **result2 = ioopm_hash_table_lookup(ht, 1);
  CU_ASSERT_PTR_NOT_NULL(result2);
  CU_ASSERT_STRING_EQUAL(new_val, *result2);

  ioopm_hash_table_destroy(ht);
}

void test4_lookup()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int key = 1;
  char *val = "one";
  char **result1 = ioopm_hash_table_lookup(ht, key);
  CU_ASSERT_PTR_NULL(result1);

  ioopm_hash_table_insert(ht, key, val);
  char **result2 = ioopm_hash_table_lookup(ht, key);
  CU_ASSERT_PTR_NOT_NULL(result2);
  CU_ASSERT_STRING_EQUAL(*result2, val);

  ioopm_hash_table_destroy(ht);
}

void test5_remove()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int key = 1;
  char *val = "one";
  ioopm_hash_table_insert(ht, key, val);
  char **result2 = ioopm_hash_table_lookup(ht, key);
  CU_ASSERT_PTR_NOT_NULL(result2);
  CU_ASSERT_STRING_EQUAL(*result2, val);

  char *test_res = ioopm_hash_table_remove(ht, key);
  CU_ASSERT_PTR_NOT_NULL(test_res);
  CU_ASSERT_STRING_EQUAL(test_res, val);

  char **result3 = ioopm_hash_table_lookup(ht, key);
  CU_ASSERT_PTR_NULL(result3);

  ioopm_hash_table_destroy(ht);
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
      (NULL == CU_add_test(test_suite1, "Testing creating and destroying", test1_create_destroy)) ||
      (NULL == CU_add_test(test_suite1, "Testing insert fresh", test2_insert_fresh)) ||
      (NULL == CU_add_test(test_suite1, "Testing insert existing", test3_insert_existing)) ||
      (NULL == CU_add_test(test_suite1, "Testing lookup", test4_lookup)) ||
      (NULL == CU_add_test(test_suite1, "Testing remove", test5_remove))

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
