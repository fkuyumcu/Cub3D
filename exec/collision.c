/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:20:24 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/11 19:04:45 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool	is_colliding(float ray_x, float ray_y, t_cube *cub)
{
	int	x;
	int	y;

	x = ray_x / BLOCK_SIZE;
	y = ray_y / BLOCK_SIZE;
	if (x < 0 || y < 0 || !cub->map[y] || cub->map[y][x] == ' ' || cub->map[y][x] == '\0')
		return (true);
	if (cub->map[y][x] == '1')
		return (true);
	return (false);
}
