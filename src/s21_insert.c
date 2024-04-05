#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  bool flag = true;
  s21_size_t i = -1;

  char *new_str = S21_NULL;
  if (str == S21_NULL || src == S21_NULL || start_index == i) {
    flag = false;
  }
  if (flag == true && start_index <= (s21_strlen(src) + s21_strlen(str))) {
    new_str =
        (char *)malloc((s21_strlen(str) + s21_strlen(src) + 1) * sizeof(char));
    s21_strncpy(new_str, src, start_index);
    s21_strncpy(new_str + start_index, str, s21_strlen(str));
    s21_strncpy(new_str + start_index + s21_strlen(str), src + start_index,
                s21_strlen(src) - start_index);
    new_str[s21_strlen(src) + s21_strlen(str)] = '\0';
  }
  return new_str;
}
