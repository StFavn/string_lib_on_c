#include "s21_string_test.h"

START_TEST(f_flag) {
  const char format[] = "Number first %f and number second %f";
  const double number_1 = -21.42;
  const double number_2 = 0.056245656;
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

  const char format2[] = "%f";
  s21_res = s21_sprintf(dest_s21, format2, number_1);
  def_res = sprintf(dest_def, format2, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *f_width_template_vals[] = {
    "Number first |%5f| and number second|%15f|",
    "Number first |%-5f| and number second|%-5f|",
    "Number first |%+15f| and number second|%+15f|",
    "Number first |%-015f| and number second|%-015f|",
    "Number first |%+015f| and number second|%+015f|",
    "Number first |% 15f| and number second|% 15f|",
    "Number first |% 015f| and number second|% 015f|",
    "Number first |%+- 15f| and number second|%+- 15f|",
    "Number first |%2f| and number second|%2f|",
    "Number first |%10f| and number second|%15f|",
    "Number first |%3f| and number second|%4f|",
    "Number first |%-+ 015f| and number second|%-+ 015f|",
    "Number first |%-10f| and number second|%-10f|",
    "Number first |%+15f| and number second|%+15f|",
    "Number first |%-010f| and number second|%-015f|",
    "Number first |%+010f| and number second|%+010f|",
    "Number first |% 15f| and number second|% 15f|",
    "Number first |% 010f| and number second|% 030f|",
    "Number first |%+- 10f| and number second|%+- 10f|",
    "Number first |%-+ 015f| and number second|%-+ 015f|",
    "Number first |%#5f| and number second|%#15f|",
    "Number first |%-#5f| and number second|%-#5f|",
    "Number first |%+#15f| and number second|%+#15f|",
    "Number first |%-#015f| and number second|%-#015f|",
    "Number first |%+#015f| and number second|%+#015f|",
    "Number first |% #15f| and number second|% #15f|",
    "Number first |%# 015f| and number second|%# 015f|",
    "Number first |%+#- 15f| and number second|%+#- 15f|",
};

START_TEST(f_flag_width_template) {
  const char *str = f_width_template_vals[_i];
  double number_1 = -21.42;
  double number_2 = 0.9999999565;

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

static const char *f_width_precision_template_vals[] = {
    "Number first |%10.10f| and number second|%10.10f|",
    "Number first |%+5.4f| and number second|%+5.4f|",
    "Number first |%+15.10f| and number second|%+15.10f|",
    "Number first |%+10.15f| and number second|%+10.15f|",
    "Number first |%-010.15f| and number second|%-010.15f|",
    "Number first |%+05.9f| and number second|%+05.1f|",
    "Number first |% 8.9f| and number second|% 9.8f|",
    "Number first |% 08.9f| and number second|% 09.8f|",
    "Number first |%+- 2.4f| and number second|%+- 2.4f|",
    "Number first |%+- 9.8f| and number second|%+- 8.9f|",
    "Number first |%-+ 08.9f| and number second|%-+ 09.6f|",
    "Number first |%-10.5f| and number second|%-5.10f|",
    "Number first |%.5f| and number second|% .16f|",
    "Number first |%.1f| and number second|%+.16f|",
    "Number first |%- .6f| and number second|%+ 0.5f|",
    "Number first |%10.0f| and number second|%#10.0f|",
    "Number first |%+5.4f| and number second|%+#5.0f|",
    "Number first |%+15.10f| and number second|%+#15.0f|",
    "Number first |%+10.15f| and number second|%+#10.0f|",
    "Number first |%-010.15f| and number second|%-#010.0f|",
    "Number first |%+05.9f| and number second|%+#05.0f|",
    "Number first |% 8.9f| and number second|% #9.0f|",
    "Number first |% 08.9f| and number second|% #09.0f|",
    "Number first |%+- 2.4f| and number second|%+- #2.0f|",
    "Number first |%+- 9.8f| and number second|%+- #8.0f|",
    "Number first |%-+ 08.9f| and number second|%-+ #09.0f|",
    "Number first |%-10.5f| and number second|%-#5.0f|",
    "Number first |%.5f| and number second|% #.0f|",
    "Number first |%.1f| and number second|%+#.0f|",
    "Number first |%- .6f| and number second|%+ #0.0f|",
    "Number first |%10.10f| and number second|%#10.10f|",
    "Number first |%+5.4f| and number second|%#+5.4f|",
    "Number first |%+15.10f| and number second|%#+15.10f|",
    "Number first |%+10.15f| and number second|%#+10.15f|",
    "Number first |%-010.15f| and number second|%#-010.15f|",
    "Number first |%+05.9f| and number second|%#+05.1f|",
    "Number first |% 8.9f| and number second|%# 9.8f|",
    "Number first |% 08.9f| and number second|%# 09.8f|",
    "Number first |%+- 2.4f| and number second|%#+- 2.4f|",
    "Number first |%+- 9.8f| and number second|%#+- 8.9f|",
    "Number first |%-+ 08.9f| and number second|%#-+ 09.6f|",
    "Number first |%-10.5f| and number second|%#-5.10f|"};

START_TEST(f_flag_width_precision_template) {
  const char *str = f_width_precision_template_vals[_i];
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

static const char *f_width_star_template_vals[] = {
    "Number first |%-*f| and number second|%-*f|",
    "Number first |%+*f| and number second|%+*f|",
    "Number first |%-0*f| and number second|%-0*f|",
    "Number first |%+0*f| and number second|%+0*f|",
    "Number first |% *f| and number second|% *f|",
    //"Number first |% 05d| and number second|% 0*d|",  undefined behavior case;
    "Number first |% 0*f| and number second|% #0*f|",
    "Number first |%+-*f| and number second|%+-# *f|",
    "Number first |%-+ 0*f| and numbersecond|%-+# 0*f|",
    "Number first |%-#*f| and number second|%-#*f|",
    "Number first |%+#*f| and number second|%+#*f|",
    "Number first |%-#0*f| and number second|%#-0*f|",
    "Number first |%+#0*f| and number second|%+#0*f|",
    "Number first |% #*f| and number second|% #*f|",

};

START_TEST(f_flag_width_star_template) {
  const char *str = f_width_star_template_vals[_i];
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

static const char *f_width_precision_star_template_vals[] = {
    "Test |%-*.*f| string |%+0*.*f|",     //
    "Test |%*.*f| string |%+*.*f|",       //
    "Test |%+- 0*.*f| string |%# *.*f|",  //
    "Test |%-#*.*f| string |%+#0*.*f|",   //
    "Test |%#*.*f| string |%+#*.*f|",     //
    "Test |%+#- 0*.*f| string |%# *.*f|"  //
};

START_TEST(f_flag_width_prec_star_template) {
  const char *str = f_width_precision_star_template_vals[_i];

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

static const char *f_lenght_template_vals[] = {
    "Test %Lf %f", "Test %.10Lf %.10f", "Test %-+ 02.2Lf %+07f",
    "Test %-+ 07.7Lf %+010.10f"};

START_TEST(f_lenght_test) {
  const char *str = f_lenght_template_vals[_i];
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

Suite *suite_s21_sprintf_f() {
  Suite *suite = suite_create("suite_s21_sprintf_f");

  TCase *f_flag_case = tcase_create("s21_sprintf_f_flag");
  tcase_add_test(f_flag_case, f_flag);
  suite_add_tcase(suite, f_flag_case);

  TCase *f_flag_width_template_case =
      tcase_create("s21_sprint_f_width_template");
  tcase_add_loop_test(f_flag_width_template_case, f_flag_width_template, 0,
                      GET_SIZE_ARRAY(f_width_template_vals));
  suite_add_tcase(suite, f_flag_width_template_case);

  TCase *f_flag_width_prec_template_case =
      tcase_create("s21_sprint_f_width_precision_template");
  tcase_add_loop_test(f_flag_width_prec_template_case,
                      f_flag_width_precision_template, 0,
                      GET_SIZE_ARRAY(f_width_precision_template_vals));
  suite_add_tcase(suite, f_flag_width_prec_template_case);

  TCase *f_flag_width_star_template_case =
      tcase_create("s21_sprint_f_width_star_template");
  tcase_add_loop_test(f_flag_width_star_template_case,
                      f_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(f_width_star_template_vals));
  suite_add_tcase(suite, f_flag_width_star_template_case);

  TCase *f_flag_all_stars_template_case =
      tcase_create("s21_sprint_f_all_stars_template");
  tcase_add_loop_test(f_flag_all_stars_template_case,
                      f_flag_width_prec_star_template, 0,
                      GET_SIZE_ARRAY(f_width_precision_star_template_vals));
  suite_add_tcase(suite, f_flag_all_stars_template_case);

  TCase *f_lenght_test_case = tcase_create("s21_sprintf_f_lenght");
  tcase_add_loop_test(f_lenght_test_case, f_lenght_test, 0,
                      GET_SIZE_ARRAY(f_lenght_template_vals));
  suite_add_tcase(suite, f_lenght_test_case);

  return suite;
}
