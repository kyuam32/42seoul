/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:33:13 by namkyu            #+#    #+#             */
/*   Updated: 2021/04/11 16:40:52 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../new_minilbx/mlx.h"
# include "../lib/1.libft/get_next_line.h"
# include "../lib/1.libft/libft.h"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_EXIT 17

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_RIGHT 124
# define KEY_LEFT 123

# define CUB_DATA_CORRUPTED 5000
# define MAP_DATA_CORRUPTED 4000
# define MEM_ALLOCATE_FAILED 3000
# define CANT_OPEN_FILE 2000
# define ARGUMENT_ERROR 1000

# define HORIZOTAL_SIDE 0
# define VIRTICAL_SIDE 1

# define PI 3.14159265359

# define EA_P 0
# define WE_P 1
# define SO_P 2
# define NO_P 3
# define SP_P 4

# define R_W 5
# define R_H 6
# define C_F 7
# define C_C 8
# define MAP_CHECK 9

# pragma pack(push, 1)

typedef struct		s_bmheader
{
	unsigned char	type1;
	unsigned char	type2;
	unsigned int	fsize;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	offbits;
	unsigned int	isize;
	int				width;
	int				height;
	unsigned short	planes;
	unsigned short	bitcount;
	unsigned int	compression;
	unsigned int	sizeimage;
	int				xpelspereter;
	int				ypelspereter;
	unsigned int	clrused;
	unsigned int	clrimportant;
}					t_bmheader;

# pragma pack(pop)

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_img
{
	void			*ptr;
	int				*data;
	int				width;
	int				height;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_system
{
	void			*mlx;
	void			*win;
}					t_system;

typedef struct		s_player
{
	t_vector		axis;
	t_vector		dir;
	double			mov_speed;
	double			rot_speed;
	int				locate;
}					t_player;

typedef struct		s_texture
{
	char			*path[5];
	t_img			no;
	t_img			so;
	t_img			we;
	t_img			ea;
	t_img			sp;
	int				floor;
	int				ceiling;
}					t_texture;

typedef struct		s_minimap
{
	char			**map_arr;
	char			**dfs;
	char			*map_str;
	int				cub_width;
	int				cub_height;
	int				row;
	int				col;
	int				w_scale;
	int				h_scale;
	int				h_offset;
}					t_minimap;

typedef struct		s_draw
{
	t_vector		start;
	t_vector		end;
	double			dist_adj;
	int				color;
	int				tile;
	int				side;
}					t_draw;

typedef struct		s_cam
{
	t_vector		dir;
	double			fov;
	double			dist;
	int				fov_precision;
	int				curr_precision;
	int				ray_width;
}					t_cam;

typedef struct		s_sprite
{
	t_vector		hit;
	double			sp_rad;
	double			sp_dist;
	double			sp_adj_dist;
	int				sp_side;
}					t_sprite;

typedef struct		s_data
{
	t_system		system;
	t_texture		texture;
	t_minimap		map;
	t_player		player;
	t_sprite		sprite;
	t_draw			draw;
	t_img			img;
	t_cam			cam;
	char			*cub_path;
	char			check[10];
	int				cub_size;
	int				resolution_width;
	int				resolution_height;
	int				crash_report;
	int				bit_map;
	int				graphic;
}					t_data;

/*
** valid_check
*/

char				*valid_trim(t_data *data, char *str, int skip);
void				valid_display(t_data *data);
int					valid_rgb(t_data *data, char *line, int *object, int bit);
void				valid_map(char *line, t_data *data);
void				valid_playerdir(t_data *data, char c, int row, int col);

/*
** utils
*/

void				ft_free(void *target);
void				print_ptr(char **s);
void				v_iput(t_vector *vec, int x_input, int y_input);
void				v_dput(t_vector *vec, double x_input, double y_input);
int					skip_space(char *str);

/*
** sprite
*/

void				sprite_hit(t_data *data, t_vector *hit, int x, int y);
void				sprite_ray_rad(t_data *data, int x, int y);
void				sprite_rad_inlines(t_data *data, \
										t_vector *rad, int x, int y);
void				sprite_rad(t_data *data, int x, int y);

/*
** ray_cast
*/

int					ray_hit(t_data *data, int x_map, int y_map);
void				ray_distance(t_data *data, t_vector *dir);
void				ray_cast(t_data *data, void (*draw_target)(t_data *));
void				ray_initalize(t_data *data);

/*
** ray_calculate
*/

double				ray_cal_deg2rad(int x);
void				ray_cal_delta(t_data *data, t_vector *delta, \
									t_vector *distance, t_vector *dir);
void				ray_cal_distance(t_data *data, t_vector *delta, \
									t_vector *distance, t_vector *dir);

/*
** parse_cub_data
*/

void				parse_rgb(char *str, int type, t_data *data, int *object);
void				parse_resolution(char *str, t_data *data);
void				parse_texture_path(char *str, int type, t_data *data);
void				parse_info(char *line, t_data *data);
void				parse_cub_data(t_data *data);

/*
** mini_map
*/

void				m_map_grid(t_data *data);
void				m_map_wall(t_data *data);
void				m_map_player(t_data *data);

/*
** map_dfs
*/

int					map_search_escape(t_data *data, \
										char **is_visited, int x, int y);
void				map_dfs_free(t_data *data);
void				map_dfs(t_data *data);

/*
** map_create
*/
void				map_allocate(t_data *data);
void				map_str_to_array(t_data *data);
void				map_sizecheck(t_data *data);
void				map_create(t_data *data);
void				map_copy(char *line, t_data *data);

/*
** keypress
*/

void				key_move(t_data *data, t_vector *dir, int inv, int keycode);
void				key_rotate(t_data *data, t_vector *dir, \
								int inv, int keycode);
int					key_press(int keycode, t_data *data);

/*
** exit
*/

int					exit_win(t_data *data);
void				exit_message(t_data *data);
void				exit_mlx_destroy(t_data *data);
void				exit_process(t_data *data, int errno);

/*
** draw_window
*/

t_img				*draw_texture_path(t_data *data, double *wall_x);
void				draw_texture(t_data *data, int x, int y, int height);
void				draw_sprite(t_data *data, int x, int y, int height);
int					draw_convert_height(t_data *data, double dist);
void				draw_window(t_data *data);

/*
** draw_basic
*/

void				draw_ray(t_data *data);
void				draw_rectangle(t_data *data, int x, int y, int color);
void				draw_line(t_data *data);

/*
** bitmap
*/

void				bitmap_header(t_bmheader *header, t_data *data);
void				bitmap_create(t_data *data);

/*
** allocate
*/

void				allocate_system(t_data *data);
void				allocate_texture(t_data *data);
void				allocate_player(t_data *data);

/*
** main
*/

int					main_loop(t_data *data);
void				input_check(t_data *data, int argc, char **argv);
int					main(int argc, char **argv);

#endif
