
#include "context.h"
#include "core/memory.h"

#include <stdlib.h>

void cfl_test_context_init(struct cfl_test_context *self) {
    self->result = CFL_TEST_SUCCESS;
    self->error = 0;
    self->teardown = 0;
}

void cfl_test_context_done(struct cfl_test_context *self) {
    while (self->teardown) {
        struct cfl_test_teardown *teardown = self->teardown;
        self->teardown = teardown->next;

        teardown->teardown(teardown->data);
        cfl_free(&cfl_default_allocator, teardown);
    }

    if (self->error) {
        cfl_free(&cfl_default_allocator, self->error);
        self->error = 0;
    }
}

void cfl_test_context_add_teardown(struct cfl_test_context *self, void *data, cfl_test_teardown_fn teardown_fn) {
    struct cfl_test_teardown *teardown = cfl_alloc_type(&cfl_default_allocator, struct cfl_test_teardown);
    teardown->data = data;
    teardown->teardown = teardown_fn;
    teardown->next = self->teardown;
    self->teardown = teardown;
}
