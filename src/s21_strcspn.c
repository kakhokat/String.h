#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i;
  bool flag = true;
  s21_size_t count = 0;
  s21_size_t j = 0;
  for (i = 0; (i < s21_strlen(str1) && j < s21_strlen(str2)) && (flag); i++) {
    if (str1[i] != str2[j]) {
      count++;
    } else {
      flag = false;
      j++;
    }
  }
  return str2[0] == '\0' ? s21_strlen(str1) : count;
}