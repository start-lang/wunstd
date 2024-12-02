#ifndef TIME_H
#define TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#define CLOCKS_PER_SEC 1000000

typedef uint64_t clock_t;

IMPORT("get_now") double get_now();

clock_t clock(void);

#ifdef __cplusplus
}
#endif

#endif