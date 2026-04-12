/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nearest_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:08:26 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 20:41:19 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"

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
	ret = -1;
	i = 0;
	obj_cpy = obj;
	while(obj_cpy)
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
	// t_obj	*obj_cpy;
	// double	tmp;
	// int		i;
	// int		ret;

	// hit_p->dist = MAX_DIST + 1;
	// ret = -1;
	// i = 0;
	// obj_cpy = obj;
	// while (obj_cpy)
	// {
	// 	tmp = hit_cam_ray(obj_cpy, ray, hit_p, true);
	// 	if (tmp > 0 && tmp < MAX_DIST && tmp < hit_p->dist)
	// 	{
	// 		hit_p->dist = tmp;
	// 		hit_p->index = i;
	// 		ret = i;
	// 	}
	// 	obj_cpy = obj_cpy->next;
	// 	i++;
	// }
	// if (hit_p->dist == MAX_DIST + 1)
	// 	hit_p->dist = -1;
	// return (ret);
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

	// t_obj	*obj_cpy;
	// double	tmp;
	// int		i;
	// int		ret;

	// ret = -1;
	// i = 0;
	// obj_cpy = obj;
	// while (obj_cpy)
	// {
	// 	if (hit_p->index == i)
	// 	{
	// 		tmp = hit_cam_ray(obj_cpy, sh_ray, hit_p, false);
	// 		if (tmp > EPSILON && tmp < MAX_DIST && tmp < hit_p->dist)
	// 		{
	// 			hit_p->dist = tmp;
	// 			ret = i;
	// 		}
	// 	}
	// 	obj_cpy = obj_cpy->next;
	// 	i++;
	// }
	// return (ret);
}
