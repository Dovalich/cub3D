/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/27 12:03:08 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "game.h"

int	main(int ac, char **av, char **envp)
{
	t_param	param;
	t_data	data;

	if (ac != 2 || !envp || !*envp)
		return (ERROR);
	ft_bzero(&param, sizeof(param));
	ft_bzero(&data, sizeof(data));
	cub_file_parser(av, &param);
	data.param = &param;
	data.map = param.map;
	printf("map is OK !\n");
	if (create_window(&data))
	{
		printf("Error with window creation\n");
		return (ERROR);
	}
	return (SUCCESS);
}
