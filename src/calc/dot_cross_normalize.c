/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 05:28:28 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/12 16:31:10 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

double	dot(t_xyz v1, t_xyz v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_xyz	cross(t_xyz v1, t_xyz v2)
{
	t_xyz	tmp;

	tmp.x = v1.y * v2.z - v1.z * v2.y;
	tmp.y = v1.z * v2.x - v1.x * v2.z;
	tmp.z = v1.x * v2.y - v1.y * v2.x;
	return (tmp);
}

t_xyz	normalize(t_xyz v)
{
	double	length;

	length = vec_length(v);
	return (vec_div(v, length));
}
