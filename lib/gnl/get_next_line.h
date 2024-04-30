/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:32:12 by muhnal            #+#    #+#             */
/*   Updated: 2023/01/24 15:57:33 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

//malloc
# include <stdlib.h>

//read, free
# include <unistd.h>

char	*str_join_free(char *prefix, char *suffix);
char	*remove_extractedline(char *buffer);
char	*extract_nextline(char *buffer);
char	*read_thefile(int fd, char *res);
char	*get_next_line(int fd);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *string, int searched );
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);

#endif
