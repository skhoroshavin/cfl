
#include "../test_common.h"

CFL_TEST(cfl_buffer_logger_has_empty_buffer_after_creation) {
    GIVEN_BUFFER_LOGGER(logger);

    ASSERT_NULL(logger->buffer);
}

CFL_TEST(cfl_buffer_logger_has_message_after_logging) {
    GIVEN_BUFFER_LOGGER(logger);

    cfl_logger_write(&logger->base, "Hello");

    ASSERT_NOT_NULL(logger->buffer);
    ASSERT_STR_CONTAINS(logger->buffer, "Hello");
}

CFL_TEST(cfl_buffer_logger_has_all_messages_after_logging) {
    GIVEN_BUFFER_LOGGER(logger);

    cfl_logger_write(&logger->base, "Hello");
    cfl_logger_write(&logger->base, "world");

    ASSERT_NOT_NULL(logger->buffer);
    ASSERT_STR_CONTAINS(logger->buffer, "Hello");
    ASSERT_STR_CONTAINS(logger->buffer, "world");
}

CFL_TEST_GROUP(buffer_logger) {
    CFL_RUN_TEST(cfl_buffer_logger_has_empty_buffer_after_creation);
    CFL_RUN_TEST(cfl_buffer_logger_has_message_after_logging);
    CFL_RUN_TEST(cfl_buffer_logger_has_all_messages_after_logging);
}
