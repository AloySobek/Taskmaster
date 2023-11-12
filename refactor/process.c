#include "state.h"

struct process_group *init_process_group() {
    struct process_group *group = (struct process_group *)malloc(sizeof(struct process_group));

    group->restart_policy = RESTART_POLICY_NEVER;
    group->permissions = 0;
    group->numprocs = 0;
    group->max_numprocs = 0;
    group->autostart = 0;
    group->initial_delay = 0;
    group->graceful_period = 0;

    group->cmd = NULL;
    group->exit_codes = NULL;
    group->exit_signal = NULL;
    group->alternative_stdout = NULL;
    group->alternative_stdin = NULL;
    group->cwd = NULL;

    return group;
}

struct process *init_process() {
    struct process *process = (struct process *)malloc(sizeof(struct process));

    process->status = STATUS_NONE;
    process->pid = 0;
    process->last_exit_code = 0;
    process->restarts = 0;

    process->group = NULL;

    return process;
}
