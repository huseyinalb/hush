
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "datatypes/list.h"
#include "datatypes/tree.h"

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
    char* regex_text = "(&&| |\\||[a-zA-Z0-9_\\.\\\\/]+)";
    int status = regcomp (&r, regex_text, REG_EXTENDED|REG_NEWLINE);
    if (status != 0) {
        perror("error compiling regex");
        return list;
    }
    while (!regexec (&r, p, n_matches, m, 0)) {
        // TODO you know
        char buff[MAX_BUFF];
        int finish;
        finish = (int) m[1].rm_eo;
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
    TreeNode* active_pipe_parent = tnode_add_child(active_parent, "pipe", NULL);
    ListNode* it = tokens->start;
    while (it != NULL) {
        if (!strcmp(it->var, "&&")){
            active_parent = tnode_add_child(root, "stmt", NULL);
            active_pipe_parent = tnode_add_child(active_parent, "pipe", NULL);
        } else if (!strcmp(it->var, "|")) {
            active_pipe_parent = tnode_add_child(active_parent, "pipe", NULL);
        } else {
            tnode_add_child(active_pipe_parent, strdup(it->var), destroy_charp);
        }
        it = it->next;
    }
    return tree;
}

void print_node(ListNode* node)
{
    printf("%s ", (char*) node->var);
}

void run_command(TreeNode* stmt)
{
    // TODO you know
    int pipe_d[10];
    int i;
    for(i = 0; i < 10; i+=2){
        if(pipe(&pipe_d[i]) < 0) {
            perror("Couldn't Pipe");
            exit(EXIT_FAILURE);
        }
    }
    pid_t  pid;
    int    status;
    if (stmt->child != NULL) {
        TreeNode* pipe_it = stmt->child;
        int pipe_start = 0;
        while (pipe_it != NULL) {
            if ((pid = fork()) < 0) {
                perror("Fork error");
                exit(1);
            } else if (pid == 0) {
                //printf("%s: starting\n", pipe_it->child->var);
                //if not last command
                if(pipe_it->next != NULL){
                    if(dup2(pipe_d[pipe_start + 1], 1) < 0){
                        perror("dup2");
                        exit(EXIT_FAILURE);
                    }
                }
                //if not first command
                if( pipe_it != stmt->child ){
                    if(dup2(pipe_d[pipe_start - 2], 0) < 0){
                        perror("dup2");
                        exit(EXIT_FAILURE);
                    }
                }
                for(i = 0; i < 10; i++){
                    close(pipe_d[i]);
                }
                // TODO you know
                char * args[32];
                tnode_children_to_arr(pipe_it, args);
                if (execvp(pipe_it->child->var, args) < 0) {
                    perror("Exec error");
                    exit(1);
                }
                //exit(0);
            } else {
                pipe_it = pipe_it->next;
                pipe_start += 2;
            }
        }
        for(i = 0; i < 10; i++){
            close(pipe_d[i]);
        }
        while(wait(&status) != pid);
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

