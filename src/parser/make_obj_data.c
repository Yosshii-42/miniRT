/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_obj_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:20:41 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/16 17:20:53 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	make_obj_data(char **split)
{
	t_obj	*obj;
	t_obj	*new;

	obj = set_get_obj(GET, NULL);
	new = (t_obj *)safe_malloc(1, sizeof(t_obj));
	init_obj(new);
	if (ft_memcmp(split[0], "pl", 3) == 0)
		set_pl_data(split, new);
	if (ft_memcmp(split[0], "sp", 3) == 0)
		set_sp_data(split, new);
	if (ft_memcmp(split[0], "cy", 3) == 0)
		set_cy_data(split, new);
	obj_lst_add_back(obj, new);
}

void	set_image(char *filename, t_obj *new)
{
	if (check_file(filename))
	{
		new->texture = IM;
		new->filename = ft_strdup(filename);
	}
	else
		print_error_and_exit("image", "file name error");
}

void	set_texture(char **split, t_obj *new, int count)
{
	if (ft_strncmp(split[4], "checker", 7) == 0
		&& split[4][7] == '\0' && count == 5)
		new->texture = CH;
	else if (ft_strncmp(split[4], "image", 5) == 0
		&& split[4][5] == '\0' && count == 6)
		set_image(split[5], new);
	else
		print_error_and_exit("texture", "bad texture option");
}

void	set_pl_data(char **split, t_obj *new)
{
	double	xyz[3];
	double	vector[3];
	double	rgb[3];
	int		count;

	count = count_split(split);
	if (count < 4 || 6 < count)
		print_error_and_exit("set_pl_data", "invalid argument count");
	new->id = PL;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&new->xyz, xyz);
	set_array(split[2], vector, VECTOR);
	set_struct_xyz(&new->vector, vector);
	set_array(split[3], rgb, RGB);
	set_struct_xyz(&new->rgb, rgb);
	if (count > 4)
		set_texture(split, new, count);
}

void	set_sp_data(char **split, t_obj *new)
{
	double	xyz[3];
	double	rgb[3];
	int		count;
	
	count = count_split(split);
	if (count < 4 || 6 < count)
		print_error_and_exit("set_sp_data", "invalid argument count");
	new->id = SP;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&new->xyz, xyz);
	new->diameter = ft_atof(split[2]);
	if (new->diameter <= 0)
		print_error_and_exit("set_sp_data", "diameter shuold be over 0");
	set_array(split[3], rgb, RGB);
	set_struct_xyz(&new->rgb, rgb);
	if (count > 4)
		set_texture(split, new, count);
}

void	set_cy_data(char **split, t_obj *new)
{
	double	xyz[3];
	double	vector[3];
	double	rgb[3];

	if (count_split(split) != 6)
		print_error_and_exit("set_cy_data", "number of arguments is not 6");
	new->id = CY;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&new->xyz, xyz);
	set_array(split[2], vector, VECTOR);
	set_struct_xyz(&new->vector, vector);
	new->diameter = ft_atof(split[3]);
	if (new->diameter < 0)
		print_error_and_exit("set_cam_data", "diameter shuold be over 0");
	new->height = ft_atof(split[4]);
	if (new->height < 0)
		print_error_and_exit("set_cam_data", "height shuold be over 0");
	set_array(split[5], rgb, RGB);
	set_struct_xyz(&new->rgb, rgb);
}

void	obj_lst_add_back(t_obj *obj, t_obj *new)
{
	if (!obj)
	{
		obj = new;
		set_get_obj(SET, obj);
		return ;
	}
	while (obj->next)
		obj = obj->next;
	obj->next = new;
}
