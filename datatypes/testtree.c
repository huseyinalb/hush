
#include <stdio.h>
#include "tree.h"
#include "assert.h"
#include <string.h>

void node_check(TreeNode* node) {
    static char a = 'a';
    switch (a) {
        case 'a':
            assert(!strcmp(node->var, "cnode"));
            break;
        case 'b':
            assert(!strcmp(node->var, "bnode"));
            break;
        case 'c':
            assert(!strcmp(node->var, "anode"));
            break;
    }
    a++;
}

int main()
{
    Tree* tree = tree_create();
    TreeNode* node1 = tnode_add_child(tree->root, strdup("anode"), free);
    TreeNode* node2 = tnode_add_child(tree->root, strdup("bnode"), free);
    TreeNode* node3 = tnode_add_child(node2, "cnode", NULL);
    
    int index = 0;
    // depth_first
    void* seq[] = {node3, node2, node1, tree->root};
    tnode_set_ptrchecks(&index, seq);
    depth_first_for_each(tree->root, node_check);
    assert(index == 4);
    index = 0;
    void* seq2[] = {node3, node2, node1, tree->root, tree};
    tnode_set_ptrchecks(&index, seq2);
    tree_destroy(tree);
    assert(index == 5);
    return 0;
}