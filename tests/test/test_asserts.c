
#include "../test_common.h"

/*
 * Utility macros
 */

#define TEST_PASS(name, expr)                              \
    CFL_TEST(aux_##name) { expr; }                             \
    CFL_TEST(name) {                                           \
        GIVEN_CONTEXT(context);                            \
        aux_##name(context);                               \
        ASSERT_INT(context->result, ==, CFL_TEST_SUCCESS); \
        ASSERT_NULL(context->error);                       \
    }

#define TEST_FAIL(name, expr, msg)                      \
    CFL_TEST(aux_##name) { expr; }                          \
    CFL_TEST(name) {                                        \
        GIVEN_CONTEXT(context);                         \
        aux_##name(context);                            \
        ASSERT_INT(context->result, ==, CFL_TEST_FAIL); \
        ASSERT_NOT_NULL(context->error);                \
        ASSERT_STR_EQ(context->error, msg);             \
    }

#define TEST_ASSERT(name, pass_expr, fail_expr, msg)                                  \
    TEST_PASS(cfl_passing_##name##_marks_test_as_successful, pass_expr)               \
    TEST_FAIL(cfl_passing_##name##_continues_test, pass_expr; FAIL("Error"), "Error") \
    TEST_FAIL(cfl_failing_##name##_marks_test_as_failed_and_saves_error_message, fail_expr, msg)

#define RUN_TEST_ASSERT(name)                                                        \
    do {                                                                             \
        CFL_RUN_TEST(cfl_passing_##name##_marks_test_as_successful);                     \
        CFL_RUN_TEST(cfl_passing_##name##_continues_test);                               \
        CFL_RUN_TEST(cfl_failing_##name##_marks_test_as_failed_and_saves_error_message); \
    } while (0)

/*
 * Basic tests
 */

TEST_PASS(cfl_pass_marks_test_as_successful, PASS())
TEST_PASS(cfl_pass_marks_test_as_successful_and_quits_test, PASS(); FAIL("Error message"))

TEST_FAIL(cfl_fail_marks_test_as_failed_and_saves_simple_message, FAIL("Simple message"), "Simple message")
TEST_FAIL(cfl_fail_marks_test_as_failed_and_saves_formatted_message, FAIL("Formatted %s %d", "message", 42),
          "Formatted message 42")

/*
 * Unary asserts
 */

TEST_ASSERT(assert, ASSERT(2 * 2 == 4), ASSERT(2 * 2 == 5), "Assertion failed: 2 * 2 == 5")

static void *null_ptr = 0;
static void *not_null_ptr = (void *)(size_t)0xdeadbeef;
TEST_ASSERT(assert_null, ASSERT_NULL(null_ptr), ASSERT_NULL(not_null_ptr), "Assertion failed: not_null_ptr is not null")
TEST_ASSERT(assert_not_null, ASSERT_NOT_NULL(not_null_ptr), ASSERT_NOT_NULL(null_ptr),
            "Assertion failed: null_ptr is null")

/*
 * Integer asserts
 */

TEST_ASSERT(assert_int_eq, ASSERT_INT_EQ(2 * 2, 4), ASSERT_INT_EQ(2 * 2, 5),
            "Assertion failed: 2 * 2 == 5 (expanded to 4 == 5)")
TEST_ASSERT(assert_int_less, ASSERT_INT_LESS(2 * 2, 5), ASSERT_INT_LESS(2 * 2, 3),
            "Assertion failed: 2 * 2 < 3 (expanded to 4 < 3)")

/*
 * String asserts
 */

static const char *test_str = "Hello";
TEST_ASSERT(assert_str_eq, ASSERT_STR_EQ(test_str, "Hello"), ASSERT_STR_EQ(test_str, "World"),
            "Assertion failed: test_str == \"World\" (expanded to \"Hello\" == \"World\")")
TEST_ASSERT(assert_str_contains, ASSERT_STR_CONTAINS(test_str, "el"), ASSERT_STR_CONTAINS(test_str, "ol"),
            "Assertion failed: test_str (expanded to \"Hello\") contains \"ol\" (expanded to \"ol\")")

CFL_TEST_GROUP(asserts) {
    CFL_RUN_TEST(cfl_pass_marks_test_as_successful);
    CFL_RUN_TEST(cfl_pass_marks_test_as_successful_and_quits_test);
    CFL_RUN_TEST(cfl_fail_marks_test_as_failed_and_saves_simple_message);
    CFL_RUN_TEST(cfl_fail_marks_test_as_failed_and_saves_formatted_message);

    RUN_TEST_ASSERT(assert);
    RUN_TEST_ASSERT(assert_null);
    RUN_TEST_ASSERT(assert_not_null);

    RUN_TEST_ASSERT(assert_int_eq);
    RUN_TEST_ASSERT(assert_int_less);

    RUN_TEST_ASSERT(assert_str_eq);
    RUN_TEST_ASSERT(assert_str_contains);
}
