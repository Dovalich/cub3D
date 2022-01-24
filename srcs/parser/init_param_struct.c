/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 09:50:15 by twagner           #+#    #+#             */
/*   Updated: 2022/01/24 16:37:07 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	init_param(char *file, t_param *param, int height, int width)
{
	int	fd;

	(void)width;
	(void)height;
	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return (ERROR);
	param = malloc(sizeof(*param));
	if (!param)
		return (ERROR);
	ft_bzero(param, sizeof(*param));
	get_params(param, fd);
	free_param(param);
	// get_map(param, fd, width, height);
	// init_player_pos(param);	
	return (SUCCESS);
}
