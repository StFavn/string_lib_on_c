#include "s21_string_test.h"

#define actual(str1, str2, n) s21_memcmp(str1, str2, n)
#define expected(str1, str2, n) memcmp(str1, str2, n)

/* NORMAL */

static const char *normal_vals_str1[] = {
    "hello",        // 0
    "world",        //
    "hello world",  //
    "123456",       //
    "abcde\0fseew"  //
};

START_TEST(normal_compare_same) {
  const char *str1 = normal_vals_str1[_i];
  const char *str2 = normal_vals_str1[_i];
  const size_t n = strlen(str1) + 1;

  ck_assert_int_eq(actual(str1, str2, n), expected(str1, str2, n));
}
END_TEST

static const char *normal_vals_str2[] = {
    "hell1",          // 0
    "worldess",       //
    "\0hello world",  //
    "a123456",        //
    "aBcde\0fseew"    //
};

START_TEST(normal_compare_notsame) {
  const char *str1 = normal_vals_str1[_i];
  const char *str2 = normal_vals_str2[_i];
  const size_t n = strlen(str1) + 1;

  int actual_res = actual(str1, str2, n);
  int expecpected_res = expected(str1, str2, n);

  if (expecpected_res > 0) {
    ck_assert(actual_res > 0);
  } else if (expecpected_res < 0) {
    ck_assert(actual_res < 0);
  }
}
END_TEST

START_TEST(normal_compare_notchar) {
  int str1[BUFF_SIZE] = {0};
  int str2[BUFF_SIZE] = {0};
  const size_t n = BUFF_SIZE * sizeof(int);

  // First arrray fill increment values
  for (int i = 0; i < BUFF_SIZE; ++i) str1[i] = i;

  // Second array fill 0xFF value (all bites is 1)
  memset(str2, 0xFF, BUFF_SIZE * sizeof(int));

  ck_assert_int_eq(actual(str1, str2, n), expected(str1, str2, n));
}
END_TEST

/* EDGE */

START_TEST(edge_float_val) {
  double d_x = FLT_MAX;
  long double ld_x = DBL_MAX;
  const size_t n = sizeof(d_x);

  int actual_res = actual(&d_x, &ld_x, n);
  int expecpected_res = expected(&d_x, &ld_x, n);

  if (expecpected_res > 0) {
    ck_assert(actual_res > 0);
  } else if (expecpected_res < 0) {
    ck_assert(actual_res < 0);
  }
}
END_TEST

/* ANOMALY */

START_TEST(anomaly_zero_n) {
  char str1[] = "hello";
  char str2[] = "hello";
  const size_t n = 0;

  ck_assert_int_eq(actual(str1, str2, n), expected(str1, str2, n));
}
END_TEST

/* SUITE */

static const size_t normal_elems = GET_SIZE_ARRAY(normal_vals_str1);

Suite *suite_s21_memcmp() {
  Suite *suite = suite_create("suite_s21_memcmp");

  TCase *normal_case = tcase_create("normal_case");
  tcase_add_loop_test(normal_case, normal_compare_same, 0, normal_elems);
  tcase_add_loop_test(normal_case, normal_compare_notsame, 0, normal_elems);
  tcase_add_loop_test(normal_case, normal_compare_notchar, 0, normal_elems);
  suite_add_tcase(suite, normal_case);

  TCase *edge_case = tcase_create("edge_case");
  tcase_add_test(edge_case, edge_float_val);
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("anomaly_case");
  tcase_add_test(anomaly_case, anomaly_zero_n);
  suite_add_tcase(suite, anomaly_case);

  return suite;
}