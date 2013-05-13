
#include <stdio.h>
#include "list.h"
#include "assert.h"
#include <string.h>
void node_check(ListNode* node) {
    static char a = 'a';
    switch (a) {
        case 'a':
            assert(!strcmp(node->var, "anode"));
            break;
        case 'b':
            assert(!strcmp(node->var, "bnode"));
            break;
        case 'c':
            assert(!strcmp(node->var, "cnode"));
        break;
    }
    a++;
}

int main()
{
    List* list = list_create();
    list_add(list, strdup("anode"), free);
    list_add(list, strdup("bnode"), free);
    list_add(list, strdup("cnode"), free);
    list_for_each(list, node_check);
    list_destroy(list);
    assert(list->len == 0);
    return 0;
}