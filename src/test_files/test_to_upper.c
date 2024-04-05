#include "test_main.h"

START_TEST(test_to_upper_1) {
  char s1[30] = "Hello, world!";
  void *s2 = s21_to_upper(s1);
  char s3[] = "HELLO, WORLD!";
  ck_assert_pstr_eq(s3, (const char *)s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_to_upper_2) {
  char s1[30] = "\nh\t\\g123123";
  void *s2 = s21_to_upper(s1);
  char s3[] = "\nH\t\\G123123";
  ck_assert_pstr_eq(s3, (const char *)s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_to_upper_3) {
  char s1[30] = "ALL UPPER";
  void *s2 = s21_to_upper(s1);
  char s3[] = "ALL UPPER";
  ck_assert_pstr_eq(s3, (const char *)s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_to_upper_4) {
  char s1[30] = "abcdefghijklmnopqrstuvwxyz";
  void *s2 = s21_to_upper(s1);
  char s3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  ck_assert_pstr_eq(s3, (const char *)s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_to_upper_5) {
  char s1[30] = "_?};!234";
  void *s2 = s21_to_upper(s1);
  char s3[] = "_?};!234";
  ck_assert_pstr_eq(s3, (const char *)s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_to_upper_6) {
  char *s1 = S21_NULL;
  void *s2 = s21_to_upper(s1);
  char *s3 = S21_NULL;
  ck_assert_pstr_eq(s3, (const char *)s2);
  if (s2) free(s2);
}
END_TEST

Suite *test_to_upper(void) {
  Suite *s = suite_create("\033[45m-=S21_TO_UPPER=-\033[0m");
  TCase *tc = tcase_create("to_upper_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_to_upper_1);
  tcase_add_test(tc, test_to_upper_2);
  tcase_add_test(tc, test_to_upper_3);
  tcase_add_test(tc, test_to_upper_4);
  tcase_add_test(tc, test_to_upper_5);
  tcase_add_test(tc, test_to_upper_6);

  suite_add_tcase(s, tc);
  return s;
}
