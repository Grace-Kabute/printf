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
 * _print_char - print a character 
 * @typez: list a of arguments
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: Number of characters printed
 */
int _print_char(va_list typez, char *buffer, int flags, int width, int precision, int size)
{
 char q	= va_arg(typez, int);

 return (handle_write_char(q, buffer, flags, width, precision, size));
}
/**
 * _print_string - print out string output
 * @typez: list a of arguments
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: lenght of string
 */
int _print_string(va_list typez, char *buffer, int flags, int width, int precision, int size)
{
	int len = 0, i;
	char *string = va-arg(typez, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
	{
		string = "(null)";
		if (precision >= 6)
			string = " ";
	}
	while (string[len] != '\0')
		len++;
	if (precision >= 0 && precision < len)
		len = precision;
	if (width > len)
	{
		if (flags &F_MINUS)
		{
			write(1, &string, len);

			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &string, len);
			return (width);
		}
	}
	return (write(1, string, len));
}


	return (counter);
}

/**
 * _print_percent - print out the % sign
 * @typez: list a of arguments
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: returns a percente
 */
int _print_percent(va_list typez, char *buffer, int flags, int width, int precision, int size)
{
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}
/**
 * _print_number - print a number
 * @typez: list a of arguments
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: number of characters printed
 */
int _print_number(va_list typez, char *buffer, int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	int a_negative = 0;
	long int n = va_arg(typez, long int);
	unsignes long int number;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';
	buffer[BUFFER_SIZE - 1] = '\0';
	number = (unsigned long int)n;
	if (n < 0)
	{
		number = (unsigned long int)((-1) * n);
		a_negative = 1;
	}
	while (num > 0)
	{
		buffer[i--] = (number % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_number(a_negative, i, buffer, flags, width, precision, size));
}
/**
 * _print_binary - print out a number in binary
 * @typez: list a of arguments
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: binary number of character printed
 */
int _print_binary(va_list typez, char *buffer, int flags, int width, int precision, int size)
{

	unsigned int n, m, i, sum;
	unsigned int a[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);


	n = va_arg(typez, unsigned int);
	n = 2147483648;

	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		 m = m / 2;
		 a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, counnter = 0; i < 32; i++)
	{
		sum = sum + a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];
			write(1, &z, 1);
			counter++;
		}
	}
	return (counter);
}

/**
 * _print_unsigned_num - prints positive number only(unsigned int)
 * @typez: list a of arguments
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: number of characters printed
 */
int _print_unsigned_num(va_list typez, char *buffer, int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(typez, unsigned long int);

	num = convert_size_unsigned(number, size);

	 if (number == 0)
		 buffer[i--] = '0';
	 buffer[BUFFER_SIZE - 1] = '\0';
	 while (number > 0)
	 {
		 buffer[i--] = (number % 10) + '0';
		 number = number / 10;
	 }
	 i++;
	 return(write_unsigned(0, i, buffer, flags, width, precision, size));
}


/**
 * _print_octal- prints base 8 numbers ( Octal)
 * @typez: list a of arguments
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: number of characters printed
 */
int _print_octal(va_list typez, char *buffer, int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(typez, unsigned long int);
	unsigned long int_number = number;

	UNUSED(width);

	number = convert_size_unsigned(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while(number > 0)
	{
		buffer[i--] = (number % 8) + '0';
		number = number / 8;
	}
	
	if (flag  &F_HASH && int_number != 0)
		buffer[i--] = '0';
	i++;

	return (write_unsigned(0, i, buffer, flags, width, precision, size));
}


