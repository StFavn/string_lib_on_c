#include "s21_string_test.h"

#define actual(str, n) s21_strrchr(str, n)
#define expected(str, n) strrchr(str, n)

/* NORMAL */

static const char *normal_vals[] = {
    "hello",              // 0
    "world",              //
    "hello world",        //
    "123456",             //
    "abcde\nfseew",       //
    "123456789",          // 5
    "HOFO",               //
    "C is Love",          //
    "C is L1F3",          //
    " LERROY JANKEENS ",  //
    "zzzzzzzzzz",         // 10
    "\t\n\t",             //
    "\n"                  //
};

START_TEST(all_c_in_normal_vals) {
  const char *str = normal_vals[_i];
  size_t index_max = strlen(str);

  for (size_t i = 0; i < index_max; i++) {
    const char c = str[i];
    ck_assert_str_eq(actual(str, c), expected(str, c));
  }
}
END_TEST

START_TEST(no_c_in_normal_vals) {
  const char *str = normal_vals[_i];
  const char c = 'x';

  ck_assert_ptr_null(actual(str, c));
}
END_TEST

/* EDGE */

static const char *edge_vals[] = {
    "",           // 0
    "     ",      //
    "\0",         //
    "\n\n\t\t",   //
    "\\\\",       //
    "\01\02\025"  //
};

START_TEST(all_c_in_edge_vals) {
  const char *str = edge_vals[_i];
  const size_t index_max = strlen(str);

  for (size_t i = 0; i < index_max; i++) {
    const char c = str[i];
    ck_assert_str_eq(actual(str, c), expected(str, c));
  }
}
END_TEST

START_TEST(no_c_in_edge_vals) {
  const char *str = edge_vals[_i];
  const char c = 'x';

  ck_assert_ptr_null(actual(str, c));
}
END_TEST

/* ANOMALY */

static const char *anomaly_vals[] = {
    "\0 1234",      // 0
    "привет мир!",  //
    "\00",          //
    "目标应该"      //
};

START_TEST(all_c_in_anomaly_vals) {
  const char *str = anomaly_vals[_i];
  const size_t index_max = strlen(str);

  for (size_t i = 0; i < index_max; i++) {
    const char c = str[i];
    ck_assert_str_eq(actual(str, c), expected(str, c));
  }
}
END_TEST

START_TEST(no_c_in_anomaly_vals) {
  const char *str = anomaly_vals[_i];
  const char c = 'x';

  ck_assert_ptr_null(actual(str, c));
}
END_TEST

static const char *all_vals[] = {
    "hello",              // 0
    "world",              //
    "hello world",        //
    "123456",             //
    "abcde\nfseew",       //
    "123456789",          // 5
    "HOFO",               //
    "C is Love",          //
    "C is L1F3",          //
    " LERROY JANKEENS ",  //
    "zzzzzzzzzz",         // 10
    "\t\n\t",             //
    "\n",                 //
    "\0",                 //
    "\n\n\t\t",           //
    "\\\\",               // 15
    "\01\02\025",         //
    "\0 1234",            //
    "привет мир!",        //
    "\00",                //
    "目标应该"            //
};

START_TEST(c_not_char_all_vals) {
  const char *str = all_vals[_i];
  const char c = 0;

  ck_assert_str_eq(actual(str, c), expected(str, c));
}
END_TEST

START_TEST(c_big_int_all_vals) {
  const char *str = all_vals[_i];
  const int c = 999999;

  ck_assert_ptr_null(actual(str, c));
}
END_TEST

START_TEST(c_null_symb_all_vals) {
  const char *str = all_vals[_i];
  const char c = '\0';

  ck_assert_str_eq(actual(str, c), expected(str, c));
}
END_TEST

/* SUITE */

static const size_t normal_elems = GET_SIZE_ARRAY(normal_vals);
static const size_t edge_elems = GET_SIZE_ARRAY(edge_vals);
static const size_t anomaly_elems = GET_SIZE_ARRAY(anomaly_vals);
static const size_t all_elems = GET_SIZE_ARRAY(all_vals);

Suite *suite_s21_strrchr() {
  Suite *suite = suite_create("suite_s21_strrchr");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_loop_test(normal_cases, all_c_in_normal_vals, 0, normal_elems);
  tcase_add_test(normal_cases, no_c_in_normal_vals);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_loop_test(edge_cases, all_c_in_edge_vals, 0, edge_elems);
  tcase_add_test(edge_cases, no_c_in_edge_vals);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_loop_test(anomaly_cases, all_c_in_anomaly_vals, 0, anomaly_elems);
  tcase_add_loop_test(anomaly_cases, no_c_in_anomaly_vals, 0, anomaly_elems);
  tcase_add_loop_test(anomaly_cases, c_not_char_all_vals, 0, all_elems);
  tcase_add_loop_test(anomaly_cases, c_big_int_all_vals, 0, all_elems);
  tcase_add_loop_test(anomaly_cases, c_null_symb_all_vals, 0, all_elems);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}