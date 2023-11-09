/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strange_caracteres.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:07:05 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/09 18:23:06 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strange_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '?' && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9'))
			return (1);
		else if (str[i] == '?')
			return (2);
		i++;
	}
	return (0);
}

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
	if (code_signal(0) == 130)
	{
		pipex->code_err = 130;
		code_signal(1);
	}
	code_error = ft_itoa(pipex->code_err);
	if (!code_error)
		return (NULL);
	dst = str_johnny(code_error, str + i + 1);
	if (!dst)
		return (free(code_error), NULL);
	free(code_error);
	pipex->code_err = 0;
	return (dst);
}

char	*handle_strange(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '?' && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9'))
			return (str + i);
		i++;
	}
	return (NULL);
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
