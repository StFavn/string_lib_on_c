#include "s21_string_test.h"

#define BUFFER 1024

START_TEST(e_flag) {
  const char format[] = "Number first %e and number second %e";
  const double number_1 = -21.4245445466;
  const double number_2 = 0.056245656;
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

  const char format2[] = "%e";
  s21_res = s21_sprintf(dest_s21, format2, number_1);
  def_res = sprintf(dest_def, format2, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *e_width_template_vals[] = {
    "Number first |%5e| and number second|%15e|",
    "Number first |%-5e| and number second|%-5e|",
    "Number first |%+15e| and number second|%+15e|",
    "Number first |%-015e| and number second|%-015e|",
    "Number first |%+015e| and number second|%+015e|",
    "Number first |% 15e| and number second|% 15e|",
    "Number first |% 015e| and number second|% 015e|",
    "Number first |%+- 15e| and number second|%+- 15e|",
    "Number first |%2e| and number second|%2e|",
    "Number first |%10e| and number second|%15e|",
    "Number first |%3e| and number second|%4e|",
    "Number first |%-+ 015e| and number second|%-+ 015e|",
    "Number first |%-10e| and number second|%-10e|",
    "Number first |%+15e| and number second|%+15e|",
    "Number first |%-010e| and number second|%-015e|",
    "Number first |%+010e| and number second|%+010e|",
    "Number first |% 15e| and number second|% 15e|",
    "Number first |% 010e| and number second|% 030e|",
    "Number first |%+- 10e| and number second|%+- 10e|",
    "Number first |%-+ 015e| and number second|%-+ 015e|",
    "Number first |%#10e| and number second|%#15e|",
    "Number first |%#3e| and number second|%#4e|",
    "Number first |%-#+ 015e| and number second|%-#+ 015e|",
    "Number first |%-#10e| and number second|%-#10e|",
    "Number first |%+#15e| and number second|%+#15e|",
    "Number first |%-#010e| and number second|%#-015e|",
    "Number first |%+#010e| and number second|%+#010e|",
    "Number first |% #15e| and number second|% #15e|",
    "Number first |% #010e| and number second|% #030e|",
    "Number first |%+-# 10e| and number second|%+- #10e|",
    "Number first |%-+# 015e| and number second|%-+ #015e|"};

START_TEST(e_flag_width_template) {
  const char *str = e_width_template_vals[_i];
  double number_1 = -21.424545454544;
  double number_2 = 0.9999999565;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res = sprintf(dest_def, str, number_1, number_2);
  int s21_res = s21_sprintf(dest_s21, str, number_1, number_2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  number_1 = 123456789012323;
  number_2 = 0;

  def_res = sprintf(dest_def, str, number_1, number_2);
  s21_res = s21_sprintf(dest_s21, str, number_1, number_2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *e_width_precision_template_vals[] = {
    "Number first |%10.10e| and number second|%10.10e|",
    "Number first |%+5.4e| and number second|%+5.4e|",
    "Number first |%+15.10e| and number second|%+15.10e|",
    "Number first |%+10.15e| and number second|%+10.15e|",
    "Number first |%-010.15e| and number second|%-010.15e|",
    "Number first |%+05.9e| and number second|%+05.1e|",
    "Number first |% 8.9e| and number second|% 9.8e|",
    "Number first |% 08.9e| and number second|% 09.8e|",
    "Number first |%+- 2.4e| and number second|%+- 2.4e|",
    "Number first |%+- 9.8e| and number second|%+- 8.9e|",
    "Number first |%-+ 08.9e| and number second|%-+ 09.6e|",
    "Number first |%-10.5e| and number second|%-5.10e|",
    "Number first |%.5e| and number second|% .16e|",
    "Number first |%.1e| and number second|%+.16e|",
    "Number first |%- .6e| and number second|%+ 0.5e|",
    "Number first |%#10.10e| and number second|%#10.0e|",
    "Number first |%+#5.4e| and number second|%+#5.0e|",
    "Number first |%+#15.10e| and number second|%+#15.0e|",
    "Number first |%+#10.15e| and number second|%+#10.0e|",
    "Number first |%-#010.15e| and number second|%-#010.0e|",
    "Number first |%+#05.9e| and number second|%+#05.0e|",
    "Number first |% #8.9e| and number second|% #9.0e|",
    "Number first |% #08.9e| and number second|% #09.0e|",
    "Number first |%+#- 2.4e| and number second|%+-# 2.0e|",
    "Number first |%+#- 9.8e| and number second|%+- #8.0e|",
    "Number first |%-#+ 08.9e| and number second|%-+ #09.0e|",
    "Number first |%-#10.5e| and number second|%-#5.0e|",
    "Number first |%#.5e| and number second|% #.0e|",
    "Number first |%#.1e| and number second|%+#.0e|",
    "Number first |%- #.6e| and number second|%+ #0.0e|"};

START_TEST(e_flag_width_precision_template) {
  const char *str = e_width_precision_template_vals[_i];
  double positive_number = 0.9999999565;
  double negative_number = -21.42;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res = sprintf(dest_def, str, positive_number, negative_number);
  int s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  positive_number = 123456789012323;
  negative_number = 0;

  def_res = sprintf(dest_def, str, positive_number, negative_number);
  s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *e_width_star_template_vals[] = {
    "Number first |%-*e| and number second|%-*e|",
    "Number first |%+*e| and number second|%+*e|",
    "Number first |%-0*e| and number second|%-0*e|",
    "Number first |%+0*e| and number second|%+0*e|",
    "Number first |% *e| and number second|% *e|",
    "Number first |% 0*e| and number second|% 0*e|",
    "Number first |%+-*e| and number second|%+- *e|",
    "Number first |%-+ 0*e| and numbersecond|%-+ 0*e|",
    "Number first |%-#*e| and number second|%-#*e|",
    "Number first |%+#*e| and number second|%+#*e|",
    "Number first |%-#0*e| and number second|%#-0*e|",
    "Number first |%+#0*e| and number second|%#+0*e|",
    "Number first |% #*e| and number second|% #*e|",
    "Number first |% #0*e| and number second|% #0*e|",
    "Number first |%+#-*e| and number second|%+-# *e|",
    "Number first |%-#+ 0*e| and numbersecond|%-+# 0*e|"};

START_TEST(e_flag_width_star_template) {
  const char *str = e_width_star_template_vals[_i];
  double positive_number = 0.9999999565;
  double negative_number = -21.421231132123131231;
  int star_value = 8;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res = s21_sprintf(dest_def, str, star_value, positive_number,
                            star_value, negative_number);
  int s21_res = s21_sprintf(dest_s21, str, star_value, positive_number,
                            star_value, negative_number);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  positive_number = 123456789012323;
  negative_number = 0;

  def_res = sprintf(dest_def, str, star_value, positive_number, star_value,
                    negative_number);
  s21_res = s21_sprintf(dest_s21, str, star_value, positive_number, star_value,
                        negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *e_width_precision_star_template_vals[] = {
    "Test |%-*.*e| string |%+0*.*e|",     //
    "Test |%*.*e| string |%+*.*e|",       //
    "Test |%+- 0*.*e| string |%# *.*e|",  //
    "Test |%-#*.*e| string |%+#0*.*e|",   //
    "Test |%#*.*e| string |%+#*.*e|",     //
    "Test |%+#- 0*.*e| string |%# *.*e|"  //
};

START_TEST(e_flag_width_prec_star_template) {
  const char *str = e_width_precision_star_template_vals[_i];

  int first_amount = 5;
  int second_amount = 10;
  double positive_number = 0.9999999565;
  double negative_number = -21.424646454654464;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res =
      sprintf(dest_def, str, first_amount, second_amount, positive_number,
              first_amount, second_amount, negative_number);
  int s21_res =
      s21_sprintf(dest_s21, str, first_amount, second_amount, positive_number,
                  first_amount, second_amount, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  def_res = sprintf(dest_def, str, first_amount, second_amount, positive_number,
                    first_amount, second_amount, negative_number);
  s21_res =
      s21_sprintf(dest_s21, str, first_amount, second_amount, positive_number,
                  first_amount, second_amount, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *e_lenght_template_vals[] = {
    "Test %Le %e", "Test %.10Le %.10e", "Test %-+ 02.2Le %+07e",
    "Test %-+ 07.7Le %+010.10e"};

START_TEST(e_lenght_test) {
  const char *str = e_lenght_template_vals[_i];
  long double positive_number = 0.9999999565;
  double negative_number = -21.425446446546546544;

  char dest_s21[BUFFER] = {0};
  char dest_def[BUFFER] = {0};

  int def_res = sprintf(dest_def, str, positive_number, negative_number);
  int s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  def_res = sprintf(dest_def, str, positive_number, negative_number);
  s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BUFFER);
  memset(dest_def, '@', BUFFER);

  positive_number = 123456789012323;
  negative_number = 0;

  def_res = sprintf(dest_def, str, positive_number, negative_number);
  s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

Suite *suite_s21_sprintf_es() {
  Suite *suite = suite_create("suite_s21_sprintf_es");

  TCase *e_flag_case = tcase_create("s21_sprintf_es_flag");
  tcase_add_test(e_flag_case, e_flag);
  suite_add_tcase(suite, e_flag_case);

  TCase *e_flag_width_template_case =
      tcase_create("s21_sprint_es_width_template");
  tcase_add_loop_test(e_flag_width_template_case, e_flag_width_template, 0,
                      GET_SIZE_ARRAY(e_width_template_vals));
  suite_add_tcase(suite, e_flag_width_template_case);

  TCase *e_flag_width_prec_template_case =
      tcase_create("s21_sprint_es_width_precision_template");
  tcase_add_loop_test(e_flag_width_prec_template_case,
                      e_flag_width_precision_template, 0,
                      GET_SIZE_ARRAY(e_width_precision_template_vals));
  suite_add_tcase(suite, e_flag_width_prec_template_case);

  TCase *e_flag_width_star_template_case =
      tcase_create("s21_sprint_es_width_star_template");
  tcase_add_loop_test(e_flag_width_star_template_case,
                      e_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(e_width_star_template_vals));
  suite_add_tcase(suite, e_flag_width_star_template_case);

  TCase *e_flag_all_stars_template_case =
      tcase_create("s21_sprint_es_all_stars_template");
  tcase_add_loop_test(e_flag_all_stars_template_case,
                      e_flag_width_prec_star_template, 0,
                      GET_SIZE_ARRAY(e_width_precision_star_template_vals));
  suite_add_tcase(suite, e_flag_all_stars_template_case);

  TCase *e_lenght_test_case = tcase_create("s21_sprintf_es_lenght");
  tcase_add_loop_test(e_lenght_test_case, e_lenght_test, 0,
                      GET_SIZE_ARRAY(e_lenght_template_vals));
  suite_add_tcase(suite, e_lenght_test_case);

  return suite;
}
