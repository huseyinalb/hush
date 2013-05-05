
#include "hashmapnode.h"

HashMapNode* hmnode_create(char* key, void* value, void (*destroy_key) (char *), void (*destroy_value) (void *))
{
    HashMapNode* node = malloc(sizeof(HashMapNode));
    node->key = key;
    node->value = value;
    node->destroy_key = destroy_key;
    node->destroy_value = destroy_value;
    return node;
}

void hmnode_free(HashMapNode* node)
{
#ifdef DEBUG
    printf("freeing hashmap: %s\n", node->key);
#endif
    if (node->destroy_key != NULL)
        node->destroy_key(node->key);
    if (node->destroy_value != NULL)
        node->destroy_value(node->value);
    free(node);
}