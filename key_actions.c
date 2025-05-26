/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:06:18 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/05/26 13:11:50 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int key_press_hook(int keycode, void *param)
{
    t_cube *cube = (t_cube *)param;
    key_press(keycode, &cube->player);
    return 0;
}

int key_release_hook(int keycode, void *param)
{
    t_cube *cube = (t_cube *)param;
    key_release(keycode, &cube->player);
    return 0;
}

int loop_hook(void *param)
{
    float min_angle;
    t_cube *cube;
    int column;

    column = 0;
    cube = (t_cube *)param;
    move_player(&cube->player);
    clear_image(cube);
    if (cube->debug)
    {
        draw_map(cube);
        draw_square((int)cube->player.x, (int)cube->player.y, 15, 0xFF00FF, cube);
    }

    while (column < WIDTH) // her bir ışını tek tek radar fonksiyonuna gönderiyorum debug flagine göre 2d ya da 3d çizim yapıyor
    {
        min_angle = cube->player.angle - PI / 6 + (column * (PI / 3) / WIDTH);//(column * (PI / 3) / WIDTH bak 
        radar(cube, column, min_angle);
        column++;
    }
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
    return (0);
}