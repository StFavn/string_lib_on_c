#include <stdlib.h>

#include "s21_string.h"

#define LETTER_DELTA 32

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) return S21_NULL;

  const s21_size_t len = s21_strlen(str);

  char *res = (char *)calloc(len + 1, sizeof(char));
  if (res == S21_NULL) return S21_NULL;

  for (s21_size_t i = 0; i < len; ++i) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      res[i] = str[i] - LETTER_DELTA;
    } else {
      res[i] = str[i];
    }
  }

  return res;
}