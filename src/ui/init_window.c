/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:54:11 by tamatsuu          #+#    #+#             */
/*   Updated: 2026/04/26 14:48:48 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "ui.h"
#include "calc.h"
#include <mlx.h>
#include <math.h>

static void	load_textures(t_mlx_env *mlx, t_obj *obj)
{
	while (obj)
	{
		if (obj->f_mat_tex == IM && obj->filename)
		{
			obj->tex.img = mlx_xpm_file_to_image(
					mlx->mlx, obj->filename, &obj->tex.width, &obj->tex.height
					);
			if (!obj->tex.img)
				print_error_and_exit("image load error", obj->filename);
			obj->tex.addr = mlx_get_data_addr(
					obj->tex.img, &obj->tex.bits_per_pixel,
					&obj->tex.line_length, &obj->tex.endian
					);
			if (!obj->tex.addr)
				print_error_and_exit("mlx_get_data_addr", "failed");
		}
		obj = obj->next;
	}
}

int	init_window(t_obj *obj, t_env *env)
{
	t_mlx_env	mlx;

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		print_error_and_exit("mlx_init", "failed");
	load_textures(&mlx, obj);
	mlx.window = mlx_new_window(mlx.mlx, W_WIDTH, W_HEIGHT, WIN_TITLE);
	if (!mlx.window)
		print_error_and_exit("mlx_new_window", "failed");
	mlx_key_hook(mlx.window, key_handler, &mlx);
	render_window(&mlx, obj, env);
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
		print_error_and_exit("malloc failed", "t_meta_img");
	mlx->img->img = mlx_new_image(mlx->mlx, W_WIDTH, W_HEIGHT);
	if (!mlx->img->img)
		print_error_and_exit("mlx_new_image failed", NULL);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img,
			&mlx->img->bits_per_pixel, &mlx->img->line_length,
			&mlx->img->endian);
	if (!mlx->img->addr)
		print_error_and_exit("mlx_get_data_addr failed", NULL);
	render_scene(mlx, obj, env);
	return (EXIT_SUCCESS);
}
