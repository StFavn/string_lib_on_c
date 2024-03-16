#include "s21_string_test.h"

#define actual(str, n, ...) s21_sscanf(str, format, __VA_ARGS__)
#define expected(str, n, ...) sscanf(str, format, __VA_ARGS__)

/* NORMAL */

START_TEST(one_str) {
  const char *format = "%s";
  const char *src = "Hello";

  char str_actual[BIG_BUFF_SIZE] = {0};
  char str_expected[BIG_BUFF_SIZE] = {1};

  ck_assert_int_eq(actual(src, format, str_actual),
                   expected(src, format, str_expected));
  ck_assert_str_eq(str_actual, str_expected);
}
END_TEST

START_TEST(one_str_width) {
  const char *format = "%2s";
  const char *src = "Hello";

  char str_actual[BIG_BUFF_SIZE] = {0};
  char str_expected[BIG_BUFF_SIZE] = {1};

  ck_assert_int_eq(actual(src, format, str_actual),
                   expected(src, format, str_expected));
  ck_assert_str_eq(str_actual, str_expected);
}
END_TEST

START_TEST(one_str_alloc) {
  const char *format = "%s";
  const char *src = "Hello";

  char *str_actual = malloc(BIG_BUFF_SIZE * sizeof(char));
  char *str_expected = malloc(BIG_BUFF_SIZE * sizeof(char));

  ck_assert_int_eq(actual(src, format, str_actual),
                   expected(src, format, str_expected));
  ck_assert_str_eq(str_actual, str_expected);

  free(str_expected);
  free(str_actual);
}
END_TEST

START_TEST(two_str) {
  const char *format = "%s %s";
  const char *src = "Hello world!";

  char str0_actual[BIG_BUFF_SIZE] = {0};
  char str0_expected[BIG_BUFF_SIZE] = {1};
  char str1_actual[BIG_BUFF_SIZE] = {0};
  char str1_expected[BIG_BUFF_SIZE] = {1};

  ck_assert_int_eq(actual(src, format, str0_actual, str1_actual),
                   expected(src, format, str0_expected, str1_expected));
  ck_assert_str_eq(str0_actual, str0_expected);
  ck_assert_str_eq(str1_actual, str1_expected);
}
END_TEST

START_TEST(two_str_width_no_delim) {
  const char *format = "%2s%4s";
  const char *src = "Hello world!";

  char str0_actual[BIG_BUFF_SIZE] = {0};
  char str0_expected[BIG_BUFF_SIZE] = {1};
  char str1_actual[BIG_BUFF_SIZE] = {0};
  char str1_expected[BIG_BUFF_SIZE] = {1};

  ck_assert_int_eq(actual(src, format, str0_actual, str1_actual),
                   expected(src, format, str0_expected, str1_expected));
  ck_assert_str_eq(str0_actual, str0_expected);
  ck_assert_str_eq(str1_actual, str1_expected);
}
END_TEST

#define MULTI_STR_ELEMS 4

START_TEST(multi_str_all_delim) {
  const char *format = "%s %s %s %s";
  const char *src = "Hello\tworld!\n123 STRING";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1],
                          str_actual[2], str_actual[3]),
                   expected(src, format, str_expected[0], str_expected[1],
                            str_expected[2], str_expected[3]));

  for (int i = 0; i < MULTI_STR_ELEMS; i++) {
    ck_assert_str_eq(str_actual[i], str_expected[i]);
  }
}
END_TEST

START_TEST(multi_str_multi_star) {
  const char *format = "%s %*s %s %*s";
  const char *src = "Hello world! 123 STRING";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}, {0}, {0}, {0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}, {1}, {1}, {1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1]),
                   expected(src, format, str_expected[0], str_expected[1]));

  ck_assert_str_eq(str_actual[0], str_expected[0]);
  ck_assert_str_eq(str_actual[1], str_expected[1]);
  ck_assert_str_ne(str_actual[2], str_expected[2]);
  ck_assert_str_ne(str_actual[3], str_expected[3]);
}
END_TEST

START_TEST(multi_str_width_no_delim) {
  const char *format = "%2s%4s%1s%6s";
  const char *src = "Hello world! 123 STRING";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1],
                          str_actual[2], str_actual[3]),
                   expected(src, format, str_expected[0], str_expected[1],
                            str_expected[2], str_expected[3]));

  for (int i = 0; i < MULTI_STR_ELEMS; i++) {
    ck_assert_str_eq(str_actual[i], str_expected[i]);
  }
}
END_TEST

START_TEST(multi_str_width_space_delim) {
  const char *format = "%2s %4s %1s %6s";
  const char *src = "Hello world! 123 STRING";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1],
                          str_actual[2], str_actual[3]),
                   expected(src, format, str_expected[0], str_expected[1],
                            str_expected[2], str_expected[3]));

  for (int i = 0; i < MULTI_STR_ELEMS; i++) {
    ck_assert_str_eq(str_actual[i], str_expected[i]);
  }
}
END_TEST

/* EDGE */

