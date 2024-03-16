#include "s21_string_test.h"

#define actual(str, n, ...) s21_sprintf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sprintf(str, format, __VA_ARGS__)

#define BUFFER 1024

START_TEST(p_flag) {
  const char *format = "Number first %p and number second %p";
  const double number_1 = 1256;
  const char *str = "1492";
  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  int s21_res = s21_sprintf(dest_s21, format, &number_1, &str);
  int def_res = sprintf(dest_def, format, &number_1, &str);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  const char *format2 = "%p";
  s21_res = s21_sprintf(dest_s21, format2, &number_1);
  def_res = sprintf(dest_def, format2, &number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *p_width_template_vals[] = {
    "Number first |%5p| and number second|%5p|",
    "Number first |%-5p| and number second|%-5p|",
    "Number first |%2p| and number second|%2p|",
    "Number first |%1p| and number second|%3p|",
    "Number first |%-1p| and number second|%-1p|",
    "Number first |%20x| and number second|%20x|",
    "Number first |%-20x| and number second|%-20x|"};

START_TEST(p_flag_width_template) {
  const char *str = p_width_template_vals[_i];
  const char *number1 = "21";
  unsigned long int number2 = UINT32_MAX;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res = sprintf(dest_def, str, &number1, &number2);
  int s21_res = s21_sprintf(dest_s21, str, &number1, &number2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);
}
END_TEST

static const char *p_width_star_template_vals[] = {
    "Number first |%-*p| and number second|%-*p|",
    "Number first |%*p| and number second|%*p|",
};

START_TEST(p_flag_width_star_template) {
  const char *str = p_width_star_template_vals[_i];
  const char *number1 = "1023";
  unsigned long long int number2 = ULLONG_MAX;
  int star_value = 42;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res =
      sprintf(dest_def, str, star_value, &number1, star_value, &number2);
  int s21_res =
      s21_sprintf(dest_s21, str, star_value, &number1, star_value, &number2);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

/* EDGE */

START_TEST(null_ptr) {
  char *format = "%p";
  char *ptr_null = NULL;

  char dest_actual[BUFFER];
  char dest_expected[BUFFER];

  ck_assert_int_eq(actual(dest_actual, format, ptr_null),
                   expected(dest_expected, format, ptr_null));
  ck_assert_str_eq(dest_actual, dest_expected);
}
END_TEST

START_TEST(zero_ptr) {
  char *format = "%p";

  char dest_actual[BUFFER];
  char dest_expected[BUFFER];

  ck_assert_int_eq(actual(dest_actual, format, 0),
                   expected(dest_expected, format, 0));
  ck_assert_str_eq(dest_actual, dest_expected);
}
END_TEST

Suite *suite_s21_sprintf_p() {
  Suite *suite = suite_create("suite_s21_sprintf_p");

  TCase *p_flag_case = tcase_create("s21_sprintf_p_flag");
  tcase_add_test(p_flag_case, p_flag);
  suite_add_tcase(suite, p_flag_case);

  TCase *p_flag_width_template_case =
      tcase_create("s21_sprint_p_width_template");
  tcase_add_loop_test(p_flag_width_template_case, p_flag_width_template, 0,
                      GET_SIZE_ARRAY(p_width_template_vals));
  suite_add_tcase(suite, p_flag_width_template_case);

  TCase *p_flag_width_star_template_case =
      tcase_create("s21_sprint_p_width_star_template");
  tcase_add_loop_test(p_flag_width_star_template_case,
                      p_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(p_width_star_template_vals));
  suite_add_tcase(suite, p_flag_width_star_template_case);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, null_ptr);
  tcase_add_test(edge_cases, zero_ptr);
  suite_add_tcase(suite, edge_cases);

  return suite;
}
