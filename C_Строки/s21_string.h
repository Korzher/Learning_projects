#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdarg.h>  // Для va_list в s21_snprintf и s21_scanf
#include <stdlib.h>  // Для malloc/free
#include <limits.h>  // MB_LEN_MAX
#include <math.h>    // fabs, modf, isnan
#include <stdint.h>  // uint_ptr для обработки дескриптора %p
#include <wchar.h>   // Обработка флага l для s и c

#ifdef __APPLE__
#define ERROR_MESSAGES                                                         \
  {                                                                            \
    "Success", "Operation not permitted", "No such file or directory",         \
        "No such process", "Interrupted system call", "Input/output error",    \
        "No such device or address", "Argument list too long",                 \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource deadlock avoided", "Cannot allocate memory",                 \
        "Permission denied", "Bad address", "Block device required",           \
        "Device or resource busy", "File exists", "Cross-device link",         \
        "Operation not supported by device", "Not a directory",                \
        "Is a directory", "Invalid argument", "Too many open files in system", \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain", "Result too large", \
        "Resource temporarily unavailable", "Operation now in progress",       \
        "Operation already in progress", "Socket operation on non-socket",     \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol family",                     \
        "Address already in use", "Can't assign requested address",            \
        "Network is down", "Network is unreachable",                           \
        "Network dropped connection on reset",                                 \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available", "Socket is already connected",            \
        "Socket is not connected", "Can't send after socket shutdown",         \
        "Too many references: can't splice", "Operation timed out",            \
        "Connection refused", "Too many levels of symbolic links",             \
        "File name too long", "Host is down", "No route to host",              \
        "Directory not empty", "Too many processes", "Too many users",         \
        "Disk quota exceeded", "Stale NFS file handle",                        \
        "Too many levels of remote in path", "RPC struct is bad",              \
        "RPC version wrong", "RPC prog. not avail", "Program version wrong",   \
        "Bad procedure for program", "No locks available",                     \
        "Function not implemented", "Inappropriate file type or format",       \
        "Authentication error", "Need authenticator", "Device power is off",   \
        "Device error", "Value too large to be stored in data type",           \
        "Bad executable", "Bad CPU type in executable",                        \
        "Shared library version mismatch", "Malformed Macho file",             \
        "Operation canceled", "Identifier removed",                            \
        "No message of desired type", "Illegal byte sequence",                 \
        "Attribute not found", "Bad message", "Reserved",                      \
        "No message available on STREAM", "Reserved", "No STREAM resources",   \
        "Not a STREAM", "Protocol error", "STREAM ioctl timeout",              \
        "Operation not supported on socket", "No such policy registered",      \
        "State not recoverable", "Previous owner died",                        \
        "Interface output queue is full"                                       \
  }
#elif defined(__linux__)
#define ERROR_MESSAGES                                                         \
  {                                                                            \
    "Success", "Operation not permitted", "No such file or directory",         \
        "No such process", "Interrupted system call", "Input/output error",    \
        "No such device or address", "Argument list too long",                 \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource temporarily unavailable", "Cannot allocate memory",          \
        "Permission denied", "Bad address", "Block device required",           \
        "Device or resource busy", "File exists", "Invalid cross-device link", \
        "No such device", "Not a directory", "Is a directory",                 \
        "Invalid argument", "Too many open files in system",                   \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain",                     \
        "Numerical result out of range", "Resource deadlock avoided",          \
        "File name too long", "No locks available",                            \
        "Function not implemented", "Directory not empty",                     \
        "Too many levels of symbolic links", "No message of desired type",     \
        "Identifier removed", "Channel number out of range",                   \
        "Level 2 not synchronized", "Level 3 halted", "Level 3 reset",         \
        "Link number out of range", "Protocol driver not attached",            \
        "No CSI structure available", "Level 2 halted", "Invalid exchange",    \
        "Invalid request descriptor", "Exchange full", "No anode",             \
        "Invalid request code", "Invalid slot",                                \
        "Resource deadlock would occur", "Bad font file format",               \
        "Device not a stream", "No data available", "Timer expired",           \
        "Out of streams resources", "Machine is not on the network",           \
        "Package not installed", "Object is remote", "Link has been severed",  \
        "Advertise error", "Srmount error", "Communication error on send",     \
        "Protocol error", "Multihop attempted", "RFS specific error",          \
        "Bad message", "Value too large for defined data type",                \
        "Name not unique on network", "File descriptor in bad state",          \
        "Remote address changed", "Cannot access a needed shared library",     \
        "Accessing a corrupted shared library",                                \
        ".lib section in a.out corrupted",                                     \
        "Attempting to link in too many shared libraries",                     \
        "Cannot exec a shared library directly",                               \
        "Invalid or incomplete multibyte or wide character",                   \
        "Interrupted system call should be restarted", "Streams pipe error",   \
        "Too many users", "Socket operation on non-socket",                    \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol", "Address already in use",  \
        "Cannot assign requested address", "Network is down",                  \
        "Network is unreachable", "Network dropped connection on reset",       \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available",                                           \
        "Transport endpoint is already connected",                             \
        "Transport endpoint is not connected",                                 \
        "Cannot send after transport endpoint shutdown",                       \
        "Too many references: cannot splice", "Connection timed out",          \
        "Connection refused", "Host is down", "No route to host",              \
        "Operation already in progress", "Operation now in progress",          \
        "Stale file handle", "Structure needs cleaning",                       \
        "Not a XENIX named type file", "No XENIX semaphores available",        \
        "Is a named type file", "Remote I/O error", "Disk quota exceeded",     \
        "No medium found", "Wrong medium type", "Operation canceled",          \
        "Required key not available", "Key has expired",                       \
        "Key has been revoked", "Key was rejected by service", "Owner died",   \
        "State not recoverable", "Operation not possible due to RF-kill",      \
        "Memory page has hardware error"                                       \
  }
#else
#define ERROR_MESSAGES \
  { "Unknown error" }
#endif

#define S21_NULL ((void *)0)

typedef unsigned long s21_size_t;

typedef struct {
  int flags[5];    // Флаги: [0] '-', [1] '+', [2] ' ', [3] '0', [4] '#'
  int width;       // Ширина поля
  int precision;   // Точность
  int prefix_len;  // Длина префикса для x, X, o
  char length;     // l, h, L
  char specifier;  // Спецификатор (d, f, s и т.д.)
  char prefix[3];  // Префикс для x, X, o
} s21_format;

// Основные функции string.h
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
int s21_sprintf(char *str, const char *format, ...);

// Дополнительные функции
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

//Помощники
void s21_parse_format(const char **format, va_list args, s21_format *fmt);
void s21_integer(char **ptr, va_list args, const s21_format *fmt);
int s21_convert_integer(long num, char *str, int base,
                        int uppercase);
void s21_reverse(char *str, int length);
void s21_format_number(char **ptr, const char *num_buf, int num_len,
                       const s21_format *fmt, int sign_char);
void s21_unsigned(char **ptr, va_list args, s21_format *fmt);
void s21_float(char **ptr, va_list args, const s21_format *fmt);
int s21_convert_float(long double num, char *str, int precision);
void s21_char(char **ptr, va_list args, const s21_format *fmt);
void s21_string(char **ptr, va_list args, const s21_format *fmt);
char *s21_wide_string(const wchar_t *ws, int max_bytes);
int s21_string_length(const char *s, int precision);
void s21_output_string(char **ptr, const char *s, int num_len,
                       const s21_format *fmt);
void s21_pointer(char **ptr, va_list args, const s21_format *fmt);
int s21_convert_float_g(double num, char *str, int precision, int uppercase,
                        int is_sharp);
int s21_convert_float_e(double num, char *str, int precision, int uppercase);
int s21_exponent(double num);
double s21_pow(double base, int exponent);

#endif  // S21_STRING_H
