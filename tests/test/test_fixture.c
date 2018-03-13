
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

CFL_TEST(cfl_test_fixture_correctly_calls_virtual_functions) {
    GIVEN_STRING_LIST(log);

    struct test_fixture fixture;
    fixture.base.setup = test_setup;
    fixture.base.teardown = test_teardown;
    fixture.log = log;
    fixture.name = "Hello";

    cfl_test_fixture_setup(&fixture.base);
    cfl_test_fixture_teardown(&fixture.base);

    ASSERT(cfl_string_list_contains(log, "Setup: Hello"));
    ASSERT(cfl_string_list_contains(log, "Teardown: Hello"));
}

CFL_TEST_GROUP(fixture) {
    CFL_RUN_TEST(cfl_test_fixture_correctly_calls_virtual_functions);
}