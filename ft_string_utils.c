/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:59:59 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 15:43:41 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdlib.h>

#include "ft_utilities.h"

size_t	string_length(char *string)
{
	size_t	size;

	size = -1;
	while (string[++size])
		;
	return (size);
}

int	string_compare(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (n == 0)
		return (0);
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (i < n - 1 && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

static size_t	calc_words_count(char *string, char sep)
{
	size_t	count;

	count = 0;
	while (1)
	{
		while (*string && *string == sep)
			string++;
		if (*string == 0)
			break ;
		count++;
		while (*string && *string != sep)
			string++;
	}
	return (count);
}

static char	*split_substring(
	char **strings, char **src_string, size_t *src_index, char sep)
{
	size_t	substring_length;
	char	*substring;
	char	*string;
	size_t	i;

	string = *src_string;
	substring_length = 0;
	while (string[substring_length] && string[substring_length] != sep)
		substring_length++;
	substring = malloc(sizeof(char) * (substring_length + 1));
	if (substring == 0)
	{
		while (*src_index >= 0)
			free(strings[(*src_index)--]);
		free(strings);
		return (0);
	}
	i = 0;
	while (*string && i < substring_length)
		substring[i++] = *string++;
	substring[i] = 0;
	*src_string = string;
	return (substring);
}

char	**string_split(char *string, char sep)
{
	char	*substring;
	size_t	words_count;
	char	**strings;
	size_t	index;

	words_count = calc_words_count(string, sep);
	strings = malloc(sizeof(char *) * (words_count + 1));
	if (strings == 0)
		memory_error();
	index = 0;
	while (index < words_count)
	{
		while (*string == sep)
			string++;
		substring = split_substring(strings, &string, &index, sep);
		if (substring == 0)
			memory_error();
		strings[index++] = substring;
	}
	strings[index] = 0;
	return (strings);
}
