#include "s21_sprintf.h"

#define NIL_STR "(nil)"

// https://www.ibm.com/docs/en/zos/2.1.0?topic=programs-sprintf-format-write-data
// FORMAT
// % <-flags-> <-width-> <-.-precision-> <-optional-> <-type->

char *init_sprintf_params(const char *format, Sprintf_params *params) {
  char *res = (char *)format;

  if (*res == '%') {
    res++;
    res = init_flags(res, &params->flags);          // <-flags->
    res = init_width(res, &params->width);          // <-width->
    res = init_precision(res, &params->precision);  // <-.-precision->
    res = init_lenght(res, &params->lenght);        // <-optional->
    res = init_specifiers(res, &params->spec);      // <-type->
  }

  return res;
}

int s21_sprintf(char *str, const char *format, ...) {
  if (str == S21_NULL || format == S21_NULL) return -1;

  char *str_start = str;
  va_list va;
  va_start(va, format);

  int print_counter = 0;
  while (*format != '\0') {
    if (*format == '%') {
      Sprintf_params params = {0};
      format = init_sprintf_params(format, &params);

      if (is_valid_specifier(params.spec)) {
        handle_star_flag(&params, va);
        str = handle_specifier(&params, str_start, str, va, &print_counter);
      }
    } else {
      *str = *format;
      ++format;
      ++str;
      ++print_counter;
    }
  }

  *str = '\0';
  va_end(va);
  return print_counter;
}

unsigned long long get_ull_data(Lenght lenght, va_list va) {
  unsigned long long data = 0;

  if (lenght.h) {
    data = (unsigned short)va_arg(va, int);
  } else if (lenght.l) {
    data = va_arg(va, unsigned long);
  } else {
    data = va_arg(va, unsigned int);
  }

  return data;
}

void handle_star_flag(Sprintf_params *params, va_list va) {
  if (params->width.star) {
    params->width.number = va_arg(va, int);
  }

  if (params->precision.star) {
    params->precision.number = va_arg(va, int);
  }
}

char *handle_specifier(Sprintf_params *params, char *dest_start, char *dest,
                       va_list va, int *print_counter) {
  if (params->spec.percent) {
    dest = spec_percent_handler(dest, print_counter);
  } else if (params->spec.s) {
    const char *data = va_arg(va, const char *);
    dest = spec_s_handler(params, dest_start, dest, data, print_counter);
  } else if (params->spec.c) {
    dest = spec_c_handler(params, dest_start, dest, va, print_counter);
  } else if (params->spec.d || params->spec.i) {
    dest = spec_d_handler(params, dest_start, dest, va, print_counter);
  } else if (params->spec.u) {
    dest = spec_u_handler(params, dest_start, dest, va, print_counter);
  } else if (params->spec.f) {
    dest = spec_f_handler(params, dest_start, dest, va, print_counter);
  } else if (params->spec.e || params->spec.E) {
    dest = spec_e_handler(params, dest_start, dest, va, print_counter);
  } else if (params->spec.x || params->spec.X) {
    unsigned long long data = get_ull_data(params->lenght, va);
    dest = spec_x_handler(params, dest_start, dest, data, print_counter);
  } else if (params->spec.g || params->spec.G) {
    dest = spec_g_handler(params, dest_start, dest, va, print_counter);
  } else if (params->spec.p) {
    Lenght len = {.l = true};
    unsigned long long data = get_ull_data(len, va);
    dest = spec_p_handler(params, dest_start, dest, data, print_counter);
  } else if (params->spec.o) {
    dest = spec_o_handler(params, dest_start, dest, va, print_counter);
  }

  return dest;
}

char *spec_percent_handler(char *dest, int *counter) {
  *dest = '%';
  *counter += 1;

  return dest + 1;
}

char *spec_s_handler(Sprintf_params *params, char *dest_start, char *dest,
                     const char *data, int *counter) {
  s21_size_t data_len = s21_strlen(data);

  char *data_copy = (char *)calloc(data_len + 1, sizeof(char));
  s21_strncpy(data_copy, data, data_len + 1);
  int data_copy_len = s21_strlen(data_copy);

  if (params->precision.is_set) {
    data_copy_len = (params->precision.number > data_copy_len)
                        ? data_copy_len
                        : params->precision.number;
  }

  int space_count_add = 0;
  if (params->width.number) {
    if (params->precision.number < params->width.number) {
      space_count_add = 0;
    }
    data_copy = width_handler(params, data_copy, &data_copy_len,
                              space_count_add, false);
  }

  dest = dest_format_data_adder(dest_start, data_copy, data_copy_len, counter);

  return dest;
}

