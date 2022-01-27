/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:48:01 by twagner           #+#    #+#             */
/*   Updated: 2022/01/27 18:45:39 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		file_name = ft_get_trimed_right(line + i);
		if (file_name == NULL)
			return (false);
		fd = open(file_name, O_RDONLY);
		free(file_name);
		if (fd == ERROR)
			return (false);
		close(fd);
		return (true);
	}
	else
		return (false);
}

static bool	are_digits_and_two_colons_only(char *line)
{
	int	i;
	int	nb_colon;

	i = 0;
	nb_colon = 0;
	if (!line || !line[i])
		return (false);
	while (line[i])
	{
		if (line[i] == ',')
			++nb_colon;
		else if (line[i] && !ft_is_space(line[i]) && !ft_isdigit(line[i]))
			return (false);
		++i;
	}
	if (nb_colon != 2)
		return (false);
	return (true);
}

static bool	are_num_valid(char **num)
{
	int	i;
	int	j;
	int	value;

	i = 0;
	while (num[i] && i < 3)
	{
		j = 0;
		while (ft_is_space(num[i][j]))
			++j;
		while (num[i][j] && ft_isdigit(num[i][j]))
			++j;
		value = ft_atoi(num[i]);
		if (value > 255 || value < 0)
			return (false);
		++i;
	}
	if (num[i] != NULL || i < 3)
		return (false);
	return (true);
}

static bool	is_color_valid(char *line)
{
	char	**color;

	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		if (line && (line + 1) && (line + 2))
			line += 2;
		else
			return (false);
		if (!are_digits_and_two_colons_only(line))
			return (false);
		color = ft_split(line, ',');
		if (!color || !are_num_valid(color))
		{
			free_two_d_array(color);
			return (false);
		}
		free_two_d_array(color);
		return (true);
	}
	return (false);
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
