/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:09:51 by tamatsuu          #+#    #+#             */
/*   Updated: 2026/05/03 23:49:41 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "calc.h"
#include <math.h>

static inline t_data_set	set_data(t_obj *obj, t_lit *lit, t_hit_point hit)
{
	t_data_set	data;

	data.obj = obj;
	data.lit = lit;
	data.hit_p = hit;
	return (data);
}

static t_xyz	pls_shade(t_data_set data, double diff_ref, double spec_ref)
{
	t_xyz	dif_col;
	t_xyz	spec_col;
	t_xyz	lit_rgb;
	t_xyz	base_color;
	t_xyz	ret_col;

	base_color = get_optional_color(data.obj, data.hit_p);
	lit_rgb = data.lit->rgb;
	lit_rgb = vec_div(lit_rgb, 255.0);
	dif_col = vec_scale(vec_mul(base_color, lit_rgb), diff_ref);
	dif_col = vec_scale(dif_col, data.lit->t);
	if (data.obj->id == PL)
		spec_ref *= 0.2;
	spec_col = vec_scale(vec_scale(lit_rgb, 255.0), spec_ref);
	spec_col = vec_scale(spec_col, data.lit->t);
	ret_col = vec_add(dif_col, spec_col);
	return (ret_col);
}

// this function calculate shade.
// shade including diffuse reflection and specular reflection
t_xyz	calc_shade(t_obj *obj, t_lit *lit, t_hit_point hit_obj, t_ray cam_ray)
{
	t_xyz			reverse_vec;
	t_xyz			view_dir;
	t_xyz			incident_dir;
	t_shade_data	s;

	s.specular_ref = 0.0;
	incident_dir = vec_sub(lit->xyz, hit_obj.pos);
	s.light_dist = vec_length(incident_dir);
	incident_dir = normalize(incident_dir);
	s.attenuation = 1.0 / (1.0 + 0.0001 * s.light_dist * s.light_dist);
	s.dot_res = fmax(dot(incident_dir, hit_obj.norm), 0.0);
	s.dot_res *= s.attenuation;
	if (s.dot_res > 0)
	{
		reverse_vec = vec_sub(
				vec_scale(hit_obj.norm, 2 * s.dot_res), incident_dir);
		reverse_vec = normalize(reverse_vec);
		view_dir = normalize(vec_sub(cam_ray.pos, hit_obj.pos));
		s.specular_ref = dot(reverse_vec, view_dir);
		s.specular_ref = pow(clamp_double(s.specular_ref, 0.0, 1.0), SHINENESS);
		s.specular_ref *= s.attenuation;
	}
	return (pls_shade(set_data(obj, lit, hit_obj), s.dot_res, s.specular_ref));
}

void	pls_amb_color(t_obj *obj, t_env *env, t_xyz *col, t_hit_point hit)
{
	t_xyz	base_color;

	base_color = get_optional_color(obj, hit);
	col->x = base_color.x * (env->amb_rgb.x / 255.0) * env->amb_t;
	col->y = base_color.y * (env->amb_rgb.y / 255.0) * env->amb_t;
	col->z = base_color.z * (env->amb_rgb.z / 255.0) * env->amb_t;
}
