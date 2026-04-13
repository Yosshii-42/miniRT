/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_screen_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:47:58 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/20 21:49:00 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ui.h"
#include "raytracing.h"
#include "calc.h"
#include <math.h>

double	convert_x_to_screen(int x)
{
	double	ret;
	double	aspect_ratio;

	aspect_ratio = (double)W_WIDTH / (double)W_HEIGHT;
	ret = 2 * x;
	ret = ret / (W_WIDTH - 1) - 1;
	return (ret * aspect_ratio);
}

double	convert_y_to_screen(int y)
{
	double	ret;

	ret = -2 * y;
	ret = ret / (W_HEIGHT - 1) + 1;
	return (ret);
}

void	set_screen_vector(t_xyz *screen, int x, int y, double fov)
{
	double	scale;

	scale = tan(deg_to_rad(fov * 0.5));
	screen->x = convert_x_to_screen(x) * scale;
	screen->y = convert_y_to_screen(y) * scale;
	screen->z = 0;
}

