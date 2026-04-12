/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:12:31 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 19:12:59 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raytracing.h"
#include "../../includes/calc.h"

int	calc_shadow(t_obj *obj, t_lit *lit, t_hit_point *hit_p)
{
	t_ray		shadow_ray;
	t_xyz		incident_dir;
	double		dist_shadow_to_lit;
	double		ret;
	t_hit_point	tmp_hit;

	incident_dir = minus_v1_v2(lit->xyz, hit_p->pos);
	incident_dir = normalize(incident_dir);
	tmp_hit = *hit_p;
	tmp_hit.dist = MAX_DIST;
	shadow_ray.pos = plus_v1_v2(hit_p->pos, multi_v_f(hit_p->norm, EPSILON));
	// shadow_ray.pos = plus_v1_v2(hit_p->pos, multi_v_f(incident_dir, EPSILON));
	shadow_ray.dir = incident_dir;
	dist_shadow_to_lit = distance_between(lit->xyz, hit_p->pos);
	ret = hit_shadow_ray(obj, &shadow_ray, &tmp_hit);
	if (ret != -1 && tmp_hit.dist > EPSILON \
		&& tmp_hit.dist < dist_shadow_to_lit - EPSILON)
		return (RENDERED_SHADOW);
	return (NOT_RENDERED_SHADOW);
}
