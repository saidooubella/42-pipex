/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:51:54 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 19:55:31 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "ft_utilities.h"
#include "ft_pipe.h"

static t_pipe	*open_pipe(void)
{
	t_pipe	*pipe_ends;
	int		read_write[2];

	pipe_ends = malloc(sizeof(t_pipe));
	if (pipe_ends == 0)
		memory_error();
	if (pipe(read_write) == -1)
	{
		perror("pipex");
		exit(1);
	}
	pipe_ends->out = read_write[1];
	pipe_ends->in = read_write[0];
	return (pipe_ends);
}

t_pipe	**open_pipes(size_t count)
{
	t_pipe	**pipes;
	size_t	index;

	pipes = malloc(sizeof(t_pipe *) * (count + 1));
	if (pipes == 0)
		memory_error();
	index = 0;
	while (index < count)
	{
		pipes[index] = open_pipe();
		if (pipes[index] == 0)
		{
			while (index >= 0)
				free(pipes[index--]);
			free(pipes);
			memory_error();
		}
		index++;
	}
	pipes[index] = 0;
	return (pipes);
}

void	close_pipe(t_pipe *pipe_ends)
{
	close(pipe_ends->out);
	close(pipe_ends->in);
}
