/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/25 15:16:38 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "execution.h"


// Longest map width helps us malloc the right size <-->
// Map height helps us malloc enough blocks map[height][width]
// I put them here to avoid opening the file again just to count the lines



static void	cub_file_parser(char **av, t_param **param)
{
	int	fd;
	int	longest_map_width;
	int	map_height;

	if (!is_cub_file(av[1]))
	{
		exit_clean(FILE_ERROR, 0, NULL, NULL);	
	}
	fd = open(av[1], O_RDONLY);
	if ((fd == ERROR) || !are_parameters_ok(fd))
	{
		exit_clean(PARAM_ERROR, fd, NULL, NULL);
	}
	if (!is_map_ok(fd, &longest_map_width, &map_height))
	{
		exit_clean(MAP_ERROR, fd, NULL, NULL);
	}
	*param = malloc(sizeof(**param));
	if (!*param)
		exit_clean(MALLOC_FAIL, fd, NULL, NULL);
	init_param(av[1], *param, longest_map_width, map_height);
	(*param)->width = longest_map_width;
	(*param)->height = map_height;
}

int	main(int ac, char **av, char **envp)
{
	t_param	*param;
	t_data	data;

	if (ac != 2 || !envp || !*envp)
		return (ERROR);
	param = NULL;
	cub_file_parser(av, &param);
	print_param(param);
	print_map(param);
	data.param = param;
	data.map = param->map;
	printf("map is OK !\n");
	if (create_window(&data))
	{
		printf("Error with window creation\n");
		return (ERROR);
	}
	// int fd = open(av[1], O_RDONLY);
	// printf("this is the value of fd %d and the name of the file |%s|\n", fd, av[1]);
	// close(fd);
	free_param(param);
	return (SUCCESS);
}
