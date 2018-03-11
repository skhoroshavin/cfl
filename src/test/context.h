
#pragma once

enum cfl_test_result { CFL_TEST_SUCCESS, CFL_TEST_FAIL };

typedef void (*cfl_test_teardown_fn)(void *);

struct cfl_test_teardown {
    void *data;
    cfl_test_teardown_fn teardown;
    struct cfl_test_teardown *next;
};

struct cfl_test_context {
    enum cfl_test_result result;
    char *error;
    struct cfl_test_teardown *teardown;
};

void cfl_test_context_init(struct cfl_test_context *self);
void cfl_test_context_done(struct cfl_test_context *self);
void cfl_test_context_add_teardown(struct cfl_test_context *self, void *data, cfl_test_teardown_fn teardown_fn);
