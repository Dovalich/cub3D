/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:43:25 by nammari           #+#    #+#             */
/*   Updated: 2022/01/25 10:36:41 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

#define X 0
#define Y 1

typedef struct mlx_data
{
	void				*mlx;
	void				*win;
	int					key;
	char				**map;
	t_param				*param;
	double				dir_vect[2];
	double				plane_vect[2];
	double				pos_vect[2];
}					t_data;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img_data;


void	ft_img_pixel_put(t_img_data *img, int x, int y, int pix);
int		create_window(t_data *data);
