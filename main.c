
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatypes/list.h"
#include "datatypes/tree.h"
#include "parser/parser.h"
#include "parser/interpreter.h"
#include "builtins/builtins.h"

#define MAX_BUFF 512

const char* exit_str = "exit\n";

int prompt(char * command)
{
    printf(">> ");
    if (!fgets(command, MAX_BUFF, stdin)) {
        printf("\n");
        return 0;
    } else
        return 1;
}

void print_node(ListNode* node)
{
    printf("%s ", (char*) node->var);
}

int main(int argc, const char * argv[])
{
    char command[MAX_BUFF];
    printf("mangalsh v0.1\n");
    Builtins* builtins = builtins_create();
    while (prompt(command)) {
        size_t command_len = strlen(command);
        if (command_len > 1)
            command[command_len-1] = '\0';
        struct List* list = tokenize(command);
        struct Tree* tree = parse_command(list);
        list_destroy(list);
        
        //list_for_each(list, print_node);
        TreeNode* it = tree->root->child;
        while (it != NULL) {
            run_command(builtins, it);
            it = it->next;
        }
        tree_destroy(tree);
    };
    builtins_destroy(builtins);
    return 0;
}

