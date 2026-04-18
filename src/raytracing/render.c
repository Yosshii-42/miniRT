/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:18:26 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/18 23:51:07 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "ui.h"
#include "calc.h"
#include <mlx.h>
#include <math.h>

static t_obj	get_indexed_obj(int index, t_obj *obj)
{
	t_obj	*ret;
	int		i;

	if (!obj)
		print_error_and_exit("get_indexed_obj", "obj is null");
	if (index < 0)
		print_error_and_exit("get_indexed_obj", "invalid index");
	ret = obj;
	i = 0;
	while (ret && i < index)
	{
		ret = ret->next;
		i++;
	}
	if (!ret)
		print_error_and_exit("get_indexed_obj", "index out of range");
	return (*ret);
}

static t_xyz	render_sample(t_obj *obj, t_env *env, double x, double y)
{
	t_xyz	screen_vec;
	t_xyz	color;
	t_ray	cam_ray;

	set_screen_vector(&screen_vec, x, y, env->cam_degree);
	cam_ray.pos = env->cam_xyz;
	cam_ray.dir = calc_cam_dir(screen_vec, env->cam_vector);
	reset_light_flags(env);
	ray_tracing(obj, env, cam_ray, &color);
	return (color);
}

static t_xyz	render_pixel(t_obj *obj, t_env *env, int x, int y)
{
	double	sx[4];
	double	sy[4];
	t_xyz	color;
	int		i;

	init_offset(sx, sy);
	init_xyz(&color);
	i = 0;
	while (i < 4)
	{
		color = vec_add(color, render_sample(obj, env, x + sx[i], y + sy[i]));
		i++;
	}
	return (vec_div(color, 4.0));
}

int	render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	double	x;
	double	y;
	t_xyz	color;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			color = render_pixel(obj, env, x, y);
			color_set_to_pixel
				(mlx->img, x, y, make_trgb(0, color.x, color.y, color.z));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx->img->img = NULL;
	return (EXIT_SUCCESS);
}

int	ray_tracing(t_obj *obj, t_env *env, t_ray cam_ray, t_xyz *color)
{
	t_hit_point	hit_obj;
	t_lit		*tmp_lit;
	t_obj		cpy_obj;
	int			ret;

	hit_obj.index = hit_nearest_obj(obj, &cam_ray, &hit_obj);
	if (hit_obj.index < 0)
		return (set_amb_col(color, env), 0);
	cpy_obj = get_indexed_obj(hit_obj.index, obj);
	fill_hit_obj(&cpy_obj, cam_ray, &hit_obj);
	tmp_lit = env->lit;
	pls_amb_color(&cpy_obj, env, color, hit_obj);
	while (tmp_lit)
	{
		if (tmp_lit->valid_flag)
		{
			ret = calc_shadow(obj, tmp_lit, &hit_obj);
			if (ret == NOT_RENDERED_SHADOW)
				*color = vec_add(calc_shade(&cpy_obj, tmp_lit, hit_obj,
							cam_ray), *color);
		}
		tmp_lit = tmp_lit->next;
	}
	return (clamp_xyz(color, 0, 255), 1);
	return (0);
}
