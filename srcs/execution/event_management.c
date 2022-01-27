/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:14:35 by noufel            #+#    #+#             */
/*   Updated: 2022/01/27 17:17:55 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "game_controle.h"

static void	rotate_player(int rotation, t_data *data, t_player *player)
{
	t_vector	old_plane;
	t_vector	old_dir;
	double		rt;
	
	rt = ROT_SPEED;
	if (rotation == ROTATE_LEFT)
	{
		old_dir[X] = player->dir[X];
		player->dir[X] = player->dir[X] * cos(-rt) - player->dir[Y] * sin(-rt);	
		player->dir[Y] = old_dir[X] * sin(-rt) + player->dir[Y] * cos(-rt);
		old_plane[X] = data->plane[X];
		data->plane[X] = data->plane[X] * cos(-rt) - data->plane[Y] * sin(-rt);
		data->plane[Y] = old_plane[X] * sin(-rt) + data->plane[Y] * cos(-rt);
	}
	else if (rotation == ROTATE_RIGHT)
	{
		old_dir[X] = player->dir[X];
		player->dir[X] = player->dir[X] * cos(rt) - player->dir[Y] * sin(rt);	
		player->dir[Y] = old_dir[X] * sin(rt) + player->dir[Y] * cos(rt);
		old_plane[X] = data->plane[X];
		data->plane[X] = data->plane[X] * cos(rt) - data->plane[Y] * sin(rt);
		data->plane[Y] = old_plane[X] * sin(rt) + data->plane[Y] * cos(rt);
	}
}

static void	print_map_pos(t_param *param, double pos_x, double pos_y)
{
	int	y;
	int x;

	y = 0;
	while (param->map[y])
	{
		x = 0;
		while (param->map[y][x])
		{
			if (x == (int)pos_x && y == (int)pos_y)
				printf("P");
			else
				printf("%c", param->map[y][x]);
			++x;
		}
		printf("\n");
		++y;
	}
}

void	get_new_position(double *new_x, double *new_y, int move, t_data *data)
{
	t_player	player;

	player = data->player;
	if (move == MOVE_FORWARD)
	{
		*new_x = player.pos[X] + player.dir[X] * MOVE_SPEED;
		*new_y = player.pos[Y] + player.dir[Y] * MOVE_SPEED;
	}
	else if (move == MOVE_BACK)
	{
		*new_x = player.pos[X] - player.dir[X] * MOVE_SPEED;
		*new_y = player.pos[Y] - player.dir[Y] * MOVE_SPEED;
	}
	else if (move == MOVE_LEFT)
	{
		*new_x = player.pos[X] - data->plane[X] * MOVE_SPEED;
		*new_y = player.pos[Y] - data->plane[Y] * MOVE_SPEED;	
	}
	else if (move == MOVE_RIGHT)
	{
		*new_x = player.pos[X] + data->plane[X] * MOVE_SPEED;
		*new_y = player.pos[Y] + data->plane[Y] * MOVE_SPEED;	
	}
}

void	update_collision_offset(int move, double *new_x, double *new_y, t_data *data)
{
	if (move == MOVE_FORWARD)
	{
		*new_x += data->player.dir[X];
		*new_y += data->player.dir[Y];
	}
	else if (move == MOVE_RIGHT)
	{
		*new_x += data->plane[X];
		*new_y += data->plane[Y];	
	}
	else if (move == MOVE_BACK)
	{
		*new_x -= data->player.dir[X];
		*new_y -= data->player.dir[Y];
	}
	else if (move == MOVE_LEFT)
	{
		*new_x -= data->plane[X];
		*new_y -= data->plane[Y];
	}
}

static bool	is_colision(t_data *data, int move, double new_x, double new_y)
{
	double w;
	double h;

	w = data->param->width;
	h = data->param->height;
	update_collision_offset(move, &new_x, &new_y, data);
	if (new_x < w && new_y < h && new_x >= 0 && new_y >= 0
			&& data->param->map[(int)(new_y)][(int)(new_x)] != '1')
			{
				return (false);
			}
	return (true);
}

static void	move_player(int keyhook, t_data *data, t_player *player)
{
	double	new_x;
	double	new_y;

	if (keyhook == ROTATE_LEFT || keyhook == ROTATE_RIGHT)
	{
		rotate_player(keyhook, data, player);
		return ;
	}
	get_new_position(&new_x, &new_y, keyhook, data);
	if (is_colision(data, keyhook, new_x, new_y) == false)
	{
		print_map_pos(data->param, new_x, new_y);
		printf("this is player dir X %lf and Y %lf\n", player->dir[X], player->dir[Y]);
		printf("this is plane dir X %lf and Y %lf\n", data->plane[X], data->plane[Y]);
		player->pos[X] = new_x;
		player->pos[Y] = new_y;
	}
}


static bool	movement_key_pressed(int keyhook)
{
	if (keyhook == MOVE_BACK || keyhook == MOVE_FORWARD\
		|| keyhook == MOVE_LEFT || keyhook == MOVE_RIGHT\
		|| keyhook == ROTATE_LEFT || keyhook == ROTATE_RIGHT)
		return (true);
	return (false);
}	

int	capture_keyhook(int keyhook, t_data *data)
{
	if (movement_key_pressed(keyhook))
	{
		move_player(keyhook, data, &data->player);
		display_frame(data);
	}
	else if (keyhook == KILL_PROGRAM)
	{
		exit_program(data, KILL_PROGRAM);
	}
	return (SUCCESS);
}
