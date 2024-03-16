#include <limits.h>
#include <stdarg.h>

#include "s21_converters.h"
#include "s21_formatter_params.h"
#include "s21_string.h"
#include "s21_utils.h"

typedef enum error_t { OK = 0, ERR_BAD_SRC = 1, ERR_BAD_FORMAT = 2 } error_t;

typedef struct Sscanf_formatter {
  Width width;
  Lenght lenght;
  Specifiers spec;
} Sscanf_formatter;

typedef struct Context {
  int ch_counter;
  bool is_token_end;
} Context;

char *init_sscanf_params(const char *format, Sscanf_formatter *params) {
  char *next = (char *)format;

  next = init_width(next, &params->width);
  next = init_lenght(next, &params->lenght);
  next = init_specifiers(next, &params->spec);

  return next;
}

error_t validate_data(const char *src, Specifiers spec, Width width) {
  error_t res = ERR_BAD_SRC;

  if (spec.c || spec.s || spec.n) {
    res = OK;
  } else if (spec.f || spec.e || spec.E || spec.g || spec.G) {
    if (is_float_valid(src, width)) res = OK;
  } else if (spec.d || spec.u) {
    if (is_int_valid(src, width)) res = OK;
  } else if (spec.x || spec.X || spec.p) {
    if (is_hex_valid(src, width)) res = OK;
  } else if (spec.o) {
    if (is_oct_valid(src, width)) res = OK;
  } else if (spec.i) {
    if ((is_int_valid(src, width) || is_oct_valid(src, width) ||
         is_hex_valid(src, width)))
      res = OK;
  } else if (spec.percent) {
    if (*src == '%') res = OK;
  }

  return res;
}

int handle_int(const char *src, void *res, Sscanf_formatter params,
               Context *ctx) {
  int shift = 0;
  if (params.lenght.h) {
    shift = parse_int(src, res, SHORT_INT_T, params.width, &ctx->is_token_end);
  } else if (params.lenght.l) {
    shift = parse_int(src, res, LONG_INT_T, params.width, &ctx->is_token_end);
  } else {
    shift = parse_int(src, res, INT_T, params.width, &ctx->is_token_end);
  }

  return shift;
}

int handle_uint(const char *src, void *res, Sscanf_formatter params,
                Context *ctx) {
  int shift = 0;
  if (params.lenght.h) {
    shift = parse_int(src, res, SHORT_UINT_T, params.width, &ctx->is_token_end);
  } else if (params.lenght.l) {
    shift = parse_int(src, res, LONG_UINT_T, params.width, &ctx->is_token_end);
  } else {
    shift = parse_int(src, res, UINT_T, params.width, &ctx->is_token_end);
  }

  return shift;
}

int handle_hex(const char *src, void *res, Sscanf_formatter params,
               Context *ctx) {
  int shift = 0;
  if (params.lenght.h) {
    shift = parse_hex(src, res, SHORT_INT_T, params.width, &ctx->is_token_end);
  } else if (params.lenght.l) {
    shift = parse_hex(src, res, LONG_INT_T, params.width, &ctx->is_token_end);
  } else {
    shift = parse_hex(src, res, INT_T, params.width, &ctx->is_token_end);
  }

  return shift;
}

int handle_oct(const char *src, void *res, Sscanf_formatter params,
               Context *ctx) {
  int shift = 0;
  if (params.lenght.h) {
    shift = parse_oct(src, res, SHORT_INT_T, params.width, &ctx->is_token_end);
  } else if (params.lenght.l) {
    shift = parse_oct(src, res, LONG_INT_T, params.width, &ctx->is_token_end);
  } else {
    shift = parse_oct(src, res, INT_T, params.width, &ctx->is_token_end);
  }

  return shift;
}

int handle_float(const char *src, void *res, Sscanf_formatter params,
                 Context *ctx) {
  int shift = 0;
  if (params.lenght.L) {
    shift =
        parse_float(src, res, LONG_DOUBLE_T, params.width, &ctx->is_token_end);
  } else {
    shift = parse_float(src, res, FLOAT_T, params.width, &ctx->is_token_end);
  }

  return shift;
}

