#include "s21_string_test.h"

#define actual(str) s21_strlen(str)
#define expected(str) strlen(str)

/* NORMAL */

static const char *normal_vals[] = {
    "hello",        // 0
    "world",        //
    "hello world",  //
    "123456",       //
    "abcde\nfseew"  //
};

START_TEST(test_normal) {
  const char *str = normal_vals[_i];

  ck_assert_uint_eq(actual(str), expected(str));
}
END_TEST

/* EDGE */

static const char *edge_vals[] = {
    "",           // 0
    "    ",       //
    "\n\n\t\t",   //
    "\\\\",       //
    "\01\02\025"  //
};

START_TEST(test_edge) {
  const char *str = edge_vals[_i];

  ck_assert_uint_eq(actual(str), expected(str));
}
END_TEST

/* ANOMALY */

// `NULL` val is not supported strlen() from std (seg fault).
static const char *anomaly_vals[] = {
    "\0 1234",      // 0
    "привет мир!",  //
    "\00",          //
    "目标应该"      //
};

START_TEST(test_anomaly) {
  const char *str = anomaly_vals[_i];

  ck_assert_uint_eq(actual(str), expected(str));
}
END_TEST

/* SUITE */

static const size_t normal_vals_count = GET_SIZE_ARRAY(normal_vals);
static const size_t edge_vals_count = GET_SIZE_ARRAY(edge_vals);
static const size_t anomaly_vals_count = GET_SIZE_ARRAY(anomaly_vals);

Suite *suite_s21_strlen() {
  Suite *suite = suite_create("suite_s21_strlen");

  TCase *normal_case = tcase_create("normal_case");
  tcase_add_loop_test(normal_case, test_normal, 0, normal_vals_count);
  suite_add_tcase(suite, normal_case);

  TCase *edge_case = tcase_create("edge_case");
  tcase_add_loop_test(edge_case, test_edge, 0, edge_vals_count);
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("anomaly_case");
  tcase_add_loop_test(anomaly_case, test_anomaly, 0, anomaly_vals_count);
  suite_add_tcase(suite, anomaly_case);

  return suite;
}