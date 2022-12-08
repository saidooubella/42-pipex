/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:57:21 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 11:27:03 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "ft_string_utils.h"

char	**find_env_paths(char **envp)
{
	while (*envp)
	{
		if (string_compare(*envp, "PATH", 4) == 0)
			return (string_split(*envp + 5, ':'));
		envp++;
	}
	return (0);
}

void	free_2d_array(void ***elements, void del(void *))
{
	void	**temp;

	temp = *elements;
	if (temp == 0)
		return ;
	while (*temp)
		del(*temp++);
	free(*elements);
	*elements = 0;
}

void	switch_fd(int dst, int src)
{
	dup2(src, dst);
	close(src);
}

int	ft_isdigit(int ch)
{
	return ('0' <= ch && ch <= '9');
}

size_t	get_number_size(unsigned long long number, size_t base)
{
	size_t	size;

	if (number == 0)
		return (1);
	size = 0;
	while (number > 0)
	{
		number /= base;
		size += 1;
	}
	return (size);
}
