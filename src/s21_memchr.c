#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *new_str = (char *)str;
  char ch = (char)c;
  int consists = 0;
  while ((n-- && !consists) && (*new_str != '\0' || ch == '\0')) {
    if (*new_str == ch) {
      consists = 1;
      new_str--;
    }
    new_str++;
  }
  return (consists ? (void *)new_str : S21_NULL);
}