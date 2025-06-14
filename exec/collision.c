/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:20:24 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/14 14:53:13 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	key_left(t_player *player)
{
	float	new_x;
	float	new_y;
	float	padding;

	padding = 30.0f;
	new_x = player->x + player->cube->sin_val * player->cube->speed;
	new_y = player->y - player->cube->cos_val * player->cube->speed;
	if (player->cube->sin_val > 0)
		player->check_x = new_x + padding;
	else
		player->check_x = new_x - padding;
	if (!is_colliding(player->check_x, new_y, player->cube))
		player->x = new_x;
	if (player->cube->cos_val < 0)
		player->check_x = new_y + padding;
	else
		player->check_x = new_y - padding;
	if (!is_colliding(new_x, player->check_x, player->cube))
		player->y = new_y;
}

void	key_up(t_player *player)
{
	float	new_x;
	float	new_y;
	float	padding;

	padding = 30.0f;
	new_x = player->x + player->cube->cos_val * player->cube->speed;
	new_y = player->y + player->cube->sin_val * player->cube->speed;
	if (player->cube->cos_val > 0)
		player->check_x = new_x + padding;
	else
		player->check_x = new_x - padding;
	if (!is_colliding(player->check_x, new_y, player->cube))
		player->x = new_x;
	if (player->cube->sin_val > 0)
		player->check_x = new_y + padding;
	else
		player->check_x = new_y - padding;
	if (!is_colliding(new_x, player->check_x, player->cube))
		player->y = new_y;
}

bool	is_colliding(float ray_x, float ray_y, t_cube *cub)
{
	int	x;
	int	y;

	x = ray_x / BLOCK_SIZE;
	y = ray_y / BLOCK_SIZE;
	if (cub->map[y][x] == ' ' || cub->map[y][x] == '\0'
			|| cub->map[y][x] == '\n' || cub->map[y][x] == '1')
		return (true);
	return (false);
}
