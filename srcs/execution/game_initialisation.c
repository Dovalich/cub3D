/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:13:31 by noufel            #+#    #+#             */
/*   Updated: 2022/01/27 14:56:15 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

static void	init_textures(t_data *data, t_param *param)
{
	param->no.img = mlx_xpm_file_to_image(data->mlx,\
				param->tex_no_path, &(param->no.x), &(param->no.y));
	param->we.img = mlx_xpm_file_to_image(data->mlx,\
				param->tex_we_path, &param->we.x, &param->we.y);
	param->ea.img = mlx_xpm_file_to_image(data->mlx,\
				param->tex_ea_path, &param->ea.x, &param->ea.y);
	param->so.img = mlx_xpm_file_to_image(data->mlx,\
				param->tex_so_path, &param->so.x, &param->so.y);
	if (!param->ea.img || !param->no.img ||\
		!param->so.img || !param->we.img)
	{
		ft_putstr_fd("Init texture failed\n", 2);
		exit_program(data, MLX_FAIL);
	}
}

static void	init_player_pos(char **map, t_player *player)
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

void	game_init(t_data *data, t_param *param)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_clean(MLX_FAIL, 0, NULL, param);
	data->win = mlx_new_window(data->mlx,\
			SCREEN_WIDTH, SCREEN_HEIGHT, "Welcome to CUB3D !");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit_clean(MLX_FAIL, 0, NULL, param);
	}
	data->plane[X] = 0;
	data->plane[Y] = 0.66;
	data->player.dir[X] = 1;
	data->player.dir[Y] = 0;
	init_player_pos(param->map, &data->player);
	init_textures(data, param);
}
