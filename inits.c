/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:08:26 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/01 14:47:35 by yalp             ###   ########.fr       */
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
    cube->fps = 0;
    
    // Initialize textures
    cube->e_text.img = mlx_xpm_file_to_image(cube->mlx, "textures/wall.xpm", &cube->e_text.width, &cube->e_text.height);
    cube->w_text.img = mlx_xpm_file_to_image(cube->mlx, "textures/wall_2.xpm", &cube->w_text.width, &cube->w_text.height);
    cube->n_text.img = mlx_xpm_file_to_image(cube->mlx, "textures/wall_3.xpm", &cube->n_text.width, &cube->n_text.height);
    cube->s_text.img = mlx_xpm_file_to_image(cube->mlx, "textures/wall_4.xpm", &cube->s_text.width, &cube->s_text.height);

    cube->e_text.data = NULL;
    cube->w_text.data = NULL;
    cube->n_text.data = NULL;
    cube->s_text.data = NULL;
    
    // Get data addresses for textures only if loading was successful
    if (cube->e_text.img)
        cube->e_text.data = (int *)mlx_get_data_addr(cube->e_text.img, &cube->e_text.bpp, &cube->e_text.line_length, &cube->e_text.endian);
    if (cube->w_text.img)
        cube->w_text.data = (int *)mlx_get_data_addr(cube->w_text.img, &cube->w_text.bpp, &cube->w_text.line_length, &cube->w_text.endian);
    if (cube->n_text.img)
        cube->n_text.data = (int *)mlx_get_data_addr(cube->n_text.img, &cube->n_text.bpp, &cube->n_text.line_length, &cube->n_text.endian);
    if (cube->s_text.img)
        cube->s_text.data = (int *)mlx_get_data_addr(cube->s_text.img, &cube->s_text.bpp, &cube->s_text.line_length, &cube->s_text.endian);
        
    // Check if textures loaded successfully
    if (!cube->e_text.img || !cube->w_text.img || !cube->n_text.img || !cube->s_text.img) {
        printf("Warning: Some textures failed to load. Check if 'textures/wall.xpm' exists and is valid.\n");
    }
}