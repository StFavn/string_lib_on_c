#include "s21_string_test.h"

#define actual(dest, str, n) s21_strncpy(dest, str, n)
#define expected(dest, str, n) strncpy(dest, str, n)

/* NORMAL */

static const char *normal_vals[] = {
    "aA",          // 0
    "bbA",         //
    "ccccccA",     //
    "dddeeedddA",  //
    "ffA\0ffA",    //
    "01",          // 5
    "0_2",         //
    "0__3__6",     //
    "0__3__6__9",  //
    "0__3\0_6__9"  //
};

START_TEST(normal_full_n) {
  char actual_dest[BUFF_SIZE] = {0};
  char expect_dest[BUFF_SIZE] = {0};

  const char *str = normal_vals[_i];
  const size_t n = strlen(str) + 1;

  actual(actual_dest, str, n);
  expected(expect_dest, str, n);

  ck_assert_str_eq(actual_dest, expect_dest);
}
END_TEST

START_TEST(normal_half_n) {
  char actual_dest[BUFF_SIZE] = {0};
  char expect_dest[BUFF_SIZE] = {0};

  const char *str = normal_vals[_i];
  const size_t n = (strlen(str) / 2);

  actual(actual_dest, str, n);
  expected(expect_dest, str, n);

  ck_assert_str_eq(actual_dest, expect_dest);
}
END_TEST

/* EDGE */

static const char *edge_vals[] = {
    "",            // 0
    "\0",          //
    "\0\0",        //
    "\0\0\n\0\0",  //
    "\0__0__"      //
};

START_TEST(edge_n_is_len) {
  char actual_dest[BUFF_SIZE] = {0};
  char expect_dest[BUFF_SIZE] = {0};

  const char *str = edge_vals[_i];
  const size_t n = strlen(str);

  actual(actual_dest, str, n);
  expected(expect_dest, str, n);

  ck_assert_str_eq(actual_dest, expect_dest);
}
END_TEST

START_TEST(normal_val_not_empty_dest) {
  char actual_dest[BUFF_SIZE] = {0};
  char expect_dest[BUFF_SIZE] = {0};

  strcpy(actual_dest, "0_________0_________0");
  strcpy(expect_dest, "0_________0_________0");

  const char *str = normal_vals[_i];
  const size_t n = strlen(str) + 1;

  actual(actual_dest, str, n);
  expected(expect_dest, str, n);

  ck_assert_str_eq(actual_dest, expect_dest);
}
END_TEST

START_TEST(edge_val_to_not_empty_dest) {
  char actual_dest[BUFF_SIZE] = {"_"};
  char expect_dest[BUFF_SIZE] = {"_"};

  const char *str = edge_vals[_i];
  const size_t n = strlen(str);

  actual(actual_dest, str, n);
  expected(expect_dest, str, n);

  ck_assert_str_eq(actual_dest, expect_dest);
}
END_TEST

START_TEST(separate_case_1) {
  char actual_dest[BUFF_SIZE] = {"12311111"};
  char expect_dest[BUFF_SIZE] = {"12311111"};

  const char *str = "\0\0xx456789";
  const size_t n = 4;

  actual(actual_dest, str, n);
  expected(expect_dest, str, n);

  ck_assert_str_eq(actual_dest, expect_dest);
}
END_TEST

/* ANOMALY */

static const char *str_anomaly_base_val = "_1__4__7__0";
static const size_t n_anomaly_base_val = 10;

START_TEST(anomaly_n_outsize) {
  char actual_dest[BUFF_SIZE] = {0};
  char expect_dest[BUFF_SIZE] = {0};

  const char *str = str_anomaly_base_val;
  const size_t n = n_anomaly_base_val + 2;

  actual(actual_dest, str, n);
  expected(expect_dest, str, n);

  ck_assert_str_eq(actual_dest, expect_dest);
}
END_TEST

/* SUITE */

static const size_t normal_elems = GET_SIZE_ARRAY(normal_vals);
static const size_t edge_elems = GET_SIZE_ARRAY(edge_vals);

Suite *suite_s21_strncpy() {
  Suite *suite = suite_create("suite_s21_strncpy");

  TCase *normal_case = tcase_create("normal_case");
  tcase_add_loop_test(normal_case, normal_full_n, 0, normal_elems);
  tcase_add_loop_test(normal_case, normal_half_n, 0, normal_elems);
  suite_add_tcase(suite, normal_case);

  TCase *edge_case = tcase_create("edge_case");
  tcase_add_loop_test(edge_case, edge_n_is_len, 0, edge_elems);
  tcase_add_loop_test(edge_case, normal_val_not_empty_dest, 0, edge_elems);
  tcase_add_loop_test(edge_case, edge_val_to_not_empty_dest, 0, edge_elems);
  tcase_add_loop_test(edge_case, separate_case_1, 0, edge_elems);
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("anomaly_case");
  tcase_add_test(anomaly_case, anomaly_n_outsize);
  suite_add_tcase(suite, anomaly_case);

  return suite;
}
