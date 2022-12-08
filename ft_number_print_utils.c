/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_print_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:57:02 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 11:25:29 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

#include "ft_string_utils.h"
#include "ft_printf.h"

size_t	put_u64(unsigned long long number, char *base, size_t base_size)
{
	size_t	length;

	length = 0;
	if (number >= base_size)
		length = put_u64(number / base_size, base, base_size);
	write(STDERR_FILENO, &base[number % base_size], 1);
	return (length + 1);
}

size_t	put_i32_prefix(char *prefix, unsigned int number, char *base)
{
	size_t		prefix_size;

	prefix_size = string_length(prefix);
	write(STDERR_FILENO, prefix, prefix_size);
	return (prefix_size + put_u64(number, base, string_length(base)));
}

size_t	put_i32(int number, char *base)
{
	if (number < 0)
		return (put_i32_prefix("-", -number, base));
	return (put_i32_prefix("", number, base));
}

size_t	put_u32(char *prefix, unsigned int number, char *base)
{
	size_t		prefix_size;

	prefix_size = string_length(prefix);
	write(STDERR_FILENO, prefix, prefix_size);
	return (prefix_size + put_u64(number, base, string_length(base)));
}

size_t	put_address(void *pointer)
{
	write(STDERR_FILENO, "0x", 2);
	return (2 + put_u64((unsigned long long) pointer, BASE_16_LOWER, 16));
}
