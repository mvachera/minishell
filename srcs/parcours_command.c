/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcours_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:03:50 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/10 18:48:30 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_cmd(t_pipex *pipex)
{
	char	**all_cmd;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	all_cmd = ft_calloc(sizeof(char *), (pipex->cmd_count + 1));
	if (!all_cmd)
		return (NULL);
	while (i[0] < pipex->count)
	{
		if (pipex->token[i[0]] == PIPE)
			i[1]++;
		else if (pipex->token[i[0]] == COMMAND || pipex->token[i[0]] == BUILTIN)
		{
			get_all_cmd2(pipex, i, all_cmd);
			if (!all_cmd[i[1]])
			{
				while (i[1] >= 0)
					free(all_cmd[i[1]--]);
				return (free(all_cmd), NULL);
			}
		}
		i[0]++;
	}
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
	while (i < pipex->count)
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
	parcours_cmd2(pipex);
	while (i < pipex->count)
	{
		if (pipex->token[i] == COMMAND)
		{
			c = i;
			tab_tmp = ft_split(pipex->tab[i], ' ');
			cmd = get_cmd(tab_tmp, pipex);
			negatif_to_positif(pipex->tab[i]);
			if (!cmd)
				pipex->code_err = 127;
			if (!cmd && errno == 13)
				ft_printf("%s : Permission denied\n", pipex->tab[i]);
			else if (!cmd && is_slash(pipex->tab[i]) == 0)
				ft_printf("%s : command not found\n", pipex->tab[i]);
			else if (!cmd && is_slash(pipex->tab[i]) == 1)
				ft_printf("%s : No such file or directory\n", pipex->tab[i]);
			else if (cmd && is_slash(pipex->tab[i]) == 1)
				ft_printf("%s : Is a directory\n", pipex->tab[i]);
			if (cmd)
				free(cmd);
			free_map(tab_tmp);
			positif_to_negatif(pipex->tab[i]);
		}
		i++;
	}
}

void	parcours_cmd2(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == COMMAND || pipex->token[i] == BUILTIN)
		{
			i++;
			if (pipex->tab[i] == NULL)
				return ;
			while (pipex->tab[i] && pipex->token[i] != PIPE)
			{
				if (pipex->token[i] == COMMAND || pipex->token[i] == BUILTIN)
					pipex->token[i] = ARGUMENT;
				i++;
			}
			if (pipex->tab[i] == NULL)
				return ;
		}
		i++;
	}
}
