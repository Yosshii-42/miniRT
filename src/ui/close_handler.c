/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:49:41 by tamatsuu          #+#    #+#             */
/*   Updated: 2026/04/17 20:23:03 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/ui.h"
#include <mlx.h>
#include <stdlib.h>
#include <X11/keysym.h>

int	key_handler(int keycode, t_mlx_env *mlx)
{
	if (keycode == XK_Escape)
		close_btn_click(mlx);
	return (0);
}

int	close_btn_click(t_mlx_env *mlx)
{
	t_env	*env;
	t_obj	*obj;

	env = set_get_env(GET, NULL);
	obj = set_get_obj(GET, NULL);
	free_obj(obj, mlx);
	if (mlx->img)
	{
		free(mlx->img);
		mlx->img = NULL;
	}
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_lit(env->lit);
	free(env);
	exit(0);
}
