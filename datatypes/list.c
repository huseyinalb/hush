
#include "list.h"

List* list_create()
{
    List* list = malloc(sizeof(List));
    list->start = NULL;
    list->last = NULL;
    list->len = 0;
    return list;
}

void list_destroy(List* list)
{
    ListNode* node;
    if ((node = list->start)!= NULL) {
        do {
            ListNode* tail = node;
            node = node->next;
            lnode_destroy(tail);
        } while (node!=NULL);
    }
    free(list);
}

void for_each(List* list, void (func) (ListNode*))
{
    ListNode* it = list->start;
    while(it != NULL) {
        func(it);
        it = it->next;
    }
    
}

void list_add(List* list, void* var, void (*destroy_var) (void *)){
    if (list->start == NULL) {
        list->start = lnode_create(var, destroy_var);
        list->last = list->start;
    } else {
        ListNode* new_last = lnode_create(var, destroy_var);
        list->last->next = new_last;
        list->last = new_last;
    }
    list->len++;
}

int list_len(List* list)
{
    return list->len;
}

void list_to_arr(List* list, int start, int end, char* arr[])
{
    ListNode* it = list->start;
    int i = 0;
    while(it != NULL) {
        if (i>=start)
            arr[i] = it->var;
        else if (i >= end)
            break;
        it = it->next;
        i++;
    }
    arr[i] = NULL;
}
