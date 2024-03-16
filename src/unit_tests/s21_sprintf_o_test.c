#include "s21_string_test.h"

#define BUFFER 1024

START_TEST(o_flag) {
  const char format[] = "Number first %o and number second %o";
  const unsigned int number_1 = 1256;
  const unsigned int number_2 = 1492;
  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  int s21_res = s21_sprintf(dest_s21, format, number_1, number_2);
  int def_res = sprintf(dest_def, format, number_1, number_2);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  const char format2[] = "%o";
  s21_res = s21_sprintf(dest_s21, format2, number_1);
  def_res = sprintf(dest_def, format2, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  const char format3[] = "%#o";
  s21_res = s21_sprintf(dest_s21, format3, number_1);
  def_res = sprintf(dest_def, format3, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *o_width_template_vals[] = {
    "Number first |%5o| and number second|%5o",
    "Number first |%-5o| and number second|%-5o",
    "Number first |%+5o| and number second|%+5o",
    "Number first |%-05o| and number second|%-05o",
    "Number first |%+05o| and number second|%+05o",
    "Number first |% 5o| and number second|% 5o",
    "Number first |% 05o| and number second|% 05o",
    "Number first |%+- 5o| and number second|%+- 5o",
    "Number first |%2o| and number second|%2o",
    "Number first |%1o| and number second|%3o",
    "Number first |%3o| and number second|%4o",
    "Number first |%-+ 02o| and number second|%-+ 02o",
    "Number first |%-1o| and number second|%-1o",
    "Number first |%+2o| and number second|%+2o",
    "Number first |%-01o| and number second|%-03o",
    "Number first |%+01o| and number second|%+01o",
    "Number first |% 20o| and number second|% 30o",
    "Number first |% 010o| and number second|% 030o",
    "Number first |%+- 1o| and number second|%+- 1o",
    "Number first |%-+ 02o| and number second|%-+ 02o",
    "Number first |%-+ 010o| and number second|%-+ 010o",
    "Number first |%#5o| and number second|%#5o",
    "Number first |%#-15o| and number second|%-#50o",
    "Number first |%#+5o| and number second|%+#5o",
    "Number first |%#-05o| and number second|%-#05o",
    "Number first |%#+010o| and number second|%+#010o",
    "Number first |%# 5o| and number second|%# 5o",
    "Number first |%# 05o| and number second|%# 05o",
    "Number first |%#+- 15o| and number second|%#+- 15o",
    "Number first |%#+- 015o| and number second|%#+- 015o",
    "Number first |%#+- 0150o| and number second|%#+- 0150o"};

START_TEST(o_flag_width_template) {
  const char *str = o_width_template_vals[_i];
  unsigned int number1 = 21;
  unsigned long int number2 = UINT32_MAX;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res = sprintf(dest_def, str, number1, number2);
  int s21_res = s21_sprintf(dest_s21, str, number1, number2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  number1 = 0;

  def_res = sprintf(dest_def, str, number1, number1);
  s21_res = s21_sprintf(dest_s21, str, number1, number1);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *o_width_precision_template_vals[] = {
    "Number first |%2.5o| and number second|%2.3o|",
    "Number first |%+5.4o| and number second|%+5.4o|",
    "Number first |%-05.2o| and number second|%-05.8o|",
    "Number first |%+05.9o| and number second|%+05.1o|",
    "Number first |% 5.4o| and number second|% 5.4o|",
    "Number first |% 05.4o| and number second|% 05.4o|",
    "Number first |%+- 2.4o| and number second|%+- 2.4o|",
    "Number first |%-+ 02.2o| and number second|%-+ 02.2o|",
    "Number first |%-2.5o| and number second|%-2.3o|",
    "Number first |%.5o| and number second|% .3o|",
    "Number first |%.1o| and number second|%+.5o|",
    "Number first |%- .6o| and number second|%+ 0.5o|",
    "Number first |%#2.5o| and number second|%#2.3o|",
    "Number first |%#+5.4o| and number second|%#+5.4o|",
    "Number first |%#-05.2o| and number second|%#-05.8o|",
    "Number first |%#+05.9o| and number second|%#+05.1o|",
    "Number first |%# 5.4o| and number second|%# 5.4o|",
    "Number first |%# 05.4o| and number second|%# 05.4o|",
    "Number first |%#+- 2.4o| and number second|%#+- 2.4o|",
    "Number first |%#-+ 02.2o| and number second|%#-+ 02.2o|",
    "Number first |%#-2.5o| and number second|%#-2.3o|",
    "Number first |%#.5o| and number second|%# .3o|",
    "Number first |%#.1o| and number second|%#+.5o|",
    "Number first |%#- .6o| and number second|%#+ 0.5o|",
    "Number first |%#10.5o| and number second|%#5.10o|",
    "Number first |%#+10.5o| and number second|%#+5.10o|",
    "Number first |%#-010.5o| and number second|%#-05.10o|",
    "Number first |%#+010.5o| and number second|%#+05.10o|",
    "Number first |%# 10.5o| and number second|%# 5.10o|",
    "Number first |%# 010.5o| and number second|%# 05.10o|",
    "Number first |%#+- 10.5o| and number second|%#+- 5.10o|",
    "Number first |%#-+ 010.5o| and number second|%#-+ 05.10o|",
    "Number first |%#-10.5o| and number second|%#-5.10o",
    "Number first |%#.10o| and number second|%# .3o|",
    "Number first |%#.1o| and number second|%#+.5o|",
    "Number first |%#- .6o| and number second|%#+ 0.5o|",
};

START_TEST(o_flag_width_precision_template) {
  const char *str = o_width_precision_template_vals[_i];
  unsigned long long int number1 = ULLONG_MAX;
  unsigned int number2 = 525;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res = sprintf(dest_def, str, number1, number2);
  int s21_res = s21_sprintf(dest_s21, str, number1, number2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  number1 = 0;

  def_res = sprintf(dest_def, str, number1, number1);
  s21_res = s21_sprintf(dest_s21, str, number1, number1);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *o_width_star_template_vals[] = {
    "Number first |%-*o| and number second|%-*o|",
    "Number first |%+*o| and number second|%+*o|",
    "Number first |%-0*o| and number second|%-0*o|",
    "Number first |%+0*o| and number second|%+0*o|",
    "Number first |% *o| and number second|% *o|",
    "Number first |% 0*o| and number second|% 0*o|",
    "Number first |%+- *o| and number second|%+- *o|",
    "Number first |%-+ 0*o| and number second|%-+ 0*o|",
    "Number first |%#-*o| and number second|%#-*o|",
    "Number first |%+#*o| and number second|%+#*o|",
    "Number first |%-#0*o| and number second|%#-0*o|",
    "Number first |%#+0*o| and number second|%+#0*o|",
    "Number first |%# *o| and number second|%# *o|",
    "Number first |%# 0*o| and number second|%# 0*o|",
    "Number first |%#+- *o| and number second|%+-# *o|",
    "Number first |%-#+ 0*o| and number second|%-#+ 0*o|"};

START_TEST(o_flag_width_star_template) {
  const char *str = o_width_star_template_vals[_i];
  unsigned int number1 = 1023;
  unsigned long long int number2 = ULLONG_MAX;
  int star_value = 15;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res =
      s21_sprintf(dest_def, str, star_value, number1, star_value, number2);
  int s21_res =
      s21_sprintf(dest_s21, str, star_value, number1, star_value, number2);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  number1 = 0;

  def_res = sprintf(dest_def, str, star_value, number1, star_value, number1);
  s21_res =
      s21_sprintf(dest_s21, str, star_value, number1, star_value, number1);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *o_width_precision_star_template_vals[] = {
    "Test |%-*.*o| string |%+0*.*o|",   "Test |%*.*o| string |%+*.*o|",
    "Test |%+- 0*.*o| string |% *.*o|", "Test |%#-*.*o| string |%+0#*.*o|",
    "Test |%#*.*o| string |%+#*.*o|",   "Test |%+-# 0*.*o| string |%# *.*o|"};

START_TEST(o_flag_width_prec_star_template) {
  const char *str = o_width_precision_star_template_vals[_i];

  int first_amount = 10;
  int second_amount = 15;
  unsigned int number1 = 1022;
  unsigned long long int number2 = ULONG_MAX;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res = sprintf(dest_def, str, first_amount, second_amount, number1,
                        first_amount, second_amount, number2);
  int s21_res = s21_sprintf(dest_s21, str, first_amount, second_amount, number1,
                            first_amount, second_amount, number2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  def_res = sprintf(dest_def, str, first_amount, second_amount, number1,
                    first_amount, second_amount, number2);
  s21_res = s21_sprintf(dest_s21, str, first_amount, second_amount, number1,
                        first_amount, second_amount, number2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *o_lenght_template_vals[] = {
    "Test %lo %lo", "Test %ho %ho", "Test %-+ 02.2ho %+03.5lo",
    "Test %-+ 02.2o %+03.5o", "Test %-#+ 05.10ho %+#010.5lo"};

START_TEST(o_lenght_test) {
  const char *str = o_lenght_template_vals[_i];
  unsigned long long int number1 = ULLONG_MAX;
  unsigned long long int number2 = ULONG_MAX;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res = sprintf(dest_def, str, number1, number2);
  int s21_res = s21_sprintf(dest_s21, str, number1, number2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  def_res = sprintf(dest_def, str, number1, number2);
  s21_res = s21_sprintf(dest_s21, str, number1, number2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  number1 = 0;
  number2 = 0;

  def_res = sprintf(dest_def, str, number1, number2);
  s21_res = s21_sprintf(dest_s21, str, number1, number2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

Suite *suite_s21_sprintf_o() {
  Suite *suite = suite_create("suite_s21_sprintf_o");

  TCase *o_flag_case = tcase_create("s21_sprintf_o_flag");
  tcase_add_test(o_flag_case, o_flag);
  suite_add_tcase(suite, o_flag_case);

  TCase *o_flag_width_template_case =
      tcase_create("s21_sprint_o_width_template");
  tcase_add_loop_test(o_flag_width_template_case, o_flag_width_template, 0,
                      GET_SIZE_ARRAY(o_width_template_vals));
  suite_add_tcase(suite, o_flag_width_template_case);

  TCase *o_flag_width_prec_template_case =
      tcase_create("s21_sprint_o_width_precision_template");
  tcase_add_loop_test(o_flag_width_prec_template_case,
                      o_flag_width_precision_template, 0,
                      GET_SIZE_ARRAY(o_width_precision_template_vals));
  suite_add_tcase(suite, o_flag_width_prec_template_case);

  TCase *o_flag_width_star_template_case =
      tcase_create("s21_sprint_o_width_star_template");
  tcase_add_loop_test(o_flag_width_star_template_case,
                      o_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(o_width_star_template_vals));
  suite_add_tcase(suite, o_flag_width_star_template_case);

  TCase *o_flag_all_stars_template_case =
      tcase_create("s21_sprint_o_all_stars_template");
  tcase_add_loop_test(o_flag_all_stars_template_case,
                      o_flag_width_prec_star_template, 0,
                      GET_SIZE_ARRAY(o_width_precision_star_template_vals));
  suite_add_tcase(suite, o_flag_all_stars_template_case);

  TCase *o_lenght_test_case = tcase_create("s21_sprintf_o_lenght");
  tcase_add_loop_test(o_lenght_test_case, o_lenght_test, 0,
                      GET_SIZE_ARRAY(o_lenght_template_vals));
  suite_add_tcase(suite, o_lenght_test_case);

  return suite;
}
