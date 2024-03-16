#include "s21_string_test.h"

START_TEST(c_flag) {
  const char format[] = "Simple %c and another %c";
  const char sample = '@';
  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int s21_res = s21_sprintf(dest_s21, format, sample, sample);
  int def_res = sprintf(dest_def, format, sample, sample);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  const char format2[] = "%c";
  s21_res = s21_sprintf(dest_s21, format2, sample);
  def_res = sprintf(dest_def, format2, sample);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *c_template_vals[] = {
    "Test |%-5.10c| string.", "Test |%-35.10c| string.",
    "Test |%5.10c| string.",  "Test |%35.10c| string.",
    "Test |%-5.3c| string.",  "Test |%5.3c| string.",
    "Test |%.3c| string.",    "Test |%.10c| string.",
    "Test |%5c| string.",     "Test |%10c| string."};

START_TEST(c_flag_template) {
  const char *str = c_template_vals[_i];
  const char sample = '@';

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

static const char *c_template_double_vals[] = {
    "Test |%-5.10c| string |%-35.10c", "Test |%5.10c| string |%35.10c",
    "Test |%-5.3c| string |%5.3c",     "Test |%.3c| string |%.10c",
    "Test |%5c| string |%10c",
};

START_TEST(c_flag_double_template) {
  const char *str = c_template_double_vals[_i];
  const char sample1 = '@';
  const char sample2 = '*';

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str, sample1, sample2);
  int s21_res = s21_sprintf(dest_s21, str, sample1, sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, 0, BIG_BUFF_SIZE);
  memset(dest_def, 0, BIG_BUFF_SIZE);

  def_res = sprintf(dest_def, str, sample1, sample2);
  s21_res = s21_sprintf(dest_s21, str, sample1, sample2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

START_TEST(c_flag_star_template) {
  const char *str1 = "Test |%-*.10c| string |%-15.10c|";
  const char *str2 = "Test |%*.*c| string |%+35.10c|";
  const char *str3 = "Test |%-*.*c| string |%-c|";
  const char *str4 = "Test |%*.*c| string |%*.*c|";

  const char sample1 = '@';
  const char sample2 = '*';
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

Suite *suite_s21_sprintf_c() {
  Suite *suite = suite_create("suite_s21_sprintf_c");

  TCase *c_flag_case = tcase_create("s21_sprintf_c_flag");
  tcase_add_test(c_flag_case, c_flag);
  suite_add_tcase(suite, c_flag_case);

  TCase *c_flag_template_case = tcase_create("s21_sprint_c_template_flag");
  tcase_add_loop_test(c_flag_template_case, c_flag_template, 0,
                      GET_SIZE_ARRAY(c_template_vals));
  suite_add_tcase(suite, c_flag_template_case);

  TCase *c_flag_double_template_case =
      tcase_create("s21_sprint_c_template_double_flag");
  tcase_add_loop_test(c_flag_double_template_case, c_flag_double_template, 0,
                      GET_SIZE_ARRAY(c_template_double_vals));
  suite_add_tcase(suite, c_flag_double_template_case);

  TCase *c_flag_star_template_case =
      tcase_create("s21_sprint_c_template_star_flag");
  tcase_add_test(c_flag_star_template_case, c_flag_star_template);
  suite_add_tcase(suite, c_flag_star_template_case);

  return suite;
}
