/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strange_caracteres.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:07:05 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/06 18:17:48 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strange_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '?' && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

char	*handle_strange(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '?' && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9'))
			return (str + i);
		i++;
	}
	return (NULL);
}
