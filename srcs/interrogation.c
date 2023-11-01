/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrogation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:16:28 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/01 19:38:22 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_interrogation(t_pipex *pipex, char *str)
{
	char	*code_error;
	char	*dst;
	int		i;

	i = 0;
	while (str[i] && str[i] != '?')
		i++;
	if (i != 0)
		return (ft_strdup(str + i));
	code_error = ft_itoa(pipex->code_err);
	if (!code_error)
		return (NULL);
	dst = str_johnny(code_error, str + i + 1);
	if (!dst)
		return (free(code_error), NULL);
	free(code_error);
	return (dst);
}

int	last_command(t_pipex *pipex, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (pipex->tab[i])
	{
		if (pipex->token[i] == COMMAND || pipex->token[i] == BUILTIN)
			count++;
		if (ft_strcmp(pipex->tab[i], str) == 0 && count == pipex->cmd_count)
			return (1);
		i++;
	}
	return (0);
}

int	is_interrogation(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '?')
			return (1);
		i++;
	}
	return (0);
}
