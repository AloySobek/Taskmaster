#ifndef TASKMASTER_H
#define TASKMASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

enum restart_policy_e {
    never = 0,
    always = 1,
    failure = 2,
};

typedef struct process_t {
    int pid;
    char **cmd;
    int numprocs;
    int exit_code;
    enum restart_policy_e restart_policy;
    mode_t permissions;
    char *dir;
} process_t;

typedef struct runner_context_s {
    process_t **processes;
    char running;
} runner_context_t;

typedef struct node_s {
    int height;

    struct node_s *right;
    struct node_s *left;

    process_t *process;
} node_t;

node_t *insert_into_avl_tree(node_t *root, process_t *process);
process_t *get_from_avl_tree(node_t *root, int pid);
node_t *delete_from_avl_tree(node_t *root, int pid);

#endif
