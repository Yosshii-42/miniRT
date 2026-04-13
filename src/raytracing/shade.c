/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:09:51 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 20:40:43 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include <math.h>
#include "../../includes/calc.h"

// this function calculate shade.
// shade including diffuse reflection and specular reflection
t_xyz	calc_shade(t_obj *obj, t_lit *lit, t_hit_point hit_obj, t_ray cam_ray)
{
	double	dot_res;
	t_xyz	reverse_vec;
	t_xyz	view_dir;
	double	specular_ref;
	t_xyz	incident_dir;

	specular_ref = 0.0;
	incident_dir = vec_sub(lit->xyz, hit_obj.pos);
	incident_dir = normalize(incident_dir);
	dot_res = fmax(dot(incident_dir, hit_obj.norm), 0.0);
	if (dot_res > 0)
	{
		reverse_vec = vec_sub(
			vec_scale(hit_obj.norm, 2 * dot_res), incident_dir);
		reverse_vec = normalize(reverse_vec);
		view_dir = normalize(vec_sub(cam_ray.pos, hit_obj.pos));
		specular_ref = dot(reverse_vec, view_dir);
		specular_ref = pow(clamp_double(specular_ref, 0.0, 1.0), SHINENESS);
	}
	return (pls_shade(obj, lit, dot_res, specular_ref));
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
