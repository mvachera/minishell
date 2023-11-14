/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:05:17 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/14 21:58:40 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_random(t_pipex *pipex, int i)
{
	if (pipex->tab[0] && pipex->quote[i] == NO_QUOTE && ft_strcmp(pipex->tab[0],
			"|") == 0)
		return (pipex->code_err = 2,
			print_error_syntax(pipex->tab[0][0], 0, 1),
				1);
	if (pipex->tab[0] && pipex->tab[0][0] == '!'
		&& ft_strlen(pipex->tab[i]) == 1)
		return (pipex->code_err = 1, 1);
	if (pipex->tab[0] && pipex->tab[0][0] == ':'
		&& ft_strlen(pipex->tab[i]) == 1)
		return (pipex->code_err = 0, 1);
	if (pipex->token[0] == COMMAND && check_base_directory(pipex) != 1)
		return (1);
	while (i < pipex->count)
	{
		if (check_random2(pipex, i) != 0)
			return (1);
		i++;
	}
	if (pipex->token[pipex->count - 1] >= 0 && pipex->token[pipex->count - 1]
		<= 4 && pipex->quote[pipex->count - 1] == NO_QUOTE)
		return (pipex->code_err = 2,
			print_error_syntax(0, 0, 3), 1);
	return (0);
}

int	check_random2(t_pipex *pipex, int i)
{
	if (pipex->token[i] == RANDOM && pipex->quote[i] == NO_QUOTE)
		return (pipex->code_err = 2, ft_handle_size(pipex->tab[i]));
	if (check_token_kind(pipex, i) == 1)
		return (1);
	if (pipex->token[i] > 0 && pipex->token[i] < 5)
	{
		if (i + 1 < pipex->count && pipex->tab[i + 1] == NULL)
			return (ft_printf("ambiguous redirect\n"), 1);
		else if (pipex->tab[i + 1] && pipex->token[i + 1] >= 0
			&& pipex->token[i + 1] <= 4)
			return (ft_printf("syntax error near unexpected token %s\n",
					pipex->tab[i + 1]), 1);
	}
	return (0);
}

int	check_base_directory(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	while (pipex->tab[0][i])
	{
		if (pipex->tab[0][i] != '.' && pipex->tab[0][i] != '/')
			return (1);
		j = 0;
		while (pipex->tab[0][i + j] == '.')
		{
			j++;
			if (j == 3)
			{
				ft_printf(": No such file or directory\n");
				return (pipex->code_err = 127, 0);
			}
		}
		i++;
	}
	ft_printf(": Is a directory\n");
	pipex->code_err = 126;
	return (0);
}

void	print_error_syntax(char c, char d, int i)
{
	if (c == '|')
		i = 1;
	if (i == 1)
		ft_printf("syntax error near unexpected token `%c'\n", c);
	if (i == 2)
		ft_printf("syntax error near unexpected token `%c%c'\n", c, d);
	if (i == 3)
		ft_printf("syntax error near unexpected token `newline'\n");
}

int	ft_handle_size(char *tab)
{
	int	i;

	i = 0;
	if (ft_strlen(tab) == 3)
	{
		if (ft_strncmp("<<<", tab, 3) == 0)
			return (1);
		return (print_error_syntax(tab[2], 0, 1), 2);
	}
	else if (ft_strlen(tab) > 3)
	{
		if (ft_strncmp("<<", tab, 2) == 0 && (tab[2] == '|' || tab[3] == '|'))
			return (print_error_syntax('|', 0, 1), 2);
		if ((ft_strncmp("<<<", tab, 3) == 0) && tab[4] == '|')
			return (print_error_syntax(tab[3], 0, 1), 2);
		if ((ft_strncmp("<<<", tab, 3) == 0) && tab[4] != '|')
			return (print_error_syntax(tab[3], tab[4], 2), 2);
		return (print_error_syntax(tab[2], tab[3], 2), 2);
	}
	if (ft_strncmp("<>", tab, 2) == 0)
		return (print_error_syntax(tab[0], tab[1], 3), 2);
	return (print_error_syntax(tab[0], 0, 1), 2);
}
