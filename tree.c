#include "taskmaster.h"

node_t *insert_into_avl_tree(node_t *root, process_t *process) {
    if (root == NULL) {
        node_t *node = (node_t *)malloc(sizeof(node_t));

        node->left = NULL;
        node->height = 0;
        node->process = process;
        node->right = NULL;

        root = node;
    } else if (process->pid > root->process->pid) {
        root->left = insert_into_avl_tree(root->left, process);

        root->height += 1;
    } else {
        root->right = insert_into_avl_tree(root->right, process);

        root->height += 1;
    }

    return root;
}

process_t *get_from_avl_tree(node_t *root, int pid) {
    if (root == NULL) {
        return NULL;
    }

    if (root->process->pid == pid) {
        return root->process;
    }

    if (root->process->pid > pid) {
        return get_from_avl_tree(root->left, pid);
    } else {
        return get_from_avl_tree(root->right, pid);
    }
}

node_t *delete_from_avl_tree(node_t *root, int pid) { return root; }
