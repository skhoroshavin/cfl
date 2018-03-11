
#include "../test_common.h"

CFL_TEST(cfl_buffer_logger_has_empty_buffer_after_creation) {
    GIVEN_BUFFER_LOGGER(logger);

    ASSERT(cfl_string_list_is_empty(&logger->log));
}

CFL_TEST(cfl_buffer_logger_has_message_after_logging) {
    GIVEN_BUFFER_LOGGER(logger);

    cfl_logger_printf(&logger->base, "Hello");

    ASSERT(!cfl_string_list_is_empty(&logger->log));
    ASSERT(cfl_string_list_contains(&logger->log, "Hello"));
}

CFL_TEST(cfl_buffer_logger_has_all_messages_after_logging) {
    GIVEN_BUFFER_LOGGER(logger);

    cfl_logger_printf(&logger->base, "Hello");
    cfl_logger_printf(&logger->base, "world");

    ASSERT(!cfl_string_list_is_empty(&logger->log));
    ASSERT(cfl_string_list_contains(&logger->log, "Hello"));
    ASSERT(cfl_string_list_contains(&logger->log, "world"));
}

CFL_TEST_GROUP(buffer_logger) {
    CFL_RUN_TEST(cfl_buffer_logger_has_empty_buffer_after_creation);
    CFL_RUN_TEST(cfl_buffer_logger_has_message_after_logging);
    CFL_RUN_TEST(cfl_buffer_logger_has_all_messages_after_logging);
}
