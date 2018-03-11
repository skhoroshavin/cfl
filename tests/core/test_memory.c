
#include <test/test.h>
#include <stdlib.h>

static const unsigned test_data[] = {0xdeadbeef, 0xcafebabe, 0x8badf00d};

CFL_TEST(cfl_alloc_allocates_memory) {
    void *ptr = cfl_alloc(&cfl_default_allocator, 4);

    ASSERT_NOT_NULL(ptr);
    memset(ptr, 0, 4);

    cfl_free(&cfl_default_allocator, ptr);
}

CFL_TEST(cfl_realloc_returns_null_ptr_when_given_null_ptr_and_requested_zero_bytes) {
    void *ptr = cfl_realloc(&cfl_default_allocator, 0, 0);
    ASSERT_NULL(ptr);
}

CFL_TEST(cfl_realloc_allocates_memory_when_given_null_ptr_and_requested_some_bytes) {
    void *ptr = cfl_realloc(&cfl_default_allocator, 0, 4);

    ASSERT_NOT_NULL(ptr);
    memset(ptr, 0, 4);

    cfl_free(&cfl_default_allocator, ptr);
}

CFL_TEST(cfl_realloc_returns_null_ptr_when_given_non_null_ptr_and_requested_zero_bytes) {
    void *ptr = cfl_realloc(&cfl_default_allocator, 0, 4);
    ASSERT_NOT_NULL(ptr);

    ptr = cfl_realloc(&cfl_default_allocator, ptr, 0);
    ASSERT_NULL(ptr);
}

CFL_TEST(cfl_realloc_keeps_old_data_when_asked_for_more_memory) {
    void *ptr = cfl_realloc(&cfl_default_allocator, 0, sizeof(test_data));
    memcpy(ptr, &test_data, sizeof(test_data));
    ptr = cfl_realloc(&cfl_default_allocator, ptr, 2 * sizeof(test_data));

    ASSERT_NOT_NULL(ptr);
    ASSERT(memcmp(ptr, &test_data, sizeof(test_data)) == 0);

    cfl_free(&cfl_default_allocator, ptr);
}

CFL_TEST(cfl_realloc_keeps_old_data_when_asked_for_less_memory) {
    void *ptr = cfl_realloc(&cfl_default_allocator, 0, sizeof(test_data));
    memcpy(ptr, &test_data, sizeof(test_data));
    ptr = cfl_realloc(&cfl_default_allocator, ptr, sizeof(test_data) / 2);

    ASSERT_NOT_NULL(ptr);
    ASSERT(memcmp(ptr, &test_data, sizeof(test_data) / 2) == 0);

    cfl_free(&cfl_default_allocator, ptr);
}

CFL_TEST(cfl_format_creates_formatted_strings) {
    char *str = cfl_format(&cfl_default_allocator, "%s is %d", "The Answer", 42);

    ASSERT_NOT_NULL(str);
    ASSERT_STR_EQ(str, "The Answer is 42");

    cfl_free(&cfl_default_allocator, str);
}

CFL_TEST_GROUP(memory) {
    CFL_RUN_TEST(cfl_alloc_allocates_memory);
    CFL_RUN_TEST(cfl_realloc_returns_null_ptr_when_given_null_ptr_and_requested_zero_bytes);
    CFL_RUN_TEST(cfl_realloc_allocates_memory_when_given_null_ptr_and_requested_some_bytes);
    CFL_RUN_TEST(cfl_realloc_returns_null_ptr_when_given_non_null_ptr_and_requested_zero_bytes);
    CFL_RUN_TEST(cfl_realloc_keeps_old_data_when_asked_for_more_memory);
    CFL_RUN_TEST(cfl_realloc_keeps_old_data_when_asked_for_less_memory);

    CFL_RUN_TEST(cfl_format_creates_formatted_strings);
}
