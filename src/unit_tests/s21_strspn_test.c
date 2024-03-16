#include "s21_string_test.h"

#define actual(str1, str2) s21_strspn(str1, str2)
#define expected(str1, str2) strspn(str1, str2)

/* NORMAL */

static const char *normal_str1_lst_g[] = {
    "Hello world!",                                     // 0
    "Robot1 TEST ma.chine1 1.11100-kjUTT014,..001",     //
    "       123       456!!!!!!!!!!!jtdgfhgfsnoln24?4"  //
};

static const char *normal_str2_lst_g[] = {
    "Hew",  // 0
    "obR",  //
    " 1"    //
};

START_TEST(all_str_found) {
  const size_t strs1_elem = GET_SIZE_ARRAY(normal_str1_lst_g);

  for (size_t i = 0; i < strs1_elem; ++i) {
    char str1[BUFF_SIZE] = {0};

    strcpy(str1, normal_str1_lst_g[i]);

    const size_t strs2_elem = GET_SIZE_ARRAY(normal_str2_lst_g);
    for (size_t j = 0; j < strs2_elem; ++j) {
      ck_assert_int_eq(actual(str1, normal_str2_lst_g[j]),
                       expected(str1, normal_str2_lst_g[j]));
    }
  }
}
END_TEST

static const char *str2_lst_fail[] = {
    "XYZ",   // 0
    "7890",  //
    "\t"     //
};

START_TEST(not_found) {
  const char *str2 = str2_lst_fail[_i];
  const size_t strs1_elem = GET_SIZE_ARRAY(normal_str1_lst_g);

  for (size_t i = 0; i < strs1_elem; ++i) {
    char str1[BUFF_SIZE] = {0};

    strcpy(str1, normal_str1_lst_g[i]);

    ck_assert_int_eq(actual(str1, str2), expected(str1, str2));
  }
}
END_TEST

START_TEST(repeated_words) {
  char str1[] = "TEST TEST TEST TEST";
  char str2[] = "TEST ";

  ck_assert_int_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

/* EDGE */

START_TEST(words_with_any_register) {
  char str1[] = "AbOBosNyTSa";
  char str2[] = "aBoboSNYTsa";

  ck_assert_int_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

/* ANOMALY */

START_TEST(empty_str2) {
  char str1[] = "asdgadrfhdfASFSDGNLgfnsfdlgn42143ln4g34h";
  char str2[] = "";

  ck_assert_int_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

START_TEST(empty_str1) {
  char str1[] = "";
  char str2[] = "asdgadrfhdfASFSDGNLgfnsfdlgn42143ln4g34h";

  ck_assert_int_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

START_TEST(empty_all_str) {
  char str1[] = "";
  char str2[] = "";

  ck_assert_int_eq(actual(str1, str2), expected(str1, str2));
}
END_TEST

/// * Argument `NULL` raise Segmentation fault (or Undefined Behavior) in
/// std::strspn()

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

/* SUITE */

static const size_t str_list_elem = GET_SIZE_ARRAY(normal_str1_lst_g);

Suite *suite_s21_strspn() {
  Suite *suite = suite_create("suite_s21_strspn");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, all_str_found);
  tcase_add_loop_test(normal_cases, not_found, 0, str_list_elem);
  tcase_add_test(normal_cases, repeated_words);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, words_with_any_register);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, empty_str2);
  tcase_add_test(anomaly_cases, empty_str1);
  tcase_add_test(anomaly_cases, empty_all_str);
  // tcase_add_test(anomaly_cases, one_of_str_is_null);
  // tcase_add_test(anomaly_cases, all_str_is_null);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}