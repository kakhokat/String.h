#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int ans = 0;
  int is_diff = 0;
  char *p_char_to_compare1 = (char *)str1;
  char *p_char_to_compare2 = (char *)str2;
  while (n-- && !is_diff) {
    if (*p_char_to_compare1 != *p_char_to_compare2) {
      ans = *p_char_to_compare1 > *p_char_to_compare2 ? 1 : -1;
      is_diff = 1;
    }
    p_char_to_compare1++;
    p_char_to_compare2++;
  }
  return ans;
}