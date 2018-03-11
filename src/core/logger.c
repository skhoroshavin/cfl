
#include "logger.h"

#include <stdio.h>

/*
 * CFL logger interface
 */

void cfl_logger_printf(struct cfl_logger *self, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    self->vprintf(self, fmt, args);
    va_end(args);
}

/*
 * CFL buffer logger
 */

static void cfl_buffer_logger_vprintf(struct cfl_logger *base, const char *fmt, va_list args) {
    struct cfl_buffer_logger *self = (struct cfl_buffer_logger *) base;
    cfl_string_list_vprintf(&self->log, fmt, args);
}

void cfl_buffer_logger_init(struct cfl_buffer_logger *self) {
    self->base.vprintf = &cfl_buffer_logger_vprintf;
    cfl_string_list_init(&self->log);
}

void cfl_buffer_logger_done(struct cfl_buffer_logger *self) {
    cfl_string_list_done(&self->log);
}

/*
 * CFL default logger
 */

static void cfl_default_logger_vprintf(struct cfl_logger *base, const char *fmt, va_list args) {
    cfl_unused(base);
    vprintf(fmt, args);
    printf("\n");
}

struct cfl_logger cfl_default_logger = {.vprintf = cfl_default_logger_vprintf};
