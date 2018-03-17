
#pragma once

#include "core/memory.h"
#include "core/list.h"

struct cfl_test_fixture {
    void (*setup)(struct cfl_test_fixture *);
    void (*teardown)(struct cfl_test_fixture *);
    struct cfl_list_node node;
};

void cfl_test_fixture_setup(struct cfl_test_fixture *self);
void cfl_test_fixture_teardown(struct cfl_test_fixture *self);

struct cfl_test_fixture_list {
    struct cfl_list list;
};

void cfl_test_fixture_list_init(struct cfl_test_fixture_list *self);
void cfl_test_fixture_list_done(struct cfl_test_fixture_list *self);

void cfl_test_fixture_list_add(struct cfl_test_fixture_list *self, struct cfl_test_fixture *fixture);
