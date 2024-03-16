#include "s21_converters.h"
#include "s21_sprintf.h"

static int get_negative_pow_ten_counter(long double x);
static int get_positive_pow_ten_counter(long double x);

char *get_e_notation(Sprintf_params *params, long double x) {
  char *res = S21_NULL;

  bool is_negative = (x < 0);
  bool is_e_negative = (fabsl(x) < 1);

  int pow_ten = 0;
  int res_len = 0;
  long double k_number = 0;

  if (is_e_negative) {
    pow_ten = (x == 0) ? 0 : get_negative_pow_ten_counter(x);
    // precision + dot + integer (1) + sign + '\0'
    res_len = params->precision.number + 1 + 1 + is_negative + 1;
  } else {
    pow_ten = get_positive_pow_ten_counter(x);
    res_len = pow_ten + is_negative + 1;
  }

  k_number = x * powl(10, -pow_ten);

  // Проверить, что при округлении до precision не получили 10
  if (is_e_negative) {
    int check_multiplier = powl(10, params->precision.number);
    int check_k_number = roundl(k_number * check_multiplier) / check_multiplier;
    if (check_k_number >= 10) {
      k_number /= 10;
      ++pow_ten;
    }
  }

  char *format = S21_NULL;
  if (params->flags.hash) {
    format = (params->spec.E) ? "%#.*LfE%+0.2d" : "%#.*Lfe%+0.2d";
  } else {
    format = (params->spec.E) ? "%.*LfE%+0.2d" : "%.*Lfe%+0.2d";
  }

  res = calloc(res_len + 30,
               sizeof(char));  // +20 исключает ошибку Invalid read of size 1
  if (res == S21_NULL) return S21_NULL;

  int k = s21_sprintf(res, format, params->precision.number, k_number, pow_ten);

  return (k == -1) ? S21_NULL : res;
}

long double get_e_notation_coeff(long double x, int precision) {
  bool is_e_negative = (fabsl(x) < 1);

  int pow_ten = 0;
  long double k_number = 0;

  if (is_e_negative) {
    pow_ten = (x == 0) ? 0 : get_negative_pow_ten_counter(x);
  } else {
    pow_ten = get_positive_pow_ten_counter(x);
  }

  k_number = x * powl(10, -pow_ten);

  // Проверить, что при округлении до precision не получили 10
  if (is_e_negative) {
    int check_multiplier = powl(10, precision);
    int check_k_number = roundl(k_number * check_multiplier) / check_multiplier;
    if (check_k_number >= 10) {
      k_number /= 10;
    }
  }
  return k_number;
}

int get_negative_pow_ten_counter(long double x) {
  int counter = 0;
  int tmp = 0;

  while (tmp == 0) {
    ++counter;
    x *= 10;
    tmp = (int)x;
  }

  //
  return -1 * counter;
}

int get_positive_pow_ten_counter(long double x) {
  int counter = 0;
  counter = (int)floorl(log10l(fabsl(x)));
  return counter;
}