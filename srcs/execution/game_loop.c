/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:40:52 by nammari           #+#    #+#             */
/*   Updated: 2022/01/27 14:27:06 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	ft_img_pixel_put(t_img_data *img, int x, int y, int pix)
{
	char	*dst;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = pix;
}

void	calculate_line_height(t_data *data, t_ray *ray)
{
	int	line_height;

	line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	data->draw_start = -1 * line_height / 2 + (SCREEN_HEIGHT) / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = SCREEN_HEIGHT / 2 + line_height / 2;
	if (data->draw_end < 0)
		data->draw_end = SCREEN_HEIGHT - 1;
}

void	draw_line(t_data *data, t_img_data *frame, int x)
{
	int	y;

	y = data->draw_start;
	while (y < data->draw_end)
	{
		ft_img_pixel_put(frame, x, y, data->color);
		++y;
	}
}

void	calculate_side_dist(int map_x, int map_y, t_ray *ray, t_player *player)
{
	if(ray->dir[X] < 0)
	{
		ray->step_x = -1;
		ray->side_dist[X] = (player->pos[X] - map_x) * ray->delta_dist[X];
	} 
	else
	{
		ray->step_x = 1;
		ray->side_dist[X] = (map_x + 1 - player->pos[X]) * ray->delta_dist[X];
	}
	if (ray->dir[Y] < 0)
	{
		ray->step_y = -1;
		ray->side_dist[Y] = (player->pos[Y] - map_y) * ray->delta_dist[Y];
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist[Y] = (map_y + 1 - player->pos[Y]) * ray->delta_dist[Y];
	}
}

void	hit_detector(char **map, int *map_x, int *map_y, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			*map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			*map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[*map_y][*map_x] == '1')
			hit = 1;
	}
}

void	dda(t_data *data, t_ray *ray, t_player *player)
{
	int	map_x;
	int	map_y;

	map_x = (int)(player->pos[X]);
	map_y = (int)(player->pos[Y]);
	if (ray->dir[X] == 0)
		ray->delta_dist[X] = BIG_VALUE;
	else
		ray->delta_dist[X] = fabs(1 / ray->dir[X]);
	if (ray->dir[Y] == 0)
		ray->delta_dist[Y] = BIG_VALUE;
	else
		ray->delta_dist[Y] = fabs(1 / ray->dir[Y]);
	calculate_side_dist(map_x, map_y, ray, player);
	ray->side = 0;
	hit_detector(data->param->map, &map_x, &map_y, ray);
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist[X] - ray->delta_dist[X];
	else
		ray->perp_wall_dist = ray->side_dist[Y] - ray->delta_dist[Y];
}

void	draw_frame(t_data *data)
{
	if (data->frame.img)
		mlx_destroy_image(data->mlx, data->frame.img);
	data->frame.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->frame.addr = mlx_get_data_addr(data->frame.img, 
		&data->frame.bpp, &data->frame.line_len, &data->frame.endian);
	raycaster(data, &data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
}

void	raycaster(t_data *data, t_player *player)
{
	int			x;
	t_vector	camera;
	t_ray		ray;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera[X] = (2 * x / (double)SCREEN_WIDTH) - 1;
		ray.dir[X] = player->dir[X] + data->plane[X] * camera[X];
		ray.dir[Y] = player->dir[Y] + data->plane[Y] * camera[X];
		dda(data, &ray, player);
		calculate_line_height(data, &ray);
		if (ray.side == 1)
			data->color = 0x000000AA;
		else
			data->color = RGB_BLUE;
		draw_line(data, &data->frame, x);
		++x;
	}
}
