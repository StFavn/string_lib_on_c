#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last_token = S21_NULL;

  if (str != S21_NULL) {
    last_token = str;
  } else {
    if (last_token == S21_NULL) return S21_NULL;
    str = last_token;
  }

  str += s21_strspn(str, delim);
  if (*str == '\0') {
    last_token = S21_NULL;
    return S21_NULL;
  }

  char *token = str;
  str = s21_strpbrk(token, delim);
  if (str != S21_NULL) {
    *str = '\0';
    last_token = str + 1;
  } else {
    last_token = S21_NULL;
  }

  return token;
}