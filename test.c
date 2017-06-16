#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "lend.h"

int main(int argc, char** argv) {
    if(argc != 4) {
        fprintf(stderr, "usage: %s [seed] [size] [inum]\n", argv[0]);
        return 1;
    }

    int seed = atoi(argv[1]),
        size = atoi(argv[2]),
        inum = atoi(argv[3]);

    printf("seed %d\n", seed);
    srand(seed);

    struct lend_pool pool;
    struct lend_pool * const p = &pool;
    void *area = malloc(size);
    if (0 != lend_init(p, area, size)) {
        return 2;
    }

    int ptrc = 0;
    void **ptrv = calloc(size / sizeof(void*), sizeof(void *));

    for(int iter = 0; iter < inum; iter++) {
        if(getenv("SHOW")) lend_show(p);

        if(!ptrc || rand() < INT_MAX / 2) {
            if(getenv("SHOW")) printf("take\n");

            void **ptri;
            for(ptri = ptrv; *ptri; ptri++);
            *ptri = lend_calloc(p, 1, rand() % (size / 2));
            if(*ptri && ptri - ptrv == ptrc)
                ptrc++;
        } else {
            if(getenv("SHOW")) printf("give\n");

            void **ptri = ptrv + (rand() % ptrc);
            lend_free(p, *ptri);
            *ptri = NULL;
        }
    }

    while(ptrc-- > 0) {
        lend_free(p, ptrv[ptrc]);
    }

    lend_free(p, lend_malloc(p, 0));
    lend_show(p);

    return 0;
}
