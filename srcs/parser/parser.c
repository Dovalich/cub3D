/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:03:50 by twagner           #+#    #+#             */
/*   Updated: 2022/01/23 16:03:59 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_cub_file(char *file)
{
	int	dot_pos;

	dot_pos = ft_strchr_index(file, '.', -1);
	if (dot_pos == ERROR)
		return (false);
	else
	{	
		if ((ft_strcmp(file + dot_pos, ".cub")) == 0 \
			&& (dot_pos != 0) \
			&& (*(file + dot_pos - 1) != '/'))
			return (true);
		else
				
			return (false);
	}
	return (true);
}

bool	are_params_ok(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd == ERROR)
		return (false);
	if (param_controller(*fd) == ERROR)
		return (false);
	return (true);
}

bool	is_map_ok(int fd)
{
	if (map_controller(fd) == ERROR)
	{
		return (false);
	}
	free_gnl_buffer();
	close(fd);
	return (true);
}
