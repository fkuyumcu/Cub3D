/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/06/01 14:46:59 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void draw_square(int x, int y, int size, int color, t_cube *game)
{

    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}





int main(int argc, char **argv)
{
    t_cube cube;

    cube.map = get_map();
    init_player(&cube);
    init_mlx(&cube);
    init_cube(&cube);
    cube.player.x = WIDTH / 2; // doğum noktasını buradan ayarla
    cube.player.y = HEIGHT / 2;

    mlx_hook(cube.win, 2, 1, key_press_hook, &cube);   // 1L<<0 eventler ve maskler??
    mlx_hook(cube.win, 3, 2, key_release_hook, &cube); // 1L<<1
    mlx_loop_hook(cube.mlx, loop_hook, &cube);

    mlx_loop(cube.mlx);
    return (0);
}