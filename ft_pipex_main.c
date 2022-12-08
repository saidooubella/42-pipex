/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 09:33:19 by soubella          #+#    #+#             */
/*   Updated: 2022/10/21 09:41:25 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include "ft_printf.h"

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		ft_printf_err("pipex: too few arguments\n");
		return (0);
	}
	if (argc > 5)
	{
		ft_printf_err("pipex: too many arguments\n");
		return (0);
	}
	return (program_entry(argc, argv, env, 0));
}
