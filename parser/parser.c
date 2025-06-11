/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:58:58 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/11 15:52:03 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_cube(t_cube *cube)
{
	cube->map = NULL;
	cube->cpymap = NULL;
	cube->cpy_map = NULL;
	cube->texture_n = NULL;
	cube->texture_s = NULL;
	cube->texture_e = NULL;
	cube->texture_w = NULL;
	cube->color_f = NULL;
	cube->color_c = NULL;
	cube->all_of_file = NULL;
	cube->mlx = NULL;
	cube->win = NULL;
	cube->values_c = NULL;
	cube->values_f = NULL;
	cube->player_pov = 0;
	cube->width = 0;
	cube->height = 0;
	cube->count_n = 0;
	cube->count_s = 0;
	cube->count_e = 0;
	cube->count_w = 0;
	cube->count_f = 0;
	cube->count_c = 0;
}

int	ft_isdigit(int c)
{
	if (c <= 57 && c >= 48)
		return (1);
	else
		return (0);
}

void	check_rgb_values(char **rgb, t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (rgb[i][j])
		{
			if (ft_atoi(rgb[i]) == 0 && ft_strlen(rgb[i]) != 1)
			{
				free_double_pointer(rgb);
				put_error("Invalid rgb", NULL, cube);
			}
			if (ft_isdigit(rgb[i][j]) == 0)
			{
				free_double_pointer(rgb);
				put_error("Invalid rgb", NULL, cube);
			}
			j++;
		}
		i++;
	}
}

void	check_rgb(char **rgb, char *line, t_cube *cube)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i++] == ',')
			count++;
	}
	if (count > 2)
	{
		free_double_pointer(rgb);
		put_error("Invalid rgb", NULL, cube);
	}
}

int	is_valid_rgb(char *line, t_cube *cube)
{
	char	**rgb;
	int		i;

	i = 0;
	rgb = ft_split(skip_spaces(trim_spaces(line) + 1), ',');
	if (!rgb)
	return (0);
	while (rgb[i])
		i++;
	if (i != 3)
	{
		free_double_pointer(rgb);
		return (0);
	}
	check_rgb(rgb, line, cube);
	check_rgb_values(rgb, cube);
	if (!check_len(rgb))
		return (0);
	if (!check_range(rgb))
	{
		free_double_pointer(rgb);
		return (0);
	}
	free_double_pointer(rgb);
	return (1);
}

int	is_map_line(char *line)
{
	if (!line || line == NULL)
		return (0);
	line = skip_spaces(line);
	return (*line == '1' || *line == '0');
}

void	check_player(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	cube->player_count = 0;
	while (cube->map[i])
	{
		j = 0;
		while (cube->map[i][j])
		{
			if (cube->map[i][j] == 'N' || cube->map[i][j] == 'S' ||
				cube->map[i][j] == 'E' || cube->map[i][j] == 'W')
			{
				cube->player_pov = cube->map[i][j];
				cube->player_x = j;
				cube->player_y = i;
				cube->player_count++;
			}
			j++;
		}
		i++;
	}
	if (cube->player_count != 1)
		put_error("There must be exactly one player in the map", NULL, cube);
}

int	parser(int argc, char **argv, t_cube *cube)
{
	init_cube(cube);
	arg_check(argc, argv);
	read_file(cube, argv[1]);
	check_file(cube);
	get_map(cube);
	check_map(cube);
	return (0);
}
