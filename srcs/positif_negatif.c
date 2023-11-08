/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positif_negatif.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:48:44 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/07 21:10:21 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_negatif(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			return (0);
		i++;
	}
	return (1);
}

void	negatif_to_positif(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] = -str[i];
		i++;
	}
}

void	positif_to_negatif(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			str[i] = -str[i];
		i++;
	}
}

void	clean_arg(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (is_negatif(tab[i]) == 0)
			negatif_to_positif(tab[i]);
		i++;
	}
}
