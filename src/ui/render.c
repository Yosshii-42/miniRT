/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:18:26 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/30 23:40:39 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "ui.h"
#include "calc.h"
#include <mlx.h>
#include <math.h>

static t_xyz	render_sample(t_scene *scene, double x, double y)
{
	t_xyz	screen_vec;
	t_xyz	color;
	t_ray	cam_ray;
	int		depth;

	set_screen_vector(&screen_vec, x, y, scene->env->cam_degree);
	cam_ray.pos = scene->env->cam_xyz;
	cam_ray.dir = calc_cam_dir(screen_vec, scene->env->cam_vector);
	reset_light_flags(scene->env);
	depth = 5;
	color = ray_tracing(scene, cam_ray, depth);
	return (color);
}

static t_xyz	render_pixel(t_scene *scene, int x, int y)
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
		color = vec_add(color, render_sample(scene, x + sx[i], y + sy[i]));
		i++;
	}
	return (vec_div(color, 4.0));
}

int	render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	double	x;
	double	y;
	t_xyz	color;
	t_scene	scene;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			scene = set_scene_data(env, obj);
			color = render_pixel(&scene, x, y);
			color_set_to_pixel(mlx->img, x, y,
				make_trgb(0, color.x, color.y, color.z));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx->img->img = NULL;
	return (EXIT_SUCCESS);
}
