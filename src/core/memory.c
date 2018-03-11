
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * CFL allocator interface
 */

void *cfl_alloc(struct cfl_allocator *self, size_t size) { return cfl_realloc(self, 0, size); }

void *cfl_realloc(struct cfl_allocator *self, void *old_ptr, size_t new_size) {
    return self->realloc(self, old_ptr, new_size);
}

void cfl_free(struct cfl_allocator *self, void *ptr) { cfl_realloc(self, ptr, 0); }

/*
 * CFL default allocator
 */

static void *cfl_default_allocator_realloc(struct cfl_allocator *base, void *old_ptr, size_t new_size) {
    cfl_unused(base);
    if (!old_ptr && !new_size) return 0;
    return realloc(old_ptr, new_size);
}

struct cfl_allocator cfl_default_allocator = {.realloc = cfl_default_allocator_realloc};

/*
 * Memory utility
 */

char *cfl_format_v(struct cfl_allocator *alloc, const char *fmt, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    unsigned buf_size = vsnprintf(0, 0, fmt, args) + 1;
    va_end(args);

    char *buf = cfl_alloc(alloc, buf_size);
    vsnprintf(buf, buf_size, fmt, args_copy);
    va_end(args_copy);

    return buf;
}

char *cfl_format(struct cfl_allocator *alloc, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char *buf = cfl_format_v(alloc, fmt, args);
    va_end(args);

    return buf;
}
