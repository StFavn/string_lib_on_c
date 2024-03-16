#include <stdio.h>

#include "s21_string_test.h"

#define actual(str1, str2, n) s21_strncmp(str1, str2, n)
#define expected(str1, str2, n) strncmp(str1, str2, n)

#define LEN_DELTA 30

/* NORMAL */

static const char *str1_global = "Simple test string 1235a356 tHe\ngood choice";
static const char *str2_global =
    "Simple tes\0T string 1235a356 tHe\ngood choice";

START_TEST(str_is_equal) {
  const char *str1 = str1_global;
  const char *str2 = str2_global;

  for (size_t n = 0; n <= strlen(str2) + LEN_DELTA; ++n) {
    ck_assert_int_eq(actual(str1, str2, n), expected(str1, str2, n));
  }
}
END_TEST

START_TEST(str_not_equal_01) {
  const char *str1 = str1_global;
  const char *str2 = "sIMPLE_TESt STRIN\0G 1235";

  for (size_t n = 0; n <= strlen(str2_global) + LEN_DELTA; ++n) {
    ck_assert_int_eq(actual(str1, str2, n) < 0, expected(str1, str2, n) < 0);
  }
}
END_TEST

START_TEST(str_not_equal_02) {
  const char *str1 = str1_global;
  const char *str2 = "After all";

  for (size_t n = 0; n <= strlen(str2_global) + LEN_DELTA; ++n) {
    ck_assert_int_eq(actual(str1, str2, n) > 0, expected(str1, str2, n) > 0);
  }
}
END_TEST

START_TEST(repeated_words) {
  char str1[] = "TEST TEST TEST TEST";
  char str2[BUFF_SIZE] = "TEST";
  size_t n = LEN_DELTA;

  ck_assert_int_eq(actual(str1, str2, n) > 0, expected(str1, str2, n) > 0);
}
END_TEST

static const char droids_str1[][BUFF_SIZE] = {
    "R2D2",  // 0
    "C3PO",  //
    "R2A6"   //
};

START_TEST(find_droid) {
  const char *str1 = droids_str1[_i];
  const char str2[BUFF_SIZE] = "R2**";
  const size_t n = LEN_DELTA;

  ck_assert_int_eq(actual(str1, str2, n) > 0, expected(str1, str2, n) > 0);
}
END_TEST

/* EDGE */

START_TEST(words_with_any_register) {
  char str1[] = "AbOBosNyTSa";
  char str2[BUFF_SIZE] = "aBoboSNYTsa";
  const size_t n = LEN_DELTA;

  ck_assert_int_eq(actual(str1, str2, n) < 0, expected(str1, str2, n) < 0);
}
END_TEST

/* ANOMALY */

// These tests raise Segmentation fault in standart strncmp
// START_TEST(one_of_str_is_null) {
//   const char *str1 = NULL;
//   const char *str2 = "12345";

//  ck_assert_int_eq(actual(str1, str2, LEN_DELTA), expected(str1, str2,
//  LEN_DELTA));

// }
// END_TEST

// START_TEST(all_str_is_null) {
//   const char *str1 = NULL;
//   const char *str2 = NULL;

//   ck_assert_int_eq(actual(str1, str2, LEN_DELTA), expected(str1, str2,
//   LEN_DELTA));

// }
// END_TEST

START_TEST(empty_str2) {
  char str1[] = "asdgadrfhdfASFSDGNLgfnsfdlgn42143ln4g34h";
  char str2[BUFF_SIZE] = "";
  const size_t n = LEN_DELTA;

  ck_assert_int_eq(actual(str1, str2, n) > 0, expected(str1, str2, n) > 0);
}
END_TEST

START_TEST(empty_str1) {
  char str1[] = "";
  char str2[BUFF_SIZE] = "asdgadrfhdfASFSDGNLgfnsfdlgn42143ln4g34h";
  const size_t n = LEN_DELTA;

  ck_assert_int_eq(actual(str1, str2, n) < 0, expected(str1, str2, n) < 0);
}
END_TEST

START_TEST(empty_all_str) {
  char str1[] = "";
  char str2[BUFF_SIZE] = "";
  const size_t n = LEN_DELTA;

  ck_assert_int_eq(actual(str1, str2, n), expected(str1, str2, n));
}
END_TEST

/* SUITE */

static const size_t droids_elems = GET_SIZE_ARRAY(droids_str1);

Suite *suite_s21_strncmp() {
  Suite *suite = suite_create("suite_s21_strncmp");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, str_is_equal);
  tcase_add_test(normal_cases, str_not_equal_01);
  tcase_add_test(normal_cases, str_not_equal_02);
  tcase_add_test(normal_cases, repeated_words);
  tcase_add_loop_test(normal_cases, find_droid, 0, droids_elems);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, words_with_any_register);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  // tcase_add_test(anomaly_cases, one_of_str_is_null);
  // tcase_add_test(anomaly_cases, all_str_is_null);
  tcase_add_test(anomaly_cases, empty_str2);
  tcase_add_test(anomaly_cases, empty_str1);
  tcase_add_test(anomaly_cases, empty_all_str);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}