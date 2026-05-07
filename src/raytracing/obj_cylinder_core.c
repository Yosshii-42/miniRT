/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:17:56 by yotsurud          #+#    #+#             */
/*   Updated: 2026/05/01 20:27:12 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "parser.h"
#include "raytracing.h"

// cylinder side quadratic coefficients
static void	calc_cy_side_abc(t_cy *cy)
{
	t_xyz	d_cross;
	t_xyz	oc_cross;

	d_cross = cross(cy->ray.dir, cy->axis);
	oc_cross = cross(cy->oc, cy->axis);
	cy->a = dot(d_cross, d_cross);
	cy->b = 2.0 * dot(d_cross, oc_cross);
	cy->c = dot(oc_cross, oc_cross) - cy->radius * cy->radius;
}

static bool	judge_cylinder_t(t_cy *cy, t_hit_point *hit, double t)
{
	t_xyz	pos;
	double	s;

	pos = vec_add(cy->ray.pos, vec_scale(cy->ray.dir, t));
	s = dot(vec_sub(pos, cy->obj->xyz), cy->axis);
	if (-cy->half_h <= s && s <= cy->half_h)
	{
		hit->dist = t;
		hit->pos = pos;
		hit->norm = normalize(vec_sub(pos,
					vec_add(cy->obj->xyz, vec_scale(cy->axis, s))));
		hit->part = HIT_CY_SIDE;
		return (true);
	}
	return (false);
}

bool	hit_cy_side(t_cy *cy, t_hit_point *hit)
{
	double		t0;
	double		t1;
	bool		found;
	t_hit_point	tmp;

	found = false;
	init_t_hit_point(&tmp);
	calc_cy_side_abc(cy);
	if (!solve_quadratic(cy, &t0, &t1))
		return (false);
	if (cy->min <= t0 && t0 <= cy->max && judge_cylinder_t(cy, &tmp, t0))
	{
		*hit = tmp;
		found = true;
	}
	if (cy->min <= t1 && t1 <= cy->max && judge_cylinder_t(cy, &tmp, t1))
	{
		if (!found || tmp.dist < hit->dist)
			*hit = tmp;
		found = true;
	}
	return (found);
}

bool	hit_cy_caps(t_cy *cy, t_hit_point *hit)
{
	t_hit_point	tmp;
	bool		found;

	init_t_hit_point(&tmp);
	found = false;
	if (hit_cy_cap(cy, cy->axis, HIT_CY_CAP_TOP, &tmp))
	{
		*hit = tmp;
		found = true;
	}
	if (hit_cy_cap(cy, vec_scale(cy->axis, -1.0), HIT_CY_CAP_BOTTOM, &tmp))
	{
		if (!found || tmp.dist < hit->dist)
			*hit = tmp;
		found = true;
	}
	return (found);
}

bool	hit_cy_cap(t_cy *cy, t_xyz normal, t_hit_part part, t_hit_point *hit)
{
	double	denom;
	double	t;
	t_xyz	position;
	t_xyz	direction;
	t_xyz	center;

	if (part == HIT_CY_CAP_TOP)
		center = cy->top;
	else
		center = cy->bottom;
	denom = dot(cy->ray.dir, normal);
	if (fabs(denom) < EPS)
		return (false);
	t = dot(vec_sub(center, cy->ray.pos), normal) / denom;
	if (t < cy->min || cy->max < t)
		return (false);
	position = vec_add(cy->ray.pos, vec_scale(cy->ray.dir, t));
	direction = vec_sub(position, center);
	if (vec_length_sq(direction) > sqr(cy->radius))
		return (false);
	hit->dist = t;
	hit->pos = position;
	hit->norm = normal;
	hit->part = part;
	return (true);
}
