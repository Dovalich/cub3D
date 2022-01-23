/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 09:50:15 by twagner           #+#    #+#             */
/*   Updated: 2022/01/23 13:17:49 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_param	*init_param(char *file)
{
	t_param	*tmp_to_silence_error;
	
	(void)file;
	tmp_to_silence_error = malloc(sizeof(t_param));
	tmp_to_silence_error->map = NULL;
	return (tmp_to_silence_error);
}