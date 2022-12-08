/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:08:53 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 16:27:24 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_utilities.h"
#include "ft_command.h"
#include "ft_printf.h"

static t_command	*validate_command(t_command *command, int *failed)
{
	if (command == 0)
		*failed = 1;
	else if (command->path == 0)
	{
		ft_printf_err("pipex: command not found: %s\n", command->args[0]);
		*failed = 1;
	}
	return (command);
}

t_command	**fetch_commands(size_t argc, char **argv, char **env)
{
	t_command	**commands;
	char		**paths;
	size_t		index;
	int			failed;

	commands = malloc(sizeof(t_command *) * (argc + 1));
	if (commands == 0)
		return (0);
	paths = find_env_paths(env);
	failed = 0;
	index = 0;
	while (index < argc)
	{
		commands[index] = validate_command(
				command_new(paths, argv[index]), &failed);
		index += 1;
	}
	commands[index] = 0;
	free_2d_array((void ***) &paths, free);
	if (failed)
		free_2d_array((void ***) &commands, command_free);
	return (commands);
}
