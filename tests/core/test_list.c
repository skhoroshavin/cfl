
#include "../test_common.h"

static int index_of_node(const struct cfl_list *list, const struct cfl_list_node *node) {
    int counter = 0;
    struct cfl_list_node *cur;
    cfl_list_foreach(cur, list) {
        if (cur == node)
            return counter;
        ++counter;
    }
    return -1;
}

CFL_TEST(cfl_list_is_initialized_as_empty) {
    struct cfl_list list;
    cfl_list_init(&list);

    ASSERT(cfl_list_is_empty(&list));
    ASSERT_INT_EQ(cfl_list_size(&list), 0);
}

CFL_TEST(cfl_list_append_adds_node_to_list) {
    struct cfl_list list;
    cfl_list_init(&list);

    struct cfl_list_node node;
    cfl_list_append(&list, &node);

    ASSERT(!cfl_list_is_empty(&list));
    ASSERT_INT_EQ(cfl_list_size(&list), 1);
    ASSERT_INT_EQ(index_of_node(&list, &node), 0);
}

CFL_TEST(cfl_list_append_adds_node_to_end_of_list) {
    struct cfl_list list;
    cfl_list_init(&list);

    struct cfl_list_node node1, node2;
    cfl_list_append(&list, &node1);
    cfl_list_append(&list, &node2);

    ASSERT(!cfl_list_is_empty(&list));
    ASSERT_INT_EQ(cfl_list_size(&list), 2);
    ASSERT_INT_EQ(index_of_node(&list, &node1), 0);
    ASSERT_INT_EQ(index_of_node(&list, &node2), 1);
}

CFL_TEST(cfl_list_prepend_adds_node_to_start_of_list) {
    struct cfl_list list;
    cfl_list_init(&list);

    struct cfl_list_node node1, node2;
    cfl_list_prepend(&list, &node1);
    cfl_list_prepend(&list, &node2);

    ASSERT(!cfl_list_is_empty(&list));
    ASSERT_INT_EQ(cfl_list_size(&list), 2);
    ASSERT_INT_EQ(index_of_node(&list, &node2), 0);
    ASSERT_INT_EQ(index_of_node(&list, &node1), 1);
}

CFL_TEST(cfl_list_node_remove_removes_node_from_list) {
    struct cfl_list list;
    cfl_list_init(&list);

    struct cfl_list_node node1, node2, node3;
    cfl_list_append(&list, &node1);
    cfl_list_append(&list, &node2);
    cfl_list_append(&list, &node3);

    cfl_list_node_remove(&node2);

    ASSERT(!cfl_list_is_empty(&list));
    ASSERT_INT_EQ(cfl_list_size(&list), 2);
    ASSERT_INT_EQ(index_of_node(&list, &node1), 0);
    ASSERT_INT_EQ(index_of_node(&list, &node3), 1);
}

CFL_TEST_GROUP(linked_list) {
    CFL_RUN_TEST(cfl_list_is_initialized_as_empty);
    CFL_RUN_TEST(cfl_list_append_adds_node_to_list);
    CFL_RUN_TEST(cfl_list_append_adds_node_to_end_of_list);
    CFL_RUN_TEST(cfl_list_prepend_adds_node_to_start_of_list);

    CFL_RUN_TEST(cfl_list_node_remove_removes_node_from_list);
}
