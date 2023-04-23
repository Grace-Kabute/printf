#include "main.h"

/**
 * _printf - produces output as written
 * @format: string passed in function
 * Return: return length of string
 */
int _printf(const char *format, ...)
{
	int i, counter, output = 0;
	int flagz, width, precision, size, buffer_index = 0; 

	va_list list;

	va_start(list, format);

	if (format == NULL)
	{
		return (-1);
	}
	counter = 0;

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffer_index++] = format[i];
			if (buffer_index == BUFFER_SIZE)
				print_buffer(buffer, &buffer_index);
			counter++;
		}
		else
		{
			print_buffer(buffer, &buffer_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i);
			size = get_size(format, &i);
			++i;
			output = handle_print(format, &i, list, buffer, flags, width, precision, size);
			if (output == -1)
				return (-1);
			counter += output;
		}
	}
	print_buffer(buffer, &buffer_index);
	va_end(list);
	return (counter);
}
/**
 * print_buffer - Prints the content of the buffer if it available
 * @buffer: pointer to string
 * @buffer_index: index to store curret character format[i]
 */
 void print_buffer(char *buffer, *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer, *buffer_index);
	*buffer_index = 0;
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
* _print_char - Prints a character
* @types: List a of arguments passed
* @buffer: Buffer array to handle our output
* @flags: identifies the active flags
* @width: Width of character
* @precision: specifies precision
* @size: specifies the size
* Return: Number of characters passed
*/
int _print_char(va_list types, char buffer[],int flags, int width, int precision, int size)
{
	char q = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/**
* _print_str - prints out a string
* @types: List a of arguments passed
* @buffer: Buffer array to handle our output
* @flags: identifies the active flags
* @width: Width of character
* @precision: specifies precision
* @size: specifies the size
* Return: lenght of string
 */
int _print_str(va_list types, char buffer[],int flags, int width, int precision, int size)
{
	int len, counter;
	char *string = va_arg(types, char *);
	
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNSED(precision);
	UNUSED(size);
	if(str == NULL)
	{
		string = "(null)";
		if (precision >= 6)
			string =" ";
	}
	while (string[len] != '\0')
		len++;
	if (precision >= 0 && precison < len)
		len = precision;
	if (width > len )
	{
		if (flag & F_MINUS)
		{
			write(1, &string, len;
			for (i = width -len; i > 0; i--)
			write(1,"", 1);
			
			return (width);
			}
			else
			{
			for (i = width -len; i > 0; i--)
			write(1,"",1);
			write(1, &string, len);
			return (width);
			}
			}
			return (write(1, string, len));
			}
