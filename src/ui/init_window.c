/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:54:11 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 20:44:33 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/ui.h"
#include "../../includes/calc.h"
#include <mlx.h>
#include <math.h>

int	init_window(t_obj *data, t_env *env)
{
	t_mlx_env	mlx;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, W_WIDTH, W_HEIGHT, WIN_TITLE);
	mlx_key_hook(mlx.window, key_handler, &mlx);
	render_window(&mlx, data, env);
	mlx_hook(mlx.window, DESTROY_NOTIFY, 0, close_btn_click, &mlx);
	mlx_loop(mlx.mlx);
	return (EXIT_SUCCESS);
}

int	render_window(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	if (!mlx || !obj || !env)
		print_error_and_exit("render_window", "arg is NULL");
	mlx->img = malloc(sizeof(t_meta_img));
	if (!mlx->img)
		print_error_and_exit("mlx_new_image failed", NULL);
	mlx->img->img = mlx_new_image(mlx->mlx, W_WIDTH, W_HEIGHT);
	if (!mlx->img->img)
		print_error_and_exit("mlx_new_image failed", NULL);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, \
		&mlx->img->bits_per_pixel, &mlx->img->line_length, &mlx->img->endian);
	if (!mlx->img->addr)
		print_error_and_exit("mlx_new_image failed", NULL);
	render_scene(mlx, obj, env);
	return (EXIT_SUCCESS);
}

t_obj	get_indexed_obj(int index, t_obj *obj)
{
	t_obj	*ret;
	int		j;

	ret = obj;
	if (!obj)
		print_error_and_exit("get_indexed_obj", "obj is null");
	if (index < 0)
		return (*obj);
	j = -1;
	while (ret && ++j != index)
		ret = ret->next;
	return (*ret);
}

void	reset_light_flags(t_env *env)
{
	t_lit	*l = env->lit;
	while (l)
	{
		l->valid_flag = true;
		l = l->next;
	}
}

int	render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	int		x;
	int		y;
	t_xyz	color;
	t_xyz	screen_vec;
	t_ray	cam_ray;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			init_xyz(&color);
			set_screen_vector(&screen_vec, x, y, env->cam_degree);
			cam_ray.pos = env->cam_xyz;
			cam_ray.dir = calc_cam_dir(screen_vec, env->cam_vector);
			reset_light_flags(env);
			check_light_pos(obj, env, cam_ray);
			ray_tracing(obj, env, cam_ray, &color);
			color_set_to_pixel \
				(mlx->img, x, y, make_trgb(0, color.x, color.y, color.z));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
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
	if (hit_obj.index >= 0)
	{
		pls_amb_color(&cpy_obj, env, color);
		// while (tmp_lit && tmp_lit->valid_flag)
		// {
		// 	ret = calc_shadow(obj, tmp_lit, &hit_obj);
		// 	if (ret == NOT_RENDERED_SHADOW)
		// 		*color = vec_add(
		// 			calc_shade(&cpy_obj, tmp_lit, hit_obj, cam_ray), *color);
		// 	tmp_lit = tmp_lit->next;
		// }
		while (tmp_lit)
		{
			if (tmp_lit->valid_flag)
			{
				ret = calc_shadow(obj, tmp_lit, &hit_obj);
				if (ret == NOT_RENDERED_SHADOW)
					*color = vec_add(calc_shade(&cpy_obj, tmp_lit, hit_obj, cam_ray), *color);
			}
			tmp_lit = tmp_lit->next;
		}
		return (clamp_xyz(color, 0, 255), 1);
	}
	return (0);
}
