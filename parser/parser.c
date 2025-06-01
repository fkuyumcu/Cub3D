/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:58:58 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/01 15:21:34 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void put_error(char *message, t_cube *cube)
{
	ft_putstr_fd(2, "Error: %s\n", message);
	end(cube, 1);
}


void arg_check(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd(2, "Error: Wrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if (argv[1][strlen(argv[1]) - 4] != '.')
	{
		ft_putstr_fd(2, "Error: Invalid file extension\n");
		exit(EXIT_FAILURE);
	}
	if (strcmp(&argv[1][strlen(argv[1]) - 4], ".cub") != 0)
	{
		ft_putstr_fd(2, "Error: Invalid file extension\n");
		exit(EXIT_FAILURE);
	}
	if (open(argv[1], O_RDONLY) < 0)
	{
		ft_putstr_fd(2, "Error: File can not be read\n");
		exit(EXIT_FAILURE);
	}
}

void init_cube(t_cube *cube)
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










int is_valid_rgb(char *line)
{
    char    **rgb;
    int     i;

    i = 0;
    rgb = ft_split(skip_spaces(trim_spaces(line) + 1 ), ',');
    if (!rgb)
        return (0);
    while (rgb[i])
        i++;;
    if (i != 3)
    {
        free_double_pointer(rgb);
        return 0;
    }
	if (ft_strlen_gnl(rgb[0]) > 3 || ft_strlen_gnl(rgb[1]) > 3 || ft_strlen_gnl(rgb[2]) > 3)
	{
		free_double_pointer(rgb);
		return 0;
	}
    i = 0;
    while (rgb[i])
    {
        if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
        {
			free_double_pointer(rgb);
            return 0;
        }
        i++;
    }
	i = 0;
	free_double_pointer(rgb);
    return (1);
}


int is_map_line(char *line)
{
    line = skip_spaces(line);
    return (*line == '1' || *line == '0');
}







void check_player(t_cube *cube)
{
	int i;
	int j;

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
		put_error("Error: There must be exactly one player in the map\n", cube);

}




int parser(int argc, char **argv)
{
    t_cube cube;

    int i = 0;
    init_cube(&cube);
    arg_check(argc, argv);
    read_file(&cube, argv[1]);
    check_file(&cube);
	get_map(&cube);
	check_map(&cube);

    end(&cube, 0);

    return (0);
}