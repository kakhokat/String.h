#include "s21_sprintf.h"

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  configuration parameters = {0};
  va_list args;
  va_start(args, format);
  char *strStart = str;
  while (*format != '\0') {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      s21_memset(&parameters, 0, sizeof(configuration));
      format++;
      format = parse_flags(format, &parameters);
      format = parse_width(format, &parameters, args);
      format = parse_precision(format, &parameters, args);
      format = parse_len(format, &parameters);
      parameters.spec = *format;
      format++;
      char buffer[BUFFER] = {'\0'};
      spec_processing(buffer, &parameters, args);
      if (s21_strncmp(buffer, "\0", 1) == 0 && parameters.spec == 'c') {
        *str++ = *buffer;
      }
      for (int i = 0; buffer[i]; i++, str++) {
        *str = buffer[i];
      }

      if (parameters.spec == 'n') {
        int *spec_n = va_arg(args, int *);
        *spec_n = str - strStart;
      }
    }
  }
  *str = '\0';
  va_end(args);
  return str - strStart;
}

const char *parse_flags(const char *format, configuration *parameters) {
  char *flags = "-+ #0";
  while (s21_strchr(flags, *format)) {
    switch (*format) {
      case '-':
        parameters->minus = 1;
        break;
      case '+':
        parameters->plus = 1;
        break;
      case ' ':
        parameters->space = 1;
        break;
      case '#':
        parameters->hash = 1;
        break;
      case '0':
        parameters->zero = 1;
        break;
    }
    format++;
  }
  return format;
}
const char *parse_width(const char *format, configuration *parameters,
                        va_list args) {
  if (is_digit(*format)) {
    char temp[BUFFER] = {'\0'};
    int i = 0;
    while (is_digit(*format)) {
      temp[i++] = *format++;
    }
    parameters->width = str_to_int(temp);
  } else if (*format == '*') {
    parameters->width = va_arg(args, int);
    format++;
  }
  return format;
}
const char *parse_precision(const char *format, configuration *parameters,
                            va_list args) {
  if (*format == '.') {
    parameters->has_precision = 1;
    format++;
  }
  if (is_digit(*format)) {
    char temp[BUFFER] = {'\0'};
    int i = 0;
    while (is_digit(*format)) {
      temp[i++] = *format++;
    }
    parameters->precision = str_to_int(temp);
  } else if (*format == '*') {
    parameters->has_precision = 1;
    parameters->precision = va_arg(args, int);
    format++;
  }
  return format;
}
const char *parse_len(const char *format, configuration *parameters) {
  switch (*format) {
    case 'h':
      parameters->len = 'h';
      format++;
      break;
    case 'l':
      parameters->len = 'l';
      format++;
      break;
    case 'L':
      parameters->len = 'L';
      format++;
      break;
  }
  return format;
}

