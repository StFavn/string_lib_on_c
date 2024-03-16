#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

/* NORMAL */

START_TEST(one_udec) {
  const char *format = "%u";
  const char *src = "42";

  unsigned int num_actual = 0;
  unsigned int num_expected = 1;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_positive_dec) {
  const char *format = "%u";
  const char *src = "+42";

  unsigned int num_actual = 0;
  unsigned int num_expected = 0;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_udec_width) {
  const char *format = "%2u";
  const char *src = "12345";

  unsigned int num_actual = 0;
  unsigned int num_expected = 1;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_short_width) {
  const char *format = "%2hu";
  const char *src = "12345";

  unsigned short num_actual = 0;
  unsigned short num_expected = 1;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
}
END_TEST

#define MULTI_DEC_ELEMS 4

START_TEST(multi_dec) {
  const char *format = "%u %u %u %u";
  const char *src = "42 11 22 754";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_types_dec) {
  const char *format = "%u %lu %hu %u";
  const char *src = "42 11 22 754";

  unsigned int d0_actual = 0;
  unsigned int d0_expected = 1;
  unsigned long l0_actual = 0;
  unsigned long l0_expected = 1;
  unsigned short si0_actual = 0;
  unsigned short si0_expected = 1;
  unsigned int d1_actual = 0;
  unsigned int d1_expected = 1;

  ck_assert_int_eq(
      actual(src, format, &d0_actual, &l0_actual, &si0_actual, &d1_actual),
      expected(src, format, &d0_expected, &l0_expected, &si0_expected,
               &d1_expected));

  ck_assert_uint_eq(d0_actual, d0_expected);
  ck_assert_uint_eq(l0_actual, l0_expected);
  ck_assert_uint_eq(si0_actual, si0_expected);
  ck_assert_uint_eq(d1_actual, d1_expected);
}
END_TEST

