/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:14:35 by noufel            #+#    #+#             */
/*   Updated: 2022/01/27 13:53:41 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "game_controle.h"

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

void	move_player(int keyhook, t_data *data, t_player *player)
{
	if (keyhook == ROTATE_LEFT || keyhook == ROTATE_RIGHT)
	{
		rotate_player(keyhook, data, player);
		return ;
	}
	if (keyhook == MOVE_FORWARD)
	{
		player->pos[X] += player->dir[X] * MOVE_SPEED;
		player->pos[Y] += player->dir[Y] * MOVE_SPEED;
	}
	else if (keyhook == MOVE_BACK)
	{
		player->pos[X] -= player->dir[X] * MOVE_SPEED;
		player->pos[Y] -= player->dir[Y] * MOVE_SPEED;
	}
	else if (keyhook == MOVE_LEFT)
	{
		player->pos[X] -= data->plane[X] * MOVE_SPEED;
		player->pos[Y] -= data->plane[Y] * MOVE_SPEED;	
	}
	else if (keyhook == MOVE_RIGHT)
	{
		player->pos[X] += data->plane[X] * MOVE_SPEED;
		player->pos[Y] += data->plane[Y] * MOVE_SPEED;	
	}
}

static bool	movement_key_pressed(int keyhook)
{
	if (keyhook == MOVE_BACK || keyhook == MOVE_FORWARD\
		|| keyhook == MOVE_LEFT || keyhook == MOVE_RIGHT\
		|| keyhook == ROTATE_LEFT || keyhook || ROTATE_RIGHT)
		return (true);
	return (false);
}	

int	capture_keyhook(int keyhook, t_data *data)
{
	printf("this is keyhook %d\n", keyhook);
	if (movement_key_pressed(keyhook))
	{
		move_player(keyhook, data, &data->player);
		draw_frame(data);
	}
	else if (keyhook == KILL_PROGRAM)
	{
		printf("kill prog\n");
		close_win(data);
	}
	return (SUCCESS);
}
