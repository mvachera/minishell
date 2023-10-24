/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:37:58 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/24 17:12:39 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(char *str)
{
	char	c;
	int		i;

	i = 0;
	c = str[i++];
	while (str[i] && str[i] != c)
	{
		str[i] = -str[i];
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
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	j = 0;
	i = 1;
	while (j < len - 1)
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

void	modif_to_do(t_pipex *pipex)
{
	int		i;
	char	*tmp;

	i = 0;
	while (pipex->tab[i])
	{
		if (pipex->tab[i][0] == '\'' || pipex->tab[i][0] == '\"')
		{
			tmp = handle_quotes2(pipex->tab[i]);
			free(pipex->tab[i]);
			pipex->tab[i] = tmp;
		}
		i++;
	}
}
