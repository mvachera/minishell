# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 07:38:17 by mvachera          #+#    #+#              #
#    Updated: 2023/11/26 17:23:09 by mvachera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell

CC      = clang

CFLAGS  = -Wall -Wextra -Werror -g3

RM      = rm -f

LIBFT          = libft

FT_LIBFT        = libft/libft.a

PRINTF          = ft_printf

FT_PRINTF       = ft_printf/libftprintf.a

SRC     = srcs/main.c srcs/builtin1.c srcs/builtin2.c srcs/create_tab.c srcs/exec_builtin.c srcs/free_functions.c srcs/handle_quote.c srcs/parcours_command.c srcs/pipex.c srcs/pipex_utils.c srcs/tab_utils.c srcs/token.c srcs/manage_one_builtin.c srcs/manage_files.c srcs/manage_arg.c srcs/error_msg.c srcs/dollars.c srcs/dollars_utils.c srcs/signal.c srcs/start_fc.c srcs/strange_caracteres.c srcs/files_one_builtin.c srcs/positif_negatif.c srcs/pipex_utils2.c srcs/get_len.c srcs/here_doc.c srcs/find_char.c srcs/exec_builtin_utils.c srcs/parcours_command_utils.c srcs/builtin3.c

OBJ     = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
		${MAKE} -C ${LIBFT}
		${MAKE} -C ${PRINTF}
		${CC} ${OBJ} -o ${NAME} ${FT_LIBFT} -lreadline ${FT_PRINTF}

leaks : all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=ignore.txt   ./minishell

clean :
	${RM} ${OBJ} ${OBJ_BONUS}

fclean : clean
	${RM} ${NAME} ${BONUS}

re : fclean all

.PHONY : all clean fclean re
