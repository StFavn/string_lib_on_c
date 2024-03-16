#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

/* NORMAL */

START_TEST(one_sci_g) {
  const char *format = "%g";
  const char *src = "3.14e3";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_sci_big_g) {
  const char *format = "%G";
  const char *src = "3.14e3";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_sci_g_e_minus) {
  const char *format = "%g";
  const char *src = "3.14e-3";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_sci_e) {
  const char *format = "%e";
  const char *src = "3.14e3";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_sci_big_e) {
  const char *format = "%E";
  const char *src = "3.14e3";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_sci_e_minus) {
  const char *format = "%e";
  const char *src = "3.14e-3";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_g_width) {
  const char *format = "%4g";
  const char *src = "0e-4555";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_e_width) {
  const char *format = "%4e";
  const char *src = "0e-4555";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_negative_g) {
  const char *format = "%g";
  const char *src = "-3.e-3";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_negative_e) {
  const char *format = "%e";
  const char *src = "-3.e-3";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

#define MULTI_FLOAT_ELEMS 4

START_TEST(multi_float_0) {
  const char *format = "%e %g %e %g";
  const char *src = "4.2 0.1e-5 3.22e7 7545.43524e-3";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_float_1) {
  const char *format = "%e %g %e %e";
  const char *src = "4. 0. 0.22 0.00001";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_float_width) {
  const char *format = "%1e %g %3g %e";
  const char *src = "4.2 0.1e3 3.22e-3 7545.43524";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_sign_float) {
  const char *format = "%e %g %e %g";
  const char *src = "+4.2e-4 -0.1e4 -3.22e-4 +7545.43524";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_sign_float_width) {
  const char *format = "%6e %6g %3e %4g";
  const char *src = "+4.2e356 -0.00144 +3.22 -7545.43524";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_types_float_width) {
  const char *format = "%5e %5Lg %g %12Le";
  const char *src = "4.e-46 23525332.523523523 1e-3 0.00000000000001";

  float f0_actual = 0;
  float f0_expected = 1;
  long double ld0_actual = 0;
  long double ld0_expected = 1;
  float f1_actual = 0;
  float f1_expected = 1;
  long double ld1_actual = 0;
  long double ld1_expected = 1;

  ck_assert_int_eq(
      actual(src, format, &f0_actual, &ld0_actual, &f1_actual, &ld1_actual),
      expected(src, format, &f0_expected, &ld0_expected, &f1_expected,
               &ld1_expected));

  ck_assert_double_eq(f0_actual, f0_expected);
  ck_assert_double_eq(ld0_actual, ld0_expected);
  ck_assert_double_eq(f1_actual, f1_expected);
  ck_assert_double_eq(ld1_actual, ld1_expected);
}
END_TEST

START_TEST(multi_types_float) {
  const char *format = "%e %Lg %e %Lg";
  const char *src = "4.e-7 23525332.523523523e4 1e3 1e-8";

  float f0_actual = 0;
  float f0_expected = 1;
  long double ld0_actual = 0;
  long double ld0_expected = 1;
  float f1_actual = 0;
  float f1_expected = 1;
  long double ld1_actual = 0;
  long double ld1_expected = 1;

  ck_assert_int_eq(
      actual(src, format, &f0_actual, &ld0_actual, &f1_actual, &ld1_actual),
      expected(src, format, &f0_expected, &ld0_expected, &f1_expected,
               &ld1_expected));

  ck_assert_double_eq(f0_actual, f0_expected);
  ck_assert_double_eq(ld0_actual, ld0_expected);
  ck_assert_double_eq(f1_actual, f1_expected);
  ck_assert_double_eq(ld1_actual, ld1_expected);
}
END_TEST

/* EDGE */

START_TEST(multi_sign_zeros_float) {
  const char *format = "%e %g %e %g";
  const char *src = "-0.1e-5 +42.6654e4 +0.0001e4 -11.1e-4";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_float_good_format_0) {
  const char *format = "%e_%g_%e_%g";
  const char *src = "151.35e3_614.42e-4_1e-5_1e5";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_float_good_format_1) {
  const char *format = "%e_%g__%e %g";
  const char *src = "151.35e3_614.42e-4_1e-5_1e5";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(nan_float_0) {
  const char *format = "%e %g %3e %4g";
  const char *src = "nan NaN NAN -nAn";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_nan(nums_expected[i]);
    ck_assert_double_nan(nums_actual[i]);
  }
}
END_TEST

/* ANOMALY */

START_TEST(one_big_positive_float) {
  const char *format = "%e";
  const char *src = "1e32";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_big_positive_double) {
  const char *format = "%Lg";
  const char *src = "1e32";

  double num_actual = 0;
  double num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_big_negative_float) {
  const char *format = "%e";
  const char *src = "-1e32";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_not_float_0) {
  const char *format = "%e";
  const char *src = "e";

  float num_actual = 2.44;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_ne(num_actual, num_expected);
}
END_TEST

START_TEST(one_not_float_1) {
  const char *format = "%e";
  const char *src = "e-1";

  float num_actual = 2.44;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_ne(num_actual, num_expected);
}
END_TEST

START_TEST(one_mix_good_bad_src) {
  const char *format = "%e %g";
  const char *src = "12.353e4 f2";

  float nums_actual[] = {0, 2.67};
  float nums_expected[] = {-3.14, 3.14};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1]),
                   expected(src, format, &nums_expected[0], &nums_expected[1]));
  ck_assert_double_eq(nums_actual[0], nums_expected[0]);
  ck_assert_double_ne(nums_actual[1], nums_expected[1]);
}
END_TEST

