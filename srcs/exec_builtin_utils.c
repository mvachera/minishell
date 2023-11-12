/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 07:26:08 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/12 08:21:43 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(t_pipex *pipex, char *str, int index)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == PIPE)
			k++;
		else if (ft_strcmp(str, pipex->tab[i]) == 0 && k == index)
		{
			if (pipex->tab[i + 1] == NULL)
				return (0);
			else
			{
				i++;
				j = count_arg2(pipex, i);
				break ;
			}
		}
		i++;
	}
	return (j);
}

int	count_arg2(t_pipex *pipex, int i)
{
	int	j;

	j = 0;
	while (i < pipex->count && pipex->token[i] != PIPE)
	{
		if (pipex->token[i] == ARGUMENT && ft_strcmp(pipex->tab[i], "''") != 0
			&& ft_strcmp(pipex->tab[i], "\"\"") != 0)
			j++;
		i++;
	}
	return (j);
}

void	cd_command2(t_pipex *pipex, char *path)
{
	if (chdir(path) == -1)
	{
		pipex->code_err = 1;
		ft_printf("cd : %s\n", strerror(errno));
	}
}
