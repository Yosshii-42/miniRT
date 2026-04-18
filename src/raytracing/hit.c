/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:31:53 by tamatsuu          #+#    #+#             */
/*   Updated: 2026/04/18 13:09:06 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "calc.h"

double	hit_cam_ray(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
{
	if (obj->id == SP)
		return (hit_sphere(obj, ray));
	else if (obj->id == PL)
		return (hit_plane(obj, ray, h_obj, rec_hit));
	else if (obj->id == CY)
		return (hit_cylinder(obj, ray, h_obj, rec_hit));
	else if (obj->id == CN)
		return (hit_cone(obj, ray, h_obj, rec_hit));
	return (NO_HIT);
}

int	hit_shadow_ray(t_obj *obj, t_ray *sh_ray, t_hit_point *hit_p)
{
	t_obj		*obj_cpy;
	t_hit_point	tmp_hit;
	double		tmp_dist;
	int			i;
	int			ret;

	init_variables(&ret, &i, &obj_cpy, obj);
	while (obj_cpy)
	{
		if (hit_p->index != i)
		{
			tmp_hit = *hit_p;
			tmp_dist = hit_cam_ray(obj_cpy, sh_ray, &tmp_hit, false);
			if (tmp_dist > EPSILON && tmp_dist < MAX_DIST
				&& tmp_dist < hit_p->dist)
			{
				*hit_p = tmp_hit;
				hit_p->dist = tmp_dist;
				ret = i;
			}
		}
		obj_cpy = obj_cpy->next;
		i++;
	}
	return (ret);
}

// this funciton will return the index of object which is nearest
// -1 means there is no object which camera ray hit
int	hit_nearest_obj(t_obj *obj, t_ray *ray, t_hit_point *hit_p)
{
	t_obj		*obj_cpy;
	t_hit_point	tmp_hit;
	double		tmp_dist;
	int			i;
	int			ret;

	init_hit_p(hit_p);
	init_variables(&ret, &i, &obj_cpy, obj);
	while (obj_cpy)
	{
		tmp_hit = *hit_p;
		tmp_dist = hit_cam_ray(obj_cpy, ray, &tmp_hit, true);
		if (tmp_dist > 0 && tmp_dist < MAX_DIST && tmp_dist < hit_p->dist)
		{
			*hit_p = tmp_hit;
			hit_p->dist = tmp_dist;
			hit_p->index = i;
			ret = i;
		}
		obj_cpy = obj_cpy->next;
		i++;
	}
	if (ret == -1)
		hit_p->dist = -1;
	return (ret);
}

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
}
