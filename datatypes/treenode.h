
#ifndef hush_treenode_h
#define hush_treenode_h

#include <stdio.h>
#include <stdlib.h>

#ifdef TEST
#include <assert.h>
int* treenode_test_index;
void** treenode_test_ptrchecks;
#endif

typedef struct TreeNode {
    void* var;
    struct TreeNode* next;
    struct TreeNode* child;
    void (*destroy_var) (void *);
} TreeNode;


TreeNode* tnode_create(void *, void (*) (void *));

void tnode__free(TreeNode*);

void depth_first_for_each(TreeNode*, void (*) (TreeNode*));

void tnode_destroy(TreeNode*);

TreeNode* tnode_add_child(TreeNode*, void*, void (*) (void *));

void tnode_children_to_arr(TreeNode*, char* []);

#ifdef TEST
void tnode_set_ptrchecks(int* index, void** ptrchecks);
#endif


#endif
