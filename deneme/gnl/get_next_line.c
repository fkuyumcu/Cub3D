/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:54 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/10 16:41:10 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	del(char **data)
{
	free(*data);
	*data = NULL;
}

int	content_buf(int fd, char **content, char *buffer)
{
	ssize_t	bytes;
	char	*temp;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
	{
		del(content);
		return (-1);
	}
	if (bytes == 0)
		return (0);
	buffer[bytes] = '\0';
	temp = ft_strjoin(*content, buffer);
	free(*content);
	*content = temp;
	return (1);
}

void	content_nl(char *content, char **next_line)
{
	size_t	len;
	char	*start;

	start = findnewline(content);
	len = (ft_strlen(content) - ft_strlen(start) + 2);
	*next_line = malloc(len * sizeof(char));
	if (!*next_line)
		return ;
	ft_strlcpy(*next_line, content, len);
}

void	lineclear(char **content)
{
	char	*start;
	char	*temp;

	start = findnewline(*content);
	if (!start)
	{
		del(content);
		return ;
	}
	temp = malloc(ft_strlen(start) * sizeof(char));
	if (!temp)
	{
		del(content);
		return ;
	}
	ft_strlcpy(temp,
		(*content) + ft_strlen(*content) - ft_strlen(start) + 1,
		ft_strlen(start));
	free(*content);
	*content = temp;
	if (!**content)
		del(content);
}

char	*get_next_line(int fd)
{
	static char		*content;
	char			*next_line;
	char			*buffer;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	status = 1;
	while (!findnewline(content) && status > 0)
		status = content_buf(fd, &content, buffer);
	free(buffer);
	if (!content || status == -1)
		return (NULL);
	content_nl(content, &next_line);
	lineclear(&content);
	return (next_line);
}
