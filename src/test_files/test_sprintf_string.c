#include <wchar.h>

#include "test_main.h"
START_TEST(sprintf_1_string) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "smthiswrtn %s smthiswrtn";
  char *val = "hello this is the first test phrase";

  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s smthiswrtn %s smthiswrtn %s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s smthiswrtn %s smthiswrtn %s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_string) {
  char str1[100];
  char str2[100];
  char *str3 = "smthiswrtn %ls smthiswrtn2";
  wchar_t *val = L"3wtf80";
  sprintf(str1, str3, val);
  s21_sprintf(str2, str3, val);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%3s smthiswrtn %5s smthiswrtn %10s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5s smthiswrtn %.23s smthiswrtn %3.s TEST %.s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  char *val4 = "test phrase again and again...";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5s smthiswrtn %-.8s smthiswrtn %-7s TEST %-.s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  char *val4 = "test phrase again and again...";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%0s smthiswrtn %0.s smthiswrtn %0.0s TEST %0s GOD %.s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  char *val4 = "test phrase again and again...";
  char *val5 = "another one?";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%+s smthiswrtn %+3.s smthiswrtn %5.7s TEST %10s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  char *val4 = "test phrase again and again...";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_10_string) {
  char str1[200];
  char str2[200];
  char *str3 =
      "%s smthiswrtn %3.s smthiswrtn %5.7s TEST %10s %#s %-s %+s %.s % .s";
  char *val = NULL;
  wchar_t *val2 = NULL;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val2),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_string) {
  char str1[200];
  char str2[200];
  char *str3 = "% s smthiswrtn % 3.s smthiswrtn % 5.7s TEST % 10s GOD %.s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  char *val4 = "test phrase again and again...";
  char *val5 = "another one?";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%+s smthiswrtn %+3.s smthiswrtn %+5.7s TEST %+10s GOD %+.s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  char *val4 = "test phrase again and again...";
  char *val5 = "another one?";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_13_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%#s smthiswrtn %#3s smthiswrtn %#5.7s TEST %#.7s Oof %#.s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  char *val4 = "test phrase again and again...";
  char *val5 = "another one?";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%0s smthiswrtn %06s smthiswrtn %05.7s TEST %0.7s Oof %0.s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  char *val4 = "test phrase again and again...";
  char *val5 = "another one?";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_15_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%*s smthiswrtn %-*s smthiswrtn %*.*s TEST %.*s";
  char *val = "hello this is the first test phrase";
  char *val2 = "testphrase";
  char *val3 = "test phrase again";
  char *val4 = "test phrase again and again...";
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s %s %s %% %d";
  char *val = "1232131s";
  char *val2 = "\0";
  int val3 = 65;
  char *val4 = "hehehe";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val4, val3),
                   s21_sprintf(str2, str3, val, val2, val4, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_string) {
  char str1[1024];
  char str2[1024];
  char *str3 =
      "%0.0s %1.0s %2.0s %3.0s %5.0s %6.0s %7.0s %0.3s %0.7s %3.2s %3.7s %7.3s";
  char *val = NULL;
  s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val, val, val,
              val);
  sprintf(str1, str3, val, val, val, val, val, val, val, val, val, val, val,
          val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *test_sprintf_string(void) {
  Suite *s = suite_create("\033[45m-=S21_SPRINTF_STRING=-\033[0m");
  TCase *tc = tcase_create("sprintf_tc");

  tcase_add_test(tc, sprintf_1_string);
  tcase_add_test(tc, sprintf_2_string);
  tcase_add_test(tc, sprintf_3_string);
  tcase_add_test(tc, sprintf_4_string);
  tcase_add_test(tc, sprintf_5_string);
  tcase_add_test(tc, sprintf_6_string);
  tcase_add_test(tc, sprintf_7_string);
  tcase_add_test(tc, sprintf_8_string);
  tcase_add_test(tc, sprintf_9_string);
  tcase_add_test(tc, sprintf_10_string);
  tcase_add_test(tc, sprintf_11_string);
  tcase_add_test(tc, sprintf_12_string);
  tcase_add_test(tc, sprintf_13_string);
  tcase_add_test(tc, sprintf_14_string);
  tcase_add_test(tc, sprintf_15_string);
  tcase_add_test(tc, sprintf_16_string);
  tcase_add_test(tc, sprintf_17_string);

  suite_add_tcase(s, tc);
  return s;
}
