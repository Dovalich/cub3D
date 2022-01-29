/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:35:12 by twagner           #+#    #+#             */
/*   Updated: 2022/01/29 09:31:54 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h" 
# include <math.h>

# define PLAYER_CHAR "NSWE"
# define VALID_CHAR "NSWE 01"

// Used to count the number of parameters in the parser

enum e_parameter_bit_codes {
	ALL_PARAMS_ARE_SET = 63,
	NO_TEXTURE_CODE = 32,
	SO_TEXTURE_CODE = 16,
	WE_TEXTURE_CODE = 8,
	EA_TEXTURE_CODE = 4,
	F_COLOR_CODE	= 2,
	C_COLOR_CODE	= 1,
};

enum e_exit_codes {
	SUCCESS = 0,
	ARG_ERROR,
	ENV_ERROR,
	MAP_ERROR,
	PARAM_ERROR,
	FILE_ERROR,
	MALLOC_FAIL,
	MLX_FAIL,
	USER_INTERRUPT,
	NUMBER_OF_EXIT_CODES,
};

typedef struct img_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img_data;

typedef struct texture
{
	int			x;
	int			y;
	t_img_data	tex;
}			t_texture;

typedef struct s_param
{
	char		*tex_no_path;
	char		*tex_so_path;
	char		*tex_we_path;
	char		*tex_ea_path;
	t_texture	no;
	t_texture	ea;
	t_texture	so;
	t_texture	we;
	int			col_floor;
	int			col_ceiling;
	char		**map;
	int			width;
	int			height;
}			t_param;

/*
** FUNCTIONS
*/

/*
** Error Handling
*/
int		exit_clean(int error_msg, int fd, char **to_free, t_param *param);

/*
** parser
*/
int		line_param_code(char *line);
bool	is_cub_file(char *file);
bool	are_parameters_ok(int fd);
int		param_controller(int fd);
bool	is_map_ok(int fd, int *longest_map_width, int *map_height);
int		map_controller(int fd, int *longest_map_width, int *map_height);
int		init_param(char *file, t_param *param, int height, int width);
bool	is_valid_parameter(char *line, char param_counter, char code);
void	cub_file_parser(char **av, t_param *param);
/*
** Resource Free
*/
void	free_two_d_array(char **tab);
void	free_param(t_param *param);

/*
** Test functions
*/
void	print_param(t_param *param);
void	print_map(t_param *param);
#endif