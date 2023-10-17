/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:20:40 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/16 15:37:21 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_command(char *var, t_pipex *pipex)
{
	int	i;
	int	len_var;

	i = 0;
	len_var = 0;
	while (pipex->envp[i])
	{
		if (ft_strncmp(pipex->envp[i], var, len_var) == 0
			&& pipex->envp[i][len_var] == '=')
		{
			while (pipex->envp[i])
			{
				pipex->envp[i] = pipex->envp[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

void	env_command(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->envp[i])
	{
		ft_printf("%s\n", pipex->envp[i]);
		i++;
	}
}

void	exit_command(t_pipex *pipex)
{
	free_memory(pipex);
	exit(0);
}