void precision_processing(char *buffer, configuration *parameters) {
  char temp[BUFFER] = {'\0'};
  int sign = 0;
  s21_size_t len = s21_strlen(buffer);
  if (buffer[0] == '-') {
    temp[0] = '-';
    len--;
    sign = 1;
  }
  if (len < (s21_size_t)parameters->precision) {
    int i = sign;
    for (; (s21_size_t)i <
           (s21_size_t)parameters->precision - len + (s21_size_t)sign;
         i++) {
      temp[i] = '0';
    }
    for (int j = sign; buffer[j]; i++, j++) {
      temp[i] = buffer[j];
    }
  }
  s21_strncpy(buffer, temp, s21_strlen(temp));
}
void flags_processing(char *buffer, configuration *parameters) {
  char temp[BUFFER + 1] = {'\0'};
  if (parameters->plus && !is_unsigned_spec(parameters) &&
      s21_strncmp(buffer, "(nil)", s21_strlen(buffer)) != 0) {
    if (buffer[0] == '-') {
      s21_strncpy(temp, buffer, s21_strlen(buffer));
    } else {
      temp[0] = '+';
      s21_strncpy(temp + 1, buffer, s21_strlen(buffer));
    }
    s21_strncpy(buffer, temp, s21_strlen(temp));
  } else if (parameters->space && buffer[0] != '-' &&
             !is_unsigned_spec(parameters)) {
    temp[0] = ' ';
    s21_strncpy(temp + 1, buffer, s21_strlen(buffer));
    s21_strncpy(buffer, temp, s21_strlen(temp));
  }
}
void width_processing(char *buffer, configuration *parameters) {
  char temp[BUFFER + 1] = {'\0'};
  if ((s21_size_t)parameters->width > s21_strlen(buffer)) {
    int difference = parameters->width - s21_strlen(buffer);
    if (!parameters->minus) {
      if ((buffer[0] == '-' || buffer[0] == '+') && parameters->zero) {
        temp[0] = buffer[0];
        s21_memset(temp + 1, '0', difference);
        s21_strncpy(temp + difference + 1, buffer + 1, s21_strlen(buffer + 1));
      } else {
        s21_memset(temp, parameters->zero ? '0' : ' ', difference);
        s21_strncpy(temp + difference, buffer, s21_strlen(buffer));
      }
    } else {
      s21_strncpy(temp, buffer, s21_strlen(buffer));
      s21_memset(temp + s21_strlen(buffer), ' ', difference);
    }
    s21_strncpy(buffer, temp, s21_strlen(temp));
  }
}
void spec_processing(char *buffer, configuration *parameters, va_list args) {
  if (parameters->spec == 'c') {
    spec_c(buffer, parameters, args);
  } else if (parameters->spec == 'd' || parameters->spec == 'i') {
    spec_i_d(buffer, parameters, args);
  } else if (parameters->spec == 'e' || parameters->spec == 'E') {
    spec_e(buffer, parameters, args);
  } else if (parameters->spec == 'f') {
    spec_f(buffer, parameters, args);
  } else if (parameters->spec == 'o') {
    spec_o(buffer, parameters, args);
  } else if (parameters->spec == 's') {
    spec_s(buffer, parameters, args);
  } else if (parameters->spec == 'u') {
    spec_u(buffer, parameters, args);
  } else if (parameters->spec == 'x' || parameters->spec == 'X') {
    spec_x(buffer, parameters, args);
  } else if (parameters->spec == 'p') {
    spec_p(buffer, parameters, args);
  } else if (parameters->spec == '%') {
    buffer[0] = '%';
  }
  if (parameters->spec == 'G' || parameters->spec == 'E' ||
      parameters->spec == 'X') {
    convert_to_capital(buffer);
  }
}

void spec_i_d(char *buffer, configuration *parameters, va_list args) {
  int64_t num = va_arg(args, int64_t);
  if (parameters->len == 0) {
    num = (int32_t)num;
  } else if (parameters->len == 'h') {
    num = (int16_t)num;
  }
  num_to_str(num, buffer, 10);
  precision_processing(buffer, parameters);

  if (parameters->precision == 0 && parameters->has_precision == 1 &&
      buffer[0] == '0' && is_num_spec(parameters)) {
    buffer[0] = '\0';
  }
  flags_processing(buffer, parameters);
  width_processing(buffer, parameters);
}

void spec_c(char *buffer, configuration *parameters, va_list args) {
  if (parameters->len == 'l') {
    wchar_t ch = va_arg(args, wchar_t);
    wchar_processing(ch, buffer, parameters);
  } else {
    char ch = va_arg(args, int);
    char_processing(ch, buffer, parameters);
  }
}
void char_processing(char ch, char *buffer, configuration *parameters) {
  if (parameters->width && parameters->minus) {
    buffer[0] = ch;
    for (int i = 1; i < parameters->width; i++) {
      buffer[i] = ' ';
    }
  } else if (parameters->width) {
    for (int i = 0; i < parameters->width - 1; i++) {
      buffer[i] = ' ';
    }
    buffer[parameters->width - 1] = ch;
  } else {
    buffer[0] = ch;
  }
}
void wchar_processing(wchar_t ch, char *buffer, configuration *parameters) {
  if (parameters->width && parameters->minus) {
    wcstombs(buffer, &ch, BUFFER);
    for (int i = 1; i < parameters->width; i++) {
      buffer[i] = ' ';
    }
  } else if (parameters->width) {
    for (int i = 0; i < parameters->width - 1; i++) {
      buffer[i] = ' ';
    }
    char temp[BUFFER] = {'\0'};
    wcstombs(temp, &ch, BUFFER);
    s21_strncat(buffer, temp, s21_strlen(temp));
  } else {
    buffer[0] = ch;
  }
}

void spec_f(char *buffer, configuration *parameters, va_list args) {
  long double num = 0;
  if (parameters->len == 'L') {
    num = va_arg(args, long double);
  } else {
    num = va_arg(args, double);
  }
  if (!parameters->has_precision) {
    parameters->precision = 6;
  }
  float_to_str(num, buffer, parameters);
  flags_processing(buffer, parameters);
  width_processing(buffer, parameters);
}

