#include <stdio.h>

#include "s21_string_test.h"

static const long long int x_global[] = {123, 10, 0, 100500600900100, -25};

START_TEST(case_10base) {
  const long long int x = x_global[_i];
  int base = 10;

  char expected_buff[BIG_BUFF_SIZE] = {0};
  char *actual_buff = s21_itoa(x, base, 0, 0, 0);

  sprintf(expected_buff, "%lld", x);
  ck_assert_str_eq(actual_buff, expected_buff);
  if (actual_buff != NULL) free(actual_buff);
}
END_TEST

START_TEST(case_8base) {
  const long long int x = x_global[_i];
  int base = 8;

  char expected_buff[BIG_BUFF_SIZE] = {0};
  char *actual_buff = s21_itoa(x, base, 0, 0, 0);

  sprintf(expected_buff, "%llo", x);  // only unsigned octal integers
  ck_assert_str_eq(actual_buff, expected_buff);
  if (actual_buff != NULL) free(actual_buff);
}
END_TEST

START_TEST(case_16Lbase) {
  const long long int x = x_global[_i];
  int base = 16;
  bool hex_big = true;

  char expected_buff[BIG_BUFF_SIZE] = {0};
  char *actual_buff = s21_itoa(x, base, 0, 0, hex_big);

  sprintf(expected_buff, "%llX", x);  // only unsigned hex integers
  ck_assert_str_eq(actual_buff, expected_buff);
  if (actual_buff != NULL) free(actual_buff);
}
END_TEST

START_TEST(case_16Sbase) {
  const long long int x = x_global[_i];
  int base = 16;
  bool hex_big = false;

  char expected_buff[BIG_BUFF_SIZE] = {0};
  char *actual_buff = s21_itoa(x, base, 0, 0, hex_big);

  sprintf(expected_buff, "%llx", x);  // only unsigned hex integers
  ck_assert_str_eq(actual_buff, expected_buff);
  if (actual_buff != NULL) free(actual_buff);
}
END_TEST

START_TEST(case_10sign_save) {
  const long long int x = x_global[_i];
  int base = 10;
  bool hex_big = false;
  bool sign_save = true;

  char expected_buff[BIG_BUFF_SIZE] = {0};
  char *actual_buff = s21_itoa(x, base, sign_save, 0, hex_big);

  sprintf(expected_buff, "%+lld", x);
  ck_assert_str_eq(actual_buff, expected_buff);
  if (actual_buff != NULL) free(actual_buff);
}
END_TEST

START_TEST(case_10sign_place) {
  const long long int x = x_global[_i];
  int base = 10;
  bool hex_big = false;
  bool sign_place = true;

  char expected_buff[BIG_BUFF_SIZE] = {0};
  char *actual_buff = s21_itoa(x, base, 0, sign_place, hex_big);

  sprintf(expected_buff, "% lld", x);
  ck_assert_str_eq(actual_buff, expected_buff);
  if (actual_buff != NULL) free(actual_buff);
}
END_TEST

/* EDGE */

// GCC error: error: ' ' flag ignored with '+' flag in gnu_printf format
// START_TEST(case_10_all_sign_flags) {
//   const long long int x = x_global[_i];
//   int base = 10;
//   bool hex_big = false;
//   bool sign_save = true;
//   bool sign_place = true;
//   char expected_buff[BIG_BUFF_SIZE] = {0};
//   sprintf(expected_buff, "%+ lld", x);
//   ck_assert_str_eq(s21_itoa(x, base, sign_save, sign_place, hex_big),
//   expected_buff);
// }
// END_TEST

Suite *suite_s21_itoa() {
  Suite *suite = suite_create("suite_s21_itoa");
  s21_size_t x_gloal_size = sizeof(x_global) / sizeof(x_global[0]);

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_loop_test(normal_cases, case_10base, 0, x_gloal_size);
  tcase_add_loop_test(normal_cases, case_8base, 0, x_gloal_size - 1);
  tcase_add_loop_test(normal_cases, case_16Lbase, 0, x_gloal_size - 1);
  tcase_add_loop_test(normal_cases, case_16Sbase, 0, x_gloal_size - 1);
  tcase_add_loop_test(normal_cases, case_10sign_save, 0, x_gloal_size);
  tcase_add_loop_test(normal_cases, case_10sign_place, 0, x_gloal_size);
  suite_add_tcase(suite, normal_cases);

  // TCase *edge_cases = tcase_create("edge_cases");
  // tcase_add_loop_test(edge_cases, case_10_all_sign_flags, 0, x_gloal_size);
  // suite_add_tcase(suite, edge_cases);

  return suite;
}