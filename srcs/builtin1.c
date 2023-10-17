/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:43:12 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/17 18:34:28 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_command(char *str, int choice)
{
	if (choice == 0)
		ft_printf("%s", str);
	else
		ft_printf("%s\n", str);
}

void	cd_utils(char *path)
{
	if (chdir(path) != 0)
	{
		ft_printf("cd : no such file or directory: %s\n", path);
		return ;
	}
}

void	cd_command(char *path)
{
	char	cwd[1024];
	char	*cwd2;
	char	*absolu;

	cwd2 = NULL;
	if (path[0] == '\\')
		cd_utils(path);
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
		ft_printf("cd : no such file or directory: %s\n", path);
		free(cwd2);
		free(absolu);
		return ;
	}
	free(cwd2);
	free(absolu);
}

void	pwd_command(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("getcwd");
}

void	export_command(t_pipex *pipex, char *str)
{
	char	**new_envp;
	int		envp_count;
	int		i;

	envp_count = 0;
	while (pipex->envp[envp_count] != NULL)
		envp_count++;
	new_envp = malloc(sizeof(char *) * (envp_count + 2));
	if (!new_envp)
		return ;
	i = 0;
	while (i < envp_count)
	{
		new_envp[i] = pipex->envp[i];
		i++;
	}
	new_envp[envp_count] = str;
	new_envp[envp_count + 1] = NULL;
	if (pipex->envp2 != NULL)
		free_map(pipex->envp2);
	pipex->envp2 = new_envp;
	pipex->envp = pipex->envp2;
}
