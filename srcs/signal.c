/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:18:33 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/07 19:27:48 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	code_signal(int b)
{
	static int	a;
	int			c;

	a = 0;
	if (b == -1)
	{
		a = 130;
		c = b;
	}
	if (b == 1)
		a = 0;
	return (a);
}

void	ft_react_to_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		code_signal(-1);
		return ;
	}
}

void	ft_interrupt(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_redisplay();
		code_signal(-1);
		return ;
	}
}
