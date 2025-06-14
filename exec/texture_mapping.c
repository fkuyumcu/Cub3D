/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:12:52 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/14 14:51:12 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	which_wall(t_cube *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			cub->wall_face = EAST;
		else
			cub->wall_face = WEST;
	}
	else
	{
		if (ray->step_y > 0)
			cub->wall_face = SOUTH;
		else
			cub->wall_face = NORTH;
	}
}

float	get_raw_dist(t_cube *cub, t_ray *ray)
{
	float	raw_dist;

	if (ray->side == 0)
		raw_dist = (ray->map_x - cub->player.x / BLOCK_SIZE
				+ (1 - ray->step_x) / 2) / ray->ray_dirx;
	else
		raw_dist = (ray->map_y - cub->player.y / BLOCK_SIZE
				+ (1 - ray->step_y) / 2) / ray->ray_diry;
	return (raw_dist);
}

void	draw_params(float dist, t_cube *cub)
{
	cub->start_wall = (HEIGHT - (BLOCK_SIZE / dist) * WIDTH) / 2;
	cub->end_wall = cub->start_wall + (BLOCK_SIZE / dist) * WIDTH;
	cub->start = (int)cub->start_wall;
	cub->end = fmin(HEIGHT - 1, (int)cub->end_wall);
	cub->line_h = (int)(cub->end_wall - cub->start_wall);
}

int	get_x(t_cube *cub, t_ray *ray, float raw_dist, t_text *tex)
{
	float	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = cub->player.y / BLOCK_SIZE + raw_dist * ray->ray_diry;
	else
		wall_x = cub->player.x / BLOCK_SIZE + raw_dist * ray->ray_dirx;
	wall_x = wall_x
		- floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->ray_dirx > 0)
		|| (ray->side == 1 && ray->ray_diry < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	draw_textured_wall(t_cube *cub, int column, int tex_x, t_text *texture)
{
	int	y;
	int	color;
	int	tex_y;
	int	index;

	y = cub->start;
	while (y < cub->end)
	{
		tex_y = ((y - cub->start_wall) / cub->line_h) * texture->height;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		if (tex_x >= texture->width)
			tex_x = texture->width - 1;
		index = tex_y * (texture->line_length / 4) + tex_x;
		if (index >= 0 && index < (texture->height * texture->width))
			color = texture->data[index];
		else
			color = 0;
		put_pixel(column, y, color, cub);
		y++;
	}
}
