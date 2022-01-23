/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:27:59 by nammari           #+#    #+#             */
/*   Updated: 2022/01/23 16:03:27 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// When exiting due to an error we need a way 
// to close fds and free 2-d arrays if any. 

int exit_clean(int error_msg, int fd, char **to_free)
{
    char	*tab[6];

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
    free_gnl_buffer();
    exit (error_msg);
    return (error_msg);
}