START_TEST(multi_float_bad_format) {
  const char *format = "%e1%g1%e1%g";
  const char *src = "-151.3425 +614.42 -710 +0.1";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(one_bad_num) {
  const char *format = "%e";
  const char *src = "13..4...5";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(bad_nums_0) {
  const char *format = "%e %g %e %g";
  const char *src = "++++1e-2 ---61.2e5__0.e-4.4 ..9..";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_float_only_dots) {
  const char *format = "%e %g %e %g";
  const char *src = ". . . .";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_float_sign_dots) {
  const char *format = "%e %g %e %g";
  const char *src = "+. -. +. -.";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(multi_float_only_sci) {
  const char *format = "%e %g %e %g";
  const char *src = "e-1 e2 e ee";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_double_eq(nums_actual[i], nums_expected[i]);
  }
}
END_TEST

START_TEST(one_big_positive_double_big_width) {
  const char *format = "%100Le";
  const char *src = "123456789123456789.123456789";

  double num_actual = 0;
  double num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(only_sci_float) {
  const char *format = "%g";
  const char *src = "e-2";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_ne(num_actual, num_expected);
}

Suite *suite_s21_sscanf_eg() {
  Suite *suite = suite_create("suite_s21_sscanf_eg");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, one_sci_g);
  tcase_add_test(normal_cases, one_sci_big_g);
  tcase_add_test(normal_cases, one_sci_g_e_minus);
  tcase_add_test(normal_cases, one_sci_e);
  tcase_add_test(normal_cases, one_sci_big_e);
  tcase_add_test(normal_cases, one_sci_e_minus);
  tcase_add_test(normal_cases, one_g_width);
  tcase_add_test(normal_cases, one_e_width);
  tcase_add_test(normal_cases, one_negative_g);
  tcase_add_test(normal_cases, one_negative_e);
  tcase_add_test(normal_cases, one_negative_g);
  tcase_add_test(normal_cases, multi_float_0);
  tcase_add_test(normal_cases, multi_float_1);
  tcase_add_test(normal_cases, multi_float_width);
  tcase_add_test(normal_cases, multi_types_float);
  tcase_add_test(normal_cases, multi_sign_float);
  tcase_add_test(normal_cases, multi_sign_float_width);
  tcase_add_test(normal_cases, multi_types_float_width);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, multi_sign_zeros_float);
  tcase_add_test(edge_cases, multi_float_good_format_0);
  tcase_add_test(edge_cases, multi_float_good_format_1);
  tcase_add_test(edge_cases, nan_float_0);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, one_big_positive_float);
  tcase_add_test(anomaly_cases, one_big_positive_double);
  tcase_add_test(anomaly_cases, one_big_negative_float);
  tcase_add_test(anomaly_cases, one_not_float_0);
  tcase_add_test(anomaly_cases, one_not_float_1);
  tcase_add_test(anomaly_cases, one_mix_good_bad_src);
  tcase_add_test(anomaly_cases, multi_float_bad_format);
  tcase_add_test(anomaly_cases, one_bad_num);
  tcase_add_test(anomaly_cases, bad_nums_0);
  tcase_add_test(anomaly_cases, multi_float_only_dots);
  tcase_add_test(anomaly_cases, multi_float_sign_dots);
  tcase_add_test(anomaly_cases, one_big_positive_double_big_width);
  tcase_add_test(anomaly_cases, only_sci_float);
  tcase_add_test(anomaly_cases, multi_float_only_sci);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
