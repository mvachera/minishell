/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:37:58 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/22 15:34:32 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char **tab, t_pipex *pipex)
{
	int		i;
	char	*tmp;

	i = 0;
	pipex->quote = ft_calloc(sizeof(int), pipex->count);
	if (!pipex->quote)
		return (-1);
	while (i < pipex->count)
	{
		pipex->quote[i] = NO_QUOTE;
		if (tab[i] && find_quotes(tab[i]) != 0 && ft_strcmp(tab[i], "\"\"") != 0
			&& ft_strcmp(tab[i], "''") != 0)
		{
			if (find_quotes(tab[i]) == 1)
				pipex->quote[i] = SINGLE_QUOTE;
			else if (find_quotes(tab[i]) == 2)
				pipex->quote[i] = DOUBLE_QUOTES;
			handle_quotes(tab[i]);
			tmp = handle_quotes2(tab[i]);
			free(tab[i]);
			tab[i] = tmp;
		}
		i++;
	}
	return (0);
}

int	find_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		if (str[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

void	handle_quotes(char *str)
{
	char	c;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i + 1])
				c = str[i++];
			else
				break ;
			while (str[i] && str[i] != c)
			{
				if (str[i] != - '>' && str[i] != - '<')
					str[i] = -str[i];
				if (str[i] == ' ' || str[i] == '\t')
					str[i] = -str[i];
				i++;
			}
		}
		i++;
	}
}

char	*handle_quotes2(char *s)
{
	char	*dest;
	char	c;
	int		len;
	int		i[2];

	len = 0;
	while (s[len + 1])
		len++;
	dest = ft_calloc(sizeof(char), len);
	if (!dest)
		return (NULL);
	i[1] = 0;
	i[0] = 0;
	while (s[i[0]] && i[1] < len - 1 && s[i[0]] != '\'' && s[i[0]] != '\"')
		dest[i[1]++] = s[i[0]++];
	c = s[i[0]++];
	while (s[i[0]] && i[1] < len - 1)
	{
		while (s[i[0]] && s[i[0]] == c)
			i[0]++;
		if (!s[i[0]])
			break ;
		dest[i[1]++] = s[i[0]++];
	}
	return (dest);
}
