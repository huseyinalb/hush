
#ifndef hush_list_h
#define hush_list_h

#include <stdio.h>
#include <stdlib.h>
#include "listnode.h"

typedef struct List {
    ListNode* start;
    ListNode* last;
    int len;
} List;


List* list_create();

void list_destroy(List*);

void for_each(List*, void (*) (ListNode*));

void list_add(List*, void*, void (*) (void *));

int list_len(List*);

void list_to_arr(List*, int, int, char* []);

#endif