char *spec_c_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter) {
  char *data = (char *)calloc(2, sizeof(char));
  data[0] = va_arg(va, int);

  int data_len = s21_strlen(data);
  int space_width_add = 0;

  if (params->width.number) {
    data = width_handler(params, data, &data_len, space_width_add, false);
  }

  dest = dest_format_data_adder(dest_start, data, data_len, print_counter);

  return dest;
}

char *spec_d_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter) {
  long long int data = 0;
  // LENGHT
  if (params->lenght.h) {
    data = (short)va_arg(va, int);
  } else if (params->lenght.l) {
    data = va_arg(va, long long int);
  } else {
    data = va_arg(va, int);
  }

  // CASE: precision == 0 && argument == 0
  bool is_zero_and_zero_prec =
      (params->precision.is_set && params->precision.number == 0) &&
      (data == 0);

  char *data_str = S21_NULL;

  if (params->precision.is_set && !params->precision.number) {
    if (params->flags.zero && (params->flags.space || params->flags.plus)) {
      params->flags.zero = false;
    }
  }

  // FLAGS
  bool flags_zero = params->flags.zero;
  bool flags_minus = params->flags.minus;
  if ((flags_zero && !flags_minus) || params->precision.number) {
    data_str = s21_itoa_abs(data, 10, false);
  } else {
    data_str = s21_itoa(data, 10, params->flags.plus && !is_zero_and_zero_prec,
                        params->flags.space && !is_zero_and_zero_prec, false);
  }

  if (data_str == S21_NULL) return S21_NULL;

  bool is_positive_number = (data >= 0);
  int data_len = s21_strlen(data_str);
  int space_width_add = 0;

  // PRECISION
  if (params->precision.number != 0) {
    // Флаг 0 выключается при указании точности
    params->flags.zero = false;
    int shift = 0;  // Смещение для заполнение строки ведущими нулями
    int sprintf_params_shift = (params->flags.plus || params->flags.space);
    int prec_width = data_len;

    if ((data_len >= params->precision.number) &&
        (params->flags.plus || params->flags.space)) {
      // Добавляем знак к строке
      ++prec_width;
    } else if (data_len < params->precision.number) {
      prec_width = params->precision.number + sprintf_params_shift;
      shift = prec_width - data_len - sprintf_params_shift;
    }

    char *data_str_tmp = (char *)calloc(prec_width + shift + 1, sizeof(char));
    char *ptr = data_str_tmp;

    if (sprintf_params_shift == 1) {
      if (params->flags.plus) {
        data_str_tmp[0] = (is_positive_number) ? '+' : '-';
      } else {
        data_str_tmp[0] = (is_positive_number) ? ' ' : '-';
      }
      ++ptr;
    } else {
      if (!is_positive_number) {
        data_str_tmp[0] = '-';
        ++ptr;
      }
    }

    if (shift) {
      s21_memset(ptr, '0', shift);
      ptr += shift;
    }

    s21_memcpy(ptr, data_str, data_len + 1);
    if (data_str != S21_NULL) free(data_str);
    data_str = data_str_tmp;
    data_len = s21_strlen(data_str);
  }

  bool need_add_check = true;
  if (is_zero_and_zero_prec) {
    need_add_check = false;
    if (params->flags.plus) {
      data_str[0] = '+';
    } else if (params->flags.space) {
      data_str[0] = ' ';
    } else if (params->width.number) {
      data_str[0] = ' ';
    } else {
      free(data_str);
      return dest;
    }
  }

  // WIDTH
  if (params->width.number) {
    // Дополнительная проверка заданной ширины - если она меньше, либо равна
    // длине числа: сформируем строку заново с учётом флагов
    if (need_add_check) {
      if ((data_len >= params->width.number) && (!params->precision.number)) {
        free(data_str);

        data_str =
            s21_itoa(data, 10, params->flags.plus, params->flags.space, false);
        data_len = s21_strlen(data_str);
      }
    }

    data_str = width_handler(params, data_str, &data_len, space_width_add,
                             is_positive_number);
  }

  // FINISH
  dest = dest_format_data_adder(dest_start, data_str, data_len, print_counter);

  return dest;
}

