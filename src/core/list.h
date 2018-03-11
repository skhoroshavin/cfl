
#pragma once

#include "utils.h"

struct cfl_list_node {
    struct cfl_list_node *next;
    struct cfl_list_node *prev;
};

struct cfl_list {
    struct cfl_list_node head;
};

#define cfl_list_foreach(node, list) \
    for(node = (list)->head.next; node != &((list)->head); node = node->next)

/*
 * List based API
 */

void cfl_list_init(struct cfl_list *self);

int cfl_list_is_empty(const struct cfl_list *self);
int cfl_list_size(const struct cfl_list *self);

void cfl_list_append(struct cfl_list *self, struct cfl_list_node *node);
void cfl_list_prepend(struct cfl_list *self, struct cfl_list_node *node);

/*
 * Node based API
 */

void cfl_list_node_remove(struct cfl_list_node *self);
