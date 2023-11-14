/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:51:47 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/14 22:05:57 by mvachera         ###   ########.fr       */
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

static void	exit_hd(int sig)
{
	t_pipex	*pipex;
	int		i;

	pipex = starton();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < pipex->nbhdocs)
		{
			close(pipex->hdocs[i].fd[1]);
			close(pipex->hdocs[i].fd[0]);
		}
		free_memory(pipex);
		free_map(pipex->envp);
		free(pipex->hdocs);
		exit(130);
	}
}

void	fork_hdocs(t_pipex *pipex, t_here *hd)
{
	char	*str;
	int		i;

	i = 0;
	signal(SIGINT, &exit_hd);
	while (i < hd->nbhdocs)
	{
		while (1)
		{
			str = readline("heredoc> ");
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
