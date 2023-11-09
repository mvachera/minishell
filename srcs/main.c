/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:54:57 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/09 18:25:53 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	static t_pipex	pipex = {0};
	char			*str;

	(void)av;
	if (start_main(ac, &pipex, envp) == 2)
		return (2);
	while (1)
	{
		if (capt_sign() == -1)
			return (-1);
		str = readline("> ");
		if (!str)
			break ;
		if (str)
			add_history(str);
		if (!*str)
			continue ;
		if (nb_quotes(str) == 0)
		{
			str = tonegatif(&pipex, str);
			create_tab(str, &pipex);
		}
	}
	free_map(pipex.envp);
}
