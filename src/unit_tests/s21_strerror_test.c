#include "../s21_strerror.h"

#include "s21_string_test.h"

#define actual(err) s21_strerror(err)
#define expected(err) strerror(err)

/* NORMAL */

START_TEST(normal_errors) {
  for (int errn = 0; errn < S21_ERRLIST_SIZE; errn++) {
    ck_assert_str_eq(actual(errn), expected(errn));
  }
}
END_TEST

/* ANOMALY */

START_TEST(unknown_errors_minus) {
  for (int errn = -255; errn < 0; errn++) {
    ck_assert_str_eq(actual(errn), expected(errn));
  }
}
END_TEST

START_TEST(unknown_errors_plus) {
  for (int errn = S21_ERRLIST_SIZE; errn < 255; errn++) {
    ck_assert_str_eq(actual(errn), expected(errn));
  }
}
END_TEST

Suite *suite_s21_strerror() {
  Suite *suite = suite_create("suite_s21_strerror");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, normal_errors);
  suite_add_tcase(suite, normal_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, unknown_errors_minus);
  tcase_add_test(anomaly_cases, unknown_errors_plus);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}