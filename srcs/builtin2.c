/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:20:40 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/02 18:37:30 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset(char *var, t_pipex *pipex, int len_var)
{
	int	i;

	i = 0;
	while (pipex->envp[i])
	{
		if (ft_strncmp(pipex->envp[i], var, len_var) == 0
			&& pipex->envp[i][len_var] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	unset_command(char *var, t_pipex *pipex)
{
	char	**new_envp;
	int		i[4];

	i[2] = 0;
	i[3] = ft_strlen(var);
	if (ft_strchr(var, '=') != NULL || check_unset(var, pipex, i[3]) == 0)
		return ;
	while (pipex->envp[i[2]])
		i[2]++;
	new_envp = ft_calloc(sizeof(char *), i[2]);
	if (!new_envp)
		return ;
	i[0] = 0;
	i[1] = 0;
	while (pipex->envp[i[0]])
	{
		if (ft_strncmp(pipex->envp[i[0]], var, i[3]) == 0
			&& pipex->envp[i[0]][i[3]] == '=')
			i[0]++;
		if (!pipex->envp[i[0]])
			break ;
		new_envp[i[1]++] = ft_strdup(pipex->envp[i[0]++]);
	}
	free_map(pipex->envp);
	pipex->envp = new_envp;
}

void	env_command(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->envp && pipex->envp[i])
	{
		write(1, pipex->envp[i], strlen(pipex->envp[i]));
		write(1, "\n", 1);
		// ft_putendl_fd(pipex->envp[i], 1);
		i++;
	}
}
