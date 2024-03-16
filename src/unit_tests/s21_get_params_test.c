#include <stdio.h>

#include "s21_string_test.h"

/* GET FLAGS */

START_TEST(get_flags_case_01) {
  Flags flags = {0};
  const char *format = "-+ #0";
  init_flags(format, &flags);
  bool actual =
      (flags.minus && flags.plus && flags.space && flags.hash && flags.zero);
  ck_assert_int_eq(actual, 1);
}
END_TEST

START_TEST(get_flags_case_02) {
  Flags flags = {0};
  const char *format = "+ ";
  init_flags(format, &flags);
  bool actual = ((flags.plus && flags.space) &&
                 (!flags.minus && !flags.hash && !flags.zero));
  ck_assert_int_eq(actual, 1);
}
END_TEST

START_TEST(get_flags_case_03) {
  Flags flags = {0};
  const char *format = "00";
  init_flags(format, &flags);
  bool actual = (flags.zero &&
                 (!flags.space && !flags.minus && !flags.hash && !flags.plus));
  ck_assert_int_eq(actual, 1);
}
END_TEST

START_TEST(get_flags_case_04) {
  Flags flags = {0};
  const char *format = "2+";
  init_flags(format, &flags);
  bool actual = (!flags.zero && !flags.space && !flags.minus && !flags.hash &&
                 !flags.plus);
  ck_assert_int_eq(actual, 1);
}
END_TEST

/* GET WIDTH */

START_TEST(get_width_case_01) {
  Width width = {0};
  const char *format = "*23";
  init_width(format, &width);
  bool actual = (width.star && !width.number);
  ck_assert_int_eq(actual, 1);
}
END_TEST

START_TEST(get_width_case_02) {
  Width width = {0};
  const char *format = "23*";
  init_width(format, &width);
  bool actual = (!width.star && width.number);
  ck_assert_int_eq(actual, 1);
  ck_assert_int_eq(width.number, 23);
}
END_TEST

Suite *suite_s21_sprintf_get_params() {
  Suite *suite = suite_create("suite_s21_sprintf_get_params");

  TCase *get_flags_cases = tcase_create("get_flags_cases");
  tcase_add_test(get_flags_cases, get_flags_case_01);
  tcase_add_test(get_flags_cases, get_flags_case_02);
  tcase_add_test(get_flags_cases, get_flags_case_03);
  tcase_add_test(get_flags_cases, get_flags_case_04);
  suite_add_tcase(suite, get_flags_cases);

  TCase *get_width_cases = tcase_create("get_width_cases");
  tcase_add_test(get_width_cases, get_width_case_01);
  tcase_add_test(get_width_cases, get_width_case_02);
  suite_add_tcase(suite, get_width_cases);

  return suite;
}