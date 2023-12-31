/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:27:38 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/08 19:41:12 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*manage_arg(char *str, t_pipex *pipex)
{
	char	*dst;
	int		len;
	int		i;

	len = get_len(str, pipex);
	i = 0;
	dst = ft_calloc(sizeof(char), (len + 1));
	if (!dst)
		return (NULL);
	while (i < pipex->count)
	{
		if (ft_strcmp(str, pipex->tab[i]) == 0)
		{
			ft_strcpy(dst, pipex->tab[i++]);
			while (pipex->tab[i] && pipex->token[i] != PIPE)
			{
				if (pipex->token[i] == ARGUMENT)
					ft_strcat(dst, pipex->tab[i]);
				i++;
			}
			break ;
		}
		i++;
	}
	return (dst);
}

int	get_len(char *str, t_pipex *pipex)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < pipex->count)
	{
		if (ft_strcmp(str, pipex->tab[i]) == 0)
		{
			count = ft_strlen(str);
			i++;
			while (pipex->tab[i] && pipex->token[i] != PIPE)
			{
				if (pipex->token[i] == ARGUMENT)
					count += ft_strlen(pipex->tab[i]) + 1;
				i++;
			}
			break ;
		}
		i++;
	}
	return (count);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	dest[i++] = ' ';
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
