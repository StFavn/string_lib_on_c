#include "s21_string_test.h"

START_TEST(d_flag) {
  const char format[] = "Number first %d and number second %d";
  const char number_1 = 21;
  const char number_2 = -42;
  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  int s21_res = s21_sprintf(dest_s21, format, number_1, number_2);
  int def_res = sprintf(dest_def, format, number_1, number_2);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  const char format2[] = "%d";
  s21_res = s21_sprintf(dest_s21, format2, number_1);
  def_res = sprintf(dest_def, format2, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *d_edge_vals[] = {
    "%.0d",    "%10.0d", "%+10.0d", "% 10.0d", "%+ 10.0d", "%+.0d",
    "% .0d",   "%+ .0d", "%.d",     "%10.d",   "%+10.d",   "% 10.d",
    "%+ 10.d", "%+.d",   "% .d",    "%+ .d",
};

START_TEST(d_edge_cases) {
  const char *str = d_edge_vals[_i];
  int zero_number = 0;

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str, zero_number);
  int s21_res = s21_sprintf(dest_s21, str, zero_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *d_width_template_vals[] = {
    "Number first |%5d| and number second|%5d|",
    "Number first |%-5d| and number second|%-5d|",
    "Number first |%+5d| and number second|%+5d|",
    "Number first |%-05d| and number second|%-05d|",
    "Number first |%+05d| and number second|%+05d|",
    "Number first |% 5d| and number second|% 5d|",
    "Number first |% 05d| and number second|% 05d|",
    "Number first |%+- 5d| and number second|%+- 5d|",
    "Number first |%2d| and number second|%2d|",
    "Number first |%1d| and number second|%3d|",
    "Number first |%3d| and number second|%4d|",
    "Number first |%-+ 02d| and number second|%-+ 02d|",
    "Number first |%-1d| and number second|%-1d|",
    "Number first |%+2d| and number second|%+2d|",
    "Number first |%-01d| and number second|%-03d|",
    "Number first |%+01d| and number second|%+01d|",
    "Number first |% 2d| and number second|% 3d|",
    "Number first |% 01d| and number second|% 03d|",
    "Number first |%+- 1d| and number second|%+- 1d|",
    "Number first |%-+ 02d| and number second|%-+ 02d|"};

START_TEST(d_flag_width_template) {
  const char *str = d_width_template_vals[_i];
  int positive_number = 21;
  int negative_number = -42;

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str, positive_number, negative_number);
  int s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  positive_number = 0;

  def_res = sprintf(dest_def, str, positive_number, positive_number);
  s21_res = s21_sprintf(dest_s21, str, positive_number, positive_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *d_width_precision_template_vals[] = {
    "Number first |%2.5d| and number second|%2.3d|",
    "Number first |%+5.4d| and number second|%+5.4d|",
    "Number first |%-05.2d| and number second|%-05.8d|",
    "Number first |%+05.9d| and number second|%+05.1d|",
    "Number first |% 5.4d| and number second|% 5.4d|",
    "Number first |% 05.4d| and number second|% 05.4d|",
    "Number first |%+- 2.4d| and number second|%+- 2.4d|",
    "Number first |%-+ 02.2d| and number second|%-+ 02.2d|",
    "Number first |%-2.5d| and number second|%-2.3d|",
    "Number first |%.5d| and number second|% .3d|",
    "Number first |%.1d| and number second|%+.5d|",
    "Number first |%- .6d| and number second|%+ 0.5d|",
};

START_TEST(d_flag_width_precision_template) {
  const char *str = d_width_precision_template_vals[_i];
  int positive_number = 21;
  int negative_number = -42;

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str, positive_number, negative_number);
  int s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  positive_number = 0;

  def_res = sprintf(dest_def, str, positive_number, positive_number);
  s21_res = s21_sprintf(dest_s21, str, positive_number, positive_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *d_width_star_template_vals[] = {
    "Number first |%-*d| and number second|%-*d|",
    "Number first |%+*d| and number second|%+*d|",
    "Number first |%-0*d| and number second|%-0*d|",
    "Number first |%+0*d| and number second|%+0*d|",
    "Number first |% *d| and number second|% *d|",
    //"Number first |% 05d| and number second|% 0*d|",  undefined behavior case;
    "Number first |% 0*d| and number second|% 0*d|",
    "Number first |%+- *d| and number second|%+- *d|",
    "Number first |%-+ 0*d| and number second|%-+ 0*d|"};

START_TEST(d_flag_width_star_template) {
  const char *str = d_width_star_template_vals[_i];
  int positive_number = 21;
  int negative_number = -42;
  int star_value = 8;

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = s21_sprintf(dest_def, str, star_value, positive_number,
                            star_value, negative_number);
  int s21_res = s21_sprintf(dest_s21, str, star_value, positive_number,
                            star_value, negative_number);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  positive_number = 0;

  def_res = sprintf(dest_def, str, star_value, positive_number, star_value,
                    positive_number);
  s21_res = s21_sprintf(dest_s21, str, star_value, positive_number, star_value,
                        positive_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *d_width_precision_star_template_vals[] = {
    "Test |%-*.*d| string |%+0*.*d|", "Test |%*.*d| string |%+*.*d|",
    "Test |%+- 0*.*d| string |% *.*d|"};

START_TEST(d_flag_width_prec_star_template) {
  const char *str = d_width_precision_star_template_vals[_i];

  int first_amount = 5;
  int second_amount = 10;
  int positive_number = 21;
  int negative_number = -42;

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res =
      sprintf(dest_def, str, first_amount, second_amount, positive_number,
              first_amount, second_amount, negative_number);
  int s21_res =
      s21_sprintf(dest_s21, str, first_amount, second_amount, positive_number,
                  first_amount, second_amount, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  def_res = sprintf(dest_def, str, first_amount, second_amount, positive_number,
                    first_amount, second_amount, negative_number);
  s21_res =
      s21_sprintf(dest_s21, str, first_amount, second_amount, positive_number,
                  first_amount, second_amount, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *d_lenght_template_vals[] = {"Test %ld %ld", "Test %hd %hd",
                                               "Test %-+ 02.2hd %+03.5ld",
                                               "Test %-+ 02.2d %+03.5d"};

START_TEST(d_lenght_test) {
  const char *str = d_lenght_template_vals[_i];
  long int positive_number = LONG_MAX;
  long int negative_number = LONG_MIN;

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str, positive_number, negative_number);
  int s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  def_res = sprintf(dest_def, str, positive_number, negative_number);
  s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  positive_number = 0;
  negative_number = 0;

  def_res = sprintf(dest_def, str, positive_number, negative_number);
  s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

Suite *suite_s21_sprintf_d() {
  Suite *suite = suite_create("suite_s21_sprintf_d");

  TCase *d_flag_case = tcase_create("s21_sprintf_d_flag");
  tcase_add_test(d_flag_case, d_flag);
  suite_add_tcase(suite, d_flag_case);

  TCase *d_edge_case = tcase_create("s21_sprint_d_edge_vals");
  tcase_add_loop_test(d_edge_case, d_edge_cases, 0,
                      GET_SIZE_ARRAY(d_edge_vals));
  suite_add_tcase(suite, d_edge_case);

  TCase *d_flag_width_template_case =
      tcase_create("s21_sprint_d_width_template");
  tcase_add_loop_test(d_flag_width_template_case, d_flag_width_template, 0,
                      GET_SIZE_ARRAY(d_width_template_vals));
  suite_add_tcase(suite, d_flag_width_template_case);

  TCase *d_flag_width_prec_template_case =
      tcase_create("s21_sprint_d_width_precision_template");
  tcase_add_loop_test(d_flag_width_prec_template_case,
                      d_flag_width_precision_template, 0,
                      GET_SIZE_ARRAY(d_width_precision_template_vals));
  suite_add_tcase(suite, d_flag_width_prec_template_case);

  TCase *d_flag_width_star_template_case =
      tcase_create("s21_sprint_d_width_star_template");
  tcase_add_loop_test(d_flag_width_star_template_case,
                      d_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(d_width_star_template_vals));
  suite_add_tcase(suite, d_flag_width_star_template_case);

  TCase *d_flag_all_stars_template_case =
      tcase_create("s21_sprint_d_all_stars_template");
  tcase_add_loop_test(d_flag_all_stars_template_case,
                      d_flag_width_prec_star_template, 0,
                      GET_SIZE_ARRAY(d_width_precision_star_template_vals));
  suite_add_tcase(suite, d_flag_all_stars_template_case);

  TCase *d_lenght_test_case = tcase_create("s21_sprintf_d_lenght");
  tcase_add_loop_test(d_lenght_test_case, d_lenght_test, 0,
                      GET_SIZE_ARRAY(d_lenght_template_vals));
  suite_add_tcase(suite, d_lenght_test_case);

  return suite;
}
