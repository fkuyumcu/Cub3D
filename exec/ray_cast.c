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

static void	init_step(t_cube *cub, t_ray *ray)
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

void	init_ray(t_cube *cub, t_ray *ray, float sin_ang, float cos_ang)
{
	ray->rayDirX = cos_ang;
	ray->rayDirY = sin_ang;
	ray->mapX = (int)(cub->player.x / BLOCK_SIZE);
	ray->mapY = (int)(cub->player.y / BLOCK_SIZE);
	ray->deltaDistX = fabs(1.0f / ray->rayDirX);
	ray->deltaDistY = fabs(1.0f / ray->rayDirY);
	init_step(cub, ray);
}

int	dda_algorithm(t_cube *cub, t_ray *ray)
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
			break ;
	}
	return (ray->side);
}

void	ray_cast(t_cube *cub, int i, float sin_ang, float cos_ang)
//texture yerleşimi için rawdist kullanılmalı
{
	t_ray	ray;
	t_text	*tex;
	int		tex_x;

	init_ray(cub, &ray, sin_ang, cos_ang);
	dda_algorithm(cub, &ray);
	which_wall(cub, &ray);
	cub->rawDist = get_raw_dist(cub, &ray);
	cub->perpDist = cub->rawDist * cos(atan2(ray.rayDirY, ray.rayDirX)
			- cub->player.angle);
	cub->block_dist = cub->perpDist * BLOCK_SIZE;
	draw_params(cub->block_dist, cub);
	tex = get_wall_texture(cub);
	tex_x = get_x(cub, &ray, cub->rawDist, tex);
	draw_textured_wall(cub, i, tex_x, tex);
	set_background(cub->start, cub->end, cub, i);
}
