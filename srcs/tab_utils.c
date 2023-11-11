/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:11:40 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/11 21:59:20 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_random(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->tab[0] && ft_strcmp(pipex->tab[0], "|") == 0)
		return (pipex->code_err = 2,
			print_error_syntax(pipex->tab[0][0], 0, 1), 1);
	// if (pipex->count == 1 && pipex->tab[0] && pipex->tab[0][0] == '!')
	// 	return (pipex->code_err = 1, 1);
	// // if (pipex->count == 1 && pipex->tab[0] && pipex->tab[0][0] == ':')
	// 	return (1);
	// ft_printf("%s    : %d\n", pipex->tab[0], pipex->token[0]);
	while (i < pipex->count)
	{
		if (pipex->token[i] == RANDOM && pipex->quote[i] == NO_QUOTE)
			return (pipex->code_err = 2, ft_handle_size(pipex->tab[i]));
		if (check_token_kind(pipex, i) == 1)
			return (1);
		i++;
	}
	if (pipex->token[pipex->count - 1] >= 0
		&& pipex->token[pipex->count - 1] <= 4
		&& pipex->quote[pipex->count - 1] == NO_QUOTE)
		return (pipex->code_err = 2,
			print_error_syntax(0, 0, 3), 1);
	return (0);
}

int	is_meta_string(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (is_metacaractere(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	stop_str(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0)
	{
		if (str[i] != ' ' && (str[i] < 9 || str[i] > 13))
			break ;
		i--;
	}
	return (i);
}

int	is_metacaractere(char c)
{
	if (c == '|')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == ' ' || (c >= 9 && c <= 13))
		return (2);
	return (0);
}

char	*cpy(char *str, int i, int j)
{
	char	*line;
	int		k;

	k = 0;
	line = malloc(sizeof(char) * (j - i + 1));
	if (!line)
		return (NULL);
	while (i < j)
	{
		if (is_metacaractere(str[i]) == 2)
		{
			line[k] = ' ';
			k++;
			while (is_metacaractere(str[i]) == 2)
				i++;
		}
		line[k] = str[i];
		i++;
		k++;
	}
	line[k] = '\0';
	return (line);
}
