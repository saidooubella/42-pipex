/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:55:17 by soubella          #+#    #+#             */
/*   Updated: 2022/10/21 11:57:51 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#include "ft_string_utils.h"
#include "ft_utilities.h"
#include "ft_printf.h"
#include "ft_pipex.h"

static t_pipe	get_current_ends(t_pipex *pipex, size_t index)
{
	t_pipe	pipe_ends;

	if (index == 0)
		pipe_ends.in = pipex->infile;
	else
		pipe_ends.in = pipex->pipes[index - 1]->in;
	if (index == pipex->commands_size - 1)
		pipe_ends.out = pipex->outfile;
	else
		pipe_ends.out = pipex->pipes[index]->out;
	return (pipe_ends);
}

static void	close_unused_ends(t_pipex *pipex, size_t index)
{
	if (index != pipex->commands_size - 1)
		close(pipex->pipes[index]->in);
	if (index != 0)
		close(pipex->pipes[index - 1]->out);
}

int	are_equals(char *s1, char *s2)
{
	size_t	s1_size;
	size_t	s2_size;

	s1_size = string_length(s1);
	s2_size = string_length(s2);
	if (s1_size == s2_size || (s1_size == s2_size - 1
			&& s2[s2_size - 1] == '\n'))
		if (!string_compare(s1, s2, s1_size))
			return (1);
	return (0);
}

void	fork_child(t_pipex *pipex, size_t index, char **env)
{
	t_pipe	pipe_ends;
	int		child_id;

	pipe_ends = get_current_ends(pipex, index);
	child_id = fork();
	if (child_id == -1)
	{
		perror("pipex");
		exit(1);
	}
	if (child_id == 0)
	{
		close_unused_ends(pipex, index);
		switch_fd(STDIN_FILENO, pipe_ends.in);
		switch_fd(STDOUT_FILENO, pipe_ends.out);
		execve(pipex->commands[index]->path,
			pipex->commands[index]->args, env);
		perror("pipex");
		exit(1);
	}
	close_pipe(&pipe_ends);
}
