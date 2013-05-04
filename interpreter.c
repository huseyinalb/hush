

#include "interpreter.h"

void run_command(TreeNode* stmt)
{
    int command_count = 0;
    TreeNode* cmd_node = stmt->child;
    // TODO? we may insert a length var to the struct
    for (;cmd_node!=NULL;cmd_node=cmd_node->next)
        command_count++;
    int pipe_d[command_count];
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
                for(i = 0; i < command_count*2; i++){
                    close(pipe_d[i]);
                }
                // TODO you know
                char * args[32];
                tnode_children_to_arr(pipe_it, args);
                if (execvp(pipe_it->child->var, args) < 0) {
                    perror("Exec error");
                    exit(1);
                }
            }
            pipe_it = pipe_it->next;
            pipe_start += 2;
        }
        for(i = 0; i < command_count*2; i++){
            close(pipe_d[i]);
        }
        while((wait(&status)!= -1) || errno != ECHILD);
        
    }
    
}