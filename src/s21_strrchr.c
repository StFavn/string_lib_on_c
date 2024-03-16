#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const s21_size_t str_len = s21_strlen(str);
  const char ch = (char)c;

  char *res = S21_NULL;
  bool is_found = false;

  for (int i = str_len; (i >= 0) && !is_found; --i) {
    if (str[i] == ch) {
      res = (char *)&str[i];
      is_found = true;
    }
  }

  return res;
}