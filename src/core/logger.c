
#include "logger.h"

#include <stdio.h>
#include <string.h>

/*
 * CFL logger interface
 */

void cfl_logger_write(struct cfl_logger *self, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    self->write(self, fmt, args);
    va_end(args);
}

/*
 * CFL buffer logger
 */

static void cfl_buffer_logger_write(struct cfl_logger *base, const char *fmt, va_list args) {
    struct cfl_buffer_logger *self = (struct cfl_buffer_logger *) base;

    va_list args_copy;
    va_copy(args_copy, args);
    unsigned msg_len = vsnprintf(0, 0, fmt, args_copy) + 1;
    va_end(args_copy);

    char *msg = cfl_alloc(&cfl_default_allocator, msg_len);
    vsnprintf(msg, msg_len, fmt, args);
    cfl_string_list_append(&self->log, msg);
}

void cfl_buffer_logger_init(struct cfl_buffer_logger *self) {
    self->base.write = &cfl_buffer_logger_write;
    cfl_string_list_init(&self->log);
}

void cfl_buffer_logger_done(struct cfl_buffer_logger *self) {
    cfl_string_list_done(&self->log);
}

/*
 * CFL default logger
 */

static void cfl_default_logger_write(struct cfl_logger *base, const char *fmt, va_list args) {
    cfl_unused(base);
    vprintf(fmt, args);
    printf("\n");
}

struct cfl_logger cfl_default_logger = {.write = cfl_default_logger_write};
