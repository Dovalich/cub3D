/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/28 18:20:40 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "game.h"

int	game_launch(t_data *data)
{
	display_frame(data);
	mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->win, 2, 1L << 0, &capture_keyhook, data);
	mlx_hook(data->win, 6, 1L << 6, &capture_mousehook, data);
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
