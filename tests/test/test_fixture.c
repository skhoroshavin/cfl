
#include "../test_common.h"

struct test_fixture {
    struct cfl_test_fixture base;
    struct cfl_string_list *log;
    const char *name;
};

static void test_setup(struct cfl_test_fixture *base) {
    struct test_fixture *self = (struct test_fixture *) base;
    cfl_string_list_printf(self->log, "Setup: %s", self->name);
}

static void test_teardown(struct cfl_test_fixture *base) {
    struct test_fixture *self = (struct test_fixture *) base;
    cfl_string_list_printf(self->log, "Teardown: %s", self->name);
}

static void test_fixture_init(struct test_fixture *self, const char *name, struct cfl_string_list *log) {
    self->base.setup = test_setup;
    self->base.teardown = test_teardown;
    self->name = name;
    self->log = log;
}

CFL_TEST(cfl_test_fixture_list_is_initialized_as_empty) {
    GIVEN_FIXTURE_LIST(fixtures);

    ASSERT(cfl_list_is_empty(&fixtures->list));
}

CFL_TEST(cfl_test_fixture_list_calls_setup_when_adding_fixture_and_teardown_when_destroyed) {
    GIVEN_STRING_LIST(log);

    struct cfl_test_fixture_list fixtures;
    cfl_test_fixture_list_init(&fixtures);

    struct test_fixture fixture;
    test_fixture_init(&fixture, "Hello", log);
    ASSERT(!cfl_string_list_contains(log, "Setup: Hello"));
    ASSERT(!cfl_string_list_contains(log, "Teardown: Hello"));

    cfl_test_fixture_list_add(&fixtures, &fixture.base);
    ASSERT(cfl_string_list_contains(log, "Setup: Hello"));
    ASSERT(!cfl_string_list_contains(log, "Teardown: Hello"));

    cfl_test_fixture_list_done(&fixtures);
    ASSERT(cfl_string_list_contains(log, "Setup: Hello"));
    ASSERT(cfl_string_list_contains(log, "Teardown: Hello"));
}

CFL_TEST_GROUP(fixture) {
    CFL_RUN_TEST(cfl_test_fixture_list_is_initialized_as_empty);
    CFL_RUN_TEST(cfl_test_fixture_list_calls_setup_when_adding_fixture_and_teardown_when_destroyed);
}