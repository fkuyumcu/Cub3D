/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:12:52 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/14 17:52:35 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static	void	init_step(t_cube *cub, t_ray *ray)
{
	if (ray->ray_dirx < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_diry < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	if (ray->ray_dirx < 0)
		ray->side_distx = (cub->player.x / BLOCK_SIZE - ray->map_x)
			* ray->delta_distx;
	else
		ray->side_distx = (ray->map_x + 1.0f - cub->player.x / BLOCK_SIZE)
			* ray->delta_distx;
	if (ray->ray_diry < 0)
		ray->side_disty = (cub->player.y / BLOCK_SIZE - ray->map_y)
			* ray->delta_disty;
	else
		ray->side_disty = (ray->map_y + 1.0f - cub->player.y / BLOCK_SIZE)
			* ray->delta_disty;
}

void	init_ray(t_cube *cub, t_ray *ray, float sin_ang, float cos_ang)
{
	ray->ray_dirx = cos_ang;
	ray->ray_diry = sin_ang;
	ray->map_x = (int)(cub->player.x / BLOCK_SIZE);
	ray->map_y = (int)(cub->player.y / BLOCK_SIZE);
	ray->delta_distx = fabs(1.0f / ray->ray_dirx);
	ray->delta_disty = fabs(1.0f / ray->ray_diry);
	init_step(cub, ray);
}

//if hit x, side 0
int	dda_algorithm(t_cube *cub, t_ray *ray)
{
	while (1)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] == '1')
			break ;
	}
	return (ray->side);
}

void	ray_cast(t_cube *cub, int i, float sin_ang, float cos_ang)
{
	t_ray	ray;
	t_text	*tex;
	int		tex_x;

	init_ray(cub, &ray, sin_ang, cos_ang);
	dda_algorithm(cub, &ray);
	which_wall(cub, &ray);
	cub->raw_dist = get_raw_dist(cub, &ray);
	cub->perp_dist = cub->raw_dist
		* cos(atan2(ray.ray_diry, ray.ray_dirx) - cub->player.angle);
	cub->block_dist = cub->perp_dist * BLOCK_SIZE;
	draw_params(cub->block_dist, cub);
	tex = get_wall_texture(cub);
	tex_x = get_x(cub, &ray, cub->raw_dist, tex);
	draw_textured_wall(cub, i, tex_x, tex);
	set_background(cub->start, cub->end, cub, i);
}
