/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:55:16 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/17 17:46:28 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf/ft_printf.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*in_name;
	char	*out_name;
	int		here_doc;
	char	*str_end;
	int		is_invalid_infile;
	char	**cmd_paths;
	char	**cmd_args;
	char	**envp;
	char	**envp2;
	char	*limiteur;
	int		cmd_count;
	int		pipefd[2];
	int		pid[1024];
	int		prev;
	int		fd;

	char	**tab;
	int		*token;
}			t_pipex;

enum		e_token
{
	PIPE,
	CHEVRON_G,
	CHEVRON_D,
	D_CHEVRON_G,
	D_CHEVRON_D,
	FILES,
	HERE_DOC,
	BUILTIN,
	COMMAND,
	ARGUMENT,
	RANDOM,
};

int			main_pipex(char *str, t_pipex *pipex, char **envp);
int			ft_exec(t_pipex *pipex);
void		child_process(t_pipex *pipex, int index);
char		*get_cmd(char **tab2, t_pipex *pipex);
void		execute(t_pipex *pipex, char *command, char **tab);
void		ft_init_pipex(t_pipex *pipex);
char		**find_path(char **envp);
void		je_souffre(t_pipex *pipex, int index);
void		je_souffre_trop(t_pipex *pipex);
void		ft_here_doc(t_pipex *pipex);
char		*str_johnny(char *s1, char *s2);
int			ft_count(char const *s, char c);
int			nb_cmd(t_pipex *pipex);

void		echo_command(char *str, int choice);
void		cd_utils(char *path);
void		cd_command(char *path);
void		pwd_command(void);
void		export_command(t_pipex *pipex, char *str);
void		unset_command(char *var, t_pipex *pipex);
void		env_command(t_pipex *pipex);
void		exit_command(t_pipex *pipex);
// void		execute_builtin(char *str, t_pipex *pipex);
// char		*get_arg(char *str, t_pipex *pipex);
// void		check_exit(t_pipex *pipex);

char		*tonegatif(char *str);
void		ft_react_to_signal(int sig);
int			create_tab(char *str, t_pipex *pipex, char **envp);
void		count_nb_tab(char *str, int *count);
void		extract_to_tab(char **tab, char *str, int count);
void		extract_to_tab2(char *str, int *i, int *j);
void		letters_arg(char *str, int *j);
int			stop_str(char *str);
int			check_tab(char **tab, int count);
void		handle_quotes(char *str);
char		*handle_quotes2(char *str);
int			check_first_str(char *str);
int			is_metacaractere(char c);
char		*cpy(char *str, int i, int j);
void		sort_token(char **tab, int *token, int i);
void		sort_token2(char **tab, int *token, int i);
int			check_builtin(char *str);
void		free_memory(t_pipex *pipex);
void		free_pipex(t_pipex *pipex);
int			ft_strcmp(char *s1, char *s2);
void		free_map(char **map_a_parser);
char		**get_all_cmd(t_pipex *pipex);
void		get_all_cmd2(t_pipex *pipex, int *i, char **all_cmd);
void		parcours_cmd(t_pipex *pipex);
void		parcours_cmd2(t_pipex *pipex, int c, int i);

void		test_print(t_pipex *pipex);

#endif
