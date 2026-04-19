/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lit_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:20:18 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/20 01:28:32 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_lit_data(char **split, t_lit *lit, t_env *env)
{
	double	xyz[3];
	double	rgb[3];

	if (count_split(split) != 4)
		print_error_and_exit("set_lit_data", "number of arguments is not 4");
	if (env->part == MANDATORY && env->flag[L] > 0)
		print_error_and_exit("set_lit_data", "L already existed");
	env->flag[L] += 1;
	set_array(split[1], xyz, OTHER);
	set_struct_xyz(&lit->xyz, xyz);
	lit->t = ft_atof(split[2]);
	if (is_0_1(lit->t) == false)
		print_error_and_exit("set_light_data",
			"3rd element is not between 0 and 1");
	set_array(split[3], rgb, RGB);
	set_struct_xyz(&lit->rgb, rgb);
}

static void	lit_lst_add_back(t_lit *lit, t_lit *new)
{
	if (!lit)
	{
		lit = new;
		set_get_lit(SET, lit);
		return ;
	}
	while (lit->next)
		lit = lit->next;
	lit->next = new;
}

void	make_lit_data(char **split)
{
	t_env	*env;
	t_lit	*lit;
	t_lit	*new;

	env = set_get_env(GET, NULL);
	lit = set_get_lit(GET, NULL);
	new = (t_lit *)safe_malloc(1, sizeof(t_lit));
	init_lit(new);
	set_lit_data(split, new, env);
	lit_lst_add_back(lit, new);
}
