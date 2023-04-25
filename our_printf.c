#include "main.h"

/**
 * _printf - produces output as written
 * @format: string passed in function
 * Return: return length of string
 */
int _printf(const char *format, ...)
{
	int i, counter, output = 0;
	int flags, width, precision, size, buffer_index = 0;
	char buffer[BUFFER_SIZE];

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
			flags = get_the_flag(format, &i);
			width = get_the_width(format, &i, list);
			precision = get_the_precision(format, &i, list);
			size = get_the_size(format, &i);
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
 void print_buffer(char *buffer, int *buffer_index)
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

 return (handle_write_character(q, buffer, flags, width, precision, size));
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
	char *string = va_arg(typez, char *);

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
	UNUSED(typez);
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
	unsigned long int number;

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
	while (number > 0)
	{
		buffer[i--] = (number % 10) + '0';
		number = number  / 10;
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
	m = 2147483648;

	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		 m = m / 2;
		 a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, counter = 0; i < 32; i++)
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

	number = convert_size_unsigned(number, size);

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
	
	if (flags  &F_HASH && int_number != 0)
		buffer[i--] = '0';
	i++;

	return (write_unsigned(0, i, buffer, flags, width, precision, size));
}
/**
 * _print_hexa_decimals - prints out hexa decimal numbers
 * @typez: list a of arguments
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: number of characters printed
 */
int _print_hexa_decimals(va_list typez, char *buffer, int flags, int width, int precision, int size)
{
	return (_print_any_hexa(typez, "0123456789abcef", buffer, flags, 'x', width, precision, size));
}

/**
 * _print_hexa_capital - prints out hexa decimal number in uppercase
 * @typez: list a of arguments
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: number of characters printed
 */
int _print_hexa_capital(va_list typez, char *buffer, int flags, int width, int precision, int size)
{

	return (_print_any_hexa(typez, "0123456789ABCDEF", buffer, flags, 'x', width, precision, size));
}

/**
* is_digit - Verifies if a char is a digit
* @c: Char to be evaluated
* Return: 1 if c is a digit, 0 otherwise
*/
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * _print_any_hexa - prints out hexa decimal number in uppercase or lowercase
 * @typez: list a of arguments
 * @map_to: pointer to map the number to
 * @buffer: Buffer to handle print output
 * @flags: identify active flags
 * @flag_ch: computes active flags
 * @width: gives width of the character
 * @precision: identify precisions
 * @size: specify the size of the character
 * Return: number of characters printed
 */
int _print_any_hexa(va_list typez, char *map_to, char *buffer, int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(typez, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(width);

	number = convert_size_unsigned(number, size);
	if (number == 0)
		buffer[i--] = '0';
	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = map_to[number % 16];
		number = number / 16;
	}
	if (flags &F_HASH && init_number != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;
	return (write_unsigned(0, i, buffer, flags, width, precision, size));
}
/**
* get_the_flag - Computes  active flags
* @format: Formatted string in which to print the arguments
* @i: take a parameter.
* Return: the Flag:
*/
int get_the_flag(const char *format, int *i)
{
	int j, curr_i;
	int flags = 0;
	const char FLAGS_CHARACTER[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
	for (j = 0; FLAGS_CHARACTER[j] != '\0'; j++)
		if (format[curr_i] == FLAGS_CHARACTER[j])
		{
			flags |= FLAGS_ARRAY[j];
			break;
		}
	if (FLAGS_CHARACTER[j] == 0)
		break;
	}
	*i = curr_i - 1;
	return (flags);
}

/**
* get_the_precision - Computes the precision for printing
* @format: Formatted string in which to print the arguments
* @i: List of arguments to be printed.
* @list: list of arguments.
* Return: Precision.
*/
int get_the_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1;


	if (format[curr_i] != '.')
		return (precision);
	precision = 0;

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			precision = precision * 10;
			precision = precision + format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = curr_i - 1;
	return (precision);
}

/**
* get_the_size - Computes the size to cast the argument
* @format: Formatted string in which to print the arguments
* @i: List of arguments to be printed.
* Return: Precision.
*/
int get_the_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;
	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;
	return (size);

}

/**
* get_the_width - Computes the width for printing
* @format: Formatted string in which to print the arguments.
* @i: List of arguments to be printed.
* @list: list of arguments.
* Return: width.
*/
int get_the_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width = width * 10;
			width = width + format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = curr_i - 1;
	return (width);
}

/**
* handle_write_character - Prints a string
* @c: char types.
* @buffer: Buffer array to handle print
* @flags: Calculates active flags.
* @width: get width.
* @precision: precision specifier
* @size: Size specifier
* Return: Number of chars printed.
*/
int handle_write_character(char c, char *buffer,int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';
	buffer[i++] = c;
	buffer[i] = '\0';
	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFFER_SIZE - i - 2] = padd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) +
					write(1, &buffer, 1));
	}
	return (write(1, &buffer, 1));
}

/**
* convert_size_number - Casts a number to the specified size
* @num: Number to be casted.
* @size: Number indicating the type to be casted.
* Return: Casted value of num
*/
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);
	return ((int)num);
}

/**
* convert_size_unsigned - Casts a number to the specified size
* @num: Number to be casted
* @size: Number indicating the type to be casted
* Return: Casted value of num
*/
long int convert_size_unsigned(unsigned long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);
	return ((unsigned int)number);
}
/**
* write_number - Prints a string
* @is_negative: Lista of arguments
* @ind: char types.
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width.
* @precision: precision specifier
* @size: Size specifier
* Return: Number of chars printed.
*/
int write_number(int a_negative, int ind, char *buffer,int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - ind - 1;
	char padd = ' ', extra_character = 0;

	UNUSED(size);
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (a_negative)
		extra_character = '-';
	else if (flags & F_PLUS)
		extra_character = '+';
	else if (flags & F_SPACE)
		extra_character = ' ';
	return (write_a_number(ind, buffer, flags, width, precision,length, padd, extra_character));
}


/**
* write_a_number - Write a number using a bufffer
* @ind: Index at which the number starts on the buffer
* @buffer: Buffer
* @flags: Flags
* @width: width
* @prec: Precision specifier
* @length: Number length
* @padd: Pading char
* @extra_character: Extra char
* Return: Number of printed chars.
*/
int write_num(int ind, char *buffer,int flags, int width, int prec,int length, char padd, char extra_character)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';

	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;

	if (extra_character != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';

		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_character)
				buffer[--ind] = extra_character;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_character)
				buffer[--ind] = extra_character;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_character)
				buffer[--padd_start] = extra_character;

			return (write(1, &buffer[padd_start], i - padd_start) + write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_character)
		buffer[--ind] = extra_character;

	return (write(1, &buffer[ind], length));
}
/**
* write_unsigned - Writes an unsigned number
* @a_negative: Number indicating if the num is negative
* @ind: Index at which the number starts in the buffer
* @buffer: Array of chars
* @flags: Flags specifiers
* @width: Width specifier
* @precision: Precision specifier
* @size: Size specifier
* Return: Number of written chars.
*/
int write_unsigned(int a_negative, int ind,char *buffer,int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(a_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		return (0);
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer, i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}
	return (write(1, &buffer[ind], length));
}
