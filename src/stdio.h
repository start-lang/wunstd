#ifndef STDIO_H
#define STDIO_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define setvbuf(a, b, c, d)
#define stdout
#define _IONBF

IMPORT("pechar") void pechar(int c);

IMPORT("putchar") int putchar(int c);

int puts(const char *s);

int sprintf(char *out, const char *format, ...);

int wprintf(const char *format, ...);

#define printf(...) wprintf(__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif