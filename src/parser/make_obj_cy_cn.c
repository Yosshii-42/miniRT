#include "parser.h"

void	set_cy_data(char **split, t_obj *new)
{
	double	xyz[3];
	double	vector[3];
	double	rgb[3];
	int		count;

	count = count_split(split);
	if (count != 6)
		print_error_and_exit("set_cy_data", "number of arguments is not 6");
	new->id = CY;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&new->xyz, xyz);
	set_array(split[2], vector, VECTOR);
	set_struct_xyz(&new->vector, vector);
	new->diameter = ft_atof(split[3]);
	if (new->diameter <= 0)
		print_error_and_exit("set_cy_data", "diameter should be over 0");
	new->height = ft_atof(split[4]);
	if (new->height <= 0)
		print_error_and_exit("set_cy_data", "height should be over 0");
	set_array(split[5], rgb, RGB);
	set_struct_xyz(&new->rgb, rgb);
}

void	set_cn_data(char **split, t_obj *new)
{
	double	xyz[3];
	double	vector[3];
	double	rgb[3];
	int		count;

	count = count_split(split);
	if (count != 6)
		print_error_and_exit("set_cn_data", "number of arguments is not 6");
	new->id = CN;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&new->xyz, xyz);
	set_array(split[2], vector, VECTOR);
	set_struct_xyz(&new->vector, vector);
	new->diameter = ft_atof(split[3]);
	if (new->diameter <= 0)
		print_error_and_exit("set_cn_data", "diameter should be over 0");
	new->height = ft_atof(split[4]);
	if (new->height <= 0)
		print_error_and_exit("set_cn_data", "height should be over 0");
	set_array(split[5], rgb, RGB);
	set_struct_xyz(&new->rgb, rgb);
}
