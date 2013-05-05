
#ifndef hush_hashmap_h
#define hush_hashmap_h

#include <string.h>
#ifdef DEBUG
#include <stdio.h>
#endif
#include "hashmapnode.h"

#define INITIAL_HASHMAP_SIZE 512

typedef struct HashMap {
    HashMapNode** table;
    unsigned int size;
    unsigned int count;
} HashMap;

HashMap* hashmap_create();

void hashmap_add_node(HashMap*, char*, void*, void (*) (char *), void (*) (void *));

HashMapNode* hashmap_get(HashMap*, char*);

void hashmap_destroy(HashMap*);

#endif
