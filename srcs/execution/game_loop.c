/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:40:52 by nammari           #+#    #+#             */
/*   Updated: 2022/01/26 20:16:28 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

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
	// why not : data->draw_end = data->draw_start + line_height ?
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

int	raycaster(t_data *data)
{
	int			x;
	t_vector	camera;
	t_ray		ray;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera[X] = (2 * x / (double)SCREEN_WIDTH) - 1;
		ray.dir[X] = data->dir[X] + data->plane[X] * camera[X];
		ray.dir[Y] = data->dir[Y] + data->plane[Y] * camera[X];
		dda(data, &ray);
		calculate_line_height(data, &ray);
		if (data->side == 1)
			data->color = 0x000000AA;
		else
			data->color = RGB_BLUE;
		draw_line(data, &data->frame, x);
		++x;
	}
	return (0);
}

void	calculate_side_dist(t_data *data, t_coord map, t_ray *ray)
{
	if(ray->dir[X] < 0)
	{
		ray->step_x = -1;
		ray->side_dist[X] = (data->pos[X] - map[X]) * ray->delta_dist[X];
	} 
	else
	{
		ray->step_x = 1;
		ray->side_dist[X] = (map[X] + 1 - data->pos[X]) * ray->delta_dist[X];
	}
	if (ray->dir[Y] < 0)
	{
		ray->step_y = -1;
		ray->side_dist[Y] = (data->pos[Y] - map[Y]) * ray->delta_dist[Y];
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist[Y] = (map[Y] + 1 - data->pos[Y]) * ray->delta_dist[Y];
	}
}

void	hit_detector(t_data *data, t_coord map, int *side, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			map[X] += ray->step_x;
			*side = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			map[Y] += ray->step_y;
			*side = 1;
		}
		if (data->map[map[Y]][map[X]] == '1')
			hit = 1;
	}
}

int	dda(t_data *data, t_ray *ray)
{
	t_coord	map;

	map[X] = (int)(data->pos[X]);
	map[Y] = (int)(data->pos[Y]);
	if (ray->dir[X] == 0)
		ray->delta_dist[X] = BIG_VALUE;
	else
		ray->delta_dist[X] = fabs(1 / ray->dir[X]);
	if (ray->dir[Y] == 0)
		ray->delta_dist[Y] = BIG_VALUE;
	else
		ray->delta_dist[Y] = fabs(1 / ray->dir[Y]);
	calculate_side_dist(data, map, ray);
	data->side = 0;
	hit_detector(data, map, &data->side, ray);
	if (data->side == 0)
		ray->perp_wall_dist = ray->side_dist[X] - ray->delta_dist[X];
	else
		ray->perp_wall_dist = ray->side_dist[Y] - ray->delta_dist[Y];
	return (SUCCESS);
}

int start = 0;

int	game_loop(t_data *data)
{
	if (start != 0)
		mlx_destroy_image(data->mlx, data->frame.img);
	start = 1;
	data->frame.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->frame.addr = mlx_get_data_addr(data->frame.img, 
		&data->frame.bpp, &data->frame.line_len, &data->frame.endian);
	raycaster(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
	return (SUCCESS);
}

int	move_player(int keyhook, t_data *data)
{
	double		move_speed;
	double		rot_speed;
	t_vector	old_plane;
	t_vector	old_dir;

	move_speed = 0.15;
	rot_speed = 0.09;
	if (keyhook == 'w')
	{
		data->pos[X] += data->dir[X] * move_speed;
		data->pos[Y] += data->dir[Y] * move_speed;
	}
	else if (keyhook == 's' && data->pos[Y] > 0)
	{
		data->pos[X] -= data->dir[X] * move_speed;
		data->pos[Y] -= data->dir[Y] * move_speed;
	}
	else if (keyhook == 'a')
	{
		old_dir[X] = data->dir[X];
		data->dir[X] = data->dir[X] * cos(-rot_speed) - data->dir[Y] * sin(-rot_speed);	
		data->dir[Y] = old_dir[X] * sin(-rot_speed) + data->dir[Y] * cos(-rot_speed);
		old_plane[X] = data->plane[X];
		data->plane[X] = data->plane[X] * cos(-rot_speed) - data->plane[Y] * sin(-rot_speed);
		data->plane[Y] = old_plane[X] * sin(-rot_speed) + data->plane[Y] * cos(-rot_speed);
	}
	else if (keyhook == 'd')
	{
		old_dir[X] = data->dir[X];
		data->dir[X] = data->dir[X] * cos(rot_speed) - data->dir[Y] * sin(rot_speed);	
		data->dir[Y] = old_dir[X] * sin(rot_speed) + data->dir[Y] * cos(rot_speed);
		old_plane[X] = data->plane[X];
		data->plane[X] = data->plane[X] * cos(rot_speed) - data->plane[Y] * sin(rot_speed);
		data->plane[Y] = old_plane[X] * sin(rot_speed) + data->plane[Y] * cos(rot_speed);
	}
	game_loop(data);
	return (0);
}

void	ft_img_pixel_put(t_img_data *img, int x, int y, int pix)
{
	char	*dst;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = pix;
}

	//mlx_hook(data->win, 3, 1L << 1, &get_hook, data);
	//mlx_hook(data->win, 17, 1L << 17, &close_win, data);
	//mlx_hook(data->win, 12, 1L << 15, &resize_func, data);