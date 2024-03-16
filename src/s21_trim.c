#include <stdlib.h>

#include "s21_string.h"

/**
 * Trims the specified characters from the start and end of the source string.
 *
 * Parameters:
 *   - src: A constant pointer to the source string to be trimmed.
 *   - trim_chars: A constant pointer to a string containing the characters to
 * be trimmed.
 *
 * Returns:
 *   - On success, a dynamically allocated string containing the result of the
 * trimming operation.
 *   - On failure or invalid inputs, returns S21_NULL.
 *
 * Notes:
 *   - This function allocates memory using the 'calloc' function for the result
 * string.
 *   - The caller is responsible for freeing the memory allocated for the
 * returned string.
 *   - If 'src' is S21_NULL, the function returns S21_NULL.
 *   - If 'src' is an empty string, the function returns an empty string.
 *   - If 'trim_chars' is S21_NULL or an empty string, the function returns a
 * copy of 'src'.
 */
void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL) return S21_NULL;

  char *res = (char *)calloc(s21_strlen(src) + 1, sizeof(char));
  if (res == S21_NULL) return S21_NULL;

  if (s21_strlen(src) == 0) return res;
  if (trim_chars == S21_NULL || s21_strlen(trim_chars) == 0) {
    s21_memcpy(res, src, s21_strlen(src) + 1);
    return res;
  }

  s21_size_t src_start_i = 0;
  s21_size_t src_end_i = s21_strlen(src) - 1;

  while (src[src_start_i] != '\0') {
    if (s21_strchr(trim_chars, src[src_start_i]) == S21_NULL) break;
    src_start_i++;
  }

  while (src_end_i >= src_start_i) {
    if (s21_strchr(trim_chars, src[src_end_i]) == S21_NULL) break;
    src_end_i--;
  }

  s21_size_t result_i = 0;
  while (src_start_i <= src_end_i) {
    res[result_i] = src[src_start_i];
    result_i++;
    src_start_i++;
  }

  return res;
}