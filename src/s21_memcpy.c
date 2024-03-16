#include "s21_string.h"

/*
 * The function is unsafe, when transmitting abnormal values,
 * either Segmentation fault (NULL) or undefined behavior
 * (overlapping memory areas).
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (dest == src) return dest;

  unsigned char *dest_ptr = dest;
  const unsigned char *src_ptr = src;

  while (n--) {
    *dest_ptr = (unsigned char)*src_ptr;
    dest_ptr++;
    src_ptr++;
  }

  return dest;
}