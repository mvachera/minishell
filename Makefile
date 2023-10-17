# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 07:38:17 by mvachera          #+#    #+#              #
#    Updated: 2023/10/17 17:59:45 by mvachera         ###   ########.fr        #
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

SRC     = srcs/main.c srcs/builtin1.c srcs/builtin2.c srcs/create_tab.c srcs/exec_builtin.c srcs/handle_error.c srcs/handle_quote.c srcs/parcours_command.c srcs/pipex.c srcs/pipex_utils1.c srcs/pipex_utils2.c srcs/tab_utils.c srcs/token.c gnl/get_next_line.c gnl/get_next_line_utils.c

OBJ     = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
		${MAKE} -C ${LIBFT}
		${MAKE} -C ${PRINTF}
		${CC} ${OBJ} -o ${NAME} ${FT_LIBFT} -lreadline ${FT_PRINTF}

clean :
	${RM} ${OBJ} ${OBJ_BONUS}

fclean : clean
	${RM} ${NAME} ${BONUS}

re : fclean all

.PHONY : all clean fclean re
