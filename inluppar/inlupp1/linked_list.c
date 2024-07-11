#include "linked_list.h"

typedef struct link link_t;

struct link
{
  int value;
  link_t *next;
};

struct list
{
  link_t *first;
  link_t *last;
  int size;
};

link_t *list_inner_find_previous(link_t *link, int index)
{
  link_t *cursor = link;

  for (int i = 0; i < index; ++i)
  {
    cursor = cursor->next;
  }

  return cursor;
}

int list_inner_adjust_index(int index, int upper_bound)
{
  if (index < 0)
  {
    return 0;
  }
  else if (index > upper_bound)
  {
    return upper_bound;
  }
  else
  {
    return index;
  }
}

/////////////////// Internals end ////////////////////

link_t *link_create(int value, link_t *next)
{
  link_t *link = calloc(1, sizeof(link_t));

  if (link)
  {
    link->value = value;
    link->next = next;
  }
  return link;
}

ioopm_list_t *ioopm_linked_list_create(void)
{
  ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));

  if (list)
  {
    list->first = list->last = calloc(1, sizeof(link_t));
    list->size = 0;
  }

  return list;
}

void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
  link_t *new_link = link_create(value, NULL);
  list->last->next = new_link;
  list->last = new_link;
  list->size++;
}

void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
  link_t *new_link = link_create(value, list->first->next);

  if (list->first == list->last)
  {
    list->last = new_link;
  }
  list->first->next = new_link;
  list->size++;
}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{
  int valid_index = list_inner_adjust_index(index, list->size);
  link_t *prev = list_inner_find_previous(list->first, valid_index);

  link_t *new_link = link_create(value, prev->next);
  prev->next = new_link;
  // prev->next = link_create(value, prev->next);could be one-liner
  list->size++;

  if (valid_index == list->size)
  {
    list->last->next = new_link;
    list->last = new_link;
  }
  // TODO:test this
}

int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
  int valid_index = list_inner_adjust_index(index, list->size);

  link_t *prev = list_inner_find_previous(list->first, valid_index);
  link_t *to_remove = prev->next;
  int removed_value = to_remove->value;

  prev->next = to_remove->next;
  free(to_remove);
  list->size--;

  return removed_value;
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
  link_t *cursor = list->first->next;

  while (cursor)
  {
    link_t *tmp = cursor;
    cursor = cursor->next;
    free(tmp);
    list->size--;
  }
  // these two are important
  // TODO: remove them successively and test
  list->first->next = NULL;
  list->last = list->first;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
  ioopm_linked_list_clear(list);
  free(list->first);
  free(list);
}

int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
  int valid_index = list_inner_adjust_index(index, list->size);
  link_t *prev = list_inner_find_previous(list->first, valid_index);

  return prev->next->value;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, int value)
{
  link_t *cursor = list->first->next;

  while (cursor)
  {
    if (cursor->value == value)
    {
      return true;
    }
    cursor = cursor->next;
  }
  return false;
}

int ioopm_linked_list_size(ioopm_list_t *list)
{
  return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
  return list->size == 0;
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
  //same as hash table, without this an empty linked list returns true
  if (ioopm_linked_list_size(list) == 0)
  {
    return false;
  }

  link_t *cursor = list->first->next;

  for (int i = 0; i < list->size && cursor; i++)
  {
    if (!prop(i, cursor->value, extra))
    {
      return false;
    }
    cursor = cursor->next;
  }
  return true;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
  link_t *cursor = list->first->next;

  for (int i = 0; i < list->size && cursor; i++)
  {
    if (prop(i, cursor->value, extra))
    {
      return true;
    }
    cursor = cursor->next;
  }
  return false;
}

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{
  link_t *cursor = list->first->next;

  for (int i = 0; i < list->size && cursor; i++)
  {
    fun(i, &cursor->value, extra);
    cursor = cursor->next;
  }
}