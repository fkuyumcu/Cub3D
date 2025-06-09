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

void	which_wall(t_cube *cub, t_ray *ray)
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

float	get_raw_dist(t_cube *cub, t_ray *ray)
{
	float	rawdist;

	if (ray->side == 0)
		rawdist = (ray->mapX - cub->player.x / BLOCK_SIZE + (1 - ray->stepX)
				/ 2) / ray->rayDirX;
	else
		rawdist = (ray->mapY - cub->player.y / BLOCK_SIZE + (1 - ray->stepY)
				/ 2) / ray->rayDirY;
	return (rawdist);
}

void	draw_params(float dist, t_cube *cub)
{
	cub->startO = (HEIGHT - (BLOCK_SIZE / dist) * WIDTH) / 2;
	cub->endO = cub->startO + (BLOCK_SIZE / dist) * WIDTH;
	cub->start = fmax(0, (int)cub->startO);
	cub->end = fmin(HEIGHT - 1, (int)cub->endO);
	cub->lineH = (int)(cub->endO - cub->startO);
}

int	get_x(t_cube *cub, t_ray *ray, float rawDist, t_text *tex)
{
	float	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = cub->player.y / BLOCK_SIZE + rawDist * ray->rayDirY;
	else
		wall_x = cub->player.x / BLOCK_SIZE + rawDist * ray->rayDirX;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->rayDirX > 0) || (ray->side == 1
			&& ray->rayDirY < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	draw_textured_wall(t_cube *cub, int column, int tex_x, t_text *texture)
{
	int	y;
	int	color;
	int	tex_y;

	y = cub->start;
	while (y < cub->end)
	{
		tex_y = ((y - cub->startO) / cub->lineH) * texture->height;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		color = texture->data[tex_y * (texture->line_length / 4) + tex_x];
		put_pixel(column, y, color, cub);
		y++;
	}
}
