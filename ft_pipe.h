/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:51:47 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 11:27:47 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPE_H
# define FT_PIPE_H

# include <sys/types.h>

typedef struct s_pipe
{
	int	in;
	int	out;
}	t_pipe;

t_pipe	**open_pipes(size_t count);
void	close_pipe(t_pipe *pipe_ends);

#endif