#include "test_main.h"

START_TEST(strlen_1) {
  char str[] = "Test, hello, Phrase";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_2) {
  char str[] =
      "test "
      "phrase";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_3) {
  char str[] = "Test, hello, Phrase";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_4) {
  char str[] = "\0";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_5) {
  char str[] = "";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_6) {
  char str[] = "12401247823170421";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_7) {
  char str[] = "luhcrqrljkhqwriJLHLJR#lrc2ouhqlj";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_8) {
  char str[] = "            ";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_9) {
  char str[] = "\n\n\n\nsfhjsafhljsn\n\nlololol\n\n\n\n\n";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_10) {
  char str[] = "\0hel1231lo\n";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_11) {
  char str[] = "\thellow\t";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_12) {
  char str[] = "\0hell3o";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strlen_13) {
  char str[] = "hel3113212313lo \0";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

Suite *test_strlen(void) {
  Suite *s = suite_create("\033[45m-=S21_STRLEN=-\033[0m");
  TCase *tc = tcase_create("strlen_tc");

  tcase_add_test(tc, strlen_1);
  tcase_add_test(tc, strlen_2);
  tcase_add_test(tc, strlen_3);
  tcase_add_test(tc, strlen_4);
  tcase_add_test(tc, strlen_5);
  tcase_add_test(tc, strlen_6);
  tcase_add_test(tc, strlen_7);
  tcase_add_test(tc, strlen_8);
  tcase_add_test(tc, strlen_9);
  tcase_add_test(tc, strlen_10);
  tcase_add_test(tc, strlen_11);
  tcase_add_test(tc, strlen_12);
  tcase_add_test(tc, strlen_13);

  suite_add_tcase(s, tc);
  return s;
}
