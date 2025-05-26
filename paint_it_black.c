/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_it_black.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:02:46 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/05/26 14:02:55 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void ray_cast(t_cube *cub, int i, float sin_ang, float cos_ang) // 3D painting
{
    float params[3]; // ray_x, ray_y, dist
    float height;
    float start;
    float end;
    float shade;

    cub->r = 0;
    cub->g = 0;
    cub->b = 255;
    shade = 1.0;

    params[0] = cub->player.x;
    params[1] = cub->player.y;
    while (!is_colliding(params[0], params[1], cub))
    {
        params[0] += cos_ang;
        params[1] += sin_ang;
    }
    params[2] = distance(cub->player.x, cub->player.y, params[0], params[1], cub->player);
    if (params[2] > 0)
        shade = 1.0 - (params[2] / 1000.0);
    cub->r = (int)(cub->r * shade);
    cub->g = (int)(cub->g * shade);
    cub->b = (int)(cub->b * shade);
    height = (BLOCK_SIZE / params[2]) * (WIDTH);
    start = (HEIGHT - height) / 2;
    end = start + height;
    set_background(start, end, cub, i);
}

void radar(t_cube *cub, int column, float angle) // 2D painting
{
    float ray_x;
    float ray_y;
    float sin_ang;
    float cos_ang;

    ray_x = cub->player.x;
    ray_y = cub->player.y;
    sin_ang = sin(angle);
    cos_ang = cos(angle);
    if (!cub->debug)
        ray_cast(cub, column, sin_ang, cos_ang);
    else
    {
        while (!is_colliding(ray_x, ray_y, cub))
        {
            ray_x += cos_ang;
            ray_y += sin_ang;
            put_pixel(ray_x, ray_y, 0xFF0000, cub);
        }
    }
}

void set_background(int start, int end, t_cube *cub, int i)
{
    int color;
    int ceiling_color = 0x808080;
    int basement_color = 0x00FF00;
    int y;
    color = (cub->r << 16) | (cub->g << 8) | cub->b;

    y = -1;

    while (++y < start)
        put_pixel(i, y, ceiling_color, cub); // ekranın en üst kısmının y değeri 0
    // y = 0 ekranın en alt kısmı
    // aşağı indikçe y değeri artmakta

    y = end - 1;
    while (++y < HEIGHT - 1)
        put_pixel(i, y, basement_color, cub);

    while (start < end)
    {
        put_pixel(i, start, color, cub);
        start++;
    }
}

void draw_map(t_cube *cub)
{
    int x;
    int y;
    int color;
    y = -1;
    color = 0x00FF00; // yeşil renk
    while (cub->map[++y])
    {
        x = -1;
        while (cub->map[y][++x])
        {
            if (cub->map[y][x] == '1')
                draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, color, cub);
        }
    }
}

void put_pixel(int x, int y, int color, t_cube *game)
{
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;

    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;             // mavi
    game->data[index + 1] = (color >> 8) & 0xFF;  // 8 bit sağı yeşil
    game->data[index + 2] = (color >> 16) & 0xFF; // 8 bit sağı kırmızı
}
