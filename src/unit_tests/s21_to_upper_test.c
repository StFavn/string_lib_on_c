#include "s21_string_test.h"

#define actual(str) s21_to_upper(str)

/* NORMAL */

static const char *normal_vals[] = {
    "abcdefghijklmnopqrstuvwxyz",  // 0
    "1234567890klmnopqrstuvwxyz",  //
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",  //
    "abcdefghijklmnOPQRSTUVWXYZ",  //
    "1234567890KLMNOPQRSTUVWXYZ",  //
    "12345fghijkl  opqrstu67890",  // 5
    "a1c2e3g  5k6  o8q  0u1w2y3",  //
    "a1  e3G  5K6  O8q  0u1  y3",  //
    "a_ d 2 _ j 4  5 _ s 7 _ y_",  //
    "a_  _2g  J_4  5P_  _7V  y_",  //
    "!@#$%^&  )_+  []{  ;':><,.",  // 10
    "abcdefghijkl  []{}|;':><,.",  //
    "ABCDEFGHIJKLM!@#$%^&*()_+-",  //
    "abcdefgHIJKLM=[]{}|;':><,.",  //
    "abcdefgHIJKLM1234567*&^%$#",  //
    "____________aA____________",  // 15
    "                          "   //
};

static const char *normal_vals_expected[] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",  // 0
    "1234567890KLMNOPQRSTUVWXYZ",  //
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",  //
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",  //
    "1234567890KLMNOPQRSTUVWXYZ",  //
    "12345FGHIJKL  OPQRSTU67890",  // 5
    "A1C2E3G  5K6  O8Q  0U1W2Y3",  //
    "A1  E3G  5K6  O8Q  0U1  Y3",  //
    "A_ D 2 _ J 4  5 _ S 7 _ Y_",  //
    "A_  _2G  J_4  5P_  _7V  Y_",  //
    "!@#$%^&  )_+  []{  ;':><,.",  // 10
    "ABCDEFGHIJKL  []{}|;':><,.",  //
    "ABCDEFGHIJKLM!@#$%^&*()_+-",  //
    "ABCDEFGHIJKLM=[]{}|;':><,.",  //
    "ABCDEFGHIJKLM1234567*&^%$#",  //
    "____________AA____________",  // 15
    "                          "   //
};

START_TEST(base_vals_normal) {
  const char *str = normal_vals[_i];
  const char *expect_dest = normal_vals_expected[_i];

  void *actual_dest = actual(str);
  ck_assert_str_eq((char *)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

/* EDGE */

static const char *edge_vals[] = {
    "",             // 0
    " ",            //
    "  ",           //
    "\0",           //
    "\0\0",         //
    "\n\0",         // 5
    "\n\n",         //
    "\0\n\0",       //
    "\0aA\0",       //
    "\naa\0",       //
    "\n\t__aA\0aA"  // 10
};

static const char *edge_vals_expected[] = {
    "",         // 0
    " ",        //
    "  ",       //
    "",         //
    "",         //
    "\n",       // 5
    "\n\n",     //
    "",         //
    "",         //
    "\nAA",     //
    "\n\t__AA"  // 10
};

START_TEST(base_vals_edge) {
  const char *str = edge_vals[_i];
  const char *expect_dest = edge_vals_expected[_i];

  void *actual_dest = actual(str);
  ck_assert_str_eq((char *)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

/* ANOMALY */

static const char *anomaly_vals[] = {
    "абвгдеёжзикл_AbC_СТУФХЦЧШЩЪЫЬЭЮЯ",       // 0
    "абв___ЁЖЗ   123---!@#$ABCabcdЭЮЯ",       //
    NULL,                                     //
    "ぁあ ぃぅぇりグ ピヹョフッ ゙ ゚ ン※ャダ㍿"  //
};

static const char *anomaly_vals_expected[] = {
    "абвгдеёжзикл_ABC_СТУФХЦЧШЩЪЫЬЭЮЯ",       // 0
    "абв___ЁЖЗ   123---!@#$ABCABCDЭЮЯ",       //
    NULL,                                     //
    "ぁあ ぃぅぇりグ ピヹョフッ ゙ ゚ ン※ャダ㍿"  //
};

START_TEST(base_vals_anomaly) {
  const char *str = anomaly_vals[_i];
  const char *expect_dest = anomaly_vals_expected[_i];

  void *actual_dest = actual(str);
  if (expect_dest == NULL) {
    ck_assert_ptr_null(actual_dest);
  } else {
    ck_assert_str_eq((char *)actual_dest, expect_dest);
  }

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

/* SUITE */

static const size_t normal_vals_elems = GET_SIZE_ARRAY(normal_vals);
static const size_t edge_vals_elems = GET_SIZE_ARRAY(edge_vals);
static const size_t anomaly_vals_elems = GET_SIZE_ARRAY(anomaly_vals);

Suite *suite_s21_to_upper() {
  Suite *suite = suite_create("suite_s21_to_upper");

  TCase *normal_cases = tcase_create("normal_cases");
  tcase_add_loop_test(normal_cases, base_vals_normal, 0, normal_vals_elems);
  suite_add_tcase(suite, normal_cases);

  TCase *edge_cases = tcase_create("edge_cases");
  tcase_add_loop_test(edge_cases, base_vals_edge, 0, edge_vals_elems);
  suite_add_tcase(suite, edge_cases);

  TCase *anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_loop_test(anomaly_cases, base_vals_anomaly, 0, anomaly_vals_elems);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}
