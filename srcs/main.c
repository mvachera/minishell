/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:54:57 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/10 19:03:38 by mvachera         ###   ########.fr       */
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
			printf("exit\n");
		if (!str)
			break ;
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
