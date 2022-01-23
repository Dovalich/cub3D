/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/23 15:13:39 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int cub_file_parser(char **av, t_param *param)
{
	int	fd;

	if (is_cub_file(av[1]))
	{
		if (are_params_ok(av[1], &fd))
		{
			if (is_map_ok(fd))
			{
				init_param(av[1], param);
				return (SUCCESS);
			}
			else
				exit_error_clean(MAP_ERROR, 0, NULL);
		}
		else
			exit_error_clean(PARAM_ERROR, 0, NULL);
	}
	exit_error_clean(FILE_ERROR, 0, NULL);
	return (ERROR);
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
