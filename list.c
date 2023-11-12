#include "taskmaster.h"

struct list_node *create_list_node(struct process *process) {
    struct list_node *node = (struct list_node *)malloc(sizeof(struct list_node));

    node->process = process;

    node->next = node;
    node->prev = node;

    return node;
}

struct list_node *list_insert(struct list_node *node, struct process *process) {
    if (node == NULL) {
        return create_list_node(process);
    }

    struct list_node *new = create_list_node(process);

    new->prev = node->prev;
    new->next = node;

    node->prev->next = new;
    node->prev = new;

    return node;
}

void *list_free(struct list_node *node) {
    if (node == NULL) {
        return NULL;
    }

    struct list_node *iter = node;

    do {
        struct list_node *next = iter->next;

        free(iter);

        iter = next;
    } while (iter != node);

    return NULL;
}
