/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:27:59 by nammari           #+#    #+#             */
/*   Updated: 2022/01/28 22:28:00 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "game.h"

// When exiting due to an error we need a way
// to close fds and free 2-d arrays if any.

int	exit_clean(int error_msg, int fd, char **to_free, t_param *param)
{
	char	*tab[NUMBER_OF_EXIT_CODES];

	tab[MAP_ERROR] = "Something's wrong in the map.\n";
	tab[PARAM_ERROR] = "Something's wrong with the parameters.\n";
	tab[FILE_ERROR] = "The file doesn't seem to be working.\n";
	tab[MALLOC_FAIL] = "Malloc failed. Oopsi.\n";
	tab[MLX_FAIL] = "An MLX Function just shat its pants.\n";
	tab[USER_INTERRUPT] = "User interrupted the game.\n";
	ft_putstr_fd("Error\n", 2);
	if (error_msg >= 1 && error_msg < NUMBER_OF_EXIT_CODES)
		ft_putstr_fd(tab[error_msg], 2);
	if (fd > 1)
		close(fd);
	free_two_d_array(to_free);
	ft_get_next_line(0, NULL, 1);
	if (param)
		free_param(param);
	exit(error_msg);
	return (error_msg);
}

void	exit_program(t_data *data, int exit_status)
{
	if (!data)
		exit(exit_status);
	if (data->param)
	{
		free_param(data->param);
		if (data->param->no.tex.img)
			mlx_destroy_image(data->mlx, data->param->no.tex.img);
		if (data->param->so.tex.img)
			mlx_destroy_image(data->mlx, data->param->so.tex.img);
		if (data->param->we.tex.img)
			mlx_destroy_image(data->mlx, data->param->we.tex.img);
		if (data->param->ea.tex.img)
			mlx_destroy_image(data->mlx, data->param->ea.tex.img);
		if (data->frame.img)
			mlx_destroy_image(data->mlx, data->frame.img);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(exit_status);
}

int	close_win(t_data *data)
{
	exit_program(data, USER_INTERRUPT);
	return (USER_INTERRUPT);
}
