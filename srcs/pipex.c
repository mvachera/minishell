/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:40:46 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/12 06:57:06 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(char **tab2, t_pipex *pipex)
{
	char	**tab;
	char	*pathcmd;
	int		j;

	j = 0;
	if (tab2[0] && ft_strchr(tab2[0], '/'))
	{
		if (access(tab2[0], F_OK | X_OK) != -1)
			return (ft_strdup(tab2[0]));
		return (NULL);
	}
	tab = find_path(pipex->envp);
	if (!tab)
		return (NULL);
	while (tab && tab[j])
	{
		pathcmd = ft_strjoin(tab[j], tab2[0]);
		if (access(pathcmd, F_OK | X_OK) != -1)
			return (free_map(tab), pathcmd);
		free(pathcmd);
		j++;
	}
	return (free_map(tab), NULL);
}

void	execute(t_pipex *pipex, char *command, char **tab)
{
	if (command)
	{
		clean_arg(tab);
		execve(command, tab, pipex->envp);
		free(command);
	}
	free_pipex(pipex);
	free_map(tab);
	return (exit(pipex->code_err = 127));
}

void	child_process(t_pipex *pipex, int index)
{
	char	**tab2;
	char	*cmd;

	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, &antislash);
	if (index != 0)
		dup2(pipex->prev, 0);
	if (index != 0)
		close(pipex->prev);
	if (index != pipex->cmd_count - 1)
		dup2(pipex->pipefd[1], 1);
	child_process2(pipex);
	openfiles(pipex, index);
	if (!pipex->cmd_args[index])
		return (free_pipex(pipex), exit(0));
	if (check_builtin(pipex->cmd_args[index]) == 1)
		execute_builtin(pipex->cmd_args[index], pipex, 1, index);
	tab2 = ft_split(pipex->cmd_args[index], ' ');
	if (!tab2)
		return (ft_printf("Function split fail\n"), exit(EXIT_FAILURE));
	if (!*tab2)
		return (free_map(tab2), ft_printf("Incorrect argument\n"),
			exit(EXIT_FAILURE));
	cmd = get_cmd(tab2, pipex);
	execute(pipex, cmd, tab2);
}

int	ft_exec(t_pipex *pipex)
{
	int			i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < pipex->cmd_count)
	{
		if (pipe(pipex->pipefd) == -1)
			return (ft_printf("Function pipe fail\n"), 0);
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (ft_printf("Function fork fail\n"),
				close(pipex->pipefd[0]),
				close(pipex->pipefd[1]), 0);
		else if (pipex->pid[i] == 0)
			child_process(pipex, i);
		close(pipex->pipefd[1]);
		if (i != 0)
			close(pipex->prev);
		pipex->prev = pipex->pipefd[0];
		signal(SIGQUIT, SIG_IGN);
		i++;
	}
	i = 0;
	close(pipex->pipefd[0]);
	return (waitfunction(pipex), 1);
}

int	main_pipex(char *str, t_pipex *pipex)
{
	int	tmp;

	pipex->code_err = 0;
	pipex->cmd_count = ft_count(str, '|');
	if (pipex->cmd_count >= 1024)
		return (pipex->code_err = 127, ft_printf("Pipex: too many commands\n"),
			free_memory(pipex), 127);
	parcours_cmd(pipex);
	pipex->cmd_args = get_all_cmd(pipex);
	if (!pipex->cmd_args)
		return (pipex->code_err = 127, free_memory(pipex), 127);
	tmp = ft_exec(pipex);
	if (tmp == 1)
		close(pipex->pipefd[0]);
	parcours_last_command(pipex);
	free_memory(pipex);
	free_map(pipex->cmd_args);
	return (0);
}
