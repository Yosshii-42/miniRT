/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:18:54 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/26 14:50:33 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "calc.h"
#include <math.h>

t_xyz	get_optional_color(t_obj *obj, t_hit_point hit)
{
	if (obj->id == PL && obj->f_mat_tex == IM
		&& (obj->vector.y == 1 || obj->vector.y == -1))
		return (get_pl_texture_color(obj, hit, &(obj->tex)));
	if (obj->id == PL && obj->f_mat_tex == CH
		&& (obj->vector.y == 1 || obj->vector.y == -1))
		return (get_pl_checker_color(obj, hit));
	if (obj->id == SP && obj->f_mat_tex == IM)
		return (get_sp_texture_color(obj, hit, &(obj->tex)));
	else if (obj->id == SP && obj->f_mat_tex == CH)
		return (get_sp_checker_color(obj, hit));
	return (obj->rgb);
}

unsigned int	get_tex_pixel(t_meta_img *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_xyz	color_from_int(unsigned int c)
{
	return (make_xyz((c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF));
}
