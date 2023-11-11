/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:28:55 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/11 20:29:56 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_var(t_pipex *pipex, char *var)
{
	int		i;
	int		d;
	char	**dst_tab;
	char	*dst;
	char	**all_var;

	d = 0;
	if (var[ft_strlen(var) - 1] == '$')
		d = 1;
	all_var = ft_split(var, '$');
	if (!all_var)
		return (NULL);
	i = get_nb_var(pipex, all_var, d);
	if (i == 0)
		return (free_map(all_var), NULL);
	dst_tab = ft_calloc(sizeof(char *), i + 1);
	if (!dst_tab)
		return (free_map(all_var), NULL);
	new_tab(pipex, dst_tab, all_var);
	free_map(all_var);
	dst = handle_array_dollar(dst_tab, d);
	if (!dst)
		return (free_map(dst_tab), NULL);
	free_map(dst_tab);
	return (dst);
}

void	new_tab(t_pipex *pipex, char **dst_tab, char **all_var)
{
	int		i;
	int		j;
	int		k;
	int		len_var;

	i = 0;
	k = 0;
	while (all_var[i])
	{
		j = 0;
		len_var = ft_strlen3(all_var[i]);
		if (strange_char(all_var[i]) == 2)
			dst_tab[k++] = handle_interrogation(pipex, all_var[i]);
		else if (strange_char(all_var[i]) == 1)
			dst_tab[k++] = handle_strange(pipex, all_var[i]);
		else
		{
			while (pipex->envp[j])
			{
				if (ft_strncmp(pipex->envp[j], all_var[i], len_var) == 0
					&& pipex->envp[j][len_var] == '=')
						dst_tab[k++] = ft_strdup(pipex->envp[j] + len_var + 1);
				j++;
			}
		}
		i++;
	}
}

char	*handle_array_dollar(char **dst_tab, int d)
{
	char	*dst;
	int		i[3];

	i[2] = 0;
	i[0] = 0;
	while (dst_tab[i[0]])
	{
		i[2] += ft_strlen(dst_tab[i[0]]);
		i[0]++;
	}
	dst = ft_calloc(sizeof(char), i[2] + 2);
	if (!dst)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (dst_tab[i[0]])
	{
		i[2] = 0;
		while (dst_tab[i[0]][i[2]])
		{
			if (dst_tab[i[0]][i[2]] == '\\')
				i[2]++;
			if (!dst_tab[i[0]][i[2]])
				break ;
			dst[i[1]++] = dst_tab[i[0]][i[2]++];
		}
		i[0]++;
	}
	if (d == 1)
		dst[i[1]] = '$';
	return (dst);
}

int	get_nb_var(t_pipex *pipex, char **s, int d)
{
	int	i[4];

	i[0] = 0;
	i[2] = 0;
	if (d == 1)
		i[2]++;
	while (s[i[0]])
	{
		i[3] = ft_strlen2(s[i[0]]);
		i[1] = 0;
		if (strange_char(s[i[0]]) != 0)
			i[2]++;
		else
		{
			while (pipex->envp[i[1]])
			{
				if (ft_strncmp(pipex->envp[i[1]], s[i[0]], i[3]) == 0
					&& pipex->envp[i[1]][i[3]] == '=')
					i[2]++;
				i[1]++;
			}
		}
		i[0]++;
	}
	return (i[2]);
}

int	is_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
