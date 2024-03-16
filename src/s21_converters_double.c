#include "s21_converters.h"
#include "s21_utils.h"

#define CONVER_BUFF_SIZE 256
#define CHAR_SHIFT 48
#define DBL_ZERO .1e-25

char *s21_ditoa(long double x, int precision) {
  char *res = S21_NULL;
  char *integer_str = S21_NULL;
  char *fraction_str = S21_NULL;
  char dot = '.';
  bool is_minus = (x < 0);
  bool need_int_round = false;

  if (precision == 0) {
    x = rintl(x);
  }

  // Выделить целую и дробные части числа
  long double integer = 0.0;
  long double fraction = 0.0;
  x = fabsl(x);
  fraction = modfl(x, &integer);

  // Получить строки для дробной и целой частей
  if (precision != 0) {
    fraction_str = s21_fraction_to_char(fraction, precision, &need_int_round);
    if (fraction_str == S21_NULL) return S21_NULL;
  }

  if (need_int_round) {
    integer = rintl(x);
  }

  integer_str = s21_integer_to_char(integer);
  if (integer_str == S21_NULL) return S21_NULL;

  // Сформировать целевую строку
  int fraction_str_len = (precision != 0) ? s21_strlen(fraction_str) : 0;
  int integer_str_len = s21_strlen(integer_str);
  int res_len =
      fraction_str_len + integer_str_len + is_minus + (precision != 0);
  res = (char *)calloc(res_len + 1, sizeof(char));

  if (res == S21_NULL) return S21_NULL;

  char *ptr = res;

  if (is_minus) {
    *ptr = '-';
    ++ptr;
  }

  s21_memcpy(ptr, integer_str, integer_str_len);

  if (precision != 0) {
    ptr = get_end_ptr(res);
    *ptr = dot;
    ++ptr;
    s21_memcpy(ptr, fraction_str, fraction_str_len);
    free(fraction_str);
  }

  free(integer_str);
  return res;
}

char *s21_fraction_to_char(long double fraction, int precision,
                           bool *need_int_round) {
  char *res = S21_NULL;
  double base = 10.0;

  long double precision_multiplier = powl(10, precision);
  fraction *= precision_multiplier;
  // round their argument to an integer
  // using the current rounding direction (see fesetround(3))
  fraction = rintl(fraction);
  if (fabsl(fraction - precision_multiplier) < DBL_ZERO) {
    fraction = 0;
    *need_int_round = true;
  }

  long double log_base = (fraction != 0) ? log10l(fraction) : 0.0;
  int numbers_str_lenght = floorl(log_base) + 1;

  // Количество ведущих нулей
  int leading_zeroes_count = 0;
  if (precision > numbers_str_lenght) {
    leading_zeroes_count = precision - numbers_str_lenght;
  }

  int res_str_lenght = numbers_str_lenght + leading_zeroes_count;
  res = (char *)calloc(res_str_lenght + 1, sizeof(char));

  if (res == S21_NULL) return S21_NULL;

  if (fraction < DBL_ZERO) {
    s21_memset(res, '0', res_str_lenght);
    leading_zeroes_count = 0;
  }

  while (fraction > DBL_ZERO) {
    --res_str_lenght;
    res[res_str_lenght] = (int)fmodl(fraction, base) + '0';
    fraction = floorl(fraction / base);
  }

  while (leading_zeroes_count != 0) {
    --res_str_lenght;
    --leading_zeroes_count;
    res[res_str_lenght] = '0';
  }

  return res;
}

char *s21_integer_to_char(long double integer) {
  char *res = S21_NULL;
  long double base = 10.0;

  double log_base = (integer != 0) ? log10(integer) : 0.0L;
  s21_size_t numbers_str_lenght = floor(log_base) + 1;

  res = (char *)calloc(numbers_str_lenght + 1, sizeof(char));
  if (res == S21_NULL) return S21_NULL;

  if (integer < DBL_ZERO) {
    s21_memset(res, '0', numbers_str_lenght);
  }

  while (integer > DBL_ZERO) {
    --numbers_str_lenght;
    int number = (int)fmodl(integer, base);
    res[numbers_str_lenght] = number + '0';
    // Здесь ошибка, возникающая при делении больших чисел на 10
    integer = floorl(integer / base);
  }

  return res;
}

long double s21_atold(const char *nptr) {
  int sign = 1;
  if (*nptr == '+') ++nptr;

  if (*nptr == '-') {
    ++nptr;
    sign *= -1;
  }

  if (is_float_nan(nptr)) {
    return NAN * sign;
  }

  if (is_float_inf(nptr)) {
    return INFINITY * sign;
  }

  long double res = 0.0;
  int ten_pow_int = get_len_valid_int(nptr) - 1;

  while (ten_pow_int >= 0) {
    res += (*nptr - CHAR_SHIFT_NUM) * powl(10, ten_pow_int);
    --ten_pow_int;
    ++nptr;
  }

  if (*nptr == '.') {
    nptr++;

    int point_nums = get_len_valid_int(nptr);
    int ten_pow_mant = -1;

    while (abs(ten_pow_mant) <= point_nums) {
      res += (*nptr - CHAR_SHIFT_NUM) * powl(10, ten_pow_mant);
      --ten_pow_mant;
      nptr++;
    }
  }

  if (*nptr == 'e' || *nptr == 'E') {
    nptr++;

    int e_sign = 1;
    if (*nptr == '+') ++nptr;

    if (*nptr == '-') {
      ++nptr;
      e_sign *= -1;
    }

    int e_nums = get_len_valid_int(nptr);
    if (e_nums != 0) {
      char buff[CONVER_BUFF_SIZE] = {0};
      s21_strncpy(buff, nptr, e_nums);

      int e_val = (int)s21_atoll(buff);
      if (e_val != 0) {
        res *= powl(10, (e_sign * e_val));
      }
    }
  }

  return res * sign;
}