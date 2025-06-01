/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:30:25 by yalp              #+#    #+#             */
/*   Updated: 2025/06/01 14:52:15 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(int fd, char *s)
{
	int	i;

	i = 0;
	if (s[i] != '\0')
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

char *ft_strdup(const char *s1)
{
	size_t  len;
	char    *copy;

	if (!s1)
		return (NULL);
	len = strlen(s1);
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	memcpy(copy, s1, len);
	copy[len] = '\0';
	return (copy);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 1;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = -1;
		i++;
	}
	while ((str[i] <= 57 && str[i] >= 48))
	{
		j = j * 10 + (str[i] - 48);
		i++;
	}
	return (k * j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		a;
	size_t		slen;
	char		*str;

	slen = strlen(s);
	a = 0;
	if (len > slen - start)
		len = slen - start;
	if (start >= slen)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (a < len)
	{
		str[a] = s[start + a];
		a++;
	}
	str[a] = '\0';
	return (str);
}

static int	cw(char const *str, char c)
{
	int	count;

	count = 0;
	if (!*str)
		return (0);
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			count++;
		while (*str != c && *str)
			str++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char		**words;
	long		wordlen;
	int			i;

	i = 0;
	words = (char **)malloc((cw(s, c) + 1) * sizeof(char *));
	if (!words || !s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!strchr(s, c))
				wordlen = strlen(s);
			else
				wordlen = strchr(s, c) - s;
			words[i++] = ft_substr(s, 0, wordlen);
			s += wordlen;
		}
	}
	words[i] = NULL;
	return (words);
}