/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:54:11 by tamatsuu          #+#    #+#             */
/*   Updated: 2026/04/15 16:59:27 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracing.h"
#include "ui.h"
#include "calc.h"
#include <mlx.h>
#include <math.h>

int	init_window(t_obj *data, t_env *env)
{
	t_mlx_env	mlx;
	t_meta_img	tex;

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		print_error_and_exit("mlx_init failed", NULL);
	mlx.window = mlx_new_window(mlx.mlx, W_WIDTH, W_HEIGHT, WIN_TITLE);
	if (!mlx.window)
		print_error_and_exit("mlx_new_window failed", NULL);
	tex.img = mlx_xpm_file_to_image(mlx.mlx, "earth.xpm", &tex.width, &tex.height);
	tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel, &tex.line_length, &tex.endian);
	env->tex = tex;
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
		print_error_and_exit("malloc failed", "t_meta_img");
	mlx->img->img = mlx_new_image(mlx->mlx, W_WIDTH, W_HEIGHT);
	if (!mlx->img->img)
		print_error_and_exit("mlx_new_image failed", NULL);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img,
			&mlx->img->bits_per_pixel, &mlx->img->line_length, &mlx->img->endian);
	if (!mlx->img->addr)
		print_error_and_exit("mlx_get_data_addr failed", NULL);
	render_scene(mlx, obj, env);
	return (EXIT_SUCCESS);
}
