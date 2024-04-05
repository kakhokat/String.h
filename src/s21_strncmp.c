#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0, check_break = 1;
  for (s21_size_t i = 0; i < n && check_break; i++) {
    if (str1[i] != str2[i]) {
      check_break = 0;
      res = str1[i] - str2[i];
    }
  }
  return res;
}