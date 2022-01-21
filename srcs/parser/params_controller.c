/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:48:01 by twagner           #+#    #+#             */
/*   Updated: 2022/01/21 11:54:54 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check line
// Si XX ou X > regarder ce aqu'il y a apres et essayer de l'open > Si open = -1 > Error, sinon close et ok
// Si vide ou 11 ou EOF > Stop read params et check si tous les params > Si oui : ok, si non : ko

int	param_controller(int fd)
{
	int		ret;
	char	*line;

	ret = ft_get_next_line(fd, &line, 0);
	while (ret >= 0)
	{
		printf("Line\n");
		if (ret == 0)
			break ;
		ret = ft_get_next_line(fd, &line, 0);
	}
	if (ret == ERROR)
		return (ERROR);
	return (OK);
}
