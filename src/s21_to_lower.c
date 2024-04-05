#include "s21_string.h"

void *s21_to_lower(const char *str) {
  bool flag = true;
  char *new_str = (char *)str;
  if (new_str == S21_NULL) {
    flag = false;
  }
  if (flag == true) {
    size_t length = s21_strlen(str);
    new_str = (char *)calloc(sizeof(char), length + 1);
    s21_strncpy(new_str, str, length);

    for (size_t i = 0; i < length; i++) {
      if (new_str[i] >= 'A' && new_str[i] <= 'Z') {
        new_str[i] = new_str[i] + 32;
      }
    }
  }
  return (void *)new_str;
}