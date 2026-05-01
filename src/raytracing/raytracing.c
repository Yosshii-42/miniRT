#include "raytracing.h"
#include "calc.h"

static t_xyz	calc_light_sum_color(t_scene *scene, t_shade_ctx *ctx)
{
	t_lit	*tmp_lit;
	t_xyz	color;
	int		shadow;

	tmp_lit = scene->lit;
	init_xyz(&color);
	while (tmp_lit)
	{
		if (tmp_lit->valid_flag)
		{
			shadow = calc_shadow(scene->obj, tmp_lit, &ctx->hit);
			if (shadow == NOT_RENDERED_SHADOW)
				color = vec_add(color,
						calc_shade(ctx->obj, tmp_lit, ctx->hit, ctx->ray));
		}
		tmp_lit = tmp_lit->next;
	}
	return (color);
}

static void	handle_bump(t_obj *obj, t_hit_point *hit)
{
	if (obj->id == SP)
		hit->norm = apply_bump_sp(obj, *hit);
	else
		hit->norm = apply_bump(hit);
}

t_xyz	ray_tracing(t_scene *scene, t_ray cam_ray, int depth)
{
	t_hit_point	hit_obj;
	t_obj		cpy_obj;
	t_xyz		color;
	t_shade_ctx	ctx;

	if (depth <= 0)
		return (make_xyz(0, 0, 0));
	init_xyz(&color);
	hit_obj.index = hit_nearest_obj(scene->obj, &cam_ray, &hit_obj);
	if (hit_obj.index < 0)
		return (make_xyz(0, 0, 0));
	cpy_obj = get_indexed_obj(hit_obj.index, scene->obj);
	fill_hit_obj(&cpy_obj, cam_ray, &hit_obj);
	if (cpy_obj.f_bump == ON)
		handle_bump(&cpy_obj, &hit_obj);
	if (cpy_obj.f_mat_tex == ME)
		return (calc_metal(scene, cam_ray, &hit_obj, depth));
	pls_amb_color(&cpy_obj, scene->env, &color, hit_obj);
	ctx = set_shade_data(&cpy_obj, hit_obj, cam_ray);
	color = vec_add(color, calc_light_sum_color(scene, &ctx));
	clamp_xyz(&color, 0, 255);
	return (color);
}
