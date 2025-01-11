#ifndef STDIO_H
#define STDIO_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define setvbuf(a, b, c, d)
#define stdout 0
#define stderr 1
#define stdin
#define _IONBF
#define EOF -1

IMPORT("pechar") void pechar(int c);

IMPORT("putchar") int putchar(int c);

IMPORT("getch") uint8_t _getch(void);

IMPORT("needs_input") void needs_input(void);

uint8_t getch();

int puts(const char *s);

int sprintf(char *out, const char *format, ...);

int wprintf(const char *format, ...);

int atoi(const char *nptr);

uint8_t getc(void);

#define printf(...) wprintf(__VA_ARGS__)

#define fprintf(f, ...) wprintf(__VA_ARGS__)

#define exit(...)

#ifdef __cplusplus
}
#endif

#endif