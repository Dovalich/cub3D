/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/23 16:00:21 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_file_parser(char **av, t_param *param)
{
	int	fd;

	if (!is_cub_file(av[1]))
	{
		exit_clean(FILE_ERROR, 0, NULL);	
	}
	if (!are_params_ok(av[1], &fd))
	{
		exit_clean(PARAM_ERROR, fd, NULL);
	}
	if (!is_map_ok(fd))
	{
		exit_clean(MAP_ERROR, fd, NULL);
	}
	init_param(av[1], param);
}

int	main(int ac, char **av)
{
	t_param	*param;

	if (ac != 2)
		return (KO);
	param = NULL;
	cub_file_parser(av, param);
	printf("map is OK !\n");
	return (SUCCESS);
}
