/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:16:35 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/18 18:16:38 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "calc.h"

void	init_t_hit_point(t_hit_point *tmp)
{
	tmp->dist = MAX_DIST;
	tmp->index = -1;
	init_xyz(&tmp->pos);
	init_xyz(&tmp->norm);
}

void	set_init_cylinder_data(t_cy *cy, t_obj *obj, t_ray *ray)
{
	cy->ray = *ray;
	cy->obj = obj;
	cy->axis = normalize(obj->vector);
	cy->radius = obj->diameter / 2.0;
	cy->half_h = obj->height / 2.0;
	cy->min = EPS;
	cy->max = MAX_DIST;
	cy->top = vec_add(cy->obj->xyz, vec_scale(cy->axis, cy->half_h));
	cy->bottom = vec_sub(cy->obj->xyz, vec_scale(cy->axis, cy->half_h));
	cy->oc = vec_sub(ray->pos, obj->xyz);
}

void	set_init_cone_data(t_cn *cn, t_obj *obj, t_ray *ray)
{
	cn->ray = *ray;
	cn->obj = obj;
	cn->axis = normalize(obj->vector);
	cn->radius = obj->diameter / 2.0;
	cn->height = obj->height;
	cn->co = vec_sub(ray->pos, obj->xyz);
	cn->k = sqr(cn->radius / cn->height);
	cn->dir_axis = dot(ray->dir, cn->axis);
	cn->co_axis = dot(cn->co, cn->axis);
}
