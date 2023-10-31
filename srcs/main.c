/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:54:57 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/31 19:51:00 by mvachera         ###   ########.fr       */
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
		if (signal(SIGINT, &ft_react_to_signal) == SIG_ERR)
			return (-1);
		else if (signal(SIGINT, &ft_react_to_signal) == 0)
			return (pipex.code_err = 130, 130);
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
			create_tab(str, &pipex, 0);
		}
	}
	free_map(pipex.envp);
}
