/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:19:57 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/15 07:10:57 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	make_env_data(char **split)
{
	t_env	*env;

	env = set_get_env(GET, NULL);
	if (ft_memcmp(split[0], "A", 2) == 0)
		set_amb_data(split, env);
	else if (ft_memcmp(split[0], "C", 2) == 0)
		set_cam_data(split, env);
}

void	set_amb_data(char **split, t_env *env)
{
	double	rgb[3];

	if (env->flag[A] == 1)
		print_error_and_exit("set_amb_data", "A data already existed");
	env->flag[A] = 1;
	if (count_split(split) != 3)
		print_error_and_exit("set_amb_data", "number of arguments is not 3");
	env->amb_t = ft_atof(split[1]);
	if (is_0_1(env->amb_t) == false)
		print_error_and_exit("set_amb_data",
			"2nd element is not between 0 and 1");
	set_array(split[2], rgb, RGB);
	set_struct_xyz(&env->amb_rgb, rgb);
}

void	set_cam_data(char **split, t_env *env)
{
	double	xyz[3];
	double	vector[3];
	double	degree;

	if (env->flag[C] == 1)
		print_error_and_exit("set_cam_data", "C data already existed");
	env->flag[C] = 1;
	if (count_split(split) != 4)
		print_error_and_exit("set_cam_data", "number of arguments is not 4");
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&env->cam_xyz, xyz);
	set_array(split[2], vector, VECTOR);
	set_struct_xyz(&env->cam_vector, vector);
	degree = ft_atof(split[3]);
	if (is_0_180(degree) == false)
		print_error_and_exit("set_cam_data",
			"4th element is not between 0 and 180");
	env->cam_degree = degree;
}
