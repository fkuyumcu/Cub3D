/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:02:34 by yalp              #+#    #+#             */
/*   Updated: 2025/06/11 13:20:56 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "gnl/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

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

typedef enum e_face
{
	NORTH ,
	SOUTH ,
	EAST ,
	WEST
}					t_face;

typedef struct s_ray
{
	float			ray_dirx;
	float			ray_diry;
	float			side_distx;
	float			side_disty;
	float			delta_distx;
	float			delta_disty;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
}					t_ray;

typedef struct s_text
{
	void			*img;
	int				*data;
	int				width;
	int				height;
	int				line_length;
	int				endian;
	int				bpp;
}					t_text;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;

	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			key_pov;

	bool			left;
	bool			right;
	struct s_cube	*cube;
}					t_player;

typedef struct s_cube
{
	char			**all_of_file;
	char			**map;
	char			**cpymap;
	char			**cpy_map;
	char			*texture_s;
	int				count_s;
	char			*texture_n;
	int				count_n;
	char			*texture_w;
	int				count_w;
	char			*texture_e;
	int				count_e;
	char			*color_c;
	int				count_c;
	int				*values_c;
	char			*color_f;
	int				count_f;
	int				*values_f;
	char			player_pov;
	int				player_count;
	int				player_x;
	int				player_y;
	int				width;
	int				height;

	void			*img;
	void			*mlx;
	void			*win;

	char			*data;
	int				bpp;
	int				size_line;
	int				endian;

	bool			debug;
	int				speed;
	float			a_speed;
	float			cos_val;
	float			sin_val;
	float			min_angle;
	float			angle_step;
	float			elapsed_time;

	t_text			e_text;
	t_text			w_text;
	t_text			n_text;
	t_text			s_text;
	int				r;
	int				g;
	int				b;

	int				fps;
	t_face			wall_face;
	t_player		player;

	float			start_z;
	float			end_z;
	int				start;
	int				end;
	int				line_h;
	float			raw_dist;
	float			perp_dist;
	float			block_dist;

}					t_cube;

int					check_len(char **rgb);
int					check_range(char **rgb);
int					close_hook(t_cube *cube);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strncpy(char *dest, char *src, int n);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strcpy(char *s1, char *s2);
void				arg_check(int argc, char **argv);
void				init_cube(t_cube *cube);
void				check_file(t_cube *cube);
void				free_double_pointer(char **ptr);
void				end(t_cube *cube, int exit_code);
char				*skip_spaces(char *str);
char				*trim_spaces(char *str);
int					*init_values(char *color);
void				check_file(t_cube *cube);
int					is_empty_line(char *line);
int					is_valid_path(char *line);
void				init_idents(t_cube *cube, char *line, int id);
void				send_to_init(t_cube *cube, char *line, int id);
int					is_ident_line(char *line);
void				read_file(t_cube *cube, char *file);
void				put_error(char *message, char *messagee, t_cube *cube);
int					is_valid_rgb(char *line);
int					is_map_line(char *line);
int					find_largest_line(char **map);
void				add_space_line(char ***map_ptr, int space_count,
						t_cube *cube);
void				get_map(t_cube *cube);
char				**mapcpy(char **map, t_cube *cube);
void				flood_fill(char **map, int x, int y, t_cube *cube);
void				add_space(char **map, int i, t_cube *cube);
void				fill_space(char ***map);
void				manage_map(char ***map, t_cube *cube);
void				check_double_map(char **map, t_cube *cube);
void				ffill(char **map, int x, int y, t_cube *cube);
void				check_map_chars(char **map, t_cube *cube);
void				check_map(t_cube *cube);
void				check_player(t_cube *cube);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strdup(const char *s1);
int					ft_atoi(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(char *s, char c);

void				put_pixel(int x, int y, int color, t_cube *game);
void				init_mlx(t_cube *cube);
void				draw_square(int x, int y, int size,
						t_cube *game);
int					key_press_hook(int keycode, void *param);
int					key_release_hook(int keycode, void *param);
void				clear_image(t_cube *cube);
void				draw_map(t_cube *cub);
bool				is_colliding(float ray_x, float ray_y, t_cube *cub);
bool				is_colliding_point(float ray_x, float ray_y, t_cube *cub);
/* float				distance(float x1, float y1, float x2, float y2,
						t_player player, t_cube *cub); */

void				ray_cast(t_cube *cub, int i, float sin_ang, float cos_ang);
void				radar(t_cube *cub, int column, float angle);
int					loop_hook(t_cube *cube);

void				end(t_cube *cube, int exit_code);
void				arg_check(int argc, char **argv);
void				init_cube(t_cube *cube);
int					parser(int argc, char **argv, t_cube *cube);

void				init_player(t_cube *cube);
int					key_press(int keycode, t_player *player);
int					key_release(int keycode, t_player *player);
void				move_player(t_player *player);
void				set_background(int start, int end, t_cube *cub, int i);

void				draw_textured_wall(t_cube *cub, int column, int tex_x,
						t_text *texture);
t_text				*get_wall_texture(t_cube *cub);
int					ft_atoi(const char *str);
void				set_background(int start, int end, t_cube *cub, int i);

void				ray_cast(t_cube *cub, int i, float sin_ang, float cos_ang);

void				which_wall(t_cube *cub, t_ray *ray);
float				get_raw_dist(t_cube *cub, t_ray *ray);
void				draw_params(float dist, t_cube *cub);
int					get_x(t_cube *cub, t_ray *ray, float raw_dist, t_text *tex);

void				check_textures(t_cube *cube);
void				get_addr(t_cube *cube);
void				load_textures(t_cube *cube);

#endif