char *spec_u_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter) {
  // Флаги +, ' ' не применимы
  params->flags.plus = false;
  params->flags.space = false;

  unsigned long long data = 0;

  // LENGHT
  if (params->lenght.h) {
    data = (unsigned short)va_arg(va, int);
  } else if (params->lenght.l) {
    data = va_arg(va, unsigned long int);
  } else {
    data = va_arg(va, unsigned int);
  }

  int base = 10;
  bool is_hex_big = false;

  char *data_str = s21_uitoa_abs(data, base, is_hex_big);
  if (data_str == S21_NULL) return S21_NULL;

  int data_len = s21_strlen(data_str);
  int space_width_add = 0;

  // PRECISION
  if (params->precision.number) {
    // Флаг 0 выключается при указании точности
    params->flags.zero = false;
    int shift = 0;  // Смещение для заполнение строки ведущими нулями
    int prec_width = data_len;

    if (data_len < params->precision.number) {
      shift = params->precision.number - data_len;
    }

    // + shift + 1 -> иначе valgrind: Invalid write of size 1
    char *data_str_tmp = (char *)calloc(prec_width + shift + 1, sizeof(char));
    char *ptr = data_str_tmp;

    if (shift) {
      s21_memset(ptr, '0', shift);
      ptr += shift;
    }

    s21_memcpy(ptr, data_str, data_len);
    if (data_str != S21_NULL) free(data_str);
    data_str = data_str_tmp;
    data_len = s21_strlen(data_str);
  }

  // WIDTH
  if (params->width.number) {
    data_str =
        width_handler(params, data_str, &data_len, space_width_add, true);
  }

  // FINISH
  dest = dest_format_data_adder(dest_start, data_str, data_len, print_counter);

  return dest;
}

char *spec_f_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter) {
  long double data = 0;
  double sign = 1.0;
  char *data_str = S21_NULL;

  if (params->lenght.L) {
    data = va_arg(va, long double);
  } else {
    // При прямой записи va типа double в переменную
    // long double возникает ошибка;
    double tmp = va_arg(va, double);
    data = (long double)tmp;
  }

  if (isnan(data)) {
    data = 0.0;
  }

  if (!params->precision.number && !params->precision.is_set)
    params->precision.number = 6;

  if (params->flags.minus) {
    // Флаг 0 выключается при выравнивании по правому краю
    params->flags.zero = false;
  }

  if (params->width.number) {
    int check_delta = (data < 0) ? 3 : 2;
    // +2: 0. <- эти два символа
    // +3: -1. <- эти три символа
    if ((params->precision.number != 0) &&
        (params->width.number <= params->precision.number + check_delta)) {
      params->width.number = 0;
      params->flags.zero = false;
    }
  } else {
    // Ширина не задана - отключить заполнение нулями
    params->flags.zero = false;
  }

  if (params->flags.zero && (data < 0)) {
    // Сформировать строку по модулю числа
    // Для указания знака перед ведущими нулями
    sign = -1;
    params->flags.plus = true;
  }

  data_str = s21_ditoa(data * sign, params->precision.number);
  if (data_str == S21_NULL) {
    return S21_NULL;
  }

  int data_len = s21_strlen(data_str);
  int space_width_add = 0;

  // HASH FLAG
  if (params->flags.hash &&
      (params->precision.is_set && params->precision.number == 0)) {
    char *tmp = calloc(data_len + 2, sizeof(char));
    s21_memcpy(tmp, data_str, data_len);
    char *ptr = get_end_ptr(tmp);
    *ptr = '.';
    free(data_str);
    data_str = tmp;
    data_len = s21_strlen(data_str);
  }

  if (data_len >= params->width.number) {
    params->flags.zero = false;
  }

  if (!params->flags.zero && (params->flags.plus || params->flags.space)) {
    char number_sign = '@';

    if (data >= 0) {
      int tmp_char_len = data_len + 1;
      char *tmp_str = (char *)calloc(tmp_char_len, sizeof(char));
      char *ptr = tmp_str;

      if (params->flags.plus) {
        number_sign = '+';
      } else if (params->flags.space) {
        number_sign = ' ';
      }

      *ptr = number_sign;
      ++ptr;
      s21_memcpy(ptr, data_str, data_len);
      free(data_str);
      data_str = tmp_str;
      ++data_len;
    }
  }

  // WIDTH
  if (params->width.number) {
    bool is_positive_number = (data >= 0);
    data_str = width_handler(params, data_str, &data_len, space_width_add,
                             is_positive_number);
  }

  // FINISH
  dest = dest_format_data_adder(dest_start, data_str, data_len, print_counter);

  return dest;
}

