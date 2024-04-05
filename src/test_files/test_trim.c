#include "test_main.h"

START_TEST(test_trim_1) {
  char s1[30] = "-?test, String!";
  char s3[] = "!?-";
  char s4[] = "test, String";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_2) {
  char s1[30] = "";
  char s3[] = "";
  char *s4 = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_3) {
  char *s1 = S21_NULL;
  char s3[] = "";
  char *s4 = S21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_4) {
  char s1[30] = "!!!3j2hl231j!?!";
  char s3[] = "!?";
  char s4[] = "3j2hl231j";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_5) {
  char *s1 = S21_NULL;
  char s3[] = "333";
  char *s4 = S21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_6) {
  char s1[30] = "test, String!";
  char s3[] = "?!";
  char *s4 = "test, String";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_7) {
  char *s1 = S21_NULL;
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_8) {
  char s1[30] = " test\tspecial\tspaces ";
  char s3[] = "";
  char s4[] = "test\tspecial\tspaces";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_9) {
  char s1[] = " test_   spaceshehe ";
  char *s3 = S21_NULL;
  char *s4 = "test_   spaceshehe";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_10) {
  char s1[] = " test_spaceshehe ";
  char *s3 = "";
  char *s4 = "test_spaceshehe";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

Suite *test_trim(void) {
  Suite *s = suite_create("\033[45m-=S21_TRIM=-\033[0m");
  TCase *tc = tcase_create("trim_tc");

  tcase_add_test(tc, test_trim_1);
  tcase_add_test(tc, test_trim_2);
  tcase_add_test(tc, test_trim_3);
  tcase_add_test(tc, test_trim_4);
  tcase_add_test(tc, test_trim_5);
  tcase_add_test(tc, test_trim_6);
  tcase_add_test(tc, test_trim_7);
  tcase_add_test(tc, test_trim_8);
  tcase_add_test(tc, test_trim_9);
  tcase_add_test(tc, test_trim_10);

  suite_add_tcase(s, tc);
  return s;
}
