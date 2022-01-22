/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:01:31 by twagner           #+#    #+#             */
/*   Updated: 2022/01/22 10:35:33 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_controller(int fd)
{
	int		ret;
	char	*line;
	char	map_checker;

	map_checker = 0;
	ret = ft_get_next_line(fd, &line, 0);
	while (ret >= 0)
	{
		/*if (line is valid)
		{
			map_checker = map_checker | line_code(line);
			ret = map_checker ^ 63;
		}
		else
			ret = ERROR;*/
		printf("line : %s\n", line);
		free(line);
		line = NULL;
		if (ret == 0 || ret == ERROR)
			break ;
		ret = ft_get_next_line(fd, &line, 0);
	}
	if (ret == ERROR)
		return (ERROR);
	return (OK);
}

