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
            put_pixel(x, y, 0, cube);
        }
    }
}


char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

void radar(t_cube *cub)
{

    
}


void draw_map(t_cube *cub)
{
    int color = 0x0000FF;//mavi
    for(int y = 0; cub->map[y]; y++)
        for(int x = 0; cub->map[y][x]; x++)
            if(cub->map[y][x] == '1')
                draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, color, cub);
}

bool is_colliding(float player_x, float player_y, t_cube *cub)//ışının çarpışıp çarşpışmadığının kontrolü
{
    //aşağıdaki kodda playerin piksel cinsinden koordinatlarını oyunun bir bloğu cinsinden koordinata çevirdim.
    //örneğin bir bloğumuz 64 piksel olsun, player piksel cinsinden (128,128) koordinatına sahip olsun.
    //bu durumda playerin block cinsinden x ve y koordinatları 2,2 olur.
    int x = player_x / BLOCK_SIZE;
    int y = player_y / BLOCK_SIZE;
    if(cub->map[y][x] == '1')
        return (true);
    return (false);
}



int loop_hook(void *param)
{
    t_cube *cube = (t_cube *)param;
    float ray_x;
    float ray_y;
    move_player(&cube->player);
    clear_image(cube);
    draw_map(cube);
    draw_square((int)cube->player.x, (int)cube->player.y, 15, 0xFF0000, cube);
    
    ray_x = cube->player.x;
    ray_y = cube->player.y;
    cube->player.sin_ang = sin(cube->player.angle);
    //oyuncunun açısının sin ve cos değerleri, oyuncunun baktığı açıya göre 
    //ışının bir sonraki pikselde nereye gideceğini belirler.
    cube->player.cos_ang = cos(cube->player.angle);
    
    while (!is_colliding(ray_x, ray_y, cube))//ray_x ve ray_y çarpışmadığı sürece
    {
        put_pixel(ray_x, ray_y, 0xFF0000, cube);
        ray_x += cube->player.cos_ang;
        ray_y += cube->player.sin_ang;
    } 

    mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
    return (0);
}


int main(int argc, char **argv)
{
    t_cube cube;

    cube.map = get_map();
    cube.width = WIDTH;
    cube.height = HEIGHT;
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