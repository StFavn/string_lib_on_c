#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t len_str1 = s21_strlen(str1) + 1;  // include \0 char
  s21_size_t len_str2 = s21_strlen(str2) + 1;
  int res = 0;

  s21_size_t i = 0;
  while ((i < len_str1 && i < len_str2) && (i < n)) {
    if (str1[i] != str2[i]) {
      res = str1[i] - str2[i];
      break;
    }
    ++i;
  }

  return res;
}
