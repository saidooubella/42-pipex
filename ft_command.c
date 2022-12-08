/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:33:03 by soubella          #+#    #+#             */
/*   Updated: 2022/11/11 19:00:42 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ft_string_builder.h"
#include "ft_string_utils.h"
#include "ft_utilities.h"
#include "ft_command.h"

t_command	*command_new(char **paths, char *command)
{
	char		**args;
	char		*path;
	t_command	*cmd;

	args = string_split(command, ' ');
	if (args == 0)
		return (0);
	path = find_command_path(paths, args[0]);
	cmd = malloc(sizeof(t_command));
	if (cmd == 0)
	{
		free_2d_array((void ***) &args, free);
		free(path);
		return (0);
	}
	cmd->path = path;
	cmd->args = args;
	return (cmd);
}

void	command_free(void *cmd)
{
	t_command	*command;

	command = (t_command *) cmd;
	free_2d_array((void ***) &(command->args), free);
	free(command->path);
	free(command);
}

static char	*build_path(
	t_string_builder *b, char *path, char *cmd, size_t cmd_size)
{
	if (!string_builder_append_string(b, path, string_length(path)))
		return (0);
	if (!string_builder_append_char(b, '/'))
		return (0);
	if (!string_builder_append_string(b, cmd, cmd_size))
		return (0);
	return (string_builder_to_cstr(b));
}

char	*find_command_path(char **paths, char *command)
{
	t_string_builder	*builder;
	size_t				command_length;
	char				*full_path;

	if (paths == 0)
		return (0);
	builder = string_builder_new();
	if (builder == 0)
		return (0);
	command_length = string_length(command);
	full_path = 0;
	while (*paths)
	{
		full_path = build_path(builder, *paths, command, command_length);
		if (full_path == 0)
			break ;
		if (access(full_path, F_OK & (X_OK | R_OK)) == 0)
			break ;
		string_builder_clear(builder);
		free(full_path);
		full_path = 0;
		paths++;
	}
	string_builder_free(&builder);
	return (full_path);
}
