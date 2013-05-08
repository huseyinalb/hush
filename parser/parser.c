
#include "parser.h"

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
        char buff[PARSER_MAX_BUFF];
        int finish;
        finish = (int) m[1].rm_eo;
        snprintf(buff, finish+1, "%s", p);
        if (buff[0]!=' ') {
            list_add(list, strdup(buff), free);
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
            tnode_add_child(active_pipe_parent, strdup(it->var), free);
        }
        it = it->next;
    }
    return tree;
}
