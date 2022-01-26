/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:13:31 by noufel            #+#    #+#             */
/*   Updated: 2022/01/26 20:37:30 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

int	create_window(t_data *data)
{
	data->key_was_pressed = true;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ERROR);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Welcome to CUB3D !");
	if (!data->win)
		return (ERROR);
	init_vectors(data);
	init_textures(data);
	game_loop(data);
	mlx_loop_hook(data->mlx, NULL, data);
	mlx_hook(data->win, 3, 1L << 1, &get_hook, data);
	mlx_hook(data->win, 17, 1L << 17, &close_win, data);
	// mlx_hook(data->win, 12, 1L << 15, &resize_func, data);
	mlx_loop(data->mlx);
	return (SUCCESS);
}

void	init_vectors(t_data *data)
{
	get_player_pos(data);
	data->plane[X] = 0;
	data->plane[Y] = 0.66;
	data->dir[X] = 1;
	data->dir[Y] = 0;
}

void	init_textures(t_data *data)
{
	data->no.pixels = mlx_xpm_file_to_image(data->mlx,\
				data->param->tex_no, &data->no.x, &data->no.y);
	data->we.pixels = mlx_xpm_file_to_image(data->mlx,\
				data->param->tex_we, &data->we.x, &data->we.y);
	data->ea.pixels = mlx_xpm_file_to_image(data->mlx,\
				data->param->tex_ea, &data->ea.x, &data->ea.y);
	data->so.pixels = mlx_xpm_file_to_image(data->mlx,\
				data->param->tex_so, &data->so.x, &data->so.y);
	if (!data->ea.pixels || !data->no.pixels ||\
		!data->so.pixels || !data->we.pixels)
	{
		//printf will be deleted and replaced with proper error fun
		printf("Init texture failed\n");
		exit_clean(MLX_FAIL, 0, NULL, NULL);
	}
}

void	get_player_pos(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr(PLAYER_CHAR, data->map[y][x]) != NULL)
			{
				data->pos[X] = x;
				data->pos[Y] = y;
				return ;
			}
			++x;
		}
		++y;
	}
}
