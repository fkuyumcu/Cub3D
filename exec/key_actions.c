/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:06:18 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/10 18:27:44 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	key_press_hook(int keycode, void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	key_press(keycode, &cube->player);
	return (0);
}

int	key_release_hook(int keycode, void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	key_release(keycode, &cube->player);
	return (0);
}

int	loop_hook(t_cube *cube)
{
	float	min_angle;
	int		column;

	column = 0;
	move_player(&cube->player);
	clear_image(cube);
	while (column < WIDTH)
	{
		min_angle = cube->player.angle - PI / 6 + (column * (PI / 3) / WIDTH);
		radar(cube, column, min_angle);
		column++;
	}
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
	return (0);
}
