/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosshii <yosshii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:19:44 by yotsurud          #+#    #+#             */
/*   Updated: 2026/04/19 14:55:35 by yosshii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_meta_img(t_meta_img *tex)
{
	tex->img = NULL;
	tex->addr = NULL;
	tex->width = 0;
	tex->height = 0;
	tex->bits_per_pixel = 0;
	tex->line_length = 0;
	tex->endian = 0;
}

void	init_xyz(t_xyz *xyz)
{
	xyz->x = 0.0;
	xyz->y = 0.0;
	xyz->z = 0.0;
}

void	init_env(t_env *env, t_lit *lit, int part)
{
	env->part = part;
	env->flag[A] = 0;
	env->flag[C] = 0;
	env->flag[L] = 0;
	env->amb_t = 0;
	init_xyz(&env->amb_rgb);
	init_xyz(&env->cam_xyz);
	init_xyz(&env->cam_vector);
	env->cam_degree = 0.0;
	env->lit = lit;
}

void	init_lit(t_lit *lit)
{
	lit->flag = 0;
	init_xyz(&lit->xyz);
	lit->t = 0;
	init_xyz(&lit->rgb);
	lit->valid_flag = true;
	lit->next = NULL;
}

void	init_obj(t_obj *obj)
{
	obj->id = -1;
	obj->material = DEFAULT;
	init_xyz(&obj->xyz);
	init_xyz(&obj->vector);
	init_xyz(&obj->rgb);
	obj->diameter = 0.0;
	obj->height = 0.0;
	obj->texture = -1;
	obj->filename = NULL;
	init_meta_img(&obj->tex);
	obj->next = NULL;
}
