/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:40:52 by nammari           #+#    #+#             */
/*   Updated: 2022/01/25 10:51:30 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

void	init_vectors(t_data *data)
{
	get_player_pos(&data);
	data->plane_vect[X] = 0;
	data->plane_vect[Y] = 0.66;
	data->dir_vect[X] = -1;
	data->dir_vect[Y] = 0;
}

int	create_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ERROR);
	data->win = mlx_new_window(data->mlx, 800, 600, "Welcome to CUB3D !");
	if (!data->win)
	{
		free(data->mlx);
		return (ERROR);
	}
	init_vectors(data);
	while (1)
		;
	//mlx_loop_hook(data->mlx, NULL, data);
	mlx_loop(data->mlx);
	return (1);
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