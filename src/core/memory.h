
#pragma once

#include "utils.h"
#include <stdarg.h>
#include <stddef.h>

/*
 * CFL allocator interface
 */

struct cfl_allocator {
    void *(*realloc)(struct cfl_allocator *self, void *old_ptr, size_t new_size);
};

void *cfl_alloc(struct cfl_allocator *self, size_t size);
void cfl_free(struct cfl_allocator *self, void *ptr);
void *cfl_realloc(struct cfl_allocator *self, void *old_ptr, size_t new_size);

/*
 * CFL default allocator
 */

extern struct cfl_allocator cfl_default_allocator;

/*
 * Memory utility
 */

#define cfl_alloc_type(alloc, type) (type *)cfl_alloc(alloc, sizeof(type))

char *cfl_format_v(struct cfl_allocator *alloc, const char *fmt, va_list args);
char *cfl_format(struct cfl_allocator *alloc, const char *fmt, ...) CFL_PRINTF;
