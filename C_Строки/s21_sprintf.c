#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *ptr = str;

  while (*format) {
    if (*format != '%') {
      *ptr++ = *format++;
      continue;
    }

    format++;
    s21_format fmt = {0};
    s21_parse_format(&format, args, &fmt);

    switch (fmt.specifier) {
      case 'd':
      case 'i':
        s21_integer(&ptr, args, &fmt);
        break;
      case 'u':
      case 'o':
      case 'x':
      case 'X':
        s21_unsigned(&ptr, args, &fmt);
        break;
      case 'f':
      case 'e':
      case 'E':
      case 'g':
      case 'G':
        s21_float(&ptr, args, &fmt);
        break;
      case 'c':
        s21_char(&ptr, args, &fmt);
        break;
      case 's':
        s21_string(&ptr, args, &fmt);
        break;
      case '%':
        *ptr++ = '%';
        break;
      case 'p':
        s21_pointer(&ptr, args, &fmt);
        break;
      default:
        *ptr++ = '%';
        *ptr++ = fmt.specifier;
        break;
    }
  }

  *ptr = '\0';
  va_end(args);
  return ptr - str;
}

void s21_parse_format(const char **format, va_list args, s21_format *fmt) {
  while (1) {
    if (**format == '-')
      fmt->flags[0] = 1;
    else if (**format == '+')
      fmt->flags[1] = 1;
    else if (**format == ' ')
      fmt->flags[2] = 1;
    else if (**format == '0')
      fmt->flags[3] = 1;
    else if (**format == '#')
      fmt->flags[4] = 1;
    else
      break;
    (*format)++;
  }

  if (**format == '*') {
    fmt->width = va_arg(args, int);
    if (fmt->width < 0) {
      fmt->flags[0] = 1;
      fmt->width = -fmt->width;
    }
    (*format)++;
  } else {
    while (**format >= '0' && **format <= '9') {
      fmt->width = fmt->width * 10 + (**format - '0');
      (*format)++;
    }
  }

  if (**format == '.') {
    (*format)++;
    fmt->precision = 0;
    if (**format == '*') {
      fmt->precision = va_arg(args, int);
      (*format)++;
    } else {
      while (**format >= '0' && **format <= '9') {
        fmt->precision = fmt->precision * 10 + (**format - '0');
        (*format)++;
      }
    }
  } else {
    fmt->precision = -1;
  }

  if (**format == 'l') {
    fmt->length = 'l';
    (*format)++;
  }
  if (**format == 'h') {
    fmt->length = 'h';
    (*format)++;
  }
  if (**format == 'L') {
    fmt->length = 'L';
    (*format)++;
  }

  fmt->specifier = **format;
  if (fmt->specifier) (*format)++;
}

void s21_integer(char **ptr, va_list args, const s21_format *fmt) {
  long num;

  switch (fmt->length) {
    case 'h':
      num = (short)va_arg(args, int);
      break;
    case 'l':
      num = va_arg(args, long);
      break;
    default:
      num = va_arg(args, int);
      break;
  }

  char num_buf[64];
  int num_len = 0;
  int sign_char = 0;
  int base = 10;

  if (fmt->precision == 0 && num == 0) {
    num_buf[0] = '\0';
    num_len = 0;
  } else {
    num_len = s21_convert_integer(num, num_buf, base, 0);
  }

  if (num >= 0) {
    if (fmt->flags[1])
      sign_char = '+';
    else if (fmt->flags[2])
      sign_char = ' ';
  }
  s21_format_number(ptr, num_buf, num_len, fmt, sign_char);
}

int s21_convert_integer(long num, char *str, int base, int uppercase) {
  int i = 0;
  int is_negative = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return i;
  }

  if (num < 0) {
    is_negative = 1;
    num = -num;
  }

  while (num != 0) {
    int rem = num % base;
    char c;
    if (rem > 9) {
      c = (rem - 10) + (uppercase ? 'A' : 'a');
    } else {
      c = rem + '0';
    }
    str[i++] = c;
    num /= base;
  }

  if (is_negative) {
    str[i++] = '-';
  }

  str[i] = '\0';
  s21_reverse(str, i);
  return i;
}

