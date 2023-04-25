#ifndef HEADER
#define HEADER
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

#define S_LONG 2
#define S_SHORT 1
#define BUFFER_SIZE 1024
#define UNUSED(x) (void)(x)

#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16
long int convert_size_number(long int number, int size);
long int convert_size_unsigned(unsigned long int number, int size);
int _print_chr(char q);
int _print_char(va_list typez, char *buffer, int flags, int width, int precision, int size);
void print_buffer(char *buffer, int *buffer_index);
int _print_str(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_percent(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_number(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_binary(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_unsigned_num(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_octal(va_list typez, char *buffer, int flags, int width, int precision, int size);
int write_unsigned(int a_negative, int ind, char *buffer, int flags, int width, int precision, int size);
int handle_write_character(char c, char *buffer, int flags, int width, int precision, int size);
int _print_hexa_decimals(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_hexa_capital(va_list typez, char *buffer, int flags, int width, int precision, int size);
int _print_any_hexa(va_list typez, char *map_to, char *buffer, int flags, char flag_ch, int width, int precision, int size);
int write_number(int a_negative, int ind, char *buffer,int flags, int width, int precision, int size);
int get_the_flag(const char *format, int *i);
int get_the_width(const char *format, int *i, va_list list);
int get_the_precision(const char *format, int *i, va_list list);
int get_the_size(const char *format, int *i);
int _print_handler(va_list typez, char *buffer, int flags, int width, int precision, int size);
int handle_write_chr(va_list typez, char *buffer, int flags, int width, int precision, int size);
int handle_number(va_list typez, char *buffer, int flags, int width, int precision, int size);
int write_a_number(int ind, char *buffer, int flags, int width, int precision, int length, char padd, char extra_character);
int write_pointer(va_list typez, char *buffer, int flags, int width, int precision, int size);
int unsigned_number(va_list typez, char *buffer, int flags, int width, int precision, int size);
int is_digit(char c);
int handle_print(const char *format, int *ind, va_list list, char *buffer,int flags, int width, int precision, int size);

/**
* struct format - Struct op
*
* @format: The format.
* @fn: The function associated.
*/
struct format
{
	char format;
	int (*fn)(va_list, char[], int, int, int, int);
};
/**
* typedef struct format format_t - Struct op
*
* @format: The format.
* @fm_t: The function associated.
*/
typedef struct format format_t;

int _printf(const char *format, ...);
int handle_print(const char *format, int *i,va_list list, char *buffer, int flags, int width, int precision, int size);


#endif /*HEADER*/
