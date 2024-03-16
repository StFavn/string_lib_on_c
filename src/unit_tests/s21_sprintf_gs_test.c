#include "s21_string_test.h"

const double gs_flag_numbers[] = {0.0506245656,
                                  0.00506245656,
                                  0.000506245656,
                                  0.0000506245656,
                                  -0.0506245656,
                                  -0.00506245656,
                                  -0.000506245656,
                                  -0.0000506245656,
                                  1,
                                  0.1,
                                  0.01,
                                  0.001,
                                  0.0001,
                                  0.00001,
                                  -1,
                                  -0.1,
                                  -0.01,
                                  -0.001,
                                  -0.0001,
                                  -0.00001};

START_TEST(gs_flag) {
  const char format[] = "Number first %g and number second %g";
  const double number_1 = -21.42;
  const double number_2 = gs_flag_numbers[_i];

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int s21_res = s21_sprintf(dest_s21, format, number_1, number_2);
  int def_res = sprintf(dest_def, format, number_1, number_2);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  const char format2[] = "%g";
  s21_res = s21_sprintf(dest_s21, format2, number_2);
  def_res = sprintf(dest_def, format2, number_2);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  const char format3[] = "%#g";
  s21_res = s21_sprintf(dest_s21, format3, number_2);
  def_res = sprintf(dest_def, format3, number_2);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *gs_width_template_vals[] = {
    "Number first |%5g| and number second|%15g|",
    "Number first |%-5g| and number second|%-5g|",
    "Number first |%+15g| and number second|%+15g|",
    "Number first |%-015g| and number second|%-015g|",
    "Number first |%+015g| and number second|%+015g|",
    "Number first |% 15g| and number second|% 15g|",
    "Number first |% 015g| and number second|% 015g|",
    "Number first |%+- 15g| and number second|%+- 15g|",
    "Number first |%2g| and number second|%2g|",
    "Number first |%10g| and number second|%15g|",
    "Number first |%3g| and number second|%4g|",
    "Number first |%-+ 015g| and number second|%-+ 015g|",
    "Number first |%-10g| and number second|%-10g|",
    "Number first |%+15g| and number second|%+15g|",
    "Number first |%-010g| and number second|%-015g|",
    "Number first |%+010g| and number second|%+010g|",
    "Number first |% 15g| and number second|% 15g|",
    "Number first |% 010g| and number second|% 030g|",
    "Number first |%+- 10g| and number second|%+- 10g|",
    "Number first |%-+ 015g| and number second|%-+ 015g|",
    "Number first |%#5g| and number second|%#15g|",
    "Number first |%-#5g| and number second|%-#5g|",
    "Number first |%+#15g| and number second|%+#15g|",
    "Number first |%-#015g| and number second|%-#015g|",
    "Number first |%+#015g| and number second|%+#015g|",
    "Number first |% #15g| and number second|% #15g|",
    "Number first |%# 015g| and number second|%# 015g|",
    "Number first |%+#- 15g| and number second|%+#- 15g|"};

START_TEST(gs_flag_width_template) {
  const char *str = gs_width_template_vals[_i];
  double number_1 = -21.42;
  double number_2 = 0.000506245656;

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str, number_1, number_2);
  int s21_res = s21_sprintf(dest_s21, str, number_1, number_2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  number_1 = 123456789012323;
  number_2 = 0;

  def_res = sprintf(dest_def, str, number_1, number_2);
  s21_res = s21_sprintf(dest_s21, str, number_1, number_2);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *gs_width_precision_template_vals[] = {
    "Number first |%10.10g| and number second|%10.10g|",
    "Number first |%+5.4g| and number second|%+5.4g|",
    "Number first |%+15.10g| and number second|%+15.10g|",
    "Number first |%+10.15g| and number second|%+10.15g|",
    "Number first |%-010.15g| and number second|%-010.15g|",
    "Number first |%+05.9g| and number second|%+05.1g|",
    "Number first |% 8.9g| and number second|% 9.8g|",
    "Number first |% 08.9g| and number second|% 09.8g|",
    "Number first |%+- 2.4g| and number second|%+- 2.4g|",
    "Number first |%+- 9.8g| and number second|%+- 8.9g|",
    "Number first |%-+ 08.9g| and number second|%-+ 09.6g|",
    "Number first |%-10.5g| and number second|%-5.10g|",
    "Number first |%.5g| and number second|% .16g|",
    "Number first |%.1g| and number second|%+.16g|",
    "Number first |%- .6g| and number second|%+ 0.5g|",
    "Number first |%10.0g| and number second|%#10.0g|",
    "Number first |%+5.4g| and number second|%+#5.0g|",
    "Number first |%+15.10g| and number second|%+#15.0g|",
    "Number first |%+10.15g| and number second|%+#10.0g|",
    "Number first |%-010.15g| and number second|%-#010.0g|",
    "Number first |%+05.9g| and number second|%+#05.0g|",
    "Number first |% 8.9g| and number second|% #9.0g|",
    "Number first |% 08.9g| and number second|% #09.0g|",
    "Number first |%+- 2.4g| and number second|%+- #2.0g|",
    "Number first |%+- 9.8g| and number second|%+- #8.0g|",
    "Number first |%-+ 08.9g| and number second|%-+ #09.0g|",
    "Number first |%-10.5g| and number second|%-#5.0g|",
    "Number first |%.5g| and number second|% #.0g|",
    "Number first |%.1g| and number second|%+#.0g|",
    "Number first |%- .6g| and number second|%+ #0.0g|",
    "Number first |%10.10g| and number second|%#10.10g|",
    "Number first |%+5.4g| and number second|%#+5.4g|",
    "Number first |%+15.10g| and number second|%#+15.10g|",
    "Number first |%+10.15g| and number second|%#+10.15g|",
    "Number first |%-010.15g| and number second|%#-010.15g|",
    "Number first |%+05.9g| and number second|%#+05.1g|",
    "Number first |% 8.9g| and number second|%# 9.8g|",
    "Number first |% 08.9g| and number second|%# 09.8g|",
    "Number first |%+- 2.4g| and number second|%#+- 2.4g|",
    "Number first |%+- 9.8g| and number second|%#+- 8.9g|",
    "Number first |%-+ 08.9g| and number second|%#-+ 09.6g|",
    "Number first |%-10.5g| and number second|%#-5.10g|"};

START_TEST(gs_flag_width_precision_template) {
  const char *str = gs_width_precision_template_vals[_i];
  double positive_number = 0.9999999565;
  double negative_number = -21.42;

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  int def_res = sprintf(dest_def, str, positive_number, negative_number);
  int s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  memset(dest_s21, '@', BIG_BUFF_SIZE);
  memset(dest_def, '@', BIG_BUFF_SIZE);

  positive_number = 123456789012323;
  negative_number = 0;

  def_res = sprintf(dest_def, str, positive_number, negative_number);
  s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *gs_width_star_template_vals[] = {
    "Number first |%-*g| and number second|%-*g|",
    "Number first |%+*g| and number second|%+*g|",
    "Number first |%-0*g| and number second|%-0*g|",
    "Number first |%+0*g| and number second|%+0*g|",
    "Number first |% *g| and number second|% *g|",
    "Number first |% 0*g| and number second|% #0*g|",
    "Number first |%+-*g| and number second|%+-# *g|",
    "Number first |%-+ 0*g| and number second|%-+# 0*g|",
    "Number first |%-#*g| and number second|%-#*g|",
    "Number first |%+#*g| and number second|%+#*g|",
    "Number first |%-#0*g| and number second|%#-0*g|",
    "Number first |%+#0*g| and number second|%+#0*g|",
    "Number first |% #*g| and number second|% #*g|",
};

START_TEST(gs_flag_width_star_template) {
  const char *str = gs_width_star_template_vals[_i];
  double positive_number = 0.9999999565;
  double negative_number = -21.42;
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

static const char *gs_width_precision_star_template_vals[] = {
    "Test |%-*.*g| string |%+0*.*g|",    "Test |%*.*g| string |%+*.*g|",
    "Test |%+- 0*.*g| string |%# *.*g|", "Test |%-#*.*g| string |%+#0*.*g|",
    "Test |%#*.*g| string |%+#*.*g|",    "Test |%+#- 0*.*g| string |%# *.*g|"};

START_TEST(gs_flag_width_prec_star_template) {
  const char *str = gs_width_precision_star_template_vals[_i];

  int first_amount = 5;
  int second_amount = 10;
  double positive_number = 0.9999999565;
  double negative_number = -21.42;

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

static const char *gs_lenght_template_vals[] = {
    "Test %Lf %f", "Test %.10Lf %.10f", "Test %-+ 02.2Lf %+07f",
    "Test %-+ 07.7Lf %+010.10f"};

START_TEST(gs_lenght_test) {
  const char *str = gs_lenght_template_vals[_i];
  long double positive_number = 0.9999999565;
  double negative_number = -21.42;

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

  positive_number = 123456789012323;
  negative_number = 0;

  def_res = sprintf(dest_def, str, positive_number, negative_number);
  s21_res = s21_sprintf(dest_s21, str, positive_number, negative_number);
  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

Suite *suite_s21_sprintf_gs() {
  Suite *suite = suite_create("suite_s21_sprintf_gs");

  TCase *gs_flag_case = tcase_create("s21_sprintf_gs_flag");
  tcase_add_loop_test(gs_flag_case, gs_flag, 0,
                      GET_SIZE_ARRAY(gs_flag_numbers));
  suite_add_tcase(suite, gs_flag_case);

  TCase *gs_flag_width_template_case =
      tcase_create("s21_sprint_gs_width_template");
  tcase_add_loop_test(gs_flag_width_template_case, gs_flag_width_template, 0,
                      GET_SIZE_ARRAY(gs_width_template_vals));
  suite_add_tcase(suite, gs_flag_width_template_case);

  TCase *gs_flag_width_prec_template_case =
      tcase_create("s21_sprint_gs_width_precision_template");
  tcase_add_loop_test(gs_flag_width_prec_template_case,
                      gs_flag_width_precision_template, 0,
                      GET_SIZE_ARRAY(gs_width_precision_template_vals));
  suite_add_tcase(suite, gs_flag_width_prec_template_case);

  TCase *gs_flag_width_star_template_case =
      tcase_create("s21_sprint_gs_width_star_template");
  tcase_add_loop_test(gs_flag_width_star_template_case,
                      gs_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(gs_width_star_template_vals));
  suite_add_tcase(suite, gs_flag_width_star_template_case);

  TCase *gs_flag_all_stars_template_case =
      tcase_create("s21_sprint_gs_all_stars_template");
  tcase_add_loop_test(gs_flag_all_stars_template_case,
                      gs_flag_width_prec_star_template, 0,
                      GET_SIZE_ARRAY(gs_width_precision_star_template_vals));
  suite_add_tcase(suite, gs_flag_all_stars_template_case);

  TCase *gs_lenght_test_case = tcase_create("s21_sprintf_gs_lenght");
  tcase_add_loop_test(gs_lenght_test_case, gs_lenght_test, 0,
                      GET_SIZE_ARRAY(gs_lenght_template_vals));
  suite_add_tcase(suite, gs_lenght_test_case);

  return suite;
}
