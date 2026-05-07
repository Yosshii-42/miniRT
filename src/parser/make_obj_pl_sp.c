/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_obj_pl_sp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:20:25 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/27 17:35:51 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_tex_or_mat(char **split, t_obj *new)
{
	bool	no_image;

	no_image = false;
	if (ft_strncmp(split[6], "NONE", 4) == 0 && split[6][4] == '\0')
		no_image = true;
	if (ft_strncmp(split[5], "ON", 2) == 0 && split[5][2] == '\0')
		new->f_bump = ON;
	if (ft_strncmp(split[4], "metal", 5) == 0 && split[4][5] == '\0'
		&& no_image)
		new->f_mat_tex = ME;
	else if (ft_strncmp(split[4], "checker", 7) == 0 && split[4][7] == '\0'
		&& no_image)
		new->f_mat_tex = CH;
	else if (ft_strncmp(split[4], "image", 5) == 0 && split[4][5] == '\0'
			&& !no_image && check_file(split[6]))
	{
		new->f_mat_tex = IM;
		new->filename = ft_strdup(split[6]);
	}
	else if (ft_strncmp(split[4], "OFF", 3) == 0 && split[4][3] == '\0')
		new->f_mat_tex = OFF;
	else
		print_error_and_exit("tex or mat", "bad option");
}

void	set_pl_data(char **split, t_obj *new, int part)
{
	double	xyz[3];
	double	vector[3];
	double	rgb[3];

	if ((part == MANDATORY && new->count != 4)
		|| (part == BONUS && !(new->count == 4 || new->count == 7)))
		print_error_and_exit("set_pl_data", "invalid argument count");
	new->id = PL;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&new->xyz, xyz);
	set_array(split[2], vector, VECTOR);
	set_struct_xyz(&new->vector, vector);
	normalize_check(new->vector, "set_pl_data");
	set_array(split[3], rgb, RGB);
	set_struct_xyz(&new->rgb, rgb);
	if (part == BONUS && new->count == 7)
		set_tex_or_mat(split, new);
}

void	set_sp_data(char **split, t_obj *new, int part)
{
	double	xyz[3];
	double	rgb[3];

	if ((part == MANDATORY && new->count != 4)
		|| (part == BONUS && !(new->count == 4 || new->count == 7)))
		print_error_and_exit("set_sp_data", "invalid argument count");
	new->id = SP;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&new->xyz, xyz);
	new->diameter = ft_atof(split[2]);
	if (new->diameter <= 0)
		print_error_and_exit("set_sp_data", "diameter should be over 0");
	set_array(split[3], rgb, RGB);
	set_struct_xyz(&new->rgb, rgb);
	if (part == BONUS && new->count == 7)
		set_tex_or_mat(split, new);
}
