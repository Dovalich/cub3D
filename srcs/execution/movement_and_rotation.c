/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_and_rotation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:14:35 by noufel            #+#    #+#             */
/*   Updated: 2022/01/28 22:48:55 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "game_control.h"

void	rotate_player(int rotation, t_data *data, t_player *player)
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

static void	get_new_position(double *new_x, double *new_y, int move,
								t_data *data)
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

static bool	is_collision(t_data *data, int move, double new_x, double new_y)
{
	double	w;
	double	h;

	(void)move;
	w = data->param->width;
	h = data->param->height;
	if (!(new_x < w && new_y < h && new_x >= 0 && new_y >= 0
			&& data->param->map[(int)(new_y)][(int)(new_x)] != '1'))
	{
		return (true);
	}
	return (false);
}

bool	move_player(int keyhook, t_data *data, t_player *player)
{
	double	new_x;
	double	new_y;

	if (!BONUS && (keyhook == ROTATE_LEFT || keyhook == ROTATE_RIGHT))
	{
		rotate_player(keyhook, data, player);
		return (true);
	}
	get_new_position(&new_x, &new_y, keyhook, data);
	if (is_collision(data, keyhook, new_x, new_y) == false)
	{
		player->pos[X] = new_x;
		player->pos[Y] = new_y;
		return (true);
	}
	return (false);
}
