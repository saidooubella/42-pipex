/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soubella <soubella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:01:55 by soubella          #+#    #+#             */
/*   Updated: 2022/10/20 15:45:31 by soubella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_UTILS_H
# define FT_STRING_UTILS_H

# include <sys/types.h>

int		string_compare(const char *s1, const char *s2, size_t n);
char	**string_split(char *string, char sep);
size_t	string_length(char *string);

#endif
