/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcours_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 08:03:03 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/12 08:05:18 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parcours_cmd3(t_pipex *pipex, char *cmd, int i)
{
	if (!cmd)
		pipex->code_err = 127;
	if (!cmd && errno == 13)
		ft_printf("%s : Permission denied\n", pipex->tab[i]);
	else if (!cmd && is_slash(pipex->tab[i]) == 0)
		ft_printf("%s : command not found\n", pipex->tab[i]);
	else if (!cmd && is_slash(pipex->tab[i]) == 1)
		ft_printf("%s : No such file or directory\n", pipex->tab[i]);
	else if (cmd && is_slash(pipex->tab[i]) == 1 && in_env(pipex,
			pipex->tab[i]) == 1)
		ft_printf("%s : Is a directory\n", pipex->tab[i]);
}

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
			parcours_last_command2(pipex, cmd, i);
			if (cmd)
				free(cmd);
			free_map(tab_cmd);
		}
		i++;
	}
}

void	parcours_last_command2(t_pipex *pipex, char *cmd, int i)
{
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
}
