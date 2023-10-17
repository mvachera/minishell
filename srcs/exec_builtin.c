/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:00:11 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/17 17:35:21 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	execute_builtin(char *str, t_pipex *pipex)
// {
// 	char	**arg;

// 	arg = get_arg(str, pipex);
// 	//printf("%s\n", str);
// 	if (ft_strcmp(str, "echo") == 0)
// 		echo_command(arg, 1);
// 	else if (ft_strcmp(arg, "echo -n") == 0)
// 		echo_command(str, 0);
// 	else if (ft_strcmp(str, "cd") == 0)
// 		cd_command(arg);
// 	else if (ft_strcmp(str, "pwd") == 0)
// 		pwd_command();
// 	else if (ft_strcmp(str, "export") == 0)
// 		export_command(pipex, arg);
// 	else if (ft_strcmp(str, "unset") == 0)
// 		unset_command(arg, pipex);
// 	else if (ft_strcmp(str, "env") == 0)
// 		env_command(pipex);
// 	if (arg != NULL)
// 		free_map(arg);
// 	free_pipex(pipex);
// 	exit(0);
// }

// char	**get_arg(char *str, t_pipex *pipex)
// {
// 	char	**all_arg;
// 	int		i;
// 	int		nb_arg;

// 	i = 0;
// 	nb_arg = count_arg(pipex, str);
// 	if (nb_arg == 0)
// 		return (NULL);
// 	all_arg = malloc(sizeof(char *) * (nb_arg + 1));
// 	if (!all_arg)
// 		return (NULL);
// 	nb_arg = 0;
// 	while (pipex->tab[i])
// 	{
// 		if (ft_strcmp(str, pipex->tab[i]) == 0)
// 		{
// 			i++;
// 			while (pipex->token[i] == ARGUMENT)
// 			{
// 				all_arg[nb_arg] = ft_strdup(pipex->tab[i]);
// 				if (!all_arg)
// 				{
// 					while (nb_arg >= 0)
// 						free(all_arg[nb_arg--]);
// 					return (free(all_arg), NULL);
// 				}
// 				nb_arg++;
// 				i++;
// 			}
// 			break ;
// 		}
// 		i++;
// 	}
// 	all_arg[nb_arg] = 0;
// 	return (all_arg);
// }

// int	count_arg(t_pipex *pipex, char *str)
// {
// 	int	nb;
// 	int	i;

// 	nb = 0;
// 	i = 0;
// 	while (pipex->tab[i])
// 	{
// 		if (ft_strcmp(str, pipex->tab[i]) == 0)
// 		{
// 			if (pipex->token[i + 1] != ARGUMENT)
// 				return (0);
// 			else
// 			{
// 				i++;
// 				while (pipex->token[i] == ARGUMENT)
// 				{
// 					nb++;
// 					i++;
// 				}
// 				break ;
// 			}
// 		}
// 		i++;
// 	}
// 	return (nb);
// }

// void	check_exit(t_pipex *pipex)
// {
// 	int	i;

// 	i = 0;
// 	while (pipex->tab[i])
// 	{
// 		if (ft_strcmp(pipex->tab[i], "exit") == 0 && pipex->token[i] == COMMAND)
// 			exit_command(pipex);
// 		i++;
// 	}
// }
