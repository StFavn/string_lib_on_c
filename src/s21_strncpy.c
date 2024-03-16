#include "s21_string.h"

char* s21_strncpy(char* dest, const char* str, s21_size_t n) {
  s21_memset(dest, 0, n);

  char* ptr = dest;
  while (n-- && *str != '\0') {
    *ptr = *str;
    ptr++;
    str++;
  }

  return dest;
}
