/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:20:50 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/29 20:28:04 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_dollars(t_pipex *pipex)
{
	int		i;
	char	*tmp_before;
	char	*tmp;

	i = 0;
	while (pipex->tab[i])
	{
		if (is_dollars(pipex->tab[i]) == 1 && ft_strlen(pipex->tab[i]) > 1)
		{
			tmp_before = manage_dollars2(pipex, i);
			tmp = new_var(pipex, pipex->tab[i] + ft_strlen(tmp_before) + 1);
			if (tmp)
				manage_dollars3(pipex, tmp, tmp_before, i);
			else
			{
				free(pipex->tab[i]);
				if (!tmp && tmp_before)
					pipex->tab[i] = tmp_before;
				else
					pipex->tab[i] = 0;
			}
		}
		i++;
	}
}

char	*manage_dollars2(t_pipex *pipex, int i)
{
	char	*tmp_before;
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (pipex->tab[i][j] && pipex->tab[i][j] != '$')
		j++;
	if (j == 0)
		return (NULL);
	tmp_before = ft_calloc(sizeof(char), (j + 1));
	if (!tmp_before)
		return (NULL);
	while (k < j)
	{
		tmp_before[k] = pipex->tab[i][k];
		k++;
	}
	return (tmp_before);
}

void	manage_dollars3(t_pipex *pipex, char *tmp, char *tmp_before, int i)
{
	free(pipex->tab[i]);
	if (tmp_before)
	{
		pipex->tab[i] = str_johnny(tmp_before, tmp);
		free(tmp_before);
	}
	else
		pipex->tab[i] = ft_strdup(tmp);
	if (!pipex->tab[i])
	{
		while (i >= 0)
			free(pipex->tab[--i]);
		free(pipex->tab);
		return ;
	}
	free(tmp);
}
