/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:48:01 by twagner           #+#    #+#             */
/*   Updated: 2022/01/24 11:29:35 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_file_name(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (false);
	while (line[i])
	{
		if (line[i] == '\\')
			return (false);
		++i;
		if (line[i] == ' ')
			break ;
	}
	while (line[i] == ' ')
		++i;
	if (line[i] == '\0')
		return (true);
	return (false);
}

static bool	is_texture_file_valid(char *line)
{
	int		i;
	int		fd;
	char	*file_name;

	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		i = 3;
		while (line[i] == ' ')
			++i;
		if (!is_valid_file_name(line + i))
			return (false);
		file_name = ft_get_trimed_right(line + i);
		if (file_name == NULL)
			return (false);
		fd = open(file_name, O_RDONLY);
		if (fd == ERROR)
			return (false);
		free(file_name);
		close(fd);
		return (true);
	}
	else
		return (false);
}

static bool	is_color_valid(char *line)
{
	int		i;
	int		value;
	int		ret;
	char	**color;

	ret = true;
	color = NULL;
	i = -1;
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		color = ft_split(line + 2, ',');
		if (!color || (color && color[0] && color[1] && color[2] && color[3]))
			return (false);
		while (++i < 3 && color[i])
		{
			value = ft_atoi(color[i]);
			if (ft_strchr(color[i], '-') || value < 0 || value > 255)
				ret = false;
		}
	}
	if (i == -1 || (i > 0 && i != 3))
		ret = false;
	free_two_d_array(color);
	return (ret);
}

bool	is_valid_parameter(char *line, char param_counter, char code)
{
	if (code != 0 && (param_counter & code) != 0)
		return (false);
	else if (code == 0)
		return (true);
	else if (is_texture_file_valid(line))
		return (true);
	else if (is_color_valid(line))
		return (true);
	else
		return (false);
}

/* Legacy function -> Will delete after talking with Thomas.

int	param_controller(int fd)
{
	int		ret;
	char	*line;
	char	param_checker;

	param_checker = 0;
	ret = ft_get_next_line(fd, &line, 0);
	while (ret > 0)
	{
		if (line_param_code(line) >= 0 && is_file_valid(line)
			&& is_color_valid(line))
		{
			param_checker = param_checker | line_param_code(line);
			ret = param_checker ^ 63;
		}
		else
			ret = ERROR;
		free(line);
		line = NULL;
		if (ret == 0 || ret == ERROR)
			break ;
		ret = ft_get_next_line(fd, &line, 0);
	}
	if (ret == ERROR)
		return (ERROR);
	return (OK);
}*/
