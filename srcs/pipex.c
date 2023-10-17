/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:40:46 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/17 17:35:59 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(char **tab2, t_pipex *pipex)
{
	char	**tab;
	char	*pathcmd;
	int		j;

	j = 0;
	if (ft_strchr(tab2[0], '/'))
	{
		if (access(tab2[0], F_OK | X_OK) != -1)
			return (ft_strdup(tab2[0]));
		return (NULL);
	}
	tab = find_path(pipex->envp);
	if (!tab)
		return (ft_printf("Function find path fail\n"),
			exit(EXIT_FAILURE), NULL);
	while (tab[j] && tab)
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
		execve(command, tab, pipex->envp);
		free(command);
	}
	free_map(tab);
	free_pipex(pipex);
	return (exit(EXIT_FAILURE));
}

void	child_process(t_pipex *pipex, int index)
{
	char	**tab2;
	char	*cmd;

	if (index == 0 || index == pipex->cmd_count - 1)
		je_souffre(pipex, index);
	if (index != 0)
		dup2(pipex->prev, 0);
	if (index != pipex->cmd_count - 1)
		dup2(pipex->pipefd[1], 1);
	close(pipex->pipefd[1]);
	close(pipex->pipefd[0]);
	// if (check_builtin(pipex->cmd_args[index]) == 1)
	// {
	// 	//printf("%s", pipex->cmd_args[index]);
	// 	execute_builtin(pipex->cmd_args[index], pipex);
	// }
	tab2 = ft_split(pipex->cmd_args[index], ' ');
	if (!tab2)
		return (ft_printf("Function split fail\n"), exit(EXIT_FAILURE));
	if (!*tab2)
		return (free_map(tab2), ft_printf("L'argument est incorrect\n")
			, exit(EXIT_FAILURE));
	cmd = get_cmd(tab2, pipex);
	execute(pipex, cmd, tab2);
}

int	ft_exec(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		if (pipe(pipex->pipefd) == -1)
			return (ft_printf("Function pipe fail\n"), 0);
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (ft_printf("Function fork fail\n"),
				close(pipex->pipefd[0]), close(pipex->pipefd[1]), 0);
		else if (pipex->pid[i] == 0)
			child_process(pipex, i);
		close(pipex->pipefd[1]);
		if (i != 0)
			close(pipex->prev);
		pipex->prev = pipex->pipefd[0];
		i++;
	}
	i = 0;
	while (i < pipex->cmd_count)
		waitpid(pipex->pid[i++], NULL, 0);
	return (1);
}

int	main_pipex(char *str, t_pipex *pipex, char **envp)
{
	int	tmp;

	pipex->envp = envp;
	parcours_cmd(pipex);
	pipex->cmd_count = ft_count(str, '|');
	if (pipex->cmd_count >= 1024)
		return (ft_printf("Pipex: too many commands\n"), free_memory(pipex),
			0);
	pipex->cmd_args = get_all_cmd(pipex);
	if (!pipex->cmd_args)
		return (free_memory(pipex), 0);
	ft_init_pipex(pipex);
	if (pipex->here_doc == 1)
		ft_here_doc(pipex);
	// test_print(pipex);
	tmp = ft_exec(pipex);
	if (pipex->here_doc == 1)
		unlink(pipex->in_name);
	if (tmp == 1)
		close(pipex->pipefd[0]);
	free_pipex(pipex);
	return (1);
}