char *spec_e_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter) {
  long double data = 0;
  char *data_str = S21_NULL;
  double sign = 1.0;

  // LENGTH
  if (params->lenght.L) {
    data = va_arg(va, long double);
  } else {
    // При прямой записи va типа double в переменную
    // long double возникает ошибка;
    double tmp = va_arg(va, double);
    data = (long double)tmp;
  }

  if (!params->precision.number && !params->precision.is_set)
    params->precision.number = 6;

  if (params->flags.minus) {
    // Флаг 0 выключается при выравнивании по правому краю
    params->flags.zero = false;
  }

  data_str = get_e_notation(params, data * sign);
  if (data_str == S21_NULL) return S21_NULL;
  int data_len = s21_strlen(data_str);
  int space_width_add = 0;

  if (params->width.number) {
    if (params->width.number <= data_len) {
      // +2: 0. <- эти два символа
      params->width.number = 0;
      params->flags.zero = false;
    }
  } else {
    // Ширина не задана - отключить заполнение нулями
    params->flags.zero = false;
  }

  if (params->flags.zero && (data < 0)) {
    // Сформировать строку по модулю числа
    // Для указания знака перед ведущими нулями
    sign = -1;
    params->flags.plus = true;
    if (data_str) {
      free(data_str);
    }
    data_str = get_e_notation(params, data * sign);
    if (data_str == S21_NULL) return S21_NULL;
    data_len = s21_strlen(data_str);
  }

  if (!params->flags.zero && (params->flags.plus || params->flags.space)) {
    char number_sign = '@';

    if (data >= 0) {
      int tmp_char_len = data_len + 1;
      char *tmp_str =
          (char *)calloc(tmp_char_len + 1, sizeof(char));  // +1 valgrind
      char *ptr = tmp_str;

      if (params->flags.plus) {
        number_sign = '+';
      } else if (params->flags.space) {
        number_sign = ' ';
      }

      *ptr = number_sign;
      ++ptr;
      s21_memcpy(ptr, data_str, data_len);
      free(data_str);
      data_str = tmp_str;
      ++data_len;
    }
  }

  if (data_len > params->width.number) {
    params->flags.zero = false;
  }

  // WIDTH
  if (params->width.number) {
    bool is_positive_number = (data >= 0);
    data_str = width_handler(params, data_str, &data_len, space_width_add,
                             is_positive_number);
  }

  // FINISH
  dest = dest_format_data_adder(dest_start, data_str, data_len, print_counter);
  return dest;
}

