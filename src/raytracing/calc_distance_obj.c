/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:55:12 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/20 23:39:45 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/ui.h"
#include <math.h>
#include "../../includes/raytracing.h"
#include "../../includes/calc.h"

double	distance_sphere(double *abcd)
{
	double	t[3];

	t[0] = -1;
	if (abcd[L_D] == 0)
		t[0] = (-1 * abcd[L_B]) / (2 * abcd[L_A]);
	else if (abcd[L_D] > 0)
	{
		t[1] = (-1 * abcd[L_B] + sqrt(abcd[L_D])) / (2 * abcd[L_A]);
		t[2] = (-1 * abcd[L_B] - sqrt(abcd[L_D])) / (2 * abcd[L_A]);
		if (t[1] > 0 && t[2] > 0)
			t[0] = fmin(t[1], t[2]);
		else if (t[1] > 0)
			t[0] = t[1];
		else if (t[2] > 0)
			t[0] = t[2];
	}
	return (t[0]);
}

double	get_nearest_inter_cy(t_obj *obj, t_xyz *h_pos, double *t, t_xyz norm_c)
{
	if (0 <= dot(minus_v1_v2(h_pos[0], obj->xyz), norm_c) \
	&& dot(minus_v1_v2(h_pos[0], obj->xyz), norm_c) <= obj->height)
		t[0] = t[1];
	if (0 <= dot(minus_v1_v2(h_pos[1], obj->xyz), norm_c) \
	&& dot(minus_v1_v2(h_pos[1], obj->xyz), norm_c) <= obj->height)
	{
		if (t[0] < 0 || t[2] < t[0])
			t[0] = t[2];
	}
	return (t[0]);
}

double	hit_cylinder_caps(t_obj *obj, t_ray *ray, t_xyz norm_c)
{
	t_xyz	caps[2];
	double	denom;
	double	t[3];
	int		i;
	t_xyz	d;

	i = 0;
	caps[0] = obj->xyz;
	caps[1] = plus_v1_v2(obj->xyz, multi_v_f(norm_c, obj->height));
	t[0] = NO_HIT;
	denom = dot(ray->dir, norm_c);
	while (i < 2)
	{
		t[i + 1] = dot(minus_v1_v2(caps[i], ray->pos), norm_c) / denom;
		d = minus_v1_v2(plus_v1_v2(ray->pos, multi_v_f(ray->dir, t[i + 1])), \
		caps[i]);
		if (squared_norm(d) <= sqr(obj->diameter * 0.5))
		{
			if (t[0] < 0 || t[i + 1] < t[0])
				t[0] = t[i + 1];
		}
		i++;
	}
	return (t[0]);
}

double	dist_cylndr(double *abcd, t_obj *obj, t_ray *ray)
{
	double	t[4];
	t_xyz	hit_pos[2];
	t_xyz	norm_c;

	t[0] = NO_HIT;
	norm_c = normalize(obj->vector);
	if (abcd[L_D] < 0)
		return (NO_HIT);
	t[1] = (-1 * abcd[L_B] - sqrt(abcd[L_D])) / (2 * abcd[L_A]);
	t[2] = (-1 * abcd[L_B] + sqrt(abcd[L_D])) / (2 * abcd[L_A]);
	hit_pos[0] = plus_v1_v2(ray->pos, multi_v_f(ray->dir, t[1]));
	hit_pos[1] = plus_v1_v2(ray->pos, multi_v_f(ray->dir, t[2]));
	t[0] = get_nearest_inter_cy(obj, hit_pos, t, norm_c);
	t[3] = hit_cylinder_caps(obj, ray, norm_c);
	if ((t[0] < 0 && 0 < t[3]) || t[3] < t[0])
		t[0] = t[3];
	return (t[0]);
}
