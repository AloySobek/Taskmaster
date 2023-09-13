#include "list.h"

node_t *init_list(process_t *process) {
    node_t *node = (node_t *)malloc(sizeof(node_t));

    node->next = node;
    node->process = process;
    node->prev = node;

    return node;
}

node_t *append_to_list(node_t *head, process_t *process) {
    if (head == (void *)0) {
        return head;
    }

    node_t *node = (node_t *)malloc(sizeof(node_t));

    node->next = head;
    node->process = process;
    node->prev = head->prev;

    head->prev->next = node;
    head->prev = node;

    return head;
}

node_t *remove_from_list(node_t *head, process_t *process) {
    if (head == (void *)0) {
        return head;
    }

    if (head->process == process) {
    }

    node_t *iter = head;

    return head;
}
