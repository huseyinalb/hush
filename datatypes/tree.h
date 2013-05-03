
#ifndef hush_tree_h
#define hush_tree_h

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "treenode.h"

typedef struct Tree {
    TreeNode* root;
} Tree;

Tree* tree_create();

void tree_destroy(Tree*);

void children_to_arr(TreeNode*, int, int, char* []);

#endif
