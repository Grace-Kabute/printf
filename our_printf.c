#include "main.h"

/**
 * _printf - produces output as written
 * @format: string passed in function
 * Return: return length of string
 */
int _printf(const char *format, ...)
{
	int i, counter;

	va_list list;

	va_start(list, format);

	counter = 0;

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
		_print_chr(format[i]);
		}
		else if (format[i + 1] == 's')
		{
			_print_str(va_arg(list, char *));
		}
		else if (format[i + 1] == '%')
		{
			_print_chr(format[i]);
		}

		counter++;
	}
	va_end(list);
	return (counter);
}
/**
 * _print_chr - prints out one character
 * @q: input character
 * Return: return 1
 */
int _print_chr(char q)
{
	write(1, &q, 1);
	return (1);
}
/**
 * _print_str - prints out a string
 * @str: pointer to string being passed
 * Return: lenght of string
 */
int _print_str(char *str)
{
	int m, counter;

	counter = 0;

	for (m = 0; str[m] != '\0'; m++)
	{
		_print_chr(str[m]);
		counter++;
	}
	return (counter);
}
