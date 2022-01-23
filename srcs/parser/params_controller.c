/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:48:01 by twagner           #+#    #+#             */
/*   Updated: 2022/01/23 19:39:11 by nammari          ###   ########.fr       */
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

static bool	is_file_valid(char *line)
{
	int		i;
	int		fd;
	char	*file;

	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		i = 3;
		while (line[i] == ' ')
			++i;
		file = ft_strdup(line + i);
		if (!file)
			return (false);
		fd = open(file, O_RDONLY);
		free(file);
		if (fd == ERROR)
			return (false);
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
	if (i > 0 && i != 3)
		ret = false;
	free_two_d_array(color);
	return (ret);
}

bool	are_texture_param_ok(int fd, char *param_bit_counter, char **line)
{
	int		ret;
	char	code_bits;
	
	ret = ft_get_next_line(fd, line, 0);
	while (ret > 0)
	{
		code_bits = line_param_code(*line);
		if (code_bits == ERROR || (code_bits & *param_bit_counter) != 0)
			return(false);
		else if (code_bits <= 4 && *param_bit_counter == 60)
			return (true);
		else if (code_bits != 0 && is_file_valid(*line))
			*param_bit_counter = code_bits | *param_bit_counter;
		else if (code_bits != 0)
			return (false);
		free(*line);
		ret = ft_get_next_line(fd, line, 0);
	}
	return (false);
}

bool	are_color_param_ok(int fd, char *param_bit_counter, char **line)
{
	int		ret;
	char	code_bits;

	ret = 1;
	while (ret > 0)
	{
		code_bits = line_param_code(*line);
		if (code_bits == ERROR || (code_bits & *param_bit_counter) != 0)
			return (false);
		else if (*param_bit_counter == 63)
		{
			return (true);
		}
		else if (code_bits != 0 && is_color_valid(*line) == false)
		{
			return (false);
		}
		else if (code_bits != 0)
			*param_bit_counter = *param_bit_counter | code_bits;
		free(*line);
		ret = ft_get_next_line(fd, line, 0);
	}
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
