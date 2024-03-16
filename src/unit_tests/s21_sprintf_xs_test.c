#include "s21_string_test.h"

#define BUFFER 1024

START_TEST(xs_flag) {
  const char format[] = "Number first %x and number second %x";
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

  const char format2[] = "%x";
  s21_res = s21_sprintf(dest_s21, format2, number_1);
  def_res = sprintf(dest_def, format2, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  const char format3[] = "%#x";
  s21_res = s21_sprintf(dest_s21, format3, number_1);
  def_res = sprintf(dest_def, format3, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *xs_width_template_vals[] = {
    "Number first |%5x| and number second|%5x|",
    "Number first |%-5x| and number second|%-5x|",
    "Number first |%+5x| and number second|%+5x|",
    "Number first |%-05x| and number second|%-05x|",
    "Number first |%+05x| and number second|%+05x|",
    "Number first |% 5x| and number second|% 5x|",
    "Number first |% 05x| and number second|% 05x|",
    "Number first |%+- 5x| and number second|%+- 5x|",
    "Number first |%2x| and number second|%2x|",
    "Number first |%1x| and number second|%3x|",
    "Number first |%3x| and number second|%4x|",
    "Number first |%-+ 02x| and number second|%-+ 02x|",
    "Number first |%-1x| and number second|%-1x|",
    "Number first |%+2x| and number second|%+2x|",
    "Number first |%-01x| and number second|%-03x|",
    "Number first |%+01x| and number second|%+01x|",
    "Number first |% 2x| and number second|% 3x|",
    "Number first |% 01x| and number second|% 03x|",
    "Number first |%+- 1x| and number second|%+- 1x|",
    "Number first |%-+ 02x| and number second|%-+ 02x|",
    "Number first |%-+ 010x| and number second|%-+ 010x|",
    "Number first |%#5x| and number second|%#5x|",
    "Number first |%#-5x| and number second|%-#5x|",
    "Number first |%#+5x| and number second|%+#5x|",
    "Number first |%#-05x| and number second|%-#05x|",
    "Number first |%#+010x| and number second|%+#010x|",
    "Number first |%# 5x| and number second|%# 5x|",
    "Number first |%# 05x| and number second|%# 05x|",
    "Number first |%#+- 15x| and number second|%#+- 15x|",
    "Number first |%#+- 015x| and number second|%#+- 015x|"};

START_TEST(xs_flag_width_template) {
  const char *str = xs_width_template_vals[_i];
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

static const char *xs_width_precision_template_vals[] = {
    "Number first |%2.5x| and number second|%2.3x|",
    "Number first |%+5.4x| and number second|%+5.4x|",
    "Number first |%-05.2x| and number second|%-05.8x|",
    "Number first |%+05.9x| and number second|%+05.1x|",
    "Number first |% 5.4x| and number second|% 5.4x|",
    "Number first |% 05.4x| and number second|% 05.4x|",
    "Number first |%+- 2.4x| and number second|%+- 2.4x|",
    "Number first |%-+ 02.2x| and number second|%-+ 02.2x|",
    "Number first |%-2.5x| and number second|%-2.3x|",
    "Number first |%.5x| and number second|% .3x|",
    "Number first |%.1x| and number second|%+.5x|",
    "Number first |%- .6x| and number second|%+ 0.5x|",
    "Number first |%#2.5x| and number second|%#2.3x|",
    "Number first |%#+5.4x| and number second|%#+5.4x|",
    "Number first |%#-05.2x| and number second|%#-05.8x|",
    "Number first |%#+05.9x| and number second|%#+05.1x|",
    "Number first |%# 5.4x| and number second|%# 5.4x|",
    "Number first |%# 05.4x| and number second|%# 05.4x|",
    "Number first |%#+- 2.4x| and number second|%#+- 2.4x|",
    "Number first |%#-+ 02.2x| and number second|%#-+ 02.2x|",
    "Number first |%#-2.5x| and number second|%#-2.3x|",
    "Number first |%#.5x| and number second|%# .3x|",
    "Number first |%#.1x| and number second|%#+.5x|",
    "Number first |%#- .6x| and number second|%#+ 0.5x|",
    "Number first |%#10.5x| and number second|%#5.10x|",
    "Number first |%#+10.5x| and number second|%#+5.10x|",
    "Number first |%#-010.5x| and number second|%#-05.10x|",
    "Number first |%#+010.5x| and number second|%#+05.10x|",
    "Number first |%# 10.5x| and number second|%# 5.10x|",
    "Number first |%# 010.5x| and number second|%# 05.10x|",
    "Number first |%#+- 10.5x| and number second|%#+- 5.10x|",
    "Number first |%#-+ 010.5x| and number second|%#-+ 05.10x|",
    "Number first |%#-10.5x| and number second|%#-5.10x|",
    "Number first |%#.10x| and number second|%# .3x|",
    "Number first |%#.1x| and number second|%#+.5x|",
    "Number first |%#- .6x| and number second|%#+ 0.5x|",
};

START_TEST(xs_flag_width_precision_template) {
  const char *str = xs_width_precision_template_vals[_i];
  unsigned long long int number1 = 258;
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

static const char *xs_width_star_template_vals[] = {
    "Number first |%-*x| and number second|%-*x|",
    "Number first |%+*x| and number second|%+*x|",
    "Number first |%-0*x| and number second|%-0*x|",
    "Number first |%+0*x| and number second|%+0*x|",
    "Number first |% *x| and number second|% *x|",
    "Number first |% 0*x| and number second|% 0*x|",
    "Number first |%+- *x| and number second|%+- *x|",
    "Number first |%-+ 0*x| and number second|%-+ 0*x|"};

START_TEST(xs_flag_width_star_template) {
  const char *str = xs_width_star_template_vals[_i];
  unsigned int number1 = 1023;
  unsigned long long int number2 = ULLONG_MAX;
  int star_value = 8;

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

static const char *xs_width_precision_star_template_vals[] = {
    "Test |%-*.*x| string |%+0*.*x|", "Test |%*.*x| string |%+*.*x|",
    "Test |%+- 0*.*x| string |% *.*x|"};

START_TEST(xs_flag_width_prec_star_template) {
  const char *str = xs_width_precision_star_template_vals[_i];

  int first_amount = 5;
  int second_amount = 10;
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

static const char *xs_lenght_template_vals[] = {"Test %lx %lx", "Test %hx %hx",
                                                "Test %-+ 02.2hx %+03.5lx",
                                                "Test %-+ 02.2x %+03.5x"};

START_TEST(xs_lenght_test) {
  const char *str = xs_lenght_template_vals[_i];
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

Suite *suite_s21_sprintf_xs() {
  Suite *suite = suite_create("suite_s21_sprintf_xs");

  TCase *xs_flag_case = tcase_create("s21_sprintf_xs_flag");
  tcase_add_test(xs_flag_case, xs_flag);
  suite_add_tcase(suite, xs_flag_case);

  TCase *xs_flag_width_template_case =
      tcase_create("s21_sprint_xs_width_template");
  tcase_add_loop_test(xs_flag_width_template_case, xs_flag_width_template, 0,
                      GET_SIZE_ARRAY(xs_width_template_vals));
  suite_add_tcase(suite, xs_flag_width_template_case);

  TCase *xs_flag_width_prec_template_case =
      tcase_create("s21_sprint_xs_width_precision_template");
  tcase_add_loop_test(xs_flag_width_prec_template_case,
                      xs_flag_width_precision_template, 0,
                      GET_SIZE_ARRAY(xs_width_precision_template_vals));
  suite_add_tcase(suite, xs_flag_width_prec_template_case);

  TCase *xs_flag_width_star_template_case =
      tcase_create("s21_sprint_xs_width_star_template");
  tcase_add_loop_test(xs_flag_width_star_template_case,
                      xs_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(xs_width_star_template_vals));
  suite_add_tcase(suite, xs_flag_width_star_template_case);

  TCase *xs_flag_all_stars_template_case =
      tcase_create("s21_sprint_xs_all_stars_template");
  tcase_add_loop_test(xs_flag_all_stars_template_case,
                      xs_flag_width_prec_star_template, 0,
                      GET_SIZE_ARRAY(xs_width_precision_star_template_vals));
  suite_add_tcase(suite, xs_flag_all_stars_template_case);

  TCase *xs_lenght_test_case = tcase_create("s21_sprintf_xs_lenght");
  tcase_add_loop_test(xs_lenght_test_case, xs_lenght_test, 0,
                      GET_SIZE_ARRAY(xs_lenght_template_vals));
  suite_add_tcase(suite, xs_lenght_test_case);

  return suite;
}
