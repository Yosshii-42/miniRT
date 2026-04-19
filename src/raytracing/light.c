/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:24:54 by tamatsuu          #+#    #+#             */
/*   Updated: 2026/04/20 01:37:37 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/calc.h"

static void	check_light_and_cam_pos(t_obj *obj, t_lit *lit, t_ray cam_ray)
{
	double	dot_n_light;
	double	dot_n_camera;
	t_xyz	norm_p;

	norm_p = normalize(obj->vector);
	dot_n_light = dot(norm_p, vec_sub(lit->xyz, obj->xyz));
	dot_n_camera = dot(norm_p, vec_sub(cam_ray.pos, obj->xyz));
	if ((dot_n_light > 0 && dot_n_camera > 0)
		|| (dot_n_light < 0 && dot_n_camera < 0))
		;
	else
		lit->valid_flag = false;
}

static void	is_light_inside_sp(t_obj *obj, t_lit *lit)
{
	t_xyz	center_to_light;
	double	dist2;
	double	r2;
	double	epsilon;

	r2 = sqr(obj->diameter / 2);
	center_to_light = vec_sub(lit->xyz, obj->xyz);
	dist2 = dot(center_to_light, center_to_light);
	epsilon = EPS * r2;
	if (dist2 >= r2 - epsilon)
		return ;
	lit->valid_flag = false;
}

static void	is_light_inside_cy(t_obj *obj, t_lit *lit)
{
	t_xyz	center_to_light;
	t_xyz	axis;
	double	axis_dist;
	double	dist2;
	double	half_h;

	center_to_light = vec_sub(lit->xyz, obj->xyz);
	axis = normalize(obj->vector);
	half_h = obj->height / 2.0;
	axis_dist = dot(center_to_light, axis);
	if (axis_dist < -half_h || half_h < axis_dist)
		return ;
	dist2 = dot(
			vec_sub(center_to_light, vec_scale(axis, axis_dist)),
			vec_sub(center_to_light, vec_scale(axis, axis_dist))
			);
	if (dist2 <= sqr(obj->diameter / 2.0))
		lit->valid_flag = false;
}

void	check_light_pos(t_obj *obj, t_env *env, t_ray cam_ray)
{
	t_obj	*obj_cpy;
	t_lit	*lit_cpy;

	lit_cpy = env->lit;
	while (lit_cpy)
	{
		obj_cpy = obj;
		while (obj_cpy)
		{
			if (obj_cpy->id == PL)
				check_light_and_cam_pos(obj_cpy, lit_cpy, cam_ray);
			else if (obj_cpy->id == SP)
				is_light_inside_sp(obj_cpy, lit_cpy);
			else if (obj_cpy->id == CY)
				is_light_inside_cy(obj_cpy, lit_cpy);
			obj_cpy = obj_cpy->next;
		}
		lit_cpy = lit_cpy->next;
	}
}
