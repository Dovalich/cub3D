/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:03:50 by twagner           #+#    #+#             */
/*   Updated: 2022/01/24 11:02:52 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_param_code(char *line)
{
	if (ft_strlen(line) == 0)
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
		return (32);
	if (!ft_strncmp(line, "SO ", 3))
		return (16);
	if (!ft_strncmp(line, "WE ", 3))
		return (8);
	if (!ft_strncmp(line, "EA ", 3))
		return (4);
	if (!ft_strncmp(line, "F ", 2))
		return (2);
	if (!ft_strncmp(line, "C ", 2))
		return (1);
	return (ERROR);
}

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


bool	are_parameters_ok(int fd)
{
	char	*line;
	char	param_counter;
	char	code;
	int		ret;

	param_counter = 0;
	code = 0;
	ret = 1;
	while (ret > 0)
	{
		ret = ft_get_next_line(fd, &line, 0);
		code = line_param_code(line);
		if (!is_valid_parameter(line, param_counter, code))
			break ;
		free(line);
		if (code != 0)
			param_counter = param_counter | code;
		if (param_counter == 63)
			return (true);
	}
	free(line);
	return (false);
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
