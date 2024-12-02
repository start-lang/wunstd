#ifndef STDLIB_H
#define STDLIB_H

#include <walloc.h>

#define EXPORT __attribute__((visibility("default")))
#define IMPORT(name) __attribute__((import_module("env"), import_name(name)))

#ifdef __cplusplus
extern "C" {
#endif

IMPORT("getargc") int getargc(void);

IMPORT("getarglen") int getarglen(int);

IMPORT("getargstr") char * getargstr(char *, int);

#ifdef __cplusplus
}
#endif

#endif