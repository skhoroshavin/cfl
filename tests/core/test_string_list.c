
#include "../test_common.h"

CFL_TEST(cfl_string_list_is_initialized_as_empty) {
    GIVEN_STRING_LIST(list);

    ASSERT(cfl_string_list_is_empty(list));
}

CFL_TEST(cfl_empty_string_list_doesnt_contain_any_string) {
    GIVEN_STRING_LIST(list);

    ASSERT(cfl_string_list_contains(list, "Hello") == 0);
}

CFL_TEST(cfl_string_list_append_adds_string_to_list) {
    GIVEN_STRING_LIST(list);

    cfl_string_list_append(list, "Hello");

    ASSERT(cfl_string_list_contains(list, "Hello"));
}

CFL_TEST(cfl_string_list_doesnt_contain_strings_that_were_not_added_to_it) {
    GIVEN_STRING_LIST(list);

    cfl_string_list_append(list, "Hello");

    ASSERT(!cfl_string_list_contains(list, "world"));
}

CFL_TEST(cfl_string_list_can_append_multiple_strings) {
    GIVEN_STRING_LIST(list);

    cfl_string_list_append(list, "Hello");
    cfl_string_list_append(list, "world");

    ASSERT(cfl_string_list_contains(list, "Hello"));
    ASSERT(cfl_string_list_contains(list, "world"));
}

CFL_TEST_GROUP(string_list) {
    CFL_RUN_TEST(cfl_string_list_is_initialized_as_empty);
    CFL_RUN_TEST(cfl_empty_string_list_doesnt_contain_any_string);
    CFL_RUN_TEST(cfl_string_list_append_adds_string_to_list);
    CFL_RUN_TEST(cfl_string_list_doesnt_contain_strings_that_were_not_added_to_it);
    CFL_RUN_TEST(cfl_string_list_can_append_multiple_strings);
}
