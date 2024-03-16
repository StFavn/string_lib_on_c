#include "s21_string_test.h"

#define actual(src, str, start_index) s21_insert(src, str, start_index)

/* NORMAL */

static const char *src_normal_vals[] = {
    "a",           // 0
    "aa",          //
    "aaa",         //
    "aaaa",        //
    "aaaaaaaa",    //
    "________",    // 5
    "12345678",    //
    "I AM LOCK.",  //
    "aaa12aaa",    //
    "aaA12!@#",    //
    "         "    // 10
};

static const char *str_normal_vals[] = {
    "_",                  // 0
    "_",                  //
    "_",                  //
    "_",                  //
    "AAAAA",              //
    "|||||",              // 5
    "_____",              //
    "SHER",               //
    "*********",          //
    "(((((_______)))))",  //
    "         "           // 10
};

static const char *zero_index_normal_expected[] = {
    "_a",                         // 0
    "_aa",                        //
    "_aaa",                       //
    "_aaaa",                      //
    "AAAAAaaaaaaaa",              //
    "|||||________",              // 5
    "_____12345678",              //
    "SHERI AM LOCK.",             //
    "*********aaa12aaa",          //
    "(((((_______)))))aaA12!@#",  //
    "                  "          // 10
};

static const char *half_index_normal_expected[] = {
    "_a",                         // 0
    "a_a",                        //
    "a_aa",                       //
    "aa_aa",                      //
    "aaaaAAAAAaaaa",              //
    "____|||||____",              // 5
    "1234_____5678",              //
    "I AM SHERLOCK.",             //
    "aaa1*********2aaa",          //
    "aaA1(((((_______)))))2!@#",  //
    "                  "          // 10
};

static const char *len_index_normal_expected[] = {
    "a_",                         // 0
    "aa_",                        //
    "aaa_",                       //
    "aaaa_",                      //
    "aaaaaaaaAAAAA",              //
    "________|||||",              // 5
    "12345678_____",              //
    "I AM LOCK.SHER",             //
    "aaa12aaa*********",          //
    "aaA12!@#(((((_______)))))",  //
    "                  "          // 10
};

START_TEST(zero_index_normal) {
  const char *expected_dest = zero_index_normal_expected[_i];

  const char *src = src_normal_vals[_i];
  const char *str = str_normal_vals[_i];
  size_t index = 0;

  void *actual_dest = actual(src, str, index);
  ck_assert_str_eq((char *)actual_dest, expected_dest);

  if (actual_dest != NULL) free(actual_dest);
};
END_TEST

START_TEST(half_index_normal) {
  const char *expected_dest = half_index_normal_expected[_i];

  const char *src = src_normal_vals[_i];
  const char *str = str_normal_vals[_i];
  size_t index = strlen(src) / 2;

  void *actual_dest = actual(src, str, index);
  ck_assert_str_eq((char *)actual_dest, expected_dest);

  if (actual_dest != NULL) free(actual_dest);
};
END_TEST

START_TEST(len_index_normal) {
  const char *expected_dest = len_index_normal_expected[_i];

  const char *src = src_normal_vals[_i];
  const char *str = str_normal_vals[_i];
  size_t index = strlen(src);

  void *actual_dest = actual(src, str, index);
  ck_assert_str_eq((char *)actual_dest, expected_dest);

  if (actual_dest != NULL) free(actual_dest);
};
END_TEST

static const char *index_check_normal_expected[] = {
    "__aaaaaaaa",  // 0
    "a__aaaaaaa",  //
    "aa__aaaaaa",  //
    "aaa__aaaaa",  //
    "aaaa__aaaa",  //
    "aaaaa__aaa",  // 5
    "aaaaaa__aa",  //
    "aaaaaaa__a",  //
    "aaaaaaaa__"   //
};

START_TEST(index_check_normal) {
  const char *expected_dest;

  const char *src = "aaaaaaaa";
  const char *str = "__";
  size_t index_max = strlen(src);

  for (size_t i = 0; i < (index_max) + 1; i++) {
    expected_dest = index_check_normal_expected[i];

    void *actual_dest = actual(src, str, i);
    ck_assert_str_eq((char *)actual_dest, expected_dest);

    if (actual_dest != NULL) free(actual_dest);
  }
};
END_TEST

/* EDGE */

