
#pragma once

#include <test/test.h>

/*
 * String list fixture
 */

void cfl_string_list_teardown(struct cfl_string_list *list);

#define GIVEN_STRING_LIST(name)                                                                    \
    struct cfl_string_list *name = cfl_alloc_type(&cfl_default_allocator, struct cfl_string_list); \
    cfl_string_list_init(name);                                                                    \
    CFL_ADD_TEARDOWN(name, cfl_string_list_teardown);

/*
 * Buffer logger fixture
 */

void cfl_buffer_logger_teardown(struct cfl_buffer_logger *logger);

#define GIVEN_BUFFER_LOGGER(name)                                                                      \
    struct cfl_buffer_logger *name = cfl_alloc_type(&cfl_default_allocator, struct cfl_buffer_logger); \
    cfl_buffer_logger_init(name);                                                                      \
    CFL_ADD_TEARDOWN(name, cfl_buffer_logger_teardown);

/*
 * Fixture list fixture :)
 */

void cfl_test_fixture_list_teardown(struct cfl_test_fixture_list *list);

#define GIVEN_FIXTURE_LIST(name)                                                                               \
    struct cfl_test_fixture_list *name = cfl_alloc_type(&cfl_default_allocator, struct cfl_test_fixture_list); \
    cfl_test_fixture_list_init(name);                                                                          \
    CFL_ADD_TEARDOWN(name, cfl_test_fixture_list_teardown);

/*
 * Context fixture
 */

void cfl_test_context_teardown(struct cfl_test_context *context);

#define GIVEN_CONTEXT(name)                                                                \
    struct cfl_test_context *name = cfl_alloc_type(&cfl_default_allocator, struct cfl_test_context); \
    cfl_test_context_init(name);                                                                \
    CFL_ADD_TEARDOWN(name, cfl_test_context_teardown);
