/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcours_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:03:50 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/17 16:28:25 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_cmd(t_pipex *pipex)
{
	char	**all_cmd;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	all_cmd = malloc(sizeof(char *) * (nb_cmd(pipex) + 1));
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
					free(all_cmd[i[1]--]);
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
	if (pipex->tab[i[0]][0] == '\'' || pipex->tab[i[0]][0] == '\"')
		all_cmd[i[1]] = handle_quotes2(pipex->tab[i[0]]);
	else
		all_cmd[i[1]] = ft_strdup(pipex->tab[i[0]]);
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
	while (pipex->tab[i])
	{
		if (pipex->token[i] == COMMAND)
		{
			c = i;
			tab_tmp = ft_split(pipex->tab[i], ' ');
			cmd = get_cmd(tab_tmp, pipex);
			if (!cmd)
				(ft_printf("Command %s not found\n", pipex->tab[i]));
			else
				free(cmd);
			free_map(tab_tmp);
		}
		parcours_cmd2(pipex, c, i);
		i++;
	}
}

void	parcours_cmd2(t_pipex *pipex, int c, int i)
{
	if (pipex->token[c] == COMMAND && pipex->token[i] == ARGUMENT)
		ft_printf("%s, bad argument of %s\n", pipex->tab[i], pipex->tab[c]);
}
