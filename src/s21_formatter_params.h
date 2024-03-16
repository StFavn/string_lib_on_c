#ifndef SRC_S21_SPECIFIERS_PARAMS_H_
#define SRC_S21_SPECIFIERS_PARAMS_H_

#include <stdbool.h>

typedef struct Specifiers {
  // Character
  bool c;
  // Signed decimal integer
  bool d;
  // Signed decimal integer
  bool i;
  // Scientific notation (mantissa/exponent) using e character
  bool e;
  // Scientific notation (mantissa/exponent) using E character
  bool E;
  // Decimal floating point
  bool f;
  // Uses the shortest representation of decimal floating point
  bool g;
  // Uses the shortest representation of decimal floating point
  bool G;
  // Unsigned octal
  bool o;
  // String of characters
  bool s;
  // Unsigned decimal integer
  bool u;
  // Unsigned hexadecimal integer
  bool x;
  // Unsigned hexadecimal integer (capital letters)
  bool X;
  // Pointer address
  bool p;
  // Number of characters printed until %n occurs
  bool n;
  // Escaping a character %
  bool percent;
} Specifiers;

typedef struct Flags {
  bool minus;
  bool plus;
  bool space;
  bool hash;
  bool zero;
} Flags;

typedef struct Width {
  bool is_set;
  int number;
  bool star;
} Width;

typedef struct Precision {
  bool is_set;
  int number;
  bool star;
} Precision;

typedef struct Lenght {
  bool h;
  bool l;
  bool L;
} Lenght;

// Parse format string
char *init_flags(const char *format, Flags *flags);
char *init_width(const char *format, Width *flags);
char *init_precision(const char *format, Precision *flags);
char *init_lenght(const char *format, Lenght *flags);
char *init_specifiers(const char *format, Specifiers *flags);
char *get_end_ptr(const char *str);

bool is_valid_specifier(Specifiers spec);

#endif  // SRC_S21_SPECIFIERS_PARAMS_H_