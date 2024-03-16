#include "s21_string_test.h"

#define actual(str, c, n) s21_memchr(str, c, n)
#define expected(str, c, n) memchr(str, c, n)

/* NORMAL */

static const char *normal_vals[] = {
    "aloha!",       // 0
    "world",        //
    "hello world",  //
    "123456",       //
    "bcde\0flseew"  // 4
};

START_TEST(test_normal) {
  const char *str = normal_vals[_i];
  const int c = 'l';
  const size_t n = strlen(str);

  ck_assert_pstr_eq(actual(str, c, n), expected(str, c, n));
}
END_TEST

START_TEST(test_normal_not_find) {
  const char *str = normal_vals[_i];
  const int c = 'z';
  const size_t n = strlen(str);

  ck_assert_ptr_null(actual(str, c, n));
}
END_TEST

/* ANOMALY */

START_TEST(test_anomaly_zero_n) {
  const char *str = normal_vals[_i];
  const int c = 'l';
  const size_t n = 0;

  ck_assert_ptr_null(actual(str, c, n));
}
END_TEST

/* SUITE */

static const size_t normal_elems = GET_SIZE_ARRAY(normal_vals);

Suite *suite_s21_memchr() {
  Suite *suite = suite_create("suite_s21_memchr");

  TCase *normal_case = tcase_create("normal_case");
  tcase_add_loop_test(normal_case, test_normal, 0, normal_elems);
  tcase_add_loop_test(normal_case, test_normal_not_find, 0, normal_elems);
  suite_add_tcase(suite, normal_case);

  TCase *anomaly_case = tcase_create("anomaly_case");
  tcase_add_test(anomaly_case, test_anomaly_zero_n);
  suite_add_tcase(suite, anomaly_case);

  return suite;
}