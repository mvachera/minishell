/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:54:57 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/14 22:11:05 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;
	char	*str;

	pipex = starton();
	if (start_main(ac, pipex, av, envp) == 2)
		return (2);
	while (1)
	{
		if (capt_sign() == -1)
			return (-1);
		str = readline("> ");
		if (!str)
			break ;
		if (!*str)
			continue ;
		add_history(str);
		str = vide(str);
		if (nb_quotes(str) == 0)
		{
			str = tonegatif(pipex, str);
			create_tab(str, pipex);
		}
	}
	printf("exit\n");
	free_map(pipex->envp);
}
