/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_pl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:19:08 by yotsurud          #+#    #+#             */
/*   Updated: 2026/05/01 18:16:18 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "calc.h"
#include <math.h>

t_xyz	get_pl_texture_color(t_obj *obj, t_hit_point hit, t_meta_img *tex)
{
	double			u;
	double			v;
	int				px;
	int				py;
	unsigned int	color;

	(void)obj;
	u = hit.pos.x * 0.01;
	v = hit.pos.z * 0.01;
	u = (hit.pos.x + 50.0) / 100.0;
	v = (hit.pos.z + 50.0) / 100.0;
	if (u < 0.0 || u > 1.0 || v < 0.0 || v > 1.0)
		return (obj->rgb);
	px = (int)(u * (tex->width - 1));
	py = (int)((1.0 - v) * (tex->height - 1));
	color = get_tex_pixel(tex, px, py);
	return (color_from_int(color));
}

t_xyz	get_pl_checker_color(t_obj *obj, t_hit_point hit)
{
	int		check;
	int		ix;
	int		iz;
	// double	scale;

	// scale = 0.1;
	ix = (int)floor(hit.pos.x * SCALE_PL);
	iz = (int)floor(hit.pos.z * SCALE_PL);
	check = (ix + iz) & 1;
	if (check == 0)
		return (make_xyz(255.0, 255.0, 255.0));
	return (make_xyz(obj->rgb.x, obj->rgb.y, obj->rgb.z));
}
