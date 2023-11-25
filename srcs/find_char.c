/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 06:46:52 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/25 21:14:18 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollars(t_pipex *pipex, int i)
{
	int	j;

	j = 0;
	if (i != 0 && !ft_strcmp(pipex->tab[i - 1], "<<"))
		return (0);
	while (pipex->tab[i][j])
	{
		if (pipex->tab[i][j] == '$')
			return (1);
		j++;
	}
	return (0);
}

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
