/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:53:22 by yotsurud          #+#    #+#             */
/*   Updated: 2026/05/07 14:54:12 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "calc.h"

// get height using the color brightness
static double	get_bump_height(t_meta_img *img, double u, double v)
{
	unsigned int	color;
	int				x;
	int				y;
	t_xyz			rgb;

	if (!img || !img->addr || img->width <= 0 || img->height <= 0)
		return (0.0);
	u = u - floor(u);
	v = v - floor(v);
	x = (int)(u * (img->width - 1));
	y = (int)(v * (img->height - 1));
	color = get_tex_pixel(img, x, y);
	init_xyz(&rgb);
	rgb.x = (color >> 16) & 0xFF;
	rgb.y = (color >> 8) & 0xFF;
	rgb.z = color & 0xFF;
	return ((0.299 * rgb.x + 0.587 * rgb.y + 0.114 * rgb.z) / 255.0);
}

static void	set_bump_data(t_bump *b, t_obj *obj, t_hit_point hit)
{
	get_sp_uv(obj, hit, &(b->u), &(b->v));
	b->du = 1.0 / obj->tex.width;
	b->dv = 1.0 / obj->tex.height;
	b->h = get_bump_height(&obj->tex, b->u, b->v);
	b->h = (b->h - 0.5) * 2.0;
	b->hx = get_bump_height(&obj->tex, b->u + b->du, b->v);
	b->hy = get_bump_height(&obj->tex, b->u, b->v + b->dv);
	b->hx = (b->hx - 0.5) * 2.0;
	b->hy = (b->hy - 0.5) * 2.0;
	b->dx = b->hx - b->h;
	b->dy = b->hy - b->h;
	b->strength = 5.0;
}

t_xyz	apply_bump_sp(t_obj *obj, t_hit_point hit)
{
	t_bump	bump;
	t_xyz	norm;
	t_xyz	tangent;
	t_xyz	bitangent;

	set_bump_data(&bump, obj, hit);
	norm = hit.norm;
	if (fabs(norm.y) < 0.999)
		tangent = normalize(cross((t_xyz){0, 1, 0}, norm));
	else
		tangent = normalize(cross((t_xyz){1, 0, 0}, norm));
	bitangent = normalize(cross(norm, tangent));
	norm = vec_add(norm, vec_scale(tangent, bump.dx * bump.strength));
	norm = vec_add(norm, vec_scale(bitangent, bump.dy * bump.strength));
	return (normalize(norm));
}

t_xyz	apply_bump(t_hit_point *hit)
{
	t_xyz	norm;
	double	f;
	double	g;

	norm = hit->norm;
	f = sin(hit->pos.x * 2.0 + hit->pos.z * 4.0) * 0.15;
	f += sin(hit->pos.x * 4.0 - hit->pos.z * 3.0) * 0.1;
	f += cos(hit->pos.x * 3.0 + hit->pos.z * 4.0) * 0.07;
	g = cos(hit->pos.x * 2.0 - hit->pos.z * 2.0) * 0.15;
	g += sin(hit->pos.x * 3.0 + hit->pos.z * 5.0) * 0.1;
	norm.x += 0.03 * f;
	norm.z += 0.04 * g;
	norm.y += 0.01 * (f + g);
	return (normalize(norm));
}
