#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

/* NORMAL */

START_TEST(nums_delim_percent) {
  const char *format = "%f%%%d";
  const char *src = "3.14159265359%123";

  float f0_actual = 0.4;
  float f0_expected = -0.4;
  int d0_actual = 5;
  int d0_expected = -5;

  ck_assert_int_eq(actual(src, format, &f0_actual, &d0_actual),
                   expected(src, format, &f0_expected, &d0_expected));

  ck_assert_double_eq(f0_actual, f0_expected);
  ck_assert_int_eq(d0_actual, d0_expected);
}
END_TEST

START_TEST(all_only_spec) {
  const char *format = "%f %d %u %s %c";
  const char *src = "3.14159265359 -123 214748364900 Hello !";

  float f0_actual = 0.4;
  float f0_expected = -0.4;
  int d0_actual = 5;
  int d0_expected = -5;
  unsigned int u0_actual = 5;
  unsigned int u0_expected = 7;

  char str0_actual[BUFF_SIZE] = {0};
  char str0_expected[BUFF_SIZE] = {0};
  char ch0_actual = 0;
  char ch0_expected = 1;

  ck_assert_int_eq(actual(src, format, &f0_actual, &d0_actual, &u0_actual,
                          str0_actual, &ch0_actual),
                   expected(src, format, &f0_expected, &d0_expected,
                            &u0_expected, str0_expected, &ch0_expected));

  ck_assert_double_eq(f0_actual, f0_expected);
  ck_assert_int_eq(d0_actual, d0_expected);
  ck_assert_uint_eq(u0_actual, u0_expected);
  ck_assert_str_eq(str0_actual, str0_expected);
  ck_assert_int_eq(ch0_actual, ch0_expected);
}
END_TEST

START_TEST(spec_n_0) {
  const char *format = "%f %n %d %u %n %s %c %n";
  const char *src = "3.14159265359 -123 214748364900 Hello !";

  float f0_actual = 0.4;
  float f0_expected = -0.4;

  int n0_actual = 0;
  int n0_expected = 1;

  int d0_actual = 5;
  int d0_expected = -5;
  unsigned int u0_actual = 5;
  unsigned int u0_expected = 7;

  int n1_actual = 0;
  int n1_expected = 1;

  char str0_actual[BUFF_SIZE] = {0};
  char str0_expected[BUFF_SIZE] = {0};
  char ch0_actual = 0;
  char ch0_expected = 1;

  int n2_actual = 0;
  int n2_expected = 1;

  ck_assert_int_eq(
      actual(src, format, &f0_actual, &n0_actual, &d0_actual, &u0_actual,
             &n1_actual, str0_actual, &ch0_actual, &n2_actual),
      expected(src, format, &f0_expected, &n0_expected, &d0_expected,
               &u0_expected, &n1_expected, str0_expected, &ch0_expected,
               &n2_expected));

  ck_assert_double_eq(f0_actual, f0_expected);
  ck_assert_int_eq(n0_actual, n0_expected);
  ck_assert_int_eq(d0_actual, d0_expected);
  ck_assert_uint_eq(u0_actual, u0_expected);
  ck_assert_int_eq(n1_actual, n1_expected);
  ck_assert_str_eq(str0_actual, str0_expected);
  ck_assert_int_eq(ch0_actual, ch0_expected);
  ck_assert_int_eq(n2_actual, n2_expected);
}
END_TEST

START_TEST(spec_n_1) {
  const char *format = "%f %n %n %n";
  const char *src = "+nan -123 214748364900 Hello !";

  float f0_actual = 0.4;
  float f0_expected = -0.4;

  int n0_actual = 0;
  int n0_expected = 1;

  int n1_actual = 0;
  int n1_expected = 1;

  int n2_actual = 0;
  int n2_expected = 1;

  ck_assert_int_eq(
      actual(src, format, &f0_actual, &n0_actual, &n1_actual, &n2_actual),
      expected(src, format, &f0_expected, &n0_expected, &n1_expected,
               &n2_expected));

  ck_assert_float_nan(f0_actual);
  ck_assert_int_eq(n0_actual, n0_expected);
  ck_assert_int_eq(n1_actual, n1_expected);
  ck_assert_int_eq(n2_actual, n2_expected);
}
END_TEST

