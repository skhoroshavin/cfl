
#include <test/test.h>

struct test_teardown_log {
    char data[16];
    int size;
};

static void test_teardown_a(void *data) {
    struct test_teardown_log *log = (struct test_teardown_log *)data;
    log->data[log->size] = 'A';
    ++log->size;
}

static void test_teardown_b(void *data) {
    struct test_teardown_log *log = (struct test_teardown_log *)data;
    log->data[log->size] = 'B';
    ++log->size;
}

CFL_TEST(cfl_test_context_done_runs_teardown) {
    struct test_teardown_log teardown_log;
    memset(&teardown_log, 0, sizeof(teardown_log));

    struct cfl_test_context context;
    cfl_test_context_init(&context);
    cfl_test_context_add_teardown(&context, &teardown_log, test_teardown_a);
    cfl_test_context_done(&context);

    ASSERT_INT_EQ(teardown_log.size, 1);
    ASSERT_STR_EQ(teardown_log.data, "A");
}

CFL_TEST(cfl_test_context_done_runs_teardown_in_reverse_order) {
    struct test_teardown_log teardown_log;
    memset(&teardown_log, 0, sizeof(teardown_log));

    struct cfl_test_context context;
    cfl_test_context_init(&context);
    cfl_test_context_add_teardown(&context, &teardown_log, test_teardown_a);
    cfl_test_context_add_teardown(&context, &teardown_log, test_teardown_b);
    cfl_test_context_done(&context);

    ASSERT_INT_EQ(teardown_log.size, 2);
    ASSERT_STR_EQ(teardown_log.data, "BA");
}

CFL_TEST_GROUP(context) {
    CFL_RUN_TEST(cfl_test_context_done_runs_teardown);
    CFL_RUN_TEST(cfl_test_context_done_runs_teardown_in_reverse_order);
}
