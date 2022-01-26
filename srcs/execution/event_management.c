/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:14:35 by noufel            #+#    #+#             */
/*   Updated: 2022/01/26 20:37:30 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	get_hook(int keyhook, t_data *data)
{
	if (keyhook == 'w' || keyhook == 's' || keyhook == 'a' || keyhook == 'd')
		return (move_player(keyhook, data));
	else if (keyhook == 65307)
		close_win(data);
	return (1);
}
