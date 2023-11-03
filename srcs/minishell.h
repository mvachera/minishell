/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:55:16 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/03 20:45:04 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		here_doc;
	char	**cmd_paths;
	char	**cmd_args;
	char	**envp;
	char	*limiteur;
	char	*file_here_doc;
	int		cmd_count;
	int		pipefd[2];
	int		pid[1024];
	int		prev;
	int		fd;

	char	**tab;
	int		*token;
	char	**files;
	int		*type;
	int		*quote;
	int		is_dollars;
	int		is_quotes;
	int		code_err;
}			t_pipex;

enum		e_token
{
	PIPE,
	CHEVRON_G,
	CHEVRON_D,
	D_CHEVRON_G,
	D_CHEVRON_D,
	IN_FILES,
	OUT_FILES,
	HERE_DOC,
	BUILTIN,
	COMMAND,
	ARGUMENT,
	RANDOM,
	SINGLE_QUOTE,
	DOUBLE_QUOTES,
	NO_QUOTE,
	EMPTY,
};

int			main_pipex(char *str, t_pipex *pipex);
int			ft_exec(t_pipex *pipex);
void		child_process(t_pipex *pipex, int index);
char		*get_cmd(char **tab2, t_pipex *pipex);
void		execute(t_pipex *pipex, char *command, char **tab);
char		**find_path(char **envp);
void		ft_here_doc(t_pipex *pipex);
char		*str_johnny(char *s1, char *s2);
int			ft_count(char const *s, char c);
int			nb_cmd(t_pipex *pipex);

void		echo_command(char **arg, int choice, int nb_arg);
void		cd_utils(char *path);
void		cd_command(t_pipex *pipex, char *path);
void		pwd_command(void);
void		export_command(t_pipex *pipex, char *str);
void		unset_command(char *var, t_pipex *pipex);
int			check_unset(char *var, t_pipex *pipex, int len_var);
void		env_command(t_pipex *pipex);
void		execute_builtin(char *str, t_pipex *pipex, int to_free, int index);
void		execute_builtin2(char *str, t_pipex *pipex, char **arg, int nb_arg);
char		**get_arg(char *str, t_pipex *pipex, int nb_arg, int index);
void		get_arg2(t_pipex *pipex, int *i, int *nb_arg, char **all_arg);
int			count_arg(t_pipex *pipex, char *str, int index);
int			handle_builtin(t_pipex *pipex, char *str);
int			handle_builtin2(t_pipex *pipex, int i);
int			is_builtin(t_pipex *pipex);
void		handle_exit(t_pipex *pipex, int i);

int			start_main(int ac, t_pipex *pipex, char **envp);
int			nb_quotes(char *str);
char		*tonegatif(t_pipex *pipex, char *str);
void		ft_react_to_signal(int sig);
void		ft_interrupt(int sig);
void		create_tab(char *str, t_pipex *pipex, int count);
void		count_nb_tab(char *str, int *count);
void		extract_to_tab(char **tab, char *str, int count);
void		extract_to_tab2(char *str, int *i, int *j);
void		letters_arg(char *str, int *j);
int			stop_str(char *str);
int			check_quotes(char **tab, t_pipex *pipex, int count);
int			find_quotes(char *str);
void		handle_quotes(char *str);
char		*handle_quotes2(char *str);
int			check_random(t_pipex *pipex, int count);
int			check_first_str(char *str);
int			is_meta_string(char *str);
int			is_metacaractere(char c);
char		*cpy(char *str, int i, int j);
void		sort_token(char **tab, int *token, int i, int *quote);
void		sort_token2(char **tab, int *token, int i);
int			check_builtin(char *str);
void		free_memory(t_pipex *pipex);
void		free_pipex(t_pipex *pipex);
void		free_files(t_pipex *pipex);
void		free_exit(t_pipex *pipex);
char		**cpy_envp(char **envp);
int			ft_strcmp(char *s1, char *s2);
void		free_map(char **map_a_parser);
char		**get_all_cmd(t_pipex *pipex);
void		get_all_cmd2(t_pipex *pipex, int *i, char **all_cmd);
int			check_arg(char *str, t_pipex *pipex);
char		*manage_arg(char *str, t_pipex *pipex);
int			get_len(char *str, t_pipex *pipex);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
void		parcours_cmd(t_pipex *pipex);
void		parcours_cmd2(t_pipex *pipex);
void		openfiles(t_pipex *pipex, int i);
void		openfiles2(t_pipex *pipex, int i);
void		mallocfichiers(t_pipex *pipex);
void		check_here_doc(t_pipex *pipex);
void		manage_dollars(t_pipex *pipex);
char		*manage_dollars2(t_pipex *pipex, int i);
void		manage_dollars3(t_pipex *pipex, char *tmp, char *tmp_before, int i);
char		*new_var(t_pipex *pipex, char *var);
void		new_tab(t_pipex *pipex, char **dst_tab, char **all_var);
char		*handle_array_dollar(char **dst_tab, int d);
int			get_nb_var(t_pipex *pipex, char **all_var, int d);
int			is_dollars(char *str);
char		*handle_interrogation(t_pipex *pipex, char *str);
int			last_command(t_pipex *pipex, char *str);
int			is_interrogation(char *str);
void		print_error_syntax(char c, char d, int i);
int			ft_handle_size(char *tab);
int			ft_strlen2(char *str);

#endif