char *spec_x_handler(Sprintf_params *params, char *dest_start, char *dest,
                     unsigned long long data, int *print_counter) {
  // Флаги +, ' ' не применимы
  params->flags.plus = false;
  params->flags.space = false;

  // Если значение 0 флаг # не применим
  if (data == 0) params->flags.hash = false;
  // Если флаг '-' флаг 0 не применим
  if (params->flags.minus) params->flags.zero = false;

  int base = 16;
  bool is_hex_big = (params->spec.X);
  int hex_prefix_len = (params->flags.hash) ? 2 : 0;

  char *data_str = s21_uitoa_abs(data, base, is_hex_big);
  if (data_str == S21_NULL) return S21_NULL;

  int data_len = s21_strlen(data_str);
  int space_width_add = 0;

  // Учесть выставление флага # для width_handler
  if ((data_len + hex_prefix_len) >= params->width.number) {
    params->flags.zero = false;
  }

  // PRECISION
  if (params->precision.number) {
    // Флаг 0 выключается при указании точности
    params->flags.zero = false;
    int shift = 0;  // Смещение для заполнение строки ведущими нулями
    int prec_width = data_len;

    if (data_len < params->precision.number) {
      shift = params->precision.number - data_len;
    }

    // + shift + 1 -> иначе valgrind: Invalid write of size 1
    char *data_str_tmp = (char *)calloc(prec_width + shift + 1, sizeof(char));
    char *ptr = data_str_tmp;

    if (shift) {
      s21_memset(ptr, '0', shift);
      ptr += shift;
    }

    s21_memcpy(ptr, data_str, data_len);
    if (data_str != S21_NULL) free(data_str);
    data_str = data_str_tmp;
    data_len = s21_strlen(data_str);
  }

  // Если нет флага 0 -> добавить перед числом 0x
  if (params->flags.hash && !params->flags.zero) {
    char x_char = (params->spec.X) ? 'X' : 'x';
    data_str = hex_prefix_adder(x_char, data_str);
    data_len = s21_strlen(data_str);
  }

  // WIDTH
  if (params->width.number) {
    data_str =
        width_handler(params, data_str, &data_len, space_width_add, true);
  }

  // Заменить первые два символа на '0x' если:
  // ширина была заполнена нулями.
  if (params->flags.hash && params->flags.zero) {
    char x_char = (params->spec.X) ? 'X' : 'x';
    data_str[0] = '0';
    data_str[1] = x_char;
  }

  // FINISH
  dest = dest_format_data_adder(dest_start, data_str, data_len, print_counter);

  return dest;
}

