
#pragma once

#include "asserts.h"
#include "context.h"
#include "core/logger.h"

#include <string.h>

struct cfl_test_engine {
    struct cfl_logger *logger;
    int total_tests;
    int failed_tests;
};

void cfl_test_engine_init(struct cfl_test_engine *self, struct cfl_logger *logger);
void cfl_test_engine_done(struct cfl_test_engine *self);
void cfl_test_engine_run_test(struct cfl_test_engine *self, const char *test_name,
                              void (*test_fn)(struct cfl_test_context *));

int cfl_test_main(int argc, const char *argv[], struct cfl_logger *logger, void (*main_fn)(struct cfl_test_engine *));

/*
 * Utility macros
 */

#define CFL_TEST(name) static void name(struct cfl_test_context *_ctx)

#define CFL_RUN_TEST(name) cfl_test_engine_run_test(_engine, #name, name)

#define CFL_TEST_GROUP(name) void cfl_test_group##_##name(struct cfl_test_engine *_engine)

#define CFL_RUN_GROUP(name) cfl_test_group##_##name(_engine)

#define CFL_ADD_TEARDOWN(data, fn) cfl_test_context_add_teardown(_ctx, data, (cfl_test_teardown_fn)fn)

#define CFL_TEST_MAIN()                                                            \
    static void cfl_test_main_impl(struct cfl_test_engine *_engine);               \
    int main(int argc, const char *argv[]) {                                       \
        return cfl_test_main(argc, argv, &cfl_default_logger, cfl_test_main_impl); \
    }                                                                              \
    void cfl_test_main_impl(struct cfl_test_engine *_engine)
