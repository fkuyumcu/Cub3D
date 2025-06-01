/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:06:18 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/05/26 20:30:49 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int key_press_hook(int keycode, void *param)
{
    t_cube *cube = (t_cube *)param;
    key_press(keycode, &cube->player);
    return (0);
}

int key_release_hook(int keycode, void *param)
{
    t_cube *cube = (t_cube *)param;
    key_release(keycode, &cube->player);
    return (0);
}


int calculate_fps(t_cube *cube)
{
    struct timeval now;
    static struct timeval last_time;
    static int fps;
    static int frame_count;
    float elapsed_time;
    
    gettimeofday(&now, NULL);
    if(last_time.tv_sec == 0 && last_time.tv_usec == 0)
    last_time = now;    
    elapsed_time = (now.tv_sec - last_time.tv_sec) + (now.tv_usec - last_time.tv_usec) / 1000000.0;
    frame_count++;
    if(elapsed_time >= 1.0)
    {
        fps = frame_count / elapsed_time;
        last_time = now;
        frame_count = 0;
    }
    return (fps);
}



int loop_hook(t_cube *cube)
{
    float min_angle;
    int column;
    
    cube->fps = calculate_fps(cube);
    //printf("FPS: %d\n", cube->fps);
    column = 0;
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