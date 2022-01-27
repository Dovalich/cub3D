/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:13:31 by noufel            #+#    #+#             */
/*   Updated: 2022/01/27 12:05:53 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

int	create_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ERROR);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Welcome to CUB3D !");
	if (!data->win)
		return (ERROR);
	init_vectors(data, &data->player);
	init_textures(data, data->param);
	game_loop(data);
	mlx_loop_hook(data->mlx, NULL, data);
	mlx_hook(data->win, 3, 1L << 1, &get_hook, data);
	mlx_hook(data->win, 17, 1L << 17, &close_win, data);
	// mlx_hook(data->win, 12, 1L << 15, &resize_func, data);
	mlx_loop(data->mlx);
	return (SUCCESS);
}

void	init_vectors(t_data *data, t_player *player)
{
	init_player_pos(data->map, player);
	data->plane[X] = 0;
	data->plane[Y] = 0.66;
	player->dir[X] = 1;
	player->dir[Y] = 0;
}

void	init_textures(t_data *data, t_param *param)
{
	param->no.pixels = mlx_xpm_file_to_image(data->mlx,\
				param->tex_no, &param->no.x, &(param->no.y));
	param->we.pixels = mlx_xpm_file_to_image(data->mlx,\
				param->tex_we, &param->we.x, &param->we.y);
	param->ea.pixels = mlx_xpm_file_to_image(data->mlx,\
				param->tex_ea, &param->ea.x, &param->ea.y);
	param->so.pixels = mlx_xpm_file_to_image(data->mlx,\
				param->tex_so, &param->so.x, &param->so.y);
	if (!param->ea.pixels || !param->no.pixels ||\
		!param->so.pixels || !param->we.pixels)
	{
		//printf will be deleted and replaced with proper error fun
		printf("Init texture failed\n");
		exit_clean(MLX_FAIL, 0, NULL, NULL);
	}
}

void	init_player_pos(char **map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr(PLAYER_CHAR, map[y][x]) != NULL)
			{
				player->pos[X] = x;
				player->pos[Y] = y;
				return ;
			}
			++x;
		}
		++y;
	}
}
