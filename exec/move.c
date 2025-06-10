/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:51:35 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/10 15:51:43 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ws_keys(t_player *player)
{
	float	new_x;
	float	new_y;

	if (player->key_up)
	{
		new_x = player->x + player->cube->cos_val * player->cube->speed;
		new_y = player->y + player->cube->sin_val * player->cube->speed;
		if (!is_colliding(new_x, new_y, player->cube))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->key_down)
	{
		new_x = player->x - player->cube->cos_val * player->cube->speed;
		new_y = player->y - player->cube->sin_val * player->cube->speed;
		if (!is_colliding(new_x, new_y, player->cube))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}

void	wasd_keys(t_player *player)
{
	float	new_x;
	float	new_y;

	ws_keys(player);
	if (player->key_left)
	{
		new_x = player->x + player->cube->sin_val * player->cube->speed;
		new_y = player->y - player->cube->cos_val * player->cube->speed;
		if (!is_colliding(new_x, new_y, player->cube))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->key_right)
	{
		new_x = player->x - player->cube->sin_val * player->cube->speed;
		new_y = player->y + player->cube->cos_val * player->cube->speed;
		if (!is_colliding(new_x, new_y, player->cube))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}

void	move_player(t_player *player)
{
	player->cube->sin_val = sin(player->angle);
	player->cube->cos_val = cos(player->angle);
	player->cube->speed = 3;
	player->cube->a_speed = 0.05;
	if (player->left)
	{
		player->angle -= player->cube->a_speed;
		if (player->angle < 0)
			player->angle += 2 * PI;
		if (player->angle > 2 * PI)
			player->angle -= 2 * PI;
	}
	if (player->right)
	{
		player->angle += player->cube->a_speed;
		if (player->angle < 0)
			player->angle += 2 * PI;
		if (player->angle > 2 * PI)
			player->angle -= 2 * PI;
	}
	wasd_keys(player);
	if (player->key_pov)
		player->cube->debug = !player->cube->debug;
}
