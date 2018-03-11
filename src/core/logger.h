
#pragma once

#include "string_list.h"

/*
 * CFL logger interface
 */

struct cfl_logger {
    void (*write)(struct cfl_logger *self, const char *fmt, va_list args);
};

void cfl_logger_write(struct cfl_logger *self, const char *fmt, ...) CFL_PRINTF;

/*
 * CFL buffer logger
 */

struct cfl_buffer_logger {
    struct cfl_logger base;
    struct cfl_string_list log;
};
void cfl_buffer_logger_init(struct cfl_buffer_logger *self);
void cfl_buffer_logger_done(struct cfl_buffer_logger *self);

/*
 * CFL default logger
 */

extern struct cfl_logger cfl_default_logger;
