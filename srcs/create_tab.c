/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:42:31 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/08 16:39:32 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_tab(char *str, t_pipex *pipex, int count)
{
	if (signal(SIGINT, &ft_interrupt) == 0)
	{
		pipex->code_err = 255;
		return ;
	}
	count_nb_tab(str, &count);
	if (count == 0)
		return ;
	pipex->tab = ft_calloc(sizeof(char *), (count + 1));
	if (!pipex->tab)
		return ;
	extract_to_tab(pipex->tab, str, count);
	if (!pipex->tab)
		return ;
	if (check_quotes(pipex->tab, pipex, count) != 0)
		return ;
	pipex->token = ft_calloc(sizeof(int), count);
	if (!pipex->token)
		return (free_map(pipex->tab));
	sort_token(pipex->tab, pipex->token, 0, pipex->quote);
	if (check_random(pipex, count) != 0)
		return (free(pipex->quote), free_memory(pipex));
	if (pipex->is_dollars == 1)
		manage_dollars(pipex);
	free(pipex->quote);
	clear_files(pipex);
	if (handle_builtin(pipex, str) == 0)
		main_pipex(str, pipex);
}

void	count_nb_tab(char *str, int *count)
{
	int	i;

	i = 0;
	(*count) = 0;
	while (str[i] && i <= stop_str(str))
	{
		while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
			i++;
		if (is_metacaractere(str[i]) == 1)
		{
			(*count)++;
			while (is_metacaractere(str[i]) == 1 && str[i])
			{
				if (str[i] == '|' && str[i + 1] != '\0'
					&& (str[i + 1] == '>' || str[i + 1] == '<'))
					(*count)++;
				i++;
			}
		}
		else if (is_metacaractere(str[i]) == 0)
		{
			(*count)++;
			while (is_metacaractere(str[i]) == 0 && str[i])
				i++;
		}
	}
}

void	extract_to_tab(char **tab, char *str, int count)
{
	int		i;
	int		j;
	int		l;
	char	*line;

	i = 0;
	l = 0;
	while (str[i] && l < count)
	{
		extract_to_tab2(str, &i, &j);
		line = cpy(str, i, j);
		tab[l] = ft_strdup(line);
		if (!tab[l])
		{
			while (l >= 0)
				free(tab[l--]);
			free(tab);
			return ;
		}
		free(line);
		l++;
		i = j;
	}
	tab[l] = 0;
}

void	extract_to_tab2(char *str, int *i, int *j)
{
	while ((str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13)) && str[*i])
		(*i)++;
	*j = *i;
	if (is_metacaractere(str[*i]) == 1)
	{
		while (is_metacaractere(str[*j]) == 1 && str[*j])
			(*j)++;
	}
	else if (is_metacaractere(str[*i]) == 0)
	{
		while (is_metacaractere(str[*j]) == 0 && str[*j])
			(*j)++;
	}
}

void	clear_files(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->tab[i])
	{
		if (is_negatif(pipex->tab[i]) == 0 && (pipex->token[i] == IN_FILES
				|| pipex->token[i] == OUT_FILES || pipex->token[i] == HERE_DOC))
			negatif_to_positif(pipex->tab[i]);
		i++;
	}
}
