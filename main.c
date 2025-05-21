/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/05/21 18:16:45 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void arg_check(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
    if (argv[1][strlen(argv[1]) - 4] != '.')
    {
        fprintf(stderr, "Error: Invalid file extension\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(&argv[1][strlen(argv[1]) - 4], ".cub") != 0)
    {
        fprintf(stderr, "Error: Invalid file extension\n");
        exit(EXIT_FAILURE);
    }
    if (open(argv[1], O_RDONLY) < 0)
    {
        fprintf(stderr, "Error: File not found\n");
        exit(EXIT_FAILURE);
    }
}

void init_cube(t_cube *cube)
{
    cube->width = 0;
    cube->height = 0;
    cube->map = NULL;
    cube->texture_n = NULL;
    cube->texture_s = NULL;
    cube->texture_e = NULL;
    cube->texture_w = NULL;
    cube->color_f = NULL;
    cube->color_c = NULL;
    cube->all_of_file = NULL;
    cube->player_pov = 0;
}
void read_file(t_cube *cube, char *file)
{
    int		y;
	int		fd;
	int		i;
	char	*lines;

	i = 0;
	y = 0;
	fd = open(file, O_RDONLY);
	lines = get_next_line(fd);
	while (lines != NULL)
	{
		free(lines);
		lines = get_next_line(fd);
		y++;
	}	
	close(fd);
	cube->all_of_file = malloc(sizeof(char *) * (y + 1));
	fd = open(file, O_RDONLY);
	while (y > 0)
	{
		cube->all_of_file[i++] = get_next_line(fd);
		y--;
	}
    close(fd);
}
void init_mlx(t_cube *cube)
{
    cube->mlx = mlx_init();
    if (!cube->mlx)
    {
        fprintf(stderr, "Error: Failed to initialize mlx\n");
        exit(EXIT_FAILURE);
    }
    cube->win = mlx_new_window(cube->mlx, cube->width * 32, cube->height * 32, "Cub3D");
    if (!cube->win)
    {
        fprintf(stderr, "Error: Failed to create window\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    t_cube cube;

    int i = 0;
    arg_check(argc, argv);
    //init_cube(&cube);
    read_file(&cube, argv[1]);
    while(cube.all_of_file[i])
    {
        printf("%s", cube.all_of_file[i]);
        i++;
    }
    //init_mlx(&cube);

    return (0);
}