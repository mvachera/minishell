/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:55:33 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/12 08:05:00 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_env(t_pipex *pipex, char *str)
{
	int	len;
	int	i;

	i = 0;
	while (pipex->envp[i])
	{
		len = ft_strlen4(pipex->envp[i]) + 1;
		if (ft_strcmp(pipex->envp[i] + len, str) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	waitfunction(t_pipex *pipex)
{
	static int	var;
	int			i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pid[i++], &pipex->code_err, 0);
		if (WIFEXITED(pipex->code_err))
			pipex->code_err = WEXITSTATUS(pipex->code_err);
		if (pipex->code_err == 131 && !var++)
			ft_printf("Quit (core dumped)\n");
	}
	signal(SIGINT, &ctrlc);
}

void	child_process2(t_pipex *pipex)
{
	close(pipex->pipefd[1]);
	close(pipex->pipefd[0]);
	pipex->fd = -1;
}
