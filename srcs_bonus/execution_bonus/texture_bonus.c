/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:35:41 by twagner           #+#    #+#             */
/*   Updated: 2022/01/28 15:17:00 by twagner          ###   ########.fr       */
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

int	get_texture_column(t_texture *texture, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * (double)texture->x);
	if (ray->side == 0 && ray->dir[X] > 0)
		tex_x = texture->x - tex_x -1;
	if (ray->side == 1 && ray->dir[Y] < 0)
		tex_x = texture->x - tex_x - 1;
	return (tex_x);
}

void	draw_texel(t_img_data *frame, t_texel *texel, int x, int y)
{
	texel->tex_y = (int)texel->tex_pos & (texel->texture->y - 1);
	texel->color = \
		((int *)texel->texture->tex.addr)[(texel->texture->tex.line_len / 4) \
			* texel->tex_y + texel->tex_x];
	ft_img_pixel_put(frame, x, y, texel->color);
}
