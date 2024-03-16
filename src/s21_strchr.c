#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  const char ch = (char)c;
  char *res = (char *)str;

  while (*res != '\0' && (*res != ch)) {
    res++;
  }

  return (*res == ch) ? res : S21_NULL;
}