/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:55:33 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/11 22:15:48 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parcours_last_command(t_pipex *pipex)
{
	char	**tab_cmd;
	char	*cmd;
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (i < pipex->count)
	{
		if (pipex->token[i] == PIPE)
			c++;
		if (c == pipex->cmd_count - 1 && pipex->token[i] == COMMAND)
		{
			tab_cmd = ft_split(pipex->tab[i], ' ');
			cmd = get_cmd(tab_cmd, pipex);
			negatif_to_positif(pipex->tab[i]);
			if (!cmd)
				pipex->code_err = 127;
			if (!cmd && errno == 13)
				pipex->code_err = 126;
			else if (!cmd && is_slash(pipex->tab[i]) == 0)
				pipex->code_err = 127;
			else if (!cmd && is_slash(pipex->tab[i]) == 1)
				pipex->code_err = 127;
			else if (cmd && is_slash(pipex->tab[i]) == 1
				&& in_env(pipex, pipex->tab[i]) == 1)
				pipex->code_err = 126;
			if (cmd)
				free(cmd);
			free_map(tab_cmd);
		}
		i++;
	}
}

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

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen3(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '?' && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9'))
			break ;
		i++;
	}
	return (i);
}