void spec_u(char *buffer, configuration *parameters, va_list args) {
  uint64_t num = va_arg(args, uint64_t);
  if (parameters->len == 'h') {
    num = (uint16_t)num;
  } else if (parameters->len == 0) {
    num = (uint32_t)num;
  }
  unum_to_str(num, buffer, 10);
  precision_processing(buffer, parameters);
  if (parameters->precision == 0 && parameters->has_precision == 1 &&
      buffer[0] == '0' && is_num_spec(parameters)) {
    buffer[0] = '\0';
  }
  flags_processing(buffer, parameters);
  width_processing(buffer, parameters);
}

void spec_o(char *buffer, configuration *parameters, va_list args) {
  uint64_t num = va_arg(args, uint64_t);
  if (parameters->len == 0) {
    num = (uint32_t)num;
  } else if (parameters->len == 'h') {
    num = (uint16_t)num;
  }
  buffer[0] = '0';
  if (num != 0) {
    unum_to_str(num, buffer + parameters->hash, 8);
  } else {
    unum_to_str(num, buffer, 8);
  }
  precision_processing(buffer, parameters);

  if (parameters->precision == 0 && parameters->has_precision == 1 &&
      buffer[0] == '0') {
    if (num != 0) {
      buffer[0] = '0';
    } else {
      buffer[0] = '\0';
    }
  }
  flags_processing(buffer, parameters);
  width_processing(buffer, parameters);
}

void spec_s(char *buffer, configuration *parameters, va_list args) {
  char temp[BUFFER] = {'\0'};
  if (parameters->len == 'l') {
    wchar_t *str = va_arg(args, wchar_t *);
    wcstombs(temp, str, BUFFER);
  } else {
    char *str = va_arg(args, char *);
    if (str) {
      s21_strncpy(temp, str, BUFFER);
    } else {
      s21_strncpy(temp, "(null)", BUFFER);
    }
  }
  string_processing(temp, buffer, parameters);
}

