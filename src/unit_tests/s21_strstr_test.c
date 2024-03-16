#include "s21_string_test.h"

#define actual(haystack, needle) s21_strstr(haystack, needle)
#define expected(haystack, needle) strstr(haystack, needle)

/* NORMAL */

static const char *haystack_global =
    "Simple test string 1235a356 the\ngood choice";

static const char *needle_vals[] = {
    "g 123",   // 0
    "the",     //
    " ",       //
    "5a3",     //
    "good",    //
    "ice",     // 5
    "",        //
    "\n",      //
    "Simple",  //
    "string"   //
};

START_TEST(found) {
  const char *haystack = haystack_global;
  const char *needle = needle_vals[_i];

  ck_assert_str_eq(actual(haystack, needle), expected(haystack, needle));
}
END_TEST

static const char *needle_vals_fail[] = {
    "nothing",  // 0
    "thet",     //
    "\t",       //
    "5a33",     //
    "bad",      //
    "hooc",     // 5
    "SIMPLE",   //
    "TeSt"      //
};

START_TEST(not_found) {
  const char *haystack = haystack_global;
  const char *needle = needle_vals_fail[_i];

  ck_assert_pstr_eq(actual(haystack, needle), expected(haystack, needle));
}
END_TEST

START_TEST(repeated_words) {
  char haystack[] = "TEST TEST TEST TEST";
  char needle[] = "TEST";

  ck_assert_pstr_eq(actual(haystack, needle), expected(haystack, needle));
}
END_TEST

/* EDGE */

START_TEST(words_with_any_register) {
  char haystack[] = "AbOBosNyTSa";
  char needle[] = "aBoboSNYTsa";

  ck_assert_pstr_eq(actual(haystack, needle), expected(haystack, needle));
}
END_TEST

/* ANOMALY */

START_TEST(needle_len_is_bigger) {
  const char *needle = "123456789";
  const char *haystack = "12345";

  ck_assert_pstr_eq(actual(haystack, needle), expected(haystack, needle));
}
END_TEST

START_TEST(empty_needle) {
  char haystack[] = "asdgadrfhdfASFSDGNLgfnsfdlgn42143ln4g34h";
  char needle[] = "";

  ck_assert_pstr_eq(actual(haystack, needle), expected(haystack, needle));
}
END_TEST

START_TEST(empty_haystack) {
  char haystack[] = "";
  char needle[] = "asdgadrfhdfASFSDGNLgfnsfdlgn42143ln4g34h";

  ck_assert_pstr_eq(actual(haystack, needle), expected(haystack, needle));
}
END_TEST

START_TEST(empty_haystack_and_needle) {
  char haystack[] = "";
  char needle[] = "";

  ck_assert_pstr_eq(actual(haystack, needle), expected(haystack, needle));
}
END_TEST

/* SUITE */

static const size_t needle_vals_elems = GET_SIZE_ARRAY(needle_vals);
static const size_t needle_vals_fail_elems = GET_SIZE_ARRAY(needle_vals_fail);

Suite *suite_s21_strstr() {
  Suite *suite = suite_create("suite_s21_strstr");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_loop_test(normal_cases, found, 0, needle_vals_elems);
  tcase_add_loop_test(normal_cases, not_found, 0, needle_vals_fail_elems);
  tcase_add_test(normal_cases, repeated_words);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, words_with_any_register);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, needle_len_is_bigger);
  tcase_add_test(anomaly_cases, empty_needle);
  tcase_add_test(anomaly_cases, empty_haystack);
  tcase_add_test(anomaly_cases, empty_haystack_and_needle);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}