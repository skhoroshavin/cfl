
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
    struct cfl_buffer_logger *self = (struct cfl_buffer_logger *)base;

    va_list args_copy;
    va_copy(args_copy, args);
    unsigned msg_len = vsnprintf(0, 0, fmt, args_copy);
    va_end(args_copy);

    if (self->buffer) {
        char *old_buffer = self->buffer;
        unsigned old_size = strlen(old_buffer);

        unsigned new_size = old_size + msg_len + 2;
        char *new_buffer = cfl_alloc(&cfl_default_allocator, new_size);
        self->buffer = new_buffer;

        memcpy(new_buffer, old_buffer, old_size);
        new_buffer += old_size;
        vsnprintf(new_buffer, msg_len+1, fmt, args);
        new_buffer += msg_len;
        *(new_buffer++) = '\n';
        *new_buffer = 0;

        cfl_free(&cfl_default_allocator, old_buffer);
    } else {
        unsigned new_size = msg_len + 2;
        char *new_buffer = cfl_alloc(&cfl_default_allocator, new_size);
        self->buffer = new_buffer;

        vsnprintf(new_buffer, msg_len+1, fmt, args);
        new_buffer += msg_len;
        *(new_buffer++) = '\n';
        *new_buffer = 0;
    }
}

void cfl_buffer_logger_init(struct cfl_buffer_logger *self) {
    self->base.write = &cfl_buffer_logger_write;
    self->buffer = 0;
}

void cfl_buffer_logger_done(struct cfl_buffer_logger *self) {
    if (self->buffer) {
        cfl_free(&cfl_default_allocator, self->buffer);
        self->buffer = 0;
    }
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
