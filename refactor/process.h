#ifndef PROCESS_H
#define PROCESS_H

#include <stdlib.h>
#include <sys/stat.h>

enum restart_policy {
    RESTART_POLICY_NEVER,
    RESTART_POLICY_ALWAYS,
    RESTART_POLICY_FAILURE,

    RESTART_POLICY_MAX
};

enum status {
    STATUS_NONE,
    STATUS_STARTING,
    STATUS_RUNNING,
    STATUS_STOPPING,
    STATUS_STOPPED,
    STATUS_FAILED,

    STATUS_MAX
};

struct process_group {
    enum restart_policy restart_policy;

    mode_t permissions;

    int numprocs;
    int max_numprocs;
    int autostart;
    int initial_delay;
    int graceful_period;
    int max_restarts;

    char *cmd;
    char *exit_codes;
    char *exit_signal;
    char *alternative_stdout;
    char *alternative_stdin;
    char *cwd;
};

struct process {
    enum status status;

    int pid;
    int last_exit_code;
    int restarts;

    struct process_group *group;
};

struct process_group *init_process_group();

struct process *init_process();

#endif
