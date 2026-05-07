/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:15:59 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/20 01:46:12 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "parser.h"
#include "raytracing.h"

static double	distance_sphere(double *abcd)
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

// check if cam_ray is hitting to sphere and return distance
double	hit_sphere(t_obj *obj, t_ray *ray)
{
	t_xyz	ray_to_obj;
	double	abcd[4];
	double	radius;
	double	ret;

	radius = obj->diameter / 2.0;
	ray_to_obj = vec_sub(ray->pos, obj->xyz);
	abcd[L_A] = vec_length_sq(ray->dir);
	abcd[L_B] = 2 * dot(ray->dir, ray_to_obj);
	abcd[L_C] = vec_length_sq(ray_to_obj) - radius * radius;
	abcd[L_D] = abcd[L_B] * abcd[L_B] - 4 * abcd[L_A] * abcd[L_C];
	if (abcd[L_D] < 0)
		return (NO_HIT);
	ret = distance_sphere(abcd);
	return (ret);
}
