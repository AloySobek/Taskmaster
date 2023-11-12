#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "stdlib.h"

struct node {
    int height;

    void *data;

    struct node *left;
    struct node *right;
};

struct node *insert_into_avl_tree(struct node *node, void *data, int (*cmp)(void *a, void *b));
struct node *get_from_avl_tree(struct node *node, void *data, int (*cmp)(void *a, void *b));
struct node *remove_from_avl_tree(struct node *node, void *data, int (*cmp)(void *a, void *b));

#endif
