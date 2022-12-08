/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:57:09 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 11:26:45 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "ft_printf.h"

size_t	put_argument(char **format, va_list args)
{
	size_t			length;

	if (**format == 0)
		return (0);
	if (**format == 'd' || **format == 'i')
		length = put_i32(va_arg(args, int), BASE_10);
	else if (**format == 'c')
		length = put_char((char) va_arg(args, int));
	else if (**format == 's')
		length = put_string(va_arg(args, char *));
	else if (**format == 'p')
		length = put_address(va_arg(args, void *));
	else if (**format == 'u')
		length = put_u32("", va_arg(args, unsigned int), BASE_10);
	else if (**format == 'x')
		length = put_u32("", va_arg(args, unsigned int), BASE_16_LOWER);
	else if (**format == 'X')
		length = put_u32("", va_arg(args, unsigned int), BASE_16_UPPER);
	else
		length = put_char(**format);
	*format += 1;
	return (length);
}

int	ft_printf_err(const char *format, ...)
{
	va_list	args;
	int		size;

	va_start(args, format);
	size = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			size += put_argument((char **) &format, args);
		}
		else
		{
			put_char(*format++);
			size += 1;
		}
	}
	va_end(args);
	return (size);
}
