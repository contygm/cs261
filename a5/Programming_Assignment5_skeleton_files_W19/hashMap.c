/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: 
 * Date: 
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // REVIEW: implement
    assert(map != 0);
    HashLink * next;
    HashLink * current;

    for (int i = 0; i < map->capacity; i++)
    {
        if(map->size == 0) {
            break;
        }

        current = map->table[i];

        if (current != 0)
        {
            next = current->next;
        }
        
        while (current != 0)
        {
            current->key = 0;
            current->value = 0;

            hashLinkDelete(current);
            map->size--;
            current = next;

            if(current != 0) {
                next = current->next;
            }
        }
    }
    
    free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // REVIEW: implement
    int index;
    struct HashLink * current;

    index = HASH_FUNCTION(key) % map->capacity;
    current = map->table[index];

    while (current != 0)
    {
        if(strcmp(current->key, key) == 0) {
            // using & cuz must return int*
            return &(current->value); 
        }

        current= current->next;
    }
    
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // REVIEW: implement
    int oldCap = hashMapCapacity(map);
    struct HashMap * tmp = hashMapNew(capacity);

    for (int i = 0; i < oldCap; i++)
    {
        HashLink * current = map->table[i];
        while (current != 0)
        {
            hashMapPut(tmp, current->key, current->value);
            current = current->next;
        }
    }

    hashMapCleanUp(map);
    
    map->capacity = tmp->capacity;
    map->size = tmp->size;
    map->table = tmp->table;

    tmp->table = NULL;
    free(tmp);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // REVIEW: implement
    float load;
    int capacity = hashMapCapacity(map);
    int index = HASH_FUNCTION(key) % capacity;

    if(index < 0) {
        index += capacity;
    }

    if (hashMapContainsKey(map, key))
    {
        int * tmp = hashMapGet(map, key);
        (*tmp) = value;
    }
    else
    {
        HashLink * new = hashLinkNew(key, value, NULL);
        assert(new != NULL);

        if (map->table[index] == NULL)
        {
            map->table[index] = new;
        }
        else
        {
            HashLink* current = map->table[index];
            while(current->next) {
                current = current->next;
            }
            current->next = new;
        }
        map->size++;  
    }

    load = hashMapTableLoad(map);
    if (load >= MAX_TABLE_LOAD)
    {
        resizeTable(map, (2*capacity));
    }
    
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // REVIEW: implement
    assert(map != NULL);
    assert(key != NULL);

    int index = HASH_FUNCTION(key) % hashMapCapacity(map);

    HashLink * current = map->table[index];
    HashLink * prev = NULL;

    if(current != NULL) {
        if (strcmp(current->key, key) == 0) {
            map->table[index] = current->next;
        } else {
            while (strcmp(current->key, key) != 0)
            {
                prev = current;
                current = current->next;
            }
            
            if (prev) {
                prev->next = current->next;
            }
        }

        hashLinkDelete(current);
        map->size--;
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // REVIEW: implement
    assert(map != NULL);
    assert(key != NULL);

    int capacity = hashMapCapacity(map);
    int index = HASH_FUNCTION(key) % capacity;

    if(index < 0) {
        index += capacity;
    }

    HashLink * current = map->table[index];

    while (current)
    {
        if(strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // REVIEW: implement
    assert(map != 0);

    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // REVIEW: implement
    assert(map != 0);
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // REVIEW: implement
    int count = 0;
    int capacity = hashMapCapacity(map);
    for (int i = 0; i < capacity; i++)
    {
        if (map->table[i] == 0) {
            count++;
        }
    }
    
    return count;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // REVIEW: implement
    assert(map != 0);
    float size = (float) hashMapSize(map);
    float capacity = (float) hashMapCapacity(map);

    // (number of links) / (number of buckets)
    return (size/capacity);
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
  // REVIEW: implement
  for (int i = 0; i < map->capacity; i++)
  {
      HashLink * tmp = map->table[i];
      if(tmp != NULL) {
          while (tmp != NULL)
          {
              printf("key: %s, value: %d", tmp->key, tmp->value);
              tmp = tmp->next;
          }
      }
  }

   printf("\n");
}