START_TEST(multi_dec_width) {
  const char *format = "%1u %u %3u %u";
  const char *src = "42 11553 225564 754";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

/* EDGE */

START_TEST(one_positive_zero) {
  const char *format = "%u";
  const char *src = "+0";

  unsigned int num_actual = 0;
  unsigned int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_max_int) {
  const char *format = "%u";
  const char *src = "2147483650";  // INT_MAX + 3

  unsigned int num_actual = 0;
  unsigned int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
  ck_assert_uint_eq(num_actual, 2147483650);
}
END_TEST

START_TEST(one_max_short_dec) {
  const char *format = "%hu";
  const char *src = "32770";  // SHRT_MAX + 3

  unsigned short num_actual = 0;
  unsigned short num_expected = 99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
  ck_assert_uint_eq(num_actual, 32770);
}
END_TEST

// START_TEST(one_max_long_dec) {
//   const char *format = "%lu";
//   const char *src = "9223372036854775810";  // LONG_MAX + 3

//   unsigned long num_actual = 0;
//   unsigned long num_expected = 99;

//   ck_assert_int_eq(actual(src, format, &num_actual), expected(src, format,
//   &num_expected)); ck_assert_uint_eq(num_actual, num_expected);
//   // #NOTE - Too large constant
//   // ck_assert_uint_eq(num_actual, 9223372036854775810);
// }
// END_TEST

START_TEST(multi_dec_good_format_0) {
  const char *format = "%u_%u_%u_%u";
  const char *src = "15135_612_710_53";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_dec_bad_format_0) {
  const char *format = "%u1%u1%u1%u";
  const char *src = "15135 612 710 53";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_dec_bad_format_1) {
  const char *format = "%u__%u__%u__%u";
  const char *src = "15135 612 710 53";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

/* ANOMALY */

START_TEST(one_negative_dec) {
  const char *format = "%u";
  const char *src = "-42";

  unsigned int num_actual = 0;
  unsigned int num_expected = 1;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
}
END_TEST

START_TEST(multi_sign_dec) {
  const char *format = "%u %u %u";
  const char *src = "-42 +11 -22";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 0};

  ck_assert_int_eq(
      actual(src, format, &nums_actual[0], &nums_actual[1], &nums_actual[2]),
      expected(src, format, &nums_expected[0], &nums_expected[1],
               &nums_expected[2]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_sign_dec_width) {
  const char *format = "%2u %2u %2u";
  const char *src = "-423 +11 -22";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 0};

  ck_assert_int_eq(
      actual(src, format, &nums_actual[0], &nums_actual[1], &nums_actual[2]),
      expected(src, format, &nums_expected[0], &nums_expected[1],
               &nums_expected[2]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(one_negative_zero) {
  const char *format = "%u";
  const char *src = "-0";

  unsigned int num_actual = 0;
  unsigned int num_expected = 1;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
}
END_TEST

START_TEST(multi_sign_zeros_dec) {
  const char *format = "%u %u %u %u";
  const char *src = "-0 +42 +0 -111";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(uint_overflow) {
  const char *format = "%u";
  const char *src = "214748364900";  // UINT_MAX + n

  unsigned int num_actual = 0;
  unsigned int num_expected = 99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_not_dec) {
  const char *format = "%u";
  const char *src = "ff";

  unsigned int num_actual = 0;
  unsigned int num_expected = 99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_uint_ne(num_actual, num_expected);
}
END_TEST

START_TEST(one_mix_good_bad_src) {
  const char *format = "%u %u";
  const char *src = "123 f2";

  unsigned int nums_actual[] = {0, 1};
  unsigned int nums_expected[] = {22, 22};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1]),
                   expected(src, format, &nums_expected[0], &nums_expected[1]));
  ck_assert_uint_eq(nums_actual[0], nums_expected[0]);
  ck_assert_uint_ne(nums_actual[1], nums_expected[1]);
}
END_TEST

START_TEST(multi_dec_good_format_1) {
  const char *format = "%u_%u_%u_%u";
  const char *src = "+15135_-612_-0_+0";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_dec_good_format_2) {
  const char *format = "%u_%u__%u %u";
  const char *src = "+15135_-612__-0 +0";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(bad_nums_0) {
  const char *format = "%u %u %u %u";
  const char *src = "++++15135_---612__+-0 +0";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {0, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(bad_nums_1) {
  const char *format = "%u %u %u %u";
  const char *src = "+15135_---612__+-0 +0";

  unsigned int nums_actual[MULTI_DEC_ELEMS] = {0, 0, 0, 0};
  unsigned int nums_expected[MULTI_DEC_ELEMS] = {0, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_DEC_ELEMS; i++) {
    ck_assert_uint_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

// #NOTE - very-very big nums, which crash atoi() func's.
// START_TEST(one_big_positive_dec) {
//   const char *format = "%u";
//   const char *src = "123456789123456789123456789";

//   unsigned int num_actual = 0;
//   unsigned int num_expected = -99;

//   ck_assert_int_eq(actual(src, format, &num_actual), expected(src, format,
//   &num_expected)); ck_assert_uint_eq(num_actual, num_expected);
// }
// END_TEST

// START_TEST(one_big_negative_dec) {
//   const char *format = "%u";
//   const char *src = "-123456789123456789123456789";

//   unsigned int num_actual = 0;
//   unsigned int num_expected = -99;

//   ck_assert_int_eq(actual(src, format, &num_actual), expected(src, format,
//   &num_expected)); ck_assert_uint_eq(num_actual, num_expected);
// }
// END_TEST

Suite *suite_s21_sscanf_u() {
  Suite *suite = suite_create("suite_s21_sscanf_u");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, one_udec);
  tcase_add_test(normal_cases, one_positive_dec);
  tcase_add_test(normal_cases, one_udec_width);
  tcase_add_test(normal_cases, one_short_width);
  tcase_add_test(normal_cases, multi_dec);
  tcase_add_test(normal_cases, multi_types_dec);
  tcase_add_test(normal_cases, multi_dec_width);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, one_positive_zero);
  tcase_add_test(edge_cases, one_max_int);
  tcase_add_test(edge_cases, one_max_short_dec);
  // tcase_add_test(edge_cases, one_max_long_dec);
  tcase_add_test(edge_cases, multi_sign_zeros_dec);
  tcase_add_test(edge_cases, multi_dec_good_format_0);
  tcase_add_test(edge_cases, multi_dec_bad_format_0);
  tcase_add_test(edge_cases, multi_dec_bad_format_1);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, one_negative_dec);
  tcase_add_test(anomaly_cases, one_negative_zero);
  tcase_add_test(anomaly_cases, multi_sign_dec);
  tcase_add_test(anomaly_cases, multi_sign_dec_width);
  tcase_add_test(anomaly_cases, uint_overflow);
  // tcase_add_test(anomaly_cases, one_big_positive_dec);
  // tcase_add_test(anomaly_cases, one_big_negative_dec);
  tcase_add_test(anomaly_cases, one_not_dec);
  tcase_add_test(anomaly_cases, one_mix_good_bad_src);
  tcase_add_test(anomaly_cases, multi_dec_good_format_1);
  tcase_add_test(anomaly_cases, multi_dec_good_format_2);
  tcase_add_test(anomaly_cases, bad_nums_0);
  tcase_add_test(anomaly_cases, bad_nums_1);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
