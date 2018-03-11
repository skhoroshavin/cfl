
#include "../test_common.h"

CFL_TEST(cfl_passing_test) { PASS(); }

CFL_TEST(cfl_failing_test) { FAIL("Failure message"); }

/*
 * Engine tests
 */

static void cfl_test_engine_teardown(struct cfl_test_engine *engine) {
    cfl_test_engine_done(engine);
    cfl_free(&cfl_default_allocator, engine);
}

#define GIVEN_ENGINE(name, logger)                                                       \
    struct cfl_test_engine *name = cfl_alloc_type(&cfl_default_allocator, struct cfl_test_engine); \
    cfl_test_engine_init(name, logger);                                                       \
    CFL_ADD_TEARDOWN(name, cfl_test_engine_teardown);

CFL_TEST(cfl_test_engine_run_test_keeps_clean_status_and_logs_nothing_on_success) {
    GIVEN_BUFFER_LOGGER(logger);
    GIVEN_ENGINE(engine, &logger->base);

    cfl_test_engine_run_test(engine, "Passing test", cfl_passing_test);
    ASSERT_INT_EQ(engine->failed_tests, 0);
    ASSERT(cfl_string_list_is_empty(&logger->log));
}

CFL_TEST(cfl_test_engine_run_test_raises_failure_and_logs_test_name_and_error_on_failure) {
    GIVEN_BUFFER_LOGGER(logger);
    GIVEN_ENGINE(engine, &logger->base);

    cfl_test_engine_run_test(engine, "Failing test", cfl_failing_test);
    ASSERT_INT_GREATER(engine->failed_tests, 0);
    ASSERT(!cfl_string_list_is_empty(&logger->log));
    ASSERT(cfl_string_list_contains(&logger->log, "Failing test"));
    ASSERT(cfl_string_list_contains(&logger->log, "Failure message"));
}

CFL_TEST_GROUP(engine) {
    CFL_RUN_TEST(cfl_test_engine_run_test_keeps_clean_status_and_logs_nothing_on_success);
    CFL_RUN_TEST(cfl_test_engine_run_test_raises_failure_and_logs_test_name_and_error_on_failure);
}

/*
 * Main tests
 */

static void cfl_test_main_without_tests(struct cfl_test_engine *_engine) { cfl_unused(_engine); }

CFL_TEST(cfl_test_main_returns_zero_and_reports_passing_tests_without_tests) {
    GIVEN_BUFFER_LOGGER(logger);

    int return_code = cfl_test_main(0, 0, &logger->base, cfl_test_main_without_tests);

    ASSERT_INT_EQ(return_code, 0);
    ASSERT(!cfl_string_list_is_empty(&logger->log));
    ASSERT(cfl_string_list_contains(&logger->log, "All 0 tests passed"));
}

static void cfl_test_main_with_one_passing_test(struct cfl_test_engine *_engine) { CFL_RUN_TEST(cfl_passing_test); }

CFL_TEST(cfl_test_main_returns_zero_and_reports_passing_tests_with_passing_test) {
    GIVEN_BUFFER_LOGGER(logger);

    int return_code = cfl_test_main(0, 0, &logger->base, cfl_test_main_with_one_passing_test);

    ASSERT_INT_EQ(return_code, 0);
    ASSERT(!cfl_string_list_is_empty(&logger->log));
    ASSERT(cfl_string_list_contains(&logger->log, "All 1 tests passed"));
}

static void cfl_test_main_with_one_failing_test(struct cfl_test_engine *_engine) { CFL_RUN_TEST(cfl_failing_test); }

CFL_TEST(cfl_test_main_returns_one_and_reports_failing_tests_with_failing_test) {
    GIVEN_BUFFER_LOGGER(logger);

    int return_code = cfl_test_main(0, 0, &logger->base, cfl_test_main_with_one_failing_test);

    ASSERT_INT_EQ(return_code, 1);
    ASSERT(!cfl_string_list_is_empty(&logger->log));
    ASSERT(cfl_string_list_contains(&logger->log, "Failed 1 tests from 1 total tests"));
}

static void cfl_test_main_with_one_failing_test_followed_by_passing_test(struct cfl_test_engine *_engine) {
    CFL_RUN_TEST(cfl_failing_test);
    CFL_RUN_TEST(cfl_passing_test);
}

CFL_TEST(cfl_test_main_returns_one_and_reports_failing_tests_with_failing_test_followed_by_passing_test) {
    GIVEN_BUFFER_LOGGER(logger);

    int return_code = cfl_test_main(0, 0, &logger->base, cfl_test_main_with_one_failing_test_followed_by_passing_test);

    ASSERT_INT_EQ(return_code, 1);
    ASSERT(!cfl_string_list_is_empty(&logger->log));
    ASSERT(cfl_string_list_contains(&logger->log, "Failed 1 tests from 2 total tests"));
}

CFL_TEST_GROUP(main) {
    CFL_RUN_TEST(cfl_test_main_returns_zero_and_reports_passing_tests_without_tests);
    CFL_RUN_TEST(cfl_test_main_returns_zero_and_reports_passing_tests_with_passing_test);
    CFL_RUN_TEST(cfl_test_main_returns_one_and_reports_failing_tests_with_failing_test);
    CFL_RUN_TEST(cfl_test_main_returns_one_and_reports_failing_tests_with_failing_test_followed_by_passing_test);
}
