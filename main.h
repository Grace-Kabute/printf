#ifndef HEADER
#define HEADER
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

#define BUFFFER_SIZE 1024

#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_space 16
int _print_chr(char q);
int _print_char(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _printf(const char *format, ...);
void print_buffer(char buffer*, int *buffer_index;
int _print_str(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_percent(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_number(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_binary(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_unsigned_num(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_octal(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_hexa_decimals(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_hexa_capital(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_handler(va_list typez, char *buffer, int flags, int width, int precision, int size);
int handle_write_chr(va_list typez, char *buffer, int flags, int width, int precision, int size);
int handle_number(va_list typez, char *buffer, int flags, int width, int precision, int size);
int write_number(va_list typez, char *buffer, int flags, int width, int precision, int size);
int write_pointer(va_list typez, char *buffer, int flags, int width, int precision, int size);
int unsigned_number(va_list typez, char *buffer, int flags, int width, int precision, int size);



#endif /*HEADER*/
