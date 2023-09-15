#ifndef TASKMASTER_H
#define TASKMASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

enum process_status {
    none = 0,
    starting = 1,
    running = 2,
    stopping = 3,
    stopped = 4,
    failed = 5,

    process_status_max
};

enum restart_policy {
    never = 0,
    always = 1,
    failure = 2,

    restart_policy_max
};

struct process {
    enum restart_policy restart_policy;
    enum process_status status;

    mode_t permissions;

    int pid;
    int numprocs;
    int max_numprocs;
    int autostart;
    int initial_delay;
    int restarts;
    int graceful_period;
    int last_exit_code;

    int *exit_codes;

    char *cmd;
    char *exit_signal;
    char *alternative_stdout;
    char *alternative_stdin;
    char *cwd;
};

struct node {
    int height;

    struct node *right;
    struct node *left;

    struct process *process;
};

struct context {
    struct node *root;

    char running;
};

struct node *insert_into_avl_tree(struct node *node, struct process *process);
struct node *get_from_avl_tree(struct node *node, int pid);

struct context *init_context();
void runner_loop();

#endif
