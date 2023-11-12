#include "avl_tree.h"

int max(int a, int b) { return a > b ? a : b; }

int get_height(struct node *node) {
    if (node == NULL) {
        return 0;
    }

    return node->height;
}

int get_balance_factor(struct node *node) {
    return get_height(node->left) - get_height(node->right);
}

struct node *create_node(void *data) {
    struct node *node = (struct node *)malloc(sizeof(struct node));

    node->height = 1;

    node->data = data;

    node->left = NULL;
    node->right = NULL;

    return node;
}

struct node *left_rotation(struct node *node) {
    struct node *right = node->right;
    struct node *left = right->left;

    right->left = node;
    node->right = left;

    node->height = max(get_height(node->left), get_height(node->right)) + 1;
    right->height = max(get_height(right->left), get_height(right->right)) + 1;

    return right;
}

struct node *right_rotation(struct node *node) {
    struct node *left = node->left;
    struct node *right = left->right;

    left->right = node;
    node->left = right;

    node->height = max(get_height(node->left), get_height(node->right)) + 1;
    left->height = max(get_height(left->left), get_height(left->right)) + 1;

    return left;
}

struct node *insert_into_avl_tree(struct node *node, void *data, int (*cmp)(void *a, void *b)) {
    if (node == NULL) {
        return create_node(data);
    } else if (cmp(data, node->data) < 0) {
        node->left = insert_into_avl_tree(node->left, data, cmp);
    } else if (cmp(data, node->data) > 0) {
        node->right = insert_into_avl_tree(node->right, data, cmp);
    } else {
        // TODO: WARNING, potential leak, data has been replaced but the original value not returned
        // so there is no way to free the memory
        node->data = data;

        return node;
    }

    node->height = max(get_height(node->left), get_height(node->right)) + 1;

    int balance_factor = get_balance_factor(node);

    if (balance_factor > 1) {
        if (node->left->left) {
            return right_rotation(node);
        } else {
            node->left = left_rotation(node->left);

            return right_rotation(node);
        }
    } else if (balance_factor < -1) {
        if (node->right->right) {
            return left_rotation(node);
        } else {
            node->right = right_rotation(node->right);

            return left_rotation(node);
        }
    }

    return node;
}

struct node *get_from_avl_tree(struct node *node, void *data, int (*cmp)(void *a, void *b)) {
    if (node == NULL) {
        return NULL;
    }

    if (cmp(data, node->data) == 0) {
        return node;
    } else if (cmp(data, node->data) < 0) {
        return get_from_avl_tree(node->left, data, cmp);
    } else {
        return get_from_avl_tree(node->right, data, cmp);
    }
}

struct node *remove_from_avl_tree(struct node *node, void *data, int (*cmp)(void *a, void *b)) {
    // TODO: Implement deletion later
    return node;
}
