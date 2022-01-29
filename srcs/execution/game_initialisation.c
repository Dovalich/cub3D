/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:13:31 by noufel            #+#    #+#             */
/*   Updated: 2022/01/29 09:40:29 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	init_textures_detail(t_data *data, t_param *param)
{
	param->no.tex.addr = mlx_get_data_addr(param->no.tex.img, \
		&param->no.tex.bpp, &param->no.tex.line_len, &param->no.tex.endian);
	param->we.tex.addr = mlx_get_data_addr(param->we.tex.img, \
		&param->we.tex.bpp, &param->we.tex.line_len, &param->we.tex.endian);
	param->ea.tex.addr = mlx_get_data_addr(param->ea.tex.img, \
		&param->ea.tex.bpp, &param->ea.tex.line_len, &param->ea.tex.endian);
	param->so.tex.addr = mlx_get_data_addr(param->so.tex.img, \
		&param->so.tex.bpp, &param->so.tex.line_len, &param->so.tex.endian);
	if (!param->ea.tex.addr || !param->no.tex.addr
		|| !param->so.tex.addr || !param->we.tex.addr)
	{
		ft_putstr_fd("Init texture failed\n", 2);
		exit_program(data, MLX_FAIL);
	}
}

static void	init_textures(t_data *data, t_param *param)
{
	param->no.tex.img = mlx_xpm_file_to_image(data->mlx,
			param->tex_no_path, &(param->no.x), &(param->no.y));
	param->we.tex.img = mlx_xpm_file_to_image(data->mlx,
			param->tex_we_path, &param->we.x, &param->we.y);
	param->ea.tex.img = mlx_xpm_file_to_image(data->mlx,
			param->tex_ea_path, &param->ea.x, &param->ea.y);
	param->so.tex.img = mlx_xpm_file_to_image(data->mlx,
			param->tex_so_path, &param->so.x, &param->so.y);
	if (!param->ea.tex.img || !param->no.tex.img
		|| !param->so.tex.img || !param->we.tex.img)
	{
		ft_putstr_fd("Init texture failed\n", 2);
		exit_program(data, MLX_FAIL);
	}
	init_textures_detail(data, param);
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
				player->pos[X] = x + 0.5;
				player->pos[Y] = y + 0.5;
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
	data->win = mlx_new_window(data->mlx,
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
