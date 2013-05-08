
#include "hashmap.h"

HashMap* hashmap_create()
{
    HashMap* hashmap = malloc(sizeof(HashMap));
    // TODO enough for builtins for now but dynamize the table size later to make more generic
    hashmap->table = calloc(sizeof(HashMapNode*), INITIAL_HASHMAP_SIZE);
    hashmap->size = INITIAL_HASHMAP_SIZE;
    hashmap->count = 0;
    return hashmap;
}

// seems a suitable algorithm for a simple hashmap implementation
static unsigned long sdbm(unsigned char *str)
{
    unsigned long hash = 0;
    int c;
    
    while ((c = *str) != '\0'){
        str++;
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned long find_place(HashMap* hashmap, char* key)
{
    unsigned long place = sdbm((unsigned char*)key) % hashmap->size;
    if(hashmap->table[place] != NULL && strcmp(hashmap->table[place]->key, key)) {
        do {
            place = (place+1) % hashmap->size;
        } while(hashmap->table[place] != 0 || strcmp(hashmap->table[place]->key, key));
    }
    return place;
}

void hashmap_add_node(HashMap* hashmap, char* key, void* value, void (*destroy_key) (char *), void (*destroy_value) (void *))
{
    unsigned long place = find_place(hashmap, key);
    if (hashmap->table[place] != 0){
        hmnode_free(hashmap->table[place]);
    }
    hashmap->table[place] = hmnode_create(key, value, destroy_key, destroy_value);
    hashmap->count++;
}

int hashmap_for_each(HashMap* hashmap, void (*func) (HashMapNode* node))
{
    int i = 0;
    int count = 0;
    for(;i<hashmap->size;i++) {
        HashMapNode* node = hashmap->table[i];
        if (node != NULL) {
            func(node);
            count++;
        }
    }
    return count;
}

HashMapNode* hashmap_get(HashMap* hashmap, char* key)
{
    return hashmap->table[find_place(hashmap, key)];
}

void hashmap_destroy(HashMap* hashmap)
{
#ifdef DEBUG
    printf("freeing hashmap:%d\n", (int) hashmap);
#endif
    int freed_count = hashmap_for_each(hashmap, hmnode_free);
    hashmap->count -= freed_count;
    free(hashmap);
}