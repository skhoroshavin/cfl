
#pragma once

#include "memory.h"
#include <string.h>

#define PASS()            \
    do {                  \
        cfl_unused(_ctx); \
        return;           \
    } while (0)

#define FAIL(...)                                                      \
    do {                                                               \
        _ctx->result = CFL_TEST_FAIL;                                  \
        _ctx->error = cfl_format(&cfl_default_allocator, __VA_ARGS__); \
        return;                                                        \
    } while (0)

#define ASSERT(cond)                                      \
    do {                                                  \
        if (!(cond)) FAIL("Assertion failed: %s", #cond); \
    } while (0)

#define ASSERT_NULL(ptr)                                         \
    do {                                                         \
        if (ptr) FAIL("Assertion failed: %s is not null", #ptr); \
    } while (0)

#define ASSERT_NOT_NULL(ptr)                                  \
    do {                                                      \
        if (!ptr) FAIL("Assertion failed: %s is null", #ptr); \
    } while (0)

#define ASSERT_INT(a, op, b)                                                                                \
    do {                                                                                                    \
        if (!((a)op(b))) FAIL("Assertion failed: %s %s %s (expanded to %d %s %d)", #a, #op, #b, a, #op, b); \
    } while (0)

#define ASSERT_INT_EQ(a, b) ASSERT_INT(a, ==, b)
#define ASSERT_INT_LESS(a, b) ASSERT_INT(a, <, b)
#define ASSERT_INT_GREATER(a, b) ASSERT_INT(a, >, b)
#define ASSERT_INT_NOT_EQ(a, b) ASSERT_INT(a, !=, b)
#define ASSERT_INT_NOT_LESS(a, b) ASSERT_INT(a, >=, b)
#define ASSERT_INT_NOT_GREATER(a, b) ASSERT_INT(a, <=, b)

#define ASSERT_STR_EQ(a, b)                                                                                     \
    do {                                                                                                        \
        if (strcmp(a, b) != 0) FAIL("Assertion failed: %s == %s (expanded to \"%s\" == \"%s\")", #a, #b, a, b); \
    } while (0)

#define ASSERT_STR_CONTAINS(a, b)                                                                             \
    do {                                                                                                      \
        if (strstr(a, b) == 0)                                                                                \
            FAIL("Assertion failed: %s (expanded to \"%s\") contains %s (expanded to \"%s\")", #a, a, #b, b); \
    } while (0)
