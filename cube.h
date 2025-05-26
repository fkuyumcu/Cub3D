/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:02:34 by yalp              #+#    #+#             */
/*   Updated: 2025/05/26 13:11:32 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "minilibx-linux/mlx.h"
# include <stdbool.h>
# include <math.h>

//defines

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK_SIZE 64
//block, bir karenin piksel cinsinden uzunluğunu belirler
# define DEBUG 0

# define W 119
# define D 100
# define S 115
# define A 97
# define ESC 65307
# define P 112

# define LEFT 65361
# define RIGHT 65363 

# define PI 3.14159

typedef struct s_player
{
	float x;
	float y;
	float angle;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;
	bool key_pov;

	bool left;
	bool right;
	struct s_cube *cube;
}	t_player;


typedef struct s_cube
{
	char	**all_of_file;
	char	**map;
	char	*texture_s;
	int		count_s;
	char	*texture_n;
	int		count_n;
	char	*texture_w;
	int		count_w;
	char	*texture_e;
	int		count_e;
	char	*color_c;
	int		count_c;
	char	*color_f;
	int		count_f;
	char	player_pov;

	void	*img;
	void	*mlx;
	void	*win;

	char *data;
    int bpp;
    int size_line;
    int endian;
	
	bool debug;
	int speed;
    float a_speed;
    float cos_val;
    float sin_val;
	float min_angle;
	float angle_step;

	int r;
	int g;
	int b;
	
    t_player player;
}	t_cube;


void arg_check(int argc, char **argv);
void init_cube(t_cube *cube);
void check_file(t_cube *cube);

void put_pixel(int x, int y, int color, t_cube *game);
void init_mlx(t_cube *cube);
void draw_square(int x, int y, int size, int color, t_cube *game);
int key_press_hook(int keycode, void *param);
int key_release_hook(int keycode, void *param);
void clear_image(t_cube *cube);
char **get_map(void);
void draw_map(t_cube *cub);
bool is_colliding(float ray_x, float ray_y, t_cube *cub);
float distance(float x1, float y1, float x2, float y2, t_player player);

void ray_cast(t_cube *cub, int i, float sin_ang, float cos_ang);
void radar(t_cube *cub, int column, float angle);
int loop_hook(void *param);

void end(t_cube *cube);
void arg_check(int argc, char **argv);
void init_cube(t_cube *cube);


void init_player(t_cube *cube);
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);
void move_player(t_player *player);
void set_background(int start, int end, t_cube *cub, int i);



#endif