
#include "fixture.h"

void cfl_test_fixture_setup(struct cfl_test_fixture *self) {
    self->setup(self);
}

void cfl_test_fixture_teardown(struct cfl_test_fixture *self) {
    self->teardown(self);
}

void cfl_test_fixture_list_init(struct cfl_test_fixture_list *self) {
    cfl_list_init(&self->list);
}

void cfl_test_fixture_list_done(struct cfl_test_fixture_list *self) {
    struct cfl_list_node *node;
    cfl_list_foreach(node, &self->list) {
        struct cfl_test_fixture *fixture = containerof(node, struct cfl_test_fixture, node);
        cfl_test_fixture_teardown(fixture);
    }
}

void cfl_test_fixture_list_add(struct cfl_test_fixture_list *self, struct cfl_test_fixture *fixture) {
    cfl_list_append(&self->list, &fixture->node);
    cfl_test_fixture_setup(fixture);
}
