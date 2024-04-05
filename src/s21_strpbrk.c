#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  bool flag = true;
  char *new_str = S21_NULL;
  for (int i = 0; str1[i] != '\0' && flag; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        flag = false;
        new_str = (char *)str1 + i;
      }
    }
  }
  return new_str;
}