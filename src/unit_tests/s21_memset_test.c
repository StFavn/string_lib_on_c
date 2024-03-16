#include "s21_string_test.h"

#define actual(str, val, n) s21_memset(str, val, n)
#define expected(str, val, n) memset(str, val, n)

/* NORMAL */

static const char normal_vals[] = {
    'a',   // 0
    'b',   //
    'c',   //
    '\n',  //
    '\0',  //
    123,   // 5
    77,    //
    88     //
};

START_TEST(normal_empty_str) {
  char str_actual[BUFF_SIZE] = {0};
  char str_expected[BUFF_SIZE] = {0};
  const char val = normal_vals[_i];
  const size_t n = BUFF_SIZE;

  ck_assert_mem_eq(actual(str_actual, val, n), expected(str_expected, val, n),
                   BUFF_SIZE);
}
END_TEST

START_TEST(normal_first_bytes) {
  char arr_actual[BUFF_SIZE] =
      "1234567890abcderetwtwetewfgwgwegwegwegwefgbfsdb";
  char arr_expected[BUFF_SIZE] =
      "1234567890abcderetwtwetewfgwgwegwegwegwefgbfsdb";
  const char val = 'X';
  const size_t n_byte = 10;

  ck_assert_mem_eq(actual(arr_actual, val, n_byte),
                   expected(arr_expected, val, n_byte), BUFF_SIZE);
}
END_TEST

START_TEST(normal_two_step) {
  char arr_actual[BUFF_SIZE] = {0};
  char arr_expected[BUFF_SIZE] = {0};
  void *ptr_actual = arr_actual;
  void *ptr_expected = arr_expected;

  const char val = normal_vals[_i];

  const size_t half_size = BUFF_SIZE / 2;
  const size_t n = half_size;

  ck_assert_mem_eq(actual(ptr_actual, val, n), expected(ptr_expected, val, n),
                   half_size);
  ck_assert_mem_eq(arr_actual, arr_expected, BUFF_SIZE);

  ptr_actual += half_size;
  ptr_expected += half_size;

  ck_assert_mem_eq(actual(ptr_actual, val, n), expected(ptr_expected, val, n),
                   half_size);
  ck_assert_mem_eq(arr_actual, arr_expected, BUFF_SIZE);
}
END_TEST

/* ANOMALY */

static const int anomaly_vals[] = {
    256,        // 0
    258,        //
    123456789,  //
    -532,       //
    255,        //
    0xAA,       // 5
    -1,         //
    -2,         //
    -123        //
};

START_TEST(anomaly_empty_str) {
  char arr_actual[BUFF_SIZE] = {0};
  char arr_expected[BUFF_SIZE] = {0};
  const int val = anomaly_vals[_i];
  const size_t n = BUFF_SIZE;

  ck_assert_mem_eq(actual(arr_actual, val, n), expected(arr_expected, val, n),
                   BUFF_SIZE);
}
END_TEST

START_TEST(anomaly_zero_n) {
  char arr_actual[BUFF_SIZE] = {0};
  char arr_expected[BUFF_SIZE] = {0};
  const int val = 'w';
  const size_t n = 0;

  ck_assert_mem_eq(actual(arr_actual, val, n), expected(arr_expected, val, n),
                   BUFF_SIZE);
}
END_TEST

/* SUITE */

static const size_t normal_vals_elems = GET_SIZE_ARRAY(normal_vals);
static const size_t anomaly_vals_elems = GET_SIZE_ARRAY(anomaly_vals);

Suite *suite_s21_memset() {
  Suite *suite = suite_create("suite_s21_memset");

  TCase *normal_case = tcase_create("normal_case");
  tcase_add_loop_test(normal_case, normal_empty_str, 0, normal_vals_elems);
  tcase_add_test(normal_case, normal_first_bytes);
  tcase_add_loop_test(normal_case, normal_two_step, 0, normal_vals_elems);
  suite_add_tcase(suite, normal_case);

  TCase *anomaly_case = tcase_create("anomaly_case");
  tcase_add_test(anomaly_case, anomaly_empty_str);
  tcase_add_loop_test(anomaly_case, anomaly_zero_n, 0, anomaly_vals_elems);
  suite_add_tcase(suite, anomaly_case);

  return suite;
}