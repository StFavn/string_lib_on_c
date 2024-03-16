#include "s21_string_test.h"

#define actual(str, n, ...) s21_sprintf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sprintf(str, format, __VA_ARGS__)

/* GET FLAGS */

START_TEST(get_params) {
  // Проверка парсера строки, используется не реализуемый нами флаг F
  const char *format =
      "start template_%+25.15hF_end##an%%other_% 32.763F_end%+-025.23LF";
  const char *result = "start template_F_end##an%other_F_endF";
  char dest[BIG_BUFF_SIZE] = {0};

  s21_sprintf(dest, format);
  ck_assert_str_eq(result, dest);

  memset(dest, '@', BIG_BUFF_SIZE);
  s21_sprintf(dest, format);
  ck_assert_str_eq(result, dest);
}
END_TEST

START_TEST(no_template_str) {
  const char format[] = "Simple no template string.";
  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int s21_res = s21_sprintf(dest_s21, format);
  int def_res = sprintf(dest_def, format);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  s21_res = s21_sprintf(dest_s21, format);
  def_res = sprintf(dest_def, format);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

START_TEST(s_flag) {
  const char format[] = "Simple %s and another %s";
  const char *sample = "!ABOBA!";
  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int s21_res = s21_sprintf(dest_s21, format, sample, sample);
  int def_res = sprintf(dest_def, format, sample, sample);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  s21_res = s21_sprintf(dest_s21, format, sample, sample);
  def_res = sprintf(dest_def, format, sample, sample);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  const char format2[] = "%s";
  s21_res = s21_sprintf(dest_s21, format2, sample);
  def_res = sprintf(dest_def, format2, sample);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, 0, BIG_BUFF_SIZE);
  memset(dest_def, 0, BIG_BUFF_SIZE);

  s21_res = s21_sprintf(dest_s21, format2, sample);
  def_res = sprintf(dest_def, format2, sample);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *s_template_vals[] = {
    "Test |%-5.10s| string.", "Test |%-35.10s| string.",
    "Test |%5.10s| string.",  "Test |%35.10s| string.",
    "Test |%-5.3s| string.",  "Test |%5.3s| string.",
    "Test |%.3s| string.",    "Test |%.10s| string.",
    "Test |%5s| string.",     "Test |%10s| string."};

START_TEST(s_flag_template) {
  const char *str = s_template_vals[_i];
  const char *sample = "!ABOBA!";

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str, sample);
  int s21_res = s21_sprintf(dest_s21, str, sample);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  def_res = sprintf(dest_def, str, sample);
  s21_res = s21_sprintf(dest_s21, str, sample);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *s_template_double_vals[] = {
    "Test |%-5.10s| string |%-35.10s", "Test |%5.10s| string |%35.10s",
    "Test |%-5.3s| string |%5.3s",     "Test |%.3s| string |%.10s",
    "Test |%5s| string |%10s",
};

START_TEST(s_flag_double_template) {
  const char *str = s_template_double_vals[_i];
  const char sample1[] = "!ABOBA!";
  const char sample2[] = "*STAR*";

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str, sample1, sample2);
  int s21_res = s21_sprintf(dest_s21, str, sample1, sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  def_res = sprintf(dest_def, str, sample1, sample2);
  s21_res = s21_sprintf(dest_s21, str, sample1, sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

START_TEST(s_flag_star_template) {
  const char *str1 = "Test |%-*.10s| string |%-15.10s|";
  const char *str2 = "Test |%*.*s| string |%35.10s|";
  const char *str3 = "Test |%-*.*s| string |%s|";
  const char *str4 = "Test |%*.*s| string |%*.*s|";  // 35, 10

  const char sample1[] = "!ABOBA!";
  const char sample2[] = "*STAR*";
  int first_amount = 5;
  int second_amount = 10;

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str1, first_amount, sample1, sample2);
  int s21_res = s21_sprintf(dest_s21, str1, first_amount, sample1, sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  def_res = sprintf(dest_def, str1, first_amount, sample1, sample2);
  s21_res = s21_sprintf(dest_s21, str1, first_amount, sample1, sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  def_res =
      sprintf(dest_def, str2, first_amount, second_amount, sample1, sample2);
  s21_res = s21_sprintf(dest_s21, str2, first_amount, second_amount, sample1,
                        sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  def_res =
      sprintf(dest_def, str3, first_amount, second_amount, sample1, sample2);
  s21_res = s21_sprintf(dest_s21, str3, first_amount, second_amount, sample1,
                        sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  def_res = sprintf(dest_def, str4, first_amount, second_amount, sample1, 35,
                    10, sample2);
  s21_res = s21_sprintf(dest_s21, str4, first_amount, second_amount, sample1,
                        35, 10, sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, 0, BIG_BUFF_SIZE);
  memset(dest_def, 0, BIG_BUFF_SIZE);

  def_res = sprintf(dest_def, str4, first_amount, second_amount, sample1, 35,
                    10, sample2);
  s21_res = s21_sprintf(dest_s21, str4, first_amount, second_amount, sample1,
                        35, 10, sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

/* EDGE */

START_TEST(nums_delim_percent) {
  const char *format = "%f%%%d%%";

  char dest_actual[BIG_BUFF_SIZE] = {0};
  char dest_expected[BIG_BUFF_SIZE] = {0};

  ck_assert_int_eq(actual(dest_actual, format, 3.14, 123),
                   expected(dest_expected, format, 3.14, 123));

  ck_assert_str_eq(dest_actual, dest_expected);
}
END_TEST

Suite *suite_s21_sprintf() {
  Suite *suite = suite_create("suite_s21_sprintf core && s");

  TCase *get_params_case = tcase_create("s21_sprintf_get_params");
  tcase_add_test(get_params_case, get_params);
  suite_add_tcase(suite, get_params_case);

  TCase *no_template_case = tcase_create("s21_sprintf_no_template_str");
  tcase_add_test(no_template_case, no_template_str);
  suite_add_tcase(suite, no_template_case);

  TCase *s_flag_case = tcase_create("s21_sprintf_s_flag");
  tcase_add_test(s_flag_case, s_flag);
  suite_add_tcase(suite, s_flag_case);

  TCase *s_flag_template_case = tcase_create("s21_sprint_s_template_flag");
  tcase_add_loop_test(s_flag_template_case, s_flag_template, 0,
                      GET_SIZE_ARRAY(s_template_vals));
  suite_add_tcase(suite, s_flag_template_case);

  TCase *s_flag_double_template_case =
      tcase_create("s21_sprint_s_template_double_flag");
  tcase_add_loop_test(s_flag_double_template_case, s_flag_double_template, 0,
                      GET_SIZE_ARRAY(s_template_double_vals));
  suite_add_tcase(suite, s_flag_double_template_case);

  TCase *s_flag_star_template_case =
      tcase_create("s21_sprint_s_template_star_flag");
  tcase_add_test(s_flag_star_template_case, s_flag_star_template);
  suite_add_tcase(suite, s_flag_star_template_case);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, nums_delim_percent);
  suite_add_tcase(suite, edge_cases);

  return suite;
}
