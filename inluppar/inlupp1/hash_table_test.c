#include <CUnit/Basic.h>
#include "hash_table.h"
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

static bool key_equiv(int key, char *value_ignored, void *x)
{
  int *other_key_ptr = x;
  int other_key = *other_key_ptr;
  return key == other_key;
}

static bool value_equiv(int key_ignored, char *value, void *x)
{
  char *other_value = (char *)x;

  if (value == NULL && other_value == NULL)
  {
    return true;
  }
  else if (value == NULL || other_value == NULL)
  {
    return false;
  }
  else
  {
    return strcmp(value, other_value) == 0;
  }
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

void test6_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int test1 = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(test1, 0);

  int key = 1;
  char *val = "one";
  ioopm_hash_table_insert(ht, key, val);
  int test2 = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(test2, 1);

  ioopm_hash_table_remove(ht, key);
  int test3 = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(test3, 0);

  ioopm_hash_table_destroy(ht);
}

void test7_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  bool result1 = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(result1);

  int key = 1;
  char *val = "one";
  ioopm_hash_table_insert(ht, key, val);
  bool result2 = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_FALSE(result2);

  ioopm_hash_table_remove(ht, key);
  bool result3 = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(result3);

  ioopm_hash_table_destroy(ht);
}

void test8_clear()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_PTR_NOT_NULL(ht);

  bool result1 = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(result1);

  int key = 1;
  char *val = "one";
  ioopm_hash_table_insert(ht, key, val);
  bool result2 = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_FALSE(result2)
  int size1 = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(size1, 1);

  ioopm_hash_table_clear(ht);
  bool result3 = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(result3);
  int size2 = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(size2, 0);

  ioopm_hash_table_destroy(ht);
}

void test9_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int key1 = 1;
  char *val1 = "one";
  ioopm_hash_table_insert(ht, key1, val1);

  int key2 = 3;
  char *val2 = "fifty five";
  ioopm_hash_table_insert(ht, key2, val2);

  int *keys = ioopm_hash_table_keys(ht);
  CU_ASSERT_EQUAL(*(keys), 1);
  CU_ASSERT_EQUAL(*(keys + 1), 3);

  ioopm_hash_table_destroy(ht);
  free(keys);
}

void test10_values()
{

  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int key1 = 1;
  char *val1 = "one";
  ioopm_hash_table_insert(ht, key1, val1);

  int key2 = 3;
  char *val2 = "fifty five";
  ioopm_hash_table_insert(ht, key2, val2);

  char **values = ioopm_hash_table_values(ht);
  CU_ASSERT_STRING_EQUAL(values[0], val1);
  CU_ASSERT_STRING_EQUAL(*(values + 1), val2);

  ioopm_hash_table_destroy(ht);
  free(values);
}

void test11_has_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int key1 = 1;
  char *val1 = "one";
  bool result1 = ioopm_hash_table_has_key(ht, key1);
  CU_ASSERT_FALSE(result1);

  ioopm_hash_table_insert(ht, key1, val1);
  bool result2 = ioopm_hash_table_has_key(ht, key1);
  CU_ASSERT_TRUE(result2);

  ioopm_hash_table_remove(ht, key1);
  bool result3 = ioopm_hash_table_has_key(ht, key1);
  CU_ASSERT_FALSE(result3);

  ioopm_hash_table_destroy(ht);
}

void test12_has_value()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int key1 = 1;
  char *val1 = "one";
  char *testy1 = ioopm_strdup(val1);

  int key2 = 8;
  char *val2 = NULL;
  // char *testy2 = ioopm_strdup(val2);

  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, val1));
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, val2));

  ioopm_hash_table_insert(ht, key1, val1);
  ioopm_hash_table_insert(ht, key2, val2);
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, val1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, val2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, testy1));

  ioopm_hash_table_clear(ht);
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, val1));
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, val2));
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, testy1));

  ioopm_hash_table_destroy(ht);
  free(testy1);
}

