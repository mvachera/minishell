/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:51:47 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/12 06:08:53 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_hdocs(t_here *hd, int size)
{
	int	i;

	if (!size)
		return ;
	i = 0;
	while (i < size)
		close(hd[i++].fd[0]);
	free(hd);
}

int	count_hdocs(t_pipex *pipex)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == HERE_DOC)
			nb++;
		i++;
	}
	return (nb);
}

void	remplissage_hdocs(t_here *here, int nbhdocs, t_pipex *pipex)
{
	int	i;
	int	hd;

	i = 0;
	hd = 0;
	while (i < pipex->count && hd < nbhdocs)
	{
		if (pipex->token[i] == HERE_DOC)
		{
			here[hd].limit = pipex->tab[i];
			here[hd].nbhdocs = nbhdocs;
			pipe(here[hd++].fd);
		}
		i++;
	}
}

void	fork_hdocs(t_pipex *pipex, t_here *hd)
{
	char	*str;
	int		i;

	i = 0;
	while (i < hd->nbhdocs)
	{
		while (1)
		{
			str = readline("hdocs> ");
			if (!str || !ft_strcmp(hd[i].limit, str))
				break ;
			ft_putendl_fd(str, hd[i].fd[1]);
			free(str);
		}
		close(hd[i].fd[0]);
		close(hd[i].fd[1]);
		i++;
	}
	free_memory(pipex);
	free_map(pipex->envp);
	free(hd);
	exit(0);
}

void	here_doc(t_pipex *pipex)
{
	int	pid;
	int	i;

	pipex->nbhdocs = count_hdocs(pipex);
	if (!pipex->nbhdocs)
		return ;
	pipex->hdocs = ft_calloc(sizeof(t_here), pipex->nbhdocs);
	remplissage_hdocs(pipex->hdocs, pipex->nbhdocs, pipex);
	pid = fork();
	if (pid == 0)
	{
		fork_hdocs(pipex, pipex->hdocs);
	}
	else if (pid > 0)
	{
		i = 0;
		while (i < pipex->nbhdocs)
			close(pipex->hdocs[i++].fd[1]);
	}
	wait(NULL);
}
