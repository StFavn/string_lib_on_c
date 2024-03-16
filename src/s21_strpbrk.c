#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  if (str1 == S21_NULL || str2 == S21_NULL) return S21_NULL;

  char *res = S21_NULL;
  s21_size_t len_str1 = s21_strlen(str1);
  s21_size_t len_str2 = s21_strlen(str2);
  bool is_found = false;

  for (s21_size_t i = 0; (i < len_str1) && !is_found; ++i) {
    for (s21_size_t j = 0; (j < len_str2) && !is_found; ++j) {
      if (str1[i] == str2[j]) {
        is_found = true;
        res = (char *)&str1[i];
      }
    }
  }

  return res;
}
