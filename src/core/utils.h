
#pragma once

#define cfl_unused(x) \
    do { (void)(x); } while (0)

#define containerof(ptr, type, member) \
    (type*)((char*)ptr - offsetof(type,member))

#ifdef WIN32
#define CFL_PRINTF
#else
#define CFL_PRINTF __attribute__((format(printf, 2, 3)))
#endif /* WIN32 */
