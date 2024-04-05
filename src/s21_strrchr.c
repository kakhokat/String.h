#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  unsigned char character = '\0';
  int counter = 0;
  int searching_character = 0;
  if (str != NULL) {
    character = *(str);
  }
  while (character != '\0') {
    if (character == c) {
      searching_character = counter;
    }
    character = *(str++);
    counter++;
  }
  if (c == '\0') {
    searching_character = counter + 1;
  }
  return searching_character > 0 || c == '\0'
             ? (char *)(str - (counter - searching_character) - 1)
             : S21_NULL;
}