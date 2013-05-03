
#include "listnode.h"

ListNode* lnode_create(void * var, void (*destroy_var) (void *))
{
    ListNode* node = malloc(sizeof(ListNode));
    node->var = var;
    node->next = NULL;
    node->destroy_var = destroy_var;
    return node;
}

void lnode_destroy(ListNode* node)
{
    if (node->destroy_var != NULL)
        node->destroy_var(node->var);
    free(node);
}