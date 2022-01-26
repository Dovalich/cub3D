/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:43:25 by nammari           #+#    #+#             */
/*   Updated: 2022/01/26 20:36:01 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <time.h>

#define X 0 // representing the X coordinate of the t_vector struct
#define Y 1 // representing the Y coordinate of the t_vector struct

#define BIG_VALUE 100000000000

// Define colors

#define RGB_RED 0x00FF0000
#define RGB_GREEN 0x0000FF00
#define RGB_BLUE 0x000000FF

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef double t_vector[2];
typedef int		t_coord[2];

typedef struct img_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img_data;

typedef	struct texture
{
	int		x;
	int		y;
	void	*pixels;
}				t_texture;

typedef struct ray
{
	t_vector	dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
}				t_ray;


typedef struct mlx_data
{
	void				*mlx;
	void				*win;
	int					key;
	char				**map;
	t_param				*param;
	int					side;
	int					draw_start;
	int					draw_end;
	int					color;
	bool				key_was_pressed;
	t_texture			no;
	t_texture			ea;
	t_texture			so;
	t_texture			we;
	t_vector			dir;
	t_vector			plane;
	t_vector			pos;
	t_img_data			frame;
}					t_data;

void	ft_img_pixel_put(t_img_data *img, int x, int y, int pix);
int	get_hook(int keyhook, t_data *data);
int	close_win(t_data *data);
int	move_player(int keyhook, t_data *data);
// int		dda(t_data *data, t_vector ray_dir);
int		dda(t_data *data, t_ray *ray);
int		create_window(t_data *data);
int	create_window(t_data *data);
void	init_vectors(t_data *data);
void	init_textures(t_data *data);
void	get_player_pos(t_data *data);
int	game_loop(t_data *data);