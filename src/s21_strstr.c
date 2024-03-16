#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (*haystack == '\0' && *needle == '\0') return (char *)haystack;

  const s21_size_t needle_len = s21_strlen(needle);
  if (needle_len > s21_strlen(haystack)) return S21_NULL;

  char *res = S21_NULL;
  bool is_find = false;

  for (const char *ptr = haystack; (*ptr != '\0') && !is_find; ++ptr) {
    if (s21_memcmp(ptr, needle, needle_len) == 0) {
      res = (char *)ptr;
      is_find = true;
    }
  }

  return res;
}