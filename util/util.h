#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

#include <error_handling.h>


#define ulong unsigned long

typedef struct {
    char *str;
    double score;
} StringScore;

static inline bool will_mult_overflow(size_t a, size_t b) {
    return a > ULONG_MAX / b;
}

static inline size_t st_mult(size_t a, size_t b) {
    if (will_mult_overflow(a, b)) {
        app_error("st_mult: overflow");
    }
    return a * b;
}

#endif // UTIL_H
