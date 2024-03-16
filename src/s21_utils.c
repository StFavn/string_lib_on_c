#include "s21_utils.h"

#include <stdbool.h>

#include "s21_string.h"

#define NUM_BUFF_SIZE 512

bool is_symbol(const char ch, const char *symbols) {
  while (*symbols != '\0') {
    if (ch == *symbols) return true;
    symbols++;
  }

  return false;
}

bool is_float_nan(const char *num_str) {
  s21_size_t nan_len = s21_strspn(num_str, "+-nNaA");
  if (nan_len == 3) {
    if (is_symbol(num_str[0], "nN") && is_symbol(num_str[1], "aA") &&
        is_symbol(num_str[2], "nN")) {
      return true;
    }
  } else if (nan_len == 4) {
    if (is_symbol(num_str[0], S21_SYMBOLS_SIGNS) &&
        is_symbol(num_str[1], "nN") && is_symbol(num_str[2], "aA") &&
        is_symbol(num_str[3], "nN")) {
      return true;
    }
  }

  return false;
}

bool is_float_inf(const char *num_str) {
  s21_size_t inf_len = s21_strspn(num_str, "+-iInNfF");
  if (inf_len == 3) {
    if (is_symbol(num_str[0], "iI") && is_symbol(num_str[1], "nN") &&
        is_symbol(num_str[2], "fF")) {
      return true;
    }
  } else if (inf_len == 4) {
    if (is_symbol(num_str[0], S21_SYMBOLS_SIGNS) &&
        is_symbol(num_str[1], "iI") && is_symbol(num_str[2], "nN") &&
        is_symbol(num_str[3], "fF")) {
      return true;
    }
  }

  return false;
}

bool is_float_valid(const char *num_str, Width width) {
  s21_size_t len = get_len_valid_float(num_str);

  if (len == 3 || len == 4) {
    if (is_float_nan(num_str) || is_float_inf(num_str)) {
      if (width.is_set && (len > (s21_size_t)width.number)) {
        return false;
      } else {
        return true;
      }
    }
  }

  if (len == 1 && (*num_str == '.')) {
    return false;
  }

  if (len == 2 && (num_str[0] == '-' || num_str[0] == '+') &&
      !is_symbol(num_str[1], S21_SYMBOLS_DEC_NUMS)) {
    return false;
  }

  return (len != 0);
}

bool is_int_valid(const char *num_str, Width width) {
  int len = get_len_valid_int(num_str);

  if (width.is_set) {
    if (width.number == 1 && is_symbol(*num_str, S21_SYMBOLS_SIGNS))
      return false;
  }

  return (len != 0);
}

bool is_oct_valid(const char *num_str, Width width) {
  int len = get_len_valid_oct(num_str);

  if (width.is_set) {
    if (width.number == 1 && is_symbol(*num_str, S21_SYMBOLS_SIGNS))
      return false;
  }

  return (len != 0);
}

bool is_hex_valid(const char *num_str, Width width) {
  int len = get_len_valid_hex(num_str);

  if (width.is_set) {
    if (width.number == 1 && is_symbol(*num_str, S21_SYMBOLS_SIGNS))
      return false;
  }

  return (len != 0);
}

s21_size_t get_len_valid_int(const char *num_str) {
  s21_size_t len_sing = s21_strspn(num_str, S21_SYMBOLS_SIGNS);
  if (len_sing > 1) return 0;

  num_str += len_sing;

  s21_size_t len_nums = s21_strspn(num_str, S21_SYMBOLS_DEC_NUMS);
  if (len_nums == 0) return 0;

  return (len_sing + len_nums);
}

s21_size_t get_len_valid_oct(const char *num_str) {
  s21_size_t len_sing = s21_strspn(num_str, S21_SYMBOLS_SIGNS);
  if (len_sing > 1) return 0;

  num_str += len_sing;

  s21_size_t len_nums = s21_strspn(num_str, S21_SYMBOLS_OCT_NUMS);
  if (len_nums == 0) return 0;

  return (len_sing + len_nums);
}

s21_size_t get_len_valid_hex(const char *num_str) {
  s21_size_t len_sing = s21_strspn(num_str, S21_SYMBOLS_SIGNS);
  if (len_sing > 1) return 0;

  num_str += len_sing;

  s21_size_t len_pref = 0;
  if (num_str[0] == '0' && (num_str[1] == 'x' || num_str[1] == 'X')) {
    len_pref = 2;
    num_str += len_pref;
  }

  s21_size_t len_nums = s21_strspn(num_str, S21_SYMBOLS_HEX_NUMS);
  if (len_nums == 0 && len_pref == 0) return 0;

  return (len_sing + len_pref + len_nums);
}

s21_size_t get_len_valid_float(const char *num_str) {
  s21_size_t len_sing = s21_strspn(num_str, S21_SYMBOLS_SIGNS);
  if (len_sing > 1) return 0;

  num_str += len_sing;

  if (is_float_nan(num_str) || is_float_inf(num_str)) {
    s21_size_t len_na = 3;
    return len_sing + len_na;
  }

  s21_size_t len_int_part = s21_strspn(num_str, S21_SYMBOLS_DEC_NUMS);
  num_str += len_int_part;

  s21_size_t len_mant_part = 0;
  if (*num_str == '.') {
    num_str++;
    len_mant_part =
        s21_strspn(num_str, S21_SYMBOLS_DEC_NUMS) + 1;  // +1 for '.'
  }

  if (len_int_part == 0 && len_mant_part == 0 && len_sing == 1) return 0;
  if (len_int_part == 0 && len_mant_part == 0) return 0;

  num_str += (len_mant_part > 0) ? len_mant_part - 1 : 0;

  s21_size_t len_e_part = 0;
  if (*num_str == 'e' || *num_str == 'E') {
    num_str++;
    len_e_part = get_len_valid_int(num_str) + 1;  // +1 for 'e'
  }

  if (len_int_part == 0 && len_mant_part == 0) return 0;

  return (len_sing + len_int_part + len_mant_part + len_e_part);
}

