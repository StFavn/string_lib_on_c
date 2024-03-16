#include "s21_converters.h"

#define OCT_BASE 8
#define DEC_BASE 10
#define HEX_BASE 16

int s21_atoi(const char *nptr) {
  int sign = 1;
  int res = 0;

  if (*nptr == '+') ++nptr;

  if (*nptr == '-') {
    ++nptr;
    sign *= -1;
  }

  s21_size_t num_pos = s21_strlen(nptr) - 1;

  while (*nptr != '\0') {
    res += (*nptr - CHAR_SHIFT_NUM) * pow(DEC_BASE, num_pos);
    --num_pos;
    ++nptr;
  }

  return res * sign;
}

long long s21_atoll(const char *nptr) {
  int sign = 1;
  long long res = 0;

  if (*nptr == '+') ++nptr;

  if (*nptr == '-') {
    ++nptr;
    sign *= -1;
  }

  s21_size_t num_pos = s21_strlen(nptr) - 1;

  while (*nptr != '\0') {
    res += (*nptr - CHAR_SHIFT_NUM) * powl(DEC_BASE, num_pos);
    --num_pos;
    ++nptr;
  }

  return res * sign;
}

long long s21_atoll_oct(const char *nptr) {
  int sign = 1;
  long long res = 0;

  if (*nptr == '+') ++nptr;

  if (*nptr == '-') {
    ++nptr;
    sign *= -1;
  }

  s21_size_t num_pos = s21_strlen(nptr) - 1;

  while (*nptr != '\0') {
    res += (*nptr - CHAR_SHIFT_NUM) * powl(OCT_BASE, num_pos);
    --num_pos;
    ++nptr;
  }

  return res * sign;
}

long long s21_atoll_hex(const char *nptr) {
  int sign = 1;
  long long res = 0;

  if (*nptr == '+') ++nptr;

  if (*nptr == '-') {
    ++nptr;
    sign *= -1;
  }

  if (nptr[0] == '0' && (nptr[1] == 'x' || nptr[1] == 'X')) {
    nptr += 2;
  }

  int num_pos = s21_strlen(nptr) - 1;
  while (*nptr != '\0') {
    const char cur_ch = *nptr;

    switch (cur_ch) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
        res += (cur_ch - CHAR_SHIFT_NUM) * powl(HEX_BASE, num_pos);
        break;
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
        res += (cur_ch - CHAR_SHIFT_SMALL_HEX) * powl(HEX_BASE, num_pos);
        break;
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
        res += (cur_ch - CHAR_SHIFT_BIG_HEX) * powl(HEX_BASE, num_pos);
        break;
      default:
        break;
    }

    --num_pos;
    ++nptr;
  }

  return res * sign;
}