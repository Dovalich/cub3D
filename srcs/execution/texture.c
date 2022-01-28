/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:35:41 by twagner           #+#    #+#             */
/*   Updated: 2022/01/28 12:28:08 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_texture	*get_texture(t_ray ray, t_data *data)
{
	if (ray.side == 1)
	{
		if (ray.dir[Y] >= 0)
			return (&data->param->no);
		else if (ray.dir[Y] < 0)
			return (&data->param->so);
	}
	if (ray.side == 0)
	{
		if (ray.dir[X] >= 0)
			return (&data->param->ea);
		else if (ray.dir[X] < 0)
			return (&data->param->we);
	}
	return (NULL);
}
