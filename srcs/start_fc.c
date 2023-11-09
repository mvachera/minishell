/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:20:53 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/09 18:24:45 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_envp(char **envp)
{
	char	**dst;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	dst = ft_calloc(sizeof(char *), i + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		dst[i] = ft_strdup(envp[i]);
		i++;
	}
	return (dst);
}

int	nb_quotes(char *str)
{
	int		i;
	char	tmp;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp = str[i++];
			count++;
			while (str[i] && str[i] != tmp)
				i++;
			if (!str[i])
				return (ft_printf("syntax error, unclosed quotes\n"), 1);
		}
		count--;
		i++;
	}
	if (count % 2 == 1)
		return (ft_printf("syntax error, unclosed quotes\n"), 1);
	return (0);
}

char	*tonegatif(t_pipex *pipex, char *str)
{
	char	c;
	int		i;

	i = 0;
	if (is_dollars(str) == 1)
		pipex->is_dollars = 1;
	if (find_quotes(str) != 0)
		pipex->is_quotes = 1;
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
				str[i] = -str[i];
				i++;
			}
		}
		i++;
	}
	return (str);
}

int	start_main(int ac, t_pipex *pipex, char **envp)
{
	if (ac != 1)
		return (2);
	pipex->envp = cpy_envp(envp);
	if (!pipex->envp)
		return (2);
	return (0);
}

int	capt_sign(void)
{
	if (signal(SIGINT, &ft_react_to_signal) == SIG_ERR)
		return (-1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (-1);
	return (0);
}
