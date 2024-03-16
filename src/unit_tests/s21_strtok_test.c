#include "s21_string_test.h"

#define actual(str, delim) s21_strtok(str, delim)
#define expected(str, delim) strtok(str, delim)

/* NORMAL */

static const char *normal_strs_g[] = {
    "Hello world! Mr. Jones, we have message for you.\nDo you wanna see ",
    "this?\nOk, this is... Hmm",  // 0                       // 0
    "Robot1 TEST ma.chine1 1.11100-kjUTT014,..001",     //
    "<hello>>?f1nd0m,!",                                //
    "       123       456!!!!!!!!!!!jtdgfhgfsnoln24?4"  //
};

static const char *normal_delims_g[] = {
    " ",     // 0
    "\n",    //
    "a",     //
    "elMm",  //
    ".,!",   //
    "?<>1",  // 5
    "-io"    //
};

START_TEST(all_str_delim_found) {
  const size_t strs_elem = GET_SIZE_ARRAY(normal_strs_g);
  for (size_t i = 0; i < strs_elem; ++i) {
    char str_actual[BUFF_SIZE] = {0};
    char str_expected[BUFF_SIZE] = {0};

    strcpy(str_actual, normal_strs_g[i]);
    strcpy(str_expected, normal_strs_g[i]);

    const size_t delims_elem = GET_SIZE_ARRAY(normal_delims_g);
    for (size_t j = 0; j < delims_elem; ++j) {
      char *found_actual = actual(str_actual, normal_delims_g[j]);
      char *found_expected = expected(str_expected, normal_delims_g[j]);

      ck_assert_str_eq(found_actual, found_expected);

      while (found_actual != NULL && found_expected != NULL) {
        found_actual = actual(NULL, normal_delims_g[j]);
        found_expected = expected(NULL, normal_delims_g[j]);

        if (found_expected != NULL) {
          ck_assert_str_eq(found_actual, found_expected);
        } else if (found_expected == NULL) {
          ck_assert_ptr_null(found_actual);
        }
      }
    }
  }
}
END_TEST

START_TEST(not_found) {
  char str_actual[BUFF_SIZE] = "Hello world!";
  char str_expected[BUFF_SIZE] = "Hello world!";
  char delim[] = "-+=";

  char *found_actual = actual(str_actual, delim);
  char *found_expected = expected(str_expected, delim);

  ck_assert_str_eq(found_actual, found_expected);
}
END_TEST

/* EDGE */

START_TEST(one_match) {
  char str_actual[BUFF_SIZE] = "123x456";
  char str_expected[BUFF_SIZE] = "123x456";
  char delim[] = "x-+=";

  char *found_actual = actual(str_actual, delim);
  char *found_expected = expected(str_expected, delim);

  ck_assert_str_eq(found_actual, found_expected);

  while (found_actual != NULL && found_expected != NULL) {
    found_actual = actual(NULL, delim);
    found_expected = expected(NULL, delim);

    if (found_expected != NULL) {
      ck_assert_str_eq(found_actual, found_expected);
    } else if (found_expected == NULL) {
      ck_assert_ptr_null(found_actual);
    }
  }
}
END_TEST

START_TEST(dynamic_delim) {
  char str_actual[BUFF_SIZE] = "123x456!abc-def=jkl.bvc";
  char str_expected[BUFF_SIZE] = "123x456!abc-def=jkl.bvc";

  char *delims[] = {"x", "!", "-", "=", "."};
  const size_t delims_elem = GET_SIZE_ARRAY(delims);

  char *found_actual = actual(str_actual, delims[0]);
  char *found_expected = expected(str_expected, delims[0]);

  ck_assert_str_eq(found_actual, found_expected);

  for (size_t i = 1; i < delims_elem; ++i) {
    while (found_actual != NULL && found_expected != NULL) {
      found_actual = actual(NULL, delims[i]);
      found_expected = expected(NULL, delims[i]);

      if (found_expected != NULL) {
        ck_assert_str_eq(found_actual, found_expected);
      } else if (found_expected == NULL) {
        ck_assert_ptr_null(found_actual);
      }
    }
  }
}
END_TEST

START_TEST(dynamic_str) {
  char str_actual[BUFF_SIZE] = "123x456!abc-def=jkl.bvc";
  char str_expected[BUFF_SIZE] = "123x456!abc-def=jkl.bvc";
  char delim[] = "x-+=";

  char *found_actual = actual(str_actual, delim);
  char *found_expected = expected(str_expected, delim);

  ck_assert_str_eq(found_actual, found_expected);

  strcpy(str_actual, "HelloxWorld-123");
  strcpy(str_expected, "HelloxWorld-123");

  found_actual = actual(str_actual, delim);
  found_expected = expected(str_expected, delim);

  ck_assert_str_eq(found_actual, found_expected);
}
END_TEST

/* ANOMALY */

START_TEST(one_str_multi_call_no_null) {
  char str_actual[BUFF_SIZE] = "123x456!abc-def=jkl.bvc";
  char str_expected[BUFF_SIZE] = "123x456!abc-def=jkl.bvc";
  char delim[] = "x-+=";

  char *found_actual = actual(str_actual, delim);
  char *found_expected = expected(str_expected, delim);

  ck_assert_str_eq(found_actual, found_expected);

  found_actual = actual(str_actual, delim);
  found_expected = expected(str_expected, delim);

  ck_assert_str_eq(found_actual, found_expected);
}
END_TEST

START_TEST(empty_delim) {
  char str_actual[BUFF_SIZE] = "123x456!abc-def=jkl.bvc";
  char str_expected[BUFF_SIZE] = "123x456!abc-def=jkl.bvc";
  char delim[] = "";

  char *found_actual = actual(str_actual, delim);
  char *found_expected = expected(str_expected, delim);

  ck_assert_str_eq(found_actual, found_expected);
}
END_TEST

START_TEST(empty_str) {
  char str_actual[BUFF_SIZE] = "";
  char delim[] = "x-+=";

  char *found_actual = actual(str_actual, delim);

  ck_assert_ptr_null(found_actual);
}
END_TEST

START_TEST(empty_str_and_delim) {
  char str_actual[BUFF_SIZE] = "";
  char delim[] = "";

  char *found_actual = actual(str_actual, delim);

  ck_assert_ptr_null(found_actual);
}
END_TEST

/// * Argument `NULL` to std::strtok() is raise Undefined Behavior - result is
/// * random garbage from memory

// START_TEST(null_first_call) {
//   char *found_actual = actual(NULL, "x");
//   char *found_expected = expected(NULL, "x");

//   if (found_expected != NULL) {
//     ck_assert_str_eq(found_actual, found_expected);
//   } else if (found_expected == NULL) {
//     ck_assert_ptr_null(found_actual);
//   }
// } END_TEST

/* SUITE */

Suite *suite_s21_strtok() {
  Suite *suite = suite_create("suite_s21_strtok");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, all_str_delim_found);
  tcase_add_test(normal_cases, not_found);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, one_match);
  tcase_add_test(edge_cases, dynamic_delim);
  tcase_add_test(edge_cases, dynamic_str);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, one_str_multi_call_no_null);
  tcase_add_test(anomaly_cases, empty_delim);
  tcase_add_test(anomaly_cases, empty_str);
  tcase_add_test(anomaly_cases, empty_str_and_delim);
  // tcase_add_test(anomaly_cases, null_first_call);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}