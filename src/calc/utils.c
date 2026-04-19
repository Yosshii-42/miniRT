/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:29:01 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/19 13:25:17 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "raytracing.h"

double	sqr(double x)
{
	return (x * x);
}

double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

bool	solve_quadratic(t_cy *cy, double *t0, double *t1)
{
	double	d;
	double	tmp;

	if (fabs(cy->a) < EPS)
		return (false);
	d = sqr(cy->b) - 4.0 * cy->a * cy->c;
	if (d < -EPS)
		return (false);
	if (d < 0.0)
		d = 0.0;
	d = sqrt(d);
	*t0 = (-cy->b - d) / (2.0 * cy->a);
	*t1 = (-cy->b + d) / (2.0 * cy->a);
	if (*t1 < *t0)
	{
		tmp = *t0;
		*t0 = *t1;
		*t1 = tmp;
	}
	return (true);
}

t_xyz	make_xyz(double x, double y, double z)
{
	t_xyz	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_xyz	refrect(t_xyz v, t_xyz n)
{
	return (vec_sub(v, vec_scale(n, 2.0 * dot(v, n))));
}
