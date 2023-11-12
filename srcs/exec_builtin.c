/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:00:11 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/12 07:28:51 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(char *str, t_pipex *pipex, int to_free, int index)
{
	char	**arg;
	int		nb_arg;

	nb_arg = count_arg(pipex, str, index);
	arg = get_arg(pipex, nb_arg, index);
	if (nb_arg > 0)
		clean_arg(arg);
	if (ft_strcmp(str, "echo") == 0
		&& nb_arg > 0 && echo_first_arg(arg[0]) == 1)
		echo_command(arg, 0, nb_arg);
	else if (ft_strcmp(str, "echo") == 0)
		echo_command(arg, 1, nb_arg);
	else if (ft_strcmp(str, "exit") == 0)
		handle_exit(pipex, arg, nb_arg, to_free);
	else
		execute_builtin2(str, pipex, arg, nb_arg);
	if (nb_arg > 0)
		free_map(arg);
	if (to_free == 0)
		free_memory(pipex);
	else
	{
		free_pipex(pipex);
		exit(0);
	}
}

void	execute_builtin2(char *str, t_pipex *pipex, char **arg, int nb_arg)
{
	if (ft_strcmp(str, "pwd") == 0)
		pwd_command();
	else if (ft_strcmp(str, "cd") == 0)
	{
		if (nb_arg > 1)
			pipex->code_err = 1;
		if (nb_arg == 0)
			chdir("/mnt/nfs/homes/mvachera");
		else if (nb_arg > 1)
			ft_printf("cd : too many arguments\n");
		else
			cd_command(pipex, arg[0]);
	}
	else if (ft_strcmp(str, "env") == 0)
	{
		if (nb_arg != 0)
			pipex->code_err = 127;
		if (nb_arg == 0)
			env_command(pipex);
		else
			ft_printf("env : %s : no such file or directory\n", arg[0]);
	}
	else
		execute_builtin3(str, pipex, arg, nb_arg);
}

void	execute_builtin3(char *str, t_pipex *pipex, char **arg, int nb_arg)
{
	if (ft_strcmp(str, "export") == 0)
	{
		if (nb_arg == 0)
			env_command(pipex);
		else
			export_command(pipex, arg[0]);
	}
	else if (ft_strcmp(str, "unset") == 0 && nb_arg > 0)
		unset_command(arg[0], pipex);
}

char	**get_arg(t_pipex *pipex, int nb_arg, int index)
{
	char	**all_arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (nb_arg == 0)
		return (NULL);
	all_arg = ft_calloc(sizeof(char *), (nb_arg + 1));
	if (!all_arg)
		return (NULL);
	nb_arg = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == PIPE)
			j++;
		else if (j == index && (pipex->token[i] == COMMAND
				|| pipex->token[i] == BUILTIN))
		{
			get_arg2(pipex, &i, &nb_arg, all_arg);
			break ;
		}
		i++;
	}
	return (all_arg);
}

void	get_arg2(t_pipex *pipex, int *i, int *nb_arg, char **all_arg)
{
	(*i)++;
	while (*i < pipex->count && pipex->token[*i] != PIPE)
	{
		if (pipex->token[*i] == ARGUMENT
			&& ft_strcmp(pipex->tab[*i], "''") != 0
			&& ft_strcmp(pipex->tab[*i], "\"\"") != 0)
		{
			all_arg[*nb_arg] = ft_strdup(pipex->tab[*i]);
			if (!all_arg[*nb_arg])
				return ;
			(*nb_arg)++;
		}
		(*i)++;
	}
}
