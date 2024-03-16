#include "s21_string_test.h"

#define BUFFER 1024

START_TEST(xl_flag) {
  const char format[] = "Number first %X and number second %X";
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

  const char format2[] = "%X";
  s21_res = s21_sprintf(dest_s21, format2, number_1);
  def_res = sprintf(dest_def, format2, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);

  const char format3[] = "%#X";
  s21_res = s21_sprintf(dest_s21, format3, number_1);
  def_res = sprintf(dest_def, format3, number_1);

  ck_assert_str_eq(dest_s21, dest_def);
  ck_assert_int_eq(s21_res, def_res);
}
END_TEST

static const char *xl_width_template_vals[] = {
    "Number first |%5X| and number second|%5X",
    "Number first |%-5X| and number second|%-5X",
    "Number first |%+5X| and number second|%+5X",
    "Number first |%-05X| and number second|%-05X",
    "Number first |%+05X| and number second|%+05X",
    "Number first |% 5X| and number second|% 5X",
    "Number first |% 05X| and number second|% 05X",
    "Number first |%+- 5X| and number second|%+- 5X",
    "Number first |%2X| and number second|%2X",
    "Number first |%1X| and number second|%3X",
    "Number first |%3X| and number second|%4X",
    "Number first |%-+ 02X| and number second|%-+ 02X",
    "Number first |%-1X| and number second|%-1X",
    "Number first |%+2X| and number second|%+2X",
    "Number first |%-01X| and number second|%-03X",
    "Number first |%+01X| and number second|%+01X",
    "Number first |% 2X| and number second|% 3X",
    "Number first |% 01X| and number second|% 03X",
    "Number first |%+- 1X| and number second|%+- 1X",
    "Number first |%-+ 02X| and number second|%-+ 02X",
    "Number first |%-+ 010X| and number second|%-+ 010X",
    "Number first |%#5X| and number second|%#5X",
    "Number first |%#-5X| and number second|%-#5X",
    "Number first |%#+5X| and number second|%+#5x",
    "Number first |%#-05X| and number second|%-#05X",
    "Number first |%#+010X| and number second|%+#010X",
    "Number first |%# 5X| and number second|%# 5X",
    "Number first |%# 05X| and number second|%# 05X",
    "Number first |%#+- 15X| and number second|%#+- 15X",
    "Number first |%#+- 015X| and number second|%#+- 015X"};

