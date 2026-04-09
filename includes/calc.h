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

// dot_cross.c
double	dot(t_xyz v1, t_xyz v2);
t_xyz	cross(t_xyz v1, t_xyz v2);

// multi_sub_vector.c
t_xyz	multi_v1_v2(t_xyz v1, t_xyz v2);
t_xyz	multi_v_f(t_xyz v, double f);
t_xyz	divid_v_f(t_xyz v, double f);

// plus_minus_vector.c
t_xyz	plus_v1_v2(t_xyz v1, t_xyz v2);
t_xyz	minus_v1_v2(t_xyz v1, t_xyz v2);

// normalize.c
double	sqr(double x);
double	calc_length2(t_xyz vector);
double	calc_length(t_xyz vector);
t_xyz	normalize(t_xyz vector);

// distance_vector.c
double	squared_norm(t_xyz v);
double	distance_between(t_xyz a, t_xyz b);

//
bool	solve_quadratic(double abc[3], double *t0, double *t1);

#endif
