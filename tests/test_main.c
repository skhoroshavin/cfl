
#include <test/test.h>

CFL_TEST_GROUP(utils);
CFL_TEST_GROUP(memory);
CFL_TEST_GROUP(linked_list);
CFL_TEST_GROUP(string_list);
CFL_TEST_GROUP(buffer_logger);
CFL_TEST_GROUP(context);
CFL_TEST_GROUP(engine);
CFL_TEST_GROUP(asserts);
CFL_TEST_GROUP(main);

CFL_TEST_MAIN() {
    CFL_RUN_GROUP(utils);
    CFL_RUN_GROUP(memory);
    CFL_RUN_GROUP(linked_list);
    CFL_RUN_GROUP(string_list);
    CFL_RUN_GROUP(buffer_logger);
    CFL_RUN_GROUP(context);
    CFL_RUN_GROUP(engine);
    CFL_RUN_GROUP(asserts);
    CFL_RUN_GROUP(main);
}
