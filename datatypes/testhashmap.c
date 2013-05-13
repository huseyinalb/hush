
#include <stdio.h>
#include "hashmap.h"
#include "assert.h"

int main()
{
    HashMap* hashmap = hashmap_create();
    hashmap_add_node(hashmap, "trykey", "tryval", NULL, NULL);
    hashmap_add_node(hashmap, "trykey2", "tryval2", NULL, NULL);
    
    HashMapNode* node = hashmap_get(hashmap, "trykey");
    assert(!strcmp("trykey", node->key));
    assert(!strcmp("tryval", node->value));
    node = hashmap_get(hashmap, "trykey2");
    assert(!strcmp("trykey2", node->key));
    assert(!strcmp("tryval2", node->value));
    assert(hashmap->count == 2);
    hashmap_destroy(hashmap);
    assert(hashmap->count == 0);
    return 0;
}