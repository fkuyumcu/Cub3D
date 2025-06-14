/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_supply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:50:39 by yalp              #+#    #+#             */
/*   Updated: 2025/06/14 16:03:41 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	find_map_start(t_cube *cube)
{
	int	i;

	i = 0;
	while (cube->all_of_file[i])
	{
		if (is_empty_line(cube->all_of_file[i]))
		{
			i++;
			continue ;
		}
		if (check_all_identifiers_collected(cube))
			break ;
		if (is_ident_line(cube->all_of_file[i]))
			i++;
		else
			break ;
	}
	if (!check_all_identifiers_collected(cube))
		put_error("All identifiers must be collected before map", NULL, cube);
	while (cube->all_of_file[i] && (is_empty_line(cube->all_of_file[i])
			|| is_ident_line(cube->all_of_file[i])))
		i++;
	if (cube->all_of_file[i] == NULL)
		put_error("map can not found", NULL, cube);
	return (i);
}

void	copy_map_lines(t_cube *cube, int start, int end)
{
	int	a;
	int	i;

	a = 0;
	i = start;
	while (i < end)
	{
		cube->map[a++] = ft_strdup(cube->all_of_file[i]);
		i++;
	}
	cube->map[a] = NULL;
}

void	flood_fill_supply(char **map, int x, int y, t_cube *cube)
{
	map[y][x] = 'X';
	if (map[y + 1] && map[y + 1][x + 1])
		flood_fill(map, x + 1, y + 1, cube);
	if (map[y - 1] && map[y - 1][x - 1])
		flood_fill(map, x - 1, y - 1, cube);
	if (map[y + 1] && map[y + 1][x - 1])
		flood_fill(map, x - 1, y + 1, cube);
	if (map[y - 1] && map[y - 1][x + 1])
		flood_fill(map, x + 1, y - 1, cube);
}
