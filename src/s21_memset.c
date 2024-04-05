#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  void *new_str = str;
  char ch = (char)c;
  while (n--) {
    *(char *)str = ch;
    str = (char *)str + 1;
  }
  return new_str;
}