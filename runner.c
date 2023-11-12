#include "runner.h"
#include "process.h"

struct state *init_context() {
    struct state *runner = (struct state *)malloc(sizeof(struct state));

    runner->running = 0;

    runner->proccesses = NULL;

    return runner;
}

struct process_group *read_input() {
    char *cmd = (char *)malloc(sizeof(char) * 256);
    char *exit_codes = (char *)malloc(sizeof(char) * 64);
    char *exit_signal = (char *)malloc(sizeof(char) * 32);
    char *alternative_stdout = (char *)malloc(sizeof(char) * 128);
    char *alternative_stdin = (char *)malloc(sizeof(char) * 128);
    char *cwd = (char *)malloc(sizeof(char) * 128);
    char *tmp = (char *)malloc(sizeof(char) * 16);

    int numprocs = 0;
    int autostart = 0;
    int restart_policy = 0;
    int initial_delay = 0;
    int restarts = 0;
    int graceful_period = 0;
    int permissions = 0;

    printf("Command: ");

    fgets(cmd, 256, stdin);
    cmd[strcspn(cmd, "\n")] = 0;

    printf("Number of processes: ");

    fgets(tmp, 16, stdin);
    numprocs = atoi(tmp);

    printf("Autostart: ");

    fgets(tmp, 16, stdin);
    autostart = atoi(tmp);

    printf("Restart policy: ");

    fgets(tmp, 16, stdin);
    restart_policy = atoi(tmp);

    printf("Exit codes: ");

    fgets(exit_codes, 32, stdin);
    exit_codes[strcspn(exit_codes, "\n")] = 0;

    printf("Initial delay: ");

    fgets(tmp, 16, stdin);
    initial_delay = atoi(tmp);

    printf("Restarts: ");

    fgets(tmp, 16, stdin);
    restarts = atoi(tmp);

    printf("Signal: ");

    fgets(exit_signal, 16, stdin);
    exit_signal[strcspn(exit_signal, "\n")] = 0;

    printf("Graceful period: ");

    fgets(tmp, 16, stdin);
    graceful_period = atoi(tmp);

    printf("Alternative stdout: ");

    fgets(alternative_stdout, 64, stdin);
    alternative_stdout[strcspn(alternative_stdout, "\n")] = 0;

    printf("Alternative stdin: ");

    fgets(alternative_stdin, 64, stdin);
    alternative_stdin[strcspn(alternative_stdin, "\n")] = 0;

    printf("Working dir: ");

    fgets(cwd, 128, stdin);
    cwd[strcspn(cwd, "\n")] = 0;

    printf("umask: ");

    fgets(tmp, 16, stdin);
    permissions = strtol(tmp, NULL, 8);

    struct process_group *group = init_process_group();

    group->restart_policy = restart_policy;

    group->permissions = permissions;

    group->max_numprocs = numprocs;
    group->autostart = autostart;
    group->initial_delay = initial_delay;
    group->graceful_period = graceful_period;
    group->max_restarts = restarts;

    group->cmd = cmd;
    group->exit_codes = exit_codes;
    group->exit_signal = exit_signal;
    group->alternative_stdout = alternative_stdout;
    group->alternative_stdin = alternative_stdin;
    group->cwd = cwd;

    return group;
}

void poll_status(struct state *state) {}

void sync_state(struct state *state) {}

void runner_loop() {
    struct state *state = init_context();

    while (state->running) {
        struct node_group *group = read_input();

        poll_status(state);

        sync_state(state);
    }
}

// void runner_loop(struct context *context) {
//     if (context == NULL) {
//         return;
//     }
//
//     mode_t mask;
//
//     int test = 0;
//
//     while (context->running) {
//         int numprocs;
//         int exit_code;
//         enum restart_policy restart_policy;
//         unsigned int permissions;
//         char *dir;
//         int retries;
//         struct process *process;
//
//         char **cmd = (char **)malloc(sizeof(char *) * 32);
//
//         for (int i = 0; i < 31; ++i) {
//             *(cmd + i) = (char *)malloc(sizeof(char) * 32);
//         }
//
//         cmd[2] = (char *)0;
//
//         if (test == 0) {
//             dir = (char *)malloc(sizeof(char) * 256);
//
//             scanf("%d %s %s %d %d %o %s %d", &exit_code, cmd[0], cmd[1], &numprocs,
//             &restart_policy,
//                   &permissions, dir, &retries);
//
//             test = 1;
//
//             for (int i = 0; i < numprocs; ++i) {
//                 int pid = fork();
//
//                 if (pid == 0) {
//                     umask(permissions);
//
//                     chdir(dir);
//
//                     execvp(cmd[0], cmd);
//                 } else {
//                     process = init_process(pid, cmd, numprocs, exit_code, restart_policy,
//                                            permissions, dir, retries);
//
//                     context->root = insert_into_avl_tree(context->root, process);
//                 }
//             }
//         }
//
//         int stat_lock;
//
//         int pid = waitpid(-1, &stat_lock, WNOHANG);
//
//         if (pid > 0) {
//             struct node *node = get_from_avl_tree(context->root, pid);
//
//             if (node) {
//                 process = node->process;
//             }
//
//             if (process->restart_policy == never) {
//                 printf("The process %d has finished sucessfully, restart policy never, so no "
//                        "reload...\n",
//                        pid);
//             } else if (process->restart_policy == always) {
//                 printf("The process %d finished, no matter the exit code the restart policy is "
//                        "always, restarting...\n",
//                        pid);
//
//                 pid = fork();
//
//                 if (pid == 0) {
//                     umask(process->permissions);
//
//                     chdir(process->dir);
//
//                     execvp(process->cmd[0], process->cmd);
//                 } else {
//                     context->root = insert_into_avl_tree(context->root, process);
//                 }
//             } else if (process->restart_policy == failure && process->exit_code != stat_lock) {
//                 printf("The process %d has failed, restarting...\n", pid);
//
//                 if (process->retries == 0) {
//                     printf("Max retries reached, the process will not be reloaded again...");
//                 }
//
//                 pid = fork();
//
//                 if (pid == 0) {
//                     umask(process->permissions);
//
//                     chdir(process->dir);
//
//                     execvp(process->cmd[0], process->cmd);
//                 } else {
//                     process->pid = pid;
//
//                     process->retries -= 1;
//
//                     context->root = insert_into_avl_tree(context->root, process);
//                 }
//             }
//         }
//     }
// }