START_TEST(spec_n_2) {
  const char *format = "%*f %n %d %*u %n %s %*c %n";
  const char *src = "3.14159265359 -123 214748364900 Hello !";

  int n0_actual = 0;
  int n0_expected = 1;

  int d0_actual = 5;
  int d0_expected = -5;

  int n1_actual = 0;
  int n1_expected = 1;

  const char str0_actual[BUFF_SIZE];
  const char str0_expected[BUFF_SIZE];

  int n2_actual = 0;
  int n2_expected = 1;

  ck_assert_int_eq(actual(src, format, &n0_actual, &d0_actual, &n1_actual,
                          str0_actual, &n2_actual),
                   expected(src, format, &n0_expected, &d0_expected,
                            &n1_expected, str0_expected, &n2_expected));

  ck_assert_int_eq(n0_actual, n0_expected);
  ck_assert_int_eq(d0_actual, d0_expected);
  ck_assert_int_eq(n1_actual, n1_expected);
  ck_assert_str_eq(str0_actual, str0_expected);
  ck_assert_int_eq(n2_actual, n2_expected);
}
END_TEST

START_TEST(multi_percent_delim) {
  const char *format = "%f%%%d%%%u%%%s %c";
  const char *src = "3.14159265359%-123%214748364900%Hello !%";

  float f0_actual = 0.4;
  float f0_expected = -0.4;
  int d0_actual = 5;
  int d0_expected = -5;
  unsigned int u0_actual = 5;
  unsigned int u0_expected = 7;

  char str0_actual[BUFF_SIZE] = {0};
  char str0_expected[BUFF_SIZE] = {0};
  char ch0_actual = 0;
  char ch0_expected = 1;

  ck_assert_int_eq(actual(src, format, &f0_actual, &d0_actual, &u0_actual,
                          str0_actual, &ch0_actual),
                   expected(src, format, &f0_expected, &d0_expected,
                            &u0_expected, str0_expected, &ch0_expected));

  ck_assert_double_eq(f0_actual, f0_expected);
  ck_assert_int_eq(d0_actual, d0_expected);
  ck_assert_uint_eq(u0_actual, u0_expected);
  ck_assert_str_eq(str0_actual, str0_expected);
  ck_assert_int_eq(ch0_actual, ch0_expected);
}
END_TEST

START_TEST(all_star_width) {
  const char *format = "%*f %*d %*u %*s %*c";
  const char *src = "3.14159265359 -123 214748364900 Hello !";

  float f0_actual = 0.4;
  float f0_expected = -0.4;
  int d0_actual = 5;
  int d0_expected = -5;
  unsigned int u0_actual = 5;
  unsigned int u0_expected = 7;

  char str0_actual[BUFF_SIZE] = {0};
  char str0_expected[BUFF_SIZE] = {0};
  char ch0_actual = 0;
  char ch0_expected = 1;

  ck_assert_int_eq(actual(src, format, &f0_actual, &d0_actual, &u0_actual,
                          str0_actual, &ch0_actual),
                   expected(src, format, &f0_expected, &d0_expected,
                            &u0_expected, str0_expected, &ch0_expected));

  ck_assert_double_ne(f0_actual, f0_expected);
  ck_assert_int_ne(d0_actual, d0_expected);
  ck_assert_uint_ne(u0_actual, u0_expected);
  ck_assert_str_eq(str0_actual, str0_expected);
  ck_assert_int_ne(ch0_actual, ch0_expected);
}
END_TEST

START_TEST(mix_star_width) {
  const char *format = "%*f %d %*u %*s %c";
  const char *src = "3.14159265359 -123 214748364900 Hello !";

  int d0_actual = 5;
  int d0_expected = -5;

  char ch0_actual = 0;
  char ch0_expected = 1;

  ck_assert_int_eq(actual(src, format, &d0_actual, &ch0_actual),
                   expected(src, format, &d0_expected, &ch0_expected));

  ck_assert_int_eq(d0_actual, d0_expected);
  ck_assert_int_eq(ch0_actual, ch0_expected);
}
END_TEST

/* EDGE */

/* ANOMALY */

START_TEST(not_corrent_spec) {
  const char *format = "%f %d %y %v %w";
  const char *src = "3.14159265359 -123 214748364900 Hello !";

  float f0_actual = 0.4;
  float f0_expected = -0.4;
  int d0_actual = 5;
  int d0_expected = -5;
  unsigned int u0_actual = 5;
  unsigned int u0_expected = 7;

  char str0_actual[BUFF_SIZE] = {0};
  char str0_expected[BUFF_SIZE] = {0};
  char ch0_actual = 0;
  char ch0_expected = 1;

  ck_assert_int_eq(actual(src, format, &f0_actual, &d0_actual, &u0_actual,
                          str0_actual, &ch0_actual),
                   expected(src, format, &f0_expected, &d0_expected,
                            &u0_expected, str0_expected, &ch0_expected));

  ck_assert_double_eq(f0_actual, f0_expected);
  ck_assert_int_eq(d0_actual, d0_expected);
  ck_assert_uint_ne(u0_actual, u0_expected);
  ck_assert_str_eq(str0_actual, str0_expected);
  ck_assert_int_ne(ch0_actual, ch0_expected);
}
END_TEST

