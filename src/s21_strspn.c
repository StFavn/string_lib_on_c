#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t counter = 0;

  for (const char *ptr1 = str1; *ptr1 != '\0'; ++ptr1) {
    bool is_found = false;
    for (const char *ptr2 = str2; (*ptr2 != '\0') && !is_found; ++ptr2) {
      if (*ptr1 == *ptr2) {
        counter++;
        is_found = true;
      }
    }
    if (!is_found) break;
  }

  return counter;
}