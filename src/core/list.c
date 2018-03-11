
#include "list.h"

static void cfl_list_node_insert_after(struct cfl_list_node *self, struct cfl_list_node *other) {
    other->next = self->next;
    other->prev = self;

    self->next->prev = other;
    self->next = other;
}

static void cfl_list_node_insert_before(struct cfl_list_node *self, struct cfl_list_node *other) {
    other->prev = self->prev;
    other->next = self;

    self->prev->next = other;
    self->prev = other;
}

/*
 * List based API
 */

void cfl_list_init(struct cfl_list *self) {
    self->head.prev = self->head.next = &self->head;
}

int cfl_list_is_empty(const struct cfl_list *self) {
    return self->head.next == &self->head;
}

int cfl_list_size(const struct cfl_list *self) {
    int result = 0;
    struct cfl_list_node *node;
    cfl_list_foreach(node, self) {
        ++result;
    }
    return result;
}

void cfl_list_append(struct cfl_list *self, struct cfl_list_node *node) {
    cfl_list_node_insert_before(&self->head, node);
}

void cfl_list_prepend(struct cfl_list *self, struct cfl_list_node *node) {
    cfl_list_node_insert_after(&self->head, node);
}

/*
 * Node based API
 */

void cfl_list_node_remove(struct cfl_list_node *self) {
    self->prev->next = self->next;
    self->next->prev = self->prev;
}
