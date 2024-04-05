#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>
#include <stdint.h>
#include <wchar.h>

typedef struct {
  int minus;
  int plus;
  int space;
  int hash;

  int zero;
  int width;
  int has_precision;
  int precision;
  char len;
  char spec;
} configuration;

int s21_sprintf(char *str, const char *format, ...);

const char *parse_flags(const char *format, configuration *parameters);

const char *parse_width(const char *format, configuration *parameters,
                        va_list args);

const char *parse_precision(const char *format, configuration *parameters,
                            va_list args);

const char *parse_len(const char *format, configuration *parameters);

void spec_processing(char *buffer, configuration *parameters, va_list args);

void precision_processing(char *buffer, configuration *parameters);

void flags_processing(char *buffer, configuration *parameters);

void width_processing(char *buffer, configuration *parameters);

void spec_i_d(char *buffer, configuration *parameters, va_list args);

void spec_c(char *buffer, configuration *parameters, va_list args);

void char_processing(char ch, char *buffer, configuration *parameters);

void wchar_processing(wchar_t ch, char *buffer, configuration *parameters);

void spec_f(char *buffer, configuration *parameters, va_list args);

void spec_u(char *buffer, configuration *parameters, va_list args);

void spec_o(char *buffer, configuration *parameters, va_list args);

void spec_s(char *buffer, configuration *parameters, va_list args);

void string_processing(char *temp, char *buffer, configuration *parameters);

void spec_x(char *buffer, configuration *parameters, va_list args);

void spec_p(char *buffer, configuration *parameters, va_list args);

void spec_e(char *buffer, configuration *parameters, va_list args);

void add_e(char *buffer, int pow, char sign);

void num_to_str(int64_t num, char *buffer, int base);

void unum_to_str(uint64_t num, char *buffer, int base);

void float_to_str(long double num, char *buffer, configuration *parameters);

int str_to_int(const char *str);

int is_digit(int c);

int is_num_spec(configuration *parameters);

int is_unsigned_spec(configuration *parameters);

void add_prefix(char *buffer);

void convert_to_capital(char *buffer);
#endif