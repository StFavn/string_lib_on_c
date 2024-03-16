#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

/* NORMAL */

START_TEST(one_dec) {
  const char *format = "%i";
  const char *src = "123";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_hex) {
  const char *format = "%i";
  const char *src = "0xff";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_oct) {
  const char *format = "%i";
  const char *src = "0123";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_hex_width) {
  const char *format = "%4i";
  const char *src = "0xfa123";

  int num_actual = 0;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_short_width) {
  const char *format = "%hi";
  const char *src = "017";

  short num_actual = 0;
  short num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

#define MULTI_NUMS_ELEMS 4

START_TEST(multi_nums) {
  const char *format = "%i %i %i %i";
  const char *src = "123 0xa1bc 0X12bd 01246";

  int nums_actual[MULTI_NUMS_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_NUMS_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_NUMS_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_nums_width) {
  const char *format = "%1i %3i %3i %8i";
  const char *src = "123 0xa1bc 01245 0X124";

  int nums_actual[MULTI_NUMS_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_NUMS_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_NUMS_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_sign_nums) {
  const char *format = "%2i %4i %4i %8i";
  const char *src = "-123 -0xa1bc -01245 +0X124";

  int nums_actual[MULTI_NUMS_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_NUMS_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_NUMS_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_types_nums) {
  const char *format = "%i %li %hi %i";
  const char *src = "-123 +0x1c1 -0xFF -0564";

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

START_TEST(multi_hex_good_format_0) {
  const char *format = "%i_%i_%i_%i";
  const char *src = "0xfff_123_0710_0x53ac1";

  int nums_actual[MULTI_NUMS_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_NUMS_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_NUMS_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_hex_good_format_1) {
  const char *format = "%i_%i_%i_%i";
  const char *src = "-0xfff_-123_+0710_+0x53ac1";

  int nums_actual[MULTI_NUMS_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_NUMS_ELEMS] = {1, 1, 1, 1};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_NUMS_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

/* ANOMALY */

START_TEST(one_not_num_0) {
  const char *format = "%i";
  const char *src = "hello!";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_not_num_1) {
  const char *format = "%i";
  const char *src = "0xhello!";

  int num_actual = -99;
  int num_expected = -99;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_int_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_mix_good_bad_src) {
  const char *format = "%i %i %i";
  const char *src = "13 0xvvv 0999";

  int nums_actual[] = {0, 0, 0};
  int nums_expected[] = {-99, -99, -99};

  ck_assert_int_eq(
      actual(src, format, &nums_actual[0], &nums_actual[1], &nums_actual[2]),
      expected(src, format, &nums_expected[0], &nums_expected[1],
               &nums_expected[2]));
  ck_assert_int_eq(nums_actual[0], nums_expected[0]);
  ck_assert_int_eq(nums_actual[1], nums_expected[1]);
  ck_assert_int_ne(nums_actual[2], nums_expected[2]);
}
END_TEST

START_TEST(bad_nums_0) {
  const char *format = "%i %i %i %i";
  const char *src = "++++0xff_---13__+-034 +1";

  int nums_actual[MULTI_NUMS_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_NUMS_ELEMS] = {0, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_NUMS_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(bad_nums_1) {
  const char *format = "%i %i %i %i";
  const char *src = "+0x24f nnn2 0789 0";

  int nums_actual[MULTI_NUMS_ELEMS] = {0, 0, 0, 0};
  int nums_expected[MULTI_NUMS_ELEMS] = {1, 0, 0, 0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_NUMS_ELEMS; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

Suite *suite_s21_sscanf_i() {
  Suite *suite = suite_create("suite_s21_sscanf_i");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, one_dec);
  tcase_add_test(normal_cases, one_hex);
  tcase_add_test(normal_cases, one_oct);
  tcase_add_test(normal_cases, one_hex_width);
  tcase_add_test(normal_cases, one_short_width);
  tcase_add_test(normal_cases, multi_nums);
  tcase_add_test(normal_cases, multi_nums_width);
  tcase_add_test(normal_cases, multi_sign_nums);
  tcase_add_test(normal_cases, multi_types_nums);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, multi_hex_good_format_0);
  tcase_add_test(edge_cases, multi_hex_good_format_1);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, one_not_num_0);
  tcase_add_test(anomaly_cases, one_not_num_1);
  tcase_add_test(anomaly_cases, one_mix_good_bad_src);
  tcase_add_test(anomaly_cases, bad_nums_0);
  tcase_add_test(anomaly_cases, bad_nums_1);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