void s21_reverse(char *str, int length) {
  int start = 0, end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

void s21_format_number(char **ptr, const char *num_buf, int num_len,
                       const s21_format *fmt, int sign_char) {
  int padding = 0;
  int total_len = num_len + (sign_char ? 1 : 0);

  if (fmt->precision > num_len) {
    padding = fmt->precision - num_len;
    total_len += padding;
  }

  if (fmt->width > total_len && !fmt->flags[0]) {
    s21_memset(*ptr, fmt->flags[3] ? '0' : ' ', fmt->width - total_len);
    *ptr += fmt->width - total_len;
  }

  if (sign_char) *(*ptr)++ = sign_char;
  for (int i = 0; i < fmt->prefix_len; i++) *(*ptr)++ = fmt->prefix[i];

  if (padding > 0) {
    s21_memset(*ptr, '0', padding);
    *ptr += padding;
  }

  for (int i = 0; i < num_len; i++) *(*ptr)++ = num_buf[i];

  if (fmt->flags[0] && fmt->width > total_len) {
    s21_memset(*ptr, ' ', fmt->width - total_len);
    *ptr += fmt->width - total_len;
  }
}

void s21_unsigned(char **ptr, va_list args, s21_format *fmt) {
  unsigned long num;

  switch (fmt->length) {
    case 'h':
      num = (unsigned short)va_arg(args, unsigned int);
      break;
    case 'l':
      num = va_arg(args, unsigned long);
      break;
    default:
      num = va_arg(args, unsigned int);
  }

  char num_buf[64];
  int num_len = 0;
  int base = 10;
  if (fmt->specifier == 'o') {
    base = 8;
    if (fmt->flags[4] && num != 0) {
      fmt->prefix[0] = '0';
      fmt->prefix_len = 1;
    }
  } else if (fmt->specifier == 'x' || fmt->specifier == 'X') {
    base = 16;
    if (fmt->flags[4] && num != 0) {
      fmt->prefix[0] = '0';
      fmt->prefix[1] = fmt->specifier == 'x' ? 'x' : 'X';
      fmt->prefix_len = 2;
    }
  }

  if (fmt->precision == 0 && num == 0) {
    num_buf[0] = '\0';
    num_len = 0;
  } else {
    num_len = s21_convert_integer(num, num_buf, base, fmt->specifier == 'X');
  }
  s21_format_number(ptr, num_buf, num_len, fmt, 0);
}

void s21_float(char **ptr, va_list args, const s21_format *fmt) {
  double num;

  if (fmt->length == 'L') {
    long double ld_num = va_arg(args, long double);
    num = (double)ld_num;
  } else {
    num = va_arg(args, double);
  }
  char num_buf[128] = {0};
  int num_len = 0;
  int sign_char = 0;
  int precision = fmt->precision < 0 ? 6 : fmt->precision;

  if (isinf(num)) {
    const char *inf_str =
        (num < 0) ? "-inf"
                  : (fmt->flags[1] ? "+inf" : (fmt->flags[2] ? " inf" : "inf"));
    num_len = s21_strlen(inf_str);
    s21_strncpy(num_buf, inf_str, num_len + 1);
  } else if (isnan(num)) {
    s21_strncpy(num_buf, "nan", 4);
    num_len = 3;
  } else {
    if (num >= 0 || (num == 0.0 && !signbit(num))) {
      if (fmt->flags[1])
        sign_char = '+';
      else if (fmt->flags[2])
        sign_char = ' ';
    }

    switch (fmt->specifier) {
      case 'f':
        num_len = s21_convert_float(num, num_buf, precision);
        break;
      case 'e':
      case 'E':
        num_len =
            s21_convert_float_e(num, num_buf, precision, fmt->specifier == 'E');
        break;
      case 'g':
      case 'G':
        num_len = s21_convert_float_g(num, num_buf, precision,
                                      fmt->specifier == 'G', fmt->flags[4]);
        break;
    }
  }

  s21_format_number(ptr, num_buf, num_len, fmt, sign_char);
}

void s21_char(char **ptr, va_list args, const s21_format *fmt) {
  if (fmt->length == 'l') {
    wint_t wc = va_arg(args, wint_t);
    char mb_buf[MB_LEN_MAX];
    mbstate_t state = {0};

    s21_size_t len = wcrtomb(mb_buf, wc, &state);
    s21_format_number(ptr, mb_buf, (int)len, fmt, 0);
  } else {
    char c = (char)va_arg(args, int);
    char num_buf[1] = {c};
    s21_format_number(ptr, num_buf, 1, fmt, 0);
  }
}

int s21_convert_float(long double num, char *str, int precision) {
  int i = 0, is_negative = (num < 0) || (num == 0.0 && signbit(num)), base = 10,
      is_uppercase = 0;

  if (is_negative) {
    str[i++] = '-';
    num = -num;
  }

  if (num == 0.0) {
    str[i++] = '0';
    if (precision > 0) {
      str[i++] = '.';
      while (precision-- > 0) str[i++] = '0';
    }
  } else {
    double int_part_d, fractional_part = modf(num, &int_part_d), rounding = 0.5;
    long int_part = (long)int_part_d;

    for (int j = 0; j < precision; j++) {
      rounding /= 10.0;
    }
    fractional_part += rounding;

    if (fractional_part >= 1.0) {
      fractional_part -= 1.0;
      int_part++;
    }

    i += s21_convert_integer(int_part, str + i, base, is_uppercase);

    if (precision > 0) {
      str[i++] = '.';
      for (int j = 0; j < precision; j++) {
        fractional_part *= 10;
        int digit = (int)fractional_part;
        str[i++] = digit + '0';
        fractional_part -= digit;
      }
    }
  }
  str[i] = '\0';
  return i;
}

int s21_convert_float_e(double num, char *str, int precision, int uppercase) {
  int exponent = 0;

  if (num != 0.0) {
    exponent = s21_exponent(num);
    num /= s21_pow(10.0, exponent);
  } else {
    exponent = 0;
  }

  int len = s21_convert_float(num, str, precision);
  str[len++] = uppercase ? 'E' : 'e';
  str[len++] = exponent >= 0 ? '+' : '-';
  exponent = abs(exponent);
  if (exponent < 10) {
    str[len++] = '0';
    str[len++] = exponent + '0';
  } else {
    char exp_buf[4];
    int exp_len = s21_convert_integer(exponent, exp_buf, 10, 0);
    for (int i = 0; i < exp_len; i++) str[len++] = exp_buf[i];
  }

  str[len] = '\0';
  return len;
}

int s21_exponent(double num) {
  if (num < 0) num = -num;
  int exponent = 0;

  if (num < 1.0) {
    while (num < 1.0 && num != 0.0) {
      num *= 10.0;
      exponent--;
    }
  } else {
    while (num >= 10.0) {
      num /= 10.0;
      exponent++;
    }
  }

  return exponent;
}

double s21_pow(double base, int exponent) {
  double result = 1.0;
  int negative = exponent < 0;
  int n = negative ? -exponent : exponent;

  while (n > 0) {
    if (n % 2 == 1) {
      result *= base;
    }
    base *= base;
    n /= 2;
  }

  return negative ? 1.0 / result : result;
}

int s21_convert_float_g(double num, char *str, int precision, int uppercase,
                        int is_sharp) {
  if (precision == 0) precision = 1;
  if (precision == -1) precision = 6;

  int exponent = (num == 0) ? 0 : s21_exponent(num);
  char *dot_pos = s21_strchr(str, '.');
  int len = 0;

  if (fabs(num) < 1e-4 || fabs(num) >= 1e6) {
    len = s21_convert_float_e(num, str, precision - 2, uppercase);
  } else {
    int decimal_places = precision - 1 - exponent;
    if (decimal_places < 0) decimal_places = 0;
    len = s21_convert_float(num, str, decimal_places);
  }

  if (!is_sharp) {
    dot_pos = s21_strchr(str, '.');
    if (dot_pos) {
      char *end = str + len - 1;
      while (end > dot_pos && *end == '0') {
        *end-- = '\0';
        len--;
      }
      if (end == dot_pos) {
        *dot_pos = '\0';
        len--;
      }
    }
  }

  return len;
}

void s21_string(char **ptr, va_list args, const s21_format *fmt) {
  char *temp_buffer = S21_NULL;
  char *s = S21_NULL;

  if (fmt->length == 'l') {
    wchar_t *ws = va_arg(args, wchar_t *);
    if (!ws) {
      s = "(null)";
    } else {
      temp_buffer = s21_wide_string(ws, fmt->precision);
      s = temp_buffer ? temp_buffer : "(null)";
    }
  } else {
    s = va_arg(args, char *);
    if (!s) s = "(null)";
  }

  int num_len = s21_string_length(s, fmt->precision);
  s21_output_string(ptr, s, num_len, fmt);

  if (temp_buffer) {
    free(temp_buffer);
  }
}

char *s21_wide_string(const wchar_t *ws, int max_bytes) {
  if (!ws) return S21_NULL;

  mbstate_t state = {0};
  s21_size_t required_bytes = 0;
  const wchar_t *p = ws;
  int error = 0;

  while (*p != L'\0') {
    char buf[MB_LEN_MAX];
    s21_size_t n = wcrtomb(buf, *p, &state);
    if (n == (s21_size_t)-1) {
      error = 1;
      break;
    }
    if (max_bytes >= 0 && required_bytes + n > (s21_size_t)max_bytes) {
      break;
    }
    required_bytes += n;
    p++;
  }

  if (error) return S21_NULL;

  char *buffer = (char *)malloc(required_bytes + 1);
  if (!buffer) return S21_NULL;

  state = (mbstate_t){0};
  char *dst = buffer;
  p = ws;
  s21_size_t bytes_written = 0;
  while (bytes_written < required_bytes && *p) {
    s21_size_t n = wcrtomb(dst, *p, &state);
    if (n == (s21_size_t)-1) {
      free(buffer);
      return S21_NULL;
    }
    dst += n;
    bytes_written += n;
    p++;
  }
  *dst = '\0';
  return buffer;
}

int s21_string_length(const char *s, int precision) {
  int len = s21_strlen(s);
  if (precision >= 0 && len > precision) {
    len = precision;
  }
  return len;
}

void s21_output_string(char **ptr, const char *s, int num_len,
                       const s21_format *fmt) {
  if (fmt->width > num_len && !fmt->flags[0]) {
    s21_memset(*ptr, ' ', fmt->width - num_len);
    *ptr += fmt->width - num_len;
  }

  for (int i = 0; i < num_len; i++) {
    *(*ptr)++ = s[i];
  }

  if (fmt->flags[0] && fmt->width > num_len) {
    s21_memset(*ptr, ' ', fmt->width - num_len);
    *ptr += fmt->width - num_len;
  }
}

void s21_pointer(char **ptr, va_list args, const s21_format *fmt) {
  void *pointer = va_arg(args, void *);

  if (pointer == S21_NULL) {
    char *nil_str = "(nil)";
    int nil_len = 5;

    s21_format nil_fmt = *fmt;
    nil_fmt.prefix_len = 0;
    nil_fmt.flags[3] = 0;
    nil_fmt.precision = -1;

    s21_output_string(ptr, nil_str, nil_len, &nil_fmt);
  } else {
    char num_buf[20];
    int num_len = 0;
    uintptr_t num = (uintptr_t)pointer;

    s21_format ptr_fmt = *fmt;
    ptr_fmt.flags[4] = 1;
    ptr_fmt.prefix[0] = '0';
    ptr_fmt.prefix[1] = 'x';
    ptr_fmt.prefix_len = 2;

    num_len = s21_convert_integer(num, num_buf, 16, 0);

    s21_format_number(ptr, num_buf, num_len, &ptr_fmt, 0);
  }
}