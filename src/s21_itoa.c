#include "s21_converters.h"

/// Преобразование целого числа по модулю
/// x заданной системы счисления base  в строку
/// с учётом знака и дополнительных параметров функции s21_sprintf
char *s21_itoa(long long int x, int base, bool sign_save, bool sign_place,
               bool is_hex_big) {
  char *res = S21_NULL;
  bool is_minus = (x < 0);

  if (is_minus || sign_save || sign_place) {
    char *numbers_str = s21_itoa_abs(x, base, is_hex_big);
    if (numbers_str == S21_NULL) return S21_NULL;

    // Additional place for sign
    int res_str_lenght = s21_strlen(numbers_str);

    res = (char *)calloc(res_str_lenght + 2, sizeof(char));  // +2 for valgrind

    if (res != S21_NULL) {
      if (is_minus) {
        res[0] = '-';
      } else if (sign_save) {
        res[0] = '+';
      } else if (sign_place) {
        res[0] = ' ';
      }

      // Использование s21_strncat приводит к ошибке valgrind
      // s21_strncat(res, numbers_str, res_str_lenght + 1);

      for (int i = 1; i <= res_str_lenght; ++i) {
        res[i] = numbers_str[i - 1];
      }
    }

    free(numbers_str);
  } else {
    res = s21_itoa_abs(x, base, is_hex_big);
  }

  return res;
}

/// Преобразование целого числа по модулю
/// x заданной системы счисления base  в строку
char *s21_itoa_abs(long long int x, int base, bool is_hex_big) {
  x = (x < 0) ? -x : x;
  char *res = s21_uitoa_abs(x, base, is_hex_big);
  return res;
}
