/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:59 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/10 16:31:39 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char	*buf;
	void	*next;

}				t_list;

size_t	ft_strlcpy(char *dest, const char *src, size_t n);
int		readbuf(int fd, char **content, char *buffer);
void	readline(char *content, char **next_line);
void	lineclear(char **content);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, int c);
char	*findnewline(char *content);
size_t	ft_strlen(const char *s);
int		readbuf(int fd, char **content, char *buffer);
void	del(char **data);
char	*get_next_line(int fd);

#endif