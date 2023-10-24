/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:49:07 by elcesped          #+#    #+#             */
/*   Updated: 2023/10/24 19:29:40 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlensep(char *str, char charset);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_buffer(int fd);
char	*ft_switch(char *result, char *buffer);
char	*ft_stocktemp(char *tostock);
char	*ft_maketempb(char *tostock, int fd);
char	*ft_strchr(const char *s, int c);
size_t	ft_lenght(char *temp, char *buffer);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

#endif