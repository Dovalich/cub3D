/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/27 15:24:48 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "game.h"

int	game_launch(t_data *data)
{
	display_frame(data);
	mlx_hook(data->win, 3, 1L << 1, &capture_keyhook, data);
	mlx_hook(data->win, 17, 1L << 17, &close_win, data);
	mlx_loop(data->mlx);
	//mlx_hook(data->win, 12, 1L << 15, &resize_func, data);	
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
