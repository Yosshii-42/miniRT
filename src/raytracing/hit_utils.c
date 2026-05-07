/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:16:17 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/18 18:16:19 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "calc.h"

void	init_variables(int *ret, int *i, t_obj **obj_cpy, t_obj *obj)
{
	*ret = -1;
	*i = 0;
	*obj_cpy = obj;
}

void	init_hit_p(t_hit_point *hit)
{
	hit->dist = MAX_DIST + 1;
	hit->index = -1;
}

void	set_face_normal(t_ray *ray, t_hit_point *h_obj)
{
	if (dot(ray->dir, h_obj->norm) > 0)
		h_obj->norm = vec_scale(h_obj->norm, -1.0);
}
