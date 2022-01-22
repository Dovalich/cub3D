/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:01:31 by twagner           #+#    #+#             */
/*   Updated: 2022/01/22 14:24:39 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	nb_island(char *line, int search)
{
	//static char **map;
	(void)line;
	(void)search;
	return (0);
	// add lines to map until search == 1
	// when search == 1 : search for island
}

static int	check_around(char *line, int i, char *prev)
{
	int	left_char;
	int	right_char;
	int	top_char;

	left_char = 0;
	right_char = line[i + 1];
	top_char = 0;
	if (i > 0)
		left_char = line[i - 1];
	if (prev && (int)ft_strlen(prev) > i)
		top_char = prev[i];
	if (line[i] == '0' && (left_char == ' ' || left_char == 0
			|| right_char == ' ' || right_char == 0
			|| top_char == ' ' || top_char == 0))
		return (KO);
	if (line[i] == ' ' && top_char == '0')
		return (KO);
	return (OK);
}

int	is_line_valid(char *line, char *prev, int last_line)
{
	int		i;
	char	left_char;

	i = -1;
	left_char = 0;
	while (line[++i])
	{
		if (last_line && line[i] == '0')
			return (NO);
		if (!last_line && !ft_strchr(line, '1'))
			return (NO);
		if (check_around(line, i, prev))
			return (NO);
		left_char = line[i];
	}
	return (YES);
}

static int	control_loop(char **line, int ret)
{
	static char	*prev = NULL;
	int			last_line;	

	last_line = !ret;
	if (is_line_valid(*line, prev, last_line))
	{
		printf("line : %s : OK\n", *line);
		ret = !last_line;
	}
	else
	{
		printf("line : %s : KO\n", *line);
		ret = ERROR;
	}
	free(prev);
	prev = *line;
	*line = NULL;
	if (ret == 0 || ret == ERROR)
		free(prev);
	return (ret);
}

int	map_controller(int fd)
{
	int		ret;
	char	*line;

	line = NULL;
	ret = ft_get_next_line(fd, &line, 0);
	while (ret >= 0)
	{
		ret = control_loop(&line, ret);
		if (ret == 0 || ret == ERROR)
			break ;
		ret = ft_get_next_line(fd, &line, 0);
	}
	free(line);
	if (ret == ERROR)
		return (ERROR);
	return (OK);
}
