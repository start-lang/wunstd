#include <stdlib.h>
#include <stdio.h>

extern int main(int argc, char ** argv);
extern int main_init(int argc, char ** argv);
extern int main_step(void);
extern void main_free(void);
extern uint8_t getch_input;


EXPORT int wasm_main() {
  int argc = getargc();
  char **argv = (char **) malloc(sizeof(char *) * argc);
  if (!argv) return -1;
  for (int i = 0; i < argc; i++) {
    int len = getarglen(i);
    char *arg = (char *) malloc(len + 1);
    if (!arg) return -1;
    arg = getargstr(arg, i);
    arg[len] = '\0';
    argv[i] = arg;
  }
  int r = main(argc, argv);
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  free(argv);
  return r;
}

EXPORT int wasm_init() {
  int argc = getargc();
  char **argv = (char **) malloc(sizeof(char *) * argc);
  if (!argv) return -1;
  for (int i = 0; i < argc; i++) {
    int len = getarglen(i);
    char *arg = (char *) malloc(len + 1);
    if (!arg) return -1;
    arg = getargstr(arg, i);
    arg[len] = '\0';
    argv[i] = arg;
  }
  int r = main_init(argc, argv);
  return r;
}

EXPORT int wasm_step(char input) {
  getch_input = input;
  return main_step();
}

EXPORT void wasm_free() {
  main_free();
}

int atoi(const char *nptr) {
  int res = 0;
  int sign = 1;
  if (*nptr == '-') {
    sign = -1;
    nptr++;
  }
  while (*nptr >= '0' && *nptr <= '9') {
    res = res * 10 + *nptr - '0';
    nptr++;
  }
  return res * sign;
}