static const char *src_edge_vals[] = {
    "",            // 0
    "aaaa",        //
    "\n",          //
    "aaaa",        //
    "\t\na\t",     //
    "aaaa\0aaaa",  // 5
    "aaaa",        //
    "\0",          //
    "aaaa",        //
    "\0aaaa",      //
    "aaaa",        // 10
    "\0\0\0\0",    //
    "aaaa",        //
    "\0",          //
    "\0a\0",       //
    "\n\n\n\n"     // 15
};

static const char *str_edge_vals[] = {
    "AAA",       // 0
    "",          //
    "AAA",       //
    "\n",        //
    "\t\n\t",    //
    "AAA",       // 5
    "AAA\0AAA",  //
    "AAA",       //
    "\0",        //
    "AAA",       //
    "\0AAA",     // 10
    "AAA",       //
    "\0\0\0",    //
    "\0",        //
    "\0A\0",     //
    "\t\t\t"     // 15
};

static const char *half_index_edge_expected[] = {
    "AAA",            // 0
    "aaaa",           //
    "AAA\n",          //
    "aa\naa",         //
    "\t\n\t\n\ta\t",  //
    "aaAAAaa",        // 5
    "aaAAAaa",        //
    "AAA",            //
    "aaaa",           //
    "AAA",            //
    "aaaa",           // 10
    "AAA",            //
    "aaaa",           //
    "",               //
    "",               //
    "\n\n\t\t\t\n\n"  // 15
};

START_TEST(half_index_edge) {
  const char *expected_dest = half_index_edge_expected[_i];

  const char *src = src_edge_vals[_i];
  const char *str = str_edge_vals[_i];
  size_t index = strlen(src) / 2;

  void *actual_dest = actual(src, str, index);
  ck_assert_str_eq((char *)actual_dest, expected_dest);

  if (actual_dest != NULL) free(actual_dest);
};
END_TEST

/* ANOMALY */

static const char *src_anomaly_vals[] = {
    "гггг",  // 0
    "гггг",  //
    "",      //
    "aaaa",  //
    NULL,    //
    NULL     // 5
};

static const char *str_anomaly_vals[] = {
    "ГГГ",  // 0
    "",     //
    "ГГГ",  //
    NULL,   //
    "AAA",  //
    NULL    // 5
};

static const char *anomaly_vals_expected[] = {
    "ггГГГгг",  // 0
    "гггг",     //
    "ГГГ",      //
    NULL,       //
    NULL,       //
    NULL        // 5
};

START_TEST(half_index_anomaly) {
  const char *expected_dest = anomaly_vals_expected[_i];

  const char *src = src_anomaly_vals[_i];
  const char *str = str_anomaly_vals[_i];
  size_t n;

  if (src != NULL) {
    n = strlen(src) / 2;
  } else {
    n = 0;
  }

  void *actual_dest = actual(src, str, n);
  if (expected_dest == NULL) {
    ck_assert_ptr_null(actual_dest);
  } else {
    ck_assert_str_eq((char *)actual_dest, expected_dest);
  }

  if (actual_dest != NULL) free(actual_dest);
};
END_TEST

START_TEST(over_index_normal) {
  const char *src = src_normal_vals[_i];
  const char *str = str_normal_vals[_i];
  size_t index = strlen(src) + 1;

  void *actual_dest = actual(src, str, index);
  ck_assert_ptr_null(actual_dest);

  if (actual_dest != NULL) free(actual_dest);
};
END_TEST

/* SUITES */

Suite *suite_s21_insert() {
  Suite *suite = suite_create("suite_s21_insert");

  TCase *normal_cases = tcase_create("normal_cases");
  const size_t normal_vals_elems =
      sizeof(src_normal_vals) / sizeof(src_normal_vals[0]);
  tcase_add_loop_test(normal_cases, zero_index_normal, 0, normal_vals_elems);
  tcase_add_loop_test(normal_cases, half_index_normal, 0, normal_vals_elems);
  tcase_add_loop_test(normal_cases, len_index_normal, 0, normal_vals_elems);
  tcase_add_test(normal_cases, index_check_normal);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  const size_t edge_vals_elems =
      sizeof(src_edge_vals) / sizeof(src_edge_vals[0]);
  tcase_add_loop_test(edge_cases, half_index_edge, 0, edge_vals_elems);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  const size_t anomaly_vals_elems =
      sizeof(anomaly_vals_expected) / sizeof(anomaly_vals_expected[0]);
  tcase_add_loop_test(anomaly_cases, half_index_anomaly, 0, anomaly_vals_elems);
  tcase_add_loop_test(anomaly_cases, over_index_normal, 0, normal_vals_elems);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}