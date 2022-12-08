/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:27:06 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 15:25:42 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILITIES_H
# define FT_UTILITIES_H

# include <sys/types.h>

void	memory_error(void);
size_t	get_number_size(unsigned long long number, size_t base);
void	free_2d_array(void ***elements, void del(void *));
char	**find_env_paths(char **envp);
void	switch_fd(int dst, int src);
int		ft_isdigit(int ch);

#endif
