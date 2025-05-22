/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/05/21 18:39:58 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <math.h>

void put_pixel(int x, int y, int color, t_cube *game)
{
    if(x >= game->width || y >= game->height || x < 0 || y < 0)
        return;
    
    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;//mavi
    game->data[index + 1] = (color >> 8) & 0xFF;//8 bit sonrası yeşil
    game->data[index + 2] = (color >> 16) & 0xFF;//8 bit sağı kırmızı
}

void init_mlx(t_cube *cube)
{
    cube->mlx = mlx_init();
    cube->win = mlx_new_window(cube->mlx, cube->width, cube->height, "Cub3D");
    cube->img = mlx_new_image(cube->mlx, cube->width, cube->height);
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
    cube->data = mlx_get_data_addr(cube->img, &cube->bpp, &cube->size_line, &cube->endian);
}


void draw_square(int x, int y, int size, int color, t_cube *game)
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}

int key_press_hook(int keycode, void *param)
{
    t_cube *cube = (t_cube *)param;
    key_press(keycode, &cube->player);
    return 0;
}

int key_release_hook(int keycode, void *param)
{
    t_cube *cube = (t_cube *)param;
    key_release(keycode, &cube->player);
    return 0;
}

void clear_image(t_cube *cube)
{
    int x, y;
    for (y = 0; y < cube->height; y++)
    {
        for (x = 0; x < cube->width; x++)
        {
            put_pixel(x, y, 0x000000, cube);
        }
    }
}

int loop_hook(void *param)
{
    t_cube *cube = (t_cube *)param;
    move_player(&cube->player);
    clear_image(cube);
    draw_square((int)cube->player.x, (int)cube->player.y, 15, 0xFF0000, cube);
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
    return 0;
}

int main(int argc, char **argv)
{
    t_cube cube;

    cube.width = 800;
    cube.height = 600;
    init_player(&cube);
    init_mlx(&cube);
    cube.player.x = cube.width / 2; 
    cube.player.y = cube.height / 2;
    
    mlx_hook(cube.win, 2, 1, key_press_hook, &cube);//1L<<0 eventler ve maskler??
    mlx_hook(cube.win, 3, 2, key_release_hook, &cube);//1L<<1
    mlx_loop_hook(cube.mlx, loop_hook, &cube);
    
    mlx_loop(cube.mlx);
    return (0);
}