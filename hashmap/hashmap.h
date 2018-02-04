//
// Created by Administrator on 2018/2/3 0003.
//

#ifndef HELLO_HASHMAP_H
#define HELLO_HASHMAP_H

#include <stdint.h>    /** uint64_t */
#include <stddef.h>    /** size_t */

struct _hashmap;
typedef struct _hashmap hashmap;

hashmap* create_hashmap(size_t size);

int free_hashmap(hashmap* map);

int hashmap_insert(hashmap* map, char* key, size_t key_len, void* data, size_t data_len);

int hashmap_insert_uint64_key(hashmap* map, uint64_t key, void* data, size_t data_len);


int hashmap_remove(hashmap* map, char* key, size_t key_len);

int hashmap_remove_uint64_key(hashmap* map, uint64_t key);

void* hashmap_get(hashmap* map, char* key, size_t key_len);

void* hashmap_get_uint64_key(hashmap* map, uint64_t key);

size_t hashmap_count(hashmap* map);


#endif // HELLO_HASHMAP_H
