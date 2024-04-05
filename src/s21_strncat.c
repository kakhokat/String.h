#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *tmp = dest + s21_strlen(dest);
  while (*src != '\0' && n--) {
    *tmp++ = *src++;
    *tmp = '\0';
  }
  return dest;
}
