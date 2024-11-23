#ifndef STRING_H
#define STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

char *strcpy(char *dest, const char *src);

char *strncpy(char *dest, const char *src, size_t n);

size_t strlen(const char *s);

int strcmp(const char *s1, const char *s2);

char *strcat(char *dest, const char *src);

#ifdef __cplusplus
}
#endif

#endif