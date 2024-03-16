#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res = s21_strlen(str1);
  const s21_size_t str2_len = s21_strlen(str2);

  bool is_found = false;
  for (s21_size_t i = 0; (i < res) && !is_found; ++i) {
    for (s21_size_t j = 0; (j < str2_len) && !is_found; ++j) {
      if (str1[i] == str2[j]) {
        is_found = true;
        res = i;
      }
    }
  }

  return res;
}