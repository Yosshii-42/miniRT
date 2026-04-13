/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_divid_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 05:28:37 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/12 16:32:37 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_xyz	vec_add(t_xyz a, t_xyz b)
{
	t_xyz	tmp;

	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	tmp.z = a.z + b.z;
	return (tmp);
}

t_xyz	vec_sub(t_xyz a, t_xyz b)
{
	t_xyz	tmp;

	tmp.x = a.x - b.x;
	tmp.y = a.y - b.y;
	tmp.z = a.z - b.z;
	return (tmp);
}

t_xyz	vec_mul(t_xyz a, t_xyz b)
{
	t_xyz	tmp;

	tmp.x = a.x * b.x;
	tmp.y = a.y * b.y;
	tmp.z = a.z * b.z;
	return (tmp);
}

t_xyz	vec_scale(t_xyz v, double s)
{
	t_xyz	tmp;

	tmp.x = v.x * s;
	tmp.y = v.y * s;
	tmp.z = v.z * s;
	return (tmp);
}

t_xyz	vec_div(t_xyz v, double s)
{
	t_xyz	tmp;

	tmp.x = v.x / s;
	tmp.y = v.y / s;
	tmp.z = v.z / s;
	return (tmp);
}
