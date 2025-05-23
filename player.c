#include "cube.h"
#include <math.h>

#define LEFT 65361 // Sol ok tuşu için doğru bir değer
#define RIGHT 65363 // Sağ ok tuşu için doğru bir değer

void init_player(t_cube *cube)
{
    cube->player.x = 0;
    cube->player.y = 0;
    cube->player.angle = 0;
    cube->player.key_up = false;
    cube->player.key_down = false;
    cube->player.key_left = false;
    cube->player.key_right = false;
    cube->player.left = false;
    cube->player.right = false;
    cube->player.cube = cube;
}

int key_press(int keycode, t_player *player)
{
    if(keycode == W)
        player->key_up = true;
    if(keycode == S)
        player->key_down = true;
    if(keycode == A)
        player->key_left = true;
    if(keycode == D)
        player->key_right = true;
    if(keycode == LEFT)
        player->left = true;
    if(keycode == RIGHT)
        player->right = true; 
    return 0;
}

int key_release(int keycode, t_player *player)
{
    if(keycode == W)
        player->key_up = false;
    if(keycode == S)
        player->key_down = false;
    if(keycode == A)
        player->key_left = false;
    if(keycode == D)
        player->key_right = false;
    if(keycode == LEFT)
        player->left = false;
    if(keycode == RIGHT)
        player->right = false;
    return 0;
}

void move_player(t_player *player)
{


    player->cube->sin_val = sin(player->angle);
    player->cube->cos_val = cos(player->angle);
    player->cube->speed = 3;
    player->cube->a_speed = 0.05;

    if(player->left)
    {
        player->angle -= player->cube->a_speed;
        if (player->angle < 0)
            player->angle += 2 * PI;
        if (player->angle > 2 * PI)
            player->angle -= 2 * PI;
    }

    if(player->right)
    {
        player->angle += player->cube->a_speed;
        if (player->angle < 0)
            player->angle += 2 * PI;
        if (player->angle > 2 * PI)
            player->angle -= 2 * PI;
    }

    if (player->key_up)
    {
        player->x += player->cube->cos_val * player->cube->speed;
        player->y += player->cube->sin_val * player->cube->speed;
    }
    if (player->key_down)
    {
        player->x -= player->cube->cos_val * player->cube->speed;
        player->y -= player->cube->sin_val * player->cube->speed;
    }
    if (player->key_left)
    {
        player->x += player->cube->sin_val * player->cube->speed;
        player->y -= player->cube->cos_val * player->cube->speed;
    }
    if (player->key_right)
    {
        player->x -= player->cube->sin_val * player->cube->speed;
        player->y += player->cube->cos_val * player->cube->speed;
    }
}