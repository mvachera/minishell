/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_one_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:01:39 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/01 20:46:36 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtin(t_pipex *pipex, char *str)
{
	int	i;

	i = 0;
	pipex->cmd_count = ft_count(str, '|');
	if (pipex->cmd_count != 1 || is_builtin(pipex) == 0)
		return (0);
	while (pipex->tab[i])
	{
		if (ft_strcmp(pipex->tab[i], "exit") == 0 && pipex->token[i] == BUILTIN)
			handle_exit(pipex, i);
		else if (ft_strcmp(pipex->tab[i], "cd") == 0
			&& pipex->token[i] == BUILTIN)
			return (execute_builtin("cd", pipex, 0), 1);
		else if (ft_strcmp(pipex->tab[i], "unset") == 0
			&& pipex->token[i] == BUILTIN)
			return (execute_builtin("unset", pipex, 0), 1);
		else if (ft_strcmp(pipex->tab[i], "export") == 0
			&& pipex->token[i] == BUILTIN)
			return (execute_builtin("export", pipex, 0), 1);
		else if (handle_builtin2(pipex, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	handle_builtin2(t_pipex *pipex, int i)
{
	if (ft_strcmp(pipex->tab[i], "echo") == 0
		&& pipex->token[i] == BUILTIN)
		return (execute_builtin("echo", pipex, 0), 1);
	else if (ft_strcmp(pipex->tab[i], "echo -n") == 0
		&& pipex->token[i] == BUILTIN)
		return (execute_builtin("echo -n", pipex, 0), 1);
	else if (ft_strcmp(pipex->tab[i], "pwd") == 0
		&& pipex->token[i] == BUILTIN)
		return (execute_builtin("pwd", pipex, 0), 1);
	else if (ft_strcmp(pipex->tab[i], "env") == 0
		&& pipex->token[i] == BUILTIN)
		return (execute_builtin("env", pipex, 0), 1);
	return (0);
}

int	is_builtin(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->tab[i])
	{
		if (pipex->token[i] == BUILTIN)
			return (1);
		i++;
	}
	return (0);
}

void	handle_exit(t_pipex *pipex, int i)
{
	int	arg;

	arg = 0;
	ft_printf("exit\n");
	while (pipex->tab[i])
	{
		if (pipex->token[i] == ARGUMENT && arg == 0)
		{
			arg = 1;
			pipex->code_err = 2;
			ft_printf("exit : %s : numeric argument required\n", pipex->tab[i]);
		}
		else if (pipex->token[i] == OUT_FILES)
		{
			pipex->fd = open(pipex->tab[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (pipex->fd == -1)
				return (ft_printf("Fail open out_name file\n"),
					close(pipex->pipefd[1]), close(pipex->pipefd[0]),
					exit(EXIT_FAILURE));
			close(pipex->fd);
		}
		i++;
	}
	free_exit(pipex);
	exit(0);
}
