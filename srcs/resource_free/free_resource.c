/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:45:52 by nammari           #+#    #+#             */
/*   Updated: 2022/01/24 16:38:40 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_two_d_array(char **tab)
{
    int	i;

    i = 0;
    if (!tab)
        return ;
    while (tab[i])
    {
        free(tab[i]);
        ++i;
    }
    free(tab);
}

void    free_param(t_param *param)
{
    if (!param)
        return ;
    if (param->tex_no)
        free(param->tex_no);
    if (param->tex_ea)
        free(param->tex_ea);
    if (param->tex_so)
        free(param->tex_so);
    if (param->tex_we)
        free(param->tex_we);
    if (param->map)
        free_two_d_array(param->map);
    free(param);
}
