
#pragma once

#include "core/memory.h"
#include "core/list.h"

struct cfl_test_fixture {
    void (*setup)(struct cfl_test_fixture *);
    void (*teardown)(struct cfl_test_fixture *);
};

void cfl_test_fixture_setup(struct cfl_test_fixture *self);
void cfl_test_fixture_teardown(struct cfl_test_fixture *self);
