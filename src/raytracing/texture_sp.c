/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:19:15 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/18 18:19:19 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "calc.h"
#include <math.h>

// p は球の表面上の位置を、中心基準で表す
// atan2(p.z, p.x) で横方向
// asin(p.y) で縦方向
void	get_sp_uv(t_obj *obj, t_hit_point hit, double *u, double *v)
{
	t_xyz	p;

	p = vec_sub(hit.pos, obj->xyz);
	p = normalize(p);
	*u = atan2(p.z, p.x) / (2.0 * M_PI) + 0.5;
	*v = 0.5 - asin(p.y) / M_PI;
}

t_xyz	get_sp_checker_color(t_obj *obj, t_hit_point hit)
{
	double	u;
	double	v;
	int		iu;
	int		iv;
	// double	scale;

	get_sp_uv(obj, hit, &u, &v);
	// scale = 20.0;
	iu = (int)floor(u * SCALE_SP);
	iv = (int)floor(v * SCALE_SP);
	if (((iu + iv) & 1) == 0)
		return (make_xyz(255.0, 255.0, 255.0));
	return (make_xyz(obj->rgb.x, obj->rgb.y, obj->rgb.z));
}

t_xyz	get_sp_texture_color(t_obj *obj, t_hit_point hit, t_meta_img *tex)
{
	double			u;
	double			v;
	int				px;
	int				py;
	unsigned int	c;

	get_sp_uv(obj, hit, &u, &v);
	px = (int)(u * (tex->width - 1));
	py = (int)(v * (tex->height - 1));
	c = get_tex_pixel(tex, px, py);
	return (color_from_int(c));
}
