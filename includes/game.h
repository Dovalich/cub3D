/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:43:25 by nammari           #+#    #+#             */
/*   Updated: 2022/01/28 22:13:11 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "parsing.h"

# define X 0 // representing the X coordinate of the t_vector struct
# define Y 1 // representing the Y coordinate of the t_vector struct

# define BIG_VALUE 100000000000

// Define colors

# define RGB_RED 0x00FF0000
# define RGB_GREEN 0x0000FF00
# define RGB_BLUE 0x000000FF

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

typedef double	t_vector[2];

typedef struct	s_texel
{
	t_texture		*texture;
	int				tex_x;
	int				tex_y;
	int				color;
	double			tex_pos;
}	t_texel;

typedef struct ray
{
	t_vector	dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			real_line_h;
	int			side;
	double		wall_x;
}				t_ray;

typedef struct player
{
	t_vector	dir;
	t_vector	pos;
}			t_player;

typedef struct mlx_data
{
	void		*mlx;
	void		*win;
	t_param		*param;
	t_player	player;
	int			draw_start;
	int			draw_end;
	int			color;
	int			mouse_x;
	int			mouse_y;
	t_vector	plane;
	t_img_data	frame;
}					t_data;

int			capture_keyhook(int keyhook, t_data *data);
int			capture_mouse_move(t_data *data);
bool		move_player(int keyhook, t_data *data, t_player *player);
void		rotate_player(int rotation, t_data *data, t_player *player, \
				double rot_speed);
int			close_win(t_data *data);
void		game_init(t_data *data, t_param *param);
void		draw_line(t_data *data, t_img_data *frame, int x, t_ray ray);
void		raycaster(t_data *data, t_player *player);
void		display_frame(t_data *data);
void		exit_program(t_data *data, int exit_status);
int			handle_resize(int keyhook, t_data *data);
t_texture	*get_texture(t_ray ray, t_data *data);
int			get_texture_column(t_texture *texture, t_ray *ray);
void		ft_img_pixel_put(t_img_data *img, int x, int y, int pix);
void		draw_texel(t_img_data *frame, t_texel *texel, int x, int y);

#endif
