

#include "interpreter.h"



void run_command(Builtins* builtins, TreeNode* stmt)
{
    // TODO this func is very messy, should be refactored
    pid_t  pid;
    int    status;
    if (stmt->child != NULL) {
        TreeNode* pipe_it = stmt->child;
        int pipe_exclusion = pipe_it->next == NULL && pipe_it->child && builtin_has(builtins, pipe_it->child->var);
        int command_count = 0;
        TreeNode* cmd_node = pipe_it;
        // TODO? we may insert a length var to the struct
        for (;cmd_node!=NULL;cmd_node=cmd_node->next)
            command_count++;
        int pipe_d[command_count];
        if (!pipe_exclusion) {
            int i;
            for(i = 0; i < command_count*2; i+=2){
                if(pipe(&pipe_d[i]) < 0) {
                    perror("Couldn't Pipe");
                    exit(EXIT_FAILURE);
                }
            }
        }
        int pipe_start = 0;
        while (pipe_it != NULL) {
            if (pipe_exclusion) {
                // TODO you know
                char * args[32];
                tnode_children_to_arr(pipe_it, args);
                // return value should be used in env or sth :)
                int code = builtin_run(builtins, pipe_it->child->var, args);
            } else {
                if ((pid = fork()) < 0) {
                    perror("Fork error");
                    exit(1);
                } else if (pid == 0) {
                    //if not the last command
                    if(pipe_it->next != NULL){
                        if(dup2(pipe_d[pipe_start + 1], 1) < 0){
                            perror("dup2");
                            exit(EXIT_FAILURE);
                        }
                    }
                    //if not the first command
                    if( pipe_it != stmt->child ){
                        if(dup2(pipe_d[pipe_start - 2], 0) < 0){
                            perror("dup2");
                            exit(EXIT_FAILURE);
                        }
                    }
                    int i;
                    for(i = 0; i < command_count*2; i++){
                        close(pipe_d[i]);
                    }
                    // TODO you know
                    char * args[32];
                    tnode_children_to_arr(pipe_it, args);
                    if (builtin_has(builtins, pipe_it->child->var) != 0){
                        int code = builtin_run(builtins, pipe_it->child->var, args);
                        exit(code);
                    } else if (execvp(pipe_it->child->var, args) < 0) {
                        perror("Exec error");
                        exit(1);
                    }
                }
            }
            pipe_it = pipe_it->next;
            pipe_start += 2;
        }
        if (!pipe_exclusion) {
            int i;
            for(i = 0; i < command_count*2; i++){
                close(pipe_d[i]);
            }
            while((wait(&status)!= -1) || errno != ECHILD);
        }
    }
    
}