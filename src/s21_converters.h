#ifndef SRC_S21_CONVERTERS_H_
#define SRC_S21_CONVERTERS_H_

#include <math.h>
#include <stdlib.h>

#include "s21_string.h"

#define CHAR_SHIFT_NUM 48
#define CHAR_SHIFT_BIG_HEX 55
#define CHAR_SHIFT_SMALL_HEX 87

/* From ASCII */

int s21_atoi(const char *s);
long long s21_atoll(const char *s);

long long s21_atoll_oct(const char *s);
long long s21_atoll_hex(const char *s);

long double s21_atold(const char *s);

/* To ASCII */

/// Convert integer number to string with sign and flags
char *s21_itoa(long long int x, int base, bool sign_save, bool sign_place,
               bool is_hex_big);

/// Convert ABS integer number to string wihout sign
char *s21_itoa_abs(long long int x, int base, bool is_hex_big);
char *s21_uitoa_abs(unsigned long long int x, int base, bool is_hex_big);

/// Convert float number to string
char *s21_ditoa(long double x, int precision);
char *s21_fraction_to_char(long double fraction, int precision,
                           bool *need_int_round);
char *s21_integer_to_char(long double integer);

#endif  // SRC_S21_CONVERTERS_H_