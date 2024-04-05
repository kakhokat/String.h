#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  unsigned char character = '\0';
  if (str != S21_NULL) {
    character = *(str++);
  }
  while (character != c && character != '\0') {
    character = *(str++);
  }
  return character == c ? (char *)(str - 1) : S21_NULL;
}