char *spec_g_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter) {
  long double data = 0;
  va_list va_data_copy;
  va_copy(va_data_copy, va);
  char *res = S21_NULL;

  // LENGTH
  if (params->lenght.L) {
    data = va_arg(va_data_copy, long double);
  } else {
    // При прямой записи va типа double в переменную
    // long double возникает ошибка;
    double tmp = va_arg(va_data_copy, double);
    data = (long double)tmp;
  }

  va_end(va_data_copy);
  // Если data > 1: подсчитать количество цифр до точки, если их больше 7
  // -> %e Если data < 1: подсичтать количество цифр после точки, если их
  // больше 9 -> %e
  int count_digits_integral = 0;
  int count_digits_fract = 0;

  if (fabsl(data) >= 1 || data == 0) {
    count_digits_integral = digit_count_g(data);

    // params->precision.number > длины числа; например %.15g для
    // 123456789012323 в этом случае должны попасть в %f
    if (!params->precision.is_set) {
      params->precision.is_set = true;
      params->precision.number = 6;
    }

    // int check_prec_len = (params->precision.number < 8) ? 8 :
    // params->precision.number;
    int check_prec_len = params->precision.number;
    int precision_data = 0;

    bool check_lenght = ((count_digits_integral > check_prec_len) && data);

    // count_digits_integral >= 7
    if (check_lenght || (params->precision.number &&
                         (count_digits_integral > params->precision.number))) {
      // %e
      if (params->spec.g) {
        params->spec.e = true;
      } else if (params->spec.G) {
        params->spec.E = true;
      }

      params->spec.g = false;
      params->spec.G = false;

      int prec_coeff = 0;

      if (!params->precision.is_set) {
        params->precision.is_set = true;
        prec_coeff = 9;
      } else {
        if (params->precision.number == 0) {
          params->precision.number = 1;
        }
        prec_coeff = params->precision.number;
        if (prec_coeff > 1) --prec_coeff;
      }

      long double tmp = get_e_notation_coeff(data, prec_coeff);
      precision_data = digit_count_g_trailing_zeroes(tmp, prec_coeff);

      if (!params->precision.number) {
        params->precision.number = (precision_data > 5) ? 5 : precision_data;
      } else {
        if (precision_data != params->precision.number) {
          params->precision.number = precision_data;
        } else {
          --params->precision.number;
        }
      }

      res = spec_e_handler(params, dest_start, dest, va, print_counter);

    } else {
      // %f
      params->spec.g = false;
      params->spec.G = false;
      params->spec.f = true;

      if (!params->precision.is_set) {
        params->precision.is_set = true;
      }

      // Количество цифр до точки
      int count_digits = digit_count_g(data);
      // Количество цифр после точки
      int count_digits_t_zeroes = digit_count_g_trailing_zeroes(data, 9);
      // Всего чисел дожно быть не больше 6
      precision_data = 6 - count_digits;  // TODO разобраться с шестёркой
      if (precision_data < 0) precision_data = 0;

      if (precision_data) {
        precision_data = (count_digits_t_zeroes < precision_data)
                             ? count_digits_t_zeroes
                             : precision_data;
      }

      if (params->flags.hash && params->width.number) {
        // precision_data = (data == 0) ? 5 : 4;

        int integral_digits = digit_count_g(data);
        precision_data = params->precision.number - integral_digits;

        if ((data == 0) && (params->precision.number == 0)) precision_data = 0;
      } else if (params->flags.hash) {
        precision_data += 5;
        if ((data == 0) && (params->precision.number == 0)) precision_data = 0;
      }

      params->precision.number = precision_data;
      res = spec_f_handler(params, dest_start, dest, va, print_counter);
    }

  } else {
    count_digits_fract = digit_count_g_leading_zeroes(data);
    // int precision_data = 0;

    if (count_digits_fract > 9) {
      // %e
      if (params->spec.g) {
        params->spec.e = true;
        params->spec.g = false;
      } else if (params->spec.G) {
        params->spec.E = true;
        params->spec.G = false;
      }

      if (!params->precision.is_set) {
        params->precision.is_set = true;
      }

      long double tmp = get_e_notation_coeff(data, 9);
      int precision_data = digit_count_g_trailing_zeroes(tmp, 9);

      if (params->flags.hash) {
        precision_data = 5;
      }

      params->precision.number = (precision_data > 5) ? 5 : precision_data;

      res = spec_e_handler(params, dest_start, dest, va, print_counter);
    } else {
      // %f
      params->spec.g = false;
      params->spec.G = false;
      params->spec.f = true;

      if (!params->precision.is_set) {
        params->precision.is_set = true;
        int precision_data = count_digits_fract;

        if (params->flags.hash) {
          // Подсчитать количество ведущих нулей и число цифр
          // Максимальное значение precision: 9
          // 000 + 123456 : три ведущих нуля + 6 цифр после
          // Числа с количеством ведущих нулей от 4-х в это условие не попадают
          int zeroes_count = 0;
          int digit_count = 0;
          zeroes_count = digit_count_ld_zeroes(data, &digit_count);
          digit_count = (digit_count > 6) ? 6 : digit_count;
          precision_data = zeroes_count + digit_count;
        }

        params->precision.number = precision_data;
      } else {
        // Необходимо подсчитать количество ведущих нулей после точки
        // Если их число <= 3 и params->precision.number <= 3 - то
        // ++params->precision.number

        int precision_data = 0;
        int count_zeroes = digit_count_ld_zeroes(data, &precision_data);

        if ((count_zeroes && count_zeroes <= 3) &&
            (count_zeroes >= params->precision.number)) {
          precision_data = count_zeroes + 1;
        } else {
          precision_data =
              digit_count_g_trailing_zeroes(data, params->precision.number);
        }

        // int precision_data = digit_count_g_trailing_zeroes(data,
        // params->precision.number);
        params->precision.number = precision_data;
      }

      res = spec_f_handler(params, dest_start, dest, va, print_counter);
    }
  }
  return res;
}

char *spec_p_handler(Sprintf_params *params, char *dest_start, char *dest,
                     unsigned long long data, int *print_counter) {
  char *res = S21_NULL;
  if (data == 0) {
    res = spec_s_handler(params, dest_start, dest, NIL_STR, print_counter);
  } else {
    // Not usable parameters:
    // 1. Precision
    // 2. Flags: +, #, 0, ' '
    // 3. Lenght: l, L, h
    // Disable unusable params
    params->precision.is_set = false;
    params->precision.number = 0;

    params->flags.plus = false;
    params->flags.zero = false;
    params->flags.space = false;

    params->lenght.h = false;
    params->lenght.L = false;

    // Set target format for %x
    params->flags.hash = true;
    params->lenght.l = true;
    params->spec.x = true;
    params->spec.p = false;

    res = spec_x_handler(params, dest_start, dest, data, print_counter);
  }

  return res;
}

