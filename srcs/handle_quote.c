/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:37:58 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/26 21:55:04 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char **tab, t_pipex *pipex, int count)
{
	int		i;
	char	*tmp;

	i = 0;
	pipex->quote = ft_calloc(sizeof(int), count);
	if (!pipex->quote)
		return (-1);
	while (tab[i])
	{
		pipex->quote[i] = NO_QUOTE;
		if (find_quotes(tab[i]) == 1 || find_quotes(tab[i]) == 1)
		{
			pipex->quote[i] = QUOTE;
			handle_quotes(tab[i]);
			if (ft_strchr(tab[i], ' ') == NULL)
			{
				tmp = handle_quotes2(tab[i]);
				free(tab[i]);
				tab[i] = tmp;
			}
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
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
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
			c = str[i++];
			while (str[i] && str[i] != c)
			{
				str[i] = -str[i];
				i++;
			}
		}
		i++;
	}
}

char	*handle_quotes2(char *str)
{
	char	*dest;
	int		len;
	int		i;
	int		j;

	len = 0;
	while (str[len + 1])
		len++;
	dest = ft_calloc(sizeof(char), len);
	if (!dest)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i] && j < len - 1)
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		dest[j++] = str[i++];
	}
	return (dest);
}
