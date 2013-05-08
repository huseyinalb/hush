
#ifndef hush_builtins_h
#define hush_builtins_h

#include <stdio.h>
#include "../datatypes/hashmap.h"
#include "cd.h"

typedef struct Builtins {
    HashMap* table;
} Builtins;

Builtins* builtins_create();

int builtin_run(Builtins*, char*, char**);

int builtin_has(Builtins*, char*);

void builtins_destroy(Builtins* builtins);

#endif

