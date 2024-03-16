#include "s21_string_test.h"

#include <stdio.h>

void run_suite(Suite *suite) {
  SRunner *sr = srunner_create(suite);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

void run_suites_collection(Suite *suites[]) {
  for (Suite **cur = suites; *cur != NULL; cur++) {
    run_suite(*cur);
  }
}

void run_tests_collection(const char *label, Suite *suites[]) {
  printf("\n=========================================\n");
  printf("%s\n\n", label);

  run_suites_collection(suites);
}

void run_tests() {
  Suite *suites_mem[] = {suite_s21_memcpy(), suite_s21_memcmp(),
                         suite_s21_memchr(), suite_s21_memset(), NULL};

  run_tests_collection("Memory unit-tests:", suites_mem);

  Suite *suites_str[] = {suite_s21_strlen(),  suite_s21_strncpy(),
                         suite_s21_strstr(),  suite_s21_strcspn(),
                         suite_s21_strncmp(), suite_s21_strchr(),
                         suite_s21_strrchr(), suite_s21_strtok(),
                         suite_s21_sprintf(), suite_s21_strerror(),
                         suite_s21_strncat(), suite_s21_strpbrk(),
                         suite_s21_strspn(),  NULL};

  run_tests_collection("String unit-tests:", suites_str);

  Suite *suites_s21_sprintf[] = {
      suite_s21_sprintf(),     suite_s21_sprintf_c(),
      suite_s21_sprintf_d(),   suite_s21_sprintf_u(),
      suite_s21_sprintf_f(),   suite_s21_sprintf_xs(),
      suite_s21_sprintf_xl(),  suite_s21_sprintf_o(),
      suite_s21_sprintf_es(),  suite_s21_sprintf_el(),
      suite_s21_sprintf_gs(),  suite_s21_sprintf_p(),
      suite_s21_sprintf_ext(), NULL};

  run_tests_collection("s21_sprintf unit-tests:", suites_s21_sprintf);

  Suite *suites_s21_sscanf[] = {suite_s21_sscanf_c(),
                                suite_s21_sscanf_s(),
                                suite_s21_sscanf_d(),
                                suite_s21_sscanf_u(),
                                suite_s21_sscanf_x(),
                                suite_s21_sscanf_o(),
                                suite_s21_sscanf_f(),
                                suite_s21_sscanf_p(),
                                suite_s21_sscanf_eg(),
                                suite_s21_sscanf_i(),
                                suite_s21_sscanf_ext(),
                                suite_s21_sscanf(),
                                NULL};

  run_tests_collection("s21_sscanf unit-tests:", suites_s21_sscanf);

  Suite *suites_additional[] = {suite_s21_to_lower(), suite_s21_to_upper(),
                                suite_s21_insert(), suite_s21_trim(), NULL};

  run_tests_collection("Additional unit-tests:", suites_additional);

  Suite *suites_helpers[] = {suite_s21_atoi(), suite_s21_sprintf_get_params(),
                             suite_s21_itoa(), suite_s21_ditoa(), NULL};

  run_tests_collection("Helper functions unit-tests:", suites_helpers);

  printf("\n=========================================\n");
}

int main() {
  run_tests();
  return 0;
}
