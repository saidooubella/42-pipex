/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:26:43 by soubella          #+#    #+#             */
/*   Updated: 2022/11/11 09:44:23 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "ft_command.h"
# include "ft_pipe.h"

typedef struct s_pipex
{
	int			infile;
	int			outfile;
	size_t		commands_size;
	t_command	**commands;
	t_pipe		**pipes;
}	t_pipex;

int		program_entry(int argc, char **argv, char **env, int enable_bonus);
void	fork_child(t_pipex *pipex, size_t index, char **env);
int		reopen_temp(int fd, int flags);
int		are_equals(char *s1, char *s2);

#endif
