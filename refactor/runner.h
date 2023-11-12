#ifndef RUNNER_H
#define RUNNER_H

#include <stdio.h>
#include <string.h>

#include "avl_tree.h"

struct state {
    char running;

    struct node *proccesses;
};

struct state *init_state();

void runner_loop();

#endif
