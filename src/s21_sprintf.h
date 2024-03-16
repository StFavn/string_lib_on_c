#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_formatter_params.h"
#include "s21_string.h"

typedef struct Sprintf_params {
  Specifiers spec;
  Flags flags;
  Width width;
  Precision precision;
  Lenght lenght;
} Sprintf_params;

/// Get E notation string
char *get_e_notation(Sprintf_params *params, long double x);
long double get_e_notation_coeff(long double x, int precision);

// Sprintf handlers
char *width_handler(Sprintf_params *params, char *format_arg,
                    int *format_arg_len, int space_count_add,
                    bool is_positive_number);

char *dest_format_data_adder(char *dest_start, char *format_arg,
                             int format_arg_len, int *print_counter);

void handle_star_flag(Sprintf_params *params, va_list va);
char *handle_specifier(Sprintf_params *params, char *dest_start, char *dest,
                       va_list va, int *print_counter);

char *spec_percent_handler(char *dest, int *print_counter);
char *spec_s_handler(Sprintf_params *params, char *dest_start, char *dest,
                     const char *data, int *print_counter);
char *spec_c_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter);
char *spec_d_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter);
char *spec_u_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter);
char *spec_f_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter);
char *spec_x_handler(Sprintf_params *params, char *dest_start, char *dest,
                     unsigned long long data, int *print_counter);
char *spec_o_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter);
char *spec_e_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter);
char *spec_g_handler(Sprintf_params *params, char *dest_start, char *dest,
                     va_list va, int *print_counter);
char *spec_p_handler(Sprintf_params *params, char *dest_start, char *dest,
                     unsigned long long data, int *print_counter);

char *hex_prefix_adder(char x_char, char *format_arg_str);
char *oct_prefix_adder(char *format_arg_str);
int digit_count_g_trailing_zeroes(long double x, int precision);
int digit_count_g_leading_zeroes(long double x);
int digit_count_ld_zeroes(long double x, int *digits);
int digit_count_g(long double x);

#endif  // SRC_S21_SPRINTF_H_