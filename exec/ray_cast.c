/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:12:52 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/03 14:50:09 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


static void init_step(t_cube *cub, t_ray *ray)
{
    
        if (ray->rayDirX < 0)
            ray->stepX = -1;
        else
            ray->stepX = 1;
        if (ray->rayDirY < 0)
            ray->stepY = -1;
        else
            ray->stepY = 1;
        if (ray->rayDirX < 0)
            ray->sideDistX = (cub->player.x / BLOCK_SIZE - ray->mapX)
                * ray->deltaDistX;
        else
            ray->sideDistX = (ray->mapX + 1.0f - cub->player.x / BLOCK_SIZE)
                * ray->deltaDistX;
        if (ray->rayDirY < 0)
            ray->sideDistY = (cub->player.y / BLOCK_SIZE - ray->mapY)
                * ray->deltaDistY;
        else
            ray->sideDistY = (ray->mapY + 1.0f - cub->player.y / BLOCK_SIZE)
                * ray->deltaDistY;
}
    
void init_ray(t_cube *cub, t_ray *ray, float sin_ang, float cos_ang)
{
    ray->rayDirX = cos_ang;
    ray->rayDirY = sin_ang;
    ray->mapX = (int)(cub->player.x / BLOCK_SIZE);
    ray->mapY = (int)(cub->player.y / BLOCK_SIZE);
    ray->deltaDistX = fabs(1.0f / ray->rayDirX);
    ray->deltaDistY = fabs(1.0f / ray->rayDirY);
    init_step(cub, ray);
}

int dda_algorithm(t_cube *cub, t_ray *ray)
{
    while (1)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        if (ray->mapY < 0 || ray->mapX < 0 || !cub->map[ray->mapY]
            || !cub->map[ray->mapY][ray->mapX]
            || cub->map[ray->mapY][ray->mapX] == '1')
            break;
    }
    return (ray->side);
}

void which_wall(t_cube *cub, t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->stepX > 0)
            cub->wall_face = EAST;
        else
            cub->wall_face = WEST;
    }
    else
    {
        if (ray->stepY > 0)
            cub->wall_face = SOUTH;
        else
            cub->wall_face = NORTH;
    }
}

float get_raw_dist(t_cube *cub, t_ray *ray)//camera plane distance hesaplanıyor
{
    float rawdist;

    if (ray->side == 0)
        rawdist = (ray->mapX - cub->player.x / BLOCK_SIZE
            + (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        rawdist = (ray->mapY - cub->player.y / BLOCK_SIZE
            + (1 - ray->stepY) / 2) / ray->rayDirY;
    return rawdist;
}

void draw_params(float dist,t_cube *cub)
{
    cub->startO = (HEIGHT - (BLOCK_SIZE / dist) * WIDTH) / 2;
    cub->endO = cub->startO + (BLOCK_SIZE / dist) * WIDTH;
    cub->start = fmax(0, (int)cub->startO);
    cub->end = fmin(HEIGHT - 1, (int)cub->endO);
    cub->lineH = (int)(cub->endO - cub->startO);
}

int get_x(t_cube *cub, t_ray *ray, float rawDist, t_text *tex)//texture'dan dilim dilim veri çekeceğimizden dolayı hangi x dilimine çarptığımızı hesaplayalım
{
    float wallX;
    int   tex_x;

    if (ray->side == 0)
        wallX = cub->player.y / BLOCK_SIZE + rawDist * ray->rayDirY;//rawdist * raydiry aslında bir vektör olduğundan dolayı oyuncunun y koordinatına ekleniyor
    else
        wallX = cub->player.x / BLOCK_SIZE + rawDist * ray->rayDirX;
    wallX = wallX - floor(wallX);
    tex_x = (int)(wallX * tex->width);
    if ((ray->side == 0 && ray->rayDirX > 0)
        || (ray->side == 1 && ray->rayDirY < 0))
        tex_x = tex->width - tex_x - 1;
    return tex_x;
}

void draw_textured_wall(t_cube *cub, int column, int tex_x, t_text *texture)
{
    int y;
    int color;
        
    y = cub->start;
    while (y < cub->end)
    {
        int tex_y;
        tex_y = ((y - cub->startO) / cub->lineH) * texture->height;
        

        if (tex_y >= texture->height)
            tex_y = texture->height - 1;
        
        color = texture->data[tex_y * (texture->line_length / 4) + tex_x];//texture datasından color seç
        put_pixel(column, y, color, cub);        
        y++;
    }
}


void ray_cast(t_cube *cub, int i, float sin_ang, float cos_ang)//texture yerleşimi için rawdist kullanılmalı
{
    t_ray        ray;
    float         rawDist;//orijinal distance
    float         perpDist;//camera plane distance
    float         dist;
    t_text       *tex;
    int           tex_x;

    init_ray(cub, &ray, sin_ang, cos_ang);
    dda_algorithm(cub, &ray);
    which_wall(cub, &ray);
    rawDist = get_raw_dist(cub, &ray);
    perpDist = rawDist * cos(atan2(ray.rayDirY, ray.rayDirX) - cub->player.angle);
    dist = perpDist * BLOCK_SIZE;
    draw_params(dist, cub);
    tex = get_wall_texture(cub);
    tex_x = get_x(cub, &ray, rawDist, tex);
    draw_textured_wall(cub, i, tex_x, tex);
    set_background(cub->start, cub->end, cub, i);
}