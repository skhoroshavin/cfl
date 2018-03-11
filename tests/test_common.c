
#include "test_common.h"

void cfl_string_list_teardown(struct cfl_string_list *list) {
    cfl_string_list_done(list);
    cfl_free(&cfl_default_allocator, list);
}

void cfl_buffer_logger_teardown(struct cfl_buffer_logger *logger) {
    cfl_buffer_logger_done(logger);
    cfl_free(&cfl_default_allocator, logger);
}

void cfl_test_context_teardown(struct cfl_test_context *context) {
    cfl_test_context_done(context);
    cfl_free(&cfl_default_allocator, context);
}
