/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:02:34 by yalp              #+#    #+#             */
/*   Updated: 2025/05/24 09:42:18 by fkuyumcu         ###   ########.fr       */
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

#define LEFT 65361
#define RIGHT 65363 

# define PI 3.14159

typedef struct s_player
{
	float x;
	float y;
	float angle;
	float sin_ang;
	float cos_ang;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

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
	int		width;
	int		height;

	void	*img;
	void	*mlx;
	void	*win;

	char *data;
    int bpp;
    int size_line;
    int endian;
	
	int speed;
    float a_speed;
    float cos_val;
    float sin_val;
    t_player player;
}	t_cube;


void arg_check(int argc, char **argv);
void init_cube(t_cube *cube);
void check_file(t_cube *cube);

#endif