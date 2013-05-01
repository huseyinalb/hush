
#ifndef hush_listnode_h
#define hush_listnode_h

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    void* var;
    struct ListNode* next;
    void (*destroy_var) (void *);
} ListNode;

ListNode* lnode_create(void *, void (*) (void *));

void lnode_destroy(ListNode*);

#endif
