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

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *sentinel = &ht->buckets[i];
    entry_t *current = sentinel->next;
    sentinel->next = NULL; // viktigt,
    // test8 clear  tar bort alla entries i HT med   ioopm_hash_table_clear(ht);
    // När man därefter på slutet anropar  ioopm_hash_table_destroy(ht); så blir det anrop till free två gånger,
    // dessutom på en null pointer eftersom man sätter den NULL nedanför.
    // Det som behöver göras är att sätta sentinels next NULL så destroy inte hamnar i while loopen nedan
    // Kom ihåg att destroy är samma sak som clear och en free(ht)

    while (current)
    {
      entry_t *tmp = current;
      current = current->next;
      entry_destroy(tmp);
      current = NULL;
    }
  }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_clear(ht);
  free(ht);
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  int counter = 0;

  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current)
    {
      counter++;
      current = current->next;
    }
  }
  return counter;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *current = (&ht->buckets[i])->next;

    if (current)
    {
      return false;
    }
  }
  return true;
}

int *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  int size = ioopm_hash_table_size(ht);
  int *keys = calloc(size, sizeof(int));
  // I had k++ in the for loop instead of "*(keys + k++)"
  // The problem with that is that it increases the k for every bucket, regardless if there is anything in the bucket.
  // The correct implementation is this, where k is increased only if there is a current(bucket has an entry other than sentinel)
  int k = 0;

  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current)
    {
      *(keys + k++) = current->key;
      current = current->next;
    }
  }
  return keys;
}

char **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  int size = ioopm_hash_table_size(ht);
  char **values = calloc(size, sizeof(char *));

  int k = 0;
  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current)
    {
      *(values + k++) = current->value;
      current = current->next;
    }
  }
  return values;
}

static bool key_equiv(int key, char *value_ignored, void *x)
{
  int *other_key_ptr = x;
  int other_key = *other_key_ptr;

  // return key == *((int *)x); one-liner
  return key == other_key;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key)
{
  return ioopm_hash_table_any(ht, key_equiv, &key);
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

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value)
{
  return ioopm_hash_table_any(ht, value_equiv, value);
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
  //this is neccessary since test14 checks the corner case of an empty HT, in that case the last statement "return true" is executed.
  //An empty HT should not return true since it is not comparing to any keys, it should return false.
  bool is_empty = ioopm_hash_table_is_empty(ht);
  if (is_empty) 
  {
    return false;
  }

  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current)
    {
      if (!pred(current->key, current->value, arg))
      {
        return false;
      }
      current = current->next;
    }
  }
  return true;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current)
    {
      if (pred(current->key, current->value, arg))
      {
        return true;
      }
      current = current->next;
    }
  }
  return false;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg)
{
  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current)
    {
      apply_fun(current->key, &current->value, arg);
      current = current->next;
    }
  }
}

// old
/*
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key)
{
  entry_t *previous = find_previous_entry_for_key(&ht->buckets[key % BUCKETS_SIZE], key);
  entry_t *current = previous->next;

  if (current && current->key == key)
  {
    return true;
  }
  return false;
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value)
{
  for (int i = 0; i < BUCKETS_SIZE; i++)
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current)
    {
      if ((current->value == NULL && value == NULL) ||
          (current->value != NULL && value != NULL && strcmp(current->value, value) == 0))
      {
        return true;
      }
      current = current->next;
    }
  }
  return false;
}
*/