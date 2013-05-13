
#include "tree.h"

Tree* tree_create()
{
    Tree* tree = malloc(sizeof(Tree));
    tree->root = tnode_create("root", NULL);
    return tree;
}

void tree_destroy(Tree* tree)
{
    tnode_destroy(tree->root);
#ifdef TEST
    assert(treenode_test_ptrchecks[*treenode_test_index] == tree);
    (*treenode_test_index)++;
#endif
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