char *spec_o_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter) {
  // Флаги +, ' ' не применимы
  params->flags.plus = false;
  params->flags.space = false;

  unsigned long long data = 0;

  // LENGHT
  if (params->lenght.h) {
    data = (unsigned short)va_arg(va, int);
  } else if (params->lenght.l) {
    data = va_arg(va, unsigned long int);
  } else {
    data = va_arg(va, unsigned int);
  }

  // Если значение 0 флаг # не применим
  if (data == 0) params->flags.hash = false;
  // Если флаг '-' флаг 0 не применим
  if (params->flags.minus) params->flags.zero = false;
  // Если задан precision флаг 0 не применим
  if (params->precision.is_set) params->flags.zero = false;

  int base = 8;
  bool is_hex_big = (params->spec.X);
  int hex_prefix_len = (params->flags.hash) ? 2 : 0;

  char *data_str = s21_uitoa_abs(data, base, is_hex_big);
  if (data_str == S21_NULL) return S21_NULL;

  int data_len = s21_strlen(data_str);
  int space_width_add = 0;

  // Учесть выставление флага # для width_handler
  if ((data_len + hex_prefix_len) >= params->width.number) {
    params->flags.zero = false;
  }

  // PRECISION
  if (params->precision.number) {
    // Флаг 0 выключается при указании точности
    params->flags.zero = false;
    int shift = 0;  // Смещение для заполнение строки ведущими нулями
    int prec_width = data_len;

    if (data_len < params->precision.number) {
      shift = params->precision.number - data_len;
      params->flags.hash = false;
    }

    char *data_str_tmp = (char *)calloc(
        prec_width + shift +
            1,  // + shift + 1 -> иначе valgrind: Invalid write of size 1
        sizeof(char));
    char *ptr = data_str_tmp;

    if (shift) {
      s21_memset(ptr, '0', shift);
      ptr += shift;
    }

    s21_memcpy(ptr, data_str, data_len);
    if (data_str != S21_NULL) free(data_str);
    data_str = data_str_tmp;
    data_len = s21_strlen(data_str);
  }

  // Если нет флага 0 -> добавить перед числом 0
  if (params->flags.hash && !params->flags.zero) {
    data_str = oct_prefix_adder(data_str);
    data_len = s21_strlen(data_str);
  }

  // WIDTH
  if (params->width.number) {
    data_str =
        width_handler(params, data_str, &data_len, space_width_add, true);
  }

  // FINISH
  dest = dest_format_data_adder(dest_start, data_str, data_len, print_counter);

  return dest;
}

char *width_handler(Sprintf_params *params, char *data, int *data_len,
                    int space_width_add, bool is_positive_number) {
  if (*data_len <= params->width.number) {
    int spaces_count = (params->width.number - *data_len) + space_width_add;

    // Memory reallocation
    // +1: Valgrind Invalid write of size 1; +2: OK
    char *temp_ptr = calloc(*data_len + spaces_count + 2, sizeof(char));

    if (temp_ptr == S21_NULL) {
      free(data);
      return S21_NULL;
    }

    if (params->flags.minus) {
      s21_strncpy(temp_ptr, data, *data_len);
      char *last_tmp = get_end_ptr(temp_ptr);
      s21_memset(last_tmp, ' ', spaces_count);
    } else {
      char filler = (params->flags.zero) ? '0' : ' ';

      if (params->flags.zero && (params->flags.plus || params->flags.space)) {
        if (params->flags.plus) {
          temp_ptr[0] = (is_positive_number) ? '+' : '-';
        } else if (params->flags.space) {
          temp_ptr[0] = (is_positive_number) ? ' ' : '-';
        }
        for (int i = 1; i < spaces_count; ++i) {
          temp_ptr[i] = filler;
        }
      } else {
        if (spaces_count) {
          s21_memset(temp_ptr, filler, spaces_count);
        }
      }
      s21_strncat(temp_ptr, data, *data_len);
    }
    *data_len = s21_strlen(temp_ptr);
    free(data);
    data = temp_ptr;
  }

  return data;
}

char *dest_format_data_adder(char *dest_start, char *data, int data_len,
                             int *counter) {
  if (data == S21_NULL) return S21_NULL;

  s21_strncpy(dest_start + *counter, data, data_len);
  *counter += data_len;
  dest_start += *counter;
  if (data != S21_NULL) free(data);
  return dest_start;
}

