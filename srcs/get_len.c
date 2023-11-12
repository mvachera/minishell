/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 06:21:17 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/12 06:22:57 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen2(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && (s[i] < 9 || s[i] > 13))
		i++;
	return (i);
}

int	ft_strlen3(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '?' && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9'))
			break ;
		i++;
	}
	return (i);
}

int	ft_strlen4(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
