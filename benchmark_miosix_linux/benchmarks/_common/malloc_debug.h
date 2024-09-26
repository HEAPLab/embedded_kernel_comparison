#ifndef MALLOC_DEBUG
#define MALLOC_DEBUG

#include <stdlib.h>
#include <stdio.h>

static inline void *_debug_calloc(size_t count, size_t size, const char *file, int line)
{
    fiprintf(stderr, "** %s:%d calloc(%ld, %ld)", file, line, count, size);
    void *res = calloc(count, size);
    fiprintf(stderr, " => %p\n", res);
    return res;
}

static inline void _debug_free(void *ptr, const char *file, int line)
{
    fiprintf(stderr, "** %s:%d free(%p)\n", file, line, ptr);
    free(ptr);
}

static inline void *_debug_malloc(size_t size, const char *file, int line)
{
    fiprintf(stderr, "** %s:%d malloc(%ld)", file, line, size);
    void *res = malloc(size);
    fiprintf(stderr, " => %p\n", res);
    return res;
}

static inline void *_debug_realloc(void *ptr, size_t size, const char *file, int line)
{
    fiprintf(stderr, "** %s:%d realloc(%p, %ld)", file, line, ptr, size);
    void *res = realloc(ptr, size);
    fiprintf(stderr, " => %p\n", res);
    return res;
}

#define calloc(c,s) _debug_calloc(c,s,__FILE__,__LINE__)
#define free(p) _debug_free(p,__FILE__,__LINE__)
#define malloc(s) _debug_malloc(s,__FILE__,__LINE__)
#define realloc(p,s) _debug_realloc(p,s,__FILE__,__LINE__)

#endif
