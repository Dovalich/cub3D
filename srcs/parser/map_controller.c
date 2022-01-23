/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:01:31 by twagner           #+#    #+#             */
/*   Updated: 2022/01/23 13:03:58 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	is_line_valid(char *line, char *prev, int last_line, int *is_player)
{
	int		i;
	// char	left_char;

	i = -1;
	// left_char = 0;
	while (line[++i])
	{
		if (ft_strchr(PLAYER_CHAR, line[i]))
			++*is_player;
		if (!ft_strchr(VALID_CHAR, line[i]))
			return (NO);
		if (last_line && line[i] == '0')
			return (NO);
		if (!last_line && !ft_strchr(line, '1'))
			return (NO);
		if (check_around(line, i, prev))
			return (NO);
		// left_char = line[i]; unused
	}
	return (YES);
}

static int	control_loop(char **line, int ret, int *is_player)
{
	static char	*prev = NULL;
	int			last_line;	

	last_line = !ret;
	if (is_line_valid(*line, prev, last_line, is_player))
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
	int		is_player;
	char	*line;

	line = NULL;
	is_player = 0;
	ret = ft_get_next_line(fd, &line, 0);
	while (ret >= 0)
	{
		ret = control_loop(&line, ret, &is_player);
		if (ret == 0 || ret == ERROR)
			break ;
		ret = ft_get_next_line(fd, &line, 0);
	}
	free(line);
	if (ret == ERROR || is_player != 1)
		return (ERROR);
	return (OK);
}