int handle_uni_num(const char *src, void *res, Sscanf_formatter params,
                   Context *ctx) {
  int shift = 0;

  s21_num_base_t base = DEC_T;

  int i_ch = 0;
  if (is_symbol(src[i_ch], "+-")) i_ch++;

  if (is_symbol(src[i_ch], "0") && is_symbol(src[i_ch + 1], "xX")) {
    base = HEX_T;
  } else if (is_symbol(src[i_ch], "0")) {
    base = OCT_T;
  }

  switch (base) {
    case DEC_T:
      shift = handle_int(src, res, params, ctx);
      break;
    case OCT_T:
      shift = handle_oct(src, res, params, ctx);
      break;
    case HEX_T:
      shift = handle_hex(src, res, params, ctx);
      break;
  }

  return shift;
}
int parse_specifier(const char *src, Sscanf_formatter params, Context *ctx,
                    va_list *va, error_t *err) {
  Specifiers spec = params.spec;
  Width width = params.width;
  *err = validate_data(src, spec, width);

  int shift = 0;
  if (*err == OK) {
    void *res = S21_NULL;
    if (!(width.star || spec.percent)) {
      res = va_arg(*va, void *);
    }

    if (spec.c) {
      shift = parse_char(src, (char *)res);
    } else if (spec.s) {
      shift = parse_str(src, (char *)res, width, &ctx->is_token_end);
    } else if (spec.d) {
      shift = handle_int(src, res, params, ctx);
    } else if (spec.u) {
      shift = handle_uint(src, res, params, ctx);
    } else if (spec.x || spec.X) {
      shift = handle_hex(src, res, params, ctx);
    } else if (spec.o) {
      shift = handle_oct(src, res, params, ctx);
    } else if (spec.p) {
      shift = parse_hex(src, res, LONG_INT_T, width, &ctx->is_token_end);
    } else if (spec.f || spec.e || spec.E || spec.g || spec.G) {
      shift = handle_float(src, res, params, ctx);
    } else if (spec.i) {
      shift = handle_uni_num(src, res, params, ctx);
    } else if (spec.n) {
      int *i_res = res;
      *i_res = ctx->ch_counter;
      ctx->is_token_end = false;
      shift = 0;
    } else if (spec.percent) {
      shift = 1;
    }
  }

  return shift;
}

bool is_match_format(const char format_ch, const char str_ch) {
  if (is_symbol(format_ch, S21_SYMBOLS_SPACES) &&
      is_symbol(str_ch, S21_SYMBOLS_SPACES))
    return true;

  return (format_ch == '%' || format_ch == str_ch);
}

bool is_next_c_symbol(const char *format) {
  if (*format == '%') {
    format++;

    Sscanf_formatter params = {0};
    format = init_sscanf_params(format, &params);

    if (params.spec.c) {
      return true;
    }
  }

  return false;
}

bool is_next_c_spec(const char *format) {
  while (*format != '\0') {
    if (is_next_c_symbol(format)) {
      return true;
    } else if (!is_symbol(*format, S21_SYMBOLS_SPACES)) {
      return false;
    }

    format++;
  }

  return false;
}

void handle_lasts_n(const char *format, va_list *va, int ch_counter) {
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      if (*format == '\0') continue;

      Sscanf_formatter params = {0};
      format = init_sscanf_params(format, &params);

      if (!params.width.star && params.spec.n) {
        int *res = va_arg(*va, int *);
        *res = ch_counter;
      }
    }

    format++;
  }
}

bool is_src_valid(const char *src, const char *format) {
  s21_size_t src_len = s21_strlen(src);
  if (src_len == 0) return false;

  for (s21_size_t i = 0; i < src_len; i++) {
    if (!is_symbol(src[i], S21_SYMBOLS_SPACES)) {
      return true;
    }
  }

  if (is_next_c_spec(format)) return true;

  return false;
}

int s21_sscanf(const char *src, const char *format, ...) {
  if (src == S21_NULL || format == S21_NULL) return -1;
  if (!is_src_valid(src, format)) return -1;

  va_list va;
  va_start(va, format);

  error_t err = OK;
  int scan_counter = 0;

  Context ctx = {.ch_counter = 0, .is_token_end = true};
  bool is_c_next_spec = false;

  while ((*format != '\0' && *src != '\0') && (err == OK)) {
    is_c_next_spec = is_next_c_spec(format);

    if ((ctx.is_token_end && !is_c_next_spec) &&
        !is_match_format(*format, *src)) {
      err = ERR_BAD_SRC;
      continue;
    }

    if (!is_next_c_symbol(format) && is_symbol(*src, S21_SYMBOLS_SPACES)) {
      int shift = get_extra_symbols_shift(src, S21_SYMBOLS_SPACES);
      src += shift;
      ctx.ch_counter += shift;
    }

    if (is_symbol(*format, S21_SYMBOLS_SPACES)) {
      format += get_extra_symbols_shift(format, S21_SYMBOLS_SPACES);
    }

    if (*format == '%') {
      format++;
      if (*format == '\0') continue;

      Sscanf_formatter params = {0};
      format = init_sscanf_params(format, &params);

      if (is_valid_specifier(params.spec)) {
        if (!params.spec.c && ctx.is_token_end && *src == ' ') src++;

        int shift = parse_specifier(src, params, &ctx, &va, &err);
        src += shift;
        ctx.ch_counter += shift;
        if (err == OK &&
            !(params.width.star || params.spec.percent || params.spec.n)) {
          scan_counter++;
        }
      } else {
        err = ERR_BAD_FORMAT;
      }
    } else {
      if (*format == *src) {
        format++;
        src++;
        ctx.ch_counter++;
      } else if (is_c_next_spec && is_symbol(*format, S21_SYMBOLS_SPACES)) {
        format++;
      } else {
        format++;
        if (ctx.is_token_end) {
          src++;
          ctx.ch_counter++;
        }
      }
    }
  }

  handle_lasts_n(format, &va, ctx.ch_counter);

  va_end(va);

  return scan_counter;
}