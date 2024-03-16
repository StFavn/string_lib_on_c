#include <stdlib.h>

#include "s21_string.h"

/**
 * Inserts the string 'str' into the string 'src' at the specified 'start_index'
 * position.
 *
 * Parameters:
 *   - src: The source string into which the 'str' will be inserted.
 *   - str: The string to be inserted into 'src'.
 *   - start_index: The position at which 'str' will be inserted into 'src'.
 *
 * Returns:
 *   - On success, a dynamically allocated string containing the result of the
 * insertion.
 *   - On failure or invalid inputs, returns S21_NULL.
 *
 * Notes:
 *   - This function allocates memory using the 'calloc' function.
 *   - The caller is responsible for freeing the memory allocated for the
 * returned string.
 */
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) return S21_NULL;
  if (start_index > s21_strlen(src)) return S21_NULL;

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  s21_size_t res_len = src_len + str_len;

  char *res = (char *)calloc(res_len + 1, sizeof(char));
  if (res == S21_NULL) return S21_NULL;

  s21_memcpy(res, src, start_index);
  s21_memcpy(res + start_index, str, str_len);
  s21_memcpy(res + start_index + str_len, src + start_index,
             src_len - start_index);

  return res;
}