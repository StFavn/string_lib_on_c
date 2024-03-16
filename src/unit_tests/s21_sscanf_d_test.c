#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

/* NORMAL */

START_TEST(one_dec) {
  const char *format = "%d";
  const char *src = "42";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_negative_dec) {
  const char *format = "%d";
  const char *src = "-42";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_positive_dec) {
  const char *format = "%d";
  const char *src = "+42";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_dec_width) {
  const char *format = "%2d";
  const char *src = "12345";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_short_width) {
  const char *format = "%2hd";
  const char *src = "12345";

  short num_actual = 0;
  short num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

#define MULTI_DEC_ELEMS 4

START_TEST(multi_dec) {
  const char *format = "%d %d %d %d";
  const char *src = "42 1910 28200 754";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_dec_width) {
  const char *format = "%1d %d %3d %d";
  const char *src = "42 113 225564 754";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_sign_dec) {
  const char *format = "%d %d %d";
  const char *src = "-42 +11 -22";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 0};

  ck_assert_int_eq(
      actual(src, format, &nums_actual[0], &nums_actual[1], &nums_actual[2]),
      expected(src, format, &nums_expected[0], &nums_expected[1],
               &nums_expected[2]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_sign_dec_width) {
  const char *format = "%2d %2d %2d";
  const char *src = "-423 +11 -22";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 0};

  ck_assert_int_eq(
      actual(src, format, &nums_actual[0], &nums_actual[1], &nums_actual[2]),
      expected(src, format, &nums_expected[0], &nums_expected[1],
               &nums_expected[2]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_types_dec) {
  const char *format = "%d %ld %hd %d";
  const char *src = "42 11 22 754";

  int d0_actual = 0;
  int d0_expected = 1;
  long l0_actual = 0;
  long l0_expected = 1;
  short si0_actual = 0;
  short si0_expected = 1;
  int d1_actual = 0;
  int d1_expected = 1;

  ck_assert_int_eq(
      actual(src, format, &d0_actual, &l0_actual, &si0_actual, &d1_actual),
      expected(src, format, &d0_expected, &l0_expected, &si0_expected,
               &d1_expected));

  ck_assert_int_eq(d0_actual, d0_expected);
  ck_assert_int_eq(l0_actual, l0_expected);
  ck_assert_int_eq(si0_actual, si0_expected);
  ck_assert_int_eq(d1_actual, d1_expected);
}
END_TEST

/* EDGE */

START_TEST(one_negative_zero) {
  const char *format = "%d";
  const char *src = "-0";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_positive_zero) {
  const char *format = "%d";
  const char *src = "+0";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_max_int_dec) {
  const char *format = "%d";
  const char *src = "2147483647";  // INT_MIN

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(num_actual, INT_MAX);
}
END_TEST

START_TEST(one_min_int_dec) {
  const char *format = "%d";
  const char *src = "-2147483648";  // INT_MIN

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(num_actual, INT_MIN);
}
END_TEST

START_TEST(one_max_short_dec) {
  const char *format = "%hd";
  const char *src = "32767";  // SHRT_MAX

  short num_actual = 0;
  short num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(num_actual, SHRT_MAX);
}
END_TEST

START_TEST(one_max_long_dec) {
  const char *format = "%ld";
  const char *src = "9223372036854775807";  // LONG_MAX

  long num_actual = 0;
  long num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(num_actual, LONG_MAX);
}
END_TEST

START_TEST(multi_sign_zeros_dec) {
  const char *format = "%d %d %d %d";
  const char *src = "-0 +42 +0 -111";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_dec_good_format_0) {
  const char *format = "%d_%d_%d_%d";
  const char *src = "15135_612_710_53";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_dec_good_format_1) {
  const char *format = "%d_%d_%d_%d";
  const char *src = "+15135_-612_-0_+0";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_dec_good_format_2) {
  const char *format = "%d_%d__%d %d";
  const char *src = "+15135_-612__-0 +0";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

// START_TEST(multi_dec_good_format_2_width) {
//   const char *format = "%5d_%2d__%4d %1d";
//   const char *src = "+15135_-612__-0 +0";

//   int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
//   int nums_expected[MULTI_DEC_ELEMS]  = {1, 1, 1, 1};

//   ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
//   &nums_actual[2], &nums_actual[3]),
//                    expected(src, format, &nums_expected[0],
//                    &nums_expected[1], &nums_expected[2], &nums_expected[3]));

//   for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
//     ck_assert_int_eq(nums_actual[i], nums_expected[i]);
//   }
// }
// END_TEST

START_TEST(multi_dec_bad_format) {
  const char *format = "%d1%d1%d1%d";
  const char *src = "15135 612 710 53";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

/* ANOMALY */

START_TEST(one_big_positive_dec) {
  const char *format = "%d";
  const char *src = "922337203685477584";  // LONG_MAX - 3

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_big_negative_dec) {
  const char *format = "%d";
  const char *src = "-922337203685477584";  // LONG_MIN + 3

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_int_dec_overflow) {
  const char *format = "%ld";
  const char *src = "2147483650";  // INT_MAX + 3

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_short_dec_overflow) {
  const char *format = "%hd";
  const char *src = "32763";  // SHRT_MAX + 3

  short num_actual = 0;
  short num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

// START_TEST(one_long_dec_overflow) {
//   const char *format = "%ld";
//   const char *src = "9223372036854775810";  // LONG_MAX + 3

//   long num_actual = 0;
//   long num_expected = -99;

//   ck_assert_int_eq(actual(src, format, &num_actual), expected(src, format,
//   &num_expected)); ck_assert_int_eq(num_actual, num_expected);
// }
// END_TEST

START_TEST(multi_zeros) {
  const char *format = "%d";
  const char *src = "0000000";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_not_dec) {
  const char *format = "%d";
  const char *src = "ff";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_mix_good_bad_src) {
  const char *format = "%d %d";
  const char *src = "999 f2";

  int nums_actual[] = {0, 1};
  int nums_expected[] = {-99, -99};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1]),
                   expected(src, format, &nums_expected[0], &nums_expected[1]));
  ck_assert_int_eq(nums_actual[0], nums_expected[0]);
  ck_assert_int_ne(nums_actual[1], nums_expected[1]);
}
END_TEST

START_TEST(bad_nums_0) {
  const char *format = "%d %d %d %d";
  const char *src = "++++15135_---612__+-0 +0";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {0, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(bad_nums_1) {
  const char *format = "%d %d %d %d";
  const char *src = "+15135_---612__+-0 +0";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_dec_big_width) {
  const char *format = "%100d %d %3d %d";
  const char *src = "424523 113 22 754";

  int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

Suite *suite_s21_sscanf_d() {
  Suite *suite = suite_create("suite_s21_sscanf_d");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, one_dec);
  tcase_add_test(normal_cases, one_negative_dec);
  tcase_add_test(normal_cases, one_positive_dec);
  tcase_add_test(normal_cases, one_dec_width);
  tcase_add_test(normal_cases, one_short_width);
  tcase_add_test(normal_cases, multi_dec);
  tcase_add_test(normal_cases, multi_dec_width);
  tcase_add_test(normal_cases, multi_sign_dec);
  tcase_add_test(normal_cases, multi_sign_dec_width);
  tcase_add_test(normal_cases, multi_types_dec);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, one_negative_zero);
  tcase_add_test(edge_cases, one_positive_zero);
  tcase_add_test(edge_cases, one_max_int_dec);
  tcase_add_test(edge_cases, one_min_int_dec);
  tcase_add_test(edge_cases, one_max_short_dec);
  tcase_add_test(edge_cases, one_max_long_dec);
  tcase_add_test(edge_cases, multi_sign_zeros_dec);
  tcase_add_test(edge_cases, multi_dec_good_format_0);
  tcase_add_test(edge_cases, multi_dec_good_format_1);
  tcase_add_test(edge_cases, multi_dec_good_format_2);
  // tcase_add_test(edge_cases, multi_dec_good_format_2_width);
  tcase_add_test(edge_cases, multi_dec_bad_format);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, one_big_positive_dec);
  tcase_add_test(anomaly_cases, one_big_negative_dec);
  tcase_add_test(anomaly_cases, one_short_dec_overflow);
  tcase_add_test(anomaly_cases, one_int_dec_overflow);
  // tcase_add_test(anomaly_cases, one_long_dec_overflow);
  tcase_add_test(anomaly_cases, multi_zeros);
  tcase_add_test(anomaly_cases, one_not_dec);
  tcase_add_test(anomaly_cases, one_mix_good_bad_src);
  tcase_add_test(anomaly_cases, bad_nums_0);
  tcase_add_test(anomaly_cases, bad_nums_1);
  tcase_add_test(anomaly_cases, multi_dec_big_width);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