void test13_any_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int eqkey = 1;
  bool result1 = ioopm_hash_table_any(ht, key_equiv, &eqkey);
  CU_ASSERT_FALSE(result1);

  int key1 = 2;
  char *val1 = "Two";
  ioopm_hash_table_insert(ht, key1, val1);
  bool result2 = ioopm_hash_table_any(ht, key_equiv, &eqkey);
  CU_ASSERT_FALSE(result2);

  int key2 = 1;
  char *val2 = "one one";
  ioopm_hash_table_insert(ht, key2, val2);
  bool result3 = ioopm_hash_table_any(ht, key_equiv, &eqkey);
  CU_ASSERT_TRUE(result3);

  ioopm_hash_table_destroy(ht);
}

void test14_all_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int eqkey = 1;
  bool result1 = ioopm_hash_table_all(ht, key_equiv, &eqkey);
  CU_ASSERT_FALSE(result1);

  int key1 = 1;
  char *val1 = "oneeeeee";
  ioopm_hash_table_insert(ht, key1, val1);
  bool result2 = ioopm_hash_table_all(ht, key_equiv, &eqkey);
  CU_ASSERT_TRUE(result2);

  int key2 = 1;
  char *val2 = "small one one";
  ioopm_hash_table_insert(ht, key2, val2);
  bool result3 = ioopm_hash_table_all(ht, key_equiv, &eqkey);
  CU_ASSERT_TRUE(result3);

  int key3 = 15;
  char *val3 = "nothing nnn";
  ioopm_hash_table_insert(ht, key3, val3);
  bool result4 = ioopm_hash_table_all(ht, key_equiv, &eqkey);
  CU_ASSERT_FALSE(result4);

  ioopm_hash_table_destroy(ht);
}

void test15_any_value()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *eq_val = "one";
  bool result1 = ioopm_hash_table_any(ht, value_equiv, eq_val);
  CU_ASSERT_FALSE(result1);

  int key1 = 1;
  char *val1 = "ONE ONE";
  ioopm_hash_table_insert(ht, key1, val1);
  bool result2 = ioopm_hash_table_any(ht, value_equiv, eq_val);
  CU_ASSERT_FALSE(result2);

  int key2 = 22;
  char *val2 = "one";
  ioopm_hash_table_insert(ht, key2, val2);
  bool result3 = ioopm_hash_table_any(ht, value_equiv, eq_val);
  CU_ASSERT_TRUE(result3);

  ioopm_hash_table_destroy(ht);
}

void test16_all_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *eq_val = "one";
  bool result1 = ioopm_hash_table_all(ht, value_equiv, eq_val);
  CU_ASSERT_FALSE(result1);

  int key1 = 1;
  char *val1 = "one";
  ioopm_hash_table_insert(ht, key1, val1);
  bool result2 = ioopm_hash_table_all(ht, value_equiv, eq_val);
  CU_ASSERT_TRUE(result2);

  int key2 = 2;
  char *val2 = "one";
  ioopm_hash_table_insert(ht, key2, val2);
  bool result3 = ioopm_hash_table_all(ht, value_equiv, eq_val);
  CU_ASSERT_TRUE(result3);

  int key3 = 33;
  char *val3 = "one one";
  ioopm_hash_table_insert(ht, key3, val3);
  bool result4 = ioopm_hash_table_all(ht, value_equiv, eq_val);
  CU_ASSERT_FALSE(result4);

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
      (NULL == CU_add_test(test_suite1, "Testing remove", test5_remove)) ||
      (NULL == CU_add_test(test_suite1, "Testing size", test6_size)) ||
      (NULL == CU_add_test(test_suite1, "Testing empty", test7_empty)) ||
      (NULL == CU_add_test(test_suite1, "Testing clear", test8_clear)) ||
      (NULL == CU_add_test(test_suite1, "Testing keys", test9_keys)) ||
      (NULL == CU_add_test(test_suite1, "Testing values", test10_values)) ||
      (NULL == CU_add_test(test_suite1, "Testing has key", test11_has_key)) ||
      (NULL == CU_add_test(test_suite1, "Testing has value", test12_has_value)) ||
      (NULL == CU_add_test(test_suite1, "Testing any key", test13_any_key)) ||
      (NULL == CU_add_test(test_suite1, "Testing all keys", test14_all_keys)) ||
      (NULL == CU_add_test(test_suite1, "Testing any value", test15_any_value)) ||
      (NULL == CU_add_test(test_suite1, "Testing all values", test16_all_values))

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
