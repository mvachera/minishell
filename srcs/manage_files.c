/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:58:15 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/14 22:06:03 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	openfiles(t_pipex *pipex, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == PIPE)
			j++;
		else if (j == index)
		{
			handle_files(pipex, i);
			break ;
		}
		i++;
	}
}

void	handle_files(t_pipex *pipex, int i)
{
	while (i > 0 && pipex->token[i] != PIPE)
		i--;
	i++;
	while (i < pipex->count && pipex->token[i] != PIPE)
	{
		if (pipex->token[i] == OUT_FILES || pipex->token[i] == IN_FILES
			|| pipex->token[i] == HERE_DOC)
			handle_files2(pipex, i);
		i++;
	}
	close_hdocs(pipex->hdocs, pipex->nbhdocs);
}

void	handle_files2(t_pipex *pipex, int i)
{
	if (i != 0 && pipex->token[i - 1] == CHEVRON_D)
		pipex->fd = open(pipex->tab[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (i != 0 && pipex->token[i - 1] == D_CHEVRON_D)
		pipex->fd = open(pipex->tab[i], O_CREAT | O_RDWR | O_APPEND, 0666);
	if (pipex->token[i] == IN_FILES)
		pipex->fd = open(pipex->tab[i], O_RDONLY);
	if (pipex->token[i] == HERE_DOC)
		pipex->fd = getpipe(pipex->hdocs, pipex->tab[i]);
	if (pipex->fd == -1)
	{
		ft_printf("%s : %s\n", pipex->tab[i], strerror(errno));
		free_pipex(pipex);
		pipex->code_err = 126;
		exit(1);
	}
	if (pipex->token[i] == OUT_FILES)
		dup2(pipex->fd, 1);
	if (pipex->token[i] == IN_FILES || pipex->token[i] == HERE_DOC)
		dup2(pipex->fd, 0);
	if (pipex->token[i] != HERE_DOC)
		close(pipex->fd);
}

void	here_doc(t_pipex *pipex)
{
	int	pid;
	int	i;

	pipex->nbhdocs = count_hdocs(pipex);
	if (!pipex->nbhdocs)
		return ;
	pipex->hdocs = ft_calloc(sizeof(t_here), pipex->nbhdocs);
	if (!pipex->hdocs)
		return ;
	remplissage_hdocs(pipex->hdocs, pipex->nbhdocs, pipex);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		fork_hdocs(pipex, pipex->hdocs);
	else if (pid > 0)
	{
		i = 0;
		while (i < pipex->nbhdocs)
			close(pipex->hdocs[i++].fd[1]);
	}
	signal(SIGINT, &ctrlc);
	wait(NULL);
}

int	getpipe(t_here *hd, char *file)
{
	int	i;

	i = 0;
	while (i < hd->nbhdocs)
	{
		if (!ft_strcmp(hd[i].limit, file))
			return (hd[i].fd[0]);
		i++;
	}
	return (-1);
}
