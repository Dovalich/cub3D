/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:12 by twagner           #+#    #+#             */
/*   Updated: 2022/01/22 10:35:15 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "unistd.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

/*
** PARAMS
*/

typedef enum e_return_codes
{
	OK = 0,
	NO = 0,
	YES = 1,
	KO = 1
}	t_return_codes;

/* for floor and ceiling colors
blue = (RGB >> 16) & 0xFF;
green = (RGB >> 8) & 0xFF;
red = RGB & 0xFF;

new_RGB = (blue << 16) | (green << 8) | red;
*/

typedef struct s_param
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		*col_floor;
	int		*col_ceiling;
	char	**map;
}			t_param;

/*
** FUNCTIONS
*/

/*
** parser
*/
int		is_cub_file(char *file);
int		are_params_ok(char *file, int *fd);
int		param_controller(int fd);
int		is_map_ok(int fd);
int		map_controller(int fd);
t_param	*init_param(char *file);

#endif