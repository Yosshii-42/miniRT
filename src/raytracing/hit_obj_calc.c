/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:31:53 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 19:35:29 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/calc.h"

// dist が決まった後に、pos と norm を完成させる関　sphere-ok
void	fill_hit_obj(t_obj *obj, t_ray c_ray, t_hit_point *h_obj)
{
	h_obj->pos = vec_add(c_ray.pos, vec_scale(c_ray.dir, h_obj->dist));
	if (obj->id == SP)
	{
		h_obj->norm = vec_sub(h_obj->pos, obj->xyz);
		h_obj->norm = normalize(h_obj->norm);
	}
	else if (obj->id == PL)
	{
		h_obj->norm = normalize(obj->vector);
		if (dot(c_ray.dir, h_obj->norm) > 0)
			h_obj->norm = vec_scale(h_obj->norm, -1);
	}
	// else if (obj->id == CY)
	// 	set_h_obj_cy(obj, &c_ray, h_obj, &h_obj->dist);
}

void	set_hit_obj(t_obj *obj, t_ray *ray, t_hit_point *h_obj, double dist)
{
	h_obj->dist = dist;
	h_obj->pos = vec_add(ray->pos, vec_scale(ray->dir, h_obj->dist));
	if (obj->id == SP)
	{
		h_obj->norm = vec_sub(h_obj->pos, obj->xyz);
		h_obj->norm = normalize(h_obj->norm);
	}
	else if (obj->id == PL)
		h_obj->norm = normalize(obj->vector);
}

void	set_h_obj_cy(t_obj *obj, t_ray *ray, t_hit_point *h_obj, double *t)
{
	t_xyz	obj_center;
	t_xyz	obj_vector;
	t_xyz	pos;
	double	s;

	if (t[0] == NO_HIT)
		return ;
	h_obj->dist = t[0];
	h_obj->pos = vec_add(ray->pos, vec_scale(ray->dir, h_obj->dist));
	obj_center = obj->xyz;
	obj_vector = normalize(obj->vector);
	s = dot(vec_sub(h_obj->pos, obj_center), obj_vector);
	if (s >= 0 && s <= obj->height)
	{
		pos = vec_add(obj_center, vec_scale(obj_vector, s));
		h_obj->norm = normalize(vec_sub(h_obj->pos, pos));
	}
	else if (s < 0)
		h_obj->norm = vec_scale(obj_vector, -1);
	else
		h_obj->norm = obj_vector;
}
