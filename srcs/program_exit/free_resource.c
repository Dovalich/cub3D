/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:45:52 by nammari           #+#    #+#             */
/*   Updated: 2022/01/27 15:21:58 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
    if (param->tex_no_path)
        free(param->tex_no_path);
    if (param->tex_ea_path)
        free(param->tex_ea_path);
    if (param->tex_so_path)
        free(param->tex_so_path);
    if (param->tex_we_path)
        free(param->tex_we_path);
    if (param->map)
        free_two_d_array(param->map);
}
