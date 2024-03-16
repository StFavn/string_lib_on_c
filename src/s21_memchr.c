#include "s21_string.h"

/// Unsafe
void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *found_p = S21_NULL;
  const unsigned char *ptr = str;

  while (n--) {
    if (*ptr == (unsigned char)c) {
      found_p = (void *)ptr;
      break;
    }
    ptr++;
  }

  return found_p;
}