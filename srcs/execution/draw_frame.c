/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:32:14 by noufel            #+#    #+#             */
/*   Updated: 2022/01/28 12:26:19 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	ft_img_pixel_put(t_img_data *img, int x, int y, int pix)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = pix;
}

void	draw_line(t_data *data, t_img_data *frame, int x, t_ray ray)
{
	int			y;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	t_texture	*texture;
	int			line_height;
	double		step;
	double		tex_pos;
	int			texel;


	y = data->draw_start;
	if (y < 0)
		return ;
	texture = get_texture(ray, data);
	// get x coordinates of the hit point in the wall
	if (ray.side == 0)
		wall_x = data->player.pos[Y] + ray.perp_wall_dist * ray.dir[Y];
	else
		wall_x = data->player.pos[X] + ray.perp_wall_dist * ray.dir[X];
	wall_x -= floor(wall_x);
	// get x in the texture image
	tex_x = (int)(wall_x * (double)texture->x);
	if (ray.side == 0 && ray.dir[X] > 0)
		tex_x = texture->x - tex_x -1;
	if (ray.side == 1 && ray.dir[Y] < 0)
		tex_x = texture->x -tex_x - 1;
	// calculate tex_y then loop on the wall
	line_height = data->draw_start - data->draw_end;
	if (line_height == 0)
		line_height = (int)BIG_VALUE;
	step = texture->y / line_height;
	tex_pos = (data->draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
	while (y < data->draw_end && y < SCREEN_WIDTH)
	{
		tex_y = (int)tex_pos & (texture->y - 1);
		tex_pos += step;
		texel = (int)*(texture->tex.addr + (tex_y * texture->tex.line_len + tex_x * (texture->tex.bpp / 8)));
		ft_img_pixel_put(frame, x, y, texel);
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
