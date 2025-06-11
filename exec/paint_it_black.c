/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_it_black.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:02:46 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/10 18:24:31 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_text	*get_wall_texture(t_cube *cub)
{
	if (cub->wall_face == NORTH)
		return (&(cub->n_text));
	else if (cub->wall_face == SOUTH)
		return (&(cub->s_text));
	else if (cub->wall_face == EAST)
		return (&(cub->e_text));
	else
		return (&(cub->w_text));
}

void	radar(t_cube *cub, int column, float angle)
{
	float	ray_x;
	float	ray_y;
	float	sin_ang;
	float	cos_ang;

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

void	set_background(int start, int end, t_cube *cub, int i)
{
	int	ceiling_hex;
	int	basement_hex;
	int	y;

	ceiling_hex = (cub->values_c[0] << 16)
		| (cub->values_c[1] << 8) | cub->values_c[2];
	basement_hex = (cub->values_f[0] << 16)
		| (cub->values_f[1] << 8) | cub->values_f[2];
	y = -1;
	while (++y < start)
		put_pixel(i, y, ceiling_hex, cub);
	y = end - 1;
	while (++y < HEIGHT - 1)
		put_pixel(i, y, basement_hex, cub);
}

void	draw_map(t_cube *cub)
{
	int	x;
	int	y;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE,
					cub);
		}
	}
}

void	put_pixel(int x, int y, int color, t_cube *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}
