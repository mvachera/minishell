/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:55:33 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/10 19:01:07 by mvachera         ###   ########.fr       */
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
			else if (cmd && is_slash(pipex->tab[i]) == 1)
				pipex->code_err = 126;
			if (cmd)
				free(cmd);
			free_map(tab_cmd);
		}
		i++;
	}
}
