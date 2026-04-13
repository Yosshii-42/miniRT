/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:29:01 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/20 18:52:46 by tamatsuu         ###   ########.fr       */
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

bool	solve_quadratic(double abc[3], double *t0, double *t1)
{
	double	d;
	double	tmp;

	if (fabs(abc[0]) < EPS)
		return (false);
	d = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (d < -EPS)
		return (false);
	if (d < 0.0)
		d = 0.0;
	d = sqrt(d);
	*t0 = (-abc[1] - d) / (2.0 * abc[0]);
	*t1 = (-abc[1] + d) / (2.0 * abc[0]);
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