s21_size_t get_extra_symbols_shift(const char *str, const char *symbols) {
  return s21_strspn(str, symbols);
}

int parse_int(const char *src, void *res, s21_basic_type type, Width width,
              bool *is_token_end) {
  int num_len = get_len_valid_int(src);
  if (width.is_set) {
    if (num_len > width.number) num_len = width.number;
  }

  if ((num_len > 0) && res != S21_NULL) {
    char buff[NUM_BUFF_SIZE] = {0};
    s21_strncpy(buff, src, num_len);

    if (type == SHORT_INT_T) {
      short *si_res = res;
      *si_res = (short)s21_atoll(buff);
    } else if (type == INT_T) {
      int *i_res = res;
      *i_res = (int)s21_atoll(buff);
    } else if (type == LONG_INT_T) {
      long *l_res = res;
      *l_res = (long)s21_atoll(buff);
    } else if (type == SHORT_UINT_T) {
      unsigned short *usi_res = res;
      *usi_res = (unsigned short)s21_atoll(buff);
    } else if (type == UINT_T) {
      unsigned int *ui_res = res;
      *ui_res = (unsigned int)s21_atoll(buff);
    } else if (type == LONG_UINT_T) {
      unsigned long *ul_res = res;
      *ul_res = s21_atoll(buff);
    }
  }

  const char next_ch = *(src + num_len);
  *is_token_end = !(is_symbol(next_ch, S21_SYMBOLS_DEC_NUMS) ||
                    is_symbol(next_ch, S21_SYMBOLS_SIGNS));

  return num_len;
}

int parse_hex(const char *src, void *res, s21_basic_type type, Width width,
              bool *is_token_end) {
  int num_len = get_len_valid_hex(src);
  if (width.is_set) {
    if (num_len > width.number) num_len = width.number;
  }

  if ((num_len > 0) && res != S21_NULL) {
    char buff[NUM_BUFF_SIZE] = {0};
    s21_strncpy(buff, src, num_len);

    if (type == SHORT_INT_T) {
      short *si_res = res;
      *si_res = (short)s21_atoll_hex(buff);
    } else if (type == INT_T) {
      int *i_res = res;
      *i_res = (int)s21_atoll_hex(buff);
    } else if (type == LONG_INT_T) {
      long *l_res = res;
      *l_res = (long)s21_atoll_hex(buff);
    }
  }

  const char next_ch = *(src + num_len);
  *is_token_end = !(is_symbol(next_ch, S21_SYMBOLS_HEX_NUMS) ||
                    is_symbol(next_ch, S21_SYMBOLS_SIGNS));

  return num_len;
}

int parse_oct(const char *src, void *res, s21_basic_type type, Width width,
              bool *is_token_end) {
  int num_len = get_len_valid_oct(src);
  if (width.is_set) {
    if (num_len > width.number) num_len = width.number;
  }

  if ((num_len > 0) && res != S21_NULL) {
    char buff[NUM_BUFF_SIZE] = {0};
    s21_strncpy(buff, src, num_len);

    if (type == SHORT_INT_T) {
      short *si_res = res;
      *si_res = (short)s21_atoll_oct(buff);
    } else if (type == INT_T) {
      int *i_res = res;
      *i_res = (int)s21_atoll_oct(buff);
    } else if (type == LONG_INT_T) {
      long *l_res = res;
      *l_res = (long)s21_atoll_oct(buff);
    }
  }

  const char next_ch = *(src + num_len);
  *is_token_end = !(is_symbol(next_ch, S21_SYMBOLS_OCT_NUMS) ||
                    is_symbol(next_ch, S21_SYMBOLS_SIGNS));

  return num_len;
}

void write_float(void *res, long double val, s21_basic_type type) {
  if (type == FLOAT_T) {
    float *f_res = res;
    *f_res = val;
  } else if (type == LONG_DOUBLE_T) {
    long double *ld_res = res;
    *ld_res = val;
  }
}

int parse_float(const char *src, void *res, s21_basic_type type, Width width,
                bool *is_token_end) {
  int num_len = get_len_valid_float(src);
  if (width.is_set) {
    if (num_len > width.number) num_len = width.number;
  }

  if ((num_len > 0) && res != S21_NULL) {
    char buff[NUM_BUFF_SIZE] = {0};
    s21_strncpy(buff, src, num_len);
    long double num_ld = s21_atold(buff);

    write_float(res, num_ld, type);
  }

  const char next_ch = *(src + num_len);
  *is_token_end =
      !(is_symbol(next_ch, S21_SYMBOLS_DEC_NUMS) || is_symbol(next_ch, ".") ||
        is_symbol(next_ch, S21_SYMBOLS_SIGNS));

  return num_len;
}

int parse_char(const char *src, char *res) {
  if (res != S21_NULL) {
    *res = *src;
  }

  return 1;
}

int parse_str(const char *src, char *res, Width width, bool *is_token_end) {
  int i = 0;
  while (!is_symbol(src[i], S21_SYMBOLS_SPACES) && (src[i] != '\0')) {
    if (width.is_set && (width.number <= 0)) break;

    if (res != S21_NULL) res[i] = src[i];

    i++;
    if (width.is_set) width.number--;
  }

  if (res != S21_NULL) res[i] = '\0';
  *is_token_end = is_symbol(src[i], S21_SYMBOLS_SPACES) || (src[i] == '\0');
  return i;
}
