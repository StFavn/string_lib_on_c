#include "s21_string_test.h"

#define actual(str1) s21_atoi(str1)
#define expected(str1) atoi(str1)

/* NORMAL */

#define STR1_GLOBAL_LEN 8
static const char *str1_global[] = {"123", "0010", "0532", "0",
                                    "000", "1000", "-25",  "-005"};

START_TEST(normal_case) {
  const char *str1 = str1_global[_i];
  ck_assert_int_eq(actual(str1), expected(str1));
}
END_TEST

// Пока не вижу необходимости в обработке таких сценариев
// static const char *anomaly_global[] = {"25.23", "-01.23", "-23.22"};

/* ANOMALY */
// START_TEST(anomaly_case) {
//   const char *str1 = anomaly_global[_i];
//   ck_assert_int_eq(actual(str1), expected(str1));
// }
// END_TEST

Suite *suite_s21_atoi() {
  Suite *suite = suite_create("suite_s21_atoi");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_loop_test(normal_cases, normal_case, 0, STR1_GLOBAL_LEN);
  suite_add_tcase(suite, normal_cases);

  // TCase *anomaly_cases = tcase_create("anomaly_cases");
  // tcase_add_loop_test(anomaly_cases, anomaly_case, 0, 3);
  // suite_add_tcase(suite, anomaly_cases);

  return suite;
}