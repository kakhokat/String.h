#include "s21_string.h"

int first_nonspace(const char *str) {
  int count = 0;
  while (str[count] < 33 && str[count] != '\0') {
    count++;
  }
  return count;
}

int last_nonspace(const char *str) {
  int count = s21_strlen(str) - 1;
  while (str[count] < 33 && count > 0) {
    count--;
  }
  return count;
}

void *s21_trim(const char *str, const char *trim_chars) {
  char *result = S21_NULL;
  if (str != S21_NULL && trim_chars != S21_NULL) {
    int count_ch_str = s21_strlen(str);
    int count_ch_trim_chars = s21_strlen(trim_chars);
    int counter = 0, flag = 0, start = first_nonspace(str),
        end = last_nonspace(str);
    char *new_str = (char *)calloc(count_ch_str + 1, sizeof(char));
    for (int i = start; i <= end; i++) {
      for (int j = 0; j < count_ch_trim_chars; j++) {
        if (str[i] == trim_chars[j] && trim_chars[j] != ' ') {
          flag = 1;
        }
      }
      if (flag == 0) {
        new_str[counter] = str[i];
        counter++;
      }
      flag = 0;
    }

    result = new_str;
  } else if (str != S21_NULL && trim_chars == S21_NULL) {
    int count_ch_str = s21_strlen(str), count = 0;
    int start = first_nonspace(str), end = last_nonspace(str);
    char *new_str = (char *)calloc(count_ch_str + 1, sizeof(char));
    for (int i = start; i <= end; i++) {
      new_str[count] = str[i];
      count++;
    }
    result = new_str;
  }
  return (void *)result;
}