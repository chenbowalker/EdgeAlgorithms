//
// Created by Administrator on 2018/2/3 0003.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashmap.h"

struct _hashmap_entry {
    uint64_t key_hash;
    void* data;
    struct _hashmap_entry* next;
};

typedef _hashmap_entry hashmap_entry;

struct _hashmap {
    hashmap_entry** table;
    size_t size;
    size_t count;
};

static void free_entry(hashmap_entry* entry) {
    hashmap_entry* next = entry->next;
    free(entry->data);
    free(entry);
    if (next != NULL)
        free_entry(next);
}

static void* copy_content(void* data, size_t data_len) {
    void* des = malloc(data_len);
    memcpy(des, data, data_len);
    return des;
}

static hashmap_entry* create_hashmap_entry(uint64_t key, void* data, size_t data_len) {
    hashmap_entry* entry = (hashmap_entry*)malloc(sizeof(hashmap_entry));
    entry->key_hash = key;
    entry->data = copy_content(data, data_len);
    entry->next = NULL;
    return entry;
}

static int search_hashmap_entry_in_linkedlist(hashmap_entry** entry, uint64_t key_hash, hashmap_entry** previous) {
    int key_match = (*entry)->key_hash == key_hash;
    while (!key_match && (*entry)->next != NULL) {
        *previous = *entry;
        *entry = (*entry)->next;
        key_match = (*entry)->key_hash == key_hash;
    }
    return key_match;
}

static uint64_t string_hash(char* key, size_t key_len) {
    uint64_t key_hash = 0;
    unsigned char* p;
    int i;
    for (i = 0, p = (unsigned char*) key; i < key_len; ++i) {
        key_hash = 31 * key_hash + *(p + i);
    }
    printf("%d\n",key_hash);
    return (key_hash & 0x7FFFFFFFFFFFFFFF);
}


/**
 * =================================================
 *                  public function
 * =================================================
 * */

hashmap* create_hashmap(size_t size) {
    hashmap* hm = (hashmap*)malloc(sizeof(hashmap));
    hm->table = (hashmap_entry**)calloc(sizeof(hashmap_entry*), size);
    hm->size = size;
    hm->count = 0;
    return hm;
}

int free_hashmap(hashmap* map){
    int i;
    for(i = 0; i < map->size; i++) {
        hashmap_entry* entry = map->table[i];
        if (entry != NULL)
            free_entry(entry);
    }
    free(map->table);
    free(map);
}

int hashmap_insert(hashmap* map, char* key, size_t key_len, void* data, size_t data_len) {
    return hashmap_insert_uint64_key(map, string_hash(key,key_len), data, data_len);
}

int hashmap_insert_uint64_key(hashmap* map, uint64_t key, void* data, size_t data_len) {
    if (map->size < map->count) {
        return -1;
    }
    ++map->count;
    size_t index = key % map->size;
    if (map->table[index] != NULL) {
        hashmap_entry* entry = map->table[index];
        int key_match = search_hashmap_entry_in_linkedlist(&entry, key, NULL); // &entry  和 二级指针的利用
        if (key_match) {
            free(entry->data);
            entry->data = copy_content(data, data_len);
            --map->count;
        } else {
            entry->next = create_hashmap_entry(key, data, data_len);
        }

    } else {
        map->table[index] = create_hashmap_entry(key, data, data_len);
    }
}


int hashmap_remove(hashmap* map, char* key, size_t key_len) {
    return hashmap_remove_uint64_key(map, string_hash(key, key_len));
}

int hashmap_remove_uint64_key(hashmap* map, uint64_t key) {
    if (map->count == 0)
        return -1;
    size_t index = key % map->size;
    hashmap_entry* entry = map->table[index];
    if (entry != NULL) {
        hashmap_entry* previous = NULL;
        int key_match = search_hashmap_entry_in_linkedlist(&entry, key, &previous);
        if (key_match) {
            --map->count;
            if (previous == NULL) {
                map->table[index] = entry->next;
            } else {
                previous->next = entry->next;
            }
            free(entry->data);
            free(entry);
        }
    }
    return 0;
}

void* hashmap_get(hashmap* map, char* key, size_t key_len) {
    return hashmap_get_uint64_key(map, string_hash(key, key_len));
}

void* hashmap_get_uint64_key(hashmap* map, uint64_t key) {
    size_t index = key % map->size;
    hashmap_entry* entry = map->table[index];
    if (entry != NULL) {
        int key_match = search_hashmap_entry_in_linkedlist(&entry, key, NULL);
        if (key_match) {
            return entry->data;
        }
    }
    return NULL;
}

size_t hashmap_count(hashmap* map) {
    return map->count;
}
