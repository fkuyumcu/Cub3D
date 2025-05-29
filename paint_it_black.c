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

// DDA algoritması ile ışın takibi
void ray_cast_dda(t_cube *cub, int column, float angle)
{
    float ray_dir_x = cos(angle);
    float ray_dir_y = sin(angle);
    
    // Oyuncunun grid koordinatları
    int map_x = (int)(cub->player.x / BLOCK_SIZE);
    int map_y = (int)(cub->player.y / BLOCK_SIZE);
    
    // Delta mesafeler (1 grid hücresi için)
    float delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
    float delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
    
    // Hareket yönü ve başlangıç mesafeleri
    int step_x, step_y;
    float side_dist_x, side_dist_y;
    
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = ((cub->player.x / BLOCK_SIZE) - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - (cub->player.x / BLOCK_SIZE)) * delta_dist_x;
    }
    
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = ((cub->player.y / BLOCK_SIZE) - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - (cub->player.y / BLOCK_SIZE)) * delta_dist_y;
    }
    
    // DDA algoritması
    int hit = 0;
    int side; // 0: X duvarı, 1: Y duvarı
    
    while (hit == 0)
    {
        // En yakın kenarı seç ve adım at
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        
        // Duvar kontrolü
        if (map_x < 0 || map_y < 0 || !cub->map[map_y] || cub->map[map_y][map_x] == '\0')
            break;
            
        if (cub->map[map_y][map_x] == '1')
            hit = 1;
    }
    
    // Duvar yüzünü belirle
    if (side == 0)
    {
        if (step_x > 0)
            cub->wall_face = WEST;
        else
            cub->wall_face = EAST;
    }
    else
    {
        if (step_y > 0)
            cub->wall_face = NORTH;
        else
            cub->wall_face = SOUTH;
    }
    
    // Perpendicular distance hesabı (fish-eye etkisini önlemek için)
    float perp_wall_dist;
    if (side == 0)
        perp_wall_dist = (map_x - (cub->player.x / BLOCK_SIZE) + (1 - step_x) / 2) / ray_dir_x;
    else
        perp_wall_dist = (map_y - (cub->player.y / BLOCK_SIZE) + (1 - step_y) / 2) / ray_dir_y;
    
    // Fish-eye düzeltmesi: ışını kamera düzlemine olan açıya göre düzelt
    float player_angle = cub->player.angle;
    float ray_angle = angle;
    float fix_angle = player_angle - ray_angle;
    // Açı 0-2PI aralığında olsun
    if (fix_angle < 0)
        fix_angle += 2 * PI;
    if (fix_angle > 2 * PI)
        fix_angle -= 2 * PI;
    
    // Düzeltilmiş mesafe ile duvar yüksekliğini hesapla
    float corrected_dist = perp_wall_dist * cos(fix_angle);
    float line_height = (BLOCK_SIZE / (corrected_dist * BLOCK_SIZE)) * WIDTH;
    float drawStartOrig = (HEIGHT - line_height) / 2;
    float drawEndOrig = drawStartOrig + line_height;
    
    // Ekran sınırları kontrolü
    int drawStart = (int)drawStartOrig;
    int drawEnd = (int)drawEndOrig;
    
    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
    
    // Wall X koordinatı (doku için)
    float wall_x;
    if (side == 0)
        wall_x = cub->player.y / BLOCK_SIZE + perp_wall_dist * ray_dir_y;
    else
        wall_x = cub->player.x / BLOCK_SIZE + perp_wall_dist * ray_dir_x;
    wall_x -= floor(wall_x); // Ondalık kısmını al
    
    // Texture koordinatı
    t_text *texture = get_wall_texture(cub);
    int tex_x = (int)(wall_x * texture->width);
    
    // Texture yönü düzeltme
    if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
        tex_x = texture->width - tex_x - 1;
    
    // Texture çizimi
    if (texture && texture->img)
    {
        draw_textured_wall(cub, column, drawStart, drawEnd, 1.0, 
                          (int)line_height, drawStartOrig, tex_x, texture);
        cub->r = 0;
        cub->g = 0;
        cub->b = 255;
        set_background(drawStart, drawEnd, cub, column);
    }
}

void radar(t_cube *cub, int column, float angle) // 2D painting
{
    if (!cub->debug)
    {
        ray_cast_dda(cub, column, angle);
    }
    else
    {
        // Debug modu için eski ray-tracing
        float ray_x = cub->player.x;
        float ray_y = cub->player.y;
        float sin_ang = sin(angle);
        float cos_ang = cos(angle);

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
        put_pixel(i, y, ceiling_color, cub);

    y = end - 1;
    while (++y < HEIGHT - 1)
        put_pixel(i, y, basement_color, cub);
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
