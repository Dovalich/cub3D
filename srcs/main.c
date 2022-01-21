/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/21 11:15:55 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_param	*cub_file_parser(int ac, char **av)
{
	if (ac == 2)
	{
		if (is_cub_file(av[1]))
		{
			if (are_params_ok(av[1]))
			{
				if (is_map_ok(av[1]))
					return (init_param(av[1]));
				ft_putstr_fd("Error\nMap error\n", 2);
			}
			else
				ft_putstr_fd("Error\nParams error\n", 2);
		}
		else
			ft_putstr_fd("Error\nFile is not .cub file\n", 2);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_param	*param;

	param = cub_file_parser(ac, av);
	if (param)
	{
		printf("map is OK !\n");
		return (OK);
	}
	return (KO);
}
