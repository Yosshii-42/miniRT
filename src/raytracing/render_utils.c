/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:18:37 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/19 22:09:03 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "ui.h"
#include "calc.h"
#include <mlx.h>
#include <math.h>

void	reset_light_flags(t_env *env)
{
	t_lit	*l;

	l = env->lit;
	while (l)
	{
		l->valid_flag = true;
		l = l->next;
	}
}

void	init_offset(double sx[4], double sy[4])
{
	sx[0] = 0.25;
	sx[1] = 0.75;
	sx[2] = 0.25;
	sx[3] = 0.75;
	sy[0] = 0.25;
	sy[1] = 0.25;
	sy[2] = 0.75;
	sy[3] = 0.75;
}

t_shade_ctx	set_shade_data(t_obj *obj, t_hit_point hit, t_ray ray)
{
	t_shade_ctx	shade;

	shade.obj = obj;
	shade.hit = hit;
	shade.ray = ray;
	return (shade);
}

t_obj	get_indexed_obj(int index, t_obj *obj)
{
	t_obj	*ret;
	int		i;

	if (!obj)
		print_error_and_exit("get_indexed_obj", "obj is null");
	if (index < 0)
		print_error_and_exit("get_indexed_obj", "invalid index");
	ret = obj;
	i = 0;
	while (ret && i < index)
	{
		ret = ret->next;
		i++;
	}
	if (!ret)
		print_error_and_exit("get_indexed_obj", "index out of range");
	return (*ret);
}
