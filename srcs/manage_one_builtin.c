/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_one_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:01:39 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/10 19:46:20 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtin(t_pipex *pipex, char *str)
{
	int	i;
	int	tmp[2];

	i = 0;
	pipex->code_err = 0;
	pipex->cmd_count = ft_count(str, '|');
	if (pipex->cmd_count != 1 || is_builtin(pipex) == 0)
		return (0);
	parcours_cmd2(pipex);
	tmp[0] = dup(0);
	tmp[1] = dup(1);
	if (builtin_open_files(pipex) == 0)
	{
		dup2(tmp[0], 0);
		dup2(tmp[1], 1);
		close(tmp[0]);
		close(tmp[1]);
		return (1);
	}
	dup2(tmp[0], 0);
	dup2(tmp[1], 1);
	close(tmp[0]);
	close(tmp[1]);
	while (i < pipex->count)
	{
		if (pipex->token[i] == BUILTIN)
			return (execute_builtin(pipex->tab[i], pipex, 0, 0), 1);
		i++;
	}
	return (0);
}

int	is_builtin(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == BUILTIN)
			return (1);
		i++;
	}
	return (0);
}

void	handle_exit(t_pipex *pipex, char **arg, int nb_arg)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (nb_arg > 1 && is_numeric_string(arg[0]) != 0)
	{
		pipex->code_err = 1;
		ft_printf("exit: too many arguments\n");
		return ;
	}
	else if (nb_arg == 1 && is_numeric_string(arg[0]) == 1)
		pipex->code_err = 100;
	else if (nb_arg == 1 && is_numeric_string(arg[0]) == 2)
		pipex->code_err = 156;
	else if (nb_arg == 1 && is_numeric_string(arg[0]) == 3)
		pipex->code_err = ft_atoi(arg[0]);
	else if (nb_arg > 0 && is_numeric_string(arg[0]) == 0)
	{
		pipex->code_err = 2;
		ft_printf("exit : %s : numeric argument required\n", arg[0]);
	}
	free_exit(pipex, arg, nb_arg);
	exit(pipex->code_err);
}

int	is_numeric_string(char *str)
{
	int	i;
	int	result;

	if (str[0] != '-' && str[0] != '+' && (str[0] < '0' || str[0] > '9'))
		return (0);
	i = 1;
	result = 3;
	if (str[0] == '+')
		result = 1;
	if (str[0] == '-')
		result = 2;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (result);
}
