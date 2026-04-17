/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:31:53 by tamatsuu          #+#    #+#             */
/*   Updated: 2026/04/17 18:04:54 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/calc.h"

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

// this funciton will return the index of object which is nearest
// -1 means there is no object which camera ray hit
// 各オブジェクト判定は
// まず tmp_hit に書く
// 本当に「今の最短」だったときだけ hit_p に反映する
int	hit_nearest_obj(t_obj *obj, t_ray *ray, t_hit_point *hit_p)
{
	t_obj		*obj_cpy;
	t_hit_point	tmp_hit;
	double		tmp_dist;
	int			i;
	int			ret;

	hit_p->dist = MAX_DIST + 1;
	hit_p->index = -1;
	ret = -1;
	i = 0;
	obj_cpy = obj;
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

// 各オブジェクト判定は
// まず tmp_hit に書く
// 本当に「今の最短」だったときだけ hit_p に反映する
int	hit_shadow_ray(t_obj *obj, t_ray *sh_ray, t_hit_point *hit_p)
{
	t_obj		*obj_cpy;
	t_hit_point	tmp_hit;
	double		tmp_dist;
	int			i;
	int			ret;

	ret = -1;
	i = 0;
	obj_cpy = obj;
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

void	set_face_normal(t_ray *ray, t_hit_point *h_obj)
{
	if (dot(ray->dir, h_obj->norm) > 0)
		h_obj->norm = vec_scale(h_obj->norm, -1.0);
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
