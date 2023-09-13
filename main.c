#include "taskmaster.h"

process_t *init_process(int pid, char **cmd, int numprocs, int exit_code,
                        enum restart_policy_e restart_policy, mode_t permissions, char *dir) {
    process_t *process = (process_t *)malloc(sizeof(process_t));

    process->pid = pid;
    process->cmd = cmd;
    process->numprocs = numprocs;
    process->exit_code = exit_code;
    process->restart_policy = restart_policy;
    process->permissions = permissions;
    process->dir = dir;

    return process;
}

runner_context_t *init_runner_context() {
    runner_context_t *runner = (runner_context_t *)malloc(sizeof(runner_context_t));

    runner->processes = (process_t **)malloc(sizeof(process_t *) * 131072);
    runner->running = 1;

    return runner;
}

void destroy_runner_context(runner_context_t *context) {
    context->running = 0;

    free(context);
}

void loop(runner_context_t *context) {
    if (context == NULL) {
        return;
    }

    mode_t mask;

    int test = 0;

    while (context->running) {
        int numprocs;
        int exit_code;
        enum restart_policy_e restart_policy;
        unsigned int permissions;
        char *dir;
        process_t *process;

        char **cmd = (char **)malloc(sizeof(char *) * 32);

        for (int i = 0; i < 31; ++i) {
            *(cmd + i) = (char *)malloc(sizeof(char) * 32);
        }

        cmd[2] = (char *)0;

        if (test == 0) {
            dir = (char *)malloc(sizeof(char) * 256);

            scanf("%d %s %s %d %d %o %s", &exit_code, cmd[0], cmd[1], &numprocs, &restart_policy,
                  &permissions, dir);

            test = 1;

            for (int i = 0; i < numprocs; ++i) {
                int pid = fork();

                if (pid == 0) {
                    umask(permissions);

                    chdir(dir);

                    execvp(cmd[0], cmd);
                } else {
                    process = init_process(pid, cmd, numprocs, exit_code, restart_policy,
                                           permissions, dir);

                    context->processes[pid] = process;
                }
            }
        }

        int stat_lock;

        int pid = waitpid(-1, &stat_lock, WNOHANG);

        if (pid > 0) {
            process = context->processes[pid];

            if (process->restart_policy == never) {
                printf("The process %d has finished sucessfully, restart policy never, so no "
                       "reload...\n",
                       pid);
            } else if (process->restart_policy == always) {
                printf("The process %d finished, no matter the exit code the restart policy is "
                       "always, restarting...\n",
                       pid);

                pid = fork();

                if (pid == 0) {
                    umask(process->permissions);

                    chdir(process->dir);

                    execvp(process->cmd[0], process->cmd);
                } else {
                    context->processes[pid] = process;
                }
            } else if (process->restart_policy == failure && process->exit_code != stat_lock) {
                printf("The process %d has failed, restarting...\n", pid);

                pid = fork();

                if (pid == 0) {
                    umask(process->permissions);

                    chdir(process->dir);

                    execvp(process->cmd[0], process->cmd);
                } else {
                    context->processes[pid] = process;
                }
            }
        }
    }
}

int main() {
    // runner_context_t *context = init_runner_context();

    // loop(context);

    // destroy_runner_context(context);

    process_t *process = init_process(0, NULL, 0, 0, never, 0, NULL);
    process_t *process1 = init_process(1, NULL, 0, 0, never, 0, NULL);
    process_t *process2 = init_process(2, NULL, 0, 0, never, 0, NULL);
    process_t *process3 = init_process(3, NULL, 0, 0, never, 0, NULL);
    process_t *process4 = init_process(4, NULL, 0, 0, never, 0, NULL);
    process_t *process5 = init_process(5, NULL, 0, 0, never, 0, NULL);
    process_t *process6 = init_process(6, NULL, 0, 0, never, 0, NULL);
    process_t *process7 = init_process(7, NULL, 0, 0, never, 0, NULL);

    node_t *root = insert_into_avl_tree(NULL, process);

    root = insert_into_avl_tree(root, process1);
    root = insert_into_avl_tree(root, process2);
    root = insert_into_avl_tree(root, process3);
    root = insert_into_avl_tree(root, process4);
    root = insert_into_avl_tree(root, process5);
    root = insert_into_avl_tree(root, process6);
    root = insert_into_avl_tree(root, process7);

    printf("Here is your height: %d\n And your balance factor: %d\n", root->height,
           (root->left ? root->left->height : 0) - (root->right ? root->right->height : 0));

    return (0);
}
