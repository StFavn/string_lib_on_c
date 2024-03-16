#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

#define DEF_VAL (void *)0xAA

/* NORMAL */

START_TEST(one_ptr) {
  const char *format = "%p";
  const char *src = "12abc";

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_dynamic_ptr) {
  const char *format = "%p";

  int *a_ptr = malloc(2 * sizeof(int));
  char src[BUFF_SIZE] = {0};

  char *address_str = s21_itoa((long long)a_ptr, 16, false, false, false);
  strcat(src, address_str);

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);

  free(address_str);
  free(a_ptr);
}
END_TEST

START_TEST(one_positive_ptr) {
  const char *format = "%p";
  const char *src = "+ff";

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_ptr_width) {
  const char *format = "%2p";
  const char *src = "fa123";

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

#define MULTI_PTRS_ELEMS 4

START_TEST(multi_ptr) {
  const char *format = "%p %p %p %p";
  const char *src = "abc 0xa1bc 0X12bd ABC12";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, DEF_VAL, DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ptr_width) {
  const char *format = "%1p %p %3p %p";
  const char *src = "abc 0xa1bc 0X12bd ABC12";

  int *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  int *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, DEF_VAL, DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

START_TEST(multi_types_ptr) {
  const char *format = "%p %lp %hp %p";
  const char *src = "abc 1c1 0xFF 1Fc2";

  int *d0_actual = NULL;
  int *d0_expected = DEF_VAL;
  long *l0_actual = NULL;
  long *l0_expected = DEF_VAL;
  short *si0_actual = NULL;
  short *si0_expected = DEF_VAL;
  int *d1_actual = NULL;
  int *d1_expected = DEF_VAL;

  ck_assert_int_eq(
      actual(src, format, &d0_actual, &l0_actual, &si0_actual, &d1_actual),
      expected(src, format, &d0_expected, &l0_expected, &si0_expected,
               &d1_expected));

  ck_assert_ptr_eq(d0_actual, d0_expected);
  ck_assert_ptr_eq(l0_actual, l0_expected);
  ck_assert_ptr_eq(si0_actual, si0_expected);
  ck_assert_ptr_eq(d1_actual, d1_expected);
}
END_TEST

/* EDGE */

START_TEST(one_negative_zero) {
  const char *format = "%p";
  const char *src = "-0";

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_positive_zero) {
  const char *format = "%p";
  const char *src = "+0";

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_max_int_ptr) {
  const char *format = "%p";
  const char *src = "7FFFFFFF";  // INT_MAX

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_min_int_ptr) {
  const char *format = "%p";
  const char *src = "-80000000";  // INT_MIN

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(multi_sign_zeros_ptr) {
  const char *format = "%p %p %p %p";
  const char *src = "-0x0 +42 +0x0 -111";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, DEF_VAL, DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ptr_good_format_0) {
  const char *format = "%p_%p_%p_%p";
  const char *src = "fff_AA_0xb710_53ac1";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, DEF_VAL, DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ptr_good_format_1) {
  const char *format = "%p_%p_%p_%p";
  const char *src = "+fff_-AA_+0xb710_53ac1";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, DEF_VAL, DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ptr_good_format_2) {
  const char *format = "%p_%p__%p %p";
  const char *src = "+0Xd5135_-6a2__-f1 +0x0";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, DEF_VAL, DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

// // START_TEST(multi_dec_good_format_2_width) {
// //   const char *format = "%5d_%2d__%4d %1d";
// //   const char *src = "+15135_-612__-0 +0";

// //   void *ptrs_actual[MULTI_HEX_ELEMS] = {NULL, NULL, NULL, NULL};
// //   void *ptrs_expected[MULTI_HEX_ELEMS]  = {DEF_VAL, DEF_VAL, DEF_VAL,
// DEF_VAL};

// //   ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
// &ptrs_actual[2], &ptrs_actual[3]),
// //                    expected(src, format, &ptrs_expected[0],
// &ptrs_expected[1], &ptrs_expected[2], &ptrs_expected[3]));

// //   for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
// //     ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
// //   }
// // }
// // END_TEST

START_TEST(multi_ptr_bad_format) {
  const char *format = "%p1%p1%p1%p";
  const char *src = "ffac 612 710 53";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, NULL, NULL, NULL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

/* ANOMALY */

START_TEST(one_big_positive_ptr) {
  const char *format = "%p";
  const char *src = "CCCCCCCCCCCCCD0";  // LONG_MAX - 3

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_big_negative_ptr) {
  const char *format = "%p";
  const char *src = "-CCCCCCCCCCCCCD0";  // LONG_MIN + 3

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_int_ptr_overflow) {
  const char *format = "%lp";
  const char *src = "80000002";  // INT_MAX + 3

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_not_ptr_0) {
  const char *format = "%p";
  const char *src = "hello!";

  void *ptr_actual = DEF_VAL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_not_ptr_1) {
  const char *format = "%p";
  const char *src = "0xhello!";

  void *ptr_actual = DEF_VAL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(only_pref_small) {
  const char *format = "%p";
  const char *src0 = "0x";

  void *ptr_actual = DEF_VAL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src0, format, &ptr_actual),
                   expected(src0, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(only_pref_big) {
  const char *format = "%p";
  const char *src0 = "0X";

  void *ptr_actual = DEF_VAL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src0, format, &ptr_actual),
                   expected(src0, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(only_pref_width) {
  const char *format = "%1p";
  const char *src0 = "0x";

  void *ptr_actual = DEF_VAL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src0, format, &ptr_actual),
                   expected(src0, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(one_mix_good_bad_src) {
  const char *format = "%p %p";
  const char *src = "fab1 vvv";

  void *ptrs_actual[] = {NULL, NULL};
  void *ptrs_expected[] = {DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1]));
  ck_assert_ptr_eq(ptrs_actual[0], ptrs_expected[0]);
  ck_assert_ptr_ne(ptrs_actual[1], ptrs_expected[1]);
}
END_TEST

START_TEST(bad_ptrs_0) {
  const char *format = "%p %p %p %p";
  const char *src = "++++ff_---a1__+-b1 +c1";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

START_TEST(bad_ptrs_1) {
  const char *format = "%p %p %p %p";
  const char *src = "+0x24f_---nnn2__+-0 +0";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, NULL, NULL, NULL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ptr_big_width) {
  const char *format = "%100p %p %3p %p";
  const char *src = "ffff4 1f13 0x2a 754";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, DEF_VAL, DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

START_TEST(one_negative_ptr) {
  const char *format = "%p";
  const char *src = "-ff";

  void *ptr_actual = NULL;
  void *ptr_expected = DEF_VAL;

  ck_assert_int_eq(actual(src, format, &ptr_actual),
                   expected(src, format, &ptr_expected));
  ck_assert_ptr_eq(ptr_actual, ptr_expected);
}
END_TEST

START_TEST(multi_sign_ptr) {
  const char *format = "%p %p %p %p";
  const char *src = "-abc +1c1 -0xFF -1Fc2";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, DEF_VAL, DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

START_TEST(multi_sign_ptr_width) {
  const char *format = "%2p %2p %2p %2p";
  const char *src = "-abc +1c1 -0xFF -1Fc2";

  void *ptrs_actual[MULTI_PTRS_ELEMS] = {NULL, NULL, NULL, NULL};
  void *ptrs_expected[MULTI_PTRS_ELEMS] = {DEF_VAL, DEF_VAL, DEF_VAL, DEF_VAL};

  ck_assert_int_eq(actual(src, format, &ptrs_actual[0], &ptrs_actual[1],
                          &ptrs_actual[2], &ptrs_actual[3]),
                   expected(src, format, &ptrs_expected[0], &ptrs_expected[1],
                            &ptrs_expected[2], &ptrs_expected[3]));

  for (size_t i = 0; i < MULTI_PTRS_ELEMS; i++) {
    ck_assert_ptr_eq(ptrs_actual[i], ptrs_expected[i]);
  }
}
END_TEST

Suite *suite_s21_sscanf_p() {
  Suite *suite = suite_create("suite_s21_sscanf_p");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, one_ptr);
  tcase_add_test(normal_cases, one_dynamic_ptr);
  tcase_add_test(normal_cases, one_negative_ptr);
  tcase_add_test(normal_cases, one_positive_ptr);
  tcase_add_test(normal_cases, one_ptr_width);
  tcase_add_test(normal_cases, multi_ptr);
  tcase_add_test(normal_cases, multi_ptr_width);
  tcase_add_test(normal_cases, multi_sign_ptr);
  tcase_add_test(normal_cases, multi_sign_ptr_width);
  tcase_add_test(normal_cases, multi_types_ptr);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, one_negative_zero);
  tcase_add_test(edge_cases, one_positive_zero);
  tcase_add_test(edge_cases, one_max_int_ptr);
  tcase_add_test(edge_cases, one_min_int_ptr);
  tcase_add_test(edge_cases, multi_sign_zeros_ptr);
  tcase_add_test(edge_cases, multi_ptr_good_format_0);
  tcase_add_test(edge_cases, multi_ptr_good_format_1);
  tcase_add_test(edge_cases, multi_ptr_good_format_2);
  tcase_add_test(edge_cases, multi_ptr_bad_format);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, one_big_positive_ptr);
  tcase_add_test(anomaly_cases, one_big_negative_ptr);
  tcase_add_test(anomaly_cases, one_int_ptr_overflow);
  tcase_add_test(anomaly_cases, one_not_ptr_0);
  tcase_add_test(anomaly_cases, one_not_ptr_1);
  tcase_add_test(anomaly_cases, only_pref_big);
  tcase_add_test(anomaly_cases, only_pref_small);
  tcase_add_test(anomaly_cases, only_pref_width);
  tcase_add_test(anomaly_cases, one_mix_good_bad_src);
  tcase_add_test(anomaly_cases, bad_ptrs_0);
  tcase_add_test(anomaly_cases, bad_ptrs_1);
  tcase_add_test(anomaly_cases, multi_ptr_big_width);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
