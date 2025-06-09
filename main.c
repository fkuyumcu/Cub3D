/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/06/03 15:30:23 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void draw_square(int x, int y, int size, int color, t_cube *game)
{

    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}


int close_hook(t_cube *cube)
{

    
    mlx_destroy_image(cube->mlx, cube->img);
    mlx_destroy_image(cube->mlx, cube->e_text.img);
    mlx_destroy_image(cube->mlx, cube->w_text.img);
    mlx_destroy_image(cube->mlx, cube->n_text.img);
    mlx_destroy_image(cube->mlx, cube->s_text.img);
    mlx_destroy_window(cube->mlx, cube->win);
    mlx_destroy_display(cube->mlx);
    free(cube->mlx);
    end(cube, 0);
    return 0;
}

void check_textures(t_cube *cube)
{
    if(open(cube->texture_e,O_RDONLY) == -1)
    {
        put_error("Loading Texture", NULL, cube);
        end(cube,1);
    }
    if(open(cube->texture_w,O_RDONLY) == -1)
    {
        put_error("Loading Texture", NULL, cube);
        end(cube,1);
    }
    if(open(cube->texture_s,O_RDONLY) == -1)
    {
        put_error("Loading Texture", NULL, cube);
        end(cube,1);
    }
    if(open(cube->texture_n,O_RDONLY) == -1)
    {
        put_error("Loading texture.", NULL, cube);
        end(cube,1);
    }
}

void load_textures(t_cube *cube)
{
    int width;
    int height;
    cube->e_text.img = mlx_xpm_file_to_image(cube->mlx, cube->texture_e, &width, &height);
    cube->e_text.width = width;
    cube->e_text.height = height;
    
    cube->w_text.img = mlx_xpm_file_to_image(cube->mlx, cube->texture_w, &width, &height);
    cube->w_text.width = width;
    cube->w_text.height = height;
    
    cube->n_text.img = mlx_xpm_file_to_image(cube->mlx, cube->texture_n, &width, &height);
    cube->n_text.width = width;
    cube->n_text.height = height;
    
    cube->s_text.img = mlx_xpm_file_to_image(cube->mlx, cube->texture_s, &width, &height);
    cube->s_text.width = width;
    cube->s_text.height = height;
    
    cube->e_text.data = (int *)mlx_get_data_addr(cube->e_text.img, &cube->e_text.bpp, &cube->e_text.line_length, &cube->e_text.endian);
    cube->w_text.data = (int *)mlx_get_data_addr(cube->w_text.img, &cube->w_text.bpp, &cube->w_text.line_length, &cube->w_text.endian);
    cube->n_text.data = (int *)mlx_get_data_addr(cube->n_text.img, &cube->n_text.bpp, &cube->n_text.line_length, &cube->n_text.endian);
    cube->s_text.data = (int *)mlx_get_data_addr(cube->s_text.img, &cube->s_text.bpp, &cube->s_text.line_length, &cube->s_text.endian);
    
}

void set_direction(t_cube *cub)
{
    cub->player.x = (cub->player_x * BLOCK_SIZE) + (BLOCK_SIZE / 2);
    cub->player.y = (cub->player_y * BLOCK_SIZE) + (BLOCK_SIZE / 2);
    if (cub->player_pov == 'N')
    cub->player.angle = 3 * PI / 2;  
    else if (cub->player_pov == 'S')
    cub->player.angle = PI / 2;
    else if (cub->player_pov == 'E')
    cub->player.angle = 0;           
    else if (cub->player_pov == 'W')
    cub->player.angle = PI;
    
}

int main(int argc, char **argv)
{
    t_cube cube;

    parser(argc, argv, &cube);
    check_textures(&cube);
    init_mlx(&cube);
    init_player(&cube);
    set_direction(&cube);
    load_textures(&cube);

    mlx_hook(cube.win, 2, 1, key_press_hook, &cube);
    mlx_hook(cube.win, 3, 2, key_release_hook, &cube);
    mlx_hook(cube.win, 17, 0, close_hook, &cube);
    
    mlx_loop_hook(cube.mlx, loop_hook, &cube);
    mlx_loop(cube.mlx);
    return (0);
}
