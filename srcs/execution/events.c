/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:29:15 by noufel            #+#    #+#             */
/*   Updated: 2022/01/27 18:42:31 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "game_controle.h"

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
