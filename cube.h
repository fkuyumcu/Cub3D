/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:02:34 by yalp              #+#    #+#             */
/*   Updated: 2025/05/21 18:42:19 by yalp             ###   ########.fr       */
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


//defines

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0

# define W 100
# define D 115
# define S 97
# define A 119
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

	bool left_rotate;
	bool right_rotate;
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
    t_player player;
}	t_cube;


void arg_check(int argc, char **argv);
void init_cube(t_cube *cube);
void check_file(t_cube *cube);

#endif