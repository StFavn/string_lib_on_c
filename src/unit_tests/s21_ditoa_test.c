#include "s21_string_test.h"

static double frac_global[] = {
    0.123,   0.000010,
    0,       0.555551,
    0.02105, 0.01232356565323265656562323265656232326565625326565652323655};

START_TEST(frac_case) {
  const double x = frac_global[_i];
  bool need_int_round = false;
  const int prec_max = 19;  // 20 приводит к ошибке

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  // Провека с prec == 0 не имеет смысла
  for (int prec = 1; prec <= prec_max; ++prec) {
    if (prec != 0) {
      dest_s21[0] = '0';
      dest_s21[1] = '.';
    }
    char *buff = s21_fraction_to_char(x, prec, &need_int_round);
    sprintf(dest_def, "%.*f", prec, x);
    strcat(dest_s21, buff);
    free(buff);

    ck_assert_str_eq(dest_s21, dest_def);
    memset(dest_s21, 0, BIG_BUFF_SIZE);
    memset(dest_def, 0, BIG_BUFF_SIZE);
  }
}
END_TEST

static long double numbers_global[] = {
    -12345970556556.21, 0, 0.00001235, 123.56, -9.99999999, 8.595959595959595};

START_TEST(base_test) {
  const long double x = numbers_global[_i];
  const int prec_max = 18;  // 19 и больше - ошибка

  char dest_s21[BIG_BUFF_SIZE] = {0};
  char dest_def[BIG_BUFF_SIZE] = {0};

  for (int prec = 0; prec <= prec_max; ++prec) {
    sprintf(dest_def, "%.*Lf", prec, x);

    char *buff = s21_ditoa(x, prec);
    strcat(dest_s21, buff);
    free(buff);

    ck_assert_str_eq(dest_s21, dest_def);
    memset(dest_s21, 0, BIG_BUFF_SIZE);
    memset(dest_def, 0, BIG_BUFF_SIZE);
  }
}
END_TEST

Suite *suite_s21_ditoa() {
  Suite *suite = suite_create("suite_s21_ditoa");

  TCase *fractional_case = tcase_create("s21_fraction_to_char");
  tcase_add_loop_test(fractional_case, frac_case, 0,
                      sizeof(frac_global) / sizeof(frac_global[0]));
  suite_add_tcase(suite, fractional_case);

  TCase *base_case = tcase_create("s21_double_to_char");
  tcase_add_loop_test(base_case, base_test, 0,
                      sizeof(numbers_global) / sizeof(numbers_global[0]));
  suite_add_tcase(suite, base_case);

  return suite;
}