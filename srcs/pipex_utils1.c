/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:41:01 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/17 16:05:02 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_pipex(t_pipex *pipex)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (pipex->tab[i])
	{
		if (pipex->token[i] == HERE_DOC)
		{
			pipex->in_name = ft_strdup("here_doc");
			pipex->here_doc = 1;
			pipex->limiteur = "LIMITER";
		}
		if (pipex->token[i] == COMMAND || pipex->token[i] == BUILTIN)
			f++;
		if (pipex->token[i] == FILES && f != 0)
			pipex->out_name = ft_strdup(pipex->tab[i]);
		if (pipex->token[i] == FILES && f == 0)
		{
			pipex->in_name = ft_strdup(pipex->tab[i]);
			f++;
		}
		i++;
	}
}

char	**find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void	je_souffre(t_pipex *pipex, int index)
{
	if (index == 0 && pipex->in_name != NULL)
	{
		pipex->fd = open(pipex->in_name, O_RDONLY);
		if (pipex->fd == -1)
			return (ft_printf("Fail open in_name file\n"),
				close(pipex->pipefd[1]), close(pipex->pipefd[0]),
				exit(EXIT_FAILURE));
		dup2(pipex->fd, 0);
		close(pipex->fd);
	}
	if (index == pipex->cmd_count - 1 && pipex->out_name != NULL)
	{
		pipex->fd = open(pipex->out_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (pipex->fd == -1)
			return (ft_printf("Fail open out_name file\n"),
				close(pipex->pipefd[1]), close(pipex->pipefd[0]),
				exit(EXIT_FAILURE));
		dup2(pipex->fd, 1);
		close(pipex->fd);
	}
}

void	ft_here_doc(t_pipex *pipex)
{
	char	*str;
	int		fd;

	je_souffre_trop(pipex);
	fd = open(pipex->in_name, O_RDWR | O_CREAT, 0664);
	if (fd == -1)
		return (ft_printf("Fail open here_doc\n"), exit(EXIT_FAILURE));
	while (1)
	{
		str = get_next_line(0, 0);
		if (!str)
			break ;
		if (!ft_strcmp(str, pipex->str_end))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd);
		free(str);
	}
	get_next_line(0, 1);
	free(pipex->str_end);
	close(fd);
}
