/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:06:51 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/10 19:35:00 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_memory(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->tab != NULL)
	{
		while (i < pipex->count)
			free(pipex->tab[i++]);
		free(pipex->tab);
	}
	if (pipex->token != NULL)
		free(pipex->token);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->tab != NULL)
	{
		while (i < pipex->count)
			free(pipex->tab[i++]);
		free(pipex->tab);
	}
	if (pipex->token != NULL)
		free(pipex->token);
	i = 0;
	if (pipex->cmd_args != NULL)
	{
		while (i < pipex->cmd_count)
			free(pipex->cmd_args[i++]);
		free(pipex->cmd_args);
	}
	if (pipex->envp != NULL)
		free_map(pipex->envp);
}

void	free_exit(t_pipex *pipex, char **arg, int nb_arg)
{
	int	i;

	i = 0;
	while (i < nb_arg)
	{
		if (arg[i] != NULL)
			free(arg[i]);
		i++;
	}
	if (arg != NULL)
		free(arg);
	if (pipex->envp != NULL)
		free_map(pipex->envp);
	free_memory(pipex);
}
