#include "s21_string.h"

/// Unsafe
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *ptr1 = str1;
  const unsigned char *ptr2 = str2;
  int dif = 0;

  while (n--) {
    if (*ptr1 != *ptr2) {
      dif = *ptr1 - *ptr2;
      break;
    }
    ptr1++;
    ptr2++;
  }

  return dif;
}