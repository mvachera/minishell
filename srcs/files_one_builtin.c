/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_one_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:02:20 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/12 06:08:21 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_open_files(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == BUILTIN)
		{
			if (builtin_in_files(pipex) == 0)
				return (0);
			if (builtin_out_files(pipex) == 0)
				return (0);
			break ;
		}
		i++;
	}
	return (1);
}

int	builtin_in_files(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == IN_FILES || pipex->token[i] == HERE_DOC)
		{
			if (pipex->token[i] == IN_FILES)
				pipex->fd = open(pipex->tab[i], O_RDONLY);
			else if (pipex->token[i] == HERE_DOC)
				pipex->fd = 0;
			if (pipex->fd == -1)
			{
				ft_printf("%s : %s\n", pipex->tab[i], strerror(errno));
				free_memory(pipex);
				pipex->code_err = 1;
				return (0);
			}
			dup2(pipex->fd, 0);
			if (pipex->token[i] != HERE_DOC)
				close(pipex->fd);
		}
		i++;
	}
	return (close_hdocs(pipex->hdocs, pipex->nbhdocs), 1);
}

int	builtin_out_files(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == OUT_FILES)
		{
			if (i != 0 && pipex->token[i - 1] == CHEVRON_D)
				pipex->fd = open(pipex->tab[i],
						O_CREAT | O_RDWR | O_TRUNC, 0666);
			else if (i != 0 && pipex->token[i - 1] == D_CHEVRON_D)
				pipex->fd = open(pipex->tab[i],
						O_CREAT | O_RDWR | O_APPEND, 0666);
			if (pipex->fd == -1)
			{
				ft_printf("%s : %s\n", pipex->tab[i], strerror(errno));
				return (free_memory(pipex), pipex->code_err = 1, 0);
			}
			dup2(pipex->fd, 1);
			close(pipex->fd);
		}
		i++;
	}
	return (1);
}
