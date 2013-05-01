
#include "tree.h"
#include "treenode.h"

Tree* tree_create()
{
    Tree* tree = malloc(sizeof(tree));
    tree->root = tnode_create("root", NULL);
    return tree;
}

void tree_destroy(Tree* tree)
{
    tnode_destroy(tree->root);
    free(tree);
}

void children_to_arr(TreeNode* node, int start, int end, char* arr[])
{
    TreeNode* it = node->child;
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