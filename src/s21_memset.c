#include "s21_string.h"

/// Unsafe
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = str;

  while (n > 0) {
    *ptr = (unsigned char)c;
    ptr++;
    n--;
  }

  return str;
}