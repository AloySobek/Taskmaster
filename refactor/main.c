#include <stdio.h>

#include "avl_tree.h"

int cmp(void *a, void *b) {
    if (*((int *)a) < *((int *)b)) {
        return -1;
    } else if (*((int *)a) == *((int *)b)) {
        return 0;
    } else {
        return 1;
    }
}

void print_tree(struct node *node, int height) {
    if (node == NULL) {
        return;
    }

    print_tree(node->right, height + 1);

    printf("% *d\n", height * 3, *(int *)node->data);

    print_tree(node->left, height + 1);
}

int main() {
    int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    struct node *root = NULL;

    for (int i = 0; i < 10; ++i) {
        root = insert_into_avl_tree(root, data + i, cmp);
    }

    print_tree(root, 0);

    printf("---------------\n");

    print_tree(root, 0);

    // printf("Here we go: %d\n", *(int *)get_from_avl_tree(root, data + 7, cmp)->data);

    return 0;
}
