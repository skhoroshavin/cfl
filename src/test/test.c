
#include "test.h"

void cfl_test_engine_init(struct cfl_test_engine *self, struct cfl_logger *logger) {
    self->logger = logger;
    self->total_tests = 0;
    self->failed_tests = 0;
}

void cfl_test_engine_done(struct cfl_test_engine *self) { cfl_unused(self); }

void cfl_test_engine_run_test(struct cfl_test_engine *self, const char *test_name,
                              void (*test_fn)(struct cfl_test_context *)) {
    struct cfl_test_context ctx;
    cfl_test_context_init(&ctx);
    test_fn(&ctx);
    ++self->total_tests;
    if (ctx.result == CFL_TEST_FAIL) {
        cfl_logger_printf(self->logger, "FAIL %s:", test_name);
        cfl_logger_printf(self->logger, "%s", ctx.error);
        ++self->failed_tests;
    }
    cfl_test_context_done(&ctx);
}

int cfl_test_main(int argc, const char *argv[], struct cfl_logger *logger, void (*main_fn)(struct cfl_test_engine *)) {
    cfl_unused(argc);
    cfl_unused(argv);

    struct cfl_test_engine engine;
    cfl_test_engine_init(&engine, logger);

    main_fn(&engine);
    int return_code = engine.failed_tests > 0 ? 1 : 0;

    if (engine.failed_tests > 0)
        cfl_logger_printf(logger, "Failed %d tests from %d total tests", engine.failed_tests, engine.total_tests);
    else
        cfl_logger_printf(logger, "All %d tests passed", engine.total_tests);

    cfl_test_engine_done(&engine);

    return return_code;
}
