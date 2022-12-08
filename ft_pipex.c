/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:45:16 by soubella          #+#    #+#             */
/*   Updated: 2022/10/21 11:56:45 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "ft_get_next_line.h"
#include "ft_printf.h"
#include "ft_string_utils.h"
#include "ft_utilities.h"
#include "ft_command.h"
#include "ft_pipex.h"
#include "ft_pipe.h"

int	read_from_stdin(char *limiter)
{
	int		read_write[2];
	char	*line;

	if (pipe(read_write) == -1)
	{
		perror("pipex");
		exit(0);
	}
	while (1)
	{
		ft_printf_err("heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (line == 0)
			break ;
		if (are_equals(limiter, line))
		{
			free(line);
			break ;
		}
		write(read_write[1], line, string_length(line));
		free(line);
	}
	close(read_write[1]);
	return (read_write[0]);
}

void	init_in_file(t_pipex *pipex, int flags, int argc, char **argv)
{
	if ((flags & O_APPEND) != 0)
	{
		pipex->commands_size = argc - 4;
		pipex->infile = read_from_stdin(argv[2]);
	}
	else
	{
		pipex->commands_size = argc - 3;
		pipex->infile = open(argv[1], O_RDONLY);
	}
}

t_pipex	*pipex_init(int argc, char **argv, char **env, int flags)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (pipex == 0)
		memory_error();
	pipex->outfile = open(argv[argc - 1], flags, 0644);
	if (pipex->outfile == -1)
	{
		ft_printf_err("pipex: %s: %s\n", strerror(errno), argv[argc - 1]);
		exit(1);
	}
	init_in_file(pipex, flags, argc, argv);
	if (pipex->infile == -1)
	{
		ft_printf_err("pipex: %s: %s\n", strerror(errno), argv[1]);
		exit(1);
	}
	if ((flags & O_APPEND) != 0)
		pipex->commands = fetch_commands(pipex->commands_size, argv + 3, env);
	else
		pipex->commands = fetch_commands(pipex->commands_size, argv + 2, env);
	if (pipex->commands == 0)
		exit(1);
	pipex->pipes = open_pipes(pipex->commands_size - 1);
	return (pipex);
}

int	program_entry(int argc, char **argv, char **env, int enable_bonus)
{
	t_pipex	*pipex;
	size_t	index;
	int		flags;

	flags = O_CREAT | O_TRUNC | O_WRONLY;
	if (enable_bonus && are_equals(argv[1], "here_doc"))
		flags = O_CREAT | O_APPEND | O_WRONLY;
	if (enable_bonus && (flags & O_APPEND) != 0 && argc < 6)
	{
		ft_printf_err("pipex: too few arguments\n");
		return (1);
	}
	pipex = pipex_init(argc, argv, env, flags);
	index = -1;
	while (++index < pipex->commands_size)
		fork_child(pipex, index, env);
	while (wait(0) != -1)
		;
	free_2d_array((void ***) &pipex->commands, command_free);
	free_2d_array((void ***) &pipex->pipes, free);
	free(pipex);
	return (0);
}