void string_processing(char *temp, char *buffer, configuration *parameters) {
  if (parameters->has_precision &&
      s21_strncmp("(null)", temp, s21_strlen("(null)")) != 0) {
    temp[parameters->precision] = '\0';
  }
  if (s21_strncmp("(null)", temp, s21_strlen("(null)")) == 0 &&
      parameters->precision < 6 && parameters->has_precision) {
    temp[0] = '\0';
  }
  int shift = (s21_size_t)parameters->width - s21_strlen(temp);
  if (parameters->minus && shift > 0) {
    s21_strncpy(buffer, temp, s21_strlen(temp));
    s21_memset(buffer + s21_strlen(temp), ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strncpy(buffer + shift, temp, s21_strlen(temp));
  } else {
    s21_strncpy(buffer, temp, s21_strlen(temp));
  }
}

void spec_x(char *buffer, configuration *parameters, va_list args) {
  uint64_t num = va_arg(args, uint64_t);
  if (parameters->len == 0) {
    num = (uint32_t)num;
  } else if (parameters->len == 'h') {
    num = (uint16_t)num;
  }
  if (num == 0 && parameters->has_precision) {
    buffer[0] = '\0';
  } else {
    unum_to_str(num, buffer, 16);
  }
  precision_processing(buffer, parameters);
  if (str_to_int(buffer) != 0 && parameters->hash) add_prefix(buffer);
  flags_processing(buffer, parameters);
  width_processing(buffer, parameters);
}

void spec_p(char *buffer, configuration *parameters, va_list args) {
  uint64_t pointer = va_arg(args, uint64_t);
  if (pointer == 0) {
    s21_strncpy(buffer, "(nil)", s21_strlen("(nil)"));
    parameters->space = 0;
  } else {
    unum_to_str(pointer, buffer, 16);
    precision_processing(buffer, parameters);
    add_prefix(buffer);
  }
  flags_processing(buffer, parameters);
  width_processing(buffer, parameters);
}

void spec_e(char *buffer, configuration *parameters, va_list args) {
  long double num;
  if (parameters->len == 'L') {
    num = va_arg(args, long double);
  } else {
    num = va_arg(args, double);
  }
  char sign = '+';
  int pow = 0;

  if ((int)num == 0) {
    sign = '-';
  }
  if ((int)num - num) {
    while ((int)num == 0) {
      num = num * 10.0;
      pow++;
    }
  } else {
    sign = '+';
  }
  while ((int)num / 10 != 0) {
    num = num / 10.0;
    pow++;
  }
  if (!parameters->has_precision) {
    parameters->precision = 6;
  }
  precision_processing(buffer, parameters);
  float_to_str(num, buffer, parameters);
  add_e(buffer, pow, sign);
  flags_processing(buffer, parameters);
  width_processing(buffer, parameters);
}

void add_e(char *buffer, int pow, char sign) {
  s21_strncat(buffer, "e", 2);
  int len = s21_strlen(buffer);
  buffer[len] = sign;
  buffer[len + 2] = '0' + pow % 10;
  pow /= 10;
  buffer[len + 1] = '0' + pow % 10;
}

int is_digit(int c) { return c >= '0' && c <= '9'; }
int is_unsigned_spec(configuration *parameters) {
  return parameters->spec == 'u' || parameters->spec == 'o' ||
         parameters->spec == 'x' || parameters->spec == 'X';
}
int is_num_spec(configuration *parameters) {
  return parameters->spec == 'd' || parameters->spec == 'i' ||
         parameters->spec == 'u' || parameters->spec == 'o' ||
         parameters->spec == 'x' || parameters->spec == 'X';
}

void unum_to_str(uint64_t num, char *buffer, int base) {
  char temp[BUFFER] = {'\0'};

  if (num == 0) {
    temp[BUFFER - 2] = '0';
  }

  char *alph = "0123456789abcdef";

  int i = BUFFER - 3;

  while (num > 0) {
    temp[i] = alph[num % base];
    i--;
    num /= base;
  }
  i++;
  for (int j = 0; temp[i]; j++, i++) {
    buffer[j] = temp[i];
  }
}
void num_to_str(int64_t num, char *buffer, int base) {
  char temp[BUFFER] = {'\0'};
  int j = 0;
  if (num < 0) {
    num = -num;
    buffer[0] = '-';
    j++;
  }

  if (num == 0) {
    temp[BUFFER - 2] = '0';
  }

  char *alph = "0123456789abcdef";

  int i = BUFFER - 3;

  while (num > 0) {
    temp[i] = alph[num % base];
    i--;
    num /= base;
  }
  i++;
  for (; temp[i]; j++, i++) {
    buffer[j] = temp[i];
  }
}
void float_to_str(long double num, char *buffer, configuration *parameters) {
  char temp[BUFFER] = {'\0'};
  char temp_float[BUFFER] = {'\0'};
  int sign = 0;
  if (num < 0) {
    num = -num;
    buffer[0] = '-';
    sign = 1;
  }

  long long int num_int_part = (long long int)num;
  long double num_float_part = num - (long double)num_int_part;
  long double num_float_part_rounded = num_float_part;

  for (int j = 0; j < parameters->precision; j++) {
    num_float_part_rounded *= 10;
  }
  num_float_part_rounded += 0.5;

  long long int num_float_part_rounded_int =
      (long long int)num_float_part_rounded;
  for (int j = 0; j < parameters->precision; j++) {
    num_float_part_rounded /= 10;
  }

  long double rounded_num = (long double)num_int_part + num_float_part_rounded;
  long long int rounded_num_int_part = (long long int)rounded_num;
  num_to_str(rounded_num_int_part, temp, 10);
  int i = s21_strlen(temp);
  if (parameters->precision || parameters->hash) {
    temp[i++] = '.';
  }
  if (parameters->precision > 0) {
    num_to_str(num_float_part_rounded_int, temp_float, 10);
  }
  s21_strncat(temp, temp_float, parameters->precision);
  s21_strncpy(buffer + sign, temp, s21_strlen(temp));
}
int str_to_int(const char *str) {
  int result = 0;
  int sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  }
  while (*str != '\0') {
    result = result * 10 + (*str - '0');
    str++;
  }
  return result * sign;
}

void convert_to_capital(char *buffer) {
  while (*buffer) {
    if (*buffer >= 'a' && *buffer <= 'z') *buffer = *buffer - 32;
    buffer++;
  }
}
void add_prefix(char *buffer) {
  char temp[BUFFER] = {'\0'};
  temp[0] = '0';
  temp[1] = 'x';
  s21_strncat(temp, buffer, s21_strlen(buffer));
  s21_strncpy(buffer, temp, s21_strlen(temp));
}
