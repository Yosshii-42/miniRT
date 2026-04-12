/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:22:21 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 19:23:54 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include <math.h>
#include "../../includes/calc.h"
#include "../../includes/ui.h"

int	set_amb_col(t_xyz *color, t_env *env)
{
	color->x = (env->amb_rgb.x / 255.0) * env->amb_t;
	color->y = (env->amb_rgb.y / 255.0) * env->amb_t;
	color->z = (env->amb_rgb.z / 255.0) * env->amb_t;
	return (0);
}

void	pls_amb_color(t_obj *obj, t_env *env, t_xyz *col)
{
	col->x = obj->rgb.x * (env->amb_rgb.x / 255.0) * env->amb_t;
	col->y = obj->rgb.y * (env->amb_rgb.y / 255.0) * env->amb_t;
	col->z = obj->rgb.z * (env->amb_rgb.z / 255.0) * env->amb_t;
}

t_xyz	pls_shade(t_obj *obj, t_lit *lit, double diff_ref, double spec_ref)
{
	t_xyz	dif_col;
	t_xyz	spec_col;
	t_xyz	ret_col;
	t_xyz	lit_rgb;

	lit_rgb = lit->rgb;
	lit_rgb = vec_div(lit_rgb, 255.0);
	dif_col = vec_scale(vec_mul(obj->rgb, lit_rgb), diff_ref);
	dif_col = vec_scale(dif_col, lit->t);
	spec_col = vec_scale(vec_scale(lit_rgb, 255.0), spec_ref);
	spec_col = vec_scale(spec_col, lit->t);
	ret_col = vec_add(dif_col, spec_col);
	return (ret_col);
}

void	color_set_to_pixel(t_meta_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
