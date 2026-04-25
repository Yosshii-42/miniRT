/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_obj_pl_sp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:20:25 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/24 12:59:47 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_image(char *filename, t_obj *new)
{
	if (check_file(filename))
	{
		new->texture = IM;
		new->filename = ft_strdup(filename);
	}
	else
		print_error_and_exit("image", "file name error");
}

static void	set_tex_or_mat(char **split, t_obj *new, int count)
{
	if (ft_strncmp(split[4], "checker", 7) == 0
		&& split[4][7] == '\0' && count == 5)
		new->texture = CH;
	else if (ft_strncmp(split[4], "image", 5) == 0
		&& split[4][5] == '\0' && count == 6)
		set_image(split[5], new);
	else if (ft_strncmp(split[4], "metal", 5) == 0
		&& split[4][5] == '\0' && count == 5)
		new->material = METAL;
	else
		print_error_and_exit("tex or mat", "bad option");
}

void	set_pl_data(char **split, t_obj *new, int part)
{
	double	xyz[3];
	double	vector[3];
	double	rgb[3];
	int		count;

	count = count_split(split);
	if (count < 4 || (part == MANDATORY && count != 4)
		|| (part == BONUS && count > 6))
		print_error_and_exit("set_pl_data", "invalid argument count");
	new->id = PL;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&new->xyz, xyz);
	set_array(split[2], vector, VECTOR);
	set_struct_xyz(&new->vector, vector);
	normalize_check(new->vector, "set_pl_data");
	set_array(split[3], rgb, RGB);
	set_struct_xyz(&new->rgb, rgb);
	if (part == BONUS && count > 4)
		set_tex_or_mat(split, new, count);
}

void	set_sp_data(char **split, t_obj *new, int part)
{
	double	xyz[3];
	double	rgb[3];
	int		count;

	count = count_split(split);
	if (count < 4 || (part == MANDATORY && count != 4)
		|| (part == BONUS && count > 6))
		print_error_and_exit("set_sp_data", "invalid argument count");
	new->id = SP;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&new->xyz, xyz);
	new->diameter = ft_atof(split[2]);
	if (new->diameter <= 0)
		print_error_and_exit("set_sp_data", "diameter should be over 0");
	set_array(split[3], rgb, RGB);
	set_struct_xyz(&new->rgb, rgb);
	if (part == BONUS && count > 4)
		set_tex_or_mat(split, new, count);
}
