/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/28 22:28:21 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "game.h"

int	game_launch(t_data *data)
{
	display_frame(data);
	mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->win, 2, 1L << 0, &capture_keyhook, data);
	mlx_loop_hook(data->mlx, &capture_mouse_move, data);
	mlx_hook(data->win, 17, 1L << 17, &close_win, data);
	mlx_loop(data->mlx);
	mlx_hook(data->win, 12, 1L << 15, &handle_resize, data);
	return (SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	t_param	param;
	t_data	data;

	if (ac != 2 || !envp || !*envp)
		return (ERROR);
	ft_bzero(&param, sizeof(param));
	ft_bzero(&data, sizeof(data));
	cub_file_parser(av, &param);
	print_param(&param);
	data.param = &param;
	printf("map is OK !\n");
	game_init(&data, &param);
	game_launch(&data);
	return (SUCCESS);
}
