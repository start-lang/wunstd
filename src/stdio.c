#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int puts(const char *s) {
  while (*s) putchar(*s++);
  putchar('\n');
  return 0;
}

int int_to_string(int value, char *out) {
  int index = 0;
  char digits[16];
  unsigned int abs_value;

  if (value == 0) {
    out[0] = '0';
    out[1] = '\0';
    return 1;
  }

  if (value < 0) {
    out[index++] = '-';
    abs_value = (unsigned int)(-((long)value));
  } else {
    abs_value = (unsigned int)value;
  }

  int digit_count = 0;
  while (abs_value > 0) {
    digits[digit_count++] = (abs_value % 10) + '0';
    abs_value /= 10;
  }

  for (int i = digit_count - 1; i >= 0; i--) {
    out[index++] = digits[i];
  }

  out[index] = '\0';
  return index;
}

int float_to_string_fixed(float value, char *out, int precision) {
  int index = 0;
  char digits[32];

  if (value < 0) {
    out[index++] = '-';
    value = -value;
  }

  int integer_part = (int)value;
  float fractional_part = value - (float)integer_part;

  int int_index = 0;
  if (integer_part == 0) {
    digits[int_index++] = '0';
  } else {
    while (integer_part > 0) {
      digits[int_index++] = (integer_part % 10) + '0';
      integer_part /= 10;
    }
  }

  for (int i = int_index - 1; i >= 0; i--) {
    out[index++] = digits[i];
  }

  out[index++] = '.';

  for (int i = 0; i < precision; i++) {
    fractional_part *= 10.0f;
    int frac_digit = (int)(fractional_part + 0.00001f);
    out[index++] = frac_digit + '0';
    fractional_part -= frac_digit;
  }

  out[index] = '\0';
  return index;
}

int vsprintf(char *out, const char *format, va_list args) {
  int out_index = 0;
  int format_index = 0;

  while (format[format_index] != '\0') {
    if (format[format_index] == '%') {
      format_index++;
      char padding_char = ' ';
      int width = 0;
      int precision = -1;

      if (format[format_index] == '0') {
        padding_char = '0';
        format_index++;
      }

      while (format[format_index] >= '0' && format[format_index] <= '9') {
        width = width * 10 + (format[format_index] - '0');
        format_index++;
      }

      if (format[format_index] == '.') {
        format_index++;
        precision = 0;
        while (format[format_index] >= '0' && format[format_index] <= '9') {
          precision = precision * 10 + (format[format_index] - '0');
          format_index++;
        }
      }

      char specifier = format[format_index++];

      if (specifier == 'd' || specifier == 'i' || specifier == 'u' || specifier == 'l') {
        if (specifier == 'l') {
          format_index++;
        }
        int value = va_arg(args, int);
        char temp[16];
        int len = int_to_string(value, temp);
        int padding = width - len;
        for (int i = 0; i < padding; i++) {
          out[out_index++] = padding_char;
        }
        for (int i = 0; i < len; i++) {
          out[out_index++] = temp[i];
        }
      } else if (specifier == 's') {
        char *str = va_arg(args, char *);
        int len = strlen(str);
        int padding = width - len;
        for (int i = 0; i < padding; i++) {
          out[out_index++] = padding_char;
        }
        for (int i = 0; i < len; i++) {
          out[out_index++] = str[i];
        }
      } else if (specifier == 'f') {
        double value = va_arg(args, double);
        char temp[32];
        int prec = (precision >= 0) ? precision : 2;
        int len = float_to_string_fixed((float)value, temp, prec);
        int padding = width - len;
        for (int i = 0; i < padding; i++) {
          out[out_index++] = padding_char;
        }
        for (int i = 0; i < len; i++) {
          out[out_index++] = temp[i];
        }
      } else if (specifier == 'c') {
        char c = (char)va_arg(args, int);
        out[out_index++] = c;
      } else {
        out[out_index++] = '%';
        out[out_index++] = specifier;
      }
    } else {
      out[out_index++] = format[format_index++];
    }
  }

  out[out_index] = '\0';
  return out_index;
}

int sprintf(char *out, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int length = vsprintf(out, format, args);
  va_end(args);
  return length;
}

int wprintf(const char *format, ...) {
  char buffer[1024];
  va_list args;
  va_start(args, format);
  int length = vsprintf(buffer, format, args);
  va_end(args);
  for (int i = 0; i < length; i++) {
    putchar(buffer[i]);
  }
  return length;
}

uint8_t getc(void) {
  return getch();
}

uint8_t getch() {
  while (1) {
    uint8_t c = _getch();
    if (c != 0) {
      return c;
    }
  }
}