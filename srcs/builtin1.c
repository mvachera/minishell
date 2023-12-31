/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:43:12 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/22 15:12:13 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_command(char **arg, int choice, int nb_arg)
{
	int	i;

	i = 0;
	if (nb_arg == 0)
	{
		if (choice == 1)
			write(1, "\n", 1);
		return ;
	}
	while (arg[i] && echo_first_arg(arg[i]) == 1)
		i++;
	while (i < nb_arg - 1)
	{
		write(1, arg[i], ft_strlen(arg[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, arg[i], ft_strlen(arg[i]));
	if (choice == 1)
		write(1, "\n", 1);
}

int	echo_first_arg(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || !arg[1])
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	cd_command(t_pipex *pipex, char *path)
{
	char	cwd[1024];
	char	*cwd2;
	char	*absolu;

	if (path[0] == '/')
		return (cd_command2(pipex, path));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("getcwd"));
	cwd2 = ft_strdup(cwd);
	if (!cwd2)
		return ;
	absolu = ft_strjoin(cwd2, path);
	if (!absolu)
		return (free(cwd2));
	if (chdir(absolu) != 0)
	{
		pipex->code_err = 1;
		ft_printf("cd : %s\n", strerror(errno));
	}
	free(cwd2);
	free(absolu);
}

void	pwd_command(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd");
}

void	export_command(t_pipex *pipex, char *str)
{
	char	**new_envp;
	int		env_count;
	int		len_var;
	int		i;

	if (export_utils(str) == 1)
	{
		pipex->code_err = 1;
		ft_printf("%s : not a valid identifier\n", str);
		return ;
	}
	env_count = 0;
	while (pipex->envp[env_count] != NULL)
		env_count++;
	new_envp = ft_calloc(sizeof(char *), (env_count + 2));
	if (!new_envp)
		return ;
	i = 0;
	len_var = ft_strlen4(str);
	export_command2(pipex, new_envp, str, len_var);
	free_map(pipex->envp);
	pipex->envp = new_envp;
	pipex->code_err = 0;
}
