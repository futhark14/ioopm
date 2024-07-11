#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef bool (*ioopm_int_predicate)(int index, int value, void *extra);
typedef void (*ioopm_apply_int_function)(int index, int *value, void *extra);

typedef struct list ioopm_list_t; /// Meta: struct definition goes in C file

/// @brief Creates a new empty list
/// @return an empty linked list
ioopm_list_t *ioopm_linked_list_create(void);

/// @brief Tear down the linked list and return all its memory (but not the memory of the values)
/// @param list the list to be destroyed
void ioopm_linked_list_destroy(ioopm_list_t *list);

/// @brief Insert at the end of a linked list in O(1) time
/// @param list the linked list that will be appended
/// @param value the value to be appended
void ioopm_linked_list_append(ioopm_list_t *list, int value);

/// @brief Insert at the front of a linked list in O(1) time
/// @param list the linked list that will be prepended to
/// @param value the value to be prepended
void ioopm_linked_list_prepend(ioopm_list_t *list, int value);

/// @brief Insert an value into a linked list in O(n) time.
/// The valid values of index are [0,n] for a list of n values,
/// where 0 means before the first value and n means after
/// the last value.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be inserted 
void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value);

/// @brief Remove an value from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n values,
/// where 0 means the first value and n-1 means the last value.
/// @param list the linked list
/// @param index the position in the list
/// @return the value removed
int ioopm_linked_list_remove(ioopm_list_t *list, int index);

/// @brief Retrieve an value from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n values,
/// where 0 means the first value and n-1 means the last value.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @return the value at the given position
int ioopm_linked_list_get(ioopm_list_t *list, int index);

/// @brief Test if an value is in the list
/// @param list the linked list
/// @param value the value sought
/// @return true if value is in the list, else false
bool ioopm_linked_list_contains(ioopm_list_t *list, int value);

/// @brief Lookup the number of values in the linked list in O(1) time
/// @param list the linked list
/// @return the number of values in the list
int ioopm_linked_list_size(ioopm_list_t *list);

/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of values int the list is 0, else false
bool ioopm_linked_list_is_empty(ioopm_list_t *list);

/// @brief Remove all values from a linked list
/// @param list the linked list
void ioopm_linked_list_clear(ioopm_list_t *list);

/// @brief Test if a supplied property holds for all values in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested (function pointer)
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for all values in the list, else false
bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra);

/// @brief Test if a supplied property holds for any value in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for any values in the list, else false
bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra);

/// @brief Apply a supplied function to all values in a list.
/// @param list the linked list
/// @param fun the function to be applied
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of fun
void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra);
