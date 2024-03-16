#ifndef SRC_UNIT_S21_STRING_TEST_H_
#define SRC_UNIT_S21_STRING_TEST_H_

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

// Global values
#define BUFF_SIZE 128
#define BIG_BUFF_SIZE 1024

// Macroses
#define GET_SIZE_ARRAY(array) (sizeof(array) / sizeof(array[0]))

// Memory
Suite *suite_s21_memset();
Suite *suite_s21_memcpy();
Suite *suite_s21_memcmp();
Suite *suite_s21_memchr();

// String
Suite *suite_s21_strlen();
Suite *suite_s21_strncpy();
Suite *suite_s21_strstr();
Suite *suite_s21_strncat();
Suite *suite_s21_strpbrk();
Suite *suite_s21_strspn();
Suite *suite_s21_strcspn();
Suite *suite_s21_strncmp();
Suite *suite_s21_strchr();
Suite *suite_s21_strrchr();
Suite *suite_s21_strtok();
Suite *suite_s21_strerror();

// Sprintf
Suite *suite_s21_sprintf();
Suite *suite_s21_sprintf_c();
Suite *suite_s21_sprintf_d();
Suite *suite_s21_sprintf_u();
Suite *suite_s21_sprintf_f();
Suite *suite_s21_sprintf_es();
Suite *suite_s21_sprintf_el();
Suite *suite_s21_sprintf_xs();
Suite *suite_s21_sprintf_xl();
Suite *suite_s21_sprintf_o();
Suite *suite_s21_sprintf_gs();
Suite *suite_s21_sprintf_p();
Suite *suite_s21_sprintf_ext();

// s21_scanf
Suite *suite_s21_sscanf();
Suite *suite_s21_sscanf_c();
Suite *suite_s21_sscanf_s();
Suite *suite_s21_sscanf_d();
Suite *suite_s21_sscanf_u();
Suite *suite_s21_sscanf_o();
Suite *suite_s21_sscanf_x();
Suite *suite_s21_sscanf_i();
Suite *suite_s21_sscanf_p();
Suite *suite_s21_sscanf_f();
Suite *suite_s21_sscanf_eg();
Suite *suite_s21_sscanf_ext();

// Additional
Suite *suite_s21_to_lower();
Suite *suite_s21_to_upper();
Suite *suite_s21_trim();

// Helper functions
Suite *suite_s21_atoi();
Suite *suite_s21_itoa();
Suite *suite_s21_ditoa();
Suite *suite_s21_sprintf_get_params();

// Addition
Suite *suite_s21_insert();

#endif  // SRC_UNIT_S21_STRING_TEST_H_