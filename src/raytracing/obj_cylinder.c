/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:17:45 by yotsurud          #+#    #+#             */
/*   Updated: 2026/05/01 20:27:35 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "parser.h"
#include "raytracing.h"

static bool	hit_cy_core(t_cy *cy, t_hit_point *hit)
{
	t_hit_point	side_hit;
	t_hit_point	cap_hit;
	bool		has_side;
	bool		has_cap;

	has_side = hit_cy_side(cy, &side_hit);
	has_cap = hit_cy_caps(cy, &cap_hit);
	if (!has_side && !has_cap)
		return (false);
	if (has_side && !has_cap)
		return (*hit = side_hit, true);
	if (!has_side && has_cap)
		return (*hit = cap_hit, true);
	if (side_hit.dist < cap_hit.dist)
		*hit = side_hit;
	else
		*hit = cap_hit;
	return (true);
}

double	hit_cylinder(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
{
	t_cy		cy;
	t_hit_point	tmp;

	set_init_cylinder_data(&cy, obj, ray);
	init_t_hit_point(&tmp);
	if (!hit_cy_core(&cy, &tmp))
		return (NO_HIT);
	if (rec_hit)
	{
		*h_obj = tmp;
		set_face_normal(ray, h_obj);
	}
	return (tmp.dist);
}
