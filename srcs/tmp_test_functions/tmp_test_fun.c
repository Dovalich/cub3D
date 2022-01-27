# include "game.h"
# include "parsing.h"

void	print_map(t_param *param)
{
	int	y;

	y = 0;
	while (param->map[y])
	{
		printf("%s\n", param->map[y]);
		++y;
	}
}

void	print_param(t_param *param)
{
	printf("This is texture NO |%s|\n", param->tex_no_path);
	printf("This is texture SO |%s|\n", param->tex_so_path);
	printf("This is texture WE |%s|\n", param->tex_we_path);
	printf("This is texture EA |%s|\n", param->tex_ea_path);
	printf("This is col_ceiling R |%d|\n", param->col_ceiling & 0xFF);
	printf("This is col_ceiling G |%d|\n", (param->col_ceiling >> 8) & 0xFF);
	printf("This is col_celing B|%d|\n", (param->col_ceiling >> 16)& 0xFF);
	printf("This is col_floor R |%d|\n", param->col_floor & 0xFF);
	printf("This is col_floor G |%d|\n", (param->col_floor >> 8) & 0xFF);
	printf("This is col_floor B |%d|\n", (param->col_floor >> 16) & 0xFF);
}
