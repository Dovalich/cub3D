/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:03:50 by twagner           #+#    #+#             */
/*   Updated: 2022/01/26 20:36:59 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	line_param_code(char *line)
{
	if (ft_strlen(line) == 0)
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
		return (NO_TEXTURE_CODE);
	if (!ft_strncmp(line, "SO ", 3))
		return (SO_TEXTURE_CODE);
	if (!ft_strncmp(line, "WE ", 3))
		return (WE_TEXTURE_CODE);
	if (!ft_strncmp(line, "EA ", 3))
		return (EA_TEXTURE_CODE);
	if (!ft_strncmp(line, "F ", 2))
		return (F_COLOR_CODE);
	if (!ft_strncmp(line, "C ", 2))
		return (C_COLOR_CODE);
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
		if (param_counter == ALL_PARAMS_ARE_SET)
			return (true);
	}
	free(line);
	return (false);
}

bool	is_map_ok(int fd, int *longest_map_width, int *map_height)
{
	if (map_controller(fd, longest_map_width, map_height) == ERROR)
	{
		return (false);
	}
	free_gnl_buffer();
	close(fd);
	return (true);
}

void	cub_file_parser(char **av, t_param *param)
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
	init_param(av[1], param, longest_map_width, map_height);
	param->width = longest_map_width;
	param->height = map_height;
}
