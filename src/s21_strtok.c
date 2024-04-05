#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *lastToken = S21_NULL;
  char *token = S21_NULL;
  bool flag = true;
  if (str == S21_NULL && delim[0] == '\0') {
    flag = false;
  }
  if (flag) {
    if (str != S21_NULL) {
      lastToken = str;
    }
    while (*lastToken && s21_strchr(delim, *lastToken)) {
      lastToken++;
    }

    if (*lastToken != '\0') {
      token = lastToken;
      while (*lastToken && !s21_strchr(delim, *lastToken)) {
        lastToken++;
      }
      if (*lastToken != '\0') {
        *lastToken = '\0';
        lastToken++;
      }
    }
  }
  return token;
}