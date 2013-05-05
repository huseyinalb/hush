
#ifndef hush_hashmapnode_h
#define hush_hashmapnode_h
#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>

typedef struct HashMapNode {
    char* key;
    void* value;
    void (*destroy_key) (char *);
    void (*destroy_value) (void *);
} HashMapNode;

HashMapNode* hmnode_create(char*, void*, void (*) (char *), void (*) (void *));
void hmnode_free(HashMapNode*);

#endif
