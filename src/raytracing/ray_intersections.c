/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:51:26 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 02:37:18 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/calc.h"
#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
// check if cam_ray is hitting to sphere and return distance
double	hit_sphere(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
{
	t_xyz	ray_to_obj;
	double	abcd[4];
	double	radius;
	double	ret;

	radius = obj->diameter / 2.0;
	ray_to_obj = minus_v1_v2(ray->pos, obj->xyz);
	abcd[L_A] = squared_norm(ray->dir);
	abcd[L_B] = 2 * dot(ray->dir, ray_to_obj);
	abcd[L_C] = squared_norm(ray_to_obj) - radius * radius;
	abcd[L_D] = abcd[L_B] * abcd[L_B] - 4 * abcd[L_A] * abcd[L_C];
	if (abcd[L_D] <= 0)
		return (NO_HIT);
	ret = distance_sphere(abcd);
	if (ret > 0 && rec_hit && 0)
		set_hit_obj(obj, ray, h_obj, ret);
	return (ret);
}

//ray : →p = →s + t→d
//plane: (→p・→n)= 0
// t = - (→s・→n) / (→d・→n) t> 0 のとき交点を持つ
double	hit_plane(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
{
	t_xyz	p_norm;
	double	numerator;
	double	denominator;
	double	ret;

	p_norm = normalize(obj->vector);
	denominator = dot(ray->dir, p_norm);
	if (denominator)
	{
		numerator = -1 * dot(minus_v1_v2(ray->pos, obj->xyz), p_norm);
		if (!numerator)
			return (-1);
		ret = numerator / denominator;
		if (ret > 0 && rec_hit && 0)
			set_hit_obj(obj, ray, h_obj, ret);
		return (ret);
	}
	return (-1);
}

// 軸を正規化
// top/bottom centerを作る
//　side
// cap
// cap
// 一番近いものを採用
double	hit_cylinder(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
{
	t_cy		cy;
	t_hit_point	tmp;

	cy.ray = *ray;
	cy.obj = obj;
	cy.axis = normalize(obj->vector);
	cy.radius = obj->diameter / 2.0;
	cy.half_h = obj->height / 2.0;
	cy.min = EPS;
	cy.max = MAX_DIST;
	if (!hit_cy_core(&cy, &tmp))
		return (NO_HIT);
	if (rec_hit)
		*h_obj = tmp;
	return (tmp.dist);
}

// double	hit_cylinder(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
// {
// 	t_xyz	ray_to_obj;
// 	double	abcd[4];
// 	double	radius;
// 	t_xyz	norm_cylinder;

// 	radius = obj->diameter / 2.0;
// 	norm_cylinder = normalize(obj->vector);
// 	ray_to_obj = minus_v1_v2(ray->pos, obj->xyz);
// 	abcd[L_A] = squared_norm(cross(ray->dir, norm_cylinder));
// 	abcd[L_B] = dot(cross(ray->dir, norm_cylinder), \
// 	cross(ray_to_obj, norm_cylinder)) * 2;
// 	abcd[L_C] = dot(cross(ray_to_obj, norm_cylinder), \
// 	cross(ray_to_obj, norm_cylinder)) - sqr(radius);
// 	if (abcd[L_A] == 0)
// 		return (NO_HIT);
// 	abcd[L_D] = abcd[L_B] * abcd[L_B] - 4 * abcd[L_A] * abcd[L_C];
// 	if (abcd[L_D] <= 0)
// 		return (NO_HIT);
// 	if (rec_hit)
// 		return (dist_cylndr(abcd, obj, ray, h_obj));
// 	return (dist_cylndr(abcd, obj, ray, NULL));
// }



double	hit_cam_ray(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit)
{
	if (obj->id == SP)
		return (hit_sphere(obj, ray, h_obj, rec_hit));
	else if (obj->id == PL)
		return (hit_plane(obj, ray, h_obj, rec_hit));
	else if (obj->id == CY)
		return (hit_cylinder(obj, ray, h_obj, rec_hit));
	return (NO_HIT);
}
