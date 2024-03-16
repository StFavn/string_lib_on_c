#include "s21_string_test.h"

#define actual(str1, str2) s21_strpbrk(str1, str2)
#define expected(str1, str2) strpbrk(str1, str2)

/* NORMAL */

static const char *str1_global = "Simple test string 1235a356 tHe\ngood choice";
static const char *str2_vals[] = {
    "1234567890",                 // 0
    "abcdefghikklmnoprstuvwxyz",  //
    " ",                          //
    "\n\t",                       //
    "ABCDEFGH"                    //
};

START_TEST(found) {
  const char *str1 = str1_global;
  const char *str2 = str2_vals[_i];

  ck_assert_str_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

static const char *str2_vals_fail[] = {"XYZ", "7890", "\t"};

START_TEST(not_found) {
  const char *str1 = str1_global;
  const char *str2 = str2_vals_fail[_i];

  ck_assert_pstr_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

START_TEST(repeated_words) {
  char str1[] = "TEST TEST TEST TEST";
  char str2[] = "TEST";

  ck_assert_pstr_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

/* EDGE */

START_TEST(words_with_any_register) {
  char str1[] = "AbOBosNyTSa";
  char str2[] = "aBoboSNYTsa";

  ck_assert_pstr_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

/* ANOMALY */

// These tests raise Segmentation fault in standart strpbrk()
// START_TEST(one_of_str_is_null) {
//   const char *str1 = NULL;
//   const char *str2 = "12345";

//   ck_assert_pstr_eq(actual(str1, str2),
//                     expected(str1, str2));
//   ck_assert_pstr_eq(actual(str2, str1),
//                     expected(str2, str1));
// }
// END_TEST

// START_TEST(all_str_is_null) {
//   const char *str1 = NULL;
//   const char *str2 = NULL;

//   ck_assert_pstr_eq(actual(str1, str2),
//                     expected(str1, str2));
// }
// END_TEST

START_TEST(empty_str2) {
  char str1[] = "asdgadrfhdfASFSDGNLgfnsfdlgn42143ln4g34h";
  char str2[] = "";

  ck_assert_pstr_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

START_TEST(empty_str1) {
  char str1[] = "";
  char str2[] = "asdgadrfhdfASFSDGNLgfnsfdlgn42143ln4g34h";

  ck_assert_pstr_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

START_TEST(empty_all_str) {
  char str1[] = "";
  char str2[] = "";

  ck_assert_pstr_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

/* SUITE */

static const size_t str2_vals_elems = GET_SIZE_ARRAY(str2_vals);
static const size_t str2_vals_fail_elems = GET_SIZE_ARRAY(str2_vals_fail);

Suite *suite_s21_strpbrk() {
  Suite *suite = suite_create("suite_s21_strpbrk");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_loop_test(normal_cases, found, 0, str2_vals_elems);
  tcase_add_loop_test(normal_cases, not_found, 0, str2_vals_fail_elems);
  tcase_add_test(normal_cases, repeated_words);
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