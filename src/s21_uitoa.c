#include "s21_converters.h"

/// Преобразование целого числа ULL по модулю
/// x заданной системы счисления base  в строку
char *s21_uitoa_abs(unsigned long long x, int base, bool is_hex_big) {
  const double log_base = (x != 0) ? log(x) / log(base) : 0.0;
  s21_size_t len =
      (((int)log_base != base)) ? floor(log_base) + 1 : round(log_base);

  char *res = (char *)calloc(len + 1, sizeof(char));
  if (res == S21_NULL) return S21_NULL;

  if (x == 0) {
    --len;
    res[len] = '0';
  }

  while (x != 0) {
    --len;
    unsigned long long tmp = x % base;

    if (tmp < 10)
      tmp += CHAR_SHIFT_NUM;
    else
      tmp += (is_hex_big) ? CHAR_SHIFT_BIG_HEX : CHAR_SHIFT_SMALL_HEX;

    res[len] = tmp;
    x /= base;
  }

  return res;
}
