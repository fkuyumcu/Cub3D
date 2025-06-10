/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:40:34 by yalp              #+#    #+#             */
/*   Updated: 2025/06/10 15:42:00 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	check_range(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
		{
			free_double_pointer(rgb);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_len(char **rgb)
{
	if (ft_strlen(rgb[0]) > 3 || ft_strlen(rgb[1]) > 3 || ft_strlen(rgb[2]) > 3)
	{
		free_double_pointer(rgb);
		return (0);
	}
	return (1);
}

void	check_double_map(char **map, t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr("01NSEW", map[i][j]) != 0)
				put_error("invalid map", NULL, cube);
			j++;
		}
		i++;
	}
}

void	check_map_chars(char **map, t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr("01NSEW\n ", map[i][j]) == 0)
				put_error("Invalid character in map", map[i], cube);
			j++;
		}
		i++;
	}
}
