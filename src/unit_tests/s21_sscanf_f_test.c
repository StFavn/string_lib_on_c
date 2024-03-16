#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

/* NORMAL */

START_TEST(one_float_0) {
  const char *format = "%f";
  const char *src = "3.14159265359";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_float_1) {
  const char *format = "%f";
  const char *src = "3";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_sci_float) {
  const char *format = "%f";
  const char *src = "3e-2";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}

START_TEST(one_float_width) {
  const char *format = "%3f";
  const char *src = "3.14159265359";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_negative_float) {
  const char *format = "%f";
  const char *src = "-3.14159265359";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_positive_float) {
  const char *format = "%f";
  const char *src = "+3.14159265359";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

#define MULTI_FLOAT_ELEMS 4

START_TEST(multi_float_0) {
  const char *format = "%f %f %f %f";
  const char *src = "4.2 0.1 3.22 7545.43524";

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
  const char *format = "%f %f %f %f";
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
  const char *format = "%1f %f %3f %f";
  const char *src = "4.2 0.1 3.22 7545.43524";

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
  const char *format = "%f %f %f %f";
  const char *src = "+4.2 -0.1 -3.22 +7545.43524";

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
  const char *format = "%f %6f %3f %4f";
  const char *src = "+4.2 -0.0001 3.22 -7545.43524";

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

START_TEST(multi_sci_float) {
  const char *format = "%f %f %f %f";
  const char *src = "4e5 0.e3 0.22e-4 0.00001e10";

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

START_TEST(multi_sci_float_sign) {
  const char *format = "%f %f %f %f";
  const char *src = "+4e5 -0.e3 -0.22e-4 +0.00001e10";

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

START_TEST(multi_sci_float_width) {
  const char *format = "%1f %2f %4f %8f";
  const char *src = "4e5 0.e3 0.22e-4 0.00001e10";

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
  const char *format = "%2f %Lf %f %12Lf";
  const char *src = "4. 23525332.523523523 0. 0.00000000000001";

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
  const char *format = "%f %Lf %f %Lf";
  const char *src = "4. 23525332.523523523 0. 0.00000000000001";

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

START_TEST(nan_float_0) {
  const char *format = "%f %f %f %f";
  const char *src = "nan NaN NAN nAn";

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

START_TEST(nan_float_1) {
  const char *format = "%f %f %f %f";
  const char *src = "+nan -NaN +NAN -nAn";

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

START_TEST(nan_float_2) {
  const char *format = "%f %f %f %f";
  const char *src = "3.4156 +NaN +1e-5 +nAn";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  ck_assert_double_eq(nums_actual[0], nums_expected[0]);

  ck_assert_double_nan(nums_expected[1]);
  ck_assert_double_nan(nums_actual[1]);

  ck_assert_double_eq(nums_actual[2], nums_expected[2]);

  ck_assert_double_nan(nums_expected[3]);
  ck_assert_double_nan(nums_actual[3]);
}
END_TEST

START_TEST(inf_float_0) {
  const char *format = "%f %f %f %f";
  const char *src = "inf InF INF iNf";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_float_infinite(nums_expected[i]);
    ck_assert_float_infinite(nums_actual[i]);
  }
}
END_TEST

START_TEST(inf_float_1) {
  const char *format = "%f %f %f %f";
  const char *src = "+inf -InF +INF -iNf";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  for (size_t i = 0; i < MULTI_FLOAT_ELEMS; i++) {
    ck_assert_float_infinite(nums_expected[i]);
    ck_assert_float_infinite(nums_actual[i]);
  }
}
END_TEST

START_TEST(inf_float_2) {
  const char *format = "%f %f %f %f";
  const char *src = "3.4156 +InF +1e-5 +iNf";

  float nums_actual[MULTI_FLOAT_ELEMS] = {0};
  float nums_expected[MULTI_FLOAT_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1],
                          &nums_actual[2], &nums_actual[3]),
                   expected(src, format, &nums_expected[0], &nums_expected[1],
                            &nums_expected[2], &nums_expected[3]));

  ck_assert_double_eq(nums_actual[0], nums_expected[0]);

  ck_assert_float_infinite(nums_expected[1]);
  ck_assert_float_infinite(nums_actual[1]);

  ck_assert_double_eq(nums_actual[2], nums_expected[2]);

  ck_assert_float_infinite(nums_expected[3]);
  ck_assert_float_infinite(nums_actual[3]);
}
END_TEST

START_TEST(one_negative_zero) {
  const char *format = "%f";
  const char *src = "-0";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_positive_zero) {
  const char *format = "%f";
  const char *src = "+0";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(multi_sign_zeros_float) {
  const char *format = "%f %f %f %f";
  const char *src = "-0.0 +42.6654 +0.0 -11.1";

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

START_TEST(one_float_medium_width) {
  const char *format = "%7f";
  const char *src = "3.14159265359";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(multi_float_good_format_0) {
  const char *format = "%f_%f_%f_%f";
  const char *src = "151.35_614.42_710_5.3";

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
  const char *format = "%f_%f_%f_%f";
  const char *src = "-151.35_+614.42_-710_+5.3";

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

START_TEST(multi_float_good_format_2) {
  const char *format = "%f_%f__%f %f";
  const char *src = "-151.3425_+614.42__-710_+0.1";

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

/* ANOMALY */

START_TEST(one_big_positive_float) {
  const char *format = "%f";
  const char *src = "123456789123456789.123456789";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_big_positive_double) {
  const char *format = "%Lf";
  const char *src = "123456789123456789.123456789";

  double num_actual = 0;
  double num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_big_negative_float) {
  const char *format = "%f";
  const char *src = "-123456789123456789.123456789";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_not_float) {
  const char *format = "%f";
  const char *src = "ff";

  float num_actual = -2.44;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(one_mix_good_bad_src) {
  const char *format = "%f %f";
  const char *src = "12.353 f2";

  float nums_actual[] = {0, 2.67};
  float nums_expected[] = {-3.14, 3.14};

  ck_assert_int_eq(actual(src, format, &nums_actual[0], &nums_actual[1]),
                   expected(src, format, &nums_expected[0], &nums_expected[1]));
  ck_assert_double_eq(nums_actual[0], nums_expected[0]);
  ck_assert_double_ne(nums_actual[1], nums_expected[1]);
}
END_TEST

START_TEST(multi_float_bad_format) {
  const char *format = "%f1%f1%f1%f";
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
  const char *format = "%f";
  const char *src = "13..4...5";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(bad_nums_0) {
  const char *format = "%f %f %f %f";
  const char *src = "++++151.35 ---61.2__0..4 ..9..";

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

START_TEST(bad_nums_1) {
  const char *format = "%f %f %f %f";
  const char *src = "+15135_---612__+-0 +0";

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

START_TEST(bad_nan) {
  const char *format = "%2f %f %f %f";
  const char *src = "nan NfaN 1NAN non";

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

START_TEST(bad_inf) {
  const char *format = "%2f %f %f %f";
  const char *src = "inf NfaN hello iof";

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
  const char *format = "%f %f %f %f";
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
  const char *format = "%f %f %f %f";
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

START_TEST(one_big_positive_double_big_width) {
  const char *format = "%100Lf";
  const char *src = "123456789123456789.123456789";

  double num_actual = 0;
  double num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_eq(num_actual, num_expected);
}
END_TEST

START_TEST(only_sci_float) {
  const char *format = "%f";
  const char *src = "e-2";

  float num_actual = 0;
  float num_expected = -2.44;

  ck_assert_int_eq(actual(src, format, &num_actual),
                   expected(src, format, &num_expected));
  ck_assert_double_ne(num_actual, num_expected);
}

Suite *suite_s21_sscanf_f() {
  Suite *suite = suite_create("suite_s21_sscanf_f");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, one_float_0);
  tcase_add_test(normal_cases, one_float_1);
  tcase_add_test(normal_cases, one_sci_float);
  tcase_add_test(normal_cases, multi_sci_float);
  tcase_add_test(normal_cases, multi_sci_float_sign);
  tcase_add_test(normal_cases, multi_sci_float_width);
  tcase_add_test(normal_cases, one_float_width);
  tcase_add_test(normal_cases, one_negative_float);
  tcase_add_test(normal_cases, one_positive_float);
  tcase_add_test(normal_cases, multi_float_0);
  tcase_add_test(normal_cases, multi_float_1);
  tcase_add_test(normal_cases, multi_float_width);
  tcase_add_test(normal_cases, multi_types_float);
  tcase_add_test(normal_cases, multi_sign_float);
  tcase_add_test(normal_cases, multi_sign_float_width);
  tcase_add_test(normal_cases, multi_types_float_width);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, nan_float_0);
  tcase_add_test(edge_cases, nan_float_1);
  tcase_add_test(edge_cases, nan_float_2);
  tcase_add_test(edge_cases, inf_float_0);
  tcase_add_test(edge_cases, inf_float_1);
  tcase_add_test(edge_cases, inf_float_2);
  tcase_add_test(edge_cases, one_negative_zero);
  tcase_add_test(edge_cases, one_positive_zero);
  tcase_add_test(edge_cases, one_float_medium_width);
  tcase_add_test(edge_cases, multi_sign_zeros_float);
  tcase_add_test(edge_cases, multi_float_good_format_0);
  tcase_add_test(edge_cases, multi_float_good_format_1);
  tcase_add_test(edge_cases, multi_float_good_format_2);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, one_big_positive_float);
  tcase_add_test(anomaly_cases, one_big_positive_double);
  tcase_add_test(anomaly_cases, one_big_negative_float);
  tcase_add_test(anomaly_cases, one_not_float);
  tcase_add_test(anomaly_cases, one_mix_good_bad_src);
  tcase_add_test(anomaly_cases, multi_float_bad_format);
  tcase_add_test(anomaly_cases, one_bad_num);
  tcase_add_test(anomaly_cases, bad_nums_0);
  tcase_add_test(anomaly_cases, bad_nums_1);
  tcase_add_test(anomaly_cases, bad_nan);
  tcase_add_test(anomaly_cases, bad_inf);
  tcase_add_test(anomaly_cases, multi_float_only_dots);
  tcase_add_test(anomaly_cases, multi_float_sign_dots);
  tcase_add_test(anomaly_cases, one_big_positive_double_big_width);
  tcase_add_test(anomaly_cases, only_sci_float);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
