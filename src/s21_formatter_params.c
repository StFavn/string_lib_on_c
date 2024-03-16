#include "s21_formatter_params.h"

#include "s21_string.h"

#define BUFFER_SIZE 512

char *get_end_ptr(const char *str) {
  long long int str_len = s21_strlen(str);
  char *res = (char *)str + str_len;

  return res;
}

char *init_flags(const char *format, Flags *flags) {
  const char flags_symbols[] = "-+ #0";
  while (s21_strchr(flags_symbols, *format) != S21_NULL) {
    switch (*format) {
      case '-':
        flags->minus = true;
        break;
      case '+':
        flags->plus = true;
        break;
      case ' ':
        flags->space = true;
        break;
      case '#':
        flags->hash = true;
        break;
      case '0':
        flags->zero = true;
        break;
      default:
        break;
    }

    ++format;
  }

  return (char *)format;
}

char *str_to_int(const char *str, int *res) {
  char tmp[BUFFER_SIZE] = {0};
  for (int i = 0; s21_isdigit(*str); ++i) {
    tmp[i] = *str;
    ++str;
  }

  *res = s21_atoi(tmp);
  return (char *)str;
}

char *init_width(const char *format, Width *flags) {
  if (*format == '*') {
    flags->star = true;
    ++format;
  } else if (s21_isdigit(*format)) {
    format = str_to_int(format, &flags->number);
    flags->is_set = (flags->number != 0) ? true : false;
  }

  return (char *)format;
}

char *init_precision(const char *format, Precision *flags) {
  if (*format == '.') {
    ++format;
    if (*format == '*') {
      flags->star = true;
      flags->is_set = true;
      ++format;
    } else if (s21_isdigit(*format)) {
      format = str_to_int(format, &flags->number);
      flags->is_set = true;
    } else {
      flags->number = 0;
      flags->is_set = true;
    }
  }
  return (char *)format;
}

char *init_lenght(const char *format, Lenght *flags) {
  switch (*format) {
    case 'h':
      flags->h = true;
      ++format;
      break;
    case 'l':
      flags->l = true;
      ++format;
      break;
    case 'L':
      flags->L = true;
      ++format;
      break;
    default:
      break;
  }
  return (char *)format;
}

char *init_specifiers(const char *format, Specifiers *flags) {
  switch (*format) {
    case 'c':
      flags->c = true;
      ++format;
      break;
    case 'd':
      flags->d = true;
      ++format;
      break;
    case 'i':
      flags->i = true;
      ++format;
      break;
    case 'e':
      flags->e = true;
      ++format;
      break;
    case 'E':
      flags->E = true;
      ++format;
      break;
    case 'f':
      flags->f = true;
      ++format;
      break;
    case 'g':
      flags->g = true;
      ++format;
      break;
    case 'G':
      flags->G = true;
      ++format;
      break;
    case 'o':
      flags->o = true;
      ++format;
      break;
    case 's':
      flags->s = true;
      ++format;
      break;
    case 'u':
      flags->u = true;
      ++format;
      break;
    case 'x':
      flags->x = true;
      ++format;
      break;
    case 'X':
      flags->X = true;
      ++format;
      break;
    case 'p':
      flags->p = true;
      ++format;
      break;
    case 'n':
      flags->n = true;
      ++format;
      break;
    case '%':
      flags->percent = true;
      ++format;
      break;
    default:
      break;
  }

  return (char *)format;
}

bool is_valid_specifier(Specifiers spec) {
  if (spec.c || spec.d || spec.e || spec.E || spec.f || spec.g || spec.G ||
      spec.i || spec.n || spec.o || spec.p || spec.s || spec.u || spec.x ||
      spec.X || spec.percent) {
    return true;
  }

  return false;
}