START_TEST(only_percents) {
  const char *format = "%%%%";
  const char *src = "3.14159265359%123";

  float f0_actual = 0.4;
  int d0_actual = 5;
  float f0_expected = -0.4;
  int d0_expected = -5;

  ck_assert_int_eq(actual(src, format, &f0_actual, &d0_actual),
                   expected(src, format, &f0_expected, &d0_expected));

  ck_assert_double_ne(f0_actual, f0_expected);
  ck_assert_int_ne(d0_actual, d0_expected);
}
END_TEST

START_TEST(multi_percent_delim_bad_src) {
  const char *format = "%f%%%d%%%u%%%s %c";
  const char *src = "3.14159265359%-123 214748364900 Hello !%";

  float f0_actual = 0.4;
  float f0_expected = -0.4;
  int d0_actual = 5;
  int d0_expected = -5;
  unsigned int u0_actual = 5;
  unsigned int u0_expected = 7;

  char str0_actual[BUFF_SIZE] = {0};
  char str0_expected[BUFF_SIZE] = {0};
  char ch0_actual = 0;
  char ch0_expected = 1;

  ck_assert_int_eq(actual(src, format, &f0_actual, &d0_actual, &u0_actual,
                          str0_actual, &ch0_actual),
                   expected(src, format, &f0_expected, &d0_expected,
                            &u0_expected, str0_expected, &ch0_expected));

  ck_assert_double_eq(f0_actual, f0_expected);
  ck_assert_int_eq(d0_actual, d0_expected);
  ck_assert_uint_ne(u0_actual, u0_expected);
  ck_assert_str_eq(str0_actual, str0_expected);
  ck_assert_int_ne(ch0_actual, ch0_expected);
}
END_TEST

START_TEST(only_spec_n) {
  const char *format = "%n %n %n";
  const char *src = "+nan -123 214748364900 Hello !";

  int n0_actual = 0;
  int n0_expected = 1;

  int n1_actual = 0;
  int n1_expected = 1;

  int n2_actual = 0;
  int n2_expected = 1;

  ck_assert_int_eq(
      actual(src, format, &n0_actual, &n1_actual, &n2_actual),
      expected(src, format, &n0_expected, &n1_expected, &n2_expected));

  ck_assert_int_eq(n0_actual, n0_expected);
  ck_assert_int_eq(n1_actual, n1_expected);
  ck_assert_int_eq(n2_actual, n2_expected);
}
END_TEST

START_TEST(src_only_spaces_good) {
  const char *format = "%c";
  const char *src = "        ";

  char ch0_actual = 0;
  char ch0_expected = 1;

  ck_assert_int_eq(actual(src, format, &ch0_actual),
                   expected(src, format, &ch0_expected));

  ck_assert_int_eq(ch0_actual, ch0_expected);
}
END_TEST

START_TEST(src_only_spaces_bad) {
  const char *format = "%d";
  const char *src = "        ";

  int n0_actual = 0;
  int n0_expected = 1;

  ck_assert_int_eq(actual(src, format, &n0_actual),
                   expected(src, format, &n0_expected));

  ck_assert_int_ne(n0_actual, n0_expected);
}
END_TEST

Suite *suite_s21_sscanf() {
  Suite *suite = suite_create("suite_s21_sscanf");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, nums_delim_percent);
  tcase_add_test(normal_cases, all_only_spec);
  tcase_add_test(normal_cases, spec_n_0);
  tcase_add_test(normal_cases, spec_n_1);
  tcase_add_test(normal_cases, spec_n_2);
  tcase_add_test(normal_cases, multi_percent_delim);
  tcase_add_test(normal_cases, all_star_width);
  tcase_add_test(normal_cases, mix_star_width);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(normal_cases, only_percents);
  tcase_add_test(normal_cases, not_corrent_spec);
  tcase_add_test(normal_cases, multi_percent_delim_bad_src);
  tcase_add_test(normal_cases, only_spec_n);
  tcase_add_test(normal_cases, src_only_spaces_good);
  tcase_add_test(normal_cases, src_only_spaces_bad);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
