/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:25:03 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/10 16:37:13 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*res;

	res = malloc((ft_strlen(s1)+ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && *s1)
	{
		res[i++] = *s1;
		s1++;
	}
	while (s2 && *s2)
	{
		res[i++] = *s2;
		s2++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *) &str[i]);
		i++;
	}
	return (0);
}

char	*findnewline(char *content)
{
	size_t	i;

	i = 0;
	if (!content)
		return (NULL);
	while (content[i])
	{
		if (content[i] == (char) '\n')
			return ((char *) &content[i]);
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	srclen;

	srclen = 0;
	while (src[srclen])
		srclen++;
	if (!destsize)
		return (srclen);
	i = 0;
	while (src[i] && i < destsize -1)
	{
		dest[i] = src[i];
		i++;
	}
	if (destsize)
		dest[i] = '\0';
	return (srclen);
}
