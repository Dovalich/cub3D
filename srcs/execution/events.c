/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:29:15 by noufel            #+#    #+#             */
/*   Updated: 2022/01/28 18:55:26 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "game_control.h"

static bool	movement_key_pressed(int keyhook)
{
	if (keyhook == MOVE_BACK || keyhook == MOVE_FORWARD
		|| keyhook == MOVE_LEFT || keyhook == MOVE_RIGHT
		|| keyhook == ROTATE_LEFT || keyhook == ROTATE_RIGHT)
		return (true);
	return (false);
}	

// In order to save resources we will call our raycaster
// And draw the frame only if the user pressed a button
// to move the player and only if the player moved.
// If the player didn't move nor rotate it doesn't
// make sense to display a new image

int	capture_keyhook(int keyhook, t_data *data)
{
	if (movement_key_pressed(keyhook))
	{
		if (move_player(keyhook, data, &data->player))
			display_frame(data);
	}
	else if (keyhook == KILL_PROGRAM)
	{
		exit_program(data, KILL_PROGRAM);
	}
	return (SUCCESS);
}

int	capture_mousehook(int mouse_x, int mouse_y, t_data *data)
{
	static int	mouse_old_x = SCREEN_WIDTH / 2;
	int			direction;
	int			rot_speed;
	
	(void)mouse_y;
	direction = 0;
	rot_speed = 1;
	if (mouse_x - mouse_old_x > 0)
	{
		direction = ROTATE_RIGHT;
	}
	else if (mouse_x - mouse_old_x < 0)
	{
		direction = ROTATE_LEFT;
	}
	if (direction)
	{
		rotate_player(direction, data, &data->player, rot_speed);
		display_frame(data);
	}
	mouse_old_x = mouse_x;
	return (SUCCESS);
}

int	handle_resize(int keyhook, t_data *data)
{
	(void)keyhook;
	display_frame(data);
	return (SUCCESS);
}
