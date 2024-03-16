#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

/* NORMAL */

START_TEST(one_hex) {
  const char *format = "%x";
  const char *src = "12abc";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_bigX_hex) {
  const char *format = "%X";
  const char *src = "12ABC";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_negative_hex) {
  const char *format = "%x";
  const char *src = "-ff";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_positive_hex) {
  const char *format = "%x";
  const char *src = "+ff";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_hex_width) {
  const char *format = "%2x";
  const char *src = "fa123";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_short_width) {
  const char *format = "%2hx";
  const char *src = "abcdef";

  short num_actual = 0;
  short num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

#define MULTI_HEX_ELEMS 4

START_TEST(multi_hex) {
  const char *format = "%x %x %x %x";
  const char *src = "abc 0xa1bc 0X12bd ABC12";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_hex_width) {
  const char *format = "%1x %x %3x %x";
  const char *src = "abc 0xa1bc 0X12bd ABC12";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_sign_hex) {
  const char *format = "%x %x %x %x";
  const char *src = "-abc +1c1 -0xFF -1Fc2";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_sign_hex_width) {
  const char *format = "%2x %2x %2x %2x";
  const char *src = "-abc +1c1 -0xFF -1Fc2";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_types_hex) {
  const char *format = "%x %lx %hx %x";
  const char *src = "-abc +1c1 -0xFF -1Fc2";

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
  const char *format = "%x";
  const char *src = "-0";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_positive_zero) {
  const char *format = "%x";
  const char *src = "+0";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_max_int_hex) {
  const char *format = "%x";
  const char *src = "7FFFFFFF";  // INT_MAX

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(num_actual, INT_MAX);
}
END_TEST

START_TEST(one_min_int_hex) {
  const char *format = "%x";
  const char *src = "-80000000";  // INT_MIN

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(num_actual, INT_MIN);
}
END_TEST

START_TEST(one_max_short_hex) {
  const char *format = "%hx";
  const char *src = "7FFF";  // SHRT_MAX

  short num_actual = 0;
  short num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(num_actual, SHRT_MAX);
}
END_TEST

START_TEST(one_max_long_hex) {
  const char *format = "%lx";
  const char *src = "7FFFFFFFFFFFFFFF";  // LONG_MAX

  long num_actual = 0;
  long num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(num_actual, LONG_MAX);
}
END_TEST

START_TEST(multi_sign_zeros_hex) {
  const char *format = "%x %x %x %x";
  const char *src = "-0x0 +42 +0x0 -111";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_hex_good_format_0) {
  const char *format = "%x_%x_%x_%x";
  const char *src = "fff_AA_0xb710_53ac1";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_hex_good_format_1) {
  const char *format = "%x_%x_%x_%x";
  const char *src = "+fff_-AA_+0xb710_53ac1";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_hex_good_format_2) {
  const char *format = "%x_%x__%x %x";
  const char *src = "+0Xd5135_-6a2__-f1 +0x0";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

// // START_TEST(multi_dec_good_format_2_width) {
// //   const char *format = "%5d_%2d__%4d %1d";
// //   const char *src = "+15135_-612__-0 +0";

// //   int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
// //   int nums_expected[MULTI_HEX_ELEMS]  = {1, 1, 1, 1};

// //   ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
// &nums_actual[2], &nums_actual[3]),
// //                    expected(src, format, &nums_expected[0],
// &nums_expected[1], &nums_expected[2], &nums_expected[3]));

// //   for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
// //     ck_assert_int_eq(nums_actual[i], nums_expected[i]);
// //   }
// // }
// // END_TEST

START_TEST(multi_hex_bad_format) {
  const char *format = "%x1%x1%x1%x";
  const char *src = "ffac 612 710 53";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

/* ANOMALY */

START_TEST(one_big_positive_hex) {
  const char *format = "%x";
  const char *src = "CCCCCCCCCCCCCD0";  // LONG_MAX - 3

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_big_negative_hex) {
  const char *format = "%x";
  const char *src = "-CCCCCCCCCCCCCD0";  // LONG_MIN + 3

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_int_hex_overflow) {
  const char *format = "%lx";
  const char *src = "80000002";  // INT_MAX + 3

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_not_hex_0) {
  const char *format = "%x";
  const char *src = "hello!";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_not_hex_1) {
  const char *format = "%x";
  const char *src = "0xhello!";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(only_pref_small) {
  const char *format = "%x";
  const char *src0 = "0x";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src0, format, &num_actual),
                   expected(src0, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(only_pref_big) {
  const char *format = "%x";
  const char *src0 = "0X";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src0, format, &num_actual),
                   expected(src0, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(only_pref_width) {
  const char *format = "%1x";
  const char *src0 = "0x";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src0, format, &num_actual),
                   expected(src0, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_mix_good_bad_src) {
  const char *format = "%x %x";
  const char *src = "fab1 vvv";

  int nums_actual[] = {0, 1};
  int nums_expected[] = {-99, -99};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1]),
                   expected(src, format, &nums_expected[0], &nums_expected[1]));
  ck_assert_int_eq(nums_actual[0], nums_expected[0]);
  ck_assert_int_ne(nums_actual[1], nums_expected[1]);
}
END_TEST

START_TEST(bad_nums_0) {
  const char *format = "%x %x %x %x";
  const char *src = "++++ff_---a1__+-b1 +c1";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {0, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(bad_nums_1) {
  const char *format = "%d %d %d %d";
  const char *src = "+0x24f_---nnn2__+-0 +0";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_hex_big_width) {
  const char *format = "%100x %x %3x %x";
  const char *src = "ffff4 1f13 0x2a 754";

  int nums_actual[MULTI_HEX_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_HEX_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_HEX_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(sign_width) {
  const char *format = "%1x";
  const char *src = "-1";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

Suite *suite_s21_sscanf_x() {
  Suite *suite = suite_create("suite_s21_sscanf_x");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, one_hex);
  tcase_add_test(normal_cases, one_bigX_hex);
  tcase_add_test(normal_cases, one_negative_hex);
  tcase_add_test(normal_cases, one_positive_hex);
  tcase_add_test(normal_cases, one_hex_width);
  tcase_add_test(normal_cases, one_short_width);
  tcase_add_test(normal_cases, multi_hex);
  tcase_add_test(normal_cases, multi_hex_width);
  tcase_add_test(normal_cases, multi_sign_hex);
  tcase_add_test(normal_cases, multi_sign_hex_width);
  tcase_add_test(normal_cases, multi_types_hex);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, one_negative_zero);
  tcase_add_test(edge_cases, one_positive_zero);
  tcase_add_test(edge_cases, one_max_int_hex);
  tcase_add_test(edge_cases, one_min_int_hex);
  tcase_add_test(edge_cases, one_max_short_hex);
  tcase_add_test(edge_cases, one_max_long_hex);
  tcase_add_test(edge_cases, multi_sign_zeros_hex);
  tcase_add_test(edge_cases, multi_hex_good_format_0);
  tcase_add_test(edge_cases, multi_hex_good_format_1);
  tcase_add_test(edge_cases, multi_hex_good_format_2);
  tcase_add_test(edge_cases, multi_hex_bad_format);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, one_big_positive_hex);
  tcase_add_test(anomaly_cases, one_big_negative_hex);
  tcase_add_test(anomaly_cases, one_int_hex_overflow);
  tcase_add_test(anomaly_cases, one_not_hex_0);
  tcase_add_test(anomaly_cases, one_not_hex_1);
  tcase_add_test(anomaly_cases, only_pref_big);
  tcase_add_test(anomaly_cases, only_pref_small);
  tcase_add_test(anomaly_cases, only_pref_width);
  tcase_add_test(anomaly_cases, one_mix_good_bad_src);
  tcase_add_test(anomaly_cases, bad_nums_0);
  tcase_add_test(anomaly_cases, bad_nums_1);
  tcase_add_test(anomaly_cases, multi_hex_big_width);
  tcase_add_test(anomaly_cases, sign_width);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
