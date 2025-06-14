/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:51:35 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/14 16:01:26 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_player(t_cube *cube)
{
	cube->player.x = 0;
	cube->player.y = 0;
	cube->player.angle = 0;
	cube->min_angle = 0;
	cube->angle_step = PI / 6 / WIDTH;
	cube->player.key_pov = false;
	cube->player.key_up = false;
	cube->player.key_down = false;
	cube->player.key_left = false;
	cube->player.key_right = false;
	cube->player.left = false;
	cube->player.right = false;
	cube->player.cube = cube;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left = true;
	if (keycode == RIGHT)
		player->right = true;
	if (keycode == P)
		player->key_pov = true;
	if (keycode == ESC)
		close_hook(player->cube);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left = false;
	if (keycode == RIGHT)
		player->right = false;
	if (keycode == P)
		player->key_pov = false;
	return (0);
}