char *hex_prefix_adder(char x_char, char *data_str) {
  // Если нет флага 0 -> добавить перед числом 0x
  int data_len = s21_strlen(data_str);
  int tmp_str_len = data_len + 3;
  char *res = calloc(tmp_str_len, sizeof(char));
  if (res == S21_NULL) return S21_NULL;

  res[0] = '0';
  res[1] = x_char;

  char *ptr = get_end_ptr(res);
  s21_memcpy(ptr, data_str, data_len);
  if (data_str != S21_NULL) free(data_str);

  return res;
}

char *oct_prefix_adder(char *data_str) {
  // Если нет флага 0 -> добавить перед числом 0
  int data_len = s21_strlen(data_str);
  int tmp_str_len = data_len + 2;
  char *res = calloc(tmp_str_len, sizeof(char));
  if (res == S21_NULL) return S21_NULL;

  res[0] = '0';

  char *ptr = get_end_ptr(res);
  s21_memcpy(ptr, data_str, data_len);
  if (data_str != S21_NULL) free(data_str);

  return res;
}

int digit_count_g(long double x) {
  int counter = 0;

  char *tmp = s21_ditoa(x, 9);
  if (tmp == S21_NULL) return counter;

  int indx = s21_strlen(tmp);

  for (int i = 0; i < indx; ++i) {
    if (s21_isdigit(tmp[i])) {
      ++counter;
    }
    if (tmp[i] == '.') {
      break;
    }
  }

  free(tmp);
  return counter;
}

int digit_count_g_trailing_zeroes(long double x, int precision) {
  // Максимальная точность %g (%f сценарий): 000 123456 <- три нуля после точки,
  // и шесть цифр; но, для числа 0.021 при точности 9 нули отсекаются
  int counter = 0;
  // Если precision равен нулю - установить в 1;
  // Лишняя точка будет убрана при последующей обработке
  precision = (precision == 0) ? 1 : precision;
  char *tmp = s21_ditoa(x, precision);
  if (tmp == S21_NULL) return counter;

  char *dot = s21_strchr(tmp, '.');
  ++dot;
  if (dot == S21_NULL) return counter;

  int indx = s21_strlen(dot);
  bool is_flag = false;
  for (int i = indx - 1; i >= 0; --i) {
    if (dot[i] != '0') is_flag = true;
    if (is_flag) {
      ++counter;
    }
  }

  free(tmp);
  return (counter > precision) ? precision : counter;
}

int digit_count_g_leading_zeroes(long double x) {
  // TODO для обратной совместимости предыдущей версии кода
  // Пересмотреть на предмет исключения этой функции
  int counter_numbers = 0;
  int counter_zeroes = digit_count_ld_zeroes(x, &counter_numbers);

  // Код ниже определяет условие для выбора ветки %e или %f в функции
  // spec_g_handler
  int counter_exl_trail_zeroes = digit_count_g_trailing_zeroes(x, 9);
  int counter = counter_numbers + counter_zeroes - counter_exl_trail_zeroes;

  if (counter_zeroes > 3) {
    counter = 10;
  } else {
    if (counter_exl_trail_zeroes < counter_numbers) {
      counter_numbers = counter_exl_trail_zeroes - counter_zeroes;
    }
    int numbers = (counter_numbers > 6) ? 6 : counter_numbers;
    counter = numbers + counter_zeroes;
  }
  // Максимум: 9
  // Число зависит от ведущих нулей: если 0 один, до 8, и так далее
  // int counter = 6 + counter_zeroes;
  // int counter = counter_numbers + counter_zeroes;

  return counter;
}

int digit_count_ld_zeroes(long double x, int *digits) {
  // Количество ведущих нулей в числе вида 0.0001
  // Для спецификатора %g
  int counter_zeroes = 0;
  char *tmp = s21_ditoa(x, 9);
  char *dot = s21_strchr(tmp, '.');
  ++dot;

  int indx = s21_strlen(dot);
  bool is_flag = true;
  for (int i = 0; i < indx; ++i) {
    if (dot[i] == '0' && is_flag) {
      ++counter_zeroes;
    } else {
      is_flag = false;
      ++*digits;
    }
  }

  free(tmp);
  return counter_zeroes;
}
