/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/26 20:35:27 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "game.h"

t_param	*get_param_ptr(void)
{
	static t_param	*param = NULL;

	if (!param)
	{
		param = malloc(sizeof(*param));
		if (!param)
			return (NULL);
		ft_bzero(param, sizeof(*param));
	}
	return (param);
}

t_data	*get_data_ptr(void)
{
	static t_data	*data = NULL;
	
	if (!data)
	{
		data = malloc(sizeof(*data));
		if (!data)
			return (NULL);
		ft_bzero(data, sizeof(*data));
	}
	return (data);
}

int	main(int ac, char **av, char **envp)
{
	t_param	*param;
	t_data	*data;

	if (ac != 2 || !envp || !*envp)
		return (ERROR);
	param = get_param_ptr();
	if (!param)
		return (MALLOC_FAIL);
	cub_file_parser(av, param);
	data = get_data_ptr();
	if (!data)
		exit_clean(MALLOC_FAIL, 0, NULL, param);
	data->param = param;
	data->map = param->map;
	printf("map is OK !\n");
	if (create_window(data))
	{
		printf("Error with window creation\n");
		return (ERROR);
	}
	free_param(param);
	return (SUCCESS);
}
