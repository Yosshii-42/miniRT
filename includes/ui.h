/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:08:53 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/20 01:56:55 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "parser.h"
# include "types.h"

# define W_WIDTH 1600
# define W_HEIGHT 900
# define WIN_TITLE "minirt"
# define DESTROY_NOTIFY 17

// init_window.c
int		init_window(t_obj *obj, t_env *env);
int		render_window(t_mlx_env *mlx, t_obj *obj, t_env *env);

// close_handler.c
int		close_btn_click(t_mlx_env *mlx);
int		key_handler(int keycode, t_mlx_env *mlx);

#endif
