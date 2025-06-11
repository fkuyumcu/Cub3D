/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:32:08 by yalp              #+#    #+#             */
/*   Updated: 2025/06/11 11:32:03 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	get_map(t_cube *cube)
{
	int	i;
	int	j;
	int	a;

	a = 0;
	i = 0;
	j = 0;
	while (!is_map_line(cube->all_of_file[i++]))
		j++;
	i = j;
	while (is_map_line(cube->all_of_file[j]))
		j++;
	cube->map = malloc(sizeof(char *) * (j - i + 1));
	if (!cube->map)
		put_error("Memory allocation failed for map", NULL, cube);
	while (j > i)
	{
		cube->map[a++] = ft_strdup(cube->all_of_file[i]);
		i++;
	}
	cube->map[a] = NULL;
}

char	**mapcpy(char **map, t_cube *cube)
{
	int		i;
	char	**cpymap;

	i = 0;
	while (map[i] != NULL)
		i++;
	cpymap = malloc(sizeof(char *) * (i + 1));
	if (!cpymap)
		put_error("Memory allocation failed for cpymap", NULL, cube);
	i = 0;
	while (map[i] != NULL)
	{
		cpymap[i] = ft_strdup(map[i]);
		i++;
	}
	cpymap[i] = NULL;
	return (cpymap);
}

void	flood_fill(char **map, int x, int y, t_cube *cube)
{
	if (map[y][x] == ' ' || map[y][x] == 'X'
		|| map[y][x] == '\n' || map[y][x] == '\0')
		return ;
	if (map[y][x] == '1')
		map[y][x] = 'X';
	else if (map[y][x] == '0' || map[y][x] == cube->player_pov)
	{
		if ((map[y + 1] && map[y + 1][x] == ' ') ||
			(map[y - 1] && map[y - 1][x] == ' ') ||
			(map[y][x + 1] == ' ') ||
			(map[y][x - 1] == ' '))
			put_error("invalid map", NULL, cube);
		map[y][x] = 'X';
	}
	else
		return ;
	if (map[y + 1] && map[y + 1][x])
		flood_fill(map, x, y + 1, cube);
	if (map[y - 1] && map[y - 1][x])
		flood_fill(map, x, y - 1, cube);
	if (map[y][x + 1])
		flood_fill(map, x + 1, y, cube);
	if (map[y][x - 1])
		flood_fill(map, x - 1, y, cube);
}

void	ffill(char **map, int x, int y, t_cube *cube)
{
	if (map[y][x] == 'X' || map[y][x] == ' ')
		return ;
	if (map[y][x] == '0' || map[y][x] == cube->player_pov || map[y][x] == '1')
		map[y][x] = 'X';
	if (map[y + 1] && map[y + 1][x])
		ffill(map, x, y + 1, cube);
	if (map[y - 1] && map[y - 1][x])
		ffill(map, x, y - 1, cube);
	if (map[y][x + 1])
		ffill(map, x + 1, y, cube);
	if (map[y][x - 1])
		ffill(map, x - 1, y, cube);
	if (map[y + 1] && map[y + 1][x + 1])
		ffill(map, x + 1, y + 1, cube);
	if (map[y - 1] && map[y - 1][x - 1])
		ffill(map, x - 1, y - 1, cube);
	if (map[y + 1] && map[y + 1][x - 1])
		ffill(map, x - 1, y + 1, cube);
	if (map[y - 1] && map[y - 1][x + 1])
		ffill(map, x + 1, y - 1, cube);
}

void	check_map(t_cube *cube)
{
	check_map_chars(cube->map, cube);
	cube->cpymap = mapcpy(cube->map, cube);
	manage_map(&cube->cpymap, cube);
	cube->cpy_map = mapcpy(cube->cpymap, cube);
	flood_fill(cube->cpymap, cube->player_x + 1, cube->player_y + 1, cube);
	check_player(cube);
	ffill(cube->cpy_map, cube->player_x + 1, cube->player_y + 1, cube);
	check_double_map(cube->cpy_map, cube);
}
