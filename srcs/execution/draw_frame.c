/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:32:14 by noufel            #+#    #+#             */
/*   Updated: 2022/01/27 18:53:21 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	ft_img_pixel_put(t_img_data *img, int x, int y, int pix)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = pix;
}

void	draw_line(t_data *data, t_img_data *frame, int x)
{
	int	y;

	y = data->draw_start;
	if (y < 0)
		return ;
	while (y < data->draw_end && y < SCREEN_WIDTH)
	{
		ft_img_pixel_put(frame, x, y, data->color);
		++y;
	}
}

static void	draw_floor(t_param *param, t_img_data *img)
{
	int	x;
	int	y;

	y = SCREEN_HEIGHT;
	x = 0;
	while (y > SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			ft_img_pixel_put(img, x, y, param->col_floor);
			++x;
		}
		--y;
	}
}

static void	draw_ceiling(t_param *param, t_img_data *img)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			ft_img_pixel_put(img, x, y, param->col_ceiling);
			++x;
		}
		++y;
	}
}

void	display_frame(t_data *data)
{
	if (data->frame.img)
		mlx_destroy_image(data->mlx, data->frame.img);
	data->frame.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->frame.addr = mlx_get_data_addr(data->frame.img,
			&data->frame.bpp, &data->frame.line_len, &data->frame.endian);
	draw_floor(data->param, &data->frame);
	draw_ceiling(data->param, &data->frame);
	raycaster(data, &data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
}
