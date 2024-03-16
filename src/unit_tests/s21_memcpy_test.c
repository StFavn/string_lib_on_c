#include "s21_string_test.h"

#define actual(dest, src, n) s21_memcpy(dest, src, n)
#define expected(dest, src, n) memcpy(dest, src, n)

/* NORMAL */

START_TEST(normal_chars) {
  char src[] = {'1', '2', 'a', 'b', 'c'};
  char dest_actual[BUFF_SIZE] = {0};
  char dest_expected[BUFF_SIZE] = {0};
  const size_t n = sizeof(src);

  ck_assert_mem_eq(actual(dest_actual, src, n), expected(dest_expected, src, n),
                   BUFF_SIZE);
  ck_assert_mem_eq(dest_actual, dest_expected, BUFF_SIZE);
}
END_TEST

START_TEST(normal_integers) {
  int src[] = {1, 35, 456, -5, 0};
  int dest_actual[BUFF_SIZE] = {0};
  int dest_expected[BUFF_SIZE] = {0};
  const size_t n = sizeof(src);

  ck_assert_mem_eq(actual(dest_actual, src, n), expected(dest_expected, src, n),
                   BUFF_SIZE);
  ck_assert_mem_eq(dest_actual, dest_expected, BUFF_SIZE);
}
END_TEST

START_TEST(normal_doubles) {
  double src[] = {1.565, 35.22, FLT_MAX, FLT_MIN, -0.0};
  double dest_actual[BUFF_SIZE] = {0};
  double dest_expected[BUFF_SIZE] = {0};
  const size_t n = sizeof(src);

  ck_assert_mem_eq(actual(dest_actual, src, n), expected(dest_expected, src, n),
                   BUFF_SIZE);
  ck_assert_mem_eq(dest_actual, dest_expected, BUFF_SIZE);
}
END_TEST

START_TEST(normal_struct) {
  typedef struct {
    char name[256];
    int grade;
  } Student;

  Student student_src = {.name = {0}, .grade = 0};
  strcpy(student_src.name, "Joe");
  student_src.grade = 90;

  Student student_actual;
  Student student_expected;
  const size_t n = sizeof(Student);

  ck_assert_mem_eq(actual(&student_actual, &student_src, n),
                   expected(&student_expected, &student_src, n),
                   sizeof(Student));
}
END_TEST

START_TEST(anomaly_zero_n) {
  int src[] = {1, 35, 456, -5, 0};
  int dest_actual[BUFF_SIZE] = {0};
  int dest_expected[BUFF_SIZE] = {0};
  const size_t n = 0;

  ck_assert_mem_eq(actual(dest_actual, src, n), expected(dest_expected, src, n),
                   BUFF_SIZE);
  ck_assert_mem_eq(dest_actual, dest_expected, BUFF_SIZE);
}
END_TEST

/* SUITE */

Suite *suite_s21_memcpy() {
  Suite *suite = suite_create("suite_s21_memcpy");

  TCase *normal_case = tcase_create("normal_case");
  tcase_add_test(normal_case, normal_chars);
  tcase_add_test(normal_case, normal_integers);
  tcase_add_test(normal_case, normal_doubles);
  tcase_add_test(normal_case, normal_struct);
  suite_add_tcase(suite, normal_case);

  TCase *anomaly_case = tcase_create("anomaly_case");
  tcase_add_test(anomaly_case, anomaly_zero_n);
  suite_add_tcase(suite, anomaly_case);

  return suite;
}