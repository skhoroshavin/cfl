
#include "fixture.h"

void cfl_test_fixture_setup(struct cfl_test_fixture *self) {
    self->setup(self);
}

void cfl_test_fixture_teardown(struct cfl_test_fixture *self) {
    self->teardown(self);
}
