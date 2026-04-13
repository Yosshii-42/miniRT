/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 06:14:16 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/20 18:54:00 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "parser.h"

// dot_cross_normalize.c
double	dot(t_xyz v1, t_xyz v2);
t_xyz	cross(t_xyz v1, t_xyz v2);
t_xyz	normalize(t_xyz v);

// arithmetic_operations.c
t_xyz	vec_add(t_xyz a, t_xyz b);
t_xyz	vec_sub(t_xyz a, t_xyz b);
t_xyz	vec_mul(t_xyz a, t_xyz b);
t_xyz	vec_scale(t_xyz v, double s);
t_xyz	vec_div(t_xyz v, double s);

// vec_length.c
double	vec_length_sq(t_xyz v);
double	vec_length(t_xyz v);
double	vec_dist(t_xyz a, t_xyz b);

// utils.c
double	sqr(double x);
double	deg_to_rad(double deg);
bool	solve_quadratic(double abc[3], double *t0, double *t1);
t_xyz	make_xyz(double x, double y, double z);

#endif
