#ifndef SRC_S21_UTILS_H_
#define SRC_S21_UTILS_H_

#include "s21_formatter_params.h"
#include "s21_string.h"

#define S21_SYMBOLS_SPACES " \t\n"
#define S21_SYMBOLS_OCT_NUMS "12345670"
#define S21_SYMBOLS_DEC_NUMS "1234567890"
#define S21_SYMBOLS_HEX_NUMS "1234567890abcdefABCDEF"
#define S21_SYMBOLS_SIGNS "+-"

typedef enum s21_basic_type {
  CHAR_T,
  SHORT_INT_T,
  SHORT_UINT_T,
  INT_T,
  UINT_T,
  LONG_INT_T,
  LONG_UINT_T,
  LONG_LONG_INT_T,
  LONG_LONG_UINT_T,
  FLOAT_T,
  DOUBLE_T,
  LONG_DOUBLE_T
} s21_basic_type;

typedef enum s21_num_base_t { OCT_T, DEC_T, HEX_T } s21_num_base_t;

bool is_symbol(const char ch, const char *symbols);
bool is_float_valid(const char *num_str, Width width);
bool is_int_valid(const char *num_str, Width width);
bool is_oct_valid(const char *num_str, Width width);
bool is_hex_valid(const char *num_str, Width width);

bool is_float_nan(const char *num_str);
bool is_float_inf(const char *num_str);

s21_size_t get_len_valid_int(const char *num_str);
s21_size_t get_len_valid_float(const char *num_str);
s21_size_t get_len_valid_oct(const char *num_str);
s21_size_t get_len_valid_hex(const char *num_str);
s21_size_t get_extra_symbols_shift(const char *str, const char *symbols);

int parse_int(const char *src, void *res, s21_basic_type type, Width width,
              bool *is_token_end);
int parse_oct(const char *src, void *res, s21_basic_type type, Width width,
              bool *is_token_end);
int parse_hex(const char *src, void *res, s21_basic_type type, Width width,
              bool *is_token_end);
int parse_float(const char *src, void *res, s21_basic_type type, Width width,
                bool *is_token_end);
int parse_char(const char *src, char *res);
int parse_str(const char *src, char *res, Width width, bool *is_str_end);

#endif  // SRC_S21_UTILS_H_