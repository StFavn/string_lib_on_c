#include "s21_string_test.h"

#define actual(src, trim_chars) s21_trim(src, trim_chars)

/* NORMAL */

static const char* A_standart_tchars = "A";
static const char* A_standart_expected = "____";
static const char* A_standart_src[] = {
    "____",          // 0
    "A____A",        //
    "A____",         //
    "____A",         //
    "AA____AA",      //
    "AAAAAAAA____",  // 5
    "____AAAAAAAA"   //
};

START_TEST(A_standart) {
  const char* src = A_standart_src[_i];
  const char* trim_chars = A_standart_tchars;
  const char* expect_dest = A_standart_expected;

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

static const char* A_in_src_tchars = "A";
static const char* A_in_src_expected = "_AA_";
static const char* A_in_src_src[] = {
    "_AA_",      // 0
    "_AA_A",     //
    "A_AA_",     //
    "A_AA_A",    //
    "AA_AA_AA",  //
    "AAAA_AA_"   // 5
};

START_TEST(A_in_src) {
  const char* src = A_in_src_src[_i];
  const char* trim_chars = A_in_src_tchars;
  const char* expect_dest = A_in_src_expected;

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

static const char* any_symbols_tchars = "1A*";
static const char* any_symbols_expected = "____";
static const char* any_symbols_src[] = {
    "1____A*",         // 0
    "A*____1",         //
    "1A*____***",      //
    "1A1*1*A____1A*",  //
    "____",            //
    "A*1____"          // 5
};

START_TEST(any_symbols) {
  const char* src = any_symbols_src[_i];
  const char* trim_chars = any_symbols_tchars;
  const char* expect_dest = any_symbols_expected;

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

START_TEST(other_array) {
  const char* src = any_symbols_src[_i];
  const char trim_chars[] = {'1', 'A', '*', '\0'};
  const char* expect_dest = any_symbols_expected;

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

static const char* normal_vals_tchars = "abcdefghijklmnopqrstuvwxyz";
static const char* normal_vals_src[] = {
    "abs__asd__ghh",  // 0
    "a1d_ag_dd asd",  //
    "jfdsk_a_a_a_a",  //
    "fDeDfEsAsDfDS",  //
    "   asdadasdas",  //
    "1233__dsad_as",  // 5
    "asd ad ad fgf",  //
    "__fakfaflkj__",  //
    "^&**___asdadd",  //
    "123aasd*&^asd",  //
    "aasf__da(*&&)",  // 10
    "_____________",  //
    "        afd  ",  //
    "             "   //
};

static const char* normal_vals_expected[] = {
    "__asd__",        // 0
    "1d_ag_dd ",      //
    "_a_a_a_",        //
    "DeDfEsAsDfDS",   //
    "   ",            //
    "1233__dsad_",    // 5
    " ad ad ",        //
    "__fakfaflkj__",  //
    "^&**___",        //
    "123aasd*&^",     //
    "__da(*&&)",      // 10
    "_____________",  //
    "        afd  ",  //
    "             "   //
};

START_TEST(base_normal_vals) {
  const char* src = normal_vals_src[_i];
  const char* trim_chars = normal_vals_tchars;
  const char* expect_dest = normal_vals_expected[_i];

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

/* EDGE */

static const char* empty_tchars_tchars = "";
static const char* empty_tchars_src[] = {
    "12345678",  // 0
    "abcdefgh",  //
    "1qA#_ af"   //
};

static const char* empty_tchars_expected[] = {
    "12345678",  // 0
    "abcdefgh",  //
    "1qA#_ af"   //
};

START_TEST(empty_tchars) {
  const char* src = empty_tchars_src[_i];
  const char* trim_chars = empty_tchars_tchars;
  const char* expect_dest = empty_tchars_expected[_i];

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

static const char* tchars_zero_symb_tchar = "\0";
static const char* tchars_zero_symb_src[] = {
    "___AAA___",  // 0
    "         ",  //
    "123456789"   //
};

static const char* tchars_zero_symb_expected[] = {
    "___AAA___",  // 0
    "         ",  //
    "123456789"   //
};

START_TEST(tchars_zero_symb) {
  const char* src = tchars_zero_symb_src[_i];
  const char* trim_chars = tchars_zero_symb_tchar;
  const char* expect_dest = tchars_zero_symb_expected[_i];

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

static const char* empty_src_tchars[] = {
    "a",                           // 0
    "abcdefghijklmnopqrstuvwxyz",  //
    "1234567890"                   //
};

START_TEST(empty_src) {
  const char* src = "";
  const char* trim_chars = empty_src_tchars[_i];
  const char* expect_dest = "";

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

START_TEST(empty_src_and_tchars) {
  const char* src = "";
  const char* trim_chars = "";
  const char* expect_dest = "";

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

static const char* edge_vals_tchars = "A\n\t";
static const char* edge_vals_src[] = {
    "",                 // 0
    "____",             //
    "\n",               //
    "\t\n\t",           //
    "\n\tA____",        //
    "__\n__",           // 5
    "____",             //
    "____\n\n",         //
    "\n\n\n\n",         //
    "\0",               //
    "\0\n\n\t",         // 10
    "\0\0\0\0",         //
    "\0_\0",            //
    "\nA____\0____A",   //
    "\n__A__\0____\t",  //
    "___\n\0___\0\n"    // 15
};

static const char* edge_vals_expected[] = {
    "",        // 0
    "____",    //
    "",        //
    "",        //
    "____",    //
    "__\n__",  // 5
    "____",    //
    "____",    //
    "",        //
    "",        //
    "",        // 10
    "",        //
    "",        //
    "____",    //
    "__A__",   //
    "___"      // 15
};

START_TEST(base_edge_vals) {
  const char* src = edge_vals_src[_i];
  const char* trim_chars = edge_vals_tchars;
  const char* expect_dest = edge_vals_expected[_i];

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

/* ANOMALY */

static const char* other_vals_tchars = "_";
static const char* other_vals_src[] = {
    "привет",            // 0
    "__привет",          //
    "__привет__",        //
    "__привет",          //
    "__при__вет__",      //
    "при__вет",          // 5
    "__dDDda_Прив_&&*_"  //
};

static const char* other_vals_expected[] = {
    "привет",         // 0
    "привет",         //
    "привет",         //
    "привет",         //
    "при__вет",       //
    "при__вет",       // 5
    "dDDda_Прив_&&*"  //
};

START_TEST(other_vals) {
  const char* src = other_vals_src[_i];
  const char* trim_chars = other_vals_tchars;
  const char* expect_dest = other_vals_expected[_i];

  void* actual_dest = actual(src, trim_chars);
  ck_assert_str_eq((char*)actual_dest, expect_dest);

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

static const char* null_vals_src[] = {
    NULL,  // 0
    "_",   //
    NULL   //
};
static const char* null_vals_tchars[] = {
    "_",   // 0
    NULL,  //
    NULL   //
};
static const char* null_vals_expected[] = {
    NULL,  // 0
    "_",   //
    NULL   //
};

START_TEST(null_vals) {
  const char* src = null_vals_src[_i];
  const char* trim_chars = null_vals_tchars[_i];
  const char* expect_dest = null_vals_expected[_i];

  void* actual_dest = actual(src, trim_chars);
  if (expect_dest == NULL) {
    ck_assert(actual_dest == NULL);
  }

  if (actual_dest != S21_NULL) free(actual_dest);
};
END_TEST

/* SUITE */

static const size_t A_standart_elems = GET_SIZE_ARRAY(A_standart_src);
static const size_t A_in_src_elems = GET_SIZE_ARRAY(A_in_src_src);
static const size_t any_symbols_elems = GET_SIZE_ARRAY(any_symbols_src);
static const size_t normal_vals_elems = GET_SIZE_ARRAY(normal_vals_src);

static const size_t empty_tchars_elems = GET_SIZE_ARRAY(empty_tchars_src);
static const size_t tchars_zero_elems = GET_SIZE_ARRAY(tchars_zero_symb_src);
static const size_t empty_src_elems = GET_SIZE_ARRAY(empty_src_tchars);
static const size_t edge_vals_elems = GET_SIZE_ARRAY(edge_vals_src);

static const size_t other_vals_elems = GET_SIZE_ARRAY(other_vals_src);
static const size_t null_vals_elems = GET_SIZE_ARRAY(null_vals_src);

Suite* suite_s21_trim() {
  Suite* suite = suite_create("suite_s21_trim");

  TCase* normal_cases = tcase_create("normal_cases");
  tcase_add_loop_test(normal_cases, A_standart, 0, A_standart_elems);
  tcase_add_loop_test(normal_cases, A_in_src, 0, A_in_src_elems);
  tcase_add_loop_test(normal_cases, any_symbols, 0, any_symbols_elems);
  tcase_add_loop_test(normal_cases, other_array, 0, any_symbols_elems);
  tcase_add_loop_test(normal_cases, base_normal_vals, 0, normal_vals_elems);
  suite_add_tcase(suite, normal_cases);

  TCase* edge_cases = tcase_create("edge_cases");
  tcase_add_loop_test(edge_cases, empty_tchars, 0, empty_tchars_elems);
  tcase_add_loop_test(edge_cases, tchars_zero_symb, 0, tchars_zero_elems);
  tcase_add_loop_test(edge_cases, empty_src, 0, empty_src_elems);
  tcase_add_test(edge_cases, empty_src_and_tchars);
  tcase_add_loop_test(edge_cases, base_edge_vals, 0, edge_vals_elems);
  suite_add_tcase(suite, edge_cases);

  TCase* anomaly_cases = tcase_create("anomaly_cases");
  tcase_add_loop_test(anomaly_cases, other_vals, 0, other_vals_elems);
  tcase_add_loop_test(anomaly_cases, null_vals, 0, null_vals_elems);
  suite_add_tcase(suite, anomaly_cases);

  return suite;
}