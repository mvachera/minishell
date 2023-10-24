/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:06:51 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/24 20:22:54 by mvachera         ###   ########.fr       */
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
	if (pipex->tab != NULL)
		free_map(pipex->tab);
	if (pipex->token != NULL)
		free(pipex->token);
	if (pipex->cmd_args != NULL)
		free_map(pipex->cmd_args);
	// if (pipex->envp2 != NULL)
	// 	free_map(pipex->envp2);
}