START_TEST(one_str_zero_width) {
  const char *format = "%0s";
  const char *src = "Hello";

  char str_actual[BIG_BUFF_SIZE] = {0};
  char str_expected[BIG_BUFF_SIZE] = {1};

  ck_assert_int_eq(actual(src, format, str_actual),
                   expected(src, format, str_expected));
  ck_assert_str_eq(str_actual, str_expected);
}
END_TEST

START_TEST(src_is_bigger) {
  const char *format = "%s";
  const char *src = "Hello world!";

  char str_actual[BIG_BUFF_SIZE] = {0};
  char str_expected[BIG_BUFF_SIZE] = {1};

  ck_assert_int_eq(actual(src, format, &str_actual),
                   expected(src, format, &str_expected));
  ck_assert_str_eq(str_actual, str_expected);
}
END_TEST

START_TEST(multi_str_format_delim) {
  const char *format = "%s_%s_%s_%s";
  const char *src = "Hello_world!_123_STRING";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1],
                          str_actual[2], str_actual[3]),
                   expected(src, format, str_expected[0], str_expected[1],
                            str_expected[2], str_expected[3]));

  for (int i = 0; i < MULTI_STR_ELEMS; i++) {
    ck_assert_str_eq(str_actual[i], str_expected[i]);
  }
}
END_TEST

START_TEST(multi_str_multi_spaces) {
  const char *format = "%s  %s\n\n%s\t\t%s";
  const char *src = "Hello world! 123 STRING";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1],
                          str_actual[2], str_actual[3]),
                   expected(src, format, str_expected[0], str_expected[1],
                            str_expected[2], str_expected[3]));

  for (int i = 0; i < MULTI_STR_ELEMS; i++) {
    ck_assert_str_eq(str_actual[i], str_expected[i]);
  }
}
END_TEST

START_TEST(multi_str_multi_spaces_src) {
  const char *format = "%s  %s\n\n%s\t\t%s";
  const char *src = "Hello       world!\t\t123\n\nSTRING     ";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1],
                          str_actual[2], str_actual[3]),
                   expected(src, format, str_expected[0], str_expected[1],
                            str_expected[2], str_expected[3]));

  for (int i = 0; i < MULTI_STR_ELEMS; i++) {
    ck_assert_str_eq(str_actual[i], str_expected[i]);
  }
}
END_TEST

/* ANOMALY */

START_TEST(multi_UTF_str) {
  const char *format = "%s %s %s %s";
  const char *src = "筛选 мир! 万岁\n行";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1],
                          str_actual[2], str_actual[3]),
                   expected(src, format, str_expected[0], str_expected[1],
                            str_expected[2], str_expected[3]));

  for (int i = 0; i < MULTI_STR_ELEMS; i++) {
    ck_assert_str_eq(str_actual[i], str_expected[i]);
  }
}
END_TEST

START_TEST(multi_not_correct_str) {
  const char *format = "%s %s %s %s";
  const char *src = "hello\0world!";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1],
                          str_actual[2], str_actual[3]),
                   expected(src, format, str_expected[0], str_expected[1],
                            str_expected[2], str_expected[3]));

  for (int i = 0; i < MULTI_STR_ELEMS; i++) {
    ck_assert_str_eq(str_actual[i], str_expected[i]);
  }
}
END_TEST

START_TEST(multi_str_big_width) {
  const char *format = "%200s %4s %1s %6s";
  const char *src = "Hello world! 123 STRING";

  char str_actual[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{0}};
  char str_expected[MULTI_STR_ELEMS][BIG_BUFF_SIZE] = {{1}};

  ck_assert_int_eq(actual(src, format, str_actual[0], str_actual[1],
                          str_actual[2], str_actual[3]),
                   expected(src, format, str_expected[0], str_expected[1],
                            str_expected[2], str_expected[3]));

  for (int i = 0; i < MULTI_STR_ELEMS; i++) {
    ck_assert_str_eq(str_actual[i], str_expected[i]);
  }
}
END_TEST

Suite *suite_s21_sscanf_s() {
  Suite *suite = suite_create("suite_s21_sscanf_s");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_test(normal_cases, one_str);
  tcase_add_test(normal_cases, one_str_width);
  tcase_add_test(normal_cases, one_str_alloc);
  tcase_add_test(normal_cases, two_str);
  tcase_add_test(normal_cases, two_str_width_no_delim);
  tcase_add_test(normal_cases, multi_str_all_delim);
  tcase_add_test(normal_cases, multi_str_multi_star);
  tcase_add_test(normal_cases, multi_str_width_no_delim);
  tcase_add_test(normal_cases, multi_str_width_space_delim);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_test(edge_cases, one_str_zero_width);
  tcase_add_test(edge_cases, src_is_bigger);
  tcase_add_test(edge_cases, multi_str_format_delim);
  tcase_add_test(edge_cases, multi_str_multi_spaces);
  tcase_add_test(edge_cases, multi_str_multi_spaces_src);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_test(anomaly_cases, multi_UTF_str);
  tcase_add_test(anomaly_cases, multi_not_correct_str);
  tcase_add_test(anomaly_cases, multi_str_big_width);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
