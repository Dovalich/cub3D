/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:32:14 by noufel            #+#    #+#             */
/*   Updated: 2022/01/28 13:26:52 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_img_pixel_put(t_img_data *img, int x, int y, int pix)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = pix;
}

void	draw_line(t_data *data, t_img_data *frame, int x, t_ray ray)
{
	int			y;
	t_texel		texel;
	int			line_h;
	double		step;

	y = data->draw_start;
	if (y < 0)
		return ;
	texel.texture = get_texture(ray, data);
	texel.tex_x = get_texture_column(texel.texture, &ray);
	if (data->draw_start - data->draw_end == 0)
		line_h = (int)BIG_VALUE;
	else
		line_h = data->draw_start - data->draw_end;
	step = 1.0 * texel.texture->y / line_h;
	texel.tex_pos = (data->draw_start - SCREEN_HEIGHT / 2 + line_h / 2) * step;
	while (y < data->draw_end && y < SCREEN_WIDTH)
	{	
		draw_texel(frame, &texel, x, y);
		texel.tex_pos += step;
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
