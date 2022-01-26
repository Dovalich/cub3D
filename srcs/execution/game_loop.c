/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:40:52 by nammari           #+#    #+#             */
/*   Updated: 2022/01/26 13:13:33 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

void	get_player_pos(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr(PLAYER_CHAR, data->map[y][x]) != NULL)
			{
				data->pos[X] = x;
				data->pos[Y] = y;
				return ;
			}
			++x;
		}
		++y;
	}
}

void	init_vectors(t_data *data)
{
	get_player_pos(data);
	data->plane[X] = 0;
	data->plane[Y] = 0.66;
	data->dir[X] = -1;
	data->dir[Y] = 0;
}

void	calculate_line_height(t_data *data)
{
	int	line_height;

	line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
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

int start = 0;

int	raycaster(t_data *data)
{
	int			x;
	int			width;
	t_vector	camera;
	t_vector	ray_dir;

	width = SCREEN_WIDTH;
	x = 0;
	if (start != 0)
		mlx_destroy_image(data->mlx, data->frame.img);
	start = 1;
	data->frame.img = mlx_new_image(data->mlx, width, SCREEN_HEIGHT);
	data->frame.addr = mlx_get_data_addr(data->frame.img, \
		&data->frame.bpp, &data->frame.line_len, &data->frame.endian);
	while (x < width)
	{
		camera[X] = (2 * x / (double)width) - 1;
		ray_dir[X] = data->dir[X] + data->plane[X] * camera[X];
		ray_dir[Y] = data->dir[Y] + data->plane[Y] * camera[X];
		dda(data, ray_dir);
		//calculate pixel len to draw on column
		calculate_line_height(data);
		if (data->side == 1)
		{
			data->color = 0x000000AA;
		}
		else
			data->color = RGB_BLUE;
		// if (!(data->frame))
		// 	exit_clean(MLX_FAIL, 0, NULL, data->param);
		draw_line(data, &data->frame, x);
		++x;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->frame.img, 0, 0);
	return (0);
}

void	calculate_side_dist(t_data *data, t_coord map, t_vector ray_dir)
{
	if(ray_dir[X] < 0)
	{
		data->step_x = -1;
		data->side_dist[X] = (data->pos[X] - map[X]) * data->delta_dist[X];
	} 
	else
	{
		data->step_x = 1;
		data->side_dist[X] = (map[X] + 1 - data->pos[X]) * data->delta_dist[X];
	}
	if (ray_dir[Y] < 0)
	{
		data->step_y = -1;
		data->side_dist[Y] = (data->pos[Y] - map[Y]) * data->delta_dist[Y];
	}
	else
	{
		data->step_y = 1;
		data->side_dist[Y] = (map[Y] + 1 - data->pos[Y]) * data->delta_dist[Y];
	}
}

void	hit_detector(t_data *data, t_coord map, int *side)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->side_dist[X] < data->side_dist[Y])
		{
			data->side_dist[X] += data->delta_dist[X];
			map[X] += data->step_x;
			*side = 0;
		}
		else
		{
			data->side_dist[Y] += data->delta_dist[Y];
			map[Y] += data->step_y;
			*side = 1;
		}
		if (data->map[map[Y]][map[X]] == '1')
			hit = 1;
	}
}

int	dda(t_data *data, t_vector ray_dir)
{
	t_coord	map;

	map[X] = (int)(data->pos[X]);
	map[Y] = (int)(data->pos[Y]);
	if (ray_dir[X] == 0)
		data->delta_dist[X] = BIG_VALUE;
	else
		data->delta_dist[X] = fabs(1 / ray_dir[X]);
	if (ray_dir[Y] == 0)
		data->delta_dist[Y] = BIG_VALUE;
	else
		data->delta_dist[Y] = fabs(1 / ray_dir[Y]);
	calculate_side_dist(data, map, ray_dir);
	data->side = 0;
	hit_detector(data, map, &data->side);
	if (data->side == 0)
		data->perp_wall_dist = data->side_dist[X] - data->delta_dist[X];
	else
		data->perp_wall_dist = data->side_dist[Y] - data->delta_dist[Y];
	return (SUCCESS);
}


int	game_loop(t_data *data)
{
	// dda
	// put_frame
	raycaster(data);
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
	else if (keyhook == 'd')
	{
		old_dir[X] = data->dir[X];
		data->dir[X] = data->dir[X] * cos(-rot_speed) - data->dir[Y] * sin(-rot_speed);	
		data->dir[Y] = old_dir[X] * sin(-rot_speed) + data->dir[Y] * cos(-rot_speed);
		old_plane[X] = data->plane[X];
		data->plane[X] = data->plane[X] * cos(-rot_speed) - data->plane[Y] * sin(-rot_speed);
		data->plane[Y] = old_plane[X] * sin(-rot_speed) + data->plane[Y] * cos(-rot_speed);
	}
	else if (keyhook == 'a')
	{
		old_dir[X] = data->dir[X];
		data->dir[X] = data->dir[X] * cos(rot_speed) - data->dir[Y] * sin(rot_speed);	
		data->dir[Y] = old_dir[X] * sin(rot_speed) + data->dir[Y] * cos(rot_speed);
		old_plane[X] = data->plane[X];
		data->plane[X] = data->plane[X] * cos(rot_speed) - data->plane[Y] * sin(rot_speed);
		data->plane[Y] = old_plane[X] * sin(rot_speed) + data->plane[Y] * cos(rot_speed);
	}
	return (0);
}

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	exit(0);
	return (0);
}

int	get_hook(int keyhook, t_data *data)
{
	if (keyhook == 'w' || keyhook == 's' || keyhook == 'a' || keyhook == 'd')
		return (move_player(keyhook, data));
	else if (keyhook == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		return (0);
	}
	return (1);
}

int	create_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ERROR);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Welcome to CUB3D !");
	if (!data->win)
		return (ERROR);
	init_vectors(data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_hook(data->win, 3, 1L << 1, &get_hook, data);
	mlx_hook(data->win, 17, 1L << 17, &close_win, data);
	// mlx_hook(data->win, 12, 1L << 15, &resize_func, data);
	mlx_loop(data->mlx);
	return (SUCCESS);
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