/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:08:26 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/05/26 13:12:44 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void init_mlx(t_cube *cube)
{
    cube->mlx = mlx_init();
    cube->win = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "Cub3D");
    cube->img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
    cube->data = mlx_get_data_addr(cube->img, &cube->bpp, &cube->size_line, &cube->endian);
}

void clear_image(t_cube *cube)
{
    int x;
    int y;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            put_pixel(x, y, 0, cube);
        }
    }
}


char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100001100000001";
    map[3] = "100000100001001";
    map[4] = "100000111100001";
    map[5] = "100000010000001";
    map[6] = "100001101000001";
    map[7] = "100000000001001";
    map[8] = "100000010001001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

void init_cube(t_cube *cube)
{   
    cube->texture_n = NULL;
    cube->texture_s = NULL;
    cube->texture_e = NULL;
    cube->texture_w = NULL;
    cube->color_f = NULL;
    cube->color_c = NULL; 
    cube->all_of_file = NULL;
    cube->player_pov = 0;
    cube->r = 0;
    cube->g = 0;
    cube->b = 255;
}