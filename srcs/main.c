/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/23 13:02:34 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_param	*cub_file_parser(int ac, char **av)
{
	int	fd;

	if (ac == 2)
	{
		if (is_cub_file(av[1]))
		{
			if (are_params_ok(av[1], &fd) != ERROR)
			{
				if (is_map_ok(fd))
				{
					ft_get_next_line(0, NULL, 1);
					return (init_param(av[1]));
				}
				ft_putstr_fd("Error\nMap error\n", 2);
			}
			else
				ft_putstr_fd("Error\nParams error\n", 2);
		}
		else
			ft_putstr_fd("Error\nFile is not .cub file\n", 2);
	}
	ft_get_next_line(0, NULL, 1);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_param	*param;

	param = cub_file_parser(ac, av);
	if (!param)
	{
		return (KO);
	}
	printf("map is OK !\n");
	return (OK);
}
