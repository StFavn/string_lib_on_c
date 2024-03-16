#include "s21_string_test.h"

#define BUFFER 1024

START_TEST(el_flag) {
  const char format[] = "Number first %E and number second %E";
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

  const char format2[] = "%E";
  s21_res = s21_sprintf(dest_s21, format2, number_1);
  def_res = sprintf(dest_def, format2, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *el_width_template_vals[] = {
    "Number first |%5E| and number second|%15E|",
    "Number first |%-5E| and number second|%-5E|",
    "Number first |%+15E| and number second|%+15E|",
    "Number first |%-015E| and number second|%-015E|",
    "Number first |%+015E| and number second|%+015E|",
    "Number first |% 15E| and number second|% 15E|",
    "Number first |% 015E| and number second|% 015E|",
    "Number first |%+- 15E| and number second|%+- 15E|",
    "Number first |%2E| and number second|%2E|",
    "Number first |%10E| and number second|%15E|",
    "Number first |%3E| and number second|%4E|",
    "Number first |%-+ 015E| and number second|%-+ 015E|",
    "Number first |%-10E| and number second|%-10E|",
    "Number first |%+15E| and number second|%+15E|",
    "Number first |%-010E| and number second|%-015E|",
    "Number first |%+010E| and number second|%+010E|",
    "Number first |% 15E| and number second|% 15E|",
    "Number first |% 010E| and number second|% 030E|",
    "Number first |%+- 10E| and number second|%+- 10E|",
    "Number first |%-+ 015E| and number second|%-+ 015E|",
    "Number first |%+- 15E| and number second|%+#- 15E|",
    "Number first |%2E| and number second|%#2E|",
    "Number first |%10E| and number second|%#15E|",
    "Number first |%3E| and number second|%#4E|",
    "Number first |%-+ 015E| and number second|%-#+ 015E|",
    "Number first |%-10E| and number second|%-#10E|",
    "Number first |%+15E| and number second|%+#15E|",
    "Number first |%-010E| and number second|%#-015E|",
    "Number first |%+010E| and number second|%+#010E|",
    "Number first |% 15E| and number second|% #15E|",
    "Number first |% 010E| and number second|% #030E|",
    "Number first |%+- 10E| and number second|%+#- 10E|",
    "Number first |%-+ 015E| and number second|%-#+ 015E|"};

START_TEST(el_flag_width_template) {
  const char *str = el_width_template_vals[_i];
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

static const char *el_width_precision_template_vals[] = {
    "Number first |%10.10E| and number second|%10.10E|",
    "Number first |%+5.4E| and number second|%+5.4E|",
    "Number first |%+15.10E| and number second|%+15.10E|",
    "Number first |%+10.15E| and number second|%+10.15E|",
    "Number first |%-010.15E| and number second|%-010.15E|",
    "Number first |%+05.9E| and number second|%+05.1E|",
    "Number first |% 8.9E| and number second|% 9.8E|",
    "Number first |% 08.9E| and number second|% 09.8E|",
    "Number first |%+- 2.4E| and number second|%+- 2.4E|",
    "Number first |%+- 9.8E| and number second|%+- 8.9E|",
    "Number first |%-+ 08.9E| and number second|%-+ 09.6E|",
    "Number first |%-10.5E| and number second|%-5.10E|",
    "Number first |%.5E| and number second|% .16E|",
    "Number first |%.1E| and number second|%+.16E|",
    "Number first |%- .6E| and number second|%+ 0.5E|",

    "Number first |%10.10E| and number second|%#10.0E|",
    "Number first |%+5.4E| and number second|%+#5.0E|",
    "Number first |%+15.10E| and number second|%+#15.0E|",
    "Number first |%+10.15E| and number second|%+#10.0E|",
    "Number first |%-010.15E| and number second|%-#010.0E|",
    "Number first |%+05.9E| and number second|%+#05.0E|",
    "Number first |% 8.9E| and number second|% #9.0E|",
    "Number first |% 08.9E| and number second|% #09.0E|",
    "Number first |%+- 2.4E| and number second|%+- #2.0E|",
    "Number first |%+- 9.8E| and number second|%+#- 8.0E|",
    "Number first |%-+ 08.9E| and number second|%-#+ 09.0E|",
    "Number first |%-10.5E| and number second|%-#5.0E|",
    "Number first |%.5E| and number second|% #.0E|",
    "Number first |%.1E| and number second|%+#.0E|",
    "Number first |%- .6E| and number second|%+# 0.0E|",

};

START_TEST(el_flag_width_precision_template) {
  const char *str = el_width_precision_template_vals[_i];
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

static const char *el_width_star_template_vals[] = {
    "Number first |%-*E| and number second|%-*E|",
    "Number first |%+*E| and number second|%+*E|",
    "Number first |%-0*E| and number second|%-0*E|",
    "Number first |%+0*E| and number second|%+0*E|",
    "Number first |% *E| and number second|% *E|",
    "Number first |% 0*E| and number second|% 0*E|",
    "Number first |%+-*E| and number second|%+- *E|",
    "Number first |%-+ 0*E| and numbersecond|%-+ 0*E|",
    "Number first |%-#*E| and number second|%-#*E|",
    "Number first |%+#*E| and number second|%+#*E|",
    "Number first |%-#0*E| and number second|%-0#*E|",
    "Number first |%+#0*E| and number second|%+0#*E|",
    "Number first |% #*E| and number second|% #*E|",
    "Number first |% #0*E| and number second|% 0#*E|",
    "Number first |%+#-*E| and number second|%+- #*E|",
    "Number first |%-#+ 0*E| and numbersecond|%-+ #0*E|"};

START_TEST(el_flag_width_star_template) {
  const char *str = el_width_star_template_vals[_i];
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

static const char *el_width_precision_star_template_vals[] = {
    "Test |%-*.*E| string |%+0*.*E|",     //
    "Test |%*.*E| string |%+*.*E|",       //
    "Test |%+- 0*.*E| string |% #*.*E|",  //
    "Test |%-#*.*E| string |%+0#*.*E|",   //
    "Test |%#*.*E| string |%+#*.*E|",     //
    "Test |%+#- 0*.*E| string |% #*.*E|"  //
};

START_TEST(el_flag_width_prec_star_template) {
  const char *str = el_width_precision_star_template_vals[_i];

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

static const char *el_lenght_template_vals[] = {
    "Test %LE %E", "Test %.10LE %.10E", "Test %-+ 02.2LE %+07E",
    "Test %-+ 07.7LE %+010.10E"};

START_TEST(el_lenght_test) {
  const char *str = el_lenght_template_vals[_i];
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

Suite *suite_s21_sprintf_el() {
  Suite *suite = suite_create("suite_s21_sprintf_el");

  TCase *el_flag_case = tcase_create("s21_sprintf_el_flag");
  tcase_add_test(el_flag_case, el_flag);
  suite_add_tcase(suite, el_flag_case);

  TCase *el_flag_width_template_case =
      tcase_create("s21_sprint_el_width_template");
  tcase_add_loop_test(el_flag_width_template_case, el_flag_width_template, 0,
                      GET_SIZE_ARRAY(el_width_template_vals));
  suite_add_tcase(suite, el_flag_width_template_case);

  TCase *el_flag_width_prec_template_case =
      tcase_create("s21_sprint_el_width_precision_template");
  tcase_add_loop_test(el_flag_width_prec_template_case,
                      el_flag_width_precision_template, 0,
                      GET_SIZE_ARRAY(el_width_precision_template_vals));
  suite_add_tcase(suite, el_flag_width_prec_template_case);

  TCase *el_flag_width_star_template_case =
      tcase_create("s21_sprint_el_width_star_template");
  tcase_add_loop_test(el_flag_width_star_template_case,
                      el_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(el_width_star_template_vals));
  suite_add_tcase(suite, el_flag_width_star_template_case);

  TCase *el_flag_all_stars_template_case =
      tcase_create("s21_sprint_el_all_stars_template");
  tcase_add_loop_test(el_flag_all_stars_template_case,
                      el_flag_width_prec_star_template, 0,
                      GET_SIZE_ARRAY(el_width_precision_star_template_vals));
  suite_add_tcase(suite, el_flag_all_stars_template_case);

  TCase *el_lenght_test_case = tcase_create("s21_sprintf_el_lenght");
  tcase_add_loop_test(el_lenght_test_case, el_lenght_test, 0,
                      GET_SIZE_ARRAY(el_lenght_template_vals));
  suite_add_tcase(suite, el_lenght_test_case);

  return suite;
}
