#include <stdlib.h>
#include "hash_table.h"
#define BUCKETS_SIZE 17

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[BUCKETS_SIZE];
};

static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  if (new_entry == NULL)
  {
    return NULL; // Handle allocation failure
  }

  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;

  return new_entry;
}

static void entry_destroy(entry_t *current)
{
  free(current);
}

static entry_t *find_previous_entry_for_key(entry_t *sentinel, int key)
{

  entry_t *current = sentinel;
  while (current && current->next)
  {
    if (current->next->key == key)
    {
      return current;
    }
    current = current->next;
  }
  return sentinel;
}

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = key % BUCKETS_SIZE;
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
  {
    next->value = value;
  }
  else
  {
    entry->next = entry_create(key, value, next);
  }
}

char **ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[key % BUCKETS_SIZE], key);
  entry_t *next = tmp->next;

  if (next && next->key == key)
  {
    return &next->value;
  }
  else
  {
    return NULL;
  }
}

char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
  entry_t *current = find_previous_entry_for_key(&ht->buckets[key % BUCKETS_SIZE], key);
  entry_t *to_be_removed = current->next;

  if (to_be_removed && to_be_removed->key == key)
  {
    char *val = to_be_removed->value;
    current->next = to_be_removed->next;
    entry_destroy(to_be_removed);
    to_be_removed = NULL;

    return val;
  }
  return NULL;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *sentinel = &ht->buckets[i];
    entry_t *current = sentinel->next;
    //sentinel->next = NULL; // viktigt, utan den memleaks --eller? den behövs inte alls?

    while (current)
    {
      entry_t *tmp = current;
      current = current->next;
      entry_destroy(tmp);
      current = NULL;
    }
  }
  free(ht);
}