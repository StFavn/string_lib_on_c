#include "s21_string_test.h"

START_TEST(u_flag) {
  const char format[] = "Number first %u and number second %u";
  const unsigned int number_1 = 1256;
  const unsigned int number_2 = 1492;
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

  const char format2[] = "%u";
  s21_res = s21_sprintf(dest_s21, format2, number_1);
  def_res = sprintf(dest_def, format2, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *u_width_template_vals[] = {
    "Number first |%5u| and number second|%5u|",
    "Number first |%-5u| and number second|%-5u|",
    "Number first |%+5u| and number second|%+5u|",
    "Number first |%-05u| and number second|%-05u|",
    "Number first |%+05u| and number second|%+05u|",
    "Number first |% 5u| and number second|% 5u|",
    "Number first |% 05u| and number second|% 05u|",
    "Number first |%+- 5u| and number second|%+- 5u|",
    "Number first |%2u| and number second|%2u|",
    "Number first |%1u| and number second|%3u|",
    "Number first |%3u| and number second|%4u|",
    "Number first |%-+ 02u| and number second|%-+ 02u|",
    "Number first |%-1u| and number second|%-1u|",
    "Number first |%+2u| and number second|%+2u|",
    "Number first |%-01u| and number second|%-03u|",
    "Number first |%+01u| and number second|%+01u|",
    "Number first |% 2u| and number second|% 3u|",
    "Number first |% 01u| and number second|% 03u|",
    "Number first |%+- 1u| and number second|%+- 1u|",
    "Number first |%-+ 02u| and number second|%-+ 02u|"};

START_TEST(u_flag_width_template) {
  const char *str = u_width_template_vals[_i];
  unsigned int positive_number = 21;
  unsigned long int negative_number = UINT32_MAX;

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

static const char *u_width_precision_template_vals[] = {
    "Number first |%2.5u| and number second|%2.3u|",
    "Number first |%+5.4u| and number second|%+5.4u|",
    "Number first |%-05.2u| and number second|%-05.8u|",
    "Number first |%+05.9u| and number second|%+05.1u|",
    "Number first |% 5.4u| and number second|% 5.4u|",
    "Number first |% 05.4u| and number second|% 05.4u|",
    "Number first |%+- 2.4u| and number second|%+- 2.4u|",
    "Number first |%-+ 02.2u| and number second|%-+ 02.2u|",
    "Number first |%-2.5u| and number second|%-2.3u|",
    "Number first |%.5u| and number second|% .3u|",
    "Number first |%.1u| and number second|%+.5u|",
    "Number first |%- .6u| and number second|%+ 0.5u|",
};

START_TEST(u_flag_width_precision_template) {
  const char *str = u_width_precision_template_vals[_i];
  unsigned long long int positive_number = ULLONG_MAX;
  unsigned int negative_number = 525;

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

static const char *u_width_star_template_vals[] = {
    "Number first |%-*u| and number second|%-*u|",
    "Number first |%+*u| and number second|%+*u|",
    "Number first |%-0*u| and number second|%-0*u|",
    "Number first |%+0*u| and number second|%+0*u|",
    "Number first |% *u| and number second|% *u|",
    //"Number first |% 05d| and number second|% 0*d|",  undefined behavior case;
    "Number first |% 0*u| and number second|% 0*u|",
    "Number first |%+- *u| and number second|%+- *u|",
    "Number first |%-+ 0*u| and number second|%-+ 0*u|"};

START_TEST(u_flag_width_star_template) {
  const char *str = u_width_star_template_vals[_i];
  unsigned int positive_number = 896;
  unsigned long long int negative_number = ULLONG_MAX;
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

static const char *u_width_precision_star_template_vals[] = {
    "Test |%-*.*u| string |%+0*.*u|", "Test |%*.*u| string |%+*.*u|",
    "Test |%+- 0*.*u| string |% *.*u|"};

START_TEST(u_flag_width_prec_star_template) {
  const char *str = u_width_precision_star_template_vals[_i];

  int first_amount = 5;
  int second_amount = 10;
  unsigned int positive_number = 21;
  unsigned long long int negative_number = ULONG_MAX;

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

static const char *u_lenght_template_vals[] = {"Test %lu %lu", "Test %hu %hu",
                                               "Test %-+ 02.2hu %+03.5lu",
                                               "Test %-+ 02.2u %+03.5u"};

START_TEST(u_lenght_test) {
  const char *str = u_lenght_template_vals[_i];
  unsigned long long int positive_number = ULLONG_MAX;
  unsigned long long int negative_number = ULONG_MAX;

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

Suite *suite_s21_sprintf_u() {
  Suite *suite = suite_create("suite_s21_sprintf_u");

  TCase *u_flag_case = tcase_create("s21_sprintf_u_flag");
  tcase_add_test(u_flag_case, u_flag);
  suite_add_tcase(suite, u_flag_case);

  TCase *u_flag_width_template_case =
      tcase_create("s21_sprint_u_width_template");
  tcase_add_loop_test(u_flag_width_template_case, u_flag_width_template, 0,
                      GET_SIZE_ARRAY(u_width_template_vals));
  suite_add_tcase(suite, u_flag_width_template_case);

  TCase *u_flag_width_prec_template_case =
      tcase_create("s21_sprint_u_width_precision_template");
  tcase_add_loop_test(u_flag_width_prec_template_case,
                      u_flag_width_precision_template, 0,
                      GET_SIZE_ARRAY(u_width_precision_template_vals));
  suite_add_tcase(suite, u_flag_width_prec_template_case);

  TCase *u_flag_width_star_template_case =
      tcase_create("s21_sprint_u_width_star_template");
  tcase_add_loop_test(u_flag_width_star_template_case,
                      u_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(u_width_star_template_vals));
  suite_add_tcase(suite, u_flag_width_star_template_case);

  TCase *u_flag_all_stars_template_case =
      tcase_create("s21_sprint_u_all_stars_template");
  tcase_add_loop_test(u_flag_all_stars_template_case,
                      u_flag_width_prec_star_template, 0,
                      GET_SIZE_ARRAY(u_width_precision_star_template_vals));
  suite_add_tcase(suite, u_flag_all_stars_template_case);

  TCase *u_lenght_test_case = tcase_create("s21_sprintf_u_lenght");
  tcase_add_loop_test(u_lenght_test_case, u_lenght_test, 0,
                      GET_SIZE_ARRAY(u_lenght_template_vals));
  suite_add_tcase(suite, u_lenght_test_case);

  return suite;
}
