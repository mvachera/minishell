/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_one_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:01:39 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/08 22:04:21 by mvachera         ###   ########.fr       */
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
	parcours_cmd2(pipex);
	if (builtin_open_files(pipex) == 0)
		return (1);
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

void	handle_exit(t_pipex *pipex, int nb_arg)
{
	int	i;

	i = 0;
	ft_printf("exit\n");
	while (i < pipex->count)
	{
		if (pipex->token[i] == ARGUMENT)
		{
			pipex->code_err = 2;
			ft_printf("exit : %s : numeric argument required\n", pipex->tab[i]);
		}
		i++;
	}
	if (nb_arg > 1)
		return (pipex->code_err = 1, ft_printf("exit: too many arguments\n"),
			free_exit(pipex));
	free_exit(pipex);
	exit(pipex->code_err);
}
