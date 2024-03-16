#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = (dest + s21_strlen(dest));

  while (n-- && *src != '\0') {
    *ptr = *src;
    ptr++;
    src++;
  }

  *(ptr + 1) = '\0';

  return dest;
}