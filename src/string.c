#include <string.h>

char *strcpy(char *dest, const char *src) {
  char *ret = dest;
  while ((*dest++ = *src++));
  return ret;
}

char *strncpy(char *dest, const char *src, size_t n) {
  char *ret = dest;
  while (n-- && (*dest++ = *src++));
  return ret;
}

size_t strlen(const char *s) {
  const char *p = s;
  while (*s) {
    s++;
  }
  return s - p;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

char *strcat(char *dest, const char *src) {
  char *ret = dest;
  while (*dest) {
    dest++;
  }
  while ((*dest++ = *src++))
    ;
  return ret;
}