#include "s21_strerror.h"

#include "s21_string.h"

char *s21_strerror(int errnum) {
  static char msg[ERR_MSG_SIZE] = {0};

  if (errnum < 0 || errnum >= S21_ERRLIST_SIZE) {
    s21_sprintf(msg, "Unknown error %d", errnum);
    return msg;
  }

  return s21_sys_errlist[errnum];
}