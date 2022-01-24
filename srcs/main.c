/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/24 14:04:08 by noufel           ###   ########.fr       */
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
	fd = open(av[1], O_RDONLY);
	if ((fd == ERROR) || !are_parameters_ok(fd))
	{
		exit_clean(PARAM_ERROR, fd, NULL);
	}
	if (!is_map_ok(fd))
	{
		exit_clean(MAP_ERROR, fd, NULL);
	}
	init_param(av[1], param);
}

int	main(int ac, char **av, char **envp)
{
	t_param	*param;

	if (ac != 2 || !envp || !*envp)
		return (ERROR);
	param = NULL;
	cub_file_parser(av, param);
	// int fd = open(av[1], O_RDONLY);
	// printf("this is the value of fd %d and the name of the file |%s|\n", fd, av[1]);
	// close(fd);
	printf("map is OK !\n");
	return (SUCCESS);
}
