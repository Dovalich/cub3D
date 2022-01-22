/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:03:50 by twagner           #+#    #+#             */
/*   Updated: 2022/01/22 10:35:06 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub_file(char *file)
{
	int	dot_pos;

	dot_pos = ft_strchr_index(file, '.', -1);
	if (dot_pos == ERROR)
		return (NO);
	else
	{	
		if ((ft_strcmp(file + dot_pos, ".cub")) == 0 \
			&& (dot_pos != 0) \
			&& (*(file + dot_pos - 1) != '/'))
			return (YES);
		else
			return (NO);
	}
}

int	are_params_ok(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd == ERROR)
		return (ERROR);
	if (param_controller(*fd) == ERROR)
	{
		close(*fd);
		return (NO);
	}
	return (YES);
}

int	is_map_ok(int fd)
{
	if (map_controller(fd) == ERROR)
	{
		close(fd);
		return (NO);
	}
	close(fd);
	return (YES);
}

t_param	*init_param(char *file)
{
	(void)file;
	return (NULL);
}