START_TEST(xl_flag_width_template) {
  const char *str = xl_width_template_vals[_i];
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

static const char *xl_width_precision_template_vals[] = {
    "Number first |%2.5X| and number second|%2.3X|",
    "Number first |%+5.4X| and number second|%+5.4X|",
    "Number first |%-05.2X| and number second|%-05.8X|",
    "Number first |%+05.9X| and number second|%+05.1X|",
    "Number first |% 5.4X| and number second|% 5.4X|",
    "Number first |% 05.4X| and number second|% 05.4X|",
    "Number first |%+- 2.4X| and number second|%+- 2.4X|",
    "Number first |%-+ 02.2X| and number second|%-+ 02.2X|",
    "Number first |%-2.5X| and number second|%-2.3X|",
    "Number first |%.5X| and number second|% .3X|",
    "Number first |%.1X| and number second|%+.5X|",
    "Number first |%- .6X| and number second|%+ 0.5X|",
    "Number first |%#2.5X| and number second|%#2.3X|",
    "Number first |%#+5.4X| and number second|%#+5.4X|",
    "Number first |%#-05.2X| and number second|%#-05.8X|",
    "Number first |%#+05.9X| and number second|%#+05.1X|",
    "Number first |%# 5.4X| and number second|%# 5.4X|",
    "Number first |%# 05.4X| and number second|%# 05.4X|",
    "Number first |%#+- 2.4X| and number second|%#+- 2.4X|",
    "Number first |%#-+ 02.2X| and number second|%#-+ 02.2X|",
    "Number first |%#-2.5X| and number second|%#-2.3X|",
    "Number first |%#.5X| and number second|%# .3X|",
    "Number first |%#.1X| and number second|%#+.5X|",
    "Number first |%#- .6X| and number second|%#+ 0.5X|",
    "Number first |%#10.5X| and number second|%#5.10X|",
    "Number first |%#+10.5X| and number second|%#+5.10X|",
    "Number first |%#-010.5X| and number second|%#-05.10X|",
    "Number first |%#+010.5X| and number second|%#+05.10X|",
    "Number first |%# 10.5X| and number second|%# 5.10X|",
    "Number first |%# 010.5X| and number second|%# 05.10X|",
    "Number first |%#+- 10.5X| and number second|%#+- 5.10X|",
    "Number first |%#-+ 010.5X| and number second|%#-+ 05.10X|",
    "Number first |%#-10.5X| and number second|%#-5.10X",
    "Number first |%#.10X| and number second|%# .3X|",
    "Number first |%#.1X| and number second|%#+.5X|",
    "Number first |%#- .6X| and number second|%#+ 0.5X|",
};

START_TEST(xl_flag_width_precision_template) {
  const char *str = xl_width_precision_template_vals[_i];
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

static const char *xl_width_star_template_vals[] = {
    "Number first |%-*X| and number second|%-*X|",
    "Number first |%+*X| and number second|%+*X|",
    "Number first |%-0*X| and number second|%-0*X|",
    "Number first |%+0*X| and number second|%+0*X|",
    "Number first |% *X| and number second|% *X|",
    "Number first |% 0*X| and number second|% 0*X|",
    "Number first |%+- *X| and number second|%+- *X|",
    "Number first |%-+ 0*X| and number second|%-+ 0*X|",
    "Number first |%#-*X| and number second|%#-*X|",
    "Number first |%+#*X| and number second|%+#*X|",
    "Number first |%-#0*X| and number second|%#-0*X|",
    "Number first |%#+0*X| and number second|%+#0*X|",
    "Number first |%# *X| and number second|%# *X|",
    "Number first |%# 0*X| and number second|%# 0*X|",
    "Number first |%#+- *X| and number second|%+-# *X|",
    "Number first |%-#+ 0*X| and number second|%-#+ 0*X|"};

START_TEST(xl_flag_width_star_template) {
  const char *str = xl_width_star_template_vals[_i];
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

static const char *xl_width_precision_star_template_vals[] = {
    "Test |%-*.*X| string |%+0*.*X|",   "Test |%*.*X| string |%+*.*X|",
    "Test |%+- 0*.*X| string |% *.*X|", "Test |%#-*.*X| string |%+0#*.*X|",
    "Test |%#*.*X| string |%+#*.*X|",   "Test |%+-# 0*.*X| string |%# *.*X|"};

START_TEST(xl_flag_width_prec_star_template) {
  const char *str = xl_width_precision_star_template_vals[_i];

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

static const char *xl_lenght_template_vals[] = {
    "Test %lX %lX", "Test %hX %hX", "Test %-+ 02.2hX %+03.5lX",
    "Test %-+ 02.2X %+03.5X", "Test %-#+ 05.10hX %+#010.5lX"};

START_TEST(xl_lenght_test) {
  const char *str = xl_lenght_template_vals[_i];
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

Suite *suite_s21_sprintf_xl() {
  Suite *suite = suite_create("suite_s21_sprintf_xl");

  TCase *xl_flag_case = tcase_create("s21_sprintf_xl_flag");
  tcase_add_test(xl_flag_case, xl_flag);
  suite_add_tcase(suite, xl_flag_case);

  TCase *xl_flag_width_template_case =
      tcase_create("s21_sprint_xl_width_template");
  tcase_add_loop_test(xl_flag_width_template_case, xl_flag_width_template, 0,
                      GET_SIZE_ARRAY(xl_width_template_vals));
  suite_add_tcase(suite, xl_flag_width_template_case);

  TCase *xl_flag_width_prec_template_case =
      tcase_create("s21_sprint_xl_width_precision_template");
  tcase_add_loop_test(xl_flag_width_prec_template_case,
                      xl_flag_width_precision_template, 0,
                      GET_SIZE_ARRAY(xl_width_precision_template_vals));
  suite_add_tcase(suite, xl_flag_width_prec_template_case);

  TCase *xl_flag_width_star_template_case =
      tcase_create("s21_sprint_xl_width_star_template");
  tcase_add_loop_test(xl_flag_width_star_template_case,
                      xl_flag_width_star_template, 0,
                      GET_SIZE_ARRAY(xl_width_star_template_vals));
  suite_add_tcase(suite, xl_flag_width_star_template_case);

  TCase *xl_flag_all_stars_template_case =
      tcase_create("s21_sprint_xl_all_stars_template");
  tcase_add_loop_test(xl_flag_all_stars_template_case,
                      xl_flag_width_prec_star_template, 0,
                      GET_SIZE_ARRAY(xl_width_precision_star_template_vals));
  suite_add_tcase(suite, xl_flag_all_stars_template_case);

  TCase *xl_lenght_test_case = tcase_create("s21_sprintf_xl_lenght");
  tcase_add_loop_test(xl_lenght_test_case, xl_lenght_test, 0,
                      GET_SIZE_ARRAY(xl_lenght_template_vals));
  suite_add_tcase(suite, xl_lenght_test_case);

  return suite;
}
