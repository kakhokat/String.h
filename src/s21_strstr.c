#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  if (*needle == '\0') {
    result = (char *)haystack;
  } else {
    while (*haystack != '\0' && result == S21_NULL) {
      const char *haystackPtr = haystack;
      const char *needlePtr = needle;

      while (*needlePtr != '\0' && *haystackPtr == *needlePtr) {
        haystackPtr++;
        needlePtr++;
      }

      if (*needlePtr == '\0') {
        result = (char *)haystack;
      }

      haystack++;
    }
  }

  return result;
}
