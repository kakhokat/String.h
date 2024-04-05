#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  void *new_dest = dest;
  while (n--) {
    *(char *)dest = *(char *)src;
    dest = (char *)dest + 1;
    src = (char *)src + 1;
  }
  return new_dest;
}