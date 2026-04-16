/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:08:53 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/16 22:00:55 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "parser.h"
# include "types.h"

# define W_WIDTH 800
# define W_HEIGHT 450
# define WIN_TITLE "minirt"
# define DESTROY_NOTIFY 17

int		close_btn_click(t_mlx_env *mlx);
int		init_window(t_obj *obj, t_env *env);
int		render_window(t_mlx_env *mlx, t_obj *obj, t_env *env);
int		render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env);
double	hit_ray(t_obj *obj, t_env *env, t_xyz cam_dir);
int		key_handler(int keycode, t_mlx_env *mlx);

#endif
