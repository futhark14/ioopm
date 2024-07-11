#include <CUnit/Basic.h>
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *ioopm_strdup(char *str)
{
  size_t len = strlen(str);
  char *result = calloc(len + 1, sizeof(char));
  strncpy(result, str, len);
  return result;
}
// static bool key_equiv(int key, char *value_ignored, void *x)

static bool is_divisible_by_extra(int index_ignored, int value, void *extra)
{
  int ex = *(int *)extra;

  if (value % ex == 0)
  {
    return true;
  }
  return false;
}

void multiply_all(int index_ignored, int *value, void *extra)
{
  int ex = *(int *)extra;
  *value = *value * ex;
}

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
  ioopm_list_t *list = ioopm_linked_list_create();
  CU_ASSERT_PTR_NOT_NULL(list);

  ioopm_linked_list_destroy(list);
}

void test2_append()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  int val1 = 1;
  ioopm_linked_list_append(list, val1);
  int result1 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_EQUAL(result1, 1);

  int val2 = 23;
  ioopm_linked_list_append(list, val2);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0), 1);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1), 23);

  ioopm_linked_list_destroy(list);
}

void test3_prepend()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  int val1 = 1;
  ioopm_linked_list_prepend(list, val1);
  int result1 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_EQUAL(val1, result1);

  int val2 = 23;
  ioopm_linked_list_prepend(list, val2);
  int result2 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_EQUAL(val2, result2);
  int result3 = ioopm_linked_list_get(list, 1);
  CU_ASSERT_EQUAL(val1, result3);

  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0), 23);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1), 1);

  ioopm_linked_list_destroy(list);
}

void test4_insert()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  int val1 = 1;
  ioopm_linked_list_insert(list, 999, val1); // this tests the inner adjust function
  int result1 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_EQUAL(result1, val1);

  int val2 = 33;
  ioopm_linked_list_insert(list, 999, val2);
  int result2 = ioopm_linked_list_get(list, 1);
  CU_ASSERT_EQUAL(val2, result2);

  int val3 = 44;
  ioopm_linked_list_insert(list, 0, val3);
  int result3 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_EQUAL(val3, result3);

  ioopm_linked_list_destroy(list);
}

void test5_remove()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  int val1 = 1;
  ioopm_linked_list_insert(list, 999, val1); // this tests the inner adjust function
  int result1 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_EQUAL(result1, val1);

  int val2 = 33;
  ioopm_linked_list_insert(list, 999, val2);
  int result2 = ioopm_linked_list_get(list, 1);
  CU_ASSERT_EQUAL(val2, result2);

  int val3 = 44;
  ioopm_linked_list_insert(list, 0, val3);
  int result3 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_EQUAL(val3, result3);

  bool result4 = ioopm_linked_list_contains(list, val3);
  CU_ASSERT_TRUE(result4);
  int result5 = ioopm_linked_list_remove(list, 0);
  CU_ASSERT_EQUAL(result5, val3);
  bool result6 = ioopm_linked_list_contains(list, val3);
  CU_ASSERT_FALSE(result6);

  ioopm_linked_list_destroy(list);
}

void test6_clear()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  int val1 = 1;
  ioopm_linked_list_insert(list, 999, val1); // this tests the inner adjust function
  int result1 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_EQUAL(result1, val1);

  int val3 = 44;
  ioopm_linked_list_insert(list, 0, val3);
  int result3 = ioopm_linked_list_get(list, 0);
  CU_ASSERT_EQUAL(val3, result3);

  ioopm_linked_list_clear(list);
  bool result4 = ioopm_linked_list_contains(list, val3);
  CU_ASSERT_FALSE(result4);

  ioopm_linked_list_destroy(list);
}

void test7_size_and_empty(void)
{
  ioopm_list_t *list = ioopm_linked_list_create();
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 0);
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));

  ioopm_linked_list_insert(list, 0, 333);
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 1);
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));

  ioopm_linked_list_insert(list, 0, 22);
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 2);
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));

  ioopm_linked_list_remove(list, 0);
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 1);
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));

  ioopm_linked_list_remove(list, 0);
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 0);
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));

  ioopm_linked_list_destroy(list);
}

void test8_list_all(void)
{
  ioopm_list_t *list = ioopm_linked_list_create();

  int arg = 3;
  CU_ASSERT_FALSE(ioopm_linked_list_all(list, is_divisible_by_extra, &arg));

  ioopm_linked_list_insert(list, 0, 33);
  CU_ASSERT_TRUE(ioopm_linked_list_all(list, is_divisible_by_extra, &arg));
  ioopm_linked_list_insert(list, 0, 3);
  CU_ASSERT_TRUE(ioopm_linked_list_all(list, is_divisible_by_extra, &arg));
  ioopm_linked_list_insert(list, 0, 1);
  CU_ASSERT_FALSE(ioopm_linked_list_all(list, is_divisible_by_extra, &arg));

  ioopm_linked_list_destroy(list);
}

void test9_list_any(void)
{
  ioopm_list_t *list = ioopm_linked_list_create();

  int arg = 3;
  CU_ASSERT_FALSE(ioopm_linked_list_any(list, is_divisible_by_extra, &arg));

  ioopm_linked_list_insert(list, 0, 1);
  CU_ASSERT_FALSE(ioopm_linked_list_any(list, is_divisible_by_extra, &arg));

  ioopm_linked_list_insert(list, 0, 33);
  CU_ASSERT_TRUE(ioopm_linked_list_any(list, is_divisible_by_extra, &arg));

  ioopm_linked_list_remove(list, 0);
  CU_ASSERT_FALSE(ioopm_linked_list_any(list, is_divisible_by_extra, &arg));

  ioopm_linked_list_destroy(list);
}

void test10_apply_all(void)
{
  ioopm_list_t *list = ioopm_linked_list_create();

  ioopm_linked_list_append(list, 1);
  ioopm_linked_list_append(list, 0);
  ioopm_linked_list_append(list, 33);

  int extra = 3;
  ioopm_linked_list_apply_to_all(list, multiply_all, &extra);

  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0), 3);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 1), 0);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2), 99);

  ioopm_linked_list_destroy(list);
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
      (NULL == CU_add_test(test_suite1, "Testing append", test2_append)) ||
      (NULL == CU_add_test(test_suite1, "Testing prepend", test3_prepend)) ||
      (NULL == CU_add_test(test_suite1, "Testing insert", test4_insert)) ||
      (NULL == CU_add_test(test_suite1, "Testing remove", test5_remove)) ||
      (NULL == CU_add_test(test_suite1, "Testing clear", test6_clear)) ||
      (NULL == CU_add_test(test_suite1, "Testing size and empty", test7_size_and_empty)) ||
      (NULL == CU_add_test(test_suite1, "Testing list all", test8_list_all)) ||
      (NULL == CU_add_test(test_suite1, "Testing list any", test9_list_any)) ||
      (NULL == CU_add_test(test_suite1, "Testing apply all", test10_apply_all))

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
