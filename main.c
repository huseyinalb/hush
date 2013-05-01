
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "list.h"
#include "tree.h"

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

void destroy_charp(void* word) {
    free(word);
}

List* tokenize(char* command)
{
    struct List* list = list_create();
    const int n_matches = 10;
    const char * p = command;
    regmatch_t m[n_matches];
    regex_t r;
    char* regex_text = "(&&| |[a-zA-Z0-9_\\.\\\\/]+)";
    int status = regcomp (&r, regex_text, REG_EXTENDED|REG_NEWLINE);
    if (status != 0) {
        perror("error compiling regex");
        return list;
    }
    while (regexec (&r, p, n_matches, m, 0)) {
        // TODO you know
        char buff[MAX_BUFF];
        int finish;
        finish = (int)m[1].rm_eo;
        snprintf(buff, finish+1, "%s", p);
        //printf(":%s\n", buff);
        if (buff[0]!=' ') {
            list_add(list, strdup(buff), destroy_charp);
        }
        p += m[0].rm_eo;
    }
    regfree(&r);
    return list;
}

struct Tree* parse_command(List* tokens)
{
    Tree* tree = tree_create();
    TreeNode* root = tree->root;
    TreeNode* active_parent = tnode_add_child(root, "stmt", NULL);
    ListNode* it = tokens->start;
    while (it != NULL) {
        if (!strcmp(it->var, "&&")){
            active_parent = tnode_add_child(root, "stmt", NULL);
        } else {
            tnode_add_child(active_parent, strdup(it->var), destroy_charp);
        }
        it = it->next;
    }
    return tree;
}

void print_node(ListNode* node)
{
    printf("%s ", (char*) node->var);
}

void run_command(TreeNode* node)
{
    pid_t  pid;
    int    status;
    if (node->child != NULL) {
        if ((pid = fork()) < 0) {
            perror("EROR ULAN");
            exit(1);
        } else if (pid == 0) {
            // TODO you know
            char * args[32];
            tnode_children_to_arr(node, args);
            if (execvp(node->child->var, args) < 0) {
                perror("EROR ULAN");
                exit(1);
            }
        } else {
            while (wait(&status) != pid);
        }

    }
}

int main(int argc, const char * argv[])
{
    char command[MAX_BUFF];
    printf("Hush v0.1\n");
    while (prompt(command)) {
        size_t command_len = strlen(command);
        if (command_len > 1)
            command[command_len-1] = '\0';
        struct List* list = tokenize(command);
        struct Tree* tree = parse_command(list);
        list_destroy(list);
        
        //for_each(list, print_node);
        TreeNode* it = tree->root->child;
        while (it != NULL) {
            run_command(it);
            it = it->next;
        }
        tree_destroy(tree);
    };
    return 0;
}

