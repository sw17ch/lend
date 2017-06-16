#ifndef _LEND_H
#define _LEND_H

#include <stdlib.h>
#include <string.h>

struct meta {
    uintptr_t    magi;
    size_t       size;
    struct meta *next;
};

struct lend_pool {
    struct meta *root;
    size_t       size;
};

void *lend_malloc(struct lend_pool *pool, size_t size);
void *lend_calloc(struct lend_pool *pool, size_t numb, size_t size);
void *lend_realloc(struct lend_pool *pool, void *oldp, size_t size);
void lend_free(struct lend_pool *pool, void *objp);

int lend_init(struct lend_pool *pool, void *area, size_t size);
void lend_show(struct lend_pool *pool);

#endif
