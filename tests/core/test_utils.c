
#include <test/test.h>

struct test_struct {
    int a;
    int b;
    int c;
};

CFL_TEST(cfl_containerof_returns_pointer_to_containing_structure) {
    struct test_struct test;
    int *b_ptr = &test.b;

    struct test_struct *container = containerof(b_ptr, struct test_struct, b);

    ASSERT(container == &test);
}

CFL_TEST_GROUP(utils) {
    CFL_RUN_TEST(cfl_containerof_returns_pointer_to_containing_structure);
}