/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:48:01 by twagner           #+#    #+#             */
/*   Updated: 2022/01/21 15:22:08 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check line
// Si XX<space> ou X<space> > regarder ce aqu'il y a apres et essayer de l'open > Si open = -1 > Error, sinon close et ok
// Si vide ou 11 ou EOF > Stop read params et check si tous les params > Si oui : ok, si non : ko
// Sinon : erreur

int	is_line_a_param(char *line)
{
	if (!ft_strncmp(line, 'NO ', 3))
		return (YES);
	if (!ft_strncmp(line, 'SO ', 3))
		return (YES);
	if (!ft_strncmp(line, 'WE ', 3))
		return (YES);
	if (!ft_strncmp(line, 'EA ', 3))
		return (YES);
	if (!ft_strncmp(line, 'F ', 2))
		return (YES);
	if (!ft_strncmp(line, 'C ', 2))
		return (YES);
	return (NO);
}

int is_file_valid(char *line)
{
	int 	fd;
	char	*file;

	if (!ft_strncmp(line, 'NO ', 3) || !ft_strncmp(line, 'SO ', 3)
		|| !ft_strncmp(line, 'WE ', 3) || !ft_strncmp(line, 'EA ', 3))
	{
		file = ft_strdup(line + 3);
		if (!file)
			return (ERROR)
		fd = open(file, O_RDONLY));
		free(file);
		if (fd == ERROR)
			return (NO);
		close(fd);
		return (YES);
	}
	else
		return (YES);
}

static int	free_color(char **color)
{
	char	**begin;

	if (color)
	{
		begin = *color
		while (*color)
		{
			free(*color)
			++color;
		}
		free(begin);
	}
}

int is_color_valid(char *line)
{
	int 	fd;
	int		i;
	int		value;
	int		ret;
	char	**color;

	ret = YES;
	color = NULL;
	i = -1;
	if (!ft_strncmp(line, 'F ', 2) || !ft_strncmp(line, 'C ', 2))
	{
		color = ft_split(line + 2, ',');
		if (!color)
			return (ERROR);
		while (++i < 3 && color[i])
		{
			value = ft_atoi(color[i]);
			if (ft_strlen(color[i]) > 4 || value < 0 || value > 255)
				ret = NO;
		}
	}
	if (i > 0 && i != 3)
		ret = NO;
	free_color(color);
	return (ret);
}

int	param_controller(int fd)
{
	int		ret;
	char	*line;

	ret = ft_get_next_line(fd, &line, 0);
	while (ret >= 0)
	{
		if (is_line_a_param(line) && is_file_valid(line) 
			&& is_color_valid(line))
			// OK
		else
			// KO
		if (ret == 0)
			break ;
		ret = ft_get_next_line(fd, &line, 0);
	}
	if (ret == ERROR)
		return (ERROR);
	return (OK);
}
