/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_it_black.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:02:46 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/05/28 16:06:39 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_text *get_wall_texture(t_cube *cub)
{
	if (cub->wall_face == NORTH)
		return &(cub->n_text);
	else if (cub->wall_face == SOUTH)
		return &(cub->s_text);
	else if (cub->wall_face == EAST)
		return &(cub->e_text);
	else
		return &(cub->w_text);
}

int get_texture_x(t_cube *cub, float ray_x, float ray_y, t_text *texture)
{
	float wall_hit;

	if (cub->wall_face == EAST || cub->wall_face == WEST)
		wall_hit = fmod(ray_y, BLOCK_SIZE);
	else
		wall_hit = fmod(ray_x, BLOCK_SIZE);

	int tex_x = (wall_hit / BLOCK_SIZE) * texture->width;

	// Kenar taşmalarını önle
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;

	return tex_x;
}

void draw_textured_wall(t_cube *cub, int column, int start, int end, float shade, int ray_height, float start_orig, int tex_x, t_text *texture)
{
    int y;
    int color;

    if (!texture || !texture->data || !texture->img)
    {
        color = (cub->r << 16) | (cub->g << 8) | cub->b;
        for (y = start; y < end; y++)
            put_pixel(column, y, color, cub);
        return;
    }
    
    for (y = start; y < end; y++)
    {
        // Duyarlı texture y koordinatı: y - original start
        int tex_y = ((y - start_orig) / ray_height) * texture->height;
        
        // Boundary check for texture coordinates
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= texture->height)
            tex_y = texture->height - 1;

        // pixel renk verisi
        color = texture->data[tex_y * (texture->line_length / 4) + tex_x];

        // gölgelendirme
        int r = ((color >> 16) & 0xFF);
        int g = ((color >> 8) & 0xFF);
        int b = (color & 0xFF);
        color = (r << 16) | (g << 8) | b;

        put_pixel(column, y, color, cub);
    }
}

void ray_cast(t_cube *cub, int i, float sin_ang, float cos_ang) // 3D painting
{
    float ray_x = cub->player.x;
    float ray_y = cub->player.y;
    float prev_x, prev_y;
    float dist;
    float height;
    float shade = 1.0;

    cub->r = 0;
    cub->g = 0;
    cub->b = 255;

    // Ray ilerletme
    while (!is_colliding(ray_x, ray_y, cub))
    {
        prev_x = ray_x;
        prev_y = ray_y;
        ray_x += cos_ang;
        ray_y += sin_ang;
    }

    // Duvara çarpınca yön tespiti
    int map_x = (int)(ray_x / BLOCK_SIZE);
    int map_y = (int)(ray_y / BLOCK_SIZE);
    int prev_map_x = (int)(prev_x / BLOCK_SIZE);
    int prev_map_y = (int)(prev_y / BLOCK_SIZE);

    if (map_x > prev_map_x)
        cub->wall_face = EAST;
    else if (map_x < prev_map_x)
        cub->wall_face = WEST;
    else if (map_y > prev_map_y)
        cub->wall_face = SOUTH;
    else if (map_y < prev_map_y)
        cub->wall_face = NORTH;

    dist = distance(cub->player.x, cub->player.y, ray_x, ray_y, cub->player);

    // duvar yüksekliği ve orijinal çizim aralığı
    height = (BLOCK_SIZE / dist) * WIDTH;
    float drawStartOrig = (HEIGHT - height) / 2;
    float drawEndOrig = drawStartOrig + height;
    int drawStart = (int)drawStartOrig;
    int drawEnd = (int)drawEndOrig;
    int lineHeight = (int)(drawEndOrig - drawStartOrig);

    // clamp çizim sınırları
    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;

    t_text *texture = get_wall_texture(cub);
    
    if (texture && texture->img) {
        int tex_x = get_texture_x(cub, ray_x, ray_y, texture);
        draw_textured_wall(cub, i, drawStart, drawEnd, shade, lineHeight, drawStartOrig, tex_x, texture);
    } else {
        set_background(drawStart, drawEnd, cub, i);
    }
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
