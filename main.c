/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/05/26 13:10:04 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"





void draw_square(int x, int y, int size, int color, t_cube *game)
{
    int i;
    i = -1;
    while (++i < size)
    {
        put_pixel(x + i, y + i, color, game);
        put_pixel(x + size - i, y + i, color, game);
        put_pixel(x + i, y + size - i, color, game);
        put_pixel(x + size - i, y + size - i, color, game);
    }
}


bool is_colliding(float ray_x, float ray_y, t_cube *cub) // ışının çarpışıp çarşpışmadığının kontrolü
{
    // aşağıdaki kodda playerin piksel cinsinden koordinatlarını oyunun bir bloğu cinsinden koordinata çevirdim.
    // örneğin bir bloğumuz 64 piksel olsun, player piksel cinsinden (128,128) koordinatına sahip olsun.
    // bu durumda playerin block cinsinden x ve y koordinatları 2,2 olur.
    int x;
    int y;
    x = ray_x / BLOCK_SIZE;
    y = ray_y / BLOCK_SIZE;
    if (cub->map[y][x] == '1')
        return (true);
    return (false);
}

float distance(float x1, float y1, float x2, float y2, t_player player) // fisheye fix
{
    float dx;
    float dy;
    float dist;
    float angle_diff;

    dx = x2 - x1;
    dy = y2 - y1;
    dist = sqrt(dx * dx + dy * dy);
    angle_diff = atan2(dy, dx) - player.angle;

    return (dist * cos(angle_diff));
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