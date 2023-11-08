/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:58:15 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/07 15:59:53 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_here_doc(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->tab[i])
	{
		if (pipex->token[i] == HERE_DOC)
		{
			pipex->here_doc = 1;
			pipex->file_here_doc = "here_doc";
			pipex->limiteur = pipex->tab[i];
		}
		i++;
	}
}

void	openfiles(t_pipex *pipex, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipex->tab[i])
	{
		if (pipex->token[i] == PIPE)
			j++;
		else if ((pipex->token[i] == COMMAND || pipex->token[i] == BUILTIN)
			&& j == index)
		{
			handle_in_files(pipex, i);
			handle_out_files(pipex, i);
			break ;
		}
		i++;
	}
}

void	handle_in_files(t_pipex *pipex, int i)
{
	while (i > 0 && pipex->token[i] != PIPE)
		i--;
	i++;
	while (pipex->tab[i] && pipex->token[i] != PIPE)
	{
		if (pipex->token[i] == IN_FILES || pipex->token[i] == HERE_DOC)
		{
			if (pipex->token[i] == IN_FILES)
				pipex->fd = open(pipex->tab[i], O_RDONLY);
			else if (pipex->token[i] == HERE_DOC)
				pipex->fd = open(pipex->file_here_doc, O_RDONLY);
			if (pipex->fd == -1)
			{
				ft_printf("%s : No such file or directory\n", pipex->tab[i]);
				free_pipex(pipex);
				exit(1);
			}
			dup2(pipex->fd, 0);
			close(pipex->fd);
		}
		i++;
	}
}

void	handle_out_files(t_pipex *pipex, int i)
{
	while (i > 0 && pipex->token[i] != PIPE)
		i--;
	i++;
	while (pipex->tab[i] && pipex->token[i] != PIPE)
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
				ft_printf("%s : No such file or directory\n", pipex->tab[i]);
				free_pipex(pipex);
				exit(1);
			}
			dup2(pipex->fd, 1);
			close(pipex->fd);
		}
		i++;
	}
}

// void	openfiles(t_pipex *pipex, int i)
// {
// 	mallocfichiers(pipex);
// 	while (pipex->files[i])
// 	{
// 		if (pipex->type[i] == CHEVRON_G)
// 			pipex->fd = open(pipex->files[i], O_RDONLY);
// 		else if (pipex->type[i] == D_CHEVRON_G)
// 			pipex->fd = open(pipex->file_here_doc, O_RDONLY);
// 		else if (pipex->type[i] == CHEVRON_D)
// 			pipex->fd = open(pipex->files[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
// 		else if (pipex->type[i] == D_CHEVRON_D)
// 			pipex->fd = open(pipex->files[i], O_CREAT | O_RDWR
// 					| O_APPEND, 0666);
// 		if (pipex->fd == -1)
// 		{
// 			ft_printf("%s : No such file or directory\n", pipex->files[i]);
// 			free_files(pipex);
// 			free_pipex(pipex);
// 			exit(1);
// 		}
// 		openfiles2(pipex, i);
// 		close(pipex->fd);
// 		i++;
// 	}
// 	free_files(pipex);
// }

// void	openfiles2(t_pipex *pipex, int i)
// {
// 	if (pipex->type[i] == CHEVRON_G || pipex->type[i] == D_CHEVRON_G)
// 		dup2(pipex->fd, 0);
// 	else
// 		dup2(pipex->fd, 1);
// }

// void	mallocfichiers(t_pipex *pipex)
// {
// 	int		i[2];

// 	i[0] = 0;
// 	i[1] = 0;
// 	while (pipex->tab[i[0]])
// 	{
// 		if (pipex->token[i[0]] == IN_FILES || pipex->token[i[0]] == OUT_FILES
// 			|| pipex->token[i[0]] == HERE_DOC)
// 			i[1]++;
// 		i[0]++;
// 	}
// 	pipex->files = ft_calloc(sizeof(char *), i[1] + 1);
// 	pipex->type = ft_calloc(sizeof(int), i[1]);
// 	i[0] = 0;
// 	i[1] = 0;
// 	while (pipex->tab[i[0]])
// 	{
// 		if (pipex->token[i[0]] == IN_FILES || pipex->token[i[0]] == OUT_FILES
// 			|| pipex->token[i[0]] == HERE_DOC)
// 		{
// 			pipex->files[i[1]] = ft_strdup(pipex->tab[i[0]]);
// 			pipex->type[i[1]++] = pipex->token[i[0] - 1];
// 		}
// 		i[0]++;
// 	}
// }
