/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   island_detector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:36:30 by twagner           #+#    #+#             */
/*   Updated: 2022/01/22 17:35:17 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(char **map)
{
	char	**tmp;

	if (map)
	{
		tmp = map;
		while (*map)
		{
			free(*map);
			++map;
		}
		free(tmp);
	}
}

static int	add_one_line(char ***map, char *line)
{
	int		i;
	char	**new_map;

	if (*map)
	{
		i = 0;
		while ((*map)[i])
			++i;
		new_map = (char **)malloc(sizeof(*new_map) * (i + 2));
		if (!new_map)
		{
			free_map(*map);
			return (ERROR);
		}
		i = -1;
		while ((*map)[++i])
			new_map[i] = ft_strdup((*map)[i]);
		new_map[i] = ft_strdup(line);
		new_map[i + 1] = NULL;
		free_map(*map);
		*map = new_map;
		return (OK);
	}
	return (ERROR);
}

static int	init_map(char ***map)
{
	*map = (char **)malloc(sizeof(**map));
	if (!*map)
		return (ERROR);
	(*map)[0] = NULL;
	return (0);
}

int	count_island(char *line, int action)
{
	static char	**map = NULL;

	if (map == NULL && init_map(&map) == ERROR)
		return (ERROR);
	if (action == ADD && add_one_line(&map, line) == ERROR)
		return (ERROR);
	else if (action == COUNT)
	{
		// function to count islands
		free_map(map);
		return (2);
	}
	return (0);
}
