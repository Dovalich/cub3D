/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:43:25 by nammari           #+#    #+#             */
/*   Updated: 2022/01/25 15:24:59 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

#define X 0
#define Y 1
#define BIG_VALUE 100000000000

// Define colors

#define RGB_RED 0x00FF0000
#define RGB_GREEN 0x0000FF00
#define RGB_BLUE 0x000000FF

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef double t_vector[2];
typedef int		t_coord[2];

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img_data;

typedef struct mlx_data
{
	void				*mlx;
	void				*win;
	int					key;
	char				**map;
	t_param				*param;
	double				perp_wall_dist;
	int					side;
	int					step_x;
	int					step_y;
	int					draw_start;
	int					draw_end;
	int					color;
	t_vector			dir;
	t_vector			plane;
	t_vector			pos;
	t_vector			side_dist;
	t_vector			delta_dist;
	t_img_data			frame;
}					t_data;


void	ft_img_pixel_put(t_img_data *img, int x, int y, int pix);

int    dda(t_data *data, t_vector ray_dir);
int		create_window(t_data *data);
