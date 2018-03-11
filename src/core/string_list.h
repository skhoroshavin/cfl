
#pragma once

#include "memory.h"
#include "list.h"

struct cfl_string_list {
    struct cfl_list list;
};

void cfl_string_list_init(struct cfl_string_list *self);
void cfl_string_list_done(struct cfl_string_list *self);

int cfl_string_list_is_empty(const struct cfl_string_list *self);
int cfl_string_list_contains(const struct cfl_string_list *self, const char *text);

void cfl_string_list_vprintf(struct cfl_string_list *self, const char *fmt, va_list args);
void cfl_string_list_printf(struct cfl_string_list *self, const char *fmt, ...) CFL_PRINTF;
