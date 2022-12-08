/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:26:31 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 15:17:02 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMAND_H
# define FT_COMMAND_H

# include <sys/types.h>

# include "ft_string_builder.h"

typedef struct s_command
{
	char	*path;
	char	**args;
}	t_command;

t_command	**fetch_commands(size_t argc, char **argv, char **env);
t_command	*command_new(char **paths, char *command);
char		*find_command_path(char **paths, char *command);
void		command_free(void *cmd);

#endif