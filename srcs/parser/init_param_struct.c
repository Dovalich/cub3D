/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 09:50:15 by twagner           #+#    #+#             */
/*   Updated: 2022/01/24 18:02:27 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//test function to be deleted before we push

void	print_map(t_param *param)
{
	int	y;

	y = 0;
	while (param->map[y])
	{
		printf("%s\n", param->map[y]);
		++y;
	}
}

void	print_param(t_param *param)
{
	printf("This is texture NO |%s|\n", param->tex_no);
	printf("This is texture SO |%s|\n", param->tex_so);
	printf("This is texture WE |%s|\n", param->tex_we);
	printf("This is texture EA |%s|\n", param->tex_ea);
	printf("This is col_ceiling R |%d|\n", param->col_ceiling & 0xFF);
	printf("This is col_ceiling G |%d|\n", (param->col_ceiling >> 8) & 0xFF);
	printf("This is col_celing B|%d|\n", (param->col_ceiling >> 16)& 0xFF);
	printf("This is col_floor R |%d|\n", param->col_floor & 0xFF);
	printf("This is col_floor G |%d|\n", (param->col_floor >> 8) & 0xFF);
	printf("This is col_floor B |%d|\n", (param->col_floor >> 16) & 0xFF);
}

static void	get_color(t_param *param, char *line, int code, int fd)
{
	char	**color;

	if (*line)
		++line;
	while (ft_is_space(*line))
		++line;
	color = ft_split(line, ',');
	if (!color)
		exit_clean(MALLOC_FAIL, fd, NULL, param);
	if (code == C_COLOR_CODE)
	{
		param->col_ceiling = 0;
		param->col_ceiling = ft_atoi(color[0]);
		param->col_ceiling = param->col_ceiling | (ft_atoi(color[1]) << 8);
		param->col_ceiling = param->col_ceiling | (ft_atoi(color[2]) << 16);
	}
	else if (code == F_COLOR_CODE)
	{
		param->col_floor = 0;
		param->col_floor = ft_atoi(color[0]);
		param->col_floor = param->col_floor | (ft_atoi(color[1]) << 8);
		param->col_floor = param->col_floor | (ft_atoi(color[2]) << 16);
	}
	free_two_d_array(color);
}

static void	get_texture(t_param *param, char *line, int code, int fd)
{
	line = line + 2;
	while (*line && ft_is_space(*line))
		++line;
	if (code == NO_TEXTURE_CODE)
		param->tex_no = ft_get_trimed_right(line);
	else if (code == SO_TEXTURE_CODE)
		param->tex_so = ft_get_trimed_right(line);
	else if (code == WE_TEXTURE_CODE)
		param->tex_we = ft_get_trimed_right(line);
	else if (code == EA_TEXTURE_CODE)
		param->tex_ea = ft_get_trimed_right(line);
	if ((code == NO_TEXTURE_CODE && param->tex_no == NULL) ||
		(code == SO_TEXTURE_CODE && param->tex_no == NULL) ||
		(code == EA_TEXTURE_CODE && param->tex_so == NULL) ||
		(code == WE_TEXTURE_CODE && param->tex_we == NULL))
		exit_clean(MALLOC_FAIL, fd, NULL, param);
}

static void	get_params(t_param *param, int fd)
{
	char	*line;
	int		code;
	int		param_counter;

	param_counter = 0;
	while (ft_get_next_line(fd, &line, 0))
	{
		code = line_param_code(line);
		if (code != 0)
		{
			if (code == F_COLOR_CODE || code == C_COLOR_CODE)
				get_color(param, line, code, fd);
			else
				get_texture(param, line, code, fd);
			param_counter = param_counter | code;
		}
		free(line);
		if (param_counter == ALL_PARAMS_ARE_SET)
			return ;
	}
}

static void	get_map(t_param *param, int height, int width, int fd)
{
	char	*line;
	int		y;
	int		x;

	y = -1;
	while (ft_get_next_line(fd, &line, 0) > 0)
	{
		if (ft_strlen(line) > 0)
			break ;
		free(line);
	}
	while (++y < height)
	{
		if (y > 0 && ft_get_next_line(fd, &line, 0) == ERROR)
			exit_clean(MALLOC_FAIL, fd, NULL, param);
		ft_memset(param->map[y], '1', width);
		param->map[y][width] = '\0';
		x = -1;
		while (line[++x])
			if (line[x] != ' ')
				param->map[y][x] = line[x];
		free(line);
	}
	close(fd);
	free_gnl_buffer();
}

int	init_param(char *file, t_param *param, int width, int height)
{
	int	fd;
	int	i;

	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return (ERROR);
	ft_bzero(param, sizeof(*param));
	get_params(param, fd);
	param->map = malloc(sizeof(*param->map) * (height + 1));
	if (!param->map)
		exit_clean(MALLOC_FAIL, fd, NULL, param);
	param->map[height] = NULL;
	i = 0;
	while (i < height)
	{
		param->map[i] = malloc(sizeof(char) * (width + 1));
		if (!(param->map[i]))
			exit_clean(MALLOC_FAIL, fd, NULL, param);
		++i;
	}
	get_map(param, height, width, fd);
	return (SUCCESS);
}
