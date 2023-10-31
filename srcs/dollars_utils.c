/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:28:55 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/31 20:25:16 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_var(t_pipex *pipex, char *var)
{
	int		i;
	char	**dst_tab;
	char	*dst;
	char	**all_var;

	all_var = ft_split(var, '$');
	if (!all_var)
		return (NULL);
	i = get_nb_var(pipex, all_var);
	if (i == 0)
		return (free_map(all_var), NULL);
	dst_tab = ft_calloc(sizeof(char *), i + 1);
	if (!dst_tab)
		return (free_map(all_var), NULL);
	new_tab(pipex, dst_tab, all_var);
	free_map(all_var);
	dst = handle_array_dollar(dst_tab);
	if (!dst)
		return (free_map(dst_tab), NULL);
	free_map(dst_tab);
	return (dst);
}

void	new_tab(t_pipex *pipex, char **dst_tab, char **all_var)
{
	int	i;
	int	j;
	int	k;
	int	len_var;

	i = 0;
	k = 0;
	while (all_var[i])
	{
		j = 0;
		len_var = ft_strlen2(all_var[i]);
		while (pipex->envp[j])
		{
			if (ft_strncmp(pipex->envp[j], all_var[i], len_var) == 0
				&& pipex->envp[j][len_var] == '=')
			{
				dst_tab[k] = ft_strdup(pipex->envp[j] + len_var + 1);
				k++;
			}
			j++;
		}
		i++;
	}
}

char	*handle_array_dollar(char **dst_tab)
{
	char	*dst;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (dst_tab[i])
	{
		len += ft_strlen(dst_tab[i]);
		i++;
	}
	dst = ft_calloc(sizeof(char), len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (dst_tab[i])
	{
		len = 0;
		while (dst_tab[i][len])
			dst[j++] = dst_tab[i][len++];
		i++;
	}
	return (dst);
}

int	get_nb_var(t_pipex *pipex, char **all_var)
{
	int	i;
	int	j;
	int	count;
	int	len_var;

	i = 0;
	count = 0;
	while (all_var[i])
	{
		len_var = ft_strlen2(all_var[i]);
		j = 0;
		while (pipex->envp[j])
		{
			if (ft_strncmp(pipex->envp[j], all_var[i], len_var) == 0
				&& pipex->envp[j][len_var] == '=')
				count++;
			j++;
		}
		i++;
	}
	return (count);
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
