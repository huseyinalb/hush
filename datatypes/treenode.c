
#include "treenode.h"

#ifdef TEST
void tnode_set_ptrchecks(int* index, void** ptrchecks)
{
    treenode_test_index = index;
    treenode_test_ptrchecks = ptrchecks;
}
#endif

TreeNode* tnode_create(void * var, void (*destroy_var) (void *))
{
    TreeNode* node = malloc(sizeof(TreeNode));
    node->var = var;
    node->next = NULL;
    node->child = NULL;
    node->destroy_var = destroy_var;
    return node;
}

void tnode__free(TreeNode* node)
{
    if (node->destroy_var != NULL)
        node->destroy_var(node->var);
    free(node);
}

void depth_first_for_each(TreeNode* node, void func(TreeNode*))
{
    if (node->child != NULL)
        depth_first_for_each(node->child, func);
    if (node->next != NULL)
        depth_first_for_each(node->next, func);
#ifdef TEST
    printf("node:%s\n",node->var);
    printf("node:%s\n",((TreeNode*)treenode_test_ptrchecks[*treenode_test_index])->var);
    assert(treenode_test_ptrchecks[*treenode_test_index] == node);
    (*treenode_test_index)++;
#endif
    func(node);
}

void tnode_destroy(TreeNode* node)
{
    depth_first_for_each(node, tnode__free);
}

TreeNode* tnode_add_child(TreeNode* tnode, void* var, void (*destroy_var) (void *))
{
    if (tnode->child == NULL) {
        tnode->child = tnode_create(var, destroy_var);
        return tnode->child;
    } else {
        TreeNode* it = tnode->child;
        while (it->next != NULL)
            it = it->next;
        it->next = tnode_create(var, destroy_var);
        return it->next;
    }
}

void tnode_children_to_arr(TreeNode* node, char* arr[])
{
    TreeNode* it = node->child;
    int i = 0;
    while(it != NULL) {
        arr[i] = it->var;
        it = it->next;
        i++;
    }
    arr[i] = NULL;
}