/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:35:41 by twagner           #+#    #+#             */
/*   Updated: 2022/01/28 10:56:05 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (ray.dir[X] < 0)
			return (&data->param->we);
	}
}
