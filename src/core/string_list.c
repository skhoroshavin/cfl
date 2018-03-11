
#include "string_list.h"
#include <string.h>

struct cfl_string_list_node {
    struct cfl_list_node node;
    char *text;
};

static struct cfl_string_list_node *cfl_string_list_node_create(const char *text) {
    size_t text_size = strlen(text) + 1;
    size_t size = sizeof(struct cfl_string_list_node) + text_size;

    struct cfl_string_list_node *node = (struct cfl_string_list_node *) cfl_alloc(&cfl_default_allocator, size);
    node->text = (char *) node + sizeof(struct cfl_string_list_node);
    memcpy(node->text, text, text_size);

    return node;
}

void cfl_string_list_init(struct cfl_string_list *self) {
    cfl_list_init(&self->list);
}

void cfl_string_list_done(struct cfl_string_list *self) {
    while (!cfl_list_is_empty(&self->list)) {
        struct cfl_list_node *list_node = self->list.head.next;
        cfl_list_node_remove(list_node);

        struct cfl_string_list_node *node = containerof(list_node, struct cfl_string_list_node, node);
        cfl_free(&cfl_default_allocator, node);
    }
}

int cfl_string_list_is_empty(const struct cfl_string_list *self) { return cfl_list_is_empty(&self->list); }

int cfl_string_list_contains(const struct cfl_string_list *self, const char *text) {
    struct cfl_list_node *list_node;
    cfl_list_foreach(list_node, &self->list) {
        struct cfl_string_list_node *node = containerof(list_node, struct cfl_string_list_node, node);
        if (strstr(node->text, text) != 0) return 1;
    }
    return 0;
}

void cfl_string_list_append(struct cfl_string_list *self, const char *text) {
    struct cfl_string_list_node *node = cfl_string_list_node_create(text);
    cfl_list_append(&self->list, &node->node);
}
