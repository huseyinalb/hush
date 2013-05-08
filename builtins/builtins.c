
#include "builtins.h"

Builtins* builtins_create()
{
    Builtins* builtins = malloc(sizeof(Builtins));
    builtins->table = hashmap_create();
    hashmap_add_node(builtins->table, "cd", cd, NULL, NULL);
    return builtins;
}

int builtin_run(Builtins* builtins, char* cmd, char** args)
{
    int (*builtin_func) (char ** args) = hashmap_get(builtins->table, cmd)->value;
    return builtin_func(args);
}

int builtin_has(Builtins* builtins, char* cmd)
{
    if (hashmap_get(builtins->table, cmd) != NULL){
        return 1;
    } else
        return 0;
}

void builtins_destroy(Builtins* builtins)
{
    hashmap_destroy(builtins->table);
    free(builtins);
}