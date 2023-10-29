/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcours_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:03:50 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/27 16:33:57 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_cmd(t_pipex *pipex)
{
	char	**all_cmd;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	all_cmd = ft_calloc(sizeof(char *), (nb_cmd(pipex) + 1));
	if (!all_cmd)
		return (NULL);
	while (pipex->tab[i[0]])
	{
		if (pipex->token[i[0]] == COMMAND || pipex->token[i[0]] == BUILTIN)
		{
			get_all_cmd2(pipex, i, all_cmd);
			if (!all_cmd[i[1]])
			{
				while (i[1] >= 0)
					free(all_cmd[--i[1]]);
				return (free(all_cmd), NULL);
			}
			i[1]++;
		}
		i[0]++;
	}
	all_cmd[i[1]] = 0;
	return (all_cmd);
}

void	get_all_cmd2(t_pipex *pipex, int *i, char **all_cmd)
{
	if (check_arg(pipex->tab[i[0]], pipex) == 1
		&& pipex->token[i[0]] == COMMAND)
		all_cmd[i[1]] = manage_arg(pipex->tab[i[0]], pipex);
	else
		all_cmd[i[1]] = ft_strdup(pipex->tab[i[0]]);
}

int	check_arg(char *str, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->tab[i])
	{
		if (ft_strcmp(str, pipex->tab[i]) == 0)
		{
			if (pipex->tab[i])
				i++;
			else
				return (0);
			while (pipex->tab[i] != NULL && pipex->token[i] != PIPE)
			{
				if (pipex->token[i] == ARGUMENT)
					return (1);
				i++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}

void	parcours_cmd(t_pipex *pipex)
{
	int		i;
	int		c;
	char	*cmd;
	char	**tab_tmp;

	i = 0;
	c = 0;
	cmd = NULL;
	tab_tmp = NULL;
	parcours_cmd2(pipex);
	while (pipex->tab[i])
	{
		if (pipex->token[i] == COMMAND)
		{
			c = i;
			tab_tmp = ft_split(pipex->tab[i], ' ');
			cmd = get_cmd(tab_tmp, pipex);
			if (!cmd)
				(ft_printf("%s : command not found\n", pipex->tab[i]));
			else
				free(cmd);
			free_map(tab_tmp);
		}
		i++;
	}
}

void	parcours_cmd2(t_pipex *pipex)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (pipex->tab[i])
	{
		if (pipex->token[i] == COMMAND && pipex->tab[i + 1])
		{
			j = i + 1;
			tmp = i;
			while (pipex->tab[j])
			{
				if (pipex->token[j] == PIPE)
					i++;
				else if (pipex->token[j] == COMMAND && i == tmp)
					pipex->token[j] = ARGUMENT;
				j++;
			}
		}
		i++;
	}
}
