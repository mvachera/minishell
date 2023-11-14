/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:55:16 by mvachera          #+#    #+#             */
/*   Updated: 2023/11/14 22:09:19 by mvachera         ###   ########.fr       */
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

typedef struct s_here
{
	int		nbhdocs;
	char	*limit;
	int		fd[2];
}			t_here;

typedef struct s_pipex
{
	char	**cmd_paths;
	char	**cmd_args;
	char	**envp;
	int		cmd_count;
	int		pipefd[2];
	int		pid[1024];
	int		prev;
	int		fd;

	char	**tab;
	int		*token;
	int		*quote;
	int		is_dollars;
	int		code_err;
	int		count;
	int		tmp[2];
	t_here	*hdocs;
	int		nbhdocs;
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

t_pipex		*starton(void);

int			main_pipex(char *str, t_pipex *pipex);
int			ft_exec(t_pipex *pipex);
void		child_process(t_pipex *pipex, int index);
void		child_process2(t_pipex *pipex);
char		*get_cmd(char **tab2, t_pipex *pipex);
void		execute(t_pipex *pipex, char *command, char **tab);
char		**find_path(char **envp);
char		*str_johnny(char *s1, char *s2);
int			ft_count(char const *s, char c);
int			nb_cmd(t_pipex *pipex);

void		echo_command(char **arg, int choice, int nb_arg);
int			echo_first_arg(char *arg);
void		cd_utils(char *path);
void		cd_command(t_pipex *pipex, char *path);
void		cd_command2(t_pipex *pipex, char *path);
void		pwd_command(void);
void		export_command(t_pipex *pipex, char *str);
void		export_command2(t_pipex *pipex, char **new_envp, char *str,
				int len_var);
int			export_utils(char *str);
void		unset_command(char *var, t_pipex *pipex);
int			check_unset(char *var, t_pipex *pipex, int len_var);
void		env_command(t_pipex *pipex);
void		execute_builtin(char *str, t_pipex *pipex, int to_free, int index);
void		execute_builtin2(char *str, t_pipex *pipex, char **arg, int nb_arg);
void		execute_builtin3(char *str, t_pipex *pipex, char **arg, int nb_arg);
char		**get_arg(t_pipex *pipex, int nb_arg, int index);
void		get_arg2(t_pipex *pipex, int *i, int *nb_arg, char **all_arg);
int			count_arg(t_pipex *pipex, char *str, int index);
int			count_arg2(t_pipex *pipex, int i);
int			handle_builtin(t_pipex *pipex, char *str);
int			is_builtin(t_pipex *pipex);
void		handle_exit(t_pipex *pipex, char **arg, int nb_arg, int to_free);
int			is_numeric_string(char *str);

char		*tonegatif(t_pipex *pipex, char *str);
int			start_main(int ac, t_pipex *pipex, char **av, char **envp);
int			capt_sign(void);
int			nb_quotes(char *str);
int			code_signal(int b);
void		ft_react_to_signal(int sig);
void		create_tab(char *str, t_pipex *pipex);
void		create_tab2(t_pipex *pipex, char *str);
void		count_nb_tab(char *str, t_pipex *pipex, int i);
void		extract_to_tab(t_pipex *pipex, char **tab, char *str);
void		extract_to_tab2(char *str, int *i, int *j);
int			stop_str(char *str);
int			check_quotes(char **tab, t_pipex *pipex);
int			find_quotes(char *str);
void		handle_quotes(char *str);
char		*handle_quotes2(char *str);
int			is_negatif(char *str);
void		negatif_to_positif(char *str);
void		positif_to_negatif(char *str);
void		clean_arg(char **tab);
void		clear_all(t_pipex *pipex);
int			check_random(t_pipex *pipex, int i);
int			check_random2(t_pipex *pipex, int i);
int			check_base_directory(t_pipex *pipex);
int			check_token_kind(t_pipex *pipex, int i);
int			check_first_str(char *str);
int			is_meta_string(char *str);
int			is_metacaractere(char c);
char		*cpy(char *str, int i, int j);
void		sort_token(t_pipex *pipex, char **tab, int *token, int *quote);
void		sort_token2(t_pipex *pipex, char **tab, int *token, int i);
int			check_builtin(char *str);
void		free_memory(t_pipex *pipex);
void		free_pipex(t_pipex *pipex);
void		free_files(t_pipex *pipex);
void		free_exit(t_pipex *pipex, char **arg, int nb_arg, int to_free);
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
void		parcours_cmd3(t_pipex *pipex, char *cmd, int i);
void		openfiles(t_pipex *pipex, int index);
void		handle_files(t_pipex *pipex, int i);
void		handle_files2(t_pipex *pipex, int i);
void		manage_dollars(t_pipex *pipex);
char		*manage_dollars2(t_pipex *pipex, int i);
void		manage_dollars3(t_pipex *pipex, char *tmp, char *tmp_before, int i);
char		*new_var(t_pipex *pipex, char *var);
void		new_tab(t_pipex *pipex, char **dst_tab, char **all_var);
char		*handle_array_dollar(char **dst_tab, int d);
void		handle_array_dollar2(char *dst, char **dst_tab, int d);
int			get_nb_var(t_pipex *pipex, char **s, int d);
int			is_dollars(char *str);
char		*handle_interrogation(t_pipex *pipex, char *str);
char		*strange_not_first(t_pipex *pipex, char *str, char *after_str,
				int len);
void		print_error_syntax(char c, char d, int i);
int			ft_handle_size(char *tab);
int			strange_char(char *str);
char		*handle_strange(t_pipex *pipex, char *str);
int			ft_strlen2(char *str);
int			ft_strlen3(char *str);
int			ft_strlen4(char *str);
int			builtin_open_files(t_pipex *pipex);
int			builtin_in_files(t_pipex *pipex);
int			builtin_out_files(t_pipex *pipex);
int			is_slash(char *str);
void		parcours_last_command(t_pipex *pipex);
void		parcours_last_command2(t_pipex *pipex, char *cmd, int i);
int			in_env(t_pipex *pipex, char *str);
char		*vide(char *str);

void		waitfunction(t_pipex *pipex);
void		antislash(int sig);
void		ctrlc(int sig);
void		here_doc(t_pipex *pipex);
void		fork_hdocs(t_pipex *pipex, t_here *hd);
void		remplissage_hdocs(t_here *here, int nbhdocs, t_pipex *pipex);
int			count_hdocs(t_pipex *pipex);
void		close_hdocs(t_here *hd, int size);
int			getpipe(t_here *hd, char *file);

#endif
