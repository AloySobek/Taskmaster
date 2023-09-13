#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#include "process.h"

// Double linked circular list

typedef struct node_s {
    struct node_s *next;

    process_t *process;

    struct node_s *prev;
} node_t;

node_t *init_list(process_t *process);
node_t *append_to_list(node_t *head, process_t *process);
node_t *remove_from_list(node_t *head, process_t *process);
node_t *destroy_list();

#endif
