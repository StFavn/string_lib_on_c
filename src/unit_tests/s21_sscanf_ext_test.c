#include "s21_string_test.h"

START_TEST(EOF1) {
  char *format = "%d";
  char *src = "        ";

  int16_t res1 = s21_sscanf(src, format, 0);
  int16_t res2 = sscanf(src, format, 100);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(EOF2) {
  char *format = "%d ";
  char *src = "               ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1);
  int16_t res2 = sscanf(src, format, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(EOF3) {
  char *format = "%d ";
  char *src = "  ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1);
  int16_t res2 = sscanf(src, format, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(only_chars1) {
  char *format = "%c %c %c %c";
  char *src = "   a     b c d";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(only_chars2) {
  char *format = "%c%c%c%c";
  char *src = "abcd";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(only_chars3) {
  char *format = "%c %c %c      %c";
  char *src = "1 a 3   c           ";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(only_chars4) {
  char *format = "%c %c %c %c";
  char *src = "   000 0    ";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(only_chars5) {
  char *format = "%c %c %c %c";
  char *src = "tttt";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(special_symbols_as_chars1) {
  char *format = "%c%c%c%c";
  char *src = "\\\n\t\t\t";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(special_symbols_as_chars2) {
  char *format = "%c %c %c %c";
  char *src = "z ' ' /";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(special_symbols_as_chars3) {
  char *format = "%c%*c%c%c";
  char *src = "ABCD";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1);

  int16_t res2 = sscanf(src, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(chars_flags1) {
  char *format = "%c %c %c %c";
  char *src = "z *'@";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(chars_flags2) {
  char *format = "%1c %c %c %0c";
  char *src = "z *'@";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(chars_flags3) {
  char *format = "%c %c %c %c";
  char *src = "z *'@";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(chars_flags5) {
  char *format = "%*c%*c%*c%c";
  char *src = "abcde";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1);
  int16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(chars_aster1) {
  char *format = "%*c%*c%*c%*c";
  char *src = "   c ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1);
  int16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(chars_aster2) {
  char *format = "%*c%*c%*c%c";
  char *src = "abcd ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(src, format, &a1);
  int16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(only_ints1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *format = "%ld %ld %ld %ld";
  const char *src = "555 666 777 888";

  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(only_ints2) {
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "1337 21 5008 3000";
  const char *format = "%hd %hd %hd %hd";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(only_ints3) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "1337 21 5008 300004";
  const char *format = "%ld %ld %ld %ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(ints_nwidth1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "1337 21 5008 300004";
  const char *format = "%1ld %3ld %1ld %4ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(ints_nwidth2) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "1337";
  const char *format = "%1ld %1ld %1ld %1ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(ints_nwidth3) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "100000000000000005";
  const char *format = "%3ld%ld%1ld%5ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(ints_nwidth4) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "1337";
  const char *format = "%15ld %1ld %1ld %1ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(ints_astwidth1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  const char *src = "1337123123 1 123412341234 1 999999 0";
  const char *format = "%*d %ld %*d %ld %*d %ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(ints_astwidth2) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "1337";
  const char *format = "%15ld %1ld %1ld %1ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(ints_astwidth3) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "1337";
  const char *format = "%15ld %1ld %1ld %1ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(signed_ints1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "11337 ++3 -5 ------4";
  const char *format = "%ld %ld %ld %ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(signed_ints2) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "-1337 +1 -1 -1";
  const char *format = "%15ld %1ld %1ld %5ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(signed_ints3) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "-0 +0 +0 -0";
  const char *format = "%2ld %1ld %1ld %1ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(signed_ints4) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "1 01 10 0";
  const char *format = "%ld %ld %ld %ld";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(spec_i_int1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "300 500 -600 +700";
  const char *format = "%li %li %li %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(spec_i_int2) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "300500-600+700 111";
  const char *format = "%li %ld %ld %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(spec_i_int3) {
  long a1 = 0, a2 = 0, c1 = 0, c2 = 0;
  char b1 = 0, b2 = 0, d1 = 0, d2 = 0;
  const char *src = "300500-600+700+400";
  const char *format = "%li%c%li%c";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(spec_i_int4) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "  55555 f f f5555555 ddd   4    3    1 ";
  const char *format = "%li %ld %ld %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(spec_i_hex1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "0xFFF 0xA123123 0x123123 0x0";
  const char *format = "%li %ld %ld %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(spec_i_hex2) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = " 0xFFFF 0xf 0xf 0xf5555555 ddd   4    3    1 ";
  const char *format = "%li %ld %ld %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(spec_i_oct1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "  055555 0f 0f 0f5555555 0ddd   4    3    1 ";
  const char *format = "%li %ld %ld %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(spec_i_oct2) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "  055555 0f 0f 0f5555555 0ddd   4    3    1 ";
  const char *format = "%li %ld %ld %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

/* [%s] */

START_TEST(strings1) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *src = "Aboba Floppa Keppa Shleppa Anuroba";
  const char *format = "%s %s %s %s";

  int16_t res1 = s21_sscanf(src, format, s1, s2, s3, s4);
  int16_t res2 = sscanf(src, format, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings_mixed3) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *src = "Aboba 123 Floppa -3 Keppa 4444Shleppa 333Anuroba 3";
  const char *format = "%s%ld%s%d%s%d%s";

  int16_t res1 = s21_sscanf(src, format, s1, &a1, s2, &b1, s3, &c1, s4, &d1);
  int16_t res2 = s21_sscanf(src, format, s5, &a2, s6, &b2, s7, &c2, s8, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings2) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *src = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char *format = "%s%s%s%s";

  int16_t res1 = s21_sscanf(src, format, s1, s2, s3, s4);
  int16_t res2 = sscanf(src, format, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

#if !(defined(__APPLE__) || defined(__MACH__))

START_TEST(strings3) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *src = "aboba\tkepaboba floppa shleppa koooppa ap p p p p";
  const char *format = "%*s%*s%*s%*s";

  int16_t res1 = s21_sscanf(src, format);
  int16_t res2 = sscanf(src, format);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

#endif

START_TEST(strings4) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *src = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char *format = "%1s%1s%1s%1s";

  int16_t res1 = s21_sscanf(src, format, s1, s2, s3, s4);
  int16_t res2 = sscanf(src, format, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings5) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *src = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char *format = "%3s%3s%3s%3s";

  int16_t res1 = s21_sscanf(src, format, s1, s2, s3, s4);
  int16_t res2 = sscanf(src, format, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings6) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *src = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char *format = "%150s%1s%1s\t%3s";

  int16_t res1 = s21_sscanf(src, format, s1, s2, s3, s4);
  int16_t res2 = sscanf(src, format, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

// strings_mixed1

START_TEST(strings_mixed1) {
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  long d1 = 0, d2 = 0;
  long double e1 = 0, e2 = 0;

  const char *src =
      "4444444"
      "eeeeeee\teeeeeee";
  const char *format = "%5s %1s %*s %*s %lu %s %lu %lu %ld %Lf %33s";

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};
  char s9[BUFF_SIZE] = {'\0'};
  char s10[BUFF_SIZE] = {'\0'};

  int16_t res1 =
      s21_sscanf(src, format, s7, s9, &a1, s5, &b1, &c1, &d1, &e1, s1);
  int16_t res2 = sscanf(src, format, s8, s10, &a2, s6, &b2, &c2, &d2, &e2, s2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
  ck_assert_str_eq(s5, s6);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(strings_mixed2) {
  int d1 = 0, d2 = 0, b1 = 0, b2 = 0, a1 = 0, a2 = 0;
  long v1, v2;

  const char *src = "1 1 1 1 1 -1";
  const char *format = "%1s %5d %1s %1s %d %ld %d";

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};

  int16_t res1 = s21_sscanf(src, format, s1, &a1, s2, s3, &b1, &v1, &d1);
  int16_t res2 = sscanf(src, format, s4, &a2, s5, s6, &b2, &v2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
  ck_assert_str_eq(s5, s6);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

/* [%n] */

START_TEST(n1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int32_t n1 = 0, n2 = 5;

  const char src[BUFF_SIZE] = "50 160 70 80";
  const char format[BUFF_SIZE] = "%li %li %n %li %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &n1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &n2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(n2) {
  int n1 = 1, n2 = 5;

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};

  const char *src = "cbobErobM fl? asdfasdflkasdf asdfasdf asdfasdf 88888";
  const char *format = "%s %s %n %s";

  int32_t res1 = s21_sscanf(src, format, s1, s2, &n1, s3);
  int32_t res2 = sscanf(src, format, s5, s6, &n2, s7);

  ck_assert_int_eq(res1, res2);

  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
}
END_TEST

START_TEST(n3) {
  int n1 = 0, n2 = 5;

  const char src[BUFF_SIZE] = "50 60 70 80";
  const char format[BUFF_SIZE] = "%n";

  int16_t res1 = s21_sscanf(src, format, &n1);
  int16_t res2 = sscanf(src, format, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(n4) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int32_t n1 = 0, n2 = 5;

  const char *src = "50 60 70 80";
  const char *format = "%li %li %n %li %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &n1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &n2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(n5) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int n1 = 0, n2 = 5;

  const char *src = "50 60 70 80";
  const char *format = "%li %li %n %li %li";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &n1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &n2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

/* [%f] / [%g] / %[%G] */

START_TEST(floats1) {
  long double a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0, d1 = 1, d2 = 0;

  const char *src = "53.1 -4.1135 41.3333 +2.0001";
  const char *format = "%Lf %Lf %Lf %Lf";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(floats2) {
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *src = "0.00001 -4123123 4. .";
  const char *format = "%Lf %Lf %Lf %Lf";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(floats3) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *src = ". . . .";
  const char *format = "%f %f %f %f";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(floats4) {
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *src = "513.41 -4.14135 414.3333 +112.0001";
  const char *format = "%Lf %Lf %Lf %Lf";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(floats5) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  const char *src = "53.1 -4.1135 411231.333 +2.0001";
  const char *format = "%*f %f %f %f";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(floats_sci1) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *src = "1.4441 1.31e+4 -3.31e-4 0.444e-5";
  const char *format = "%G %G %G %G";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(floats_sci2) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *src = "inf 1.31e+4 NaN 0.444e-5";
  const char *format = "%G %G %G %G";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  // Unfortunately, assertions for inf do not work correctly in libcheck
  // ck_assert_ldouble_infinite(a1);
  // ck_assert_ldouble_infinite(a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_float_nan(c1);
  ck_assert_float_nan(c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(floats_sci3) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *src = "inF InF inF INF";
  const char *format = "%G %G %G %G";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(floats_sci4) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *src = "Nan NAN 0.0000 0";
  const char *format = "%G %G %G %G";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(a1);
  ck_assert_float_nan(a2);
  ck_assert_float_nan(b1);
  ck_assert_float_nan(b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(floats_sci5) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *src = "nAN           INF                   -0.1111         1e-10";
  const char *format = "%G %G %G %G";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(a1);
  ck_assert_float_nan(a2);
  ck_assert_ldouble_eq(b1, b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

/* [%u] */

START_TEST(uint1) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "-1337 +21 --5008 3000";
  const char *format = "%hu %hu %hu %hu";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(uint2) {
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0,
                    d2 = 0;
  const char *src = "-1337 233333331 5008 3000";
  const char *format = "%1lu %2lu %5lu %4lu";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(uint3) {
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  long d1 = 0, d2 = 0;
  long double v1, v2;

  const char *src =
      "\t\t\t\t\t\n 3      adsfdfa%$$$$`adfasdfasdfaszcvzcxvcv -1337 "
      "anurobich+ 21 -5008 -33000 0.3333";
  const char *format = "%*s %*s %lu %s %lu %lu %ld %Lf";

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};

  int16_t res1 = s21_sscanf(src, format, &a1, s1, &b1, &c1, &d1, &v1);
  int16_t res2 = sscanf(src, format, &a2, s2, &b2, &c2, &d2, &v2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_ldouble_eq_tol(v1, v2, 0.0001);
}
END_TEST

START_TEST(uint4) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "-1337 +21 --5008 3000";
  const char *format = "%hu %hu %hu %hu";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(uint5) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "-1337 +21 --5008 3000";
  const char *format = "%hu %hu %hu %hu";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(uint6) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *src = "-1337 +21 --5008 3000";
  const char *format = "%hu %hu %hu %hu";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(upeer_hex_base_version) {
  uint32_t a1, a2;
  const char *src = "F";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upeer_hex_overflow) {
  uint32_t a1, a2;
  const char *src = "0xFFFFFFFF";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upeer_hex_0x) {
  uint32_t a1, a2;
  const char *src = "0x";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upeer_hex_0X) {
  uint32_t a1, a2;
  const char *src = "0X";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upeer_hex_empty) {
  uint32_t a1, a2;
  const char *src = "";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(upeer_hex_fail) {
  uint32_t a1, a2;
  const char *src = "qF";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(upeer_hex_spaces_tabs_sns) {
  uint32_t a1, a2;
  const char *src = "          \n             \n     F";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upeer_hex_short) {
  uint16_t a1, a2;
  const char *src = "F";
  const char *format = "%hX";
  uint16_t res1 = s21_sscanf(src, format, &a1);
  uint16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upeer_hex_long) {
  unsigned long int a1, a2;
  const char *src = "F";
  const char *format = "%lX";
  uint16_t res1 = s21_sscanf(src, format, &a1);
  uint16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upeer_hex_longlong) {
  unsigned long int a1, a2;
  const char *src = "F";
  const char *format = "%lX";
  uint16_t res1 = s21_sscanf(src, format, &a1);
  uint16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upeer_hex_2x) {
  uint32_t a1, a2;
  const char *src = "0xFF0x0xFFF 0xFFxFF";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

#if !(defined(__APPLE__) || defined(__MACH__))

START_TEST(upeer_hex_star) {
  const char *src = "0xFF0x0xFFF 0xFFxFF";
  const char *format = "%*X";
  uint32_t res1 = s21_sscanf(src, format);
  uint32_t res2 = sscanf(src, format);

  ck_assert_int_eq(res1, res2);
}
END_TEST

#endif

START_TEST(upeer_hex_nohex) {
  uint32_t a1, a2;
  const char *src = "tqwqpl";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(upeer_hex_lower) {
  uint32_t a1, a2;
  const char *src = "abcdef";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upeer_hex_sign) {
  uint32_t a1, a2;
  const char *src = "-f";
  const char *format = "%X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_base_version) {
  uint32_t a1, a2;
  const char *src = "f";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_overflow) {
  uint32_t a1, a2;
  const char *src = "0xfffffffffffffffffff";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_0x) {
  uint32_t a1, a2;
  const char *src = "0x";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_0X) {
  uint32_t a1, a2;
  const char *src = "0X";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_empty) {
  uint32_t a1, a2;
  const char *src = "";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(lower_hex_fail) {
  uint32_t a1, a2;
  const char *src = "qF";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(lower_hex_spaces_tabs_sns) {
  uint32_t a1, a2;
  const char *src = "          \n             \n     F";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_short) {
  uint16_t a1, a2;
  const char *src = "ff";
  const char *format = "%hx";
  uint16_t res1 = s21_sscanf(src, format, &a1);
  uint16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_long) {
  unsigned long int a1, a2;
  const char *src = "ff";
  const char *format = "%lx";
  uint16_t res1 = s21_sscanf(src, format, &a1);
  uint16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_longlong) {
  unsigned long int a1, a2;
  const char *src = "faaaaaaaaaaaaf";
  const char *format = "%lX";
  uint16_t res1 = s21_sscanf(src, format, &a1);
  uint16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  // ck_assert_unsigned long int_eq(a1, a2);
  // ck_assert_uint64_eq(a1, a2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_2x) {
  uint32_t a1, a2;
  const char *src = "0xFF0x0xFFF 0xFFxFF";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

#if !(defined(__APPLE__) || defined(__MACH__))

START_TEST(lower_hex_star) {
  const char *src = "0xFF0x0xFFF 0xFFxFF";
  const char *format = "%*x";
  uint32_t res1 = s21_sscanf(src, format);
  uint32_t res2 = sscanf(src, format);

  ck_assert_int_eq(res1, res2);
}
END_TEST

#endif

START_TEST(lower_hex_nohex) {
  uint32_t a1, a2;
  const char *src = "tqwqpl";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(lower_hex_lower) {
  uint32_t a1, a2;
  const char *src = "abcdef";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_sign) {
  uint32_t a1, a2;
  const char *src = "-f";
  const char *format = "%x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upper_hex_len) {
  uint32_t a1, a2;
  const char *src = "123531FFF";
  const char *format = "%2X";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(lower_hex_len) {
  uint32_t a1, a2;
  const char *src = "123531FFF";
  const char *format = "%2x";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_base_version) {
  uint32_t a1, a2;
  const char *src = "777";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_overflow) {
  uint32_t a1, a2;
  const char *src = "0x7777777777777777777777";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_0x) {
  uint32_t a1, a2;
  const char *src = "0x";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_0X) {
  uint32_t a1, a2;
  const char *src = "0X";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_empty) {
  uint32_t a1, a2;
  const char *src = "";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(octal_fail) {
  uint32_t a1, a2;
  const char *src = "q1";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(octal_spaces_tabs_sns) {
  uint32_t a1, a2;
  const char *src = "          \n             \n     5";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_short) {
  uint16_t a1, a2;
  const char *src = "12";
  const char *format = "%ho";
  uint16_t res1 = s21_sscanf(src, format, &a1);
  uint16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_long) {
  unsigned long int a1, a2;
  const char *src = "57234";
  const char *format = "%lo";
  uint16_t res1 = s21_sscanf(src, format, &a1);
  uint16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_longlong) {
  unsigned long int a1, a2;
  const char *src = "12356226137";
  const char *format = "%lo";
  uint16_t res1 = s21_sscanf(src, format, &a1);
  uint16_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_2x) {
  uint32_t a1, a2;
  const char *src = "0x12320x213x123213";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

#if !(defined(__APPLE__) || defined(__MACH__))

START_TEST(octal_star) {
  const char *src = "521561612";
  const char *format = "%*o";
  uint32_t res1 = s21_sscanf(src, format);
  uint32_t res2 = sscanf(src, format);

  ck_assert_int_eq(res1, res2);
}
END_TEST

#endif

START_TEST(octal_nohex) {
  uint32_t a1, a2;
  const char *src = "tqwqpl";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(octal_lower) {
  uint32_t a1, a2;
  const char *src = "01234567";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_sign) {
  uint32_t a1, a2;
  const char *src = "-66";
  const char *format = "%o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(octal_len) {
  uint32_t a1, a2;
  const char *src = "123531";
  const char *format = "%2o";
  uint32_t res1 = s21_sscanf(src, format, &a1);
  uint32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(buff1) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char *src = "12 keppa 12";
  const char *format = "%d keppa %d";
  int32_t res1 = s21_sscanf(src, format, &a1, &b1);
  int32_t res2 = sscanf(src, format, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(buff2) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char *src = "12keppa12";
  const char *format = "%dkeppa%d";
  int32_t res1 = s21_sscanf(src, format, &a1, &b1);
  int32_t res2 = sscanf(src, format, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(pointer1) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char *src = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char *format = "%p %p %p %p";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(pointer2) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char *src = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char *format = "%p %p %p %p";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(pointer3) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char *src = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char *format = "%p %p %p %p";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(pointer4) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char *src = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char *format = "%p %p %p %p";

  int16_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(hard1) {
  int a1 = 0, a2 = 5, a3 = 3, a4 = 9;
  int32_t n1 = 500, n2 = 10000;

  const char *src = "123123SkipMePlease!!!!123";
  const char *format = "%dSkipMePlease!!!!%d %n";

  int16_t res1 = s21_sscanf(src, format, &a1, &a3, &n1);
  int16_t res2 = sscanf(src, format, &a2, &a4, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a3, a4);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(buff3) {
  int32_t a1, a2;
  int32_t b1 = 0, b2 = 0;
  const char *src = "12keppa12";
  const char *format = "%dkeppapos%d";
  int32_t res1 = s21_sscanf(src, format, &a1, &b1);
  int32_t res2 = sscanf(src, format, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(perc1) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char *src = "12 % 13 % 14";
  const char *format = "%d %% %d %% %d";
  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(perc2) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char *src = "12%13%14";
  const char *format = "%d%%%d%%%d";
  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(perc3) {
  int32_t a1 = 1234, a2 = 33333;

  const char *src = "%%%16";
  const char *format = "%%%%%%%d";
  int32_t res1 = s21_sscanf(src, format, &a1);
  int32_t res2 = sscanf(src, format, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

#if !(defined(__APPLE__) || defined(__MACH__))

START_TEST(perc4) {
  const char *src = "%%%";
  const char *format = "%%%%%%";
  int32_t res1 = s21_sscanf(src, format);
  int32_t res2 = sscanf(src, format);

  ck_assert_int_eq(res1, res2);
}
END_TEST

#endif

START_TEST(perc5) {
  int32_t a1 = 1234, a2 = 33333;
  int32_t b1 = 1234, b2 = 33333;

  const char *src = "%%123%888";
  const char *format = "%%%%%d%%%d";
  int32_t res1 = s21_sscanf(src, format, &a1, &b1);
  int32_t res2 = sscanf(src, format, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(mixed_ptrs1) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char *src = "0xFFFF 0xAAA 7123 0xBBC1FF";
  const char *format = "%p %p %p %p";

  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(mixed_ptrs2) {
  char *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char *src = "0x4 0x3 0x2 0x1";
  const char *format = "%p %p %p %p";

  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(mixed_ptrs3) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char *src = "03033 0333 0123 0123 0x123 0xFFFFF 0xBBC1FF";
  const char *format = "%p %p %p %p";

  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(mixed_ptrs4) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char *src = "0xABCDEF 0xAAA 7123 0xBBC1FF";
  const char *format = "%p %p %p %p";

  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(mixed_ptrs5) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char *src = "NULL";
  const char *format = "%p %p %p %p";

  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(hard3) {
  char a1, a2;
  char b1[256] = {'\0'};
  char b2[256] = {'\0'};
  float c1, c2;
  short int d1, d2;
  long int e1, e2;

  const char *src = "$AmIIn%%sane? %\n\n\n \n \n \n\t   InF 0 %FIN9D-ME%";
  const char *format = "%c%5s%%%*s %%  %G %hi %%FIN%ldDME%%";

  int32_t res1 = s21_sscanf(src, format, &a1, b1, &c1, &d1, &e1);
  int32_t res2 = sscanf(src, format, &a2, b2, &c2, &d2, &e2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_float_infinite(c1);
  ck_assert_float_infinite(c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(hard4) {
  char a1, a2;
  char b1, b2;
  char c1, c2;
  char d1, d2;

  const char *src = "%%$Char!StressssT%%estus!&&&";
  const char *format = "%% %*c%*c%*c%*c%*c %c %c %c %c ### %*c";

  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(hard5) {
  char a1, a2;
  char b1, b2;
  char c1, c2;
  char d1, d2;
  const char *src =
      "%%$Char!StressssVIm User Aboba %% %%% %%% %% % % %% % "
      "% % %% % % %% %T%%estus!%%&&&";
  const char *format =
      "%% %*c%*c%*c%*c%*c %c %c %c %c %% %% %% %% %% %% %% "
      "%% %% %% %% %% %% %% %% %% ### %*c";

  int32_t res1 = s21_sscanf(src, format, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(src, format, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

Suite *suite_s21_sscanf_ext(void) {
  Suite *s = suite_create("suite_s21_sscanf_ext");
  TCase *tc = tcase_create("sscanf_tc");
  // %[width][length][specifier]

  // [EOF]
  // Flags: do nothing (unapplicable to this specifier)

  tcase_add_test(tc, EOF1);
  tcase_add_test(tc, EOF2);
  tcase_add_test(tc, EOF3);

  // // [%c]
  // // Flags:
  // // [Width] - N: 0, 1 - Do nothing; N > 1 - Undefined beh.
  // //          * - skips chars
  // // [Precision] - Any precision flag immediately stops sscanf (error)
  // // [Length] - Does nothing

  tcase_add_test(tc, only_chars1);
  tcase_add_test(tc, only_chars2);
  tcase_add_test(tc, only_chars3);
  tcase_add_test(tc, only_chars4);
  tcase_add_test(tc, only_chars5);
  tcase_add_test(tc, special_symbols_as_chars1);
  tcase_add_test(tc, special_symbols_as_chars2);
  tcase_add_test(tc, special_symbols_as_chars3);

  tcase_add_test(tc, chars_flags1);  // Precision flags lead to fail
  tcase_add_test(tc, chars_flags2);  // Width flags do nothing (if <= 1)
  tcase_add_test(
      tc, chars_flags3);  // Demonstrates how (*) works. * - ignore the char
  tcase_add_test(tc, chars_flags5);  // * flags - ignores char
  // Test cases specifically for (%*c), as this is very important concept
  tcase_add_test(tc, chars_aster1);
  tcase_add_test(tc, chars_aster2);

  // // [%d]/[%i]
  // // [Width]: * - skip token, (N) - read N chars as a number
  // // [Precision]: Not applicable to int, considered as UB

  // // Length (h, l, ll)
  tcase_add_test(tc, only_ints1);
  tcase_add_test(tc, only_ints2);
  tcase_add_test(tc, only_ints3);
  // // Width (N)
  tcase_add_test(tc, ints_nwidth1);
  tcase_add_test(tc, ints_nwidth2);
  tcase_add_test(tc, ints_nwidth3);
  tcase_add_test(tc, ints_nwidth4);
  // // Width (*)
  tcase_add_test(tc, ints_astwidth1);
  tcase_add_test(tc, ints_astwidth2);
  tcase_add_test(tc, ints_astwidth3);
  // // Negative & positive ints
  tcase_add_test(tc, signed_ints1);
  tcase_add_test(tc, signed_ints2);
  tcase_add_test(tc, signed_ints3);
  tcase_add_test(tc, signed_ints4);

  // // // [%i] Specifier. It may be INT, OCT, HEX

  tcase_add_test(tc, spec_i_int1);
  tcase_add_test(tc, spec_i_int2);
  // // Mixed with chars & ints
  tcase_add_test(tc, spec_i_int3);
  tcase_add_test(tc, spec_i_int4);

  tcase_add_test(tc, spec_i_oct1);
  tcase_add_test(tc, spec_i_oct2);
  tcase_add_test(tc, spec_i_hex1);
  tcase_add_test(tc, spec_i_hex2);

  // // [%s]
  // // Width: (N) - parses N chars, (*) - пропустить строку
  // // OUT: res = 4 (корректно парсит все в разные строки)
  // // int res = sscanf("abobashlepafloppakoppa", "%5s %6s %6s %4s", s1, s2,
  // s3,
  // // s4); Precision, length - not applicable

  tcase_add_test(tc, strings1);
  tcase_add_test(tc, strings2);
  tcase_add_test(tc, strings4);
  tcase_add_test(tc, strings5);
  tcase_add_test(tc, strings6);
  tcase_add_test(tc, uint1);
  tcase_add_test(tc, uint2);
  tcase_add_test(tc, uint3);
  tcase_add_test(tc, uint4);
  tcase_add_test(tc, uint5);
  tcase_add_test(tc, uint6);
  tcase_add_test(tc, strings_mixed1);
  tcase_add_test(tc, strings_mixed2);
  tcase_add_test(tc, strings_mixed3);

  // // [%f] [%g] [%G]
  // // Width: (N) - parses N chars, (*) - пропустить строку
  // // Precision: take it into account while parsing AFTER (.)
  // // Length - l - long

  tcase_add_test(tc, floats1);
  tcase_add_test(tc, floats2);
  tcase_add_test(tc, floats3);
  tcase_add_test(tc, floats4);
  tcase_add_test(tc, floats5);

  tcase_add_test(tc, floats_sci1);
  tcase_add_test(tc, floats_sci2);
  tcase_add_test(tc, floats_sci3);
  tcase_add_test(tc, floats_sci4);
  tcase_add_test(tc, floats_sci5);

  // [%n] specifier

  tcase_add_test(tc, n1);

  tcase_add_test(tc, n2);
  tcase_add_test(tc, n3);
  tcase_add_test(tc, n4);
  tcase_add_test(tc, n5);

  tcase_add_test(tc, n2);
  tcase_add_test(tc, n3);
  tcase_add_test(tc, n4);
  tcase_add_test(tc, n5);

  tcase_add_test(tc, upeer_hex_base_version);
  tcase_add_test(tc, upeer_hex_overflow);
  tcase_add_test(tc, upeer_hex_0x);
  tcase_add_test(tc, upeer_hex_0X);
  tcase_add_test(tc, upeer_hex_empty);
  tcase_add_test(tc, upeer_hex_fail);
  tcase_add_test(tc, upeer_hex_spaces_tabs_sns);
  tcase_add_test(tc, upeer_hex_short);
  tcase_add_test(tc, upeer_hex_long);
  tcase_add_test(tc, upeer_hex_longlong);
  tcase_add_test(tc, upeer_hex_2x);
  tcase_add_test(tc, upeer_hex_nohex);
  tcase_add_test(tc, upeer_hex_lower);
  tcase_add_test(tc, upeer_hex_sign);
  tcase_add_test(tc, upper_hex_len);

  tcase_add_test(tc, lower_hex_base_version);
  tcase_add_test(tc, lower_hex_overflow);
  tcase_add_test(tc, lower_hex_0x);
  tcase_add_test(tc, lower_hex_0X);
  tcase_add_test(tc, lower_hex_empty);
  tcase_add_test(tc, lower_hex_fail);
  tcase_add_test(tc, lower_hex_spaces_tabs_sns);
  tcase_add_test(tc, lower_hex_short);
  tcase_add_test(tc, lower_hex_long);
  tcase_add_test(tc, lower_hex_longlong);
  tcase_add_test(tc, lower_hex_2x);
  tcase_add_test(tc, lower_hex_nohex);
  tcase_add_test(tc, lower_hex_lower);
  tcase_add_test(tc, lower_hex_sign);
  tcase_add_test(tc, lower_hex_len);

  tcase_add_test(tc, octal_base_version);
  tcase_add_test(tc, octal_overflow);
  tcase_add_test(tc, octal_0x);
  tcase_add_test(tc, octal_0X);
  tcase_add_test(tc, octal_empty);
  tcase_add_test(tc, octal_fail);
  tcase_add_test(tc, octal_spaces_tabs_sns);
  tcase_add_test(tc, octal_short);
  tcase_add_test(tc, octal_long);
  tcase_add_test(tc, octal_longlong);
  tcase_add_test(tc, octal_2x);
  tcase_add_test(tc, octal_nohex);
  tcase_add_test(tc, octal_lower);
  tcase_add_test(tc, octal_sign);
  tcase_add_test(tc, octal_len);

  tcase_add_test(tc, pointer1);
  tcase_add_test(tc, pointer2);
  tcase_add_test(tc, pointer3);
  tcase_add_test(tc, pointer4);

  tcase_add_test(tc, buff1);
  tcase_add_test(tc, buff2);
  tcase_add_test(tc, buff3);

  tcase_add_test(tc, perc1);
  tcase_add_test(tc, perc2);
  tcase_add_test(tc, perc3);

  tcase_add_test(tc, perc3);
  tcase_add_test(tc, perc5);

  tcase_add_test(tc, mixed_ptrs1);
  tcase_add_test(tc, mixed_ptrs2);
  tcase_add_test(tc, mixed_ptrs3);
  tcase_add_test(tc, mixed_ptrs4);
  tcase_add_test(tc, mixed_ptrs5);

#if !(defined(__APPLE__) || defined(__MACH__))
  tcase_add_test(tc, strings3);
  tcase_add_test(tc, perc4);
  tcase_add_test(tc, upeer_hex_star);
  tcase_add_test(tc, lower_hex_star);
  tcase_add_test(tc, octal_star);
#endif

  // Hard mixed tests

  tcase_add_test(tc, hard1);
  tcase_add_test(tc, hard3);
  tcase_add_test(tc, hard4);
  tcase_add_test(tc, hard5);

  suite_add_tcase(s, tc);

  return s;
}