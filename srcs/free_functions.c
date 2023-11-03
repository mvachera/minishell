/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:06:51 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/03 19:17:59 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_memory(t_pipex *pipex)
{
	if (pipex->tab != NULL)
		free_map(pipex->tab);
	if (pipex->token != NULL)
		free(pipex->token);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->tab != NULL)
		free_map(pipex->tab);
	if (pipex->token != NULL)
		free(pipex->token);
	while (i < pipex->cmd_count)
	{
		if (pipex->cmd_args[i] != NULL)
			free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	if (pipex->envp != NULL)
		free_map(pipex->envp);
}

void	free_files(t_pipex *pipex)
{
	if (pipex->files != NULL)
		free_map(pipex->files);
	if (pipex->type != NULL)
		free(pipex->type);
}

void	free_exit(t_pipex *pipex)
{
	if (pipex->envp != NULL)
		free_map(pipex->envp);
	free_memory(pipex);
}

char	**cpy_envp(char **envp)
{
	char	**dst;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	dst = ft_calloc(sizeof(char *), i + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		dst[i] = ft_strdup(envp[i]);
		i++;
	}
	return (dst);
}
