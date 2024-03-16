#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

/* NORMAL */

START_TEST(one_char) {
  const char *format = "%c";
  const char *src = "f";

  char ch_actual = 0;
  char ch_expected = -1;

  ck_assert_int_eq(actual(src, format, &ch_actual),
                   expected(src, format, &ch_expected));
  ck_assert_int_eq(ch_actual, ch_expected);
}
END_TEST

#define MULTI_CHAR_ELEMS 4

START_TEST(multi_char) {
  const char *format = "%c %c %c %c";
  const char *src = "a 1 2 d";

  char chars_actual[MULTI_CHAR_ELEMS] = {0};
  char chars_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chars_actual[0], &chars_actual[1],
                          &chars_actual[2], &chars_actual[3]),
                   expected(src, format, &chars_expected[0], &chars_expected[1],
                            &chars_expected[2], &chars_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chars_actual[i], chars_expected[i]);
  }
}
END_TEST

START_TEST(multi_char_screen) {
  const char *format = "%c %c %c %c";
  const char *src = "\n \t \t \\";

  char chars_actual[MULTI_CHAR_ELEMS] = {0};
  char chars_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chars_actual[0], &chars_actual[1],
                          &chars_actual[2], &chars_actual[3]),
                   expected(src, format, &chars_expected[0], &chars_expected[1],
                            &chars_expected[2], &chars_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chars_actual[i], chars_expected[i]);
  }
}
END_TEST

START_TEST(multi_char_mix) {
  const char *format = "%c %c %c %c";
  const char *src = "\n 1 \t 7";

  char chars_actual[MULTI_CHAR_ELEMS] = {0};
  char chars_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chars_actual[0], &chars_actual[1],
                          &chars_actual[2], &chars_actual[3]),
                   expected(src, format, &chars_expected[0], &chars_expected[1],
                            &chars_expected[2], &chars_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chars_actual[i], chars_expected[i]);
  }
}
END_TEST

/* EDGE */

START_TEST(multi_ch_good_format_0) {
  const char *format = "%c_%c_%c_%c";
  const char *src = "a_b_c_d";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_good_format_1) {
  const char *format = "%c  %c  %c  %c";
  const char *src = "a  b  c  d";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_good_format_2) {
  const char *format = "%c1%c %c%c";
  const char *src = "a1b c ";

  char chars_actual[MULTI_CHAR_ELEMS] = {0};
  char chars_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chars_actual[0], &chars_actual[1],
                          &chars_actual[2], &chars_actual[3]),
                   expected(src, format, &chars_expected[0], &chars_expected[1],
                            &chars_expected[2], &chars_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chars_actual[i], chars_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_bad_format) {
  const char *format = "%c_%c_%c_%c";
  const char *src = "a b c d";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_mix_good_bad_format) {
  const char *format = "%c_%c__%c_%c";
  const char *src = "a_b__c1d";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

#define MULTI_CHAR_MAX_ALL_ELEMS 8

START_TEST(multi_ch_mix_all) {
  const char *format = "%c_%c__%c1%c  %c%c%c %c";
  const char *src = "\na_b__c1d j  P";

  char chs_actual[MULTI_CHAR_MAX_ALL_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_MAX_ALL_ELEMS] = {0};

  ck_assert_int_eq(
      actual(src, format, &chs_actual[0], &chs_actual[1], &chs_actual[2],
             &chs_actual[3], &chs_actual[4], &chs_actual[5], &chs_actual[6],
             &chs_actual[7]),
      expected(src, format, &chs_expected[0], &chs_expected[1],
               &chs_expected[2], &chs_expected[3], &chs_expected[4],
               &chs_expected[5], &chs_expected[6], &chs_expected[7]));

  for (size_t i = 0; i < MULTI_CHAR_MAX_ALL_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

/* ANOMALY */

START_TEST(multi_ch_extra_spaces) {
  const char *format = "%c %c %c %c";
  const char *src = "a     b     c     d";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_multi_spaces) {
  const char *format = "%c%c%c%c";
  const char *src = "a   b";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_multi_spaces_start) {
  const char *format = "%c%c%c%c";
  const char *src = "  ab";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_multi_spaces_middle) {
  const char *format = "%c %c%c %c";
  const char *src = "_    _";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_multi_spaces_end) {
  const char *format = "%c%c%c%c";
  const char *src = "ab \n";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_multi_spaces_starts) {
  const char *format = "%c%*c%c%*c";
  const char *src = "  ab";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

START_TEST(multi_ch_src_is_bigger) {
  const char *format = "%c %c %c %c";
  const char *src = "a b c d 1 2 3 4 5";

  char chs_actual[MULTI_CHAR_ELEMS] = {0};
  char chs_expected[MULTI_CHAR_ELEMS] = {0};

  ck_assert_int_eq(actual(src, format, &chs_actual[0], &chs_actual[1],
                          &chs_actual[2], &chs_actual[3]),
                   expected(src, format, &chs_expected[0], &chs_expected[1],
                            &chs_expected[2], &chs_expected[3]));

  for (size_t i = 0; i < MULTI_CHAR_ELEMS; i++) {
    ck_assert_int_eq(chs_actual[i], chs_expected[i]);
  }
}
END_TEST

Suite *suite_s21_sscanf_c() {
  Suite *suite = suite_create("suite_s21_sscanf_c");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, one_char);
  tcase_add_test(normal_cases, multi_char);
  tcase_add_test(normal_cases, multi_char_screen);
  tcase_add_test(normal_cases, multi_char_mix);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, multi_ch_good_format_0);
  tcase_add_test(edge_cases, multi_ch_good_format_1);
  tcase_add_test(edge_cases, multi_ch_good_format_2);
  tcase_add_test(edge_cases, multi_ch_bad_format);
  tcase_add_test(edge_cases, multi_ch_mix_good_bad_format);
  tcase_add_test(edge_cases, multi_ch_mix_all);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, multi_ch_extra_spaces);
  tcase_add_test(anomaly_cases, multi_ch_multi_spaces);
  tcase_add_test(anomaly_cases, multi_ch_multi_spaces_start);
  tcase_add_test(anomaly_cases, multi_ch_multi_spaces_middle);
  tcase_add_test(anomaly_cases, multi_ch_multi_spaces_end);
  tcase_add_test(anomaly_cases, multi_ch_multi_spaces_starts);
  tcase_add_test(anomaly_cases, multi_ch_src_is_bigger);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
