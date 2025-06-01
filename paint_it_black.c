/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_it_black.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:02:46 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/05/31 14:50:55 by fkuyumcu         ###   ########.fr       */
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


void draw_textured_wall(t_cube *cub, int column, int start, int end, float shade, int ray_height, float start_orig, int tex_x, t_text *texture)
{
    int y;
    int color;
    y = start;
    while (y < end)
    {
        int tex_y;
        tex_y = ((y - start_orig) / ray_height) * texture->height;
        
        color = texture->data[tex_y * (texture->line_length / 4) + tex_x];
        put_pixel(column, y, color, cub);        
        y++;
    }
}

void ray_cast(t_cube *cub, int i, float sin_ang, float cos_ang)
{
    float sideDistX;
    float sideDistY;
    float rayDirX =  cos_ang;//açının sinüsü ve kosinüsü
    float rayDirY =  sin_ang;
    
    int mapX = (int)(cub->player.x / BLOCK_SIZE);
    int mapY = (int)(cub->player.y / BLOCK_SIZE);
    
    float deltaDistX = fabs(1.0f / rayDirX);
    float deltaDistY = fabs(1.0f / rayDirY);
    
    // 4) Step ve sideDist
    int stepX;
    int stepY;
    if (rayDirX < 0)//rayDirX negatif ise ışın sola bakıyordur. duruma göre xde bir blok yer değiştir
        stepX = -1;
    else
        stepX = 1;

    if (rayDirY < 0)//raydiry negatif ise ışın aşağı bakıyordur
        stepY = -1;
    else
        stepY = 1;

    if (rayDirX < 0)
        sideDistX = (cub->player.x / BLOCK_SIZE - mapX) * deltaDistX;//sidedistx ilk başta özel hesaplanır. sonra deltadistx kadar artar
    else
        sideDistX = (mapX + 1.0f - cub->player.x / BLOCK_SIZE) * deltaDistX;

    if (rayDirY < 0)
        sideDistY = (cub->player.y / BLOCK_SIZE - mapY) * deltaDistY;
    else
        sideDistY = (mapY + 1.0f - cub->player.y / BLOCK_SIZE) * deltaDistY;


    int side = 0; // 0: x gridine, 1: y gridine çarpma
    
  
    //deltaDistX ve deltaDistY ise x ve y yönündeki adım mesafelerini tutar
    while (1)
    {
        if (sideDistX < sideDistY)//en yakın hangisinde grid değiştirecekse 
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else// y gridine olan mesafe x gridine olan mesafeden küçükse
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (cub->map[mapY] && cub->map[mapY][mapX] == '1')
            break;
    }
    // ışının sola ya da sağa bakmasına göre duvar yüzeyini belirle
    if (side == 0)//duvar dikeydir
    {
        if (stepX > 0)
            cub->wall_face = EAST;
        else
            cub->wall_face = WEST;
    }
    else//duvar yataydır
    {
        if (stepY > 0)//duvar yatay ve aşağı bakıyorsa
            cub->wall_face = SOUTH;
        else
            cub->wall_face = NORTH;
    }

    
    // 7) Perp mesafe (fish-eye düzeltmeli)
    float perpDist;
    if (side == 0)
        perpDist = (mapX - cub->player.x/BLOCK_SIZE + (1 - stepX)/2)/rayDirX;
    else
        perpDist = (mapY - cub->player.y/BLOCK_SIZE + (1 - stepY)/2)/rayDirY;

    // Fish-eye düzeltmesi için ray açısı ile oyuncu açısı arasındaki farkı kullan
    float ray_angle = atan2(sin_ang, cos_ang);
    float angle_diff = ray_angle - cub->player.angle;
    perpDist = perpDist * cos(angle_diff);

    float dist = fabs(perpDist * BLOCK_SIZE);

    float height = (BLOCK_SIZE / dist) * WIDTH;
    float startO = (HEIGHT - height)/2, endO = startO + height;
    int start = fmax(0, (int)startO), end = fmin(HEIGHT-1, (int)endO);
    int lineH = (int)(endO - startO);
    t_text *tex = get_wall_texture(cub);

    float wallX;
    if (side == 0)
        wallX = cub->player.y/BLOCK_SIZE + perpDist * rayDirY;
    else
        wallX = cub->player.x/BLOCK_SIZE + perpDist * rayDirX;

    wallX -= floor(wallX);
    int tex_x = (int)(wallX * tex->width);
    if ((side==0 && rayDirX>0) || (side==1 && rayDirY<0))
        tex_x = tex->width - tex_x - 1;
    draw_textured_wall(cub, i, start, end, 1.0f, lineH, startO, tex_x, tex);
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
