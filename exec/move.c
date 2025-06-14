/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:51:35 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/14 15:59:53 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ws_keys(t_player *player)
{
	float	new_x;
	float	new_y;
	float	padding;

	padding = 30.0f;
	if (player->key_up)
		key_up(player);
	if (player->key_down)
	{
		new_x = player->x - player->cube->cos_val * player->cube->speed;
		new_y = player->y - player->cube->sin_val * player->cube->speed;
		if (player->cube->cos_val < 0)
			player->check_x = new_x + padding;
		else
			player->check_x = new_x - padding;
		if (!is_colliding(player->check_x, new_y, player->cube))
			player->x = new_x;
		if (player->cube->sin_val < 0)
			player->check_x = new_y + padding;
		else
			player->check_x = new_y - padding;
		if (!is_colliding(new_x, player->check_x, player->cube))
			player->y = new_y;
	}
}

void	wasd_keys(t_player *player)
{
	float	new_x;
	float	new_y;
	float	padding;

	padding = 30.0f;
	ws_keys(player);
	if (player->key_left)
		key_left(player);
	if (player->key_right)
	{
		new_x = player->x - player->cube->sin_val * player->cube->speed;
		new_y = player->y + player->cube->cos_val * player->cube->speed;
		if (player->cube->sin_val < 0)
			player->check_x = new_x + padding;
		else
			player->check_x = new_x - padding;
		if (!is_colliding(player->check_x, new_y, player->cube))
			player->x = new_x;
		if (player->cube->cos_val > 0)
			player->check_x = new_y + padding;
		else
			player->check_x = new_y - padding;
		if (!is_colliding(new_x, player->check_x, player->cube))
			player->y = new_y;
	}
}

void	move_player(t_player *player)
{
	player->cube->sin_val = sin(player->angle);
	player->cube->cos_val = cos(player->angle);
	player->cube->speed = 8;
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
}
