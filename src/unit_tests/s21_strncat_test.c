#include "s21_string_test.h"

#define actual(dest, src, n) s21_strncat(dest, src, n)
#define expected(dest, src, n) strncat(dest, src, n)

/* NORMAL */

static const char *normal_vals_0[] = {
    "hello",        // 0
    "world",        //
    "hello world",  //
    "123456",       //
    "abcde\nfseew"  //
};

static const char *normal_vals_1[] = {
    "123456789",          // 0
    "HOFO",               //
    "C is Love",          //
    "C is L1F3",          //
    " LERROY JANKEENS ",  //
    "\t\n\t",             // 5
    "\n"                  //
};

START_TEST(to_empty) {
  const size_t elems = GET_SIZE_ARRAY(normal_vals_1);
  for (size_t i = 0; i < elems; i++) {
    char dest_act[BUFF_SIZE] = {0};
    char dest_exp[BUFF_SIZE] = {0};

    const char *src = normal_vals_1[i];
    const size_t n = strlen(src);

    ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
  }
}
END_TEST

START_TEST(to_normal_0) {
  const size_t elems = GET_SIZE_ARRAY(normal_vals_1);
  for (size_t i = 0; i < elems; i++) {
    char dest_act[BUFF_SIZE] = {0};
    char dest_exp[BUFF_SIZE] = {0};

    strcat(dest_act, normal_vals_0[_i]);
    strcat(dest_exp, normal_vals_0[_i]);

    const char *src = normal_vals_1[i];
    const size_t n = strlen(src);

    ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
  }
}
END_TEST

START_TEST(to_normal_1) {
  const size_t elems = GET_SIZE_ARRAY(normal_vals_0);
  for (size_t i = 0; i < elems; i++) {
    char dest_act[BUFF_SIZE] = {0};
    char dest_exp[BUFF_SIZE] = {0};

    strcat(dest_act, normal_vals_1[_i]);
    strcat(dest_exp, normal_vals_1[_i]);

    const char *src = normal_vals_0[i];
    const size_t n = strlen(src);

    ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
  }
}
END_TEST

START_TEST(half_n) {
  const size_t elems = GET_SIZE_ARRAY(normal_vals_1);
  for (size_t i = 0; i < elems; i++) {
    char dest_act[BUFF_SIZE] = {0};
    char dest_exp[BUFF_SIZE] = {0};

    strcat(dest_act, normal_vals_0[_i]);
    strcat(dest_exp, normal_vals_0[_i]);

    const char *src = normal_vals_1[i];
    const size_t n = strlen(src) / 2;

    ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
  }
}
END_TEST

START_TEST(two_steps) {
  const size_t elems = GET_SIZE_ARRAY(normal_vals_1);
  for (size_t i = 0; i < elems; i++) {
    char dest_act[BUFF_SIZE] = {0};
    char dest_exp[BUFF_SIZE] = {0};

    strcat(dest_act, normal_vals_0[_i]);
    strcat(dest_exp, normal_vals_0[_i]);

    const char *src = normal_vals_1[i];
    const size_t n = strlen(src) / 2;

    ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
    ck_assert_str_eq(actual(dest_act, src + n, n),
                     expected(dest_exp, src + n, n));
  }
}
END_TEST

/* EDGE */

static const char *edge_vals[] = {
    "     ",      // 0
    "",           //
    "\n\n\t\t",   //
    "\\\\",       //
    "\01\02\025"  //
};

START_TEST(edge_to_normal_0) {
  const size_t elems = GET_SIZE_ARRAY(edge_vals);
  for (size_t i = 0; i < elems; i++) {
    char dest_act[BUFF_SIZE] = {0};
    char dest_exp[BUFF_SIZE] = {0};

    strcat(dest_act, normal_vals_0[_i]);
    strcat(dest_exp, normal_vals_0[_i]);

    const char *src = edge_vals[i];
    const size_t n = strlen(src);

    ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
  }
}
END_TEST

START_TEST(normal_0_to_edge) {
  const size_t elems = GET_SIZE_ARRAY(normal_vals_0);
  for (size_t i = 0; i < elems; i++) {
    char dest_act[BUFF_SIZE] = {0};
    char dest_exp[BUFF_SIZE] = {0};

    strcat(dest_act, edge_vals[_i]);
    strcat(dest_exp, edge_vals[_i]);

    const char *src = normal_vals_0[i];
    const size_t n = strlen(src);

    ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
  }
}
END_TEST

/* ANOMALY */

static const char *anomaly_vals[] = {
    "\0 1234",      // 0
    "\00",          //
    "привет мир!",  //
    "目标应该"      //
};

START_TEST(anomaly_to_normal_0) {
  const size_t elems = GET_SIZE_ARRAY(anomaly_vals);
  for (size_t i = 0; i < elems; i++) {
    char dest_act[BUFF_SIZE] = {0};
    char dest_exp[BUFF_SIZE] = {0};

    strcat(dest_act, normal_vals_0[_i]);
    strcat(dest_exp, normal_vals_0[_i]);

    const char *src = anomaly_vals[i];
    const size_t n = strlen(src);

    ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
  }
}
END_TEST

START_TEST(normal_0_to_anomaly) {
  const size_t elems = GET_SIZE_ARRAY(normal_vals_0);
  for (size_t i = 0; i < elems; i++) {
    char dest_act[BUFF_SIZE] = {0};
    char dest_exp[BUFF_SIZE] = {0};

    strcat(dest_act, anomaly_vals[_i]);
    strcat(dest_exp, anomaly_vals[_i]);

    const char *src = normal_vals_0[i];
    const size_t n = strlen(src);

    ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
  }
}
END_TEST

START_TEST(n_is_bigger_src) {
  char dest_act[BUFF_SIZE] = "123456789";
  char dest_exp[BUFF_SIZE] = "123456789";

  const char src[BUFF_SIZE] = "x\0xxxxxx";
  const size_t n = 128;

  ck_assert_str_eq(actual(dest_act, src, n), expected(dest_exp, src, n));
}
END_TEST

/* SUITE */

static const size_t normal_0_elems = GET_SIZE_ARRAY(normal_vals_0);
static const size_t normal_1_elems = GET_SIZE_ARRAY(normal_vals_1);
static const size_t edge__elems = GET_SIZE_ARRAY(edge_vals);
static const size_t anomaly_elems = GET_SIZE_ARRAY(anomaly_vals);

Suite *suite_s21_strncat() {
  Suite *suite = suite_create("suite_s21_strncat");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, to_empty);
  tcase_add_loop_test(normal_cases, to_normal_0, 0, normal_0_elems);
  tcase_add_loop_test(normal_cases, to_normal_1, 0, normal_1_elems);
  tcase_add_loop_test(normal_cases, half_n, 0, normal_0_elems);
  tcase_add_loop_test(normal_cases, two_steps, 0, normal_0_elems);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_loop_test(edge_cases, edge_to_normal_0, 0, normal_0_elems);
  tcase_add_loop_test(edge_cases, normal_0_to_edge, 0, edge__elems);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_loop_test(anomaly_cases, anomaly_to_normal_0, 0, normal_0_elems);
  tcase_add_loop_test(anomaly_cases, normal_0_to_anomaly, 0, anomaly_elems);
  tcase_add_test(anomaly_cases, n_is_bigger_src);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}